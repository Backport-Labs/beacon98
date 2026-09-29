/* install.c - updating the catalog, installing and removing packages.
 *
 * Installing a package:
 *   1. Download each file named on its Download lines, into DOWNLOAD\.
 *   2. Check the size and the SHA-256 against the signed catalog. A file
 *      that does not match is deleted and nothing is run.
 *   3. Run its setup program silently, or unpack it (unzip.c).
 *   4. Carry out its After steps and make its Start Menu shortcuts.
 *   5. Record it in INSTALLED.TXT, and what Beacon itself created in
 *      FILES\<package>.TXT, so Remove can take it away again.
 */
#include "beacon.h"

#define MAX_QUEUE 64

typedef struct {
    PKG *q[MAX_QUEUE];
    int n;
    int done;                  /* packages installed */
} JOB;

static char g_downloadDir[MAX_PATH], g_filesDir[MAX_PATH];
static int g_selfUpdate;                /* Beacon's own setup was started: close */

static void Dirs(void)
{
    wsprintf(g_downloadDir, "%sDOWNLOAD\\", g_dir);
    wsprintf(g_filesDir, "%sFILES\\", g_dir);
    CreateDirectory(g_downloadDir, NULL);
    CreateDirectory(g_filesDir, NULL);
}

/* ------------------------------------------------------------------------
 * INSTALLED.TXT: one "package|version|folder" per line
 * --------------------------------------------------------------------- */

static void SetInstalled(const char *id, const char *version, const char *dir)
{
    char path[MAX_PATH], tmp[MAX_PATH], line[700];
    FILE *in, *out;
    int len = lstrlen(id);
    wsprintf(path, "%sINSTALLED.TXT", g_dir);
    wsprintf(tmp, "%sINSTALLED.NEW", g_dir);
    out = fopen(tmp, "w");
    if (!out) return;
    in = fopen(path, "r");
    if (in) {
        while (fgets(line, sizeof(line), in))
            if (!(strncmp(line, id, len) == 0 && line[len] == '|')) fputs(line, out);
        fclose(in);
    }
    if (version) fprintf(out, "%s|%s|%s\n", id, version, dir ? dir : "");
    fclose(out);
    DeleteFile(path);
    MoveFile(tmp, path);
}

/* The folder an installed package was put in, from INSTALLED.TXT. */
static int InstalledDir(const char *id, char *dir, int dirLen)
{
    char path[MAX_PATH], line[700], *p;
    FILE *f;
    int len = lstrlen(id), found = 0;
    dir[0] = 0;
    wsprintf(path, "%sINSTALLED.TXT", g_dir);
    f = fopen(path, "r");
    if (!f) return 0;
    while (!found && fgets(line, sizeof(line), f)) {
        if (strncmp(line, id, len) != 0 || line[len] != '|') continue;
        p = strchr(line + len + 1, '|');
        if (!p) continue;
        lstrcpyn(dir, p + 1, dirLen);
        len = lstrlen(dir);
        while (len && (dir[len - 1] == '\n' || dir[len - 1] == '\r')) dir[--len] = 0;
        found = 1;
    }
    fclose(f);
    return found;
}

/* ------------------------------------------------------------------------
 * FILES\<package>.TXT: what Beacon created, one "kind path" per line:
 * F file, D folder, L shortcut, P folder added to PATH in AUTOEXEC.BAT
 * --------------------------------------------------------------------- */

typedef struct { FILE *f; } RECORD;

static void RecordOpen(RECORD *r, const char *id)
{
    char path[MAX_PATH];
    wsprintf(path, "%s%s.TXT", g_filesDir, id);
    r->f = fopen(path, "a");
}

static void Record(char kind, const char *path, void *ctx)
{
    RECORD *r = (RECORD *)ctx;
    if (r && r->f) { fprintf(r->f, "%c %s\n", kind, path); fflush(r->f); }
}

/* ------------------------------------------------------------------------
 * Places: {pf}, {win}, {sys}, {dir}, {dir:package}
 * --------------------------------------------------------------------- */

static void Expand(const char *in, const char *dir, char *out, int outLen)
{
    char tmp[1024], other[MAX_PATH], id[40];
    int o = 0, i, n;
    while (*in && o < (int)sizeof(tmp) - 1) {
        if (strncmp(in, "{dir}", 5) == 0) {
            n = lstrlen(dir);
            if (o + n >= (int)sizeof(tmp)) break;
            lstrcpy(tmp + o, dir);
            o += n;
            in += 5;
        } else if (strncmp(in, "{dir:", 5) == 0) {
            in += 5;
            for (i = 0; *in && *in != '}' && i < (int)sizeof(id) - 1; i++) id[i] = *in++;
            id[i] = 0;
            if (*in == '}') in++;
            InstalledDir(id, other, sizeof(other));
            n = lstrlen(other);
            if (o + n >= (int)sizeof(tmp)) break;
            lstrcpy(tmp + o, other);
            o += n;
        } else tmp[o++] = *in++;
    }
    tmp[o] = 0;
    ExpandPlaces(tmp, out, outLen);
}

/* The folder a package goes in: the target of an unzip or copy, otherwise
 * Program Files\<Name>. */
static void PackageDir(PKG *p, char *out, int outLen)
{
    char target[MAX_PATH], def[MAX_PATH];
    const char *inst = p->f[F_INSTALL];
    int i = 0;
    wsprintf(target, "{pf}\\%s", p->f[F_NAME]);
    ExpandPlaces(target, def, sizeof(def));
    if (strncmp(inst, "unzip ", 6) == 0 || strncmp(inst, "copy ", 5) == 0) {
        inst = strchr(inst, ' ') + 1;
        while (inst[i] && inst[i] != ' ' && i < (int)sizeof(target) - 1) { target[i] = inst[i]; i++; }
        target[i] = 0;
        Expand(target, def, out, outLen);
    } else lstrcpyn(out, def, outLen);
}

