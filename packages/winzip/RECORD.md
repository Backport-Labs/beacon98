# WinZip 10.0 (build 7245) - Beacon 98 record

- Date checked: 2026-09-29
- Package: WinZip (WinZip International LLC / WinZip Computing; now part of Corel/Alludo)
- Version: 10.0 (7245) (README.TXT: "WinZip(R) Version 10.0 (7245) Copyright (C) 1991-2005")
- License: Shareware (evaluation version); license text not readable
- Recommendation: 10.0 build 7245, external. It is the newest WinZip still served by WinZip for 98/ME.

## Windows 9x support evidence

- README.TXT inside winzip100.exe: "This version of WinZip requires Windows 98, Windows Me, Windows 2000, or Windows XP." (No Windows 95.)
- WinZip 11.2 (https://download.winzip.com/ov/winzip112.exe, downloaded) is an MSI whose LaunchCondition table says "NOT Version9X || WinZip(R) requires Windows Vista, Windows XP, or Windows 2000." WinZip 12.0 (ov/winzip120.exe) is also MSI-based. So 11.2 and later do not install on 9x.
- WinZip 11.0 and 11.1 (winzip110.exe/winzip111.exe under /ov/) return 404; download.winzip.com/winzip110.exe redirects to a current 116 MB installer. Whether 11.0/11.1 supported 98/ME was not checked.
- The row's own address, http://download.winzip.com/ov/winzip121.exe (WinZip 12.1), is still served but is not a 9x version.

## Download

- https://download.winzip.com/winzip100.exe (last modified 2006-11-14) and https://download.winzip.com/ov/winzip100.exe (2014-03-06): identical size; both 200 over https and plain http.
- Also still served in /ov/: winzip90.exe (9.0), wzipse30.exe (Self-Extractor 3.0), winzip112.exe, winzip120.exe, winzip121.exe. 8.x files return 404. WinZip 9.0 (which likely supports 95) was not examined.
- No page on winzip.com that links these old versions was found; the /ov/ folder is on WinZip's own download server.
- File: winzip100.exe, 6,252,136 bytes (WinZip Self-Extractor Personal Edition 9.0 stub; contains SETUP.EXE, SETUP.WZ (password-protected zip with the program), README.TXT, GDS.EXE, GTB9X.EXE, GTBXP.EXE)
- SHA-256: 7ecb819cff97a67b2ac3b672471972cac9b9724899d5fe2e60792f453d591122
- MD5: 0db71a66d36100d242e9ef43ee1f7130
- Authenticode: Valid, signer "CN=WinZip Computing, O=WinZip Computing, L=Mansfield, S=Connecticut, C=US" (Class 3 Microsoft Software Validation v2; certificate expired 2009-10-18, timestamped signature still validates).
- Published checksum: none found.

## Windows Defender

2026-09-29, engine 1.1.26080.3, signatures 1.459.466.0: "found no threats".

## License

- Shareware evaluation. README.TXT: "The installation and use of this software is subject to the license agreement included in the program. [...] Caution, WinZip 10.0 is not a free upgrade." The agreement itself is inside the encrypted SETUP.WZ; it was not decrypted and the setup was not run.
- The current Corel EULA (https://www.winzip.com/eula.htm redirects to https://www.corel.com/en/eula/) does not describe 10.0. Redistribution permission: unknown. External.
- Evaluation period length for 10.0: not verified (the Notice does not state a number of days).
- Whether WinZip 10.0 licenses can still be bought was not checked.

## Security

NVD keyword search "winzip" (2026-09-29), 38 results. Relevant to 10.0 build 7245:
- CVE-2008-3442: WinZip before 11.0 does not verify the authenticity of updates (MITM, code execution). Applies.
- CVE-2006-5198, CVE-2006-3890: FileView ActiveX (WZFILVW.OCX) in WinZip 10.0 "before build 7245". Fixed in this build. CVE-2006-6884 names build 6667.
- CVE-2025-1240 (7Z parsing out-of-bounds write): affected versions not checked against 10.0.
- CVE-2024-8811, CVE-2025-33028 (Mark-of-the-Web): not applicable on 9x.
- Older CVEs (8.x/9.0) are fixed by 10.0 per their descriptions.

## Install behaviour

- The outer file is a WinZip Self-Extractor that runs SETUP.EXE. SETUP.EXE strings show it runs `gds.exe -silent -bundle "WZPA"`, `gtb9x.exe /q /d` and `gtbxp.exe /q /d` (Google Desktop / Google Toolbar), apparently as offers; whether they are opt-in or opt-out was not verified.
- Silent install: not documented in the package; unknown. ENTRY.TXT uses `Install: exe` (interactive).
- Add/Remove name: not verified; ENTRY.TXT uses "WinZip".

## Verification notes

- Opened/downloaded: winzip100.exe, winzip112.exe (MSI LaunchCondition read with the Windows Installer COM API), winzip120.exe listing, README.TXT, NVD. Not verified: license text, eval period, silent switch, uninstall name.
