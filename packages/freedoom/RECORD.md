# Freedoom 0.13.0 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: Freedoom (Contributors to the Freedoom project), id `freedoom`
- Version: 0.13.0 (GitHub release published 2024-01-29), the newest Freedoom release (GitHub releases API, checked 2026-09-29; earlier: 0.12.1 2019-10-22, 0.12.0 2019-10-10, 0.11.3 2017-07-19).
- Contents: freedoom1.wad (Phase 1, Doom 1 style, episodes 1-4) and freedoom2.wad (Phase 2, Doom II style, MAP01-MAP32), manuals (PDF in English, Spanish, French), README/NEWS (HTML), CREDITS, COPYING.
- License: BSD 3-clause (COPYING.txt in the zip). Data only; no program.
- Engine: `Depends: prboom` (PrBoom 2.5.0). The game package depends on the engine, as beneath-a-steel-sky depends on scummvm.
- Recommendation: 0.13.0.

## Compatibility with PrBoom 2.5.0

- Freedoom's own statements (NEWS.adoc, opened raw from GitHub master; release notes on GitHub, opened):
  - 0.11: "Freedoom is now a limit-removing game rather than using Boom specials."
  - 0.12.0: "A strong focus on vanilla compatibility has been sought for this release."
  - 0.13.0: "Improved vanilla compatibility. Boom features removed. Hall of mirrors greatly reduced. Visplane overflows fixed."
  - README.adoc (master): "All levels for Freedoom must be vanilla-compatible, requiring an expanded-limits or limit-removing engine is not permissible."
  - Earlier releases (up to 0.10.x) used Boom specials. PrBoom supports Boom too, so every release since then should play, but 0.13.0 needs the least.
- Checked in the WAD files themselves (WAD directory parsed on the host):
  - Both are type IWAD. freedoom1.wad: 3,163 lumps, E1M1 to E4M1 present (PrBoom will detect "retail" Doom). freedoom2.wad: 3,610 lumps, MAP01 present (detected as Doom II).
  - No ANIMATED or SWITCHES lumps (Boom), no MAPINFO/UMAPINFO/ZMAPINFO/DECORATE (port-specific), no PNG graphics (0 lumps with a PNG signature).
  - Music lumps D_*: all 35 are standard MIDI ("MThd"). PrBoom 2.5.0 passes non-MUS music straight to SDL_mixer (src/SDL/i_sound.c), so MIDI works.
  - Each WAD has a DEHACKED lump ("Patch File for DeHackEd v3.0", "Doom version = 19", "Patch format = 6") with Frame, [PARS] and [STRINGS] sections. PrBoom 2.5.0 loads a DEHACKED lump from any loaded WAD automatically (d_main.c, "dehacked-in-a-wad support") and supports the BEX [PARS]/[STRINGS] extensions (Boom/MBF feature list in README.txt).
- Not tested in PrBoom (no VM interaction). The first level of each phase should be tried in the VM.

## How PrBoom finds the WADs

- PrBoom 2.5.0 recognises only these IWAD names automatically: doom2f, doom2, plutonia, tnt, doom, doom1, doomu, freedoom (src/d_main.c, standard_iwads). "freedoom.wad" is the pre-0.8 Freedoom name; freedoom1.wad and freedoom2.wad are not recognised.
- `-iwad` takes a name or a full path; I_FindFile first tries the argument exactly as given, so `-iwad "C:\Program Files\Freedoom\freedoom2.wad"` works. SDL's WinMain splits the command line honouring quotes.
- Decision: Freedoom installs into its own folder and gets two shortcuts that start `{dir:prboom}\prboom.exe -iwad "{dir}\freedoom1.wad"` / `...freedoom2.wad`. This keeps both phases available, avoids renaming files (a renamed freedoom.wad would be picked only when no doom*.wad is present), and avoids writing into PrBoom's folder, so each package removes only its own files. Saved games and prboom.cfg go to PrBoom's folder (exe folder), shared with other IWADs; PrBoom's savegames record the WADs used.

