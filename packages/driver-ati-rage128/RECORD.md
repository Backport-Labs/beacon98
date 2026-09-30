# ATI Rage 128 / Rage 128 Pro display driver 4.13.7192 - Beacon 98 record

- Date checked: 2026-09-29
- Package: WMER1284137192.exe, "Windows Millennium Display Driver for ATI RAGE 128 / RAGE 128 PRO", ATI Technologies
- Version: 4.13.7192 (INF DriverVer 09/22/2001, 4.13.7192; readme dated October 2001)
- License: proprietary ATI End User License Agreement (distribution forbidden)
- Availability: external (AMD's own download server)

## Windows 9x support evidence

- AMD pages https://www.amd.com/en/support/downloads/drivers.html/graphics/legacy-graphics/rage-series/ati-rage-128-pro.html
  and .../ati-rage-128.html (opened 2026-09-29): "Windows ME 98 Driver Display Driver Bundle Revision Number 4.13.7192
  File Size 12 MB Release Date 2001-10-22", link https://www2.ati.com/drivers/WMER1284137192.exe. This is the only
  9x entry on those pages.
- Readme (WME_R128_4_13_7192.rtf in the package): "The display driver included in this package is for Microsoft
  Windows Millennium, Windows 98 and Windows 98SE. This driver may be used with ATI products based on the RAGE 128 /
  RAGE 128 PRO." Windows 95 is not mentioned.
- Readme: "To avoid difficulties running multimedia applications or games you must install: DirectX 8.0a" (hence
  `Requires: dx 8.0`).

## Download

- URL: https://drivers.amd.com/drivers/WMER1284137192.exe (needs `Referer: https://www.amd.com/`, otherwise 302);
  https://www2.ati.com/... and http://www2.ati.com/... redirect there.
- Last-Modified: Wed, 09 Jul 2003 13:28:33 GMT
- File: WMER1284137192.exe, 12,562,724 bytes
- SHA-256: 21ba14dcd5f12ee2d1e5892269899474cc0a5e515a19a09f304ae6527266cf4c
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT: ATI "End User License Agreement", found in the InstallShield cabinet _user1.cab of this package
  (decompressed on the host; installer not run); identical wording to the Rage Pro package's license.txt.
- Distribution forbidden (section 2 b and c). Therefore external.

## Security

None known (not verified against NVD in this session).

## Install behaviour

- Outer file: self-extracting cabinet (7-Zip type "Cab"); readme: it "creates a temporary directory on the system
  disk and unpacks all the individual files", then "the ATI SETUP program is launched from the temporary directory".
  Default unpack folder per readme: C:\ATI\... (readme shows C:\...\_R128_4_13_7192).
- Inside: InstallShield 5 setup (SETUP.EXE, setup.ins, _sys1.cab, _user1.cab), setup.iss (Welcome, License, Finish
  with BootOption=0), INSTALL.INI (`Path=-1,ATIDRIVE,ATII9XAA.INF,-1`), driver INF Atidrive\Atii9xaa.inf.
- Silent install: not documented; the entry runs it interactively (`Install: exe`).
- Add/Remove Programs name: "ATI Display Driver" (readme: 'Select "ATI Display Driver" and then click the
  ADD/REMOVE button').
- Readme: uninstall any previous Rage 128 driver first; answer "NO" to Version Conflict messages.

## Hardware IDs

VEN/DEV pairs in Atii9xaa.inf (9):

- PCI\VEN_1002&DEV_5044
- PCI\VEN_1002&DEV_5046
- PCI\VEN_1002&DEV_5050
- PCI\VEN_1002&DEV_5245
- PCI\VEN_1002&DEV_5246
- PCI\VEN_1002&DEV_524C
- PCI\VEN_1002&DEV_534D
- PCI\VEN_1002&DEV_5446
- PCI\VEN_1002&DEV_5452

## Verification notes

- Opened: both AMD pages, the file (downloaded, 7-Zip listing/extraction on the host, not executed), readme, INF,
  INSTALL.INI, setup.iss, the EULA.
- Not verified: behaviour on real hardware.