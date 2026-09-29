/* tls.c - HTTPS for Windows 95 and 98, which cannot use the encryption
 * current servers require.
 *
 * Beacon carries its own TLS: BearSSL 0.6 (vendor/bearssl, MIT license) over
 * Windows Sockets 1.1, which every Windows 95 and 98 computer has. The
 * certificate authorities it trusts are Mozilla's list (vendor/cacert,
 * MPL 2.0), built into the program; a CAROOTS.PEM next to the program
 * replaces it.
 *
 * Certificates are checked against the date. Old computers often have a
 * wrong clock, so when the clock is clearly wrong (before this program was
 * built, or more than ten years after), Beacon uses the date from the answer
 * header of its own server instead, and says so. Every downloaded file is
 * still checked against the SHA-256 in the signed catalog; TLS keeps the
 * download private and reaches servers that no longer speak plain HTTP.
 */
#include "beacon.h"
#include "../vendor/bearssl/inc/bearssl.h"

/* ------------------------------------------------------------------------
 * Windows Sockets 1.1 (WSOCK32.DLL); Tiny C Compiler has no header for it
 * --------------------------------------------------------------------- */
typedef unsigned int SOCK;
#define BAD_SOCK ((SOCK)(~0))
#define MY_AF_INET 2
#define MY_SOCK_STREAM 1
#define MY_FIONBIO 0x8004667EL
typedef struct { short family; unsigned short port; unsigned long addr; char zero[8]; } MY_SOCKADDR;
typedef struct { char *name; char **aliases; short type, length; char **addrs; } MY_HOSTENT;
typedef struct { WORD version, highVersion; char description[257], status[129]; unsigned short maxSockets, maxUdp; char *vendor; } MY_WSADATA;
typedef struct { unsigned int count; SOCK socks[64]; } MY_FDSET;
typedef struct { long sec, usec; } MY_TIMEVAL;
int WINAPI WSAStartup(WORD, MY_WSADATA *);
int WINAPI WSAGetLastError(void);
MY_HOSTENT * WINAPI gethostbyname(const char *);
unsigned long WINAPI inet_addr(const char *);
unsigned short WINAPI htons(unsigned short);
SOCK WINAPI socket(int, int, int);
int WINAPI connect(SOCK, const MY_SOCKADDR *, int);
int WINAPI ioctlsocket(SOCK, long, unsigned long *);
int WINAPI select(int, MY_FDSET *, MY_FDSET *, MY_FDSET *, const MY_TIMEVAL *);
int WINAPI send(SOCK, const char *, int, int);
int WINAPI recv(SOCK, char *, int, int);
int WINAPI closesocket(SOCK);

#define TIMEOUT_S 60                    /* no data for this long ends a connection */

extern const char g_cacerts[];          /* made by the build from vendor/cacert/cacert.pem */

/* ------------------------------------------------------------------------
 * Randomness: BearSSL asks br_prng_seeder_system for a seeder. Windows 95
 * and 98 have CryptGenRandom only where Internet Explorer installed it, so it
 * is looked up when the program runs, and mixed with timers and counters.
 * --------------------------------------------------------------------- */
typedef BOOL (WINAPI *ACQUIRE_FN)(ULONG_PTR *, LPCSTR, LPCSTR, DWORD, DWORD);
typedef BOOL (WINAPI *GENRANDOM_FN)(ULONG_PTR, DWORD, BYTE *);
typedef BOOL (WINAPI *RELEASE_FN)(ULONG_PTR, DWORD);

static int Seed(const br_prng_class **ctx)
{
    struct {
        BYTE crypt[32];
        LARGE_INTEGER counter;
        DWORD tick, pid, tid;
        FILETIME now;
        MEMORYSTATUS mem;
        POINT cursor;
        void *stack;
    } e;
    SHA256 s;
    BYTE out[32];
    HMODULE adv = LoadLibrary("ADVAPI32.DLL");
    ACQUIRE_FN acquire = adv ? (ACQUIRE_FN)GetProcAddress(adv, "CryptAcquireContextA") : NULL;
    GENRANDOM_FN gen = adv ? (GENRANDOM_FN)GetProcAddress(adv, "CryptGenRandom") : NULL;
    RELEASE_FN release = adv ? (RELEASE_FN)GetProcAddress(adv, "CryptReleaseContext") : NULL;
    ULONG_PTR prov;
    memset(&e, 0, sizeof(e));
    if (acquire && gen && release && acquire(&prov, NULL, NULL, 1 /* PROV_RSA_FULL */, 0xF0000000 /* VERIFYCONTEXT */)) {
        gen(prov, sizeof(e.crypt), e.crypt);
        release(prov, 0);
    }
    QueryPerformanceCounter(&e.counter);
    e.tick = GetTickCount();
    e.pid = GetCurrentProcessId();
    e.tid = GetCurrentThreadId();
    GetSystemTimeAsFileTime(&e.now);
    e.mem.dwLength = sizeof(e.mem);
    GlobalMemoryStatus(&e.mem);
    GetCursorPos(&e.cursor);
    e.stack = &e;
    Sha256Init(&s);
    Sha256Add(&s, &e, sizeof(e));
    Sha256Done(&s, out);
    (*ctx)->update(ctx, out, sizeof(out));
    if (adv) FreeLibrary(adv);
    return 1;
}

