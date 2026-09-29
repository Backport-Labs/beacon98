# Project Dogwaffle 1.2 (free version) - Beacon 98 record

- Date checked: 2026-09-29
- Package: Project Dogwaffle, Dan Ritchie / thebest3d.com
- Version: 1.2 free (SETUP.LST lists dogwaffle.exe file version 1.5.0.0 dated 1/29/2004; the publisher calls it "Version 1.2")
- License: freeware; the publisher explicitly allows redistribution
- Availability: external in this draft (see License for why hosting is possible but not chosen yet)

## Windows 9x support evidence

- Weak. The publisher's page does not name 95/98/ME; it only says 1.2 also runs on Vista and 7.
- Indirect evidence from the installer (listed with 7-Zip, not run): a Visual Basic 5 application installed with the
  VB5 Setup Toolkit (SETUP.EXE 1997, setup1.exe 5.0.0.3905, VB5StKit.dll, MSVBVM50.dll 5.2.82.44, OleAut32.dll
  2.20.4118.1, Ctl3d32.dll, COMCTL32.OCX 6.0.81.5). These are the Windows 95/98-era runtime files, and nothing in the
  package needs NT. mdgx's Windows 9x "toys" list (the source row) lists Dogwaffle 1.2.
- Not tested on 9x. Treat "Systems: 95, 98, ME" as unverified.

## Download

- Page: https://www.thebest3d.com/dogwaffle/free/ (opened): "Version 1.2 is Free! download it from here now!"
- URL: https://www.thebest3d.com/dogwaffle/free/Dogwaffle_Install_1_2_free.exe (200, application/x-msdownload,
  Last-Modified Mon, 27 Feb 2023). http://www.thebest3d.com/... answers 301 to https.
- The page's other link, http://www.thebest2d.com/free1.2/Dogwaffle_Install_1_2_free.exe, answers 403 (http and https).
  mirrors.html links only the same relative file.
- File: Dogwaffle_Install_1_2_free.exe, 4,558,273 bytes
- SHA-256: acd8618fe3600439c932803a69cfde2c4a64cdd1b5c6f3d8cafce94eb7b9442e
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\dogwaffle -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- The installer has no license agreement. The publisher's page says: "This is freeware and you may freely distribute
  it with your commercial projects, cover CDs/DVDs in magazines, on a CD with a book, for download from your website,
  etc... 'Any reproduction in whole or in part is totally cool - Daddyo'". Fully functional, no time limit, no nag
  mentioned ("not time-limited or save-disabled" per the page).
- The package also contains copying.txt with the GNU LGPL 2.1, without saying which component it covers.
  Candidates are the helper DLLs (e.g. IM_MOD_RL_histogram_.dll, a module name used by ImageMagick, which is not LGPL);
  unresolved.
- LICENSE.TXT: the page statement plus copying.txt as shipped.
- Hosting: the publisher's permission is clear, but because an unidentified LGPL component would oblige us to offer
  its source, the draft uses external. The package also installs Microsoft VB5 runtime files that the developer
  was allowed to redistribute with his application.

## Security

NVD keyword "Dogwaffle": 0 results. The installer overwrites/registers old shared system files (OLEAUT32.DLL
2.20.4118.1, COMCTL32.OCX, COMDLG32.OCX) only if they are older than the installed ones (VB5 setup behaviour), not verified.

## Install behaviour

- Outer file: a self-extracting ZIP (7-Zip reads it as zip with a 52,516-byte stub; the stub contains the string
  "WinZip"). It holds 121 SZDD-compressed files and the VB5 Setup Toolkit SETUP.EXE/SETUP.LST.
- SETUP.LST [Setup]: Title=project dogwaffle, DefaultDir=$(ProgramFiles)\project dogwaffle, AppExe=dogwaffle.exe.
- Silent install: none. The VB5 Setup Toolkit has no documented silent mode; how the self-extractor starts SETUP.EXE
  was not verified. The entry runs it interactively.
- Uninstall: the VB5 Setup Toolkit registers an Add/Remove Programs entry named after the Title ("project dogwaffle")
  that runs ST5UNST.EXE. This is standard VB5 behaviour, not verified for this package.

## Verification notes

- Opened: the free-version page, mirrors.html, file headers, the SFX listing, SETUP.LST, ReadMe.txt ("Thank you for
  your purchase of Project Dogwaffle..."), copying.txt.
- Not verified: 9x operation; uninstall name; which component is LGPL.
