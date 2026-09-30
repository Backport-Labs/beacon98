# ATI Catalyst 6.2 for Windows 98/ME - Beacon 98 record

- Date checked: 2026-09-29
- Package: ATI Catalyst Software Suite for Windows ME (display driver + ATI Control Panel), ATI Technologies / AMD
- Version: Catalyst 6.2 (driver package 30314; INF DriverVer 01/24/2006, 4.15.1.9165)
- License: proprietary ATI End User License Agreement (use with ATI hardware on one computer; distribution forbidden)
- Availability: external (AMD's own download server)
- Recommendation: 6.2 is the only Windows ME/98 package AMD still lists for the Radeon 7000-9800 series; it is the
  last Catalyst for 9x.

## Windows 9x support evidence

- AMD legacy product pages (opened 2026-09-29), e.g.
  https://www.amd.com/en/support/downloads/drivers.html/graphics/legacy-graphics/radeon-7xxx-series/ati-radeon-7500-series.html
  and .../radeon-9xxx-series/ati-radeon-9800-series.html: section "Windows ME 98", "Catalyst Software Suite Revision
  Number 6.2 File Size 14 MB Release Date 2005-02-09", link https://www2.ati.com/drivers/6-2_wme_dd_cp_30314.exe,
  release notes https://www2.ati.com/drivers/Catalyst_62_ME_release_notes.html. (The page's release date looks wrong:
  the server file is dated 9 Feb 2006 and the INFs 24 Jan 2006.)
- Release notes (opened): "Catalyst Version 6.2 for Windows ME Release Note ... Note: Windows 98/98SE is supported
  through the Windows Millennium Edition driver." Supported: Radeon 9800, 9700, 9600, 9500, 9200, 9100, 9000, 8500,
  7500, 7200, 7000 series, Radeon Xpress 200 series, All-In-Wonder variants; beta support for X850, X800, X600, X550,
  X300; "now includes support for the ATI Radeon X700 AGP series". Also notes that these ME drivers are not WHQL
  certified. Windows 95 is not mentioned.

## Download

- URL: https://drivers.amd.com/drivers/6-2_wme_dd_cp_30314.exe
  - https://www2.ati.com/... and http://www2.ati.com/... answer 301 to the drivers.amd.com address.
  - http://drivers.amd.com/... answers 301 to https.
  - drivers.amd.com answers 302 (no file) without a Referer; with `Referer: https://www.amd.com/` it answers 200.
    The entry therefore has `Referer: https://www.amd.com/`.
  - Last-Modified: Thu, 09 Feb 2006 12:52:50 GMT
- File: 6-2_wme_dd_cp_30314.exe, 15,171,672 bytes
- SHA-256: 20b53b7041f0f3b87f835ef1a769b180b8059dda48f2cc7bbdbf8dd76ef11fd8
- Published checksum: none.
- Authenticode: Valid, signer "ATI TECHNOLOGIES INC." (VeriSign Class 3 Microsoft Software Validation v2).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <package folder> -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is the ATI "End User License Agreement". I found it in the InstallShield data1.cab cabinets inside the
  installer by decompressing the deflate streams on the host (the installer was not run); its wording is identical to
  license.txt shipped in the Rage Pro package.
- Redistribution is NOT allowed: "2. Restrictions ... you may not ... b) modify, network, rent, lend, loan, distribute
  or create derivative works based upon the Software in whole or in part; or c) electronically transmit the Software
  from one computer to another or over a network". Use is limited to ATI hardware on a single computer.
- Therefore `Availability: external`.

## Security

No CVEs found for ATI 9x display drivers (not otherwise verified; NVD not searched in this session because the web
search budget was exhausted).

## Install behaviour

- Outer file: NSIS 2 self-extractor (7-Zip lists "Nsis, NSIS-2"), signed by ATI. Inside: three InstallShield
  setups (Setup.ini AppName "ATI Software", "ATI Control Panel", "ATI Display Driver"), their response files
  setup.iss / setup_shortcut.iss, and the 9x driver files (C5/C7/C8/C9_30314.INF, INFSETUP.EXE).
- INSTALL.INI: `ListOnADDRemove=1`, `InstallDriver=1`, `[WIN9X]` device list pointing at `\9X_INF, C9_30314.INF`.
- Silent install: not documented by ATI; the InstallShield response files end with SdFinishReboot (one with
  BootOption=3, i.e. restart). The entry runs the installer interactively (`Install: exe`).
- Add/Remove Programs name: "ATI Display Driver" (AppName of the driver setup, and the name the ATI Rage readmes of
  the same family use). Not confirmed on a real Windows 98 system. The ATI Control Panel may register a second entry.
- Manual alternative: extract and use Device Manager, Update Driver, Have Disk with C9_30314.inf.

## Hardware IDs

All VEN/DEV pairs found in C5/C7/C8/C9_30314.INF (99 pairs; ENTRY.TXT carries the first 40):

