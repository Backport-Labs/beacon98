/* net.c - downloading. Plain http:// goes through WinInet, the library
 * Internet Explorer installs on every Windows 95 and 98 computer, so the
 * user's proxy settings apply. https:// goes through Beacon's own TLS
 * (tls.c), because Windows 95 and 98 cannot use the encryption current
 * servers require. Redirects are followed here, up to six, in either
 * direction between http and https.
 *
 * Nothing downloaded is trusted until its signature (the catalog) or its
 * SHA-256 (every other file) is checked.
 */
#include "beacon.h"

#define MAX_REDIRECTS 6

static HANDLE g_net;
static const char *g_headers;           /* extra request lines for the next WinInet request */

/* Returns the WinInet session, opening it the first time. */
static HANDLE Session(void)
{
    if (!g_net) g_net = InternetOpenA("Beacon98/" APP_VERSION, MY_INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    return g_net;
}

/* Whether s is an http:// or https:// address. */
int IsUrl(const char *s)
{
    return strncmp(s, "http://", 7) == 0 || strncmp(s, "https://", 8) == 0;
}

void CloseNet(void)
{
    if (g_net) InternetCloseHandle(g_net);
    g_net = NULL;
}

static HANDLE OpenUrl(const char *url, char *err, int errLen)
{
    HANDLE net = Session(), req;
    if (!net) { lstrcpyn(err, "The internet functions of Windows could not be started.", errLen); return NULL; }
    req = InternetOpenUrlA(net, url, g_headers, g_headers ? (DWORD)-1 : 0, MY_INTERNET_FLAG_RELOAD | MY_INTERNET_FLAG_NO_CACHE_WRITE
                           | MY_INTERNET_FLAG_PRAGMA_NOCACHE | MY_INTERNET_FLAG_NO_UI | MY_INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
    if (!req) wsprintf(err, "Could not connect (error %lu). Check the internet connection.", GetLastError());
    return req;
}

/* The Date header of Beacon's own server, over plain HTTP. */
int ServerDate(char *out, int outLen)
{
    char err[200];
    HANDLE req = OpenUrl("http://" CATALOG_HOST "/KEYS.TXT", err, sizeof(err));
    DWORD len = outLen, idx = 0;
    int ok;
    if (!req) return 0;
    ok = HttpQueryInfoA(req, MY_HTTP_QUERY_DATE, out, &len, &idx);
    InternetCloseHandle(req);
    return ok;
}

/* One plain HTTP request through WinInet, without following redirects. */
static int InetGet(const char *url, const char *path, DWORD expect, volatile int *cancel,
                   void (*progress)(DWORD done, DWORD total, void *ctx), void *ctx,
                   int *status, char *location, int locLen, char *err, int errLen)
{
    static char buf[16384];
    HANDLE req, out;
    DWORD code = 0, len = sizeof(code), idx = 0, total = expect, got, done = 0, written, lenSize;
    char lenText[32];
    int ok = 0;

    *status = 0;
    location[0] = 0;
    req = OpenUrl(url, err, errLen);
    if (!req) return 0;
    if (HttpQueryInfoA(req, MY_HTTP_QUERY_STATUS_CODE | MY_HTTP_QUERY_FLAG_NUMBER, &code, &len, &idx)) *status = (int)code;
    if (*status >= 300 && *status < 400) {
        len = locLen;
        idx = 0;
        if (HttpQueryInfoA(req, MY_HTTP_QUERY_LOCATION, location, &len, &idx) && location[0]) ok = 1;
        else wsprintf(err, "The server answered %d without a new address.", *status);
        InternetCloseHandle(req);
        return ok;
    }
    if (*status != 200) {
        wsprintf(err, "The server answered %d.", *status);
        InternetCloseHandle(req);
        return 0;
    }
    if (!total) {
        lenSize = sizeof(lenText);
        idx = 0;
        if (HttpQueryInfoA(req, MY_HTTP_QUERY_CONTENT_LENGTH, lenText, &lenSize, &idx)) total = strtoul(lenText, NULL, 10);
    }
    out = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (out == INVALID_HANDLE_VALUE) {
        wsprintf(err, "Could not write %s.", path);
        InternetCloseHandle(req);
        return 0;
    }
    for (;;) {
        if (cancel && *cancel) { lstrcpyn(err, "Cancelled.", errLen); break; }
        if (!InternetReadFile(req, buf, sizeof(buf), &got)) {
            wsprintf(err, "The download was interrupted (error %lu).", GetLastError());
            break;
        }
        if (!got) { ok = 1; break; }
        if (expect && done + got > expect) { lstrcpyn(err, "The server sent more than the catalog lists.", errLen); break; }
        if (!WriteFile(out, buf, got, &written, NULL) || written != got) { lstrcpyn(err, "The disk is full or cannot be written.", errLen); break; }
        done += got;
        if (progress) progress(done, total, ctx);
    }
    CloseHandle(out);
    InternetCloseHandle(req);
    if (ok && expect && done != expect) {
        wsprintf(err, "The download has %lu bytes; the catalog lists %lu.", done, expect);
        ok = 0;
    }
    if (!ok) DeleteFile(path);
    return ok;
}

/* Makes the address a redirect points to: absolute, from the server root, or relative. */
static void Resolve(const char *base, const char *loc, char *out, int outLen)
{
    const char *p;
    int n;
    if (strncmp(loc, "http://", 7) == 0 || strncmp(loc, "https://", 8) == 0) { lstrcpyn(out, loc, outLen); return; }
    p = strstr(base, "://");
    p = p ? p + 3 : base;
    if (strncmp(loc, "//", 2) == 0) {
        n = (int)(p - base) - 2;                            /* keep "http:" or "https:" */
        if (n + lstrlen(loc) >= outLen) { lstrcpyn(out, loc, outLen); return; }
        lstrcpyn(out, base, n + 1);
        lstrcat(out, loc);
        return;
    }
    if (loc[0] == '/') {
        while (*p && *p != '/') p++;
        n = (int)(p - base);
    } else {
        const char *slash = strrchr(p, '/');
        n = slash ? (int)(slash - base) + 1 : lstrlen(base);
        if (!slash) { lstrcpyn(out, base, outLen); lstrcat(out, "/"); n = lstrlen(out); lstrcpyn(out + n, loc, outLen - n); return; }
    }
    if (n >= outLen) n = outLen - 1;
    lstrcpyn(out, base, n + 1);
    lstrcpyn(out + n, loc, outLen - n);
}

int HttpGetFile(const char *url, const char *path, DWORD expect, volatile int *cancel,
                void (*progress)(DWORD done, DWORD total, void *ctx), void *ctx, char *err, int errLen)
{
    return HttpGetFileH(url, NULL, 0, path, expect, cancel, progress, ctx, err, errLen);
}

static int SameHost(const char *a, const char *b)
{
    const char *p = strstr(a, "://"), *q = strstr(b, "://");
    int i;
    if (!p || !q) return 0;
    p += 3; q += 3;
    for (i = 0; p[i] && p[i] != '/' && q[i] && q[i] != '/'; i++)
        if (CharLower((LPSTR)(DWORD_PTR)(BYTE)p[i]) != CharLower((LPSTR)(DWORD_PTR)(BYTE)q[i])) return 0;
    return (!p[i] || p[i] == '/') && (!q[i] || q[i] == '/');
}

/* Downloads url into path. expect, when not 0, is the exact size the file
 * must have; a longer answer is cut off and reported. Calls progress with
 * the bytes received so far. headers, when given, are extra request lines
 * ("Name: value\r\n" each). With secret set (an access token of a source),
 * they are sent only over HTTPS and only to the host of url, never to a
 * server a redirect points to. Returns 1 on success. */
int HttpGetFileH(const char *url, const char *headers, int secret, const char *path, DWORD expect, volatile int *cancel,
                 void (*progress)(DWORD done, DWORD total, void *ctx), void *ctx, char *err, int errLen)
{
    char cur[1024], next[1024], loc[1024];
    const char *h;
    int hop, status, ok;
    err[0] = 0;
    g_headers = NULL;
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        lstrcpyn(err, "Only http:// and https:// addresses can be used.", errLen);
        return 0;
    }
    if (secret && headers && strncmp(url, "https://", 8) != 0) {
        lstrcpyn(err, "This source's access key is only sent over HTTPS; its address must start with https://.", errLen);
        return 0;
    }
    lstrcpyn(cur, url, sizeof(cur));
    for (hop = 0; hop <= MAX_REDIRECTS; hop++) {
        h = headers && (!secret || (strncmp(cur, "https://", 8) == 0 && SameHost(cur, url))) ? headers : NULL;
        if (strncmp(cur, "https://", 8) == 0)
            ok = SockHttpGet(cur, h, path, expect, cancel, progress, ctx, &status, loc, sizeof(loc), err, errLen);
        else {
            g_headers = h;
            ok = InetGet(cur, path, expect, cancel, progress, ctx, &status, loc, sizeof(loc), err, errLen);
            g_headers = NULL;
        }
        if (!ok) return 0;
        if (status == 200) return 1;
        Resolve(cur, loc, next, sizeof(next));
        lstrcpy(cur, next);
    }
    lstrcpyn(err, "The server sent too many redirects.", errLen);
    return 0;
}