/* ------------------------------------------------------------------------
 * Running programs
 * --------------------------------------------------------------------- */

/* Runs a command line and waits up to wait milliseconds. Returns the exit
 * code, or -1 if the program could not be started, -2 if it is still running. */
static int Run(const char *cmdLine, DWORD wait)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmd[1200];
    DWORD code = 0;
    lstrcpyn(cmd, cmdLine, sizeof(cmd));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) return -1;
    if (WaitForSingleObject(pi.hProcess, wait) == WAIT_TIMEOUT) code = (DWORD)-2;
    else GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return (int)code;
}

/* ------------------------------------------------------------------------
 * Shortcuts
 * --------------------------------------------------------------------- */

static const MYGUID CLSID_ShellLink = { 0x00021401, 0, 0, { 0xC0, 0, 0, 0, 0, 0, 0, 0x46 } };
static const MYGUID IID_ShellLinkA  = { 0x000214EE, 0, 0, { 0xC0, 0, 0, 0, 0, 0, 0, 0x46 } };
static const MYGUID IID_PersistFile = { 0x0000010B, 0, 0, { 0xC0, 0, 0, 0, 0, 0, 0, 0x46 } };

static int ProgramsFolder(char *out)
{
    void *pidl = NULL;
    int ok = 0;
    if (SHGetSpecialFolderLocation(NULL, MY_CSIDL_PROGRAMS, &pidl) == 0 && pidl) {
        ok = SHGetPathFromIDListA(pidl, out);
        CoTaskMemFree(pidl);
    }
    return ok;
}

static int MakeShortcut(const char *name, const char *target, const char *args, RECORD *rec)
{
    ShellLink *link = NULL;
    PersistFile *file = NULL;
    char path[MAX_PATH], dir[MAX_PATH], *slash;
    WCHAR wide[MAX_PATH];
    int ok = 0;
    if (!ProgramsFolder(path)) return 0;
    lstrcat(path, "\\");
    lstrcat(path, name);
    lstrcat(path, ".lnk");
    lstrcpyn(dir, target, sizeof(dir));
    slash = strrchr(dir, '\\');
    if (slash) *slash = 0;
    if (CoCreateInstance(&CLSID_ShellLink, NULL, 1, &IID_ShellLinkA, (void **)&link) != 0) return 0;
    link->v->SetPath(link, target);
    link->v->SetArguments(link, args ? args : "");
    link->v->SetWorkingDirectory(link, dir);
    if (link->v->QueryInterface(link, &IID_PersistFile, (void **)&file) == 0) {
        MultiByteToWideChar(CP_ACP, 0, path, -1, wide, MAX_PATH);
        ok = file->v->Save(file, wide, TRUE) == 0;
        file->v->Release(file);
    }
    link->v->Release(link);
    if (ok) Record('L', path, rec);
    return ok;
}

/* ------------------------------------------------------------------------
 * AUTOEXEC.BAT
 * --------------------------------------------------------------------- */

static const char *g_autoexec = "C:\\AUTOEXEC.BAT";

static int AddToPath(const char *folder, const char *id)
{
    FILE *f;
    char line[600], mark[100];
    int found = 0;
    wsprintf(mark, "REM Added by Beacon 98 for %s", id);
    f = fopen(g_autoexec, "r");
    if (f) {
        while (fgets(line, sizeof(line), f)) if (strstr(line, mark)) found = 1;
        fclose(f);
    }
    if (found) return 1;
    f = fopen(g_autoexec, "a");
    if (!f) return 0;
    fprintf(f, "%s\nSET PATH=%%PATH%%;%s\n", mark, folder);
    fclose(f);
    return 1;
}

static void RemoveFromPath(const char *id)
{
    char tmp[MAX_PATH], line[600], mark[100];
    FILE *in, *out;
    int skip = 0;
    wsprintf(mark, "REM Added by Beacon 98 for %s", id);
    in = fopen(g_autoexec, "r");
    if (!in) return;
    wsprintf(tmp, "%sAUTOEXEC.NEW", g_dir);
    out = fopen(tmp, "w");
    if (!out) { fclose(in); return; }
    while (fgets(line, sizeof(line), in)) {
        if (skip) { skip = 0; continue; }
        if (strstr(line, mark)) { skip = 1; continue; }
        fputs(line, out);
    }
    fclose(in);
    fclose(out);
    CopyFile(tmp, g_autoexec, FALSE);
    DeleteFile(tmp);
}

/* ------------------------------------------------------------------------
 * Installing
 * --------------------------------------------------------------------- */

typedef struct { const char *name; } PROGRESS_CTX;

static void OnProgress(DWORD done, DWORD total, void *ctx)
{
    static int last = -1;
    int pct = total ? (int)((double)done * 100 / total) : 0;
    (void)ctx;
    if (pct != last) { TaskProgress(pct); last = pct; }
}

/* Copies the n-th line of a multi-line field. Returns 0 when there is none. */
static int Line(const char *field, int n, char *out, int outLen)
{
    int i;
    if (!field) return 0;
    while (n-- > 0) {
        field = strchr(field, '\n');
        if (!field) return 0;
        field++;
    }
    for (i = 0; field[i] && field[i] != '\n' && i < outLen - 1; i++) out[i] = field[i];
    out[i] = 0;
    return i > 0;
}

/* The host part of an address, for messages: "downloads.sourceforge.net". */
static void Host(const char *url, char *out, int outLen)
{
    const char *p = strstr(url, "://");
    int i = 0;
    p = p ? p + 3 : CATALOG_HOST;
    while (p[i] && p[i] != '/' && i < outLen - 1) { out[i] = p[i]; i++; }
    out[i] = 0;
}

