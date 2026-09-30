# Drascula: The Vampire Strikes Back 1.0 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-drascula`
- Version: 1.0
- License: Freeware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder: Alcachofa Soft S.L. ("Copyright (C) 1996-2008 Alcachofa Soft S.L."; "kindly freewared by Alcachofa Soft S.L.").
- License text (opened):
> 1) You may distribute "DRASCULA" for free on any medium, provided this Readme and all associated copyright notices and disclaimers are left intact.
> 3) You may not charge a fee for the game itself.
> 5) All game content is Copyright (C) Alcachofa Soft S.L.
- Assessment: free redistribution on any medium, provided the license and notices stay intact; no fee for the game itself. Beacon is free and ships the unmodified archive with its license. **Qualifies.**
- drascula-audio-2.0.zip readme.txt has the identical license text.

## Windows 9x support

- Needs ScummVM (Depends: scummvm, the catalog's 2026.1.0 Windows 95+ build, Systems 98, ME).
- https://www.scummvm.org/compatibility/2026.1.0/ (opened): "DrÃ¡scula: The Vampire Strikes Back | drascula:drascula | Excellent".
- drascula.dat is built into scummvm.exe (UTF-16 resource name DRASCULA.DAT found). The music pack is Ogg Vorbis; the scummvm record lists libvorbis in the win9x build.
- Not tested on 98 here (no VM interaction).

## Download

- URL: https://downloads.scummvm.org/frs/extras/Drascula_%20The%20Vampire%20Strikes%20Back/drascula-1.0.zip
  Published checksum: drascula-1.0.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- URL: https://downloads.scummvm.org/frs/extras/Drascula_%20The%20Vampire%20Strikes%20Back/drascula-audio-2.0.zip
  Published checksum: drascula-audio-2.0.zip.sha256 on downloads.scummvm.org lists the same SHA-256: **MATCH**.
- https://www.scummvm.org/games/ (opened) lists both files with these sha256 values.
- File: drascula-1.0.zip, 32,842,993 bytes
  - SHA-256: b731f6cb5a22ba8b4c3b3362f570b9a10a67b6cb0b395394b19a94b36e4e42de
  - MD5: fe2ee0948159c3acb923c89a1af7cc84
- File: drascula-audio-2.0.zip, 36,531,704 bytes
  - SHA-256: 7e6afba36eed13dd02e0360119e9a6a8d0e7b334ddc11d7c46ab7faceb8fe401
  - MD5: 4098145ef089e65f88a5f9f1e980073f

## Archive contents

- drascula-1.0.zip (Deflate): Packet.001 (32,847,563 bytes), drascula.doc, readme.txt, at the root.
- drascula-audio-2.0.zip (Deflate/Store): audio\track*.ogg (31 files) and readme.txt. Its readme says to unpack it into the same folder. Both unzip into {dir}; the second readme.txt replaces the first. Both readme files carry the same license text (checked), so the license stays intact.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: readme.txt (inside drascula-1.0.zip).
- Source code: not required (not an open-source license) and not available.

## Security

Game data for ScummVM. NVD keyword search for the game name (2026-09-29): 0 results. Engine risks are in the scummvm record.

## Install behaviour

- Type: plain zip. `unzip {dir}`. The After step registers the game with ScummVM (as for beneath-a-steel-sky); the shortcut starts ScummVM with the game target `drascula`.
- No registry entries. Uninstall: `files` (the scummvm.ini entry written by --add stays; same as beneath-a-steel-sky).
- Installed-Size in ENTRY.TXT: 68188 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
