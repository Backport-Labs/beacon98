# Notepad2 1.0.12 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Notepad2 (Florian Balmer, flos-freeware.ch), id `notepad2`
- Version: 1.0.12 (released June 25, 2004). The last release for Windows 9x.
- License: the program readme says freeware that "may be used and distributed freely" (no fees); the source is GNU GPL version 2 (License.txt in the source archive). Notepad2 only moved to the BSD license with 2.0.15, which also dropped 9x. **BSD does not apply to 1.0.12.**
- Bundled: Scintilla editing component (Neil Hodgson), statically linked. It is under its own permissive license and is **not** in the source archive.
- Recommendation: 1.0.12, the file `notepad2_1.0.12.zip` the author offered on his own site until the 1.0.12 downloads were taken down. His server no longer has it (HTTP 404), so it comes from the Internet Archive's copy of his own URL. The license allows free distribution, so that is acceptable. There is no second version to choose from: 2.0.13 and 2.0.14 were "not released to the public", and 2.0.15 dropped 9x.

## Windows 9x support evidence

- https://www.flos-freeware.ch/doc/Notepad2.txt (the 4.2.25 readme with the full change log; downloaded and read):
  - "New in Version 2.0.15 (released April 07, 2007)" ... "- BSD License for Notepad2 and source code (see License.txt)" ... "- Dropped Windows 9x support" ... "- Requires msvcr70.dll runtime library"
  - "New in Version 2.0.14 (not released to the public)" and "New in Version 2.0.13 (not released to the public)"
  - "New in Version 1.0.12 (released June 25, 2004)" ... "- Notepad2 source code now released under the GNU GPL"
  - The current 4.2.25 readme says it "works on NT-based versions of Windows."
- The author's Notepad2 page as archived on 2007-06-12 (https://web.archive.org/web/20070612103821/http://www.flos-freeware.ch/notepad2.html, opened):
  "There's also some regressions, i.e. ANSI code page support has been reduced to the system default, the bookmarks feature has been removed, a few syntax schemes have been dropped, and Notepad2 does no longer run on Windows 9x. If you need any of these features, you'll have to stick to Notepad2 version 1.0.12."
- Notepad2.txt inside notepad2_1.0.12.zip (opened): "Notepad2 works on Windows 9x, Me, NT, 2k and XP."
- Readme.txt inside np2src_1.0.12.zip (opened): "This package contains the full source code of Notepad2 1.0.12 for Windows 9x/Me/NT/2k/XP."
- Import table of Notepad2.exe (parsed with a PE reader, not run): only ANSI APIs from KERNEL32, USER32, GDI32, ADVAPI32, SHELL32, COMCTL32, comdlg32, ole32, IMM32 and SHLWAPI. It statically imports `SHLWAPI!SHAutoComplete`, which needs "Shlwapi.dll (version 5.0 or later)" (https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-shautocomplete, opened). Shlwapi 5.0 comes with Internet Explorer 5. So:
  - Windows 98 SE (ships IE 5) and ME (IE 5.5): should run as is.
  - Windows 98 first edition (IE 4.01) and Windows 95: Notepad2.exe will probably not start unless IE 5 or later is installed. This follows from the import table and Microsoft's documentation; it was not tested.
- No KernelEx needed. Nothing was tested in a VM.

## Download

- The author's download page for 1.0.12, as archived on 2007-06-12 (link above), lists:
  "Download Notepad2 1.0.12 Binary Files [242 KB]" -> `zip/notepad2_1.0.12.zip` and
  "Download Notepad2 1.0.12 Source Code [166 KB]" -> `zip/np2src_1.0.12.zip`.
- Author's URL: http://www.flos-freeware.ch/zip/notepad2_1.0.12.zip. Today it gives 404 (https) or a 301 redirect to https and then 404 (http), checked with `curl -I`. The current notepad2.html offers only 4.2.25.
- Used: Internet Archive copy of that URL, https://web.archive.org/web/20070612104152id_/http://www.flos-freeware.ch/zip/notepad2_1.0.12.zip
- File: notepad2_1.0.12.zip, 246,814 bytes, plain ZIP (no installer)
- SHA-256: a20f099decfe5588623b1cc868a9205ffe7050469fe66fd8ca5393b2d592836d
- MD5: e97fa3b63eb0f97d441e9b1925e24291
- Published checksum: the author never published any. The Wayback CDX index records a SHA-1 digest for its capture, `EEY2KR35FC7TWNVMPIKRN2RA7PFMBVKS` (base32). The SHA-1 of the downloaded file in base32 is the same: MATCH. That only proves the file is the archived copy, not that the author signed it. The same digest appears for http://www.flos-freeware.ch/zip/notepad2.zip captured 2005-11-24, when 1.0.12 was still the current version.
- Authenticode: not signed. The version resource says FileVersion 1.0.12, "(c) Florian Balmer 2004".

