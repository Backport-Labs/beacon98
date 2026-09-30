# Heretic (shareware) 1.2 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-heretic-shareware`
- Version: 1.2
- License: Shareware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- LICENSE.DOC, "LIMITED USE SOFTWARE LICENSE AGREEMENT" between the end user and Id Software (opened):
  > 3 Electronic Distribution is Permitted: ID grants to you the right to distribute, royalty free and by electronic means only, the Software; provided, however the Software must be so distributed only in compressed format.
  > 4. Copyright. The Software is owned by Raven Software, Inc. and exclusively licensed to id Software for distribution ... you may make copies of the Software to give to other persons. You may not charge or receive any consideration from any other person for the receipt or use of the Software without receiving ID's prior written consent
- Section 1 and 2 forbid selling, renting and distributing "for money or other consideration", and modifying the software.
- VENDOR.DOC: GT Interactive held the exclusive license to distribute the shareware to resellers; "Note: This does not apply to electronic forms (BBS, FTP, etc.) of distribution."
- HTIC_V12.DAT (installer text): "Copyright (C) 1994-5 Raven Software Corp. / Published by id Software, inc. / FREELY DISTRIBUTE".
- Assessment: electronic distribution, free of charge, in compressed format (a zip) is explicitly permitted. **Qualifies.**

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.

## Download

- Source: idgames archive, idstuff/heretic (id Software's directory). URL: https://www.gamers.org/pub/idgames/idstuff/heretic/htic_v12.zip (listing date 1996-10-13). idgames text htic_v12.txt: "Heretic ... Version 1.2". The rights holders' servers (ftp.idsoftware.com) are gone; the license in the archive grants electronic distribution.
- Second copy: https://youfailit.net/pub/idgames/idstuff/heretic/htic_v12.zip is byte-identical. Both are idgames mirrors.
- Published checksum: none.
- File: htic_v12.zip, 2,898,794 bytes
  - SHA-256: 5ffbb47e4a5750fef144c312973ee5782266b4a63474b77478103b6c1aaed39d
  - MD5: 420b23b3d8f2cbd164c121369eaa2b09

## Archive contents

- htic_v12.zip (Deflate): HTIC_V12.DAT, INSTALL.BAT, HTIC_V12.BAT, DEICE.EXE, HTIC_V12.1, HTIC_V12.2.
- HTIC_V12.1 + .2 joined are a self-extracting PKZIP archive (listed with 7-Zip, not run): HERETIC.EXE, HERETIC1.WAD (5,120,920 bytes), SETUP.EXE, DM.EXE, DWANGO.EXE, IPXSETUP.EXE, SERSETUP.EXE, VIOHT.EXE, README.TXT, HELPME.TXT, LICENSE.DOC, VENDOR.DOC, ORDER.FRM, FILE_ID.DIZ, modem files.
- INSTALL.BAT runs DEICE.EXE (default folder \HERETIC per "PATH=\HERETIC"), then HTIC_V12.EXE.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: LICENSE.DOC (inside the HTIC_V12 archive); VENDOR.DOC (inside the HTIC_V12 archive); HTIC_V12.DAT (installer data inside htic_v12.zip).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword "heretic" (2026-09-29): 0 results. No known security problems.

## Install behaviour

- Type: plain zip (Deflate). `unzip {pf}\Games\Heretic`.
- The game is installed by id's DOS installer (INSTALL.BAT -> DEICE.EXE) that the user runs; it writes outside Beacon's folder (default C:\HERETIC). Beacon's uninstall removes only the archive files.
- No registry entries, no Add/Remove Programs entry.
- Installed-Size in ENTRY.TXT: 2833 KB (unpacked size of the archive; the game itself needs more space where its installer puts it).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
