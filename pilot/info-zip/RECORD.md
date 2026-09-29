# Info-ZIP Zip 3.0 and UnZip 6.0 - Beacon 98 pilot record

- Date checked: 2026-09-28
- Package: Info-ZIP Zip and UnZip (command-line tools)
- Versions: Zip 3.0 (released 2008-07-05; Win32 binary package dated 2008-10-19) and UnZip 6.0 (released 2009-04-20)
- License: Info-ZIP license, a BSD-style permissive license (Zip binary package carries version 2007-Mar-4; UnZip carries version 2009-Jan-02)
- Recommendation: Zip 3.0 and UnZip 6.0. Both are the latest official releases. Zip 3.1 and UnZip 6.10 were only ever betas (e.g. "unreleased Betas/UnZip betas/unzip610a.zip" on SourceForge), and I found no official statement that the betas drop 9x. The stable releases are recommended.

## Windows 9x support evidence

- Zip 3.0: "Contents" file inside the official Win32 binary package zip300xn.zip (opened):
  "The programs should run on every Windows version that supports 32-bit x86 executables: Windows 9x/ME, Windows NT3.x/NT4/2000/XP/2003/Vista/2008. The Windows port of Zip 3.0 supports Unicode (UTF-8 coded) archive entry names; on the "non-unicode" Windows variants 95/98/ME, this unicode support is limited to the character subset supported by the active ... system codepage".
  The binaries are built with MSVC 6.0 SP6 and the static C runtime, so no extra runtime DLL is needed.
- Zip 3.0 source (zip30.zip, from SourceForge): INSTALL has "WIN32 (Windows NT/2K/XP/2K3 and Windows 95/98/ME)". CHANGES (3.0i05, 2008-06-23): "Win32 zip.exe also supported on Win9x (32-bit)".
- UnZip 6.0: README.NT inside the official unz600xn.exe (opened, dated 20 April 2009):
  "Contents of the UnZip 6.0 distribution archive for Win9x/NT/2K/XP/2K3/Vista/2K8 (Intel)".
  It also notes that the optional *-gcc SFX stubs need msvcrt.dll, "supplied as part of the operating system core for ... Windows 98/Me. Older Windows systems (Win95/NT4) support this runtime DLL when Internet Explorer 4.0 (or newer) is installed."
- UnZip 6.0 source (unzip60.zip): win32/Makefile begins "NMAKE Makefile for Windows NT/2K/XP/... and Windows 95/98/Me". WHERE lists "unz###xN.exe NT/2K/XP/2K3/W9x self-extracting i386 executables".
- Windows 95: named explicitly for Zip ("95/98/ME"). For UnZip, "Win9x" covers it; the main unzip.exe is an MSVC 7.1 static build, and only the optional gcc SFX stubs need msvcrt.dll (IE4) on 95.
- Binary check (not run): all exes have OS/subsystem version 4.0. zip.exe is linked with linker 6.0 and unzip.exe with 7.10. Their imports are ANSI plus a few W functions for runtime-detected Unicode.

## Download

