# FCEUX 2.1.5 (Win2000/Win98 build) - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: fceu (NES / Famicom emulator)
- Chosen: **FCEUX 2.1.5, the "Win2000/98" build** (fceux-2.1.5-win32-Win2000_Win98.zip, 2011-06-04)
- License: GPL-2.0-or-later; 7z.dll is 7-Zip 4.57 (LGPL-2.1-or-later + unRAR restriction); Lua 5.1 (MIT) is linked in
- Recommendation and why:
  - FCEUX is the continuation of FCE Ultra by the same SourceForge project (fceultra). Its official download page offers a separate build of 2.1.5 labelled "Win2000/98". That is the newest release with an official 98 build; 2.2.0 and later offer only the normal win32 build.
  - FCE Ultra 0.98.12 (the version batch2.md named from memory) is **not on the official hosts**: the SourceForge project has only "0.98.8 Win32" under Binaries and 0.98.10/0.98.15 sources and a 0.98.15 rerecording build under OldFiles. The old fceultra.sourceforge.net site now returns only a short stub. So 0.98.12 has no official download to take.
  - FCE Ultra 0.98.8 Win32 (2004) would be the fallback; not downloaded.

## Windows 9x support evidence

- https://fceux.com/web/download.html (opened via WebFetch), old-versions table, FCEUX 2.1.5 row: "Win32 Binary" `https://sourceforge.net/projects/fceultra/files/Binaries/2.1.5/fceux-2.1.5-win32.zip/download` and "Win2000/98" `http://sourceforge.net/projects/fceultra/files/Binaries/2.1.5/fceux-2.1.5-win32-Win2000_Win98.zip/download`. The 2.2.x rows have only "Win32 Binary".
- SourceForge folder Binaries/2.1.5 (opened via WebFetch): fceux-2.1.5-win32.zip (2011-06-22) and fceux-2.1.5-win32-Win2000_Win98.zip (2011-06-04).
- fceux.exe is UPX-packed; its import directory names ADVAPI32, AVIFIL32, COMCTL32, comdlg32, DDRAW, DINPUT, KERNEL32, ole32, OLEAUT32, SHELL32, USER32, WINMM, WINSPOOL.DRV, WS2_32 (all present on 98; WS2_32 is Winsock 2, which 98 has). The individual functions could not be checked without unpacking. Not run.
- Windows ME: not named; inferred from 98 support (same Win32 API level). Windows 95: not named, not claimed.
- The build difference is not documented in changelog.txt (the 2.1.5 section does not mention it). What exactly differs is unknown.
- Not verified: running on 98/ME.

## Download

- URL: https://downloads.sourceforge.net/project/fceultra/Binaries/2.1.5/fceux-2.1.5-win32-Win2000_Win98.zip
- File: fceux-2.1.5-win32-Win2000_Win98.zip, 1,686,703 bytes
- SHA-256: 8ac5fe8ad76a3e475d99bc7815c0bb8f667a60e6ae0b0f5e531cf995fcf7382f
- MD5: 14e4963c662ba54535026909355d4119. SourceForge RSS for /Binaries/2.1.5 (WebFetch) lists 14e4963c662ba54535026909355d4119, 1,686,703 bytes: MATCH (SourceForge-generated).
- Alternative not taken: fceux-2.1.5-win32.zip (MD5 3a6cd62c89b26a7bb5366a0c724d2601 per SF), the XP build.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\fceu -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- Source headers (e.g. src/fceu.cpp): "FCE Ultra - NES/Famicom Emulator ... Copyright (C) 2003 Xodnizel ... GNU General Public License ... either version 2 of the License, or (at your option) any later version." COPYING in the source is the GPL 2.
- **The binary zip contains no license text at all.** Beacon's LICENSE.TXT fills that gap.
- 7z.dll: version resource "7z Standalone Plugin" 4.57, (c) 1999-2007 Igor Pavlov. It is UPX-packed; its PE link timestamp (2007-12-06 08:37:31 UTC) equals that of 7z.dll in the official 7z457.exe, so it is the official 4.57 build compressed with UPX (byte identity after unpacking not checked). 7-Zip 4.57 License.txt: LGPL 2.1 or later, plus unRAR restriction for the RAR code.
- Lua 5.1: MIT (src/lua/COPYRIGHT), statically linked (lua51.lib in the source; no lua51.dll in the zip).
- zlib: its source is in the FCEUX archive (src/drivers/win/zlib).
- LICENSE.TXT here: FCEUX notice, GPL 2 (COPYING), Lua COPYRIGHT, 7-Zip 4.57 License.txt, LGPL 2.1 (copying.txt) and unRarLicense.txt.
- Redistribution of the unmodified zip is allowed with the license texts and the corresponding sources, which we host.

