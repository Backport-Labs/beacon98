/* beacon.h - Beacon 98: what the files of the program share.
 *
 * Constants, types, the shared state, and the functions each file offers to
 * the others. What a file keeps to itself is declared static in that file.
 */
#ifndef BEACON_H
#define BEACON_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ------------------------------------------------------------------------
 * Declarations Tiny C Compiler's headers do not have
 * --------------------------------------------------------------------- */
void WINAPI InitCommonControls(void);

/* Tree view */
#define MY_WC_TREEVIEW     "SysTreeView32"
#define MY_TVS_HASBUTTONS  0x0001
#define MY_TVS_HASLINES    0x0002
#define MY_TVS_LINESATROOT 0x0004
#define MY_TVS_SHOWSELALWAYS 0x0020
#define MY_TVIF_TEXT   0x0001
#define MY_TVIF_PARAM  0x0004
#define MY_TVIF_STATE  0x0008
#define MY_TVIS_BOLD   0x0010
#define MY_TVI_ROOT    ((HANDLE)0xFFFF0000)
#define MY_TVI_LAST    ((HANDLE)0xFFFF0002)
#define MY_TVM_INSERTITEMA 0x1100
#define MY_TVM_DELETEITEM  0x1101
#define MY_TVM_EXPAND      0x1102
#define MY_TVM_SELECTITEM  0x110B
#define MY_TVM_SETITEMA    0x110D
#define MY_TVE_EXPAND  2
#define MY_TVGN_CARET  9
#define MY_TVN_SELCHANGEDA (-402)
typedef struct {
    UINT mask;
    HANDLE hItem;
    UINT state, stateMask;
    LPSTR pszText;
    int cchTextMax, iImage, iSelectedImage, cChildren;
    LPARAM lParam;
} MY_TVITEM;
typedef struct { HANDLE hParent, hInsertAfter; MY_TVITEM item; } MY_TVINSERT;
typedef struct { NMHDR hdr; UINT action; MY_TVITEM itemOld, itemNew; POINT ptDrag; } MY_NMTREEVIEW;

/* List view */
#define MY_WC_LISTVIEW  "SysListView32"
#define MY_LVS_REPORT        0x0001
#define MY_LVS_SINGLESEL     0x0004
#define MY_LVS_SHOWSELALWAYS 0x0008
#define MY_LVS_EX_CHECKBOXES    0x0004
#define MY_LVS_EX_FULLROWSELECT 0x0020
#define MY_LVCF_FMT     0x0001
#define MY_LVCF_WIDTH   0x0002
#define MY_LVCF_TEXT    0x0004
#define MY_LVCFMT_RIGHT 1
#define MY_LVIF_TEXT    0x0001
#define MY_LVIF_PARAM   0x0004
#define MY_LVIF_STATE   0x0008
#define MY_LVIS_FOCUSED 0x0001
#define MY_LVIS_SELECTED 0x0002
#define MY_LVIS_STATEIMAGEMASK 0xF000
#define MY_LVNI_SELECTED 0x0002
#define MY_LVM_GETITEMCOUNT  0x1004
#define MY_LVM_GETITEMA      0x1005
#define MY_LVM_INSERTITEMA   0x1007
#define MY_LVM_DELETEALLITEMS 0x1009
#define MY_LVM_GETNEXTITEM   0x100C
#define MY_LVM_ENSUREVISIBLE 0x1013
#define MY_LVM_INSERTCOLUMNA 0x101B
#define MY_LVM_SETITEMSTATE  0x102B
#define MY_LVM_GETITEMSTATE  0x102C
#define MY_LVM_SETITEMTEXTA  0x102E
#define MY_LVM_SETEXTENDEDLISTVIEWSTYLE 0x1036
#define MY_LVM_SORTITEMS     0x1030
#define MY_LVN_ITEMCHANGED (-101)
#define MY_LVN_COLUMNCLICK (-108)
typedef struct { UINT mask; int fmt, cx; LPSTR pszText; int cchTextMax, iSubItem; } MY_LVCOLUMN;
typedef struct {
    UINT mask;
    int iItem, iSubItem;
    UINT state, stateMask;
    LPSTR pszText;
    int cchTextMax, iImage;
    LPARAM lParam;
} MY_LVITEM;
typedef struct {
    NMHDR hdr;
    int iItem, iSubItem;
    UINT uNewState, uOldState, uChanged;
    POINT ptAction;
    LPARAM lParam;
} MY_NMLISTVIEW;

