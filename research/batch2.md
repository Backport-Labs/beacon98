# Beacon 98 - batch 2 proposal

Prepared 2026-09-29. Source list: `candidates.csv` (1,418 leads, not modified), plus well-known titles missing from it.
Skipped: everything already in the catalog or being verified (Searchlight 98, 7-Zip, RetroZilla, VLC, PuTTY, Vim, Info-ZIP, ScummVM, Beneath a Steel Sky, Flight of the Amazon Queen, Python 2.5.4, KernelEx, Pale Moon, SeaMonkey, K-Meleon, Firefox, Thunderbird, FileZilla, Notepad++, Notepad2, Metapad, AbiWord, OpenOffice.org, SumatraPDF, MPC, ffdshow, AC3Filter, VirtualDub, Audacity, GIMP, ClamWin, Eraser, Dependency Walker, MyUninstaller, DOSBox, InfraRecorder).

No binaries were downloaded. Pages were opened on 2026-09-29.

**How to read "confidence"**
- **High**: I opened a page that confirms both the license and the 98-capable version.
- **Medium**: I confirmed the license on a page. The 98 version comes from candidates.csv or from memory.
- **Low**: I confirmed the license, but the 98 version is a guess. It has to be tested in the VM before it goes into the catalog.

Every entry still needs the normal VM test. For GPL packages, keep a matching source archive next to the binary.

A note on the csv: every row's `sources` value is a single tag, and `homepage`/`download` hold the literal text `System.Object[]`, which looks like an export bug. Source count was therefore judged from the `versions` column.

## Stock Windows 98 (34)

