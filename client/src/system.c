/* system.c - what this computer has: the requirements of each package, and
 * which packages are installed already.
 */
#include "beacon.h"

#define UNINSTALL_KEY "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall"

static int RegText(HKEY root, const char *key, const char *name, char *out, DWORD outLen)
{
    HKEY k;
    DWORD type, n = outLen;
    int ok = 0;
    out[0] = 0;
    if (RegOpenKeyEx(root, key, 0, KEY_READ, &k) != ERROR_SUCCESS) return 0;
    if (RegQueryValueEx(k, name, NULL, &type, (BYTE *)out, &n) == ERROR_SUCCESS && type == REG_SZ) ok = 1;
    else out[0] = 0;
    RegCloseKey(k);
    return ok;
}

/* Replaces {pf}, {win} and {sys} with the folders of this computer. */
void ExpandPlaces(const char *in, char *out, int outLen)
{
    char place[MAX_PATH];
    int o = 0, n;
    while (*in && o < outLen - 1) {
        place[0] = 0;
        if (strncmp(in, "{pf}", 4) == 0) {
            if (!RegText(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", "ProgramFilesDir", place, sizeof(place)))
                lstrcpy(place, "C:\\Program Files");
            in += 4;
        } else if (strncmp(in, "{win}", 5) == 0) {
            GetWindowsDirectory(place, sizeof(place));
            in += 5;
        } else if (strncmp(in, "{sys}", 5) == 0) {
            GetSystemDirectory(place, sizeof(place));
            in += 5;
        } else {
            out[o++] = *in++;
            continue;
        }
        n = lstrlen(place);
        if (o + n >= outLen) break;
        lstrcpy(out + o, place);
        o += n;
    }
    out[o] = 0;
}

/* Compares two versions number by number: "0.3.3" < "0.3.4", "9.20" = "9.20.00.0".
 * Letters are ignored. Returns <0, 0 or >0. */
static int CompareVersions(const char *a, const char *b)
{
    unsigned long x, y;
    while (*a || *b) {
        while (*a && (*a < '0' || *a > '9')) a++;
        while (*b && (*b < '0' || *b > '9')) b++;
        x = *a ? strtoul(a, (char **)&a, 10) : 0;
        y = *b ? strtoul(b, (char **)&b, 10) : 0;
        if (x != y) return x < y ? -1 : 1;
    }
    return 0;
}

/* The version of a program file, as "a.b.c.d". */
static int FileVersion(const char *path, char *out)
{
    DWORD dummy, n = GetFileVersionInfoSize((char *)path, &dummy);
    void *data;
    VS_FIXEDFILEINFO *fi;
    UINT len;
    int ok = 0;
    if (!n || !(data = malloc(n))) return 0;
    if (GetFileVersionInfo((char *)path, 0, n, data) && VerQueryValue(data, "\\", (void **)&fi, &len) && len) {
        wsprintf(out, "%u.%u.%u.%u", HIWORD(fi->dwFileVersionMS), LOWORD(fi->dwFileVersionMS),
                 HIWORD(fi->dwFileVersionLS), LOWORD(fi->dwFileVersionLS));
        ok = 1;
    }
    free(data);
    return ok;
}

/* Checks one Requires line: "check argument | text". Copies the text to what.
 * Returns 1 when met, 0 when missing, -1 when this version cannot check it. */
int RequirementMet(const char *line, char *what, int whatLen)
{
    char check[20], arg[MAX_PATH], path[MAX_PATH], ver[40];
    const char *bar = strchr(line, '|');
    int i = 0, j = 0;
    MEMORYSTATUS ms;

    what[0] = 0;
    if (bar) {
        bar++;
        while (*bar == ' ') bar++;
        lstrcpyn(what, bar, whatLen);
    }
    while (line[i] && line[i] != ' ' && line[i] != '|' && i < (int)sizeof(check) - 1) { check[i] = line[i]; i++; }
    check[i] = 0;
    while (line[i] == ' ') i++;
    while (line[i] && line[i] != '|' && j < (int)sizeof(arg) - 1) arg[j++] = line[i++];
    while (j > 0 && arg[j - 1] == ' ') j--;
    arg[j] = 0;

    if (lstrcmp(check, "file") == 0) {
        ExpandPlaces(arg, path, sizeof(path));
        return GetFileAttributes(path) != 0xFFFFFFFF;
    }
    if (lstrcmp(check, "winsock2") == 0) {
        GetSystemDirectory(path, sizeof(path));
        lstrcat(path, "\\WS2_32.DLL");
        return GetFileAttributes(path) != 0xFFFFFFFF;
    }
    if (lstrcmp(check, "msi") == 0) {
        GetSystemDirectory(path, sizeof(path));
        lstrcat(path, "\\MSIEXEC.EXE");
        if (!FileVersion(path, ver)) return 0;
        return CompareVersions(ver, arg) >= 0;
    }
    if (lstrcmp(check, "ie") == 0) {
        if (!RegText(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Internet Explorer", "Version", ver, sizeof(ver))) return 0;
        return CompareVersions(ver, arg) >= 0;
    }
    if (lstrcmp(check, "memory") == 0) {
        ms.dwLength = sizeof(ms);
        GlobalMemoryStatus(&ms);
        /* Windows reports a little less than the installed memory. */
        return ms.dwTotalPhys / (1024 * 1024) + 4 >= strtoul(arg, NULL, 10);
    }
    return -1;
}

/* Looks for an Add/Remove Programs entry whose name is display (or whose key
 * is). Copies its version, if it has one. */
static int FindUninstall(const char *display, char *version, int versionLen)
{
    HKEY root, k;
    char sub[260], name[260];
    DWORD i, n, type;
    int found = 0;
    version[0] = 0;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, UNINSTALL_KEY, 0, KEY_READ, &root) != ERROR_SUCCESS) return 0;
    for (i = 0; !found && RegEnumKey(root, i, sub, sizeof(sub)) == ERROR_SUCCESS; i++) {
        if (RegOpenKeyEx(root, sub, 0, KEY_READ, &k) != ERROR_SUCCESS) continue;
        n = sizeof(name);
        if (RegQueryValueEx(k, "DisplayName", NULL, &type, (BYTE *)name, &n) != ERROR_SUCCESS || type != REG_SZ) name[0] = 0;
        if (lstrcmpi(name, display) == 0 || lstrcmpi(sub, display) == 0) {
            found = 1;
            n = versionLen;
            if (RegQueryValueEx(k, "DisplayVersion", NULL, &type, (BYTE *)version, &n) != ERROR_SUCCESS || type != REG_SZ)
                version[0] = 0;
        }
        RegCloseKey(k);
    }
    RegCloseKey(root);
    return found;
}

/* INSTALLED.TXT, next to the program, lists what Beacon installed: one
 * "package|version|folder" per line. */
static int FindInstalledList(const char *id, char *version, int versionLen)
{
    char path[MAX_PATH], line[700], *bar;
    FILE *f;
    int len = lstrlen(id), found = 0;
    version[0] = 0;
    wsprintf(path, "%sINSTALLED.TXT", g_dir);
    f = fopen(path, "r");
    if (!f) return 0;
    while (!found && fgets(line, sizeof(line), f)) {
        if (strncmp(line, id, len) == 0 && line[len] == '|') {
            bar = strchr(line + len + 1, '|');
            if (bar) *bar = 0;
            lstrcpyn(version, line + len + 1, versionLen);
            found = 1;
        }
    }
    fclose(f);
    return found;
}

/* This version of Windows, as the catalog writes it: 95, 98, ME, NT4 or 2000.
 * Later versions give "". */
const char *ThisWindows(void)
{
    OSVERSIONINFO v;
    v.dwOSVersionInfoSize = sizeof(v);
    if (!GetVersionEx(&v)) return "";
    if (v.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        if (v.dwMinorVersion >= 90) return "ME";
        if (v.dwMinorVersion >= 10) return "98";
        return "95";
    }
    if (v.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (v.dwMajorVersion == 4) return "NT4";
        if (v.dwMajorVersion == 5 && v.dwMinorVersion == 0) return "2000";
    }
    return "";
}

/* Whether a Systems field such as "95, 98, ME" names this Windows. */
int SystemListed(const char *systems)
{
    const char *me = ThisWindows();
    char word[16];
    int i;
    if (!me[0] || !systems) return 0;
    while (*systems) {
        while (*systems == ' ' || *systems == ',') systems++;
        for (i = 0; *systems && *systems != ',' && *systems != ' ' && i < (int)sizeof(word) - 1; i++) word[i] = *systems++;
        word[i] = 0;
        if (i && lstrcmpi(word, me) == 0) return 1;
    }
    return 0;
}

void CheckSystem(CATALOG *cat)
{
    char what[400], line[600];
    const char *r, *u;
    int i, j, found;
    for (i = 0; i < cat->count; i++) {
        PKG *p = &cat->pkg[i];
        p->reqMissing = 0;
        for (r = p->f[F_REQUIRES]; r && *r; ) {
            for (j = 0; r[j] && r[j] != '\n' && j < (int)sizeof(line) - 1; j++) line[j] = r[j];
            line[j] = 0;
            if (RequirementMet(line, what, sizeof(what)) == 0) p->reqMissing++;
            r += j;
            if (*r == '\n') r++;
        }
        u = p->f[F_UNINSTALL];
        if (strncmp(u, "registry ", 9) == 0) found = FindUninstall(u + 9, p->have, sizeof(p->have));
        else found = FindInstalledList(p->f[F_PACKAGE], p->have, sizeof(p->have));
        if (!found) p->status = ST_NO;
        else if (p->have[0] && CompareVersions(p->have, p->f[F_VERSION]) < 0) p->status = ST_UPDATE;
        else p->status = ST_YES;
    }
}