/* Downloads one file of a Download line, "location size sha256 [location...]",
 * into dir, trying each location in turn until one gives a file whose size and
 * SHA-256 match. A location is an http:// address, or a path on the catalog's
 * own server. Copies the local path to out. Returns 1 on success. */
int FetchFile(const char *line, const char *dir, char *out)
{
    return FetchFileFrom(line, g_cat.base, NULL, NULL, dir, out);
}

/* The same, for a package of any source. base is the source's address or
 * folder, for locations that are paths; headers are the source's access
 * headers, sent only with those paths and only over HTTPS; referer, when
 * given, is sent with full addresses (some publishers' servers want it). */
int FetchFileFrom(const char *line, const char *base, const char *headers, const char *referer, const char *dir, char *out)
{
    char loc[8][600], urls[16][700], sizePart[20], shaPart[70], url[700], err[300], hex[65], host[100], *name, *q;
    char refHeader[700];
    const char *p = line;
    BYTE want[32], got[32];
    DWORD size, gotSize;
    int n = 0, i, k, tries = 0, kind[16], folder = !IsUrl(base), ok;

    /* Split into words: the first location, the size, the hash, then more locations. */
    for (k = 0; *p && k < 11; k++) {
        char word[600];
        while (*p == ' ') p++;
        for (i = 0; *p && *p != ' ' && i < (int)sizeof(word) - 1; i++) word[i] = *p++;
        word[i] = 0;
        if (!i) break;
        if (k == 1) lstrcpyn(sizePart, word, sizeof(sizePart));
        else if (k == 2) lstrcpyn(shaPart, word, sizeof(shaPart));
        else if (n < 8) lstrcpyn(loc[n++], word, sizeof(loc[0]));
    }
    if (k < 3 || !n || lstrlen(shaPart) != 64 || !FromHex(shaPart, want, 32)) {
        TaskLog("A Download line of the catalog is damaged.");
        return 0;
    }
    size = strtoul(sizePart, NULL, 10);
    name = strrchr(loc[0], '/');
    name = name ? name + 1 : loc[0];
    wsprintf(out, "%s%s", dir, name);
    /* The places to try, in order: kind 0 is a full address, 1 a path on the
     * source's server (tried over HTTPS first, then plain HTTP), 2 a file in the
     * source's folder. */
    for (i = 0; i < n && tries < 15; i++) {
        if (IsUrl(loc[i])) { kind[tries] = 0; lstrcpyn(urls[tries++], loc[i], sizeof(urls[0])); }
        else if (folder) {
            kind[tries] = 2;
            wsprintf(urls[tries], "%s%s", base, loc[i]);
            for (q = urls[tries]; *q; q++) if (*q == '/') *q = '\\';
            tries++;
        } else {
            if (strncmp(base, "http://", 7) == 0) { kind[tries] = 1; wsprintf(urls[tries++], "https://%s%s", base + 7, loc[i]); }
            if (!headers || !headers[0] || strncmp(base, "https://", 8) == 0) { kind[tries] = 1; wsprintf(urls[tries++], "%s%s", base, loc[i]); }
        }
    }
    if (referer) wsprintf(refHeader, "Referer: %s\r\n", referer);
    for (i = 0; i < tries; i++) {
        if (TaskCancelled()) return 0;
        lstrcpyn(url, urls[i], sizeof(url));
        if (kind[i] == 2) {
            TaskLog("%s %s (%lu KB) from %s", i ? "Trying" : "Copying", name, (size + 1023) / 1024, base);
            ok = CopyFile(url, out, FALSE);
            if (!ok) { TaskLog("  %s could not be read.", url); continue; }
            SetFileAttributes(out, FILE_ATTRIBUTE_NORMAL);
        } else {
            Host(url, host, sizeof(host));
            TaskLog("%s %s (%lu KB) from %s%s", i ? "Trying" : "Downloading", name, (size + 1023) / 1024, host,
                    strncmp(url, "https://", 8) == 0 ? " over HTTPS" : "");
            TaskProgress(0);
            if (kind[i] == 1) ok = HttpGetFileH(url, headers && headers[0] ? headers : NULL, 1, out, size, TaskCancelFlag(), OnProgress, NULL, err, sizeof(err));
            else ok = HttpGetFileH(url, referer ? refHeader : NULL, 0, out, size, TaskCancelFlag(), OnProgress, NULL, err, sizeof(err));
            if (!ok) { TaskLog("  %s", err); continue; }
        }
        if (!Sha256File(out, got, &gotSize) || gotSize != size || memcmp(got, want, 32) != 0) {
            ToHex(got, 32, hex);
            TaskLog("  The file does not match the catalog (SHA-256 %s). It was deleted.", hex);
            DeleteFile(out);
            continue;
        }
        TaskLog("  Size and SHA-256 match the signed catalog.");
        return 1;
    }
    TaskLog("  No source gave the file listed in the catalog. Nothing was run.");
    return 0;
}

/* Downloads and checks every file of p. Fills files with their local paths. */
static int Fetch(PKG *p, char files[][MAX_PATH], int *count)
{
    char line[1200];
    int n;
    *count = 0;
    for (n = 0; Line(p->f[F_DOWNLOAD], n, line, sizeof(line)) && n < 8; n++) {
        if (!FetchFileFrom(line, SourceBase(p), g_src[p->source].headers, p->f[F_REFERER], g_downloadDir, files[n])) return 0;
        *count = n + 1;
    }
    return *count > 0;
}

/* The extra switches after the installer kind, and for unzip the "strip N". */
static const char *After(const char *s, int words)
{
    while (words-- > 0) {
        while (*s && *s != ' ') s++;
        while (*s == ' ') s++;
    }
    return s;
}

