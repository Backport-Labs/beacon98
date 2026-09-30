# VIA Vinyl Audio (AC'97) driver 7.00b for Windows 98/ME - Beacon 98 record

- Date checked: 2026-09-29
- Package: VIA Vinyl Audio driver - Multilingual (VIA AC'97 controllers and VIA Vinyl AC'97 codecs), VIA Technologies, Inc.
- Version: 7.00b (portal date 11-Sep-2007; Component.cif COMPONENT_VERSION "v7.00b", DATE 20070809;
  INF DriverVer 06/27/2007, 6.14.01.4200)
- License: proprietary "VIA SOFTWARE LICENSE AGREEMENT" (personal use, no distribution to third parties)
- Availability: external (VIA's own download portal and its CloudFront download host)
- Recommendation: 7.00b is the newest entry VIA's portal lists for Windows 98SE/98/ME/95 audio. It is also the
  newest package whose setup still has Windows 9x install commands.

## Windows 9x support evidence

- VIA Driver Download Portal https://download.viatech.com/en/support/driversSelect.jsp (opened 2026-09-29, via its
  AJAX back end DriverDownloadSelectAjaxSvl / DriverDownloadSubmitAjaxSvl): operating system "Windows 98SE" > Audio >
  "VIA AC97 in VT82C686A/B" (and the other VIA AC97 / Vinyl entries) returns as first result:
  "VIA Vinyl Audio driver - Multilingual Dated: 11-Sep-2007 ... version 7.00b OS supported Windows 98,Windows 95,
  Windows XP,Windows 2000,Windows ME,Windows NT,Windows 98SE,Windows Vista 32-Bit,... Chips supported VIA AC97 in
  VT82C686A/B,VIA AC97,VIA Vinyl (or Tremor) Audio VT1612A, VT1613, VT1616/B, VT1617/A, VT1618,VIA AC97 in VT8231,
  VIA AC97 in VT8251". The same list is returned for Windows ME, 98 and 95.
- Portal note: "This driver supports DOS sound for VT82C686A/VT82C686B/VT8231 only. The VIAAUDIO.COM file mentioned
  in the Readme concerning DOS sound can be obtained from this old audio driver package" (link
  http://downloads.viaarena.com/drivers/audio/68MU220b.zip, which no longer answers: empty reply; the same file
  name on the CloudFront host gives 403).
