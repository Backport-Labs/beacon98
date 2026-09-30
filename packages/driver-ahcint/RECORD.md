# AHCINT 1.3.0.0 - Beacon 98 record

- Date checked: 2026-09-29
- Package: AHCINT, "SATA AHCI Driver for Windows NT/2000/XP and Windows 95/98/Me", by ages2001
- Version: 1.3.0.0 (GitHub release v1.3.0.0, published 2026-09-29 16:03 UTC; AHCINT9X.INF DriverVer=09/29/2026,1.3.0.0).
  Project is weeks old: 1.1.0.0 on 2026-09-21, 1.2.0.0 on 2026-09-25.
- License: conflicting statements (see below)
- Availability: external (author's GitHub release) until the license is clarified; could become hosted.

## Windows 9x support evidence

- README.md: targets "Windows 95 / 98 / Me (x86) - SCSIPORT.PDR miniport (ahcint9x.mpd)". "Windows 9x/Me setup itself runs
  through the BIOS (INT 13h) ... install AHCINT9x once Windows is up." Windows 95 RTM: SCSIPORT.PDR from the AMDK6 update
  may be needed (Beacon has `ms-amdk6upd-95`). Disks over 2 TB need LBA64HLP.VXD (SweetLow). No KernelEx.
- Known limitations (README): no NCQ, polling only (no interrupts), ~128 KB max transfer, no hot-plug, 32-bit DMA only on 9x.

## Download

- URL: https://github.com/ages2001/AHCINT/releases/download/v1.3.0.0/AHCINT-v1.3.0.0.zip
- File: AHCINT-v1.3.0.0.zip, 140,341 bytes; SHA-256 e0930ac2928e299548aa9a82749d42fc6c8cff10b4a590a7d312445ff1cf85ea
- Published checksum: none.

## Windows Defender

Scan on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- Repository LICENSE file: GNU GPL version 3 (GitHub also detects GPL-3.0).
- README.md "License" section: "Copyright (c) 2026 ages2001. All rights reserved. USE AT YOUR OWN RISK."
- The release ZIP contains no license file (it does contain src\).
- Because the statements conflict, the package is external. If the author confirms GPL-3.0, it can be hosted: the ZIP
  already includes the source (src\), but a tag source archive should be added under src\ as well.
- LICENSE.TXT = our note on the conflict + the GPL-3.0 text from the repository.

## Hardware IDs (bin\9X\AHCINT9X.INF)

`PCI\CC_010601` (Mass storage, SATA, AHCI 1.0) only. README: the driver also knows some AMD/Intel device IDs
internally for detection, not in the INF. ENTRY.TXT: `pci CC_010601`.

## Security

None known. Kernel-mode storage driver, very new; data-loss risk is the main concern (Warning).

## Install behaviour

- ZIP: bin\9X\AHCINT9X.INF + AHCINT9X.MPD (9x); bin\NT, bin\2KXP (other systems); src\.
- INF-only: Add New Hardware > SCSI controllers > Have Disk > bin\9X; the MPD is copied to WINDOWS\SYSTEM\IOSUBSYS.
  No uninstaller. Beacon: `Install: unzip {pf}\Drivers\AHCINT`, `Uninstall: files`.

## Verification notes

- Verified [V]: releases API, README.md, LICENSE, ZIP listing, AHCINT9X.INF.
- Not verified: operation in VirtualBox or on hardware.
