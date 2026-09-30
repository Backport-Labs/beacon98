# VIA Envy24 Family audio driver 5.30b for Windows 98/ME - Beacon 98 record

- Date checked: 2026-09-29
- Package: Envy24 Audio controller family driver (VIA Vinyl Envy24 controllers MT/DT/GT/PT/HT-S), VIA Technologies, Inc.
- Version: 5.30b (portal date 07-Mar-2008; Component.cif COMPONENT_VERSION "V5.30b", DATE 20080226;
  Envy24HF.INF DriverVer 12/05/2007, 5.12.01.3653)
- License: proprietary "VIA SOFTWARE LICENSE AGREEMENT" (personal use, no distribution to third parties)
- Availability: external (VIA's own download portal and its CloudFront download host)
- Recommendation: 5.30b, not the newer 5.40a (05-Aug-2008) or 5.40F (14-Oct-2009). VIA's portal still lists
  Windows 98/98SE/ME for all three, but in 5.40a and 5.40F the [EXEC.9x] install commands in
  VIAEnvyAud\Component.cif are commented out (`;INSTCMD=...`), so their setup installs nothing on 9x.
  5.30b is the newest package whose [EXEC.9x] section is active.

## Windows 9x support evidence

- VIA Driver Download Portal https://download.viatech.com/en/support/driversSelect.jsp (opened 2026-09-29):
  Windows 98SE > Audio > "VIA Vinyl Envy24 controllers: MT/DT/GT/PT/HT-S" lists
  "Envy24 Audio controller family driver Dated: 07-Mar-2008 ... version 5.30b OS supported Windows 98,Windows XP,
  Windows 2000,Windows ME,Windows 98SE,Windows Vista 32-Bit,Windows Vista 64-Bit,Windows Server 2003 x64".
- Component.cif of 5.30b: `[EXEC.9x] INSTCMD=0x101,,2,EnvyAudDrv9x.InstallAudio,4,\Drivers\WDM\;0x102,...;
  0x104,,2,EnvyAudDrvMe.InstallAudio,0,\drivers\WDM\;` (active). Compared with 5.40a and 5.40F (downloaded to a temp
  folder only for this comparison, then not kept), where the same line starts with `;`.
- Envy24HF.INF (Drivers\WDM) has `Signature="$CHICAGO$"` and a non-NT install section [WDM_Envy24HF] using ks.inf /
  wdmaudio.inf. WDM audio needs Windows 98 or later; Windows 95 is not listed by VIA for this driver.

## Download

- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/Envy24_Family_DriverV530b.zip (linked from VIA's portal)
  - http:// answers 301 to https:// (no plain-HTTP location).
  - Last-Modified: Tue, 13 Jan 2015 14:34:39 GMT
- File: Envy24_Family_DriverV530b.zip, 8,615,873 bytes
- SHA-256: 0a0248717c11015de1b2dc1534f657321b1c2f00961817655d61d24b9f28428f
- Published checksum: none.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-envy24 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats" (the folder then held only Envy24_Family_DriverV530b.zip).

## License

- LICENSE.TXT: the English License.rtf shown by the setup (Platform.msi, ISSetupFile.SetupFile15), text identical to the
  one in the VIA Vinyl 7.00b package.
- "The VIA SOFTWARE is licensed for personal use and may only be used in conjunction with VIA products."
  "You may not transfer or distribute this software to any third party." Not hostable; `Availability: external`.

## Hardware IDs (Drivers\WDM\Envy24HF.INF)

- One PCI vendor/device pair: VEN_1412&DEV_1724 (VIA/ICEnsemble Envy24HT family: VT1720/VT1724, sold as
  Envy24 HT/HT-S/PT/GT/DT/MT; chip names from general knowledge).
- 70 SUBSYS-specific entries (card makers by subsystem vendor: 10B0 x19, 14C3 x10, 1412 x6, 1106 x6, 19BE x6,
  270F x5, 160B x4, 1458 x3, 16F3 x2, and single entries for 17F2, A0A0, 147A, 1681, 1297, 1793, 10DE, 3138), plus
  `ExcludeFromSelect=PCI\VEN_1412&DEV_1724`.
- NOT covered: the original Envy24 (ICE1712, PCI VEN_1412&DEV_1712) used on M-Audio Delta, Terratec EWS/DMX,
  Hoontech cards. Whether a card with a subsystem ID not in the INF is accepted is unknown.

## Virtual machines

No common VM emulates an Envy24HT; not useful in VirtualBox, VMware or QEMU.

## Install behaviour

- Zip folder Envy24_Family_DriverV530b\: InstallShield 7 InstallScript-MSI setup (Setup.exe, Setup.ini with
  MsiVersion=2.0.2600.2, INSTMSIA.EXE, ISSCRIPT.MSI, Platform.msi). Same setup framework as VIA Vinyl 7.00b; silent
  switch `setup.exe -s` per VIA's generic guide (not verified for this package). Add/Remove Programs name: unknown.
- Beacon entry: INF-only. Unzip to {pf}\Drivers\via-envy24 (strip 1); the INF is in {dir}\VIAEnvyAud\Drivers\WDM
  (Envy24HF.INF, Envy24HF.sys, A3D.DLL). The mixer/control panel ("Audio Deck") is only installed by the setup.

## Security

No CVEs found (NVD not searched; web search unavailable in this session). Not verified.

## Verification notes

- Opened: VIA portal results, download HEAD and file, zip listing, Component.cif of 5.30b/5.40a/5.40F, Setup.ini,
  Setup.iss, Envy24HF.INF, license RTF.
- Not verified: installation on real Windows 98/ME; subsystem-ID matching for unlisted cards.
