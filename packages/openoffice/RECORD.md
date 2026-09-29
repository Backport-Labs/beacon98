# OpenOffice.org 2.4.3 - Beacon 98 record

- Date checked: 2026-09-29
- Package: OpenOffice.org (Sun Microsystems / OpenOffice.org community; the name and archive now belong to the Apache Software Foundation)
- Package id: openoffice
- Version: 2.4.3 (build OOH680_m21, "Build:9421"; files dated 2009-08-21/24; announced early September 2009)
- License: GNU LGPL version 2.1 only (LGPL-2.1-only), plus third-party components under their own licenses. NOT LGPL-3.0: OOo moved to LGPLv3 with 3.0 beta.
- Recommendation: 2.4.3, not 2.4.2. Both support 98/ME, but 2.4.3 is the last 2.x release and fixes CVE-2009-0200/0201 (Word import heap overflows) and CVE-2009-2414/2416 (libxml2), which 2.4.2 still has. There is no 2.4.4: the Apache archive's `incubator/ooo/stable/` ends at 2.4.3 before 3.x.

## Windows 9x support evidence

- readme_en_US.txt inside the 2.4.3 installer itself (extracted from openoffice.org-core02.cab, not run), section "System Requirements":
  "- Microsoft Windows 98, ME, 2000, XP or Vista / - Pentium compatible PC / - 128 MB RAM (256 MB RAM recommended) / - 650 MB including Sun JRE ... available hard disk space during installation / - 500 MB Disk space needed after installation is complete when deleting temporary installer files."
  The same readme: "Note for Windows 98 users only: If you choose to install Java during the OpenOffice.org installation program, the installer will ask you to reboot your system."
- https://www.openoffice.org/dev_docs/source/sys_reqs_20.html (opened), "System Requirements for OpenOffice.org 2": "Windows 98, Windows ME, Windows 2000 (Service Pack 2 or higher), Windows XP, Windows 2003, Windows Vista ... 128 Mbytes RAM".
- https://www.openoffice.org/dev_docs/source/sys_reqs_30.html (opened), "System Requirements for OpenOffice.org 3.0 - 3.3": "Windows 2000 (Service Pack 2 or higher), Windows XP, Windows 2003, Windows Vista, Windows 7". 98/ME were dropped at 3.0.
- The 3.0.0 release notes (http://www.openoffice.org/development/releases/3.0.0.html, opened) are a list of child workspaces and do not say in words that 9x was dropped. The OOo wiki page "Building on Windows (older releases)" (opened) says "Windows 98 is unsupported for OpenOffice.org 3.0 anyway".
- https://www.openoffice.org/development/releases/2.4.3.html (opened): "This is a bugfix release and will install as OpenOffice.org 2.4. Sources can be received from CVS by tag OOH680_m21." It lists "sb115 update libxml2", "hbso8fixes01 word import crash fix", "native263 New JRE 6u15 for OOo 2.4.3".
- https://www.openoffice.org/security/bulletin.html (opened): "Fixed in OpenOffice.org 2.4.3: CVE-2009-0200 / CVE-2009-0201 ... CVE-2009-2414 / CVE-2009-2416". 2.4.2 fixed only CVE-2008-2237/2238.
- Community forum (opened, not an official statement): moderator acknak, 21 Sep 2009: "Versions of OOo before 3.0 will work on Win98. A new update of OOo 2.4--2.4.3--was just released a few days ago; that should do nicely." A user replied the same day that 2.4.3 installed and worked on Windows 98. Another thread (Feb 2008) is titled "OOo 2.4 will likely be the last for Win98/ME".
- 2.4.2 release notes (opened) list "hro26 Update installation problems on Win9x", which shows 9x was still being maintained in the 2.4 line.
- Windows 95: NOT supported. No OOo 2.x or 1.1 system-requirements page lists 95 (1.1 lists "98, ME, NT (SP6 or higher), 2000 or XP"). Whether it runs anyway is unknown and was not tested.
- Windows ME: supported (listed).
- KernelEx: not needed.
- Windows Installer: the package needs MSI 2.0 (setup.ini `msiversion=2.0`) but carries and starts Microsoft's own installer for it. See "Install behaviour".

## Download

- Official archive: https://archive.apache.org/dist/incubator/ooo/stable/2.4.3/ (opened; the ASF keeps the legacy OOo mirror tree here). The Sun/Oracle servers (download.openoffice.org, archive.services.openoffice.org) are gone: the latter returns 404. SourceForge `openofficeorg.mirror` has only 3.2.1 and later.
- The file was downloaded from the former OOo mirror https://artfiles.org/openoffice.org/openoffice/archive/stable/2.4.3/OOo_2.4.3_Win32Intel_install_en-US.exe, because archive.apache.org is throttled (a comparison download from it stalled). ftp.gwdg.de lists the same file with the same size (118490487).
- Plain-HTTP official address, tested with `curl -I --http1.0`: http://archive.apache.org/dist/incubator/ooo/stable/2.4.3/OOo_2.4.3_Win32Intel_install_en-US.exe gives 200 with Content-Length 118490487. The server is slow.
- File: OOo_2.4.3_Win32Intel_install_en-US.exe, 118,490,487 bytes (en-US, without JRE)
- SHA-256: 4b31cca4a379e6437eca95ba435308cd3c2ba51b2044a60077d9f7c3f7193759
- MD5: 2cb0fdbfbeefbf20d838844c5ec0d829
- Published checksum: OOo's official http://download.openoffice.org/2.4.3/md5sums.txt (Wayback capture of 2009-09-22, opened) lists `2cb0fdbfbeefbf20d838844c5ec0d829  OOo_2.4.3_Win32Intel_install_en-US.exe`: MATCH. There is no SHA or signature for 2.x releases.
- Also compared with archive.apache.org: the first 104,902,656 bytes of a stalled download from the Apache archive hash identically to our file (SHA-256 of the prefix 07164a3c...). That comparison covers only part of the file; the full MD5 match above covers all of it.
- Authenticode: not signed.
- Alternatives (not downloaded): OOo_2.4.3_Win32Intel_install_wJRE_en-US.exe (127 MB, bundles Sun JRE 6u15; the JRE is not LGPL; not recommended for us, and JRE 6 on 98 is questionable), OOo_2.4.3_Win32Intel_langpack_en-US.exe, the SDK.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\openoffice -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0 as read right after the scan): "found no threats". The scan covered the installer and all src\ archives. LICENSE.TXT, RECORD.md and ENTRY.TXT (text only) were written after the scan started.

