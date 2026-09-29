# FastStone Image Viewer 5.3 - Beacon 98 record

- Date checked: 2026-09-29
- Package: FastStone Image Viewer (FastStone Soft)
- Version: 5.3 (October 24, 2014)
- License: freeware for personal and educational use; commercial use needs a license -> **external**

## Windows 9x support evidence

- System Requirements.htm inside FSViewerHelp.chm of FSViewer53.zip (extracted with host 7-Zip): "Windows 98SE, ME, XP (32-bit and 64-bit), Vista ..., Windows 7 ..., Windows 8 ..., Windows 8.1".
- Same file in FSViewer54.zip (version 5.4, downloaded to a temp folder to compare): "Windows XP (32-bit and 64-bit), Vista ... Windows 10". So 5.3 is the last version listing 98 SE/ME.
- https://www.faststone.org/FSViewerDetail.htm version history: "Version 5.4 (July 31, 2015) Added support for unicode filenames throughout the software", "Version 5.3 (October 24, 2014)".
- Windows 95 and first-edition 98: not listed. Not tested (no VM).

## Download

- Neither page links 5.3 any more; the current page links FSViewerSetup85.exe / FSViewer85.zip under /DN/ on faststone.org and faststonesoft.net (FastStone's own domains). The same folders still serve the old files by name:
  - https://www.faststone.org/DN/FSViewer53.zip and https://www.faststonesoft.net/DN/FSViewer53.zip: 200, 7,204,728 bytes (portable zip, chosen)
  - https://www.faststone.org/DN/FSViewerSetup53.exe and https://www.faststonesoft.net/DN/FSViewerSetup53.exe: 200, 5,806,407 bytes (installer, also saved here)
  - Plain HTTP: http://www.faststonesoft.net/DN/FSViewer53.zip answers 200 directly (7,204,728 bytes); http://www.faststone.org/... answers 302 to https.
- FSViewer53.zip: SHA-256 a22af33858dad8f1f2ce4dd33c1fdd8995f6ef58dd4996a511f42061355e2c38, MD5 b66a01f62c3d0d65d0d2ae002ee998d3
- FSViewerSetup53.exe: SHA-256 a4df2303edcf8cda50f76452339ae8104c9197db87e55a6f720431afe68f3e3b
- Published checksum: none.
- Authenticode: FSViewer.exe (5.3.0.0) and FSViewerSetup53.exe not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\faststone-viewer -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

LicenseAgreement.pdf in the zip (same wording as License.htm in the help), saved as LICENSE.TXT:
"FastStone Image Viewer is free for personal and educational (including non-profit organization) use. In these cases, you are granted the right to use and to make an unlimited number of copies of this software. For commercial use, it is required to register." and "must not be decompiled, disassembled, reverse engineered or otherwise modified."
- Personal/educational use only, and the copy right is granted to the user, not clearly to distributors. Not hostable; external from FastStone's server. No trial expiry or nag for personal use.
- Note: VERIFY-INSTRUCTIONS says personal-use-only licenses are not acceptable for hosting; this is listed only as external under the new external policy. The parent should confirm this is acceptable for the catalog.

## Security

NVD keyword "FastStone Image Viewer": 38 results. Those whose stated range covers 5.3: CVE-2021-26233, -26234, -26235, -26236 (stack overflow, CUR parsing), -26237 ("<= 7.5"), CVE-2022-36947 (PNG tRNS stack overflow, "through 7.5"), CVE-2026-101202 to -101205 ("up to 8.3", TGA/RLE/PCX). CVE-2024-9112/9113/9114 (PSD/TGA/GIF out-of-bounds write RCE) give no version range. Others name specific later versions (6.2, 6.5, 7.0, 7.5, 8.3) and may also apply but are not confirmed. Worst: CVE-2021-26236 / CVE-2022-36947 stack buffer overflows from a crafted image. Warning field added.

## Install behaviour

- Chosen file: portable zip; one top folder `FSViewer53/` (FSViewer.exe, plugins fsplugin01-04.dll, ZipDll.dll, databases, Skins, Callout, Mask and other resource folders; 191 entries, about 14.9 MB unpacked). Beacon: `unzip {pf}\FastStone Image Viewer strip 1`, shortcut `{dir}\FSViewer.exe`, uninstall `files`.
- Alternative: FSViewerSetup53.exe is NSIS 2 (`/S`), with uninst.exe; default folder and ARP name unknown.

## Verification notes

- Verified: history page, help files from 5.3 and 5.4, license PDF, file headers.
- Not verified: 5.3 on real 98 SE/ME.
