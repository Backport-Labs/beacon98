# AbiWord 2.4.6 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: AbiWord (AbiSource community), package id `abiword`
- Version: 2.4.6 (stable, bugfix release; files dated 2006-11-08)
- License: GNU GPL version 2 or later
- Recommendation: **2.4.6**. It is the version AbiSource itself told Windows 95/98/ME users to keep using once 2.6 came out. 2.5.2, which some lists name as "the last for Windows 98", is a development snapshot (the project's own words), and no primary source says it runs on 9x (see below). 2.6.x and 2.8.x do not run on stock 9x. 2.8.6 runs only with KernelEx plus the Microsoft Layer for Unicode, according to a community wiki page on abisource.com. Since the requested target is stock Windows 98, no KernelEx variant is proposed.
- Important: **abisource.com is gone.** On 2026-09-29, www.abisource.com, abisource.com and the www.nl.abisource.com mirror all failed DNS lookup (SERVFAIL from the local resolver and from 1.1.1.1). There is no other official mirror of the Windows builds: SourceForge project "abiword" only holds OldFiles and an SDK, and GitLab (gitlab.gnome.org/World/AbiWord) has source only, with no release-2.4.6 tag at the URL tried. All files were therefore taken from the Internet Archive's copy of abisource.com/downloads/. That is acceptable under our rules because the license (GPL) allows sharing and the publisher's server is gone. Every file matches the MD5SUM files that AbiSource published, which were also retrieved from the archive.

## Windows 9x support evidence

All of the following were verified by downloading the archived pages (web.archive.org `id_` raw captures):

- Release notes 2.6.3, 2.6.4, 2.6.5, 2.6.6 and 2.6.8 (http://www.abisource.com/release-notes/2.6.x.phtml) all contain:
  "Note for Windows 95, 98 and ME users: AbiWord 2.6 is currently not available for your operating system. Please continue using AbiWord 2.4.6 instead." (with a link to /downloads/abiword/2.4.6/Windows/).
  The 2.6.0 and 2.6.2 notes (captures of 2008-04-01 and 2008-04-11) do not contain that note. 2.6.0 says only that the Windows equation plugin is unavailable and that users who need it should "continue using AbiWord 2.4.6".
- Release notes 2.5.0, 2.5.1 and 2.5.2: "please be aware that is a development snapshot and is not expected to be stable in any sort of way." 2.5.2 is "the third snapshot of the development that will lead to AbiWord 2.6". None of the 2.5.x notes mentions Windows 9x.
- Release notes 2.8.0 and 2.8.6: no mention of Windows 9x.
- AbiWiki "Install on Win98" (http://www.abisource.com/wiki/Install_on_Win98, capture of 2025-07-16, page last modified 6 January 2011):
  "Abiword developers have oficially dropped win9x support. You can install an old version (2.4.6 or older) but you will miss some great new features. Is possible to install and run Abiword 2.8.6 on Win98 [...] Download and install [...] MS unicode layer for Win9x [...] Download and Install kernelex [...] If needed, copy msvcp90.dll and msvcr90 to c:\windows\system". The page cites bugzilla.abisource.com bug 12923, which I could not open (the archive refused connections at that moment). This is a community wiki page, not a release statement.
- readme.txt inside abiword-setup-2.4.6.exe (extracted with the host's 7-Zip; the installer was not run): "At the present time, AbiWord is supported on Windows (including Windows 95 through Windows XP)".
- help\en-US\info\inforequirements.html inside the same installer, for Microsoft Windows: "486dx or better processor / At least 16MB RAM / Windows 95b or later". So the original Windows 95 release (not OSR2) is not claimed.
- MSFN forum thread "Abiword no longer for 9x/ME" (msfn.org/board/topic/117959, opened through WebFetch, which returns a summary rather than the raw page): 2008 posts repeat the 2.6 note, and one user reports that 2.6.5 with KernelEx 0.3.6 gave "Microsoft Visual C++ Runtime Error". This is community evidence only.
- 2.5.2 on Windows 98 was **not verified.** I could find no primary statement either way; the search snippets that say "2.5.2 supported Windows 98" come from download-mirror sites (oldapps.com and similar), not from AbiSource. As a static check only, I extracted AbiWord.exe from the archived abiword-setup-2.5.2.exe (MD5 d572261e994a4c215bc24b6d562136c5 matches AbiSource's MD5SUM) into a temporary folder. It now links glib, gobject, libgsf and libxml2 as DLLs and imports `GetCommandLineW` and `SHELL32!CommandLineToArgvW`, which 2.4.6 does not import. Whether that breaks it on 98 is unknown. The file was only inspected, never run, and was not kept in the package folder.
- Static check of 2.4.6 (not a test): libAbiWord.dll imports only system DLLs present on 98 (KERNEL32, USER32, GDI32, ADVAPI32, COMCTL32, COMDLG32, SHELL32, OLE32, VERSION, WINSPOOL.DRV, msvcrt.dll) plus its own zlib1.dll. Its wide-character imports (CreateWindowExW, ExtTextOutW, GetCharacterPlacementW and others) are exports that Windows 98 also has. usp10.dll appears only as a string, which fits dynamic loading.
- Windows ME: named in the 2.6 release-note sentence above as a system that should use 2.4.6, and covered by "Windows 95 through Windows XP". Not tested.

## Download

- Official location (dead): http://www.abisource.com/downloads/abiword/2.4.6/Windows/. An archived directory listing (capture of 2006-11-16) shows three files: abiword-plugins-impexp-2.4.6.exe (697K), abiword-plugins-tools-2.4.6.exe (721K) and abiword-setup-2.4.6.exe (5.2M), all dated 08-Nov-2006.
- Retrieved from: https://web.archive.org/web/20061207014735id_/http://www.abisource.com:80/downloads/abiword/2.4.6/Windows/abiword-setup-2.4.6.exe
- File: abiword-setup-2.4.6.exe, 5,410,865 bytes (32-bit NSIS 2.25 installer)
- SHA-256: 685a82ca2a9c56861e5ca22b38e697791485664c36ad883f410dac9e96d09f62
- MD5: d06198b0bb87c5981e9fc88e1ee4e78e
- Published checksum: AbiSource's /downloads/abiword/2.4.6/Windows/MD5SUM (archived 2007-03-17, saved here as MD5SUM.Windows.txt) lists d06198b0bb87c5981e9fc88e1ee4e78e: **MATCH**. There is no signature, and the MD5SUM itself came through the archive.
- Authenticode: not signed.
- Plugin installers (separate downloads from the same folder, also saved here, **not proposed for the catalog**):
  - abiword-plugins-impexp-2.4.6.exe, 713,459 bytes, SHA-256 9b5987327f0c0840249748b378d0f84d79457fe9b4cad84cac693e8c0afcdf31, MD5 bd0986706608b6c3fd8bf8087fa7dfbe: MATCH. It contains import/export filters (OpenDocument, OpenWriter, WordPerfect, DocBook, LaTeX, XSL-FO and others) and bundles libwpd-0.8.dll and libwpd-stream-0.8.dll (LGPL; their source is **not** in abiword-2.4.6.tar.bz2).
  - abiword-plugins-tools-2.4.6.exe, 738,111 bytes, SHA-256 ce04691bc23f04cf0aae4ab1bd1728734c02b99be24baf32c16887cf60c1be17, MD5 7ee4f9fade33dd0655f0801e3a04d3ab: MATCH. It contains MathView (equations), Grammar, Google, Wikipedia, Babelfish and other tools, and bundles liblink-grammar-4.dll, whose source is **not** in the tarball.
  - Both plugin installers **download dependencies at install time** from http://www.abisource.com/downloads/dependencies/ (libiconv-1.9.1, gettext-runtime-0.13.1, glib-2.4.7, libgsf-1.11.1, libxml2-2.6.19, libmathview-0.7.6-1), according to pluginImportersExporters.nsi and pluginTools.nsi in the source. That server is gone, so the sections that need these (at least OpenDocument/OpenWriter and MathView, which import libgsf, gobject and libmathview) cannot install. Packaging the plugins would need those runtime zips and their sources, which is a separate task.
- Also existing (not downloaded): a 2.4.6 source tar.gz (29M), and Ubuntu/Mac folders. There was never a zip or MSI build for Windows 2.4.6.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\abiword -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". This covers all three installers and src\.

## License

- copying.txt inside abiword-setup-2.4.6.exe is the GNU GPL version 2. readme.txt ("Legalese") says: "This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License [...] either version 2 of the License, or (at your option) any later version." SPDX: GPL-2.0-or-later.
- LICENSE.TXT here holds a short header written by me (a pointer to the sources and the list of bundled libraries), then the readme Legalese section, then the full copying.txt.
- Redistributing the unmodified binaries is allowed. Conditions: include the license, and accompany the binary with the complete corresponding source or an offer of it (GPL-2 s.3). We host the source next to the binary.
- Trademarks: readme.txt says AbiSource, AbiWord and AbiSuite are trademarks (of AbiSource, Inc.; the later release notes say Dom Lachowicz). Distributing the unmodified program under its own name is ordinary GPL redistribution; we should not use the logo as our branding.

## Matching source (hosted)

- URL (dead): http://www.abisource.com/downloads/abiword/2.4.6/source/abiword-2.4.6.tar.bz2
- Retrieved from: https://web.archive.org/web/20150709091246id_/http://www.abisource.com/downloads/abiword/2.4.6/source/abiword-2.4.6.tar.bz2
- File: src\abiword-2.4.6.tar.bz2, 24,994,889 bytes
- SHA-256: 1ca509814d1ce939c98f2776f95351a2a6ea216d12c20be30d40eefd13f43020
- MD5: 8ed5fb282b9741aca75b9e47500d39a1. AbiSource's /2.4.6/source/MD5SUM (archived 2007-06-05, saved as src\MD5SUM.source.txt) lists 8ed5fb282b9741aca75b9e47500d39a1: **MATCH**.
- Contents (listed, not built): abi/ (AbiWord), abiword-plugins/, abiword-docs/, abidistfiles/, and these bundled libraries: expat (1.95.7), fribidi (0.10.4), libiconv (1.9), libpng (1.2.5), popt (1.6.2), wv (configure.ac 1.0.2, configure.in 1.0.3), zlib (1.2.1), plus MSVC6/MSVC71 project files and the NSIS installer scripts (abi/src/pkg/win/setup/).
- The Windows build links these statically into libAbiWord.dll. Version strings found in the binary: "libpng version 1.2.5", "fribidi 0.10.4", "expat_1.95.7", plus libiconv, popt and wv symbols. All of these are in the tarball.
- **Not in the tarball: zlib1.dll.** The shipped zlib1.dll (dated 2005-07-20) contains "deflate 1.2.3" and "inflate 1.2.3", while the tarball holds zlib 1.2.1. I added the zlib 1.2.3 source:
  - URL: https://zlib.net/fossils/zlib-1.2.3.tar.gz (zlib's official archive of old releases)
  - File: src\zlib-1.2.3.tar.gz, 496,597 bytes, SHA-256 1795c7d067a43174113fdf03447532f373e1c6c57c08d61d9e4e9be5e244b05e, MD5 debc62758716a169df9f62e6ab2bc634 (no published checksum was compared).
  - The zlib license does not require source to be offered; I include it so the offer is complete.
- The C runtime is the system msvcrt.dll, which Windows 98 already has; none is bundled.

## Security

Sources: NVD API 2.0 keyword search "abiword" (7 results, all opened), individual NVD records, and the 2.4.6 release notes.

AbiWord's own CVEs:
- CVE-2005-2964 and CVE-2005-2972 (RTF import stack overflows): fixed before 2.2.11. **Not affected.**
- CVE-2006-4513 (wvWare integer overflows, i.e. iDefense IDEF1613/IDEF1614): the 2.4.6 release notes say "Fix IDEF vulnerabilities IDEF1613 and IDEF1614 in the MS Word import library wvWare". **Fixed in 2.4.6.**
- CVE-2007-5395 (Link Grammar stack overflow, CVSS2 10.0, "as used in AbiWord Link Grammar 4.2.4"): affects only the Grammar plugin in abiword-plugins-tools-2.4.6.exe (liblink-grammar-4.dll). **Not part of the proposed package.**
- CVE-2006-3376 (libwmf): the Windows build has no libwmf (no string or DLL found). Probably not applicable; not proven.
- CVE-2009-3938 (pdftoabw/poppler) and CVE-2017-17529 (BROWSER variable, 3.0.x on Unix): not applicable.

Bundled libraries (they apply to 2.4.6 because the vulnerable versions are linked in; this list is not complete):
- libpng 1.2.5: CVE-2004-0597 (multiple buffer overflows, "libpng 1.2.5 and earlier", CVSS2 10.0), plus the other 2004+ libpng advisories. AbiWord loads PNG images from documents.
- expat 1.95.7: CVE-2016-0718 (malformed input, possible code execution, CVSS3 9.8), CVE-2009-3720 and later expat CVEs.
- zlib 1.2.3 (zlib1.dll): e.g. CVE-2018-25032 and CVE-2016-9841.
- fribidi 0.10.4 and wv (MS Word import): no specific CVE checked.

Summary: no known unfixed AbiWord CVE in the core program. At least 5 known CVEs apply through bundled libraries; the exact count was not established. The worst are CVE-2004-0597 (libpng, CVSS2 10.0) and CVE-2016-0718 (expat, CVSS3 9.8). They need the user to open a crafted document or image. The Word (.doc) importer is old wvWare code from 2006.

## Install behaviour

- Installer type: NSIS 2.25 (7-Zip reports "SubType = NSIS-2.25"), Modern UI with a language selection. The script is abi/src/pkg/win/setup/NSISv2/AbiWord.nsi and its .nsh includes in the source tarball. The binary's own compiled script was not decompiled; the uninstaller name found in the binary (UninstallAbiWord2.exe) and the plugin DLLs used (StartMenu, LangDLL, Dialer, NSISdl) match that NSISv2 script.
- Silent install: standard NSIS `/S`. The script's own help text (abi_parsecmdline.nsh) says: "/S silent install", "/D=path sets default install dir, MUST be last option, No quotes, supports spaces", "/INSTALLTYPE=# sets default install type to nth option, e.g. 0=Typical", plus /OPT_ENABLE_DOWNLOADS and /OPT_DISABLE_DOWNLOADS.
- **Caveat for silent install (from the script, not tested):** .onInit always calls `Dialer::AttemptConnect` to decide whether the optional downloadable dictionaries can be offered. If the computer is offline it shows `MessageBox MB_OK|MB_ICONSTOP "Cannot connect to the internet."` without a /SD default, so even a `/S` install may stop at that box until the user clicks OK. If IE3's wininet is missing it shows "Please connect to the internet now." With a working network connection nothing is downloaded in the default "Typical" install type: download sections are only in "Full" (dictionaries) and "Full plus Downloads". Whether MUI_LANGDLL_DISPLAY shows the language box under /S was not verified. This should be tested in the VM.
- Default folder: `$PROGRAMFILES\AbiSuite2` (i.e. C:\Program Files\AbiSuite2), with the program in AbiSuite2\AbiWord\bin\AbiWord.exe. The folder is stored in HKLM `SOFTWARE\AbiSuite\AbiWord\v2` "Install_Dir".
- Uninstaller: yes. `$INSTDIR\UninstallAbiWord2.exe` is registered at HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\AbiWord2` with DisplayName `"${PRODUCT} ${VERSION} (remove only)"`, which for this build is **"AbiWord 2.4.6 (remove only)"** (from abi_util_reg_uninst.nsh; the VERSION is supplied at build time, so this is inferred rather than read from the binary).
- Side effects (Typical): Start Menu group, help, templates, clipart, the English dictionary (american.hash is included in the installer), and file associations for .abw, .awt and .zabw. .doc and .rtf associations happen only in "Full".
- Installed size: the installer holds 480 files, 20,414,052 bytes uncompressed, for all components.

## Verification notes

- Verified by opening or downloading: the Wayback CDX listings of abisource.com/downloads/abiword/; the release notes 2.4.0, 2.4.6, 2.5.0, 2.5.1, 2.5.2, 2.6.0, 2.6.2 to 2.6.6, 2.6.8, 2.8.0 and 2.8.6; the AbiWiki Install_on_Win98 page; the 2.4.6 Windows and source directory listings and MD5SUMs; all three 2.4.6 installers (contents listed with 7-Zip; readme.txt, copying.txt, inforequirements.html and binaries extracted to a temporary folder and never run); the source tarball (listed; NSIS scripts and library headers extracted); PE import tables and version strings; the NVD records named above; the archived 2.5.2 setup (static check only).
- Only from search snippets or WebFetch summaries: that abisource.com has been dead "since September", the MSFN thread content, and the "2.5.2 supports Windows 98" claims from download sites.
- Not verified: running anything on Windows 95/98/ME (no VM interaction); bugzilla bug 12923; whether 2.5.2 runs on 98; the silent-install behaviour of the language box and the offline MessageBox.
