# Herc9x 0.6 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Herc9x, "Hercules Display Driver for Windows 95/98", by FalconFour
- Version: 0.6 (GitHub release v0.6, 2026-02-22; herc9x.inf DriverVer=02/15/2026,1.2026.0.0)
- License: MIT (repository LICENSE) - hosted
- Availability: hosted

## Windows 9x support evidence

- install.txt: "Herc9x - Hercules Display Driver for Windows 95/98". README: "Windows 95/98 display driver for the Hercules
  Graphics Card (and compatibles)... 720x348 pixels, 1 bit per pixel". "Tested on 86Box (Hercules emulation) and real
  Hercules-class hardware (Winbond W86855AF)". Windows ME not mentioned (so not listed). No KernelEx.
- README "Origin": built on VMDisp9x (MIT).

## Download

- URL: https://github.com/FalconFour/Herc9x/releases/download/v0.6/Herc9x-v0.6.zip
- File: Herc9x-v0.6.zip, 109,786 bytes; SHA-256 76231e645b97bfa99eb46f90abb23e1ad81b3906234b5656e8d9979b38b8e241
- Published checksum: none.

## Windows Defender

Scan on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

LICENSE.TXT = https://raw.githubusercontent.com/FalconFour/Herc9x/main/LICENSE (MIT). The ZIP itself has no license
file; the MIT notice is shipped by Beacon as LICENSE.TXT. Source at the GitHub repository (not required by MIT).

## Hardware IDs

None: the Hercules card is 8-bit ISA without Plug and Play. herc9x.inf uses the private ID `Display_Herc9x`. No
Hardware field.

## Security

None known.

## Install behaviour

- ZIP: root herc9x.inf, hercmini.drv, hercmini.vxd, bsplash.exe, install.txt; W9XHERC\ (another copy with
  HERCULES.DRV, setupmod.exe, README.TXT).
- INF-only via Display Properties > Have Disk (install.txt), or manual SYSTEM.INI edit. No uninstaller.
  Beacon: `Install: unzip {pf}\Drivers\Herc9x`, `Uninstall: files`.

## Verification notes

- Verified [V]: releases API, README, install.txt, INF, LICENSE.
- Not verified: hardware behaviour. Niche package (needs a Hercules card; usually as the only display).
