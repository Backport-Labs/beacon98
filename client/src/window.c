/* window.c - the main window: groups on the left, packages on the right with
 * a search box above them, the details of the selected package below, and a
 * status bar that says whether the catalog's signature was verified.
 */
#include "beacon.h"

#define CLASS_MAIN "Beacon98Main"
#define ID_UPDATE  101
#define ID_INSTALL 102
#define ID_REMOVE  103
#define ID_SEARCH  104
#define ID_TREE    105
#define ID_LIST    106
#define ID_STATUS  107
#define ID_EXIT    120
#define ID_SOURCES 121
#define ID_README  122
#define ID_ABOUT   123

#define WM_FIRST_RUN (WM_APP + 1)
#define WM_OFFER     (WM_APP + 2)

#define G_ALL       (-1)
#define G_INSTALLED (-2)
#define G_UPDATES   (-3)
#define G_SOURCE(i) (-10 - (i))       /* the packages of custom source i */

#define BAR_H   32
#define TREE_W  176

static HWND g_main, g_tree, g_list, g_details, g_status, g_search, g_searchLabel;
static HWND g_bUpdate, g_bInstall, g_bRemove;
static HFONT g_font;
static int g_group = G_ALL;
static int g_filling;               /* the list is being refilled: ignore its notices */
static char g_catalogState[200];
static int g_sortCol = -1, g_sortDesc;  /* -1: catalog order */

static int ContainsNoCase(const char *text, const char *word)
{
    int n = lstrlen(word), i;
    char a[2], b[2];
    if (!text) return 0;
    a[1] = b[1] = 0;
    for (; *text; text++) {
        for (i = 0; i < n; i++) {
            a[0] = text[i]; b[0] = word[i];
            if (!a[0]) return 0;
            if (lstrcmpi(a, b) != 0) break;
        }
        if (i == n) return 1;
    }
    return 0;
}

/* Every word of the search must appear in the name, summary, description or identifier. */
static int Matches(PKG *p, const char *search)
{
    char word[64];
    int i;
    while (*search) {
        while (*search == ' ') search++;
        for (i = 0; *search && *search != ' ' && i < (int)sizeof(word) - 1; i++) word[i] = *search++;
        word[i] = 0;
        if (!i) break;
        if (!ContainsNoCase(p->f[F_NAME], word) && !ContainsNoCase(p->f[F_SUMMARY], word)
            && !ContainsNoCase(p->f[F_DESCRIPTION], word) && !ContainsNoCase(p->f[F_PACKAGE], word)) return 0;
    }
    return 1;
}

static int InGroup(PKG *p, int group)
{
    if (group == G_ALL) return 1;
    if (group == G_INSTALLED) return p->status == ST_YES || p->status == ST_UPDATE;
    if (group == G_UPDATES) return p->status == ST_UPDATE;
    if (group <= G_SOURCE(0)) return p->source == G_SOURCE(0) - group;
    return SectionIndex(p->f[F_SECTION]) == group;
}

static int Count(int group)
{
    int i, n = 0;
    for (i = 0; i < g_cat.count; i++) if (InGroup(&g_cat.pkg[i], group)) n++;
    return n;
}

static HANDLE AddGroup(const char *label, int group, HANDLE parent)
{
    MY_TVINSERT ins;
    char text[80];
    wsprintf(text, "%s (%d)", label, Count(group));
    memset(&ins, 0, sizeof(ins));
    ins.hParent = parent;
    ins.hInsertAfter = MY_TVI_LAST;
    ins.item.mask = MY_TVIF_TEXT | MY_TVIF_PARAM;
    ins.item.pszText = text;
    ins.item.lParam = group;
    return (HANDLE)SendMessage(g_tree, MY_TVM_INSERTITEMA, 0, (LPARAM)&ins);
}

