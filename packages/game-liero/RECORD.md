# Liero 1.33 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-liero`
- Version: 1.33
- License: WTFPL
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- Official site https://www.liero.be/ ("LIERO official website", opened 2026-09-29) offers "Liero 1.33 ... This is final version of the original generation of Liero released in early 2000 ... Requires Windows 98 or older ... Download" linking https://www.liero.be/download/lierov133winxp.zip, with the license at https://www.liero.be/licenses/133/license.txt.
- LICENSE.TXT (in the zip, dated 2011-12-20; identical to the site's license page):
  > The original Liero data and binary files are copyright 1998 Joosa Riekkinen. They are, unless otherwise stated, available under the WTFPL license: <http://sam.zoy.org/wtfpl/>
  > The LIERO.EXE binary contains the SMIX sound library ... The author of SMIX has stated that it is available under a BSD-3-Clause license ...
  > LIERO.SND contains sounds from Molez ... Molez is freeware and freely distributable.
  > The license in LIEROENG.TXT is no longer valid but the file is kept for nostalgic purposes ;)
- The original LIEROENG.TXT also allowed it: "Liero is freeware. ... You may distribute it to anyone and anyhow WITHOUT ANY CHANGES MADE TO IT'S CONTAINMENTS."
- Who wrote LICENSE.TXT is not stated in it; it is published on the official site. **Qualifies.** Conditions: none under WTFPL; SMIX (BSD-3-Clause) needs its notice, which LICENSE.TXT carries; Molez sounds are freely distributable.

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.
- The official site states for 1.33: "Requires Windows 98 or older". LIEROENG.TXT: needs 386SX, VGA, 560 KB free conventional memory; Sound Blaster supported, 760 KB XMS for sounds.
- WINXP.BAT starts LIERO.EXE /n (a switch for Windows XP; its meaning was not checked). The shortcut starts LIERO.EXE without it.

## Download

- URL: https://www.liero.be/download/lierov133winxp.zip (official site; downloaded 2026-09-29).
- The zip is a later repack of 1.33: most files dated 1999-02-13, LIERO.DAT and LIERO.OPT 2005-04-19, WINXP.BAT 2006-09-16 (contains `LIERO.EXE /n`), LICENSE.TXT 2011-12-20. It is the only 1.33 download the official site offers.
- Second copy: none compared. Published checksum: none.
- File: lierov133winxp.zip, 366,080 bytes
  - SHA-256: c1f0331d00ec983263a2d8c395947306eb590843883d2b81272201b6e3859112
  - MD5: 6cc57f55bf9654f26406aa796dad5cd4

## Archive contents

- lierov133winxp.zip (Deflate/Store, 12 files, at the root): LIERO.EXE (DOS), LEVEDIT.EXE, LIERO.CHR, LIERO.SND, LIERO.DAT, LIERO.OPT, NAMES.DAT, LIERO.TXT (Finnish), LIEROENG.TXT, FILE_ID.DIZ, WINXP.BAT, LICENSE.TXT.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: LICENSE.TXT (inside lierov133winxp.zip; same text at https://www.liero.be/licenses/133/license.txt); LIEROENG.TXT (inside lierov133winxp.zip), original 1999 documentation, kept "for nostalgic purposes".
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword "liero" (2026-09-29): 2 results, both for Liero Xtreme (a different game). No known security problems in Liero 1.33.

## Install behaviour

- Type: plain zip, files at the root. `unzip {pf}\Games\Liero`; shortcut to LIERO.EXE.
- No installer, no registry entries, no Add/Remove Programs entry. Uninstall: `files`. Settings are written into the game folder (LIERO.OPT/LIERO.DAT).
- Installed-Size in ENTRY.TXT: 715 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
