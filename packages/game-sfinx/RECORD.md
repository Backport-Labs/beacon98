# Sfinx 1.1 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-sfinx`
- Version: 1.1
- License: Freeware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder: Laboratorium Komputerowe Avalon ("Sfinx, PC DOS version English v0.3 (C) Laboratorium Komputerowe Avalon 1995-2014"; the file name says v1.1, the license header says English v0.3).
- License text (opened):
> 1) You may distribute this game for free on any medium, provided this license and all associated copyright notices and disclaimers are left intact.
> 3) You may not charge a fee for the game itself. This includes reselling the game as an individual item.
> 4) You may modify the game as you wish. You may also distribute modified versions ...
- Assessment: free redistribution on any medium, provided the license and notices stay intact; no fee for the game itself. Beacon is free and ships the unmodified archive with its license. **Qualifies.**

## Windows 9x support

- Needs ScummVM (Depends: scummvm, the catalog's 2026.1.0 Windows 95+ build, Systems 98, ME).
- https://www.scummvm.org/compatibility/2026.1.0/ (opened): "Sfinx | cge2:sfinx | Good".
- Not tested on 98 here (no VM interaction).

## Download

- URL: https://downloads.scummvm.org/frs/extras/Sfinx/sfinx-en-v1.1.zip
  Published checksum: sfinx-en-v1.1.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- https://www.scummvm.org/games/ lists Sfinx (EN/DE/PL).
- File: sfinx-en-v1.1.zip, 16,549,117 bytes
  - SHA-256: f516b30a046526f78cbc923d8f907d267ab964ccd9b770afc72350e8d467ec4d
  - MD5: cabaaef213d1e027d46e453636c28d9a

## Archive contents

- sfinx-en-v1.1.zip: folder sfinx-en-v1.1\ with vol.cat, vol.dat, license.txt. Hence `strip 1`.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: license.txt (inside sfinx-en-v1.1.zip).
- Source code: not required (not an open-source license) and not available.

## Security

Game data for ScummVM. NVD keyword search for the game name (2026-09-29): 0 results. Engine risks are in the scummvm record.

## Install behaviour

- Type: plain zip. `unzip {dir} strip 1`. The After step registers the game with ScummVM (as for beneath-a-steel-sky); the shortcut starts ScummVM with the game target `sfinx`.
- No registry entries. Uninstall: `files` (the scummvm.ini entry written by --add stays; same as beneath-a-steel-sky).
- Installed-Size in ENTRY.TXT: 33509 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
