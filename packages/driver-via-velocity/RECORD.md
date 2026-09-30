# VIA Velocity Gigabit Ethernet drivers 3.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: "VT6120/VT6122/VT6130/VT6132 Drivers package", VIA Networking Technologies, Inc.
- Version: package release 3.1 (readme.txt "Release 3.1 Oct, 2007"; portal "VIA Velocity Family Gigabit LAN
  driver Dated: 07-Aug-2008"). The Windows 98SE/ME driver inside is v1.59 (WINX86.txt "v1.59 Sep, 2007";
  INF DriverVer 09/21/2007, 1.59.0.117).
- License: none found (proprietary; no redistribution right granted) - see LICENSE.TXT
- Availability: external (VIA's download server)
- Section: System

## Windows 9x support evidence

- XP_Srv2003_2K_ME_98SE\X86\WINX86.txt: "NDIS Driver for Windows 98SE/ME/2000/XP, Server 2003 x86 Edition /
  v1.59 Sep, 2007" and "GETND5AV.SYS The NDIS5 driver for Windows 98/98SE/ME."
- getndis.inf header: "Netcard setup information file for Windows 98SE/ME/2000/XP/Server2003 x86 Edition",
  Signature "$Chicago$", 9x install via DeviceVxDs "getnd5av.sys".
- UNATTEND\W9x\unatdw9x.txt: "Unattended Installation on Windows 95/98/ME".
- VIA's portal lists the download for Windows 98, 98SE and ME. The folder name and INF header say 98SE/ME, the
  driver line says 98/98SE/ME; the entry claims only 98SE and ME. No Windows 95 driver is in the package.
- Newest 9x-capable Velocity package on VIA's portal (other entries: "vt6120_vt6122_vt6130_vt6132_drivers31_full.zip"
  3.1 dated 01-Aug-2008, 16.8 MB, not examined; older v2.x packages).

## Download

- Portal: https://download.viatech.com/en/support/driversSelect.jsp (Microsoft Windows > Windows 98SE >
  Ethernet (Networking/LAN) > "VIA Velocity VT6120, VT6122, 6130, 6132 Gigabit Ethernet").
- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/velocity_driver_v31_via.zip
  - http:// answers 301 to the https address.
  - Last-Modified: Tue, 13 Jan 2015 12:28:45 GMT (Amazon S3 / CloudFront bucket used by VIA's portal).
- File: velocity_driver_v31_via.zip, 5,031,043 bytes
- SHA-256: bc4a491216a534723da445152978ba61872b1536d7c915a0f66fa423e0c9cae1
- Published checksum: none published by VIA.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-velocity -DisableRemediation` on
2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license text in the archive (readme.txt, *.txt, DriversRelease31.pdf) or on the portal; the INF says only
  "Copyright (C) VIA Networking Technologies, Inc.". Nothing permits redistribution, so `Availability: external`.

## Security

NVD keyword searches "velocity gigabit" (0 results) and "VIA Velocity" (20 results, all unrelated products:
Velocity Security Management System, Apache Velocity templates, etc.), 2026-09-29. No known issues found.

## Hardware IDs (XP_Srv2003_2K_ME_98SE\X86\getndis.inf)

1 distinct VEN/DEV pair (plus many SUBSYS variants): PCI\VEN_1106&DEV_3119 - "VIA Networking Velocity-Family
Giga-bit Ethernet Adapter" (VT6120, VT6122, VT6130, VT6132). Not emulated by VirtualBox, QEMU or VMware.

## Install behaviour

- Plain ZIP without a top folder; multi-OS package (CE, DOS, NetWare, Linux, Mac OS X, Solaris, PXE/RPL boot
  ROMs, Vista, XPE). The Windows 98SE/ME driver is in XP_Srv2003_2K_ME_98SE\X86 (getndis.inf, GETND5AV.sys,
  GETND5BV.sys, getndis.cat, WNDI.DLL, VUINS16/32.DLL, winsetup\WinSetup.exe v3.32 with the same switches as
  the Rhine package).
- Beacon: `unzip {pf}\Drivers\VIA-Velocity`; the user points Device Manager at
  {pf}\Drivers\VIA-Velocity\XP_Srv2003_2K_ME_98SE\X86. Windows 98 may ask for the Windows CD.
- Uninstall: `files`.

## Verification notes

- Opened: the portal result page, the archive listing, readme.txt, WINX86.txt, unatdw9x.txt, getndis.inf.
  Nothing was executed.
- Not verified: behaviour on real hardware; Windows 98 first edition.
