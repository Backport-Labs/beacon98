# Eraser 5.82 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Eraser (Sami Tolvanen 1997-2002, Garrett Trant / Heidi Computers Ltd 2002-2006)
- Version: 5.82 (2006-12-26)
- License: GNU GPL 2 or later (lic.txt adds: "YOU MAY NOT REDISTRIBUTE MODIFIED VERSIONS OF THIS BINARY DISTRIBUTION"; we redistribute unmodified files only)
- Recommendation: 5.82. It is the last version whose own readme names Windows 95, 98 and ME, and its binaries are ANSI with the MFC/CRT linked statically. The asked-for "5.8.8" is the final 5.x (2010), but its release notes say "Fix Win32 Eraser builds to be truly Unicode builds", so it will not run on stock 9x.

## Windows 9x support evidence

- readme.txt installed by eraser582setup.exe (extracted with innoextract 1.9 on the host, installer not run), header "Eraser 5.82 (December 26th 2006)", section 2:
  "This version of Eraser runs on Windows 95, 98, ME, NT 4.0, 2000, XP and later."
  It also requires "version 4.72 or later version of the Windows Common Control Library" (COMCTL32.DLL; Windows 98 ships 4.72, Windows 95 needs IE 4.01 or the COMCTL32 update).
- history.txt in the same installer: "26-December-2006 / V5.82 Fixed issues with Freespace Erase / V5.81 Fixed issues with First/Last 2Kb Erase / V5.8 Final 5.8 release".
- Binary check (string scan, not executed): eraser.exe, Eraser.dll and Erasext.dll 5.82 use ANSI APIs (CreateFileA etc.) and need no MFC/MSVCR DLL (static). FileVersion of eraser.exe is 5.82.
- Note: the readme inside the 5.82 *source* archive is an older copy that says "runs on Windows 2006x64, XP64 and later" (evidently a leftover from the 5.8 x64 build); the readme actually shipped in the 5.82 installer says 95/98/ME.
- Later versions:
  - 5.84 (EraserSetup584x32.exe, 2007-07, downloaded to temp only): changed to an MSI-based setup that carries the Windows Installer 3.1 ANSI (9x) redistributable. Whether 5.84 runs on 9x: unknown (no statement found; its Eraser.exe appears packed, so the string scan was inconclusive).
  - 5.86a: PortableApps.com news 2008-02-26 (page opened): "Eraser no longer works with Windows 95, 98, Me but the older 5.82 release is available". This is the PortableApps packager's statement, not the Eraser project's.
  - 5.8.8 (last 5.x): release notes (SourceForge, opened): "Fix Win32 Eraser builds to be truly Unicode builds". A Unicode build does not run on 9x without MSLU/KernelEx; not tested.
- 5.7 (SourceForge /Eraser 5/5.7, Eraser57Setup.zip, readme opened) also states 95/98/ME. It is the fallback if 5.82 misbehaves.
- The eraser.heidi.ie announcement page returned HTTP 403, not read.
- Not tested on a real 95/98/ME system.

## Download

- Official archive: SourceForge project "eraser", folder /OldFiles (5.82 is not in the "Eraser 5" folder, which only has 5.7 and 5.8.8)
- URL: https://downloads.sourceforge.net/project/eraser/OldFiles/eraser582setup.exe
- File: eraser582setup.exe, 2,694,679 bytes (32-bit Inno Setup installer)
- SHA-256: 7f6afa94dd935ef2217b5c800f5fb0ac9a1815b556a952b265a71589556cd02e
- MD5: 59ece7eb4f27858237b389868b60ea6a
- Published checksum: SourceForge file listing for /OldFiles lists SHA-256 7f6afa94...cd02e, MD5 59ece7eb...0ea6a, SHA-1 be43012e10ee9f138397096ad78851aa5f47d905: MATCH (SourceForge-generated, not signed by the author). No PGP .asc exists for 5.82.
- Alternatives: eraser58setup.exe / eraser581setup.exe (earlier 5.8.x), Eraser57Setup.zip (5.7). No 5.82 zip/portable build from the project.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\eraser -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- GPL-2.0-or-later. lic.txt (source archive) and readme section 1.2: "you can redistribute it and/or modify it under the terms of the GNU General Public License ... either version 2 of the License, or (at your option) any later version." Full GPL 2 text as copying.txt in the installer.
- lic.txt also says "YOU MAY NOT REDISTRIBUTE MODIFIED VERSIONS OF THIS BINARY DISTRIBUTION." Not a problem: we host the unmodified installer.
- LICENSE.TXT here = lic.txt + copying.txt (GPL 2).
- Conditions: include the license; offer the complete corresponding source (GPL 2 s.3). We host it next to the binary:

