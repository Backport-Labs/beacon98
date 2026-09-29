# GTK+ 2.4.9 runtime - Beacon 98 record

- Date checked: 2026-09-29
- Package: "GTK+ 2 runtime environment" 2.4.9, installer by Jernej Simoncic (the runtime for GIMP 2.0.5)
- Version: 2.4.9. DLL file versions: GTK+/GDK/gdk-pixbuf 2.4.9.0, GLib 2.4.5.0, Pango 1.4.1.0, ATK 1.6.0.0.
- License: GNU LGPL v2 (GTK+ COPYING, "GNU LIBRARY GENERAL PUBLIC LICENSE Version 2"); bundled libraries under LGPL, zlib, libpng, IJG, libtiff, FreeType (FTL/GPL), MIT (fontconfig, expat) licenses
- KernelEx: not needed. The installer has Windows 9x code (adds GTK+ to PATH in AUTOEXEC.BAT); no unicows in any DLL.
- **Recommendation: list as `external`** from ftp.arnes.si, as the runtime of GIMP 2.0.5.

## Why 2.4.9 and not 2.4.14

- The builder's pages over time paired GIMP 2.0.5 with GTK+ 2.4.9 (stable.html capture 2004-10-13), then 2.4.10-20041001 (captures 2004-10-15 to 2004-11-29), and finally 2.4.14 (old.html, 2010). All three satisfy "requires GTK+ 2.4.1 runtime environment or newer".
- 2.4.10 and 2.4.14 were only on SourceForge (gimp-win project gone, 404). On ftp.arnes.si the newest GTK+ 2.4 runtime is gtk+-2.4.9-setup.zip (the mirror also has 2.4.1, 2.4.3 and 2.4.7). The builder's own page of 2004-11-29 still linked the arnes mirror to gtk+-2.4.9-setup.zip for GIMP 2.0.5.
- download.gimp.org /pub/gtk/v2.4/ holds only sources (and `dependencies/`); download.gnome.org /binaries/win32/gtk+/ starts at 2.8. No official server has a newer GTK+ 2.4 runtime installer.

## Windows 9x support evidence (primary)

- Installer text (default.isl+ inside gtk+-2.4.9-setup.exe): `ProblemWin9xME=GTK 2 is no longer actively supported on Windows 9x/ME by the developers. It may run without problems, but don't expect fixes for bugs that only occur on these platforms.` and `WimpWin9x=GTK-Wimp requires that only TrueType fonts are used for Windows display...`
- Builder's GTK+ 2.4 install script (install-scripts.zip on the mirror, GTKVer 2.4.0): on non-NT systems it appends `SET PATH=%PATH%;<GTK>\bin` to AUTOEXEC.BAT, and the installer shows the Wimp/TrueType note on 9x. So 9x is a handled, if unsupported, target.
- Builder's FAQ (capture 2004-11-28) describes running GIMP 2.0 with this runtime on "Windows 9x/ME or NT 4".
- Systems: 98, ME, NT4, 2000. Windows 95 not named separately; not listed. Not tested here.

## Download

| Location | Result (curl.exe -sS -I, 2026-09-29) |
|---|---|
| https://ftp.arnes.si/software/gimp-win/gtk+-2.4.9-setup.zip | 200, Content-Length 4045552, Last-Modified Sun, 26 Sep 2004 21:31:29 GMT |
| http://ftp.arnes.si/software/gimp-win/gtk+-2.4.9-setup.zip | 200 (also with `--http1.0`, and with `%2B` for `+`), same length |

- File: gtk+-2.4.9-setup.zip, 4,045,552 bytes
  - SHA-256: a210b645308c62bf64a0b697ea330f410634ddfda6604d2808b7e4493b3d8efe
  - MD5: e94694b491605df1a02714d2af61c6fc. The builder's stable.html (capture 2004-10-13, when 2.4.9 was the listed runtime) gives e94694b491605df1a02714d2af61c6fc: **MATCH**.
