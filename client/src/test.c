/* test.c - the self-test: BEACON98.EXE /selftest.
 *
 * Reads the files in the program's folder and writes SELFTEST.OUT, which the
 * build compares with tests\EXPECTED.OUT, and HASHES.OUT, which the build
 * compares with the SHA-256 that Windows PowerShell computes for the same files.
 *   ED25519.TXT  Ed25519 test vectors
 *   CATALOG.TXT, CATALOG.SIG  the signed catalog
 *   PARSE.TXT    a catalog with unusual but valid lines
 *   HASHME.TXT   names of files to hash, one per line
 */
#include "beacon.h"

static FILE *g_out;

static void Hash(const char *label, const void *data, DWORD n)
{
    SHA256 s;
    BYTE h[32];
    char hex[65];
    Sha256Init(&s);
    Sha256Add(&s, data, n);
    Sha256Done(&s, h);
    ToHex(h, 32, hex);
    fprintf(g_out, "SHA256 %s %s\n", label, hex);
}

static void TestSha256(void)
{
    static char million[1000000];
    const char *two = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    SHA256 s;
    BYTE a[32], b[32];
    int i;
    Hash("empty", "", 0);
    Hash("abc", "abc", 3);
    Hash("448-bits", two, lstrlen(two));
    memset(million, 'a', sizeof(million));
    Hash("million-a", million, sizeof(million));
    /* The same data added in pieces of every size from 1 to 130 bytes. */
    Sha256Init(&s);
    Sha256Add(&s, million, 100000);
    Sha256Done(&s, a);
    for (i = 1; i <= 130; i++) {
        DWORD done = 0, step;
        Sha256Init(&s);
        while (done < 100000) {
            step = 100000 - done < (DWORD)i ? 100000 - done : (DWORD)i;
            Sha256Add(&s, million + done, step);
            done += step;
        }
        Sha256Done(&s, b);
        if (memcmp(a, b, 32) != 0) break;
    }
    fprintf(g_out, "SHA256 in pieces of 1 to 130 bytes: %s\n", i > 130 ? "same" : "DIFFERENT");
}

static void TestEd25519(void)
{
    char path[MAX_PATH], *line;
    static char buf[4096];
    BYTE key[32], sig[64], *msg;
    FILE *f;
    int n = 0, valid = 0, forged = 0, changed = 0, bad = 0, len, mlen;
    wsprintf(path, "%sED25519.TXT", g_dir);
    f = fopen(path, "r");
    if (!f) { fprintf(g_out, "ED25519 no test vectors\n"); return; }
    msg = (BYTE *)malloc(2048);
    while (fgets(buf, sizeof(buf), f)) {
        if (buf[0] == '#' || buf[0] == '\n') continue;
        line = buf;
        len = lstrlen(line);
        while (len && (line[len - 1] == '\n' || line[len - 1] == '\r')) line[--len] = 0;
        if (len < 64 + 1 + 128 + 2 || !FromHex(line, key, 32) || !FromHex(line + 65, sig, 64)) { bad++; continue; }
        line += 64 + 1 + 128 + 1;
        mlen = line[0] == '-' ? 0 : lstrlen(line) / 2;
        if (mlen > 2048 || (mlen && !FromHex(line, msg, mlen))) { bad++; continue; }
        n++;
        if (VerifyBytes(msg, mlen, sig, key)) valid++;
        sig[n % 64] ^= 1 << (n % 8);
        if (!VerifyBytes(msg, mlen, sig, key)) forged++;
        sig[n % 64] ^= 1 << (n % 8);
        if (mlen) {
            msg[n % mlen] ^= 0x80;
            if (!VerifyBytes(msg, mlen, sig, key)) changed++;
        }
    }
    fclose(f);
    free(msg);
    fprintf(g_out, "ED25519 %d vectors: %d valid, %d forged signatures rejected, %d changed messages rejected, %d unreadable lines\n",
            n, valid, forged, changed, bad);
}

