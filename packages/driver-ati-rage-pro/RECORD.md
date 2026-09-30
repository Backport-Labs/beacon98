# ATI Rage Pro / Rage XL display driver 4.13.2655 - Beacon 98 record

- Date checked: 2026-09-29
- Package: wme-j5-30-1-b02.exe, "Windows Display Driver for ATI RAGE PRO / RAGE XL", Version 4.13.1.2655, April 2002
- Version: 4.13.2655 (as AMD lists it; INF DriverVer 02/28/2002, 4.13.1.2655)
- License: proprietary ATI End User License Agreement (distribution forbidden)
- Availability: external (AMD's own download server)

## Windows 9x support evidence

- AMD pages .../legacy-graphics/rage-series/ati-rage-pro.html, ati-rage-xl.html and ati-rage-lt-pro.html (opened
  2026-09-29): "Windows ME 98 Driver Display Driver Bundle Revision Number 4.13.2655 File Size 11 MB Release Date
  2002-04-02", link https://www2.ati.com/drivers/wme-j5-30-1-b02.exe.
- The readme inside (wme-j5-30-1-b02.rtf) says only: "The display driver included in this package is for Microsoft
  Windows Millennium." AMD's page files it under "Windows ME 98". Windows 98 support therefore rests on AMD's page;
  Windows 95 is not claimed. Older Rage II cards have a separate 4.10.2420 package (1998) on AMD's Rage II page.
- The All-In-Wonder Pro capture components "require DirectX 8.1".

## Download

- URL: https://drivers.amd.com/drivers/wme-j5-30-1-b02.exe (needs `Referer: https://www.amd.com/`);
  https://www2.ati.com/... and http://www2.ati.com/... redirect there.
- Last-Modified: Tue, 08 Jul 2003 18:11:16 GMT
- File: wme-j5-30-1-b02.exe, 10,751,795 bytes
- SHA-256: 7344838553d41fe9ac74b42d3fd159c9a8bf33b651cd75008e21523568559a26
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT: ATIDrive\license.txt from the package, unchanged ("End User License Agreement", ATI Technologies Inc.).
- "2. Restrictions ... you may not ... b) modify, network, rent, lend, loan, distribute or create derivative works
  based upon the Software in whole or in part". Therefore external.

## Security

None known (not verified against NVD in this session).

## Install behaviour

- Self-extracting cabinet; unpacks to a folder (readme: C:\j5-30-1-b02) and starts ATI SETUP (InstallShield 5).
- setup.iss: Welcome, License, Finish (BootOption=0). Silent install not documented; entry runs it interactively.
- Add/Remove Programs name: "ATI Display Driver" (readme uninstall section).
- INSTALL.INI: `Path = -1,ATIDRIVE,ATIi9xAE.INF,-1`.

## Hardware IDs

VEN/DEV pairs in ATIi9xae.inf (12):

- PCI\VEN_1002&DEV_4742
- PCI\VEN_1002&DEV_4744
- PCI\VEN_1002&DEV_4749
- PCI\VEN_1002&DEV_474D
- PCI\VEN_1002&DEV_474E
- PCI\VEN_1002&DEV_474F
- PCI\VEN_1002&DEV_4750
- PCI\VEN_1002&DEV_4752
- PCI\VEN_1002&DEV_4C42
- PCI\VEN_1002&DEV_4C49
- PCI\VEN_1002&DEV_4C4D
- PCI\VEN_1002&DEV_4C50

## Verification notes

- Opened: the three AMD pages, the file (downloaded, listed and extracted with 7-Zip on the host, not executed),
  readme, INF, INSTALL.INI, SETUP.ISS, license.txt.
- Not verified: Windows 98 (non-ME) operation; real hardware.