- PCI\VEN_1002&DEV_3E50
- PCI\VEN_1002&DEV_3E70
- PCI\VEN_1002&DEV_4136
- PCI\VEN_1002&DEV_4137
- PCI\VEN_1002&DEV_4144
- PCI\VEN_1002&DEV_4146
- PCI\VEN_1002&DEV_4148
- PCI\VEN_1002&DEV_4150
- PCI\VEN_1002&DEV_4151
- PCI\VEN_1002&DEV_4152
- PCI\VEN_1002&DEV_4153
- PCI\VEN_1002&DEV_4164
- PCI\VEN_1002&DEV_4166
- PCI\VEN_1002&DEV_4168
- PCI\VEN_1002&DEV_4170
- PCI\VEN_1002&DEV_4171
- PCI\VEN_1002&DEV_4172
- PCI\VEN_1002&DEV_4173
- PCI\VEN_1002&DEV_4242
- PCI\VEN_1002&DEV_4966
- PCI\VEN_1002&DEV_496E
- PCI\VEN_1002&DEV_4A49
- PCI\VEN_1002&DEV_4A4A
- PCI\VEN_1002&DEV_4A4B
- PCI\VEN_1002&DEV_4A50
- PCI\VEN_1002&DEV_4A69
- PCI\VEN_1002&DEV_4A6A
- PCI\VEN_1002&DEV_4A6B
- PCI\VEN_1002&DEV_4A70
- PCI\VEN_1002&DEV_4B49
- PCI\VEN_1002&DEV_4B4B
- PCI\VEN_1002&DEV_4B4C
- PCI\VEN_1002&DEV_4B69
- PCI\VEN_1002&DEV_4B6B
- PCI\VEN_1002&DEV_4B6C
- PCI\VEN_1002&DEV_4E44
- PCI\VEN_1002&DEV_4E45
- PCI\VEN_1002&DEV_4E46
- PCI\VEN_1002&DEV_4E48
- PCI\VEN_1002&DEV_4E49
- PCI\VEN_1002&DEV_4E4A
- PCI\VEN_1002&DEV_4E51
- PCI\VEN_1002&DEV_4E64
- PCI\VEN_1002&DEV_4E65
- PCI\VEN_1002&DEV_4E66
- PCI\VEN_1002&DEV_4E68
- PCI\VEN_1002&DEV_4E69
- PCI\VEN_1002&DEV_4E6A
- PCI\VEN_1002&DEV_4E71
- PCI\VEN_1002&DEV_5144
- PCI\VEN_1002&DEV_514C
- PCI\VEN_1002&DEV_514D
- PCI\VEN_1002&DEV_5157
- PCI\VEN_1002&DEV_5159
- PCI\VEN_1002&DEV_515A
- PCI\VEN_1002&DEV_5549
- PCI\VEN_1002&DEV_554A
- PCI\VEN_1002&DEV_554B
- PCI\VEN_1002&DEV_554D
- PCI\VEN_1002&DEV_554F
- PCI\VEN_1002&DEV_5569
- PCI\VEN_1002&DEV_556A
- PCI\VEN_1002&DEV_556B
- PCI\VEN_1002&DEV_556D
- PCI\VEN_1002&DEV_556F
- PCI\VEN_1002&DEV_5834
- PCI\VEN_1002&DEV_5940
- PCI\VEN_1002&DEV_5941
- PCI\VEN_1002&DEV_5954
- PCI\VEN_1002&DEV_5960
- PCI\VEN_1002&DEV_5961
- PCI\VEN_1002&DEV_5964
- PCI\VEN_1002&DEV_5974
- PCI\VEN_1002&DEV_5A41
- PCI\VEN_1002&DEV_5B60
- PCI\VEN_1002&DEV_5B62
- PCI\VEN_1002&DEV_5B63
- PCI\VEN_1002&DEV_5B70
- PCI\VEN_1002&DEV_5B72
- PCI\VEN_1002&DEV_5B73
- PCI\VEN_1002&DEV_5C61
- PCI\VEN_1002&DEV_5D44
- PCI\VEN_1002&DEV_5D4D
- PCI\VEN_1002&DEV_5D4F
- PCI\VEN_1002&DEV_5D52
- PCI\VEN_1002&DEV_5D57
- PCI\VEN_1002&DEV_5D6D
- PCI\VEN_1002&DEV_5D6F
- PCI\VEN_1002&DEV_5D72
- PCI\VEN_1002&DEV_5D77
- PCI\VEN_1002&DEV_5E4A
- PCI\VEN_1002&DEV_5E4B
- PCI\VEN_1002&DEV_5E4C
- PCI\VEN_1002&DEV_5E4D
- PCI\VEN_1002&DEV_5E6A
- PCI\VEN_1002&DEV_5E6B
- PCI\VEN_1002&DEV_5E6C
- PCI\VEN_1002&DEV_5E6D
- PCI\VEN_1002&DEV_7834

## Verification notes

- Opened: the AMD product pages above, the 6.2 ME release notes, the file (download and 7-Zip listing / extraction of
  INF, INI and ISS files on the host, not executed), the EULA.
- Not verified: behaviour on real hardware; the Add/Remove Programs name; silent switches.