static int CopyChanged(const char *from, const char *to, long offset, int xor)
{
    FILE *a = fopen(from, "rb"), *b = fopen(to, "wb");
    long i = 0;
    int c;
    if (!a || !b) { if (a) fclose(a); if (b) fclose(b); return 0; }
    while ((c = fgetc(a)) != EOF) { if (i++ == offset) c ^= xor; fputc(c, b); }
    fclose(a);
    fclose(b);
    return 1;
}

static void PrintPkg(PKG *p)
{
    char first[80];
    FirstLine(p->f[F_DOWNLOAD], first, sizeof(first));
    fprintf(g_out, "PKG %s | %s | %s | %s | %lu bytes | %s | depends %s\n", p->f[F_PACKAGE], p->f[F_NAME],
            p->f[F_VERSION], p->f[F_SECTION], p->bytes, p->external ? "external" : "hosted",
            p->f[F_DEPENDS] ? p->f[F_DEPENDS] : "-");
}

static void TestCatalog(void)
{
    char cat[MAX_PATH], sig[MAX_PATH], bad[MAX_PATH], err[200];
    FILE *f;
    int i;
    CATALOG c;
    wsprintf(cat, "%sCATALOG.TXT", g_dir);
    wsprintf(sig, "%sCATALOG.SIG", g_dir);
    fprintf(g_out, "CATALOG signature: %s\n", SigText(VerifyCatalogFile(cat, sig)));
    wsprintf(bad, "%sCHANGED.TXT", g_dir);
    CopyChanged(cat, bad, 300, 1);
    fprintf(g_out, "CATALOG with one bit changed: %s\n", SigText(VerifyCatalogFile(bad, sig)));
    DeleteFile(bad);
    wsprintf(bad, "%sOTHERKEY.SIG", g_dir);
    f = fopen(bad, "w");
    if (f) { fprintf(f, "Key-Id: 0000000000000000\nSignature: %0128d\n", 0); fclose(f); }
    fprintf(g_out, "CATALOG signed with another key: %s\n", SigText(VerifyCatalogFile(cat, bad)));
    DeleteFile(bad);
    wsprintf(bad, "%sNOSUCH.SIG", g_dir);
    fprintf(g_out, "CATALOG without a signature: %s\n", SigText(VerifyCatalogFile(cat, bad)));

    if (!LoadCatalog(cat, &c, err, sizeof(err))) { fprintf(g_out, "CATALOG not loaded: %s\n", err); return; }
    fprintf(g_out, "CATALOG serial %s, date %s, expires %s, base %s, %d packages\n", c.serial, c.date, c.expires, c.base, c.count);
    for (i = 0; i < c.count; i++) PrintPkg(&c.pkg[i]);
    FreeCatalog(&c);
}

static void Quote(const char *label, const char *text)
{
    fprintf(g_out, "%s [", label);
    for (; text && *text; text++) {
        if (*text == '\n') fprintf(g_out, "\\n");
        else fputc(*text, g_out);
    }
    fprintf(g_out, "]\n");
}

static void TestParse(void)
{
    char path[MAX_PATH], err[200];
    CATALOG c;
    int i;
    wsprintf(path, "%sPARSE.TXT", g_dir);
    if (!LoadCatalog(path, &c, err, sizeof(err))) { fprintf(g_out, "PARSE not loaded: %s\n", err); return; }
    fprintf(g_out, "PARSE %d packages\n", c.count);
    for (i = 0; i < c.count; i++) {
        PrintPkg(&c.pkg[i]);
        Quote("  Description", c.pkg[i].f[F_DESCRIPTION]);
        Quote("  Download", c.pkg[i].f[F_DOWNLOAD]);
    }
    FreeCatalog(&c);
    wsprintf(path, "%sED25519.TXT", g_dir);
    fprintf(g_out, "PARSE a file that is not a catalog: %s\n", LoadCatalog(path, &c, err, sizeof(err)) ? "loaded" : err);
}