## Installer contents (listed with host 7-Zip 26.03; nothing was run)

- Outer wrapper: NSIS 2.25 self-extractor (7-Zip reports `Type = Nsis, SubType = NSIS-2.25`). 36 entries, including:
  setup.exe (OOo loader, 121,780 bytes), setup.ini, openofficeorg24.msi (1.47 MB), openoffice.org-*.cab (core01-09, writer, calc, impress, draw, math, base, pyuno, activex, testtool, onlineupdate...), **instmsia.exe** (Windows Installer 2.0 for 9x, 2002-03-11) and **instmsiw.exe** (for NT).
- setup.ini:
  ```
  [setup]
  database=openofficeorg24.msi
  instmsiw=instmsiw.exe
  instmsia=instmsia.exe
  msiversion=2.0
  productname=OpenOffice.org
  productcode={EF2F84A8-B322-448B-B095-F0C1BF97BF84}
  [languages]
  count=1
  default=1033
  ```
- The loader source, desktop/win32/source/setup/setup.cpp in the core source tarball (read): if the installed MSI is older than `msiversion`, it runs instmsia.exe on 9x (instmsiw.exe on NT) with `/c:"msiinst /delayreboot"`, adding ` /q` when quiet. On 95/98 (`IsWin9x() && GetMinorVersion() <= 10`) it then sets `REBOOT=Force` for the MSI, so the PC restarts at the end. ME (4.90) does not force the restart. So the package bundles AND launches InstMsiA itself; Beacon does not need a `Requires: msi` line.
- MSI (tables read with the WindowsInstaller COM object, read-only): ProductName "OpenOffice.org 2.4", ProductVersion 2.4.9421, Manufacturer "OpenOffice.org", ALLUSERS=1, schema 200 (so MSI 2.0 is enough), 3,649 files totalling about 324,546 KB. Default folder: ProgramFilesFolder\"OpenOffice.org 2.4" (short name OPENOF~1). LaunchCondition: AdminUser (always true on 9x).

## Java

