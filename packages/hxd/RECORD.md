# HxD 1.7.7.0 - Beacon 98 record

- Date checked: 2026-09-29
- Package: HxD Hex Editor (Maël Hörz, mh-nexus)
- Version: 1.7.7.0 (2009-04-03)
- License: Freeware (HxD License, own terms). Redistribution of the unmodified package allowed.
- Recommendation: 1.7.7.0, the last 1.x release. 2.0.0.0 (2018) is a Unicode rewrite and the current 2.5.0.0 lists Windows XP or later. Host the English **portable** zip (HxDenu.zip) and install it with `unzip`; the installable edition is a zip that contains setup.exe, which the catalog format cannot run directly (see Install behaviour).

## Windows 9x support evidence

- https://mh-nexus.de/en/hxd/ (opened 2026-09-29), second version block:
  "Version 1.7.7.0 (April 3, 2009) ... OS: Windows 95, 98, ME, NT 4, 2000, XP, 2003, Vista, or 7".
  The current version block: "2.5.0.0 (February 11, 2021) ... OS: Windows XP, 2003, Vista, 7, 8 or 10".
- Same page, features: "RAW reading and writing of disks and drives for Win9x, WinNT and higher".
- https://mh-nexus.de/en/hxd/changelog.php (opened): 9x-specific fixes in 1.7.x, e.g. "Some functions not supported by Windows 95 prevented HxD from running under Windows 95." (1.7.6.5 block, just before 1.7.6.4), "Fix: Windows error message when writing to a disk under Windows 98". 2.0.0.0 (May 24, 2018): "Fully Unicode based GUI and program code" (no explicit statement that it drops 9x; the page's OS line for 2.x says XP or later).
- readme.txt inside HxDenu.zip: "Disk-Editor: RAW reading and writing of disks and drives (WinNT and Win9x)".
- Windows 95 and ME: listed by name on the product page. No KernelEx needed. Not tested in a VM.

## Download

- Download page: https://mh-nexus.de/en/downloads.php?product=HxD (lists only 1.7.7.0, installable and portable, 21 languages)
- Recommended file (portable, English): https://mh-nexus.de/downloads/HxDenu.zip
  - HxDenu.zip, 807,089 bytes
  - SHA-256: ec8ab9522eefd2db19a18203e4195430a12c0c9e49b1e15cf195cee385da0d0c
  - Published: SHA-1 94e57a52e4d3eca6576bc15a99e884b6cdd5b03a, SHA-512 65be4f09...8af097 (on the download page): both MATCH.
- Also downloaded (installable, English): https://mh-nexus.de/downloads/HxDSetupENU.zip
  - HxDSetupENU.zip, 872,029 bytes (server Last-Modified 2010-05-11)
  - SHA-256: ea6ea4d4cc90f891915856b0393f99f275c0b6bb2a9e75a6b262117a18a2a469
  - Published: SHA-1 e2c3c761f2d52b754a82709c1b47c5efe9e06417, SHA-512 b1a5273a...3601d35: both MATCH.
  - Contains one entry, setup.exe (897,664 bytes, 2009-04-03); version resource "HxD Hex Editor Setup", "This installation was built with Inno Setup", Inno Setup data 5.2.3.
- Authenticode: not signed (setup.exe checked).
- Plain HTTP: `http://mh-nexus.de/downloads/HxDSetupENU.zip` answers 301 to HTTPS, so an `external` listing would not work on 98. Hosting is allowed anyway.
- The installer and portable zips are served by the author's own site; the Internet Archive is not needed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\hxd -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.TXT here is license.txt from HxDenu.zip (1.7.7.0, "Copyright© 2002-2009"), unchanged (1,692 bytes, CR LF, Windows-1252).
- 1.7.7.0 license, "Right of use/Distribution":
  "Permission is granted to anyone to use this Software for any purpose, including commercial applications, and to redistribute it, provided that the warranty disclaimer is accepted and the following conditions are met:
  1. All redistributions must keep the original package intact. No file may be removed or modified. Especially you must retain all copyright notices that are currently in place, and this license without modification.
  2. The origin of this Software must not be misrepresented; you must not claim that you wrote the original Software.
  3. You may distribute this Software and charge a distribution fee, but you must not represent in any way that you are selling the Software itself."
- The current web license (https://mh-nexus.de/en/hxd/license.php, "Copyright© 2002-2020") has the same conditions 1 and 2, forbids charging "the user for the Software itself", forbids "wrapper installers that have ads or install adware / spyware", and says "If you want to bundle HxD with other commerical /payed products, please contact me." Short version on the same page: "Distributing it as part of magazine addon CDs / DVDs / other media or putting it on download portals or private websites is allowed and welcome."
- Conclusion: hosting is allowed. Conditions: host the original zip unmodified (all files, including license.txt), free of charge, no ad/wrapper installer, do not claim authorship. Beacon meets these. Not open source; no source to offer.
- Note: batch2.md said "redistribution allowed if free and unmodified (bundling with commercial products needs permission)". Correct for the current web license; the 1.7.7.0 license is even more permissive (allows a distribution fee).

## Security

- NVD API 2.0: keyword searches "HxD hex", "mh-nexus" and "HxD" returned no HxD CVEs (the two "HxD" hits are Microsoft hxds.dll issues). NVD has a CPE `cpe:2.3:a:mh-nexus:hxd_hex_editor_version:1.7.7.0`, but a cpeName query returns 0 CVEs.
- Known security problems: 0 found. No vendor advisories found. (A web search found nothing either.)
- General note: a hex/disk/RAM editor can write raw disks by design; that is not a vulnerability.

## Install behaviour

- Portable zip (recommended): four files in the zip root, no folders: HxD.exe (1,681,920), changelog.txt, license.txt, readme.txt.
  Beacon: `unzip {pf}\HxD` (no strip), Start Menu shortcut to `{dir}\HxD.exe`, uninstall `files`. HxD stores its settings in the registry (not verified for the portable 1.7.7.0 build); Beacon's `files` uninstall will leave those.
- Installable edition: Inno Setup 5.2.3 inside a zip. Standard Inno silent switches `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART`. Default folder and Add/Remove Programs name: unknown (the Inno script is not published and the setup data is compressed; a third-party page title suggests "HxD Hex Editor version 1.7.7.0", unverified). The catalog's `inno` kind runs `{file1}` directly, and `{file1}` would be the zip, so this edition cannot be used without a format change (for example an "unzip then run" kind). Hosting setup.exe on its own would break the license's "keep the original package intact" condition.

## Verification notes

- Opened/downloaded: the HxD product page, license page, change log page, both download pages (the 1.x one gives the SHA-1/SHA-512 values), HxDenu.zip (read license.txt, readme.txt, changelog.txt without running anything), HxDSetupENU.zip (listed; setup.exe version resource and strings read, not run), NVD API.
- Not verified: running on 95/98/ME; where the portable build stores settings; the installer's default folder and Add/Remove name.