br_prng_seeder br_prng_seeder_system(const char **name)
{
    if (name) *name = "beacon";
    return Seed;
}

/* ------------------------------------------------------------------------
 * Trusted certificate authorities
 * --------------------------------------------------------------------- */
static br_x509_trust_anchor *g_tas;
static size_t g_ntas;

typedef struct { BYTE *data; size_t len, cap; } BLOB;

static void BlobAdd(void *ctx, const void *data, size_t len)
{
    BLOB *b = (BLOB *)ctx;
    if (b->len + len > b->cap) {
        size_t cap = b->cap ? b->cap * 2 : 2048;
        BYTE *grown;
        while (cap < b->len + len) cap *= 2;
        grown = (BYTE *)realloc(b->data, cap);
        if (!grown) return;
        b->data = grown;
        b->cap = cap;
    }
    memcpy(b->data + b->len, data, len);
    b->len += len;
}

static BYTE *Dup(const void *p, size_t n)
{
    BYTE *d = (BYTE *)malloc(n ? n : 1);
    if (d) memcpy(d, p, n);
    return d;
}

/* Turns one DER certificate into a trust anchor. */
static void AddAnchor(const BYTE *der, size_t len)
{
    br_x509_decoder_context dc;
    br_x509_pkey *pk;
    br_x509_trust_anchor *ta, *grown;
    BLOB dn;
    memset(&dn, 0, sizeof(dn));
    br_x509_decoder_init(&dc, BlobAdd, &dn);
    br_x509_decoder_push(&dc, der, len);
    pk = br_x509_decoder_get_pkey(&dc);
    if (!pk || (pk->key_type != BR_KEYTYPE_RSA && pk->key_type != BR_KEYTYPE_EC)) { free(dn.data); return; }
    grown = (br_x509_trust_anchor *)realloc(g_tas, (g_ntas + 1) * sizeof(br_x509_trust_anchor));
    if (!grown) { free(dn.data); return; }
    g_tas = grown;
    ta = &g_tas[g_ntas];
    memset(ta, 0, sizeof(*ta));
    ta->dn.data = dn.data;
    ta->dn.len = dn.len;
    ta->flags = br_x509_decoder_isCA(&dc) ? BR_X509_TA_CA : 0;
    ta->pkey.key_type = pk->key_type;
    if (pk->key_type == BR_KEYTYPE_RSA) {
        ta->pkey.key.rsa.n = Dup(pk->key.rsa.n, pk->key.rsa.nlen);
        ta->pkey.key.rsa.nlen = pk->key.rsa.nlen;
        ta->pkey.key.rsa.e = Dup(pk->key.rsa.e, pk->key.rsa.elen);
        ta->pkey.key.rsa.elen = pk->key.rsa.elen;
    } else {
        ta->pkey.key.ec.curve = pk->key.ec.curve;
        ta->pkey.key.ec.q = Dup(pk->key.ec.q, pk->key.ec.qlen);
        ta->pkey.key.ec.qlen = pk->key.ec.qlen;
    }
    g_ntas++;
}

