# Matrox PowerDesk 4.12.013 for Windows 95/98 (Millennium, Mystique) - Beacon 98 record

- Date checked: 2026-09-29
- Package: 1677_412.exe, "Matrox PowerDesk for Windows 95/98 Revision 4.12.013" (readme dated 1998.07.22)
- Version: 4.12.013
- License: Matrox proprietary; the package also carries Microsoft's "Windows 95 and 98 Driver Library" license text
  (see License)
- Availability: external (Matrox's own archive server, HTTPS only)

## Windows 9x support evidence

- Matrox legacy grid (https://video.matrox.com/en/apps/drivers/graphics/previous/legacy/, opened 2026-09-29):
  "Matrox Mystique 220 - Win 98: 4.12.013 07oct98, Win Me: available with OS"; the same for "Matrox Mystique" and
  "Matrox Millennium". The grid links the file page w9x_412.php (now 404).
- The file is in https://ftp.matrox.com/pub/mga/archive/win_9x/1998/ as 1677_412.exe (other 1998 files: 1677_411.exe,
  split-disk zips). The readme inside says revision 4.12.013 and "Windows 95/98".
- mgapdx64.inf lists "Matrox Millennium PCI" (0519), "Matrox Mystique PCI" (051A), "Matrox Millennium II AGP" (051F)
  and MGA-G200/Mystique G200/Millennium G200 AGP (0521 with SUBSYS). Newer drivers exist for Millennium II and G200.
- Windows ME: Matrox says "available with OS", so the package is listed for 95 and 98 only.

## Download

- URL: https://ftp.matrox.com/pub/mga/archive/win_9x/1998/1677_412.exe (200; http:// answers 522)
- Last-Modified: Tue, 06 Oct 1998 15:48:22 GMT
- File: 1677_412.exe, 1,657,522 bytes
- SHA-256: 98bc33adc675618a44bf0676f03c61b483a57bcc02094e647339ffa3057911ee
- Published checksum: none. Authenticode: not signed (PowerShell reports "UnknownError" for this old stub).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- The archive contains license.txt: "MICROSOFT WINDOWS 95 AND 98 DRIVER LIBRARY - MICROSOFT SOFTWARE LICENSE ...
  Microsoft grants to you the right to use and to reproduce and distribute all or a portion of the Windows 95 and/or 98
  Driver Library ("Software") provided that (i) the Software is not distributed for profit; ... (iii) the Software may
  NOT be modified". It also contains Microsoft's INSTALL.TXT. These look like Microsoft Driver Library boilerplate
  bundled with the package; the text names Microsoft as owner, and it is not certain that it grants rights in
  Matrox's files. Beacon's rule is to host only when certain, so the package is external.
- LICENSE.TXT holds that file unchanged (part 1) and Matrox's current driver license (part 2, which forbids
  redistribution).

## Security

None known (not verified against NVD in this session).

## Install behaviour

- WinZip self-extractor (stub 19,715 bytes); zip root holds setup.exe, setup.ini, mgapdx64.inf, readme.txt, the
  driver files.
- Readme: "To install both Matrox PowerDesk and the Matrox display driver, start the included "setup" program ...
  After PowerDesk is installed, the setup program automatically changes the Windows 95/98 display driver, then prompts
  you to restart your computer." Default folder "\Program Files\Matrox MGA PowerDesk". mga.ini customisation exists;
  no documented silent switch.
- Readme: DirectX 2 or later is needed for DirectDraw/Direct3D acceleration; answer "No" if a DirectX setup offers to
  replace the display driver.
- Beacon: `Install: unzip {pf}\Drivers\Matrox Millennium`, `After: run "{dir}\setup.exe"`, `Uninstall: files`.
  Add/Remove Programs name: unknown.

## Hardware IDs

VEN/DEV pairs in mgapdx64.inf (4):

- PCI\VEN_102B&DEV_0519
- PCI\VEN_102B&DEV_051A
- PCI\VEN_102B&DEV_051F
- PCI\VEN_102B&DEV_0521

## Verification notes

- Opened: Matrox legacy grid, ftp listing, the file (downloaded; 7-Zip listing and extraction of INF/TXT on the host;
  not executed), readme.txt, INSTALL.TXT, license.txt.
- Not verified: behaviour on real hardware; whether Microsoft's Driver Library license was meant to cover this
  Matrox download.