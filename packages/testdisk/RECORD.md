# TestDisk & PhotoRec 7.2 (DOS build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: TestDisk & PhotoRec (Christophe Grenier, CGSecurity)
- Version: 7.2 (2024-02-22 per the download page; VERSION.txt in the zip: "7.2 Fri Feb  2 06:05:01 PM CET 2024"), DOS/DJGPP build `testdisk-7.2.dos.zip`
- License: GPL-2.0-or-later, plus bundled CWSDPMI r5 (its own terms, redistribution allowed unmodified) and statically linked libntfs-3g (GPL-2.0-or-later) and libext2fs (LGPL-2)
- Recommendation: 7.2 DOS build, hosted with sources. batch2.md named 7.1; 7.2 is newer, stable, and its DOS build is labelled for 95/98 by the project.

## Which build, and why

- Win32 builds do not run on 98 according to the project. https://www.cgsecurity.org/wiki/TestDisk_Download (opened, raw HTML read):
  - 7.2 and 7.1 "Windows 32-bit, minimum requirement: Windows Vista, Windows Server 2008 and above."
  - 7.0 Windows: "(Last version to support Windows XP)". Nothing says any Win32 build supports 9x. Older (6.x, Cygwin-based) Win32 builds were not checked, and there is no project statement that they run on 98, so they were not chosen.
- The DOS build is the one the project names for 9x:
  - Download page: 7.2 and 7.3-WIP DOS links are labelled "Dos/Win95/Win98"; the 7.2 download button says "Dos/Win9x"; 7.1 and 7.0 DOS links are labelled "Dos/Win9x".
  - https://www.cgsecurity.org/wiki/TestDisk (opened): "TestDisk can run under DOS (either real or in a Windows 9x DOS-box), Windows / Windows Server Linux, ..."
  - readme.txt inside testdisk-7.2.dos.zip (read from the zip, not executed): "The DOS version of TestDisk & PhotoRec should work under - MSDOS 6.x - FreeDOS - Windows 95 - Windows 98. If you are using NT 4, Windows 2000..., run the Windows version of TestDisk."
- Windows ME: not named in the readme. The wiki says "Windows 9x DOS-box", which would include ME, but ME is not stated explicitly and was not tested. Systems in the entry: 95, 98.
- 7.3-WIP is a work-in-progress build; not chosen.
- The program is a 32-bit DJGPP program. In a Windows DOS box, Windows provides DPMI; in plain DOS (e.g. "Restart in MS-DOS mode") it loads the bundled CWSDPMI.EXE.
- KernelEx: not needed (DOS program).

## Download

- Page: https://www.cgsecurity.org/wiki/TestDisk_Download (link goes through https://www.cgsecurity.org/Download_and_donate.php/testdisk-7.2.dos.zip, an HTML donate page)
- Direct URL used: https://www.cgsecurity.org/testdisk-7.2.dos.zip (HTTP 200, application/zip, Last-Modified 2024-02-02)
- File: testdisk-7.2.dos.zip, 1,813,834 bytes
- SHA-256: d9174e8a98548a6a5b18e99c8abd3b6915b365fbbc5ec2e5b91dabf6f08fc7c4
- Published checksum: https://www.cgsecurity.org/testdisk_sha256.txt lists `d9174e8a98548a6a5b18e99c8abd3b6915b365fbbc5ec2e5b91dabf6f08fc7c4  testdisk-7.2.dos.zip`: MATCH. (Served over HTTPS from the same server; no signature.)
- Alternative checked: testdisk-7.1.dos.zip (1,344,718 bytes, SHA-256 dbfb544268c76279cc36ecf4af5fd8d048554639db9e47e6764facec0db9bf7c, matches testdisk_sha256.txt). Downloaded to a temp folder only.
- Plain HTTP: `http://www.cgsecurity.org/testdisk-7.2.dos.zip` answers 301 to HTTPS, so "external" is not possible.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\testdisk -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". Scope: the zip and all src\ archives.

## License

