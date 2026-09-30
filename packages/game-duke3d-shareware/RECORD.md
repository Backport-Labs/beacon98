# Duke Nukem 3D (shareware) 1.3d - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-duke3d-shareware`
- Version: 1.3d
- License: Shareware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- LICENSE.TXT, version "[V.7.16.98]", "Copyright 1996 3D Realms Entertainment a division of Apogee Software, Ltd." (opened):
  > [3] GRANT: 3D Realms grants a non-exclusive, non-transferable, royalty-free license to distribute the Game only as follows:
  > [A] INDIVIDUALS are encouraged to share and give copies of the Game to friends, family, coworkers, and members of any not-for-profit organization, but only without charge.
  > [B] ONLINE SERVICES (including BBSs, and WWW and FTP sites) that are free (except for any subscription fees or incidental Internet access charges), and BBSs with 250 or fewer nodes (regardless of any charges to users) may make the Game available for downloading.
  > [C] These grants are subject to the conditions that no copyright information or trademark will be added or removed, and all of the Game's files as released by 3D Realms will be included without modification
- The FormGen exclusive commercial right ended March 1, 1997 (same file). CD-ROM, catalog and retail distribution need written permission; not relevant.
- Assessment: Beacon is a free WWW/FTP-style download service. **Qualifies.** Conditions: free; complete and unmodified; no notices removed.

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.

## Download

- Source: gamers.org "games/duke3d/share". URL: https://www.gamers.org/pub/games/duke3d/share/3dduke13.zip (listing date 1998-07-22; the 1998 repack with the 7.16.98 license). 3D Realms' own download server for it is gone (https://3drealms.com/ lists only current games, checked 2026-09-29).
- Second, independent copy: the Internet Archive item 3dduke13SW ("Files/v1.3d (1998 Repack)/3dduke13SW.zip", uploaded by marco@icculus.org) has the same size (5,924,374) and MD5 04e4ca70b8a2d59ed56c451c5c1d5d39, which matches this file's MD5.
- Alternative: ftp.funet.fi/pub/msdos/games/3drealms/3dduke13.zip (5,910,927 bytes, 1996-04-24) is the original 1996 packing with an older license; not used.
- Published checksum: none by 3D Realms.
- File: 3dduke13.zip, 5,924,374 bytes
  - SHA-256: c67efd179022bc6d9bde54f404c707cbcbdc15423c20be72e277bc2bdddf3d0e
  - MD5: 04e4ca70b8a2d59ed56c451c5c1d5d39

## Archive contents

- 3dduke13.zip (Deflate): LICENSE.TXT, INSTALL.EXE (3D Realms installer, DOS), DN3DSW13.SHR (5,848,108 bytes, packed game files), FILE_ID.DIZ.
- The license lists the files the installed game must contain (DUKE3D.EXE, DUKE3D.GRP, SETUP.EXE, ...). They are inside DN3DSW13.SHR, which only INSTALL.EXE unpacks (not run here).

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: LICENSE.TXT (inside 3dduke13.zip).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword "duke nukem" (2026-09-29): 0 results. No known security problems.

## Install behaviour

- Type: plain zip (Deflate). `unzip {pf}\Games\Duke3D`.
- The game is installed by 3D Realms' DOS installer INSTALL.EXE, run by the user; its default folder was not checked (not run). It writes outside Beacon's folder; Beacon's uninstall removes only the archive files.
- No registry entries, no Add/Remove Programs entry.
- Installed-Size in ENTRY.TXT: 5860 KB (unpacked size of the archive; the game itself needs more space where its installer puts it).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
