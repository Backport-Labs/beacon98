# Promise FastTrak series driver 2.00.0.34 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Promise "FastTrak Series windows driver" (FastTrak, FastTrak66, FastTrak100, FastTrak100 TX2/TX4, FastTrak TX2000 IDE RAID
  controllers), Promise Technology, Inc.
- Version: 2.00.0.34 (Download Center release date 2003/05/16; Win9x-ME\FASTTRAK.INF DriverVer=04/25/2003, 2.00.0.34; README
  "Microsoft Windows9x-ME miniport driver 2.00.0.34")
- License: none in the package; Promise website Terms of Use forbid reproduction without consent
- Availability: external (Promise's own Download Center)

## Windows 9x support evidence

- Promise Download Center, Legacy products -> FastTrak -> FastTrak TX (handler
  https://www.promise.com/Ajax/DownloadCenterGetDLHandler.ashx?type=getDL&id=..., opened 2026-09-29) [V]:
  - FastTrak100 TX2 (model 1753): "FastTrak100 TX/LP Windows Driver | 98/Me/NT4/2000/XP/Server2003 | 2003/05/16 | 2.00.0.34" (file id 3516)
  - FastTrak TX2000 (model 1657): "FastTrak TX2000 Driver | 98/Me/NT4/2000/XP/Server2003 | 2003/05/16 | 2.00.0.34" (file id 2936)
  - Both file ids deliver the same bytes (same SHA-256, same published MD5).
  - FastTrak100 (1729) lists only up to 2.00.0.25 (2002/04/18); FastTrak100 TX4 (1777) up to V2.00 B11 (2001/10/25). Their PCI IDs are
    also in this 2.00.0.34 INF (DEV_4D30 SUBSYS_4D39105A/4D32105A, DEV_6268), but Promise does not list 2.00.0.34 for them.
- Windows 95: the Download Center says "98/Me" for 2.00.0.34 (older versions say 9x). Systems given as 98, ME.

## Download

- URL: https://www.promise.com/DownloadFile.aspx?DownloadFileUID=3516 (Content-Disposition "3 FastTrak Series windows driver
  2.00.0.34.zip"); also https://www.promise.com/DownloadFile.aspx?DownloadFileUID=2936 (same file). http:// answers 303 to https.
- File: saved here as fasttrak_2.00.0.34.zip, 261,773 bytes
- SHA-256: 5756a8e35d1173244496508b69c5842a21c9645e0d4e55baa43185ac930dbf61
- Published checksum: Promise lists MD5 0ca294b2f1b5786a22e0189d609610f6 for both ids; the download matches.
- The client would save it as "3516" (query URL, FORMAT.md rule); `unzip` must detect ZIP by content.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-promise-fasttrak -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

Same as driver-promise-ultra: no licence text in the zip, none shown before download; Promise Terms of Use forbid reproduction
without written consent. External only. LICENSE.TXT quotes the terms.

## Security

NVD keyword "Promise FastTrak": 0 results. No known CVEs.

## Hardware IDs (from Win9x-ME\FASTTRAK.INF)

5 distinct PCI IDs, vendor 105A: DEV_4D33 (FastTrak, PDC20246), DEV_4D38 (FastTrak66, SUBSYS_4D39105A), DEV_4D30 (FastTrak100,
SUBSYS_4D39105A or 4D32105A), DEV_6268 (FastTrak100 TX2/TX4, PDC20270), DEV_6269 (FastTrak TX2000, PDC20271).

## Install behaviour

- INF-only driver disk. Zip layout (no top folder): README.TXT, TXTSETUP.OEM, FASTTRAK, NT4\, Win2000\, Win9x-ME\ (FASTTRAK.INF,
  fasttrak.mpd, FTTKVSD.VXD, PU66VSD.VXD, PTISTP.DLL, FastTrak.cat), WinNet\, WinXP\.
- Beacon: unzip to {pf}\Drivers\promise-fasttrak; the user updates the controller in Device Manager with {dir}\Win9x-ME.
- The INF writes an Add/Remove entry under HKLM\...\Uninstall\Fasttrak (DisplayName = controller name). Beacon's Uninstall only removes
  the unpacked files.
- Promise's FastBuild/FastCheck management utility is a separate download; not included.

## Verification notes

- Opened: Download Center JSON for models 1753, 1657, 1729, 1777; the zip (7-Zip on the host, nothing executed); README.TXT; FASTTRAK.INF.
- Not verified: behaviour on real hardware; Windows 95.