## Matching source (hosted)

- FCEUX: https://downloads.sourceforge.net/project/fceultra/Source%20Code/2.1.5%20src/fceux-2.1.5.src.tar.bz2
  - src\fceux-2.1.5.src.tar.bz2, 7,322,199 bytes, SHA-256 ee6b1ee6a0347e325032f6655a5caa289e2b0458f7fccddccd5137f1cd63bf9f
  - MD5 e8b20e62bbbb061b1a59d51b47c827bd, SF RSS: MATCH.
  - Contains only headers and a 7z.dll binary for 7-Zip (src/drivers/win/7zip), not 7-Zip's source; that is why the next file is needed.
- 7-Zip 4.57 (for 7z.dll): https://downloads.sourceforge.net/project/sevenzip/7-Zip/4.57/7z457.tar.bz2
  - src\7z457.tar.bz2, 620,119 bytes, SHA-256 09fc3719fbe373edd1c62bf8e48c1f98caea4522c26d0244aa40d2058ee2fd7e
  - MD5 a504b4174d3960ef93539986b5a092fa, SF RSS for /7-Zip/4.57: MATCH.

## ROMs and other bundled data

Zip listing (.NET ZipFile), no top folder: `fceux.exe`, `fceux.chm` (help), `7z.dll`, `auxlib.lua`, `palettes\` (7 x 192-byte .pal colour tables), `luaScripts\` (47 Lua scripts and 3 text docs, 1,953 KB unpacked in all).
- **No ROMs, no FDS BIOS (disksys.rom), no other BIOS.** Nothing questionable.
- The Lua scripts are community-written helpers for specific commercial games (SMB, Punch-Out, Gradius...); they contain no game data. Only one has a notice: Rewinder.lua mentions that "'Braid' is copyright Jonathan Blow", a reference only. Their license is not stated individually; they ship as part of the GPL FCEUX distribution. Palettes are colour tables. Fine.

## Security

- NVD keyword searches "fceux" and "fce ultra" (API 2.0, 2026-09-29): 1 result, CVE-2024-32258 (path traversal in the network server of FCEUX 2.7.0). NVD names only 2.7.0, and the netplay server it describes belongs to the much later Qt/SDL code base, so it is not believed to apply to the 2.1.5 Windows build (not verified in the source). 0 known CVEs for 2.1.5.
- Bundled 7z.dll 4.57 (used to open ROMs inside archives) predates many 7-Zip fixes, e.g. CVE-2008-6536 ("unspecified vulnerability in 7-Zip before 4.65" via crafted archives); later RAR/ZIP decoder CVEs may apply too (not checked one by one).
- Lua scripts run with full access to files (Lua io/os libraries). A script is a program; only run trusted ones.
- Summary: 0 CVEs in FCEUX 2.1.5 itself; the realistic risk is a crafted archive handled by the old 7z.dll. A short Warning is proposed.

## Install behaviour

- Plain zip, files at the root. About 1,953 KB unpacked.
- Beacon: `unzip {dir}` (no strip), shortcut to `{dir}\fceux.exe`, uninstall `files`. FCEUX writes fceux.cfg and save/state folders into its own folder; Beacon does not remove them.
- The help file fceux.chm needs HTML Help (hh.exe, which comes with Internet Explorer 4 or later; 98 has it).
- No installer, no Add/Remove Programs entry.

## Verification notes

- Verified by opening/downloading: fceux.com download page and SourceForge folder listings/RSS (WebFetch), the zip and both source archives, source headers, COPYING, changelog.txt, Lua COPYRIGHT, 7-Zip 4.57 License, the 7z.dll in the official 7z457.exe (extracted with host 7-Zip to a temp folder, not run), NVD.
- Not verified: running on 98/ME; the exact difference between the Win2000/98 and normal build; byte identity of the UPX-packed 7z.dll with the official one.
