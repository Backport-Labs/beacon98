/* catalog.c - reading CATALOG.TXT.
 *
 * The catalog is a text file of blocks separated by empty lines. The first
 * block describes the catalog, each further block one package. A block is
 * made of "Field: value" lines; a line that starts with a space continues the
 * field above it, and " ." stands for an empty line. Lines that start with #
 * are comments. See design/FORMAT.md.
 *
 * The catalog is only read after its signature has been checked (sign.c), but
 * it is still read defensively: a package with a missing field is left out.
 */
#include "beacon.h"

const char *g_sections[MAX_SECTIONS] = {
    "Utilities", "Internet", "Multimedia", "Office", "Development", "Games", "System"
};

static const char *g_fieldNames[F_COUNT] = {
    "Package", "Name", "Version", "Section", "Summary", "Description",
    "Homepage", "License", "License-File", "Systems", "Availability",
    "Download", "Source", "Installed-Size", "Depends", "Requires",
    "Install", "After", "Shortcut", "Uninstall", "Warning", "Notice",
    "Remove"
};

static const int g_required[] = {
    F_PACKAGE, F_NAME, F_VERSION, F_SECTION, F_SUMMARY, F_LICENSE, F_LICENSE_FILE,
    F_SYSTEMS, F_DOWNLOAD, F_INSTALL, F_UNINSTALL
};

int SectionIndex(const char *name)
{
    int i;
    for (i = 0; i < MAX_SECTIONS; i++)
        if (name && lstrcmp(name, g_sections[i]) == 0) return i;
    return -1;
}

void FirstLine(const char *text, char *out, int outLen)
{
    int i;
    for (i = 0; i < outLen - 1 && text && text[i] && text[i] != '\n'; i++) out[i] = text[i];
    out[i] = 0;
}

static void CopyHeader(char *dst, int dstLen, const char *value)
{
    lstrcpyn(dst, value, dstLen);
}

/* Adds up the sizes on the Download lines: "path size sha256". */
static DWORD DownloadBytes(const char *lines)
{
    DWORD total = 0;
    const char *p = lines;
    while (p && *p) {
        while (*p && *p != ' ' && *p != '\n') p++;
        if (*p == ' ') total += strtoul(p + 1, NULL, 10);
        while (*p && *p != '\n') p++;
        if (*p) p++;
    }
    return total;
}

/* Whether some Download line offers the file from the catalog's own server
 * (a location that is a path, not an http:// address). */
static int HostedHere(const char *lines)
{
    const char *p = lines;
    int word = 0;
    while (p && *p) {
        while (*p == ' ') p++;
        if (*p == '\n') { p++; word = 0; continue; }
        if (!*p) break;
        if (word != 1 && word != 2 && strncmp(p, "http://", 7) != 0) return 1;   /* words 1 and 2 are size and hash */
        while (*p && *p != ' ' && *p != '\n') p++;
        word++;
    }
    return 0;
}

static int PkgComplete(PKG *p)
{
    int i;
    for (i = 0; i < (int)(sizeof(g_required) / sizeof(g_required[0])); i++)
        if (!p->f[g_required[i]] || !p->f[g_required[i]][0]) return 0;
    return 1;
}

