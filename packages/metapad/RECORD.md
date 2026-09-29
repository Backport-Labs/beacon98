# Metapad 3.6 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: Metapad (Alexander Davidson), id `metapad`
- Version: 3.6 (final, 2011-05-28), full (RichEdit) build
- License: GPL-3.0-or-later (source header and COPYING-LICENSE.txt); the readme in the binary zip also calls it freeware, "freely distributable in its unmodified zip file"
- Recommendation: 3.6, regular (full) build from liquidninja.com. It is the last release by the author, and he fixed 3.6 specifically so it loads on Windows 98. There is no later 3.6.x or 3.7 from the author. Alternative: 3.6 LE (Edit control instead of RichEdit, no RICHED20.DLL needed).

## Windows 9x support evidence

- https://liquidninja.com/metapad/ (opened): "Metapad is a small, fast and completely free text editor for Windows (95/98/NT/XP/Vista/7)". News: "May 28, 2011 : Metapad 3.6 final is available for download".
- https://liquidninja.com/metapad/download.html (opened): "Latest Release (May 2011) ... Version 3.6 / Version 3.6 LE"; "... text editor for Windows 9x/NT/XP/Vista".
- https://liquidninja.com/announcing-metapad-3-6/ (author's blog, opened): beta 2 changes include "Fixed Metapad 3.6 not loading on Windows 2000 or Windows 98".
- VisualStudio2010_setup.txt in the 3.6 source (opened), commit 0c7d368 "Win98 compatibility docs": "To allow Win98 compatibility, edit the binary with PETools or the like and change optional header "major subsystem version" from 05 to 04."
- metapad.exe from metapad36.zip, PE header read on the host (not executed): i386, linked with VC++ 10.0, subsystem version 4.0 (so the author applied that patch; 9x ignores the OS version field 5.0). Imports are ANSI (-A) functions only, from KERNEL32, USER32, GDI32, COMDLG32, COMCTL32 (CreateToolbarEx, PropertySheetA), ADVAPI32, SHELL32, msvcrt.dll, and RICHED20.DLL is loaded at run time (LE: no RICHED20.DLL). About string in the binary is "metapad 3.6" (not "beta 5").
- metapad.txt in the zip: "text editor for Windows 9x and Windows NT (2000)".
- Windows 95: stated by the site, but https://liquidninja.com/metapad/faq.html Q18 (opened) says RICHED20.DLL "ships with all versions of Windows except for Windows 95", so the full build needs it on 95. The binary also imports msvcrt.dll, which I believe is not part of retail Windows 95 (not verified). Windows 98 and ME ship both. Not tested on any 9x system (no VM interaction).
- KernelEx: not needed.
- Later versions: none from the author. GitHub alexd/metapad (API, opened): no releases, no tags; last commits are "3.6 final version change" (2011-05-28, 5f04b9a) and a merged third-party scroll-bar fix (vaifrax, 2012-03-23, merged 2012-05-12) that was never released as a binary. Wikipedia (search snippet only) gives 3.6 of 2011-05-28 as the stable release. Forks (checked via API): tenox7/metapad has a "3.6" release with rebuilt binaries for x86/x64/Alpha/MIPS/PPC/IA64 (2018, third party, 9x support not stated); alanbork/metapad_improved (2026, third party, high-DPI work, no releases). A repo "mohammadalee/metapad-360-stylized-release" (search result only, not opened) claims "Metapad 3.6.0 ... MIT License"; that is not the author and contradicts the real license; treat it as untrustworthy.
- ANSI vs Unicode: only an ANSI build exists. metapad.c has `//#define BUILD_METAPAD_UNICODE` under "Experimental/not working yet", and VisualStudio2010_setup.txt says to undefine UNICODE/_UNICODE. The binary imports only -A APIs, so no UNICOWS.DLL is needed. 3.6 reads/writes UTF-8 and UTF-16 files by converting to the ANSI code page. The two official builds differ in regular (RichEdit 2.0+) vs LE (plain Edit control), not in ANSI/Unicode.

## Download

