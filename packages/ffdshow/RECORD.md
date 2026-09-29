# ffdshow-tryouts rev 2322 - Beacon 98 record

- Date checked: 2026-09-29
- Package: ffdshow (ffdshow-tryouts project; builds by clsid)
- Version: SVN revision 2322, build of 2008-11-14 (`ffdshow_rev2322_20081114_clsid.exe`). Installer name "ffdshow [rev 2322] [2008-11-14]".
- License: GNU GPL v2 (plus unRAR license for ff_unrar.dll)
- KernelEx: not needed. The installer contains its own ANSI build for Windows 9x and installs Microsoft's unicows.dll.
- Recommendation: **rev 2322, listed as `external`** (downloaded from SourceForge, the project's own file server, over plain HTTP). **It cannot be hosted**: the bundled libavcodec.dll contains the 3GPP AMR reference decoder, which is non-free. It also contains DeCSS code and has other gaps; see License.
  - Choice between builds: rev 2352 (2008-11-24) is the last build whose installer still carries a Windows 9x (ANSI) version, and it contains the fix for CVE-2008-5381. But users report it and rev 2347 fail to register on 98 ("LoadLibrary failed; code 31"), while rev 2322 works. Rev 2322 is recommended, with a Warning. Rev 2352 is worth a test in the lab VM.
  - The original ffdshow by Milan Cutka (SourceForge project "ffdshow", builds up to 2006) is older than the tryouts builds; MSFN users ran the 2005-11-11 "ansi" build on 98SE. It was not evaluated further.

## Windows 9x support evidence

- The installer script of this exact revision, `bin/distrib/InnoSetup/ffdshow_installer.iss` at r2322 (https://sourceforge.net/p/ffdshow-tryout/code/2322/tree/trunk/bin/distrib/InnoSetup/ffdshow_installer.iss?format=raw, downloaded; identical to the file in the source archive below):
  - `#if PREF_CLSID` (the "_clsid" builds): `#define VS2003SP1 = True`, `#define unicode_required = False`.
  - "; Layer for Unicode on Windows 9x. installed only on Windows 9x (forced). The uninstaller does not remove this. ; Note Unicode build does not work on Windows 9x even with unicows.dll." then `Source: Runtimes\LayerForUnicode\unicows.dll ; DestDir: {sys}; ... MinVersion: 4,0`.
  - "; ANSI + Unicode:" `Source: ffdshow_ansi.ax; DestName: ffdshow.ax; ... MinVersion: 4,0` and `ffdshow_unicode.ax ... MinVersion: 0,4`. The same pair exists for ff_wmv9.dll. MinVersion 4,0 means Windows 9x only.
- The same script at r2359 still has the ANSI build. At r2361 (clsid2, 2008-11-25, "Updated install script.") it no longer does: no ffdshow_ansi.ax, no unicows, and `MinVersion=0,5.0` (Windows 2000). Checked at r2361, 2363, 2364, 2373, 2380, 2391, 2398, 2400 and 2527. So the last clsid builds meant for 9x are r2322, r2335 (SSE/ICL build only) and r2352 (clsid builds folder on SourceForge).
- SVN log (https://sourceforge.net/p/ffdshow-tryout/code/2364/log/?path=/trunk and earlier pages, opened): r2348 "Updated VS2008 project file. Enabled static linking.", r2349 "Use of secure string manipulation functions...fix crash with very long URL.", r2358 "Removed VS2005 project files.", r2361/2363 "Updated install script."
- Own check of the installer contents (listed and unpacked with innoextract 1.9; nothing was run): it has two ffdshow.ax files. The ANSI one (2,580,480 bytes, OS version 4.0) imports no Unicode (W) Windows functions and refers to unicows.dll, which means it uses the MSLU loader. The 2352 ANSI build instead links the C runtime statically and imports extra kernel32 functions (e.g. InitializeCriticalSectionAndSpinCount). That may explain the failure reported on 98, but the cause was not determined.
- MSFN "ffdshow rev2352 for Win98/ME installation failure" (https://msfn.org/board/topic/128016-ffdshow-rev2352-for-win98me-installation-failure/, opened; user posts, not developers), 2009-01-01: oc_dt: "This rev2352 is the last version for Win98/ME. I failed the installation with the following message: ffdshow.ax Unable to register the DLL/OCX: Loadlibrary failed; code 31." rainyd: "Yes, looks like there's problem with revisions 2352 and 2347 but you can safely install 2322".
- Windows ME: covered by the same 9x path. Windows 95: the ANSI path would also be chosen (MinVersion 4,0), but nobody states that it works; not listed.
- Needs DirectShow (DirectX) on the system; minimum version not stated.

## Download

- URL: https://downloads.sourceforge.net/project/ffdshow-tryout/SVN%20builds%20by%20clsid/very%20old%20builds/ffdshow_rev2322_20081114_clsid.exe (official SourceForge project ffdshow-tryout, folder "SVN builds by clsid/very old builds", listed 2008-11-14)
- Plain HTTP: `http://downloads.sourceforge.net/...` answers 302 to `http://master.dl.sourceforge.net/...` (a signed, time-limited address), which served the identical file over HTTP/1.0 on 2026-09-29 (same SHA-256).
- File: ffdshow_rev2322_20081114_clsid.exe, 4,259,365 bytes (32-bit Inno Setup installer)
- SHA-256: f1f5877c96d9fdfa753899f38a655ca2f54a9a676116e8e54f72d473d68a2ea7
- MD5: b8ceee3360f44dc3736123b2760a1654
- Published checksum: not obtained. The SourceForge RSS only returns the newest 100 files of that folder and does not reach rev 2322. The project publishes no checksums of its own. Unverified.
- Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ffdshow -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- ffdshow: GPL v2 (`copying.txt`; readme: "Completely free software: ffdshow is distributed under GPL"). LICENSE.TXT here = copying.txt + unrar/license.txt + the FAAD2 license header, all from the r2322 source.
- Contents of the installer (innoextract listing): ffdshow.ax (ANSI and Unicode), ff_wmv9.dll (x2), libavcodec.dll (FFmpeg), libmplayer.dll, ff_liba52, ff_libdts, ff_libfaad2, ff_libmad, ff_tremor, ff_unrar, ff_samplerate, ff_theora, ff_x264 (H.264 encoder), xvidcore.dll (MPEG-4 ASP encoder/decoder), ff_kernelDeint, TomsMoComp_ff, libmpeg2_ff, ff_vfw.dll, ff_acm.acm, makeAVIS.exe, plug-ins for AviSynth/VirtualDub/DScaler, and in {sys}: msvcr71.dll, msvcp71.dll, unicows.dll, pthreadGC2.dll.
- **Why it cannot be hosted** (the same kind of problems as VLC):
  1. **Non-free AMR code:** libavcodec.dll contains "libamr_nb", built from `src/ffmpeg/libavcodec/amr_float/` ("3GPP AMR Floating-point Speech Codec", TS 26.104 reference code). The 3GPP reference code is not under a free license. FFmpeg itself treated libamr as `--enable-nonfree`, which makes the binary unredistributable (general knowledge about FFmpeg's classification; the 3GPP terms were not opened). Verified: strings "libamr-nb Adaptive Multi-Rate (AMR) Narrow-Band" in the shipped libavcodec.dll, and the source files in the tree.
  2. **DeCSS:** `src/CSSscramble.cpp` is compiled into ffdshow.ax (listed in every ffdshow*.vcproj; "CSSscramble" strings in the ANSI ffdshow.ax). This is DVD CSS descrambling, restricted in some countries (US DMCA).
  3. **Missing source:** `src/imgFilters/awarpsharp/aws.obj` is a precompiled object linked into ffdshow.ax; its source is not in the tree (only aws_api.h).
  4. **Microsoft files:** unicows.dll (MSLU), msvcr71.dll and msvcp71.dll are in the installer and installed into the SYSTEM folder. Their redistribution terms (MSLU and VS2003 redist) were not verified.
  5. Also noted: ff_unrar.dll is under the unRAR license (free to distribute, no fee may be charged; not GPL, but a separate DLL). FAAD2 requires the notice "FAAD2 AAC/HE-AAC/HE-AACv2/DRM decoder (c) Nero AG, www.nero.com" to be visible; the string is in ff_libfaad2.dll, but whether ffdshow shows it was not checked. The RealNetworks Helix AAC decoder (RPSL/RCSL, GPL-incompatible) is in the tree as ff_realaac, but it is **not** in this installer. No FAAC (the libavcodec strings contain no "libfaac").
- Patents: H.264 (x264 encoder, libavcodec decoder), MPEG-4 ASP (Xvid), AAC (FAAD2), AMR, AC-3, DTS, MPEG-2, WMV/VC-1 and others. Some are expired, but H.264 and AAC pools were still active recently. Counsel needed if this were ever hosted.
- Conclusion: `Availability: external`. Beacon points at the SourceForge file; Backport Labs distributes nothing. This matches the VLC decision.

## Matching source (kept for the record, not hosted)

- There is no official source archive for SVN builds. The source for r2322 was taken from a git-svn mirror of the official SVN: https://github.com/jeeb/ffdshow-tryouts, commit 0d24619d0b257b5c72c12e92b3e693a9cd024467 ("Updated FFmpeg", 2008-11-14 12:35:00, `git-svn-id: https://ffdshow-tryout.svn.sourceforge.net/svnroot/ffdshow-tryout/trunk@2322`), exported with `git archive` and compressed.
- File: src\ffdshow-tryouts-trunk-r2322.tar.xz, 6,461,780 bytes, SHA-256 981c7e19ee6f6914b7f8cead5dad3d402412f9e6b29d824c81ddc95a22403bc5 (not byte-reproducible; 2,579 files).
- Cross-check: the installer script in this export is identical to the one downloaded directly from SourceForge SVN at r2322.
- SourceForge's own snapshot service (https://sourceforge.net/p/ffdshow-tryout/code/2322/tarball?path=/trunk) could not be triggered from a script (403 on the request form).
- The source includes FFmpeg, libmpeg2, liba52, libdts, libmad, FAAD2, Tremor, Theora, x264, Xvid, unRAR, KernelDeint, TomsMoComp and zlib, but not aws.obj's source (see above).

## Security

- NVD API 2.0 keyword search "ffdshow" (2026-09-29): 1 result.
  - CVE-2008-5381: buffer overflow in URL processing "before SVN revision 2347" allows remote code execution via a long URL, CVSS2 9.3. **Affects rev 2322.** Fixed by r2349 ("fix crash with very long URL"), which is only in builds that reportedly fail on 98.
- Bundled FFmpeg (Nov 2008), libmad, FAAD2, liba52, Xvid, Theora and zlib have their own large CVE backlogs (FFmpeg alone has hundreds of later CVEs for 2008-era code). Not counted.
- ffdshow is loaded by every DirectShow/VfW program, and also by Internet Explorer/Windows Media Player for web media, so crafted files or streams reach it easily.
- Summary: 1 CVE for ffdshow itself (CVSS 9.3), plus many in bundled libraries.

## Install behaviour

- Installer type: Inno Setup (setup data version 5.2.3, per innoextract).
- Silent install: standard Inno `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (not documented by the project). `ShowLanguageDialog=yes` for localized builds; a silent install skips the dialog. Codec choices come from the script's defaults. If an old NSIS-based ffdshow is registered, the script shows a message and runs its uninstaller first (message boxes are suppressed in silent mode; untested).
- Default folder: `{pf}\ffdshow` unless HKLM `Software\GNU\ffdshow\pth` points to an existing folder.
- Installs into {sys}: ff_vfw.dll, ff_acm.acm, pthreadGC2.dll, msvcr71.dll/msvcp71.dll (only if missing) and unicows.dll (never uninstalled). On 9x it registers the VfW/ACM codecs in SYSTEM.INI [drivers32] (vidc.ffds, msacm.avis). Registers ffdshow.ax (regserver). Settings are under HKCU/HKLM `Software\GNU\ffdshow*`. Start Menu group "ffdshow".
- Uninstaller: yes (Inno). `AppId=ffdshow` gives the key `...\Uninstall\ffdshow_is1`. DisplayName = AppVerName = **"ffdshow [rev 2322] [2008-11-14]"** (the name innoextract reports; the uninstall display name is inferred from the script, not seen on a machine).

## Verification notes

- Verified by opening or downloading: the installer (innoextract listing/unpack, PE imports, strings), the r2322 and later installer scripts from SourceForge SVN, the SVN log pages, the SourceForge folder listings, the MSFN threads, the git-svn mirror, NVD, and the HTTP download path.
- Not verified: running on 98/ME/95; the SourceForge MD5 for this file; the redistribution terms of unicows.dll and the MSVC 7.1 runtime; the 3GPP license text (general knowledge); why rev 2347/2352 fail on 98.
