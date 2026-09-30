# nvme9x (SweetLow) - Beacon 98 record

- Date checked: 2026-09-29
- Package: nvme9x, "NVMe driver for Windows 9x", SweetLow (GitHub LordOfMice/Tools; also http://sweetlow.orgfree.com/)
- Version: INF DriverVer=11/24/2025,1.0.0.2; nvme2k.mpd dated 2026-02-18. The file sits in the repository (no releases),
  last changed in commit 24a466f0529eb62552900c26a34d4e7131e42f44 on 2026-02-19 ("Fixed: I/O Resource in BAR1+ breaks
  work."). Version in ENTRY.TXT: "1.0.0.2 (2026-02-19)".
- License: none stated for SweetLow's work; upstream nvme2k is BSD-3-Clause
- Availability: external (the author's own repository)

## Windows 9x support evidence

- readme.eng.txt: "NVMe driver for Windows 9x. Base: nvme2k 1.0.0.2 https://github.com/techomancer/nvme2k. Changes: Port
  for Windows 9x, 64-bit LBA & Fixes ... added SCSI 64-bit LBA commands processing (large drives support). Tested on
  Windows 9x ONLY ... Install and uninstall as usual hardware, nothing specific."
- Repository README: "nvme9x - Port for Windows 9x, 64-bit LBA & Fixes of the base nvme2k 1.0.0.2 - Windows 9x
  installation"; "lba64hlp - SCSI LBA 64-bit Helper Driver for Windows 9x" (for >2 TB). 95/98/ME: the readme says
  "Windows 9x" without detail; ME/95 not separately confirmed.

## Download

- Pinned URL: https://raw.githubusercontent.com/LordOfMice/Tools/24a466f0529eb62552900c26a34d4e7131e42f44/nvme9x.zip
  (identical bytes to .../master/nvme9x.zip on 2026-09-29; ETag = its SHA-256). Pinning to the commit keeps the hash
  valid when the author updates the file. raw.githubusercontent.com over http answers 301 to https.
- File: nvme9x.zip, 14,428 bytes; SHA-256 9c4010c1c180e9892bf5576fd9bbf22978a1aaddc7c5ed52527755f62cd5a39f
- Published checksum: none (GitHub's ETag matches).

## Windows Defender

Scan on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license file in the ZIP or the repository (GitHub license: none). SweetLow's modifications and nvmevsd.vxd are
  therefore all rights reserved; not hostable. The sources are published as nvme2k-src.zip in the same repository.
- nvme2k (Dominik Behr) is BSD-3-Clause (text included in LICENSE.TXT); it allows binary redistribution, but it does
  not license SweetLow's own additions.

## Hardware IDs (nvme9x.inf)

`PCI\CC_010802` (NVM Express) only. ENTRY.TXT: `pci CC_010802`.

## Security

None known.

## Install behaviour

- ZIP (flat): nvme2k.mpd, nvmevsd.vxd, nvme9x.inf, readme.eng.txt, readme.rus.txt. INF class SCSIAdapter, files to
  IOSUBSYS (DestDir 12). INF-only; no uninstaller. Beacon: `Install: unzip {pf}\Drivers\nvme9x`, `Uninstall: files`.

## Verification notes

- Verified [V]: repository README, commits API, ZIP contents, INF, readme, nvme2k license.
- Not verified: hardware behaviour.
