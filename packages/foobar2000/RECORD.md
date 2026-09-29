# foobar2000 0.8.3 - Beacon 98 record

- Date checked: 2026-09-29
- Package: foobar2000 audio player (Peter Pawlowski), closed-source freeware
- Version: 0.8.3 (installer files dated up to 2004-09-12)
- License: foobar2000 0.8.3 license (BSD-like, binary-only), plus LGPL components
- Status: **HOLD, do not publish yet.** The license allows redistributing the unmodified installer, but the installer contains modified LGPL libraries whose source we cannot currently obtain, and "external" is not possible because the publisher only serves HTTPS.

## Windows 9x support evidence

- https://www.foobar2000.org/old-pc (opened), "Legacy hardware support": "Windows 95/98/ME supported by foobar2000 v0.8.3 and older." (Also: "Windows 2000 supported by foobar2000 v0.9.4.5 and older.")
- 0.8.3 is therefore the last version for 95/98/ME. No KernelEx needed.

## Download

- Official old-versions page https://www.foobar2000.org/old (opened) links:
  - https://www.foobar2000.org/downloads/foobar2000_0.8.3.exe - 1,325,374 bytes, SHA-256 e056c9cece879c15de58b49a10883dde4cb21a771bc7f0875cd6295c1558d8e9
  - https://www.foobar2000.org/downloads/foobar2000_0.8.3_special.exe ("v0.8.3 special", more components) - 2,482,065 bytes, SHA-256 d09f37d592aa9d04cf5bc673d44396a6b5d85a31f02406f6cf4b1e446264e3dc
- Published checksum: none.
- Both files are in this folder for reference only.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\foobar2000 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- `license.txt` inside foobar2000_0.8.3.exe (listed and extracted with 7-Zip; installer not run), saved as LICENSE.TXT:
  "Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met: Redistributions must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation ... Neither the name of the author nor the names of its contributors may be used to endorse or promote products ... Redistribution of modified binaries allowed only with prior written permission of the author."
- Current https://www.foobar2000.org/license (opened): "Only unmodified installers can be redistributed; redistribution of foobar2000 binaries in any other form is not permitted." The 0.8.3 text is, if anything, looser (it allows unmodified binaries in any form). Both allow redistributing the unmodified 0.8.3 installer free of charge, so the author's own terms are met.
- The problem: the same license.txt lists LGPL parts compiled into the installer's components:
  - "mpglib ... Distributed under terms of LGPL, modifed mpglib source available with foobar2000 SDK."
  - "Musepack decoding library ... LGPL, modified sources available with foobar2000 SDK."
  - "akrip.dll ... LGPL, modified sources available with foobar2000 SDK."
  - "SSRC and SuperEQ libraries ... LGPL, modified sources available with foobar2000 SDK."
  - "7-Zip library ... Distributed under terms of LGPL."
  When we distribute these object files, LGPL 2.1 s.6 requires us to supply or offer the corresponding source. The "foobar2000 SDK" of 2004 is not on foobar2000.org any more (the SDK page lists SDKs from 2011-03-11 onward). The Internet Archive was offline today, so I could not look for a 0.8.3-era SDK there.
- Also bundled: bass.dll (BASS 2.0, Ian Luck, proprietary freeware), Monkey's Audio (its own license), JNetLib, zlib, unRAR, FLAC, WavPack. BASS and Monkey's Audio come under the author's installer; their own redistribution terms were not checked.

## "External" option

- `curl.exe -sS -I --http1.0 http://www.foobar2000.org/downloads/foobar2000_0.8.3.exe` returns `301 Moved Permanently`, `Location: https://www.foobar2000.org/downloads/foobar2000_0.8.3.exe`. Same for http://foobar2000.org/. A Windows 98 client cannot follow it, so external is not possible.

## Security

- NVD keyword "foobar2000": 0 results. The 0.8.3 decoders (mpglib, FLAC, Monkey's Audio, WavPack, unRAR, 7-Zip from 2004) certainly have later-fixed bugs, but no CVE is recorded against this version.

## Install behaviour

- Installer type: NSIS 2.0 (7-Zip: "NSIS-2.00", LZMA solid). Contains foobar2000.exe, utf8api.dll, fooassoc.exe, bass.dll, components\*.dll (input_std, flac, ape, wavpack, speex, mod, cdda, diskwriter, rgscan, albumlist, masstag, unpack, id3v2, dsp_extra, clienc, ...), icons, uninstall.exe.
- Silent: standard NSIS `/S` (not tested). Add/Remove Programs name: unknown (the NSIS script is not published).

## What would unblock it

1. Find the foobar2000 0.8.x SDK (with the modified LGPL sources) once the Internet Archive is back, check that it matches 0.8.3, and host it in src\; or ask the author for the sources / permission.
2. Check the BASS 2.0 and Monkey's Audio terms.
Then publish with `Install: nsis`, `Systems: 95, 98, ME`, `License: Freeware`.

## Verification notes

- Opened/downloaded: /old, /old-pc, /license, /SDK pages; both installers (listed with 7-Zip, license.txt extracted, not run); HTTP header test; NVD.
