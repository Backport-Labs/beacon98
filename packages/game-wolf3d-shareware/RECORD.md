# Wolfenstein 3-D (shareware) 1.4 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-wolf3d-shareware`
- Version: 1.4
- License: Shareware
- Status: **HOLD: 1wolf14.zip uses the Implode and Shrink methods, which the Beacon client (miniz: stored and deflated only) cannot unpack.**

## Evidence of the right to redistribute

- No formal license document. READ1ST.TXT (opened):
  > This program is a "shareware program" and is provided at no charge to the user for evaluation. Feel free to share it with your friends, but please do not give it away altered or as part of another system. ... You are encouraged to pass a copy of this program along to your friends for evaluation.
- VENDOR.DOC, signed "Jay Wilbur, Id Software" (opened): "First, everyone at Id Software would like to thank you for distributing our product. ... Again thanks for helping us get the game into the hands of those who will enjoy playing it!" It explains how vendors may split the files over disks.
- WOLF3D1.DAT: "Wolfenstein 3-D: Escape From Wolfenstein / by id Software, Inc. / Copyright (c) 1992 / Distributed by Apogee".
- Assessment: sharing and vendor distribution are invited; conditions are "not altered" and "not as part of another system". Beacon offers the unmodified archive as its own optional package, not bundled into anything. **Qualifies with caveat (informal grant; "not as part of another system" needs a reviewer's reading).** Flagged for review.

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.

## Download

- Source: gamers.org "games/wolf3d/official" (a long-running game archive that also hosts idgames). URL: https://www.gamers.org/pub/games/wolf3d/official/1wolf14.zip (listing date 1992-12-21). Description file 1wolf14.txt: "WOLFENSTEIN 3-D VGA - ID/APOGEE! NEW VERSION 1.4". id's and Apogee's own servers for this file are gone.
- Second copy: none compared. The archive also contains CHKLIST.CPS (1993-02-04), a checksum file written by Central Point Anti-Virus after the original packing (1992-12-22), so the zip was touched by a distributor after release; the id files themselves carry 1992 dates.
- Published checksum: none.
- File: 1wolf14.zip, 747,094 bytes
  - SHA-256: 7755d3e6cc8897e9628fa1c13fe24d9657d901af2c3793ae258381431dcc69f2
  - MD5: e6d75d885e408003d2f4751d8dfd1cb0

## Archive contents

- 1wolf14.zip: DEICE.EXE, DESC.SDI, FILE_ID.DIZ, INSTALL.BAT, VENDOR.DOC, WOLF3D1.1, WOLF3D1.2, WOLF3D1.3, WOLF3D1.DAT, CHKLIST.CPS.
- Compression methods: Store, **Implode and Shrink** (PKZIP 1.x). The Beacon client uses miniz, which extracts only stored and deflated entries (client\vendor\miniz\miniz.h: "Extraction functions can only handle unencrypted, stored or deflated files"). **Beacon cannot install this zip as it is.**
- WOLF3D1.1-.3 joined are a self-extracting archive (listed with 7-Zip, not run): WOLF3D.EXE, the *.WL1 data files, READ1ST.TXT, ORDER.FRM, CATALOG.EXE.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: READ1ST.TXT (inside the WOLF3D1 archive); VENDOR.DOC (inside 1wolf14.zip); WOLF3D1.DAT (installer data inside 1wolf14.zip).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword "wolfenstein" (2026-09-29): 3 results, all for Return to Castle Wolfenstein / Quake 3 engine; none for Wolfenstein 3-D. No known security problems.

## Install behaviour

- Type: zip with Implode/Shrink entries. Draft: `unzip {pf}\Games\Wolf3D` would work only when the client supports these methods. **On hold** (ENTRY.TXT is commented as HOLD).
- Options: add Implode/Shrink support to the client; or host a different, deflate-only copy of the same shareware (not found from a trustworthy source); or leave it out.
- Then as for Doom: the user runs id's DEICE installer (default \WOLF1), which writes outside Beacon's folder.
- Installed-Size in ENTRY.TXT: 730 KB (unpacked size of the archive; the game itself needs more space where its installer puts it).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
