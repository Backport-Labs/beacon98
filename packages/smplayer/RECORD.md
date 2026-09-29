# SMPlayer 14.3.0 Portable - Beacon 98 record

- Date checked: 2026-09-29
- Package: SMPlayer (Ricardo Villalba), with the MPlayer build it bundles
- Version: 14.3.0 Portable Edition (2014-03-31), 32-bit
- License: SMPlayer GNU GPL v2 or later; the bundled MPlayer is GPL v2; Qt 4.8.4 is LGPL 2.1
- Needs KernelEx on Windows 98 and ME. Not for Windows 95.
- Recommendation: smplayer-portable-14.3.0.7z, the exact build that was reported working. Do NOT use the setup exe (see Defender and Install).

## Windows 9x / KernelEx evidence

- Operating System Revival, "List of Working Windows 98/ME KernelEx Applications" (downloaded and read 2026-09-29),
  https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html , Media Players:
  "SMPlayer 14.3.0 Portable (KernelEx 4.5.2019.24; Base Enhancements)".
  - KernelEx 4.5.2019.24 is the unofficial updated KernelEx build (with the "Kernel Updates" project). "Base Enhancements" is its default mode, not an XP/2000 mode. Beacon ships KernelEx 4.5.2 (official). The report is for the newer unofficial build, so test with 4.5.2 in the VM. It may not work there.
- SMPlayer is not on the MSFN KernelEx list. There, "MPlayer MPUI.2009-06-12.Full-Package, KX 4.0" and "MPlayer WW SVN-r34106 (20110916), KX 4.5.1, Win2k mode" are listed.
- MPlayer: the portable package bundles it (mplayer\mplayer.exe). mplayer\README.txt: "MPlayer/MEncoder Win32 binary Builds by Redxii <redxii@users.sourceforge.net> for SMPlayer". The version string in mplayer.exe is "Redxii-SVN-r36621-4.8.2" (MPlayer SVN r36621, GCC 4.8.2, January 2014). Qt: QtCore4.dll file version 4.8.4.0. Neither supports 9x, which is why KernelEx is needed.
- Older version without KernelEx: the SMPlayer Changelog (in the 14.3.0 source) shows 9x work in the 0.6.0 cycle: "(2007-10-04) Added some code to use an intermediate program for mplayer, when using Windows 98 and ME" and "(2007-12-17) Added patch by Florin Braghis to support Win 98." This lies between 0.5.62 and 0.6.0rc1, so SMPlayer 0.6.0/0.6.1 (2008) are the candidates. On SourceForge: /SMPlayer/0.6.1/smplayer_0.6.1_setup.exe (11,661,775 bytes, 2008-05-28, SF MD5 81ed5fead35716d8c20e4845f9404b2e). I did not download or test it. Nothing states that a released 0.6.x Windows build (and its Qt 4.x and MPlayer) runs on stock 98. Unverified, so it needs a VM test. If it works, it avoids KernelEx.

## Download

