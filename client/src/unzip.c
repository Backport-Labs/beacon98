/* unzip.c - unpacking ZIP files, for packages that have no setup program.
 *
 * Reads the central directory at the end of the archive, then inflates each
 * entry in pieces of 32 KB, so a large file never has to fit in memory.
 * Self-extracting archives work too: their offsets are corrected by the size
 * of the program in front. Each file's CRC-32 is checked. Names that would
 * leave the target folder are refused.
 *
 * Decompression is done by miniz 3.1.2 (vendor/miniz, MIT license), which is
 * compiled into this file with only its inflate part.
 */
#include "beacon.h"

#define MINIZ_NO_STDIO
#define MINIZ_NO_TIME
#define MINIZ_NO_ARCHIVE_APIS
#define MINIZ_NO_DEFLATE_APIS
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES
#include "../vendor/miniz/miniz.c"

#define SIG_EOCD    0x06054b50
#define SIG_CENTRAL 0x02014b50
#define SIG_LOCAL   0x04034b50

static DWORD g_crcTable[256];

static void CrcInit(void)
{
    DWORD c;
    int i, k;
    if (g_crcTable[1]) return;
    for (i = 0; i < 256; i++) {
        c = (DWORD)i;
        for (k = 0; k < 8; k++) c = c & 1 ? 0xEDB88320 ^ (c >> 1) : c >> 1;
        g_crcTable[i] = c;
    }
}

