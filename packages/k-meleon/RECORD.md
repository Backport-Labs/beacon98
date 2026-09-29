# K-Meleon 1.5.4 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: k-meleon
- Package: K-Meleon web browser (K-Meleon Team; core developer Dorian Boissonnade)
- Version: 1.5.4 (2010-03-05), Gecko 1.8.1.24, NSS 3.12.3.1
- License: GPL (K-Meleon; the project's SourceForge page says GPLv2) plus MPL 1.1 / NPL 1.1 for the Gecko engine; bundled chrome/extensions MPL 1.1/GPL 2.0/LGPL 2.1 tri-license
- Recommendation: official K-Meleon 1.5.4 en-US installer, listed as **external** (downloaded from SourceForge over plain HTTP). The project never published source for 1.5.4 (see "Matching source"), so we cannot meet the GPL source obligation if we host the binary ourselves.

## Windows 9x support evidence

All of these were verified by downloading the pages over http (kmeleonbrowser.org's HTTPS certificate does not match the host name).

- http://kmeleonbrowser.org/wiki/DownloadsArchive:
  "K-Meleon 1.5.4 is the last version to support Windows 98." and, under the 1.5.4 entry,
  "Note: Version 1.5.4 is the last version of K-Meleon to support Windows 9X systems."
  The 1.5.4 entry says: "Update to latest Mozilla code 1.8.1.24 with some bug fixes."
- http://kmeleonbrowser.org/download.php:
  "There is a patch to add TLS support to Version 1.54, the final version to officially support Windows 98, 98 SE, 95, and Me."
  and "Version 74 is the final version to run on Windows 2000 as well as even earlier operating systems via KernelEx."
- http://kmeleonbrowser.org/wiki/ReleaseNotes15 (1.5 release notes, System Requirements):
  "Windows 2000, Windows XP and Windows 2003 Server fully supported. Windows 95, 98, 98SE, ME, Windows NT 4.0 generally supported with updated Microsoft libraries."
- The installer itself has a separate 9x build (checked by listing and by decompressing the NSIS header, not by running it):
  it contains both `k-meleon.exe` (Unicode build, 125 W-API imports) and `k-meleonW9x.exe` (ANSI build, both version 1.5.4.0),
  and the installer script contains the step `k-meleonW9x.exe->k-meleon.exe`, reads `SOFTWARE\Microsoft\Windows NT\CurrentVersion` vs
  `SOFTWARE\Microsoft\Windows\CurrentVersion` `VersionNumber`, and writes `kmeleon.plugins.rebarmenu.load`/`bmpmenu.load` = false
  (the CVS log for the 1.x installer says "Disable bmpmenu and rebarmenu on W95/NT4"). So the "K-Meleon for Win9x" build is part of the
  normal official installer, not a separate download. MSVCR71.DLL and MSVCP71.DLL are bundled.
- Windows 95: http://kmeleonbrowser.org/wiki/InstallerForWindows98 says 95 needs COMCTL32.DLL version 5 (from IE 5/5.5) or the toolbars fail,
  and that K-Meleon does not run on a 386 (needs cmpxchg, i486+). Not tested here.
- Windows ME: named in all the statements above. Not tested here.

### Choices considered

| Build | Runs on stock 98 | Notes |
|---|---|---|
| **K-Meleon 1.5.4 official** (recommended) | yes | Last official 9x release. No TLS 1.1/1.2, so most HTTPS sites fail today. |
| K-Meleon 1.5.4 + roytam1 TLS 1.2 patch ("Installer for Windows 98" by rjjiii, https://github.com/rjjiii/K-MeleonForWindows98 releases v1.5.4.2, and https://sourceforge.net/projects/unofficial-installerforwin98/, KMforWin9x_Installer.exe 6,635,580 bytes, SF MD5 c267905066856f7cbb8f6a2341d3120e) | yes (per its page) | Community, not an official K-Meleon release; linked from the K-Meleon wiki. Replaces "most of GRE components" with a RetroZilla-based build plus NSS 3.21.4 (roytam1, forum thread http://kmeleonbrowser.org/forum/read.php?22,151512). Its repository's "SourceForCompiledBrowser" folders hold binaries, not source; no matching source for the patched Gecko/NSS was found. Not downloaded. Not suitable for hosting; could be considered later only as an external package after its sources are located. |
| K-Meleon 1.6.0 Beta2 (Gecko 1.9.1) | no | DownloadsArchive says 1.5.4 is the last 9x version; the beta needs the VS2005 runtime. |
| K-Meleon 74.0 (2014) | only with KernelEx | download.php: "Version 74 is the final version to run on Windows 2000 as well as even earlier operating systems via KernelEx." Not verified further. |

## Download

- Official file list: https://sourceforge.net/projects/kmeleon/files/k-meleon/1.5.4/ (linked from the DownloadsArchive page as prdownloads.sourceforge.net/kmeleon/K-Meleon1.5.4en-US.exe)
- URL used: https://downloads.sourceforge.net/project/kmeleon/k-meleon/1.5.4/K-Meleon1.5.4en-US.exe
- Plain HTTP (for `Availability: external`): `http://downloads.sourceforge.net/project/kmeleon/k-meleon/1.5.4/K-Meleon1.5.4en-US.exe`.
  Tested with `curl.exe -sS -I --http1.0`: 302 to `http://netactuate.dl.sourceforge.net/...K-Meleon1.5.4en-US.exe?viasf=1&...` (plain http mirror),
  which answers 200, Content-Length 6049917, application/octet-stream. The client must follow an HTTP redirect to a mirror; the mirror host varies.
- File: K-Meleon1.5.4en-US.exe, 6,049,917 bytes, 32-bit NSIS 2 installer (English)
- SHA-256: 79b58ef35dc54c21d1080aeab4eba813480ed0a037fa7d7d1b2644262b2ca458
- MD5: bb10a506379672905e93dd066b05e603; SHA-1: 61176b7e56e1da2d15f78243feb84978653184cf
- Published checksum: the project publishes none for 1.5.4 (only 1.6.0 Beta2 had .md5 files). SourceForge file RSS (https://sourceforge.net/projects/kmeleon/rss?path=/k-meleon/1.5.4) lists MD5 bb10a506379672905e93dd066b05e603, size 6049917: MATCH. The RSS gives MD5 only (no SHA-1). Generated by SourceForge, not signed by the authors.
- Authenticode: not checked as signed; no signature expected for 2010 builds (unknown).
- Alternatives in the same folder (not in the package folder):
  - K-Meleon1.5.4en-US.7z, 5,316,471 bytes, portable (no installer). SF MD5 996691e70c0980ae8420ab260daad6e6: MATCH (downloaded to a temp folder only, to inspect files). SHA-256 9b0cae9fe2097943cfa1a09c796634be477df8fae660124e0cbe26f3cbb31362. It contains k-meleonW9x.exe too, but on 9x the user would have to rename it by hand, so the installer is the better choice.
  - Installers for de-DE, es-ES, fr-FR, pl-PL, ru-RU and *_locale.7z language packs (MD5s in the SF RSS).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\k-meleon -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". The scan covered the installer, LICENSE.TXT and the src\ archives.

## License

- The installer's license page (extracted from the NSIS header, saved as LICENSE.TXT with a two-line note on top) begins:
  "K-Meleon is licensed under the GNU General Public License (GPL). The Gecko(tm) engine is subject to the Mozilla Public License (as shown below the GPL)."
  It then gives the full GPL version 2 text, the MPL 1.1 text and the NPL 1.1 amendments.
- K-Meleon's own source files (checked in the 1.5.0 source, K-MeleonBE1.5.7z): 35 of 62 .cpp files in src\ say "either version 2, or (at your option) any later version", so GPL-2.0-or-later.
- SourceForge project metadata (REST API https://sourceforge.net/rest/p/kmeleon): "GNU General Public License version 2.0 (GPLv2)". download.php: "Free, Open Source software released under the GNU General Public License".
- Bundled parts checked inside the jars: embed.jar/en-US.jar Mozilla files, Flashblock (flashblock/licence.txt) and Console2 (console2/license.txt) are MPL 1.1/GPL 2.0/LGPL 2.1; NewsFox (newsfox.jar) files carry the MPL 1.1 tri-license block; chrome/licence.txt: GPL 2+ or LGPL 2.1+.
  The 1.5 release notes say NewsFox, Flashblock and Console2 are "All Rights Reserved" and that the Phoenity skin is "included with permission of Lim Chee Aun"; the file headers above show the open licenses, and Phoenity is now "Dual-licensed under Creative Commons Attribution-Share Alike 3.0 and GNU Lesser General Public License" (https://github.com/cheeaun/phoenity-icons README). The Phoenity bitmaps in 1.5.4 carry no license file of their own.
- Redistributing the unmodified files is allowed by the GPL 2 and MPL 1.1, on conditions: include the license text, and (GPL s.3 / MPL s.3.6) accompany the binaries with the complete corresponding source or a written offer. GPL s.3(c) (passing on the author's offer) is only for non-commercial distribution and the installer contains no written offer, so a company hosting it must supply the source itself. That source does not exist for 1.5.4 (next section).
- Result: **do not host; list as `external`** (SourceForge still serves the file over plain HTTP). LICENSE.TXT is kept for the client to show.

## Matching source (not found; nearest archives downloaded)

The exact 1.5.4 source was never published:
- SourceForge files /k-meleon-src/ (RSS checked) has source only up to 1.5.0 (`K-MeleonBE1.5.7z`, 2008-08-16).
- The project's Mercurial repository (https://sourceforge.net/p/kmeleon/source/, converted from CVS) has tags kmeleon15 (1.5.0), kmeleon15a1/a2/b1, kmeleon_16b, kmeleon74, kmeleon75, kmeleon75_1, and no 1.5.1-1.5.4 tag or branch. The old CVS repository (snapshot https://sourceforge.net/code-snapshots/cvs/k/km/kmeleon.zip, 4,717,787 bytes, inspected in a temp folder) has the same tags.
- A forum answer to "Source code of K-meleon 1.5.4" (http://kmeleonbrowser.org/forum/read.php?1,120195, 2011) only points to /k-meleon-src/ and CVS.
- The default branch at the time of the 1.5.4 build (k-meleon.exe is dated 2010-02-04) already had version 1.6.0 in MfcEmbed.rc, so 1.5.4 was built from something that is not in the public repository as such.

Downloaded into src\ for reference (these are NOT the matching source and must not be offered as such):

| File | Size | SHA-256 | URL / notes |
|---|---|---|---|
| K-MeleonBE1.5.7z | 3,274,249 | edc5f741d856a71eafb4f7135a59c79adffd0344368aa28422fe8041f709807c | https://downloads.sourceforge.net/project/kmeleon/k-meleon-src/1.5.0/K-MeleonBE1.5.7z - official 1.5.0 source plus build environment (src\ tree and mozilla dist headers). SF MD5 85e87a3d6f67986e27eab924b2928152: MATCH. |
| kmeleon-source-97c3a27190109e699e89c19472f04a79a71ed68a.zip | 1,505,692 | deb460c91d066b2717bad0934b8e1056dd7150ef885fae6316db9449d4ea52ac | https://sourceforge.net/code-snapshots/hg/k/km/kmeleon/source/kmeleon-source-97c3a27190109e699e89c19472f04a79a71ed68a.zip - SourceForge-generated snapshot of the official repo at the last commit before the 1.5.4 exe date (2010-01-28, "Possible crash when using GetInfoAtClick"). Reports version 1.6.0. Our own pick of a commit, not a release. |
| seamonkey-1.1.19.source.tar.bz2 | 36,272,561 | 665e0998e7af516826b12d943206de9d9ed6d341503660b72251821fccf1932e | https://ftp.mozilla.org/pub/seamonkey/releases/1.1.19/seamonkey-1.1.19.source.tar.bz2 - Gecko source is separate from K-Meleon's. Its config/milestone.txt says 1.8.1.24 and NSS is 3.12.3.1, matching the shipped DLLs (their version resources name the product "SeaMonkey"). Mozilla MD5SUMS cd1680aab7b8732551e6ace97d0f7eb8: MATCH. But the shipped nspr4.dll reports 4.7.1 while this source has NSPR 4.7.6, and the DLLs are dated 2010-02-28, before SeaMonkey 1.1.19 was released (2010-03-16), so this is not proven to be the exact Gecko source either. |

Other bundled components whose sources are not in any of these: NewsFox 1.0.x (newsfox.jar), Flashblock, Console2 (in embed.jar), the Phoenity/Klassic skins, NSIS 2 and its InstallOptions plugin, and Microsoft's MSVCR71/MSVCP71 runtime DLLs (Microsoft redistributables, not open source).

If Backport Labs ever wants to host it: ask the K-Meleon developers (forum / kmeleon-dev list) for the 1.5.4 source tree, or rebuild from these sources and host our own build with its source.

## Security

Sources: NVD API 2.0 (keyword "K-Meleon", CPE `cpe:2.3:a:k-meleon_project:k-meleon`), Mozilla's "Known Vulnerabilities in SeaMonkey 1.1" (https://www.mozilla.org/en-US/security/known-vulnerabilities/seamonkey-1.1/), MFSA 2010-07 and MFSA 2009-59.

- NVD maps 0 CVEs to `k-meleon:1.5.4` exactly; the CPE virtual match gives 4 older CVEs (CVE-2005-4134, CVE-2006-1942, CVE-2006-4253, CVE-2009-0689).
- Gecko 1.8.1 received its last fixes in SeaMonkey 1.1.19 / Thunderbird 2.0.0.24 (MFSA 2010-07, 2010-03-16: CVE-2010-0161, CVE-2010-0163, CVE-2009-3075, CVE-2009-3072, CVE-2009-2463). Whether K-Meleon's 2010-02-28 Gecko build already had all of MFSA 2010-07 is unknown.
- Every Gecko security fix after March 2010 (hundreds of MFSAs, 2010-08 onward) was never evaluated or backported for 1.8.1. The exact count of applicable problems is therefore **unknown**; it is certainly large.

Known to apply (or very likely):
- CVE-2009-0689: dtoa heap overflow in string-to-number conversion, arbitrary code execution from JavaScript (CVSS2 6.8, MFSA 2009-59 "Critical"). MFSA 2009-59 lists only Firefox 3.0.15/3.5.4 as fixed, not SeaMonkey 1.1/Thunderbird 2; NVD lists K-Meleon up to 1.5.3. Very likely in 1.5.4 (not verified in code).
- CVE-2009-3555: TLS renegotiation man-in-the-middle (CVSS3 9.8). NVD: NSS up to 3.12.4; 1.5.4 ships NSS 3.12.3.1.
- CVE-2014-3566 (POODLE) and the lack of TLS 1.1/1.2: SSL 3.0/TLS 1.0 only. Most HTTPS sites no longer connect at all.
- CVE-2009-3008: address bar spoofing via window.open with a relative URI (CVSS2 4.3), reported against K-Meleon 1.5.3; whether 1.5.4 fixed it is unknown.

Summary: count unknown (at least 3 that clearly apply, plus every Gecko bug found after March 2010). Worst: CVE-2009-0689 (remote code execution from a web page) and CVE-2009-3555 (CVSS3 9.8). A web browser from 2010 is the highest-risk kind of package in the catalog; the Warning must say so.

## Install behaviour

Checked by listing the installer with 7-Zip and decompressing its NSIS header (never run).

- Installer type: NSIS 2 (7-Zip: "Type = Nsis, SubType = NSIS-2", LZMA solid), Modern UI with InstallOptions custom pages (bookmark support, shortcuts, "Multi-user Profiles", "K-Meleon Loader", "Set K-Meleon as your default browser").
- Silent install: `/S` (standard NSIS). Not documented by K-Meleon. Not verified: whether the "earlier install detected" and "K-Meleon or the Loader is currently running" message boxes are suppressed in silent mode, and which optional components (Loader, default-browser via `SetDefault.exe /S`) are selected by default.
- Default folder: `$PROGRAMFILES\K-Meleon\` (header strings `ProgramFilesDir`, `\K-Meleon\`), remembered in HKCU `Software\K-Meleon\General` `InstallDir`.
- Uninstaller: yes. `$INSTDIR\uninstall.exe`, registered at HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\K-Meleon` with DisplayName **`K-Meleon 1.5.4 en-US (remove only)`** (string in the header; the 1.5 release notes give the same pattern "K-Meleon 1.5.0 en-US (remove only)"), UninstallString, DisplayIcon, DisplayVersion, InstallLocation, NoModify, NoRepair, Publisher "K-Meleon Team".
- Side effects: `Software\Mozilla\K-Meleon` (GeckoVer, bin, Extensions), `Software\Clients\StartMenuInternet\k-meleon.exe` (for set-default), a Windows Media Player shim key, Start Menu/Desktop/Quick Launch shortcuts, optional Loader in Startup ("KMeleon Tray Control"). Profiles go under the application data folder unless "Multi-user Profiles" is unchecked.
- On 9x the installer renames k-meleonW9x.exe to k-meleon.exe (see above), which is why the installer is preferred over the .7z.
- Installed size: about 18,700 KB (NSIS listing: 373 files, 19,103,265 bytes).

## Verification notes

- Verified by opening or downloading: kmeleonbrowser.org DownloadsArchive, download.php, InstallerForWindows98, ReleaseNotes15, forum threads 22,151512 and 1,120195 (all over http); SourceForge RSS for /, /k-meleon/1.5.4, /k-meleon-src, /k-meleon-dev, /OldFiles; SF REST project info; SF hg tags, branches and commit log; the CVS snapshot; the installer and .7z (listed, NSIS header decompressed, text files, jars and version resources read; nothing executed); SeaMonkey 1.1.19 source (milestone.txt, nss.h, prinit.h); Mozilla SeaMonkey 1.1 known-vulnerabilities page; NVD records.
- From search snippets or fetch summaries only: MFSA 2010-07 and 2009-59 contents (via a page-summary tool), the Phoenity blog post; the rjjiii GitHub metadata came from the GitHub API.
- Not verified: running on 95/98/ME (no VM interaction); silent-install behaviour; Authenticode; whether 1.5.4 includes MFSA 2010-07 and fixes CVE-2009-3008; K-Meleon 74 with KernelEx.