/* Reads every CERTIFICATE of a PEM text. */
static void LoadPem(const char *pem, size_t len)
{
    br_pem_decoder_context pc;
    BLOB der;
    int inCert = 0;
    memset(&der, 0, sizeof(der));
    br_pem_decoder_init(&pc);
    while (len > 0) {
        size_t used = br_pem_decoder_push(&pc, pem, len);
        pem += used;
        len -= used;
        switch (br_pem_decoder_event(&pc)) {
        case BR_PEM_BEGIN_OBJ:
            inCert = lstrcmp(br_pem_decoder_name(&pc), "CERTIFICATE") == 0;
            der.len = 0;
            br_pem_decoder_setdest(&pc, inCert ? BlobAdd : NULL, inCert ? &der : NULL);
            break;
        case BR_PEM_END_OBJ:
            if (inCert && der.len) AddAnchor(der.data, der.len);
            inCert = 0;
            break;
        case BR_PEM_ERROR:
            len = 0;
            break;
        }
    }
    free(der.data);
}

/* Loads the trust anchors once: CAROOTS.PEM next to the program, else the built-in list. */
size_t TrustAnchors(void)
{
    char path[MAX_PATH];
    HANDLE f;
    DWORD n, got;
    char *text;
    if (g_ntas) return g_ntas;
    wsprintf(path, "%sCAROOTS.PEM", g_dir);
    f = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (f != INVALID_HANDLE_VALUE) {
        n = GetFileSize(f, NULL);
        text = (char *)malloc(n + 1);
        if (text && ReadFile(f, text, n, &got, NULL) && got == n) LoadPem(text, n);
        free(text);
        CloseHandle(f);
    }
    if (!g_ntas) LoadPem(g_cacerts, lstrlen(g_cacerts));
    return g_ntas;
}

/* ------------------------------------------------------------------------
 * The date certificates are checked against
 * --------------------------------------------------------------------- */

/* Days from 1 January 1970 to a date (proleptic Gregorian calendar). */
static long DaysFromCivil(long y, unsigned m, unsigned d)
{
    long era;
    unsigned yoe, doy, doe;
    y -= m <= 2;
    era = (y >= 0 ? y : y - 399) / 400;
    yoe = (unsigned)(y - era * 400);
    doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + (long)doe - 719468;
}

static int MonthNumber(const char *m)
{
    static const char *names = "JanFebMarAprMayJunJulAugSepOctNovDec";
    int i;
    for (i = 0; i < 12; i++) if (strncmp(names + i * 3, m, 3) == 0) return i + 1;
    return 0;
}

/* Reads an HTTP date, "Tue, 29 Sep 2026 00:45:08 GMT", as days since
 * 1 January 1970 and seconds since midnight. Returns 1 on success. */
int ParseHttpDate(const char *s, long *days, long *secs)
{
    char mon[4];
    int d, y, h, mi, se, m;
    const char *comma = strchr(s, ',');
    if (comma) s = comma + 1;
    if (sscanf(s, " %d %3s %d %d:%d:%d", &d, mon, &y, &h, &mi, &se) != 6) return 0;
    m = MonthNumber(mon);
    if (!m || d < 1 || d > 31 || y < 1990 || h > 23 || mi > 59 || se > 60) return 0;
    *days = DaysFromCivil(y, m, d);
    *secs = h * 3600L + mi * 60 + se;
    return 1;
}

static long BuildDay(void)
{
    char mon[4];
    int d, y;
    sscanf(__DATE__, "%3s %d %d", mon, &d, &y);
    return DaysFromCivil(y, MonthNumber(mon), d);
}

static char g_clockNote[200];
static long g_dayOffset;                /* server day minus clock day, once measured */
static int g_offsetKnown;
static long g_testShift;                /* the self-test moves the clock by this many days */

const char *ClockNote(void) { return g_clockNote; }

/* Self-test only: pretend the clock is wrong by days, and forget what was measured. */
void TestShiftClock(long days)
{
    g_testShift = days;
    g_offsetKnown = 0;
    g_dayOffset = 0;
    g_clockNote[0] = 0;
}

/* The clock of this computer, as days and seconds since 1970. */
static void ClockNow(long *days, long *secs)
{
    FILETIME ft;
    unsigned long long x;
    GetSystemTimeAsFileTime(&ft);
    x = (((unsigned long long)ft.dwHighDateTime << 32) | ft.dwLowDateTime) / 10000000ULL;
    x -= 11644473600ULL;                /* 1601 to 1970 */
    *days = (long)(x / 86400) + g_testShift;
    *secs = (long)(x % 86400);
}

/* The date to check certificates against, as BearSSL counts it: days since
 * 1 January of year 0, seconds since midnight. */