static void FillTree(void)
{
    HANDLE all, first, sel = NULL, h;
    int i;
    g_filling = 1;
    SendMessage(g_tree, MY_TVM_DELETEITEM, 0, (LPARAM)MY_TVI_ROOT);
    first = all = AddGroup("All packages", G_ALL, MY_TVI_ROOT);
    h = AddGroup("Installed", G_INSTALLED, MY_TVI_ROOT);
    if (g_group == G_INSTALLED) sel = h;
    h = AddGroup("Updates", G_UPDATES, MY_TVI_ROOT);
    if (g_group == G_UPDATES) sel = h;
    for (i = 0; i < MAX_SECTIONS; i++) {
        if (!Count(i)) continue;
        h = AddGroup(g_sections[i], i, all);
        if (g_group == i) sel = h;
    }
    for (i = 1; i < g_nsrc; i++) {
        char label[90];
        if (!g_src[i].loaded) continue;
        wsprintf(label, "From %s", g_src[i].name);
        h = AddGroup(label, G_SOURCE(i), MY_TVI_ROOT);
        if (g_group == G_SOURCE(i)) sel = h;
    }
    SendMessage(g_tree, MY_TVM_EXPAND, MY_TVE_EXPAND, (LPARAM)all);
    SendMessage(g_tree, MY_TVM_SELECTITEM, MY_TVGN_CARET, (LPARAM)(sel ? sel : first));
    g_filling = 0;
}

static void SetCell(int row, int col, const char *text)
{
    MY_LVITEM it;
    memset(&it, 0, sizeof(it));
    it.iSubItem = col;
    it.pszText = (char *)text;
    SendMessage(g_list, MY_LVM_SETITEMTEXTA, row, (LPARAM)&it);
}

static void SetCheck(int row, int on)
{
    MY_LVITEM it;
    memset(&it, 0, sizeof(it));
    it.stateMask = MY_LVIS_STATEIMAGEMASK;
    it.state = (on ? 2 : 1) << 12;
    SendMessage(g_list, MY_LVM_SETITEMSTATE, row, (LPARAM)&it);
}

static PKG *RowPkg(int row)
{
    MY_LVITEM it;
    memset(&it, 0, sizeof(it));
    it.mask = MY_LVIF_PARAM;
    it.iItem = row;
    if (row < 0 || !SendMessage(g_list, MY_LVM_GETITEMA, 0, (LPARAM)&it)) return NULL;
    return &g_cat.pkg[it.lParam];
}

static PKG *SelectedPkg(void)
{
    return RowPkg((int)SendMessage(g_list, MY_LVM_GETNEXTITEM, (WPARAM)-1, MY_LVNI_SELECTED));
}

static void UpdateButtons(void)
{
    int i, marked = 0;
    char text[40];
    PKG *p = SelectedPkg();
    for (i = 0; i < g_cat.count; i++) if (g_cat.pkg[i].marked) marked++;
    if (marked) wsprintf(text, "&Install %d Marked", marked);
    else lstrcpy(text, "&Install");
    SetWindowText(g_bInstall, text);
    EnableWindow(g_bInstall, marked || (p && p->status != ST_YES));
    EnableWindow(g_bRemove, p && (p->status == ST_YES || p->status == ST_UPDATE));
}

static void StatusCount(int shown)
{
    char text[80];
    wsprintf(text, "%d of %d packages", shown, g_cat.count);
    SendMessage(g_status, MY_SB_SETTEXTA, 1, (LPARAM)text);
}

/* Where a package stands, for sorting by the Status column. */
static int StatusRank(PKG *p)
{
    if (p->status == ST_UPDATE) return 0;
    if (p->status == ST_YES) return 1;
    if (p->reqMissing) return 3;
    return 2;
}

static int CALLBACK CompareRows(LPARAM a, LPARAM b, LPARAM col)
{
    PKG *p = &g_cat.pkg[a], *q = &g_cat.pkg[b];
    int r = 0;
    if (col == 1) r = CompareVersions(p->f[F_VERSION] ? p->f[F_VERSION] : "", q->f[F_VERSION] ? q->f[F_VERSION] : "");
    else if (col == 2) r = p->bytes < q->bytes ? -1 : p->bytes > q->bytes;
    else if (col == 3) r = StatusRank(p) - StatusRank(q);
    if (!r) r = lstrcmpi(p->f[F_NAME], q->f[F_NAME]);
    if (!r) r = (int)(a - b);
    return g_sortDesc ? -r : r;
}

/* Sorts the list by the column last clicked; the catalog's order until then. */
static void SortList(void)
{
    if (g_sortCol >= 0) SendMessage(g_list, MY_LVM_SORTITEMS, (WPARAM)g_sortCol, (LPARAM)CompareRows);
}

