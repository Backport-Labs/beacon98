# Soltys 1.0 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-soltys`
- Version: 1.0
- License: Freeware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder: Laboratorium Komputerowe Avalon ("Soltys, PC DOS version English v1.0 (C) Laboratorium Komputerowe Avalon 1995-2011").
- License text (opened):
> 1) You may distribute this game for free on any medium, provided this license and all associated copyright notices and disclaimers are left intact.
> 3) You may not charge a fee for the game itself. This includes reselling the game as an individual item.
> 4) You may modify the game as you wish. You may also distribute modified versions ...
- Assessment: free redistribution on any medium, provided the license and notices stay intact; no fee for the game itself. Beacon is free and ships the unmodified archive with its license. **Qualifies.**

## Windows 9x support

- Needs ScummVM (Depends: scummvm, the catalog's 2026.1.0 Windows 95+ build, Systems 98, ME).
- https://www.scummvm.org/compatibility/2026.1.0/ (opened): "SoÅ‚tys | cge:soltys | Good".
- Not tested on 98 here (no VM interaction).

## Download

- URL: https://downloads.scummvm.org/frs/extras/Soltys/soltys-en-v1.0.zip
  Published checksum: soltys-en-v1.0.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- https://www.scummvm.org/games/ lists Soltys (EN/DE/ES/PL).
- File: soltys-en-v1.0.zip, 3,484,518 bytes
  - SHA-256: 87b89e654b8a5b8ebe342cb4c5c6049ab9a43a5efb474d9c49bafb77dcce48f6
  - MD5: ae71d22e42bc6cdf8b0d489d9f61421b

## Archive contents

- soltys-en-v1.0.zip (Deflate): vol.cat, vol.dat, license.txt, at the root.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: license.txt (inside soltys-en-v1.0.zip).
- Source code: not required (not an open-source license) and not available.

## Security

Game data for ScummVM. NVD keyword search for the game name (2026-09-29): 0 results. Engine risks are in the scummvm record.

## Install behaviour

- Type: plain zip. `unzip {dir}`. The After step registers the game with ScummVM (as for beneath-a-steel-sky); the shortcut starts ScummVM with the game target `soltys`.
- No registry entries. Uninstall: `files` (the scummvm.ini entry written by --add stays; same as beneath-a-steel-sky).
- Installed-Size in ENTRY.TXT: 8284 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