/* Deletes a folder and everything in it. */
static void DeleteTree(const char *dir)
{
    char pattern[MAX_PATH], path[MAX_PATH];
    WIN32_FIND_DATA fd;
    HANDLE h;
    wsprintf(pattern, "%s\\*", dir);
    h = FindFirstFile(pattern, &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            if (lstrcmp(fd.cFileName, ".") == 0 || lstrcmp(fd.cFileName, "..") == 0) continue;
            wsprintf(path, "%s\\%s", dir, fd.cFileName);
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) DeleteTree(path);
            else { SetFileAttributes(path, FILE_ATTRIBUTE_NORMAL); DeleteFile(path); }
        } while (FindNextFile(h, &fd));
        FindClose(h);
    }
    RemoveDirectory(dir);
}

/* Unpacks zip into folder and copies the path of the one setup program it
 * holds (.exe or .msi, at the top of the archive) to setup. */
int SetupFromZip(const char *zip, const char *folder, char *setup, char *err, int errLen)
{
    static const char *kinds[2] = { "*.exe", "*.msi" };
    char pattern[MAX_PATH], found[MAX_PATH];
    WIN32_FIND_DATA fd;
    HANDLE h;
    int i, n = 0;
    DeleteTree(folder);
    TaskLog("Unpacking the setup program from %s", strrchr(zip, '\\') + 1);
    if (!Unzip(zip, folder, 0, TaskCancelFlag(), NULL, NULL, err, errLen)) return 0;
    for (i = 0; i < 2; i++) {
        wsprintf(pattern, "%s\\%s", folder, kinds[i]);
        h = FindFirstFile(pattern, &fd);
        if (h == INVALID_HANDLE_VALUE) continue;
        do { wsprintf(found, "%s\\%s", folder, fd.cFileName); n++; } while (FindNextFile(h, &fd));
        FindClose(h);
    }
    if (n != 1) { wsprintf(err, "The zip file holds %d setup programs; Beacon 98 expects exactly one.", n); return 0; }
    lstrcpy(setup, found);
    return 1;
}

static int InstallOne(PKG *p, RECORD *rec)
{
    char files[8][MAX_PATH], dir[MAX_PATH], cmd[1200], line[700], exp[1024], err[300], sysdir[MAX_PATH];
    const char *inst = p->f[F_INSTALL], *extra;
    int count, i, k, code, strip = 0, ok = 1;
    char unpacked[MAX_PATH], zipPath[MAX_PATH];
    unpacked[0] = zipPath[0] = 0;

    TaskLog("");
    TaskLog("%s %s", p->f[F_NAME], p->f[F_VERSION]);
    if (!Fetch(p, files, &count)) return 0;
    if (TaskCancelled()) return 0;
    PackageDir(p, dir, sizeof(dir));
    TaskProgress(-1);

    /* Beacon itself: its setup cannot replace a running program, so start it,
     * and close. Setup waits for Beacon to be gone, and starts it again. */
    if (lstrcmp(p->f[F_PACKAGE], SELF_PACKAGE) == 0) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        wsprintf(cmd, "\"%s\" /SILENT /SUPPRESSMSGBOXES /NORESTART", files[0]);
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            TaskLog("  Its setup program could not be started.");
            return 0;
        }
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        TaskLog("Beacon 98 closes now so its setup can update it, and starts again when it is done.");
        g_selfUpdate = 1;
        return 1;
    }

    if (strncmp(inst, "unzip", 5) == 0 || strncmp(inst, "copy", 4) == 0) {
        extra = After(inst, 2);
        if (strncmp(extra, "strip ", 6) == 0) strip = atoi(extra + 6);
        for (i = 0; i < count && ok; i++) {
            if (inst[0] == 'u') {
                TaskLog("Unpacking %s into %s", strrchr(files[i], '\\') + 1, dir);
                ok = Unzip(files[i], dir, strip, TaskCancelFlag(), Record, rec, err, sizeof(err));
                if (!ok) TaskLog("  %s", err);
            } else {
                wsprintf(cmd, "%s\\%s", dir, strrchr(files[i], '\\') + 1);
                CreateDirectory(dir, NULL);
                ok = CopyFile(files[i], cmd, FALSE);
                if (ok) Record('F', cmd, rec);
                else TaskLog("  %s could not be copied.", cmd);
            }
        }
    } else {
        /* Some setup programs are published inside a zip file: unpack it and
         * run the one setup program in it. */
        if (lstrlen(files[0]) > 4 && lstrcmpi(files[0] + lstrlen(files[0]) - 4, ".zip") == 0) {
            lstrcpy(zipPath, files[0]);
            wsprintf(unpacked, "%s%s", g_downloadDir, p->f[F_PACKAGE]);
            if (!SetupFromZip(zipPath, unpacked, files[0], err, sizeof(err))) { TaskLog("  %s", err); return 0; }
        }
        Expand(After(inst, 1), dir, exp, sizeof(exp));   /* switches may name {dir}, e.g. /D={dir} for NSIS */
        extra = exp;
        if (strncmp(inst, "inno", 4) == 0)
            wsprintf(cmd, "\"%s\" /VERYSILENT /SUPPRESSMSGBOXES /NORESTART %s", files[0], extra);
        else if (strncmp(inst, "nsis", 4) == 0)
            wsprintf(cmd, "\"%s\" /S %s", files[0], extra);
        else if (strncmp(inst, "msi", 3) == 0) {
            GetSystemDirectory(sysdir, sizeof(sysdir));
            wsprintf(cmd, "\"%s\\MSIEXEC.EXE\" /i \"%s\" /qb %s", sysdir, files[0], extra);
        } else
            wsprintf(cmd, "\"%s\" %s", files[0], extra);
        TaskLog("Running its setup program. This can take a minute.");
        code = Run(cmd, INFINITE);
        if (code == -1) { TaskLog("  The setup program could not be started."); ok = 0; }
        else if (code == 3010 || code == 1641) TaskLog("  Done. Windows must be restarted to finish.");
        else if (code != 0) { TaskLog("  The setup program ended with error %d.", code); ok = 0; }
    }
    if (!ok) return 0;

    /* Record the folder before After steps, which may refer to {dir:...} of this package. */
    SetInstalled(p->f[F_PACKAGE], p->f[F_VERSION], dir);
    for (i = 0; Line(p->f[F_AFTER], i, line, sizeof(line)); i++) {
        if (strncmp(line, "run ", 4) == 0) {
            Expand(line + 4, dir, exp, sizeof(exp));
            TaskLog("Running %s", exp);
            code = Run(exp, 120000);
            if (code == -1) TaskLog("  It could not be started.");
        } else if (strncmp(line, "write ", 6) == 0) {
            char *bar = strchr(line, '|'), *t;
            FILE *f;
            if (!bar) continue;
            *bar = 0;
            t = bar + 1;
            while (*t == ' ') t++;
            k = lstrlen(line + 6);
            while (k && line[5 + k] == ' ') line[5 + k--] = 0;
            Expand(line + 6, dir, exp, sizeof(exp));
            f = fopen(exp, "w");
            if (f) {
                for (; *t; t++) {
                    if (t[0] == '\\' && t[1] == 'n') { fputc('\n', f); t++; }
                    else fputc(*t, f);
                }
                fclose(f);
                Record('F', exp, rec);
                TaskLog("Wrote %s", exp);
            }
        } else if (strncmp(line, "path ", 5) == 0) {
            Expand(line + 5, dir, exp, sizeof(exp));
            if (AddToPath(exp, p->f[F_PACKAGE])) {
                Record('P', exp, rec);
                TaskLog("Added %s to PATH in AUTOEXEC.BAT. It takes effect after a restart.", exp);
            }
        }
    }
    for (i = 0; Line(p->f[F_SHORTCUT], i, line, sizeof(line)); i++) {
        char name[200], target[MAX_PATH], args[400], *a, *b;
        a = strchr(line, '|');
        if (!a) continue;
        *a++ = 0;
        b = strchr(a, '|');
        if (b) *b++ = 0;
        lstrcpyn(name, line, sizeof(name));
        while (lstrlen(name) && name[lstrlen(name) - 1] == ' ') name[lstrlen(name) - 1] = 0;
        while (*a == ' ') a++;
        k = lstrlen(a);
        while (k && a[k - 1] == ' ') a[--k] = 0;
        Expand(a, dir, target, sizeof(target));
        args[0] = 0;
        if (b) { while (*b == ' ') b++; Expand(b, dir, args, sizeof(args)); }
        if (MakeShortcut(name, target, args, rec)) TaskLog("Added %s to the Start Menu.", name);
    }
    for (i = 0; i < count; i++) DeleteFile(files[i]);
    if (zipPath[0]) { DeleteFile(zipPath); DeleteTree(unpacked); }
    TaskLog("%s is installed.", p->f[F_NAME]);
    return 1;
}