| id | name | version | KernelEx | category | license | evidence URL | why useful | confidence |
|---|---|---|---|---|---|---|---|---|
| hxd | HxD | 1.7.7.0 | no | utilities | freeware, redistribution allowed if free and unmodified (bundling with *commercial* products needs permission) | https://mh-nexus.de/en/hxd/ ; https://mh-nexus.de/en/hxd/license.php | Fast hex/disk/RAM editor; the page explicitly lists 95/98/ME for 1.7.7.0 | High |
| winmerge | WinMerge | 2.12.4 | no | utilities | GPL-2.0 | https://winmerge.org/downloads/ ; https://github.com/WinMerge/winmerge | Visual diff/merge for files and folders; the page says 2.12.4 is the last with 95/98/ME runtimes | High |
| regshot | Regshot | 1.8.2 (ANSI build, from memory) | no | system tools | LGPL-2.0 | https://sourceforge.net/projects/regshot/ | Before/after registry+file snapshot, the key tool for seeing what an installer did | Medium |
| nircmd | NirCmd | 2.87 | no | utilities | NirSoft freeware, may be distributed free and unmodified | https://www.nirsoft.net/utils/nircmd.html | Command-line Swiss army knife for scripts; the page lists 9x/ME | High (license), Medium (latest build on 98) |
| shellexview | ShellExView | 2.01 | no | system tools | NirSoft freeware (same terms) | https://www.nirsoft.net/utils/shexview.html | Disables broken shell extensions that crash Explorer; the page says "starting from Windows 98" | High |
| iconsextract | IconsExtract | 1.47 | no | graphics | NirSoft freeware (same terms, readme must be included) | https://www.nirsoft.net/utils/iconsext.html | Extracts icons and cursors from EXE/DLL; the page lists 95/98/ME | High |
| volumouse | Volumouse | 2.21 | no | multimedia | NirSoft freeware (same terms) | https://www.nirsoft.net/utils/volumouse.html | Wheel-controlled volume; the page lists 98/ME | Medium (2.21 is a 2026 build, so test it) |
| hashmyfiles | HashMyFiles (non-Unicode) | 2.51 non-Unicode build | no | utilities | NirSoft freeware (same terms) | https://www.nirsoft.net/utils/hash_my_files.html | MD5/SHA hashes for verifying downloads; the page offers a "Non-Unicode Version (For Windows 98)" | High |
| autoit | AutoIt v3 | 3.2.12.1 (last 9x build, from memory and csv osr-final) | no | development | AutoIt EULA: freeware, may "reproduce and distribute an unlimited number of copies" with notices and EULA | https://www.autoitscript.com/autoit3/docs/license.htm | GUI automation and scripting for unattended setups | Medium |
| testdisk | TestDisk & PhotoRec | 7.1 (DOS build, runs in a 9x DOS box) | no | system tools | GPL-2.0-or-later | https://www.cgsecurity.org/wiki/TestDisk ; https://www.cgsecurity.org/wiki/TestDisk_Download | Recovers lost partitions and deleted files; the page lists "DOS (real or Windows 9x DOS-box)" and DOS/9x downloads for 7.0/7.1 | High |
| gnuwin32-core | GnuWin32 core tools (grep, sed, gawk, diffutils, wget, less) | pre-2010 package builds | no | utilities | GPL / various OSI | https://gnuwin32.sourceforge.net/ | Unix text tools for batch files; the site says 9x patches were kept up to 2010 | Medium (test each package) |
| tightvnc | TightVNC | 1.3.10 | no | internet | GPL-2.0 | https://www.tightvnc.com/download-old.php | Remote desktop to or from the 98 box; the page says 1.3.10 "supports ... starting at Windows 95" | High |
| winscp | WinSCP | 5.0.6 (5.0.7 dropped 95/98/ME) | no | internet | GPL-3.0 (icon set has a separate license that restricts redistribution; see note) | https://winscp.net/eng/docs/incompatible_changes ; https://winscp.net/eng/docs/license | SFTP/SCP file transfer to modern servers | Medium |
| winhttrack | WinHTTrack | 3.33 | no | internet | GPL | https://www.httrack.com/page/2/en/index.html | Mirrors websites for offline browsing; the site gives 3.33 as the build for systems older than Win2000 | High |
| privoxy | Privoxy | 3.0.x (exact last 9x build unknown; start testing at 3.0.6) | no | internet | GPL-2.0-or-later | https://www.privoxy.org/ ; https://sourceforge.net/projects/ijbswa/files/Win32/ | Local filtering proxy that strips ads and heavy scripts for old browsers | Low |
| miranda-im | Miranda IM (ANSI) | 0.7.x ANSI (0.7.14 to 0.7.17 per secondary sources) | no | internet | GPL-2.0 | https://sourceforge.net/projects/miranda/ | Lightweight multi-protocol IM (IRC and XMPP still usable). The old miranda-im.org domain is now unrelated spam | Medium |
| apache13 | Apache HTTP Server | 1.3.41 | no | development | Apache License 1.1 (from memory) | https://archive.apache.org/dist/httpd/binaries/win32/ | Local web server for LAN or dev; 2.0 needed a 9x APR patch, so 1.3 is the safe choice | Medium |
| php52 | PHP | 5.2.17 (5.3.0 dropped 98/ME/NT) | no | development | PHP License 3.01 (from memory) | https://wiki.php.net/internals/windows/releasenotes | Scripting and CGI with Apache; php.net says 5.3 dropped 98/ME | Medium |
| cdex | CDex | 1.51 | no | multimedia | GPL (current site shows GPLv3; 1.51 was GPL-2, from memory) | https://cdex.mu/ | CD ripper to WAV/MP3/Ogg. Avoid the later 1.7x builds that came with adware installers | Medium |
| lame | LAME MP3 encoder | 3.99.5 (RareWares VC6/ICL build) | no | multimedia | LGPL (MP3 patents expired 2017) | https://lame.sourceforge.io/license.txt ; https://www.rarewares.org/mp3-lame-bundle.php | The reference MP3 encoder used by CDex and Audacity | Medium (98 run not stated) |
| vsfilter | DirectVobSub / VSFilter | 2.39 | no | multimedia | GPL-2.0 | https://sourceforge.net/projects/guliverkli/ | Subtitle renderer for MPC and other DirectShow players | Medium |
| foobar2000 | foobar2000 | 0.8.3 | no | multimedia | freeware (closed). Current license: "Only unmodified installers can be redistributed" | https://www.foobar2000.org/license | Light, capable audio player. Check the license bundled inside the 0.8.3 installer | Low |
| devcpp | Dev-C++ | 4.9.9.2 (with MinGW/GCC 3.4.2, from memory) | no | development | GPL-2.0 | https://sourceforge.net/projects/dev-cpp/ | C/C++ IDE plus compiler in one install; the project text says "Windows 98, NT, 2000 & XP" | High |
| openwatcom | Open Watcom C/C++ | 1.9 | no | development | Sybase Open Watcom Public License 1.0 (binary distribution allowed with a source-availability notice) | https://www.openwatcom.org/ftp/install/ ; https://www.openwatcom.org/ftp/install/license.txt | C/C++/Fortran for DOS, Win16, Win32 and OS/2, a natural fit for 9x (9x host support from memory) | Medium |
| nasm | NASM | 2.07+ (Win32 build; DOS build as fallback) | no | development | BSD-2-Clause (from 2.07) | https://www.nasm.us/ | x86 assembler | Medium |
| tcltk84 | Tcl/Tk | 8.4.20 | no | development | Tcl/BSD-style (from memory). Do **not** use ActiveTcl binaries (their EULA is restrictive) | https://www.tcl-lang.org/software/tcltk/8.4.html ; https://wiki.tcl-lang.org/page/Windows+98 | Scripting and GUI toolkit; 8.5+ dropped 98 | Medium |
| freepascal | Free Pascal | 2.6.4 (from memory; must be tested) | no | development | compiler GPL, RTL modified LGPL | https://www.freepascal.org/faq.html | Pascal/Delphi-compatible compiler for Win32 and DOS | Low |
| lua51 | Lua | 5.1.5 (LuaBinaries Win32) | no | development | MIT | https://www.lua.org/license.html | Tiny embeddable scripting language | Medium |
| stella | Stella | 3.6.1 | no | games/emulators | GPL-2.0 | https://stella-emu.github.io/changelog.html ; https://github.com/stella-emu/stella | Atari 2600 emulator; the changelog says 3.7 dropped 98/ME/2000 | High |
| vba | VisualBoyAdvance | 1.7.2 | no | games/emulators | GPL-2.0 | https://sourceforge.net/projects/vba/ | Game Boy / GBC / GBA emulator | Medium |
| zsnes | ZSNES | 1.51 | no | games/emulators | GPL-2.0 | https://sourceforge.net/projects/zsnes/ | SNES emulator written in asm, fast on 98-era CPUs; Windows and DOS builds | High |
| fceu | FCE Ultra | 0.98.12 (Win32, from memory) | no | games/emulators | GPL-2.0 | https://sourceforge.net/projects/fceultra/ | NES emulator. Old files show 0.98.15 source and rerecording builds | Low |
| prboom-freedoom | PrBoom + Freedoom | PrBoom 2.5.0 + Freedoom IWADs | no | games | PrBoom GPL-2.0; Freedoom BSD | https://sourceforge.net/projects/prboom/ ; https://freedoom.github.io/about.html | A complete, legal Doom-engine game with no id data needed (98 run from memory, SDL 1.2) | Medium |
| bochs | Bochs | 2.3.7 | no | games/emulators | LGPL-2.1+ (per csv, not re-checked) | https://sourceforge.net/projects/bochs/files/bochs/ | x86 PC emulator (csv: msfn-95 lists 2.3.7; 2.5 needs KernelEx) | Medium |

