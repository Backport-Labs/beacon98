# Flight of the Amazon Queen CD 1.1 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-flight-amazon-queen`
- Version: CD 1.1
- License: Freeware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder: John Passfield and Steven Stamatiadis ("Copyright (C) 1995-2008").
- License text (opened):
> Preamble: Basically, give this game away, share it with your friends. Don't remove this Readme ...
> 1) You may distribute this game for free on any medium, provided this Readme and all associated copyright notices and disclaimers are left intact.
> 3) You may not charge a fee for the game itself.
> 5) All game content is Copyright (C) John Passfield and Steven Stamatiadis.
- Assessment: free redistribution on any medium, provided the license and notices stay intact; no fee for the game itself. Beacon is free and ships the unmodified archive with its license. **Qualifies.**

## Windows 9x support

- Needs ScummVM (Depends: scummvm, the catalog's 2026.1.0 Windows 95+ build, Systems 98, ME).
- https://www.scummvm.org/compatibility/2026.1.0/ (opened): "Flight of the Amazon Queen | queen:queen | Excellent".
- The talkie 1.1 audio is MP3-compressed: the ScummVM games page recommends the uncompressed "original" edition only "if your ScummVM doesn't have mp3 support"; the scummvm record lists libmad (MP3) in the win9x build.
- Not tested on 98 here (no VM interaction).

## Download

- URL: https://downloads.scummvm.org/frs/extras/Flight%20of%20the%20Amazon%20Queen/FOTAQ_Talkie-1.1.zip
  Published checksum: FOTAQ_Talkie-1.1.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- https://www.scummvm.org/games/ (opened) lists the Freeware CD Version downloads with sha256.
- Alternative: FOTAQ_Talkie-original.zip (112,625,523 bytes, uncompressed audio; already recorded in pilot\flight-of-the-amazon-queen) and FOTAQ_Floppy.zip (7,109,570 bytes, no speech; sha256 2e59de85...61e0, matched). The 1.1 talkie is chosen as the smallest version with speech.
- File: FOTAQ_Talkie-1.1.zip, 33,744,817 bytes
  - SHA-256: a25cdd5e003a0a5e402af99b218cc7ea81ad032cb36b8c05df3bd1167038d8a8
  - MD5: 4d94f62a907123b77819010117444332

## Archive contents

- FOTAQ_Talkie-1.1.zip (Deflate): readme.txt, queen.1c (51,222,412 bytes). Files at the root.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: readme.txt (inside FOTAQ_Talkie-1.1.zip).
- Source code: not required (not an open-source license) and not available.

## Security

Game data for ScummVM. NVD keyword search for the game name (2026-09-29): 0 results. Engine risks are in the scummvm record.

## Install behaviour

- Type: plain zip. `unzip {dir}`. The After step registers the game with ScummVM (as for beneath-a-steel-sky); the shortcut starts ScummVM with the game target `queen`.
- No registry entries. Uninstall: `files` (the scummvm.ini entry written by --add stays; same as beneath-a-steel-sky).
- Installed-Size in ENTRY.TXT: 50028 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
