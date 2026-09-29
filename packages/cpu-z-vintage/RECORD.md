# CPU-Z Vintage Edition 1.04 - Beacon 98 record

- Date checked: 2026-09-29
- Package: CPU-Z Vintage Edition (CPUID)
- Version: 1.04 (May 2023; file version 1.0.4.0)
- License: freeware (CPUID); no license file shipped; **external**.

## Windows 9x support evidence

- https://www.cpuid.com/softwares/cpu-z.html (downloaded and read 2026-09-29): "Version 1.04 for windows(R) 95/98", button "zip - english 32-bit version" -> `/downloads/cpu-z/cpu-z_1.04-win9x.zip`.
- cpuz_w9x_readme.txt (in the zip): "CPU-Z Vintage Edition Readme file ... Version 1.04 May 2023". History: 1.01 (November 2019, first release) to 1.04 (VIA Apollo MVP4 and VPX chipsets). Earlier entries list AMD K5, Cyrix Cx486, Ti486SXL, Intel 430FX, Pentium Overdrive support.
- Windows ME: not stated; Systems set to 95, 98. Not tested (no VM).

## Download

- URL: https://download.cpuid.com/cpu-z/cpu-z_1.04-win9x.zip (also https://www.cpuid.com/downloads/cpu-z/cpu-z_1.04-win9x.zip; http:// redirects to https). Tested with curl -I -L: 200, 1,446,689 bytes.
- File: cpu-z_1.04-win9x.zip, 1,446,689 bytes
- SHA-256: 5bbd2a01cf2768248b82f93338815ee1e37445fa255d514272db7ade72bcbc78
- MD5: 15cdf167773416c989e08683d9ca0cfd
- Published checksum: none.
- Contents: cpuz_w9x.exe (3,695,504 bytes), cpuz_w9x_readme.txt. No folder.
- Authenticode: cpuz_w9x.exe has a **Valid** signature, signer CN=CPUID, O=CPUID, L=Dunkerque, C=FR (checked on the host after extracting; not run).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\cpu-z-vintage -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

Same situation as the cpu-z package: no license file; the page calls CPU-Z freeware; CPUID's Terms of Service (saved as LICENSE.TXT) grant only a personal license and do not clearly allow redistribution. External. No trial or nag.

## Security

NVD lists no CVE for the Vintage Edition by name. The CPU-Z driver CVEs (CVE-2017-15302, CVE-2025-65264) concern NT kernel drivers; whether the Vintage build shares that code is unknown. Not relevant on 95/98 which have no privilege separation.

## Install behaviour

Plain zip. Beacon: `unzip {pf}\CPU-Z Vintage`, shortcut `{dir}\cpuz_w9x.exe`, uninstall `files`. There is no cpuz.ini in the zip; the readme says one may be created next to the exe.

## Verification notes

- Verified by opening/downloading: the CPU-Z page, readme, headers, signature.
- Not verified: behaviour on real 95/98 hardware.
