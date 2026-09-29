# GTK+ 2.6.10 runtime (2005-08-23) - Beacon 98 record

- Date checked: 2026-09-29
- Package: GTK+ 2 Runtime Environment for Windows, installer by Jernej Simoncic (the runtime GIMP 2.2 uses on Windows 98/ME/NT4)
- Version: 2.6.10-20050823. It contains GTK+ 2.6.10 (with one patched file, gtkcombobox.c), GLib 2.6.6, Pango 1.8.2, ATK 1.9.0 and the libraries listed below.
- License: GNU LGPL v2 (GTK+ COPYING: "GNU LIBRARY GENERAL PUBLIC LICENSE Version 2"); bundled libraries under LGPL/MIT/BSD-style/IJG/libtiff/FreeType licenses
- KernelEx: not needed. GLib/GTK 2.6 contain their own Windows 9x code paths and do not use unicows (no "unicows" string in libglib or libgtk).
- Recommendation: 2.6.10-20050823. The builder's page names it as the runtime for Windows 98/ME/NT4; the next one, 2.10.13, is "for Windows 2000 and newer".
- **Hosting status: nearly ready, three sources missing** (see Matching source). No `external` option (the builder's SourceForge project is gone).

## Windows 9x support evidence

- Builder's "Old versions" page (Internet Archive capture 2010-01-02 of http://gimp-win.sourceforge.net/old.html, fetched): "GTK+ 2 Runtime Environment (version 2.6.10-20050823, for Windows 98/ME and NT4) 3557 kB. This package is required if you want to run GIMP on Windows 98, ME or NT4. It is recommended to use GTK+ 2.10 on Windows 2000 and newer." MD5 d757d14c18e8aba315023a30d64acad4. And for 2.10.13: "for Windows 2000 and newer".
- Windows 95: not mentioned; not listed.

## Download

- Official location (dead): https://sourceforge.net/projects/gimp-win/files/Obsolete/GTK%2B/GTK%2B%202.6.10-20050823/gtk%2B-2.6.10-20050823-setup.zip/download. The gimp-win SourceForge project no longer exists (301 to the directory, downloads 404, checked 2026-09-29). **No SourceForge path to download from; must be hosted.**
- Where the local copy came from: fetched earlier today by a worker that stalled before recording the address. Its identity rests on the builder's MD5 and signature.
- File as published: gtk+-2.6.10-20050823-setup.zip, 3,642,399 bytes, SHA-256 d3f7e0a352d6d0ecf9871b28f82e9e799b24fb91ccc5d77e1f328aacfca11fd3, MD5 d757d14c18e8aba315023a30d64acad4. The builder's page lists d757d14c18e8aba315023a30d64acad4: **MATCH**.
- The zip holds one file, the installer, which Beacon should host as is (Beacon has no "unzip then run" install kind). It was extracted unchanged:
  - gtk+-2.6.10-20050823-setup.exe, 3,666,752 bytes, SHA-256 7b1818cca97f92ee8a90076c4df83a929efc82eef0896f770e240a12bc667ffd
  - Authenticode: signed by "CN=Jernej Simoncic, O=Software Developer, C=SI"; the chain does not build to a trusted root on this host (old certificate).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\gtk-runtime -DisableRemediation` on 2026-09-29 (after adding the extracted exe;
engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT = COPYING from gtk+-2.6.10.tar.bz2 (GNU Library GPL v2). GLib, Pango, ATK, gettext's libintl and libiconv are also LGPL. Bundled: zlib (zlib license), libpng (libpng license), libjpeg 6b (IJG), libtiff (BSD-style), FreeType (FTL or GPL), fontconfig (MIT), expat (MIT). All permit redistribution of unmodified binaries; the LGPL parts need their source offered.
- Installer contents (innoextract, 298 entries, about 14.4 MB), with DLL file versions:
  - libgtk-win32/libgdk-win32/libgdk_pixbuf 2.6.10.0
  - libglib/gobject/gmodule/gthread 2.6.6.0
  - libpango/pangoft2/pangowin32 1.8.2.0
  - libatk 1.9.0.0
  - iconv.dll 1.9, intl.dll 0.12, asprintf.dll 1.0, charset.dll 1.2
  - freetype6.dll 2.1.8, jpeg62.dll 6b, libpng12.dll 1.2.5, libpng13.dll 1.2.8, libtiff3.dll 3.7.3, zlib1.dll 1.2.1
  - libfontconfig-1.dll, libexpat-0.dll, xmlparse.dll/xmltok.dll (expat 1.x)
  - the GTK-Wimp theme engine `lib\gtk-2.0\2.4.0\engines\libwimp.dll`
  - the pixbuf loaders, input methods and pango modules

## Matching source (in src\)

| File | Size | SHA-256 | Where it is available now (checked by size) |
|---|---|---|---|
| gtk+-2.6.10.tar.bz2 | 11,521,380 | d408b606c8dd414dfbf220ccc168a0bc85a419945439796792a5357a96ff02af | https://download.gnome.org/sources/gtk+/2.6/ |
| gtk+-2.6.10-20050823.README (describes and contains the patched gtkcombobox.c) | 155,472 | f420a13c07cfc554e5547b92c67e7c61fd5913b07a244b1a31c2bcb7f08a5a92 | origin not recorded (was download.gnome.org binaries/win32/gtk+/2.6, now 404) |
| glib-2.6.6.tar.bz2 | 2,380,899 | de4f25424840b8e3b1fb03e6bac0c095affc3ca9c228f8b780817489914bdebf | download.gnome.org/sources/glib/2.6/ |
| pango-1.8.2.tar.bz2 | 1,021,372 | 4cf04489ff291f3f1835783b8cfa8347d99f6a05d7d9da21c8d737f441bea3ac | download.gnome.org/sources/pango/1.8/ |
| atk-1.9.0.tar.bz2 | 518,003 | 6a33f5b7caab4e837ac671b4b6974059f62a2ef0fd62a9bc04c74d47f077ff14 | download.gnome.org/sources/atk/1.9/ |
| gettext-0.13.1.tar.gz | 6,458,256 | d3de5f019036772f18ae3b0ee1c3dcf6b255119e78edd81a4e1ffe932e032a4a | https://ftp.gnu.org/gnu/gettext/ |
| libiconv-1.9.1.tar.gz | 3,907,735 | ace5af6c576181a489382fa5339a2e5561284512c41989f4eff61ca09ac3583a | https://ftp.gnu.org/gnu/libiconv/ |
| freetype-2.1.8-src.zip | 2,292,930 | 8f44c563b3a0069fac4b1e50e25a25eb9a03c4cbeba3990339edac62f0de949c | SourceForge gnuwin32/freetype/2.1.8 |
| jpeg-6b-4-src.zip | 910,109 | fdf5a7d3c14647fabc689a91d5a03538e839467be08a553f21ad9f4b8d87d372 | SourceForge gnuwin32/jpeg/6b-4 |
| libpng-1.2.5-1-src.zip | 716,878 | b4b75d5dbdb3276000b984f1c339ef61521a53bcf499a5f3546c71b1e0e9dc79 | SourceForge gnuwin32/libpng/1.2.5-1 |
| libpng-1.2.8-src.zip | 698,344 | d6dea7faacaaab1ee1b5e79cd23b6208317a4e537a1950e13fc1f2b0384c7ba7 | SourceForge gnuwin32/libpng/1.2.8 |
| tiff-3.7.3-src.zip | 2,082,207 | dcf3f84ce64d7cd8e4cde933f95c40336d208bc18a36ab76c43ce92e7fa0c099 | SourceForge gnuwin32/tiff/3.7.3 |
| zlib-1.2.1-1-src.zip | 463,626 | 4e47b3e025d22514e57cd6e10cdd14e780f393aff85723173acdf300f48c9d55 | origin not recorded (not on gnuwin32 or download.gnome.org now) |
| fontconfig-2.2.2.tar.gz | 743,895 | 1cf4add79211ec9ae03cc28a83f04a9045d728a954038e5078df0d4911ff31b7 | https://www.freedesktop.org/software/fontconfig/release/ |
| fontconfig-2.2.1-tml-20040201.diff (Windows patch) | 1,376 | c272ce7247a339d260cd5f9fae128cabc1d94370e8bf97ec664b3878ebfde780 | origin not recorded |
| expat-1.95.7.tar.gz | 296,718 | c94817c67c8ff0d244092c19f5713ea8c76a9a19075ff6031d4ef93ec7b66256 | SourceForge expat/expat/1.95.7 |

- The SourceForge-hosted sources above are available at `http://downloads.sourceforge.net/project/gnuwin32/...` and `.../project/expat/...`. They are the sources, not the package files.
- Not published checksums: none of these were compared with published checksums (download.gnome.org has sha256sum files per folder; not fetched). Sizes match the current servers.
- **Missing or uncertain:**
  1. The source of the GTK-Wimp engine libwimp.dll (a separate gtk-wimp project in the GTK+ 2.6 era).
  2. The source of xmlparse.dll/xmltok.dll (expat 1.x).
  3. Whether intl.dll (file version 0.12) was built from gettext 0.13.1 or 0.12.x; asprintf.dll and charset.dll are assumed to come from gettext/libiconv.
  4. The addresses of the three "origin not recorded" files.
  These gaps must be closed before hosting, as the LGPL requires.

## Security

- NVD (virtualMatchString, 2026-09-29):
  - gtk 2.6.10: 6 matches; worst CVE-2010-4833 (9.3) and CVE-2005-2975 (gdk-pixbuf XPM, 7.8)
  - glib 2.6.6: 28; worst CVE-2024-52533 (9.8)
  - libpng 1.2.5: 38; worst CVE-2010-1205 (9.8)
  - libtiff 3.7.3: 117; worst CVE-2015-8668 (9.8)
  - freetype 2.1.8: 84; worst CVE-2012-1126 (10.0)
  - zlib 1.2.1: not queried under the right CPE; CVE-2005-2096 is known from general knowledge
- Not every match applies to Windows builds or to the code paths used. Crafted images and fonts are the main risk.

## Install behaviour

- Installer type: Inno Setup (setup data version 5.1.2 per innoextract).
- Silent install: standard Inno `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (not documented by the builder).
- Default folder: chosen by the script's `GetGTKPath` code (Jernej's runtimes installed to `{commonfiles}\GTK\2.0` and put that `bin` on PATH; general knowledge, unverified). GIMP's installer then finds the DLLs there.
- Uninstaller: yes (Inno). Add/Remove Programs name inferred from the AppVerName reported by innoextract: **"GTK+ 2.6.10-20050823 runtime environment"** (not seen on a machine).

## Verification notes

- Verified: the builder's archived page (OS statement and MD5), MD5 match, signer, installer listing and DLL versions, source sizes against current servers, NVD counts.
- Not verified: running on 98/ME; the origin of three src files; the sources listed as missing; the default folder and uninstall display name.

## 2.4.9 runtime for GIMP 2.0.5 (checked 2026-09-29)

- Full record: `2.4.9\RECORD.md`. Catalog draft: `ENTRY.TXT` (now 2.4.9); the 2.6.10 draft for GIMP 2.2.17 is `ENTRY-2.2.17.TXT`.
- Download: https://ftp.arnes.si/software/gimp-win/gtk+-2.4.9-setup.zip (also http://), 4,045,552 bytes, SHA-256 a210b645308c62bf64a0b697ea330f410634ddfda6604d2808b7e4493b3d8efe. MD5 e94694b491605df1a02714d2af61c6fc matches the builder's page of 2004-10-13, which paired 2.4.9 with GIMP 2.0.5.
- 2.4.14 (the builder's final pairing) was only on SourceForge and is gone; 2.4.9 is the newest 2.4 runtime on the mirror and meets GIMP 2.0.5's "2.4.1 or newer".
- GTK 2.4.9, GLib 2.4.5, Pango 1.4.1, ATK 1.6.0. 98/ME handled by the installer (AUTOEXEC.BAT PATH) but unsupported ("may run without problems"); no KernelEx.
- Inno Setup 4.2.5, Add/Remove "GTK+ 2.4.9 runtime environment". Defender clean. LGPL v2 and permissive licenses.
- Recommendation: list as `external`. Open points: the zip format gap, and a possible message box (GTK-Wimp font note) during a silent install on 9x.
