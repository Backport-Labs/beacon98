# ClamWin Free Antivirus 0.99.1 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: clamwin
- Package: ClamWin Free Antivirus (ClamWin Pty Ltd; GUI by "alch"; ClamAV Win32 engine port by Gianluigi Tiesi / Netfarm)
- Version: 0.99.1 (installer dated 2016-03-19 on SourceForge; news post dated 2016-01-17), ClamAV engine 0.99.1
- License: GPL-2.0 (ClamWin and ClamAV), with UnRAR licence for libclamunrar.dll and other component licences
- Recommendation: 0.99.1 is the right ClamWin build for Windows 98, and it can be hosted legally. **But it can no longer
  download virus signatures, so on its own it is useless as a virus scanner in 2026. Do not publish it as an
  antivirus.** See "Signature updates" below; the only engine that can still update on Windows 98 is ClamAV 1.4.4
  legacy-win9x, which should be verified as a separate package.

## Windows 9x support evidence

### Which versions exist

SourceForge file RSS (https://sourceforge.net/projects/clamwin/rss?path=/clamwin, opened) lists, among others:
0.95.3 (2009-11-10), 0.96 ... 0.98.7, 0.99 (2016-01), 0.99.1 (2016-03-19), 0.99.4 (2018-03-14), 0.103.2 and
0.103.2.1 (2021-06). News posts on clamwin.com (opened: content/view/220, 248, 249, 251) give the release dates.

### Primary evidence

- Installer script `Setup/Setup-nodb.iss` at commit d7ac35fe46d4 "Version 0.99" (2016-01-07) of
  https://github.com/clamwin/clamwin-py (cloned and read):
  `MinVersion=4.1.1998,5.0.2195` - i.e. the installer requires Windows 98 (4.1.1998) or Windows 2000.
  **Windows 95 (4.0) is refused.** Windows ME (4.90) passes. The script has explicit 9x branches:
  `; Copy Unicode build in NT and ANSI in 9x`, an ANSI `ExpShell.dll`, `QRecover\Release ANSI\QRecover.exe`,
  `conagent.pif` and `BalloonTip.pyd` with `Check: IsWin9x`, and `IsAllUsers()` returns True when `not UsingWinNT()`.
- clamwin.com home page (opened 2026-09-29): "ClamWin is a Free Antivirus program for Microsoft Windows 10 / 8 / 7 /
  Vista / XP / Me / 2000 / 98 and Windows Server 2012, 2008 and 2003." This text is not version-specific and is
  shown next to 0.103.2.1, which is doubtful on 98 (see below), so it is weak evidence.
- Import analysis (I extracted the installers with innoextract 1.9 and parsed the PE import tables; nothing was run):
  - 0.99.1: every binary has OS/subsystem version 4.0; imports only DLLs that exist on Windows 98 (KERNEL32, USER32,
    ADVAPI32, WS2_32/WSOCK32, IPHLPAPI, MSVCR80 which is bundled, etc.). No PSAPI, no NT-only calls found in a
    check for common NT-only APIs.
  - 0.99.4: imports differ from 0.99.1 only in a few MSVCR80 C-runtime functions, so it looks equally loadable on 98.
    Nobody I found states that it runs on 98, though.
  - 0.103.2.1: bundles unicows.dll (so it was meant to run on 9x), but `libclamav_llvm.dll` imports
    `PSAPI.DLL!GetProcessMemoryInfo` and `KERNEL32!TryEnterCriticalSection`. PSAPI.DLL is an NT component that stock
    Windows 98 does not ship (from general knowledge, not checked against a 98 file list), so 0.103.2.1 most likely
    fails on stock 98 without KernelEx. Its engine is also blocked from updates (below), so there is nothing to gain.
- Community (secondary, not primary): "Latest Versions of Software Working on Windows 98/ME"
  (https://retrosystemsrevival.blogspot.com/p/latest-versions-of-software-working-on_20.html, opened):
  "Clamwin 0.99.1 - Be sure to disable KernelEx if using this program! (CS)". A search snippet attributed to MSFN
  says "v0.99.1 is the last version that works on native Win9x" (page returned 403; not opened).
- Known 9x problem: MSFN "Unofficial ClamWin patch for Win98SE" (opened), patch author, 2011-05-01:
  "ClamWin has a bug on Win98SE, some types of files after the scan remain locked" (for 0.97.x; whether 0.99.1
  still has it is unknown).

### 0.95.3 vs 0.99.1

- 0.99.1 is newer, has the same 98 support in its installer, and its installer contains no third-party offers.
- **0.95.3 bundles the Ask.com toolbar installer**: extracting clamwin-0.95.3-setup-nodb.exe gives
  `tmp\askToolbarInstaller.exe` and `tmp\askInstallChecker.exe`; the setup script history shows "added Ask Toolbar
  Dialog" (2009-10-12). The 0.99 script has `;#DEFINE IncludeToolbar` commented out, and the extracted 0.99.1 installer
  has no toolbar files. Reject 0.95.3.
- 0.99.4 (2018) is newer and fixes ClamAV CVEs; import-wise it should run on 98 too, but there is no report that it
  does. Recommendation: 0.99.1 (community-confirmed); test 0.99.4 in the VM before ever preferring it. Both have the
  same fatal signature problem.
- KernelEx: not needed for 0.99.1. The community list says to *disable* KernelEx for it.

## Signature updates (the important part)

**ClamWin 0.99.1 cannot update its virus signatures any more. Without current signatures it detects nothing
written after 2016. It is useless as a virus scanner today.**

- ClamAV End-of-Life policy (https://docs.clamav.net/faq/faq-eol.html, opened via WebFetch): "Every version from
  ClamAV 0.105 and down, including all patch versions, are unsupported, and are actively blocked from downloading new
  updates." LTS versions get signatures for the 3-year support period plus one year. 1.4 LTS ends 2027-08-15, so its
  signature access should last until about 2028-08. 0.103 LTS ended 2024-09-14 (access until about 2025-09).
- Tested on 2026-09-29 with HEAD requests to the ClamAV CDN, using freshclam-style User-Agent strings:
  - `ClamAV/0.99.1 ...` -> `http://database.clamav.net/daily.cvd` 403 Forbidden (Cloudflare); https: 403.
  - `ClamAV/0.103.2 ...` (ClamWin 0.103.2.1's engine) -> 403 on both.
  - `ClamAV/1.4.4 ...` -> http: 301 to https; https: 200 OK, 23,434,679 bytes.
  So the CDN refuses old engines, and it no longer serves plain HTTP (it redirects to HTTPS, which 0.99.1's
  freshclam cannot follow in any case). DNS TXT `current.cvd.clamav.net` = `1.4.6:63:28138:...`.
- ClamWin itself confirmed the breakage: news of 2021-04-30 (clamwin.com/content/view/250): "Our team is working
  hard on upgrading ClamWin to use the latest ClamAV engine to re-enable the database updates." 0.103.2.1
  (2021-06-07) "Fixed Virus database updates"; that engine is now blocked too. GitHub issue
  clamwin/clamav-win32#29 (2025-12-11, opened): "ClamAV doesn't update its database on Windows 98/XP/7 with last
  version of ClamWin" - no reply.
- The full installer (clamwin-0.99.1-setup.exe, 120,690,586 bytes) ships a 2016 database. Not downloaded; stale.

### What does still work on Windows 98

- Netfarm's ClamAV port page (https://oss.netfarm.it/clamav/, opened; last update April 11 2026; this is the
  engine port ClamWin uses): "clamav-1.4.4-legacy-win9x.7z : Built with MinGW-w64. Compatible with Windows 98 SE.
  (Very unsupported, don't use this version on newer systems)." It also warns: "The 32-bit version may struggle
  with the current size of the ClamAV signature database" and "The Legacy versions rely on a custom compatibility
  layer, making them experimental and beta quality."
- I downloaded it to a temp folder only (6,539,837 bytes, SHA-256
  674a3a0512ef7f35d6f8bad4282c0ea0471039fa11e43e8a9dbe8529984eafce; no published checksum). It contains
  command-line clamscan/freshclam/sigtool/clambc, libclamav.dll (18 MB), OpenSSL 3.5.6 and curl 8.19.0, so freshclam
  can do HTTPS itself. GPL-2.0; its compatibility layer is MIT; source at https://github.com/clamwin/clamav-win32
  (no 1.4.4 tag seen; tags go v1.4.2-r1, v1.5.0).
- It is a command-line engine, not ClamWin. The page also says the 32-bit legacy engine can be dropped into
  ClamWin's bin folder together with a replacement clamwin.zip; whether that works with the win9x build on 98 is
  untested.
- Memory: the current database (daily ~23 MB compressed plus main and bytecode) needs far more RAM than most 98
  machines have; the maintainer's warning above applies. Not tested.
- Suggestion: if Beacon wants an antivirus, verify **ClamAV 1.4.4 legacy-win9x** as a separate package
  (id e.g. `clamav`), with a memory `Requires` and a clear Notice. Do not publish ClamWin 0.99.1 alone.

## Download

- Page: https://sourceforge.net/projects/clamwin/files/clamwin/0.99.1/ (official SourceForge project, linked from
  clamwin.com as "Project on SF.net")
- URL: https://downloads.sourceforge.net/project/clamwin/clamwin/0.99.1/clamwin-0.99.1-setup-nodb.exe
- File: clamwin-0.99.1-setup-nodb.exe, 8,664,331 bytes (installer without the virus database)
- SHA-256: a3ebf7225beeb5098f88bf8e656fa6fe695a8dde79dfa7000db8b8f30ea2626f
- MD5: fa8210b0979969fa2649cbe6cce1b353. SourceForge RSS lists fa8210b0979969fa2649cbe6cce1b353: MATCH.
- GPG: clamwin-0.99.1-setup-nodb.exe.asc (saved here) verified with the ClamWin Software Distribution Key from
  SourceForge ("GPG Public Key/ClamWin Software Distribution Key/ClamWin-SW-GPG-Key.asc"), DSA key
  0839CC718CC6DDB4, fingerprint DF56 551A 55CD E5A6 DEC6 1847 0839 CC71 8CC6 DDB4: "Good signature", made
  2016-04-16. The key is not certified by anyone I trust; it is simply the key the project publishes.
- Alternatives (not in this folder): clamwin-0.99.1-setup.exe (with 2016 database, 120,690,586 bytes, MD5
  5a2c77b1ba697e532cc235027fa39e5a per SF), clamwin-update-0.99-0.99.1.exe.
- Other versions downloaded to a temp folder only for comparison: 0.95.3 nodb (cd5f722e...), 0.99.4 nodb
  (77815d9d637857cce43916ff2d2a6a6d0204143a64f895de42da70ad6b9ac5f0, MD5 7a3195937d940af4cb01c647bd4aa1c7 = SF),
  0.103.2.1 nodb (90e72f30...).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\clamwin -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0), after all files incl. src\ were in place: "found no threats".

## License

- GPL-2.0. The installer's License page (Setup/Setupfiles/License.rtf) is a heading "CLAMWIN PTY LTD License
  Agreement" with uninstall instructions, followed by the unmodified GNU GPL version 2 text. No extra terms.
  COPYING in the ClamWin source is GPL 2. ClamAV 0.99.1 is GPL 2 (COPYING in its tarball).
- Components under other licences inside the installer:
  - libclamunrar.dll: UnRAR licence ("The UnRAR utility may be freely distributed. It is allowed to distribute
    UnRAR inside of other software packages."; sources may not be used to re-create RAR compression).
  - libclamav_llvm.dll (LLVM licence), bzip2, zlib, LZMA, PCRE, regex, file, getopt, YARA, LGPL parts (ClamAV's
    COPYING.* files).
  - Python 2.3 (python23.dll, PSF), wxPython/wxWidgets 2.4 (wxmsw24h.dll, wxWindows Library Licence), pywin32,
    mxDateTime (eGenix public licence), _ssl.pyd with a statically linked old OpenSSL (OpenSSL licence), and the
    Microsoft VC++ 2005 runtime DLLs (Microsoft redistributable).
- LICENSE.TXT here: my header listing the above, ClamWin's COPYING (GPL 2), then ClamAV 0.99.1's COPYING.unrar,
  .llvm, .bzip2, .zlib, .lzma, .pcre, .regex, .file, .getopt, .YARA and .LGPL. Windows-1252, CR LF.
- Redistributing the unmodified installer is allowed. Conditions: include the licence text; GPL 2 s.3 - provide
  the complete corresponding source (we host it next to the binary).

## Matching source (hosted, in src\)

| File | Size | SHA-256 | URL |
|---|---|---|---|
| clamav-0.99.1.tar.gz | 15,990,867 | e144689122d3f91293808c82cbb06b7d3ac9eca7ae29564c5d148ffe7b25d58a | https://www.clamav.net/downloads/production/clamav-0.99.1.tar.gz |
| clamav-0.99.1.tar.gz.sig | 72 | 1630422b7fe46a088d5a124ff401c3ab90a2e7c01add6ff6d38ec83440162ec8 | same + .sig |
| clamav-win32-old-0.99.1.zip | 53,740,575 | 0956971526b2f849ddbeace36f218de032c9d7d05f863c9b400e4fc36186acc9 | https://codeload.github.com/clamwin/clamav-win32-old/zip/refs/tags/0.99.1 |
| clamwin-py-d7ac35fe46d46c21d3667a8ed31cc9d24140b2b4.zip | 9,038,800 | 32496f58baecad4dd53119538aff1c231e20f5fe1f8b26d4bcebf737225f1d84 | https://codeload.github.com/clamwin/clamwin-py/zip/d7ac35fe46d46c21d3667a8ed31cc9d24140b2b4 |
| pyc-913036bda0.zip | 13,525 | d7e7724727afd723afe37eef837c64a8ed35b587823eb18b12c85c5b82152060 | https://codeload.github.com/clamwin/pyc/zip/913036bda0 |
| QRecover-036e3bb103.zip | 46,661 | 282783ff24a252ef92e0eef1437e7c4d24a993c48c9eb68124d2895573b18b1d | https://codeload.github.com/clamwin/QRecover/zip/036e3bb103 |

- clamav-0.99.1.tar.gz: upstream ClamAV. GPG: "Good signature from Talos (Talos GPG Key) <research@sourcefire.com>",
  key B3D5342C260429A0 (fingerprint F79F B2D0 8751 574C 5D3F DFFB B3D5 342C 2604 29A0, fetched from
  keyserver.ubuntu.com; the key has since expired). Signature made 2016-02-24.
- clamav-win32-old tag 0.99.1: ClamWin's Win32 port of the engine (full ClamAV tree plus the win32\ build files).
  GitHub-generated archive; GitHub does not guarantee byte-identical re-downloads, so keep our copy.
- clamwin-py: the GUI, installer scripts and shell extension (cpp\). **Exact 0.99.1 GUI source is not tagged.** The
  last commit before 0.99.1 is d7ac35fe46 "Version 0.99" (py/version.py says '0.99'), while the shipped
  clamwin.zip contains version.pyo with "0.99.1". So the GUI source may differ from the 0.99.1 build at least in
  the version string. Unresolved.
- pyc (Python ClamAV extension, pyc.pyd): last commit before March 2016. QRecover: only commit.
- Not in these archives: Python 2.3, wxPython 2.4, pywin32, mxDateTime, py2exe, OpenSSL (in _ssl.pyd), the ClamWin
  updater (clamwin/cwupdater, not shipped as a separate file here), and opencow (not in 0.99.1's file list). These
  are not GPL (except that the GPL's "complete source" arguably covers what ClamWin links); their sources are
  available from their own projects. Flag for legal review if we want to be strict.

## Security

- NVD API 2.0, `virtualMatchString=cpe:2.3:a:clamav:clamav:0.99.1`: 38 CVEs whose ranges include 0.99.1 (queried
  2026-09-29). I did not check each against the 0.99.1 source. Worst (CVSS 3 9.8):
  - CVE-2017-12377: mew packer heap overflow (0.99.2 and prior).
  - CVE-2017-12379: messageAddArgument buffer overflow in mail parsing (0.99.2 and prior).
  - CVE-2023-20032: HFS+ partition parser heap overflow, remote code execution (NVD range includes 0.99.1; whether 0.99.1 has the vulnerable HFS+ code was not checked).
  - CVE-2025-20260: PDF scanning buffer overflow.
  - Also 2026's CVE-2026-20213/-20214/-20215/-20217 (PE, FSG, 7z, PESpin parsers, 7.5).
  An antivirus parses hostile files by design, so these matter more than for most programs.
- NVD keyword "clamwin": 0 results.
- The bundled Python 2.3 _ssl.pyd uses a very old OpenSSL; the GUI's update check uses it.
- 0.99.4 would fix some of the 2017-2018 ones (0.99.4 news: "ClamAV UAF Vulnerabilities, Buffer Overflow
  Vulnerabilities, Null Dereference Vulnerability").

## Install behaviour

- Installer type: Inno Setup (innoextract: "setup data version 5.1.13"). Script: Setup/Setup-nodb.iss (clamwin-py).
- Silent switches: standard Inno Setup `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART`. ClamWin documents no switches of
  its own. The task `DownloadDB` ("Download Virus Database Files") is checked by default and runs
  `ClamWin.exe --mode=update --close` at the end of setup; that download now fails (403). Pass `/TASKS=""` to
  deselect all tasks (Inno's documented behaviour: only listed tasks are selected; not tested with this installer).
- At the end setup starts `ClamTray.exe` (nowait), also in silent mode.
- Default folder: `{code:BaseDir}\ClamWin`; on 9x IsAllUsers() is always true, so `{pf}\ClamWin`
  (C:\Program Files\ClamWin). Start Menu group "ClamWin Antivirus".
- Registry: HKLM `...\CurrentVersion\Run` value `ClamWin` = `"{app}\bin\ClamTray.exe" --logon` (starts with
  Windows); HKLM `Software\ClamWin` Path and Version (9900); Explorer context-menu shell extension (ANSI
  ExpShell.dll on 9x); Outlook add-in only if Outlook is installed. Data folders under the common profile
  `.clamwin\db`, `log`, `quarantine`.
- Uninstaller: yes (Inno). AppId is not set, so it defaults to AppName: key
  `Software\Microsoft\Windows\CurrentVersion\Uninstall\ClamWin Free Antivirus_is1`. DisplayName defaults to AppVerName;
  innoextract reports "ClamWin Free Antivirus 0.99.1", so the Add/Remove Programs name should be
  **ClamWin Free Antivirus 0.99.1** (from the script defaults; not observed on a real install).
  Uninstall runs `WClose.exe` first.

## Verification notes

- Verified by opening/downloading: SourceForge file RSS (sizes, MD5s, dates), clamwin.com home and news posts
  220/223/224/227/230-241/243-251, the installer (innoextract, not run), its GPG signature, the clamwin-py git
  history and Setup-nodb.iss/License.rtf/COPYING, ClamAV 0.99.1 tarball and signature, the ClamAV EOL FAQ
  (WebFetch; direct curl is blocked by Cloudflare), CDN responses (curl HEAD), oss.netfarm.it/clamav, the
  1.4.4 win9x archive (extracted to temp, not run), GitHub issue #29, NVD API.
- From search snippets only: the MSFN "v0.99.1 is the last version that works on native Win9x" quote.
- Not verified: running on Windows 95/98/ME (no VM interaction); whether 0.99.4 runs on 98; exact GUI source of
  0.99.1; whether Win98's kernel32 exports TryEnterCriticalSection (the Netfarm win9x build imports it too, so it
  may be present as a stub); the `/TASKS=""` behaviour; the Add/Remove Programs name on a real system.
