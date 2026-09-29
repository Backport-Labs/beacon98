# Thunderbird 2.0.0.24 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: Mozilla Thunderbird (Mozilla / Mozilla Messaging)
- Version: 2.0.0.24 (2010-03-16), the last Thunderbird 2 release
- License: program code MPL 1.1 (tri-license MPL 1.1 / GPL 2.0 / LGPL 2.1 in the file headers); the official build is shipped under the "Mozilla Thunderbird End-User Software License Agreement, Version 1.1"; the Thunderbird name and logo are Mozilla trademarks
- Recommendation: list 2.0.0.24 as **external** (downloaded from archive.mozilla.org over plain HTTP). Do **not** host the official build: Mozilla's Unaltered Software Distribution Policy only permits redistributing the most recent version, and the EULA grants only a right to use. See "License".

## Windows 9x support evidence

- Release notes, https://website-archive.mozilla.org/www.mozilla.org/thunderbird_releasenotes/en-us/thunderbird/2.0.0.24/releasenotes/ (opened):
  "March 16, 2010" and "Thunderbird 2.0.0.24 is the last security and stability release of Thunderbird 2. We encourage users to update to Thunderbird 3.1". The same page lists the profile folder for "Windows 98, ME".
- Thunderbird 2 system requirements (the release notes link to http://www.mozilla.com/en-US/thunderbird/system-requirements.html; that page is gone, opened as the Internet Archive capture https://web.archive.org/web/2009id_/http://www.mozilla.com/en-US/thunderbird/system-requirements.html):
  "Operating Systems: Windows 98, Windows 98 SE, Windows ME, Windows NT 4.0, Windows 2000, Windows XP, Windows Server 2003, Windows Vista. Minimum Hardware: Pentium 233 MHz (Recommended: Pentium 500MHz or greater), 64 MB RAM (Recommended: 128 MB RAM or greater), 52 MB hard drive space".
- Thunderbird 3.0 release notes, https://website-archive.mozilla.org/www.mozilla.org/thunderbird_releasenotes/en-us/thunderbird/3.0/releasenotes/ (opened):
  "Please note that Thunderbird 3 no longer supports versions of Windows prior to Windows 2000 (e.g. Windows 95, 98, ME and NT)".
- Windows 95: not in the Thunderbird 2 requirements list. The installer script has no OS check (no WinVer test in installer.nsi/common.nsh), so it may start on 95, but 95 is not supported. Systems: 98, ME.
- KernelEx: not needed.
- Not tested on 98/ME (no VM interaction).

## Download

- Directory: https://archive.mozilla.org/pub/thunderbird/releases/2.0.0.24/win32/en-US/ (official Mozilla archive; ftp.mozilla.org serves the same files)
- URL: https://archive.mozilla.org/pub/thunderbird/releases/2.0.0.24/win32/en-US/Thunderbird%20Setup%202.0.0.24.exe
- File: `Thunderbird Setup 2.0.0.24.exe`, 6,876,688 bytes (32-bit x86, en-US)
- SHA-256: 585e5b7ef922fc224079dbad7ff02c7dc7cd40c3bb7a12a4a94e02ecfea2da29
- SHA-1: 7f5010c6298013b81af59d75536e0cb3da4fde3f; MD5: d0a4a2bfcfab26d54fc19474849f88ec
- Published checksums: the release directory's SHA1SUMS ("7f5010c6...  ./win32/en-US/Thunderbird Setup 2.0.0.24.exe") and MD5SUMS ("d0a4a2bf...") both MATCH.
- GPG: `Thunderbird Setup 2.0.0.24.exe.asc` verified with the KEY file from the same directory: "Good signature from Mozilla Software Releases <releases@mozilla.org>", made 2010-03-15, DSA subkey B57B548417785FE8, primary 8D6F 1BA4 A340 4DDB 3F2F D080 7447 4499 8123 47DD. The key has since expired (normal for a 2010 signature). The key was fetched from the same server, so this proves consistency, not an independent trust path.
- Authenticode: valid, signer "CN=Mozilla Corporation, OU=Release Engineering" (certificate expired 2010-10-30; Windows reports "Signature verified").
- Plain HTTP (for `external`): `curl.exe -sS -I --http1.0 http://archive.mozilla.org/pub/thunderbird/releases/2.0.0.24/win32/en-US/Thunderbird%20Setup%202.0.0.24.exe` returned `HTTP/1.1 200 OK`, Content-Length 6876688, ETag = the MD5 above, no redirect to HTTPS. http://ftp.mozilla.org/... and http://download-installer.cdn.mozilla.net/... gave the same result.
- Other languages exist under win32/<locale>/; only en-US was checked. There is no .msi or zip build.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\thunderbird -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". The folder includes the source tarball.

## License

- Inside the official installer (7-Zip SFX payload, file `nonlocalized\LICENSE.txt`, read after carving the 7z payload with the host's 7-Zip; nothing was run): "MOZILLA THUNDERBIRD END-USER SOFTWARE LICENSE AGREEMENT Version 1.1". Relevant parts:
  - "1. LICENSE GRANT. The Mozilla Corporation grants you a non-exclusive license to use the executable code version of the Product."
  - "3. PROPRIETARY RIGHTS. Portions of the Product are available in source code form under the terms of the Mozilla Public License and other open source licenses ... Nothing in this Agreement will be construed to limit any rights granted under the Open Source Licenses. ... You may not remove or alter any trademark, logo, copyright or other proprietary notice in or on the Product. This license does not grant you any right to use the trademarks, service marks or logos of Mozilla or its licensors."
  - The EULA itself grants no redistribution right. Redistribution of the code rests on the MPL, which (per the MPL's own section 2.1 and Mozilla's policy) grants no trademark rights; so redistributing the Thunderbird-branded binary depends on Mozilla's trademark distribution policy.
- Source tree: mozilla/LICENSE is the MPL 1.1; mozilla/other-licenses/branding/thunderbird/LICENSE says "You are not granted rights or licenses to the trademarks of the Mozilla Foundation or any party, including without limitation the Thunderbird name or logo."
- Mozilla licensing page (https://www.mozilla.org/en-US/foundation/licensing/, opened): "Executable software binaries released by the Mozilla Project, such as Firefox and Thunderbird, are made available under the terms of the MPL." (This is today's statement; the 2.0.0.24 build itself still ships the EULA above.)
- Mozilla Foundation Distribution Policy for Mozilla Software, https://www.mozilla.org/en-US/foundation/trademarks/distribution-policy/ (opened 2026-09-29), quoted:
  - "If you wish to distribute Firefox and other Mozilla software branded with our trademarks, you must comply with the relevant software licenses, the Mozilla Trademark Guidelines and either the Unaltered Software Distribution Policy or the terms of a written distribution agreement with Mozilla."
  - "You may distribute unaltered copies of Mozilla Firefox and other Mozilla software from Mozilla.org without express permission from Mozilla as long as you comply with the following rules: You may not charge for the software. ... You may not collect personal information in the context of your distribution of the software. You may not add to, remove, or change any part of the software, including the Mozilla trademarks themselves. ... You may not modify the installation process of the software or use it to install any other themes, plugins, extensions, or software."
  - "We suggest that if you want to distribute Mozilla software, you do so by linking to official downloads linked from Mozilla.org to help ensure safe, reliable downloads. ... When distributing you must distribute the most recent version of Firefox and other Mozilla software."
- Conclusion: hosting the official 2.0.0.24 build ourselves would break the "most recent version" rule, so it is **not certain to be legal** and we do not host it. A de-branded rebuild from source would be allowed by the MPL but is out of scope (and would not be "Thunderbird").
- External: the publisher still serves the file over plain HTTP from archive.mozilla.org (tested above), and Mozilla itself suggests linking to official downloads. So the entry is `Availability: external`, like VLC. LICENSE.TXT (to be hosted as the text shown before install) contains: Part 1 the EULA from the installer, Part 2 the MPL 1.1 from the source, Part 3 the Thunderbird branding notice. Plain ASCII.
- Note: Beacon running the installer with `-ms` skips the installer's own license page; Beacon shows LICENSE.TXT (which starts with the EULA) instead. We do not change the installer.

## Matching source (not hosted, kept for reference)

Not needed in the catalog because the package is external, but downloaded and verified:
- URL: https://archive.mozilla.org/pub/thunderbird/releases/2.0.0.24/source/thunderbird-2.0.0.24-source.tar.bz2
- File: src\thunderbird-2.0.0.24-source.tar.bz2, 38,861,392 bytes
- SHA-256: c6bf225692010e5b5024e34e3bda62f0b62af83c8a25ee692bd66d7076daad80
- SHA-1 8a65daab259430bc70338a9048ecf00b397034cb and MD5 6e09f74b25aac46705abb13ea4c26f67 MATCH SHA1SUMS/MD5SUMS; the .asc signature is good (same key as above).
- mozilla/mail/config/version.txt says 2.0.0.24. The tree includes NSPR, NSS, sqlite, the LDAP SDK and the NSIS installer scripts. The Talkback crash reporter (optional\extensions\talkback@mozilla.org in the installer) is a closed-source component not in the tarball.

## Security

Source: NVD API 2.0, `cpeName=cpe:2.3:a:mozilla:thunderbird:2.0.0.24` (2026-09-29): 1,589 CVEs match. 16 were published before the release (NVD version-less "Thunderbird" entries, most fixed in 2.0.0.x); 1,573 were published after it. Most later ones use open "before X" ranges and concern code that Thunderbird 2 may not contain, so the exact number that really applies is unknown. At least 98 CVEs from 2010-2011 name "Thunderbird before 3.0.x/3.1.x" and fall in the engine that 2.0.0.24 ships (Gecko 1.8.1). None were ever fixed for Thunderbird 2.

Worst few (CVSS2, all remote code execution by a crafted message/page, fixed only in Thunderbird 3.0.x):
- CVE-2010-0174 (10.0): browser-engine memory corruption, "Thunderbird before 3.0.4".
- CVE-2010-0175 (9.3): use-after-free in nsTreeSelection, "Thunderbird before 3.0.4".
- CVE-2010-3183 (9.3): LookupGetterOrSetter in js3250.dll (the 2.0.0.24 build ships js3250.dll), "Thunderbird before 3.0.9".
- CVE-2010-3179 (9.3): stack overflow in text rendering, "Thunderbird before 3.0.9".
- CVE-2010-1196 / CVE-2010-1199 (9.3): integer overflows in DOM text nodes / XSLT sorting.

Also: its NSS/SSL is from 2010 and cannot talk to most current mail servers' TLS (TLS 1.2+ is not supported); not tested.

## Install behaviour

- Installer type: Mozilla installer = 7-Zip SFX (7zS.sfx, "7zS.sfx.exe" 4.42, company "Mozilla") that unpacks and runs `setup.exe`, an NSIS 2.25 installer (identified by host 7-Zip). Scripts: mozilla/mail/installer/windows/nsis/installer.nsi and shared.nsh in the source.
- Silent install: installer.nsi `.onInit` accepts `-ms` ("Support for the deprecated -ms command line argument" -> `SetSilent silent`) or `/INI=<full path to ini>` (silent, with InstallDirectoryPath, DesktopShortcut, QuickLaunchShortcut, StartMenuShortcuts settings). The RetroZilla entry already uses `-ms` on the same installer family. Whether the SFX passes the argument to setup.exe was not tested here (documented Mozilla behaviour, not verified on 98).
- Default folder: `$PROGRAMFILES\Mozilla Thunderbird\`.
- Uninstaller: yes. shared.nsh `SetUninstallKeys` writes HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\Mozilla Thunderbird (2.0.0.24)` with DisplayName "Mozilla Thunderbird (2.0.0.24)", UninstallString `$INSTDIR\uninstall\helper.exe`, Publisher "Mozilla", NoModify/NoRepair.
- Side effects: registers as a mail client (HKLM Software\Clients\Mail\Mozilla Thunderbird, MAPI DLLs mozMapi32.dll/MapiProxy.dll), mailto/news handlers, Start Menu, desktop and Quick Launch shortcuts. Unpacked size about 25,700 KB (26,292,949 bytes in the payload).
- Software update: the build contains the Mozilla updater (updater.exe); update servers for 2.0 are long gone.

## Verification notes

- Verified by opening or downloading: the release directory listings, SHA1SUMS/MD5SUMS/KEY/.asc files, the installer and source tarball, the 2.0.0.24 and 3.0 release notes, the Internet Archive copy of the Thunderbird 2 system requirements, the EULA and license files inside the installer and source, the NSIS scripts, the Mozilla distribution policy and licensing pages, and the NVD API results.
- Only from search snippets: nothing used as evidence.
- Not verified: behaviour on Windows 95/98/ME (no VM), the `-ms` pass-through of the SFX wrapper, how many of the 1,573 later CVEs truly apply.