/* Status bar */
#define MY_STATUSCLASS  "msctls_statusbar32"
#define MY_SBARS_SIZEGRIP 0x0100
#define MY_SB_SETTEXTA  (WM_USER + 1)
#define MY_SB_SETPARTS  (WM_USER + 4)

/* Progress bar */
#define MY_PROGRESSCLASS "msctls_progress32"
#define MY_PBM_SETRANGE (WM_USER + 1)
#define MY_PBM_SETPOS   (WM_USER + 2)

/* WinInet, which Internet Explorer installs */
HANDLE WINAPI InternetOpenA(LPCSTR, DWORD, LPCSTR, LPCSTR, DWORD);
HANDLE WINAPI InternetOpenUrlA(HANDLE, LPCSTR, LPCSTR, DWORD, DWORD, DWORD);
BOOL   WINAPI InternetReadFile(HANDLE, void *, DWORD, DWORD *);
BOOL   WINAPI InternetCloseHandle(HANDLE);
BOOL   WINAPI HttpQueryInfoA(HANDLE, DWORD, void *, DWORD *, DWORD *);
#define MY_INTERNET_OPEN_TYPE_PRECONFIG 0
#define MY_INTERNET_FLAG_RELOAD         0x80000000
#define MY_INTERNET_FLAG_NO_CACHE_WRITE 0x04000000
#define MY_INTERNET_FLAG_PRAGMA_NOCACHE 0x00000100
#define MY_INTERNET_FLAG_NO_UI          0x00000200
#define MY_INTERNET_FLAG_NO_AUTO_REDIRECT 0x00200000
#define MY_HTTP_QUERY_CONTENT_LENGTH    5
#define MY_HTTP_QUERY_DATE              9
#define MY_HTTP_QUERY_LOCATION          33
#define MY_HTTP_QUERY_STATUS_CODE       19
#define MY_HTTP_QUERY_FLAG_NUMBER       0x20000000

/* Shell links, for Start Menu shortcuts */
typedef struct { DWORD d1; WORD d2, d3; BYTE d4[8]; } MYGUID;
typedef struct ShellLink_ ShellLink;
typedef struct {
    HRESULT (WINAPI *QueryInterface)(ShellLink *, const MYGUID *, void **);
    ULONG   (WINAPI *AddRef)(ShellLink *);
    ULONG   (WINAPI *Release)(ShellLink *);
    void *GetPath, *GetIDList, *SetIDList, *GetDescription, *SetDescription, *GetWorkingDirectory;
    HRESULT (WINAPI *SetWorkingDirectory)(ShellLink *, LPCSTR);
    void *GetArguments;
    HRESULT (WINAPI *SetArguments)(ShellLink *, LPCSTR);
    void *GetHotkey, *SetHotkey, *GetShowCmd, *SetShowCmd, *GetIconLocation, *SetIconLocation;
    void *SetRelativePath, *Resolve;
    HRESULT (WINAPI *SetPath)(ShellLink *, LPCSTR);
} ShellLinkVtbl;
struct ShellLink_ { ShellLinkVtbl *v; };
typedef struct PersistFile_ PersistFile;
typedef struct {
    HRESULT (WINAPI *QueryInterface)(PersistFile *, const MYGUID *, void **);
    ULONG   (WINAPI *AddRef)(PersistFile *);
    ULONG   (WINAPI *Release)(PersistFile *);
    void *GetClassID, *IsDirty, *Load;
    HRESULT (WINAPI *Save)(PersistFile *, const WCHAR *, BOOL);
    void *SaveCompleted, *GetCurFile;
} PersistFileVtbl;
struct PersistFile_ { PersistFileVtbl *v; };
HRESULT WINAPI CoInitialize(void *);
void    WINAPI CoUninitialize(void);
HRESULT WINAPI CoCreateInstance(const MYGUID *, void *, DWORD, const MYGUID *, void **);
void    WINAPI CoTaskMemFree(void *);
HRESULT WINAPI SHGetSpecialFolderLocation(HWND, int, void **);
BOOL    WINAPI SHGetPathFromIDListA(void *, LPSTR);
#define MY_CSIDL_PROGRAMS 2
#ifndef CP_ACP
#define CP_ACP 0
int WINAPI MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int);
#endif

