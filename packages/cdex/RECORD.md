# CDex 1.51 - Beacon 98 record

- Date checked: 2026-09-29
- Package: CDex CD ripper (Albert L. Faber / Georgy Berdyshev)
- Version: 1.51 (non-Unicode)
- License: GPL (version of the 1.51 files not verified; the current site shows GPL v3)
- Status: **BLOCKED - the files cannot be downloaded today.** Nothing was downloaded; no hash, no Defender scan.

## Windows 9x support evidence

- https://cdex.mu/download (opened), section "CDex 1.51 (old version) / Non Unicode (all Windows versions)": "Installer: Download for Windows 9x series (95, 98, ME)" and "ZIP Archive: Download for Windows 9x series (95, 98, ME)", both pointing to:
  - https://mirror.cdex.mu/CDex%201.51%20release/cdex_151.exe
  - https://mirror.cdex.mu/CDex%201.51%20release/cdex_151.zip
- The same page offers CDex 2.24 ("for Windows 10/8/7/Vista/XP") and 1.77 portable. The 1.7x/2.x line is where the adware installers appeared; 1.51 predates them. Batch 2's claim that 1.51 is the last adware-free 9x version is consistent with this but I could not open the 1.51 files to confirm there is no bundled offer.

## Download

- Both 1.51 links return `301` to `http://cdex.mu/download` (the page itself), i.e. the files are gone from the mirror. Other files on the same mirror work (CDex-2.24.exe and CDex-1.77-portable-unicode.zip return 200).
- Also tried: `https://mirror.cdex.mu/cdex_151.exe`, `.../CDex%201.51/cdex_151.exe` (404), and the old SourceForge project `cdexos` (the project page now redirects to a SourceForge directory page; `downloads.sourceforge.net/project/cdexos/...` paths return 404).
- The Internet Archive, the only other permitted source for a GPL program whose own server no longer has it, returned "Temporarily Offline" / 429 today.

## License

- https://cdex.mu/license (opened): "CDex is licensed under the GNU GENERAL PUBLIC LICENSE 3". For 1.51 (2000s) the license was GPL v2 per batch 2, from memory; not verified.
- Source: https://cdex.mu/sourcecode (opened) only mentions an SVN server (the address is missing from the page) and "CDex 1.70 Beta 2 source code" (no link). No 1.51 source found.
- CDex 1.51 bundles lame_enc.dll (LGPL) and other codec DLLs; which versions is unknown without the files.

## Security

- NVD keyword "CDex": CVE-2009-1039 (buffer overflow via a crafted Ogg Vorbis info header, CDex 1.70b2, CVSS2 7.5). Whether 1.51 has the same Ogg tag code is unknown. The other three hits (CVE-2024-2463/2464/2465) are an unrelated web application called CDeX.

## Install behaviour

- Unknown (files not obtained). The site offers both an installer and a ZIP.

## What would unblock it

- Retry the Internet Archive (e.g. captures of `mirror.cdex.mu/CDex%201.51%20release/cdex_151.exe` or the old SourceForge `cdexos` files, together with `cdex_151_src.zip` if it exists) when it is back online, or ask the CDex maintainers to restore the 1.51 files. External is not possible: the mirror no longer serves them.
