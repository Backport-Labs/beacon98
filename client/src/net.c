/* net.c - downloading over HTTP with WinInet, the library Internet Explorer
 * installs on every Windows 95 and 98 computer. It uses the proxy settings
 * the user already has.
 *
 * Downloads use plain HTTP, because Windows 95 and 98 cannot use the
 * encryption current servers require. Nothing downloaded is trusted until
 * its signature (the catalog) or its SHA-256 (every other file) is checked.
 */
#include "beacon.h"

static HANDLE g_net;

/* Returns the WinInet session, opening it the first time. */
static HANDLE Session(void)
{
    if (!g_net) g_net = InternetOpenA("Beacon98/" APP_VERSION, MY_INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    return g_net;
}

void CloseNet(void)
{
    if (g_net) InternetCloseHandle(g_net);
    g_net = NULL;
}

/* Downloads url into path. expect, when not 0, is the exact size the file
 * must have; a longer answer is cut off and reported. Calls progress with
 * the bytes received so far. Returns 1 on success. */
int HttpGetFile(const char *url, const char *path, DWORD expect, volatile int *cancel,
                void (*progress)(DWORD done, DWORD total, void *ctx), void *ctx, char *err, int errLen)
{
    static char buf[16384];
    HANDLE net, req, out;
    DWORD status = 0, len = sizeof(status), idx = 0, total = expect, got, done = 0, written, lenSize;
    char lenText[32];
    int ok = 0;

    err[0] = 0;
    if (strncmp(url, "http://", 7) != 0) { lstrcpyn(err, "Only http:// addresses can be used on this computer.", errLen); return 0; }
    net = Session();
    if (!net) { lstrcpyn(err, "The internet functions of Windows could not be started.", errLen); return 0; }
    req = InternetOpenUrlA(net, url, NULL, 0, MY_INTERNET_FLAG_RELOAD | MY_INTERNET_FLAG_NO_CACHE_WRITE
                           | MY_INTERNET_FLAG_PRAGMA_NOCACHE | MY_INTERNET_FLAG_NO_UI, 0);
    if (!req) {
        wsprintf(err, "Could not connect (error %lu). Check the internet connection.", GetLastError());
        return 0;
    }
    if (HttpQueryInfoA(req, MY_HTTP_QUERY_STATUS_CODE | MY_HTTP_QUERY_FLAG_NUMBER, &status, &len, &idx) && status != 200) {
        wsprintf(err, "The server answered %lu.", status);
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