- The zip holds one file, extracted unchanged for inspection:
  - gtk+-2.4.9-setup.exe, 4,068,328 bytes, SHA-256 01f0527fb4be0362697da176ec4e40ab896f204233f868728d643fa47d5d75e6
  - Authenticode: "CN=Jernej Simoncic, O=Software Developer, C=SI" (valid to 2004-11-19); Windows reports Valid.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\gtk-runtime\2.4.9 -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT = COPYING from gtk+-2.4.9.tar.bz2 (https://download.gimp.org/pub/gtk/v2.4/gtk+-2.4.9.tar.bz2, 9,599,004 bytes, SHA-256 d88f79b7bffbc9682a317835b6120dcfb360160a9bb7c6130841232585c30d2c, MD5 bfe3b960d334e81d8f91c3509f70868d = published .md5: MATCH; downloaded to a temporary folder only). The installer shows LIBGPL.RTF (per the script).
- Contents (innoextract: 333 files, 18,063,455 bytes): libgtk/libgdk/libgdk_pixbuf 2.4.9, libglib/gobject/gmodule/gthread 2.4.5, libpango/pangoft2/pangowin32 1.4.1, libatk 1.6.0, iconv.dll 1.9, intl.dll 0.12, asprintf 1.0, charset 1.2, freetype6 2.1.7, jpeg62 6b, libpng12 1.2.5, libtiff3 3.6.1, zlib1 1.2.1, libfontconfig-1, libexpat-0, xmlparse/xmltok (expat 1.x), the GTK-Wimp engine libwimp.dll, pixbuf loaders, input methods, pango modules, locales.
- **Nothing here stops an external listing.** All components permit redistribution of unmodified binaries; the LGPL source duty lies with the distributor. For the record, the mirror's source zip is gtk+-2.4.3-src.zip ("with all dependencies"), not 2.4.9, so we could not host this runtime ourselves.

## Security

NVD API 2.0, virtualMatchString, 2026-09-29 (not checked one by one):

| Component | Matches | Worst |
|---|---|---|
| gtk 2.4.9 | 7 | CVE-2010-4833 (9.3), CVE-2005-2975 / CVE-2005-2976 (gdk-pixbuf XPM, 7.8 / 7.5) |
| glib 2.4.5 | 28 | CVE-2024-52533 (9.8) |
| libpng 1.2.5 | 38 | CVE-2010-1205 (9.8) |
| libtiff 3.6.1 | 126 | CVE-2004-0929 and CVE-2004-1308 (10.0) |
| freetype 2.1.7 | 85 | CVE-2012-1126 (10.0) |
| zlib 1.2.1 | 8 | CVE-2022-37434 (9.8); CVE-2005-2096 also applies |

Not all apply to these Windows builds or code paths. Crafted images and fonts are the risk. Needs a `Warning:`.

## Install behaviour

- Installer type: Inno Setup, setup data version 4.2.5. AppVerName "GTK+ 2.4.9 runtime environment".
- Builder's script (GTK+ 2.4.0 version): `AppID=WinGTK-2`, `DefaultDirName={cf}\GTK\2.0`, stores the folder in `Software\GTK\2.0\Path` (HKLM or HKCU), components base / theme (GTK-Wimp) / loc. When silent it installs to `{cf}\GTK\2.0` ("install into default path when running silent"). On 9x it appends GTK+'s bin folder to PATH in AUTOEXEC.BAT (effective after a restart; GIMP does not need it because its App Paths entry names the GTK+ folder).
- Silent switch: standard Inno `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (not documented by the builder). **Risk on 9x:** when the GTK-Wimp component is selected (the default), the script shows the TrueType-fonts note with a plain `MsgBox` from its Next-button handler. Inno simulates Next clicks when silent, so this box may appear during a silent install on 98/ME and wait for OK. Unverified; test in the VM.
- Uninstaller: yes (Inno). Add/Remove Programs name: **"GTK+ 2.4.9 runtime environment"** (AppVerName; not seen on a machine). AppID WinGTK-2 is shared with the builder's 2.6.10 runtime.
- Installed size: about 17,650 KB with all components.
- Same Beacon format gap as GIMP: the file is a zip around the setup program.

## Verification notes

- Verified: builder's archived pages (MD5, pairing, 9x statements); MD5 match; Authenticode; installer listing, default.isl+, setup.ini; DLL versions; the builder's GTK+ 2.4.0 install script; arnes HEAD responses; tarball MD5; NVD counts; Defender.
- Not verified: running on 98/ME; the 2.4.9 script itself (only the 2.4.0 one was read); the silent-install MsgBox behaviour; the Add/Remove name on a machine.
