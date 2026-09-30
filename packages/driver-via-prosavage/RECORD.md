# VIA / S3 ProSavage graphics driver 13.01.03 - Beacon 98 record

- Date checked: 2026-09-29
- Package: 130103Util.zip, "ProSavage Graphics Driver" with utilities, S3 Graphics (VIA)
- Version: 13.01.03 (INF ps5333ut.inf DriverVer 04/08/2003, 4.14.10.0004)
- License: none found in the package; VIA site "All Rights Reserved"
- Availability: external (VIA's own download server)

## Windows 9x support evidence

- VIA Driver Download Portal (https://download.viatech.com/en/support/driversSelect.jsp; queried 2026-09-29 through
  its own form endpoints DriverDownloadSelectAjaxSvl / DriverDownloadSubmitAjaxSvl): Windows 98SE, Integrated
  Graphics, "S3 ProSavage IGP (PL133/T, KL133/A & KM133/A)": "ProSavage Graphics Driver Dated: 06-May-2003 ...
  Download version 13.01.03 w/Util OS supported Windows 95,Windows ME,Windows 98SE,Windows 98". It is the only
  entry for that product.

## Download

- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/drivers/video/ProSavage/130103Util.zip (the link the VIA portal
  gives; VIA's CloudFront distribution). http:// answers 301 to https.
- File: 130103Util.zip, 5,332,911 bytes
- SHA-256: 4701ba7e16e9e98fa4fc0455e31477a1422bdcdac5f228158c378c885af45e40
- Published checksum: none.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license text found: none among the readable files, none in _USER1.CAB (deflate streams searched on the host),
  and SETUP.ISS shows no license dialog. The portal shows no terms; VIA's site says "All Rights Reserved". Another
  VIA driver package examined for Beacon (driver-via-hyperion) ships the "VIA Software License Agreement", which says
  "You may not transfer or distribute this software to any third party". No permission to redistribute, so external.

## Security

None known (not verified against NVD in this session).

## Install behaviour

- Plain zip, one folder S3wIShld\ with an InstallShield 5 setup (SETUP.EXE, SETUP.INS, _SYS1.CAB, _USER1.CAB),
  SETUP.ISS (SdWelcome, SdStartCopy, SdFinishReboot BootOption=3; Application Name "ProSavage Driver", Company
  "S3 Graphics, Inc."), S3UNINST.EXE, ps5333ut.inf, savagenb.cat.
- Beacon: `Install: unzip {pf}\Drivers\VIA ProSavage strip 1`, `After: run "{dir}\SETUP.EXE"`, `Uninstall: files`.
  InstallShield 5 setups normally accept `-s` with setup.iss, but BootOption=3 restarts the computer, so it is run
  interactively. Add/Remove Programs name: unknown.

## Hardware IDs

VEN/DEV pairs in ps5333ut.inf (2):

- PCI\VEN_5333&DEV_8A25
- PCI\VEN_5333&DEV_8A26

## Verification notes

- Opened: the VIA portal and its product listing, the file (downloaded; 7-Zip listing/extraction of INF/ISS/INI on
  the host; not executed).
- Not verified: real hardware; whether KM133 boards need the separate Twister or ProSavage driver in every case.