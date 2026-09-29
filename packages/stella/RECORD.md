# Stella 3.6.1 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: Stella, Atari 2600 VCS emulator (Bradford W. Mott, Stephen Anthony and the Stella Team)
- Version: 3.6.1 (2012-03-30), Windows 98/2000 build (`_98_2k`)
- License: GPL-2.0-or-later (Stella); SDL.dll 1.2.14 is LGPL-2.1
- Recommendation: 3.6.1, the separate 98/2000 zip. 3.7 (2012-06-01) dropped the 98/ME/2000 builds, so 3.6.1 is the last. There is no second sensible choice (no KernelEx route is documented).

## Windows 9x support evidence

- Changes.txt (https://raw.githubusercontent.com/stella-emu/stella/master/Changes.txt, downloaded), entry "3.6.1 to 3.7: (June 1, 2012)":
  "The Windows 98/ME/2000 builds have been discontinued, due to code and features that are only available on Windows XP/SP3 and later."
- Same file, "3.5.5 to 3.6": "Reverted to SDL 1.2.14 for the Windows 98/2k release, since SDL 1.2.15 isn't supported in that environment."
- Announce.txt in stella-3.6.1-src.tar.gz (opened): "Binaries for Windows 98/2000 : Stella-3.6.1_98_2k-windows.zip (32-bit for Windows 98/2000)".
- docs/index.html of 3.6.1 (opened): "The Windows version of Stella is designed to work on Windows 98/2000/XP/Vista/7"; "Visual C++ 2005 is required to compile the Stella source code for Windows 98 and 2000".
- Windows ME: named only in the 3.7 discontinuation line (so the 98/2k build was considered to cover ME). Windows 95: never named; unknown, not claimed.
- Stella.exe in the 98/2k zip: its import table (parsed on the host, not run) lists only SDL.dll, KERNEL32.dll and USER32.dll, so the C runtime is linked statically (no MSVCR80.dll). DDRAW, opengl32 and shfolder appear only as strings, i.e. are loaded at run time. SHFOLDER.DLL (used to find Application Data) comes with Internet Explorer 5 and is on 98 SE; Stella falls back if the folder is not found (not verified on first-edition 98).
- Not verified: running on Windows 98 (no VM interaction).

## Download

- Official release page: https://github.com/stella-emu/stella/releases/tag/release-3.6.1 (the project moved its old SourceForge files to GitHub in 2017; the SourceForge folder for 3.6.1 is empty).
- Chosen file: https://github.com/stella-emu/stella/releases/download/release-3.6.1/Stella-3.6.1_98_2k-windows.zip
  - Stella-3.6.1_98_2k-windows.zip, 1,518,520 bytes
  - SHA-256: 19639c651abd1c8d8d8c7c49894ecec5986f868d6995bef46065d79fdfbf88da
- Alternative (also downloaded): https://github.com/stella-emu/stella/releases/download/release-3.6.1/Stella-3.6.1_98_2k-win32.exe
  - 1,489,333 bytes, SHA-256 820d6e73c8cbbdfad6e6dc2e76d72d5d2c04f7420955d37cd2628923c5ba8704
  - Inno Setup (header "Inno Setup Setup Data (5.3.3)"). It is not mentioned in the 3.6.1 Announce.txt, which lists only the zip for 98/2000, and its contents could not be checked without running or unpacking it with a tool not present on the host. So the zip is recommended.
- Published checksums: none. The project publishes no hashes for 3.6.1, and the GitHub release assets (re-uploaded 2017-01-14) carry no digest.
- Authenticode: not checked/none expected (2012 open source build).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\stella -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- Copyright.txt (3.6.1): "Copyright (C) 1995-2012 Bradford W. Mott, Stephen Anthony and the Stella Team ... under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or any later version."
- SDL.dll (file version 1.2.14.0): README-SDL.txt in the zip says SDL is LGPL and asks that this file be distributed with the runtime.
- LICENSE.TXT here: Stella Copyright.txt, the GPL 2 text (License.txt, identical in source and zip), README-SDL.txt and the LGPL 2.1 text (COPYING from SDL-1.2.14.tar.gz).
- Redistribution of the unmodified binaries is allowed. Conditions: keep the notices and license texts; GPL s.3 / LGPL s.6 require the corresponding source, which we host next to the binary.

## Matching source (hosted)

- https://github.com/stella-emu/stella/releases/download/release-3.6.1/stella-3.6.1-src.tar.gz
  - stella-3.6.1-src.tar.gz, 2,073,179 bytes, SHA-256 b29ab8deb52ababd70883042bd1c037fa40a05276f3b657754b5914ed14d71be
  - Contains the bundled libpng 1.5.9 and zlib 1.2.5 (src/libpng, src/zlib), the VS2005 project for the 98/2k build (src/win32/Stella_vs2005.sln) and the Inno script (src/win32/stella.iss).
- SDL.dll is not in that archive, so its source is hosted too: https://www.libsdl.org/release/SDL-1.2.14.tar.gz
  - SDL-1.2.14.tar.gz, 4,014,154 bytes, SHA-256 5d927e287034cb6bb0ebccfa382cb1d185cb113c8ab5115a0759798642eed9b6 (libsdl.org publishes no checksum for it)

## ROMs and other bundled data

Zip listing (.NET ZipFile): `Stella-3.6.1_98_2k/32-bit/Stella.exe`, `32-bit/SDL.dll`, an empty `64-bit/` folder, and `docs/` (HTML manual, Changes, License, Copyright, README-SDL, and 50 PNG screenshots). **No ROM images and no BIOS** (the 2600 needs none). The manual's screenshots show commercial games (Pac-Man, Space Invaders, Jr. Pac-Man, Chucky Cheese); they are part of the project's own documentation and are not game data. Not a problem, noted only.

## Security

- NVD keyword search "stella atari" (API 2.0, 2026-09-29): 0 results. No project advisories found.
- Bundled libraries (not specific CVEs listed against Stella): zlib 1.2.5 (e.g. CVE-2016-9841 inffast, CVE-2018-25032 deflate; Stella inflates zipped ROMs), libpng 1.5.9 (CVE-2011-3048, fixed in 1.5.10; Stella reads PNG snapshots in the launcher), SDL 1.2.14 (CVE-2019-7572 to -7578 and others are in WAV/BMP loaders, which Stella does not use for user files as far as checked; not verified in detail).
- Summary: 0 known CVEs in Stella itself; the realistic risk is a crafted ROM zip or PNG exploiting the old zlib/libpng. No Warning proposed for the emulator itself; a short one could be added if the catalog policy covers bundled libraries.

## Install behaviour

- Chosen: plain zip. Layout: top folder `Stella-3.6.1_98_2k/` with `32-bit/` (exe + SDL.dll), empty `64-bit/`, `docs/`. Unpacked size about 3,110 KB.
- Beacon: `unzip {dir} strip 1`, shortcut to `{dir}\32-bit\Stella.exe`, uninstall `files`. Stella writes its settings to `<Application Data>\Stella` (or to the folder named in an optional `basedir.txt` beside the exe), which Beacon does not create and does not remove.
- Alternative installer: Inno Setup 5.3.3. Silent `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART`. Default folder `{pf}\Stella` (stella.iss). No AppId, so the uninstall key is `Stella_is1`; DisplayName defaults to AppVerName, i.e. "Stella 3.6.1" (inferred from the script, not observed).

## Verification notes

- Verified by opening/downloading: Changes.txt, the GitHub release asset list (via gh api), the zip listing, SDL.dll/Stella.exe version info and import names (extracted to a temp folder, not run), the source archive (Announce, index.html, Copyright, License, stella.iss, OSystemWin32.cxx), NVD.
- Not verified: the installer's contents; running on 95/98/ME.
