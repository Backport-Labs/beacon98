# xhci98 1.1.1.0 - Beacon 98 record

- Date checked: 2026-09-29
- Package: xhci98, "an xHCI host controller miniport driver" by Yeo Kheng Meng (https://github.com/yeokm1/xhci98)
- Version: 1.1.1.0 (GitHub release v1.1.1.0, 2026-09-23; readme.txt "Released 2026-09-24"; INF DriverVer=09/24/2026,1.1.1.0).
  Very young project: first releases in September 2026 (1.0.2.0 on 2026-09-08, 1.1.0.0 on 2026-09-19).
- License: GPL-2.0-only - hosted with source
- Availability: hosted

## Windows 9x support evidence

- readme.txt: "USB 2.0 for Windows 98 SE, ME, 2000, XP, Vista and 7 on xHCI-only machines". "Only Windows 98 SE has
  been validated on real hardware; the rest in virtual machines only." Windows 98 first edition and 95 are not
  supported. No KernelEx.
- Prerequisite (readme section 2/4): "On Windows 98: NUSB 3.3 or the newer SweetLow USB 2.0 stack ... installed
  BEFORE this driver"; "On Windows ME: SweetLow's USB 2.0 stack ... NOT NUSB". Both stacks are built from Microsoft
  USB files (NUSB from Windows ME files; SweetLow's is "the newer Windows XP lineage of the same port driver"), so
  Beacon cannot offer them (NUSB is explicitly rejected for the catalog). ENTRY.TXT uses
  `Requires: file {win}\SYSTEM32\DRIVERS\USBPORT.SYS` with a text; the exact install path of USBPORT.SYS under each
  stack was not verified - check before publishing.
- The Windows CD is needed: the INF has Windows copy its own usbd.sys, usbhub.sys and usbui.dll.

## Download

- URL: https://github.com/yeokm1/xhci98/releases/download/v1.1.1.0/xhci98-1.1.1.0.zip
- File: xhci98-1.1.1.0.zip, 377,889 bytes; SHA-256 4d29346712e25b5adbf6c55915092f77483eacffeef9e3770b2acada561a525f
- Published checksum: none found on the release.

## Source

- src\xhci98-1.1.1.0-source.zip from https://github.com/yeokm1/xhci98/archive/refs/tags/v1.1.1.0.zip,
  9,609,625 bytes, SHA-256 5a3fb1b220441c468eb9adca09968c3e0ebc23adf7449e8a7776fc108e02fa84.
- Per LICENSE scope note: XHCIQUAL.EXE statically contains the DOS/32 Advanced extender and the Open Watcom C runtime,
  XHCISNAP.EXE the Visual C++ 6.0 C runtime; each has a NOTICE.TXT in the download. Their sources are not in the tag
  archive (DOS/32A and Open Watcom are open source elsewhere; the VC6 runtime is Microsoft's, redistributable as part
  of a program). The driver xhci98.sys contains no third-party code (LICENSE scope note).

## Windows Defender

Scan on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

LICENSE.TXT = LICENSE from the archive: GPL version 2 ("SPDX-License-Identifier: GPL-2.0-only") plus the project's
scope note. Redistribution of unmodified binaries is allowed with the license text and the corresponding source
(offered from the same place: `Source:` line).

## Hardware IDs (release-x86\xhci98.inf)

Only the class code `PCI\CC_0C0330` (xHCI). No VEN/DEV pairs. ENTRY.TXT: `pci CC_0C0330`.

## Security

None known (new project, no advisories). Kernel-mode driver; experimental.

## Install behaviour

- ZIP: release-x86\, release-x64\, debug-x86\, debug-x64\ (xhci98.inf + xhci98.sys each), xhciqual\ (DOS
  qualification tool), xhcisnap\, LICENSE, readme.txt.
- INF-only: Device Manager > Update Driver > Specify a location > RELEASE-X86\. No uninstaller registered.
  Beacon: `Install: unzip {pf}\Drivers\xhci98`, `Uninstall: files`.
- readme suggests running XHCIQUAL.EXE from real DOS first to check the controller; mentioned in the Notice via the readme.

## Verification notes

- Verified [V]: releases API, LICENSE, readme.txt (sections 2-4), INF.
- Not verified: behaviour on hardware; USBPORT.SYS path under NUSB/SweetLow.
