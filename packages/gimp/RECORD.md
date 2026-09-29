# GIMP 2.2.17 - Beacon 98 record

- Date checked: 2026-09-29
- Package: GIMP (GNU Image Manipulation Program), Windows installer by Jernej Simoncic (the official GIMP-for-Windows builder of the time)
- Version: 2.2.17 (last 2.2.x release; the source NEWS lists "Bugs fixed in GIMP 2.2.17" as the newest entry). Installer "The GIMP 2.2.17".
- License: GNU GPL v2 or later (COPYING in gimp-2.2.17.tar.bz2)
- Needs: the GTK+ 2.6.10 runtime (package [gtk-runtime]) on Windows 98/ME.
- KernelEx: **not needed** according to the builder's own download page (below). The MSFN/OSR lists that put 2.2.17 under "needs KernelEx" contradict it. Their likely cause is pairing 2.2.17 with the default GTK+ 2.10 runtime, which is for Windows 2000 and newer. Not tested here.
- Recommendation: 2.2.17 with GTK+ 2.6.10. Alternative: 2.0.5 with GTK+ 2.4.14 (MSFN's pick), which is still on the ftp.arnes.si mirror over plain HTTP; not downloaded.
- **Hosting status: on hold.** The GIMP source is hosted, but the installer also bundles LGPL libraries whose exact source versions are not identified (see License). The publisher's own server no longer has the file, so `external` is not possible either.

## Windows 9x support evidence

- The builder's "Old versions" page, http://gimp-win.sourceforge.net/old.html. The live site is gone; it was read from the Internet Archive capture 2010-01-02 (https://web.archive.org/web/20100102175701id_/http://gimp-win.sourceforge.net/old.html, fetched). It says:
  - Gimp 2.4: "GIMP for Windows (version 2.4.7) ... GIMP requires Windows 2000 or newer to run."
  - Gimp 2.2: "GIMP for Windows (version 2.2.17) 7756 kB. If this is the first time you're installing GIMP, you will also need GTK+ 2 Runtime Environment below." MD5 6fef15632433c3cfd7eb74ec027b8246
  - "GTK+ 2 Runtime Environment (version 2.10.13, for Windows 2000 and newer) ... If you have older version of Windows, install GTK+ 2.6 instead."
  - "GTK+ 2 Runtime Environment (version 2.6.10-20050823, for Windows 98/ME and NT4) 3557 kB. This package is required if you want to run GIMP on Windows 98, ME or NT4." MD5 d757d14c18e8aba315023a30d64acad4
  - Gimp 2.0: "GTK+ 2 for Windows (version 2.4.14) ... required by GIMP 2.0.5"; "GIMP for Windows (version 2.0.5)" (MD5 1411e54521bc8127e45de7ed5a832ef1).
- So 2.2.17 is the last GIMP whose builder names a Windows 98/ME route (2.4 needs Windows 2000). Windows 95 is not mentioned; not listed.
- Installer check (innoextract 1.9, not run): `tmp\setup.ini` makes the installer look for the GTK+ DLLs (RequiredGTK libgtk-win32-2.0-0.dll etc., RequiredGLib, RequiredOtherNew with minimum versions such as libpango 1.4.1 and libatk 1.6.0). GTK+ 2.6.10 (pango 1.8.2, atk 1.9.0) satisfies these. The Inno setup data version is 5.1.10, a release that still supports 9x.

## Download

- Official location (dead): https://sourceforge.net/projects/gimp-win/files/Obsolete/GIMP/GIMP%202.2.17/gimp-2.2.17-i586-setup.exe/download (link on the page above). The SourceForge project gimp-win no longer exists: its pages answer 301 to the SourceForge directory and `downloads.sourceforge.net/project/gimp-win/...` answers 404 (checked 2026-09-29). download.gimp.org has no Windows builds for 2.2. **So there is no SourceForge path Beacon can download from; the file must be hosted.**
- Where the local copy came from: it was fetched earlier today by a worker that stalled before recording the address. Its identity is established by the builder's MD5 and signature below.
- File: gimp-2.2.17-i586-setup.exe, 7,941,896 bytes (32-bit Inno Setup installer)
- SHA-256: 3c88df2a42344a3e828eae477462688c148e5bd96b140b62c7d3cabe99d3d066
- MD5: 6fef15632433c3cfd7eb74ec027b8246. The builder's page lists 6fef15632433c3cfd7eb74ec027b8246: **MATCH**.
- Authenticode: signed by "CN=Jernej Simoncic, O=Software Developer, C=SI" (certificate expired 2007-09-17); Windows reports the signature as Valid.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\gimp -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT = COPYING from gimp-2.2.17.tar.bz2 (GPL v2). GIMP itself: GPL v2 or later; libgimp*: LGPL.
- Redistribution of the unmodified installer is allowed with the license and complete corresponding source.
- The installer (listed and unpacked with innoextract, 1,264 entries, about 31 MB) also contains these third-party DLLs in `bin\`, whose source is **not** in the GIMP tarball:
  - libart_lgpl_2-2.dll (libart 2.3.14, per strings; LGPL)
  - libcroco-0.6-3.dll (LGPL)
  - libexif-12.dll (LGPL)
  - libgsf-1-1.dll (LGPL)
  - librsvg-2-2.dll (LGPL)
  - libwmf-0-2-7.dll and libwmflite-0-2-7.dll (LGPL)
  - liblcms-1.dll (lcms 1.x, MIT)
  - libxml2.dll (2.6.20 per strings, MIT)
  - libXpm-noX4.dll (MIT-style)
  - bzip2.dll/bzip2.exe 1.0.2 (BSD-style)
  - minigzip.exe (zlib)
- The DLLs carry no version resources, so the versions of most of them are unknown. The builder's source-code page (gimp-win.sourceforge.net) is gone. **Until the matching sources of the LGPL libraries (libart, libcroco, libexif, libgsf, librsvg, libwmf) are found, the complete-source condition cannot be met.** Next step: the Internet Archive's copies of the gimp-win "Source code" page and SourceForge files (the Archive was offline during this check).
- No patent-encumbered codecs; the GIF and LZW patents have expired.

## Matching source

- GIMP: https://download.gimp.org/pub/gimp/v2.2/gimp-2.2.17.tar.bz2
- File: src\gimp-2.2.17.tar.bz2, 13,102,077 bytes
- SHA-256: 8a4d3b28b3a11ea7564df09c8990d1c90bc3dd713b1dde0737e08603854b01b4
- MD5 4f509ed4a605452d88e04045ff388d58; download.gimp.org's gimp-2.2.17.tar.bz2.md5 says 4f509ed4a605452d88e04045ff388d58: MATCH.
- Missing: the sources of the bundled libraries listed above, and any Windows-specific patches of the builder.

## Security

- NVD API 2.0, virtualMatchString cpe:2.3:a:gimp:gimp:2.2.17: 29 matches (not checked one by one; some concern code not in 2.2, e.g. the DDS plug-in and GEGL, CVE-2021-45463).
- Worst that plausibly apply: CVE-2009-0723 / CVE-2009-0733 (LittleCMS integer and stack overflows, CVSS2 9.3; lcms is bundled), CVE-2016-4994 (XCF load use-after-free, CVSS3 7.8), CVE-2012-2763 (script-fu buffer overflow, 7.5), CVE-2012-5576 (XWD plug-in stack overflows, 7.5), CVE-2025-5473 (ICO integer overflow RCE, 8.8), and several PCX/PSD/PSP/GIF/KiSS CEL loader overflows.
- Bundled libxml2 2.6.20, librsvg, libwmf and the GTK+ runtime libraries have many more (see gtk-runtime).
- Summary: 29 NVD matches, roughly 20+ applicable, triggered by opening crafted image files.

## Install behaviour

- Installer type: Inno Setup ("Inno Setup Setup Data (5.1.10)").
- Silent install: standard Inno `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (not documented by the builder). The installer checks for the GTK+ runtime; install gtk-runtime first.
- Default folder: not read from the setup header (innoextract shows only `app\`); Jernej's GIMP 2.2 installers used `{pf}\GIMP-2.0` (general knowledge, unverified).
- File associations: setup.ini lists 20 image types the installer offers to associate (PSD, GIF, JPEG, PNG, TIFF, BMP, etc.).
- Uninstaller: yes (Inno). Add/Remove Programs name inferred as the AppVerName shown by innoextract: **"The GIMP 2.2.17"** (not seen on a machine).

## Verification notes

- Verified: the builder's archived download page (MD5s and OS statements), MD5 match, Authenticode signer, installer listing and setup.ini, bundled DLL list, GIMP tarball MD5 against download.gimp.org, NVD.
- Not verified: running on 98/ME; the original download address of the local file; the exact versions and sources of the bundled libraries; the default install folder and uninstall display name.

## 2.0.5 (checked 2026-09-29)

- Full record: `2.0.5\RECORD.md`. Catalog draft: `ENTRY.TXT` (now 2.0.5); the 2.2.17 draft is `ENTRY-2.2.17.TXT`.
- Download: https://ftp.arnes.si/software/gimp-win/gimp-2.0.5-i586-setup.zip (also http://), 7,110,219 bytes, SHA-256 c7cf15d1ceb3c6e0c0210a06630d855d060aa6fc53bd7bb8a39b4e1b872bfa6c. MD5 1411e54521bc8127e45de7ed5a832ef1 matches the builder's page. ftp.arnes.si is a mirror the builder listed; download.gimp.org has no Windows build before 2.4.0.
- Needs GTK+ 2.4.1 or newer (builder's page); paired with gtk-runtime 2.4.9, the newest 2.4 runtime still on the mirror.
- 98/ME: installable and runs, but unsupported by the builder ("It may run without problems"); no KernelEx.
- Inno Setup 4.2.5, Add/Remove "The GIMP 2.0.5". Defender clean. GPL v2; bundled libraries all permit redistribution.
- 34 NVD matches; worst lcms CVE-2009-0723/0733 (9.3).
- Recommendation: list as `external` with `Depends: gtk-runtime`. Open point: the file is a zip around the setup program (format gap, see the record).