/* TweetNaCl (tweetnacl.c) */
int crypto_sign_ed25519_tweet_open(unsigned char *m, unsigned long long *mlen,
    const unsigned char *sm, unsigned long long n, const unsigned char *pk);

/* ------------------------------------------------------------------------
 * Constants, types and the state the files share
 * --------------------------------------------------------------------- */
#define APP_NAME     "Beacon 98"
#define APP_VERSION  "0.6.0"
#define CATALOG_HOST "get.backportlabs.com"
#define SELF_PACKAGE "beacon98"          /* the catalog's package for Beacon itself */
#define CATALOG_FILE "CATALOG.TXT"
#define SIG_FILE     "CATALOG.SIG"

/* Fields of a package block, in the order of g_fieldNames (catalog.c). */
enum {
    F_PACKAGE, F_NAME, F_VERSION, F_SECTION, F_SUMMARY, F_DESCRIPTION,
    F_HOMEPAGE, F_LICENSE, F_LICENSE_FILE, F_SYSTEMS, F_AVAILABILITY,
    F_DOWNLOAD, F_SOURCE, F_INSTALLED_SIZE, F_DEPENDS, F_REQUIRES,
    F_INSTALL, F_AFTER, F_SHORTCUT, F_UNINSTALL, F_WARNING, F_NOTICE,
    F_REMOVE, F_DETECT, F_REFERER, F_HARDWARE,
    F_COUNT
};

/* What is installed. */
#define ST_NO      0
#define ST_YES     1
#define ST_UPDATE  2
#define ST_UNKNOWN 3

typedef struct {
    char *f[F_COUNT];        /* field values; continuation lines joined with \n */
    DWORD bytes;             /* total size of the Download files */
    int external;            /* Availability: external */
    int status;              /* ST_ */
    char have[40];           /* installed version, when known */
    int reqMissing;          /* number of Requires lines that fail */
    int marked;              /* ticked for installing */
    int source;              /* index in g_src: 0 is Backport Labs */
    char fits[80];           /* a device of this computer its Hardware lines name, or "" */
} PKG;

typedef struct {
    char serial[16], date[16], expires[16], base[256];
    PKG *pkg;
    int count;
    char *pool;              /* all the strings of the catalog */
} CATALOG;

#define MAX_SECTIONS 7
extern const char *g_sections[MAX_SECTIONS];

extern HINSTANCE g_inst;
extern CATALOG g_cat;           /* the packages of every source, merged */
extern int g_testMode;           /* /selftest or /shot: no message boxes */
extern char g_dir[MAX_PATH];     /* folder of BEACON98.EXE, ends with \ */

/* ------------------------------------------------------------------------
 * What each file offers to the others
 * --------------------------------------------------------------------- */

/* sha256.c: SHA-256 */
typedef struct { DWORD h[8]; BYTE buf[64]; DWORD len; DWORD bitsLo, bitsHi; } SHA256;
void Sha256Init(SHA256 *s);
void Sha256Add(SHA256 *s, const void *data, DWORD n);
void Sha256Done(SHA256 *s, BYTE out[32]);
int  Sha256File(const char *path, BYTE out[32], DWORD *size);
void ToHex(const BYTE *b, int n, char *out);
int  FromHex(const char *s, BYTE *out, int n);

/* sign.c: the catalog signature */
#define SIG_OK        0
#define SIG_NO_FILE   1
#define SIG_BAD_FILE  2
#define SIG_WRONG_KEY 3
#define SIG_INVALID   4
int  VerifyBytes(const BYTE *msg, DWORD n, const BYTE sig[64], const BYTE key[32]);
int  VerifyCatalogFile(const char *catalog, const char *sigfile);
int  VerifyCatalogFileKey(const char *catalog, const char *sigfile, const BYTE key[32]);
void KeyIdOf(const BYTE key[32], char out[17]);
const char *SigText(int result);
extern const char *g_keyId;

/* sources.c: Backport Labs' catalog and the custom sources */
#define MAX_SOURCES 8
typedef struct {
    char name[64];
    char location[260];      /* ends with / (web address) or \ (folder) */
    BYTE key[32];            /* its public signing key */
    char headers[512];       /* access headers, "Name: value\r\n" each; sent over HTTPS only */
    CATALOG cat;             /* its own catalog */
    int loaded, state;       /* state: SIG_ of the last load */
} SOURCE;
extern SOURCE g_src[MAX_SOURCES];
extern int g_nsrc;
void ReadSources(void);
int  WriteSources(const SOURCE *list, int n);
void NormalizeLocation(char *loc, int len);
void SourceFiles(int n, char *cat, char *sig);
int  VerifySource(int n, const char *cat, const char *sig);
void LoadAllCatalogs(char *state, int stateLen, int *builtinResult);
const char *SourceBase(PKG *p);