## Windows 9x support

Data files only; runs wherever PrBoom runs (98 and ME; see the prboom record). No KernelEx.

## Download

- Official: https://github.com/freedoom/freedoom/releases/tag/v0.13.0 (opened). Also linked from https://freedoom.github.io/.
- URL: https://github.com/freedoom/freedoom/releases/download/v0.13.0/freedoom-0.13.0.zip
- File: freedoom-0.13.0.zip, 24,143,781 bytes
- SHA-256: 3f9b264f3e3ce503b4fb7f6bdcb1f419d93c7b546f4df3e874dd878db9688f59
- Published checksums: freedoom-0.13.0-CHECKSUM (same release) lists SHA256 3f9b264f...9688f59: MATCH. The CHECKSUM file is PGP-signed, and freedoom-0.13.0.zip.sig is a detached signature: both "Good signature from Steven Elliott <selliott512@gmail.com>", key 90BB 5F79 7B0E D14D 310F 90BE 39B3 786A 18C9 3DAD (fetched from keys.openpgp.org; not otherwise certified). The .sig and CHECKSUM files are kept in this folder as evidence; they are not part of the catalog entry.
- Alternative: freedm-0.13.0.zip (FreeDM, deathmatch IWAD) not included.

## Archive contents (listed with .NET ZipFile)

One top folder `freedoom-0.13.0/`: COPYING.txt (1,644), CREDITS.txt, CREDITS-MUSIC.txt, NEWS.html, README.html, freedoom-manual-en.pdf, -es.pdf, -fr.pdf, freedoom1.wad (28,795,076), freedoom2.wad (28,787,748). No executables. No id Software data (the WADs are Freedoom's own IWADs). Nothing questionable.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\freedoom -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- COPYING.txt of 0.13.0: "Copyright (c) 2001-2024 Contributors to the Freedoom project. All rights reserved. Redistribution and use in source and binary forms, with or without modification, are permitted provided that ..." - the BSD 3-clause license. The DEHACKED lump is tagged "SPDX-License-Identifier: BSD-3-Clause".
- README.adoc: "you may redistribute it to anyone without needing to ask for permission".
- Conditions: keep the copyright notice, conditions and disclaimer with the binary form (COPYING.txt is in the zip and is installed; LICENSE.TXT repeats it); do not use the project's or contributors' names to endorse derived products.
- Source: BSD 3-clause has no source obligation; Freedoom is not GPL. The build sources are public at https://github.com/freedoom/freedoom/tree/v0.13.0 for anyone who wants them; not hosted.
- LICENSE.TXT: a short header and COPYING.txt (the copyright sign and curly quotes transliterated to Windows-1252-safe ASCII).

## Security

Data only. NVD keyword "freedoom": 0 results. Risk is limited to the engine that reads the WADs (see the prboom record). Freedoom is signed by the project, so the files are trustworthy.

## Install behaviour

- Type: plain zip, no installer. `unzip {dir} strip 1` gives {dir}\freedoom1.wad, freedoom2.wad and the documents.
- Shortcuts: "Freedoom Phase 1" and "Freedoom Phase 2" as in ENTRY.TXT.
- Uninstall: `files`. No registry entries.
- Installed size about 60,300 KB.

## Verification notes

- Opened/downloaded: GitHub releases (web page and API via gh), README.adoc and NEWS.adoc from GitHub, the zip, CHECKSUM and .sig (verified with gpg), WAD directories and DEHACKED lump (read with a script, not executed), PrBoom 2.5.0 source for IWAD search and DEHACKED/music handling.
- The GitHub releases web page as summarised by the fetch tool gave wrong years for some releases; the dates above are from the GitHub API.
- Not verified: actually playing either phase in PrBoom 2.5.0 on Windows 98.
