/* srcdlg.c - Settings, Sources: the window where the user adds, changes and
 * deletes custom sources. Backport Labs' own source is listed first and
 * cannot be changed.
 *
 * Nothing is written until OK. Then SOURCES.TXT is rewritten, and the saved
 * catalogs (CATn.TXT) follow their sources to their new numbers, so that a
 * deleted source does not leave its catalog to the one after it.
 */
#include "beacon.h"

#define CLASS_SOURCES "Beacon98Sources"
#define DLG_W 470
#define DLG_H 354
#define ID_LIST     401
#define ID_NEW      402
#define ID_DELETE   403
#define ID_NAME     404
#define ID_LOCATION 405
#define ID_KEY      406
#define ID_HEADERS  407
#define ID_OK       408
#define ID_CANCEL   409

typedef struct {
    char name[64], location[260], key[80], headers[512];
    int from;                /* its number before, 0 for a new one */
} ENTRY;

static ENTRY g_e[MAX_SOURCES];
static int g_n, g_sel = -1, g_answer, g_done, g_loading;
static HWND g_wnd, g_lb, g_name, g_loc, g_key, g_hdr, g_del;

static void Label(ENTRY *e, char *out)
{
    wsprintf(out, "%s", e->name[0] ? e->name : "(new source)");
}

/* Copies the fields into the selected entry. */
static void Commit(void)
{
    char label[80];
    ENTRY *e;
    if (g_sel < 1 || g_sel >= g_n || g_loading) return;
    e = &g_e[g_sel];
    GetWindowText(g_name, e->name, sizeof(e->name));
    GetWindowText(g_loc, e->location, sizeof(e->location));
    GetWindowText(g_key, e->key, sizeof(e->key));
    GetWindowText(g_hdr, e->headers, sizeof(e->headers));
    Label(e, label);
    g_loading = 1;
    SendMessage(g_lb, LB_DELETESTRING, g_sel, 0);
    SendMessage(g_lb, LB_INSERTSTRING, g_sel, (LPARAM)label);
    SendMessage(g_lb, LB_SETCURSEL, g_sel, 0);
    g_loading = 0;
}

static void Show(int i)
{
    int own = i == 0;
    g_loading = 1;
    g_sel = i;
    SendMessage(g_lb, LB_SETCURSEL, i, 0);
    if (own) {
        char key[80];
        wsprintf(key, "Built into Beacon 98 (Key-Id %s)", g_keyId);
        SetWindowText(g_name, g_src[0].name);
        SetWindowText(g_loc, g_src[0].location);
        SetWindowText(g_key, key);
        SetWindowText(g_hdr, "");
    } else {
        SetWindowText(g_name, g_e[i].name);
        SetWindowText(g_loc, g_e[i].location);
        SetWindowText(g_key, g_e[i].key);
        SetWindowText(g_hdr, g_e[i].headers);
    }
    SendMessage(g_name, EM_SETREADONLY, own, 0);
    SendMessage(g_loc, EM_SETREADONLY, own, 0);
    SendMessage(g_key, EM_SETREADONLY, own, 0);
    SendMessage(g_hdr, EM_SETREADONLY, own, 0);
    EnableWindow(g_del, !own);
    g_loading = 0;
}

static int Fail(int i, HWND field, const char *msg)
{
    char text[400];
    Show(i);
    wsprintf(text, "%s: %s", g_e[i].name[0] ? g_e[i].name : "The new source", msg);
    MessageBox(g_wnd, text, APP_NAME, MB_OK | MB_ICONWARNING);
    SetFocus(field);
    return 0;
}