- Files page: https://sourceforge.net/projects/smplayer/files/SMPlayer/14.3.0/ (official project, read from the SF RSS)
- URL: https://downloads.sourceforge.net/project/smplayer/SMPlayer/14.3.0/smplayer-portable-14.3.0.7z
- File: smplayer-portable-14.3.0.7z, 19,454,066 bytes (7z, LZMA+BCJ2, top folder `smplayer-portable-14.3.0\`, 1,649 files, 67,411,902 bytes unpacked)
- SHA-256: 186630a00f3b90d2b166fe246f4c23134fd0fc7e054959a58cab96414f256de1
- MD5: 6a1204d5d7935845c4648cfd00f409b7. The project's own MD5SUMS.txt in the same folder, and the SF RSS: MATCH.
- Also downloaded, NOT recommended: smplayer-14.3.0-win32.exe, 21,395,592 bytes, SHA-256 d271df929ed37ecbe26d558f6a1781534af6bf02100582e578dc7a16b6d0ec61, MD5 2e8bf2cae67facb0ea0669b4e6851901 (MD5SUMS.txt: MATCH). Defender flags it (below). Its .onInit aborts on anything older than XP when silent (below). I left it in the folder because Defender detections must not be removed or worked around. Do not publish it.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\smplayer -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): **1 threat: PUABundler:Win32/CandyOpen in smplayer-14.3.0-win32.exe** (the setup exe; a bundled-offer/adware installer detection). Nothing else was detected, so the portable .7z and the sources are clean. Not bypassed, excluded or removed. Reported and left in place.

## License

- SMPlayer: GPL v2 or later (Readme.txt: "either version 2 of the License, or (at your option) any later version"); Copying.txt = GPL v2. QtSingleApplication BSD, libmaia Simplified BSD.
- MPlayer build: mplayer\licenses\mplayer.txt = GPL v2. The package includes license texts for its third-party libraries (a52, bzip2, enca, expat, faad, fontconfig, freetype, fribidi, giflib, gsm, jpeg, lame, libass, libbluray, libcaca, libcdio, libdca, libiconv, libilbc, libmad, libmng, libogg, libpng, libtheora, libvorbis, libvpx, live555, lzo, mpg123, opencore-amr, opus, sdl, speex, twolame, x264, xvid, zlib).
- Some icons are CC BY-SA and some "use without restrictions" (Readme.txt). Both allow redistribution.
- LICENSE.TXT = a summary header plus Copying.txt, Copying_BSD.txt, Copying_libmaia.txt and mplayer\licenses\mplayer.txt, copied unchanged from the package.
- Redistributing the unmodified package is allowed. We must offer the corresponding source:

## Matching source (hosted)

- src/smplayer-14.3.0.tar.bz2: https://downloads.sourceforge.net/project/smplayer/SMPlayer/14.3.0/smplayer-14.3.0.tar.bz2, 3,675,657 bytes,
  SHA-256 9b8db20043d1528ee5c6054526779e88a172d2c757429bd7095c794d65ecbc18, MD5 c6ef86f7fe0022b35c0f06430f4cd9bd (MD5SUMS.txt: MATCH).
- src/mplayer-r36621-src.7z: https://downloads.sourceforge.net/project/mplayerwin/MPlayer-MEncoder/Archive/2014/r36621/mplayer-r36621-src.7z (Redxii's own mplayerwin project, same revision as the bundled binary), 11,130,495 bytes,
  SHA-256 ecb2933dee68bf54181b31ff69e254f751f311dc7718175b53cd473eee7d6247. It matches the SHA256SUMS published in that folder.
- NOT included, unresolved:
  - Qt 4.8.4 (LGPL 2.1). The official source is https://download.qt.io/archive/qt/4.8/4.8.4/qt-everywhere-opensource-src-4.8.4.zip (HTTP 200, 282,284,785 bytes; checked with a HEAD request, not downloaded). Host it or link it.
  - The third-party libraries statically linked into mplayer.exe (FFmpeg is inside the MPlayer source tree; the others are not). The mplayerwin project publishes "mplayer-3rdparty-src" archives only from 2018 onward, and I found none from January 2014.

## Security

- NVD keyword "smplayer": 2. CVE-2011-3625 (MPlayer SAMI subtitle stack overflow as used in SMPlayer 0.6.9; fixed long before 14.3.0, so not affected). CVE-2019-19489 (long .m3u buffer overflow, stated for 19.5.0, CVSS 5.5; whether it affects 14.3.0 is unknown).
- NVD keyword "mplayer": 66 in all. Most predate r36621. Those published after January 2014 and probably affecting r36621: CVE-2016-4352 (demux_gif integer overflow), CVE-2016-5115, and the 2022 batch CVE-2022-32317, CVE-2022-38600 and CVE-2022-38850 to 38866 (buffer overflows and divide-by-zero in demuxers; the worst is CVE-2022-38862, af.c buffer overflow, CVSS 7.8). That is about 16. I did not check each one against r36621.
- The bundled FFmpeg (early 2014) and other codec libraries have many later-fixed memory-corruption CVEs. They are not counted.
- Summary: about 16 MPlayer CVEs plus 1 possible SMPlayer CVE. The worst is CVE-2022-38862 (7.8). The risk is opening crafted media files or playlists.

## Install behaviour

- The recommended file is a plain 7z archive with no installer. Unpack the folder `smplayer-portable-14.3.0\` anywhere and run smplayer.exe. Portable_Edition.txt: "To install it, just uncompress it wherever you want", and it "won't write anything in the Windows registry".
- **Beacon problem: FORMAT.md `unzip` handles ZIP and self-extracting ZIP only, not 7z.** Options: (a) add 7z support to the client (LZMA+BCJ2, solid); (b) repackage the unmodified files as a ZIP (this changes the container, not the files, but then the hosted file is no longer the publisher's original and the SHA-256 is ours); (c) use the setup exe (not advised, see below). This is unresolved. ENTRY.TXT assumes (a) and says so.
- Target: `{pf}\SMPlayer`, strip 1. Shortcut smplayer.exe. Uninstall: files. No Add/Remove Programs entry.
- Setup exe (not recommended): Unicode NSIS 2.46.5 (setup/smplayer.nsi in the source). Its .onInit has `${Unless} ${AtLeastWinXP}` followed by MessageBox OS_Not_Supported with `/SD IDNO`, which means a silent install (`/S`) on 98 aborts unless KernelEx makes the installer think it is on XP. Default folder `$PROGRAMFILES\SMPlayer`. Uninstall key `...\Uninstall\SMPlayer`, DisplayName "SMPlayer 14.3.0" (`$(^Name)` = "SMPlayer ${SMPLAYER_VERSION}"). uninst.exe. Also Defender PUA detection.

## Verification notes

- Verified by opening or downloading: the OSR and MSFN KernelEx lists, the SF RSS and the project's MD5SUMS.txt/README.txt, the portable listing and its Readme.txt, Portable_Edition.txt, mplayer\README.txt, licenses and the QtCore4.dll version (extracted with host 7-Zip, not run). Also the mplayer.exe version string (read as bytes, not executed), the SMPlayer source Changelog and setup/smplayer.nsi, the mplayerwin RSS and SHA256SUMS, and NVD.
- Not verified: running on 98 with KernelEx 4.5.2 (no VM interaction); 0.6.x on stock 98.
