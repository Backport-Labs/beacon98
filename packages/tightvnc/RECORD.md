# TightVNC 1.3.10 - Beacon 98 record

- Date checked: 2026-09-29
- Package: TightVNC (TightVNC Group / GlavSoft)
- Version: 1.3.10 (last of the 1.3 series)
- License: GNU GPL version 2 or later (LICENCE.txt is the GPL 2 text; the source headers say "either version 2 of the License, or (at your option) any later version")
- Recommendation: 1.3.10 with the official setup program (not the zip, see below). It is the last TightVNC for Windows 9x; 2.0 requires Windows 2000.

## Windows 9x support evidence

- https://www.tightvnc.com/download-old.php (opened): "TightVNC 1.3.10 for Windows supports all client and server versions of Microsoft Windows starting at Windows 95 and Windows NT 4 SP6."
- https://www.tightvnc.com/release-2.0.php (opened): for 2.0 "the minimum requirement is Windows 2000". So 1.3.10 is the last version for 95/98/ME. No KernelEx needed.
- The Inno Setup script in the source (vnc_winsrc/TightVNC.iss, read) installs special builds WinVNC_Win95.exe, VNCHooks_Win95.dll and vncviewer_Win95.exe on systems below 4.1 (Windows 95) and NT 4.0, and the normal builds on 98/ME and later. The portable zip holds only the normal builds, so the setup program is the right choice for 95.
- Windows 95, 98, ME: stated by the author. Not tested here (no VM interaction). Whether Windows 95 needs the Winsock 2 update was not verified.

## Download

- Page: https://www.tightvnc.com/download-old.php, section 1.3.10
- URL: https://www.tightvnc.com/download/1.3.10/tightvnc-1.3.10-setup.exe
- File: tightvnc-1.3.10-setup.exe, 1,421,291 bytes (size equals the one on the page)
- SHA-256: 9a6f155bf8e34853a388724cf28408ce5105a614cad24832a187752e03725610
- MD5: 88088d2a94bb936049b301119cb0a8a3
- Published checksum: tightvnc.com gives none. The official SourceForge project (vnc-tight) file RSS for /TightVNC-win32/1.3.10 lists MD5 88088d2a94bb936049b301119cb0a8a3 and size 1421291: MATCH (SourceForge-generated MD5, not signed by the authors).
- Alternatives (not hosted): tightvnc-1.3.10_x86.zip (943,591 bytes, SHA-256 e4b80953edda4f404adf4108264d30b5a087562cf2f07c9766841a24daa7cd2c, MD5 64a94fb645dde41c322ce8904887536e = SF MATCH; no Win95 builds; downloaded, read, then removed) and tightvnc-1.3.10_x86_viewer.zip (viewer only, not downloaded).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\tightvnc -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT = LICENCE.txt from the 1.3.10 binary distribution (GNU GPL 2 text) with a short header. README.txt in the zip: "TightVNC is available under the terms of the GNU General Public License (GPL), inclided in the file LICENCE.txt".
- Redistribution of the unmodified binaries is allowed. Conditions: include the license; GPL s.3 requires the complete corresponding source to accompany the binaries or be offered. We host the source next to the binary.

## Matching source (hosted)

- URL: https://www.tightvnc.com/download/1.3.10/tightvnc-1.3.10_winsrc.zip (listed on download-old.php)
- File: src/tightvnc-1.3.10_winsrc.zip, 2,378,726 bytes
- SHA-256: e25d218b9692b59385f8284a9e63755a26fb32e5e0a2d87dd57c20a8928c9004
- MD5: f9e2b50e2242046704508c71f04d7da4; SourceForge RSS lists f9e2b50e2242046704508c71f04d7da4: MATCH.
- The archive includes the bundled libjpeg and zlib sources (vnc_winsrc/*/libjpeg, */zlib) and the Inno Setup script. No other bundled library was found. Whether the separate *_Win95 builds come from this same tree with different build settings was not verified (BUILDING.txt not studied).

## Security

Source: NVD API 2.0, keyword "TightVNC".

Apply to 1.3.10 (NVD text names "TightVNC code version 1.3.10"; they were reported by Kaspersky in 2019 against the 1.3.10 code base, whose viewer code the Windows build shares; not verified line by line):
- CVE-2019-15678: heap buffer overflow in the rfbServerCutText handler, CVSS3 9.8
- CVE-2019-15679: heap buffer overflow in InitialiseRFBConnection, CVSS3 9.8
- CVE-2019-8287: global buffer overflow in HandleCoRREBBP, CVSS3 9.8
- CVE-2019-15680: null pointer dereference in HandleZlibBPP (DoS), CVSS3 7.5

All four are in the viewer and need the user to connect to a malicious VNC server. The 1.3.x line was never fixed.

Not applicable: CVE-2009-0388 (fixed in 1.3.10, per its WhatsNew: "Fixed integer overflow vulnerabilities reported by Core Security Technologies"), CVE-2002-1336 / CVE-2002-1848 (fixed in 1.2.6 / 1.2.4), CVE-2021-42785, CVE-2023-27830, CVE-2024-42049 (2.x tvnviewer.exe / 2.x server). CVE-2002-0971 (old WinVNC "Add new clients" dialog, local LocalSystem on NT) is unversioned in NVD; on 9x there is no privilege boundary anyway.

Design limits: VNC authentication is DES challenge/response with passwords truncated to 8 characters, and the session (including typed passwords) is not encrypted.

Summary: 4 known CVEs; worst CVE-2019-15678 / -15679 (heap overflow, CVSS 9.8, viewer).

## Install behaviour

- Installer type: Inno Setup ("Inno Setup Setup Data (5.2.3)" in the exe; script vnc_winsrc/TightVNC.iss in the source).
- Silent install: standard Inno Setup `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (Inno 5.2.3 supports all three). Components default to the "full" type: server, viewer, web documentation. Task "associate" (.vnc files) is on by default; "installservice" is unchecked by default, so a silent install does not register the server as a service.
- Default folder: `{pf}\TightVNC`; Start Menu group TightVNC.
- Uninstaller: yes, Inno Setup uninstaller. Add/Remove Programs name: `TightVNC 1.3.10` (AppVerName; no UninstallDisplayName is set, so Inno uses AppVerName), key `TightVNC_is1`. The uninstaller runs `WinVNC.exe -kill` (9x) and `WinVNC.exe -silent -remove`.
- Files use `restartreplace`, so an upgrade over a running server may ask for a restart.

## Verification notes

- Verified by opening or downloading: download-old.php, release-2.0.php, the SourceForge RSS (MD5s), the setup exe (Inno signature only; not run), the zip listing and README/LICENCE, the source zip (TightVNC.iss, LICENCE.txt, WhatsNew.txt, COPYING.txt), NVD.
- From search snippets only: nothing load-bearing.
- Not verified: running on 95/98/ME; Winsock 2 need on 95; Authenticode (not checked).
