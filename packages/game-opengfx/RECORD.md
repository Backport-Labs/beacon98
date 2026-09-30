# OpenGFX 0.5.5 - Beacon 98 package record

- Date checked: 2026-09-29
- Package id: `game-opengfx`
- Version: 0.5.5
- License: GPL-2.0-only
- Status: can be hosted (see License).

## Evidence of the right to redistribute

- license.txt in the tar: GNU General Public License version 2. readme.txt: the graphics are distributed under "the terms of the GNU General Public License version 2 as published by the Free Software Foundation" (version 2 only; SPDX GPL-2.0-only).
- **Qualifies.** Source archive hosted.

## Windows 9x support

- Data only; runs wherever OpenTTD 1.8.0 runs (see game-openttd). Not tested on 98.

## Download

- Official CDN: https://cdn.openttd.org/opengfx-releases/0.5.5/ (opened). released.txt: 2019-03-21.
- URL: https://cdn.openttd.org/opengfx-releases/0.5.5/opengfx-0.5.5-all.zip
- Published checksum: manifest.yaml (same folder) lists size 3548368, sha256 c648d56c41641f04e48873d83f13f089135909cc55342a91ed27c5c1683f0dfe: **MATCH**.
- Version choice: 0.5.5 (2019-03) is contemporary with OpenTTD 1.8/1.9. Later versions: 0.6.x (2020) adds sprites for later OpenTTD features; 7.0 (2021) "Add: GUI sprites for OpenTTD 12.0"; 7.1 fixes; 8.0 (2026). The 7.1 README says it "requires OpenTTD 1.2.0 or newer", so newer sets may also load, but 0.5.5 is the conservative choice. Not tested.
- File: opengfx-0.5.5-all.zip, 3,548,368 bytes
  - SHA-256: c648d56c41641f04e48873d83f13f089135909cc55342a91ed27c5c1683f0dfe
  - MD5: cf41c942797a874e3fb411ddaa123fe3

## Archive contents

- opengfx-0.5.5-all.zip contains one file, opengfx-0.5.5.tar (5,324,800 bytes), with folder opengfx-0.5.5\: ogfx1_base.grf, ogfxc_arctic.grf, ogfxh_tropical.grf, ogfxt_toyland.grf, ogfxi_logos.grf, ogfxe_extra.grf, opengfx.obg, license.txt, readme.txt, changelog.txt.
- OpenTTD reads base sets directly from .tar files in its baseset folder (OpenTTD readme: "OpenTTD can read inside tar files"), so the tar is not unpacked.

## Windows Defender

Windows Defender (engine 1.1.26080.3, signatures 1.459.466.0), `MpCmdRun.exe -Scan -ScanType 3 -File <folder> -DisableRemediation` on 2026-09-29: "found no threats".

## License

- LICENSE.TXT in this folder: license.txt (inside opengfx-0.5.5.tar in opengfx-0.5.5-all.zip).

## Matching source (hosted)

- Source: https://cdn.openttd.org/opengfx-releases/0.5.5/opengfx-0.5.5-source.tar.xz, 9,639,584 bytes, sha256 8958246839dcb8d15548459a3979fdbcd6f92118ecc36f3d982bd8d856502e01; manifest.yaml lists the same size and sha256: **MATCH**. Hosted in src\.

## Security

NVD keyword "opengfx": 0 results. Data only.

## Install behaviour

- `Depends: game-openttd`; `Install: unzip {dir:game-openttd}\baseset` puts opengfx-0.5.5.tar into OpenTTD's baseset folder. Beacon records the file it created, so removing game-opengfx removes only the tar.
- No shortcut, no registry entries.
- Installed-Size in ENTRY.TXT: 5200 KB (unpacked size of the archive).

## Verification notes

- Opened or downloaded and read: the archive(s) above (listed with 7-Zip 26.03 on the host; text files extracted and read; no program was run), the license files quoted, and the web pages cited as "opened".
- Nothing here comes from search-engine snippets.
- Not verified: running the game on Windows 95/98/ME (no VM interaction).
