# Lure of the Temptress 1.1 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-lure-of-the-temptress`
- Version: 1.1
- License: Freeware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder: Revolution Software Ltd ("Lure of the Temptress, PC DOS version (C) Revolution Software Ltd 1992-").
- License text (opened):
> 1) You may distribute this game for free on any medium, provided this license and all associated copyright notices and disclaimers are left intact.
> 3) You may not charge a fee for the game itself. This includes reselling the game as an individual item.
> 4) You may modify the game as you wish. You may also distribute modified versions ...
- Assessment: free redistribution on any medium, provided the license and notices stay intact; no fee for the game itself. Beacon is free and ships the unmodified archive with its license. **Qualifies.**
- README: "the game Lure of the Temptress, which was freewared by Revolution Software Ltd.".

## Windows 9x support

- Needs ScummVM (Depends: scummvm, the catalog's 2026.1.0 Windows 95+ build, Systems 98, ME).
- https://www.scummvm.org/compatibility/2026.1.0/ (opened): "Lure of the Temptress | lure:lure | Good".
- lure.dat, which the game needs, is built into scummvm.exe as a resource (the UTF-16 resource name LURE.DAT was found in the 2026.1.0 win9x exe).
- Not tested on 98 here (no VM interaction).

## Download

- URL: https://downloads.scummvm.org/frs/extras/Lure%20of%20the%20Temptress/lure-1.1.zip
  Published checksum: lure-1.1.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- https://www.scummvm.org/games/ (opened) lists "Lure of the Temptress - Freeware Version (English)" with this sha256.
- File: lure-1.1.zip, 5,678,861 bytes
  - SHA-256: f3178245a1483da1168c3a11e70b65d33c389f1f5df63d4f3a356886c1890108
  - MD5: d1300cef563bb4b6b1f88a2f1cee7832

## Archive contents

- lure-1.1.zip: folder lure\ with Lure.exe (the original DOS program), Disk1-4.vga, disk1-4.ega, Manual.pdf, PROTECT.PDF, README, notes.txt, LICENSE.txt. Hence `strip 1`. The original Lure.exe could also run in DOS (notes.txt explains how to bypass its copy protection).

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: LICENSE.txt (inside lure-1.1.zip).
- Source code: not required (not an open-source license) and not available.

## Security

Game data for ScummVM. NVD keyword search for the game name (2026-09-29): 0 results. Engine risks are in the scummvm record.

## Install behaviour

- Type: plain zip. `unzip {dir} strip 1`. The After step registers the game with ScummVM (as for beneath-a-steel-sky); the shortcut starts ScummVM with the game target `lure`.
- No registry entries. Uninstall: `files` (the scummvm.ini entry written by --add stays; same as beneath-a-steel-sky).
- Installed-Size in ENTRY.TXT: 7046 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