static int InstallWork(void *ctx)
{
    JOB *job = (JOB *)ctx;
    RECORD rec;
    int i, ok;
    Dirs();
    for (i = 0; i < job->n; i++) {
        if (TaskCancelled()) break;
        RecordOpen(&rec, job->q[i]->f[F_PACKAGE]);
        ok = InstallOne(job->q[i], &rec);
        if (rec.f) fclose(rec.f);
        if (!ok) {
            TaskLog("");
            TaskLog("%s was not installed.%s", job->q[i]->f[F_NAME], i + 1 < job->n ? " The packages after it were not installed either." : "");
            return 0;
        }
        job->done++;
    }
    TaskLog("");
    if (TaskCancelled()) { TaskLog("Cancelled."); return 0; }
    TaskLog("Finished: %d package%s installed.", job->done, job->done == 1 ? "" : "s");
    return 1;
}

/* ------------------------------------------------------------------------
 * Choosing what to install, and asking first
 * --------------------------------------------------------------------- */

static void Enqueue(JOB *job, PKG *p)
{
    PKG *dep;
    int i;
    for (i = 0; i < job->n; i++) if (job->q[i] == p) return;
    if (p->f[F_DEPENDS] && (dep = FindPkg(&g_cat, p->f[F_DEPENDS])) != NULL && dep->status == ST_NO) Enqueue(job, dep);
    if (job->n < MAX_QUEUE) job->q[job->n++] = p;
}

/* The license text of p, downloaded into memory. */
static char *GetLicense(PKG *p, char *err, int errLen)
{
    char url[600], path[MAX_PATH], *q;
    const char *base = SourceBase(p), *headers = g_src[p->source].headers;
    HANDLE f;
    DWORD n, got;
    char *text = NULL;
    Dirs();
    wsprintf(path, "%sLICENSE.TMP", g_downloadDir);
    if (!IsUrl(base)) {                                     /* a folder source */
        wsprintf(url, "%s%s", base, p->f[F_LICENSE_FILE]);
        for (q = url; *q; q++) if (*q == '/') *q = '\\';
        if (!CopyFile(url, path, FALSE)) { wsprintf(err, "%s could not be read.", url); return NULL; }
        SetFileAttributes(path, FILE_ATTRIBUTE_NORMAL);
    } else {
        /* Over HTTPS first; plain HTTP only when the source has no access key. */
        if (strncmp(base, "http://", 7) == 0) wsprintf(url, "https://%s%s", base + 7, p->f[F_LICENSE_FILE]);
        else wsprintf(url, "%s%s", base, p->f[F_LICENSE_FILE]);
        if (!HttpGetFileH(url, headers[0] ? headers : NULL, 1, path, 0, NULL, NULL, NULL, err, errLen)) {
            if (headers[0] || strncmp(base, "http://", 7) != 0) return NULL;
            wsprintf(url, "%s%s", base, p->f[F_LICENSE_FILE]);
            if (!HttpGetFile(url, path, 0, NULL, NULL, NULL, err, errLen)) return NULL;
        }
    }
    f = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (f != INVALID_HANDLE_VALUE) {
        n = GetFileSize(f, NULL);
        if (n > 200000) n = 200000;
        text = (char *)malloc(n + 1);
        if (text && ReadFile(f, text, n, &got, NULL)) text[got] = 0;
        CloseHandle(f);
    }
    DeleteFile(path);
    return text;
}

