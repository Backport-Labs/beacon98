# VLC media player 0.8.6i - Beacon 98 pilot record

- Date checked: 2026-09-28
- Package: VLC media player (VideoLAN)
- Version: 0.8.6i (Windows build respun as "0.8.6i-bis"; file name on the server is vlc-0.8.6i-win32.exe, published checksums name it vlc-0.8.6i-bis-win32.exe). Released August 2008.
- Recommendation: 0.8.6i. The 0.9.x series is not an option (requires Windows 2000).

## Windows 9x support evidence

- VLC NEWS, "Changes between 0.8.6i and 0.9.0" (https://github.com/videolan/vlc/blob/3.0.21/NEWS, verified by opening):
  "This release will need Windows 2000 and Mac OS X 10.4 (Tiger), or more recent to work correctly". So 0.9.0+ drops 9x.
- The same NEWS, "Changes between 0.8.5 and 0.8.6": "Windows 9x/ME users: - Please note that these versions of Windows are not officially supported - Unicode support for Windows 9x/ME applications is available through the Microsoft Layer for Unicode ... Download the MSLU package (unicows) and extract the content into the folder C:\Windows\System".
  IMPORTANT: VideoLAN states 9x was not *officially* supported from 0.8.6 on; it works with unicows.dll (MSLU).
- VideoLAN wiki WindowsFAQ-1.0.x (https://wiki.videolan.org/WindowsFAQ-1.0.x/, fetched): "Latest VLC (1.0.0) doesn't work with Windows Me/98/98se/95/NT. This is by design. You need at least Windows 2000 to run latest VLC. For earlier Windows release, use VLC 0.8.6i".
- VLC user docs OS compatibility matrix (https://docs.videolan.me/vlc-user/desktop/3.0/en/reference/os_compatibility.html, fetched): Windows 95/98/ME "YES" for 0.8.6, "NO" for all later versions.
- 0.8.6i is the last 0.8.6.x release: NEWS has no 0.8.6j, and https://download.videolan.org/pub/videolan/vlc/ lists 0.8.6 .. 0.8.6i then 0.9.0.
- Windows 95 separately: the compatibility matrix groups 95/98/ME together; no separate statement. INSTALL.win32 in the 0.8.6i source is titled "INSTALL file for the Windows9x/Me/NT4/2k/XP version". Win95 behaviour not tested.
- Runtime requirement on 9x: unicows.dll (Microsoft Layer for Unicode) is needed for Unicode support. It is a Microsoft component; do NOT host it without a verified redistribution license.

## Download

- URL: https://download.videolan.org/pub/videolan/vlc/0.8.6i/win32/vlc-0.8.6i-win32.exe
- File: vlc-0.8.6i-win32.exe, 9,398,688 bytes
- SHA-256: afd20c08ebf2f73e0d1ad6a341699207728eacaa57ce8bb797fb4abb5aaf3166
- Published checksums (downloaded alongside):
  - .md5: c469d3fe86042f41e4a4619db7bfa153 - MATCH
  - .sha1: e5609685bc980ac2ebdd99e0d4c818482d98b48a - MATCH
  - .asc: GPG "Good signature" from "VideoLAN Release Signing Key (2008)", DSA-1024 key 8B085231D0383537, fingerprint 88C8 6A57 D2CB 49A7 65BD BA35 8B08 5231 D038 3537, signed 2008-08-22. Key fetched from https://download.videolan.org/pub/keys/8B085231D0383537.asc; key expired 2009-01-01 (normal for an archived release; DSA-1024/SHA-1 is weak by today's standards).
- Alternatives in the same folder (not downloaded): vlc-0.8.6i-win32.zip and vlc-0.8.6i-win32.7z (no installer), each with .md5/.sha1/.asc.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\pilot\vlc -DisableRemediation` on 2026-09-28
(engine 4.18.26080.4, signatures 1.459.442.0): "found no threats".

## License

- VLC 0.8.6i: GNU GPL version 2 (or later, per source headers). LICENSE.TXT here is COPYING.txt extracted from the installer itself (GPL v2, June 1991).
- Redistribution of the unmodified binary: allowed under GPL-2.0 s.3, provided the license text accompanies it and the complete corresponding source is provided or offered (written offer valid 3 years, or source from the same place).
- Bundled third-party code, statically linked into plugins (verified in contrib list extras/contrib/src/packages.mak and by strings in the shipped DLLs):
  - FFmpeg (libffmpeg_plugin.dll) built with LAME 3.97 (MP3 encoder) and FAAC 1.24 (AAC encoder) - strings "libfaac version", "FAAC - Freeware Advanced Audio Cod...", "LAME" present in the DLL. FAAC is widely regarded as containing non-free ISO reference code (FFmpeg later required --enable-nonfree for libfaac; Debian treats it as non-free) - from general knowledge, NOT verified here. This is a potential GPL-compatibility problem in VideoLAN's own binary and needs legal review.
  - libdvdcss 1.2.9 (statically in libdvdread/libdvdnav plugins; strings "dvdcss version %s", DVDCSS_METHOD) - GPL, but CSS circumvention is legally restricted in some countries (e.g. US DMCA).
  - x264 (2005 snapshot), liba52 0.7.4, faad2 2.6.1, libdts, libmpeg2, twolame 0.3.9 - GPL/LGPL.
  - GnuTLS 2.2.5 / libgcrypt (LGPL), wxWidgets 2.6.4 (wxWindows licence), live555, Ogg/Vorbis/Theora/FLAC/Speex (BSD-style), freetype, zlib, libpng.
  - Patent-encumbered formats implemented: MPEG-1/2 video, MP3 (decode and LAME encode), AAC (FAAD decode, FAAC encode), H.264 (x264 encode + FFmpeg decode), AC-3 (a52), DTS, WMA/WMV via FFmpeg. Many of these patents have expired by 2026 (MPEG-2, MP3, AC-3) but AAC/H.264 pools should be checked by counsel.
  - libdmo_plugin / librealaudio load Windows or Real codecs present on the system; they are not bundled.

## Matching source

- URL: https://download.videolan.org/pub/videolan/vlc/0.8.6i/vlc-0.8.6i.tar.bz2
- File: vlc-0.8.6i.tar.bz2, 11,786,172 bytes
- SHA-256: a866768f7dd8254c62e059327094073800ed968214b5b35e2682eb81f448214f
- Published .md5 3c90520c9f22a68d287458d5a8af989e - MATCH; .sha1 4c6f45dffe3a8309ce201897040dc1f82b9cde99 - MATCH; .asc Good signature from the same 2008 key (signed 2008-07-08).
- GAP: this is VLC's own source only. "Complete corresponding source" for the Windows binary also includes the contrib libraries listed above (FFmpeg snapshot, x264 snapshot, libdvdcss, etc.). Their exact versions/snapshots are in extras/contrib/src/packages.mak but the exact prebuilt Win32 contrib package used for the 0.8.6i-bis build was not located. Must be resolved before hosting a GPL binary.

## Security

- VideoLAN security advisories (https://www.videolan.org/security/, each advisory page opened):
  - Explicitly covering 0.8.6i by version range (9): SA-0807 (0.8.6i and earlier; CVE-2008-3732, CVE-2008-3794 - never fixed in 0.8.6), SA-0810 (0.5.0-0.9.5; CVE-2008-5032, CVE-2008-5036), SA-0901 (0.5.0-1.0.1; MPA/AVI/ASF stack overflow), SA-1003 (0.5.0-1.0.5; CVE-2010-1441..1445), SA-1005 (DLL preloading, all up to 1.1.3; CVE-2010-3124), SA-1104 (XSPF, 0.8.5-1.1.9; CVE-2011-2194), SA-1106 (AVI, 0.5.0-1.1.10; CVE-2011-2588), SA-1201 (MMS stack overflow, all up to 2.0.1; CVE-2012-1775), SA-1202 (Real RTSP, all up to 2.0.1; CVE-2012-1776).
  - A further 11 advisories state "X and earlier" (SA-1006, 1007, 1101, 1102, 1107, 1203, 1301, 1302, 1501, 1601, 1901); some concern code not present in 0.8.6.
- NVD: 62 CVEs match cpe vlc_media_player:0.8.6i; 14 with CVSS >= 9.
- Worst: CVE-2008-3732 (TTA integer overflow, CVSS 9.3, names 0.8.6i specifically, no 0.8.6 fix), CVE-2012-1775 (MMS:// stack overflow, remote code execution, 9.3), CVE-2008-5032 (RealText/CUE stack overflow, 9.3).
- Bundled libraries (GnuTLS 2.2.5, FFmpeg 2008, libpng, freetype, zlib) carry their own large CVE backlogs, not counted here.
- Also installs a Mozilla/Netscape plugin (npvlc.dll) and ActiveX control (axvlc.dll) - these expose the above bugs to web content.

## Install behaviour

- Installer type: NSIS 2 (LZMA solid), confirmed by 7-Zip listing; script vlc.win32.nsi.in is in the source tarball.
- Silent install: `/S` is the generic NSIS switch (and `/D=path` for folder). VideoLAN does not document it for 0.8.6 and the script shows a language dialog (MUI_LANGDLL_DISPLAY); not tested.
- Default folder: `$PROGRAMFILES\VideoLAN\VLC`; install dir stored in HKLM `Software\VideoLAN\VLC`.
- Uninstaller: yes. `$INSTDIR\uninstall.exe`, registered at HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\VLC media player` (DisplayName, UninstallString, DisplayVersion, Publisher). Uses an uninstall.log.
- Side effects: file associations (HKCR), "Play with VLC" context-menu entries, optional Mozilla plugin and ActiveX registration, all-users shortcuts.

## Verification notes

- Verified by opening: NEWS (from videolan/vlc GitHub mirror), wiki FAQ, docs compatibility matrix, archive listings, checksums, GPG signatures, advisory pages, NVD API, installer contents and DLL strings.
- Not verified: Windows 95 operation; FAAC licence status (general knowledge); the exact contrib source bundle for the Win32 build.
