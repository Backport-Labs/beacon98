# IconsExtract 1.47 - Beacon 98 record

- Date checked: 2026-09-29
- Package: IconsExtract (Nir Sofer, NirSoft)
- Version: 1.47 (page date 26/09/2010; exe version resource 1.47, file date 2010-09-26)
- License: NirSoft freeware; free redistribution allowed with all files including readme.txt, unmodified
- Recommendation: host 1.47. Systems: 95, 98, ME.

## Windows 9x support evidence

- https://www.nirsoft.net/utils/iconsext.html (opened 2026-09-29), "System Requirements":
  "Windows operating system: Windows 95/98/ME, Windows NT, Windows 2000, Windows XP, Windows 2003 Server, or Windows Vista/7/2008/8.x/10 ."
- readme.txt in the zip: "Windows operating system: Windows 95/98/ME, Windows NT, Windows 2000, Windows XP, Windows 2003 Server, or Windows Vista."
- Static check (not executed): iconsext.exe is UPX-packed; a decompressed temp copy imports only ANSI functions available on Windows 95 (no SendInput/multi-monitor imports), OS/subsystem version 4.0.
- Not tested in a VM.

## Download

- Page: https://www.nirsoft.net/utils/iconsext.html ("Download IconsExtract (in Zip file)")
- URL: https://www.nirsoft.net/utils/iconsext.zip. Also on the page: iconsext_setup.exe (self-installer).
- The URL has no version number; the file could change if NirSoft releases a new version, so we must host our copy. Server Last-Modified: Mon, 27 Sep 2010 10:58:14 GMT.
- File: iconsext.zip, 34,712 bytes
- SHA-256: 97582531dd0176e312f3a8b101e50d02224970aec5030f0e0ff2ac767f572981
- MD5: 4126eb1b8c8380907500fd1b2f9771ab
- Published checksum: https://www.nirsoft.net/hash_check/?software=iconsext lists iconsext.zip, 34712 bytes, SHA-256 97582531dd0176e312f3a8b101e50d02224970aec5030f0e0ff2ac767f572981: MATCH.
- Zip contents: iconsext.exe (27,136), iconsext.chm (15,490), readme.txt (8,461). No folders.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\iconsextract -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

License section of the page and of readme.txt (verbatim, readme wrapping):

> This utility is released as freeware. You can freely use and distribute
> it. If you distribute this utility, you must include all files in the
> distribution package including the readme.txt, without any modification !

- LICENSE.TXT: License and Disclaimer from readme.txt.
- Hosting is allowed; the zip is hosted unmodified and contains readme.txt. There is no "no charge" clause in this license, and Beacon is free anyway.

## Security

NVD keyword searches "iconsextract" and "nirsoft" (2026-09-29): no CVE. 0 known problems. It parses resources of arbitrary EXE/DLL files; a crafted file could in principle crash it (no reports found).

## Install behaviour

- Plain zip, no installer, no Add/Remove Programs entry.
- Beacon: `unzip {dir}`, Start Menu shortcut to iconsext.exe, Uninstall: files.
- On Windows 95 the .chm help file needs HTML Help (installed with IE 4 or later); the program itself does not.

## Verification notes

- Opened/downloaded: iconsext.html, hash_check page, iconsext.zip and its readme.txt; version resource via .NET FileVersionInfo; imports from a UPX-decompressed temp copy. Nothing was run.
- Unverified: actual run on 95/98/ME.
