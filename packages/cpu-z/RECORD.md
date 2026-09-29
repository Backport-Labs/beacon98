# CPU-Z 1.78 (Windows 98 build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: CPU-Z (CPUID, France)
- Version: 1.78 (file version 1.7.8.1, readme dated November 2016), special "WINDOWS 98 32-bit version" build
- License: freeware (CPUID); no license file shipped. Redistribution not clearly permitted, so **external**.
- Recommendation: list as external from download.cpuid.com. For 486/Pentium-class machines and Windows 95 use the separate CPU-Z Vintage 1.04 package (cpu-z-vintage).

## Windows 9x support evidence

- https://www.cpuid.com/softwares/cpu-z.html (downloaded and read, 2026-09-29): in the version history, the 1.76 and 1.78 entries each carry a download button labelled "WINDOWS 98 32-bit version" linking to `cpu-z_1.76-win98.zip` / `/downloads/cpu-z/cpu-z_1.78-win98.zip`. No later win98 build is linked on the page; 1.78 is the last one.
- The same page offers "Version 1.04 for windows(R) 95/98" (Vintage Edition, separate package).
- Windows ME and 95: not stated for the 1.78 build; Systems is set to 98 only. Not tested (no VM interaction).

## Download

- URL: https://download.cpuid.com/cpu-z/cpu-z_1.78-win98.zip (the page link https://www.cpuid.com/downloads/cpu-z/cpu-z_1.78-win98.zip serves the file too; plain http:// on both hosts answers 301 to https, then 200, Content-Length 1154222, application/zip). Tested with `curl.exe -sS -I -L` on 2026-09-29.
- File: cpu-z_1.78-win98.zip, 1,154,222 bytes
- SHA-256: e32663cd4982f616a01acd9e57dbf365a9145adee250b0d6e0a29346fa085128
- MD5: 4d68b049f6bd5180880a9ff5f4daddba
- Published checksum: none published by CPUID for this file.
- Contents: cpuz.exe (2,797,568 bytes, file version 1.7.8.1), cpuz.ini, cpuz_readme.txt. No folder inside the zip.
- Authenticode: cpuz.exe is not signed (checked after extracting to a temp folder; not run).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\cpu-z -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- The zip contains no license text. The CPU-Z page says: "CPU-Z for Windows x86/x64 is a freeware that gathers information on some of the main devices of your system".
- The only written terms are CPUID's Terms of Service (https://www.cpuid.com/terms-of-service.html), saved as LICENSE.TXT. They grant "a personal, nonexclusive, nontransferable, revocable, limited license to view, reproduce, print, cache, store and distribute content retrieved from our Site via a generally available consumer web browser" and forbid distribution "for any commercial use without the prior written permission of CPUID". This is not a clear permission for a package manager to host the software, so the package is external.
- No trial, no nag. It checks for updates at start (cpuz.ini `CheckUpdates=1`).

## Security

NVD keyword search "CPU-Z" (2026-09-29), 3 results:
- CVE-2017-15302: improper access rights to the kernel-mode driver, CPU-Z through 1.81 (range includes 1.78). Concerns the NT driver; on Windows 98 there is no user/kernel privilege separation to protect anyway.
- CVE-2017-15303: before 1.43, not affected.
- CVE-2025-65264: kernel driver IOCTL validation, v2.17 and earlier (range includes 1.78). Same remark.
No Warning field: both affect local privilege boundaries that Windows 98 does not have.

## Install behaviour

- Plain zip, no installer. Beacon: `unzip {pf}\CPU-Z` (no strip), shortcut to `{dir}\cpuz.exe`, uninstall `files`.

## Verification notes

- Verified by opening/downloading: the CPU-Z page, the terms of service, the zip and its readme/ini (extracted as text), HTTP headers of all locations.
- Not verified: behaviour on 95/ME; whether CPUID intends 1.78-win98 for ME as well.
