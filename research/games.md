# Games for Beacon 98 - research, 2026-09-29

These are games that Beacon 98 may redistribute in unmodified form. The license or readme text inside each distributed archive is the evidence. [V] means I opened the file or page myself. [S] would mean the fact comes only from a search snippet; nothing in this table is [S]. The web search budget ran out before this task began, so every source was reached through direct URLs and directory listings.

Package records are in `D:\Win98SE\beacon\packages\game-*\`. Each has the download, LICENSE.TXT, RECORD.md and ENTRY.TXT. All 27 folders were scanned with Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), which found no threats. No program was run.

## Summary

- **Examined:** 40 titles or versions: the 27 packaged, 9 single titles that do not qualify, and 4 Apogee titles checked as a group.
- **Qualify: 27, all packaged.**
  - 26 are ready.
  - 1 is on hold: Wolfenstein 3-D. Its zip uses the Implode and Shrink compression methods, and the client's miniz library can only unpack stored and deflated entries.
- **Qualify only with review: 2.** Doom 1.9 and Wolfenstein 3-D give permission only informally.
  - Doom 1.9: its installer text says "PLEASE DISTRIBUTE!!!".
  - Wolfenstein 3-D: "Feel free to share it with your friends, but please do not give it away altered or as part of another system".
  - Every other packaged title has a formal grant (a license, or a freeware or GPL text).
- **Do not qualify, or unresolved: 13.** These are the 10 rows of the second table; the four Apogee titles share one row.
- **Not examined: 7 candidates or groups.** These are listed in the third table.
- **Installing DOS shareware.** The id and 3D Realms archives (Doom, Heretic, Quake, Wolfenstein 3-D, Duke Nukem 3D) contain the publisher's own DOS installer, either DEICE or INSTALL.EXE.
  - Beacon unpacks the archive to `{pf}\Games\<Name>` and adds a Start Menu shortcut named "... - install".
  - That installer writes the game to its own folder, such as C:\DOOMS. Beacon cannot track or remove that folder, and each Notice says so.
  - The Epic MegaGames archives and Liero run straight from the unpacked folder.
- **Suggested client feature.** An `After: unzip` step, or support for self-extracting archives split into parts, would let Beacon install Doom, Heretic and Quake fully. DOOM1.WAD could then be played with the `prboom` package. The same applies to Implode/Shrink support for Wolfenstein 3-D.

## Qualifying games (packaged)

| Package id | Game | Version | Rights holder / license | Redistribution grant (quote) | Source URL | Qualifies | Notes | |
|---|---|---|---|---|---|---|---|---|
| game-doom-shareware | Doom (shareware) | 1.9 | id Software; shareware, with no formal license document in 1.9 | DOOMS_19.DAT: "SHAREWARE VERSION / PLEASE DISTRIBUTE!!!"; README: ASP shareware | https://www.gamers.org/pub/idgames/idstuff/doom/doom19s.zip | Yes, needs review | The grant is informal. A second idgames mirror (youfailit.net) has an identical copy. Installs with the DEICE installer. | [V] |
| game-heretic-shareware | Heretic (shareware) | 1.2 | Raven Software / id Software; Limited Use License | "3 Electronic Distribution is Permitted: ID grants to you the right to distribute, royalty free and by electronic means only, the Software; provided, however the Software must be so distributed only in compressed format." | https://www.gamers.org/pub/idgames/idstuff/heretic/htic_v12.zip | Yes | The mirror copy is identical. Installs with DEICE. | [V] |
| game-quake-shareware | Quake (shareware) | 1.06 | id Software; shareware license, SLICNSE.TXT | "6. Permitted Distribution. So long as this Agreement accompanies the Software at all times, ID grants to Providers the limited right to distribute, free of charge ... by electronic means only ... in a compressed format ... ID grants to you, the end-user, the limited right to distribute, free of charge only, the Software as a whole." | https://www.gamers.org/pub/idgames/idstuff/quake/quake106.zip | Yes | The mirror copy is identical. The Warning covers the Quake 1 server CVEs. Installs with DEICE. | [V] |
| game-wolf3d-shareware | Wolfenstein 3-D (shareware) | 1.4 | id Software, distributed by Apogee; shareware | READ1ST.TXT: "Feel free to share it with your friends, but please do not give it away altered or as part of another system."; VENDOR.DOC thanks vendors for distributing it | https://www.gamers.org/pub/games/wolf3d/official/1wolf14.zip | Yes, needs review; on hold | The zip uses Implode/Shrink, which the client cannot unpack. ENTRY.TXT is commented out. | [V] |
| game-duke3d-shareware | Duke Nukem 3D (shareware) | 1.3d | 3D Realms; LICENSE.TXT [V.7.16.98] | "[B] ONLINE SERVICES (including BBSs, and WWW and FTP sites) that are free ... may make the Game available for downloading." All files must be included unmodified. | https://www.gamers.org/pub/games/duke3d/share/3dduke13.zip | Yes | The MD5 matches the independent Internet Archive copy (3dduke13SW). Installs with INSTALL.EXE. | [V] |
| game-jazz-shareware | Jazz Jackrabbit (shareware) | 1.0 | Epic MegaGames; 1994 shareware license | "Epic MegaGames allows and encourages all bulletin board systems and online services to distribute this game by modem as long as no files are altered or removed." | https://ftp.funet.fi/pub/msdos/games/epic/1jazz.zip | Yes | Must credit Epic and call it shareware. Shortcut to JAZZ.PIF. | [V] |
| game-epic-pinball-shareware | Epic Pinball (shareware) | 2.0 | Epic MegaGames; 1994 license | Same clause as Jazz | https://ftp.funet.fi/pub/msdos/games/epic/pinball2.zip | Yes | Shortcut to PINBALL.PIF. | [V] |
| game-omf2097-shareware | One Must Fall 2097 (shareware) | 2.0 | Epic MegaGames / Diversions; 1995 license | "Distribution online (BBS's, Internet, online services) and by mail is, of course, highly encouraged." | https://ftp.funet.fi/pub/msdos/games/epic/omf20.zip | Yes | Unreliable with sound under Windows, so Systems is 95, 98. | [V] |
| game-tyrian-shareware | Tyrian (shareware) | 1.0 | Epic MegaGames / Eclipse; 1995 license | "Epic allows and encourages bulletin board systems and online services to distribute the Program by modem as long as the General Terms and Conditions ... are complied with." | https://ftp.funet.fi/pub/msdos/games/epic/tyrsw1.zip | Yes | CD-ROM or retail distribution would need permission, which does not apply to Beacon. | [V] |
| game-jill-jungle-shareware | Jill of the Jungle (shareware) | 1.0 | Epic MegaGames; 1994 license | As Jazz | https://ftp.funet.fi/pub/msdos/games/epic/$jill.zip | Yes | | [V] |
| game-xargon-shareware | Xargon 1 (shareware) | 3.0 | Epic MegaGames; 1994 license | As Jazz | https://ftp.funet.fi/pub/msdos/games/epic/$xargon.zip | Yes | Sound works only from DOS, so Systems is 95, 98. | [V] |
| game-kens-labyrinth-shareware | Ken's Labyrinth (shareware) | 1993 | Epic MegaGames / Ken Silverman; 1994 license | As Jazz | https://ftp.funet.fi/pub/msdos/games/epic/$ken.zip | Yes | The archive gives no version number. | [V] |
| game-overkill-shareware | Overkill (shareware) | 1993 | Epic MegaGames; 1994 license | As Jazz | https://ftp.funet.fi/pub/msdos/games/epic/$overkil.zip | Yes | | [V] |
| game-zone66-shareware | Zone 66 (shareware) | 1993 | Epic MegaGames / Renaissance; 1994 license | As Jazz | https://ftp.funet.fi/pub/msdos/games/epic/$zone66.zip | Yes | "will not run under Windows", so it needs MS-DOS mode (Systems 95, 98). | [V] |
| game-kiloblaster-shareware | Kiloblaster (shareware) | 2.0 | Epic MegaGames; 1994 license | VENDOR.DOC: "You have permission to distribute this software, as long as you make it clear that this is SHAREWARE ... and no files are modified or deleted." | https://ftp.funet.fi/pub/msdos/games/epic/$kilo.zip | Yes | | [V] |
| game-radix-shareware | Radix: Beyond the Void (shareware) | 1.0 | Epic MegaGames / Neural Storm; 1995 license | As Tyrian | https://ftp.funet.fi/pub/msdos/games/epic/radsw1.zip | Yes | Needs a 486. | [V] |
| game-extreme-pinball-shareware | Extreme Pinball (shareware) | 1.0 | Epic MegaGames / Digital Extremes; 1995 license | As Tyrian | https://ftp.funet.fi/pub/msdos/games/epic/xpsw1.zip | Yes | | [V] |
| game-liero | Liero | 1.33 | Joosa Riekkinen; WTFPL (the 2011 license text on the official site); SMIX library BSD-3-Clause | "They are, unless otherwise stated, available under the WTFPL license". The original: "Liero is freeware ... You may distribute it to anyone and anyhow WITHOUT ANY CHANGES" | https://www.liero.be/download/lierov133winxp.zip | Yes | Official site: "Requires Windows 98 or older". This is a repack of 1.33 made in 2006/2011. | [V] |
| game-openttd | OpenTTD | 1.8.0 (win9x build) | OpenTTD team; GPL-2.0-only | COPYING (GPL v2). The source is hosted. | https://cdn.openttd.org/openttd-releases/1.8.0/openttd-1.8.0-windows-win9x.zip | Yes | This is the last win9x build; 1.9.x and later have none. The SHA-256 matches manifest.yaml. The Warning covers CVE-2021-41556. Sources for the bundled libraries are missing. | [V] |
| game-opengfx | OpenGFX | 0.5.5 | OpenGFX authors; GPL-2.0-only | license.txt (GPL v2). The source is hosted. | https://cdn.openttd.org/opengfx-releases/0.5.5/opengfx-0.5.5-all.zip | Yes | The SHA-256 matches manifest.yaml. It installs into `{dir:game-openttd}\baseset`. | [V] |
| game-flight-amazon-queen | Flight of the Amazon Queen (CD talkie) | 1.1 | J. Passfield & S. Stamatiadis; freeware | "1) You may distribute this game for free on any medium, provided this Readme and all associated copyright notices and disclaimers are left intact." | https://downloads.scummvm.org/frs/extras/Flight%20of%20the%20Amazon%20Queen/FOTAQ_Talkie-1.1.zip | Yes | MP3 audio. The SHA-256 matches. Played with ScummVM. | [V] |
| game-lure-of-the-temptress | Lure of the Temptress | 1.1 | Revolution Software; freeware | Same clause (LICENSE.txt) | https://downloads.scummvm.org/frs/extras/Lure%20of%20the%20Temptress/lure-1.1.zip | Yes | The SHA-256 matches. | [V] |
| game-drascula | Drascula: The Vampire Strikes Back | 1.0 + audio 2.0 | Alcachofa Soft; freeware | "1) You may distribute "DRASCULA" for free on any medium, provided this Readme ... left intact." | https://downloads.scummvm.org/frs/extras/Drascula_%20The%20Vampire%20Strikes%20Back/drascula-1.0.zip | Yes | Two files. Both SHA-256 values match. | [V] |
| game-dreamweb | DreamWeb (CD, UK) | 1.1 | Creative Reality (N. Dodwell & D. Dew); freeware | Same clause (license.txt) | https://downloads.scummvm.org/frs/extras/Dreamweb/dreamweb-cd-uk-1.1.zip | Yes | 226 MB. The floppy version (10 MB) is an alternative. The SHA-256 matches. | [V] |
| game-soltys | Soltys (English) | 1.0 | LK Avalon; freeware | Same clause | https://downloads.scummvm.org/frs/extras/Soltys/soltys-en-v1.0.zip | Yes | The SHA-256 matches. | [V] |
| game-sfinx | Sfinx (English) | 1.1 | LK Avalon; freeware | Same clause | https://downloads.scummvm.org/frs/extras/Sfinx/sfinx-en-v1.1.zip | Yes | The SHA-256 matches. | [V] |
| game-nippon-safes | Nippon Safes, Inc. | 1.0 | Dynabyte; freeware | Same clause (readme.txt) | https://downloads.scummvm.org/frs/extras/Nippon%20Safes/nippon-1.0.zip | Yes | The SHA-256 matches. | [V] |

"As Jazz" and "As Tyrian" mean that the archive carries the same Epic license form, checked by its hash: the 1994 form for the `$*.zip` files, and the 1995 form for Radix and Extreme Pinball.

## Examined, not qualifying or unresolved

| Game | Version / file | Rights holder / license found | Redistribution allowed? | Source URL | Qualifies | Reason | |
|---|---|---|---|---|---|---|---|
| Doom95 (Windows 95 port, shareware WAD) | doom95.zip (idstuff/doom/win95) | id Software; no license or grant in the archive. Also bundles the Microsoft DirectX 1 redistributable ("only as part of the application") | Not stated | https://www.gamers.org/pub/idgames/idstuff/doom/win95/doom95.zip | No (unclear) | README.TXT is the DOS Doom readme with no grant. doom19s already covers the shareware episode. | [V] |
| Hexen demo | hexndemo.zip | Raven / id / GT Interactive | README: "Hexen is NOT a shareware product". It contains no grant. | https://www.gamers.org/pub/idgames/idstuff/hexen/hexndemo.zip | No | No distribution grant. | [V] |
| Shadow Warrior (shareware) | 3dsw12.zip, 1.2 | 3D Realms LICENSE.TXT [V.5.01.97] | Grants only "[A] INDIVIDUALS ... to friends, family, coworkers, and members of any not-for-profit organization" and CompuServe/AOL forums after 1997. It has no WWW/FTP clause, unlike Duke3D. | https://www.gamers.org/pub/games/sw/share/3dsw12.zip | No (unclear) | A public download service is not clearly covered. | [V] |
| Strife demo | strife11.zip, 1.1 | Rogue / Velocity | README.TXT has no license. The idgames text for strife10 was written by the uploader, not the rights holder. | https://www.gamers.org/pub/games/strife/strife11.zip | No | No grant from the rights holder. | [V] |
| Descent (shareware) | desc14sw.exe, 1.4 | Parallax / Interplay | Unknown. The license is inside the proprietary DESCENT1/2.SOW installer data and cannot be read without running INSTALL.EXE. | https://ftp.funet.fi/pub/msdos/games/interplay/desc14sw.exe | Unresolved | The license could not be verified. It could be read in a VM later. | [V] |
| One Must Fall 2097 full version | omf21cd.zip, 2.1 (fan site omf2097.com) | Epic "LIMITED USE SOFTWARE LICENSE AGREEMENT" | "2. Copying Prohibited." There is no freeware grant in the archive. | https://www.omf2097.com/pub/files/omf/omf21cd.zip | No | The freeware re-release is not evidenced in the file. The shareware 2.0 is packaged instead. | [V] |
| Tyrian 2000 | tyrian2000.zip | Eclipse / Stealth Productions (readme) | The readme has no license. Only the fan site camanis.net says "Tyrian was released as freeware by Jason Emery in 2004". | https://www.camanis.net/tyrian/tyrian2000.zip | No (unclear) | No grant in the archive and none on a rights-holder site. The Tyrian 1.0 shareware is packaged. | [V] |
| God of Thunder | gotfree.zip (ScummVM "Freeware Version") | Impulse Games LICENSE.TXT | "The End User may not rent, lease, sell, or otherwise distribute the Software." | https://downloads.scummvm.org/frs/extras/God%20of%20Thunder/gotfree.zip | No | The archive's own license forbids distribution, despite the "freeware" label. Also "Untested" in ScummVM 2026.1.0. | [V] |
| The Griffon Legend | griffon-1.0.zip | Syn9; no license text | Not stated; only ScummVM's "Freeware Version" label | https://downloads.scummvm.org/frs/extras/Griffon%20Legend/griffon-1.0.zip | No (unclear) | The readme has no terms. | [V] |
| Commander Keen 1, Rise of the Triad, Blake Stone, Raptor (Apogee/3D Realms shareware) | - | Apogee / 3D Realms | Not checked | none trustworthy | Unresolved | No rights-holder download: 3drealms.com and apogeeent.com have none. The Apogee directory was removed from the gamers.org copy of the uwp/uml archive (its README says so), and ftp.funet.fi/.../apogee/ is empty. Internet Archive items exist (for example rott_shareware, blake-stone, Bs-aog-sw1, raptor-call-of-the-shadows-windows-shareware), but their provenance is unknown and they were not opened. | [V] |

## Not examined (candidates for a next batch)

- The rest of Epic's directory on FUNET, all carrying the same kind of license: $amath, $ancient/anc1s, $brix, $castle (Castle of the Winds, Windows 3.1), $dare, $electro, $heart, $solar, dblast, heroes, highway, lw2u, td2192/tddemo, and jjxmas95 (Jazz Holiday Hare). Also 3dsw10.zip, d2demo10.zip (the Descent II demo), and the funet 3drealms directory (3dtv.zip).
- Mystery House. ScummVM hosts a "public domain version" (Apple II), adl:hires1, rated "Good".
- The SLUDGE freeware games on the ScummVM page (Out of Order, Lepton's Quest, Robin's Rescue and others). Each has its own terms.
- Cave Story, Abuse, Chocolate Doom, Freeciv, LBreakout2, Pingus and FreeCol. I had no search budget left. abuse.zoy.org failed the TLS handshake from this host.
- Beneath a Steel Sky, ScummVM, DOSBox, Freedoom and PrBoom are already in the catalog and were not re-examined.

## Sources and mirrors

- The idgames archive at https://www.gamers.org/pub/idgames/idstuff/ holds id Software's own directory from ftp.idsoftware.com, which no longer exists. It was cross-checked against https://youfailit.net/pub/idgames/idstuff/ and http://ftp.fu-berlin.de/pc/games/idgames/idstuff/.
- gamers.org also keeps https://www.gamers.org/pub/games/, including wolf3d/official, duke3d/share and sw/share.
- FUNET, at https://ftp.funet.fi/pub/msdos/games/, holds the epic/, 3drealms/ and interplay/ directories.
- The ScummVM freeware page is https://www.scummvm.org/games/, with downloads and .sha256 files at https://downloads.scummvm.org/frs/extras/.
- The OpenTTD CDN is at https://cdn.openttd.org/, with a manifest.yaml of checksums for each release.
- The official Liero site is https://www.liero.be/.
- Epic's, id's, Apogee's and 3D Realms' own servers for these files are gone. Where a mirror is used, the archive's own license grants redistribution, as the instructions require.
