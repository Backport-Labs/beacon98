# VIA 4in1 4.43 chipset drivers - Beacon 98 record

- Date checked: 2026-09-29
- Package: VIA 4in1 drivers ("VIA Service Pack"), VIA Technologies, Inc.
- Version: 4.43 (VIA page says "Dated: 25-Oct-2001"; the files inside are dated up to 2002-09-10). 9x components: VIA INF
  (VIAMACH.INF DriverVer=08/15/2001,5.1.00.0170), VIA AGP VxD (VIAGART.INF DriverVer=07/24/2002,5.00.00.0430), VIA ATAPI/bus master IDE
  (VIAVSD.INF DriverVer=10/18/2001,2.0.950.120, VATAPI.VXD), VIA PCI IRQ miniport (VTNIRQ.PCI, Windows 98 only).
- License: no license text in the package; no redistribution permission (VIA's later licence forbids distribution)
- Availability: external (VIA's own download portal)
- Recommendation: VIA's recommended package for older VIA chipsets on Windows 9x: "This driver package is recommended for use with the
  following chipsets: MVP#, Apollo Pro## series, KT1##, KN1##, KM1##, KT2##, KT333, KN2##, KM2##, P4X2##, P4X3##, P4M2##".
  For KT400 and newer use `driver-via-hyperion` (5.24A). VIA also lists an even older "Retro OS" 4.35 (4in1435v.zip) for 95/98/98SE.

## Windows 9x support evidence

- VIA Driver Download Portal (https://download.viatech.com/en/support/driversSelect.jsp, Windows 98SE -> Hyperion Pro (4in1) chipset
  drivers, opened 2026-09-29): "Retro chipset VIA 4in1 drivers Dated: 25-Oct-2001 ... Download version 4.43 OS supported Windows XP,
  Windows ME,Windows 98SE,Windows 98,Windows 95,Windows 2000,Windows NT". [V]
- The package has separate Inf\WIN95, WIN98, WIN98SE, WINME INFs, AGP\ (9x) and AgpME\ AGP drivers, WIN9X\ and WINME\ IDE drivers.
  README (inside _USER1.CAB, release 4.08 text reused): "Under Windows 95: VIA INF, VIA AGP VxD and VIA IDE Drivers / Under Windows 98
  and Windows 98 Second Edition: All 4 drivers are shown ... Under Millenium: Only VIA INF will shown".

## Download

- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/VIA_4in1_443v.zip (http:// answers 301 to https).
  Last-Modified: Tue, 13 Jan 2015 12:41:07 GMT.
- File: VIA_4in1_443v.zip, 1,109,735 bytes, containing one file 4in1443v.exe (1,188,255 bytes)
- SHA-256: 48d045e40ebf04cf6ca0807cee3456e7724a98f8d6192fb70fc88430685de52d
- Published checksum: none. 4in1443v.exe is not Authenticode-signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-4in1 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No EULA in the package. The only wording is the setup prompt "Clicking Yes means you have read and agreed with the license agreement
  and README." (SETUP.INS) and "Copyright(C) 1999 VIA Technologies, Inc." (README). No redistribution grant -> external only.
- LICENSE.TXT says this and, for reference, quotes the VIA Software License Agreement shipped in 5.24A from the same portal
  ("You may not transfer or distribute this software to any third party").

## Security

NVD keyword "VIA 4in1": 1 result, CVE-2005-0950, which concerns "FastStone 4in1 Browser", not this driver. "viagart": 0.
No known CVEs.

## Hardware IDs (from the 9x INFs)

71 distinct PCI IDs, all vendor 1106, from AGP\VIAGART.INF (17), WIN9X\VIAVSD.INF (1: DEV_0571 bus master IDE),
Inf\{WIN98SE,WIN98,WINME,WIN95}\VIAMACH.INF and AgpME\VIAGART.INF. ENTRY.TXT lists the first 40. Full list:

VEN_1106&DEV_ 8598 8501 8601 8305 8605 8391 8602 B091 B099 B101 B112 B116 B148 B156 B158 B168 B188 0571 0305 0391 0601 0605 3091 3099
3101 3102 3103 3112 3123 3128 3148 3116 3156 3158 3168 3178 3188 3189 0198 3202 3204 3205 3208 3209 B102 B103 B115 B198 8231 3074 3147
3177 3109 8235 3051 3113 3213 D213 B113 B213 0501 0691 0596 0686 3050 3057 0597 0598 0586 8597 3040

## Install behaviour

- 4in1443v.exe: a self-extracting cabinet (7-Zip sees a MSZip CAB at offset 130,227; stub strings "PackageStartup",
  "PackageShutdown") containing an InstallShield 5 setup (Setup.exe, SETUP.INS, _USER1.CAB, ...). SETUP.INI AppName=VIA Service Pack.
- Setup.iss in the package is a response file for SdFinishReboot with BootOption=3 (restart); InstallShield 5 accepts `-s` for silent
  mode with such a file, but that was not tested and would restart the computer, so the entry runs the file interactively.
- Beacon: unzip to {pf}\Drivers\via-4in1, then run 4in1443v.exe. It is unverified whether the stub starts Setup.exe automatically
  after extracting (normal for such stubs).
- Add/Remove Programs name: unknown (probably "VIA Service Pack"; not verified). The setup has its own uninstall options per driver.
  Beacon's Uninstall only removes the unpacked file.

## Verification notes

- Opened: VIA portal and results, the zip and the inner CAB (7-Zip on the host, nothing executed), INFs, SETUP.INI, SETUP.ISS,
  README (decompressed from _USER1.CAB on the host).
- Not verified: whether the SFX launches setup, silent switches, Add/Remove name, behaviour on real hardware.
