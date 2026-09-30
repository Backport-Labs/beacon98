# Zone 66 (shareware) 1993 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-zone66-shareware`
- Version: 1993
- License: Shareware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- LICENSE.DOC, "Epic MegaGames LICENSING AGREEMENT" (1994 form, opened):
  > This file, LICENSE.DOC, describes the only terms by which Epic MegaGames permits other parties to distribute this program throughout the world.
  > 1. Distribution by modem: Epic MegaGames allows and encourages all bulletin board systems and online services to distribute this game by modem as long as no files are altered or removed. If a distribution fee is charged for this software, you must additionally ensure that: A. Epic MegaGames is credited as the publisher of the file. B. The file is identified as shareware. C. The shareware concept is explained adequately elsewhere online. D. You charge less than $9 for downloading this shareware program.
- VENDOR.DOC: "EPIC MEGAGAMES presents a game from RENAISSANCE PRODUCTIONS / -= Zone 66 =-" and "Read the file LICENSE.DOC to understand your rights".
- Assessment: online distribution of the unaltered archive is explicitly allowed and encouraged. Beacon is a free online service; the Description names Epic MegaGames and explains that this is shareware. **Qualifies.** Internet downloads are not named literally in the 1994 form ("by modem", "bulletin board systems and online services"); the 1995 OMF 2097 license names them ("Distribution online (BBS's, Internet, online services) and by mail is, of course, highly encouraged").

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.
- HELPME.DOC: "ZONE 66 will not run under Windows or OS/2. Only run ZONE 66 from DOS". On 95/98 this means MS-DOS mode; ME has none, so Systems is 95, 98. The shortcut will not work from inside Windows; the Notice says so.

## Download

- Source: FUNET, ftp.funet.fi/pub/msdos/games/epic/ (Finnish university network archive; the One Must Fall 2097 fan wiki at https://www.omf2097.com/wiki/doku.php?id=download calls it "Epic's old FTP"). URL: https://ftp.funet.fi/pub/msdos/games/epic/$zone66.zip. Epic MegaGames' own distribution servers are gone; the license in the archive grants online distribution.
- Second copy: none compared (Epic's directory was removed from the gamers.org copy of the ftp.uwp.edu games archive, per its README).
- Published checksum: none.
- File: $zone66.zip, 1,017,774 bytes
  - SHA-256: 57f92a0487bf72ad0ec233e6d524b29c48134037e76b7aadf90930c36fe1cd9c
  - MD5: cd57ce1801cfa45b516ad49c5c55edc4

## Archive contents

- $zone66.zip (Deflate/Store, 92 files): ZONE66.EXE, GAME.EXE, INTRO.EXE, REN-93.EXE, CATALOG.EXE, HELPME.EXE, data files, ZONE66.DOC, LICENSE.DOC, VENDOR.DOC, SYSOP.DOC, HELPME.DOC, ORDER*.DOC, FILE_ID.DIZ. Gravis Ultrasound samples are in the separate $zone66g.zip (not packaged). No version number is given; the version field uses the year.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- The license is Epic MegaGames' shareware distribution license (LICENSE.DOC in the archive), copied into LICENSE.TXT with VENDOR.DOC.
- Clause that allows us to host it (quoted from LICENSE.DOC): see "Evidence" above. Beacon is a free online service that distributes the unmodified archive, so the online/BBS distribution clause applies.
- Conditions we must keep: distribute the archive complete and unmodified (no files altered, added or removed); credit Epic MegaGames as publisher; identify the program as shareware and explain the shareware concept (the ENTRY.TXT Description does this); charge nothing (Beacon is free).
- It is shareware, not freeware: registration (buying the full game) was expected from players who keep playing. Epic MegaGames no longer sells these registrations as described in ORDER.DOC; the order addresses in the archive are obsolete. The current rights holder was not verified.
- LICENSE.TXT in this folder: LICENSE.DOC (inside $zone66.zip); VENDOR.DOC (inside $zone66.zip).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword search (2026-09-29) for the game name: 0 results. DOS game data and program; no network server component except where noted. No known security problems.

## Install behaviour

- Type: plain zip (Deflate/Store only; checked with 7-Zip), files at the root. `unzip` into the target folder; the game runs from there. Shortcuts as in ENTRY.TXT.
- No installer, no registry entries, no Add/Remove Programs entry. Uninstall: `files`. The games write configuration and saved games into their own folder.
- Installed-Size in ENTRY.TXT: 1624 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
