# NoteTab Light 7.2 - Beacon 98 record

- Date checked: 2026-09-29
- Package: NoteTab Light (Fookes Software Ltd, Switzerland)
- Version: 7.2 (NoteTab.exe file version 7.2.0.52, released 3 November 2014 per WhatsNew.txt)
- License: NoteTab Light End User License Agreement (June 2012), freeware; section 6 allows redistribution of the unmodified current version
- Recommendation: 7.2 is the only version Fookes serves, and it is still the current NoteTab Light. It may be hosted (see License) with Fookes' server as second location.

## Windows 9x support evidence

- Fookes still publishes "NoteTab Window 95 and NT4 Compatibility Pack", http://www.notetab.com/ftp/Win95-NT4.zip (downloaded; files dated 2012-10-18). Its ReadThis.txt: "Unfortunately, Windows 95 and NT4 cannot display HTML Help. If you are using NoteTab under Win95/NT4 and the WinHelp files are not already installed, simply unzip and copy the *.hlp and *.cnt files [...] These Help files are for NoteTab version 7".
- WhatsNew.txt inside the 7.2 installer (extracted with innoextract, not run): "Fixed issue causing incompatibility under Windows 95 and NT4. A new "NoteTab Window 95 and NT4 Compatibility Pack" is available"; the Clip function ^$GetWinVersion$ and a platform function are still documented with Win95/Win98/WinME return values.
- Version history page https://www.notetab.com/version-history/ (opened): no statement that 9x support was dropped in 6.x or 7.x.
- Static imports of NoteTab.exe (parsed here): kernel32, user32, gdi32, advapi32, comctl32, comdlg32, mpr, ole32, oleaut32, shell32, version, wininet, winmm, winspool. No NT-only function is imported statically (GetNativeSystemInfo and GetLongPathNameA appear only as strings, i.e. loaded dynamically). PE OS/subsystem version 4.0.
- Not tested on Windows 95/98/ME (no VM interaction). Windows 98/ME status is inferred from the above; Fookes gives no explicit current system-requirements statement.

## Download

- Official: https://www.fookes.com/ftp/free/NoteTab_Light_Setup.exe (200 over https and http; last modified 2014-11-03). http://www.fookes.com/ftp/free/NoteTab_Setup.exe (the address in availability.csv) redirects there. The product page https://www.notetab.com/notetab-light/ links /get?NoteTab_Light_Setup.exe.
- File: NoteTab_Light_Setup.exe, 2,060,990 bytes
- SHA-256: b0923198ffd6dca66d8cca6242ef2781e8bf2cb9b0e0439d663aa42fa2856749
- MD5: eb3735ed0d729a189dd1a7c851387c58
- Published checksum: none found.
- Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\notetab-light -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is app\License.txt from the installer, unchanged: "NOTETAB LIGHT END USER LICENSE AGREEMENT (Version: June 2012)".
- 2.1: "Fookes Software grants you a license to Use the Software without charge on any number of computers, including in a business environment".
- 6. Distribution License: "Provided that you are distributing the then-current version of NoteTab Light (without any feature-unlocking file and/or instructions) you are hereby licensed to make as many copies of NoteTab Light as you wish; give exact copies of the original NoteTab Light package to anyone; and distribute NoteTab Light in its unmodified form via electronic means (Internet, BBS's, software distribution libraries, CD-ROMs, DVDs, etc.). You may charge a small distribution fee for NoteTab Light, but you must not represent in any way that you are selling the software itself. All copies must reproduce copyright notices."
- Conditions to watch: only the "then-current version" may be distributed (7.2 is current as of 2026-09-29; if Fookes releases a newer NoteTab Light, hosting 7.2 would no longer be covered and the entry should become external); 5. "In no case may the Software be bundled with a hardware or software product without written permission" (Beacon offers it as a separate download, which I read as distribution through a software library, not bundling; this is an interpretation); no site that offers cracks/malware.
- Conclusion: redistribution of the unmodified installer is allowed. ENTRY.TXT hosts it with Fookes' server as fallback.

## Security

- NVD keyword search "notetab" (2026-09-29): 0 results. No known CVEs.
- The optional trial mode and wininet import suggest network use (update check); not verified.

## Install behaviour

- Installer type: Inno Setup (setup data version 5.4.2, per innoextract 1.9). Silent: standard Inno `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART`.
- Default folder: unknown (innoextract lists files under {app}); likely `{pf}\NoteTab Light`, not verified.
- Add/Remove Programs name: not verified. ENTRY.TXT uses "NoteTab Light" (the installer's AppName as reported by innoextract); Inno may append the version.
- Installed size: about 4.1 MB (sum of the extracted files).
- Help is .chm (HTML Help); Windows 98/ME have HTML Help with IE 4 or later. Windows 95 users need the WinHelp compatibility pack above (not packaged).

## Verification notes

- Opened/downloaded: notetab.com product, version-history and terms pages; the installer; the compatibility pack; License.txt, ReadMe.txt, WhatsNew.txt from the installer (innoextract, not run); NVD.
- Not verified: running on 9x; Add/Remove name; default folder.
