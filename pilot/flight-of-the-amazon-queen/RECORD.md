# Flight of the Amazon Queen (CD talkie, original)

- Date checked: 2026-09-28
- Name: Flight of the Amazon Queen, CD talkie, English, "original" (uncompressed audio) edition
- Version: FOTAQ_Talkie-original. The readme is dated March 15 2004. The server shows last update 2020-12-01.
- (C) 1995- John Passfield & Steve Stamatiadis. Freeware release distributed by the ScummVM project.

## License
This is a freeware licence that permits redistribution. **It is not an open source licence.**
- The terms are almost the same as the BASS licence.
- Clause 3 forbids charging for the game itself.
- Hosting and redistributing the unmodified zip for free is explicitly allowed, provided the readme and notices stay intact.

Verbatim from readme.txt inside the zip (the full readme is saved as LICENSE.TXT):

> Preamble:
>   Basically, give this game away, share it with your friends. Don't remove this
> Readme, or pretend that you wrote it. You can include it in a software
> collection, like a Linux distribution or coverdisk (which may be sold), but
> using it in things like commercial adventure game collections without asking is
> just playing dirty. You can modify the gamedata for such purposes as compressing
> audio. This preamble is not legally binding, but is to clarify the intent of
> the following licence.
>
> Licence:
>  1) You may distribute this game for free on any medium, provided this Readme
> and all associated copyright notices and disclaimers are left intact.
>
>  2) You may charge a reasonable copying fee for this archive, and may
> distribute it in aggregate as part of a larger and possibly commercial software
> distribution (such as a Linux distribution or magazine coverdisk). You must
> provide proper attribution and ensure that this Readme and all associated
> copyright notices and disclaimers are left intact.
>
>  3) You may not charge a fee for the game itself. This includes reselling the
> game as an individual item.
>
>  4) You may modify the game as you wish.  You may also distribute modified
> versions under the terms set forth in this licence, but with the additional
> requirement that the work is marked with a prominent notice which states that
> it is a modified version.
>
>  5) All game content is (C) John Passfield and Steven Stamatiadis.
>     The ScummVM engine is (C) The ScummVM Team (www.scummvm.org).
>
>  6) THE GAME DATA IN THIS ARCHIVE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
> IMPLIED WARRANTIES, INCLUDING AND NOT LIMITED TO ANY IMPLIED WARRANTIES OF
> MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

## Compatibility / Windows 9x
- Readme: "This game requires at least ScummVM 0.6.0 to play."
- https://www.scummvm.org/compatibility/2026.1.0/ (opened) rates "Flight of the Amazon Queen | queen:queen | Excellent"
  for 2026.1.0, the last Windows 95+ build.

## Download
- URL: https://downloads.scummvm.org/frs/extras/Flight%20of%20the%20Amazon%20Queen/FOTAQ_Talkie-original.zip
- File: FOTAQ_Talkie-original.zip
- Size: 112,625,523 bytes
- SHA-256: a298e68243f18a741d4816ef636a5a77a1593816fb2c9e23a09124c35a95dfec
- Published checksum: **MATCHES** both the `.sha256` file on the server and the value on https://www.scummvm.org/games/.
- Contents: queen.1 (190,787,021 bytes, uncompressed audio) and readme.txt, at the zip root with no subfolder.
- Alternative not evaluated: FOTAQ_Talkie-1.1.zip in the same directory, with compressed audio.
- Defender: MpCmdRun -Scan -ScanType 3 on this folder found no threats. Signature version 1.459.442.0.

## Source
Not applicable. This is a data-only freeware archive.

## Security
There are no known CVEs for the game data.

## Install notes
- Unzip into a dedicated folder, e.g. `C:\GAMES\FOTAQ`. The zip has no subfolder. It needs about 191 MB of disk.
- Register the game by one of:
  - `scummvm.exe --add --path=C:\GAMES\FOTAQ --game=queen`
  - writing a `[queen]` section with engineid=queen, gameid=queen and path=... to scummvm.ini
- Uninstall: delete the folder and remove the ini section.
