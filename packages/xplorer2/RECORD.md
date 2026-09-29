# xplorer2 Professional 5.0.0.3 (Windows 98 build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: xplorer2 Professional (Zabkat / Nikolaos Bozinis)
- Version: 5.0.0.3 ("Professional edition build 5003"), changelog date 13 Jun 21
- License: commercial, 21-day trial (+10 days with nags), then refuses to start without a key
- Catalog rows covered: "xplorer 2 lite" (2.2.0.2), "xplorer2 Lite" and "xplorer2 Pro". Zabkat offers no Windows 98 build of the free
  lite edition (current lite 6.3.0.3 is "Designed for: Windows All (32 & 64 bit) XP/Vista/7/8/10/11" per x2lite.htm, and its
  free licence is for "private (home) or academic ... and general non-profit use only"). Only this Pro trial build is offered for 98.

## Windows 9x support evidence

- https://www.zabkat.com/alldown.htm (downloaded and read), section "xplorer2 old version 5.0":
  "This is the last version that works on windows 98, for museum collectors <g>"
  "Professional edition build 5003: 32 bit" -> download.php?f=5003_98.exe
  An HTML comment beside it: "later versions may work too, minus the installer, but my virtualbox gives a funny error for all programs, not just x2".
- The installer is NSIS 2.51 ANSI ("NSIS-2" per 7-Zip; manifest "Nullsoft Install System v2.51"), which runs on 9x.
- Windows 95 and ME: not mentioned by the author. Systems is set to 98 only.
- Not tested (no VM use). The package contains both ANSI (xplorer2.exe, editor2.exe) and Unicode (_UC) executables; on 98 the ANSI ones apply.

## Download

- URL: https://www.zabkat.com/download.php?f=5003_98.exe
- IMPORTANT: the server returns the file only when the request has a Referer from zabkat.com. Tested 2026-09-29:
  - GET with `-e https://www.zabkat.com/alldown.htm`: HTTP 200, Content-Disposition "attachment; filename=5003_98.exe", 2,969,032 bytes.
  - GET or HEAD without Referer: HTTP 302 to http://www.free-downloads.net/programs/xplorer2 (a portal page, not the file).
  - http://www.zabkat.com/download.php?f=5003_98.exe: 301 to the https URL (so the Referer is lost on some clients).
  - Direct paths /5003_98.exe and /files/5003_98.exe: 404.
  Beacon's client must send `Referer: https://www.zabkat.com/alldown.htm` for this package, or it cannot be listed.
- File: 5003_98.exe, 2,969,032 bytes
- SHA-256: a378c55e744367ceb2ebadb60eb8fb4d4c79789c7ad7b75a1f3918ccf4bb758a
- Published checksum: none.
- Authenticode: signed by "Nikolaos Bozinis" (Kiti, Larnaca, CY), status Valid on the Windows 11 host. Version resource:
  FileVersion 5.0.0.3, CompanyName ZabKat, "xplorer2 installer", (C) 2002-2021 ZabKat.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\xplorer2 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is licence.txt from the installer (extracted with 7-Zip, not run).
- It forbids redistribution: "You shall not: ... (b) sell, lease, rent, transfer, copy or distribute this Software".
  Therefore `external` only.
- Trial terms, from x2help.htm in the installer: "The professional version can be installed and tried in full trim without obligation
  for the first 21 days - and a further 10 days with some extra nags." ... "After the end of the 31-day trial period you must obtain a
  registration key or the program will refuse to start."
- Zabkat still sells xplorer2 (current 6.4.0.0, 23 Aug 2026 per x2down.htm). Whether a current key unlocks 5.0 is unknown.

## Security

- NVD keyword search "xplorer2" (2026-09-29): 0 results. No known CVEs.

## Install behaviour

- Installer type: NSIS 2.51 (ANSI), requests admin (irrelevant on 98). Standard NSIS `/S` and `/D=` switches assumed; Zabkat does not
  document a silent install, so this is unverified. The installer has StartMenu and InstallOptions pages.
- Uninstaller: the NSIS package contains an uninstaller stub that 7-Zip names "Uninstall.exe.nsis", i.e. it writes Uninstall.exe into
  the install folder. `run "{dir}\Uninstall.exe" /S` is used; the Add/Remove Programs display name is unknown (script not readable).
- Default folder: unknown (NSIS script not extractable); Beacon passes /D={dir}.
- Files: xplorer2.exe, xplorer2_UC.exe, editor2.exe, editor2_UC.exe, x2SettingsEditor.exe, 19 x2t_*.dll translations, help, skins,
  about 9.8 MB unpacked.

## Verification notes

- Verified by opening/downloading: alldown.htm, x2lite.htm, x2down.htm, the installer (listed and unpacked with 7-Zip, not run),
  licence.txt, x2help.htm, changes.txt, signature, NVD.
- Not verified: silent switches, uninstall name, running on 98/ME/95.
