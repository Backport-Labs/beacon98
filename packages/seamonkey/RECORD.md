# SeaMonkey 1.1.19 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: seamonkey
- Package: SeaMonkey internet suite (browser, mail/news, Composer, ChatZilla, DOM Inspector, Venkman), SeaMonkey project; built and published on mozilla.org infrastructure
- Version: 1.1.19 (released 2010-03-16, the final 1.x release; Gecko 1.8.1.24, GRE ID 1.8.1.24_2010022818)
- License: MPL 1.1 / GPL 2.0 / LGPL 2.1 tri-license (the installer itself shows MPL 1.1 with the NPL amendments)
- Recommendation: 1.1.19. It is the last SeaMonkey release whose own system requirements list Windows 95/98/Me; 2.0 dropped them in writing. Hosting is allowed by the copyright license; see "Trademark" for one open point (Mozilla's 2009 trademark policy on meta-installers).

## Windows 9x support evidence

- https://www.seamonkey-project.org/releases/seamonkey1.1.19/installation (opened), "Windows System Requirements":
  "Windows 95*, 98, 98SE, Windows Me, Windows NT 3.51, Windows NT 4.0, Windows 2000, Windows XP or Windows 2003 *with DCOM for Windows 95. Intel pentium class processor (233 MHz or faster recommended) 64 MB RAM 100 MB of free hard disk space"
- https://www.seamonkey-project.org/releases/seamonkey2.0/ (opened), "What's New in SeaMonkey 2.0":
  "Support for Windows 95, 98, Me and NT 4 was dropped."
- https://www.seamonkey-project.org/news (opened), entry "March 16, 2010 Support For SeaMonkey 1.x Dropped":
  "the SeaMonkey project is discontinuing support for the SeaMonkey 1.x series today in favor of SeaMonkey 2.0 ... For the few who can't afford that, a last 1.x release is available. SeaMonkey 1.1.19 does fix a few security issues, but not all known security vulnerabilites, some of which may even be grave."
- https://www.seamonkey-project.org/releases/ (opened) lists 1.1.19 as the highest 1.x; the next line is 2.0 Alpha 1 and up. So 1.1.19 (released after 2.0) is the last version for 9x. This confirms the MSFN statement from primary sources.
- Windows 95: supported, but needs DCOM95 (Microsoft's DCOM update), per the requirement above. Windows 98 and 98 SE include DCOM. Windows Me: supported.
- KernelEx: not needed. (SeaMonkey 2.0.x on 9x would need KernelEx; that was not researched or verified here.)
- The installer PE header says Subsystem Version 4.0, x86, built 2010-03-01 (read with 7-Zip, not executed).

## Download

- Directory: https://archive.mozilla.org/pub/seamonkey/releases/1.1.19/ (opened; the release has no windows/ subfolder, files are at the top)
- URL: https://archive.mozilla.org/pub/seamonkey/releases/1.1.19/seamonkey-1.1.19.en-US.win32.installer.exe
- Plain HTTP also works: `curl.exe -sS -I --http1.0 http://archive.mozilla.org/pub/seamonkey/releases/1.1.19/seamonkey-1.1.19.en-US.win32.installer.exe` gives 200 OK, Content-Length 13266944, no redirect (same for http://ftp.mozilla.org/pub/seamonkey/releases/1.1.19/...).
- File: seamonkey-1.1.19.en-US.win32.installer.exe, 13,266,944 bytes (32-bit x86 full offline installer)
- SHA-256: 34dca09d77e11f6b9f0275a51aa3a90b1e2185f915e50e0b5cd0deea56d2d1b6
- MD5: 97146cc4223f5873c4ba02b5e317fdb1
- Published checksum: the release directory has only MD5SUMS (no SHA1SUMS, no signatures/.asc). MD5SUMS lists `97146cc4223f5873c4ba02b5e317fdb1  ./seamonkey-1.1.19.en-US.win32.installer.exe`: MATCH. The server's ETag and x-goog-hash md5 give the same value.
- Authenticode: not signed.
- Alternatives in the same directory (not downloaded; MD5 from MD5SUMS):
  - seamonkey-1.1.19.en-US.win32.stub-installer.exe (264 KB, net installer, MD5 ee438e786b803f4b4acbae6a46bf6c8d). Downloads components from mozilla.org servers at install time; not suitable.
  - seamonkey-1.1.19.en-US.win32.zip (11 MB, MD5 1181ed084c2069362be2291b235930ea). The README says it "contains all of dist/bin from an optimized build ... includes many debug and test files, and does not include an installer." Could be an `unzip` package, but the installer is the normal choice.
  - Localized builds are under contrib-localized/.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\seamonkey -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0), covering the installer and the source archive: "found no threats".

## License

- The installer's own license dialog (LICENSE.TXT resource inside the installer, decompressed and read) is the Mozilla Public License 1.1 with the Netscape Public License amendments. There is no EULA in this installer.
- about:license of this version (mozilla/xpfe/global/resources/content/license.html in the source) says: "Most is available under any one of the following: the Mozilla Public License (MPL), the GNU General Public License (GPL) and the GNU Lesser General Public License (LGPL). That is, you may copy and distribute such software according to the terms of any one of those three licenses." The rest is under permissive licenses whose notices it reproduces (NPRuntime, bspatch, cairo, expat, JNIC, Java Embedding Plugin, Myspell, OpenVision, UC, xregion, zlib/bzip2/libpng notices).
  - It also says: "Official binaries of this product released by the Mozilla Foundation are made available under the corresponding EULA." This is shared toolkit text; the SeaMonkey 1.1.19 installer shows no EULA, only the MPL. Today's SeaMonkey site says current release binaries are under the "SeaMonkey End-User License Agreement" v1.2 (https://www.seamonkey-project.org/legal/eula, opened). That EULA grants a use license and does not mention redistribution, and says "Nothing in this Agreement will be construed to limit any rights granted under the Open Source Licenses." It was written for SeaMonkey e.V. releases, not for this 2010 build. I consider 1.1.19 redistributable under the MPL/GPL/LGPL, but note this as a point to confirm.
  - "Exceptions" in about:license: "The Talkback crash-reporting module (Copyright 1998-2005 SupportSoft, Inc. All Rights Reserved.)" and "Image files containing the trademarks and logos of the Mozilla Foundation". I checked the installer: TALKBACK.XPI contains only bin/readme.txt and install.js (no Talkback binary), so the proprietary Talkback is NOT in this build.
- Other bundled files not in the source archive: XPCOM.XPI contains Microsoft's msvcrt.dll and msvcirt.dll (VC++ 6 runtime). Its install.js copies them to the Windows SYSTEM folder only if they do not exist ("install msvcrt.dll *only* if it does not exist"). These are Microsoft redistributable runtime files, not open source. Windows 98 already has both, so they do nothing there.
- LICENSE.TXT (129,857 bytes, SHA-256 f8fe6dc8467172f744ea4bcbc4cf45f276638a9d1b522a2b2bd778c2aaf16322) has three parts: the installer's license (MPL 1.1 + NPL amendments), about:license as plain text (includes the full GPL 2 and LGPL 2.1 texts and all third-party notices), and mozilla/LEGAL.
- Redistributing the unmodified installer is allowed under any of the three licenses. Conditions:
  - include the license text;
  - MPL 1.1 s.3.2/3.6 and GPL/LGPL: the source must be available. We host the matching source:

## Matching source (hosted)

- URL: https://archive.mozilla.org/pub/seamonkey/releases/1.1.19/seamonkey-1.1.19.source.tar.bz2
- File: src\seamonkey-1.1.19.source.tar.bz2, 36,272,561 bytes
- SHA-256: 665e0998e7af516826b12d943206de9d9ed6d341503660b72251821fccf1932e
- MD5: cd1680aab7b8732551e6ace97d0f7eb8. MD5SUMS lists cd1680aab7b8732551e6ace97d0f7eb8: MATCH.
- The README says the binaries were built from CVS tag SEAMONKEY_1_1_19_RELEASE; the tarball is that tree (mozilla/, dated 2010-02-28/03-01) including NSPR, NSS 3.12.3.1, LDAP C SDK (directory/), libpng 1.2.35, the GRE and the xpinstall installer (xpinstall/wizard). A .tar.gz of the same source (MD5 f8289fb019ef1cf31695b0c45d801167) also exists; not downloaded.
- Not in the source: msvcrt.dll/msvcirt.dll (Microsoft), see above.

## Trademark

- Owner today: "SeaMonkey and the SeaMonkey logo are registered trademarks of the SeaMonkey Association (SeaMonkey e.V.)" (site footer).
- SeaMonkey Trademark Rules, https://www.seamonkey-project.org/legal/trademark (opened): "Trademark uses not covered by this document have to follow the Mozilla trademark policy unless explicitly granted by the SeaMonkey Council." It covers logos, desktop backgrounds, links and domains; it does not mention redistributing binaries. It asks: "Before using any of these marks outside the scope of fair use ... please send an email to seamonkey-council@mozilla.org".
- Current Mozilla Trademark Guidelines, https://www.mozilla.org/en-US/foundation/trademarks/policy/ (opened): allowed without permission: "Use Mozilla wordmarks in text to truthfully refer to and/or link to unmodified Mozilla programs, products, services and technologies." ... "All other uses of a Mozilla trademark require our prior written permission." There is no longer a specific section on redistributing binaries.
- Mozilla Trademark Policy in force when 1.1.19 was released ("Updated: October 30, 2009"), Internet Archive copy http://web.archive.org/web/20110104124407/http://www.mozilla.org/foundation/trademarks/policy.html (opened), "Unaltered Binaries":
  "You may distribute unchanged official binaries (i.e., the installer file available for download for each platform (code + config) and not the program executable) downloaded from www.mozilla.com or www.mozilla.org to anyone in any way, subject to governing law, without receiving any further permission from Mozilla. If you want to distribute the unchanged official binaries using the Mozilla Marks, you may do so, without receiving any further permission from Mozilla, as long as you comply with this Trademark Policy and you distribute them without charge. However, you must not remove or change any part of the official binary, including the Mozilla Marks."
  and: "if you are distributing Mozilla binaries yourself, and wish to use the Mozilla Mark(s), you may not (a) disable, modify or otherwise interfere with any installation mechanism contained in a Mozilla product; (b) use any such installation mechanism to install any plug-ins, themes, extensions, software, or items other than the Mozilla product; or (c) use or provide any program, mechanism or process (other than an installation mechanism contained in the Mozilla product) to install such product. Any use of a meta-installer would require our prior written permission."
- Assessment: hosting the unchanged official installer free of charge was explicitly allowed. Beacon only runs the product's own installer with its own `-ms` switch, and does not change it; but under the 2009 wording a package manager could be read as a "meta-installer". That clause is no longer in Mozilla's current guidelines, and the marks now belong to SeaMonkey e.V. To be certain, either email seamonkey-council@mozilla.org for a one-line permission, or list the package as `Availability: external` pointing to http://archive.mozilla.org/ (works over plain HTTP 1.0). ENTRY.TXT is drafted as hosted, with the external line in a comment.

## Security

Sources: Mozilla's known-vulnerabilities pages for SeaMonkey 1.1, SeaMonkey 2.0 and SeaMonkey (opened and parsed), mfsa2010-07, the SeaMonkey news post, and NVD API 2.0.

- What 1.1.19 fixed: only MFSA 2010-06 (scriptable plugin in mail) and MFSA 2010-07, which "took fixes from previously fixed memory safety bugs in newer Mozilla-based products and ported them to the Mozilla 1.8.1 branch" (CVE-2010-0161, CVE-2010-0163, CVE-2009-3075, CVE-2009-3072, CVE-2009-2463).
- Count: 477 distinct Mozilla Foundation Security Advisories are listed as fixed in SeaMonkey 2.0 to 2.38 and not listed as fixed in any SeaMonkey 1.1.x (230 critical, 125 high, 96 moderate, 26 low/medium). This is only an estimate: many concern code that 1.1's Gecko 1.8.1 does not have (WebGL, Web Workers, HTML5 video, etc.), while Mozilla's pages do not list 2.1/2.2 and advisories after 2.38 are only on seamonkey-project.org. NVD: cpeName cpe:2.3:a:mozilla:seamonkey:1.1.19 gives 481 CVEs, mostly because of "SeaMonkey before 2.x" ranges; not all apply either. The project itself said 1.1.19 does not fix "all known security vulnerabilites, some of which may even be grave."
- Worst ones that do apply to 1.1.19:
  - CVE-2009-3373 (MFSA 2009-56): heap overflow in the GIF color map parser, "SeaMonkey before 2.0", CVSS2 10.0. Not in 1.1.19's fixes. Remote code execution from a web page or mail.
  - CVE-2011-2982: memory corruption in the browser engine, "SeaMonkey 1.x and 2.x", CVSS2 10.0.
  - CVE-2010-1205: libpng progressive-reader buffer overflow (before 1.2.44), CVSS3 9.8. 1.1.19 bundles libpng 1.2.35 (png.h in the source).
  - CVE-2011-2983: same-origin bypass via RegExp.input, names "SeaMonkey 1.x".
  - CVE-2010-3131 (MFSA 2010-52): DLL hijacking via files opened from a folder (fixed in 2.0.7).
- Practical: NSS 3.12.3.1 predates the TLS renegotiation fix (CVE-2009-3555, NSS 3.12.5) and supports no TLS 1.1/1.2, so most current HTTPS sites will not open at all.

## Install behaviour

- Installer type: Mozilla xpinstall "Setup" wizard (the classic Mozilla installer). The exe is a stub whose PE resources hold SETUP.EXE, SETUPRSC.DLL, CONFIG.INI, INSTALL.INI, LICENSE.TXT and the .xpi component archives, each zlib-compressed. Read with 7-Zip (-tPE) and decompressed in a temp folder; nothing was run.
- Silent install: `-ms` (silent) or `-ma` (auto, shows progress). CONFIG.INI documents the run modes ("Silent - Show no dialogs at all. It will install product using default values."), and SETUP.EXE contains the `-ms`/`-ma` switch strings and "Install mode: Silent"; the installer itself passes `-mmi -ms` to the embedded GRE installer. Same as RetroZilla (`exe -ms`). In silent mode the defaults are "Complete" (Default Setup Type=Setup Type 1), not default browser, no home page/search changes, Quick Launch off (Turbo Mode=FALSE).
- Default folder: `[PROGRAMFILESDIR]\mozilla.org\SeaMonkey` (CONFIG.INI `Path=`), i.e. C:\Program Files\mozilla.org\SeaMonkey. Start Menu folder "SeaMonkey".
- Also installs a private Gecko Runtime Environment to `[COMMONFILESDIR]\mozilla.org\GRE\1.8.1.24_2010022818` via gre-win32-installer.exe, registered separately under HKLM `...\Uninstall\GRE (1.8.1.24_2010022818)` (DisplayName "Gecko Runtime Environment (1.8.1.24_2010022818)"). It copies SeaMonkeyUninstall.exe to the Windows folder and to `<install>\uninstall`, and installs msvcrt.dll/msvcirt.dll into SYSTEM only if missing.
- Uninstaller: yes. Key HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\SeaMonkey (1.1.19)`, DisplayName `SeaMonkey (1.1.19)`, UninstallString `[WINDIR]\SeaMonkeyUninstall.exe /ua "1.1.19 (en)"` (from CONFIG.INI). The release notes say "go to Settings/Control Panel/Add Remove Programs and choose SeaMonkey 1.1.19"; the registry value is "SeaMonkey (1.1.19)", which is what Beacon should match. Whether the SeaMonkey uninstaller also removes the GRE entry is unknown.
- Release notes: "It is recommended that you uninstall previous versions of SeaMonkey before installing" and "Do not install over an old SeaMonkey version." Profiles on 9x go to C:\Windows\Application Data\Mozilla\Profiles\ (or the per-user profile folder with log-in).

## Verification notes

- Verified by opening or downloading: the archive.mozilla.org release directory, README and MD5SUMS; the 1.1.19 release notes, installation page and known-issues page; the 2.0 release notes; the SeaMonkey releases page and news page; SeaMonkey legal, EULA and trademark pages; the current Mozilla trademark guidelines and the archived 2009 policy; Mozilla known-vulnerabilities pages and mfsa2010-07; NVD records (CPE query and single CVEs). Installer resources (CONFIG.INI, INSTALL.INI, LICENSE.TXT, XPI listings, install.js, GRE CONFIG.INI) and source files (LICENSE, LEGAL, license.html, png.h, nss.h) were extracted to a temp folder and read.
- Not verified: running on Windows 95/98/ME (no VM interaction); that `-ms` completes without any dialog on 98 (standard for this installer family, and used by the RetroZilla entry, but not tested here); whether the GRE is removed with SeaMonkey; the exact security count affecting Gecko 1.8.1.
- Open: the trademark / meta-installer question above, and the generic "EULA" sentence in about:license.

## Decision update (2026-09-29, after the Firefox and Thunderbird checks)

ENTRY.TXT now uses `Availability: external` by default. Mozilla's current Distribution Policy
(https://www.mozilla.org/en-US/foundation/trademarks/distribution-policy/, opened 2026-09-29) defines
"Mozilla software" as "software developed and/or distributed by Mozilla or by one of its affiliates"
and says "When distributing you must distribute the most recent version of Firefox and other Mozilla
software." SeaMonkey 1.1.19 was released and is still distributed from mozilla.org, and "SeaMonkey"
is a Mozilla Foundation trademark, so hosting 1.1.19 is not certain to be allowed. Firefox 2.0.0.20
and Thunderbird 2.0.0.24 were listed as external for the same reason. The hosted lines are kept as
comments in ENTRY.TXT in case the SeaMonkey Council (seamonkey-council@mozilla.org) gives written
permission. The plain-HTTP download from archive.mozilla.org was already tested (200 OK over HTTP/1.0).