static void CheckDate(unsigned long *brDays, unsigned long *brSecs)
{
    long days, secs, sDays, sSecs, build = BuildDay();
    char date[80];
    ClockNow(&days, &secs);
    if ((days < build - 1 || days > build + 3650) && !g_offsetKnown) {
        if (ServerDate(date, sizeof(date)) && ParseHttpDate(date, &sDays, &sSecs)) {
            g_dayOffset = sDays - days;
            g_offsetKnown = 1;
            wsprintf(g_clockNote, "The clock of this computer is wrong; certificates were checked against the date of %s (%s).", CATALOG_HOST, date);
        } else {
            g_dayOffset = build - days;
            g_offsetKnown = 1;
            lstrcpy(g_clockNote, "The clock of this computer is wrong; certificates were checked against the date Beacon 98 was built.");
        }
    }
    if (g_offsetKnown) days += g_dayOffset;
    *brDays = (unsigned long)(days + 719528);
    *brSecs = (unsigned long)secs;
}

/* ------------------------------------------------------------------------
 * Connections
 * --------------------------------------------------------------------- */
typedef struct {
    SOCK s;
    volatile int *cancel;
    int tls;
    br_sslio_context io;
} CONN;

static int g_wsaStarted;

/* Waits until the socket can be read (write = 0) or written. */
static int Wait(CONN *c, int write)
{
    MY_FDSET set;
    MY_TIMEVAL tv;
    int i, r;
    for (i = 0; i < TIMEOUT_S; i++) {
        if (c->cancel && *c->cancel) return 0;
        set.count = 1;
        set.socks[0] = c->s;
        tv.sec = 1;
        tv.usec = 0;
        r = select(0, write ? NULL : &set, write ? &set : NULL, NULL, &tv);
        if (r > 0) return 1;
        if (r < 0) return 0;
    }
    return 0;
}

static int RawRead(void *ctx, unsigned char *buf, size_t len)
{
    CONN *c = (CONN *)ctx;
    int n;
    if (!Wait(c, 0)) return -1;
    n = recv(c->s, (char *)buf, (int)len, 0);
    return n > 0 ? n : -1;
}

static int RawWrite(void *ctx, const unsigned char *buf, size_t len)
{
    CONN *c = (CONN *)ctx;
    int n;
    if (!Wait(c, 1)) return -1;
    n = send(c->s, (const char *)buf, (int)len, 0);
    return n > 0 ? n : -1;
}

static br_ssl_client_context g_sc;
static br_x509_minimal_context g_xc;
static unsigned char g_iobuf[BR_SSL_BUFSIZE_BIDI];

static int ConnRead(CONN *c, unsigned char *buf, int len)
{
    if (c->tls) return br_sslio_read(&c->io, buf, len);
    return RawRead(c, buf, len);
}

static int ConnWriteAll(CONN *c, const char *buf, int len)
{
    int n;
    if (c->tls) {
        if (br_sslio_write_all(&c->io, buf, len) < 0) return 0;
        return br_sslio_flush(&c->io) == 0;
    }
    while (len > 0) {
        n = RawWrite(c, (const unsigned char *)buf, len);
        if (n <= 0) return 0;
        buf += n;
        len -= n;
    }
    return 1;
}

static void TlsError(int e, char *err, int errLen)
{
    if (e == BR_ERR_X509_NOT_TRUSTED)
        lstrcpyn(err, "The server's certificate is not signed by an authority Beacon 98 trusts.", errLen);
    else if (e == BR_ERR_X509_BAD_SERVER_NAME)
        lstrcpyn(err, "The server's certificate is for another name.", errLen);
    else if (e == BR_ERR_X509_EXPIRED)
        lstrcpyn(err, "The server's certificate has expired or is not valid yet.", errLen);
    else if (e == BR_ERR_UNSUPPORTED_VERSION || e == BR_ERR_BAD_HANDSHAKE)
        lstrcpyn(err, "The server does not accept the encryption Beacon 98 offers (TLS 1.0 to 1.2).", errLen);
    else
        wsprintf(err, "The secure connection failed (TLS error %d).", e);
}