static DWORD Crc(DWORD crc, const BYTE *p, DWORD n)
{
    crc = ~crc;
    while (n--) crc = g_crcTable[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return ~crc;
}

static DWORD U16(const BYTE *p) { return p[0] | (p[1] << 8); }
static DWORD U32(const BYTE *p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((DWORD)p[3] << 24); }

static int ReadAt(HANDLE f, DWORD pos, void *buf, DWORD n)
{
    DWORD got;
    if (SetFilePointer(f, pos, NULL, FILE_BEGIN) == 0xFFFFFFFF) return 0;
    return ReadFile(f, buf, n, &got, NULL) && got == n;
}

/* Makes every folder of path (not the last part, which is the file). */
static void MakeFolders(const char *path, UNZIP_LOG log, void *ctx)
{
    char dir[MAX_PATH];
    int i;
    for (i = 0; path[i] && i < MAX_PATH - 1; i++) {
        dir[i] = path[i];
        if (path[i] == '\\' && i > 2) {
            dir[i] = 0;
            if (GetFileAttributes(dir) == 0xFFFFFFFF && CreateDirectory(dir, NULL) && log) log('D', dir, ctx);
            dir[i] = '\\';
        }
    }
}

/* Turns an archive name into a path below target, dropping the first strip
 * folders. Returns 0 for a name that must not be unpacked, and 2 for a
 * folder entry or a name that is dropped entirely. */
static int SafePath(const char *target, const char *name, int strip, char *out)
{
    char part[MAX_PATH];
    const char *p = name;
    int o, i, isDir;
    if (name[0] == '/' || name[0] == '\\' || (name[0] && name[1] == ':')) return 0;
    lstrcpyn(out, target, MAX_PATH);
    o = lstrlen(out);
    if (o && out[o - 1] != '\\') out[o++] = '\\';
    out[o] = 0;
    isDir = name[0] && (name[lstrlen(name) - 1] == '/' || name[lstrlen(name) - 1] == '\\');
    while (*p) {
        for (i = 0; *p && *p != '/' && *p != '\\' && i < MAX_PATH - 1; i++) part[i] = *p++;
        part[i] = 0;
        if (*p) p++;
        if (!i) continue;
        if (lstrcmp(part, "..") == 0 || strchr(part, ':')) return 0;
        if (lstrcmp(part, ".") == 0) continue;
        if (strip > 0) { strip--; continue; }
        if (o + i + 2 >= MAX_PATH) return 0;
        if (out[o - 1] != '\\') out[o++] = '\\';
        lstrcpy(out + o, part);
        o += i;
    }
    if (strip > 0 || out[o - 1] == '\\') return 2;
    return isDir ? 2 : 1;
}

/* Unpacks archive into target. log, when given, is told of every file ('F')
 * and folder ('D') that is created, so they can be removed again. */
int Unzip(const char *archive, const char *target, int strip, volatile int *cancel,
          UNZIP_LOG log, void *ctx, char *err, int errLen)
{
    static BYTE inBuf[16384], dict[TINFL_LZ_DICT_SIZE], tail[65557];
    BYTE hdr[46], local[30];
    char name[MAX_PATH], path[MAX_PATH];
    HANDLE f, out = INVALID_HANDLE_VALUE;
    DWORD size, tailLen, i, entries, cdSize, cdOffset, eocd = 0, delta, pos;
    DWORD method, crcWant, compSize, fullSize, nameLen, extraLen, commentLen, localOffset, dataPos;
    DWORD left, crc, written, outDone, got;
    tinfl_decompressor inf;
    int ok = 0, n, kind;

    err[0] = 0;
    CrcInit();
    f = CreateFile(archive, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (f == INVALID_HANDLE_VALUE) { lstrcpyn(err, "The archive cannot be opened.", errLen); return 0; }
    size = GetFileSize(f, NULL);
    tailLen = size < sizeof(tail) ? size : sizeof(tail);
    if (tailLen < 22 || !ReadAt(f, size - tailLen, tail, tailLen)) { lstrcpyn(err, "The archive is too short.", errLen); goto done; }
    for (i = tailLen - 22 + 1; i-- > 0; ) if (U32(tail + i) == SIG_EOCD) { eocd = size - tailLen + i; break; }
    if (!eocd && U32(tail) != SIG_EOCD) { lstrcpyn(err, "This is not a ZIP archive.", errLen); goto done; }
    i = eocd - (size - tailLen);
    entries = U16(tail + i + 10);
    cdSize = U32(tail + i + 12);
    cdOffset = U32(tail + i + 16);
    if (cdOffset + cdSize > eocd) { lstrcpyn(err, "The archive's directory is damaged.", errLen); goto done; }
    delta = eocd - (cdOffset + cdSize);          /* the size of a program in front, if any */

    MakeFolders(target, log, ctx);
    if (GetFileAttributes(target) == 0xFFFFFFFF) {
        if (!CreateDirectory(target, NULL)) { wsprintf(err, "The folder %s cannot be made.", target); goto done; }
        if (log) log('D', target, ctx);
    }
    pos = cdOffset + delta;
    for (n = 0; n < (int)entries; n++) {
        if (cancel && *cancel) { lstrcpyn(err, "Cancelled.", errLen); goto done; }
        if (!ReadAt(f, pos, hdr, 46) || U32(hdr) != SIG_CENTRAL) { lstrcpyn(err, "The archive's directory is damaged.", errLen); goto done; }
        method = U16(hdr + 10);
        crcWant = U32(hdr + 16);
        compSize = U32(hdr + 20);
        fullSize = U32(hdr + 24);
        nameLen = U16(hdr + 28);
        extraLen = U16(hdr + 30);
        commentLen = U16(hdr + 32);
        localOffset = U32(hdr + 42) + delta;
        if (nameLen >= MAX_PATH || !ReadAt(f, pos + 46, name, nameLen)) { lstrcpyn(err, "A name in the archive is too long.", errLen); goto done; }
        name[nameLen] = 0;
        pos += 46 + nameLen + extraLen + commentLen;
        if (U16(hdr + 8) & 1) { lstrcpyn(err, "The archive is encrypted.", errLen); goto done; }

        kind = SafePath(target, name, strip, path);
        if (kind == 0) { wsprintf(err, "The archive contains an unsafe name: %s", name); goto done; }
        if (kind == 2) continue;
        if (method != 0 && method != 8) { wsprintf(err, "%s uses a compression method Beacon 98 does not know.", name); goto done; }
        if (!ReadAt(f, localOffset, local, 30) || U32(local) != SIG_LOCAL) { lstrcpyn(err, "The archive is damaged.", errLen); goto done; }
        dataPos = localOffset + 30 + U16(local + 26) + U16(local + 28);

        MakeFolders(path, log, ctx);
        out = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (out == INVALID_HANDLE_VALUE) { wsprintf(err, "%s cannot be written. Is the program running?", path); goto done; }
        if (log) log('F', path, ctx);
        SetFilePointer(f, dataPos, NULL, FILE_BEGIN);
        crc = 0;
        outDone = 0;
        left = compSize;
        if (method == 0) {
            while (left) {
                DWORD take = left < sizeof(inBuf) ? left : sizeof(inBuf);
                if (!ReadFile(f, inBuf, take, &got, NULL) || got != take) { lstrcpyn(err, "The archive is cut short.", errLen); goto done; }
                if (!WriteFile(out, inBuf, take, &written, NULL) || written != take) { lstrcpyn(err, "The disk is full.", errLen); goto done; }
                crc = Crc(crc, inBuf, take);
                outDone += take;
                left -= take;
            }
        } else {
            size_t inAvail = 0, dictPos = 0, inUsed, outLen;
            BYTE *inPtr = inBuf;
            tinfl_status st;
            tinfl_init(&inf);
            for (;;) {
                if (!inAvail && left) {
                    DWORD take = left < sizeof(inBuf) ? left : sizeof(inBuf);
                    if (!ReadFile(f, inBuf, take, &got, NULL) || got != take) { lstrcpyn(err, "The archive is cut short.", errLen); goto done; }
                    inPtr = inBuf;
                    inAvail = take;
                    left -= take;
                }
                inUsed = inAvail;
                outLen = TINFL_LZ_DICT_SIZE - dictPos;
                st = tinfl_decompress(&inf, inPtr, &inUsed, dict, dict + dictPos, &outLen,
                                      left ? TINFL_FLAG_HAS_MORE_INPUT : 0);
                inPtr += inUsed;
                inAvail -= inUsed;
                if (outLen) {
                    if (!WriteFile(out, dict + dictPos, (DWORD)outLen, &written, NULL) || written != outLen) { lstrcpyn(err, "The disk is full.", errLen); goto done; }
                    crc = Crc(crc, dict + dictPos, (DWORD)outLen);
                    outDone += (DWORD)outLen;
                    dictPos = (dictPos + outLen) & (TINFL_LZ_DICT_SIZE - 1);
                }
                if (st == TINFL_STATUS_DONE) break;
                if (st < 0 || (st == TINFL_STATUS_NEEDS_MORE_INPUT && !left && !inAvail)) {
                    wsprintf(err, "%s is damaged in the archive.", name);
                    goto done;
                }
                if (cancel && *cancel) { lstrcpyn(err, "Cancelled.", errLen); goto done; }
            }
        }
        CloseHandle(out);
        out = INVALID_HANDLE_VALUE;
        if (outDone != fullSize || crc != crcWant) { wsprintf(err, "%s does not match its checksum in the archive.", name); goto done; }
    }
    ok = 1;
done:
    if (out != INVALID_HANDLE_VALUE) CloseHandle(out);
    CloseHandle(f);
    return ok;
}
