# MyUninstaller 1.77 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: MyUninstaller (Nir Sofer, NirSoft)
- Version: 1.77 (2017-02-20). This is the current and final version; the page says the tool is no longer updated.
- License: Freeware (NirSoft terms: free distribution allowed, no charge, all files, unmodified)
- Recommendation: host 1.77 as the unmodified official zip. There is no older/newer choice to make: 1.77 is the latest and its own documentation lists Windows 98.

## Windows 9x support evidence

- https://www.nirsoft.net/utils/myuninst.html (verified by downloading the page on 2026-09-29), heading:
  "MyUninstaller v1.77 - Alternative to the standard add / remove control panel module", "Copyright (c) 2003 - 2017 Nir Sofer".
  Notice on the page: "MyUninstaller is very old tool and it's not updated anymore, you are welcomed to try the new UninstallView tool".
- Same page, "System Requirements": "This utility works on any version of Windows - from Windows 98 to Windows 10."
  The identical sentence is in readme.txt inside myuninst.zip 1.77 (opened, not run).
- Versions history on the page: "20/02/2017 1.77 Removed the duplicate entries of HKEY_CURRENT_USER key on 64-bit systems." No later entry.
- Windows ME: falls inside "from Windows 98 to Windows 10"; not named separately.
- Windows 95: NOT claimed by the author (the range starts at 98). Unknown whether it runs on 95; not tested. Listed as 98, ME only.
- KernelEx: not needed per the author's statement. PE header of myuninst.exe (read from the zip in memory, not run): i386, PE32, OS/subsystem version 4.0, GUI subsystem, UPX-packed; imports ADVAPI32, COMCTL32, comdlg32, GDI32, msvcrt, ole32, SHELL32, USER32, VERSION (all present on stock 98).

## Download

- Download page: https://www.nirsoft.net/utils/myuninst.html (link "Download MyUninstaller", href `myuninst.zip`)
- URL: https://www.nirsoft.net/utils/myuninst.zip (also served over plain HTTP: http://www.nirsoft.net/utils/myuninst.zip)
- File: myuninst.zip, 52,781 bytes (plain zip, no installer)
- SHA-256: 22f2fc8d324fcd8d36698e0496d7a4c5b69a09f3a36de533f99c83ba4446f799
- MD5: 037be6d876b1e4ab0570f4e0f28e5249
- Server Last-Modified: Mon, 20 Feb 2017 15:55:42 GMT (matches the 1.77 date)
- The http:// copy downloaded separately has the same SHA-256.
- Published checksum: NirSoft does not publish a hash for this file on its page. None to compare.
- Authenticode: myuninst.exe (extracted to a temp folder only to read the signature, never run, then deleted) has a VALID signature, signer "CN=Nir Sofer, O=Nir Sofer, ... C=IL". The zip itself is not signed (zips cannot be).
- Language files (trans/myuninst_*.zip) exist on the same page; not downloaded. Not needed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\myuninstaller -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

Exact License section of https://www.nirsoft.net/utils/myuninst.html (HTML line breaks kept):

> This utility is released as freeware.
> You are allowed to freely distribute this utility via floppy disk, CD-ROM,
> Internet, or in any other way, as long as you don't charge anything for this.
> If you distribute this utility, you must include all files in
> the distribution package, without any modification !

readme.txt in the 1.77 zip has the same text. LICENSE.TXT here holds the License and Disclaimer sections from that readme.

Analysis:
- "freely distribute ... via ... Internet, or in any other way" covers hosting the file on Beacon's server and a package client downloading it.
- "as long as you don't charge anything for this": Beacon is free. OK.
- "you must include all files in the distribution package, without any modification": host the original myuninst.zip byte-for-byte (myuninst.exe, myuninst.chm, readme.txt) and unpack all three files. We do not repack, strip or rename anything inside it. OK.
- The terms do not forbid being listed in a package collection or bundled; nothing needs to be asked. Can be hosted.
- NirSoft's FAQ (https://www.nirsoft.net/faq.html, opened) has no further distribution rules; it does mention a "Forbidden" error for some downloads (NirSoft blocks some hot-linking), another reason to host rather than use external.
- External alternative, if ever needed: `curl.exe -sS -I --http1.0 http://www.nirsoft.net/utils/myuninst.zip` returned HTTP/1.1 200 OK, Content-Length 52781, application/zip (no redirect to HTTPS). http://download.nirsoft.net/myuninst.zip redirects (302) to a 403 page; do not use that.

No source code: freeware, no source obligation.

## Security

- NVD API 2.0 keyword searches "myuninstaller" and "myuninst": 0 results. "nirsoft": 1 result (CVE-2006-3785, which concerns Symantec pcAnywhere, not this tool).
- NirSoft publishes no advisories for MyUninstaller.
- Known security problems: 0 found. No Warning needed.
- Note (not a CVE): the tool can delete uninstall entries and run other programs' uninstallers, which is its purpose.

## Install behaviour

- Installer type: plain zip, no installer. The page: "The MyUninstaller utility is a standalone executable. It doesn't require any installation process or additional DLL's."
- Zip layout (listed with .NET ZipFile), all at the root, no folders:
  - myuninst.exe 46,288 bytes (2017-02-20)
  - myuninst.chm 16,992 bytes
  - readme.txt 16,248 bytes
- Beacon must: unzip everything into `{pf}\MyUninstaller` (no strip), add a Start Menu shortcut to `{dir}\myuninst.exe`, remove with `files`.
- Silent switch: not applicable (no installer).
- Add/Remove Programs: none registered (it is not installed by a setup program). Uninstall via Beacon's own file record.
- Settings: saved to a .cfg file (since 1.37); Quick Mode writes an INI under Application Data. Per readme.

## Verification notes

- Verified by opening or downloading: myuninst.html (full text), myuninst.zip over HTTPS and HTTP, readme.txt inside the zip, the PE header and Authenticode signature of myuninst.exe (not run), nirsoft.net/faq.html, NVD API results, curl HEAD tests.
- Not verified: running on 98/ME (no VM interaction); behaviour on Windows 95 (unknown; not claimed by the author).
- The CHM help needs HTML Help (hh.exe), which stock 98 has only with IE 4+/HTML Help installed; readme.txt covers the same content. Not verified on 98.
