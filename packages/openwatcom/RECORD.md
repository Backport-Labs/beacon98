# Open Watcom C/C++ 1.9 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Open Watcom C/C++ (Win32-hosted installer; builds for DOS, Win16, Win32, OS/2, Linux targets)
- Version: 1.9 (files dated 2010-05-25)
- License: Sybase Open Watcom Public License 1.0 (OSI-approved)
- Recommendation: `open-watcom-c-win32-1.9.exe`, the last release of the original Open Watcom project. The later "Open Watcom V2" fork is a separate project and was not checked.

## Windows 9x support evidence

- No sentence in the 1.9 readme names Windows 95/98. The evidence is the installer's own logic and the binaries:
  - `setup.inf` in the installer (extracted, read) has host conditions `IsWin95` and `IsWinNT`, e.g. `++PATH=%DstDir%\BINNT, IsWin95 IsWinNT |`, so the Win32 tools are set up on Windows 95-family hosts; it also has 9x-specific items such as `_drwin95.exe` (Dr. Watcom for Windows 95) and an AUTOEXEC.BAT/CONFIG.SYS editing path (with `CONFIG.W95` backup names in the setup program).
  - readme.txt (install folder, opened) gives a "Win32 BAT file" for setting PATH/WATCOM/INCLUDE, which is how 9x users set the environment.
  - Every binnt tool checked (wcc386, wcl386, wlink, wlib, wmake, wrc, wd, wdw, ide, vi, viw and all DLLs in binnt) has subsystem version 4.0 and nothing from my list of APIs missing on 98. The setup program imports only KERNEL32/USER32/GDI32/ADVAPI32/SHELL32/COMDLG32/OLE32.
- Windows 95, 98, ME: expected to work (the Watcom tools historically supported them); not tested here.

## Download

- URL: https://www.openwatcom.org/ftp/install/open-watcom-c-win32-1.9.exe (official site's install directory)
- File: open-watcom-c-win32-1.9.exe, 84,012,543 bytes
- SHA-256: 040c910aba304fdb5f39b8fe508cd3c772b1da1f91a58179fa0895e0b2bf190b
- MD5: 6316f454f732b0705ebfe2a278dc1e59
- Published checksum: `open-watcom-c-win32-1.9.exe.md5` in the same directory reads `6316f454f732b0705ebfe2a278dc1e59 *open-watcom-c-win32-1.9.exe`: MATCH.
- Other files there: DOS, OS/2 and Linux hosted installers, and Fortran 77 installers (not downloaded).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\openwatcom -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT is https://www.openwatcom.org/ftp/install/license.txt (20,778 bytes), "Sybase Open Watcom Public License version 1.0". The same text is shown by the installer's License dialog.
- Section 2.2 lets anyone "use, reproduce, display, perform, modify and Deploy Covered Code" (Deploy includes distributing), provided: (a) notices and this license are kept; (b)/(c) modifications are marked and their source published; (d) "if You Deploy Covered Code in object code, executable form only, You must include a prominent notice ... stating that Source Code of the Covered Code is available under the terms of this License with information on how and where to obtain" it.
- We distribute unmodified files and host the matching source next to them, so the conditions are met. Beacon's package page should say where the source is (condition (d)).
- Note: section 2.1 on its own limits use of Original Code to "internal research and development and/or Personal Use"; 2.2 is the grant that covers distribution. The FSF calls the license non-free for other reasons (the rule on private modifications); OSI approved it. Neither affects redistributing the unmodified package.

## Matching source (hosted)

- URL: https://www.openwatcom.org/ftp/source/open_watcom_1.9.0-src.zip
- File: src/open_watcom_1.9.0-src.zip, 52,554,323 bytes
- SHA-256: c1cddd52405757a24987ea4fbcc455f3d1e61646798d908679dd6a4cc3b5272c
- No published checksum for the source.

## Security

- NVD keyword "Open Watcom": 0 results. No known CVEs.

## Install behaviour

- The installer is a self-extracting ZIP (7-Zip: "Type = zip", 428,032-byte stub) with Open Watcom's own setup program; 3,460 files, 196,660,542 bytes unpacked; `setup.inf` drives what is copied.
- Command-line switches (usage text inside the setup program): `-f=script`, `-d<name=val>`, `-i` "invisible: shows no dialogs; infers -s", `-s` "skips dialogs but shows install progress", `-np` "does not create Program Manager entries", `-ns` "does not register startup information (paths, environment)".
- Default folder `C:\WATCOM` (`DstDir=C:\WATCOM`); readme warns against folders with spaces.
- Uninstall: no Add/Remove Programs entry was found in setup.inf or the setup program; uninstalling is done by running setup again and choosing "Un-install all components". So `Uninstall: registry` is not possible.
- Setup edits AUTOEXEC.BAT on 9x (PATH, WATCOM, INCLUDE, EDPATH) unless `-ns`.
- Proposed for Beacon: since FORMAT.md treats self-extracting ZIPs as ZIPs, `Install: unzip C:\WATCOM` (unpacks everything, about 192 MB including the OS/2 and Linux host tools), add `C:\WATCOM\BINNT` and `C:\WATCOM\BINW` to PATH, write the environment batch file from the readme, `Uninstall: files`. Drawbacks: the WATCOM and INCLUDE variables are not set in AUTOEXEC.BAT (the format's After steps can only add PATH), so the user runs `C:\WATCOM\OWSETENV.BAT` in a DOS box first; the IDE and Windows 95-specific file choices made by setup.inf (e.g. `_drwin95.exe`) are not applied.
- Alternative: `Install: exe -i` lets setup do everything, but then Beacon has no way to uninstall it.

## Verification notes

- Opened/downloaded: install and source directory listings, installer, .md5, license.txt, readme.txt, setup.inf and binnt binaries (extracted with 7-Zip, headers/imports read, nothing executed), setup program strings, NVD API.
- Not verified: running on 95/98/ME; behaviour of the unzip route (vs. the real setup).