typedef struct { JOB *job; char **texts; } LICENSES;

static int LicenseWork(void *ctx)
{
    LICENSES *l = (LICENSES *)ctx;
    char err[300];
    int i;
    for (i = 0; i < l->job->n; i++) {
        if (TaskCancelled()) return 0;
        TaskLog("Getting the license of %s", l->job->q[i]->f[F_NAME]);
        l->texts[i] = GetLicense(l->job->q[i], err, sizeof(err));
        if (!l->texts[i]) { TaskLog("  %s", err); return 0; }
    }
    return 1;
}

static void Flow(const char *in, char *out, int outLen)
{
    int o = 0;
    for (; *in && o < outLen - 3; in++) {
        if (*in == '\n' && in[1] == '\n') { out[o++] = '\n'; out[o++] = '\n'; in++; }
        else if (*in == '\n') out[o++] = ' ';
        else out[o++] = *in;
    }
    out[o] = 0;
}

/* p needs need, another package of the catalog that is not installed (for
 * example KernelEx). Asks whether to install it too. */
int OfferPackage(HWND owner, PKG *p, PKG *need)
{
    char msg[1800], flow[1200];
    wsprintf(msg, "%s needs %s, which is not installed.", p->f[F_NAME], need->f[F_NAME]);
    if (need->f[F_WARNING]) {
        Flow(need->f[F_WARNING], flow, sizeof(flow));
        wsprintf(msg + lstrlen(msg), "\n\nAbout %s: %s", need->f[F_NAME], flow);
    }
    wsprintf(msg + lstrlen(msg), "\n\nTick %s too? It will be installed first.", need->f[F_NAME]);
    return MessageBox(owner, msg, APP_NAME, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES;
}

static int InQueue(JOB *job, PKG *p)
{
    int i;
    for (i = 0; i < job->n; i++) if (job->q[i] == p) return 1;
    return 0;
}

int InstallPackages(HWND owner, PKG **chosen, int count)
{
    JOB job;
    LICENSES lic;
    char *texts[MAX_QUEUE], head[1600], title[200], flow[1200], msg[1600];
    DWORD total = 0;
    int i, ok;

    memset(&job, 0, sizeof(job));
    for (i = 0; i < count; i++) if (chosen[i]->status != ST_YES) Enqueue(&job, chosen[i]);
    if (!job.n) { MessageBox(owner, "The chosen packages are already installed.", APP_NAME, MB_OK | MB_ICONINFORMATION); return 0; }
    /* Beacon itself goes last: it closes to be updated. */
    for (i = 0; i < job.n - 1; i++) {
        if (lstrcmp(job.q[i]->f[F_PACKAGE], SELF_PACKAGE) == 0) {
            PKG *self = job.q[i];
            memmove(&job.q[i], &job.q[i + 1], (job.n - 1 - i) * sizeof(PKG *));
            job.q[job.n - 1] = self;
            break;
        }
    }

    /* A missing requirement that another package provides: offer it, and put it first. */
    for (i = 0; i < job.n; i++) {
        PKG *need = MissingPackage(job.q[i]);
        int k;
        if (!need || InQueue(&job, need) || job.n >= MAX_QUEUE) continue;
        if (!OfferPackage(owner, job.q[i], need)) break;
        for (k = job.n; k > i; k--) job.q[k] = job.q[k - 1];
        job.q[i] = need;
        job.n++;
        need->marked = 1;
        i++;
    }
    for (i = 0; i < job.n; i++) {
        PKG *need = MissingPackage(job.q[i]);
        int missing = job.q[i]->reqMissing - (need && InQueue(&job, need) ? 1 : 0);
        if (missing > 0) {
            wsprintf(msg, "%s cannot be installed yet: a component it needs is missing. Its details say which one.\n\n"
                     "Beacon 98 does not supply it, because it is not ours to distribute.", job.q[i]->f[F_NAME]);
            MessageBox(owner, msg, APP_NAME, MB_OK | MB_ICONSTOP);
            return 0;
        }
        if (!SystemListed(job.q[i]->f[F_SYSTEMS])) {
            wsprintf(msg, "%s is made for Windows %s, not for this version of Windows.\n\nInstall it anyway?",
                     job.q[i]->f[F_NAME], job.q[i]->f[F_SYSTEMS]);
            if (MessageBox(owner, msg, APP_NAME, MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES) return 0;
        }
    }

    memset(texts, 0, sizeof(texts));
    lic.job = &job;
    lic.texts = texts;
    ok = RunTask(owner, "Beacon 98", LicenseWork, &lic, 1);
    for (i = 0; ok && i < job.n; i++) {
        PKG *p = job.q[i];
        head[0] = 0;
        if (p->f[F_WARNING]) {
            Flow(p->f[F_WARNING], flow, sizeof(flow));
            wsprintf(head, "Known security problems: %s\n\n", flow);
        }
        wsprintf(head + lstrlen(head), "%s is offered under the license below (%s).%s",
                 p->f[F_NAME], p->f[F_LICENSE], p->external ? " It is downloaded from its publisher's server." : "");
        wsprintf(title, "Install %s %s", p->f[F_NAME], p->f[F_VERSION]);
        ok = ConfirmBox(owner, title, head, texts[i], "I &Agree", "Cancel");
    }
    for (i = 0; i < job.n; i++) free(texts[i]);
    if (!ok) return 0;

    for (i = 0; i < job.n; i++) total += job.q[i]->bytes;
    wsprintf(msg, "Install %d package%s? About %lu KB will be downloaded.\n\nEvery file is checked against the signed catalog before it is used.",
             job.n, job.n == 1 ? "" : "s", (total + 1023) / 1024);
    if (job.n > 1) {
        lstrcat(msg, "\n");
        for (i = 0; i < job.n && lstrlen(msg) < 1400; i++) wsprintf(msg + lstrlen(msg), "\n    %s %s", job.q[i]->f[F_NAME], job.q[i]->f[F_VERSION]);
    }
    if (MessageBox(owner, msg, APP_NAME, MB_OKCANCEL | MB_ICONQUESTION) != IDOK) return 0;
    RunTask(owner, "Installing", InstallWork, &job, 0);
    for (i = 0; i < job.n; i++) job.q[i]->marked = 0;
    if (g_selfUpdate) PostMessage(owner, WM_CLOSE, 0, 0);
    return job.done;
}

/* ------------------------------------------------------------------------
 * Removing
 * --------------------------------------------------------------------- */

static int FindUninstallString(const char *display, char *out, int outLen)
{
    HKEY root, k;
    char sub[260], name[260];
    DWORD i, n, type;
    int found = 0;
    out[0] = 0;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &root) != ERROR_SUCCESS) return 0;
    for (i = 0; !found && RegEnumKey(root, i, sub, sizeof(sub)) == ERROR_SUCCESS; i++) {
        if (RegOpenKeyEx(root, sub, 0, KEY_READ, &k) != ERROR_SUCCESS) continue;
        n = sizeof(name);
        if (RegQueryValueEx(k, "DisplayName", NULL, &type, (BYTE *)name, &n) != ERROR_SUCCESS) name[0] = 0;
        if (lstrcmpi(name, display) == 0 || lstrcmpi(sub, display) == 0) {
            n = outLen;
            found = RegQueryValueEx(k, "UninstallString", NULL, &type, (BYTE *)out, &n) == ERROR_SUCCESS && out[0];
        }
        RegCloseKey(k);
    }
    RegCloseKey(root);
    return found;
}

