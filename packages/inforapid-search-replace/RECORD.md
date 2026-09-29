# InfoRapid Search & Replace 3.1f - Beacon 98 record

- Date checked: 2026-09-29
- Package: InfoRapid Search & Replace (Ingo Straub Softwareentwicklung, Germany)
- Version: 3.1f (string "3.1f" in SERAPID.EXE; the product page says "Version 3.1f"; file version resource 3.0.0.0; files dated 2003-07-12)
- License: own license agreement of 19.11.1998; freeware for private use only, commercial use needs a paid license
- Recommendation: 3.1f is the only and last version. List as external (see License).

## Windows 9x support evidence

- The publisher's page https://www.inforapid.de/html/searchreplace.htm (opened) gives no system requirements.
- The build is from 2003 (Wise installer 2001, PE subsystem 4.0). Static imports (parsed here): no NT-only functions; InitializeCriticalSectionAndSpinCount (Windows 98 and later, not 95) and shlwapi.dll (present with IE 4+) are imported. GetUserDefaultUILanguage appears only as a string.
- The license text names "Windows 95 und Windows NT" among trademarks; mdgx.com's Windows 9x list (source "mdgx-toy" in availability.csv) lists 3.1e.
- Conclusion: very likely runs on 98 and ME; not stated by the author; not tested. Windows 95 is doubtful (InitializeCriticalSectionAndSpinCount), so Systems omits 95.

## Download

- Official: https://inforapid.de/sr/sr.exe. The address in availability.csv, http://www.inforapid.com/sr/sr.exe, and http://www.inforapid.de/sr/sr.exe redirect (301) to it. Plain http alone does not serve the file (redirect to https). Last modified 2003-07-12.
- File: sr.exe, 1,037,513 bytes (Wise self-installing executable, ZIP-based)
- SHA-256: fecbd8b862beaabf261d8b85ac3c4daaa899a5132bce705974c789d59d498f37
- MD5: 565c2c299adaa767bac9246011cec58e
- Published checksum: none. Authenticode: not signed.

## Windows Defender

2026-09-29, engine 1.1.26080.3, signatures 1.459.466.0: "found no threats".

## License

- LICENSE.TXT: the "Copyright and License Agreement - 19.11.1998" embedded in SERAPID.EXE, plus the program's About text (extracted, not run).
- II.1: "The freeware version of InfoRapid Search & Replace may be used exclusively for private purposes. Any commercial usage is absolutely forbidden and only legal with the licensed full version."
- II.3: "The freeware version of InfoRapid Search & Replace may be copied freely, provided this happens in full original size and in unchanged form. No price may be taken except a copy fee of max. 3 Euro."
- II.4: "InfoRapid Search & Replace may not be sold together with hardware, other software or commercial documentation."
- Setup's welcome text: "The program is freely distributable over all media including internet, CD-ROM and others."
- Redistribution of the unmodified file is allowed. However, the free version is private-use only, and VERIFY-INSTRUCTIONS.md says personal-use-only licenses are not acceptable for hosting. ENTRY.TXT therefore uses `Availability: external` with a Notice about the commercial license. Backport Labs could decide to host it under II.3; that decision is left open.

## Security

- NVD keyword search "inforapid" (2026-09-29): 0 results.

## Install behaviour

- Installer type: Wise Installation System (WISE0001.DLL, W32INST.DLL, UNWISE32.EXE inside). Silent switch: `/s` is the generic Wise switch; not documented by the author and not verified.
- Default folder: `%PROGRAM_FILES%\seRapid` (MAINDIR=seRapid in the Wise script).
- Uninstall: UNWISE32.EXE is included; Add/Remove name not verified. ENTRY.TXT uses "InfoRapid Search & Replace" (APPTITLE in the Wise script).
- Installed size: about 2.1 MB.

## Verification notes

- Opened: product page, license text in the exe, Wise script strings. Not verified: running on 9x, silent switch, Add/Remove name.
