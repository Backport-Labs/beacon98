/* details.c - the pane below the list that describes the selected package:
 * what it is, what it needs, its known security problems, where it comes
 * from and how it installs. The pane scrolls when the text is longer than it.
 */
#include "beacon.h"

#define MARGIN   8
#define LABEL_W  104

typedef struct {
    PKG *pkg;
    int top;          /* scrolled distance, in pixels */
    int height;       /* height of everything, in pixels */
} DETAILS;

static HFONT g_fontText, g_fontBold, g_fontTitle;

static void Fonts(void)
{
    LOGFONT lf;
    if (g_fontText) return;
    g_fontText = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    GetObject(g_fontText, sizeof(lf), &lf);
    lf.lfWeight = FW_BOLD;
    g_fontBold = CreateFontIndirect(&lf);
    lf.lfHeight = lf.lfHeight * 4 / 3;
    g_fontTitle = CreateFontIndirect(&lf);
}

/* Draws text in the given width at y (or only measures it) and returns its height. */
static int Text(HDC dc, int draw, int x, int y, int w, const char *s, HFONT font, COLORREF color)
{
    RECT r;
    SetRect(&r, x, y, x + w, y);
    SelectObject(dc, font);
    DrawText(dc, s, -1, &r, DT_CALCRECT | DT_WORDBREAK | DT_NOPREFIX);
    if (draw) {
        r.right = x + w;
        SetTextColor(dc, color);
        DrawText(dc, s, -1, &r, DT_WORDBREAK | DT_NOPREFIX);
    }
    return r.bottom - r.top;
}

/* A coloured box with a bold heading and a text. Returns its height. */
static int Box(HDC dc, int draw, int x, int y, int w, COLORREF fill, COLORREF edge,
               const char *mark, const char *head, const char *body)
{
    int h = 5, inner = w - 34;
    int hh = Text(dc, 0, 0, 0, inner, head, g_fontBold, 0);
    int bh = body && body[0] ? Text(dc, 0, 0, 0, inner, body, g_fontText, 0) : 0;
    h += hh + bh + 5;
    if (draw) {
        RECT r;
        HBRUSH b = CreateSolidBrush(fill), e = CreateSolidBrush(edge);
        SetRect(&r, x, y, x + w, y + h);
        FillRect(dc, &r, b);
        FrameRect(dc, &r, e);
        DeleteObject(b);
        DeleteObject(e);
        Text(dc, 1, x + 8, y + 5, 18, mark, g_fontBold, edge);
        Text(dc, 1, x + 26, y + 5, inner, head, g_fontBold, RGB(0, 0, 0));
        if (bh) Text(dc, 1, x + 26, y + 5 + hh, inner, body, g_fontText, RGB(0, 0, 0));
    }
    return h;
}

/* A label and its value, side by side. Returns the height. */
static int Fact(HDC dc, int draw, int x, int y, int w, const char *label, const char *value)
{
    int h1 = Text(dc, draw, x, y, LABEL_W - 8, label, g_fontText, RGB(96, 96, 96));
    int h2 = Text(dc, draw, x + LABEL_W, y, w - LABEL_W, value, g_fontText, RGB(0, 0, 0));
    return (h1 > h2 ? h1 : h2) + 1;
}

/* Catalog text flows: a single line break is a space, an empty line starts a
 * new paragraph. */
static void Flow(const char *in, char *out, int outLen)
{
    int o = 0;
    for (; *in && o < outLen - 2; in++) {
        if (*in == '\n' && in[1] == '\n') { out[o++] = '\r'; out[o++] = '\n'; in++; if (o < outLen - 2) { out[o++] = '\r'; out[o++] = '\n'; } }
        else if (*in == '\n') out[o++] = ' ';
        else out[o++] = *in;
    }
    out[o] = 0;
}

static void InstallsWith(const char *install, char *out)
{
    if (strncmp(install, "inno", 4) == 0) lstrcpy(out, "Setup program (Inno Setup)");
    else if (strncmp(install, "nsis", 4) == 0) lstrcpy(out, "Setup program (NSIS)");
    else if (strncmp(install, "msi", 3) == 0) lstrcpy(out, "Windows Installer package");
    else if (strncmp(install, "exe", 3) == 0) lstrcpy(out, "Setup program");
    else if (strncmp(install, "unzip", 5) == 0) lstrcpy(out, "Unpacked by Beacon 98");
    else if (strncmp(install, "copy", 4) == 0) lstrcpy(out, "Copied by Beacon 98");
    else lstrcpy(out, install);
}