static void FillList(void)
{
    char search[100], text[80];
    PKG *keep = SelectedPkg();
    MY_LVITEM it;
    int i, row = 0, selRow = -1;
    GetWindowText(g_search, search, sizeof(search));
    g_filling = 1;
    SendMessage(g_list, MY_LVM_DELETEALLITEMS, 0, 0);
    for (i = 0; i < g_cat.count; i++) {
        PKG *p = &g_cat.pkg[i];
        if (!InGroup(p, g_group) || !Matches(p, search)) continue;
        memset(&it, 0, sizeof(it));
        it.mask = MY_LVIF_TEXT | MY_LVIF_PARAM;
        it.iItem = row;
        it.pszText = p->f[F_NAME];
        it.lParam = i;
        SendMessage(g_list, MY_LVM_INSERTITEMA, 0, (LPARAM)&it);
        SetCell(row, 1, p->f[F_VERSION]);
        wsprintf(text, "%lu KB", (p->bytes + 1023) / 1024);
        SetCell(row, 2, text);
        if (p->status == ST_YES) lstrcpy(text, "Installed");
        else if (p->status == ST_UPDATE) wsprintf(text, "Update (%s installed)", p->have);
        else if (p->reqMissing) lstrcpy(text, "Needs a component");
        else lstrcpy(text, "Not installed");
        SetCell(row, 3, text);
        SetCheck(row, p->marked);
        if (p == keep) selRow = row;
        row++;
    }
    SortList();
    if (row) {
        for (i = 0; keep && i < row; i++) if (RowPkg(i) == keep) selRow = i;
        if (selRow < 0) selRow = 0;
        memset(&it, 0, sizeof(it));
        it.stateMask = MY_LVIS_SELECTED | MY_LVIS_FOCUSED;
        it.state = MY_LVIS_SELECTED | MY_LVIS_FOCUSED;
        SendMessage(g_list, MY_LVM_SETITEMSTATE, selRow, (LPARAM)&it);
        SendMessage(g_list, MY_LVM_ENSUREVISIBLE, selRow, FALSE);
    }
    g_filling = 0;
    StatusCount(row);
    ShowDetails(g_details, SelectedPkg());
    UpdateButtons();
}

/* A tick in the list marks a package; marking one also marks what it depends on. */
static void MarkChanged(int row)
{
    PKG *p = RowPkg(row), *dep;
    int on, i, n;
    if (!p) return;
    on = ((UINT)SendMessage(g_list, MY_LVM_GETITEMSTATE, row, MY_LVIS_STATEIMAGEMASK) >> 12) == 2;
    if (on == p->marked) return;
    p->marked = on;
    if (on && (dep = MissingPackage(p)) != NULL && !dep->marked)
        PostMessage(g_main, WM_OFFER, 0, (LPARAM)p);          /* ask once the tick is drawn */
    if (on && p->f[F_DEPENDS] && (dep = FindPkg(&g_cat, p->f[F_DEPENDS])) != NULL && !dep->marked && dep->status == ST_NO) {
        dep->marked = 1;
        n = (int)SendMessage(g_list, MY_LVM_GETITEMCOUNT, 0, 0);
        g_filling = 1;
        for (i = 0; i < n; i++) if (RowPkg(i) == dep) SetCheck(i, 1);
        g_filling = 0;
    }
    UpdateButtons();
}

static void Layout(void)
{
    RECT rc, sr;
    int w, h, listH, x;
    GetClientRect(g_main, &rc);
    SendMessage(g_status, WM_SIZE, 0, 0);
    GetWindowRect(g_status, &sr);
    w = rc.right;
    h = rc.bottom - (sr.bottom - sr.top);
    MoveWindow(g_bUpdate, 6, 5, 104, 23, TRUE);
    MoveWindow(g_bInstall, 116, 5, 120, 23, TRUE);
    MoveWindow(g_bRemove, 242, 5, 80, 23, TRUE);
    x = w - 6 - 190;
    if (x < 380) x = 380;
    MoveWindow(g_searchLabel, x - 48, 9, 44, 16, TRUE);
    MoveWindow(g_search, x, 5, 190, 22, TRUE);
    MoveWindow(g_tree, 4, BAR_H + 2, TREE_W, h - BAR_H - 6, TRUE);
    listH = (h - BAR_H - 6) * 11 / 20;
    MoveWindow(g_list, TREE_W + 8, BAR_H + 2, w - TREE_W - 12, listH, TRUE);
    MoveWindow(g_details, TREE_W + 8, BAR_H + 6 + listH, w - TREE_W - 12, h - BAR_H - 10 - listH, TRUE);
    {
        int parts[3];
        parts[0] = w - 300; parts[1] = w - 170; parts[2] = -1;
        if (parts[0] < 100) parts[0] = 100;
        SendMessage(g_status, MY_SB_SETPARTS, 3, (LPARAM)parts);
    }
}

