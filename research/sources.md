# Beacon 98 - candidate-list sources (besides the MSFN 98SE thread)

Researched 2026-09-29. Scope: where to find curated, machine-usable lists of software that runs on
Windows 95/98/ME, to build Beacon 98's catalog of software that is legal to redistribute
(open source, or freeware whose terms allow redistribution). The MSFN thread
"Last Versions of Software for Windows 98SE" is covered separately (see `candidates.md`, `msfn-list.csv`).
No software binaries were downloaded.

Verification: **[V]** = page or API opened and checked; **[S]** = search-result snippet only, not opened
(or the page refused to load).

## Headline findings

1. **No GitHub "awesome-win9x" list exists.** GitHub topic pages (`windows-98`, `windows-9x`, `win9x`,
   `windows-95`, `win98`) hold tools, themes and desktop recreations, not curated app lists. Nobody has
   built a structured JSON/YAML/CSV dataset of Win9x-compatible software. Beacon would be the first.
2. **No existing old-Windows package manager supports 9x.** pmfow stops at Windows 2000, while xp-apps
   and Npackd target XP or later. Their catalogs are only useful as hints for "last version before NT-only".
3. **Wikipedia comparison tables are not usable for this.** Every OS table sampled has one generic
   "Windows" column. Wikidata has a few hundred items tagged Windows 95/98/ME, but they are mostly
   commercial CD-ROM titles, and fewer than 10% have a license.
4. The best structured sources are **forum and hobbyist lists that already use a notation** (MSFN
   Win95 thread, KernelEx lists, Operating System Revival) plus **MDGx's Power Toys page**, which records
   the OS range and a license tag for each of about 270 entries. **NirSoft PAD XML files** are the best
   machine-readable per-author source. GitHub topic search is the channel for finding *new* 9x software.
5. **Nobody records licenses reliably.** Beacon has to verify redistribution rights for every package
   itself: SPDX IDs for open source, and quoted freeware terms for everything else.

---

## 1. GitHub lists and repos

### 1.1 GitHub topics: windows-98 / windows-9x / win9x / windows-95 / win98  [V]
- URLs: https://github.com/topics/windows-98, https://github.com/topics/windows-9x,
  https://github.com/topics/win9x, https://github.com/topics/windows-95, https://github.com/topics/win98
- Contents: repositories tagged by their authors. Most are web recreations, themes, sound packs and
  drivers (e.g. 1j01/98, JHRobotics/softgpu, patcher9x). Some are real new or maintained 9x software:
  Telegacy (Telegram client for old Windows), wol-sender (Win95+), NanoShell, Backport-Labs/searchlight98.
- Size (GitHub search API, 2026-09-29): windows-98 = 99, windows-95 = 113, win98 = 38, windows-9x = 31,
  win9x = 8 repos. There is overlap between tags, and most repos are not installable 9x apps.
- Win9x compatibility: implied by the tag only, so it has to be checked per repo.
- Licenses: **yes, via the API** (`license.spdx_id` on each repo).
- Format: GitHub REST search API (JSON), e.g. `https://api.github.com/search/repositories?q=topic:win9x`.
  The API rejects one long OR query over many topics (HTTP 422), so query one topic per call.
- Reuse: repo metadata is fine to use. Each project's own license governs its binaries.
- Last update: live.
- Usefulness: **Medium.** It is the only automated way to find newly written 9x software, and the SPDX
  license comes with it. The signal-to-noise ratio is low, so a person has to triage the results.

### 1.2 "awesome" lists  [V for the searches, S for the repos named]
- No awesome-win9x, awesome-retro-windows or similar list was found. General lists such as
  awesome-soft/awesome-windows, auctors/free-lunch and zriyansh/awesome-os target modern Windows and do not
  record OS versions. **Low.**

### 1.3 oerg866/win98-quickinstall  [S]
- https://github.com/oerg866/win98-quickinstall. This is an installer framework that bundles drivers
  and patches. Its REFERENCE.md may list bundled tools. It is not a software catalog. **Low.**

---

## 2. Package managers for old Windows

