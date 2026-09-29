# Neutron 1.07 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Neutron (Robin Keir), Internet Time protocol (RFC 868) clock synchronizer
- Version: 1.07 (readme: "Version 1.07 - June 23rd 2007"; the web page says "Updated June 23rd 2008" and the zip's Last-Modified is 2008-06-23, so the readme year looks like a typo)
- License: Freeware, no redistribution grant -> Availability: external
- Recommendation: 1.07, the only version the author serves and the last one released.

## Windows 9x support evidence

- The author does not state supported systems. https://keir.net/neutron.html (opened) and readme.txt (opened) mention only a Vista warning added in 1.07.
- Technical evidence (Neutron.exe was extracted to a temp folder and its PE header read; it was not run): i386, OS version 4.0, subsystem version 4.0 (GUI). It imports only KERNEL32, USER32, GDI32 and WSOCK32, all ANSI (...A) functions, with nothing NT-only in the import names. That is the profile of a program that runs on Windows 95/98/ME.
- The MSFN Windows 98SE software list (research\msfn-list.csv) lists Neutron as freeware for 98SE ("7KB Atomic Time Synchronisation").
- Not tested on 95/98/ME (no VM interaction).

## Download

- Page: https://keir.net/neutron.html ("Download Neutron 1.07 ZIP (7K)", "Updated June 23rd 2008")
- URL: https://keir.net/download/neutron.zip. http://keir.net/download/neutron.zip answers 301 to the https address (also with --http1.0), so plain HTTP alone is not enough; Beacon's own TLS is needed, or the redirect must be followed.
- File: neutron.zip, 6,765 bytes, Last-Modified Mon, 23 Jun 2008 17:48:49 GMT
- SHA-256: 9a9ae494fe176d49abf2b764c00ffaa0d9a3b4ed9b270d0f30b5d337264b46a2
- MD5: 15a9dd1a28ff316480d2fe60ad7f8cb2
- Published checksum: none published.
- Authenticode: Neutron.exe is not signed.
- Contents: Neutron.exe (10,240 bytes, 2008-02-19), Neutron.ini (581, server list and options), readme.txt (3,476).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\neutron -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats". The extracted files in a temp folder: also no threats.

## License

- readme.txt: "This software was written by Robin Keir and is distributed as freeware. I take no responsibility for any damage or problems caused by using it but I do welcome comments and suggestions."
- No statement allows or forbids redistribution. Because permission is not clear, Beacon does not host it and lists it as external (keir.net).
- LICENSE.TXT holds that statement.

## Security

- NVD API keyword searches "keir.net" and "Robin Keir": 0 results. ("Neutron" alone matches the unrelated OpenStack Neutron.) No known CVEs.
- The Time protocol is unauthenticated; a network attacker could set a wrong time. It sets the clock only.

## Install behaviour

- Plain zip, no installer. Layout: three files at the root, no folders.
- Beacon: `Install: unzip {pf}\Neutron`, shortcut to `{dir}\Neutron.exe`, `Uninstall: files`.
- Settings are kept in Neutron.ini beside the exe (GetPrivateProfileString/WritePrivateProfileString imports), so the program folder must be writable (always the case on 9x).
- No Add/Remove Programs entry.

## Verification notes

- Verified by opening or downloading: keir.net/neutron.html, keir.net/software.html, neutron.zip and its readme.txt/Neutron.ini, PE header of Neutron.exe, NVD API.
- Not verified: an explicit 9x statement from the author; that the listed time servers still answer on UDP 37.