## Needs KernelEx (8)

| id | name | version | KernelEx | category | license | evidence URL | why useful | confidence |
|---|---|---|---|---|---|---|---|---|
| avidemux | Avidemux | 2.5.2 | yes | multimedia | GPL-2.0 | https://sourceforge.net/projects/avidemux/ | Simple video cutting and re-encoding (csv: msfn-kx and osr-kx both 2.5.2) | Medium |
| smplayer | SMPlayer | 14.3.0 | yes | multimedia | GPL-2.0 | https://sourceforge.net/projects/smplayer/ | MPlayer front-end that plays nearly any format (csv osr-kx) | Medium |
| lavfilters | LAV Filters | 0.66.0 | yes | multimedia | GPL-2.0 | https://github.com/Nevcairiel/LAVFilters | Modern DirectShow decoders (H.264 and others) for MPC (csv osr-kx) | Medium |
| wings3d | Wings 3D | 1.0 | yes | graphics | BSD-style (license.terms) | https://raw.githubusercontent.com/dgud/wings/master/license.terms | Subdivision 3D modeller | Medium |
| qemu | QEMU | 0.13.0 | yes | system tools | GPL-2.0 | https://www.qemu.org/docs/master/about/license.html | Emulates other PCs and CPUs (csv msfn-kx and osr-kx) | Medium |
| golly | Golly | 1.4 | yes | games | GPL-2.0 | https://sourceforge.net/projects/golly/ | Game of Life / cellular automata explorer | Medium |
| xchm | xCHM | version from csv lead (unspecified; test) | yes | office | GPL-2.0 | https://github.com/rzvncj/xCHM | CHM e-book/help viewer | Low |
| graphviz | Graphviz | 2.28 | yes | development | EPL (2.28 era: EPL-1.0, from memory; current EPL-2.0) | https://graphviz.org/license/ | Graph and diagram rendering from text | Medium |

