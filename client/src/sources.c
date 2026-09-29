/* sources.c - the catalogs Beacon reads: Backport Labs' own, and custom
 * sources the user adds under Settings, Sources.
 *
 * A custom source is another catalog in the same format, at a web address
 * or in a folder (a local folder, a CD, or a network share). It must be
 * signed with its own Ed25519 key, whose public half the user enters; Beacon
 * never uses the Backport Labs key for it. A source may carry an access
 * header (for example the token of a private server), which Beacon sends
 * only over HTTPS and only to that source's host.
 *
 * SOURCES.TXT, next to the program, has one source per line:
 *   name|location|public key in hexadecimal|header;;header
 * The catalog of source n is kept as CATn.TXT and CATn.SIG.
 */
#include "beacon.h"

SOURCE g_src[MAX_SOURCES];
int g_nsrc;

static void Trim(char *s)
{
    int n = lstrlen(s);
    while (n && (s[n - 1] == '\r' || s[n - 1] == '\n' || s[n - 1] == ' ')) s[--n] = 0;
}

/* Makes a location end with / (address) or \ (folder). */
void NormalizeLocation(char *loc, int len)
{
    int n = lstrlen(loc);
    char sep = IsUrl(loc) ? '/' : '\\';
    if (n && loc[n - 1] != '/' && loc[n - 1] != '\\' && n < len - 1) { loc[n] = sep; loc[n + 1] = 0; }
}

/* Reads SOURCES.TXT. Source 0 is always Backport Labs. */
void ReadSources(void)
{
    char path[MAX_PATH], line[1200], *f[4], *p;
    FILE *fp;
    int i;
    for (i = 0; i < g_nsrc; i++) FreeCatalog(&g_src[i].cat);
    memset(g_src, 0, sizeof(g_src));
    lstrcpy(g_src[0].name, "Backport Labs");
    wsprintf(g_src[0].location, "http://%s/", CATALOG_HOST);
    g_nsrc = 1;
    wsprintf(path, "%sSOURCES.TXT", g_dir);
    fp = fopen(path, "r");
    if (!fp) return;
    while (g_nsrc < MAX_SOURCES && fgets(line, sizeof(line), fp)) {
        SOURCE *s = &g_src[g_nsrc];
        Trim(line);
        if (!line[0] || line[0] == '#') continue;
        f[0] = line;
        for (i = 1, p = line; i < 4; i++) {
            p = strchr(p, '|');
            if (!p) break;
            *p++ = 0;
            f[i] = p;
        }
        if (i < 3) continue;
        lstrcpyn(s->name, f[0], sizeof(s->name));
        lstrcpyn(s->location, f[1], sizeof(s->location));
        NormalizeLocation(s->location, sizeof(s->location));
        if (lstrlen(f[2]) != 64 || !FromHex(f[2], s->key, 32)) continue;
        s->headers[0] = 0;
        if (i == 4 && f[3][0]) {                    /* ";;" separates headers */
            char *h = f[3], *sep;
            while (h && *h) {
                sep = strstr(h, ";;");
                if (sep) *sep = 0;
                if (lstrlen(s->headers) + lstrlen(h) + 3 < (int)sizeof(s->headers)) { lstrcat(s->headers, h); lstrcat(s->headers, "\r\n"); }
                h = sep ? sep + 2 : NULL;
            }
        }
        g_nsrc++;
    }
    fclose(fp);
}

/* Writes SOURCES.TXT from list[1..n-1]. */
int WriteSources(const SOURCE *list, int n)
{
    char path[MAX_PATH], hex[65], headers[512], *p;
    FILE *fp;
    int i;
    wsprintf(path, "%sSOURCES.TXT", g_dir);
    fp = fopen(path, "w");
    if (!fp) return 0;
    fprintf(fp, "# Custom sources of Beacon 98: name|location|public key|headers (separated by ;;)\n");
    for (i = 1; i < n; i++) {
        ToHex(list[i].key, 32, hex);
        lstrcpyn(headers, list[i].headers, sizeof(headers));
        for (p = headers; *p; p++) if (p[0] == '\r' && p[1] == '\n') { p[0] = ';'; p[1] = ';'; }
        Trim(headers);
        while (lstrlen(headers) >= 2 && lstrcmp(headers + lstrlen(headers) - 2, ";;") == 0) headers[lstrlen(headers) - 2] = 0;
        fprintf(fp, "%s|%s|%s|%s\n", list[i].name, list[i].location, hex, headers);
    }
    fclose(fp);
    return 1;
}

void SourceFiles(int n, char *cat, char *sig)
{
    if (n == 0) { wsprintf(cat, "%s%s", g_dir, CATALOG_FILE); wsprintf(sig, "%s%s", g_dir, SIG_FILE); }
    else { wsprintf(cat, "%sCAT%d.TXT", g_dir, n); wsprintf(sig, "%sCAT%d.SIG", g_dir, n); }
}

int VerifySource(int n, const char *cat, const char *sig)
{
    return n == 0 ? VerifyCatalogFile(cat, sig) : VerifyCatalogFileKey(cat, sig, g_src[n].key);
}

/* Loads every source's catalog and merges their packages into g_cat. state
 * gets a line for the status bar. */
void LoadAllCatalogs(char *state, int stateLen, int *builtinResult)
{
    char cat[MAX_PATH], sig[MAX_PATH], err[200], extra[80];
    int i, j, r, total = 0, loaded = 0;
    free(g_cat.pkg);
    memset(&g_cat, 0, sizeof(g_cat));
    ReadSources();
    for (i = 0; i < g_nsrc; i++) {
        SourceFiles(i, cat, sig);
        r = VerifySource(i, cat, sig);
        if (i == 0) *builtinResult = r;
        g_src[i].state = r;
        if (r != SIG_OK) continue;
        if (!LoadCatalog(cat, &g_src[i].cat, err, sizeof(err))) { g_src[i].state = SIG_BAD_FILE; continue; }
        g_src[i].loaded = 1;
        total += g_src[i].cat.count;
    }
    g_cat.pkg = (PKG *)calloc(total ? total : 1, sizeof(PKG));
    for (i = 0; i < g_nsrc && g_cat.pkg; i++) {
        if (!g_src[i].loaded) continue;
        if (i > 0) loaded++;
        for (j = 0; j < g_src[i].cat.count; j++) {
            PKG *p = &g_cat.pkg[g_cat.count++];
            *p = g_src[i].cat.pkg[j];
            p->source = i;
        }
    }
    if (g_src[0].loaded) {
        lstrcpy(g_cat.serial, g_src[0].cat.serial);
        lstrcpy(g_cat.date, g_src[0].cat.date);
        lstrcpy(g_cat.base, g_src[0].cat.base);
        wsprintf(state, "Catalog %s, %s", g_cat.serial, SigText(SIG_OK));
    } else {
        wsprintf(g_cat.base, "http://%s/", CATALOG_HOST);
        wsprintf(state, "No catalog: %s", SigText(*builtinResult));
    }
    if (g_nsrc > 1) {
        wsprintf(extra, "; %d of %d custom sources", loaded, g_nsrc - 1);
        if (lstrlen(state) + lstrlen(extra) < stateLen) lstrcat(state, extra);
    }
    CheckSystem(&g_cat);
}

/* The base of package p's source: its catalog's Base for web sources, or its folder. */
const char *SourceBase(PKG *p)
{
    SOURCE *s = &g_src[p->source];
    if (p->source == 0) return g_cat.base;
    if (!IsUrl(s->location)) return s->location;
    return s->loaded && s->cat.base[0] ? s->cat.base : s->location;
}
