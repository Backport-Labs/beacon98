# VIA / S3 ProSavageDDR graphics driver 13.01.09 - Beacon 98 record

- Date checked: 2026-09-29
- Package: S3_wIShldlogo.zip (folder ProSavDDR_130109_WME_W_IShld_logod), S3 Graphics (VIA)
- Version: 13.01.09 (INF psav5333.inf DriverVer 12/24/2003, 4.14.10.0010)
- License: none found in the package; VIA site "All Rights Reserved"
- Availability: external (VIA's own download server)

## Windows 9x support evidence

- VIA Driver Download Portal (queried 2026-09-29): Windows 98SE, Integrated Graphics, "S3 Pro SavageDDR IGP
  (KM/KN/PM/P4M/P4N266)": "ProSavageDDR Graphics Driver Dated: 07-Jan-2004 ... Download version 13.01.09 W/Ishld OS
  supported Windows 95,Windows ME,Windows 98SE,Windows 98". Only entry for that product.

## Download

- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/drivers/video/ProSavageDDR/S3_wIShldlogo.zip (http:// answers 301
  to https)
- File: S3_wIShldlogo.zip, 5,617,394 bytes
- SHA-256: 7393806730a5d0607ffeb19301a2bb5acab81e941df903dfa0e2cfb5eb5a804d
- Published checksum: none.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

As for driver-via-prosavage: no license text in the package, no terms on the portal, VIA "All Rights Reserved";
other VIA driver packages forbid distribution. External.

## Security

None known (not verified against NVD in this session).

## Install behaviour

- Plain zip, one folder with an InstallShield 5 setup (same layout as the ProSavage package, plus s3tray2.exe).
- Beacon: `Install: unzip {pf}\Drivers\VIA ProSavageDDR strip 1`, `After: run "{dir}\SETUP.EXE"`, `Uninstall: files`.
  Add/Remove Programs name: unknown.

## Hardware IDs

VEN/DEV pairs in psav5333.inf (1):

- PCI\VEN_5333&DEV_8D04

## Verification notes

- Opened: the VIA portal listing, the file (downloaded; listed/extracted with 7-Zip; not executed).
- Not verified: real hardware.