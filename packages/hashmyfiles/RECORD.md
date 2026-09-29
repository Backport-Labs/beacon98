# HashMyFiles 2.51 (non-Unicode build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: HashMyFiles (Nir Sofer, NirSoft), non-Unicode build `hashmyfiles98.zip`
- Version: 2.51 (page title "HashMyFiles v2.51"; exe version resource 2.51; build date 2026-07-13)
- License: NirSoft freeware; free redistribution of the unmodified, complete package allowed
- Recommendation: host 2.51 non-Unicode after a VM test. Systems: 98, ME. Confidence in 98 support is medium: the download link says "For Windows 98", but the System Requirements text says the opposite.

## Windows 9x support evidence

- https://www.nirsoft.net/utils/hash_my_files.html (opened 2026-09-29), download link text:
  "Download HashMyFiles - Non-Unicode Version (For Windows 98)" -> hashmyfiles98.zip
- The same page, "System Requirements", and the readme.txt inside hashmyfiles98.zip:
  "This utility works on Windows 2000/XP/2003/Vista/Windows 7/Windows 8/Windows 10/Windows 11. Older versions of Windows are not supported."
  This contradicts the link text; the requirement text is probably shared with the Unicode build. Unresolved without a VM test.
- Static check (UPX-decompressed temp copy, not executed): the 98 build imports only ANSI functions (no ...W functions at all), OS/subsystem version 4.0. Imports that need 98 or later: GetLongPathNameA, MonitorFromWindow, GetMonitorInfoA, so it will not load on Windows 95. Nothing 2000-only was seen among the static imports.
- Hash types: the page history says SHA-256/SHA-512 (1.80) and SHA-384 (1.85) "are supported on Windows XP/SP3, Windows Vista, Windows 7, Windows Server 2003, and Windows Server 2008" (they use CryptoAPI). On 98 expect only MD5, SHA-1 and CRC32 to work. Worth a Notice.

## Download

- Page: https://www.nirsoft.net/utils/hash_my_files.html
- URL: https://www.nirsoft.net/utils/hashmyfiles98.zip (no version in the URL; replaced on each release, so we must host our copy; Last-Modified: Mon, 13 Jul 2026 11:02:14 GMT)
- File: hashmyfiles98.zip, 65,521 bytes
- SHA-256: 895d96fb19846570abc0db493124d49c03f27d469a139bcd4907b0a69c38b19d
- MD5: 492f6768127953fdc03d058451c1e356
- Published checksum: NirSoft's hash page https://www.nirsoft.net/hash_check/?software=hashmyfiles lists only hashmyfiles.zip and hashmyfiles-x64.zip, not hashmyfiles98.zip. No published checksum to compare.
- Zip contents: HashMyFiles.exe (51,200, 2.51), HashMyFiles.chm (20,348), readme.txt (22,187). No folders.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\hashmyfiles -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

License section of the page and of readme.txt (verbatim):

> This utility is released as freeware. You are allowed to freely
> distribute this utility via floppy disk, CD-ROM, Internet, or in any
> other way, as long as you don't charge anything for this. If you
> distribute this utility, you must include all files in the distribution
> package, without any modification !

- LICENSE.TXT: License and Disclaimer from readme.txt. Hosting allowed (free, unmodified zip).

## Security

NVD keyword searches "hashmyfiles" and "nirsoft" (2026-09-29): no CVE. 0 known problems.

## Install behaviour

- Plain zip, no installer, no Add/Remove entry.
- Beacon: `unzip {dir}`, Start Menu shortcut. The optional "Enable Explorer Context Menu" setting (user's choice) writes registry keys that Remove does not undo; the user should turn it off first.

## Verification notes

- Opened/downloaded: hash_my_files.html, hash_check page, hashmyfiles98.zip and its readme; version resource via .NET FileVersionInfo; imports from a UPX-decompressed temp copy. Nothing was run.
- Unresolved: the 98 statement conflict (VM test needed); no published hash for the 98 zip.