### Two builds of 1.0.12 (found while checking)

The author replaced the 1.0.12 binary once without changing the version number:

| Build | Notepad2.exe PE timestamp | Zip dates | Archived as | Zip SHA-256 |
|---|---|---|---|---|
| Original | 2004-06-24 23:06:58 UTC | 2004-06-25 | zip/notepad2.zip, captured 2005-10-27 (Wayback digest K3DJHLJD...) | 52e75cc4281fadf86074b33d327d276e9f2d0ddd7e70dd1c9374be26bc402216 (246,869 bytes) |
| Rebuild (used here) | 2005-11-04 10:54:44 UTC | 2005-11-04 | zip/notepad2.zip from 2005-11-24, then zip/notepad2_1.0.12.zip (2007-06-12) | a20f099decfe5588623b1cc868a9205ffe7050469fe66fd8ca5393b2d592836d |

- Both builds' Notepad2.exe are 552,960 bytes with different contents (SHA-256 of the exe: original 90413af0...fcff3, rebuild 02d05ffd...0975a). Notepad2.txt and Notepad2.reg are the same in both.
- Both use the same compiler (linker 7.0), the same subsystem version 4.0 and the same imports, including SHAutoComplete.
- The author gave no reason for the rebuild: there is nothing about it in the MailingList.txt archive or on the archived pages.
- I chose the rebuild because it is the file the author offered last, under the 1.0.12 name. The original build is kept only in my temp folder. Either one could be used.
- A third variant of notepad2.zip (247,165 bytes, Wayback digest 63TKQ7GX..., captured 2005-08-20) exists in the CDX index. Wayback served the 2005-10-27 copy for that timestamp, so it was not checked.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\notepad2 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". This covers the zip, src\ and LICENSE.TXT.

## License

- Notepad2.txt in the program zip, section "Copyright" (quoted exactly):
  "Notepad2 is FREEWARE and may be used and distributed freely. Please do not charge any distribution or download fees for this program, except for the cost of the distribution medium. The use of the software is AT YOUR OWN RISK."
- The same file, section "Source Code": "The full Notepad2 source code is distributed under the terms of the GNU General Public License and can be found at: http://www.flos-freeware.ch"
- Readme.txt in the source zip: "Distributed under the terms of the GNU General Public License, see License.txt for details." License.txt is the GNU GPL version 2 (June 1991). The source file headers say the same without naming a version or "or later". GPL v2 section 9 allows any version when none is specified, but only v2 text is included, so the catalog uses GPL-2.0-only.
- BSD: only from 2.0.15 ("BSD License for Notepad2 and source code"). It does not cover 1.0.12.
- Redistributing the unmodified files is allowed. Conditions:
  - no charge for distribution or download (Beacon is free, so this is met);
  - GPL v2 s.3: give the source or an offer of it. We host np2src_1.0.12.zip next to the binary;
  - keep the license texts. LICENSE.TXT holds: the readme's Copyright section, the source Readme.txt Copyright section, the full GPL v2 License.txt from the source zip, and the Scintilla license.
- Scintilla (bundled, statically linked; the exe contains "Scintilla\src\Editor.cxx" and similar paths): its license is permissive ("Permission to use, copy, modify, and distribute this software ... without fee is hereby granted, provided that the above copyright notice appear in all copies and that both that copyright notice and this permission notice appear in supporting documentation"). The 1.0.12 zip does not include it, so it is added in LICENSE.TXT. The text used is today's text from https://www.scintilla.org/License.txt ("Copyright 1998-2021"), not the 2004 text. The wording of the permission is believed to be unchanged, but that was not checked against a 2004 copy.

## Matching source (hosted)

