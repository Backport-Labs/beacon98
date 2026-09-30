# VIA Hyperion Pro 5.24A chipset drivers - Beacon 98 record

- Date checked: 2026-09-29
- Package: VIA Hyperion Pro Driver Package (INF, AGP, V-RAID, IDE), VIA Technologies, Inc.
- Version: 5.24A (VIA page date 09-Jun-2009). Components per VIA: "INF V3.10A, AGP V4.60A, V-RAID V5.80F and RAID Tools
  v5.85, VIA IDE Falcon Storage Device driver v2.80A". 9x INF dates inside: VIAMACH.INF (Win98SE) DriverVer=06/21/2006,6.0.00.0300;
  VIAGART.INF (Win98_Me) DriverVer=06/29/2006,4.9.0.3460; VIAMRAID.INF (Win9X) DriverVer=12/20/2007, 2.0.950.573.
- License: proprietary "VIA Software License Agreement" (personal use, no distribution)
- Availability: external (VIA's own download portal, files on VIA's CloudFront distribution)
- Recommendation: newest VIA chipset package that still lists Windows 98/98SE/ME. VIA itself recommends it for KT4xx,
  P4X4xx and newer chipsets and the older 4.43 package (`driver-via-4in1`) for MVP3/Apollo Pro/KT133/KT266-era boards.

## Windows 9x support evidence

- VIA Driver Download Portal (https://download.viatech.com/en/support/driversSelect.jsp -> Microsoft Windows -> Windows 98SE ->
  "Hyperion Pro (4in1) chipset drivers"; queried through the portal's own form handlers DriverDownloadSelectAjaxSvl /
  DriverDownloadSubmitAjaxSvl on 2026-09-29): "VIA Hyperion Pro Driver Package Dated: 09-Jun-2009 ... version 5.24A OS supported
  Windows XP,Windows XP 64-Bit,Windows ME,Windows 98SE,Windows 98,Windows 2000,Windows NT,Windows Vista 32-Bit,Windows Vista 64-Bit,
  Windows Server 2003 x64". [V]
- The same list for "Windows 95" (OS id 8) also offers this package, but 5.24A's Setup.ini [SupportOS] lists Win95=1, Win98=1, WinME=1,
  and the package ships separate viamach\driver\win95, Win98, Win98SE, WinMe INFs and viaagp\DRIVER\Win95 + Win98_Me. Windows 95 is not
  in VIA's OS list for this entry, so Systems is given as 98, ME.
- Setup is an InstallShield 12-style MSI setup (Setup.ini ScriptVer=7.7.0.262, MsiVersion=2.0.2600.2) that carries instmsia.exe
  (Windows Installer 2.0 for 9x) and isscript.msi.

## Download

- Portal: https://download.viatech.com/en/support/driversSelect.jsp (JavaScript form; the result page links the file directly)
- URL: https://d34vhvz8ul1ifj.cloudfront.net/Driver/VIA_HyperionPro_V524A.zip
  - http:// answers 301 to the https address. Last-Modified: Tue, 13 Jan 2015 14:36:30 GMT.
- File: VIA_HyperionPro_V524A.zip, 13,299,373 bytes
- SHA-256: e706e033db40efdd8ef5e8d0d1d354e24f4432f73a2a3e0e5ce3ec992db0a4ff
- Published checksum: none.
- Authenticode of setup.exe: signed "VIA Technologies Inc." (Digital ID Class 3 - Microsoft Software Validation v2); Windows 11 reports
  status UnknownError (old SHA-1 chain / expired), so not verifiable today.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\driver-via-hyperion -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is the English License.rtf embedded in Platform.msi (ISSetupFile table), converted to text on the host.
- "The VIA SOFTWARE is licensed for personal use and may only be used in conjunction with VIA products." / "You may not transfer or
  distribute this software to any third party." Redistribution is NOT allowed -> external only.

## Security

NVD keyword searches ("Hyperion VIA chipset" exact: 0; "viagart": 0) found nothing relevant (plain "VIA Hyperion" matches Oracle Hyperion
only). No known CVEs for these 9x drivers. Not otherwise verified.

## Hardware IDs (from the 9x INFs)

