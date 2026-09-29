# QuickView Pro 2.61 (DOS multimedia player) - Beacon 98 record

- Date checked: 2026-09-29
- Package: QuickView Pro for DOS, Wolfgang Hesseler (multimediaware.com)
- Version: 2.61 (files dated 2016-07-29; the site says "QuickView Pro 2.61 ... released 29 July 2016")
- License: shareware, 3-week evaluation; registration still sold (US$25 personal, US$50 commercial, per the register page)
- Availability: external recommended (see License); the license itself allows passing the unmodified archive along.

## Windows 9x support evidence

- https://www.multimediaware.com/qv/download.htm (opened): "QuickView Pro is a 32 bit protected mode program ...
  It will run under DOS 3.0 or better, or in a DOS shell under Windows 95/98/ME and OS/2."
- Same sentence in QV.TXT inside the zip, which adds: "The DOS support of Windows XP or later however is restricted so
  that QuickView will only run with limitations." and "Some sound cards like the ESS1868F do not work in a DOS session
  under Windows but only under pure DOS."
- It is a DOS program (DOS/32 Advanced extender), started in an MS-DOS window or in MS-DOS mode. Sound needs the
  BLASTER variable or an external driver from http://www.multimediaware.com/qv/snddrv/.

## Download

- Page: http://www.multimediaware.com/qv/download.htm ("Download QuickView Pro for DOS v2.61 (1195 Kb)")
- URL: http://www.multimediaware.com/qv/qvpro261.zip (200 over plain HTTP, no redirect) and
  https://www.multimediaware.com/qv/qvpro261.zip (200). Last-Modified Sat, 29 Apr 2023 22:21:53 GMT.
- The documentation's FTP site ftp://ftp.multimediaware.com/qv does not resolve any more.
- File: qvpro261.zip, 1,223,996 bytes
- SHA-256: e276a25bfc421e123dec29902444263cfb3deedb4bd1430424690346213bcfb5
- Published checksum: none. Authenticode: not applicable (DOS executable in a zip).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\quickview-pro -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT: the "Shareware ... Legal Stuff" section of QV.TXT and all of REGISTER.TXT, verbatim.
- Trial: "This program is Shareware. You may test this unregistered version for at most three weeks but after that you
  must register." The register page (http://www.multimediaware.com/qv/register/, updated 29 January 2026) lists as
  benefits of registering: "No shareware delay, No more nag screens, No time limits, Additional features". The
  unregistered version limits playlists and shuffle to 10 files and lacks some command-line options.
- Redistribution: "You are encouraged to share it with others. If you do so, please pass along the complete
  unmodified archive. All files must be included." and "License agreement for Shareware distributors: Shareware
  distributors may distribute this program if no files of the package are left out or modified."
- Why external anyway: QV.TXT says "This product uses parts of FFmpeg ... FFmpeg is available under the terms of the
  GNU Lesser General Public License. Source code of FFmpeg can be downloaded from http://ffmpeg.org or is available upon
  request." The FFmpeg version is not named, so we could not offer the matching source ourselves. The publisher still
  serves the file over plain HTTP, so external is the simple, safe choice. Hosting would be possible if the FFmpeg
  version were obtained from the author.

## Security

NVD keyword searches "QuickView Pro" and "multimediaware": 0 results. It includes FFmpeg, mpg123, libjpeg and Ogg
Vorbis code of unknown (pre-2016) versions; old FFmpeg decoders have many published flaws, so crafted media files
may be dangerous. Not verified per CVE.

## Install behaviour

- Plain zip, no installer, no folders: file_id.diz, qv.exe (1,215,396 bytes), qv.txt, qv.dok (German), changes.txt,
  register.txt, register.dok. QV.TXT: "Since there is no installation necessary, the uninstall can be done easily by
  deleting all files." It writes a config file next to QV.EXE when options are saved.
- Beacon: unzip into {pf}\QuickView, shortcut to qv.exe (opens in an MS-DOS window), uninstall by removing files.

## Verification notes

- Opened: index.html, download.htm, register page, the zip listing and its text files.
- Not verified: running it (DOS/Windows 98 not used), whether it runs well inside a Windows DOS box on a given sound card.