Java is not required. The installer used here has no JRE. Evidence:
- sys_reqs_20.html (opened): "The minimum JDK/JRE version required to use OpenOffice.org features that require java is JDK/JRE version 1.3.1 ... For full functionality, jdk/jre 1.4.0_02 or newer ..."
- OOo 2.x Getting Started guide, wiki.openoffice.org/wiki/Documentation/OOoAuthors_User_Manual/Getting_Started/Minimum_requirements (opened with WebFetch, which returned a summary with quotes): "Some OpenOffice.org features (wizards and the HSQLDB database engine) require that the Java Runtime Environment (JRE) be installed on your computer." and "Although OOo will work fine without Java support, some features will not be available."
- The installer contains hsqldb.jar, sdbc_hsqldb.jar and ScriptProviderForJava.jar (core03.cab). They only work with a separately installed JRE. Writer, Calc, Impress, Draw and Math run without Java. Base's embedded database (HSQLDB), the Base wizards and some other wizards/filters need it.

## License

- license.txt (= license_en_US.txt) inside the installer (core02.cab, installed to `<dir>\licenses`):
  "This product is made available subject to the terms of GNU Lesser General Public License Version 2.1. ... Third Party Code. Additional copyright notices and license terms applicable to portions of the Software are set forth in the THIRDPARTYLICENSEREADME.html file. ... Copyright 2002,2007 Sun Microsystems, Inc." followed by the full LGPL 2.1 text.
