# VIA USB 2.0 driver 2.70p for Windows 98/ME - Beacon 98 record

- Date checked: 2026-09-29
- Package: VIA USB 2.0 Host Controller driver package (English), VIA Technologies, Inc.
- Version: 2.70p (VIA page: "USB 2.0 English only driver package Dated: 03-Oct-2005 ... version 270p"; Release.txt top entry
  "Full Release Version 2.70 * 2005/09/21"). 9x EHCI INF WIN98&ME\USB2VIA.INF: DriverVer=09/26/2003,4.90.3000.10.
- License: none included; no redistribution permission (VIA's page: Win2K/XP package "due to licensing agreements ... cannot be
  distributed online"; the 98/ME folder contains Microsoft's USBPORT.SYS/USBEHCI.SYS/USBHUB20.SYS)
- Availability: external (VIA's own download portal)
- A multi-language build (VIA_USB2_V270p1-L-M.zip) is also served; not downloaded.

## Windows 9x support evidence

- VIA Driver Download Portal, Windows 98SE -> USB -> "USB 2.0 (VT6202, VT6212, VT6214/L)" (opened 2026-09-29): "USB 2.0 English only
  driver package Dated: 03-Oct-2005 --> Download version 270p OS supported Windows 98,Windows XP,Windows 2000,Windows ME,Windows 98SE
  Chips supported USB 2.0 (VT6202, VT6212, VT6214/L)". [V] Not listed for Windows 95.
- ReadMe.doc: "VIA USB 2.0 Host Controller Driver for Windows ME and Windows 98/SE", section "3.0 Driver Installation for Windows
  ME/98SE/98". Release.txt: "Fixed the problem of some USB CD-ROM can not be safely removed under Windows 98SE" (2.53),
  "Fix a wireless USB adapter compatible issue under Win9X" (2.62).
- Controllers: VIA VT6202/VT6212/VT6214 PCI cards and the EHCI function of VIA south bridges (VT8235/VT8237 etc.), PCI ID 1106:3104.
  It does NOT support NEC, ALi, Intel or other EHCI controllers (the INF lists only VEN_1106&DEV_3104).

## Download

- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/VIA_USB2_V270p1-L.zip (http:// answers 301 to https).
  Last-Modified: Tue, 13 Jan 2015 14:36:38 GMT.
- File: VIA_USB2_V270p1-L.zip, 10,285,183 bytes (most of it Windows 2000 QFE files, Q810090_W2K_SP4_X86_*.exe)
- SHA-256: 2a49b9bf300f638b5615daa71da4f64b2322716ffaa5a6cfef675a9145a0b13a
- Published checksum: none. Setup.exe is not Authenticode-signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-usb2 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

No EULA in the package (checked Release.txt, ReadMe.doc, setup files). ReadMe.doc: "No license is granted, implied or otherwise,
under any patent or patent rights of VIA Technologies." No redistribution grant; the 98/ME stack includes Microsoft binaries.
External only. LICENSE.TXT explains this and quotes VIA's chipset licence for reference.

## Security

NVD keyword "VIA USB 2.0 driver": 1 result (CVE-2026-90024, a Linux kernel USB gadget bug, unrelated). No known CVEs.

## Hardware IDs (from the 9x INFs)

- WIN98&ME\USB2VIA.INF: PCI VEN_1106&DEV_3104 (VIA PCI to USB Enhanced Host Controller), plus USB\ROOT_HUB20 and
  USB\HUBCLASS&SUBCLASS_00 (hubs, created by the driver).
- WIN98&ME\VIAUSB.INF: PCI VEN_1106&DEV_3038 (VIA PCI to USB Universal Host Controller, USB 1.1 companion; uses Windows' own uhcd.sys).
- 2 PCI IDs.

## Install behaviour

- Zip layout: VIAUSB2V270-L\ with an InstallShield 5 setup (Setup.exe, SETUP.INS, _USER1.CAB, DATA1.CAB), WIN98&ME\ (USB2VIA.INF,
  VIAUSB.INF, USBEHCI.SYS, USBPORT.SYS, USBHUB20.SYS, VUSTR98.SYS, VUSTRME.SYS, VUSTRBT.SYS, VULFNTR.SYS, VIACB.EXE), filter_nt\, QFE\.
- SETUP.INS strings show it copies the 98/ME files to system32\drivers, installs USB2VIA.inf for PCI\VEN_1106&DEV_3104, and adds
  VIACB.exe to HKLM\Software\Microsoft\Windows\CurrentVersion\Run.
- SETUP.ISS: InstallShield 5 response file with an empty dialog order; `-s` silent mode not tested. The entry runs Setup.exe interactively.
- Beacon: unzip to {pf}\Drivers\via-usb2, then run VIAUSB2V270-L\Setup.exe. Alternative: Device Manager -> the "PCI Universal Serial
  Bus" / unknown EHCI device -> Update Driver -> {dir}\VIAUSB2V270-L\WIN98&ME.
- Add/Remove Programs name: unknown (SETUP.ISS Application Name "VIA USB 2.0 Driver"; not verified). Beacon's Uninstall only removes
  the unpacked files.

## Verification notes

- Opened: VIA portal and results, the zip (7-Zip on the host, nothing executed), INFs, Release.txt, ReadMe.doc text, SETUP.INS strings.
- Not verified: silent install, Add/Remove name, behaviour on real hardware.
