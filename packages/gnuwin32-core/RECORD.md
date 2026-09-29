# GnuWin32 core tools - Beacon 98 record

- Date checked: 2026-09-29
- Package id: gnuwin32-core
- Publisher: GnuWin32 project (https://gnuwin32.sourceforge.net/, files on SourceForge project `gnuwin32`)
- Contents (12 binary zips, installed together):

| Tool / library | GnuWin32 release | Files it provides | Build date |
|---|---|---|---|
| grep | 2.5.4 | grep.exe, egrep.exe, fgrep.exe | 2009-02-13 |
| sed | 4.2-1 (sed 4.2) | sed.exe | 2009-06-07 |
| gawk | 3.1.6-1 | gawk.exe, awk.exe, pgawk.exe | 2008-02-10 |
| wget | 1.11.4-1 | wget.exe, etc/wgetrc | 2008-12-31 |
| diffutils | 2.8.7-1 | diff.exe, cmp.exe, diff3.exe, sdiff.exe | 2004-05-24 |
| less | 394 | less.exe, lesskey.exe, lessecho.exe | 2006-01-03 |
| which | 2.20 | which.exe | 2008-08-10 |
| libiconv | 1.9.2-1 | libiconv2.dll, libcharset1.dll, iconv.exe | 2004-10-14 |
| libintl (gettext) | 0.14.4 | libintl3.dll | 2005-05-06 |
| PCRE | 7.0 | pcre3.dll, pcreposix3.dll, pcregrep.exe, pcretest.exe | 2007-03-17 |
| regex (glibc) | 2.7 | regex2.dll | 2007-10-24 |
| OpenSSL | 0.9.8h-1 | libeay32.dll, libssl32.dll, openssl.exe, test programs | 2008-08/09 |

- Recommendation: this set. All are the newest GnuWin32 builds of each tool whose own
  GnuWin32 page/README lists Windows 95/98/ME, except sed, where the newest (4.2.1, Dec 2010) lists
  NT and later only, so the previous release 4.2-1 is used.
- The pool folder name `2009.06` is a Beacon label (date of the newest file, sed 4.2-1), not a GnuWin32 version.

## Windows 9x support evidence

- https://gnuwin32.sourceforge.net/ (opened): "Starting with 2010, patches for making programs run on
  MS-Windows 9x (95 / 98 / ME) and NT will not be updated; existing code patches will not be removed so
  that new releases of existing packages may still run on 9x and NT, but no new changes will be made."
  and "If a package does not run on 9x or NT, use an older release."
- Package pages (all opened 2026-09-29, `https://gnuwin32.sourceforge.net/packages/<name>.htm`), section Requirements:
  - grep 2.5.4, wget 1.11.4, which 2.20: "Win32, i.e. MS-Windows 95 / 98 / ME / NT / 2000 / XP / 2003 / Vista / 2008 with msvcrt.dll and msvcp60.dll."
  - gawk 3.1.6, regex 2.7, pcre 7.0: "... 95 / 98 / ME / NT / 2000 / XP / 2003 / Vista ..." (pcre: "... / 2003")
  - diffutils 2.8.7: "MS-Windows 95 / 98 / ME / NT / 2000 / XP with msvcrt.dll."
  - less: page shows version 394 (the package list says 406, but SourceForge has no 406 files; 394 is the newest there): "... 95 / 98 / ME / NT / 2000 / XP / 2003 ..."
  - libintl 0.14.4: "MS-Windows 95 / 98 / ME ..."; openssl 0.9.8h: "... 95 / 98 / ME / NT / 2000 / XP / 2003 / Vista / 2008 ..."
  - **sed**: the current page is for 4.2.1 (28 December 2010) and says "MS-Windows NT / 2000 / XP / 2003 / Vista / 2008 / 7". The Wayback Machine copy of the same page from 2010-07-22 (https://web.archive.org/web/20100722110200/http://gnuwin32.sourceforge.net:80/packages/sed.htm, opened) is for sed 4.2, binaries dated 7 June 2009, MD5 ee89b5bf6f2f9883b6e4e93eb897c47a, and says "Win32, i.e. MS-Windows 95 / 98 / ME / NT / 2000 / XP / 2003 / Vista / 2008". That MD5 is the sed-4.2-1-bin.zip used here.
- The GnuWin32 README inside each binary zip (read from the zip, not run) repeats the same line, e.g. `contrib/sed/4.2/sed-4.2-1-GnuWin32.README`: "Win32, i.e. MS-Windows 95 / 98 / ME / NT / 2000 / XP / 2003 / Vista / 2008 with msvcrt.dll"; `libiconv-1.9.2-1-GnuWin32.README`: "MS-Windows 95 / 98 / ME / NT / 2000 / XP with msvcrt.dll".
- Static check done here (PE import tables parsed with a script, nothing executed): every .exe and .dll
  in the set has PE OS/subsystem version 4.0, imports only ANSI or 9x-present Win32 functions from
  KERNEL32/ADVAPI32/USER32/GDI32/OLE32 (the only W function is USER32 GetUserObjectInformationW in
  libeay32, which exists on 9x and OpenSSL only calls it on NT), and every import from a GnuWin32 DLL
  resolves against the DLLs in this set (checked function by function). So no KernelEx is needed.
- External runtime DLLs: msvcrt.dll (in Windows 98) for all; **MSVCP60.DLL** for grep, egrep, fgrep,
  sed, gawk and diff; WS2_32.DLL (Winsock 2) for wget, which Windows 95 only has after the Winsock 2 update.
  Whether MSVCP60.DLL is present on a stock 98/98 SE install was not verified here, so the entry has a
  `Requires: file {sys}\MSVCP60.DLL` line.
- Windows 95 and ME: listed by every GnuWin32 page above. Not tested in a VM.

## Download

All files from the official GnuWin32 SourceForge project, URL pattern
`https://downloads.sourceforge.net/project/gnuwin32/<pkg>/<release>/<file>`.
Published checksums: GnuWin32 publishes MD5 on each package page, and SourceForge lists MD5 in its file RSS
(`https://sourceforge.net/projects/gnuwin32/rss?path=/<pkg>/`). All 24 files MATCH the SourceForge MD5;
all that appear on the current package pages also match those pages (and sed 4.2-1 matches the 2010 archived page).
Not signed.

| File | Bytes | SHA-256 | MD5 (matches SF) |
|---|---|---|---|
| grep-2.5.4-bin.zip | 451824 | 3fd98201561b5af3f54a7dacc4f88068f5b5edf19ccdfc981c3c9fc60ff73519 | c1733d1bc0def1e47f99bad83a0e3116 |
| sed-4.2-1-bin.zip | 368423 | 7956b4ded4804aad8d72cb65b57c10265fb34eb56e38b2ff41a1336881a5f063 | ee89b5bf6f2f9883b6e4e93eb897c47a |
| gawk-3.1.6-1-bin.zip | 1448542 | f05128cc735e8a4a0dff027a2c54a8ce69c30b4c0774bfb2994638317927c224 | f875bfac137f5d24b38dd9fdc9408b5a |
| wget-1.11.4-1-bin.zip | 850448 | 40dc40fe4f9aa02644c2648d7d337632f5a50eed004e3d3b68da0306e4f50f1b | 254b95bd96564eb6db590f2b51f8fd8b |
| diffutils-2.8.7-1-bin.zip | 456027 | 6d64ee291c9b49a2841dbccea9795140802ff6b73fd2f4848635bbc974dc5a9c | 9e0d232d7a15b4b7b72556ecc2710a42 |
| less-394-bin.zip | 176349 | cd8233cb3caee8ccbbed6883443f44f2002218eceb4d697d38a0c40c2d181896 | 20f94bcc8a3347bd9a9ca32587d82eae |
| which-2.20-bin.zip | 41833 | 035ec15541649f75459fb81f02406c72e1129fc9041b308160938ae712a603a4 | ad4a994a82f90f24bd0d6ac2a64696f7 |
| libiconv-1.9.2-1-bin.zip | 828380 | 66f494fb37d2ac9367ef8398071f19db4b670a3d2ea2361f970d65195c336bd9 | 2ded584cdcfc87e1e3db257dd5b44651 |
| libintl-0.14.4-bin.zip | 394081 | 4e2e5f2e9becb50ee9d828f2400ca4115a8887d99c3c2b8fb59b1b77e504655b | 8ba5be33e4208bf9584b176ec606bb06 |
| pcre-7.0-bin.zip | 302480 | a28aeda3ef00951f21ecd8d97f72fe015a8081fc365248850494d241bbd8a7c3 | b2e24f4a84236e0d9695bb26dff8c59e |
| regex-2.7-bin.zip | 73283 | 64d7c7f2fc9e121d468e676af9fa3b074d552aefb8529221dd4c832baa186767 | 1c097334c32f7b977093f38b105e7580 |
| openssl-0.9.8h-1-bin.zip | 5906403 | 920c1473ed6646701cc5179b6d0a81d260228499568013334bc6f73b7f6e0787 | a1d4868d6115b654f86c68821f6be8b0 |

Total download 11,298,073 bytes (sources: 33,702,746 bytes); about 26.9 MB unpacked.

### Why standalone library zips instead of the "-dep.zip" files

The dependency zips that GnuWin32 pairs with grep 2.5.4, sed 4.2-1 and wget 1.11.4 (all dated 2008-03-14
or later) contain a **libiconv2.dll version 1.12** (file version 1.12.2872.39125). GnuWin32 never published a
libiconv 1.12 package or source; its libiconv folder on SourceForge stops at 1.9.2-1. Hosting that DLL would
mean distributing LGPL object code without its matching source. So this package uses the standalone
GnuWin32 library releases instead, each of which has a GnuWin32 source zip:

- libiconv2.dll from libiconv-1.9.2-1-bin.zip (instead of 1.12). Only libintl3.dll imports libiconv2; all of its
  imports resolve against the 1.9.2 DLL.
- libintl3.dll from libintl-0.14.4-bin.zip: byte-identical to the one in the grep/sed/wget dep zips.
- pcre3.dll from pcre-7.0-bin.zip: byte-identical to grep-2.5.4-dep's. less 394 was built against PCRE 6.4
  (its own dep zip has pcre3.dll 6.4); all less.exe imports resolve against 7.0.
- regex2.dll from regex-2.7-bin.zip: byte-identical to grep/sed dep.
- libeay32.dll and libssl32.dll from openssl-0.9.8h-1-bin.zip: byte-identical to wget-1.11.4-1-dep's.
- diffutils 2.8.7 was built with libintl 0.14.1 (its dep zip); all diff/cmp/diff3/sdiff imports resolve against 0.14.4.

The combinations are a static check only (import tables vs export tables); they have not been run on Windows 98.
The unused dep zips were downloaded (all matched SF MD5) and moved out of the package folder:
grep-2.5.4-dep.zip, sed-4.2-1-dep.zip, wget-1.11.4-1-dep.zip, diffutils-2.8.7-1-dep.zip, less-394-dep.zip.
Note: the diffutils package page gives dep MD5 daaf108f481ebdb19c8621141da350d4, while SourceForge and the
downloaded file have 8535974bc8999a18a7329eefe5340ca4 (page out of date; file not used).

Alternative if the lighter wget-1.11.4-1-dep.zip (1.4 MB) is preferred over openssl-0.9.8h-1-bin.zip (5.9 MB):
it carries the same OpenSSL DLLs but also the unsourced libiconv 1.12, so it is not recommended.
The GnuWin32 Setup .exe installers were not used (they also bundle the dep DLLs).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\gnuwin32-core -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats" (binary zips, src zips, LICENSE.TXT).

## License

Checked in the COPYING/LICENSE files inside the zips and in the source file headers:

- grep 2.5.4, sed 4.2, gawk 3.1.6, which 2.20: GPL version 3 or later (COPYING is GPLv3; grep.c, execute.c, main.c, which.c headers "version 3, or (at your option) any later version").
- wget 1.11.4: GPL-3.0-or-later plus "Additional permission under GNU GPL version 3 section 7" allowing it to be linked with OpenSSL; "Corresponding Source for a non-source form of such a combination shall include the source code for the parts of OpenSSL used as well as that of the covered work." That is met by hosting openssl-0.9.8h-1-src.zip.
- diffutils 2.8.7: GPL-2.0-or-later. less 394: GPL-2.0-or-later or the Less License (README: "1. The GNU General Public License ... 2. The Less License").
- libintl 0.14.4 and libiconv 1.9.2 (library and iconv.exe): GNU Library GPL version 2 or later (dcigettext.c, iconv.c headers; COPYING.LIB).
- regex 2.7 (from glibc 2.7): LGPL-2.1-or-later (regex.c header).
- PCRE 7.0: BSD licence (LICENCE file).
- OpenSSL 0.9.8h: OpenSSL License + original SSLeay License (dual, BSD-style, with advertising clauses). The required acknowledgements are in LICENSE.TXT.
- LICENSE.TXT (120,881 bytes, Windows-1252, CR LF) contains: a summary of which file is under which license, the wget OpenSSL permission, GPLv3, GPLv2, the Less License, LGPL 2.1, LGPL 2.0 (Library GPL), the PCRE licence and the OpenSSL license, each copied from the files in the zips.
- Redistribution of the unmodified zips is allowed. Conditions: include the licenses, and offer the complete corresponding source for the GPL/LGPL parts. Hosted below.

## Matching source (hosted)

GnuWin32 source zips from the same SourceForge folders (each contains the patched source tree GnuWin32 built from).
All MD5 MATCH the SourceForge RSS and the package pages.

| File | Bytes | SHA-256 | MD5 |
|---|---|---|---|
| src/grep-2.5.4-src.zip | 1361303 | 4591fa32fbed45abd9ace524db4847f68f60a478725441fdfab3602a57983b67 | 4cf2736470dd56094cf7d4930ff796bf |
| src/sed-4.2-1-src.zip | 2072628 | dd99ae79b0bc1f53bfbc21c0ea82818bb2cd47a68107900a80dea2e516de5908 | 67b2836670be0118b5c0942ffa840739 |
| src/gawk-3.1.6-1-src.zip | 3126204 | 78eec584753be8204e94fb0efea79e27bef5f5b2deb270c6c3874c935e14a16c | 299f9fd976aded253a5a4610ca0f2b11 |
| src/wget-1.11.4-1-src.zip | 2189442 | 8732dbdefdb34fe0938ec0cb7384497cd8ca9d6b76a48e0dc0dbf1720245a9bf | ef29b3c8b5708825ca008a3938adb8fd |
| src/diffutils-2.8.7-1-src.zip | 1482028 | 622cdfe2dcf94d5f9fd05b9546395e624fe1b84ccb7ab473bbbe893f04423821 | a660b2abcad598c12ce112b042166d96 |
| src/less-394-src.zip | 373073 | 03098c71da92893e2526dbed98b62b641d16f40f872272659bed3ed6f52849c8 | a43a0f1cec48e381576d6e605631497a |
| src/which-2.20-src.zip | 228221 | 87ebfb51793647f4f24136c7bc7877c4aa025795e7e15496fdd33eaaac1d1224 | 616804ca7704c83138accbb40e865f7c |
| src/libiconv-1.9.2-1-src.zip | 4638975 | 06e31e8c7019fbaa0dd58aeaff97cdfe7238e67865b52de5f53083e2e04ed33f | e9014f9057c5cd4cafe06f996aad9f54 |
| src/libintl-0.14.4-src.zip | 257432 | e51f536e6aaffdfe11f2c48280c985c18cc252264258362325816aaa127cd4da | 647704e168786ea21db681269fd95be6 |
| src/pcre-7.0-src.zip | 1306504 | 04fd80bb9cbc005c3d3ef9a0d59b94821ffcb666dd698835c410a7f718507c15 | 956dcb4b1aafaf6bd9d54692df1144ef |
| src/regex-2.7-src.zip | 2291538 | 321000f891a7a89e6a610cb46c7a500152791e8653ec6228366c02a9293271f3 | 61df124f42aff117bb3cbbeafb663dc1 |
| src/openssl-0.9.8h-1-src.zip | 14375398 | 6c6bd581e64e1a0ff67ab5cd8ecc50cbbc9b3eecd01076209ad1e68aff7055dc | 7238e1e11ab2076e5ec13a23ba03c08e |

Source URLs: `https://downloads.sourceforge.net/project/gnuwin32/<pkg>/<release>/<pkg>-<release>-src.zip`
(e.g. https://downloads.sourceforge.net/project/gnuwin32/sed/4.2-1/sed-4.2-1-src.zip).
Caveats: the libiconv 1.9.2-1 source zip is the October 2004 GnuWin32 release, matching the DLL in
libiconv-1.9.2-1-bin.zip (same release). The openssl-0.9.8h-1-src.zip is dated 2008-08-22 while the bin zip
was re-uploaded 2008-12-04; GnuWin32 lists them as the same release and the page links this source.
Nothing in the binary zips comes from a library outside this list (checked via import tables).

## Security

Source: NVD API 2.0 with `virtualMatchString` per component CPE (2026-09-29). Counts are NVD CPE matches,
not individually confirmed against these builds unless noted.

- wget 1.11.4: 17 matches. Worst: CVE-2014-4877 (recursive FTP absolute path traversal, arbitrary file write, CVSS2 9.3); CVE-2016-4971 (HTTP-to-FTP redirect writes arbitrary file, 8.8); CVE-2024-38428 (userinfo semicolon URL mishandling, 9.1); CVE-2019-5953 (buffer overflow, 9.8); CVE-2009-3490 (NUL in certificate CN, MITM). Probably not applicable (features absent in 1.11.4, from memory, not verified): CVE-2026-58469 (metalink), CVE-2018-20483 (xattr), CVE-2017-13089/13090 (chunked transfer decoding).
- OpenSSL 0.9.8h: 85 matches, e.g. CVE-2009-3245 (bn_wexpand NULL, CVSS2 10.0), CVE-2009-3555 (TLS renegotiation, 9.8), CVE-2016-2108 (ASN.1 negative-zero, RCE, 9.8), CVE-2011-4109 (double free, 9.3). It also only speaks SSLv3/TLS 1.0, so wget HTTPS to most current servers will fail anyway.
- PCRE 7.0: 15 matches, e.g. CVE-2015-8391 (9.8), CVE-2015-5073 (9.1), CVE-2008-0674 (character-class buffer overflow, 7.5), CVE-2007-4768 (heap overflow, code execution).
- less 394: 1 (CVE-2014-9488, malformed UTF-8 out-of-bounds read, CVSS2 10.0).
- grep 2.5.4: 1 (CVE-2012-5667, integer overflow on huge lines, 4.4). gawk 3.1.6: 1 (CVE-2023-4156, heap OOB read, 4.4).
- sed 4.2, diffutils 2.8.7, which 2.20, libiconv 1.9.2, gettext 0.14.4: 0 CPE matches.
- regex2.dll (glibc 2.7 regex): not assessed; glibc CPE matches are dominated by non-regex issues.
Summary: about 120 NVD matches across components, most in OpenSSL; the practical risks are wget used against
malicious servers and HTTPS trust. A `Warning:` is in ENTRY.TXT.

## Install behaviour

- Installer type: plain zip (no setup program). Every zip uses the same GnuWin32 tree: `bin/`, `contrib/`,
  `man/`, `manifest/`, `share/`, plus `etc/` (wget), `lib/`, `include/`, `libexec/` in some. No top-level folder
  to strip. Listed with .NET ZipFile; no file path occurs in more than one zip, so order does not matter.
- Beacon: `unzip C:\GNUWIN32` (short path so it works in AUTOEXEC.BAT PATH; GnuWin32's own default is
  C:\Program Files\GnuWin32), then `path C:\GNUWIN32\BIN`. No shortcuts (command-line tools). Uninstall: `files`.
- No silent switch needed; nothing is registered in Add/Remove Programs (Add/Remove name: none).
- wget reads `etc\wgetrc`; where the GnuWin32 build looks for it was not verified. openssl.exe and the OpenSSL
  test programs are installed too (part of the unmodified zip).

## Verification notes

- Verified by opening/downloading: gnuwin32.sourceforge.net home and package pages, the 2010 Wayback copy of
  the sed page, SourceForge RSS listings and MD5s, all 24 zips (hashes; licenses, READMEs and manifests read
  from the zips), source file headers, PE import/export tables (parsed, never executed), NVD API.
- Not verified: running any tool on Windows 95/98/ME (no VM interaction); whether stock Windows 98 SE ships
  MSVCP60.DLL; applicability of individual CVEs; wget's wgetrc lookup path.
- Web search was not available in this session (budget exhausted), so nothing here comes from search snippets.