- Source headers in the 2.4.3 tarballs (e.g. setup.cpp): "made available subject to the terms of GNU Lesser General Public License Version 2.1 ... under the terms of the GNU Lesser General Public License version 2.1". No "or later", so SPDX is **LGPL-2.1-only**.
- OOo licensing FAQ (https://www.openoffice.org/FAQs/faq-licensing.html, opened): "Effective OpenOffice.org 3.0 Beta, OpenOffice.org will use the GNU Lesser General Public License v.3 (LGPL). Prior versions use v. 2.1." and "Are OpenOffice.org binaries legal for commercial use? Yes ... You may freely distribute it to any user."
- The ASF distribution FAQ (https://www.openoffice.org/distribution/, opened): "Can I Produce a CD/DVD of your software and distribute it? Yes, this is covered under Apache License 2 for Apache OpenOffice 3.4 or later, and covered under the LGPL for older versions."
- LICENSE.TXT here holds (1) license.txt from the installer, verbatim, and (2) THIRDPARTYLICENSEREADME.html from the installer converted to plain text (markup removed). It is written in Windows-1252. 49 characters outside Windows-1252 (in non-Latin dictionary credits) became "?", and the original file itself already has "W?rterbuch".
- Redistributing the unmodified installer is allowed under LGPL 2.1 with these conditions: ship the license text, and provide the complete corresponding source (s.4/s.6). Offering it from the same place counts, so we host the source (below). The third-party licenses (for example Mozilla, ICU, zlib, OpenSSL, Python, W3C, Bitstream Vera, HSQLDB, STLport, the GPL/LGPL/LPPL texts) are listed in THIRDPARTYLICENSEREADME.

### Bundled components without source (Microsoft redistributables)

The installer contains Microsoft binaries that are not open source and whose source is not available:
- instmsia.exe and instmsiw.exe (Windows Installer 2.0 redistributables), in the NSIS wrapper
- unicows.dll (Microsoft Layer for Unicode, needed on 9x), msvcr71.dll, msvcp71.dll (VC++ 7.1 runtime), gdiplus.dll and dbghelp.dll, in openoffice.org-core05.cab

THIRDPARTYLICENSEREADME has a "Microsoft Corporation - Runtime Libraries" section, which is a Microsoft supplemental EULA text. These are "system library"-type redistributables that Sun shipped under Microsoft's redistribution terms. LGPL does not require their source. The catalog already hosts Python 2.5.4, whose MSI also carries msvcr71.dll. But this package also carries instmsia.exe, which FORMAT.md's `Requires` section treats as a component "we have no right to distribute" when it stands alone. **Unresolved, for a human decision:** whether hosting Sun's unmodified package that embeds these redistributables is acceptable. If not, list the package as `external` using the plain-HTTP Apache archive URL above (it works with HTTP/1.0).

## Matching source (hosted)

The OOo 2.4.3 source is split into five tarballs, all from the same archive directory. The complete set was downloaded. URLs: https://artfiles.org/openoffice.org/openoffice/archive/stable/2.4.3/<file>, identical in name to https://archive.apache.org/dist/incubator/ooo/stable/2.4.3/<file>. The official source page (download.openoffice.org/2.4.3/source.html, Wayback 2009-10-01, opened) lists "core (146 MB), system (40 MB), binfilter (6.5 MB), l10n (78 MB), extensions (13 MB)".

| File | Bytes | SHA-256 | MD5 vs official md5sums.txt |
|---|---|---|---|
| OOo_2.4.3_src_core.tar.bz2 | 152,311,420 | 0546441f8dad6658f2e78fa0c2a78bfae1efa281c66bd60c9174ff89ecdd0d75 | 855ed58bf480f0e16ec2e4e8bb14d71a MATCH |
| OOo_2.4.3_src_system.tar.bz2 | 41,621,781 | f0fb560b9335706c8b35a14051ef3247df2a8a95b240c80377bed61f46c9bdfb | 160761b22e0aa983d6963b9d650b3dc9 MATCH |
| OOo_2.4.3_src_binfilter.tar.bz2 | 6,738,021 | 1cd33d1318e17501d0a7e120ae098568a7c6ecb41f56e1258bd7c388e6bd9ae6 | 8fdafbaa43d749bcf115f88f0d62b2dc MATCH |
| OOo_2.4.3_src_extensions.tar.bz2 | 13,315,783 | 130f3ba340aa5051661d5081bda1041cb57e022719bff09dea903f733ea49af5 | 41e78d98a3281c17a317f14ddca9aaa0 MATCH (listed there as OOo_2.4.3_m21_extensions.tar.bz2) |
| OOo_2.4.3_src_l10n.tar.bz2 | 81,490,942 | 24db9edc142a97e423464e5b71e82b93d6dffee8b2955ccb30e160ac68506795 | 778fdadf752aac4bce92fd2fdfc55b92 MATCH |

All unpack to `OOH680_m21/` (the release tag). Third-party sources included in these tarballs (as upstream archives in `<module>/download/`):
- core: Berkeley DB 4.2.52.NC, FreeType 2.2.1, OpenSSL 0.9.8g, libsndfile 1.0.9, libwpd 0.8.8, BeanShell 2.0b1, Rhino 1.5R5, PortAudio v18.1, ICU 3.6, Boost 1.34.1/1.30.2/Spirit 1.6.1, xmlsec1 1.2.6, SampleICC 1.3.2, EPM 3.7, Adobe AFMs, libtextcat 2.2, expat, libxslt 1.1.16, HSQLDB 1.8.0, VIGRA 1.4.0, STLport 4.0/4.5, libmspack, NAS 1.6. xalan/download holds only prebuilt jars (xalan.jar, xercesImpl.jar, xml-apis.jar, serializer.jar, crimson.jar, Apache-licensed), not their source.
- system: Python 2.3.4, zlib 1.1.4, libxml2 2.6.17 (the 2.4.3 notes say libxml2 was updated, via patch), curl 7.12.2, neon 0.26.3, jpeg-6b, DejaVu 2.21 and Liberation fonts, dictionaries.
- **Not in the OOo tarballs:** the Mozilla 1.7.5 source used for the bundled Mozilla libraries (nspr4.dll, nss3.dll, smime3.dll, softokn3.dll, ssl3.dll, xpcom*.dll, mozz.dll, used by mozab2.dll for the address book and by NSS for signatures; all in core09/core05.cab). system/moz/download/mozilla-source.txt says: "Please copy the source archive for the Mozilla sources into this directory. At the moment "mozilla-source-1.7.5.tar.gz" is required ... http://ftp.mozilla.org/pub/mozilla.org/mozilla/releases/mozilla1.7.5/source/" (Windows builders also need vc71-glib/libIDL/wintools binaries, which are build tools only). I downloaded it to complete the set:
  - https://archive.mozilla.org/pub/mozilla/releases/mozilla1.7.5/source/mozilla-source-1.7.5.tar.gz
  - 38,721,366 bytes, SHA-256 3e252bab95ecad3016b72fa594e0c44b9633d8c7b6af187e088a092019b56445
  - mozilla-source-1.7.5.tar.gz.asc (189 bytes, SHA-256 a8fc7585a60682060c1d732de9b86abbdb5cef13df70b23d7c1fcd149e0ed431). Verified with gpg: "Good signature from Chase Phillips <cphillip@gmail.com>" (DSA key 24C48F806D1ECD07, fingerprint 2B75 7988 9C86 B6FA 4F31 18CD 24C4 8F80 6D1E CD07, fetched from keyserver.ubuntu.com, expired and not in a trust path; it was a Mozilla release signing key of the time, not independently confirmed). The OOo patch mozilla-source-1.7.5.patch is in the system tarball.
- Microsoft redistributables: no source exists (see above).
- Whether the exact prebuilt Mozilla binaries shipped were built from 1.7.5 + that patch is what the build files say. It was not independently verified.

## Trademark

- Today, from https://openoffice.apache.org/trademarks.html (opened): "For the Apache OpenOffice project these trademarks include the names Apache OpenOffice® and OpenOffice.org®, as well as the graphical logos. Use of these marks is prohibited without explicit permission from the ASF. However, the Apache OpenOffice project is happy to work with 3rd parties who desire to use these trademarks in ways that are beneficial to the project, which do not imply endorsement by ASF, and which are fully in conformance with Apache policy."
- ASF trademark policy https://www.apache.org/foundation/marks/ (opened): "Anyone can use ASF trademarks if that use of the trademark is nominative." Its examples of permitted nominative use include "Free copies of Apache ProjectName software under the Apache License and support services for Apache ProjectName are available at my own company website."
- ASF distribution FAQ https://www.openoffice.org/distribution/ (opened): "This means you can distribute unmodified versions of Apache OpenOffice as Apache OpenOffice, without modifying the product name." And: "If you, as company ABC, wish to distribute OpenOffice on a CD with a label "ABC OpenOffice", the answer is "no"." For resellers they ask for this acknowledgment: "Apache, the Apache feather logo, and OpenOffice are trademarks of The Apache Software Foundation. OpenOffice.org and the seagull logo are registered trademarks of The Apache Software Foundation."
- OOo-era (Sun) trademark policy: NOT obtained. The old openoffice.org trademark pages are gone (404/403), the Wayback Machine was "Temporarily Offline"/504 during this check, and the search budget was used up. The closest OOo-era statement I opened is the licensing FAQ: "You may freely distribute it to any user." That text is still on openoffice.org, so its date is unclear.
- Conclusion: hosting the unmodified installer under its own name "OpenOffice.org 2.4.3" is nominative use of the name for the genuine, unmodified product, and the ASF FAQ explicitly allows distributing unmodified builds without renaming. Conditions: do not rebrand ("Beacon OpenOffice"), do not imply ASF endorsement, and preferably include the ASF trademark acknowledgment on the package page. Hosting looks fine. Using the seagull logo on our site would need permission.

## Security

Sources: NVD API 2.0 virtualMatchString for version 2.4.3 of `cpe:2.3:a:apache:openoffice` (50), `openoffice:openoffice.org` (2), `apache:openoffice.org` (1) and `sun:openoffice.org` (1). That gives 54 unique CVEs, together with the OOo security bulletin (opened).

- The bulletin says 2.4.3 fixed CVE-2009-0200 and CVE-2009-0201, although NVD says "before 3.1.1". So these 2 do not apply: **52 remain**.
- About 50 of the 52 are Apache-era CVEs whose NVD range is "before 3.x/4.x", covering all earlier versions. Most of the code involved (Word/RTF/PPT/DBF/image filters, macros, links) already existed in 2.4. Some may not apply because the feature or code is newer or different in 2.4.3, for example the AOO 4.x installer (CVE-2016-6803), OOXML import (CVE-2013-4156), the HWP filter (CVE-2015-1774) and CVE-2009-2139 (named for Go-oo). These were not checked one by one.
- Worst (all reached by opening a crafted document):
  - CVE-2010-3451 / -3452 / -3453 / -3454: use-after-free / off-by-one in RTF and Word import, "OOo 2.x and 3.x before 3.3", arbitrary code, CVSS2 9.3
  - CVE-2009-2949 / CVE-2009-2950: XPM and GIF heap overflows (before 3.2), CVSS2 9.3
  - CVE-2010-4253 / CVE-2010-4643: PNG / TGA heap overflows in Impress (2.x and 3.x before 3.3), CVSS2 9.3
  - CVE-2010-0395: Python macro security bypass via a crafted ODT ("2.x and 3.0 before 3.2.1"), CVSS2 9.3
  - CVE-2010-3450: directory traversal overwriting files via crafted extension/XSLT filter JAR (2.x and 3.x before 3.3), CVSS2 9.3
  - CVE-2021-30245 (non-http hyperlinks can run code, "since about 2006") and CVE-2023-47804 (macro links), CVSS3 8.8
- The bundled OpenSSL 0.9.8g, libxml2 2.6.x, zlib 1.1.4 and Mozilla NSS 3.9-era libraries also have their own many CVEs, which are not counted above.

## Install behaviour

- Installer type: NSIS 2.25 wrapper that unpacks, then setup.exe (OOo loader, which also installs InstMsiA 2.0 if needed) runs openofficeorg24.msi. Script: setup_native/source/win32/nsis/downloadtemplate.nsi in the core tarball (read).
- Documented switches, from the script's own /HELP=ON text:
  "/S : Silent installation; /D=<path> : NSIS installation directory (must be the last option!); /EXTRACTONLY=ON ...; /INSTALLLOCATION=<path> : ... installation directory; /POSTREMOVE=ON : Removes the unpacked installation set after ... installation; /INSTALLJAVA=ON ...; /GUILEVEL=<guilevel> : Setting Windows Installer GUI level: qr, qb, qn, qf, ...; /PARAM1=\"key=value\" ...".
- Silent: `/S /GUILEVEL=qb /POSTREMOVE=ON`. With /S the files are unpacked to `$TEMP\<product> Installation Files`; without /S they go to the Desktop. The script then runs `setup.exe -lang <lang> ... /qb -ignore_running`, waits for it, and passes on its exit code (`SetErrorLevel $0`). The default GUI level when silent is /qr.
- setup.exe runs instmsia.exe quietly when MSI < 2.0 and then forces a restart at the end of the MSI on 95/98 (see above). The exit code will likely be 3010 or 1641 in that case. That is inferred from the code and not tested.
- Default folder: `C:\Program Files\OpenOffice.org 2.4` (MSI INSTALLLOCATION under ProgramFilesFolder).
- Add/Remove Programs: MSI product, so the DisplayName is the ProductName **"OpenOffice.org 2.4"**. ProductCode {EF2F84A8-B322-448B-B095-F0C1BF97BF84}; ARPCOMMENTS "OpenOffice.org 2.4 (en-US) (OOH680m21(Build:9421))". Uninstall via Add/Remove Programs or `msiexec /x {EF2F84A8-B322-448B-B095-F0C1BF97BF84}`.
- Installed size: about 325,000 KB of files per the MSI File table (the readme says about 500 MB after installation, including Sun JRE). Disk space needed during installation is higher (installer 113 MB + unpacked set + installed files).
- Optional features installed by default (level 20 <= INSTALLLEVEL 100): Quickstarter (adds a Startup-folder item), Online Update (queries a Sun update server that no longer exists), Python-UNO. The ActiveX control and Testtool are not installed by default (level 200).
- The Beacon Install line `exe /S /GUILEVEL=qb /POSTREMOVE=ON` was chosen rather than `msi`, because the MSI is inside the NSIS wrapper and setup.exe handles InstMsiA.

## Verification notes

- Verified by opening or downloading: the artfiles.org and archive.apache.org directory listings, the gwdg listing (size), the 2.4.3/2.4.2/3.0.0 release notes, sys_reqs_11/20/30, the security bulletin, the licensing and distribution FAQs, the ASF trademark pages, the official md5sums.txt and source.html (Wayback 2009 captures), and the Mozilla archive listing. Also, from the installer (listed and extracted to a temp folder, never run): setup.ini, license, readme, THIRDPARTYLICENSEREADME and the MSI tables. From the source tarballs (listed): the NSIS script, setup.cpp and the Mozilla notes. Also NVD API queries, and the gpg check of the Mozilla source.
- From forum posts (opened, not official): the Win98 success report for 2.4.3 and the "2.4 last for Win98/ME" discussion.
- From search snippets only: nothing is relied on.
- Not verified: running on 95/98/ME (no VM interaction), the exact silent-install exit codes and reboot behaviour on 98, the OOo-era (Sun) trademark policy text, a full-length byte comparison with archive.apache.org (partial prefix only; full MD5 matches the official list), and which of the 52 NVD CVEs truly affect 2.4.3.