- Download page: https://liquidninja.com/metapad/download.html
- URL: https://liquidninja.com/metapad/downloads/metapad36.zip (server Last-Modified: 2011-05-24 05:12:46 GMT)
- File: metapad36.zip, 111,496 bytes (plain zip, 32-bit x86)
- SHA-256: b350e854eab7ecd2d6f0510eb4bd03ea3a2eb1ff854c226247a4acda1bf36b51
- Contents: metapad.exe (194,560 bytes, SHA-256 of the extracted exe 685989bad8d8119eddbb49e36006d8ac9155c45d69dee060807368241c8e58ce), metapad.txt (10,131 bytes). Both at the zip root, no folders.
- Published checksum: the author publishes none. Third-party: the Chocolatey package metapad 3.6 (legal/VERIFICATION.txt in https://community.chocolatey.org/api/v2/package/metapad/3.6, opened, maintainer AdmiringWorm, 2017) lists SHA256 B350E854EAB7ECD2D6F0510EB4BD03EA3A2EB1FF854C226247A4ACDA1BF36B51: MATCH.
- Authenticode: metapad.exe not signed.
- Also downloaded (alternative, kept in this folder): https://liquidninja.com/metapad/downloads/metapad36LE.zip, 109,686 bytes, SHA-256 f7aee5fcc910be06111cf1ab35db31837c260648f869de45103edc03e56088c9 (Chocolatey metapad-light 3.6 lists F7AEE5FC...88C9: MATCH). Contains metapad.exe (190,464 bytes, "metapad LE 3.6") and metapad.txt.
- Plain HTTP: http://liquidninja.com/metapad/downloads/metapad36.zip answers 301 to https, so 98 cannot download it from the author; hosting is needed anyway.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\metapad -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- metapad.c header at the 3.6 final commit: "metapad 3.6 / Copyright (C) 1999-2011 Alexander Davidson / This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version." COPYING-LICENSE.txt is GPL v3 (29 June 2007). GitHub reports the repo license as GPL-3.0.
- https://liquidninja.com/metapad/sourcecode.html (opened) links gpl-3.0.html and says "The metapad code has been released under the GNU General Public License."
- Earlier history: 1.x-3.51 binaries were distributed as freeware. The source was first released on 2009-03-20 (3.51) and was already GPL v3 or later then (initial commit 45af04d, metapad.c header and COPYING-LICENSE.txt checked). I found no GPL-2 release.
- metapad.txt in the 3.6 zip keeps the older wording: "Metapad is freeware and is freely distributable in its unmodified zip file."
- LICENSE.TXT here contains the metapad.c license header, the readme's freeware statement, a note on the source, and the full GPL v3 text from COPYING-LICENSE.txt.
- Redistribution of the unmodified zip is allowed under both statements. GPL v3 conditions: include the license text, and offer the Corresponding Source (s.6d: equivalent access to the source from the same place). So we host the source.

## Matching source (hosted)

- URL: https://github.com/alexd/metapad/archive/5f04b9a2ad3d39964d9d853f022db345b31e561b.zip (commit "3.6 final version change", 2011-05-28; it only changes the About string from "3.6 beta 5" to "3.6")
- File: src\metapad-5f04b9a2ad3d39964d9d853f022db345b31e561b.zip, 150,922 bytes
- SHA-256: 7205b6c095bb0be88338145c7970cfc22a24a74365b8f2b8b36e1234a68b8d15 (GitHub generates this archive on request; no published hash. The GitHub archive hash could change if GitHub regenerates archives, so the hosted copy is the reference.)
- There are no tags or source archives from the author for 3.6. The binary's PE timestamp is 2011-05-24 04:49 UTC, before the commit time; the commit is the one the author labelled as 3.6 final and it matches the binary's About string. Byte-for-byte rebuild not attempted.
- Bundled code: libb64 (cencode.c/cdecode.c, public domain) is in the archive. No other libraries; the binary links dynamically to the system msvcrt.dll and RICHED20.DLL (Windows components, not bundled).

## Security

- NVD API 2.0 keyword search "metapad" on 2026-09-29: 0 CVEs; CPE search: no CPE for metapad. Web search found no advisories. Known security problems: 0.
- Design notes (from the source, not vulnerabilities on record): with "show hyperlinks" on, clicking a link in a document passes its text to ShellExecute; language plugins are DLLs loaded from the path in the settings. Any real risk lies in Windows' RichEdit control on 98, not in Metapad.

## Install behaviour

- Installer type: none; plain zip with metapad.exe and metapad.txt at the root.
- Beacon: `unzip {dir}` (no strip), Start Menu shortcut to `{dir}\metapad.exe`, uninstall `files`.
- Silent switch: not applicable. Add/Remove Programs name: none (no uninstaller is registered).
- Settings: stored in HKCU\SOFTWARE\metapad unless a file metapad.ini exists next to metapad.exe (portability mode; `/i` forces it, `/m` migrates registry settings). Beacon's `files` uninstall will leave that registry key. Option (not in ENTRY.TXT): `After: write {dir}\metapad.ini |` to keep settings in the program folder; the source detects the file by existence, but an empty INI was not tested.
- The author's FAQ describes replacing notepad.exe; Beacon should not do that.
- Requires on 95: RICHED20.DLL and MSVCRT.DLL in {sys} (both present on stock 98/ME).

## Verification notes

- Verified by opening or downloading: liquidninja.com metapad index, download, sourcecode, oldnews and faq pages; the 3.6 announcement blog post; GitHub API (repo, releases, tags, commits, tree, forks, commit 5f04b9a diff, commit 45af04d license); both zips and their metapad.txt; PE headers/imports of both exes (read, not run); the source archive (README, setup notes, metapad.c header, COPYING-LICENSE.txt); Chocolatey nupkgs' VERIFICATION.txt; NVD API.
- From search snippets only: Wikipedia's release date; the "mohammadalee" repo claim.
- Not verified: running on Windows 95/98/ME; whether retail Windows 95 lacks msvcrt.dll; that the binary was built from exactly commit 5f04b9a.
