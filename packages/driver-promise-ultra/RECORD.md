# Promise Ultra family driver 2.00.0.43 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Promise "Ultra Family Windows driver" (Ultra33, Ultra66, Ultra100, Ultra100 TX2, Ultra133 TX2 IDE controllers),
  Promise Technology, Inc.
- Version: 2.00.0.43 (Download Center release date 2003/10/15; Win9x-Me\ULTRA.INF DriverVer=05/16/2003, 2.0.0.43; README
  "Microsoft Windows9x-ME miniport driver 2.00.0.43")
- License: none in the package; Promise website Terms of Use forbid reproduction without consent
- Availability: external (Promise's own Download Center)

## Windows 9x support evidence

- Promise Download Center, Legacy products -> Ultra -> Ultra 133 TX2 (data from the page's own handler
  https://www.promise.com/Ajax/DownloadCenterGetDLHandler.ashx?type=getDL&id=2210, opened 2026-09-29): "Ultra Family Windows driver",
  "Ultra Family driver for Windows 95/98/ME/NT4/XP/2000/2003 Supported cards: Ultra 33, Ultra 66, Ultra 100, Ultra 100 TX2, Ultra 133 TX2",
  platform "Windows 95/98/ME/NT4/XP/2000/2003", release_date "2003/10/15", versions 2.00.0.43 (file id 3258), 2.00.0.42, 2.00.0.39,
  2.00.0.29. [V]
- The zip has a Win9x-Me folder with ULTRA.MPD, ULTRA.INF, PTISTP.DLL, PU66VSD.VXD, SMARTVSD.VXD. (README also lists ADVPACK.DLL,
  which is not in the zip; Windows 98/ME ship ADVPACK.DLL with Internet Explorer.)

## Download

- Download Center: https://www.promise.com/Support/downloadcenter (Legacy products tab; no account needed)
- URL: https://www.promise.com/DownloadFile.aspx?DownloadFileUID=3258 (Content-Disposition filename "1 ultra133 driver b43.zip").
  http://www.promise.com/... answers 303 to the https address.
- File: saved here as ultra133_driver_b43.zip, 146,851 bytes
- SHA-256: 8d38cdec2ff7204d14c33e940ca424875dddae9088d1f23689225ca455adaa97
- Published checksum: Promise lists MD5 c6d7ad7d841850a384ba9f6cc12d1ecd; the download's MD5 matches.
- Note for the client: the URL has a query, so under FORMAT.md rules the client saves it as "3258" (the last parameter value). The
  file is a plain ZIP; `unzip` must detect ZIP by content, not by extension.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-promise-ultra -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

No licence text in the zip (README has none) and no agreement is shown before the download. Promise's Terms of Use
(https://www.promise.com/TermsOfUse): "no portion of the documents or information on this website may be reproduced in any form or by
any means without the express written consent of PROMISE" and "Nothing on any PROMISE website shall be construed as conferring any
license". Not hostable -> external. LICENSE.TXT quotes these terms.

## Security

NVD keyword "Promise Ultra133": 0; "Promise FastTrak": 0. No known CVEs.

## Hardware IDs (from Win9x-Me\ULTRA.INF)

6 PCI IDs, vendor 105A (Promise): DEV_4D69 (Ultra133 TX2, PDC20269), DEV_4D68 (Ultra100 TX2, PDC20268), DEV_4D30 (Ultra100, PDC20267,
matched with SUBSYS_4D33105A), DEV_0D30 (Ultra100, PDC20265, SUBSYS_4D33105A), DEV_4D38 (Ultra66, PDC20262, SUBSYS_4D33105A),
DEV_4D33 (Ultra33, PDC20246). The same chips on FastTrak cards or motherboards with other subsystem IDs are not matched by the
subsystem-qualified lines.

## Install behaviour

- INF-only driver disk. Zip layout: ultra133_driver_b43\ with README.TXT, TXTSETUP.OEM, ULTRA and NT4\, WIN2000\, Win2003\, Win9x-Me\,
  WinXP\ folders.
- Beacon: unzip to {pf}\Drivers\promise-ultra; the user then updates the driver in Device Manager and points it at
  {dir}\ultra133_driver_b43\Win9x-Me.
- The INF itself writes an Add/Remove Programs entry under HKLM\...\Uninstall\Ultra (DisplayName = the controller name, e.g.
  "Win9x-ME Promise Ultra133 TX2 (tm) IDE Controller", UninstallString "RunDll32 ptistp.dll,LaunchINFSection ...").
  Beacon's Uninstall only removes the unpacked files.

## Verification notes

- Opened: Download Center page and its JSON handlers, Terms of Use, the zip (7-Zip on the host, nothing executed), README.TXT, ULTRA.INF.
- Not verified: behaviour on real hardware.
