# Servant Salamander 1.52 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Servant Salamander (Petr Solin; later ALTAP, now Altap Salamander)
- Version: 1.52 (5/27/1998), English
- License: freeware with a permissive license ("Permission to use, copy, and distribute ... without fee or royalty")
- Availability: hosted is allowed by the license. The publisher still serves it, but only over FTP, which Beacon cannot use.
- Recommendation: 1.52 (freeware, redistributable). Servant Salamander 2.0 (2001) also runs on 95/98/ME and is on the
  same FTP server, but it is a 30-day shareware evaluation whose registration can no longer be bought (not packaged;
  see "Other versions").

## Windows 9x support evidence

- CHANGES.TXT inside salam152.zip: "Version 1.51: (3/15/1998) -command line parameters didn't work under Win95",
  "Version 1.52: (5/27/1998) -the Drive Info dialog showed incorrect values for disks with size over 2 GB under NT".
- DOC\FAQ.HTM: "Servant Salamander is a native Win32 application"; it does not run on Win32s or NT 3.51.
- SALAMAND.EXE PE header: subsystem version 4.0 (runs on Windows 95/NT4 and later). Built 1998-05-24.
- Windows 98 and ME are not named in the 1.52 files (98 was released a month after 1.52). Not tested here.

## Download

- Official location: ftp://ftp.altap.cz/pub/altap/salamand/salam152.zip. The FTP index.txt (opened) says
  "salam152.zip 211773 05/27/1998 Servant Salamander 1.52, English". Altap's download page
  https://www.altap.cz/salamander/downloads/ links "Previous Versions" to ftp://ftp.altap.cz/pub/altap/salamand/.
- HTTP/HTTPS: none. http://ftp.altap.cz/pub/altap/salamand/salam152.zip redirects to www.altap.cz and ends in 404; the
  same path on https://ftp.altap.cz and https://www.altap.cz is 404. So Beacon can only get it from our server.
- File: salam152.zip, 211,773 bytes (downloaded twice over FTP, identical)
- SHA-256: a8cbff2e25b602e8ae06162e6b669ea5850cbcfc09550fd96e93bc88419c0949
- Published checksum: none.
- Authenticode: SALAMAND.EXE not signed.
- Other language builds on the same FTP folder: salcz152, saldu152, salge152, salit152, salru152, salsl152, salsp152 (.zip).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\servant-salamander -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- DOC\LICENSE.HTM inside the zip, "End User License Agreement for Servant Salamander. (c) 1997-98 Petr Solin."
  LICENSE.TXT is that text with the HTML markup removed.
- Quote: "Permission to use, copy, and distribute this software and its documentation for any purpose and without fee
  or royalty is hereby granted, provided that the full text of this license agreement appears on ALL copies of the
  software and documentation."
- Condition: the license text must accompany every copy (it is inside the unmodified zip, and Beacon shows LICENSE.TXT).
  "Without fee or royalty" is met because Beacon is free.
- Hosting the unmodified zip is allowed.

## Security

NVD: CVE-2007-3314 (peviewer.spl buffer overflow in Servant Salamander 2.0/2.5 Portable Executable Viewer plugin) and
CVE-2005-2856 (UNACEV2.DLL, used by several products) concern plugins; the 1.52 zip contains only SALAMAND.EXE and
documents, no plugins, so neither applies. No CVE found for 1.52.

## Install behaviour

- Plain zip, no installer. Layout: SALAMAND.EXE, SALAMAND.URL, CHANGES.TXT, SERVICES.HTM at the root and DOC\ with
  DESCRIPT.HTM, FAQ.HTM, LICENSE.HTM and three JPG images. No folder to strip.
- Beacon: unzip into {pf}\Servant Salamander, shortcut to SALAMAND.EXE, uninstall by removing its files. Where 1.52
  stores its settings (registry or INI) was not verified; they would remain after removal.

## Other versions

- Servant Salamander 2.0 (salen200.exe, 1,361,121 bytes, 02/28/2001; ftp only): readme "requires Windows 95, Windows 98,
  Windows ME, Windows NT 4.0, Windows 2000 or later". License: 30-day evaluation; "The evaluation (unregistered) version
  of the Software, may be freely distributed ... provided the distribution package is not modified. You may not charge
  any fee". Registration of 2.0 is no longer sold (Altap now offers 4.0 as freeware, Windows 7+). Affected by CVE-2007-3314.
- Altap Salamander 2.54 (as254.exe, 2010): its self-extractor has PE subsystem version 5.0, so it does not start on 9x.

## Verification notes

- Opened: Altap download page, FTP listing and index.txt, the zip contents (LICENSE.HTM, FAQ.HTM, CHANGES.TXT,
  DESCRIPT.HTM), the 2.0 readme and license, the 2.54 PE header, NVD keyword search.
- Not verified: running on Windows 98/ME; settings location.