static int RemoveWork(void *ctx)
{
    PKG *p = (PKG *)ctx;
    char path[MAX_PATH], cmd[1024], line[MAX_PATH + 4], dir[MAX_PATH];
    char **items = NULL;
    FILE *f;
    int n = 0, cap = 0, i, code;
    const char *u = p->f[F_UNINSTALL];

    TaskLog("Removing %s", p->f[F_NAME]);
    InstalledDir(p->f[F_PACKAGE], dir, sizeof(dir));
    /* Remove steps run first, while the files are still there (for example regsvr32 /u). */
    for (i = 0; Line(p->f[F_REMOVE], i, line, sizeof(line)); i++) {
        if (strncmp(line, "run ", 4) != 0) continue;
        Expand(line + 4, dir, cmd, sizeof(cmd));
        TaskLog("Running %s", cmd);
        Run(cmd, 120000);
    }
    if (strncmp(u, "registry ", 9) == 0) {
        if (!FindUninstallString(u + 9, cmd, sizeof(cmd))) { TaskLog("Windows does not list an uninstaller for it."); return 0; }
        TaskLog("Running its uninstaller. Answer its questions if it asks any.");
        code = Run(cmd, INFINITE);
        if (code == -1) { TaskLog("The uninstaller could not be started."); return 0; }
    } else if (strncmp(u, "run ", 4) == 0) {
        Expand(u + 4, dir, cmd, sizeof(cmd));
        TaskLog("Running its uninstaller.");
        code = Run(cmd, INFINITE);
        if (code == -1) { TaskLog("The uninstaller could not be started."); return 0; }
    }
    /* Then what Beacon itself created: every file for "files"; shortcuts and PATH lines otherwise. */
    wsprintf(path, "%s%s.TXT", g_filesDir, p->f[F_PACKAGE]);
    f = fopen(path, "r");
    if (!f && strncmp(u, "files", 5) == 0) { TaskLog("Beacon 98 has no record of what it installed for this package."); return 0; }
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            int len = lstrlen(line);
            while (len && (line[len - 1] == '\n' || line[len - 1] == '\r')) line[--len] = 0;
            if (len < 3) continue;
            if (n == cap) {
                char **grown;
                cap = cap ? cap * 2 : 256;
                grown = (char **)realloc(items, cap * sizeof(char *));
                if (!grown) break;
                items = grown;
            }
            items[n] = (char *)malloc(len + 1);
            if (items[n]) lstrcpy(items[n++], line);
        }
        fclose(f);
        for (i = n - 1; i >= 0; i--) {                    /* newest first: files before their folders */
            char *item = items[i] + 2;
            switch (items[i][0]) {
            case 'F': case 'L': DeleteFile(item); break;
            case 'D': RemoveDirectory(item); break;
            case 'P': RemoveFromPath(p->f[F_PACKAGE]); break;
            }
            free(items[i]);
        }
        free(items);
        DeleteFile(path);
        TaskLog("Removed %d files and folders.", n);
    }
    SetInstalled(p->f[F_PACKAGE], NULL, NULL);
    TaskLog("Done.");
    return 1;
}