235 distinct PCI IDs, all vendor 1106 (VIA), from viaagp\DRIVER\Win98_Me\VIAGART.INF (18, AGP bridges), VRAIDDrv\Win9X\VIAMRAID.INF
(8, SATA/IDE RAID: DEV_3349, 6287, 0591, 3249, 3149, 3164, 0581, 7372), viamach\driver\{Win98SE,Win98,WinMe,win95}\VIAMACH.INF
(host bridges, PCI bridges, ISA/LPC, IDE, USB, ACPI functions) and viaagp\DRIVER\Win95\viagart.inf. ENTRY.TXT lists the first 40
(AGP, RAID, then the first chipset IDs). Full list:

VEN_1106&DEV_ 8598 8501 8601 8305 8605 8391 8602 B091 B099 B101 B112 B116 B148 B156 B158 B168 B188 B198 3349 6287 0591 3249 3149 3164
0581 7372 0305 0391 0601 0605 3091 3099 3101 3112 3051 3116 3123 3128 3148 3156 3168 3178 3188 3189 3205 3113 3213 D213 B113 B213
0204 1204 2204 3204 4204 7204 0258 1258 2258 3258 4258 7258 0259 1259 2259 3259 4259 7259 0238 1238 2238 3238 4238 5238 7238 A238
C238 D238 E238 F238 0269 1269 2269 3269 4269 7269 0282 1282 2282 3282 4282 7282 0208 1208 2208 3208 4208 5208 7208 A208 C208 D208
E208 F208 0296 1296 2296 3296 4296 7296 0308 1308 2308 4308 5308 7308 0290 1290 2290 3290 4290 5290 7290 0314 1314 2314 4314 7314
0351 1351 2351 3351 4351 5351 7351 0336 1336 2336 3336 4336 5336 7336 0324 1324 2324 3324 4324 7324 0327 1327 2327 3327 4327 5327
6327 7327 A327 C327 0340 1340 2340 3340 4340 5340 6340 7340 C340 D340 E340 F340 0364 1364 2364 3364 4364 5364 6364 7364 A364 C364
0353 1353 2353 3353 4353 5353 6353 7353 8353 A353 B353 C353 E353 F353 0409 1409 2409 3409 4409 5409 6409 7409 8409 8231 3074 3109
3147 3177 3227 3287 287A 287B 287C 287D 287E 3337 337B 8324 324A 324B 324E 3372 3402 0501 0691 3050 3057 0596 0686 337A 0597 0598
8597 3040 0586

## Install behaviour

- Zip layout: one folder VIA_HyperionPro_V524A\ with setup.exe, Setup.ini, Platform.msi, instmsia.exe, instmsiw.exe, isscript.msi,
  viamach\, viaagp\, VIAStor\, VRAIDDrv\, RAIDTool\, Xfilter\, DIFXAPI\.
- Beacon: unzip to {pf}\Drivers\via-hyperion, then run setup.exe from there (interactive). The string table documents
  "/S Hide intialization dialog.  For silent mode use: /S /v/qn." (InstallShield bootstrapper); not tested, and the component
  installers may restart Windows, so the entry runs setup interactively.
- Setup installs Windows Installer 2.0 (instmsia.exe) first if missing and may ask for a restart before continuing; Beacon's
  `ms-instmsia-20` package is required instead so that happens beforehand.
- Add/Remove Programs: MSI ProductName "Platform" (ProductVersion 1.34, ProductCode {20D4A895-748C-4D88-871C-FDB1695B0169}) with
  ARPNOREMOVE=1; removal goes through VIA's own maintenance dialog ("Remove"). Exact display name on 98: unknown. Beacon's Uninstall
  therefore only removes the unpacked folder (`files`); a Notice says so.
- Manual alternative (INF only): Device Manager -> Update Driver -> point at viamach\driver\Win98SE (or Win98/WinMe), and
  viaagp\DRIVER\Win98_Me for the AGP bridge.

## Verification notes

- Opened: VIA portal pages and form results, the zip (listed and extracted with 7-Zip on the host; nothing executed), Setup.ini,
  0X0409.INI, SETUP.SCF, the INFs, Platform.msi Property table (read-only via the WindowsInstaller COM object) and License.rtf.
- Not verified: behaviour on real hardware; silent switches; Windows 95.
