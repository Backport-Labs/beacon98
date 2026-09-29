/* sign.c - checking the signature of the catalog.
 *
 * CATALOG.SIG holds an Ed25519 signature (RFC 8032) over the exact bytes of
 * CATALOG.TXT, made with the Backport Labs key. The public key is built into
 * the program; nothing downloaded can replace it. The mathematics is done by
 * TweetNaCl (tweetnacl.c).
 */
#include "beacon.h"

/* Backport Labs catalog key, created 2026-09-28 (keys/beacon-signing-key.pub.txt). */
const char *g_keyId = "94f2f398cdde0384";
static const BYTE g_key[32] = {
    0x03, 0xb6, 0x86, 0x4e, 0xef, 0x48, 0xd5, 0x15, 0x4d, 0xbf, 0xfa, 0x61, 0x65, 0x3e, 0x2a, 0xce,
    0xf1, 0x3e, 0x32, 0x51, 0xe3, 0xca, 0x01, 0xce, 0x22, 0x56, 0x80, 0x95, 0x6d, 0x0c, 0xe3, 0x31
};

/* TweetNaCl asks for random bytes only to make keys, which Beacon never does. */
void randombytes(unsigned char *x, unsigned long long n)
{
    (void)x; (void)n;
    FatalAppExit(0, "Beacon 98: random bytes were requested, which the program never needs.");
}

/* Returns 1 when sig is a valid signature of msg under key. */
int VerifyBytes(const BYTE *msg, DWORD n, const BYTE sig[64], const BYTE key[32])
{
    BYTE *sm = (BYTE *)malloc(n + 64), *m = (BYTE *)malloc(n + 64);
    unsigned long long mlen = 0;
    int ok = 0;
    if (sm && m) {
        memcpy(sm, sig, 64);
        if (n) memcpy(sm + 64, msg, n);
        ok = crypto_sign_ed25519_tweet_open(m, &mlen, sm, (unsigned long long)n + 64, key) == 0 && mlen == n;
    }
    free(sm);
    free(m);
    return ok;
}

static char *ReadWhole(const char *path, DWORD *size)
{
    HANDLE f = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    DWORD n, got = 0;
    char *buf;
    if (f == INVALID_HANDLE_VALUE) return NULL;
    n = GetFileSize(f, NULL);
    buf = (char *)malloc(n + 1);
    if (buf && (!ReadFile(f, buf, n, &got, NULL) || got != n)) { free(buf); buf = NULL; }
    CloseHandle(f);
    if (buf) { buf[n] = 0; *size = n; }
    return buf;
}

/* Finds "Name: value" at the start of a line and copies the value. */
static int SigField(const char *text, const char *name, char *out, int outLen)
{
    int len = lstrlen(name), i;
    const char *p = text;
    while (*p) {
        if (strncmp(p, name, len) == 0 && p[len] == ':' && p[len + 1] == ' ') {
            p += len + 2;
            for (i = 0; i < outLen - 1 && p[i] && p[i] != '\r' && p[i] != '\n'; i++) out[i] = p[i];
            out[i] = 0;
            return 1;
        }
        while (*p && *p != '\n') p++;
        if (*p) p++;
    }
    return 0;
}

int VerifyCatalogFile(const char *catalog, const char *sigfile)
{
    return VerifyCatalogFileKey(catalog, sigfile, g_key);
}

/* The Key-Id of a key: the first 8 bytes of its SHA-256, in hexadecimal. */
void KeyIdOf(const BYTE key[32], char out[17])
{
    SHA256 s;
    BYTE h[32];
    Sha256Init(&s);
    Sha256Add(&s, key, 32);
    Sha256Done(&s, h);
    ToHex(h, 8, out);
}

/* Checks a catalog against a given public key (a custom source's). */
int VerifyCatalogFileKey(const char *catalog, const char *sigfile, const BYTE key[32])
{
    char *sigText, *text, keyId[40], hex[200], want[17];
    BYTE sig[64];
    DWORD sigSize, size;
    int result;
    KeyIdOf(key, want);
    sigText = ReadWhole(sigfile, &sigSize);
    if (!sigText) return SIG_NO_FILE;
    if (!SigField(sigText, "Key-Id", keyId, sizeof(keyId)) || !SigField(sigText, "Signature", hex, sizeof(hex))
        || lstrlen(hex) != 128 || !FromHex(hex, sig, 64)) {
        free(sigText);
        return SIG_BAD_FILE;
    }
    free(sigText);
    if (lstrcmp(keyId, want) != 0) return SIG_WRONG_KEY;
    text = ReadWhole(catalog, &size);
    if (!text) return SIG_NO_FILE;
    result = VerifyBytes((BYTE *)text, size, sig, key) ? SIG_OK : SIG_INVALID;
    free(text);
    return result;
}

const char *SigText(int result)
{
    switch (result) {
    case SIG_OK:        return "signed by Backport Labs, verified";
    case SIG_NO_FILE:   return "the catalog or its signature is missing";
    case SIG_BAD_FILE:  return "the signature file is damaged";
    case SIG_WRONG_KEY: return "signed with a key this program does not know";
    default:            return "THE SIGNATURE DOES NOT MATCH THE CATALOG";
    }
}
