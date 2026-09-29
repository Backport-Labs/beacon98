# Free Pascal 2.6.2 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Free Pascal Compiler (FPC), i386-win32 installer
- Version: 2.6.2 (2013-02-21)
- License: compiler/IDE/tools GPL v2; RTL, packages, FCL: LGPL with static-linking exception (COPYING.FPC)
- Recommendation: 2.6.2. 2.6.4 is the last 2.6.x release, and its readme still lists Win95/98/Me, but its official Win32 installer cannot start on Windows 98 (see below). 3.0 dropped Win9x.

## Windows 9x support evidence

- https://wiki.freepascal.org/User_Changes_3.0 (opened), section "Windows 9x series unsupported": "While 2.6.x formally didn't support the Windows 9x Series, 3rd party maintenance kept most FPC 2.6.x versions working with the Windows 9x series (Windows 95, 98/98SE, ME) ... Starting from this compiler version, the Windows 9x series is not supported anymore ... users that want to use FPC for Win9x development can continue to use earlier compiler versions (e.g. FPC 2.6.4)."
- readme.txt of 2.6.2 (https://downloads.sourceforge.net/project/freepascal/Win32/2.6.2/readme.txt, opened), "Minimum requirements / Win32: Win95/98/Me/2000/2003/XP/Vista or WinNT, 16 MB RAM"; Quick start: "Don't forget to set the PATH environment variable if you install FPC under Win95/98/ME (the installer should do it automatically under WinNT/2k/XP)." The 2.6.4 readme has the same lines.
- Installers inspected (not run):
  - fpc-2.6.4.i386-win32.exe: "Inno Setup Setup Data (5.5.0) (u)" = Unicode Inno Setup, PE subsystem version 5.0. Windows 98 refuses to start a subsystem-5.0 program, and Unicode Inno Setup needs Windows 2000 or later. So 2.6.4 cannot be installed on 98 with its official installer.
  - fpc-2.6.2.i386-win32.exe: "Inno Setup Setup Data (5.5.0)" (ANSI), subsystem 4.0. Also checked 2.6.0: Inno 5.4.2 ANSI, subsystem 4.0.
- The GNU tools shipped in the installer (fpcbuild-2.6.2 `install/binw32`: as, ld, ar, make, gdb, windres, cpp, gcc, rm, cp, zip, unzip, ...) all have subsystem 4.0 and nothing from my list of APIs missing on 98. ppc386.exe itself is inside the compressed Inno data and was not inspected.
- Systems: 95, 98, ME per readme (the 3.0 note says "formally" unsupported in 2.6.x). VM test needed.

## Download

- URL: https://downloads.sourceforge.net/project/freepascal/Win32/2.6.2/fpc-2.6.2.i386-win32.exe (same file at https://downloads.freepascal.org/fpc/dist/2.6.2/i386-win32/)
- File: fpc-2.6.2.i386-win32.exe, 41,195,678 bytes
- SHA-256: 2bdf6428ba5e53f3de01d73e9cd427018e264b725d8ebc93a5c5aafdd483da79
- MD5: 5acaa177d5cd2894a3e0ab6a8c8f32dd
- Published checksum: no md5sum.txt exists for 2.6.2 on downloads.freepascal.org (2.6.4 has one). SourceForge file RSS lists MD5 5acaa177d5cd2894a3e0ab6a8c8f32dd, size 41,195,678: MATCH (SourceForge-generated).
- 2.6.4 for reference (downloaded, kept outside the package folder): 42,312,636 bytes, MD5 973fcb6dc027f020cea1d7c821ee234e, matches the official md5sum.txt.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\freepascal -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT combines copying.fpc, COPYING.v2 and COPYING from fpcbuild-2.6.2 `install/doc/`. The readme: compiler and utilities under GPL (COPYING.v2); some utilities under COPYING.v3, COPYING.DJ, COPYING.EMX, COPYING.RSX, licensez.ip; RTL/packages under LGPL with the exception "object files and libraries linked into an application may be distributed without source code".
- Redistribution of the unmodified installer is allowed; GPL/LGPL need the matching source.

## Matching source (hosted)

- URL: https://downloads.sourceforge.net/project/freepascal/Source/2.6.2/fpcbuild-2.6.2.zip
- File: src/fpcbuild-2.6.2.zip, 61,385,459 bytes
- SHA-256: 1f07fe6f6af6df2ffa2e4b950d5f4f8bae0bd5a7db2f45d2005ee29215906dd5
- MD5 899e3bb799142194b76bee5839c2d84a; SourceForge RSS: MATCH.
- It contains fpcsrc (compiler, RTL, packages, IDE), fpcdocs and the installer tree.
- Not included: the sources of the third-party GNU binaries the installer ships (binutils as/ld/ar etc., gdb, make, GNU fileutils/grep/diff/patch, Info-ZIP zip/unzip, GoRC, libexpat). fpcbuild only has them prebuilt in `install/binw32`. The readme says: "If you cannot find the sources ... please contact us ... and we will provide you the sources or information where to find them." Unresolved: the exact binutils/gdb versions and their sources.

## Security

- NVD keyword "Free Pascal": 0 results. No known CVEs for the compiler. (The bundled old binutils/gdb have CVEs for crafted object files; not counted.)

## Install behaviour

- Installer type: Inno Setup 5.5.0 (ANSI). Silent: `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (standard Inno).
- Default folder: `C:\FPC\2.6.2` (from memory; not confirmed, since the Inno script is not in fpcbuild). The draft entry forces it with `/DIR=C:\FPC\2.6.2`.
- Add/Remove Programs name: unknown (the Inno script was not found). Probably "Free Pascal 2.6.2"; must be read from the registry after a VM install before publishing.
- On 9x the installer does not set PATH (readme); Beacon adds `C:\FPC\2.6.2\bin\i386-win32`.

## Verification notes

- Opened/downloaded: FPC wiki User_Changes_3.0, both readmes, SF RSS for 2.6.2/2.6.4, downloads.freepascal.org listings and 2.6.4 md5sum.txt, both installers (headers read, not executed), fpcbuild-2.6.2.zip (listed; binw32 binaries and docs extracted and inspected), NVD.
- Not verified: running on 98; Add/Remove name; default folder; binutils/gdb source.
