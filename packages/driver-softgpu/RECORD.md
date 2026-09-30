# SoftGPU 0.8.2025.53 - Beacon 98 record

- Date checked: 2026-09-29
- Package: SoftGPU, "SW and HW accelerated GPU driver for Windows 9x Virtual Machines", by JHRobotics
- Version: 0.8.2025.53 (release v0.8.2025.53, published 2025-07-29; version.txt: "version: 0.8.2025.53, build date:
  2025-07-29"). GitHub API `releases/latest` = v0.8.2025.53. The changelog.txt inside tops out at 0.8.2025.52 ("VESA
  display driver", "VBOX: page fault in VBox VGA driver", "fixed corrupted driver inf in some cases").
- License: MIT for SoftGPU; the archive bundles LGPL/GPL components and Microsoft redistributables
- Availability: external (project's own GitHub release; https only - `http://github.com` did not connect, which is fine
  because Beacon carries its own TLS)

## Windows 9x support evidence

- readme.txt: "Windows 95/98/Me as VM guest system (or main system at bare metal)". Windows 98/Me: "required is last
  version of DirectX 9" (included); Windows 95: DirectX 8, VC6 runtime, OpenGL 95, DCOM95, Winsock 2 (all included);
  Windows 95 needs TCP/IP installed first and manual driver installation via Device Manager. "Windows 98 SE is
  recommended". No KernelEx.
- Hypervisors (GitHub README): VirtualBox 5.2-7.0 (VBoxVGA, VBoxSVGA, VMSVGA), VMware Workstation 16/17 (SVGA II),
  QEMU 7.x/8.0 (std, vmware, qemu-3dfx). Renderers: softpipe, llvmpipe (needs SSE), SVGA3D, qemu-3dfx.

## Download

- Release page: https://github.com/JHRobotics/softgpu/releases/tag/v0.8.2025.53
- URL: https://github.com/JHRobotics/softgpu/releases/download/v0.8.2025.53/softgpu-0.8.2025.53.zip
- Alternatives: softgpu-0.8.2025.53.iso (477,411,328 bytes) and .iso.xz - the ISO is the intended VM route (attach as CD);
  Beacon cannot install an ISO, so the ZIP is used.
- File: softgpu-0.8.2025.53.zip, 264,746,503 bytes (266 entries, 465,445 KB unpacked)
- SHA-256: 287449f16ad234da1d546deac66b3f91ab3101f5d3a202472117b83de42ccc68
- Published checksum: none.

## Windows Defender

Scan of D:\Win98SE\beacon\packages\driver-softgpu on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0):
"found no threats".

## License

- license.txt / license_mesa.txt: MIT (JHRobotics). license_wine.txt: Wine, LGPL 2.1+. license_openglide.txt: LGPL 2.1.
  extras\qemu3dfx\license.txt: GPL 2. simd95\license.txt: own license.
- Microsoft redistributables inside: redist\dx8_2000, redist\dx9_2004, redist\dx9_2006 (DirectX redist cabs),
  redist\dcom95.exe, redist\vc6redist.exe, redist\ws2setup.exe, redist\opengl95 (its README: "application developers may
  freely redistribute from this SDK along with their applications"), redist\setupapi.dll. These are licensed for
  redistribution with an application by its developer, not for re-hosting by us; plus LGPL parts would oblige us to
  offer source. Therefore external. LICENSE.TXT is a composite: our summary, then SoftGPU MIT, Mesa MIT, Wine and
  OpenGlide license texts.

## Hardware IDs (driver\sse3-w98\vmdisp9x.inf, DriverVer=07/29/2025,4.2025.1.119)

PCI\VEN_80EE&DEV_BEEF&SUBSYS_00000000 (VBox VGA), PCI\VEN_80EE&DEV_BEEF&SUBSYS_040515AD (VBox SVGA),
PCI\VEN_15AD&DEV_0405&SUBSYS_040515AD (VMware SVGA II / VirtualBox VMSVGA), PCI\VEN_1234&DEV_1111 (QEMU std VGA),
PCI\CC_0300 and *PNP0900 (VESA fallback, omitted from ENTRY.TXT). Commented out: VEN_15AD&DEV_0406, VEN_1B36&DEV_0100.

## Security

No advisories found. It replaces display drivers and installs 2004-2006 DirectX runtimes; treat as experimental.

## Install behaviour

- ZIP with the setup at the root: softgpu.exe (196,001 bytes, MinGW-built GUI setup), softgpu.ini, driver\mmx-w95 and
  driver\sse3-w98 driver sets, redist\, extras\, tools\, html\ docs.
- readme: "Run setup with softgpu.exe - Select Hypervisor preset to match your VM software - Press Install!".
  No documented silent switch. Nothing found about an Add/Remove Programs entry (unknown).
- Beacon: `Install: unzip {pf}\SoftGPU Setup`, `After: run "{dir}\softgpu.exe"` (interactive), `Uninstall: files`
  (removes the unpacked setup files only; the installed driver and DirectX stay).
- Readme advice copied into the Warning: install audio drivers before SoftGPU (they overwrite DirectX files).

## Verification notes

- Verified [V]: GitHub releases API, the ZIP listing, readme.txt, changelog.txt, version.txt, license files, INF.
- Not verified: the setup's behaviour (not run), whether it writes an uninstaller.