/* The servers of the first Download line, in the order they are tried:
 * "downloads.sourceforge.net, then get.backportlabs.com". */
static void Servers(const char *download, char *out, int outLen)
{
    char host[100];
    const char *p = download;
    int word = 0, i, o = 0;
    out[0] = 0;
    while (*p && *p != '\n') {
        while (*p == ' ') p++;
        if (!*p || *p == '\n') break;
        if (word != 1 && word != 2) {
            if (IsUrl(p)) {
                const char *h = strstr(p, "://") + 3;
                for (i = 0; h[i] && h[i] != '/' && h[i] != ' ' && i < (int)sizeof(host) - 1; i++) host[i] = h[i];
                host[i] = 0;
            } else lstrcpy(host, CATALOG_HOST);
            if (!strstr(out, host) && o + lstrlen(host) + 8 < outLen) {
                if (o) { lstrcpy(out + o, ", then "); o += 7; }
                lstrcpy(out + o, host);
                o += lstrlen(host);
            }
        }
        while (*p && *p != ' ' && *p != '\n') p++;
        word++;
    }
}

static int Layout(HDC dc, int draw, DETAILS *d, int width)
{
    PKG *p = d->pkg;
    char buf[1200], what[400], line[600];
    int x = MARGIN, y = MARGIN - d->top, w = width - 2 * MARGIN, j, met;
    const char *r;

    if (w < 120) w = 120;
    wsprintf(buf, "%s %s", p->f[F_NAME], p->f[F_VERSION]);
    y += Text(dc, draw, x, y, w, buf, g_fontTitle, RGB(0, 0, 0));
    y += Text(dc, draw, x, y, w, p->f[F_SUMMARY], g_fontText, RGB(0, 0, 0)) + 6;
    if (p->f[F_DESCRIPTION]) {
        Flow(p->f[F_DESCRIPTION], buf, sizeof(buf));
        y += Text(dc, draw, x, y, w, buf, g_fontText, RGB(0, 0, 0)) + 6;
    }

    for (r = p->f[F_REQUIRES]; r && *r; ) {
        for (j = 0; r[j] && r[j] != '\n' && j < (int)sizeof(line) - 1; j++) line[j] = r[j];
        line[j] = 0;
        met = RequirementMet(line, what, sizeof(what));
        if (met == 1)
            y += Box(dc, draw, x, y, w, RGB(234, 246, 234), RGB(0, 110, 0), "\x95", "Requirement met", what) + 4;
        else if (met == 0 && strncmp(line, "package ", 8) == 0)
            y += Box(dc, draw, x, y, w, RGB(251, 234, 234), RGB(170, 0, 0), "X",
                     "Needs another package from this catalog. Beacon 98 offers it when you tick this one.", what) + 4;
        else if (met == 0)
            y += Box(dc, draw, x, y, w, RGB(251, 234, 234), RGB(170, 0, 0), "X",
                     "Requirement missing. Beacon 98 cannot supply it.", what) + 4;
        else
            y += Box(dc, draw, x, y, w, RGB(240, 240, 240), RGB(96, 96, 96), "?",
                     "Requirement this version of Beacon cannot check", what) + 4;
        r += j;
        if (*r == '\n') r++;
    }
    if (p->f[F_WARNING]) {
        Flow(p->f[F_WARNING], buf, sizeof(buf));
        y += Box(dc, draw, x, y, w, RGB(255, 251, 224), RGB(150, 120, 0), "!", "Known security problems", buf) + 4;
    }
    if (p->f[F_NOTICE]) {
        Flow(p->f[F_NOTICE], buf, sizeof(buf));
        y += Box(dc, draw, x, y, w, RGB(236, 241, 250), RGB(40, 70, 140), "i", "Note", buf) + 4;
    }
    y += 4;

    Servers(p->f[F_DOWNLOAD], what, sizeof(what));
    if (p->external) wsprintf(buf, "%s. Backport Labs does not distribute it.", what);
    else lstrcpy(buf, what);
    y += Fact(dc, draw, x, y, w, "Downloaded from", buf);
    y += Fact(dc, draw, x, y, w, "License", p->f[F_LICENSE]);
    wsprintf(buf, "Windows %s", p->f[F_SYSTEMS]);
    y += Fact(dc, draw, x, y, w, "Runs on", buf);
    if (p->f[F_DEPENDS]) {
        PKG *dep = FindPkg(&g_cat, p->f[F_DEPENDS]);
        y += Fact(dc, draw, x, y, w, "Also installs", dep ? dep->f[F_NAME] : p->f[F_DEPENDS]);
    }
    InstallsWith(p->f[F_INSTALL], buf);
    y += Fact(dc, draw, x, y, w, "Installs with", buf);
    wsprintf(buf, "%lu KB", (p->bytes + 1023) / 1024);
    y += Fact(dc, draw, x, y, w, "Download", buf);
    if (p->status == ST_YES) wsprintf(buf, "Yes%s%s", p->have[0] ? ", version " : "", p->have);
    else if (p->status == ST_UPDATE) wsprintf(buf, "Version %s. This catalog has %s.", p->have, p->f[F_VERSION]);
    else lstrcpy(buf, "No");
    y += Fact(dc, draw, x, y, w, "Installed", buf);
    if (p->f[F_HOMEPAGE]) y += Fact(dc, draw, x, y, w, "Home page", p->f[F_HOMEPAGE]);
    return y + d->top + MARGIN;
}