### 2.1 pmfow (Package Manager for Old Windows)  [V]
- URL: https://github.com/MasterJayanX/pmfow (wiki: https://github.com/MasterJayanX/pmfow/wiki/Software-List)
- Contents: one catalog file per OS in `32 bit/` and `64 bit/`: `win2000.dat`, `winxp.dat`,
  `winvista.dat`, `win7.dat`, `win8.dat`, `win10.dat`.
- Size: `win2000.dat` has 39 entries and `winxp.dat` has 78 (32-bit). The wiki Software List (version 62,
  2026-08-10) describes about 150 apps, each with an OS range.
- Win9x: **explicitly not supported** ("too old for wget to work reliably"). Still, `win2000.dat` is
  a good hint list for "oldest Win32 build" versions, and some of its URLs are 9x builds
  (e.g. `cpu-z_1.04-win9x.zip`, Firefox 12, Blender 2.42, Audacity from 2007).
- Licenses: **not recorded**.
- Format: INI-like `name=download-URL` lines. The version is embedded in the URL only.
- Data license: whole repo **GPL-3.0**. The data can be reused if Beacon's derived catalog is GPL-compatible,
  or if Beacon only uses it as a research hint and does not copy it wholesale.
- Last update: latest commit 2026-08-11.
- Usefulness: **Medium-low** (hint list for Win2000-era versions; each one still needs a 9x check).

### 2.2 xp-apps (nixxoq)  [V]
- URL: https://github.com/nixxoq/xp-apps. It targets Windows XP only, and its catalog is `upd.json`.
  The repo was **archived on 2025-07-09** and was incomplete. The license was not visible on the page.
  **Low.**

### 2.3 xpykg (abrik1)  [S]
- URL: https://github.com/abrik1/xpykg. It is a package manager for XP and ReactOS, with no 9x support.
  **Low.**

### 2.4 Npackd  [V]
- URLs: https://www.npackd.org/, format documentation at https://github.com/npackd/npackd/wiki/RepositoryFormat
- Contents: more than 1000 packages in an XML repository. Each package has a `<license>` reference, and
  OS compatibility is expressed as a dependency on `com.microsoft.Windows` with a version range
  (e.g. `[5.0, 6.1)`).
- Win9x: **none.** The documentation starts at Windows 2000 (5.00.2195), and in practice the packages are
  modern.
- Licenses: **yes**, as structured references.
- Data license: package **metadata is GPLv3** (the binaries and icons are not).
- Usefulness: **Low** for 9x content. **High as a design reference:** the license-ID plus
  Windows-version-range dependency model is exactly what Beacon's manifest needs.

---

## 3. Forum, wiki and hobbyist compatibility lists

### 3.1 MSFN: "Last Versions of Software for Windows 95" (a different thread from the 98SE one)  [V]
- URL: https://msfn.org/board/topic/176623-last-versions-of-software-for-windows-95/
- Contents: started 2017-04-09 by ppgrainbow, 4 pages. It uses a strict line notation:
  `STATUS - LICENSE - Name Version (yyyy-mm-dd) --- URL`. The status values are LAST, ONGD and ????.
  The license values are FREE, SHAR and $$$$.
  Example: `LAST - FREE - 7-zip 9.20 (2010-11-18) --- http://www.7-zip.org/a/7z920.exe`.
- Size: about 18 entries in the first post, plus about 20 more in replies.
- Win9x: **yes (Win95 specifically).** This makes it the best source for the 95 baseline.
- Licenses: **coarse only** (FREE / SHAR / $$$$). FREE does not tell you whether redistribution is allowed.
- Format: forum HTML, but the notation is regular and easy to parse.
- Data license: none stated. Facts (name, version, date) are not copyrightable; do not copy the prose.
- Last update: first-post edits around 2017.
- Usefulness: **High** (small but precise, and it covers Windows 95).

### 3.2 MSFN: "KernelEx Apps Compatibility List (New)"  [V]
- URL: https://msfn.org/board/topic/152471-kernelex-apps-compatibility-list-new/
- Contents: started 2011-07-19 by xrayer; the first post was last edited 2020-06-26; 39 pages.
  It has three sections: working apps (about 150), games (about 40) and not working. Example entry:
  `Adobe Acrobat Reader 7.0.9, KX 4.5, Win2k mode`.
