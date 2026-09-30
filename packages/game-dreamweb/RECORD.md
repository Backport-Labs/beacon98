# DreamWeb CD 1.1 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-dreamweb`
- Version: CD 1.1
- License: Freeware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder: Neil Dodwell and David Dew trading as Creative Reality ("Dreamweb PC DOS version. Version 1.1 (C) 1994").
- License text (opened):
> 1) You may distribute this game for free on any medium, provided this license and all associated copyright notices and disclaimers are left intact.
> 3) You may not charge a fee for the game itself. This includes reselling the game as an individual item.
> 4) You may modify the game as you wish. You may also distribute modified versions ...
- Assessment: free redistribution on any medium, provided the license and notices stay intact; no fee for the game itself. Beacon is free and ships the unmodified archive with its license. **Qualifies.**
- license.txt changelog: "v1.0 Initial freeware release".

## Windows 9x support

- Needs ScummVM (Depends: scummvm, the catalog's 2026.1.0 Windows 95+ build, Systems 98, ME).
- https://www.scummvm.org/compatibility/2026.1.0/ (opened): "DreamWeb | dreamweb:dreamweb | Excellent".
- Not tested on 98 here (no VM interaction).

## Download

- URL: https://downloads.scummvm.org/frs/extras/Dreamweb/dreamweb-cd-uk-1.1.zip
  Published checksum: dreamweb-cd-uk-1.1.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- https://www.scummvm.org/games/ (opened) lists DreamWeb CD and floppy versions.
- Alternative: dreamweb-uk-1.1.zip (floppy, no speech, 10,198,532 bytes, sha256 0f98e5fb...cdfb3, matched). The CD version (226 MB download) is chosen for speech; the floppy version may suit slow connections better - reviewer's choice.
- File: dreamweb-cd-uk-1.1.zip, 226,067,188 bytes
  - SHA-256: 4a6f13911ce67d62c526e41048ec067b279f1b378c9210f39e0ce8d3f2b80142
  - MD5: 06ae54319977446a895753b226368830

## Archive contents

- dreamweb-cd-uk-1.1.zip (Deflate/Store, 588 files, 3 folders): DREAMWEB.* data files and DREAMWEB.EXE (original DOS program) at the root, speech files, diary\ and manual scans, license.txt. Unpacked size about 265 MB.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: license.txt (inside dreamweb-cd-uk-1.1.zip).
- Source code: not required (not an open-source license) and not available.

## Security

Game data for ScummVM. NVD keyword search for the game name (2026-09-29): 0 results. Engine risks are in the scummvm record.

## Install behaviour

- Type: plain zip. `unzip {dir}`. The After step registers the game with ScummVM (as for beneath-a-steel-sky); the shortcut starts ScummVM with the game target `dreamweb`.
- No registry entries. Uninstall: `files` (the scummvm.ini entry written by --add stays; same as beneath-a-steel-sky).
- Installed-Size in ENTRY.TXT: 264798 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
