# ShellExView 2.01 - Beacon 98 record

- Date checked: 2026-09-29
- Package: ShellExView (Nir Sofer, NirSoft)
- Version: 2.01 (page date 10/06/2019; exe version resource 2.01, file date 2019-06-10)
- License: NirSoft freeware; free redistribution of the unmodified, complete package allowed
- Recommendation: host 2.01. Systems: 98, ME (not 95).

## Windows 9x support evidence

- https://www.nirsoft.net/utils/shexview.html (opened 2026-09-29) and readme.txt in the zip, "System Requirements":
  "This utility works on any version of Windows, starting from Windows 98 and up to Windows 10. x64 versions of Windows are also supported."
- Windows 95 is not included ("starting from Windows 98").
- Static check (not executed): shexview.exe is UPX-packed; a decompressed copy in a temp folder imports only ANSI functions (plus CryptoAPI MD5 functions and WS2_32), OS/subsystem version 4.0. Nothing 2000-only was seen. WS2_32.dll is present on 98 and ME.
- Not tested in a VM.

## Download

- Page: https://www.nirsoft.net/utils/shexview.html ("Download ShellExView in Zip file")
- URL: https://www.nirsoft.net/utils/shexview.zip (32-bit). Also on the page: shexview_setup.exe (self-installer with uninstall support) and shexview-x64.zip.
- The URL has no version number; NirSoft replaces the file on each release, so we must host our copy. Server Last-Modified: Sun, 09 Jun 2019 22:54:23 GMT.
- File: shexview.zip, 73,154 bytes
- SHA-256: b0f5e6bea715be67460d24e4ffe5256297ffd990cc4f5bfa902f9d5af0d1196d
- MD5: cf61b12ea9d5babbccf04cfdbf5c1ba1
- Published checksum: https://www.nirsoft.net/hash_check/?software=shexview lists shexview.zip, 73154 bytes, SHA-256 b0f5e6bea715be67460d24e4ffe5256297ffd990cc4f5bfa902f9d5af0d1196d, MD5 cf61b12ea9d5babbccf04cfdbf5c1ba1: MATCH.
- Zip contents: shexview.exe (65,936), shexview.chm (19,458), readme.txt (21,694). No folders.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\shellexview -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

License section of the page and of readme.txt (verbatim):

> This utility is released as freeware. You are allowed to freely
> distribute this utility via floppy disk, CD-ROM, Internet, or in any
> other way, as long as you don't charge anything for this. If you
> distribute this utility, you must include all files in the distribution
> package, without any modification !

- LICENSE.TXT: License and Disclaimer from readme.txt.
- Hosting is allowed: Beacon charges nothing and hosts the zip unmodified with all its files.

## Security

NVD keyword searches "shellexview" and "nirsoft" (2026-09-29): no CVE for ShellExView. 0 known problems.

## Install behaviour

- Plain zip, no installer, no Add/Remove Programs entry (the separate shexview_setup.exe would add one; not used).
- Beacon: `unzip {dir}`, Start Menu shortcut to shexview.exe, Uninstall: files.
- Settings are saved to shexview.cfg next to the exe (NirSoft convention; not checked in detail). Disabling an extension writes to the registry (that is its purpose), which Remove does not undo.

## Verification notes

- Opened/downloaded: shexview.html, hash_check page, shexview.zip and its readme.txt; version resource via .NET FileVersionInfo; imports from a UPX-decompressed temp copy. Nothing was run.
- Unverified: actual run on 98/ME.
