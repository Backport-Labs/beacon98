# Doom (shareware) 1.9 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-doom-shareware`
- Version: 1.9
- License: Shareware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Rights holder at release: id Software (DOOMS_19.DAT: "Created by id Software / Copyright (C) 1993-1995").
- The shareware 1.9 archive contains no formal license document (no LICENSE.DOC, unlike Heretic and Quake). The permission to copy is the installer's own text, DOOMS_19.DAT (opened):
  > LINE0=DOOM / LINE1=Version 1.9 / LINE2=Created by id Software / LINE3=Copyright (C) 1993-1995 / LINE5=SHAREWARE VERSION / LINE6=PLEASE DISTRIBUTE!!!
- README.TXT (inside the DOOMS_19 archive, opened) carries the Association of Shareware Professionals member statement and asks users not to modify the shareware levels: "id Software respectfully requests that you do not modify the levels for the shareware version of DOOM."
- ORDER.FRM asks "Where did you get DOOM Episode 1 from?" with "Internet FTP Site" and "A friend gave it to me" as expected answers.
- Assessment: explicit, if informal, permission from the rights holder to distribute ("PLEASE DISTRIBUTE!!!"). No condition beyond not modifying the shareware levels. We distribute the complete, unmodified archive for free. **Qualifies, but the grant is informal**; a reviewer may prefer the formal licenses of Heretic, Quake and Duke Nukem 3D. Flagged for review.

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.
- DOOM.EXE is a 32-bit DOS extender program (DOS/4GW). The installer DEICE.EXE and SETUP.EXE are DOS programs.
- Alternative in Windows: DOOM1.WAD is a Doom IWAD that the catalog's prboom package recognises by name (doom1 is in PrBoom's IWAD list per the prboom record), once copied into PrBoom's folder.

## Download

- Source: the idgames archive, directory idstuff/doom (id Software's own "idstuff" directory, originally mirrored from ftp.idsoftware.com, which no longer exists). URL: https://www.gamers.org/pub/idgames/idstuff/doom/doom19s.zip (opened 2026-09-29; listing date 1996-10-13). The rights holder's server is gone; the archive's own text grants distribution, so using this mirror follows the instructions.
- Second copy: https://youfailit.net/pub/idgames/idstuff/doom/doom19s.zip (another idgames mirror) is byte-identical (same SHA-256). http://ftp.fu-berlin.de/pc/games/idgames/idstuff/doom/ lists the same file and size. Both are mirrors of the same archive, so this is not a fully independent check.
- Published checksum: none (idgames publishes none for idstuff).
- idgames description doom19s.txt: "DOOM v1.9 - Shareware ... This is the latest and FINAL version of DOOM, version 1.9."
- File: doom19s.zip, 2,450,688 bytes
  - SHA-256: cacf0142b31ca1af00796b4a0339e07992ac5f21bc3f81e7532fe1b5e1b486e6
  - MD5: 244d181457c9be5f28b91b488e67e042

## Archive contents

- doom19s.zip (Deflate/Store only): INSTALL.BAT, DEICE.EXE (id's installer), DOOMS_19.DAT, DOOMS_19.1, DOOMS_19.2.
- DOOMS_19.1 + DOOMS_19.2 joined form a self-extracting PKZIP archive (checked with 7-Zip on the host, not run) containing DOOM.EXE, DOOM1.WAD (4,196,020 bytes), SETUP.EXE, DM.EXE, DWANGO.EXE, IPXSETUP.EXE, SERSETUP.EXE, README.TXT, HELPME.TXT, ORDER.FRM, DMFAQ66A-D.TXT and modem files.
- INSTALL.BAT runs DEICE.EXE (joins the parts and asks for a folder, default \DOOMS per DOOMS_19.DAT "PATH=\DOOMS"), then DOOMS_19.EXE, then SETUP.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: DOOMS_19.DAT (installer data inside doom19s.zip; shown by the installer); README.TXT (inside the DOOMS_19 archive).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword "doom" (2026-09-29): no entry names Doom 1.9 for DOS. CVE-2020-15007 (buffer overflow in M_LoadDefaults, id Tech 1, via a crafted configuration file) concerns the Doom engine source; whether DOOM.EXE 1.9 is affected was not verified. It needs a crafted local default.cfg. Count: 0 confirmed, 1 possible.

## Install behaviour

- Type: plain zip (Deflate). `unzip {pf}\Games\Doom` puts the five files in the folder.
- The game itself is installed by id's own DOS installer (INSTALL.BAT -> DEICE.EXE), which the user runs from the Start Menu shortcut. It writes outside Beacon's folder (default C:\DOOMS), so Beacon's `files` uninstall removes only the archive files. No silent switch is documented for DEICE.
- No registry entries, no Add/Remove Programs entry.
- Installed-Size in ENTRY.TXT: 2395 KB (unpacked size of the archive; the game itself needs more space where its installer puts it).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
