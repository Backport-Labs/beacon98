# Windows 95/98/ME hardware drivers for Beacon 98 - survey

Date: 2026-09-29. Scope: drivers we may host (open source, or a license that explicitly allows redistributing the
unmodified files) or that the vendor still serves from its own server (external). Nothing from abandonware sites,
driver portals or third-party mirrors. NVIDIA ForceWare 81.98 / 71.84 already exist (`nvidia-forceware`,
`nvidia-forceware-tnt`) and are not repeated.

Method note: the session's web-search budget ran out at the start, so everything comes from opening vendor pages,
the GitHub API, curl against vendor servers and the downloaded files. [V] = verified by opening the page or file;
[S] = from general knowledge or a snippet, not verified. Nothing was executed; archives were listed or extracted with
7-Zip/.NET into temp folders. Every package folder was scanned with Defender (engine 1.1.26080.3, signatures
1.459.466.0): no threats in any of them. Details, hardware IDs and license texts are in each package's RECORD.md.

## Summary

- Packages created: **24** - **3 hosted**, **21 external**.
  - Hosted: `driver-vmdisp9x` (MIT), `driver-xhci98` (GPL-2.0, source in src\), `driver-herc9x` (MIT).
  - External: `driver-softgpu`, `driver-vbemp`, `driver-ahcint`, `driver-nvme9x`, `driver-ati-catalyst`,
    `driver-ati-rage128`, `driver-ati-rage-pro`, `driver-matrox-g-series`, `driver-matrox-millennium`,
    `driver-matrox-millennium2`, `driver-via-prosavage`, `driver-via-prosavageddr`, `driver-via-vinyl-ac97`,
    `driver-via-envy24`, `driver-via-rhine`, `driver-via-velocity`, `driver-via-hyperion`, `driver-via-4in1`,
    `driver-via-usb2`, `driver-promise-ultra`, `driver-promise-fasttrak`.
- Qualify but not packaged: Velocity9x (hostable; author calls it an engineering build), VMware Tools for pre-2000
  Windows (external; ISO only), and several niche vendor drivers listed below.
- Empty or blocked categories:
  - **Printers/scanners: empty.** Brother and Epson still list 98 drivers, but their download links are hidden
    behind JavaScript or a EULA button (no stable URL). HP's FTP times out; Canon and Lexmark were not resolved.
  - **Sound drivers for VMs: empty.** Realtek AC'97 A4.06 and Creative ES1371/AudioPCI/SB Live are still on the
    vendors' own sites, but each download is behind a CAPTCHA with one-time links. hda9x (open-source HD Audio)
    has no license and no release. Windows 98's built-in SB16 driver covers VirtualBox/QEMU SB16.
  - **Realtek network: blocked** by the same CAPTCHA (RTL8139/8169 98/ME drivers exist on realtek.com).
  - Vendors gone or no longer serving 9x: 3dfx, S3 Graphics (discrete), SiS, Trident, ALi/ULi, Silicon Image,
    HighPoint, 3Com, Aureal, ESS, Yamaha, Davicom, M-Audio, Terratec.
  - Unresolved (needs a real web search or JavaScript): Intel (graphics, LAN, INF/IAA), Broadcom, Marvell, Netgear,
    Linksys, Atheros, NEC USB 2.0, Adaptec, Canon, Lexmark, SoundMAX, Turtle Beach, Cirrus, SigmaTel.
- Rejected: NUSB (built from Microsoft Windows ME files); SweetLow's USB 2.0 stack (Microsoft XP-lineage USBPORT);
  both are needed by xhci98, which therefore carries a `Requires` line instead.
