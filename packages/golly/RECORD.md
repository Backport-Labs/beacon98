# Golly 1.4 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Golly (Andrew Trevorrow and Tomas Rokicki), Game of Life and cellular automata explorer
- Version: 1.4 (released 2008-05-25 on SourceForge)
- License: GNU GPL v2 or later
- Needs KernelEx on Windows 98 and ME (it is a Unicode build). Not for Windows 95.
- Two sensible choices:
  - **1.4 with KernelEx**: the version reported working (below).
  - **1.2 without KernelEx**: the last ANSI (non-Unicode) Windows build, imports only ANSI Win32 functions. Very likely runs on stock 98, and maybe on 95, but no report confirms it.
- Recommendation: offer **1.2** as the default if a VM test confirms it on stock 98 (no KernelEx needed), and 1.4 as the KernelEx option. 1.3 and 1.4 add undo/redo, Perl scripting and more, but the core is the same.

## Windows 9x / KernelEx evidence

- MSFN "KernelEx Apps Compatibility List (New)" (downloaded and read 2026-09-29), https://msfn.org/board/topic/152471-kernelex-apps-compatibility-list-new/ :
  under "Games that works": "Golly 1.4, a Game of Life simulator", linked to
  http://sourceforge.net/project/showfiles.php?group_id=139354&package_id=152849&release_id=601847 (the Golly SourceForge release). **No KernelEx version and no mode are given**, so assume the default mode. The list is for "Win98SE+KernelEx". Golly is not on the OSR list.
- Why 1.4 needs KernelEx: I read the import table of Golly.exe in golly-1.4-win.zip (not run). It uses Unicode functions throughout: USER32 MessageBoxW, GetMessageW, DefFrameProcW...; comdlg32 GetOpenFileNameW; SHELL32 ShellExecuteExW; ADVAPI32 RegOpenKeyExW; KERNEL32 CreateDirectoryW, MoveFileW. It does not use MSLU/unicows. On stock 98 these W functions are stubs, so the program cannot work. The source confirms it: makefile-win in golly-1.4-src says "nmake -f makefile.vc BUILD=release RUNTIME_LIBS=static UNICODE=1" (wxWidgets 2.8, static).
- Older versions (official SourceForge zips, downloaded to a temp folder only; MD5 matches the SF listing):
  - golly-1.3-win.zip (2007-11-18): Golly.exe uses 47 W and 3 A functions in USER32. Unicode, so KernelEx too.
  - **golly-1.2-win.zip (2007-04-15): 0 W and 49 A functions in USER32.** comdlg32, SHELL32 and ADVAPI32 are all A versions. KERNEL32 uses only functions that 9x has (the W calls present, GetEnvironmentStringsW, LCMapStringW, CompareStringW, GetStringTypeW and GetLocaleInfoW, are the usual MSVC C runtime calls, which fall back when they fail on 9x). 2,178,327 bytes, SHA-256 02c5ff2042ea79b90cb92366c61639be6cc9e9832d195179da2f3bd3b2eee79c, SF MD5 33940da6be1042dcda2077a92903d18d (match). Source: golly-1.2-src.tar.gz (SF MD5 db0b4745d4aad054c076b9b5794af85d).
  - golly-1.0-win.zip: also ANSI.
  - Golly's Help/changes.html (1.4) says under 1.1: "Golly's code can be compiled with a Unicode build of wxWidgets." It does not say when the Windows build switched; the binaries show it happened at 1.3.
  - Help/problems.html for 1.4: "Windows problems: None." There is no system requirement statement anywhere.

## Download

- Files page: https://sourceforge.net/projects/golly/files/golly/golly-1.4/ (official project; list from the SF RSS)
- URL: https://downloads.sourceforge.net/project/golly/golly/golly-1.4/golly-1.4-win.zip
- File: golly-1.4-win.zip, 2,347,109 bytes (plain zip, 277 entries, 5,852,031 bytes unpacked)
- SHA-256: 3b7eb6e853eb68092baa4f400ab4231cd7f5aa439563f4819f5776279726de0c
- MD5: 5c5bf87f65c241d869207c1619a391fd. SF RSS: MATCH.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\golly -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.txt in the zip = GPL v2 plus the Python 2.4 license (Golly embeds a Python interpreter when a Python DLL is installed; Python itself is not bundled). Source headers: "either version 2 of the License, or (at your option) any later version".
- wxWidgets 2.8 is linked statically (makefile-win: RUNTIME_LIBS=static). The wxWindows Library Licence allows distributing binaries without further conditions, so no wx source is needed.
- LICENSE.TXT = a short header plus LICENSE.txt from the zip, unchanged.
- Redistribution is allowed with the license and the source. We host the source:

## Matching source (hosted)

- URL: https://downloads.sourceforge.net/project/golly/golly/golly-1.4/golly-1.4-src.tar.gz
- File: src/golly-1.4-src.tar.gz, 1,444,433 bytes
- SHA-256: db7109d09d4ad46c882949fbbf9a94dc3dc99d538cf18ffd2e3638bf06a5dafc
- MD5: e060a41f9a838295b04f5f6d302cbed2. SF RSS: MATCH.

## Security

- NVD keyword "golly": 0 results. No known CVEs. (Pattern and script files are parsed; scripts in Perl or Python can do anything the user can, so they are as trusted as any program.)

## Install behaviour

- Plain zip, no installer. Top folder `golly-1.4-win\` containing Golly.exe, bgolly.exe (command-line version), Help\, Patterns\, Scripts\, LICENSE.txt, README.txt.
- README.txt: "The Golly application can be installed anywhere you like, but make sure you move the whole folder because the Help subfolder must be kept with the application."
- Beacon: `unzip {pf}\Golly strip 1`, a Start Menu shortcut to Golly.exe, `Uninstall: files`. No Add/Remove Programs entry. Where Golly writes its preferences was not checked.
- Scripting needs Perl 5.8 or Python 2.x installed separately. Optional.

## Verification notes

- Verified by opening or downloading: the MSFN list, the SF RSS for 1.0/1.2/1.3/1.4, the 1.4 zip (README.txt, LICENSE.txt, Help/changes.html, Help/problems.html), the import tables of Golly.exe in 1.0, 1.2, 1.3 and 1.4 (read as bytes, not run), the source README, makefile-win and source headers, and NVD.
- Not verified: running on 98 (no VM interaction). 1.2 on stock 98 and 95 is inferred from its imports only.