/* Checks every entry. Returns 0, having said what is wrong, when one is not right. */
static int Check(void)
{
    BYTE key[32];
    int i;
    for (i = 1; i < g_n; i++) {
        ENTRY *e = &g_e[i];
        const char *h;
        int url = strncmp(e->location, "http://", 7) == 0 || strncmp(e->location, "https://", 8) == 0;
        if (!e->name[0] || strchr(e->name, '|')) return Fail(i, g_name, "the name is empty or has a | in it.");
        if (!e->location[0] || strchr(e->location, '|')) return Fail(i, g_loc, "the location is empty or has a | in it.");
        if (!url && !(e->location[1] == ':' && e->location[2] == '\\') && strncmp(e->location, "\\\\", 2) != 0)
            return Fail(i, g_loc, "the location must be a web address (http:// or https://) or a folder such as D:\\SOURCE\\ or \\\\SERVER\\SHARE\\.");
        if (lstrlen(e->key) != 64 || !FromHex(e->key, key, 32))
            return Fail(i, g_key, "the public key must be 64 hexadecimal digits, as its publisher gives it.");
        for (h = e->headers; *h; ) {
            const char *end = h;
            while (*end && *end != '\r' && *end != '\n') end++;
            if (end > h) {
                const char *c = h;
                while (c < end && *c != ':') c++;
                if (c == h || c == end) return Fail(i, g_hdr, "each access header must be written as Name: value, one per line.");
            }
            h = end;
            while (*h == '\r' || *h == '\n') h++;
        }
        if (strchr(e->headers, '|') || strstr(e->headers, ";;")) return Fail(i, g_hdr, "the access headers cannot contain | or ;;.");
        if (e->headers[0] && !url) return Fail(i, g_hdr, "access headers are only for web addresses.");
        if (e->headers[0] && strncmp(e->location, "http://", 7) == 0)
            return Fail(i, g_loc, "a source with access headers must use an https:// address: Beacon never sends them unencrypted.");
    }
    return 1;
}

static void CacheName(int n, const char *ext, char *out)
{
    wsprintf(out, "%sCAT%d.%s", g_dir, n, ext);
}

/* Moves the saved catalogs of the sources that kept their key to their new numbers. */
static void MoveCaches(SOURCE *list)
{
    char a[MAX_PATH], b[MAX_PATH];
    int i, k;
    static const char *ext[2] = { "TXT", "SIG" }, *old[2] = { "OLT", "OLS" };
    for (i = 1; i < MAX_SOURCES; i++)
        for (k = 0; k < 2; k++) {
            CacheName(i, ext[k], a); CacheName(i, old[k], b);
            DeleteFile(b);
            MoveFile(a, b);
        }
    for (i = 1; i < g_n; i++) {
        int f = g_e[i].from;
        if (!f || memcmp(g_src[f].key, list[i].key, 32) != 0) continue;
        for (k = 0; k < 2; k++) {
            CacheName(f, old[k], a); CacheName(i, ext[k], b);
            MoveFile(a, b);
        }
    }
    for (i = 1; i < MAX_SOURCES; i++)
        for (k = 0; k < 2; k++) { CacheName(i, old[k], a); DeleteFile(a); }
}

/* Writes SOURCES.TXT from the entries. */
static int Save(void)
{
    static SOURCE list[MAX_SOURCES];
    char *h, *o;
    int i;
    memset(list, 0, sizeof(list));
    for (i = 1; i < g_n; i++) {
        SOURCE *s = &list[i];
        lstrcpy(s->name, g_e[i].name);
        lstrcpy(s->location, g_e[i].location);
        NormalizeLocation(s->location, sizeof(s->location));
        FromHex(g_e[i].key, s->key, 32);
        for (h = g_e[i].headers, o = s->headers; *h; ) {   /* one "Name: value\r\n" per line */
            const char *end = h;
            while (*end && *end != '\r' && *end != '\n') end++;
            if (end > h && o + (end - h) + 3 < s->headers + sizeof(s->headers)) {
                memcpy(o, h, end - h);
                o += end - h;
                *o++ = '\r'; *o++ = '\n';
            }
            h = (char *)end;
            while (*h == '\r' || *h == '\n') h++;
        }
        *o = 0;
    }
    if (!WriteSources(list, g_n)) {
        MessageBox(g_wnd, "SOURCES.TXT could not be saved in the folder of Beacon 98.", APP_NAME, MB_OK | MB_ICONWARNING);
        return 0;
    }
    MoveCaches(list);
    return 1;
}