- Win9x: **yes (98SE/ME with KernelEx)**. Entries record the KernelEx version and compatibility mode.
- Licenses: **no.**
- Format: forum HTML with semi-regular lines.
- Data license: none stated (facts only).
- Usefulness: **High** for a "KernelEx tier" of the catalog. Beacon needs a `requires: kernelex` flag
  and must keep these separate from native 9x packages.

### 3.3 Operating System Revival (retrosystemsrevival.blogspot.com)  [V]
- URLs:
  - "Latest Versions of Software Working on Windows 98/ME":
    https://retrosystemsrevival.blogspot.com/p/latest-versions-of-software-working-on_20.html
  - "List of Working Windows 98/ME KernelEx Applications":
    https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html
- Contents: the first page has about 150-180 titles in 40+ categories, with markers FV (final version),
  CS and US, plus $$$ / ~$ license hints. It is labelled "heavy WIP" and draws on MSFN and VOGONS.
  The KernelEx page has about 200-250 apps, each with the KernelEx version and mode
  (e.g. `VLC Player 2.0.5 (KernelEx 4.5.2019.24; Base Enhancements)`).
- Win9x: **yes (98/ME).**
- Licenses: coarse ($$$ vs free) on the first page, none on the KernelEx page.
- Format: blog HTML lists.
- Data license: "Copyright 2018 ... All Rights Reserved". **Use it only as a lead list.** Re-verify the
  facts and do not copy the text.
- Last update: no date shown.
- Usefulness: **High** (the broadest 98/ME list after MSFN 98SE, and it cross-checks the MSFN data).

### 3.4 MDGx "1000+ Free(ware) Windows 9x/NTx Power Toys" and sister pages  [V: toy.htm; S: others]
- URLs: https://www.mdgx.com/toy.htm (checked); also https://www.mdgx.com/web.htm (Software Essentials),
  https://www.mdgx.com/speed.htm and https://www.mdgx.com/drv.htm (snippets only; WebFetch gets HTTP 403,
  but a normal browser user agent works).
- Contents: hand-maintained since 1996 by MDGx (AXCEL216). toy.htm has **267 "Direct download" entries**.
  Each entry gives the name, version, the **exact OS range** and a **license tag in brackets**, e.g.
  `Q-Dir v4.42 32-bit + 64-bit Windows 98/NT4/2000/ME/XP/... [392 KB, freeware]`.
  Tag counts on toy.htm: freeware 192, free GPL 21, free 21, crippled freeware 11,
  free open source 8, donationware 6, freeware for personal use 5.
  The page also ends with a long list of other freeware-author sites, which gives more leads.
- Win9x: **yes, per entry.**
- Licenses: **yes, as a coarse tag.** "freeware for personal use" and "crippled freeware" are red flags.
- Format: large hand-written HTML (about 316 KB). It is regular enough to scrape with a regex
  (`name vX.Y ... Windows <os list> ... [size, tag]`).
- Data license: "Everything here at MDGx.com ... is FREEware"; third-party copyrights are reserved.
  It is not an open data license, but reusing the facts as research leads is reasonable. Credit MDGx.
- Last update: copyright "1996-2026", so it is still maintained.
- Usefulness: **High** (the only large list that records both the 9x OS range and a license per entry).

### 3.5 VOGONS threads  [V]
- "Software for Windows 98SE" (2016): https://www.vogons.org/viewtopic.php?p=525737&t=49858.
  The first post has about 25 categories plus about 20 "interesting" items, each with a version
  (e.g. Firefox 2.0.0.20, 7-Zip 9.22) and "last to support 98" notes. No licenses.
- "Essential Windows 98SE software and tweaks?" (2019, last post 2026-01-19):
  https://www.vogons.org/viewtopic.php?p=1303847. About 40 tools mentioned across posts
  (K-Meleon, RetroZilla, SpeedFan 4.51, CPU-Z, HWiNFO...). No consolidated list.
- "The 'perfect' Windows 98 SE" (2019-2022): https://www.vogons.org/viewtopic.php?t=70764. Mostly
  drivers and updates, about 8 items. **Low.**
