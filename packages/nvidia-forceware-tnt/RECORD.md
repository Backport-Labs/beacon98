# NVIDIA ForceWare 71.84 for Windows 98/ME (RIVA TNT to GeForce 6) - Beacon 98 record

- Date checked: 2026-09-29
- Package: NVIDIA Windows 95/98/ME Display Drivers, NVIDIA Corporation
- Version: 71.84 (driver file version 4.14.10.7184, 02/24/2005; INF DriverVer 02/24/2005, 7.1.8.4)
- License: proprietary "License For Customer Use of NVIDIA Software" (no redistribution)
- Availability: external (NVIDIA's own download server)
- Why this package: 71.84 is the newest NVIDIA 9x driver whose INF still lists RIVA TNT, TNT2, Vanta, Aladdin TNT2,
  GeForce 256 and GeForce2 GTS/Pro. 77.72 (INF, 66 devices) and 81.98 (INF, 69 devices) no longer contain them.
  Owners of GeForce2 MX and newer should use `nvidia-forceware` (81.98).

## Windows 9x support evidence

- Readme.txt inside the package (extracted on the host, not run): "NVIDIA Display Driver for Windows 9x version
  4.14.10.7184, 02/24/2005" / "Operating systems supported: Microsoft Windows 98, Microsoft Windows Millennium
  Edition (Windows Me)". Windows 95 is not listed.
- NVAGP.INF: 81 device names, including "NVIDIA RIVA TNT", "NVIDIA RIVA TNT2/TNT2 Pro", "NVIDIA RIVA TNT2 Ultra",
  "NVIDIA Vanta/Vanta LT", "NVIDIA RIVA TNT2 Model 64/Model 64 Pro", "NVIDIA Aladdin TNT2", "NVIDIA GeForce 256",
  "NVIDIA GeForce2 GTS/GeForce2 Pro", up to "NVIDIA GeForce 6800 Ultra", 6600 GT and 6200.
- Compared by extracting the INF from 77.72 (downloaded to a temporary folder): 77.72 has no TNT/GeForce 256 entries.
  I did not check whether any driver between 71.84 and 77.72 exists.
- NVIDIA page: none found. https://www.nvidia.com/en-us/drivers/win9x-7184/ answers 404 and the old 9x archive
  page redirects to nvidianews.nvidia.com. The file is still on NVIDIA's download server under the same naming
  pattern as the linked 77.72/66.94/56.64 files. It is NVIDIA's own server, but no current NVIDIA page links it.

## Download

- URL: https://download.nvidia.com/Windows/71.84/71.84_win9x_english.exe (200; Last-Modified Tue, 01 Mar 2005 00:54:34 GMT)
  - http://download.nvidia.com/... answers 301 to https.
  - https://download1.nvidia.com/... answers 301 to https://http.download.nvidia.com/Windows/71.84/71.84_win9x_english.exe (200, same size).
- File: 71.84_win9x_english.exe, 11,232,793 bytes
- SHA-256: c0657392fdd4ee41504e35e89f926e3bf174d25662809b7353b135efce588b94
- Published checksum: none.
- Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\nvidia-forceware-tnt -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is EULA.TXT from the installer's InstallShield data1.cab, decompressed on the host (installer not run).
  Same wording as the 81.98 EULA.
- Redistribution is NOT allowed ("may install and use one copy of the SOFTWARE on a single computer, and except for
  making one back-up copy of the Software, may not otherwise copy the SOFTWARE"). Therefore external.

## Security

NVD keyword searches "nvidia forceware" and "nvidia windows 98": 0 results. None known.

## Install behaviour

- Same structure as 81.98: InstallShield PackageForTheWeb stub containing an InstallShield 6 setup, setup.iss
  response file and the loose driver files. Setup.ini AppName and UNINST_DISPLAY_NAME:
  "NVIDIA Windows 95/98/ME Display Drivers". Setup strings require DirectX 8.
- Silent switches: not documented by NVIDIA; the entry runs the installer interactively (see the 81.98 record).

## Verification notes

- Opened: the file headers over https and http, the extracted Readme.txt, NVAGP.INF, Setup.ini, setup.iss and the EULA.
- Not verified: an official NVIDIA page for 71.84; behaviour on real hardware.