/* Opens a connection to host:port, with TLS when tls is set. */
static int Open(CONN *c, const char *host, int port, int tls, char *err, int errLen)
{
    MY_WSADATA wd;
    MY_SOCKADDR sa;
    MY_HOSTENT *he;
    unsigned long nb = 1, addr;
    unsigned long bd, bs;
    if (!g_wsaStarted) {
        if (WSAStartup(0x0101, &wd) != 0) { lstrcpyn(err, "Windows Sockets could not be started.", errLen); return 0; }
        g_wsaStarted = 1;
    }
    addr = inet_addr(host);
    if (addr == 0xFFFFFFFF) {
        he = gethostbyname(host);
        if (!he || !he->addrs || !he->addrs[0]) { wsprintf(err, "The name %s could not be found. Check the internet connection.", host); return 0; }
        memcpy(&addr, he->addrs[0], 4);
    }
    c->s = socket(MY_AF_INET, MY_SOCK_STREAM, 0);
    if (c->s == BAD_SOCK) { lstrcpyn(err, "A network connection could not be made.", errLen); return 0; }
    memset(&sa, 0, sizeof(sa));
    sa.family = MY_AF_INET;
    sa.port = htons((unsigned short)port);
    sa.addr = addr;
    ioctlsocket(c->s, MY_FIONBIO, &nb);             /* connect with a time limit */
    connect(c->s, &sa, sizeof(sa));
    if (!Wait(c, 1)) {
        closesocket(c->s);
        wsprintf(err, "Could not connect to %s.", host);
        return 0;
    }
    nb = 0;
    ioctlsocket(c->s, MY_FIONBIO, &nb);
    c->tls = tls;
    if (tls) {
        if (!TrustAnchors()) { closesocket(c->s); lstrcpyn(err, "No trusted certificate authorities could be read.", errLen); return 0; }
        br_ssl_client_init_full(&g_sc, &g_xc, g_tas, g_ntas);
        CheckDate(&bd, &bs);
        br_x509_minimal_set_time(&g_xc, bd, bs);
        br_ssl_engine_set_buffer(&g_sc.eng, g_iobuf, sizeof(g_iobuf), 1);
        if (!br_ssl_client_reset(&g_sc, host, 0)) {
            closesocket(c->s);
            TlsError(br_ssl_engine_last_error(&g_sc.eng), err, errLen);
            return 0;
        }
        br_sslio_init(&c->io, &g_sc.eng, RawRead, c, RawWrite, c);
    }
    return 1;
}

static void Close(CONN *c)
{
    if (c->tls) br_sslio_close(&c->io);
    closesocket(c->s);
}

/* ------------------------------------------------------------------------
 * HTTP/1.1 over a connection
 * --------------------------------------------------------------------- */
typedef struct {
    CONN *c;
    unsigned char buf[16384];
    int pos, len;
} READER;

static int Fill(READER *r)
{
    int n;
    if (r->pos < r->len) return 1;
    n = ConnRead(r->c, r->buf, sizeof(r->buf));
    if (n <= 0) return 0;
    r->pos = 0;
    r->len = n;
    return 1;
}

/* Reads one line without its CR LF. Returns 0 at the end of the stream. */
static int ReadLine(READER *r, char *out, int outLen)
{
    int o = 0;
    for (;;) {
        if (!Fill(r)) return 0;
        while (r->pos < r->len) {
            char ch = (char)r->buf[r->pos++];
            if (ch == '\n') {
                if (o && out[o - 1] == '\r') o--;
                out[o] = 0;
                return 1;
            }
            if (o < outLen - 1) out[o++] = ch;
        }
    }
}

/* Splits an address into scheme, host, port and path. */
int SplitUrl(const char *url, int *tls, char *host, int hostLen, int *port, char *path, int pathLen)
{
    const char *p;
    int i = 0;
    if (strncmp(url, "https://", 8) == 0) { *tls = 1; *port = 443; p = url + 8; }
    else if (strncmp(url, "http://", 7) == 0) { *tls = 0; *port = 80; p = url + 7; }
    else return 0;
    while (*p && *p != '/' && *p != ':' && i < hostLen - 1) host[i++] = *p++;
    host[i] = 0;
    if (!i) return 0;
    if (*p == ':') { *port = atoi(p + 1); while (*p && *p != '/') p++; }
    lstrcpyn(path, *p ? p : "/", pathLen);
    return 1;
}

/* GETs url over a socket (with TLS for https) and saves the body in path.
 * On a redirect, copies the Location to location and returns 1 without a
 * file; *status tells which. Returns 1 on success. */
