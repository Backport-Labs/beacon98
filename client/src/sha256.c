/* sha256.c - SHA-256 (FIPS 180-4), used to check every downloaded file
 * against the catalog.
 */
#include "beacon.h"

static const DWORD K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define ROR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

static void Block(SHA256 *s, const BYTE *p)
{
    DWORD w[64], a, b, c, d, e, f, g, h, t1, t2;
    int i;
    for (i = 0; i < 16; i++)
        w[i] = ((DWORD)p[i * 4] << 24) | ((DWORD)p[i * 4 + 1] << 16) | ((DWORD)p[i * 4 + 2] << 8) | p[i * 4 + 3];
    for (i = 16; i < 64; i++)
        w[i] = (ROR(w[i - 2], 17) ^ ROR(w[i - 2], 19) ^ (w[i - 2] >> 10)) + w[i - 7]
             + (ROR(w[i - 15], 7) ^ ROR(w[i - 15], 18) ^ (w[i - 15] >> 3)) + w[i - 16];
    a = s->h[0]; b = s->h[1]; c = s->h[2]; d = s->h[3];
    e = s->h[4]; f = s->h[5]; g = s->h[6]; h = s->h[7];
    for (i = 0; i < 64; i++) {
        t1 = h + (ROR(e, 6) ^ ROR(e, 11) ^ ROR(e, 25)) + ((e & f) ^ (~e & g)) + K[i] + w[i];
        t2 = (ROR(a, 2) ^ ROR(a, 13) ^ ROR(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }
    s->h[0] += a; s->h[1] += b; s->h[2] += c; s->h[3] += d;
    s->h[4] += e; s->h[5] += f; s->h[6] += g; s->h[7] += h;
}

void Sha256Init(SHA256 *s)
{
    static const DWORD start[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    memcpy(s->h, start, sizeof(start));
    s->len = 0;
    s->bitsLo = s->bitsHi = 0;
}

void Sha256Add(SHA256 *s, const void *data, DWORD n)
{
    const BYTE *p = (const BYTE *)data;
    DWORD lo = s->bitsLo + (n << 3);
    if (lo < s->bitsLo) s->bitsHi++;
    s->bitsHi += n >> 29;
    s->bitsLo = lo;
    while (n) {
        if (s->len == 0 && n >= 64) {
            Block(s, p);
            p += 64; n -= 64;
        } else {
            DWORD take = 64 - s->len;
            if (take > n) take = n;
            memcpy(s->buf + s->len, p, take);
            s->len += take; p += take; n -= take;
            if (s->len == 64) { Block(s, s->buf); s->len = 0; }
        }
    }
}

void Sha256Done(SHA256 *s, BYTE out[32])
{
    DWORD hi = s->bitsHi, lo = s->bitsLo;
    BYTE pad = 0x80, zero = 0, len[8];
    int i;
    for (i = 0; i < 4; i++) {
        len[i] = (BYTE)(hi >> (24 - 8 * i));
        len[4 + i] = (BYTE)(lo >> (24 - 8 * i));
    }
    Sha256Add(s, &pad, 1);
    while (s->len != 56) Sha256Add(s, &zero, 1);
    Sha256Add(s, len, 8);
    for (i = 0; i < 8; i++) {
        out[i * 4] = (BYTE)(s->h[i] >> 24);
        out[i * 4 + 1] = (BYTE)(s->h[i] >> 16);
        out[i * 4 + 2] = (BYTE)(s->h[i] >> 8);
        out[i * 4 + 3] = (BYTE)s->h[i];
    }
}

/* Hashes a whole file. Returns 0 when the file cannot be read. */
int Sha256File(const char *path, BYTE out[32], DWORD *size)
{
    static BYTE buf[32768];
    HANDLE f = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    SHA256 s;
    DWORD got, total = 0;
    int ok = 1;
    if (f == INVALID_HANDLE_VALUE) return 0;
    Sha256Init(&s);
    for (;;) {
        if (!ReadFile(f, buf, sizeof(buf), &got, NULL)) { ok = 0; break; }
        if (!got) break;
        Sha256Add(&s, buf, got);
        total += got;
    }
    CloseHandle(f);
    Sha256Done(&s, out);
    if (size) *size = total;
    return ok;
}

void ToHex(const BYTE *b, int n, char *out)
{
    static const char digits[] = "0123456789abcdef";
    int i;
    for (i = 0; i < n; i++) {
        out[i * 2] = digits[b[i] >> 4];
        out[i * 2 + 1] = digits[b[i] & 15];
    }
    out[n * 2] = 0;
}

static int Nibble(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

/* Reads exactly n bytes written as 2n hexadecimal digits. Returns 1 on success. */
int FromHex(const char *s, BYTE *out, int n)
{
    int i, hi, lo;
    for (i = 0; i < n; i++) {
        hi = Nibble(s[i * 2]);
        if (hi < 0) return 0;
        lo = Nibble(s[i * 2 + 1]);
        if (lo < 0) return 0;
        out[i] = (BYTE)(hi * 16 + lo);
    }
    return 1;
}