## Matching source (hosted)

- URL: https://downloads.sourceforge.net/project/eraser/OldFiles/eraser582src.zip
- File: src\eraser582src.zip, 1,069,150 bytes
- SHA-256: f81580900f0403ad9c137612da48186e4512b4759502c4b2f128c42026c612ac (SourceForge listing: MATCH; MD5 51064693034f153e686d97dd904e35e8 MATCH)
- It is the 5.82 source: version.h defines VERSION_NUMBER_STRING "5.82" (dated 2006-12-25).
- Not in the archive:
  - The Inno Setup script ("The setup program is not included in the archive").
  - Boot\eBoot.exe (1.7 MB): a self-extracting image of Darik's Boot and Nuke (DBAN), a Linux boot floppy containing Linux, BusyBox, uClibc, syslinux and wipe (all GPL/LGPL; their licenses are in Boot\Lic). Their sources are not in eraser582src.zip. DBAN version: Boot\changelog.txt in the install (DBAN 1.0.x per History.txt: "Upgraded DBAN To 1.0.1" in 5.7). Before hosting, either add DBAN's matching source (dban.sourceforge.net, version unverified) or accept this gap as for VLC; unresolved.
  - Third-party code from CodeGuru/MSDN is included in source form.

## Security

- NVD (API 2.0, keyword "Eraser", exact match: 13 results): the only Eraser (Heidi) entry is CVE-2002-2068, "Eraser 5.3 does not clear Windows alternate data streams" on NTFS. 5.7 improved ADS handling and Windows 9x has no NTFS, so it does not apply here. No CPE for heidi:eraser in NVD.
- Known security problems of 5.82: 0 found.
- Functional caveats (not CVEs): overwriting does not reach data in file-system journals, bad-sector remaps, or SSD/flash wear levelling. 5.8.8 notes a FL2KB (first/last 2 KB) erase corrupting sparse/compressed/encrypted NTFS files; those do not exist on FAT under 9x.

## Install behaviour

- Installer type: Inno Setup, setup data version 5.1.7 (innoextract: "Inspecting \"Eraser 5.82\" - setup data version 5.1.7", English, no password).
- Silent install: standard Inno Setup `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (Eraser documents none of its own).
- Files: {app}\ (eraser.exe, eraserl.exe, Erasext.dll shell extension, verify.exe, eraserd.exe DOS version, eraser.hlp, Boot\eBoot.exe DBAN, Examples\) and {sys}\ (Eraser.dll, eraserl.exe, erasext.dll).
- Default folder: unknown (the setup script is not published; probably {pf}\Eraser).
- Uninstaller: yes (Inno Setup always registers one; readme 3.4: "You can uninstall Eraser normally via Control Panel, Add/Remove Programs"). Display name: probably "Eraser 5.82" (the setup's AppVerName as shown by innoextract; Inno 5.1 uses it when UninstallDisplayName is not set); not confirmed.
- Registry: settings under Software\Heidi Computers Ltd\Eraser (company name from version.h; exact key not verified).
- The readme says to remove versions 5.5 and below first.

## Verification notes

- Verified by opening or downloading: SourceForge file listings (Eraser 5, OldFiles) with hashes, 5.8.8 release notes, Eraser57Setup.zip readme, eraser582setup.exe contents (innoextract, not run), eraser582src.zip (lic.txt, README, History, version.h), EraserSetup584x32.exe listing (7-Zip, not run), PortableApps.com 5.86a news, NVD.
- From search snippets only: nothing relied on.
- Not verified: running on 95/98/ME; 5.84's 9x behaviour; default folder and Add/Remove name; DBAN source version.
