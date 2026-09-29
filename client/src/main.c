/* main.c - Beacon 98, a package manager for Windows 95 and 98.
 *
 * Beacon 98 reads a catalog signed by Backport Labs and lists the packages in
 * it. Two switches are for testing and change nothing on the computer:
 *   BEACON98.EXE /selftest                  runs the self-test (test.c)
 *   BEACON98.EXE /shot FILE.BMP [row] [/sort N ...] [/sources] [search words]
 *                                           draws the window into a bitmap: after
 *                                           clicking column N, or the Sources window
 *   BEACON98.EXE /unzip ARCHIVE FOLDER [strip]
 *                                           unpacks an archive, to test unzip.c
 */
#include "beacon.h"

HINSTANCE g_inst;
CATALOG g_cat;
char g_dir[MAX_PATH];
int g_testMode;

/* Copies the next word of a command line; a word may be in double quotes. */
static const char *NextWord(const char *p, char *out, int outLen)
{
    int i = 0;
    while (*p == ' ') p++;
    if (*p == '"') {
        p++;
        while (*p && *p != '"' && i < outLen - 1) out[i++] = *p++;
        if (*p == '"') p++;
    } else {
        while (*p && *p != ' ' && i < outLen - 1) out[i++] = *p++;
    }
    out[i] = 0;
    return p;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
    char *slash, word[MAX_PATH], file[MAX_PATH];
    const char *p;
    int row = -1, sources = 0, sorts[4], nsort = 0;
    (void)prev;
    g_inst = inst;
    GetModuleFileName(NULL, g_dir, sizeof(g_dir));
    slash = strrchr(g_dir, '\\');
    if (slash) slash[1] = 0;
    p = NextWord(cmd, word, sizeof(word));
    if (lstrcmpi(word, "/selftest") == 0) {
        g_testMode = 1;
        return SelfTest();
    }
    if (lstrcmpi(word, "/unzip") == 0) {           /* test: unpack an archive into a folder */
        char archive[MAX_PATH], err[300];
        g_testMode = 1;
        p = NextWord(p, archive, sizeof(archive));
        p = NextWord(p, file, sizeof(file));
        p = NextWord(p, word, sizeof(word));
        return Unzip(archive, file, atoi(word), NULL, NULL, NULL, err, sizeof(err)) ? 0 : 1;
    }
    if (lstrcmpi(word, "/shot") == 0) {
        g_testMode = 1;
        p = NextWord(p, file, sizeof(file));
        while (*p == ' ') p++;
        if (*p >= '0' && *p <= '9') {
            p = NextWord(p, word, sizeof(word));
            row = atoi(word);
        }
        for (;;) {
            while (*p == ' ') p++;
            if (strncmp(p, "/sort ", 6) == 0 && nsort < 4) {
                p = NextWord(p + 6, word, sizeof(word));
                sorts[nsort++] = atoi(word);
            } else if (strncmp(p, "/sources", 8) == 0) {
                sources = 1;
                p += 8;
            } else break;
        }
        return Shot(file, row, p, sorts, nsort, sources);
    }
    /* Setup waits for this mutex to go before it replaces the program. */
    CreateMutex(NULL, FALSE, "Beacon98Running");
    return RunWindow(show);
}