static LRESULT CALLBACK SourcesProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_LIST:
            if (HIWORD(wp) == LBN_SELCHANGE && !g_loading) {
                int i = (int)SendMessage(g_lb, LB_GETCURSEL, 0, 0);
                Commit();
                if (i >= 0) Show(i);
            }
            return 0;
        case ID_NAME:
            if (HIWORD(wp) == EN_KILLFOCUS) Commit();
            return 0;
        case ID_NEW:
            Commit();
            if (g_n >= MAX_SOURCES) {
                MessageBox(hwnd, "Beacon 98 takes up to 7 custom sources.", APP_NAME, MB_OK | MB_ICONINFORMATION);
                return 0;
            }
            memset(&g_e[g_n], 0, sizeof(ENTRY));
            SendMessage(g_lb, LB_ADDSTRING, 0, (LPARAM)"(new source)");
            Show(g_n++);
            SetFocus(g_name);
            return 0;
        case ID_DELETE: {
            char text[200];
            int i;
            if (g_sel < 1) return 0;
            Commit();
            wsprintf(text, "Delete the source %s?", g_e[g_sel].name[0] ? g_e[g_sel].name : "(new source)");
            if (MessageBox(hwnd, text, APP_NAME, MB_YESNO | MB_ICONQUESTION) != IDYES) return 0;
            for (i = g_sel; i < g_n - 1; i++) g_e[i] = g_e[i + 1];
            g_n--;
            SendMessage(g_lb, LB_DELETESTRING, g_sel, 0);
            Show(g_sel < g_n ? g_sel : g_n - 1);
            return 0;
        }
        case ID_OK:
        case IDOK:
            Commit();
            if (!Check() || !Save()) return 0;
            g_answer = 1;
            DestroyWindow(hwnd);
            return 0;
        case ID_CANCEL:
        case IDCANCEL:
            DestroyWindow(hwnd);
            return 0;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        g_done = 1;
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

