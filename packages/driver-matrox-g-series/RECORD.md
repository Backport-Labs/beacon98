# Matrox PowerDesk 6.83.017 for Windows 98/ME (G200-G550) - Beacon 98 record

- Date checked: 2026-09-29
- Package: w9x_683.exe, "Matrox PowerDesk for Windows 98/Me Revision 6.83.017" (readme dated 2002.05.28)
- Version: 6.83.017 (INF DriverVer 05/28/2002, 6.83.017.0)
- License: proprietary Matrox Video Software License Agreement (no redistribution)
- Availability: external (Matrox's own archive server, HTTPS only)

## Windows 9x support evidence

- Matrox "Drivers for older/legacy Matrox products" grid, https://video.matrox.com/en/apps/drivers/graphics/previous/legacy/
  (reached after the notice at https://video.matrox.com/en/apps/drivers/graphics/previous; opened 2026-09-29):
  "Matrox Millennium G400 / Matrox Millennium G400 MAX ... Win 98: 6.83.017 08jul02, Win Me: 6.83.017 08jul02";
  Millennium G200, Mystique G200, MGA G200, G200 MMS: 6.82.016 27feb02 for Win 98 and Win Me.
  The G450/G550 are not in that grid (they are current G-series products); the Win ME/9x section of the "Previous
  Releases" page no longer lists any file.
- The archive https://ftp.matrox.com/pub/mga/archive/win_9x/2002/ lists w9x682notes.txt, w9x_682.exe, w9x_683.exe,
  w9x_683beta.exe; 2002 is the last year folder, so 6.83 is the last 9x release.
- w9x682notes.txt: "Supported Products G200 G400 G450 G550 ... Supports Win98 and WinME only. ICD included."
- 6.83 INFs (G200.inf, G200MMS.inf, G400.inf, G450.inf, G550.inf) cover G200 (0520/0521), G400/G450 (0525) and
  G550 (2527), so 6.83 is used for all G-series cards. Windows 95 is not supported ("Supports Win98 and WinME only").
- ReadEng.txt: "The setup program will only install software if a Matrox graphics card model supported by the setup
  program is installed in your computer."

## Download

- URL: https://ftp.matrox.com/pub/mga/archive/win_9x/2002/w9x_683.exe (200, directory listing enabled)
  - http://ftp.matrox.com/... answers "HTTP/1.1 522" (Cloudflare origin timeout), so only HTTPS is listed.
  - Last-Modified: Fri, 05 Jul 2002 14:01:14 GMT
- File: w9x_683.exe, 6,654,452 bytes
- SHA-256: d2664b8e4f60d2be73e8d5ce4319477680558f58f3cfa9a2abe4065b372003f1
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- The package has no license text (searched the readme files, Setup.exe and SetupRes.dll).
- Matrox's current license for its graphics drivers, the "Matrox Video Software License Agreement" (SLA03202026),
  is linked from the "Previously Released Drivers" notice that must be accepted before the legacy drivers are shown:
  https://video.matrox.com/apps/video_drivers/_content/pdf/graphics_drivers_eula.pdf. LICENSE.TXT transcribes its
  opening and full END USER LICENSE (pages 1-2; rendered on the host with the Windows PDF API and read) and points to
  the PDF for the rest.
- No redistribution: "3. No right to recopy, publish, display, network, rent, loan, lend, assign, sell, distribute,
  license, sublicense, alter, modify ... any Software in any manner whatsoever is hereby given". Therefore external.

## Security

None known (not verified against NVD in this session).

## Install behaviour

- Outer file: WinZip Self-Extractor (1995-96 stub, "WinZip(R) Self-Extractor ... Nico Mak Computing"); 7-Zip opens it
  as a zip (embedded stub 30,313 bytes), 72 files in the root: Setup.exe, SetupRes.dll, INFs, compressed driver files.
- Beacon: `Install: unzip {pf}\Drivers\Matrox G-series` (self-extracting ZIP counts as ZIP), then
  `After: run "{dir}\Setup.exe"`. The WinZip stub's own behaviour and switches were not tested.
- Setup.exe strings show command-line keywords (SILENT, REBOOT, LANG, NORESET_DRIVER, COPYALL ...), but Matrox does
  not document them; not used.
- Add/Remove Programs name: unknown (strings show "Matrox PowerDesk"; the package has pduninst.ex_). The entry uses
  `Uninstall: files`, which removes only the unpacked folder; the Notice says so.

## Hardware IDs

VEN/DEV pairs in the five INFs (4; entries are further split by SUBSYS):

- PCI\VEN_102B&DEV_0520
- PCI\VEN_102B&DEV_0521
- PCI\VEN_102B&DEV_0525
- PCI\VEN_102B&DEV_2527

## Verification notes

- Opened: the Matrox legacy grid and previous-drivers pages, the ftp archive listings, w9x682notes.txt, the file
  (downloaded; 7-Zip listing/extraction of INF, TXT and setup files on the host; nothing executed), the EULA PDF.
- The per-file pages linked from the grid (e.g. .../legacy/files/w9x_683.php) now answer 404; the files are reached
  through the ftp.matrox.com archive listing instead.
- Not verified: behaviour on real hardware; WinZip SFX switches; Add/Remove name.