- Also found in search only [S]: https://www.vogons.org/viewtopic.php?t=105909 ("Unique/Odd/Useful/Fun
  Windows 98 Era Software - Not Games") and https://www.vogons.org/viewtopic.php?t=29849.
- Data license: none (facts only).
- Usefulness: **Medium** (good for spotting what people actually use; needs manual extraction).

### 3.6 KernelEx official wiki  [S]
- URL: http://kernelex.sourceforge.net/wiki/Category:Compatible_applications (**HTTP 404 now**). Search
  snippets show one page per app (7-Zip, AbiWord, Battle for Wesnoth, Celestia, Firefox, OpenOffice.org,
  Opera...). It may survive in the Wayback Machine, which WebFetch could not reach.
- Usefulness: **Low-medium** (historical only; the MSFN and OS Revival lists cover the same ground).

### 3.7 Vintage2000.org wiki  [V]
- https://vintage2000.org/start. Guides for DOS, 9x and 2000, not a software catalog.
  Its content license is **CC BY-NC 4.0**. **Low.**

### 3.8 soundprogramming.net "Latest Software Versions for Windows 98"  [V]
- https://soundprogramming.net/software/latest-software-versions-for-windows-98/. About 20 titles in
  10 categories (Opera 9.64, Acrobat Reader 5.05, WinZip 10...), with informal license notes.
  Copyright Jason Champion. **Low** (small, and mostly commercial software).

### 3.9 OlderGeeks.com vintage categories  [V]
- https://www.oldergeeks.com/downloads/category.php?id=313. Its Windows 95 category has only 1 entry,
  and there are separate 98 and ME categories. **Low.**

---

## 4. Wikipedia and Wikidata