Notes:
- **WinSCP icons.** The license page says the icon set is under separate terms that restrict redistribution without permission. Official unmodified binaries are probably fine, but read the icon license before publishing.
- **NirSoft tools.** They must be redistributed with every file in the package, unmodified, and free of charge. Beacon's model meets this.
- **HxD.** Redistribution is allowed only as the unmodified original package, and bundling with commercial products needs permission. If Beacon is ever sold, ask the author first.
- **Office is thin in this batch.** Apart from xCHM, no well-licensed 98-era office tools stood out.

## Dropped candidates

| candidate | reason | external? |
|---|---|---|
| IrfanView | Verified: the EULA forbids distribution "without prior written consent" and is free for private use only (https://www.irfanview.com/eula.htm) | Possibly, if old 4.44 is still on irfanview.com (not checked) |
| Resource Hacker | Verified: "not to be distributed via any website domain or any other media without the prior written approval" (https://www.angusj.com/resourcehacker/) | Yes, the author still serves it; check whether over HTTP |
| XnView | Verified: freeware for private/educational use only; the page gives no redistribution grant (https://www.xnview.com/en/xnview/) | Possibly |
| PhotoFiltre 7 | Verified: freeware for private use only; no redistribution terms (https://www.photofiltre-studio.com/pf7-en.htm) | Possibly |
| Process Explorer, RegMon (Sysinternals) | From memory: the Sysinternals license forbids redistribution | Old versions are no longer served by Microsoft |
| Winamp 2.95 | From memory: the Nullsoft EULA forbids redistribution. Could not verify (winamp.com/legal has no terms) | No |
| ActivePerl / ActiveTcl | From memory: the ActiveState EULA restricts redistribution (license page 404). Look for a GPL/Artistic Perl 5.8 build instead | No |
| MAME / MAMEUI old builds | Pre-0.172 MAME used the old non-commercial MAME license (mamedev.org confirms GPL only from 0.172). Held until the old terms are checked | - |
| Java RE, Adobe Reader, Flash, QuickTime, RealPlayer, Opera, AIM, Yahoo Messenger | Proprietary. From memory, redistribution needs a separate distribution agreement | Some are still on vendor archives |
| RegScanner | License is fine, but the current page says XP+ only. Not a license drop, just no 98 build | - |
| XVI32, Partition Logic, GrafX2, Freeciv, OpenTTD | Not dropped for license; not verified because the author site refused the connection or returned 404/402. Candidates for batch 3 | - |
| SciTE | License verified as permissive (https://www.scintilla.org/License.txt), but the last 98-capable version is unknown. Deferred | - |

Note: foobar2000 is kept (low confidence) only because its current license allows unmodified installers. If the license inside 0.8.3 is stricter, drop it.
