# Media Player Classic 6.4.9.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Media Player Classic (MPC), package id `mpc`
- Version asked for: 6.4.9.1, described as "the original Gabest build". **That premise is wrong**, see below.
- License: GNU GPL v2 or later
- Recommendation: **6.4.9.1, build 2008-10-05 (SVN revision 82), `mplayerc_20081005_win9x.zip` from the guliverkli2 project**, listed as `external`, not hosted. The alternative is Gabest's own last release, 6.4.9.0 (2006-03-20, `mpc98me6490.zip`). Both have the same licensing problem (see License).

## Which release is which

- Gabest's project **guliverkli** (https://sourceforge.net/projects/guliverkli/, admins gabest and schultz_, GPLv2). Its file area (SourceForge RSS, opened) holds MPC releases 6.4.5.1 to **6.4.9.0**. The newest are `MPC 6.4.9.0/mpc98me6490.zip`, `mpc98me6490.7z`, `mpc2kxp6490.zip` and `mpc2kxp6490.7z`, all uploaded 2006-03-20. It has **no 6.4.9.1**.
- In Gabest's SVN (https://svn.code.sf.net/p/guliverkli/code/, read over WebDAV) the version in `src/apps/mplayerc/mplayerc.rc` is 6,4,8,9 up to r549 and becomes **6,4,9,0 in r550** (2006-03-20 19:42 UTC). It is still 6,4,9,0 at HEAD, r896 (2009-01-31). **Gabest never produced a 6.4.9.1.**
- **6.4.9.1** comes from the separate project **guliverkli2** (https://sourceforge.net/projects/guliverkli2/, opened: "based on the latest source code from the original Guliverkli project" with library updates, bug fixes and security patches; GPLv2; maintained by clsid2; registered 2007-09-14; inactive). Its SVN r1 is "Guliverkli revision 611" (2007-09-18), and r2 onwards are clsid2's changes. The file area `Media Player Classic/6.4.9.1/` (opened) has two files:
  - `mplayerc_20081005_win9x.zip` (2008-10-05): the Windows 9x (ANSI) build. The exe contains the strings "(revision 82)" and "http://sourceforge.net/projects/guliverkli2/". SVN r82 is dated 2008-10-05 13:31 UTC.
  - `mplayerc_20100214.zip` (2010-02-14, r107): Unicode build. Its imports use W functions (SetWindowTextW, SendDlgItemMessageW, ...) and it does not link unicows, so it does **not** run on 9x.
- Wikipedia's Media_Player_Classic article (opened) agrees: "MPC 6.4.9.0, released March 20, 2006, is the final official version" and "MPC 6.4.9.1 Revision 107, released February 14, 2010, is the final release version" (of the clsid fork).
- The About text in the 6.4.9.1 exe still says "Copyright (C) 2002-2008 Gabest". It is Gabest's code with clsid2's changes, not a Gabest release.

Why 6.4.9.1 (2008 win9x build) over 6.4.9.0:
- It has newer bundled libraries: faad2 2.6 (6.4.9.0 has 2.0), zlib 1.2.3 (6.4.9.0 has 1.1.4), libpng 1.2.32, and updated liba52/libdts.
- Comparing the source of r550 (6.4.9.0) with guliverkli2 r82:
  - FLICSource.cpp gains a bounds check commented "Fixed vulnerability". This is the CVE-2006-7222 FLI overflow.
  - AviFile.cpp gains a `size < MAXDWORD-8` check before allocating the AVI `indx` buffer. This covers the 0xffffffff case of CVE-2007-4939.
  - The SVN log also lists "Fixed buffer overrun in VobSub code" (r39).
- Against it: this is a third-party maintenance build, not Gabest's.
- If the catalog must carry the original author's release, use 6.4.9.0 (`alt\`). All other facts below apply to both builds unless stated.

## Windows 9x support evidence

- The file names mark the builds as 98/ME editions: Gabest's `mpc98me6490.zip`, next to `mpc2kxp6490.zip` for 2000/XP, and clsid2's `mplayerc_20081005_win9x.zip`. I found no written system-requirements statement by Gabest or clsid2 on the pages I opened.
- Static analysis of both 9x exes. I parsed the PE import tables and did not run anything.
  - PE OS/subsystem version 4.0. ANSI APIs throughout: CreateWindowExA, RegisterClassA, GetMessageA and so on.
  - **No unicows.dll/MSLU dependency.** The few W imports (RegSetValueExW, CreateFileW, TextOutW, GetTextExtentPoint32W, ChangeDisplaySettingsExW, ...) are functions that 9x exports natively or as stubs. Several are only there as Detours hook targets.
  - The import sets of the two 9x builds are identical.
  - The 2000/XP and 2010 builds are the Unicode ones.
- Static imports that set the minimum system:
  - `DDRAW.dll!DirectDrawCreateEx` needs **DirectX 7 or later**. DirectDrawCreateEx was introduced in DirectX 7 (general knowledge). Stock 98 SE has DirectX 6.1 and ME has 7.1, so a Windows 98 user must update DirectX first. Hence `Requires: dx 7.0`.
  - `USER32!MonitorFromWindow`, `EnumDisplayMonitors`, `GetMonitorInfoA` and `GetMenuBarInfo`, plus `KERNEL32!GetFileAttributesExA`: these are Windows 98-era APIs that stock Windows 95 lacks (general knowledge, not checked against a 95 system). So **Windows 95 is not supported**: the exe would fail to load.
  - WS2_32 (Winsock 2), WININET and SHLWAPI are all present on stock Windows 98.
- Delay-loaded (only loaded when used): PSAPI.DLL, d3d9.dll, gdiplus.dll, OLEACC.dll.
  - PSAPI and GDI+ do not exist on stock 98. Features that use them (probably process listing and some image saving) may fail, but the player starts.
  - d3d9 is only needed for the DirectX 9 renderers. The DirectX 7 renderer and overlay remain.
- Needs DirectShow, which comes with DirectX 6.1+ and Windows Media Player 6.4, so DirectX 7+ covers it. **KernelEx is not needed.**
- Not verified: actually running on 98 or ME (no VM interaction), and whether the Windows 98 first edition USER32 exports ChangeDisplaySettingsExW.

## Download

Recommended (6.4.9.1 win9x):
- Official file page: https://sourceforge.net/projects/guliverkli2/files/Media%20Player%20Classic/6.4.9.1/
- URL: https://downloads.sourceforge.net/project/guliverkli2/Media%20Player%20Classic/6.4.9.1/mplayerc_20081005_win9x.zip
- File: mplayerc_20081005_win9x.zip, 2,070,308 bytes. A plain zip holding one file, `mplayerc.exe` (4,345,856 bytes, FileVersion 6.4.9.1, dated 2008-10-05).
- SHA-256: 804a66aad98b2b79b3f9ae535d3e2d1dbcdc9bac31d32f9d55d79edd16b1e7d8
- MD5: d5dafbe1cbe19c88439f662256233414. The SourceForge file RSS for guliverkli2 lists the same MD5: MATCH. This MD5 is generated by SourceForge, not published or signed by the author, and there is no signature.
- Authenticode: not signed.
- Plain HTTP (tested 2026-09-29, `curl --http1.0`, redirects limited to http):
  - http://downloads.sourceforge.net/project/guliverkli2/Media%20Player%20Classic/6.4.9.1/mplayerc_20081005_win9x.zip answers 302 to http://master.dl.sourceforge.net/... (a signed, expiring query string).
  - The same test on the guliverkli URL downloaded the full file over http with the correct MD5.
  - The client must follow one HTTP redirect.

Alternative (6.4.9.0, Gabest), in `alt\`:
- URL: https://downloads.sourceforge.net/project/guliverkli/Media%20Player%20Classic/MPC%206.4.9.0/mpc98me6490.zip
- File: mpc98me6490.zip, 1,921,616 bytes, holding one file, `mplayerc.exe` (4,796,416 bytes, FileVersion 6.4.9.0, dated 2006-03-20).
- SHA-256: 6034f8fb3ea3832f325b6b87325ed7d9b4356d8c9b051247ebd425280333ea33
- MD5: 37f3705e1e216d0af2c32c7df9e2b53a. SourceForge RSS: MATCH.
- Also available: `mpc98me6490.7z` (MD5 55e5973f78d6bde62f26f6ebfd30c35f per SF), and 2000/XP builds that are not for 9x. There are also community translations under "Media Player Classic (transl.)", including 98/ME builds. None of these were downloaded.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\mpc -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". The scan covered both binaries and both source zips.

## License

- GPL v2 or later:
  - The SourceForge project pages for guliverkli and guliverkli2 both state GPLv2.
  - The About box in both exes reads "This program is freeware and released under the GNU General Public License." The 6.4.9.0 exe adds "Distribution in Codec Packs is allowed, but the author (Gabest) is not liable for the additional content."
  - Gabest's SVN r150 (2004-01-06): "Replaced the text of GPL with the text of the _real_ GPL ... guliverkli has always been released under the normal GPL".
- LICENSE.TXT here is `License.txt` from guliverkli2 SVN r82 (GPL v2, June 1991). It is identical in text to r550's except for line endings. The zip files themselves contain no license text.
- The GPL allows redistributing unmodified binaries if the license accompanies them and the complete corresponding source is provided or offered. **That condition cannot be met for these binaries.** The builds statically link code that is not GPL and whose source is not in the repository.

### Code in the binary without source

- **Microsoft Detours 1.5** (`lib/detours/detours.lib` and `detours.pdb`, header "Detours for binary functions. Version 1.5 (Build 46) Copyright 1995-2001, Microsoft Corporation").
  - It is linked into mplayerc.exe in both builds. The vcproj `AdditionalDependencies` lists detours.lib. mplayerc.cpp calls DetourFunctionWithTrampoline on IsDebuggerPresent, ChangeDisplaySettingsExA/W, CreateFileA/W, mixerSetControlDetails and DeviceIoControl. The exes contain the `.detour` marker and the imagehlp Sym* strings.
  - Only the compiled .lib is in SVN.
  - Detours before 4.0 was licensed by Microsoft Research for non-commercial/research use only; it was relicensed MIT only with 4.0.1 in 2016+. This is from general knowledge and search snippets; the 1.5 license text was not found or read. That license is not GPL-compatible.
- **Apple QuickTime SDK** `lib/qt6/qtmlClient.lib`: statically linked (strings theQuickTimeDispatcher, QTMLInitTermMutex, QuickTime.qts). It is Apple SDK code with no source.
- **Windows Media Format SDK** `lib/wm7/wmstub.lib`: linked per the vcproj. It is a Microsoft SDK stub with no source.
- **libmpeg2 MMX objects** `src/filters/transform/mpeg2decfilter/idct_mmx.obj` and `motion_comp_mmx.obj`: precompiled objects, and their C/asm sources are not in the tree. Upstream libmpeg2 has them, but I did not confirm which version.
- DirectShow BaseClasses (Microsoft DirectX SDK sample code):
  - not in r550, where they come from the DirectX 9 SDK;
  - included in guliverkli2 r82 as `src/filters/BaseClasses`, under the SDK sample license, not GPL.
- The static MFC 8 / MSVC runtime (Dinkumware) are compiler libraries. The GPL system-library exception usually covers these.
- Result:
  - The binaries combine third-party GPL code (libmad 0.15.0b, a52dec 0.7.4, dtsdec 0.0.1, faad2, libmpeg2) with proprietary static libraries. This is the same kind of problem as the unresolved VLC contrib sources, and worse, because the proprietary parts can never be supplied.
  - **Backport Labs should not host the binary.** Recommendation: `Availability: external`, downloaded from SourceForge, the project's own file host.

### Other licensing and patent notes

- **FAAD2**: the source files carry extra terms: "Any non-GPL usage of this software or parts of this software is strictly forbidden. Software using this code must display the following message visibly in the software: 'FAAD2 AAC/HE-AAC/HE-AACv2/DRM decoder (c) Ahead Software, www.nero.com'". Neither exe contains "Ahead" or "nero.com". They show only "Based on libfaad 2.0" (6.4.9.0) or "Based on libfaad 2.6" (6.4.9.1), with "http://www.audiocoding.com/", so neither binary complies with that notice requirement.
- **libdirac** (Dirac splitter/decoder, in both builds): MPL 1.1 / GPL 2 / LGPL 2.1 tri-license (COPYING read). OK.
- **DeCSS**: `src/decss` (CSSauth, CSSscramble, VobDec) is linked in. It decrypts CSS-protected DVDs, which is legally restricted in some countries (US DMCA).
- **Patent-encumbered decoders** built in:
  - MPEG-1/2 video (libmpeg2), MP3 (libmad), AC-3 (liba52), DTS (libdts) and AAC/HE-AAC (faad2).
  - The FAAD2 README warns: "the use of this software may require the payment of patent royalties".
  - MPEG-2, MP3 and AC-3 patents have expired by 2026 (general knowledge). AAC/HE-AAC and DTS should be checked by counsel.
  - No Windows Media, RealMedia or QuickTime decoders are bundled. MPC uses the system's installed codecs for those, through RealMedia and QuickTime headers and dynamic loading. unrar.dll is loaded only if present.
- No encoders are bundled, unlike VLC's LAME/FAAC.

## Matching source (not hosted; kept for reference)

No official source archive exists for either version. SourceForge's only source file releases are guliverkli_20030609.rar and guliverkli_20030820.rar from 2003. The source is in the projects' SVN repositories. I exported the exact revisions file by file, with plain GET requests on the SVN WebDAV `!svn/bc/<rev>` URLs, and zipped them. These zips are my own exports and are not byte-reproducible: they carry the download timestamps.
- 6.4.9.1: `src\guliverkli2-svn-r82.zip`, 6,899,789 bytes, 1,884 files, SHA-256 09a70f33b4a75561e77c97d0956f8a91ff812aedfd47fd9265d01e0b6185dfd3.
  - Source URL: https://svn.code.sf.net/p/guliverkli2/code/!svn/bc/82/ (whole repository root at r82, which is the trunk).
  - r82 matches the build: the exe says "(revision 82)" and mplayerc.rc says 6,4,9,1.
- 6.4.9.0: `alt\src\guliverkli-svn-r550-trunk-guliverkli.zip`, 6,428,166 bytes, 1,702 files, SHA-256 8ff8b51c582a7f71306d30b955b3319e02dc9903bde599e03566153808cff23a.
  - Source URL: https://svn.code.sf.net/p/guliverkli/code/!svn/bc/550/trunk/guliverkli/
  - r550 is the version-bump commit to 6.4.9.0. It was committed about 5 hours *after* the binaries were uploaded (14:4x UTC), so it most likely matches the release build but this is not proven.
- The SourceForge snapshot tool (https://sourceforge.net/p/guliverkli/code/550/tarball?path=/trunk/guliverkli) offered a link, but it returned 404 and needs a POST to regenerate. I did not use it.
- Both trees contain `bin/upx.exe`, a third-party packer used by the build and not part of MPC.

## Security

Sources: NVD API 2.0 (keyword "Media Player Classic", 12 results; keyword "mplayerc"; virtualMatchString cpe:2.3:a:guliverkli:media_player_classic), plus a source diff between r550 and r82.

CVEs naming MPC 6.4.9.0 or earlier (9):
- CVE-2007-4939: AVI `indx` heap overflow, possible code execution, CVSS2 9.3. Addressed in r82 for the 0xffffffff size case.
- CVE-2007-4940: AVI `indx` integer overflows, possible code execution, CVSS2 9.3. The r82 size check may cover it; not verified.
- CVE-2007-6402: .mp4 stack overflow with the 3ivx codec installed, CVSS2 9.3. Needs third-party 3ivx.
- CVE-2006-7222: FLIC `_deltachunk` buffer overflow, code execution, CVSS2 6.8. Fixed in r82 ("Fixed vulnerability" in FLICSource.cpp).
- CVE-2007-3662: crafted FLV, DoS or possible code execution, CVSS2 6.8. Not checked in r82; r82 has many FLV splitter changes.
- CVE-2007-3663 and CVE-2007-2723: MPA divide-by-zero, CVSS2 6.8 and CVSS3.1 5.5. Not checked in r82.
- CVE-2007-4884: .au divide-by-zero DoS, CVSS2 4.3. Not checked.
- CVE-2009-3201: MIDI header integer overflow DoS, CVSS2 4.3. Not checked.

Related, not counted:
- CVE-2010-3138 is an insecure DLL load in Microsoft's Indeo codec, reached through MPC on XP. It is a Windows codec bug.
- CVE-2013-3488 and CVE-2013-3489 are MPC-HC only.

Bundled libraries have their own CVE backlogs, not counted here. Examples: zlib 1.1.4 in 6.4.9.0, libpng 1.2.32 in 6.4.9.1, faad2, liba52 and libmad of 2004-2008.

Summary:
- 6.4.9.0 has 9 NVD CVEs.
- For 6.4.9.1 r82, 1 of them is fixed (CVE-2006-7222) and 1 mostly addressed (CVE-2007-4939); the other 7 are unknown.
- Worst: CVE-2007-4939 and CVE-2007-4940 (AVI index overflows, CVSS2 9.3), which only need the user to open a crafted AVI.
- The built-in web server (off by default) and the subtitle-database (ISDb) network features add network-facing code.

## Install behaviour

- Installer type: none. A plain zip with a single file at its root, `mplayerc.exe`, and no folders (listed with .NET ZipFile).
- Beacon: `unzip {dir}` (strip 0), Start Menu shortcut to `{dir}\mplayerc.exe`, `Uninstall: files`. There is no Add/Remove Programs entry, because there is no uninstaller.
- Settings are stored under HKCU `Software\Gabest\Media Player Classic` (string in the exe). By general knowledge MPC uses `mplayerc.ini` instead if that file exists next to the exe; I did not verify this, so no `After` step is proposed. Registry settings stay behind after removal.
- File associations are made by the user in Options > Formats, not at install.

## Verification notes

- Verified by opening or downloading:
  - the guliverkli and guliverkli2 SourceForge project pages and file RSS feeds (MD5s);
  - the guliverkli2 6.4.9.1 folder page and the full SVN logs of both projects (guliverkli through a WebDAV log-report; guliverkli2 through the SourceForge log page);
  - mplayerc.rc versions at r547-r550, r82 and HEAD;
  - the full r550 and r82 source trees, including the vcproj link lines, detours.h, FAAD2 README/COPYING/source headers, libdirac COPYING, and the FLIC/AVI diffs;
  - all four candidate zips (MD5 matched SF): PE imports, delay imports, version resources and strings (none executed);
  - NVD API results, the Wikipedia MPC article, and the plain-HTTP download test.
- From search snippets or general knowledge only:
  - the Detours 1.5 license terms;
  - the patent-expiry status;
  - the minimum-OS facts for MonitorFromWindow and related APIs, and that DirectDrawCreateEx needs DirectX 7;
  - the mplayerc.ini behaviour.
- Not verified:
  - running on 98/ME/95;
  - the fix status of 7 of the 9 CVEs in r82.

## Package folder

```
mplayerc_20081005_win9x.zip          recommended binary (6.4.9.1 r82, win9x)
LICENSE.TXT                          GPL v2 (License.txt from guliverkli2 r82)
src\guliverkli2-svn-r82.zip          source export for the recommended build
alt\mpc98me6490.zip                  alternative: Gabest 6.4.9.0, 98/ME build
alt\src\guliverkli-svn-r550-trunk-guliverkli.zip   source export for 6.4.9.0
ENTRY.TXT                            draft catalog block (external)
```