- COPYING.txt in the zip is the GNU GPL version 2; the wiki says "GNU General Public License (GPL v2+)"; INFO: "Copyright (C) 1998-2024 Christophe GRENIER".
- Redistributing the unmodified zip is allowed under GPL-2.0 s.1/s.3 with the license text and the complete corresponding source (we host it; s.3(a)/(c) style offer from the same place).
- Bundled / linked components whose sources are NOT in testdisk-7.2.tar.bz2:
  - CWSDPMI.EXE, CWSDPMI r5 (Copyright 1995-2000 C. W. Sandmann). CWSDPMI.DOC in the official csdpmi5b.zip (http://sandmann.dotster.com/cwsdpmi/csdpmi5b.zip, opened): "The files in this binary distribution may be redistributed under the GPL (with source) or without the source code provided: CWSDPMI.EXE or CWSDPR0.EXE are not modified in any way except via CWSPARAM. ... Notice to users that they have the right to receive the source code ... Distributors should indicate a site for the source in their documentation." The copy in TestDisk's zip is the same size (20,125 bytes) as the official r5 binary and differs in exactly one byte (offset 0x4AA4, 0x00 instead of 0x63 'c'), at the start of the swap-file name "?:\cwsdpmi.swp". This looks like the swap file disabled with CWSPARAM, which the terms allow; that it was done with CWSPARAM is my inference. We host the r5 source anyway: src\csdpmi5s.zip.
  - libntfs-3g from ntfs-3g_ntfsprogs 2022.5.17 and libext2fs from e2fsprogs 1.42.8: taken from compile.sh in the 7.2 source (the `*-msdosdjgpp)` case sets VER_LIBNTFS3G="2022.5.17", VER_E2FSPROGS="1.42.8"; the DJGPP configure line uses `--without-ewf --without-iconv`). Whether the published binary was built exactly this way cannot be checked (the exe is UPX-packed). Licenses: ntfs-3g README "distributed under the terms of the GNU General Public License ... version 2 ... or any later version"; e2fsprogs COPYING: lib/ext2fs "made available under the GNU Library General Public License Version 2".
  - DJGPP C runtime and stub loader (DJGPP license, permits binary distribution), and possibly PDCurses (public domain), zlib and libjpeg from the DJGPP environment. Their exact versions are unknown and their sources are not hosted; all are permissive, so no source obligation arises from them.
- LICENSE.TXT here: a Beacon-written summary of the components, the CWSDPMI terms quoted verbatim from CWSDPMI.DOC, the notice to users about their right to the source, then the full GPL-2 (COPYING.txt from the zip).

## Matching source (hosted)

| File | Size | SHA-256 | URL | Published check |
|---|---|---|---|---|
| src/testdisk-7.2.tar.bz2 | 855,781 | f8343be20cb4001c5d91a2e3bcd918398f00ae6d8310894a5a9f2feb813c283f | https://www.cgsecurity.org/testdisk-7.2.tar.bz2 | testdisk_sha256.txt: MATCH |
| src/ntfs-3g_ntfsprogs-2022.5.17.tgz | 1,318,476 | 0489fbb6972581e1b417ab578d543f6ae522e7fa648c3c9b49c789510fd5eb93 | https://download.tuxera.com/opensource/ntfs-3g_ntfsprogs-2022.5.17.tgz (URL named in compile.sh and on the GitHub release page, redirects here) | none published (GitHub release page has no hash) |
| src/e2fsprogs-1.42.8.tar.gz | 5,990,116 | c696d66aac1d48fa02dcf7027bc5c1e921d7cacf0eea529f2dd62d7bdf3a981c | https://mirrors.edge.kernel.org/pub/linux/kernel/people/tytso/e2fsprogs/v1.42.8/e2fsprogs-1.42.8.tar.gz | sha256sums.asc: MATCH (PGP signature not verified) |
| src/csdpmi5s.zip | 88,564 | 1198a2ee09eccf19361411a546b43d6cfb83d6f22247bb3316ee683d093ef63a | https://www.delorie.com/pub/djgpp/current/v2misc/csdpmi5s.zip | none published |

## Security

- TestDisk/PhotoRec itself: NVD API 2.0 keyword searches "testdisk", "photorec" and "cgsecurity" return 0 CVEs; NVD has no CPE for TestDisk. 0 known.
- Statically linked libraries (NVD CPE matches, 2026-09-29):
  - CVE-2022-40284 (CVSS 7.8): NTFS-3G before 2022.10.3, "Crafted metadata in an NTFS image can cause code execution." Affects libntfs-3g 2022.5.17. Reachability through TestDisk's NTFS code paths not verified.
  - CVE-2015-0247 and CVE-2015-1572 (CVSS2 4.6): libext2fs heap overflows (openfs.c / closefs.c) before 1.42.12, via crafted ext2/3/4 metadata.
- Summary: 0 in TestDisk; 3 in bundled libraries; worst CVE-2022-40284. All need the user to point the tool at a crafted NTFS or ext2/3/4 disk or image. On 98 these file systems are rare, so the practical risk is low. A Warning is still proposed.
- Not a security issue but important: TestDisk writes partition tables and boot sectors. Users must read the documentation first.

## Install behaviour

- Type: plain zip, no installer, no uninstaller, nothing in Add/Remove Programs.
- Layout (listed with .NET ZipFile, nothing extracted to run):
  ```
  testdisk-7.2/            (single top folder)
    testdisk.exe 399,624   photorec.exe 556,480   fidentify.exe 283,316
    CWSDPMI.EXE 20,125     testdisk.pdf 563,321   documentation.html 504
    readme.txt  COPYING.txt  NEWS.txt  THANKS.txt  AUTHORS.txt  VERSION.txt  INFO
  ```
  Total unpacked 1,863,791 bytes (about 1,820 KB).
- Beacon: `unzip C:\TESTDISK strip 1` (short 8.3 path because it is a DOS program), `After: path C:\TESTDISK`, shortcuts to testdisk.exe and photorec.exe (Windows creates a DOS-box PIF), `Uninstall: files`.
- Silent switch: not applicable. Add/Remove Programs name: none.

## Verification notes

- Opened/downloaded: TestDisk_Download (raw HTML), TestDisk wiki page, testdisk_sha256.txt, the 7.2 DOS zip (contents read from the archive), testdisk-7.2.tar.bz2 (compile.sh read), CWSDPMI page and csdpmi5b.zip (CWSDPMI.DOC read, binary compared), e2fsprogs sha256sums.asc and COPYING, ntfs-3g README, NVD API.
- The Compile_DOS wiki page is old (DJGPP GCC 3.0.4, PDCurses 2.4) and does not describe how 7.2 was built.
- Not verified: running on 95/98/ME (no VM interaction); exact libraries linked into the published DOS binary (UPX-packed); ME support.
- Side note: during the Defender step `MpCmdRun.exe -GetFiles` was also run by mistake; it only writes Defender's diagnostic cab under ProgramData\Microsoft\Windows Defender\Support.