static void UpdateScroll(HWND hwnd, DETAILS *d)
{
    SCROLLINFO si;
    RECT rc;
    HDC dc;
    GetClientRect(hwnd, &rc);
    d->height = 0;
    if (d->pkg) {
        dc = GetDC(hwnd);
        d->height = Layout(dc, 0, d, rc.right - GetSystemMetrics(SM_CXVSCROLL));
        ReleaseDC(hwnd, dc);
    }
    if (d->top > d->height - rc.bottom) d->top = d->height - rc.bottom;
    if (d->top < 0) d->top = 0;
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = 0;
    si.nMax = d->height;
    si.nPage = rc.bottom + 1;
    si.nPos = d->top;
    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
}

static LRESULT CALLBACK DetailsProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    DETAILS *d = (DETAILS *)GetWindowLong(hwnd, GWL_USERDATA);
    RECT rc;
    switch (msg) {
    case WM_CREATE:
        d = (DETAILS *)calloc(1, sizeof(DETAILS));
        SetWindowLong(hwnd, GWL_USERDATA, (LONG)d);
        return 0;
    case WM_DESTROY:
        free(d);
        return 0;
    case WM_SIZE:
        UpdateScroll(hwnd, d);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_VSCROLL: {
        int old = d->top, page;
        GetClientRect(hwnd, &rc);
        page = rc.bottom - 20;
        switch (LOWORD(wp)) {
        case SB_LINEUP:   d->top -= 16; break;
        case SB_LINEDOWN: d->top += 16; break;
        case SB_PAGEUP:   d->top -= page; break;
        case SB_PAGEDOWN: d->top += page; break;
        case SB_THUMBTRACK: case SB_THUMBPOSITION: d->top = HIWORD(wp); break;
        }
        UpdateScroll(hwnd, d);
        if (d->top != old) InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
    case WM_ERASEBKGND:
        GetClientRect(hwnd, &rc);
        FillRect((HDC)wp, &rc, GetSysColorBrush(COLOR_WINDOW));
        return 1;
    case WM_PRINTCLIENT:
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = msg == WM_PAINT ? BeginPaint(hwnd, &ps) : (HDC)wp;
        GetClientRect(hwnd, &rc);
        if (msg == WM_PRINTCLIENT) FillRect(dc, &rc, GetSysColorBrush(COLOR_WINDOW));
        SetBkMode(dc, TRANSPARENT);
        if (d->pkg) Layout(dc, 1, d, rc.right);
        else {
            SelectObject(dc, g_fontText);
            SetTextColor(dc, GetSysColor(COLOR_GRAYTEXT));
            rc.left += MARGIN; rc.top += MARGIN;
            DrawText(dc, "Select a package to see what it is, what it needs and where it comes from.", -1, &rc, DT_WORDBREAK | DT_NOPREFIX);
        }
        if (msg == WM_PAINT) EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

void RegisterDetails(void)
{
    WNDCLASS wc;
    Fonts();
    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = DetailsProc;
    wc.hInstance = g_inst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = CLASS_DETAILS;
    RegisterClass(&wc);
}

void ShowDetails(HWND pane, PKG *p)
{
    DETAILS *d = (DETAILS *)GetWindowLong(pane, GWL_USERDATA);
    if (!d) return;
    if (d->pkg != p) d->top = 0;
    d->pkg = p;
    UpdateScroll(pane, d);
    InvalidateRect(pane, NULL, TRUE);
}
