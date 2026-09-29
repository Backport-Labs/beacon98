# XMPlay 4.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: XMPlay (Un4seen Developments Ltd)
- Version: 4.1 (23/12/2025 per the history in xmplay.txt)
- License: freeware for non-commercial use ("XMPlay is free for non-commercial use.")
- Recommendation: external. 4.1 is the current release and the author still states Windows 95 support.

## Windows 9x support evidence

- https://www.un4seen.com/xmplay.html (downloaded and read): "XMPlay is an audio player for Windows (versions 95 to 11)".
- xmplay.txt inside xmplay41.zip (read): "XMPlay is an audio player for Windows (versions 95* to 11)" and
  "* Windows 95/98 require an MSIMG32.DLL update, which is available from the XMPlay website."
- The XMPlay page offers that update: https://www.un4seen.com/files/x/msimg32.dll, described as "Windows 95/98 alpha blending
  support ... msimg32.dll update taken from Windows Me. Place it in XMPlay's folder." Only needed for skins with alpha channels.
  It is a Microsoft file; Beacon does not download it (named in a Notice only).
- xmplay.exe imports WININET.dll and MSVCRT.dll (checked with a PE import listing; the exe is packed, so only a few imports are
  visible). Windows 98/ME ship both; a bare Windows 95 without Internet Explorer may lack WININET.DLL. Not tested (no VM use).
- Windows ME and 2000 are covered by "95 to 11". NT4 is not named, so it is left out.

## Download

- URL: https://www.un4seen.com/files/xmplay41.zip (linked as "Download" on xmplay.html). Also served over plain
  http://www.un4seen.com/files/xmplay41.zip (HTTP 200, same length, curl -I 2026-09-29).
- File: xmplay41.zip, 337,689 bytes
- SHA-256: f364d9490d722d1ff21b9a027d803cbf4d5489422b39b782580085bbc463dd5e
- Published checksum: none published.
- Authenticode: the zip cannot be signed; xmplay.exe inside is signed by "Un4seen Developments Ltd" (London, GB), status Valid.
- Note: the page's other link host xmplay.com/files/xmplay41.zip returned 404 on 2026-09-29.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\xmplay -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT holds the "Licence" section of xmplay.txt (4.1): "XMPlay is free for non-commercial use." plus the warranty disclaimer.
- Redistribution: the licence says nothing about redistribution, so it is not granted. Listed as `external`; Beacon only
  points to Un4seen's server. Beacon's users are home users, which matches "non-commercial use", but the Notice says so.

## Security

- NVD keyword search "xmplay" (2026-09-29): 2 CVEs, neither in 4.1's range:
  - CVE-2006-6063: M3U stack overflow in XMPlay 3.3.0.5 and earlier.
  - CVE-2018-19357: stack overflow via a crafted http:// URL in a .m3u file, XMPlay 3.8.3.
- Known problems in 4.1: none found.

## Install behaviour

- Plain zip, no installer ("No installation - UnZIP where you want and go!" on the page). Contents, flat at the root:
  xmplay.exe, xmplay.txt, xmp-cd.dll, xmp-wadsp.dll, xmp-waveform.dll.
- Beacon: `unzip {pf}\XMPlay`, Start Menu shortcut to xmplay.exe, `Uninstall: files`.
- XMPlay writes its settings to xmplay.ini in its own folder; file associations are optional and set by the user.

## Verification notes

- Verified by opening/downloading: xmplay.html, xmplay41.zip and its xmplay.txt, the signature of xmplay.exe, NVD.
- Not verified: running on 95/98/ME.