- Inside the zip (listed and text files extracted on the host; nothing run): Vinyl\Component.cif has an [EXEC.9x]
  section that installs from `\drivers\WDM\` with VinylDrv9x.dll (98) and VinylDrvME.dll (ME). Setup.ini lists
  Win95, Win98, WinME, NT4, 2000 under [SupportOS].
- The driver is WDM (vinyl97.sys, INFs with `Signature="$CHICAGO$"` and a non-NT install section that uses
  ks.inf / wdmaudio.inf). WDM audio drivers need Windows 98 or later, so the catalog lists 98 and ME only, even
  though VIA's portal also names Windows 95 (not verified on 95).
- Readme.htm in the package is a generic VIA "HyperionPro Drivers Package" user guide (2005), not specific to audio.

## Download

- Portal: https://download.viatech.com/en/support/driversSelect.jsp (Windows 98SE > Audio > VIA AC97 ...)
- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/vinyl_v700b.zip (linked directly from VIA's portal result page)
  - http://d34vhvz8ul1ifj.cloudfront.net/... answers 301 to the https address (tested with `curl.exe -I --http1.0`),
    so there is no plain-HTTP location; Beacon's own TLS is needed.
  - Last-Modified: Tue, 13 Jan 2015 13:20:18 GMT
- File: vinyl_v700b.zip, 7,288,855 bytes
- SHA-256: cb4fb850cedae5615c7fabce8b40429e04f0dabc2972505a517c6552c602ed8e
- Published checksum: none published by VIA.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-vinyl-ac97 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is the English License.rtf that the setup shows (stored in Platform.msi as ISSetupFile.SetupFile15;
  extracted with 7-Zip and converted from RTF to text; a second copy, SetupFile25, differs only in line wrapping).
- "1. Use of Software. The VIA SOFTWARE is licensed for personal use and may only be used in conjunction with VIA
  products." "2. Restrictions. ... You may not transfer or distribute this software to any third party."
- Redistribution is NOT allowed, so `Availability: external`; the file comes only from VIA's server.

## Hardware IDs (from the INFs Windows 9x uses: Vinyl\drivers\WDM\*.inf)

15 PCI vendor/device pairs (VinylCmp.inf has all 15; Vinyl97.inf / Vinyl971.inf / Vinyl972.inf add SUBSYS-specific
entries for 1106:3059 and 8086:266E):

- VIA: VEN_1106&DEV_3058 (VT82C686A/B AC'97), VEN_1106&DEV_3059 (VT8233/8235/8237 family AC'97)
- Intel: VEN_8086&DEV_2415, 2425, 2445, 24C5, 24D5, 25A6, 266E (ICH-family AC'97 controllers)
- SiS: VEN_1039&DEV_7012
- NVIDIA nForce: VEN_10DE&DEV_0059, 006A, 008A, 00DA, 01B1
- Component.cif also names PCI\VEN_1106&DEV_7059, which no INF contains.
- The chip names above are general knowledge, not from the INF (the INF names every device
  "Vinyl AC'97 Codec Combo Driver (WDM)").
- The non-VIA controllers are listed because VIA Vinyl codecs (VT1612A/1613/1616/1617/1618) were also used on
  Intel, SiS and nForce boards. Whether the driver works with another maker's codec is unknown.

## Virtual machines

- VirtualBox's AC'97 device is an Intel ICH AC'97 (PCI 8086:2415) with a SigmaTel STAC9700 codec by default (Analog
  Devices AD1980/AD1981B optional; from general knowledge, not re-checked here). 8086:2415 is in VinylCmp.inf, but the codec is not a VIA Vinyl codec, so this driver is
  NOT expected to work there; not tested (no VM use in this task).
- QEMU/VMware ES1371 and SB16 emulation are not covered by this driver.

## Install behaviour

- The zip holds the folder Vinyl_V700b\ with an InstallShield 7 (InstallScript MSI) setup: SETUP.EXE, Setup.ini
  (MsiVersion=2.0.2600.2; bundles INSTMSIA.EXE and ISScript.msi), Platform.msi (ProductName "Platform",
  Manufacturer "VIA Technologies, Inc.", ProductVersion 1.24). On Windows 98 the setup would first install
  Windows Installer 2.0 and the InstallScript engine. Add/Remove Programs name: unknown (the MSI ProductName is
  "Platform"; the script may set another name at run time).
- Documented silent switch (Readme.htm, generic VIA guide): `setup.exe -s` (install, no restart),
  `setup.exe -s /z"remove"` (uninstall).
- Beacon entry: INF-only. Beacon unzips to {pf}\Drivers\via-vinyl-ac97 (strip 1); the user then points Device
  Manager at {dir}\Vinyl\drivers\WDM. Windows may ask for the Windows 98 CD for the WDM audio components
  (ks.inf, wdmaudio.inf). The setup program remains in {dir} for users who want the "Audio Deck" control panel.

## Security

No CVEs found for this driver (NVD not searched; web search unavailable in this session). Not verified.

## Verification notes

- Opened: VIA portal (all selection steps, result pages for Windows ME, 98SE, 98, 95), the download URL (HEAD and
  full download), zip listing, Component.cif, Setup.ini, Setup.iss, VIAUDIO.INI, all WDM INFs, Readme.htm, the
  license RTF inside Platform.msi, the MSI Property table (read with the WindowsInstaller COM object, nothing
  installed).
- Not verified: installation on real Windows 98/ME; behaviour with non-VIA codecs; Add/Remove Programs name.