int RemovePackage(HWND owner, PKG *p)
{
    char msg[600];
    int i;
    Dirs();
    if (lstrcmp(p->f[F_UNINSTALL], "none") == 0) {
        wsprintf(msg, "%s cannot be removed: it becomes part of Windows.", p->f[F_NAME]);
        MessageBox(owner, msg, APP_NAME, MB_OK | MB_ICONINFORMATION);
        return 0;
    }
    for (i = 0; i < g_cat.count; i++) {
        PKG *o = &g_cat.pkg[i];
        if (o->status != ST_NO && o->f[F_DEPENDS] && lstrcmp(o->f[F_DEPENDS], p->f[F_PACKAGE]) == 0) {
            wsprintf(msg, "%s needs %s. Remove %s first.", o->f[F_NAME], p->f[F_NAME], o->f[F_NAME]);
            MessageBox(owner, msg, APP_NAME, MB_OK | MB_ICONINFORMATION);
            return 0;
        }
    }
    wsprintf(msg, "Remove %s %s from this computer?", p->f[F_NAME], p->have[0] ? p->have : p->f[F_VERSION]);
    if (MessageBox(owner, msg, APP_NAME, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES) return 0;
    return RunTask(owner, "Removing", RemoveWork, p, 0);
}

/* ------------------------------------------------------------------------
 * Updating the catalog
 * --------------------------------------------------------------------- */

/* Fetches a source's CATALOG.TXT or CATALOG.SIG into path: from its folder,
 * or from its address, over HTTPS first. */
static int FetchCatalogFile(int n, const char *file, const char *path)
{
    char url[600], err[300];
    SOURCE *s = &g_src[n];
    int secure;
    if (!IsUrl(s->location)) {
        wsprintf(url, "%s%s", s->location, file);
        if (CopyFile(url, path, FALSE)) { SetFileAttributes(path, FILE_ATTRIBUTE_NORMAL); return 1; }
        TaskLog("  %s could not be read.", url);
        return 0;
    }
    for (secure = 1; secure >= 0; secure--) {
        const char *rest = strstr(s->location, "://") + 3;
        if (!secure && (s->headers[0] || strncmp(s->location, "https://", 8) == 0)) break;
        wsprintf(url, "%s://%s%s", secure ? "https" : "http", rest, file);
        if (HttpGetFileH(url, s->headers[0] ? s->headers : NULL, 1, path, 0, TaskCancelFlag(), NULL, NULL, err, sizeof(err))) return 1;
        TaskLog("  %s: %s", url, err);
    }
    return 0;
}

/* Updates the catalog of source n. Returns 1 when it has a valid catalog. */
static int UpdateSource(int n)
{
    char cat[MAX_PATH], sig[MAX_PATH], newCat[MAX_PATH], newSig[MAX_PATH], err[300], keyId[17];
    SOURCE *s = &g_src[n];
    CATALOG c;
    int r;
    SourceFiles(n, cat, sig);
    wsprintf(newCat, "%sCATALOG.NEW", g_dir);
    wsprintf(newSig, "%sSIGNATUR.NEW", g_dir);
    TaskLog("");
    TaskLog("%s: downloading the catalog from %s", s->name, s->location);
    if (!FetchCatalogFile(n, CATALOG_FILE, newCat)) return 0;
    if (!FetchCatalogFile(n, SIG_FILE, newSig)) { DeleteFile(newCat); return 0; }
    if (ClockNote()[0]) TaskLog("%s", ClockNote());
    r = VerifySource(n, newCat, newSig);
    if (r != SIG_OK) {
        TaskLog("The downloaded catalog was not used: %s.", n ? (r == SIG_INVALID ? "its signature does not match" : SigText(r)) : SigText(r));
        DeleteFile(newCat); DeleteFile(newSig);
        return 0;
    }
    if (n) {
        KeyIdOf(s->key, keyId);
        TaskLog("Signature verified with this source's key %s.", keyId);
    } else TaskLog("Signature verified: Backport Labs key %s.", g_keyId);
    if (!LoadCatalog(newCat, &c, err, sizeof(err))) {
        TaskLog("The downloaded catalog was not used: %s", err);
        DeleteFile(newCat); DeleteFile(newSig);
        return 0;
    }
    if (s->loaded && s->cat.serial[0] && lstrcmp(c.serial, s->cat.serial) < 0) {
        TaskLog("The source offered catalog %s, older than the %s already here. It was not used.", c.serial, s->cat.serial);
        FreeCatalog(&c);
        DeleteFile(newCat); DeleteFile(newSig);
        return 0;
    }
    TaskLog("Catalog %s of %s, %d packages.", c.serial, c.date, c.count);
    FreeCatalog(&c);
    DeleteFile(cat); DeleteFile(sig);
    if (!MoveFile(newCat, cat) || !MoveFile(newSig, sig)) { TaskLog("The catalog could not be saved in %s.", g_dir); return 0; }
    return 1;
}

static int UpdateWork(void *ctx)
{
    int i, ok;
    (void)ctx;
    ok = UpdateSource(0);
    for (i = 1; i < g_nsrc && !TaskCancelled(); i++) UpdateSource(i);
    return ok;
}
int UpdateCatalog(HWND owner)
{
    char probe[MAX_PATH];
    HANDLE f;
    wsprintf(probe, "%sWRITE.TMP", g_dir);
    f = CreateFile(probe, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, NULL);
    if (f == INVALID_HANDLE_VALUE) {
        MessageBox(owner, "Beacon 98 cannot save files in its folder. If it runs from a CD, copy it to a folder on the hard disk first.",
                   APP_NAME, MB_OK | MB_ICONWARNING);
        return 0;
    }
    CloseHandle(f);
    return RunTask(owner, "Updating the catalog", UpdateWork, NULL, 1);
}