int LoadCatalog(const char *path, CATALOG *cat, char *err, int errLen)
{
    HANDLE f;
    DWORD size, got;
    char *text, *line, *next, *out, *value;
    char **field = NULL;          /* the field being written, for continuation lines */
    int block = 0, inBlock = 0, i, len, lineNo = 0, format = 0, cap = 0;
    PKG *cur = NULL;
    char header[5][256];          /* Format, Serial, Date, Expires, Base */

    memset(cat, 0, sizeof(*cat));
    memset(header, 0, sizeof(header));
    err[0] = 0;
    f = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (f == INVALID_HANDLE_VALUE) { lstrcpyn(err, "The catalog file was not found.", errLen); return 0; }
    size = GetFileSize(f, NULL);
    text = (char *)malloc(size + 2);
    cat->pool = (char *)malloc(size + 2);
    if (!text || !cat->pool || !ReadFile(f, text, size, &got, NULL) || got != size) {
        CloseHandle(f);
        free(text);
        FreeCatalog(cat);
        lstrcpyn(err, "The catalog file could not be read.", errLen);
        return 0;
    }
    CloseHandle(f);
    text[size] = '\n';
    text[size + 1] = 0;
    out = cat->pool;

    for (line = text; *line; line = next) {
        lineNo++;
        next = strchr(line, '\n');
        *next++ = 0;
        len = lstrlen(line);
        if (len && line[len - 1] == '\r') line[--len] = 0;

        if (len == 0) {                                   /* end of a block */
            if (inBlock) {
                if (field) { *out++ = 0; field = NULL; }
                if (block > 0 && cur && !PkgComplete(cur)) cat->count--;   /* leave it out */
                inBlock = 0;
                block++;
            }
            continue;
        }
        if (line[0] == '#') continue;
        if (line[0] == ' ') {                             /* continuation */
            if (!field) continue;
            *out++ = '\n';
            value = line + 1;
            if (lstrcmp(value, ".") == 0) value = "";
            lstrcpy(out, value);
            out += lstrlen(value);
            continue;
        }
        if (field) { *out++ = 0; field = NULL; }
        value = strstr(line, ": ");
        if (!value) continue;
        *value = 0;
        value += 2;

        if (!inBlock) {
            inBlock = 1;
            if (block > 0) {
                if (cat->count == cap) {
                    PKG *grown;
                    cap = cap ? cap * 2 : 16;
                    grown = (PKG *)realloc(cat->pkg, cap * sizeof(PKG));
                    if (!grown) { lstrcpyn(err, "Not enough memory for the catalog.", errLen); break; }
                    cat->pkg = grown;
                }
                cur = &cat->pkg[cat->count++];
                memset(cur, 0, sizeof(*cur));
            }
        }
        if (block == 0) {
            static const char *names[5] = { "Format", "Serial", "Date", "Expires", "Base" };
            for (i = 0; i < 5; i++) if (lstrcmp(line, names[i]) == 0) CopyHeader(header[i], 256, value);
            continue;
        }
        for (i = 0; i < F_COUNT; i++) {
            if (lstrcmp(line, g_fieldNames[i]) == 0) {
                cur->f[i] = out;
                lstrcpy(out, value);
                out += lstrlen(value);
                field = &cur->f[i];
                break;
            }
        }
    }
    if (field) *out++ = 0;
    if (inBlock && block > 0 && cur && !PkgComplete(cur)) cat->count--;
    free(text);

    format = atoi(header[0]);
    if (!err[0] && format != 1) lstrcpyn(err, "The catalog is in a format this version of Beacon does not know. Please update Beacon 98.", errLen);
    if (!err[0] && (!header[1][0] || !header[4][0])) lstrcpyn(err, "The catalog has no serial number or base address.", errLen);
    if (err[0]) { FreeCatalog(cat); return 0; }

    lstrcpyn(cat->serial, header[1], sizeof(cat->serial));
    lstrcpyn(cat->date, header[2], sizeof(cat->date));
    lstrcpyn(cat->expires, header[3], sizeof(cat->expires));
    lstrcpyn(cat->base, header[4], sizeof(cat->base));
    for (i = 0; i < cat->count; i++) {
        PKG *p = &cat->pkg[i];
        p->bytes = DownloadBytes(p->f[F_DOWNLOAD]);
        p->external = (p->f[F_AVAILABILITY] && lstrcmp(p->f[F_AVAILABILITY], "external") == 0) || !HostedHere(p->f[F_DOWNLOAD]);
    }
    return 1;
}

void FreeCatalog(CATALOG *cat)
{
    free(cat->pkg);
    free(cat->pool);
    memset(cat, 0, sizeof(*cat));
}

PKG *FindPkg(CATALOG *cat, const char *id)
{
    int i;
    for (i = 0; i < cat->count; i++)
        if (lstrcmp(cat->pkg[i].f[F_PACKAGE], id) == 0) return &cat->pkg[i];
    return NULL;
}
