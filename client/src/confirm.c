/* confirm.c - the window that asks before installing: a heading (the known
 * security problems, when there are any), the license in a scrolling box,
 * and the buttons to agree or cancel.
 */
#include "beacon.h"

#define CLASS_CONFIRM "Beacon98Confirm"
#define CONF_W 480
#define CONF_H 360
#define ID_YES 301
#define ID_NO  302

static int g_answer, g_done;

static LRESULT CALLBACK ConfirmProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wp) == ID_YES || LOWORD(wp) == ID_NO || LOWORD(wp) == IDCANCEL) {
            g_answer = LOWORD(wp) == ID_YES;
            DestroyWindow(hwnd);
        }
        return 0;
    case WM_CLOSE:
        g_answer = 0;
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        g_done = 1;
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

/* Converts single \n to \r\n for an edit control. */
static char *Crlf(const char *s)
{
    int n = 0, i, o = 0;
    char *out;
    for (i = 0; s[i]; i++) if (s[i] == '\n' && (i == 0 || s[i - 1] != '\r')) n++;
    out = (char *)malloc(lstrlen(s) + n + 1);
    if (!out) return NULL;
    for (i = 0; s[i]; i++) {
        if (s[i] == '\n' && (i == 0 || s[i - 1] != '\r')) out[o++] = '\r';
        out[o++] = s[i];
    }
    out[o] = 0;
    return out;
}

/* Shows head (may be empty) above body in a scrolling box. Returns 1 when
 * the user presses the yes button. */
int ConfirmBox(HWND owner, const char *title, const char *head, const char *body, const char *yes, const char *no)
{
    static int registered;
    WNDCLASS wc;
    RECT r;
    MSG m;
    HWND wnd, h, e, b1, b2;
    HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    int x, y, w, hh, headH = 0;
    char *text;

    if (!registered) {
        memset(&wc, 0, sizeof(wc));
        wc.lpfnWndProc = ConfirmProc;
        wc.hInstance = g_inst;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszClassName = CLASS_CONFIRM;
        RegisterClass(&wc);
        registered = 1;
    }
    SetRect(&r, 0, 0, CONF_W, CONF_H);
    AdjustWindowRect(&r, WS_CAPTION | WS_SYSMENU, FALSE);
    w = r.right - r.left;
    hh = r.bottom - r.top;
    GetWindowRect(owner, &r);
    x = r.left + (r.right - r.left - w) / 2;
    y = r.top + (r.bottom - r.top - hh) / 2;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    wnd = CreateWindowEx(WS_EX_DLGMODALFRAME, CLASS_CONFIRM, title, WS_CAPTION | WS_SYSMENU,
                         x, y, w, hh, owner, NULL, g_inst, NULL);
    if (!wnd) return 0;
    if (head && head[0]) {
        HDC dc = GetDC(wnd);
        RECT tr;
        SelectObject(dc, font);
        SetRect(&tr, 0, 0, CONF_W - 24, 0);
        DrawText(dc, head, -1, &tr, DT_CALCRECT | DT_WORDBREAK | DT_NOPREFIX);
        ReleaseDC(wnd, dc);
        headH = tr.bottom + 10;
        if (headH > 150) headH = 150;
        h = CreateWindowEx(0, "STATIC", head, WS_CHILD | WS_VISIBLE | SS_NOPREFIX, 12, 12, CONF_W - 24, headH - 8, wnd, NULL, g_inst, NULL);
        SendMessage(h, WM_SETFONT, (WPARAM)font, 0);
    }
    text = Crlf(body ? body : "");
    e = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", text ? text : "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP
                       | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL, 12, 12 + headH, CONF_W - 24, CONF_H - 60 - headH, wnd, NULL, g_inst, NULL);
    free(text);
    SendMessage(e, WM_SETFONT, (WPARAM)GetStockObject(ANSI_FIXED_FONT), 0);
    b1 = CreateWindowEx(0, "BUTTON", yes, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                        CONF_W - 12 - 88 - 8 - 88, CONF_H - 36, 88, 24, wnd, (HMENU)ID_YES, g_inst, NULL);
    b2 = CreateWindowEx(0, "BUTTON", no, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                        CONF_W - 12 - 88, CONF_H - 36, 88, 24, wnd, (HMENU)ID_NO, g_inst, NULL);
    SendMessage(b1, WM_SETFONT, (WPARAM)font, 0);
    SendMessage(b2, WM_SETFONT, (WPARAM)font, 0);
    ShowWindow(wnd, SW_SHOW);
    SetFocus(b2);
    EnableWindow(owner, FALSE);
    g_done = 0;
    g_answer = 0;
    while (!g_done && GetMessage(&m, NULL, 0, 0) > 0) {
        if (IsDialogMessage(wnd, &m)) continue;
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    EnableWindow(owner, TRUE);
    SetForegroundWindow(owner);
    return g_answer;
}