int SockHttpGet(const char *url, const char *path, DWORD expect, volatile int *cancel,
                void (*progress)(DWORD done, DWORD total, void *ctx), void *pctx,
                int *status, char *location, int locLen, char *err, int errLen)
{
    static READER r;
    CONN c;
    char host[256], rpath[1024], req[1400], line[2048];
    int tls, port, chunked = 0, ok = 0, e;
    DWORD length = 0, done = 0, written, chunk;
    HANDLE out = INVALID_HANDLE_VALUE;
    int haveLength = 0;

    err[0] = 0;
    *status = 0;
    location[0] = 0;
    if (!SplitUrl(url, &tls, host, sizeof(host), &port, rpath, sizeof(rpath))) { lstrcpyn(err, "The address is not an http:// or https:// address.", errLen); return 0; }
    memset(&c, 0, sizeof(c));
    c.cancel = cancel;
    if (!Open(&c, host, port, tls, err, errLen)) return 0;
    if ((tls && port != 443) || (!tls && port != 80))
        wsprintf(req, "GET %s HTTP/1.1\r\nHost: %s:%d\r\n", rpath, host, port);
    else
        wsprintf(req, "GET %s HTTP/1.1\r\nHost: %s\r\n", rpath, host);
    lstrcat(req, "User-Agent: Beacon98/" APP_VERSION "\r\nAccept: */*\r\nAccept-Encoding: identity\r\nConnection: close\r\n\r\n");
    memset(&r, 0, sizeof(r));
    r.c = &c;
    if (!ConnWriteAll(&c, req, lstrlen(req)) || !ReadLine(&r, line, sizeof(line))) goto failed;
    if (strncmp(line, "HTTP/1.", 7) != 0 || lstrlen(line) < 12) { lstrcpyn(err, "The server did not answer in HTTP.", errLen); goto done; }
    *status = atoi(line + 9);
    for (;;) {                                              /* headers */
        if (!ReadLine(&r, line, sizeof(line))) goto failed;
        if (!line[0]) break;
        if (_strnicmp(line, "Content-Length:", 15) == 0) { length = strtoul(line + 15, NULL, 10); haveLength = 1; }
        else if (_strnicmp(line, "Transfer-Encoding:", 18) == 0 && strstr(line, "chunked")) chunked = 1;
        else if (_strnicmp(line, "Location:", 9) == 0) {
            const char *v = line + 9;
            while (*v == ' ') v++;
            lstrcpyn(location, v, locLen);
        }
    }
    if (*status >= 300 && *status < 400 && location[0]) { ok = 1; goto done; }
    if (*status != 200) { wsprintf(err, "The server answered %d.", *status); goto done; }
    if (expect && haveLength && length != expect) { wsprintf(err, "The server offers %lu bytes; the catalog lists %lu.", length, expect); goto done; }

    out = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (out == INVALID_HANDLE_VALUE) { wsprintf(err, "Could not write %s.", path); goto done; }
    for (;;) {
        DWORD want;
        if (cancel && *cancel) { lstrcpyn(err, "Cancelled.", errLen); goto done; }
        if (chunked) {
            if (!ReadLine(&r, line, sizeof(line))) goto failed;
            chunk = strtoul(line, NULL, 16);
            if (!chunk) break;
        } else if (haveLength) {
            if (done >= length) break;
            chunk = length - done;
        } else chunk = 0xFFFFFFFF;                          /* until the server closes */
        while (chunk) {
            if (!Fill(&r)) {
                if (!chunked && !haveLength) { chunk = 0; break; }
                goto failed;
            }
            want = (DWORD)(r.len - r.pos);
            if (want > chunk) want = chunk;
            if (expect && done + want > expect) { lstrcpyn(err, "The server sent more than the catalog lists.", errLen); goto done; }
            if (!WriteFile(out, r.buf + r.pos, want, &written, NULL) || written != want) { lstrcpyn(err, "The disk is full or cannot be written.", errLen); goto done; }
            r.pos += want;
            done += want;
            chunk -= want;
            if (progress) progress(done, haveLength ? length : expect, pctx);
        }
        if (chunked) ReadLine(&r, line, sizeof(line));      /* the CR LF after the data */
        else break;
    }
    if (expect && done != expect) { wsprintf(err, "The download has %lu bytes; the catalog lists %lu.", done, expect); goto done; }
    ok = 1;
    goto done;
failed:
    e = tls ? br_ssl_engine_last_error(&g_sc.eng) : 0;
    if (cancel && *cancel) lstrcpyn(err, "Cancelled.", errLen);
    else if (e) TlsError(e, err, errLen);
    else lstrcpyn(err, "The connection was interrupted.", errLen);
done:
    if (out != INVALID_HANDLE_VALUE) {
        CloseHandle(out);
        if (!ok) DeleteFile(path);
    }
    Close(&c);
    return ok;
}
