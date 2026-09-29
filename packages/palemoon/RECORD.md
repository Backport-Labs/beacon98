# Pale Moon 3.6.26 - Beacon 98 verification record

- Date checked: 2026-09-29
- Package: Pale Moon (Moonchild Productions, M.C. Straver)
- Version requested: 3.6.26 ("Legacy" 3.6.x branch, Gecko 1.9.2 / Firefox 3.6 code base)
- License: source under the Mozilla licenses; official binaries under Moonchild's proprietary "Redistribution license" (see License)
- Result: STOPPED at step 5. The Pale Moon binary redistribution license does not let Backport Labs host the official builds in Beacon 98 without an individual agreement. The publisher no longer offers any 3.6.x build, so "external" is not possible either. Recommendation: do not list Pale Moon. Nothing was downloaded into this folder.

## Windows 9x support evidence

- No Pale Moon build ever ran on stock Windows 95/98/ME. The official requirement statement from the 3.x era, as quoted in a Seven Forums thread of 2010-04-15 (opened; it is a quote posted by a forum member, "Corrine", not the Pale Moon site itself):
  "Windows 2000/XP/2003/Vista/Seven, 32-bit or 64-bit (64-bit O.S.es are not natively supported, but the browser will run fine on them) A 7th generation or later processor with SSE2 support like a Pentium IV or Athlon 64 or later". The same thread says "Standard Pale Moon will NOT run on Athlon XP processors".
  URL: https://www.sevenforums.com/threads/pale-moon-browser.78606/
