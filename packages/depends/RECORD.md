# Dependency Walker 2.2 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Dependency Walker (depends.exe), by Steve P. Miller; copyright Microsoft Corporation
- Version: 2.2.6000 (x86 build; files in the zip dated 2006-10-29)
- License: Freeware with a no-profit, no-bundling condition. No license file in the zip.
- Recommendation: list as `Availability: external`, downloaded from www.dependencywalker.com over plain HTTP (tested, works). Do not host it: see License.

## Windows 9x support evidence

- https://www.dependencywalker.com/ (opened, raw HTML downloaded with curl):
  "Dependency Walker runs on Windows 95, 98, Me, NT, 2000, XP, 2003, Vista, 7, and 8."
  Download link text: "Download Version 2.2 .6000 for x86 (Windows 95 / 98 / Me / NT / 2000 / XP / 2003 / Vista / 7 / 8) [610k]"
- 2.2.6000 is the only and last 2.2 build on the site; nothing newer exists. No KernelEx needed.
- depends.exe PE header: subsystem version 4.0 (consistent with 95/NT4). Version resource: FileVersion 2.2.6000, "Dependency Walker for Win32 (x86)".
- The help (depends.chm, faq.htm) notes that some profiling features are limited on 9x (e.g. modules above 0x80000000 on 95/98/Me are shared and cannot be hooked). Static dependency viewing is unaffected.
- Not tested on 95/98/ME (no VM interaction).

## Download

- Page: https://www.dependencywalker.com/
- URL: https://www.dependencywalker.com/depends22_x86.zip (also served over plain HTTP: http://www.dependencywalker.com/depends22_x86.zip)
- File: depends22_x86.zip, 610,769 bytes (server Last-Modified 2024-06-25, ETag "17d845793bc7da1:0")
- SHA-256: 03d73abba0e856c81ba994505373fdb94a13b84eb29e6c268be1bf21b7417ca3
- MD5: 675ca981ddf557eb7d4550624157dbe5
- Published checksum: none published by the site. Not compared.
- Authenticode: depends.exe is not signed.
- Other builds on the page (not downloaded): x64 and IA64 2.2.6000; 2.0 for Alpha/AXP64; 1.0 for MIPS/PowerPC.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\depends -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

Exact terms, home page https://www.dependencywalker.com/ (opened 2026-09-29):

> "Dependency Walker is completely free to use. However, you may not profit from the distribution of it, nor may you bundle it with another product."

Also on that page: "Dependency Walker is part of several Microsoft products, such as Visual Studio, ... Platform SDK, Windows DDK, Windows SDK, and MSDN. ... This site was created in order to distribute the latest version of Dependency Walker for testing."

- The FAQ (https://www.dependencywalker.com/faq.html, opened) has no licensing terms; its "redistribute" text is about the user's own application files.
- Inside the zip: only depends.exe, depends.dll, depends.chm. The help file (extracted with 7-Zip, read, not run) has no license or redistribution text; the About topics just say it shows "the copyright". The exe's version resource: "Copyright (C) Microsoft Corporation. All rights reserved".

Analysis for Beacon:
- "not profit": Beacon is free. Backport Labs is a company, though; if it ever earns money (donations, ads, paid tiers) the hosting could be read as profiting from distribution. Uncertain.
- "not bundle it with another product": Beacon would list it as its own package, installed only on request, not inside another program. But a catalog of software served from one repository, published by a company, can reasonably be read as a product that includes it. The sentence gives no definition. Uncertain.
- Who grants it: the binary's copyright belongs to Microsoft Corporation. The grant is one sentence on the author's site, not a license from Microsoft. Whether it binds Microsoft is unknown.
- Conclusion: redistribution is not *certain* to be allowed, so the rule "certain to be legal" is not met. Recommend `Availability: external`. The publisher's own server still offers the file and serves it over plain HTTP/1.0 with no redirect:
  `curl.exe -sS -I --http1.0 http://www.dependencywalker.com/depends22_x86.zip` -> `HTTP/1.1 200 OK`, `Content-Length: 610769`, `Content-Type: application/x-zip-compressed`. (Same for http://dependencywalker.com/.)
- LICENSE.TXT here holds the quoted terms and the copyright line, for the client to show.
- No source code (closed freeware); no source obligation.

## Security

- NVD API 2.0 keyword searches "Dependency Walker" and "depends.exe": 0 results. A web search found no advisories either.
- Known security problems: 0 found. (It parses untrusted PE and .dwi files and, when profiling, runs the target program; that is by design.)

## Install behaviour

- Type: plain zip, no installer, no uninstaller, no registry entry in Add/Remove Programs.
- Layout (listed with .NET ZipFile, nothing extracted to run): flat, no folders:
  - depends.chm 164,468
  - depends.dll 9,216
  - depends.exe 817,664
- Beacon: `unzip {dir}` (default `{pf}\Dependency Walker`), no strip; Start Menu shortcut to `{dir}\depends.exe`; uninstall `files`.
- Notes: depends.chm needs HTML Help (hh.exe), which is in IE 4.01 or later / 98; stock 95 without IE4+ may not open the help. depends.exe itself can add a "View Dependencies" Explorer context-menu entry when the user enables it in Options (registry, not recorded by Beacon). Installed size about 1 MB.

## Verification notes

- Verified by opening/downloading: home page and FAQ (raw HTML), the zip (hashed, listed), depends.chm (extracted with 7-Zip and searched), depends.exe version resource and PE header (read as data, not run), NVD API, the plain-HTTP HEAD test.
- Not verified: running on 95/98/ME; any statement from Microsoft about redistribution; whether a published checksum exists anywhere (none found).