static HWND Make(const char *cls, const char *text, DWORD style, DWORD exStyle, int id)
{
    HWND h = CreateWindowEx(exStyle, cls, text, WS_CHILD | WS_VISIBLE | style, 0, 0, 10, 10, g_main, (HMENU)id, g_inst, NULL);
    SendMessage(h, WM_SETFONT, (WPARAM)g_font, 0);
    return h;
}

static void AddColumn(int i, const char *title, int width, int right)
{
    MY_LVCOLUMN c;
    memset(&c, 0, sizeof(c));
    c.mask = MY_LVCF_TEXT | MY_LVCF_WIDTH | MY_LVCF_FMT;
    c.fmt = right ? MY_LVCFMT_RIGHT : 0;
    c.cx = width;
    c.pszText = (char *)title;
    SendMessage(g_list, MY_LVM_INSERTCOLUMNA, i, (LPARAM)&c);
}

static void LoadAndCheck(void)
{
    char text[300];
    int r;
    LoadAllCatalogs(g_catalogState, sizeof(g_catalogState), &r);
    SendMessage(g_status, MY_SB_SETTEXTA, 0, (LPARAM)g_catalogState);
    SendMessage(g_status, MY_SB_SETTEXTA, 2, (LPARAM)"get.backportlabs.com");
    if (r != SIG_OK && r != SIG_NO_FILE && !g_testMode) {
        wsprintf(text, "The catalog was not loaded: %s.\n\nBeacon 98 only uses a catalog signed by Backport Labs.", SigText(r));
        MessageBox(g_main, text, APP_NAME, MB_OK | MB_ICONWARNING);
    }
}

static void ShowReadMe(void)
{
    char path[MAX_PATH], cmd[MAX_PATH + 20];
    wsprintf(path, "%sREADME.TXT", g_dir);
    if (GetFileAttributes(path) == (DWORD)-1) {
        MessageBox(g_main, "README.TXT is not in the folder of Beacon 98. It is also at\nhttps://github.com/Backport-Labs/beacon98",
                   APP_NAME, MB_OK | MB_ICONINFORMATION);
        return;
    }
    wsprintf(cmd, "notepad.exe \"%s\"", path);
    WinExec(cmd, SW_SHOWNORMAL);
}

static void ShowAbout(void)
{
    char text[1200];
    wsprintf(text,
        APP_NAME " " APP_VERSION "\n"
        "A package manager for Windows 95, 98 and Me.\n\n"
        "Copyright (C) 2026 Backport Labs\n"
        "Free software under the MIT License (LICENSE.TXT).\n"
        "https://github.com/Backport-Labs/beacon98\n\n"
        "Catalog key: %s\n"
        "Custom sources: %d\n\n"
        "Beacon 98 includes:\n"
        "  BearSSL 0.6, by Thomas Pornin (MIT License)\n"
        "  TweetNaCl, by Bernstein, van Gastel, Janssen, Lange,\n"
        "    Schwabe and Smetsers (public domain)\n"
        "  miniz 3.1.2, by Rich Geldreich and others (MIT License)\n"
        "  Root certificates from Mozilla, as published by curl\n"
        "    (Mozilla Public License 2.0)",
        g_keyId, g_nsrc - 1);
    MessageBox(g_main, text, "About " APP_NAME, MB_OK | MB_ICONINFORMATION);
}

static void Refresh(void);

static void EditSources(void)
{
    if (!SourcesDialog(g_main)) return;
    Refresh();
    if (MessageBox(g_main, "The sources were saved. Update the catalog now, to fetch the catalogs of new or changed sources?",
                   APP_NAME, MB_YESNO | MB_ICONQUESTION) == IDYES) {
        UpdateCatalog(g_main);
        Refresh();
    }
}

/* Reads the catalog and the state of the computer again, after a change. */
static void Refresh(void)
{
    LoadAndCheck();
    FillTree();
    FillList();
}

static LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_CREATE:
        g_main = hwnd;
        g_font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        g_bUpdate = Make("BUTTON", "&Update Catalog", BS_PUSHBUTTON | WS_TABSTOP, 0, ID_UPDATE);
        g_bInstall = Make("BUTTON", "&Install", BS_PUSHBUTTON | WS_TABSTOP, 0, ID_INSTALL);
        g_bRemove = Make("BUTTON", "&Remove", BS_PUSHBUTTON | WS_TABSTOP, 0, ID_REMOVE);
        g_searchLabel = Make("STATIC", "S&earch:", SS_RIGHT, 0, 0);
        g_search = Make("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP, WS_EX_CLIENTEDGE, ID_SEARCH);
        SendMessage(g_search, EM_LIMITTEXT, 90, 0);
        g_tree = Make(MY_WC_TREEVIEW, "", MY_TVS_HASBUTTONS | MY_TVS_HASLINES | MY_TVS_LINESATROOT | MY_TVS_SHOWSELALWAYS | WS_TABSTOP,
                      WS_EX_CLIENTEDGE, ID_TREE);
        g_list = Make(MY_WC_LISTVIEW, "", MY_LVS_REPORT | MY_LVS_SINGLESEL | MY_LVS_SHOWSELALWAYS | WS_TABSTOP, WS_EX_CLIENTEDGE, ID_LIST);
        SendMessage(g_list, MY_LVM_SETEXTENDEDLISTVIEWSTYLE, 0, MY_LVS_EX_CHECKBOXES | MY_LVS_EX_FULLROWSELECT);
        AddColumn(0, "Name", 200, 0);
        AddColumn(1, "Version", 80, 0);
        AddColumn(2, "Download", 76, 1);
        AddColumn(3, "Status", 150, 0);
        g_details = Make(CLASS_DETAILS, "", WS_VSCROLL, WS_EX_CLIENTEDGE, 0);
        g_status = Make(MY_STATUSCLASS, "", MY_SBARS_SIZEGRIP, 0, ID_STATUS);
        Layout();
        LoadAndCheck();
        FillTree();
        FillList();
        SetFocus(g_search);
        /* The first time, there is no catalog yet: fetch it once the window shows. */
        if (!g_src[0].loaded && !g_testMode) PostMessage(hwnd, WM_FIRST_RUN, 0, 0);
        return 0;
    case WM_SIZE:
        if (g_status) Layout();
        return 0;
    case WM_GETMINMAXINFO:
        ((MINMAXINFO *)lp)->ptMinTrackSize.x = 600;
        ((MINMAXINFO *)lp)->ptMinTrackSize.y = 400;
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_EXIT:
            DestroyWindow(hwnd);
            return 0;
        case ID_SOURCES:
            EditSources();
            return 0;
        case ID_README:
            ShowReadMe();
            return 0;
        case ID_ABOUT:
            ShowAbout();
            return 0;
        case ID_SEARCH:
            if (HIWORD(wp) == EN_CHANGE) FillList();
            return 0;
        case ID_UPDATE:
            UpdateCatalog(hwnd);
            Refresh();
            return 0;
        case ID_INSTALL: {
            PKG *chosen[64], *sel = SelectedPkg();
            int i, n = 0;
            for (i = 0; i < g_cat.count && n < 64; i++) if (g_cat.pkg[i].marked) chosen[n++] = &g_cat.pkg[i];
            if (!n && sel) chosen[n++] = sel;
            if (n && InstallPackages(hwnd, chosen, n)) Refresh();
            else FillList();
            return 0;
        }
        case ID_REMOVE: {
            PKG *sel = SelectedPkg();
            if (sel && RemovePackage(hwnd, sel)) Refresh();
            return 0;
        }
        }
        break;
    case WM_FIRST_RUN:
        if (UpdateCatalog(hwnd)) Refresh();
        return 0;
    case WM_OFFER: {
        PKG *p = (PKG *)lp, *need = MissingPackage(p);
        int i, n;
        if (!need || need->marked || !p->marked) return 0;
        if (OfferPackage(hwnd, p, need)) {
            need->marked = 1;
            n = (int)SendMessage(g_list, MY_LVM_GETITEMCOUNT, 0, 0);
            g_filling = 1;
            for (i = 0; i < n; i++) if (RowPkg(i) == need) SetCheck(i, 1);
            g_filling = 0;
            UpdateButtons();
        }
        return 0;
    }
    case WM_NOTIFY: {
        NMHDR *n = (NMHDR *)lp;
        if (g_filling) return 0;
        if (n->idFrom == ID_TREE && n->code == (UINT)MY_TVN_SELCHANGEDA) {
            g_group = (int)((MY_NMTREEVIEW *)lp)->itemNew.lParam;
            FillList();
        } else if (n->idFrom == ID_LIST && n->code == (UINT)MY_LVN_ITEMCHANGED) {
            MY_NMLISTVIEW *lv = (MY_NMLISTVIEW *)lp;
            if ((lv->uNewState ^ lv->uOldState) & MY_LVIS_STATEIMAGEMASK) MarkChanged(lv->iItem);
            if ((lv->uNewState ^ lv->uOldState) & MY_LVIS_SELECTED) {
                ShowDetails(g_details, SelectedPkg());
                UpdateButtons();
            }
        } else if (n->idFrom == ID_LIST && n->code == (UINT)MY_LVN_COLUMNCLICK) {
            int col = ((MY_NMLISTVIEW *)lp)->iSubItem;
            g_sortDesc = col == g_sortCol ? !g_sortDesc : 0;
            g_sortCol = col;
            SortList();
            SendMessage(g_list, MY_LVM_ENSUREVISIBLE, SendMessage(g_list, MY_LVM_GETNEXTITEM, (WPARAM)-1, MY_LVNI_SELECTED), FALSE);
        }
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

static HMENU MakeMenu(void)
{
    HMENU bar = CreateMenu(), file = CreatePopupMenu(), set = CreatePopupMenu(), help = CreatePopupMenu();
    AppendMenu(file, MF_STRING, ID_UPDATE, "&Update Catalog");
    AppendMenu(file, MF_SEPARATOR, 0, NULL);
    AppendMenu(file, MF_STRING, ID_EXIT, "E&xit");
    AppendMenu(set, MF_STRING, ID_SOURCES, "&Sources...");
    AppendMenu(help, MF_STRING, ID_README, "&Read Me\tF1");
    AppendMenu(help, MF_SEPARATOR, 0, NULL);
    AppendMenu(help, MF_STRING, ID_ABOUT, "&About " APP_NAME);
    AppendMenu(bar, MF_POPUP, (UINT)file, "&File");
    AppendMenu(bar, MF_POPUP, (UINT)set, "&Settings");
    AppendMenu(bar, MF_POPUP, (UINT)help, "&Help");
    return bar;
}

static HWND MakeMain(int x, int y, DWORD visible)
{
    WNDCLASS wc;
    InitCommonControls();
    RegisterDetails();
    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = MainProc;
    wc.hInstance = g_inst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = CLASS_MAIN;
    RegisterClass(&wc);
    return CreateWindow(CLASS_MAIN, APP_NAME, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | visible,
                        x, y, 760, 560, NULL, MakeMenu(), g_inst, NULL);
}

/* Test mode: the window off the screen, with a search typed and a row selected. */
HWND OpenForShot(const char *search, int row)
{
    MY_LVITEM it;
    HWND hwnd = MakeMain(-4000, -3000, WS_VISIBLE);
    if (!hwnd) return NULL;
    if (search && search[0]) SetWindowText(g_search, search);
    if (row >= 0) {
        memset(&it, 0, sizeof(it));
        it.stateMask = MY_LVIS_SELECTED | MY_LVIS_FOCUSED;
        it.state = MY_LVIS_SELECTED | MY_LVIS_FOCUSED;
        SendMessage(g_list, MY_LVM_SETITEMSTATE, row, (LPARAM)&it);
    }
    return hwnd;
}

/* Test mode: a click on a column heading, through the same notice. */
void SortForShot(int col)
{
    MY_NMLISTVIEW lv;
    memset(&lv, 0, sizeof(lv));
    lv.hdr.hwndFrom = g_list;
    lv.hdr.idFrom = ID_LIST;
    lv.hdr.code = (UINT)MY_LVN_COLUMNCLICK;
    lv.iItem = -1;
    lv.iSubItem = col;
    SendMessage(g_main, WM_NOTIFY, ID_LIST, (LPARAM)&lv);
}

int RunWindow(int show)
{
    MSG m;
    ACCEL keys[1];
    HACCEL acc;
    int i;
    HWND hwnd = MakeMain(CW_USEDEFAULT, CW_USEDEFAULT, 0);
    if (!hwnd) return 1;
    keys[0].fVirt = FVIRTKEY;
    keys[0].key = VK_F1;
    keys[0].cmd = ID_README;
    acc = CreateAcceleratorTable(keys, 1);
    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);
    while (GetMessage(&m, NULL, 0, 0) > 0) {
        if (acc && TranslateAccelerator(hwnd, acc, &m)) continue;
        if (IsDialogMessage(hwnd, &m)) continue;
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    if (acc) DestroyAcceleratorTable(acc);
    FreeCatalog(&g_cat);
    for (i = 0; i < g_nsrc; i++) FreeCatalog(&g_src[i].cat);
    CloseNet();
    return (int)m.wParam;
}
