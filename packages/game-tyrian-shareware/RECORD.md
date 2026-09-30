# Tyrian (shareware) 1.0 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-tyrian-shareware`
- Version: 1.0
- License: Shareware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- LICENSE.DOC, "Epic MegaGames, Inc. SOFTWARE LICENSE AGREEMENT" (1995 form, opened):
  > Epic encourages distribution of the Program in accordance with the provisions of this Software License Agreement.
  > 4. You may copy and/or distribute the Program only in its original, unaltered form, with all files included unmodified ...
  > 6. ... you shall not charge any fee or other compensation for the Program ... You are permitted, and encouraged, to make and distribute copies of the Program to your friends, family members and co-workers without charge
  > Distribution by BBS's and Online Services: Epic allows and encourages bulletin board systems and online services to distribute the Program by modem as long as the General Terms and Conditions set forth above are complied with.
- General Terms 1-3: credit Epic MegaGames as owner; identify the program as shareware (not "free software"); explain the shareware concept.
- VENDOR.DOC: "For Shareware Vendors / Tyrian / Version 1.0 from Epic MegaGames Inc." with the note "You may not distribute this program on CD-Rom or in retail stores without explicit written permission from Epic MegaGames."
- Assessment: online distribution of the unaltered archive is explicitly allowed and encouraged. Beacon is a free online service; the Description names Epic MegaGames and explains that this is shareware. **Qualifies.** Internet downloads are not named literally in the 1994 form ("by modem", "bulletin board systems and online services"); the 1995 OMF 2097 license names them ("Distribution online (BBS's, Internet, online services) and by mail is, of course, highly encouraged").

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.
- HELPME.DOC: "have any problems running under Windows 95, you'll have to run Tyrian from" DOS (line cut in the search result; the section is "Running with Windows").

## Download

- Source: FUNET, ftp.funet.fi/pub/msdos/games/epic/ (Finnish university network archive; the One Must Fall 2097 fan wiki at https://www.omf2097.com/wiki/doku.php?id=download calls it "Epic's old FTP"). URL: https://ftp.funet.fi/pub/msdos/games/epic/tyrsw1.zip. Epic MegaGames' own distribution servers are gone; the license in the archive grants online distribution.
- Second copy: none compared (Epic's directory was removed from the gamers.org copy of the ftp.uwp.edu games archive, per its README).
- Published checksum: none.
- File: tyrsw1.zip, 1,730,436 bytes
  - SHA-256: 2990485607d46e9fe3bc5fb572d0d9d93f0fdab997a82cff3425a4ed40564062
  - MD5: ecfb04cbb02d9ab02e40c931f7a7bc63

## Archive contents

- tyrsw1.zip (Deflate/Store, 73 files): TYRIAN.EXE (loader), FILE0001.EXE, FILE0002.EXE, RTM.EXE, SETUP.EXE, NETARENA.EXE, NETIPX.EXE, NETMODEM.EXE, NETTERM.EXE, HELPME.EXE, ORDER.EXE, data files, LICENSE.DOC, VENDOR.DOC, SYSOP.DOC, MANUAL.DOC, HELPME.DOC, ORDER*.DOC, MODEMS.TXT, FILE_ID.DIZ ("TYRIAN v1.0").

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- The license is Epic MegaGames' shareware distribution license (LICENSE.DOC in the archive), copied into LICENSE.TXT with VENDOR.DOC.
- Clause that allows us to host it (quoted from LICENSE.DOC): see "Evidence" above. Beacon is a free online service that distributes the unmodified archive, so the online/BBS distribution clause applies.
- Conditions we must keep: distribute the archive complete and unmodified (no files altered, added or removed); credit Epic MegaGames as publisher; identify the program as shareware and explain the shareware concept (the ENTRY.TXT Description does this); charge nothing (Beacon is free).
- It is shareware, not freeware: registration (buying the full game) was expected from players who keep playing. Epic MegaGames no longer sells these registrations as described in ORDER.DOC; the order addresses in the archive are obsolete. The current rights holder was not verified.
- LICENSE.TXT in this folder: LICENSE.DOC (inside tyrsw1.zip); VENDOR.DOC (inside tyrsw1.zip).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword search (2026-09-29) for the game name: 0 results. DOS game data and program; no network server component except where noted. No known security problems.

## Install behaviour

- Type: plain zip (Deflate/Store only; checked with 7-Zip), files at the root. `unzip` into the target folder; the game runs from there. Shortcuts as in ENTRY.TXT.
- No installer, no registry entries, no Add/Remove Programs entry. Uninstall: `files`. The games write configuration and saved games into their own folder.
- Installed-Size in ENTRY.TXT: 4109 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