static HWND Child(const char *cls, const char *text, DWORD style, DWORD ex, int x, int y, int w, int h, int id)
{
    HWND c = CreateWindowEx(ex, cls, text, WS_CHILD | WS_VISIBLE | style, x, y, w, h, g_wnd, (HMENU)id, g_inst, NULL);
    SendMessage(c, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
    return c;
}

/* Returns 1 when the sources were changed and saved. */
int SourcesDialog(HWND owner)
{
    static int registered;
    WNDCLASS wc;
    RECT r;
    MSG m;
    int x, y, w, h, i;
    const int fx = 190, fw = DLG_W - 190 - 12;
    if (!registered) {
        memset(&wc, 0, sizeof(wc));
        wc.lpfnWndProc = SourcesProc;
        wc.hInstance = g_inst;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszClassName = CLASS_SOURCES;
        RegisterClass(&wc);
        registered = 1;
    }
    /* the entries: the sources as last read from SOURCES.TXT */
    memset(g_e, 0, sizeof(g_e));
    g_n = g_nsrc;
    for (i = 1; i < g_n; i++) {
        SOURCE *s = &g_src[i];
        lstrcpy(g_e[i].name, s->name);
        lstrcpy(g_e[i].location, s->location);
        ToHex(s->key, 32, g_e[i].key);
        lstrcpy(g_e[i].headers, s->headers);
        g_e[i].from = i;
    }

    SetRect(&r, 0, 0, DLG_W, DLG_H);
    AdjustWindowRect(&r, WS_CAPTION | WS_SYSMENU, FALSE);
    w = r.right - r.left;
    h = r.bottom - r.top;
    GetWindowRect(owner, &r);
    x = r.left + (r.right - r.left - w) / 2;
    y = r.top + (r.bottom - r.top - h) / 2;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    g_wnd = CreateWindowEx(WS_EX_DLGMODALFRAME, CLASS_SOURCES, "Sources", WS_CAPTION | WS_SYSMENU, x, y, w, h, owner, NULL, g_inst, NULL);
    if (!g_wnd) return 0;
    Child("STATIC", "&Sources:", 0, 0, 12, 12, 160, 16, 0);
    g_lb = Child("LISTBOX", "", LBS_NOTIFY | WS_VSCROLL | WS_TABSTOP, WS_EX_CLIENTEDGE, 12, 30, 166, 214, ID_LIST);
    Child("BUTTON", "&New", BS_PUSHBUTTON | WS_TABSTOP, 0, 12, 248, 80, 23, ID_NEW);
    g_del = Child("BUTTON", "&Delete", BS_PUSHBUTTON | WS_TABSTOP, 0, 98, 248, 80, 23, ID_DELETE);
    Child("STATIC", "N&ame:", 0, 0, fx, 12, fw, 16, 0);
    g_name = Child("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP, WS_EX_CLIENTEDGE, fx, 28, fw, 21, ID_NAME);
    Child("STATIC", "&Location (a web address, or a folder):", 0, 0, fx, 56, fw, 16, 0);
    g_loc = Child("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP, WS_EX_CLIENTEDGE, fx, 72, fw, 21, ID_LOCATION);
    Child("STATIC", "Public &key (64 hexadecimal digits):", 0, 0, fx, 100, fw, 16, 0);
    g_key = Child("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP, WS_EX_CLIENTEDGE, fx, 116, fw, 21, ID_KEY);
    Child("STATIC", "Access &headers, one per line (sent only over HTTPS, only to this source):", 0, 0, fx, 144, fw, 30, 0);
    g_hdr = Child("EDIT", "", ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_TABSTOP,
                  WS_EX_CLIENTEDGE, fx, 176, fw, 68, ID_HEADERS);
    SendMessage(g_name, EM_LIMITTEXT, sizeof(g_e[0].name) - 1, 0);
    SendMessage(g_loc, EM_LIMITTEXT, sizeof(g_e[0].location) - 2, 0);
    SendMessage(g_key, EM_LIMITTEXT, 64, 0);
    SendMessage(g_hdr, EM_LIMITTEXT, sizeof(g_e[0].headers) - 40, 0);
    Child("STATIC", "A source is a catalog signed with its publisher's own key. Add only sources you trust: "
          "they choose what Beacon 98 installs. The sources are kept in SOURCES.TXT.",
          0, 0, 12, 284, DLG_W - 24, 30, 0);
    Child("BUTTON", "OK", BS_DEFPUSHBUTTON | WS_TABSTOP, 0, DLG_W - 12 - 80 - 8 - 80, DLG_H - 30, 80, 23, ID_OK);
    Child("BUTTON", "Cancel", BS_PUSHBUTTON | WS_TABSTOP, 0, DLG_W - 12 - 80, DLG_H - 30, 80, 23, ID_CANCEL);
    SendMessage(g_lb, LB_ADDSTRING, 0, (LPARAM)g_src[0].name);
    for (i = 1; i < g_n; i++) {
        char label[80];
        Label(&g_e[i], label);
        SendMessage(g_lb, LB_ADDSTRING, 0, (LPARAM)label);
    }
    Show(g_n > 1 ? 1 : 0);
    ShowWindow(g_wnd, SW_SHOW);
    if (g_shotFile) {                                 /* test mode: draw it, then close */
        if (CaptureWindow(g_wnd, g_shotFile) == 0) g_shotFile = NULL;
        DestroyWindow(g_wnd);
        return 0;
    }
    SetFocus(g_lb);
    EnableWindow(owner, FALSE);
    g_done = 0;
    g_answer = 0;
    while (!g_done && GetMessage(&m, NULL, 0, 0) > 0) {
        if (IsDialogMessage(g_wnd, &m)) continue;
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    EnableWindow(owner, TRUE);
    SetForegroundWindow(owner);
    return g_answer;
}
