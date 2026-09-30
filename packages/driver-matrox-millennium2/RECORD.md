# Matrox PowerDesk 4.33.045 for Windows 95/98 (Millennium II) - Beacon 98 record

- Date checked: 2026-09-29
- Package: w9x_433c.exe, "Matrox PowerDesk for Windows 95/98 Revision 4.33.045" (readme dated 1999.02.25)
- Version: 4.33.045 (INF DriverVer 04/12/1999, 4.33.00.0045)
- License: proprietary Matrox Video Software License Agreement (no redistribution)
- Availability: external (Matrox's own archive server, HTTPS only)

## Windows 9x support evidence

- Matrox legacy grid (opened 2026-09-29): "Matrox Millennium II - Win 98: 4.33.045 13may99, Win Me: available with OS",
  linking w9x_433c.php (now 404). The archive https://ftp.matrox.com/pub/mga/archive/win_9x/1999/ has w9x_433c.exe and
  w9x_433m.exe (both 4.33.045; the "m" build's INF lists only G100/G200 boards, the "c" build adds Millennium II PCI
  051B and AGP 051F). w9x_433c.exe is the one for the Millennium II.
- Readme: "This product includes a Windows 95/98 display driver AND the Matrox PowerDesk for Windows 95/98."

## Download

- URL: https://ftp.matrox.com/pub/mga/archive/win_9x/1999/w9x_433c.exe (200; http:// answers 522)
- Last-Modified: Thu, 26 Aug 1999 16:12:40 GMT
- File: w9x_433c.exe, 1,819,175 bytes
- SHA-256: 6ac85ae793a02636a84658191caa5b21d2adbaf052e3eff7a1f2fa2500c6728f
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license text in the package. LICENSE.TXT transcribes Matrox's current driver license (see driver-matrox-g-series
  record for the source PDF); it forbids redistribution. Therefore external.

## Security

None known (not verified against NVD in this session).

## Install behaviour

- WinZip self-extractor; all files are in a folder w9x433c\ (setup.exe, setup.ini, mgapdx64.inf, readme.txt ...).
- Beacon: `Install: unzip {pf}\Drivers\Matrox Millennium II strip 1`, `After: run "{dir}\setup.exe"`,
  `Uninstall: files`. Setup installs PowerDesk to "\Program Files\Matrox MGA PowerDesk", changes the display driver
  and asks to restart. No documented silent switch; Add/Remove Programs name unknown.

## Hardware IDs

VEN/DEV pairs in mgapdx64.inf (5):

- PCI\VEN_102B&DEV_051B
- PCI\VEN_102B&DEV_051F
- PCI\VEN_102B&DEV_0520
- PCI\VEN_102B&DEV_0521
- PCI\VEN_102B&DEV_1001

## Verification notes

- Opened: Matrox legacy grid, ftp listing, the file (downloaded; listed/extracted with 7-Zip; not executed), readme,
  INF.
- Not verified: real hardware.