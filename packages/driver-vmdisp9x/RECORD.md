# VMDisp9x 1.2025.0.119b (2D driver) - Beacon 98 record

- Date checked: 2026-09-29
- Package: VMDisp9x, "Virtual Display driver for Windows 95/98/Me", by JHRobotics (Jaroslav Hensl)
- Version: 1.2025.0.119b (release tag v1.2025.0.119, published 2025-07-29; version.txt inside: "version: 1.2025.0.119,
  build date: 2025-08-03"; INF DriverVer=08/03/2025,4.2025.0.119). Latest release per the GitHub API `releases/latest`.
- License: MIT (license.txt in the archive) - hosted
- Availability: hosted

## Windows 9x support evidence

- readme.txt in the archive: "Virtual Display driver for Windows 95/98/Me. Supported devices are: Bochs VBE Extensions
  (Bochs: VBE, VirtulBox: VboxVGA, QEMU: std-vga); VMWare SVGA-II (VMWare Workstation/Player, VirtulBox: VMSVGA, QEMU:
  vmware-svga); VBox SVGA (VirtulBox: VBoxSVGA); Any video adapter with VESA BIOS Extension 2.0/3.0". Tested with
  VirtualBox 6.0-7.x, VMware Player 16 / Workstation 17, QEMU 7.x/8.0. No KernelEx needed.
- 2D only in this archive: "2D driver is very generic ... 3D part required my Mesa port" (Mesa9x). For 3D the
  project points to SoftGPU (package `driver-softgpu`, which contains this same driver).

## Download

- Release page: https://github.com/JHRobotics/vmdisp9x/releases/tag/v1.2025.0.119
- URL: https://github.com/JHRobotics/vmdisp9x/releases/download/v1.2025.0.119/vmdisp9x-1.2025.0.119b-driver-2d.zip
- Alternatives on the same release: .img/.ima floppy images of the same files; -driver-3d-win95/-win98 zips/ISOs
  (33-35 MB, include Mesa9x) - not packaged; SoftGPU is the user-friendly 3D route.
- File: vmdisp9x-1.2025.0.119b-driver-2d.zip, 355,886 bytes
- SHA-256: e0d698a6089347a6a619ed439c092f247392fbafac6b342f4651c1380911fb23
- Published checksum: none published.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-vmdisp9x -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT = license.txt from the archive: MIT License, Copyright (c) 2022 JHRobotics. Permits redistribution of
  unmodified (and modified) copies; condition: keep the copyright and permission notice (LICENSE.TXT is shipped).
- The driver is based on Michal Necasek's boxv9x VirtualBox driver and Philip Kelley's QEMU changes (readme "Origin").
  vmhal9x.dll/vmhal486.dll come from the MIT-licensed VMHal9x project (https://github.com/JHRobotics/vmhal9x).
- Source is not required by MIT; it is at https://github.com/JHRobotics/vmdisp9x (tag v1.2025.0.119). Not downloaded.

## Hardware IDs (vmdisp9x.inf, [Mfg.VM])

| INF entry | ID |
|---|---|
| VBoxVideoVGA | PCI\VEN_80EE&DEV_BEEF&SUBSYS_00000000 |
| VBoxVideoSVGA | PCI\VEN_80EE&DEV_BEEF&SUBSYS_040515AD |
| VBoxVideoVM2 (VMware SVGA II / VirtualBox VMSVGA) | PCI\VEN_15AD&DEV_0405&SUBSYS_040515AD |
| QemuStd | PCI\VEN_1234&DEV_1111 |
| VESAPCI (generic) | PCI\CC_0300 |
| VESAISA (generic) | *PNP0900 |

Commented out in the INF: PCI\VEN_15AD&DEV_0406 (SVGA3), PCI\VEN_1B36&DEV_0100 (QXL). ENTRY.TXT lists the three
specific VEN/DEV pairs; the class-code and *PNP0900 matches are omitted so Beacon does not propose it for all PCs.

## Security

No advisories or CVEs found for VMDisp9x (GitHub repository has no security advisories; NVD not searched because the
session's web-search budget was used up). Kernel-mode driver of a hobby project; treat as experimental.

## Install behaviour

- Plain ZIP, flat layout (no folders): boxvmini.drv/.vxd, qemumini.drv/.vxd, vmwsmini.drv/.vxd, vesamini.drv/.vxd,
  vmdisp9x.dll, vmhal9x.dll, vmhal486.dll, vmdisp9x.inf, tray3d.exe, vesamode.exe, license.txt, readme.txt, version.txt.
- INF-only: no setup program, nothing registered in Add/Remove Programs. Beacon unpacks to {pf}\Drivers\VMDisp9x
  (`Install: unzip {pf}\Drivers\VMDisp9x`, `Uninstall: files`) and the Notice tells the user to use Device Manager,
  Update Driver, Have Disk with that folder. Removing the package only deletes the copy; the installed driver stays.
- readme: resolutions above 1920x1200 must be enabled in the INF; `vesamode /insert /24` or the tray icon updates the
  VESA mode list.

## Verification notes

- Opened/verified [V]: GitHub releases API, the archive listing, license.txt, readme.txt, version.txt, vmdisp9x.inf.
- Not verified: behaviour inside a VM (no VM used, as instructed).
