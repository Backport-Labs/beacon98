# TreeSize Free 2.1 (Windows 9x/ME build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: TreeSize Free (JAM Software GmbH, Trier, Germany; author Joachim Marder)
- Version: 2.1 (TreeSizeFree.exe file version 2.1.0.82, "(c) 1996-2007 by Joachim Marder", files dated 2007-05-07)
- License: JAM Software freeware terms (proprietary freeware that explicitly allows non-profit redistribution of the unmodified files)
- Recommendation: 2.1, the only build JAM offers for Windows 9x/ME. It can be **hosted** (see License), with JAM's own server as a second location.

## Windows 9x support evidence

- https://www.jam-software.com/treesize_free (opened 2026-09-29), section "TreeSize Free Information & Legacy Downloads", lists
  "Download TreeSize Free for Windows 9x / ME" -> https://downloads.jam-software.de/treesize_free/TreeSizeFree_9x.zip
  next to separate builds "for Windows 2000", "for Windows XP" and "for Windows 7".
- The exe inside is a 32-bit PE with subsystem version 4.0 (loadable by Windows 95/98/ME). Not run.
- Windows 95: the publisher says "9x / ME"; 95 is not named separately. Not tested on any 9x system (no VM interaction).
- The msfn list's "2.1" for Windows 98 SE matches the file version.

## Download

- URL: https://downloads.jam-software.de/treesize_free/TreeSizeFree_9x.zip
  - `curl.exe -sS -I -L` over https: 200, Content-Length 739972, Last-Modified 2015-09-11.
  - over http (http://downloads.jam-software.de/...): 301 to the https address, then 200. There is no plain-HTTP copy.
- File: TreeSizeFree_9x.zip, 739,972 bytes (plain zip)
- SHA-256: 98c52603ebd2278aa3abea9331f84cb71b1f7d291c14810856c81ac8dbf2afdc
- MD5: ccded1def8403faceaf336e9bb8fe459
- Published checksum: none found on the page.
- Contents (listed with .NET ZipFile): `TreeSizeFree.exe` (731,200 bytes), `TreeSizeFree.DE` (136,192 bytes, German language resource). No folders.
- Authenticode: TreeSizeFree.exe is signed, status Valid, signer "CN=JAM Software, O=JAM Software, L=Trier, S=Rheinland-Pfalz, C=DE" (checked on Windows 11 with Get-AuthenticodeSignature after extracting to a temp folder; not run).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\treesize-free -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- The zip has no license file. LICENSE.TXT holds JAM Software's current License Agreement
  (https://www.jam-software.com/company/license_agreement.shtml, linked as "Read License Agreement" from the TreeSize Free page).
  It is the current text; whether a different text shipped in 2007 is unknown.
- Section "Freeware and Trial Versions", quoted:
  "You may acquire and use freeware and trial versions of the Software free of charge. Use of these versions is free for both
  commercial and non-commercial purposes. You are not allowed to install or run TreeSize Free on server operating systems such as
  Windows Server. These versions may not be modified and no derivative works may be created from the software. Provided that the
  software is in its original state and all files are distributed, JAM Software GmbH permits copies of the software to be made and
  distributed as long as duplication and distribution are not for profit or fundraising purposes."
- Redistribution of the unmodified zip is allowed. Conditions: all files, unmodified; not for profit or fundraising (met: Beacon 98 is
  free and never sold). Hosting is possible; JAM's own URL is kept as a second location.
- No trial, no expiry, no nag known.

## Security

NVD keyword search "TreeSize" (API 2.0, 2026-09-29): 0 results. No known CVEs.

## Install behaviour

- Plain zip, no installer. Beacon: `unzip {pf}\TreeSize Free`, shortcut to `{dir}\TreeSizeFree.exe`.
- No uninstaller; Beacon removes its own files (`Uninstall: files`).
- Program settings location unknown (not run).

## Verification notes

- Verified by opening/downloading: the TreeSize Free page and its legacy link, the license agreement page, the zip (hash, listing,
  PE header, version resource, signature).
- Not verified: running on Windows 95/98/ME.
