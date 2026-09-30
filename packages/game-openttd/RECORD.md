# OpenTTD 1.8.0 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-openttd`
- Version: 1.8.0
- License: GPL-2.0-only
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- COPYING in the zip: the GNU General Public License version 2, preceded by "This is the license which applies to OpenTTD with the exception of some 3rd party modules. See readme.txt for details". readme.txt: "OpenTTD is licensed under the GNU General Public License version 2.0" (version 2 only; SPDX GPL-2.0-only).
- Redistribution of the unmodified binary is allowed with the license and the complete corresponding source (GPL-2.0 section 3). We host the source archive of the same version.
- **Qualifies.**

## Windows 9x support

- The build is named "win9x" by the project. readme.txt of 1.8.0: "Under Windows 98 and lower it is impossible to use a dedicated server; it will fail to start." and lists the personal directory "C:\My Documents\OpenTTD (95, 98, ME)". These show the build targets 9x.
- Not tested on 98 here (no VM interaction).

## Download

- Official CDN: https://cdn.openttd.org/openttd-releases/1.8.0/ (opened). The release list shows win9x builds (`openttd-X-windows-win9x.zip/.exe`) from 0.7.x up to **1.8.0**; 1.9.3 and 1.10.3 have none (listings opened), so 1.8.0 (2018-04-01) is the last Windows 9x build.
- URL: https://cdn.openttd.org/openttd-releases/1.8.0/openttd-1.8.0-windows-win9x.zip
- Published checksum: https://cdn.openttd.org/openttd-releases/1.8.0/manifest.yaml lists size 6784707 and sha256 a68bf02307cb9b30b178437bedecba061b99948bb6207c44f7ac947263f0841e for openttd-1.8.0-windows-win9x.zip: **MATCH**.
- Alternative: openttd-1.8.0-windows-win9x.exe (installer, 5,818,277 bytes, sha256 e0f5c7c5...87d6 per manifest), not downloaded. Its type and silent switch were not checked; the zip is simpler for Beacon.
- File: openttd-1.8.0-windows-win9x.zip, 6,784,707 bytes
  - SHA-256: a68bf02307cb9b30b178437bedecba061b99948bb6207c44f7ac947263f0841e
  - MD5: 298ce71f6bbdaa3383881c44d270bc1e

## Archive contents

- openttd-1.8.0-windows-win9x.zip (Deflate/Store, 115 entries, files at the root): openttd.exe (8,798,222 bytes), baseset\ (openttd.grf, orig_extra.grf, opntitle.dat, *.obg/*.obs/*.obm descriptors, no_sound.obs, no_music.obm), lang\, ai\, game\, scripts\, docs\, media\, man\, COPYING, readme.txt, changelog.txt, known-bugs.txt.
- openttd.exe PE header (read, not run): i386, OS version 4.0, GUI. Static imports (parsed from the import table): ADVAPI32, GDI32, IMM32, KERNEL32, msvcrt, SHELL32, USER32, WINMM, WS2_32. WS2_32 is Winsock 2, present on 98 and ME; Windows 95 needs the Winsock 2 update, so Systems lists 98 and ME only.
- The exe is statically linked with third-party libraries. Strings show FreeType and ICU (icu_48xx symbols); readme.txt names zlib, liblzma, lzo and libpng as optional libraries (not checked against the build). Their sources are not in openttd-1.8.0-source.tar.xz. Open issue as for ScummVM: GPL corresponding source should include them; the exact versions used for the win9x build are unknown.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: COPYING (inside openttd-1.8.0-windows-win9x.zip).

## Matching source (hosted)

- Source: https://cdn.openttd.org/openttd-releases/1.8.0/openttd-1.8.0-source.tar.xz, 6,521,016 bytes, sha256 c2d32d9d736d27202a020027a3729ae763f5432ae6f424891e57a4095eeb087f; manifest.yaml lists the same size and sha256: **MATCH**. Hosted in src\ as GPL-2.0 requires. Bundled third-party library sources are not included (see Archive contents).

## Security

- OpenTTD security tracker https://www.openttd.org/security (opened 2026-09-29): every listed CVE except one was fixed before 1.8.0 (the latest of those, CVE-2013-6411, was fixed in 1.3.3).
- **CVE-2021-41556**: "Out-of-bounds read in Squirrel interpreter allows sandbox escape and remote code execution", first vulnerable 0.7.0, first fixed 13.2. Affects 1.8.0. A crafted game script or AI (e.g. from the content service or a multiplayer server's game script) can run code.
- NVD keyword "openttd": 20 results, all fixed before 1.8.0 by their descriptions.
- Count: 1 known. ENTRY.TXT carries a Warning.

## Install behaviour

- Type: plain zip with files at the root. `unzip {dir}` (Program Files\OpenTTD). Shortcut to openttd.exe.
- Needs a base graphics set: game-opengfx installs OpenGFX into `{dir}\baseset`.
- Settings, saves and downloaded content go to C:\My Documents\OpenTTD on 95/98/ME (readme.txt), which Beacon does not remove.
- No registry entries from the zip build, no Add/Remove Programs entry. Uninstall: `files`.
- Installed-Size in ENTRY.TXT: 19180 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