- Author's URL: http://www.flos-freeware.ch/zip/np2src_1.0.12.zip (now 404). Copy used: https://web.archive.org/web/20070612104222id_/http://www.flos-freeware.ch/zip/np2src_1.0.12.zip
- File: src\np2src_1.0.12.zip, 169,497 bytes
- SHA-256: 16566be7ad3eaf02242f44aa92db379f3f3d2ad81e636efb8d7795b672529191 (MD5 e937a8aeb01580380db2b4a78f3187a0)
- The Wayback SHA-1 digest WJYORKCBA6ZXGHZXBCDORZK772UVVOMH matches. The same digest was captured as zip/np2src.zip on 2005-10-18, so the source archive did not change between 2005 and 2007.
- Contents: all Notepad2 sources (dated 2004-06-25), a VC++ .NET 7.0 project and GPL v2 License.txt.
- **Not included: Scintilla.** Readme.txt says: "The source code of the Scintilla source code editing component can be downloaded from http://www.scintilla.org and must be unzipped to the Scintilla subdirectory", and lists two small edits (extern "C" in scintilla.h, and LINK_LEXER replaced with void(0) in KeyWords.cxx). The Scintilla version is not stated anywhere I found:
  - The original build (2004-06-24) must use Scintilla 1.61 (released 29 May 2004) or earlier (per https://www.scintilla.org/ScintillaHistory.html, opened).
  - Which version the 2005-11-04 rebuild used is unknown.
  - Because GPL "complete corresponding source" arguably includes the statically linked Scintilla, we could also host the Scintilla 1.61 source. That is a decision for the maintainer; it was not downloaded.

## Security

- NVD (API 2.0, keyword "notepad2", queried 2026-09-29): 3 CVEs, all for 4.2.x and none for 1.0.12. They are CVE-2026-2538 (Msimg32.dll), CVE-2026-4545 (PROPSYS.dll) and CVE-2026-4546 (TextShaping.dll), all "uncontrolled search path" (DLL hijacking) with local access.
- 1.0.12 does not import those DLLs statically, and PROPSYS and TextShaping do not exist on 9x. Whether 1.0.12 loads any DLL by a relative path was not checked.
- NVD has a CPE for flos-freeware:notepad2:1.0.12, but no CVE matched it in the keyword search.
- Known problems: 0 for 1.0.12. Bundled Scintilla from 2004 was not checked separately. Opening an untrusted file in a 2004 editor is low risk, but it is not zero.

## Install behaviour

- Type: plain zip, no installer, flat (no folders). It holds 3 files: Notepad2.exe (552,960), Notepad2.txt (15,814), Notepad2.reg (4,271); entries listed with .NET ZipFile.
- Beacon: `unzip {pf}\Notepad2` (no strip), then a Start Menu shortcut to `{dir}\Notepad2.exe`. No silent switch is needed.
- Settings: Notepad2 1.0.12 stores its settings in the registry under HKCU\Software\Notepad2. There is no ini file; that came only in 2.0.13. The readme says:
  "Just put a copy of Notepad2.exe to any directory on your computer. To remove the Notepad2 registry entries, run "Notepad2.exe -u" from any command line, and then delete Notepad2.exe to have a complete, traceless uninstall."
- Add/Remove Programs: none (no uninstaller). The uninstall kind is `files`. Removing the files leaves HKCU\Software\Notepad2 behind unless the user runs `Notepad2.exe /u` first. Beacon has no pre-uninstall step for this, so it is mentioned in a Notice.
- Notepad2.reg holds optional extra settings for the user to edit and import; Beacon does not import it.

## Verification notes

- Verified by opening or downloading:
  - current flos-freeware.ch notepad2.html and archive.html, doc/Notepad2.txt and doc/MailingList.txt;
  - archived notepad2.html from 2004-06-29, 2005-02-21, 2006-01-03 and 2007-06-12;
  - the Wayback CDX listing of flos-freeware.ch/zip/*;
  - both zips and the readmes and license inside them;
  - PE headers, version resource and import table of both 1.0.12 builds (read as bytes, never run);
  - scintilla.org License.txt and ScintillaHistory.html, the Microsoft SHAutoComplete page, and the NVD API results.
- From search snippets only: nothing that is used in this record.
- Not verified:
  - running on 95/98/ME (no VM interaction);
  - the Scintilla version in either build;
  - why the author rebuilt the exe in 2005-11;
  - the 2005-08-20 zip variant;
  - the 2004 text of the Scintilla license.
