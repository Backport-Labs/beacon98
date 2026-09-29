# LAME 3.99.5 - Beacon 98 record

- Date checked: 2026-09-29
- Package: LAME MP3 encoder
- Version wanted: 3.99.5 (2012-02-28), with a Windows build that runs on 98
- License: GNU LGPL (version 2 "Library GPL" text in COPYING). MP3 patents have expired (2017), so no patent restriction remains.
- Status: **BLOCKED - no 98-capable 3.99.5 Windows build can be downloaded today.** The LGPL source is downloaded and verified.

## Why there is no binary

- The LAME project publishes only source (https://lame.sourceforge.io/download.php, opened, links only to the SourceForge file area). Its links page points to RareWares for Windows binaries.
- RareWares (https://www.rarewares.org/mp3-lame-bundle.php, opened) lists "LAME 3.99.5 for older Win32 OSs, 2012-12-05, Bundle compiled with VC6/Intel Compiler 9.1" linking https://www.rarewares.org/files/mp3/lame3.99.5_vc6.zip. That URL returns **404**, and the file is missing from the directory listing https://www.rarewares.org/files/mp3/.
- Every other LAME Windows build still on RareWares was downloaded to a temporary folder and inspected (not run):

| File | PE OS/subsystem | Blocking imports |
|---|---|---|
| lame3.100-20200409.zip (lame.exe, lame_enc.dll) | 5.1 | IsProcessorFeaturePresent, InitializeSListHead, GetModuleHandleExA/W, SetFilePointerEx... |
| lame3.100.1-win32.zip | 5.1 | same |
| lame3.100-libsndfile.zip (lame.exe) | 5.1 | same |
| lame-4.0-Win32.zip | 6.0 | same |
| libmp3lame-3.99.5x86.zip (DLL only) | 5.0 | none, but subsystem 5.0 |
| lamedll_MOD3.99.5.zip (lame_enc.dll, modified) | 5.0 | none, but subsystem 5.0 |
| lamedll_MOD3.99.3.zip | 5.1 | EncodePointer, DecodePointer, IsProcessorFeaturePresent |
| lamedropXPd3.x-3.99.5 (GUI front end) | 5.0 | - |
| lameACM-3.99.5.zip (ACM codec) | 5.0 | - |
| lameACM-3.98.2-vc6.zip (ACM codec 3.98.2) | 4.0 | none |
| lameexe3.97_MOD.zip (modified 3.97 lame.exe) | 4.0 | none |

  Windows 98 refuses PE files with subsystem version 5.0 or higher. The only 4.0 files are an ACM codec of 3.98.2 and a *modified* 3.97 command-line build, neither of which is an official or widely used 3.99.5 encoder.
- Other sources checked: lame.buanzo.org offers only Audacity libraries (libmp3lame 3.99.3 / 3.100), not lame.exe, and says nothing about 9x. The Internet Archive (to recover lame3.99.5_vc6.zip; allowed because LGPL permits sharing and the publisher's file is gone) returned "Temporarily Offline" / 429 today.
- Note: CDex 1.51 (also blocked) ships its own lame_enc.dll.

## Source (downloaded)

- URL: https://downloads.sourceforge.net/project/lame/lame/3.99/lame-3.99.5.tar.gz
- File: src/lame-3.99.5.tar.gz, 1,445,348 bytes
- SHA-256: 24346b4158e4af3bd9f2e194bb23eb473c75fb7377011523353196b19b9a23ff
- MD5 84835b313d4a8b68f5349816d33e07ce; SourceForge file RSS: MATCH.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\lame -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats" (source only).

## License

- LICENSE.TXT = `LICENSE` + `COPYING` from lame-3.99.5.tar.gz. LGPL: redistribution of binaries allowed with the corresponding source offered (we have it).

## Security

- NVD CPE cpe:2.3:a:lame_project:lame:3.99.5: 15 CVEs (e.g. CVE-2017-8419 signed-integer WAV/AIFF header handling, CVE-2017-9871/9872 mpglib layer 3 decoding, all CVSS2 6.8; CVE-2015-9099/9100/9101, CVE-2017-9412, CVE-2017-9869/9870 and others, CVSS2 4.3-5.5). All need a crafted input audio file; mostly crashes, some memory corruption in the mpglib decoder.

## What would unblock it

1. Recover `lame3.99.5_vc6.zip` from the Internet Archive when it is back (check it is the RareWares file: VC6/ICL 9.1 build, subsystem 4.0), or ask RareWares (John33) to restore it.
2. Or Backport Labs builds 3.99.5 from this source with a 98-capable compiler (then it is our own build and must be described as such).
