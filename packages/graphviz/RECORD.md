# Graphviz 2.28.0 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Graphviz (AT&T Research and contributors), graph drawing from the DOT text language (dot, neato, circo, twopi, fdp, sfdp, gvedit, lefty...)
- Version: 2.28.0 (Windows MSI dated 2011-05-16 on the official archive)
- License: Eclipse Public License 1.0 (source). The Windows MSI installs the Common Public License 1.0 text (EPL's predecessor). It bundles LGPL/MIT/GPL third-party libraries.
- Needs KernelEx on Windows 98 and ME, **plus** Windows Installer 2.0 **and** the Microsoft Visual C++ 2008 run-time (MSVCR90.DLL), which the MSI does not install. Not for Windows 95.
- Recommendation: 2.28.0 with KernelEx, as reported. It is heavy (60 MB download, about 160 MB installed) and has the run-time gap. 2.18 is a possible no-KernelEx alternative but is untested (see below).

## Windows 9x / KernelEx evidence

- Operating System Revival, "List of Working Windows 98/ME KernelEx Applications" (downloaded and read 2026-09-29),
  https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html , Other:
  "Graphviz 2.28 (KernelEx 4.5.2)". KernelEx 4.5.2 (the same version Beacon ships). **No mode is given**, so assume the default. Not on the MSFN list.
- Why KernelEx: I read the import tables from files extracted from the MSI's cabinet (nothing installed or run):
  - bin\dot.exe and bin\gvc.dll import **MSVCR90.dll** (Visual C++ 2008 run-time). VC 2008 does not support Windows 9x; its CRT needs functions that 98 lacks.
  - gvedit uses Qt 4.7 (QtCore4.dll 4.7.0.0). GTK+ 2.22 / GLib 2.24 / Pango 1.28 are also included. None of these support 9x.
  - The MSI contains **no MSVCR90.dll**. It carries the Visual C++ 2005 (VC80) merge module, and oddly the amd64 "uplevel" assembly (MsiAssemblyName processorArchitecture amd64). So **the MSVC 2008 run-time must already be present.** One of the three gvc.dll copies even imports the debug run-time MSVCR90D.dll (it sits in a non-bin folder). The VC 2008 redistributable installer does not support 98, so a 98 user needs msvcr90.dll by other means. Beacon cannot supply it (Microsoft component), so the entry has a `Requires: file` line. Not verified in a VM.
- Older version without KernelEx: the official archive has graphviz-2.18.exe (2008-04-01, 8,662,559 bytes, SHA-256 8c5229fe4b90dd54919d2a43a6d23fc49e1f9c826691ad31edcf7f183d13e325; downloaded to a temp folder only). It is a self-extracting zip with Setup.exe + graphviz.zip + Graphviz.ini. Its dot.exe and gvc.dll import **MSVCR80.dll** (Visual C++ 2005, the last Microsoft run-time that supports 98/ME) and only ANSI/9x-available KERNEL32 functions. So 2.18 is a plausible no-KernelEx candidate, but it also does not bundle msvcr80.dll, its Setup.exe was not examined, and nothing states it runs on 98. Unverified; needs a VM test. The .exe installers 1.14 to 2.18 and the .msi builds 2.20.3 to 2.26.3 are also in the archive and were not checked.

## Download

- Official archive: https://www2.graphviz.org/Archive/stable/windows/ (listing opened; "graphviz-2.28.0.msi 2011-05-16 18:48 58M")
- URL: https://www2.graphviz.org/Archive/stable/windows/graphviz-2.28.0.msi
- File: graphviz-2.28.0.msi, 60,429,312 bytes
- SHA-256: 88daeaac300bc0521cedfcacfe928de115d1c4019bdf99a20c238132e6fe991d
- MD5: a76dfa78ef6cee46a445f9802ea419cf
- Published checksum: none for the MSI (the archive has .md5 files only for source tarballs). Not compared.
- There is no zip build for 2.28 (zips start at 2.30.1), so the MSI is the only official Windows form.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\graphviz -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- Source graphviz-2.28.0.tar.gz: COPYING = Eclipse Public License 1.0.
- The MSI installs COPYING = Common Public License 1.0 (and license.rtf, the dialog text: "current versions of the software are now licensed on an open source basis only under The Common Public License"). The Windows packaging still carried the older license text. EPL 1.0 replaced CPL 1.0 with nearly identical terms.
- Both allow distributing unmodified object code if the license terms are included and the source is made available ("states that source code for the Program is available from such Contributor, and informs licensees how to obtain it"). We host the source.
- Third-party components inside the MSI (from its File table): GTK+ 2.x, GLib 2.2x, Pango, ATK, Cairo, gdk-pixbuf, gtkglext, libgladeui (LGPL); Qt 4.7.0 (LGPL 2.1); expat, libxml2, fontconfig (MIT); zlib; libpng 1.2; FreeType 2.1.8; jpeg62 (IJG); glut32.dll (GLUT, freely distributable); libltdl (LGPL); gettext 0.18.1 tools (GPL); Microsoft VC80 CRT merge module. **Their sources are not in graphviz-2.28.0.tar.gz.** For LGPL/GPL compliance, the matching sources should also be offered. Unresolved, and a lot of work for GTK/Qt of 2010-2011.
- LICENSE.TXT = a summary header + EPL-1.0 (COPYING from the tarball) + CPL-1.0 (COPYING from the MSI), unchanged.

## Matching source (hosted)

- URL: https://www2.graphviz.org/Archive/stable/SOURCES/graphviz-2.28.0.tar.gz
- File: src/graphviz-2.28.0.tar.gz, 19,620,087 bytes
- SHA-256: d3aa7973c578cae4cc26d9d6498c57ed06680cab9a4e940d0357a3c6527afc76
- MD5: 8d26c1171f30ca3b1dc1b429f7937e58. Published graphviz-2.28.0.tar.gz.md5: "8d26c1171f30ca3b1dc1b429f7937e58": MATCH.

## Security

- NVD keyword "graphviz": 18 results, of which these concern Graphviz itself and plausibly affect 2.28:
  - CVE-2014-1236 (chkNum stack overflow in the cgraph scanner, v2 10.0), CVE-2014-0978 (yyerror stack overflow, v2 9.3), CVE-2014-1235 (yyerror, 6.8), CVE-2014-9157 (yyerror format string, 7.5). These are stated for 2.34.0; 2.28 ships lib/cgraph, so it is probably affected.
  - CVE-2020-18032 (buffer overflow, "commit f8b9e035 and earlier", CVSS 7.8).
  - CVE-2018-10196 (dotgen NULL dereference), CVE-2019-9904 (cdt stack consumption), CVE-2019-11023 (cgraph NULL dereference): DoS.
  - Not affected: CVE-2005-4803 (before 2.2.1), CVE-2008-4555 (2.20.2 and earlier), CVE-2023-46045 (2.36.0 and later). The others are other products.
- Summary: about 8, the worst being CVE-2014-1236 / CVE-2020-18032 (code execution from a crafted .dot file). The bundled GTK/cairo/libpng/libxml2/Qt of 2010-2011 add more that were not counted.

## Install behaviour

- Installer type: MSI made with a Visual Studio setup project (VSD* properties, DIRCA_TARGETDIR). Summary: schema 200, so **Windows Installer 2.0 or later** is required. Stock 98 SE has none; 2.0 must be installed first. It has no LaunchCondition that blocks 9x.
- Silent: `msiexec /i graphviz-2.28.0.msi /qb` (FORMAT.md `msi` kind). ALLUSERS=2.
- Default folder: `[ProgramFilesFolder][ProductName]` = `C:\Program Files\Graphviz 2.28` (CustomAction DIRCA_TARGETDIR). Start Menu folder "Graphviz 2.28".
- Add/Remove Programs: ProductName **"Graphviz 2.28"**, ProductCode {D437FFB6-5C49-4DAC-ABAE-33FF065FE7CC}, Manufacturer "AT&T Research Labs". Windows Installer registers the uninstall key under the ProductCode with DisplayName = ProductName.
- 799 files, 165,563,322 bytes unpacked. Includes bin\, lib\, include\ (development files), share\, fonts\, gtk-2.0\ configuration.
- Side effects: the SxsInstallCA/SxsUninstallCA custom actions come from the VC80 merge module. The effect on 98 is unknown.

## Verification notes

- Verified by opening or downloading: the OSR KernelEx list, the www2.graphviz.org archive listings, the MSI (read-only queries of the Property, CustomAction, Directory, File, Media and MsiAssemblyName tables and the summary info, with the Windows Installer COM API in read-only mode; nothing installed), and dot.exe, gvc.dll, COPYING and license.rtf extracted from the MSI cabinet with 7-Zip (not run). Also the source tarball COPYING, the graphviz-2.18.exe structure and imports, and NVD.
- Not verified: running on 98 (no VM interaction); how a 98 user obtains msvcr90.dll; 2.18 on stock 98.
