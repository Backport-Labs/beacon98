# Volumouse - Beacon 98 record

- Date checked: 2026-09-29
- Package: Volumouse (Nir Sofer, NirSoft)
- Versions examined: 2.21 (current, page and exe version resource; build date 2026-07-08) and 2.03 (2014-10-03, from the Internet Archive)
- License: NirSoft freeware; free redistribution of the unmodified, complete package allowed (same text in 2.03 and 2.21)
- **Recommendation: do not ship 2.21 for Windows 98. Ship 2.03 (the last build with the vlmshlp.dll hook), sourced from the Internet Archive, after a VM test. Systems: 98, ME. Decision for the maintainer (see "Download").**

## Windows 9x support evidence

- https://www.nirsoft.net/utils/volumouse.html (opened 2026-09-29) and the 2.21 readme.txt, "System Requirements":
  "Windows operating system: Windows 98, Windows ME, Windows NT, Windows 2000, Windows XP, Windows Server 2003, Windows 7/Vista/2008/8/10/11. (Windows 95 is not supported)"
- But the page's history says: "Version 2.10: Volumouse now uses completely different method to hook the mouse wheel events. ... There is no need for the hook DLL anymore (vlmshlp.dll) volumouse is just a single .exe file".
- Static check of 2.21 (UPX-decompressed temp copy, not executed): the only call to SetWindowsHookExA is preceded by `push 0x0E`, i.e. `SetWindowsHookExA(WH_MOUSE_LL, proc, hInstance, 0)`. Microsoft documents WH_MOUSE_LL as available only on Windows NT 4.0 SP3 and later; Windows 98/ME do not have low-level hooks. So 2.21 most likely starts on 98 but cannot capture the mouse wheel, which is its main function (only the hot-key mode, RegisterHotKey, might work). This is an inference from the code, not a VM test, and it contradicts the page's system requirements, which were not updated when 2.10 changed the method.
- Static check of 2.03 (temp copy, not executed): vlmshlp.dll calls `SetWindowsHookExA(3 = WH_GETMESSAGE, ...)`, a global hook from a DLL, which Windows 98 supports. volumouse.exe 2.03 imports only ANSI functions available on 98 (SendInput, RegisterHotKey, WINMM mixer functions). The 2.03 readme: "Windows 98, Windows ME, Windows NT, Windows 2000, Windows XP, Windows Server 2003, Windows 7/Vista/2008/8. (Windows 95 is not supported)".
- 95: not supported by either version (stated).
- Versions 2.04 to 2.09 do not appear in the page history (2.03 is followed by 2.10), so 2.03 is the last version with the DLL hook.

## Download

### 2.21 (current, NirSoft)
- URL: https://www.nirsoft.net/utils/volumouse.zip (no version in the URL; the file changes with each release; Last-Modified: Wed, 08 Jul 2026 07:16:31 GMT)
- File: D:\Win98SE\beacon\packages\volumouse\volumouse.zip, 56,116 bytes
- SHA-256: 8736c42aa739e79d18700e290bf0aa8fab467747159df9e1a2847a06ce268acf
- MD5: 197cc09e579e9e97250906e9c6cae1b7
- Published checksum: https://www.nirsoft.net/hash_check/?software=volumouse lists volumouse.zip, 56116 bytes, SHA-256 8736c42a...268acf: MATCH.
- Contents: volumouse.exe (41,984, 2.21), volumouse.chm (20,080), readme.txt (20,324).

### 2.03 (recommended for 98; Internet Archive)
- NirSoft no longer serves 2.03; its own URL now returns 2.21. The license permits sharing, so the Internet Archive copy is acceptable under our rules only if the maintainer accepts "the publisher's server no longer has this version" as meeting "own server is gone". Flagged for decision.
- URL: http://web.archive.org/web/20141008030010id_/http://www.nirsoft.net/utils/volumouse.zip (capture of NirSoft's own URL, 2014-10-08)
- File: D:\Win98SE\beacon\packages\volumouse\2.03\volumouse.zip, 61,736 bytes
- SHA-256: a73ea9f6ad492f83660c192a8fb97d31b4e5a773981c2527fa6ab0d47bafe08a
- MD5: e82f34abda4ea84f1d97fe403f89cd21
- Published checksum: none available for 2.03 (NirSoft's hash page covers only the current file). Authenticity rests on the archive capture of nirsoft.net.
- Contents: volumouse.exe (41,568, FileVersion 2.03), vlmshlp.dll (18,528, 2.03), volumouse.chm (20,024), readme.txt (20,106), all dated 2014-10-03.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0):
D:\Win98SE\beacon\packages\volumouse "found no threats"; D:\Win98SE\beacon\packages\volumouse\2.03 "found no threats".

## License

License section of the page and of both readme.txt files (verbatim):

> This utility is released as freeware. You are allowed to freely
> distribute this utility via floppy disk, CD-ROM, Internet, or in any
> other way, as long as you don't charge anything for this. If you
> distribute this utility, you must include all files in the distribution
> package, without any modification !

- LICENSE.TXT (2.21, from its readme) and 2.03\LICENSE.TXT (from the 2.03 readme).
- Hosting allowed: no charge, whole zip unmodified.

## Security

NVD keyword searches "volumouse" and "nirsoft" (2026-09-29): no CVE. 0 known problems. 2.03 installs a global message hook DLL that is loaded into every program; that is by design.

## Install behaviour

- Plain zip, no folders; no installer, no Add/Remove entry (volumouse_setup.exe on the page is an NSIS installer for 2.21, not used).
- Beacon: `unzip {dir}`, Start Menu shortcut. Volumouse runs in the tray; its option "Start on Windows startup" (user's choice) adds a Run entry that Remove does not delete. Volumouse must be closed before Remove, since vlmshlp.dll is in use.

## Verification notes

- Opened/downloaded: volumouse.html, hash_check page, both zips and readmes, Wayback CDX list for volumouse.zip. Hook types read from UPX-decompressed temp copies by locating the call to SetWindowsHookExA. Nothing was run.
- Unresolved: VM test of 2.03 (and of 2.21, to confirm the WH_MOUSE_LL inference); maintainer decision on the Internet Archive source.