- https://www.palemoon.org/history.shtml (opened): the project was "releasing the highly optimized browser to the public from Oct 4th, 2009 onwards", starting from "Firefox 3.5.2". It also says: "a second build version was created of Pale Moon, to cater specifically to the capabilities of Athlon XP and Athlon MP processors". So the earliest Pale Moon was already Firefox 3.5-based. Firefox 3.5 and 3.6 need Windows 2000 or later (from memory of Mozilla's requirements; Mozilla's 3.6 requirements page now returns 404, so this was not verified).
- The same history page on the 3.6.x branch: "the 3.6.x (Legacy) branch continued to see patches for bugfixes, security issues and some performance improvements, including continued support beyond Mozilla's EoL (End of Life) date for the 3.x branch ... the legacy branch was discontinued in the summer of 2012."
- The current system requirements page (https://www.palemoon.org/systemrequirements.shtml, opened) mentions nothing about 9x or 3.6.
- KernelEx: the community list "List of Working Windows 98/ME KernelEx Applications" (https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html, opened) lists "Pale Moon 3.6.26" in its Web Browsers section, with no notes on mode or settings. A search snippet says the list is for KernelEx 4.5.2; not seen on the page itself. A 2020 YouTube video "Palemoon 3.6 on Windows 98 SE with Kernelex" exists (search result only; per the snippet it used the Windows 2000 SP4 compatibility mode; not watched). The Pale Moon forum thread "Windows 98/ME support" (https://forum.palemoon.org/viewtopic.php?t=15821) could not be read: the forum is behind an Anubis bot check, and web.archive.org could not be reached from this computer. The MSFN pages were not found to say anything about 3.6.26 specifically.
- Is 3.6.26 the right choice? The last 3.6.x build is 3.6.32 (search snippets from Wikipedia/soft112/the forum EoL thread "End-of-Life announcement for Pale Moon "Legacy"": "The latest, final version is 3.6.32"; the thread itself was not readable). Nobody was found reporting whether 3.6.27 to 3.6.32 work under KernelEx; 3.6.26 is simply the build the community list tested. If Pale Moon were ever listed, 3.6.32 would be worth testing first. Both need KernelEx (Windows 2000 API) and an SSE2 processor (Pentium 4/Athlon 64) for the standard build; an Athlon XP (SSE-only) build existed for 3.x but its 3.6.26/3.6.32 availability is unknown.
- Windows 95: KernelEx does not support 95, so no. Windows ME: same status as 98 (KernelEx supports ME); not tested.
- Later builds on 9x: the same community list has "Roytam1's Palemoon 27 (No SSE2 build) - Reported to work, but is super slow." That is an unofficial third-party build (roytam1), not Moonchild's, and also needs KernelEx.

## Download

- The official archive https://archive.palemoon.org/palemoon/ (opened) only holds 25.x to 35.x. No 3.x folder (https://archive.palemoon.org/palemoon/3.x/ gives 404). https://archive.palemoon.org/contrib/ holds only contributed builds (Mercury, dimag0g, fedor, ketmar, walterdnes, docsets), none of them 3.6.x.
- https://archive.palemoon.org/source/ (opened) holds source for 29.4.x and some Basilisk snapshots only. Its ReadMe: "We offer source code snapshots for the current and a limited number of past versions here."
- The Wayback Machine CDX (query for palemoon.org URLs containing 3.6.2x) listed only PGP signature files on palemoon.org itself: pgp/Palemoon-Portable-3.6.23.exe.sig (captured 2011-09-26), -3.6.25 (2011-10-07), -3.6.27 (2011-11-21), -3.6.28 (2012-01-08), pgp/palemoon-3.6.29-installer.exe.sig and pgp/palemoon-3.6.29.zip.sig (2012-02-21). So palemoon.org once hosted 3.6.x installers and zips with PGP signatures, 3.6.26 dates from about October-November 2011, and the 3.6.x numbering ran ahead of Firefox's own 3.6.x numbers. No 3.6.26 file was captured under that query. web.archive.org then stopped answering from this computer, so no capture of a 3.6.26 installer was found.
- Result: no official download of 3.6.26 exists today. Copies on download portals (soft112, software.informer, uptodown, filehorse) are third-party and were not downloaded.
- File, size, SHA-256: none (nothing downloaded). Published checksum: unknown (PGP .sig files existed in 2011).

## Windows Defender

Not run: the folder holds no downloaded files, only this record and ENTRY.TXT.

## License

- Source code: https://www.palemoon.org/legal.shtml (opened): "Our source code is for the most part covered by the Mozilla Public License v2.0". That describes the current code. 3.6.26 was built from Firefox 3.6 code, which was under the MPL 1.1 / GPL 2.0 / LGPL 2.1 tri-license (from general knowledge of Mozilla 1.9.2 code; not verified against a 3.6.26 source tree, which could not be found). https://www.palemoon.org/licensing.shtml (linked from the archive server) returns "404 - Page not found".
- Binaries: legal.shtml: "Executable software binaries of core products released by Moonchild Productions, such as Pale Moon, are made available under the terms of the binary redistribution license." Also: "we strictly enforce our trademark rights ... Our trademarks include, among others, the names Pale Moon(R) ...".
- The redistribution license, https://www.palemoon.org/redist.shtml (opened, "Last updated: 19 May 2026"), quotes:
  - Intro: "redistribution of the Pale Moon binaries (executable form) is limited by certain conditions under a proprietary license by Moonchild Productions, as permitted under 3.2b of the MPL v2.0." and "In case of any doubt, always err on the side of caution and verify with the project owner before publicly distributing Pale Moon or including it in a distribution framework."
  - Point 1: "There is NO CHARGE for the download or distribution of the browser package." (Beacon would meet this.)
  - Point 3: "The binaries and/or archives are completely UNALTERED." (Beacon would meet this.)
  - Point 4: "The browser can be obtained without the use of third-party software not officially endorsed, including but not limited to: download managers, stub installers, wrappers, proprietary clients or proprietary protocols. This includes any offering of such unendorsed downloading software or methods, regardless of offering "direct" downloads or allowed methods alongside the unendorsed ones. An exception to this is system-supplied package managers for various Linux distributions."
  - Point 5: "The binaries are not supplied or built as an integral part of a commercial/non-commercial software package/larger works ("package"). If you wish to do this, you must contact us beforehand to obtain permission and discuss terms. Inclusion in a package will be subject to an individual agreement (either extemporaneous or legalized) which may or may not involve compensation."
  - Point 6: the same for "an integral part of a commercial/non-commercial website/web service/on-line venue/etc. ("service")".
  - Points 7 and 8 are the only exceptions: educational use, and non-commercial UNIX-like operating systems (e.g. Linux). Neither applies to Beacon 98.
  - Point 14: "We reserve the right to withdraw permission ... at any time."
  - Point 15: "At all times, the latest version of this redistribution license will prevail in case of a conflict of terms of the latest version with any previously existing versions of this license." So the current license governs 3.6.26 binaries too, whatever license text shipped with them in 2012.
- Conclusion: Beacon 98 is a package manager with its own download client and a catalog of packages, so it is an unendorsed download client (point 4) and a "package"/distribution framework (point 5). Hosting the unmodified official builds is not allowed without an individual agreement from Moonchild Productions (legal{at}palemoon.org, per the page). The only freely redistributable form is an unofficially branded build ("New Moon", point 13), which does not exist for 3.6.x.
- LICENSE.TXT not saved and no source downloaded, because work stopped here. No 3.6.26 source archive was found on any official server.

## External availability

- The publisher's servers answer plain HTTP: `curl.exe -sS -I --http1.0` gave "HTTP/1.1 200 OK" (nginx) for http://archive.palemoon.org/palemoon/, http://archive.palemoon.org/palemoon/25.x/25.1.0/ and http://www.palemoon.org/archived.shtml.
- But they no longer carry 3.6.26 (or any 3.x), so there is no publisher URL to point to.
- Even for versions that are there, the publisher forbids linking: archived.shtml says "Please only download the version you personally need and do not hotlink. If you want to point people to archived versions of Pale Moon, always link to this page, not to the links below directly." The archive server's index page says: "Please do not hotlink or redirect users to this server for downloads of Pale Moon or other products hosted here". Point 4 of the redistribution license also names "download managers" and "proprietary clients" as unendorsed ways of obtaining the browser.
- Result: not suitable as "external" either. Under FORMAT.md ("Software that neither we nor its publisher distribute is not listed") Pale Moon should not be in the catalog, unless Backport Labs gets written permission from Moonchild Productions and a 3.6.x build that it may distribute.

## Security

Not researched in detail because work stopped. 3.6.26 is a Gecko 1.9.2 (Firefox 3.6) browser from about 2012, and the branch ended in summer 2012 (history.shtml). It carries every Firefox security bug fixed after that date; the number is unknown but certainly in the hundreds. No CVE count was made.

## Install behaviour

Not checked (no installer obtained). From general knowledge, Pale Moon 3.x used the Mozilla installer (NSIS-based, `-ms` silent switch, like RetroZilla in the catalog); not verified. Add/Remove Programs name: unknown.

## Verification notes

- Opened: palemoon.org redist.shtml, legal.shtml, archived.shtml, history.shtml, releasenotes-archived.shtml (it starts at 4.0 and has no 3.6.x notes), systemrequirements.shtml; archive.palemoon.org index, /palemoon/, /palemoon/25.x/, /source/ and its ReadMe, /contrib/ and subfolders; the retrosystemsrevival KernelEx list; the Seven Forums thread.
- Search snippets only: the 3.6.32 "final version" statement, the KernelEx 4.5.2 context of the list, the YouTube video.
- Not reachable: forum.palemoon.org (Anubis bot check), web.archive.org (connection refused after one CDX answer), Mozilla's Firefox 3.6 requirements page (404).
- Not verified: that 3.6.26 or 3.6.32 actually run under KernelEx (no VM interaction), which KernelEx compatibility mode is needed, 3.6.26's release date, its bundled license text, its installer type.