static void TestRequirements(void)
{
    static const char *lines[] = {
        "file {sys}\\KERNEL32.DLL | the system library",
        "file {sys}\\NO_SUCH_FILE_BEACON.DLL | a file that does not exist",
        "memory 1 | one megabyte of memory",
        "memory 999999 | a terabyte of memory",
        "dx 9 | DirectX 9",
        "future-check 1 | a check a later version may add"
    };
    char what[200];
    int i, r;
    for (i = 0; i < (int)(sizeof(lines) / sizeof(lines[0])); i++) {
        r = RequirementMet(lines[i], what, sizeof(what));
        fprintf(g_out, "REQUIRES %s: %s\n", what, r == 1 ? "met" : r == 0 ? "missing" : "not checked");
    }
}

/* The build makes TEST.ZIP, SFX.EXE (the same archive after 5000 other
 * bytes) and EVIL.ZIP (an entry named ../EVIL.TXT); it then compares what was
 * unpacked with the originals. */
static void TestUnzip(void)
{
    static const char *cases[3][3] = {
        { "TEST.ZIP", "OUT1", "0" }, { "SFX.EXE", "OUT2", "1" }, { "EVIL.ZIP", "OUT3", "0" }
    };
    char archive[MAX_PATH], target[MAX_PATH], err[300], path[MAX_PATH];
    int i;
    for (i = 0; i < 3; i++) {
        wsprintf(archive, "%s%s", g_dir, cases[i][0]);
        wsprintf(target, "%s%s", g_dir, cases[i][1]);
        if (Unzip(archive, target, atoi(cases[i][2]), NULL, NULL, NULL, err, sizeof(err)))
            fprintf(g_out, "UNZIP %s, strip %s: unpacked\n", cases[i][0], cases[i][2]);
        else
            fprintf(g_out, "UNZIP %s, strip %s: %s\n", cases[i][0], cases[i][2], err);
    }
    wsprintf(path, "%sEVIL.TXT", g_dir);
    fprintf(g_out, "UNZIP a file outside the target was %s\n", GetFileAttributes(path) == 0xFFFFFFFF ? "not written" : "WRITTEN");
    wsprintf(archive, "%sED25519.TXT", g_dir);
    wsprintf(target, "%sOUT4", g_dir);
    fprintf(g_out, "UNZIP a file that is not an archive: %s\n", Unzip(archive, target, 0, NULL, NULL, NULL, err, sizeof(err)) ? "unpacked" : err);
}

/* Downloads from the Backport Labs server. */
static void TestHttp(void)
{
    char path[MAX_PATH], err[300], hex[65];
    BYTE h[32];
    DWORD size;
    wsprintf(path, "%sKEYS.DL", g_dir);
    if (HttpGetFile("http://" CATALOG_HOST "/KEYS.TXT", path, 0, NULL, NULL, NULL, err, sizeof(err)) && Sha256File(path, h, &size)) {
        ToHex(h, 32, hex);
        fprintf(g_out, "HTTP KEYS.TXT: %lu bytes, SHA-256 %s\n", size, hex);
    } else fprintf(g_out, "HTTP KEYS.TXT: %s\n", err);
    DeleteFile(path);
    if (!HttpGetFile("http://" CATALOG_HOST "/KEYS.TXT", path, 100, NULL, NULL, NULL, err, sizeof(err)))
        fprintf(g_out, "HTTP with a size smaller than the file: %s\n", err);
    fprintf(g_out, "HTTP the partial file was %s\n", GetFileAttributes(path) == 0xFFFFFFFF ? "deleted" : "KEPT");
    if (!HttpGetFile("http://" CATALOG_HOST "/NO-SUCH-FILE.TXT", path, 0, NULL, NULL, NULL, err, sizeof(err)))
        fprintf(g_out, "HTTP a missing file: %s\n", err);
    if (!HttpGetFile("https://" CATALOG_HOST "/KEYS.TXT", path, 0, NULL, NULL, NULL, err, sizeof(err)))
        fprintf(g_out, "HTTP an https address: %s\n", err);
    CloseNet();
}

