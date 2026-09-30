# VIA Rhine Family Fast Ethernet driver 3.84A - Beacon 98 record

- Date checked: 2026-09-29
- Package: VIA Rhine Family NDIS5 driver ("VIA Rhine Family Driver"), VIA Technologies, Inc.
- Version: 3.84A (INF DriverVer 06/16/2009, 3.84.0.1; WIN.txt "v3.84 May, 2009"; portal "Dated: 29-Jan-2009")
- License: none found (proprietary; no redistribution right granted) - see LICENSE.TXT
- Availability: external (VIA's download server)
- Section: System
- Recommendation: 3.84A for Rhine (VT86C100A), Rhine II (VT6102, VT8231/8233/8235/8237 and VT6107 integrated)
  and Rhine III (VT6105/6106, VT6105M, VT6115, VT8251) on Windows 98 SE and ME.

## Windows 9x support evidence

- X86\WIN.txt inside the archive: "VIA Rhine Family Fast Ethernet Adapter / NDIS Driver for Windows
  98SE/ME/2000/XP/SRV2003/Vista / v3.84 May, 2009" and "FETND5AV.SYS The NDIS5 driver for Windows 98SE/ME."
- X86\FETNDIS.inf header: "Netcard setup information file for Windows 98SE/ME/2000/XP/SRV2003/Vista",
  Signature "$Chicago$", 9x install via DeviceVxDs "fetnd5av.sys".
- VIA's portal lists "OS supported Windows 98, Windows 95, Windows 2000, Windows ME, Windows NT, Windows 98SE"
  for this download, but the files themselves only name 98 SE and ME (NDIS5 driver). Windows 95 and 98 first
  edition are therefore NOT claimed here. For those, VIA still lists older packages (e.g. VT86c100a.zip "100a",
  6102v25VIA.zip "25") which were not examined further.
- It is the newest Windows 9x Rhine driver on VIA's portal (the other listed downloads are 1.14 NDIS6/Vista,
  "6.0" multi-OS bundle whose 98SE/ME folder holds the same FETND5AV.SYS/FETNDIS.inf family, and older
  per-chip packages).

## Download

- Portal: https://download.viatech.com/en/support/driversSelect.jsp (Microsoft Windows > Windows 98SE >
  Ethernet (Networking/LAN) > e.g. "VT6105/L/LOM and VT6106/H/L/S series (Rhine III)"; the same file is listed
  for every Rhine chip). The portal is a form (POST to /DriverDownloadSubmitAjaxSvl); the resulting page links
  directly to the file below.
- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/via_rhine_ndis5_v384a.zip
  - http://d34vhvz8ul1ifj.cloudfront.net/... answers 301 to the https address (so no plain-HTTP location).
  - Server: Amazon S3 / CloudFront bucket used by VIA's portal for all its driver links. Last-Modified: Tue,
    13 Jan 2015 13:02:59 GMT.
- File: via_rhine_ndis5_v384a.zip, 1,699,164 bytes
- SHA-256: cc032d30ad216b609b53e55da252ce4d9619498a437f99a8cd7e9cc6a31f6dc6
- Published checksum: none published by VIA.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-rhine -DisableRemediation` on
2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license text in the archive or on the portal; the INF says only "Copyright: VIA Technologies, Inc.".
  LICENSE.TXT records this. Nothing permits redistribution, so `Availability: external`.

## Security

NVD keyword searches "VIA Rhine" and "fetnd5" (services.nvd.nist.gov API, 2026-09-29): 0 results.

## Hardware IDs (X86\FETNDIS.inf)

4 distinct VEN/DEV pairs (the INF also lists many SUBSYS variants of the same pairs):

- PCI\VEN_1106&DEV_3043 - "VIA VT86C100A Rhine Fast Ethernet Adapter"
- PCI\VEN_1106&DEV_3065 - "VIA Rhine II Fast Ethernet Adapter" (VT6102, VT8231/8233/8235/8237, VT6107)
- PCI\VEN_1106&DEV_3106 - "VIA Rhine III Fast Ethernet Adapter" (VT6105/6106, VT6115, VT8251)
- PCI\VEN_1106&DEV_3053 - "VIA Rhine III Management Adapter" (VT6105M)

Not usable in the common emulators (VirtualBox, QEMU, VMware do not emulate VIA Rhine). Useful for real
VIA-chipset motherboards and D-Link DFE-530TX / later DFE-530TX+ cards (D-Link's own packages use the same
VIA driver with D-Link SUBSYS IDs; the generic VEN/DEV entries here match them too).

## Install behaviour

- Plain ZIP: top folder VIA_Rhine_NDIS5_V384A\ with X86\ (Windows 9x/2000/XP/Vista 32-bit) and X64\.
  X86 holds FETNDIS.inf, FETND5AV.sys (9x), FETND5BV.sys (NT), netvt.cat, WINNDI.DLL, VUINS16.DLL, VUINS32.DLL,
  WIN.txt, and winsetup\ (VIA's WinSetup.exe/WinUinst.exe, v3.32, documented switches `-i -d <dir> -w <Windows
  CD> -s -b`, `-r`).
- Beacon: `unzip {pf}\Drivers\VIA-Rhine strip 1`; the user then points Device Manager (Update Driver, "Specify a
  location") at {pf}\Drivers\VIA-Rhine\X86. Windows 98 may ask for the Windows CD for its networking
  components. WinSetup.exe could automate this, but the readme warns that it does not handle long file names,
  and it was not tested; the entry uses the manual INF route.
- Uninstall: `files` (removes the unpacked folder; the device stays installed in Windows until removed in
  Device Manager).

## Verification notes

- Opened: VIA's portal form and its result pages (for 98SE and ME and all Rhine chips), the archive listing,
  WIN.txt, winsetup.txt, FETNDIS.inf. Nothing was executed.
- Not verified: behaviour on real hardware; whether 98 first edition works despite the 98SE/ME wording.
