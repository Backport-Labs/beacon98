# Regshot 1.8.2 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Regshot (TiANWEi and contributors; later "The Regshot Team")
- Version: 1.8.2 (2007-11-03; SourceForge upload 2008-02-04). ANSI only (1.8.x had no Unicode build).
- License: GPL-2.0-or-later (batch2.md said LGPL-2.0; that is wrong)
- Recommendation: 1.8.2, the last stable release that can load on Windows 9x. Alternative: 1.9.1-beta r321 "VS6" ANSI build (2015), see below. Systems: 95, 98, ME (from static checks, no statement by the project, not VM-tested).

## Windows 9x support evidence

The project never states which Windows versions each release supports. Evidence found:

- 1.8.3 readme (https://downloads.sourceforge.net/project/regshot/regshot/1.8.3/readme, downloaded), note for 1.8.3_beta1_v3 by the original author:
  "(If you got to run regshot on old machine,please use 1.8.2 until new build)"
- Static PE checks (files extracted to a temp folder; nothing run):
  - 1.8.2 regshot.exe: OS/subsystem version 4.0; imports only ANSI KERNEL32/USER32/ADVAPI32/COMDLG32/SHELL32 functions, all present on Windows 95. Source (winmain.c) has no NT-only code paths (the NT privilege code is commented out). The folder-browse dialog asks for BIF_NEWDIALOGSTYLE, which older shells ignore.
  - 1.9.0 (2013-02-02, last stable) Regshot-x86-ANSI.exe: **subsystem version 5.0** and imports InitializeCriticalSectionAndSpinCount/IsDebuggerPresent (VS2010-era CRT). Windows 9x refuses to load images marked 5.0 ("requires a newer version of Windows"), so 1.9.0 needs KernelEx or does not run. Not tested.
  - 1.9.1-beta r321 (2015-07-26) Regshot-x86-ANSI.exe (normal build): subsystem 5.0, same as 1.9.0.
  - 1.9.1-beta r321 **VS6 build** (Regshot-1.9.1-beta_r321-VS6.7z) Regshot-x86-ANSI.exe: subsystem 4.0, ANSI imports; the W functions it imports (CompareStringW, GetLocaleInfoW, GetStringTypeW, LCMapStringW) are standard VC6 CRT imports that exist on 9x. It would probably load on 98. But its readme says "Note: this is the beta version for testing purpose only", and no source archive for r321 is published as a file (only SVN), so hosting it would need an SVN export to satisfy the GPL.
- Recommendation: 1.8.2 (stable, source in the same zip). Consider 1.9.1-beta VS6 later if a source export is made and it passes a VM test.

## Download

- Page: https://sourceforge.net/projects/regshot/files/regshot/1.8.2/ (official SourceForge project "regshot")
- URL: https://downloads.sourceforge.net/project/regshot/regshot/1.8.2/regshot_1.8.2_src_bin.zip
- File: regshot_1.8.2_src_bin.zip, 91,309 bytes (binary and source in one zip)
- SHA-256: 434b02c54677d8dece6c0ffb6644fd595b3e18ef9c29e675a9b08a3d013c123c
- MD5: 048f2c5dbf5b408646b5e38563c1b7c6
- Published checksum: the project publishes none. SourceForge's file RSS (https://sourceforge.net/projects/regshot/rss?path=/regshot/1.8.2) lists size 91309 and MD5 048f2c5dbf5b408646b5e38563c1b7c6: MATCH (SourceForge-generated, not signed).
- regshot.exe has no version resource; the program title string inside is "Regshot 1.8.2".
- Zip contents (no top folder): gpl.txt, history.txt, language.ini, readme.txt, regshot.exe (73,728), regshot.ini, and src\ (12 C/header/resource files).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\regshot -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- readme.txt (LICENSE section) and every source file: "Regshot is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version." history.txt: "V1.8.0 ... + Use GPLv2 license". gpl.txt is the GPL v2 text.
- LICENSE.TXT: readme.txt's LICENSE section plus gpl.txt.
- Redistribution allowed; conditions: include the license, offer the complete corresponding source. The source files are in the same zip; a copy of the zip is in src\ for the Source field.
- Bundled libraries: none (plain Win32 C). language.ini translations are "the property of their respective owner" per the readme, shipped under the same package.

## Matching source (hosted)

- src\regshot_1.8.2_src_bin.zip: the same file as above (91,309 bytes, SHA-256 434b02c5...123c). Built with MSVC 6 per the 1.8.3 notes; no build files are in the zip (only .c/.h/.rc/.ico). Whether the source alone rebuilds the exact binary was not checked.

## Security

NVD keyword search "regshot" (2026-09-29): 0 CVEs. 0 known problems.

## Install behaviour

- Plain zip, no installer, no Add/Remove Programs entry.
- Beacon: `unzip {dir}` (the src\ folder is unpacked too; 136 KB, harmless), Start Menu shortcut to regshot.exe, Uninstall: files.
- Regshot writes its logs to the Windows TEMP folder by default and saves settings to regshot.ini only if that file exists (it does, in the zip). Hive files are saved where the user chooses.

## Verification notes

- Opened/downloaded: SourceForge folder listings (via fetch), 1.8.3 readme, 1.9.0 and 1.9.1-beta readmes and archives (temp folder only), 1.8.2 zip, SourceForge RSS MD5, NVD. Nothing was run.
- Unverified: actual run on 95/98/ME; 1.9.1-beta VS6 behaviour on 98.