- Cross-cutting issues:
  - Almost every vendor server is HTTPS-only now (VIA's CloudFront, Matrox, AMD, GitHub); plain http answers
    301/522. Beacon's own TLS is required for these.
  - AMD needs `Referer: https://www.amd.com/` (ATI entries use the `Referer` field).
  - Promise URLs end in a query (`DownloadFile.aspx?DownloadFileUID=3258`), so the client saves them as `3258`;
    `unzip` must detect ZIP by content.
  - Almost no setup program has a documented silent switch; most entries run setup interactively or are INF-only
    with a Device Manager Notice.
  - Very new open-source projects (xhci98, AHCINT, Velocity9x, all 2026) change weekly; entries will need refreshes.
  - New ENTRY.TXT field `Hardware:` uses `pci VEN_xxxx&DEV_yyyy`; for class-code-only drivers it uses
    `pci CC_xxxxxx` (VBEMP, xhci98, AHCINT, nvme9x). The client needs to treat class codes as generic matches.

## 1. Virtual machine guest drivers

| Vendor / project | Device family | Last 9x version | Served by vendor? | URL | License | Hostable? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|---|---|---|
| JHRobotics VMDisp9x | VirtualBox VBoxVGA/VBoxSVGA/VMSVGA, VMware SVGA II, QEMU std VGA, VESA | 1.2025.0.119b (2025-07-29) | yes (GitHub releases) | https://github.com/JHRobotics/vmdisp9x/releases/download/v1.2025.0.119/vmdisp9x-1.2025.0.119b-driver-2d.zip | MIT | yes | **hosted** `driver-vmdisp9x` | MIT, 2D ZIP contains only JHRobotics files | [V] |
| JHRobotics SoftGPU | same + 3D (Mesa, Wine D3D, Glide wrappers) | 0.8.2025.53 (2025-07-29) | yes (GitHub) | https://github.com/JHRobotics/softgpu/releases/download/v0.8.2025.53/softgpu-0.8.2025.53.zip | MIT + LGPL/GPL parts + Microsoft redistributables | no | **external** `driver-softgpu` | Bundles DirectX 8/9 redist, DCOM95, VC6 runtime, Winsock 2, OpenGL 95 | [V] |
| Bearwindows/JW Soft VBEMP 9x | any VESA 2.0 card (universal) | 2019.12.01 (ZIP repacked 2026-03) | yes | https://bearwindows.zcm.com.au/191201.zip | freeware, non-commercial; no bundling, no mirroring | no | **external** `driver-vbemp` | License forbids bundling/"site content mirroring" | [V] |
| VMware (Broadcom) Tools for pre-2000 Windows | VMware SVGA, mouse, NIC in VMware | legacy 7.7.0 (winPre2k.iso) | yes | https://packages.vmware.com/tools/frozen/windows/winPre2k.iso (14,090,240 B, SHA-256 a17a11d6...1ebb) | VMware EULA (not read) | no | qualifies external, **not packaged** | ISO only (MSI + instmsia inside); Beacon has no ISO install kind | [V] |
| Oracle VirtualBox Guest Additions | - | none for 9x | no | - | - | - | no | Oracle never shipped 9x additions | [S] |
| QEMU std VGA / virtio | - | - | - | - | - | - | covered | std VGA is covered by VMDisp9x; no 9x virtio project found in GitHub search | [V] search |
| camthesaxman win9x_vm_display_driver | Bochs/QEMU VGA | v0.1-alpha (2022) | GitHub | https://github.com/camthesaxman/win9x_vm_display_driver | none stated | no | no | No license; alpha; superseded by VMDisp9x | [V] |
| boxv9x (Michal Necasek, clone volkertb/boxv9x) | QEMU/VirtualBox VGA | 2022 build (.img) | clone only | https://github.com/volkertb/boxv9x | none in clone | no | no | Superseded by VMDisp9x; no license file | [V] |
| camthehaxman hda9x | Intel HD Audio (VirtualBox/QEMU HDA) | no release | - | https://github.com/camthehaxman/hda9x | none | no | no | No license, no binaries | [V] |
| VM sound (SB16 / AC'97 / ES1371) | - | see Audio | - | - | - | - | no | SB16: built into Windows; AC'97/ES1371 vendor drivers behind CAPTCHAs | [V] |
| VM network (PCnet, NE2000, RTL8139) | - | see Network | - | - | - | - | no | PCnet and RTL8029 believed built into Windows 98 [S]; RTL8139 behind Realtek CAPTCHA | [S]/[V] |

## 1b. Other open-source 9x drivers (GitHub)

| Project | Device family | Last version | Served? | URL | License | Hostable? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|---|---|---|
| yeokm1 xhci98 | USB 3 xHCI controllers (as USB 2.0), 98SE/ME | 1.1.1.0 (2026-09-23) | GitHub | https://github.com/yeokm1/xhci98/releases/download/v1.1.1.0/xhci98-1.1.1.0.zip | GPL-2.0-only | yes | **hosted** `driver-xhci98` | Needs NUSB or SweetLow USB 2.0 stack first (Requires line) | [V] |
| ages2001 AHCINT | SATA AHCI controllers, 95/98/ME | 1.3.0.0 (2026-09-29) | GitHub | https://github.com/ages2001/AHCINT/releases/download/v1.3.0.0/AHCINT-v1.3.0.0.zip | LICENSE = GPL-3.0, README = "All rights reserved" | unclear | **external** `driver-ahcint` | Conflicting license statements; host after the author clarifies | [V] |
| SweetLow nvme9x | NVMe SSDs | 1.0.0.2 (commit 2026-02-19) | author's GitHub | https://raw.githubusercontent.com/LordOfMice/Tools/24a466f0529eb62552900c26a34d4e7131e42f44/nvme9x.zip | none stated (base nvme2k BSD-3) | no | **external** `driver-nvme9x` | No license for SweetLow's work | [V] |
| FalconFour Herc9x | Hercules mono graphics (ISA), 95/98 | 0.6 (2026-02-22) | GitHub | https://github.com/FalconFour/Herc9x/releases/download/v0.6/Herc9x-v0.6.zip | MIT | yes | **hosted** `driver-herc9x` | | [V] |
| michaeldale Velocity9x | Intel GMA 950, S3 ViRGE/DX, Trio32/64/3D, ATI Rage Mobility/Mach64, Matrox Millennium II, VBE | 0.9.1 (2026-09-29) | GitHub (SHA256SUMS published, matched) | https://github.com/michaeldale/velocity9x/releases/tag/v0.9.1 | GPL-3.0 | yes | qualifies, **not packaged** | INSTALL.TXT: "an engineering bring-up build, not a release driver"; asks for serial logging and disk backups. Revisit at 1.0 | [V] |
| zikolas cfu1-win9x | RATOC REX-CFU1 USB CF card | - | GitHub | https://github.com/zikolas/cfu1-win9x | MIT | yes | not examined | Very niche | [V] listing |
| SweetLow Tools (lba64hlp, gpttsd, cregfix, vmm4gfix) | system helpers, not device drivers | - | author's GitHub | https://github.com/LordOfMice/Tools | none stated | no | out of scope | Could be external "System" packages later | [V] |
| oerg866 win98-driver-lib-* | collections of vendor drivers | - | - | - | vendors' | no | no | Third-party redistribution of vendor files | [V] listing |
| NUSB / SweetLow USB 2.0 stack | generic USB 2.0 / mass storage | - | - | - | Microsoft files | no | **rejected** | Built from Microsoft Windows ME / XP files | [V] (xhci98 readme) |

## 2. Graphics (vendor)

| Vendor | Device family | Last 9x version | Served by vendor? | URL | License | Hostable? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|---|---|---|
| ATI/AMD | Radeon 7000-9800, X300-X850, Xpress 200 | Catalyst 6.2 (4.15.1.9165) | yes | https://drivers.amd.com/drivers/6-2_wme_dd_cp_30314.exe | ATI EULA (no redistribution) | no | **external** `driver-ati-catalyst` | Needs Referer www.amd.com | [V] |
| ATI/AMD | Rage 128 / 128 Pro | 4.13.7192 | yes | https://drivers.amd.com/drivers/WMER1284137192.exe | ATI EULA | no | **external** `driver-ati-rage128` | | [V] |
| ATI/AMD | Rage Pro / LT Pro / XL | 4.13.2655 | yes | https://drivers.amd.com/drivers/wme-j5-30-1-b02.exe | ATI EULA | no | **external** `driver-ati-rage-pro` | Readme names ME only; AMD page lists 98/ME | [V] |
| ATI/AMD | Rage II; Rage Fury MAXX | 4.10.2420; 4.12.7942 | yes | https://www2.ati.com/drivers/w82420en.exe; .../wmew98maxx4127942.exe | ATI EULA (presumed) | no | qualifies, not packaged | Niche | [V] page |
| Matrox | G200/G400/G450/G550 | 6.83.017 | yes (https only) | https://ftp.matrox.com/pub/mga/archive/win_9x/2002/w9x_683.exe | Matrox license (no distribution) | no | **external** `driver-matrox-g-series` | | [V] |
| Matrox | Millennium / Mystique / Mystique 220 | 4.12.013 | yes | https://ftp.matrox.com/pub/mga/archive/win_9x/1998/1677_412.exe | Microsoft Driver Library license inside + Matrox EULA | uncertain | **external** `driver-matrox-millennium` | Could be hostable if the MS Driver Library license covers it; left external | [V] |
| Matrox | Millennium II | 4.33.045 | yes | https://ftp.matrox.com/pub/mga/archive/win_9x/1999/w9x_433c.exe | Matrox EULA | no | **external** `driver-matrox-millennium2` | | [V] |
| Matrox | Productiva G100; Marvel/Rainbow Runner | 5.52.015; 6.28.017 | yes | ftp.matrox.com/pub/mga/archive/win_9x/... | Matrox EULA | no | qualifies, not packaged | Niche | [V] listing |
| VIA/S3 | ProSavage IGP (PL133/KL133/KM133) | 13.01.03 | yes (VIA CloudFront) | https://d34vhvz8ul1ifj.cloudfront.net/Driver/drivers/video/ProSavage/130103Util.zip | none found | no | **external** `driver-via-prosavage` | | [V] |
| VIA/S3 | ProSavageDDR (KM/KN/PM/P4M/P4N266) | 13.01.09 | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/drivers/video/ProSavageDDR/S3_wIShldlogo.zip | none found | no | **external** `driver-via-prosavageddr` | | [V] |
| VIA | Twister, KPLE, UniChrome IGPs (CLE266, KM400, K8M800, P4M800, CN700...) | various | yes | VIA portal (CloudFront) | not checked | no | qualifies, not packaged | Can be added the same way | [V] portal |
| S3 Graphics | Savage / ViRGE / Trio (discrete) | - | no | s3graphics.com is now a spam site | - | - | no | Vendor server gone | [V] |
| SiS | graphics | - | no | sis.com has no driver section | - | - | no | Not served | [V] |
| Trident | graphics | - | no | tridentmicro.com now unrelated | - | - | no | Vendor gone | [V] |
| 3dfx | Voodoo | - | no | 3dfx.com redirects to NVIDIA | - | - | no | Defunct | [V] |
| Intel | i740 / i810 / i815 | unknown | not confirmed | intel.com answered 403 | - | - | no | Removal not verified | unresolved |

## 3. Audio

| Vendor | Device family | Last 9x version | Served by vendor? | URL | License | Hostable? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|---|---|---|
| VIA | Vinyl AC'97 (686A/B, 8231, 8233-8237, 8251; also lists ICH, SiS 7012, nForce) | 7.00b (2007) | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/vinyl_v700b.zip | VIA license (personal use, no distribution) | no | **external** `driver-via-vinyl-ac97` | Probably no use in VirtualBox (SigmaTel codec) | [V] |
| VIA | Envy24HT (VT1720/1724) | 5.30b (2008) | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/Envy24_Family_DriverV530b.zip | VIA license | no | **external** `driver-via-envy24` | Last version whose setup installs on 9x | [V] |
| Realtek | AC'97 codecs | A4.06 | yes, behind CAPTCHA | https://www.realtek.com/Download/List?cate_id=594 | unknown | unknown | no | ALTCHA proof-of-work + one-time token URL | [V] |
| Creative | SB Live!, Audigy, PCI128/ES1371/ES1373, PCI64 | e.g. SBL51_W9xME.exe (2002) | yes, behind reCAPTCHA | https://support.creative.com/downloads/DriverDetails.aspx?driverID=414 (257, 268, 259, 265, 229) | Creative EULA (single computer) | no | no | No stable URL | [V] |
| Creative | SB16/AWE (ISA) | - | - | - | - | - | no | Windows 98 has its own driver | [V] |
| C-Media | CMI8738/8338 | none for 9x on site | no | https://www.cmedia.com.tw/support/download_center | - | - | no | | [V] |
| ESS, Yamaha, Avance Logic, Aureal, M-Audio, Terratec, SiS | various | - | no | see RECORD notes of the audio agent | - | - | no | No downloads / vendor gone | [V] |
| Intel ICH AC'97, SoundMAX, Turtle Beach, Cirrus, SigmaTel | - | unknown | unknown | - | - | - | not determined | Needs search | - |

## 4. Network

| Vendor | Device family | Last 9x version | Served by vendor? | URL | License | Hostable? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|---|---|---|
| VIA | Rhine I/II/III (VT6102/6105/6107, 8231-8237 LAN) | 3.84A (2009) | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/via_rhine_ndis5_v384a.zip | none found | no | **external** `driver-via-rhine` | 98SE/ME | [V] |
| VIA | Velocity GbE VT6120/6122 | 3.1 (driver 1.59) | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/velocity_driver_v31_via.zip | none found | no | **external** `driver-via-velocity` | | [V] |
| VIA | VT86C100A, VT6102 older (95/98) | 100a / 25 | yes | .../Driver/VT86c100a.zip, .../Driver/6102v25VIA.zip | not checked | no | qualifies, not packaged | Would cover 95/98FE | [V] listing |
| Realtek | RTL8139/810x, RTL8169/8110 | 5.707 (98SE/ME) | yes, behind CAPTCHA | https://www.realtek.com/Download/List?cate_id=587 / 583 | unknown | unknown | no | No stable URL | [V] |
| D-Link (US legacy) | DFE-530TX+ and others | 5.397 (2001) | yes (http and https) | http://legacyfiles.us.dlink.com/DFE-530TXPLUS/REVA/DRIVERS/DFE-530TXPLUS_DRIVER_5.397.ZIP | none seen | no | could qualify, not packaged | Win98 INF matches only D-Link subsystem IDs | [V] |
| AMD PCnet, NE2000 (RTL8029) | VM NICs | built into Windows 98 | - | - | - | - | n/a | Not verified against a Windows 98 CD | [S] |
| 3Com/HPE, SiS, Davicom, Linksys | - | - | no | - | - | - | no | Gone / empty pages | [V] |
| Intel, Broadcom, Marvell, Netgear, Atheros | - | unknown | unknown | - | - | - | unresolved | JavaScript pages / 403 | [V] partial |

## 5. Chipset / USB / storage

| Vendor | Device family | Last 9x version | Served by vendor? | URL | License | Hostable? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|---|---|---|
| VIA | Hyperion Pro (INF/AGP/V-RAID) | 5.24A (2009) | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/VIA_HyperionPro_V524A.zip | VIA EULA (personal use, no distribution) | no | **external** `driver-via-hyperion` | Needs Windows Installer 2.0 | [V] |
| VIA | 4in1 (MVP3, Apollo Pro, KT133-KT333) | 4.43 | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/VIA_4in1_443v.zip | none in package | no | **external** `driver-via-4in1` | | [V] |
| VIA | USB 2.0 (VT6202/6212, south-bridge EHCI) | 2.70p (2005) | yes | https://d34vhvz8ul1ifj.cloudfront.net/Driver/VIA_USB2_V270p1-L.zip | none; contains Microsoft USBPORT/USBEHCI/USBHUB20 | no | **external** `driver-via-usb2` | Vendor-served, so external is fine even with MS files | [V] |
| VIA | 4in1 4.35, USB filter 1.10, V-RAID 6.10C/5.90A, IDE MPD 3.20b | various | yes | VIA portal | not checked | no | qualifies, not packaged | Older/overlapping | [V] listing |
| Promise | Ultra33/66/100/133 TX2 | 2.00.0.43 (2003) | yes | https://www.promise.com/DownloadFile.aspx?DownloadFileUID=3258 | website Terms of Use | no | **external** `driver-promise-ultra` | MD5 matches Promise's | [V] |
| Promise | FastTrak 66/100/TX2/TX2000 | 2.00.0.34 (2003) | yes | https://www.promise.com/DownloadFile.aspx?DownloadFileUID=3516 | website Terms of Use | no | **external** `driver-promise-fasttrak` | MD5 matches | [V] |
| SiS, ALi/ULi, Silicon Image, HighPoint | chipset / IDE / SATA | - | no | - | - | - | no | Not served / domains gone | [V] |
| Intel | INF Update / IAA 9x | unknown | not confirmed | - | - | - | unresolved | | - |
| NEC/Renesas USB 2.0; Adaptec SCSI | - | unknown | unknown | microchip.com 403 | - | - | unresolved | | [V] partial |

## 6. Printers / scanners

| Vendor | Example | 9x driver | Served? | Qualifies? | Reason | |
|---|---|---|---|---|---|---|
| Brother | HL-5140 | PCL 2.05 (2004) listed for Win98 | listing yes | no | File URL behind JavaScript EULA button; curl 403 | [V] |
| Epson | Stylus/FX | 98/Me/95 in OS list | partly | no | JavaScript-rendered; ftp.epson.com 403 | [V] |
| HP | printers | - | ftp.hp.com times out | no | | [V] |
| Canon, Lexmark | - | unknown | unknown | unresolved | | - |
