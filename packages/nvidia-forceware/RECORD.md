# NVIDIA ForceWare 81.98 for Windows 98/ME - Beacon 98 record

- Date checked: 2026-09-29
- Package: NVIDIA Windows 95/98/ME Display Drivers (ForceWare Release 80), NVIDIA Corporation
- Version: 81.98 (driver file version 4.14.10.8198, INF DriverVer 12/10/2005 8.1.9.8; page release date December 21, 2005)
- License: proprietary "License For Customer Use of NVIDIA Software" (one computer, no redistribution)
- Availability: external (NVIDIA's own download server)
- Recommendation: 81.98 for GeForce2 MX, GeForce3, GeForce4, GeForce FX and GeForce 6 cards. It does NOT
  contain RIVA TNT/TNT2, Vanta, GeForce 256 or GeForce2 GTS/Pro/Ultra/Ti entries; those need 71.84
  (separate package `nvidia-forceware-tnt`).

## Windows 9x support evidence

- NVIDIA page https://www.nvidia.com/en-us/drivers/win9x-8198/ (old address http://www.nvidia.com/object/win9x_81.98.html
  redirects there; opened 2026-09-29): "Win 9x/ME - (81.98)", "ForceWare Release 80 Version: 81.98 Release Date:
  December 21, 2005", "Release Highlights: Support for the GeForce 6 series GPUs, Microsoft DirectX 9.0c and OpenGL 2.0 support".
- Readme.txt inside the package (extracted on the host with 7-Zip, installer not run): "NVIDIA Display Driver for
  Windows 9x version 4.14.10.8198, 12/10/2005" / "Operating systems supported: Microsoft Windows 98, Microsoft
  Windows Millennium Edition (Windows Me)". Windows 95 is not listed.
- The Readme's adapter list still names RIVA TNT, TNT2, Vanta, GeForce 256 and GeForce2 GTS, but NVAGP.INF
  (69 device names) has none of them: its oldest entries are GeForce2 MX / Quadro2 MXR and GeForce3; its newest are
  GeForce 6800/6600/6200 and GeForce FX 5xxx. The INF is what Windows uses, so the Readme list is stale.
- 81.98 is the newest 9x driver on nvidia.com that I found. The "Windows 95/98/Me Driver Archive" link
  (https://www.nvidia.com/object/win9x_archive.html) now redirects to nvidianews.nvidia.com, and the
  "Products Supported" link (https://www.nvidia.com/object/81.98_9x_supported) goes to a generic support page.
- Setup strings (setup.inx) include "This driver requires Microsoft DirectX 8".

## What NVIDIA still serves for Windows 9x (checked 2026-09-29)

Pages under https://www.nvidia.com/en-us/drivers/win9x-NNNN/ that answer with a driver page and download links:
81.98, 77.72, 66.94, 56.64, 53.04, 45.23, 44.03. Files tested with curl (English):
- 81.98: 200, 12,458,912 bytes (this package)
- 77.72: 200, 11,711,248 bytes (INF: 66 devices, no TNT)
- 71.84: 200, 11,232,793 bytes (no page found; win9x-7184 is 404; file name follows the same pattern). INF includes TNT/TNT2/GeForce 256.
- 66.94: 200, 10,126,258; 56.64: 200, 9,151,185; 53.04: 200, 8,296,411; 45.23: 200, 7,973,870
- 44.03: the linked file answers 404.
- RIVA 128 page (http://www.nvidia.com/object/riva_drivers.html -> https://www.nvidia.com/en-us/drivers/riva-drivers/)
  still lists "RIVA128 Driver for Windows 9x AGP/PCI 3.37", but both detail pages
  (https://www.nvidia.com/object/LO_20010606_3499.html and ..._3508.html) redirect to "page-not-found". No RIVA 128 9x file found.

## Download

- Page: https://www.nvidia.com/en-us/drivers/win9x-8198/ (U.S. English, 11.7 MB; an International build, 19.3 MB,
  81.98_forceware_win9x_international.exe, 20,401,896 bytes, is also served; not downloaded)
- URL: https://download.nvidia.com/Windows/81.98/81.98_forceware_win9x_english.exe
  - http://download.nvidia.com/... answers 301 to the https address.
  - https://download1.nvidia.com/... and http://download1.nvidia.com/... answer 301 to
    https://http.download.nvidia.com/Windows/81.98/81.98_forceware_win9x_english.exe (200, same size).
  - The page also lists ftp://download.nvidia.com/... and ftp://download1.nvidia.com/... (not tested; Beacon has no FTP).
  - Last-Modified: Sat, 17 Dec 2005 00:31:54 GMT
- File: 81.98_forceware_win9x_english.exe, 12,458,912 bytes
- SHA-256: e05b92b1322f8d01549995ddd00a9dca93d83358ee78e868acedca9dc6c7c910
- Published checksum: none published by NVIDIA.
- Authenticode: Valid. Signer "NVIDIA Corporation" (VeriSign Class 3 Code Signing 2004 CA), certificate valid
  2005-08-30 to 2006-08-31, thumbprint E206906A212278564E7C633447EFAF03C66FE31B. Windows 11 reports "Signature verified".

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\nvidia-forceware -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is the EULA.TXT shipped inside the installer's InstallShield data1.cab ("License For Customer Use of
  NVIDIA Software"). 7-Zip cannot open this InstallShield 6 cabinet; I located the deflate stream and decompressed it
  on the host. The installer was not run.
- Redistribution is NOT allowed: "2.1.1 Rights. Customer may install and use one copy of the SOFTWARE on a single
  computer, and except for making one back-up copy of the Software, may not otherwise copy the SOFTWARE."
  The Linux/FreeBSD redistribution exception (2.1.2) does not apply to Windows drivers.
- Therefore `Availability: external`; the file comes only from NVIDIA's server.

## Security

NVD keyword searches "nvidia forceware" and "nvidia windows 98" return 0 results. NVIDIA's display-driver CVEs
concern Windows NT-family and Linux drivers; none found for the 9x drivers. Not otherwise verified.

## Install behaviour

- Outer file: InstallShield PackageForTheWeb stub (stub32i.exe, "PackageForTheWeb" strings), 32-bit, signed.
  Inside: InstallShield 6 setup (Setup.exe, setup.inx, data1.cab/hdr, ikernel.ex_) plus the loose driver files.
- Setup.ini AppName and the string table: "NVIDIA Windows 95/98/ME Display Drivers";
  UNINST_DISPLAY_NAME=NVIDIA Windows 95/98/ME Display Drivers. The Readme's uninstall instructions use the same
  Add/Remove Programs name.
- Silent install: not documented by NVIDIA. The package contains a setup.iss response file (SdWelcome, then
  SdFinishReboot with BootOption=3, i.e. it restarts the computer). PackageForTheWeb is generally run with `/s /a -s`
  to pass `-s` to the inner setup, but I did not verify that here and an automatic restart would end the Beacon
  session, so the entry runs the installer interactively.
- Setup strings say that when a previous display driver is found it uninstalls it, restarts, and continues the
  installation after the restart; it also refuses to install if no NVIDIA chip is found.
- Manual alternative from the Readme: extract and use Display > Advanced > Adapter > Change > Have Disk with NVAGP.INF.

## Verification notes

- Opened: the 81.98 page and its download links, the RIVA 128 page, the other win9x-NNNN pages (link extraction),
  the installer contents (7-Zip listing and extraction on the host, not executed), Readme.txt, NVAGP.INF, setup.iss,
  Setup.ini, the EULA.
- Not verified: behaviour on real Windows 98/ME hardware; silent-install switches.