static void TestSystems(void)
{
    fprintf(g_out, "SYSTEMS \"95, 98, ME\" and \"NT4\" name this Windows: %s\n",
            SystemListed("95, 98, ME") || SystemListed("NT4") ? "yes" : "no");
    fprintf(g_out, "SYSTEMS an empty list names this Windows: %s\n", SystemListed("") ? "yes" : "no");
}

static void TestHashFiles(void)
{
    char path[MAX_PATH], name[MAX_PATH], hex[65];
    BYTE h[32];
    DWORD size;
    FILE *list, *out;
    int len;
    wsprintf(path, "%sHASHME.TXT", g_dir);
    list = fopen(path, "r");
    wsprintf(path, "%sHASHES.OUT", g_dir);
    out = fopen(path, "w");
    if (!list || !out) { if (list) fclose(list); if (out) fclose(out); return; }
    while (fgets(name, sizeof(name), list)) {
        len = lstrlen(name);
        while (len && (name[len - 1] == '\n' || name[len - 1] == '\r')) name[--len] = 0;
        if (!len) continue;
        wsprintf(path, "%s%s", g_dir, name);
        if (Sha256File(path, h, &size)) { ToHex(h, 32, hex); fprintf(out, "%s %lu %s\n", name, size, hex); }
        else fprintf(out, "%s unreadable\n", name);
    }
    fclose(list);
    fclose(out);
}

/* Draws the main window, off the screen, into a 24-bit bitmap file. */
int Shot(const char *file, int row, const char *search)
{
    HWND hwnd;
    RECT rc;
    HDC screen, dc;
    HBITMAP bmp;
    BITMAPINFO bi;
    BITMAPFILEHEADER fh;
    void *bits;
    DWORD stride, size;
    MSG m;
    FILE *f;
    int w, h;
    hwnd = OpenForShot(search, row);
    if (!hwnd) return 2;
    while (PeekMessage(&m, NULL, 0, 0, PM_REMOVE)) { TranslateMessage(&m); DispatchMessage(&m); }
    GetWindowRect(hwnd, &rc);
    w = rc.right - rc.left;
    h = rc.bottom - rc.top;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 24;
    screen = GetDC(NULL);
    dc = CreateCompatibleDC(screen);
    bmp = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
    ReleaseDC(NULL, screen);
    if (!bmp) return 3;
    SelectObject(dc, bmp);
    SendMessage(hwnd, WM_PRINT, (WPARAM)dc, PRF_NONCLIENT | PRF_CLIENT | PRF_CHILDREN | PRF_ERASEBKGND);
    GdiFlush();
    stride = ((DWORD)w * 3 + 3) & ~3u;
    size = stride * h;
    memset(&fh, 0, sizeof(fh));
    fh.bfType = 0x4D42;
    fh.bfOffBits = sizeof(fh) + sizeof(BITMAPINFOHEADER);
    fh.bfSize = fh.bfOffBits + size;
    f = fopen(file, "wb");
    if (f) {
        fwrite(&fh, sizeof(fh), 1, f);
        fwrite(&bi.bmiHeader, sizeof(BITMAPINFOHEADER), 1, f);
        fwrite(bits, size, 1, f);
        fclose(f);
    }
    DeleteDC(dc);
    DeleteObject(bmp);
    DestroyWindow(hwnd);
    return f ? 0 : 4;
}

int SelfTest(void)
{
    char path[MAX_PATH];
    wsprintf(path, "%sSELFTEST.OUT", g_dir);
    g_out = fopen(path, "w");
    if (!g_out) return 2;
    fprintf(g_out, "%s %s self-test\n", APP_NAME, APP_VERSION);
    TestSha256();
    TestEd25519();
    TestCatalog();
    TestParse();
    TestRequirements();
    TestSystems();
    TestUnzip();
    TestHttp();
    fclose(g_out);
    TestHashFiles();
    return 0;
}
