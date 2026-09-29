/* task.c - long work (downloading, checking, installing) runs in a second
 * thread, while a window shows what it is doing: one line per step, a
 * progress bar for the current file, and a Cancel button. The main window is
 * disabled until the work is done and the user closes the window.
 */
#include "beacon.h"

#define CLASS_TASK "Beacon98Task"
#define TM_LOG      (WM_APP + 21)
#define TM_PROGRESS (WM_APP + 22)
#define TM_DONE     (WM_APP + 23)
#define ID_BUTTON   201
#define TASK_W 460
#define TASK_H 300

typedef struct {
    TASKFN fn;
    void *ctx;
    int result;
    int finished;          /* the thread has ended */
    int closed;            /* the window has been closed */
    int autoClose;
    HWND wnd, log, bar, button;
} TASK;

static TASK *g_task;       /* one task at a time */
static volatile int g_cancel;

volatile int *TaskCancelFlag(void) { return &g_cancel; }
int TaskCancelled(void) { return g_cancel; }

/* Adds a line to the window. Called from the work thread. */
void TaskLog(const char *fmt, ...)
{
    char *s = (char *)malloc(600);
    va_list ap;
    if (!s || !g_task) { free(s); return; }
    va_start(ap, fmt);
    wvsprintf(s, fmt, ap);
    va_end(ap);
    PostMessage(g_task->wnd, TM_LOG, 0, (LPARAM)s);
}

/* Sets the progress bar, 0 to 100; -1 empties it. Called from the work thread. */
void TaskProgress(int percent)
{
    if (g_task) PostMessage(g_task->wnd, TM_PROGRESS, (WPARAM)percent, 0);
}

static DWORD WINAPI TaskThread(void *arg)
{
    TASK *t = (TASK *)arg;
    int r;
    CoInitialize(NULL);
    r = t->fn(t->ctx);
    CoUninitialize();
    PostMessage(t->wnd, TM_DONE, (WPARAM)r, 0);
    return 0;
}

static void AppendLog(HWND log, const char *s)
{
    int n = GetWindowTextLength(log);
    SendMessage(log, EM_SETSEL, n, n);
    if (n) SendMessage(log, EM_REPLACESEL, 0, (LPARAM)"\r\n");
    n = GetWindowTextLength(log);
    SendMessage(log, EM_SETSEL, n, n);
    SendMessage(log, EM_REPLACESEL, 0, (LPARAM)s);
    SendMessage(log, EM_SCROLLCARET, 0, 0);
}

static LRESULT CALLBACK TaskProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    TASK *t = g_task;
    switch (msg) {
    case TM_LOG:
        if (t) AppendLog(t->log, (char *)lp);
        free((void *)lp);
        return 0;
    case TM_PROGRESS:
        if (t) SendMessage(t->bar, MY_PBM_SETPOS, (int)wp < 0 ? 0 : wp, 0);
        return 0;
    case TM_DONE:
        if (!t) return 0;
        t->finished = 1;
        t->result = (int)wp;
        SetWindowText(t->button, "Close");
        SendMessage(t->bar, MY_PBM_SETPOS, t->result ? 100 : 0, 0);
        if (t->autoClose && t->result) DestroyWindow(hwnd);
        return 0;
    case WM_COMMAND:
        if (LOWORD(wp) == ID_BUTTON || LOWORD(wp) == IDCANCEL) {
            if (t && t->finished) DestroyWindow(hwnd);
            else if (t && !g_cancel) {
                g_cancel = 1;
                EnableWindow(t->button, FALSE);
                AppendLog(t->log, "Cancelling. A setup program that is already running is allowed to finish.");
            }
        }
        return 0;
    case WM_CLOSE:
        SendMessage(hwnd, WM_COMMAND, ID_BUTTON, 0);
        return 0;
    case WM_DESTROY:
        if (t) t->closed = 1;
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

/* Runs fn(ctx) in a second thread with a progress window over owner. fn
 * returns 1 on success. With autoClose, a successful task closes its window
 * by itself. Returns what fn returned. */
int RunTask(HWND owner, const char *title, TASKFN fn, void *ctx, int autoClose)
{
    static int registered;
    TASK t;
    WNDCLASS wc;
    RECT r;
    MSG m;
    HANDLE thread;
    DWORD id;
    HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    int x, y, w, h;

    if (g_task) return 0;
    if (!registered) {
        memset(&wc, 0, sizeof(wc));
        wc.lpfnWndProc = TaskProc;
        wc.hInstance = g_inst;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszClassName = CLASS_TASK;
        RegisterClass(&wc);
        registered = 1;
    }
    memset(&t, 0, sizeof(t));
    t.fn = fn;
    t.ctx = ctx;
    t.autoClose = autoClose;
    g_task = &t;
    g_cancel = 0;

    SetRect(&r, 0, 0, TASK_W, TASK_H);
    AdjustWindowRect(&r, WS_CAPTION | WS_SYSMENU, FALSE);
    w = r.right - r.left;
    h = r.bottom - r.top;
    GetWindowRect(owner, &r);
    x = r.left + (r.right - r.left - w) / 2;
    y = r.top + (r.bottom - r.top - h) / 2;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    t.wnd = CreateWindowEx(WS_EX_DLGMODALFRAME, CLASS_TASK, title, WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
                           x, y, w, h, owner, NULL, g_inst, NULL);
    t.log = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
                           12, 12, TASK_W - 24, TASK_H - 88, t.wnd, NULL, g_inst, NULL);
    t.bar = CreateWindowEx(0, MY_PROGRESSCLASS, "", WS_CHILD | WS_VISIBLE, 12, TASK_H - 66, TASK_W - 24, 18, t.wnd, NULL, g_inst, NULL);
    t.button = CreateWindowEx(0, "BUTTON", "Cancel", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                              TASK_W - 12 - 88, TASK_H - 36, 88, 24, t.wnd, (HMENU)ID_BUTTON, g_inst, NULL);
    SendMessage(t.log, WM_SETFONT, (WPARAM)font, 0);
    SendMessage(t.button, WM_SETFONT, (WPARAM)font, 0);
    SendMessage(t.log, EM_LIMITTEXT, 60000, 0);
    SendMessage(t.bar, MY_PBM_SETRANGE, 0, MAKELPARAM(0, 100));
    EnableWindow(owner, FALSE);

    thread = CreateThread(NULL, 0, TaskThread, &t, 0, &id);
    if (!thread) {
        AppendLog(t.log, "The work could not be started.");
        t.finished = 1;
        SetWindowText(t.button, "Close");
    }
    while (!t.closed && GetMessage(&m, NULL, 0, 0) > 0) {
        if (IsDialogMessage(t.wnd, &m)) continue;
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    if (thread) {
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }
    /* Messages the thread posted after the window closed carry strings to free. */
    while (PeekMessage(&m, NULL, TM_LOG, TM_LOG, PM_REMOVE)) free((void *)m.lParam);
    EnableWindow(owner, TRUE);
    SetForegroundWindow(owner);
    g_task = NULL;
    return t.result;
}
