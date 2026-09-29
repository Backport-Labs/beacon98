# NASM 2.14.02 - Beacon 98 record

- Date checked: 2026-09-29
- Package: NASM, the Netwide Assembler
- Version: 2.14.02 (2018-12-26)
- License: BSD 2-clause
- Recommendation: 2.14.02, the last release whose Win32 build opens files with plain `fopen()`. From 2.15 on, the Win32 builds open every file through `_wfopen()`, which needs working Unicode file APIs that stock Windows 98 does not have. Newer builds (up to 3.02) still load on 98 and would probably work with KernelEx, but that is untested.

## Windows 9x support evidence

NASM's documentation says nothing about Windows 9x, so this rests on the binaries and source:

- I downloaded the official Win32 zips of 2.07, 2.09.10, 2.10.09, 2.11.08, 2.12.02, 2.13.03, 2.14.02, 2.15.05, 2.16.03, 3.01 and 3.02 from https://www.nasm.us/pub/nasm/releasebuilds/<ver>/win32/ and read their PE headers and imports (not executed). All are MinGW builds with OS/subsystem version 4.0 that import only KERNEL32 and msvcrt.dll.
- Wide-character file functions imported by nasm.exe:
  - 2.07 to 2.14.02: none (2.14.02 uses `fopen`, `_stati64`, `_access`, `_lseeki64`, `_filelengthi64`).
  - 2.15.05, 2.16.03, 3.01, 3.02: `_wfopen`, `_waccess`, `_wstati64`. 2.16.03 also imports `_strtoi64`/`_strtoui64`.
- Source, `nasmlib/file.c` in nasm-2.15.05.zip and nasm-3.02.zip (read): "On Windows, we want to use _wfopen(), as fopen() has a much smaller limit on the path length that it supports." `os_fopen` is defined as `_wfopen` with no fallback. Changelog for 2.15 (doc/changes.src in nasm-3.02.zip): "Attempt to support of long path names, up to 32767 of UTF-16 characters, on Windows."
- On Windows 98, msvcrt's `_wfopen` goes to `CreateFileW`, which 98 only has as a stub that fails. So 2.15 and later cannot open source files on stock 98 (my inference, not tested).
- 2.14.02 KERNEL32 imports include GetModuleHandleW (exported by 98's KERNEL32) and nothing from my list of APIs missing on 98. The msvcrt imports include `__lconv_init`; that 98 SE's msvcrt.dll exports it is not verified.
- Windows 95: needs msvcrt.dll, which stock 95 does not have (it comes with later updates). Not claimed.
- A DOS build (`dos/`, DJGPP) also exists for every release and runs in a DOS box; not checked.

## Download

- URL: https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/win32/nasm-2.14.02-win32.zip
- File: nasm-2.14.02-win32.zip, 557,565 bytes
- SHA-256: 250f9b5eeb2111e8c7b494a977490985b8604fe7518a6f5041cde37cc727a067
- Published checksum: NASM publishes none for 2.14.02 (the release directory has only `git.id` = a73b8be6f0f9e307e3c6131011a30f2fd5b00877 and `version.id`). Nothing to compare.
- Alternative: `nasm-2.14.02-installer-x86.exe` (934,855 bytes, SHA-256 9e994909e19aec6df83265673541f426d1a80246b996f2043c5d5663bacf4306), an NSIS 3 installer (7-Zip reports "NSIS-3", not Unicode). Not recommended: NSIS 3's support for 98 was not checked and the zip is simpler. Kept outside the package folder.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\nasm -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- BSD 2-clause ("simplified BSD"), `LICENSE` in the zip, copied as LICENSE.TXT.
- Redistribution of binaries allowed; condition: reproduce the copyright notice, conditions and disclaimer in the documentation (LICENSE.TXT does this).
- Source not required; hosted anyway:

## Source (hosted, not required)

- URL: https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/nasm-2.14.02.tar.xz
- File: src/nasm-2.14.02.tar.xz, 827,620 bytes
- SHA-256: e24ade3e928f7253aa8c14aa44726d1edf3f98643f87c9d72ec1df44b26be8f5

## Security

NVD (keyword "netwide assembler", 44 results) lists these as affecting 2.14.02 by version:
- CVE-2019-6290, CVE-2019-6291: stack exhaustion in eval.c "through 2.14.02" (CVSS2 4.3)
- CVE-2019-8343: use-after-free in paste_tokens, 2.14.02 (CVSS2 6.8)
- CVE-2019-14248: NULL dereference in pragma.c, 2.14.x (CVSS2 4.3)
- CVE-2019-20334: stack consumption in eval.c, 2.14.02 (CVSS3 5.5)

Count: 5. Many other entries name only 2.14 release candidates or 2.15 and are not counted. All need a crafted assembly source file and cause crashes (possibly memory corruption in CVE-2019-8343). Low risk for a developer tool run on your own sources.

## Install behaviour

- Zip layout: one top folder `nasm-2.14.02\` with `nasm.exe`, `ndisasm.exe`, `LICENSE`, and `rdoff\` (rdf2bin, rdf2com, rdf2ihx, rdf2ith, rdf2srec, rdfdump, rdflib, rdx, ldrdf). No documentation.
- Beacon: unzip into `C:\NASM` dropping the top folder, add `C:\NASM` to PATH. Command-line only, no shortcut.
- Uninstall: files.

## Verification notes

- Opened/downloaded: release directory listings, eleven Win32 zips (imports read, not executed), nasm-2.15.05.zip and nasm-3.02.zip source (file.c, changes.src), 2.14.02 zip, installer and source, NVD API.
- Not verified: running on 98/ME; msvcrt export `__lconv_init` on 98 SE.