IMPORTANT: the official binary host ftp.info-zip.org no longer resolves in DNS (checked 2026-09-28). The Info-ZIP pages (https://infozip.sourceforge.net/Zip.html, UnZip.html) still name ftp.info-zip.org/pub/infozip/ as the home of "the latest sources and binaries". The SourceForge project (sourceforge.net/projects/infozip) carries only the SOURCE for Zip 3.0 and UnZip 6.0. Its OldFiles/iz-win.zip is a 2005 snapshot with Zip 2.31 and UnZip 5.52 only. The CTAN mirrors listed on the Info-ZIP pages returned 404.

So the binaries were taken from the Internet Archive's copy of the official FTP site:

- zip300xn.zip
  - Original URL: ftp://ftp.info-zip.org/pub/infozip/win32/zip300xn.zip (also http://ftp.info-zip.org/pub/infozip/win32/zip300xn.zip)
  - Retrieved from: https://web.archive.org/web/2019id_/http://ftp.info-zip.org/pub/infozip/win32/zip300xn.zip, which redirects to capture 20230115084431 of the ftp:// URL
  - Size: 355,794 bytes. This matches the size in the archived directory listings from 2012, 2016 and 2019 (dated Oct 18 2008).
  - SHA-256: f8bbc1821d50400245107ce8cfa4a6c7b524387b58bbd6cbe9c20094e82c3bb5
  - MD5: ff523b32f07484ff2e09262284485641
- unz600xn.exe
  - Original URL: ftp://ftp.info-zip.org/pub/infozip/win32/unz600xn.exe
  - Retrieved from: https://web.archive.org/web/2019id_/http://ftp.info-zip.org/pub/infozip/win32/unz600xn.exe, which redirects to capture 20230115084536
  - Size: 414,138 bytes. This matches the archived listings (dated Apr 19 2009).
  - SHA-256: 7869ee36346b47701ef01efd0bc2889f970266b66c80b30f74303d50bf7fa33d
  - MD5: 0c89b294a9765432b08b6039b0a5487a
- Published checksum: NONE. Info-ZIP never published hashes or signatures for these Win32 binaries, as far as I found. The only checks possible were the file sizes against the archived FTP listings (match). Every Wayback timestamp I tried (2011, 2014, 2019, 2022) resolves to the same single 2023-01-15 capture, so there was no independent second copy to compare against.
  This is the weakest provenance in the pilot set. Consider rebuilding from the verified sources below, or finding a second independent copy.
- Also on the old site (not downloaded): unz600dn.zip (UnZip DLL), zip300xn-x64.zip (64-bit), and WiZ (wiz503xn.exe, GUI).

## Source (reference; hosting not required by the license)

- https://downloads.sourceforge.net/project/infozip/Zip%203.x%20%28latest%29/3.0/zip30.zip: MD5 e88492c8abd68fa9cfba72bc08757dba, matches the SourceForge RSS
- https://downloads.sourceforge.net/project/infozip/UnZip%206.x%20%28latest%29/UnZip%206.0/unzip60.zip: MD5 85da5203f01ab0b9403efef3b9bb4010, matches the SourceForge RSS
- Downloaded to a temp folder for evidence only; not stored here.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\pilot\info-zip -DisableRemediation` on 2026-09-28
(engine 1.1.26080.3, signatures 1.459.442.0): "found no threats".

## License

- LICENSE.TXT contains:
  - the LICENSE from zip300xn.zip ("version 2007-Mar-4 of the Info-ZIP license");
  - the LICENSE from unz600xn.exe ("version 2009-Jan-02");
  - README.CR from zip300xn.zip (terms for the built-in traditional PKWARE encryption code).
- Redistributing unmodified binaries is allowed: "Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely". Conditions:
  - Clause 2: binary redistributions "must reproduce the above copyright notice, definition, disclaimer, and this list of conditions in documentation and/or other materials provided with the distribution" (ship LICENSE.TXT).
  - Clause 3: altered versions must be marked and must not be called Info-ZIP releases. This does not apply to us, because we ship the files unmodified.
- There is no obligation to host source.
- Encryption: Zip 3.0 includes traditional ZipCrypto. README.CR covers its usage terms; it is historically export-relevant but weak by modern standards.

## Security

Sources: NVD keyword searches "unzip" / "info-zip". The cpeName queries for info-zip:unzip:6.0 and info-zip:zip:3.0 returned 0 because NVD files these under unzip_project/info-zip_project.

UnZip 6.0 (11 CVEs, plus 3 that may apply):
- CVE-2014-8139: CRC32 verification heap overflow (-t), RCE (CVSS2 7.8).
- CVE-2014-8140: test_compr_eb heap overflow (-t), RCE (7.8).
- CVE-2014-8141: getZip64Data heap overflow, RCE (7.8).
- CVE-2014-9636: extra-field size mismatch, out-of-bounds read/write.
- CVE-2014-9913: list_files buffer overflow, DoS.
- CVE-2015-7696: password-protected archive heap over-read / possible RCE.
- CVE-2015-7697: empty bzip2 data, infinite loop.
- CVE-2016-9844: zipinfo zi_short buffer overflow.
- CVE-2018-1000035: password-protected archive heap overflow (<= 6.00).
- CVE-2018-18384: list.c buffer overflow.
- CVE-2019-13232: overlapping files "better zip bomb", DoS.
- CVE-2021-4217 and CVE-2022-0529/0530: Unicode conversion null dereference / out-of-bounds write. These were found in distribution-patched builds, so applicability to the official Win32 binary is unverified.
- Not applicable: CVE-2015-1315 and CVE-2018-1000031..34 are for 6.10b/6.10c22 betas (and the Unix code).

Zip 3.0 (1 CVE):
- CVE-2018-13410: invalid free / crash when using -T with -TT (CVSS 7.5). The command string is user-supplied.

There has been no upstream release since 2009, so none of the UnZip fixes exist in an official Info-ZIP binary. Linux distributions carry them as patches.
Worst: CVE-2014-8139/8140/8141 (heap overflows reachable when testing a crafted archive).

## Install behaviour

- zip300xn.zip: a plain zip containing zip.exe, zipnote.exe, zipsplit.exe, zipcloak.exe and docs. There is no installer.
- unz600xn.exe: an Info-ZIP UnZipSFX self-extracting archive (console, MSVC 7.1 stub). It is still a valid zip, so the package manager can unpack it with its own unzip instead of executing it. The SFX `-d exdir` option only exists if the stub was built with SFX_EXDIR, which I did not verify, so do not rely on it. There is no silent switch other than normal UnZip options.
- Neither package registers an uninstaller, writes registry entries or creates shortcuts.
- What the package manager must do:
  1. Unpack both into e.g. C:\INFOZIP (BIN).
  2. Add the folder to PATH on 9x (edit AUTOEXEC.BAT: `SET PATH=%PATH%;C:\INFOZIP`, which needs a reboot).
  3. Record the files for removal.
  4. A Start Menu shortcut is not useful for command-line tools. At most, add a shortcut to a DOS prompt opened in that folder.
- The SFX stubs (unzipsfx.exe, SFXWiz32.exe, and the -gcc variants that need msvcrt.dll) can be offered for building self-extractors; they are optional.

## Verification notes

- Verified by opening or downloading: the Info-ZIP pages on infozip.sourceforge.net; SourceForge RSS and file listings; iz-win.zip (2005 snapshot) and its README; archived directory listings of ftp.info-zip.org/pub/infozip/win32/ (2012/2016/2019); the Contents, README.NT and LICENSE files inside both binaries; the source trees zip30/unzip60; PE headers and imports; and NVD.
- NOT verified: the authenticity of the binaries beyond size matching (no published hashes, a single Wayback capture); running on 95/98; the CVE-2021-4217/2022-0529/0530 applicability.
