# ZSoft Uninstaller 2.4.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: ZSoft Uninstaller (ZSoft Software, Denmark)
- Version: 2.4.1 (program file dated 2007-10-06). The newer 2.5 (Uninstaller.exe dated 2010-11-18) is also served.
- License: freeware, "Permission is granted to use this software for non-commercial purpose only."
- Recommendation: 2.4.1, the version the MSFN Windows 98SE list names. 2.5 is listed only in the OSR KernelEx list, which
  suggests (not verified) that 2.5 was used with KernelEx. Both executables are UPX-packed ANSI programs with subsystem 4.0
  and the same visible imports, so no difference could be proven.
- Open question for the catalog owner: VERIFY-INSTRUCTIONS says personal-use-only licenses are not acceptable. This is a
  non-commercial-use freeware listed as `external` (we do not distribute it); decide whether that rule applies to external entries.

## Windows 9x support evidence

- ZSoft FAQ, https://www.zsoft.dk/index/faq (downloaded and read): "What operating systems can ZSoft Uninstaller be used on?
  I have only tested it on Windows XP, but I have had reports on it working in Windows 95, Windows 98, Windows ME, Windows 2000
  and Windows Vista as well."
- Not tested (no VM use). The FAQ does not say which version the reports concern.

## Download

- Official page: https://www.zsoft.dk/index/software_details/4 (shows 2.5; its Download link goes to /index/software_get/4,
  which redirects to /download.php?appid=4 -> /downloads/ZSoft_Uninstaller_2.5.exe, 1,231,522 bytes).
- 2.4.1 URL: https://www.zsoft.dk/downloads/ZSoft_Uninstaller_2.4.1.exe (same folder as the linked 2.5 file; not linked from a page,
  found by testing the file name). http:// gives 301 to https://, then 200.
  Note: other guessed names (ZSoft_Uninstaller_2.4.exe, _2.41.exe) returned 200 without Content-Length, i.e. an HTML fallback, not a file.
- File: ZSoft_Uninstaller_2.4.1.exe, 917,947 bytes
- SHA-256: f1aba17ef54b71127e32c0ef609ad977d8ba57c57cbc871a600aca5752cc16eb
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\zsoft-uninstaller -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT holds the "About ZSoft Uninstaller" text from UninstallerHelp.chm inside the 2.4.1 installer (extracted with 7-Zip):
  "Permission is granted to use this software for non-commercial purpose only." Copyright (C) 2004-2005 ZSoft Software.
  Includes Indy (Chad Z. Hower and the Indy Pit Crew), Toolbar2000/TBX; packed with UPX; NSIS installer.
- No permission to redistribute is given, so `external`.

## Security

- NVD keyword search "zsoft uninstaller" (2026-09-29): 0 results.

## Install behaviour

- Installer type: NSIS (Nullsoft strings; 7-Zip opens it as NSIS). Contents: Uninstaller.exe, lang\*.lng (11 languages),
  UninstallerHelp.chm, UninstallerHelpRus.chm, uninst.exe (uninstaller written by the script).
- Silent switch: standard NSIS `/S` and `/D=`; not documented by ZSoft, unverified.
- Default folder and Add/Remove Programs name: unknown (NSIS script not extractable). Beacon passes /D={dir} and uninstalls with
  `run "{dir}\uninst.exe" /S`.

## Verification notes

- Verified: software_details page, FAQ, download redirects, both installers listed with 7-Zip (not run), the help file's About page, NVD.
- Not verified: silent install, 9x operation, which of 2.4.1/2.5 needs KernelEx.