/* catalog.c: reading CATALOG.TXT */
int  LoadCatalog(const char *path, CATALOG *cat, char *err, int errLen);
void FreeCatalog(CATALOG *cat);
PKG *FindPkg(CATALOG *cat, const char *id);
int  SectionIndex(const char *name);
void FirstLine(const char *text, char *out, int outLen);

/* system.c: what this computer has */
void CheckSystem(CATALOG *cat);
int  RequirementMet(const char *line, char *what, int whatLen);
void ExpandPlaces(const char *in, char *out, int outLen);
const char *ThisWindows(void);
const char *ThisEdition(void);
PKG *MissingPackage(PKG *p);
int  SystemListed(const char *systems);
int  CompareVersions(const char *a, const char *b);
int  PciDevice(int n, char *id, int idLen, char *name, int nameLen);

/* net.c: downloading over HTTP */
int  HttpGetFile(const char *url, const char *path, DWORD expect, volatile int *cancel,
                 void (*progress)(DWORD done, DWORD total, void *ctx), void *ctx, char *err, int errLen);
int  HttpGetFileH(const char *url, const char *headers, int secret, const char *path, DWORD expect, volatile int *cancel,
                  void (*progress)(DWORD done, DWORD total, void *ctx), void *ctx, char *err, int errLen);
void CloseNet(void);
int  ServerDate(char *out, int outLen);
int  IsUrl(const char *s);

/* tls.c: HTTPS with BearSSL over Windows Sockets */
int  SockHttpGet(const char *url, const char *headers, const char *path, DWORD expect, volatile int *cancel,
                 void (*progress)(DWORD done, DWORD total, void *ctx), void *pctx,
                 int *status, char *location, int locLen, char *err, int errLen);
int  SplitUrl(const char *url, int *tls, char *host, int hostLen, int *port, char *path, int pathLen);
int  ParseHttpDate(const char *s, long *days, long *secs);
size_t TrustAnchors(void);
const char *ClockNote(void);
void TestShiftClock(long days);

/* unzip.c: unpacking ZIP files */
typedef void (*UNZIP_LOG)(char kind, const char *path, void *ctx);
int  Unzip(const char *archive, const char *target, int strip, volatile int *cancel,
           UNZIP_LOG log, void *ctx, char *err, int errLen);

/* task.c: work in a second thread, with a progress window */
typedef int (*TASKFN)(void *ctx);
int  RunTask(HWND owner, const char *title, TASKFN fn, void *ctx, int autoClose);
void TaskLog(const char *fmt, ...);
void TaskProgress(int percent);
int  TaskCancelled(void);
volatile int *TaskCancelFlag(void);

/* confirm.c: asking before installing */
int  ConfirmBox(HWND owner, const char *title, const char *head, const char *body, const char *yes, const char *no);

/* install.c: updating the catalog, installing and removing */
int  UpdateCatalog(HWND owner);
int  InstallPackages(HWND owner, PKG **chosen, int count);
int  RemovePackage(HWND owner, PKG *p);
int  OfferPackage(HWND owner, PKG *p, PKG *need);
int  FetchFile(const char *line, const char *dir, char *out);
void LocalName(const char *loc, char *out, int outLen);
int  FetchFileFrom(const char *line, const char *base, const char *headers, const char *referer, const char *dir, char *out);
int  SetupFromZip(const char *zip, const char *folder, char *setup, char *err, int errLen);

/* window.c: the main window */
int  RunWindow(int show);
HWND OpenForShot(const char *search, int row);
void SortForShot(int col);

/* srcdlg.c: Settings, Sources */
int  SourcesDialog(HWND owner);

/* details.c: the pane that describes the selected package */
#define CLASS_DETAILS "Beacon98Details"
void RegisterDetails(void);
void ShowDetails(HWND pane, PKG *p);

/* test.c: the self-test */
int  SelfTest(void);
int  Shot(const char *file, int row, const char *search, const int *sorts, int nsort, int sources);
int  CaptureWindow(HWND hwnd, const char *file);
extern const char *g_shotFile;   /* /shot /sources: where the Sources window is drawn */

#endif