### 4.1 Wikipedia comparison articles  [V]
Checked (all 2026-09-29): Comparison of web browsers, file archivers, text editors,
video player software and email clients. **None has a Windows 9x column.** Each OS table has one
"Windows" column (plus DOS in some). "Windows 98" does not appear at all on the email-clients page.
List of freeware is a bullet list with no OS data.
The Windows 98 and Windows 9x articles have some prose on "last version supporting 98"
(e.g. Opera 9.64, Office XP, DirectX 9.0c Dec-2006). That is useful for spot checks only.
- Data license: CC BY-SA 4.0.
- Usefulness: **Low.** Wikipedia is still useful per product (infobox "Operating system" and release
  history in each app's own article) to confirm a license and the last 9x version.

### 4.2 Wikidata (SPARQL)  [V]
- Endpoint: https://query.wikidata.org/sparql. Items with `P306` (operating system) or `P400` (platform)
  equal to Windows 95 (Q83370), Windows 98 (Q483132), Windows Me (Q484892) or Windows 98 SE (Q107693921).
- Size: Win95 201, Win98 184, WinMe 115, 98SE 26 items. Only 14, 12 and 7 of the first three
  have a license (`P275`). A sample shows mostly commercial CD-ROM titles (Print Shop, Calendar Creator,
  Microsoft Money...), apparently imported from a library catalog.
- Data license: **CC0** (fully reusable).
- Usefulness: **Low** as a discovery source. **Medium** as a license and identifier cross-reference:
  map each Beacon package to its Wikidata QID to get the homepage, license and official site.

---

## 5. SourceForge and the Free Software Directory

### 5.1 SourceForge  [V]
- The **Allura REST API** works without authentication: `https://sourceforge.net/rest/p/<project>`
  returns JSON with `categories.os` and `categories.license` (full trove path, e.g.
  `License :: OSI-Approved Open Source :: GNU General Public License version 2.0 (GPLv2)`).
- **The OS categories are collapsed to plain "Windows" today.** KernelEx, ClamWin and Audacity all show
  just `Operating System :: Windows`. The old trove category "32-bit MS Windows (95/98)" still appears in
  search snippets (e.g. `/directory/antivirus/32-bit-ms-windows-95-98/`), but those URLs now return 404.
  **You cannot search SourceForge by Windows 95/98 any more.**
- What still helps: the license (reliable, SPDX-mappable), the file-release history
  (`/projects/<p>/files/`, RSS at `/projects/<p>/rss`) to find the release from about 2005-2010, and the
  project's mirror downloads.
- Historical OS trove data: the FLOSSmole project (https://sourceforge.net/projects/ossmole/files/,
  https://github.com/FLOSSmole) scraped SourceForge from 2004 to 2008. The folder `sfRawData` (2008) may
  include trove categories with the old 95/98 values. No license was stated on the files page, and this
  was not checked further. The University of Notre Dame's SourceForge Research Data Archive is similar
  (restricted access) [S].
- Usefulness: **Medium** (license and release-history verification for open-source candidates; not for
  discovery).

### 5.2 Free Software Directory (FSF)  [V via a browser user agent; WebFetch gets 403]
- https://directory.fsf.org/wiki/Category/Runs-on/Windows has **952 entries**. "Runs-on" has one value,
  "Windows", with no version. It is Semantic MediaWiki, so it can be queried with Special:Ask or the API.
  Content is GFDL 1.3+ (the page footer confirms "GNU Free Documentation License").
- Usefulness: **Low** (confirms "free software" status only; no 9x information).

---

## 6. Individual long-standing authors (examples)

### 6.1 NirSoft  [V]
- Pages still carry **per-tool system requirements that mention 9x**. NirCmd says "all versions ...
  Windows 9x/ME, NT, 2000...". CurrPorts says it works on 98/ME with reduced features.
- **PAD XML files** exist for every tool: https://www.nirsoft.net/pad/ (with `pads.zip`, a bulk
  download). For example, https://www.nirsoft.net/pad/cports.xml has `Program_Type=Freeware` and
  `Program_OS_Support=Win2000,...,Win98,...`. The PAD OS field is coarse (it lists Win98 even where
  support is partial), so confirm against the HTML page.
- License text on each page: "You are allowed to freely distribute this utility via floppy disk, CD-ROM,
  Internet, or in any other way, as long as you don't charge anything for this ... you must include all
  files in the distribution package, without any modification!" That is **compatible with Beacon if
  Beacon is free and redistributes the original ZIP unchanged.**
- Old versions are not officially listed. The current builds of many tools still run on 9x.
- Usefulness: **High for this author.** It also shows a general method: **PAD files** (the ASP format since
  1998, with `Program_OS_Support`, `Program_Type`, `Distribution_Permissions`, `EULA`) are the standard
  machine-readable metadata of the 1998-2012 freeware scene. Many old freeware authors published them,
  so harvesting PAD files (live, or from Wayback) is a strong way to collect OS-and-license data.
  No surviving bulk PAD repository dump was found.

### 6.2 Sysinternals  [V, license only]
- The license terms (https://learn.microsoft.com/en-us/sysinternals/license-terms) forbid publishing "the
  software for others to copy", and old 9x builds are no longer hosted.
  **Not redistributable. Exclude it.**

### 6.3 Other examples worth scripting later  [S / general knowledge, not verified today]
- Mozilla FTP archive (https://ftp.mozilla.org/pub/): every historical Firefox, Thunderbird and SeaMonkey
  build (MPL). The MSFN Win95 thread links it.
- 7-Zip old versions (https://www.7-zip.org/a/, e.g. 7z920.exe, LGPL). The MSFN Win95 thread links it.
- K-Meleon wiki "InstallerForWindows98": http://kmeleonbrowser.org/wiki/InstallerForWindows98 [S].

---

## 7. Shareware and freeware CD collections (archive.org and mirrors)

### 7.1 Simtel / CICA / WinSite Walnut Creek CDs on archive.org  [V]
- Search API: `https://archive.org/advancedsearch.php?q=...&output=json` (28 relevant items for
  simtel/cica/winsite/walnut creek plus win95). Examples:
  - Simtel for Windows, June 1996: https://archive.org/details/simwin0696. A 419 MB ZIP with 1,855 files,
    about 1000 programs. It contains index files `00global.txt`, `00_index.txt`, `00_index.htm` and
    `win95/00_info/`. There is **no license field**.
  - CICA Aug 1997 (Win95 + 3.1): https://archive.org/details/cica-1-aug-97 (2 ISOs, 1.2 GB). The uploader set
    "Public Domain Mark", but **that label is not reliable** for the contents.
  - WinSite CD-ROM March 1996: https://archive.org/details/winsite0396. Browsable mirror at
    http://winsite.retropc.se/winsite-mar96-4/win95/index.html [V]. Entry format:
    `3dmaze12.zip  1029KB 11/27/95 Generate and solve mazes in 3D`, 30+ categories, **no license indicator**.
  - Simtel.Net win95 index mirror: http://www.lanet.lv/simtel.net/win95/ (the connection was refused
    today) [S].
- Win9x: **yes (a win95/ directory)**, though many files are 16-bit Win 3.x.
- Licenses: **no.** These archives are mostly **shareware** (redistributable only as unregistered trials,
  often with "no charge" terms). Beacon's freeware/OSS rule would reject most of them.
- Usefulness: **Low-medium.** It is a deep pool for period freeware (e.g. "GNU chess 3.21 for Win32"),
  but every item needs manual license review. Use it later for a "classic 1995-97 freeware" collection.

### 7.2 Other archive.org collections  [V]
- "Windows98Freeware" (https://archive.org/details/Windows98Freeware): 29 files (Opera 9.64, Firefox 2,
  7-Zip, IrfanView, Notepad++, VLC, Python 2.5...) uploaded 2019. It is a useful checklist of names. It is
  **not** a source of binaries for Beacon; get them from upstream.
- "Freeware - DOS ... 577GB FTP Archive" (https://archive.org/details/000-freeware-dls-catg-2007-22-440-gb)
  [S]: a Garbo mirror and more. Too large and unsorted. **Low.**
- Hobbes (e.g. `hobbes-0497`) is **OS/2**, so it is not relevant.

---

## 8. Summary table

| # | Source | Entries | 9x compat recorded | License recorded | Format | Data license | Last update | Use |
|---|---|---|---|---|---|---|---|---|
| 1 | MDGx toy.htm (+ sister pages) | ~267 (toy.htm) | Yes, exact OS range per entry | Yes, coarse tag | HTML (regular) | "FREEware", facts OK | 2026 | **High** |
| 2 | Operating System Revival lists | ~150-180 + ~200-250 | Yes (98/ME, KernelEx) | Coarse ($$$) / none | HTML | All rights reserved (leads only) | undated WIP | **High** |
| 3 | MSFN Win95 last-versions thread | ~40 | Yes (95) | FREE/SHAR/$$$$ | HTML, strict notation | none (facts) | 2017 | **High** |
| 4 | MSFN KernelEx compat list | ~150 apps + ~40 games | Yes (KernelEx ver/mode) | No | HTML | none (facts) | 2020-06 | **High** (KernelEx tier) |
| 5 | NirSoft pages + PAD XML | 200+ tools | Yes (text + PAD) | Yes (freeware, redistribution terms) | XML | author terms | live | **High** (per author) |
| 6 | GitHub topics via API | ~290 repos (overlapping) | Implied by tag | Yes (SPDX) | JSON API | per repo | live | Medium |
| 7 | SourceForge REST API | n/a | No (OS collapsed to "Windows") | Yes (trove) | JSON API | SF ToS | live | Medium (verification) |
| 8 | VOGONS threads | ~25-60 per thread | Yes (informal) | No | HTML | none | 2016-2026 | Medium |
| 9 | pmfow win2000.dat / Software List | 39 / ~150 | No (2000+) | No | name=URL | GPL-3.0 | 2026-08 | Medium-low |
| 10 | Wikidata SPARQL | ~500 items | Yes (P306/P400) | Rarely | JSON/RDF | CC0 | live | Low (cross-ref) |
| 11 | Simtel/CICA/WinSite CDs | ~1000s | Yes (win95 dir) | No | index TXT/HTML | unclear | 1996-97 | Low-medium |
| 12 | Npackd | 1000+ | No (2000+) | Yes | XML | GPLv3 | live | Low (design model) |
| 13 | Free Software Directory | 952 (Windows) | No | Yes (free only) | SMW | GFDL | live | Low |
| 14 | Wikipedia comparison tables | 30-60 rows each | No | Partly | wikitable | CC BY-SA | live | Low |
| 15 | xp-apps, xpykg, KernelEx wiki, Vintage2000, soundprogramming, OlderGeeks | small | No / partial | No | - | various | - | Low |

---

## 9. Ranked recommendation: sources to combine with the MSFN 98SE thread

1. **MDGx Power Toys and Software Essentials pages** (mdgx.com/toy.htm, web.htm). These are the only
   large lists with both an explicit per-entry OS range (95/98/ME) and a license tag. Scrape the
   `[size, tag]` pattern, keep entries tagged freeware / free GPL / free open source, and drop
   "personal use" and "crippled".
2. **Operating System Revival "Latest Versions ... 98/ME"** plus its KernelEx list. This is the broadest
   98/ME list, with FV (final version) markers. Use it as leads only because of its all-rights-reserved
   copyright.
3. **MSFN "Last Versions of Software for Windows 95"**. Its strict `STATUS - LICENSE - Name Ver (date) --- URL`
   notation makes it trivial to parse, and it sets the Win95 floor, which the 98SE thread does not.
4. **NirSoft PAD XML (and PAD files from other authors in general)**. This is machine-readable
   OS-and-license metadata straight from the author. NirSoft's terms explicitly allow free redistribution.
5. **MSFN KernelEx Apps Compatibility List** as a separate, clearly labelled tier (`requires: KernelEx 4.5.x`,
   plus the mode). Add **GitHub topic search** as a recurring discovery feed for new 9x software, with SPDX
   licenses included.

For verification (not discovery), use the SourceForge REST API (license and release history), Wikidata
(QID, license, homepage) and the upstream archives (ftp.mozilla.org, 7-zip.org/a/).

## 10. Suggested method to build and maintain the candidate list

1. **One canonical candidate file** in the repo, e.g. `catalog/candidates.csv` (or YAML per package),
   with these columns:
   `id, name, version, min_os (95|98|98SE|ME), max_os, requires (kernelex|ie5|dcom95|msvcrt...),
   license_spdx_or_terms, redistribution (yes|no|unknown), license_evidence_url, upstream_download_url,
   sha256, sources (msfn98|msfn95|mdgx|osr|kxmsfn|vogons|github|pad), status (lead|verified|rejected|packaged),
   notes, verified_by, verified_on`.
2. **Importers, one small script per source**, that write "lead" rows with a `sources` tag and
   never overwrite verified rows. Regex scrapers for the MSFN 95/98 notation and MDGx; a PAD XML parser;
   a GitHub topic API query; manual entry for VOGONS and OS Revival (their copyright rules out scraping
   the prose anyway). Deduplicate on normalized name, and keep the highest version that any source
   marks as 9x-compatible.
3. **License gate** (a human signs off on each row):
   - Open source: find the SPDX ID from the SourceForge/GitHub API or the upstream LICENSE file, and check
     that the source code is available for the exact version (GPL obligations).
   - Freeware: quote the redistribution clause from the readme, EULA or website into
     `license_evidence_url` and notes. Reject "personal use only", "may not be redistributed", and
     trial/shareware/crippleware. Note "no charge" and "unmodified package" conditions (NirSoft style):
     Beacon must stay free and ship the original archive byte-identical.
   - Unknown: stays `redistribution=unknown` and is never packaged.
4. **Compatibility gate**: install and run on the reference VM (E:\Win98SE, 98SE; add clean 95 OSR2 and
   ME VMs later) and record the result with `verified_on`. Where they are known, record prerequisites
   (IE version, MSVCRT, Unicode layer, KernelEx).
5. **Fetch from upstream only.** Archive the exact upstream file to Beacon's own mirror with a SHA-256,
   and keep the original URL plus a Wayback URL as provenance. Never take binaries from abandonware or
   aggregator sites.
6. **Maintenance**: a quarterly job re-runs the importers and diffs against the file. New leads open an
   issue. Also watch the MSFN 95/98SE threads, the VOGONS essentials thread and the GitHub topics.
   Accept community submissions through a PR template that requires `license_evidence_url` and a test
   report. Credit all sources in a CREDITS file (MSFN posters, MDGx, Operating System Revival).
7. **Data licensing for Beacon's own catalog**: publish Beacon's catalog metadata under CC0 or CC BY 4.0,
   built from facts that were re-verified independently rather than copied prose. Do not copy
   GPL-3.0 pmfow data wholesale into a CC0 catalog; use it as hints only.
