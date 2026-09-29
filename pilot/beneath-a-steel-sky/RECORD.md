# Beneath a Steel Sky (CD talkie)

- Date checked: 2026-09-28
- Name: Beneath a Steel Sky, CD talkie, English
- Version: bass-cd-1.2. The readme is dated August 1st 2003.
- (C) Revolution Software Ltd. Freeware release distributed by the ScummVM project.

## License
This is a freeware licence that permits redistribution. **It is not an open source licence.**
- Clause 3 forbids charging for the game itself, which fails OSD #1 (free redistribution).
- No source is involved: the archive is game data only.
- Hosting and redistributing the unmodified zip for free is explicitly allowed (clauses 1 and 2).
  The readme and copyright notices must stay intact, and we must give attribution.

Verbatim from bass-cd-1.2/readme.txt inside the zip (the full readme is saved as LICENSE.TXT):

> Preamble:
>   Basically, give this game away, share it with your friends. Don't remove this
> Readme, or pretend you wrote it. You can include it in a software collection,
> like a linux distribution or coverdisk (which may be sold), but using it in
> things like commercial adventure game collections without asking is just playing
> dirty. This preamble is not legally binding, but is to clarify the intent of the
> following license.
>
> License:
>  1) You may distribute this game for free on any medium, provided this readme
> and all associated copyright notices and disclaimers are left intact.
>
>  2) You may charge a reasonable copying fee for this archive, and may distribute
> it in aggregate as part of a larger & possibly commercial software distribution
> (such as a Linux distribution or magazine coverdisk). You must provide proper
> attribution and ensure this readme and all associated copyright notices, and
> disclaimers are left intact.
>
>  3) You may not charge a fee for the game itself. This includes reselling the
> game as an individual item.
>
>  4) You may modify the game as you wish.  You may also distribute modified
> versions under the terms set forth in this license, but with the additional
> requirement that the work is marked with a prominent notice which states that
> it is a modified version.
>
>  5) All game content is (C) Revolution Software Ltd. The ScummVM engine is (C)
> The ScummVM Team (www.scummvm.org)
>
>  6) THE GAMEDATA IN THIS ARCHIVE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
> IMPLIED WARRANTIES, INCLUDING AND NOT LIMITED TO ANY IMPLIED WARRANTIES OF
> MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.

## Compatibility / Windows 9x
- Readme: "You need ScummVM version 0.5.0 or newer to play this game".
- https://www.scummvm.org/compatibility/2026.1.0/ (opened) rates "Beneath a Steel Sky | sky:sky | Excellent"
  for 2026.1.0, the last Windows 95+ build.
- The game runs through ScummVM, so its Windows 9x support is ScummVM's. See ../scummvm/RECORD.md.

## Download
- Listed on https://www.scummvm.org/games/ with SHA-256 53209b94...4593 and last update 2005-10-31.
- URL: https://downloads.scummvm.org/frs/extras/Beneath%20a%20Steel%20Sky/bass-cd-1.2.zip
- File: bass-cd-1.2.zip
- Size: 69,377,781 bytes
- SHA-256: 53209b9400eab6fd7fa71518b2f357c8de75cfeaa5ba57024575ab79cc974593
- Published checksum: **MATCHES** both the `.sha256` file on the server and the value on the Games page.
- Contents: bass-cd-1.2/ containing sky.dnr (40,780), sky.dsk (72,395,713), sky.cpt (419,427) and readme.txt (5,891).
- Defender: MpCmdRun -Scan -ScanType 3 on this folder found no threats. Signature version 1.459.442.0.

## Source
Not applicable. This is a data-only freeware archive, and the engine source is covered in ../scummvm.

## Security
There are no known CVEs for the game data. The data is parsed by the ScummVM "sky" engine.

## Install notes
- Unzip. Contents sit in the `bass-cd-1.2\` subfolder, so the target should be e.g. `C:\GAMES\BASS`.
  Keep readme.txt, which the licence requires.
- ScummVM will not find the game automatically. The package manager must register it by one of:
  - `scummvm.exe --add --path=C:\GAMES\BASS --game=sky`, which writes a `[sky]` target with
    engineid/gameid (option verified in the 2026.1.0 source, base/commandLine.cpp; not run)
  - appending the section to scummvm.ini by hand. This form is illustrative:
    ```
    [sky]
    engineid=sky
    gameid=sky
    path=C:\GAMES\BASS
    description=Beneath a Steel Sky
    ```
- Uninstall: delete the folder and remove the `[sky]` section. Saves are stored in ScummVM's save path, not in the game folder.
