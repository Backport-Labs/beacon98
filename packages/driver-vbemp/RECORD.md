# VBEMP 9x (Universal VBE 9x Display Driver) 2019.12.01 - Beacon 98 record

- Date checked: 2026-09-29
- Package: VBEMP.DRV, "Universal VBE 9x Display Driver Project", by Bearwindows and JW Soft
- Version: "Release version beta 2019.12.01" (page https://bearwindows.zcm.com.au/vbe9x.htm); INF DriverVer =
  12/01/2019, 19.12.0001. The ZIP was repacked later: folder entries and the new 1632bit\vbemp.inf are dated
  2026-03-31; VBEMP.DRV and vbemp.inf in 032MB/064MB/128MB are dated 2019-11-30.
- License: freeware, non-commercial use only, redistribution restricted (see below)
- Availability: external (authors' own server)

## Windows 9x support evidence

- Page (WebFetch summary [V]): supports Windows 95, 98, Me ("latest Service Pack recommended") and 9x clones. No KernelEx.

## Download

- URL: https://bearwindows.zcm.com.au/191201.zip (also linked: http://www.navozhdeniye.narod.ru/191201.zip, not tested)
- `curl -I --http1.0 http://bearwindows.zcm.com.au/191201.zip` -> 301 to the https address (IIS/Plesk).
- File: 191201.zip, 35,085 bytes; SHA-256 93d9bd34fc82904e827e0f4a5cee28beb3013c5d3d8b9730b5367a74b06acd3d
- Published checksum: none. Because the ZIP was repacked in 2026 without a version change, the hash may change again
  if the authors repack it; Beacon would then refuse the file until the entry is updated.

## Windows Defender

Scan on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license file in the ZIP. LICENSE.TXT is the "License" section of the project page, copied 2026-09-29.
- Key terms: "Anyone may use this software free for noncommercial use only." "The driver, may be freely distributed ...
  provided the distribution package is not modified." "The driver may not be bundled or distributed with any other
  package without written permission of the copyright holder. ... unauthorized site content mirroring is strictly
  prohibited." "You may not ... transfer the licensed program".
- Hosting it in a package manager's pool is arguably "mirroring" and "distributing with another package"; not
  certain to be allowed, so external. (Could be hosted with written permission from the authors.)

## Hardware IDs (064MB\vbemp.inf)

Generic: 43 lines `PCI\VEN_xxxx&CC_0300` (vendor + display class, e.g. VEN_1002 ATI, VEN_10DE nVidia, VEN_8086 Intel,
VEN_5333 S3, VEN_15AD VMware, VEN_1039 SiS, VEN_1023 Trident, VEN_102B Matrox, VEN_1106 VIA, VEN_121A 3dfx), plus
PCI\CC_0300, PCI\CC_0301, PCI\CC_0380, *PNP0900, *PNP0917, NOPNP. No device-specific IDs. ENTRY.TXT uses one
`pci CC_0300` line (a class code, not a VEN/DEV pair) to mark it as a universal fallback.

## Security

None known. Not searched in NVD (web-search budget exhausted).

## Install behaviour

- ZIP layout: 032MB\, 064MB\, 128MB\ (each VBEMP.DRV, VBE.vxd, vbemp.inf), 1632bit\vbemp.inf (INF only).
- INF-only; no setup program, no Add/Remove Programs entry. `Install: unzip {pf}\Drivers\VBEMP`, `Uninstall: files`,
  Notice pointing Device Manager at the folder.

## Verification notes

- Verified [V]: project page (license, version, links), ZIP listing, INF, http behaviour.
- Not verified: which folder suits which card beyond the folder names (video memory limit).
