# GIMP 2.0.5 - Beacon 98 record

- Date checked: 2026-09-29
- Package: GIMP (GNU Image Manipulation Program) 2.0.5, Windows installer by Jernej Simoncic (the GIMP-for-Windows builder of the time; his installers were linked from www.gimp.org/win32/)
- Version: 2.0.5, the last Windows build of the 2.0 series. The source series ends at 2.0.6 (download.gimp.org/pub/gimp/v2.0/ has `0.0_LATEST-IS-2.0.6`), but the builder never published a Windows build of 2.0.6.
- License: GNU GPL v2 or later (COPYING in gimp-2.0.5.tar.bz2); libgimp* LGPL
- Needs: the GTK+ 2.4 runtime, 2.4.1 or later (package `gtk-runtime`, version 2.4.9 in this record set)
- KernelEx: not needed (the builder's installer has its own Windows 9x/ME code path; see below)
- **Recommendation: list as `external`**, downloaded from ftp.arnes.si, which the builder named as a download mirror. Nothing in the installer stops an external listing.

## Windows 9x support evidence (primary)

- Builder's download page http://gimp-win.sourceforge.net/stable.html, Internet Archive captures of 2004-10-13 and 2004-11-29 (fetched with `id_`): "GTK+ 2 for Windows (version 2.4.9) ... This package is required by The Gimp 2.0.5" (2004-10-13), and "Note: Gimp 2.0.5 available here requires GTK+ 2.4.1 runtime environment or newer, and will not work with older versions."
- Builder's FAQ, http://gimp-win.sourceforge.net/faq.html, capture 2004-11-28: "I'm trying to install Gimp 2.0 on Windows 9x/ME, and the installer informs me, that my operating system is no longer supported. What should I do? - Ideally, you should upgrade to Windows 2000 or newer. Otherwise, you can install The Gimp on Win9x/ME anyway, but don't complain if something doesn't work as expected". The same FAQ describes font warnings seen when running "Gimp 2.0 on Windows 9x/ME or NT 4" and their fix (TrueType display fonts or no GTK-Wimp).
- The installer itself (default.isl+ inside gimp-2.0.5-i586-setup.exe, read with innoextract): `WarningsWin9xME=On Windows 9x/ME, The GIMP 2 is no longer actively supported by the developers. It may run without problems, but do not expect fixes for bugs that only occur on these platforms.` The builder's GIMP 2.0.1 install script (install-scripts.zip on the mirror) shows this is a line on an information page (`if not UsingWinNT() then Warnings := Warnings or 256`), not a stop.
- Summary: runs on Windows 98 and ME without KernelEx, but unsupported by the builder ("may run without problems"). NT4 and 2000 also. Windows 95 is not named separately ("9x"); not listed. Not tested here.
- MSFN's GIMP-on-98 advice (2.0.5 + GTK+ 2.4.14) is the community pick; see ../RECORD.md.

## Download

| Location | Result (curl.exe -sS -I, 2026-09-29) |
|---|---|
| https://ftp.arnes.si/software/gimp-win/gimp-2.0.5-i586-setup.zip | 200, Content-Length 7110219, Last-Modified Sun, 26 Sep 2004 21:28:48 GMT |
| http://ftp.arnes.si/software/gimp-win/gimp-2.0.5-i586-setup.zip | 200 (also with `--http1.0`), same length |

- ftp.arnes.si (Academic and Research Network of Slovenia) is listed as a download mirror on the builder's own stable.html (2004) and old.html (2010). The files still carry their 2004 dates.
- download.gimp.org has no Windows build of 2.0 or 2.2 (`/pub/gimp/v2.0/windows/` and `/v2.2/windows/` answer 404; Windows builds there start at 2.4.0). The builder's SourceForge link (prdownloads.sourceforge.net/gimp-win/...) answers 404; the project is gone. The other mirrors on the builder's page (files.akl.lt, karolyrobert.hu) no longer resolve.
- File: gimp-2.0.5-i586-setup.zip, 7,110,219 bytes
  - SHA-256: c7cf15d1ceb3c6e0c0210a06630d855d060aa6fc53bd7bb8a39b4e1b872bfa6c
  - MD5: 1411e54521bc8127e45de7ed5a832ef1. The builder's page lists 1411e54521bc8127e45de7ed5a832ef1 (stable.html 2004-10-13 and 2004-11-29, old.html 2010-01-02): **MATCH**.
- The zip holds one file, extracted unchanged for inspection:
  - gimp-2.0.5-i586-setup.exe, 7,131,112 bytes, SHA-256 a3869fbffe28ffbd8f5bbb73f0f2f90dee87e376439578e8afb35a244876f8fc, dated 2004-09-27
  - Authenticode: signed by "CN=Jernej Simoncic, O=Software Developer, C=SI" (certificate valid to 2004-11-19); Windows reports Valid.
- Beacon note: the publisher's file is a zip around the setup program. See "Install behaviour" for how the entry handles this.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\gimp\2.0.5 -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0), zip and extracted exe: "found no threats".

## License

- LICENSE.TXT = COPYING from gimp-2.0.5.tar.bz2 (GNU GPL v2). The installer itself shows gpl.rtf (per the builder's script).
- The installer has no COPYING file; innoextract lists 1,196 files, 29,271,682 bytes.
- Bundled third-party DLLs in `bin\` (no version resources): libart_lgpl_2-2 (LGPL), libexif-9 (LGPL), libgsf-1-1 (LGPL), librsvg-2-2 (LGPL), libwmf-0-2-7 and libwmflite (LGPL), liblcms-1 (lcms 1.x, MIT), libxml2 (MIT, version unknown), libXpm-noX4 (MIT-style). Plug-ins are GIMP's own (twain.exe is GIMP's TWAIN plug-in). No Microsoft runtimes, no unicows, no proprietary or personal-use-only components.
- **Nothing here stops an external listing.** Every component permits redistribution of unmodified binaries.
- Sources: not needed for an external package. For the record: GIMP source https://download.gimp.org/pub/gimp/v2.0/gimp-2.0.5.tar.bz2 (14,107,082 bytes, SHA-256 4d20fc0dc9f14382118babc52eb2805c0e30d4fc8900a1fba116d9bced1c7d38, MD5 b24d069b9d670d92fc75ba7035e9300d = published .md5: MATCH; downloaded to a temporary folder only). The mirror has the builder's gimp-2.0.0-src-all.zip (with lcms, libart, libexif, libgsf, librsvg, libwmf) and gimp-2.0.4-src.zip, but no 2.0.5 source zip. So the complete source of this exact build is not on the mirror; that is the distributor's matter, and a reason we could not host it.

## Security

- NVD API 2.0, virtualMatchString cpe:2.3:a:gimp:gimp:2.0.5 (2026-09-29): **34 matches**, not checked one by one.
- Worst that apply: CVE-2009-0723 / CVE-2009-0733 (LittleCMS overflows, CVSS2 9.3; lcms is bundled), CVE-2023-44444 (PSP loader, 7.8), CVE-2016-4994 (XCF use-after-free), CVE-2012-5576 (XWD), and several PCX/PSD/GIF/CEL loader overflows. Some matches do not apply: CVE-2025-5473 (ICO loader; GIMP 2.0.5 has no ICO plug-in) and CVE-2018-12713 (temporary file names).
- The image libraries come from the GTK+ runtime (libtiff 3.6.1, libpng 1.2.5, zlib 1.2.1, FreeType 2.1.7); see gtk-runtime\2.4.9\RECORD.md. Bundled libxml2 (version unknown) and libwmf add more.
- Summary: opening a crafted image can run code. Needs a `Warning:`.

## Install behaviour

- Installer type: Inno Setup, setup data version 4.2.5 (innoextract 1.9). AppVerName "The GIMP 2.0.5".
- Builder's script (for 2.0.1, same series, from http://ftp.arnes.si/software/gimp-win/install-scripts.zip): `AppID=WinGimp-2.0`, `DefaultDirName={pf}\GIMP-2.0`, `DefaultGroupName=GIMP`, Start Menu shortcut "GIMP 2", App Paths entry for gimp-2.0.exe that adds the GTK+ folder, and a page offering 20 file associations (setup.ini). It finds GTK+ through `HKLM`/`HKCU` `Software\GTK\2.0\Path`, so gtk-runtime must be installed first.
- Silent switch: standard Inno `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (not documented by the builder). The 9x/ME note is on a wizard page and does not stop a silent install. A Yes/No box appears only if conflicting DLLs are found in the PATH (script line `MsgBox(S,mbError,MB_YESNO)`); in 4.2.5 `/SUPPRESSMSGBOXES` may not cover it (unverified).
- Uninstaller: yes (Inno). Add/Remove Programs name: **"The GIMP 2.0.5"** (AppVerName, Inno 4 default; not seen on a machine). AppID WinGimp-2.0 is shared with the builder's later 2.x installers, so a later GIMP 2.2 installer replaces it.
- Installed size: about 28,600 KB.
- **Beacon format gap:** Beacon has no kind for "zip containing a setup program". The draft entry uses `Install: unzip {temp}\gimp-setup` and an `After: run` of the setup program. That works with the current format but records the temp folder as the package folder. Better: a small format addition (for example `inno` accepting a zip that holds one .exe). Decide before publishing.

## Verification notes

- Verified (opened or computed): builder's archived stable.html, old.html and faq.html; the MD5 match; Authenticode; installer listing, setup.ini, default.isl+; the builder's 2.0.1 install script; arnes HEAD responses; source tarball MD5; NVD counts; Defender.
- From the 2.0.1 script, not the 2.0.5 one: default folder, shortcuts, AppID. Not verified: running on 98/ME (no VM used), the Add/Remove name on a real machine, silent behaviour when conflicting DLLs are present.
