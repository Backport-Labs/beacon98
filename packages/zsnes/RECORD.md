# ZSNES 1.51 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: ZSNES, Super Nintendo (SNES) emulator (ZSNES Team: zsKnight, _Demo_, pagefault, Nach)
- Version: 1.51 (Windows port, zsnesw151.zip; files dated 2007-01-24/25)
- License: GPL-2.0-only (ZSNES and JMAlib), ManyMouse under the zlib license
- Recommendation: 1.51 Windows port. It is the last official ZSNES release (SourceForge lists nothing newer), and its own readme lists Windows 95/98/ME. Later "ZSNES 2.x" repositories on GitHub are community Linux ports and were not considered.

## Windows 9x support evidence

- docs/readme.txt/readme.txt in zsnesw151.zip (opened), section 4 "System Requirements":
  "Official Ports - Win port: Microsoft Windows 95/98/ME/2000/XP/2003/Vista"
  and under "Win Port": "OS: Windows 95/98/ME - CPU: Pentium II (or equivalent) 233MHz (500MHz recommended) - RAM: 32MB (64MB recommended) ... API: DirectX v8.0a or later must be installed".
- SourceForge RSS for /zsnes (opened via WebFetch): newest files are zsnes151src.tar.bz2, zsnesw151.zip, zsnes151.zip (DOS port).
- zsnesw.exe is UPX-packed (about.txt: "ZSNES Win uses Visual C++ 2003 (or MinGW), DirectX 8, UPX, and ManyMouse"); its visible imports are only KERNEL32, USER32, GDI32, SHELL32 (the rest is resolved by the UPX stub). It was not unpacked or run.
- Windows 95 and ME: stated in the readme; DirectX 8.0a exists for 95. Not tested here.
- A DOS port of the same version (zsnes151.zip, MD5 049b2674ede4a91fdbcd689cd8c548b3 per SF) exists; not downloaded.

## Download

- Official: SourceForge project "zsnes", folder `zsnes/ZSNES v1.51`
- URL: https://downloads.sourceforge.net/project/zsnes/zsnes/ZSNES%20v1.51/zsnesw151.zip
- File: zsnesw151.zip, 867,785 bytes
- SHA-256: 855375a2bff44993322e495732498d0278a82590affd912bc54738b61a662d86
- MD5: d13339e5bef48124d60dc5bc155981fd. SourceForge RSS lists d13339e5bef48124d60dc5bc155981fd and size 867,785: MATCH (SourceForge-generated, not signed by the authors).
- zsnes.com is no longer the project's site; SourceForge is the remaining official host.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\zsnes -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- Source headers (e.g. src/zmovie.c in zsnes151src.tar.bz2): "Copyright (C) 1997-2007 ZSNES Team ... under the terms of the GNU General Public License version 2 as published by the Free Software Foundation." No "or later", so GPL-2.0-only.
- JMAlib (src/jma, NSRT Team): GPL version 2. ManyMouse (src/mmlib, Ryan C. Gordon): zlib-style license.
- docs/readme.txt/license.txt in the zip: GPL 2 full text.
- LICENSE.TXT here: the ZSNES, JMAlib and ManyMouse notices, then license.txt.
- Redistribution of the unmodified zip is allowed with the license and the corresponding source; we host the source.
- Linked libraries not in the source archive: zlib and libpng (makefile.ms: `MSVCLIBS=zlib.lib libpng.lib ... dinput8.lib dxguid.lib`; versions unknown because the exe is UPX-packed), both under permissive licenses whose own terms need no source; dxguid.lib is Microsoft's DirectX GUID data library, and the DirectX DLLs are system components. Strictly, GPL's "complete source" would also cover zlib/libpng; their exact versions could not be determined, so their sources were not added. Low risk; noted.

## Matching source (hosted)

- URL: https://downloads.sourceforge.net/project/zsnes/zsnes/ZSNES%20v1.51/zsnes151src.tar.bz2
- File: src\zsnes151src.tar.bz2, 1,072,340 bytes
- SHA-256: 2856dedba272e9eed66cbf68dd4a9ae56797c373686c57371a65c7df35264623
- MD5: 7071186bf80632ae88a153239498d8c9, SF RSS: MATCH.
- Contains ZSNES, JMAlib, ManyMouse, snes_ntsc and the Windows makefile (src/makefile.ms). Not in it: zlib, libpng.

## ROMs and other bundled data

Zip listing (.NET ZipFile): `zsnesw.exe` at the root, plus `docs/readme.htm/` (HTML manual with CSS and PNG icons) and `docs/readme.txt/` (text manual, license.txt). **No ROMs, no BIOS, no game data.** The readme says "uncompressed ROMs (not included!)". SNES special-chip games (DSP-1 etc.) are emulated in code; no chip ROM dumps are shipped. Nothing questionable.

## Security

- NVD keyword search "zsnes" (API 2.0, 2026-09-29): 0 results. No project advisories. A wider web search for public exploits was not possible (search budget exhausted); from memory, ZSNES has had published crafted-ROM exploits, but this could not be verified, so it is not counted.
- Netplay is disabled in 1.51 (docs/readme.txt/netplay.txt: "Netplay has been disabled for the indefinite future"), so there is no network attack surface.
- Summary: 0 known CVEs. ZSNES is largely hand-written x86 assembly from 1997-2007 and parses ROM files and ZIP/JMA/GZ archives with old libraries; treat untrusted ROM files as a risk. A mild Warning is proposed.

## Install behaviour

- Plain zip, no installer. The readme says: "Extract the contents of the archive into a new folder ... ZSNES is not packaged with an installer, so there will be no entry in the Windows Start Menu" and "to uninstall ZSNES, simply delete the entire folder".
- Layout: `zsnesw.exe` at the root, `docs\readme.htm\...`, `docs\readme.txt\...`. About 1,583 KB unpacked.
- Beacon: `unzip {dir}` (no strip), shortcut to `{dir}\zsnesw.exe`, uninstall `files`. ZSNES writes zsnesw.cfg and other settings into its folder on first run; Beacon does not remove those.
- No Add/Remove Programs entry.

## Verification notes

- Verified by opening/downloading: SourceForge file list and RSS (WebFetch), the zip and source archive, readme.txt, about.txt, netplay.txt, license.txt, source headers, makefile.ms, NVD.
- Not verified: running on 95/98/ME; zlib/libpng versions inside the packed exe.
