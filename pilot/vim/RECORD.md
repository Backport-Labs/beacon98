# Vim 7.2 (gvim, zip distribution) - Beacon 98 pilot record

- Date checked: 2026-09-28
- Package: Vim - Vi IMproved (Bram Moolenaar et al.), Win32 GUI build (gvim)
- Version: 7.2 (7.2.000, official PC binaries dated 2008-08-09)
- License: Vim License (charityware; GPL-compatible)
- Recommendation: 7.2. It is the newest official Win32 binary that is both documented for 95/98 AND built so that Windows 9x can load it (see below). Newer docs claim 9x support up to 8.0.0028, but the official 7.3+ binaries are built with a toolchain that targets Windows 2000 and later.

## Windows 9x support evidence

- Vim 7.2 binary archive, gvim72.zip. The zip comment reads "Vim - Vi IMproved - v7.2 GUI binaries for MS-Windows NT/95". README_bindos.txt inside it (opened):
  "gvim72.zip	Windows 95/98/NT/etc. GUI version".
- runtime/doc/os_win32.txt at tag v7.2 (https://raw.githubusercontent.com/vim/vim/v7.2/runtime/doc/os_win32.txt, opened):
  "The Win32 version of Vim works on both Windows NT and Windows 95."
- Later versions:
  - os_win32.txt at v7.3, v7.4, v8.0.0000 and v8.0.0028 says "works on Windows NT, 95, 98, ME, XP, Vista and Windows 7".
  - Patch 7.3.1307 (runtime/doc/version7.txt): "MS-Windows build instructions are outdated. Solution: Adjust for building on Windows 7. Drop Windows 95/98/ME support. Files: Makefile, nsis/gvim.nsi".
  - Patch 8.0.0029 (version8.txt): "Drop support for MS-Windows older than Windows XP." The 8.1 notes add: "Since patch 8.0.0029 removed support for older MS-Windows systems, only MS-Windows XP and later are supported."
- Binary check (my own inspection of the official zips from ftp.nluug.nl/pub/vim/pc/; nothing was run):
  - gvim72.zip gvim.exe: linker 7.10 (VS2003), OS/subsystem version 4.0. Loadable on 9x.
  - gvim73_46.zip, gvim74.zip and gvim80-002.zip gvim.exe: linker 9.0 (VS2008), OS/subsystem version 5.0, and imports InitializeCriticalSectionAndSpinCount and IsDebuggerPresent (not in Win95).
  - Windows 9x refuses PE files with subsystem version 5.0 ("expects a newer version of Windows"), and VS2008 dropped 9x targets. This is from search results (e.g. http://jasper-22.blogspot.com/2012/06/cc-exes-and-dlls-created-by-visual.html, https://scalibq.wordpress.com/2012/12/17/visual-studio-versioning-and-compatibility/), NOT verified in a VM.
  - So the official 7.3/7.4/8.0 binaries are expected not to start on 95/98, despite what their docs say.
- Windows 95: covered by the 7.2 doc sentence above. gvim72 gvim.exe imports nothing that I flagged as missing on 95. Not tested.
- The ftp README (https://ftp.nluug.nl/pub/vim/pc/README) labels even gvim90.zip "for Windows 95/NT and later". This is stale boilerplate, not evidence.

## Download

- Official mirror (ftp.vim.org no longer resolves; ftp.nluug.nl is the first mirror listed on https://www.vim.org/mirrors.php):
  - https://ftp.nluug.nl/pub/vim/pc/gvim72.zip: 980,100 bytes, SHA-256 7478ba4169950f802eb12961af9797f30d09e41f10841bdcff4a7a1971b2b8da, MD5 af165f87f06f9b22709c0d8894e82b0a
  - https://ftp.nluug.nl/pub/vim/pc/vim72rt.zip (runtime files, REQUIRED): 7,194,365 bytes, SHA-256 4ae8bdb21b852e202de2e0ee635792de90b964c4838de594589c4941e0694176, MD5 7fa3818568406a0a5ba5dda829227c00
- Published checksums: https://ftp.nluug.nl/pub/vim/pc/MD5SUMS (stored here) lists "af165f87... gvim72.zip" and "7fa38185... vim72rt.zip". Both MATCH. MD5 only, unsigned.
- Self-installing gvim72.exe: MD5SUMS still lists it (935bcafb75be12138753bb12b76cece5), but the file is gone. I got 404 at ftp.nluug.nl and at the mirrorservice.org, vim.mirror.garr.it and ftp.sh.cvut.cz mirrors; others timed out. The 9x user therefore needs the zip route.
- Other packages: vim72w32.zip (console build; the README labels it "Windows NT/XP console"), vim72d32.zip (32-bit DOS, for the Win95 console), gvim72ole.zip (OLE build), vim72lang.zip (translations). Not downloaded.
- Note: the official 7.2 PC binary is unpatched 7.2.000. No official patched 7.2.x Win32 binary exists on the mirror.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\pilot\vim -DisableRemediation` on 2026-09-28
(engine 1.1.26080.3, signatures 1.459.442.0): "found no threats".

## License

- LICENSE.TXT is runtime/doc/uganda.txt from vim72rt.zip ("For Vim version 7.2. Last change: 2008 Jun 21").
- Clause I: "There are no restrictions on distributing unmodified copies of Vim except that they must include this license text."
- So redistributing the unmodified binaries is allowed, provided the license text is included (it is also inside vim72rt.zip as doc/uganda.txt).
- There is no source-hosting obligation for unmodified copies; source is only required for modified versions (clause II). Source is available at https://ftp.nluug.nl/pub/vim/pc/vim72src.zip (not downloaded).
- The documentation is under the Open Publication License (noted in uganda.txt).

## Security

Source: NVD API 2.0, cpeName cpe:2.3:a:vim:vim:7.2. This returns 229 CVEs whose NVD ranges include 7.2 (by year: 2008: 4, 2009: 1, 2016: 1, 2017: 5, 2019: 2, 2021: 19, 2022: 114, 2023: 35, 2024: 5, 2025: 8, 2026: 35).
Most 2021-2026 entries are fuzzing bugs with "prior to 8.2.x/9.x" ranges. Many are in code that did not exist in 7.2; I did not check each one. Treat 229 as an upper bound.

Named for 7.x / 7.2 specifically, or clearly applicable:
- CVE-2008-3074 / CVE-2008-3075: shellescape() "!" handling allows arbitrary commands, Vim 7.0-7.2 (CVSS2 9.3).
- CVE-2008-4101: K keyword lookup and other escaping flaws, arbitrary shell commands (before 7.2.010, CVSS2 9.3).
- CVE-2008-4677: netrw stores credentials (7.2 netrw).
- CVE-2009-0316: Python interface search path (before 7.2.045). The Win32 gvim72 build probably has no Python, so likely not applicable.
- CVE-2016-1248: 'filetype'/'syntax'/'keymap' values via modeline execute commands (before 8.0.0056).
- CVE-2017-5953, CVE-2017-6349, CVE-2017-6350: spell file and undo file integer overflows (before 8.0.03xx).
- CVE-2019-12735: modeline :source! arbitrary OS command execution when opening a file (before 8.1.1365, CVSS2 9.3).

Worst: CVE-2019-12735 and CVE-2008-3074/3075. Opening an untrusted text file can run commands.
Mitigation for the package: ship a default _vimrc with `set nomodeline`.

## Install behaviour

- Package type: two plain zip archives. No self-installer is available for 7.2 (see Download).
- What a package manager must do (from README_dos.txt in vim72rt.zip):
  1. Unpack vim72rt.zip and gvim72.zip on top of each other into the same root, e.g. C:\VIM. This creates C:\VIM\vim72\.
  2. Optionally run `vim\vim72\install.exe`, Vim's own console installer. It creates .bat files, a _vimrc, the "Edit with Vim" menu (gvimext.dll), Start Menu and desktop icons, and an uninstall entry.
     - install.exe has non-interactive switches (src/dosinst.c at v7.2): `-create-batfiles [vim gvim evim view gview vimdiff gvimdiff]`, `-create-vimrc`, `-install-popup`, `-install-openwith`, `-add-start-menu`, `-install-icons`, `-create-directories [vim|home]`.
     - CAUTION: in non-interactive mode install.exe assumes the NSIS installer. It registers `HKLM\...\Uninstall\Vim 7.2 (self-installing)` with UninstallString `uninstall-gui.exe`, and that file is NOT in the zip. A package manager should either run install.exe interactively, or create the Start Menu shortcut itself and use `uninstal.exe` (which is in the zip) for removal of the context-menu entries.
  3. Alternatively, do it manually: create a Start Menu shortcut to C:\VIM\vim72\gvim.exe, and optionally add `SET PATH=%PATH%;C:\VIM\vim72` to AUTOEXEC.BAT. Set $VIM only if the runtime files are placed elsewhere.
- Uninstall: uninstal.exe (in the zip) removes the registry entries, context menu and batch files. The files themselves are deleted by hand or by the package manager.

## Verification notes

- Verified by opening or downloading: the ftp.nluug.nl pc/ listing, README and MD5SUMS; the files inside gvim72.zip and vim72rt.zip (README_bindos.txt, README_dos.txt, uganda.txt); os_win32.txt at v7.2/v7.3/v7.4/v8.0.0000/v8.0.0028; version7.txt/version8.txt (master); src/dosinst.c at v7.2; PE headers and imports of gvim.exe 7.2/7.3.046/7.4/8.0.0002 (extracted to temp, not run); and NVD.
- From search snippets only: that Win9x refuses subsystem-5.0 PE files.
- Not verified: actual running on Win95/98 (no VM interaction); CVE-by-CVE applicability to 7.2 code.
