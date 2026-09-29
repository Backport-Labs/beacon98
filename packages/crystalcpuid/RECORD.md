# CrystalCPUID 4.15.5 - Beacon 98 record

- Date checked: 2026-09-29
- Package: CrystalCPUID (hiyohiyo, Crystal Dew World)
- Version: 4.15.5 (2009-05-09), last release; the product is marked "[Obsolete]"
- License: Freeware, "can be freely distributed" -> **hosted**

## Windows 9x support evidence

- https://crystalmark.info/en/software/crystalcpuid/ (opened): "CrystalCPUID [Obsolete]", x86: "Vista/2003/XP/2000/NT4/Me/98/95".
- ReadMeCpuid.txt in the zip: "OS : Windows Vista/2003/XP/2000/NT4/Me/98/95", "CPU : Intel 386 or later". The file list names "SysInfo.vxd | 32| Device Driver (9x)" and "CrystalCPUID.exe | 32| Main Program (9x/NT)".
- HistoryCpuid.txt: top entry "<4.15.5 2009/5/9> - Fixed handle leak". CrystalCPUID.exe file version 4.15.5.0.
- Recommended extras on 9x per readme: IE 4.0 or later, WMI 1.5 (for BIOS information), and WinTop.vxd from the Windows 95 Kernel Toys for accurate CPU usage. None are required to start.

## Download

- Download page: https://crystalmark.info/en/download/ links `/download/archive/CrystalCPUID/CrystalCPUID415.zip` (and a separate x64 zip, not used).
- URL: https://crystalmark.info/download/archive/CrystalCPUID/CrystalCPUID415.zip (http:// answers 301 to https; 200, 639,998 bytes)
- File: CrystalCPUID415.zip, 639,998 bytes
- SHA-256: 6a053caf3e7132695e6ccb3f151f5b28ba1d3929d877ee7119b106f024c23ef4
- MD5: 674b253bd57a8369d12a2295d0f35b6b
- Published checksum: none.
- Authenticode: CrystalCPUID.exe and SysInfo.dll not signed.
- Contents (no top folder): CrystalCPUID.exe, SysInfo.dll, SysInfo.vxd, SysInfo.sys, SysInfoNT4.sys, SysInfoX64.sys, data\*.pci/.db/.dat, readme and history texts (EN/JA).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\crystalcpuid -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- ReadMeCpuid.txt (saved as LICENSE.TXT): "CrystalCPUID 4.x.y.z is a freeware and can be freely distributed." CrystalCPUID.txt: "License : Freeware".
- Redistribution of the unmodified zip is allowed; no conditions stated. Hosting is fine.
- Bundled libraries named in the readme: MFC (Microsoft), PCI Debug Library for Win32 (kashiwano masahiro), libpng 1.2.7, zlib 1.2.1, a DIB/libpng wrapper (HyperWorks), MatrixStatic (Nic Wilson). These are statically linked/part of the author's distribution; no separate source obligation (none is GPL).
- No trial, no nag.

## Security

NVD keyword "CrystalCPUID": 0 results. It bundles libpng 1.2.7 (2004), which has many later CVEs, but CrystalCPUID uses it only for its own images/screenshots, not for opening untrusted files. It loads a kernel driver (SysInfo.vxd on 9x) that gives raw hardware access. No Warning field.

## Install behaviour

Plain zip, no installer. Beacon: `unzip {pf}\CrystalCPUID`, shortcut `{dir}\CrystalCPUID.exe`, uninstall `files`. The program writes its settings to CrystalCPUID.ini in its own folder (per readme convention; not verified).

## Verification notes

- Verified: product page, download page, zip contents and texts, HTTP headers.
- Not verified: running on 95/98/ME.
