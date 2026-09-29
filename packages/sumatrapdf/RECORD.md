# SumatraPDF 0.7 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: SumatraPDF (Krzysztof Kowalczyk)
- Version: 0.7 (2007-07-28)
- License: GNU GPL version 2 ("License: GPLv2" in the source headers; COPYING is GPL v2). The GPLv3 switch came only in July 2009.
- Recommendation: 0.7, listed as **external** (downloaded from the author's own server over plain HTTP), not hosted. The source we can obtain is incomplete: the build contains the author's poppler fork "poppler-kjk", whose repository no longer exists, so we could not offer the complete corresponding source that GPL v2 s.3 requires of a distributor.

## Windows 9x support evidence

- Author's commit d97dbe8ca441 of 2007-08-02, five days after 0.7 (https://github.com/sumatrapdfreader/sumatrapdf/commit/d97dbe8ca441b3210ea6e134f90156c3b50d0df2, opened via the GitHub API):
  "hookup fullscreen code to menu item; bump WINVER to 0x0500 to have access to multi-monitor functions (means no more support for win98; ..." The diff changes `#define WINVER 0x0410` (Windows 98) to `0x0500` in src/SumatraPDF.h. So 0.7 is the last release built for Windows 98.
- Author's download page, archived 2008-09-13 and later (https://web.archive.org/web/20080913080830/http://blog.kowalczyk.info/software/sumatrapdf/download.html, opened): "SumatraPDF requires Windows 2000 or newer (XP, Vista). Windows 95, 98 and ME are not supported." Archived pages for 0.7 (2007-08-11), 0.8 and 0.8.1 (2008-06-12) carry no system requirements at all.
- Import tables of the official binaries (read with a PE parser; the programs were not run). All are UPX-packed, so only the stub imports are visible:
  - 0.7, 0.8, 0.8.1: imports only functions that exist on Windows 98 (PrintDlgA, MSIMG32!AlphaBlend, ...). Subsystem version 4.0.
  - 0.9: imports comdlg32!PrintDlgExA, which exists only on Windows 2000 and later. So 0.9 and later will not start on stock 98.
- Community reports (not primary): Operating System Revival's "latest versions working on 98/ME" lists "SumatraPDF 0.7 (FV)" (final working version; cached in research\import\cache\osr-final.html). MSFN thread https://msfn.org/board/topic/150481-sumatrapdf-for-win98se/ (opened): official 0.8.1 has "a lot of problems (no menu, etc.)" on 98 SE; a user ("aru") made an unofficial patched 0.8.1 (not usable for us). OSR's KernelEx list says 1.1, 2.2.1 and 3.1.2 portable work with KernelEx, and "SamutraPDF cannot print with 0.9 and later. To print requires KernelEx stubs", "GDIPLUS.DLL is required for later than 1.2".
- Windows 95: 0.7 imports MSIMG32.DLL (AlphaBlend), which Windows 95 does not ship (it came with 98). Not supported on 95 as is. ME: same family as 98, expected to work; not tested.
- Choices: 0.7 (last built for 98, stock) is recommended. Alternative with KernelEx: 1.1 (last before the GDI+ requirement per OSR; not verified here), without printing. Not pursued.

## Download

- Official page: https://www.sumatrapdfreader.org/download-prev lists releases back to 1.0 only, but its URL scheme serves 0.7: https://www.sumatrapdfreader.org/dl/rel/0.7/SumatraPDF-0.7-install.exe redirects to https://files.sumatrapdfreader.org/software/sumatrapdf/rel/0.7/SumatraPDF-0.7-install.exe (HTTPS only; plain HTTP redirects to HTTPS).
- Author's older download host, linked by his site's sumatra.js (archived 2013: `http://kjkpub.s3.amazonaws.com/sumatrapdf/rel/SumatraPDF-' + ver + '-install.exe`): http://kjkpub.s3.amazonaws.com/sumatrapdf/rel/SumatraPDF-0.7-install.exe. Still answers plain HTTP/1.0 with 200 (tested `curl.exe -sS -I --http1.0`), and the file is byte-identical to the files.sumatrapdfreader.org copy.
- File: SumatraPDF-0.7-install.exe, 865,204 bytes, NSIS installer
- SHA-256: 10851bac3fb1688cfe05a350fb61173f3086a259179d5580953bf4ba5f4f03ad
- MD5: 947c6be15fedba232542fdac83445ac8
- Published checksum: the project publishes none for 0.7. The S3 ETag (an MD5 computed by Amazon on upload, 2008-09-18) is 947c6be15fedba232542fdac83445ac8: MATCH. Not signed by the author; the exe has no Authenticode signature.
- Alternative: SumatraPDF-0.7.zip, 822,040 bytes, SHA-256 44810d98143807fda9d9a450d4d8a9ade4a7553cc896cb42b3c3b28b5bc6412d, MD5 65894f015d2223c39a9c8a80eabe8215 (S3 ETag 65894f01...: MATCH). It holds only SumatraPDF.exe, identical (SHA-256 4fd4890a...ea259) to the one inside the installer. No readme or license in either.
- Build date: the exe's PE timestamp is 2007-07-30 05:52 UTC, a day after the release date in the version history (2007-07-28). The author may have rebuilt it; the version is the same.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\sumatrapdf -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". The folder included src\.

## License

- src/SumatraPDF.cpp at the 0.7rel tag: "Copyright Krzysztof Kowalczyk 2006-2007 / License: GPLv2". COPYING at the tag root (read from the Google Code archive of the svn tag, identical to the GitHub copy) is GPL version 2. fitz/COPYING is GPL v2 as well. No "or later" is stated.
- LICENSE.TXT here: a short note naming the components plus the full GPL v2 from the 0.7rel tag.
- GPL v2 allows redistributing unmodified binaries if (s.3) they come with the complete corresponding source or a written offer valid for three years. "Complete" includes the libraries built into the exe.
- **What the source lacks.** The svn tag's `svn:externals` (read from `tags/0.7rel/.svn/dir-prop-base` in the Google Code archive) are:
  `poppler https://poppler-kjk.googlecode.com/svn/trunk/` and `baseutils https://baseutils.googlecode.com/svn/trunk/`.
  - poppler-kjk: the Google Code archive has no project of that name (access denied / missing). 0.7 contains the poppler engine (0.6 notes "fallback to poppler engine", 0.9 notes "removed poppler rendering engine"). **Its source is not available.**
  - baseutils (BSD): its Google Code archive exists, but only as the final trunk, not the July 2007 state. The externals were not pinned to a revision.
- Conclusion: we cannot meet GPL v2 s.3 ourselves, so we do not host it. Following the VLC precedent in CATALOG.TXT, list it as `Availability: external`: the author's own server still offers the unmodified file over plain HTTP.

## Matching source (kept for reference, not published)

- src\sumatrapdf-475026c9e1e1ad9c095c1672e6b359d7d00baf98.zip, 4,665,344 bytes, SHA-256 2d927da457658a98f34f713a0a4ec8932f057cd73aaa78d2d1e1379290e440c2
  from https://github.com/sumatrapdfreader/sumatrapdf/archive/475026c9e1e1ad9c095c1672e6b359d7d00baf98.zip. This commit is the "0.7rel" svn tag: src/SumatraPDF.cpp, src/translations_txt.c and src/strings.txt of the tag (Google Code archive, https://storage.googleapis.com/google-code-archive-source/v2/code.google.com/sumatrapdf/source-archive.zip, read by range requests) are identical to that commit. Contains the UI code, fitz (MuPDF), ext/freetype231, ext/jpeg, ext/zlib, breakpad. Not included: poppler-kjk, baseutils.
  GitHub builds this zip on request; its hash may differ if regenerated.
- src\baseutils-googlecode-source-archive.zip, 235,317 bytes, SHA-256 3a9a0470b2445c5844e92a80d4b14eda7c73be4ee267d2c6d3d699e0c9992d2e, from https://storage.googleapis.com/google-code-archive-source/v2/code.google.com/baseutils/source-archive.zip (final trunk, BSD).
- The binary may have been built a day after the tag revision (see Build date); the exact revision of the shipped exe is unverified.

## Security

Source: NVD API 2.0, keyword "sumatrapdf" (17 results).

NVD lists 0.7 explicitly in the vulnerable configurations of 4:
- CVE-2012-4895 and CVE-2012-4896: heap-based buffer overflows, "allows remote attackers to execute arbitrary code via a crafted PDF document" (before 2.1), CVSS2 9.3.
- CVE-2009-4117: stack-based buffer overflows in MuPDF pdf_shade4.c (type 4-7 shadings), SumatraPDF before 1.0.1, CVSS2 9.3.
- CVE-2009-1605: heap overflow in MuPDF loadexponentialfunc (mupdf-20090223), CVSS2 9.3 / CVSS3 5.4. NVD lists 0.7, but the report names a 2009 MuPDF; whether the 2007 fitz code in 0.7 has the same function was not verified.
Not applicable: CVE-2026-23951 ("all versions", Mobi reader; 0.7 has no Mobi support) and the CVEs for 2.x/3.x features (CHM, DjVu, updater, search path).
Not counted: 0.7 also contains a 2007 poppler/Xpdf fork and FreeType 2.3.1, which have many later CVEs (for example the Xpdf/poppler CVE-2007-3387 family); not mapped here.

Summary: 4 known CVEs (NVD), worst CVE-2012-4895 / -4896 (code execution from a crafted PDF, CVSS2 9.3). Opening any untrusted PDF is risky.

## Install behaviour

- Installer type: NSIS 2 (7-Zip reports `Type = Nsis, SubType = NSIS-2`; the script src/installer.nsi is in the 0.7rel source). Contents: SumatraPDF.exe (821,760 bytes) and the uninstaller.
- Silent install: standard NSIS `/S`; `/D=<folder>` last. The project does not document it for 0.7. Pages are components, directory, instfiles; both sections are read-only, so `/S` installs everything.
- Default folder: `$PROGRAMFILES\SumatraPDF`; stored in HKLM `Software\SumatraPDF\Install_Dir`.
- Uninstaller: yes. HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\SumatraPDF`, DisplayName **"Sumatra PDF reader"**, UninstallString `"$INSTDIR\uninstall.exe"`; `Uninstall.exe /S` for silent removal.
- Side effects: Start Menu folder "SumatraPDF" with SumatraPDF and Uninstall shortcuts. The installer does not associate .pdf; the program itself offers to (runtime behaviour, not tested).
- Zip alternative: one file, SumatraPDF.exe at the root; `unzip {dir}` plus a shortcut would work.

## Verification notes

- Verified by opening or downloading: sumatrapdfreader.org version history and download-prev page, archived author download pages (2007-2009) and sumatra.js (2013), GitHub commits d97dbe8ca441, 24f23b64c97f and 475026c9e1e1 and the tree at 24f23b64, the Google Code archive central directory and the 0.7rel tag's .svn/dir-prop-base, .svn/entries, COPYING and installer.nsi, the 0.7-0.9 binaries' import tables, the MSFN thread, and NVD records.
- From search snippets only: Wikipedia's GPLv2-to-v3 date; the OSR KernelEx notes (partly from the cached page in research\import\cache).
- Not verified: running on 95/98/ME (no VM interaction); which poppler-kjk revision is inside; whether 0.8/0.8.1 are usable apart from the missing menu.
