# Quake (shareware) 1.06 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-quake-shareware`
- Version: 1.06
- License: Shareware
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- SLICNSE.TXT, "SHAREWARE VERSION: QUAKE LIMITED USE SOFTWARE LICENSE AGREEMENT", June 21, 1996 (opened):
  > 6. Permitted Distribution. So long as this Agreement accompanies the Software at all times, ID grants to Providers the limited right to distribute, free of charge, except normal access fees, and by electronic means only, the Software; provided, however, the Software must be so electronically distributed only in a compressed format. The term "Providers," as used in the foregoing sentence, shall mean persons whose business it is to provide services on the Internet, on commercial online networks, or on the BBS. ... Further, ID grants to you, the end-user, the limited right to distribute, free of charge only, the Software as a whole.
  > 7. ... you may make copies of the Software to give to other persons. You may not charge or receive any consideration from any other person for the receipt or use of the Software.
- Section 2 forbids commercial exploitation; LICINFO.TXT: "You may not commercially exploit the shareware version in any way. This specifically excludes retail distribution of the shareware version."
- Assessment: free electronic distribution of the whole, compressed, with the agreement accompanying it, is permitted to Internet providers and to end users. Beacon distributes the complete archive for free and shows the agreement (LICENSE.TXT) before installing. **Qualifies.** Conditions: free of charge; electronic only; compressed; complete; agreement accompanies it.

## Windows 9x support

- DOS program. Windows 95 and 98 run DOS games in an MS-DOS window or, when a game does not work there, in MS-DOS mode (Start, Shut Down, "Restart in MS-DOS mode"). Windows ME has no MS-DOS mode, so a game that needs it will not work on ME.
- Sound: the game drives a Sound Blaster-compatible card directly. In a Windows 98 MS-DOS window this works when the sound card driver offers Sound Blaster emulation for DOS programs (most ISA cards, some PCI cards). Otherwise use MS-DOS mode with the card's DOS drivers, or run the game in the catalog's `dosbox` package.
- Not tested on Windows 95/98/ME here (no VM interaction). `Systems` in ENTRY.TXT is an inference from the program being a DOS program, not a tested claim.
- Q95.BAT with QLAUNCH.EXE, GENVXD.DLL and MGENVXD.VXD is id's launcher for running the DOS QUAKE.EXE under Windows 95 with TCP/IP play (file names from the archive; not tested).

## Download

- Source: idgames archive, idstuff/quake (id Software's directory). URL: https://www.gamers.org/pub/idgames/idstuff/quake/quake106.zip (listing date 1996-10-01). Floppy-sized split parts qsw106_1..7.zip are also there (not used).
- Second copy: https://youfailit.net/pub/idgames/idstuff/quake/quake106.zip is byte-identical. Both are idgames mirrors.
- Published checksum: none.
- File: quake106.zip, 9,094,045 bytes
  - SHA-256: ec6c9d34b1ae0252ac0066045b6611a7919c2a0d78a3a66d9387a8f597553239
  - MD5: 8cee4d03ee092909fdb6a4f84f0c1357

## Archive contents

- quake106.zip (Deflate): resource.1 (9,086,574 bytes), install.bat, deice.exe, resource.dat ("PATH=\QUAKE_SW", "Shareware Version 1.06").
- resource.1 is an archive readable by 7-Zip (listed, not run): QUAKE.EXE, ID1\PAK0.PAK (18,689,235 bytes), CWSDPMI.EXE, Q95.BAT, QLAUNCH.EXE, GENVXD.DLL, MGENVXD.VXD, QUAKEUDP.DLL, PDIPX.COM, README.TXT, READV106.TXT, TECHINFO.TXT, HELP.TXT, ORDER.TXT, SLICNSE.TXT, LICINFO.TXT.
- install.bat runs deice.exe, which unpacks resource.1 into the chosen folder (default \QUAKE_SW).

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: SLICNSE.TXT (inside resource.1 of quake106.zip); LICINFO.TXT (inside resource.1 of quake106.zip).
- Source code: not required (not an open-source license) and not available.

## Security

NVD keyword "quake" (2026-09-29), entries that name Quake 1 / NetQuake:
- CVE-1999-1066: Quake 1 server answers a connection request with much traffic (usable as an amplifier).
- CVE-1999-1569: Quake 1 and NetQuake servers, denial of service by a flood of spoofed connection packets.
- CVE-2000-1080: Quake 1 and ProQuake 1.01 and earlier, denial of service by an empty UDP packet.
- CVE-1999-1502: buffer overflows in the "Quake 1.9 client" (QuakeWorld-era client) from malicious servers; whether it applies to 1.06 was not verified.
Count: 3 apply to Quake 1 servers, 1 possible. The worst: CVE-1999-1502 (possible code execution from a malicious server) if it applies. All need network play. ENTRY.TXT carries a Warning.

## Install behaviour

- Type: plain zip (Deflate). `unzip {pf}\Games\Quake`.
- The game is installed by id's installer (install.bat -> deice.exe), run by the user; it writes outside Beacon's folder (default C:\QUAKE_SW). Beacon's uninstall removes only the archive files.
- No registry entries, no Add/Remove Programs entry.
- Installed-Size in ENTRY.TXT: 8910 KB (unpacked size of the archive; the game itself needs more space where its installer puts it).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
