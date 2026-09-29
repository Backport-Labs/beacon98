# Microsoft Data Access Components 2.5 SP3 (mdac_typ.exe 2.53.6200.2) - Beacon 98 record

- Date checked: 2026-09-29
- Package: Microsoft Data Access Components 2.5 Service Pack 3, English
- Version: 2.53.6200.2 (file version of mdac_typ.exe; cabinets dated 2002-07-26)
- License: Microsoft EULA (mdaceula.txt inside the package, saved as LICENSE.TXT). External: downloaded from Microsoft's server.
- Recommendation: list as `external` after testing the silent install in a VM (see Install). This is a fallback: MDAC 2.8 for 9x
  (MDAC_TYP.EXE) was not found on Microsoft's servers. Every MDAC_TYP.EXE URL on MDGx and 134 archived download.microsoft.com
  URLs ending in mdac_typ.exe were tested live; only this 2.5 SP3 9x/NT4 file and a French NT4 one answered.

## Windows 9x support evidence

- URL path `MDAC2.5/SP/3/W9XNT4/EN-US`.
- dasetup.exe strings: "Allowing Install on Windows2000/Millennium".
- dasetupr.dll string: "This product requires Microsoft Distributed COM for Windows 95 (DCOM95) to be installed on the system."
  So on Windows 95, DCOM95 must be installed first (Beacon has no check for it).
- Windows ME ships with MDAC 2.5 (general knowledge, not verified here); this SP3 updates it. Not tested on any system.

## Download

- URL: https://download.microsoft.com/download/MDAC2.5/SP/3/W9XNT4/EN-US/mdac_typ.exe
  (found in the Internet Archive's URL index for download.microsoft.com, verified live by downloading)
- HTTPS: 200 OK (Last-Modified 2018-12-05). Plain HTTP (`--http1.0`): 302 redirect to HTTPS only.
- File: mdac_typ.exe, 7,945,048 bytes
- SHA-256: bc9eae72a67c61796204219c5e42d48945e02484a8babb2fcd840f6c5475b04a
- Authenticode: Valid, CN=Microsoft Corporation, timestamped (certificate valid to 2003-11-24).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-mdac25sp3 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT = mdaceula.txt from the package (extracted with 7-Zip): "MICROSOFT CORPORATION END-USER LICENSE AGREEMENT,
  Microsoft Data Access Components 2.5". It grants installation and use; Beacon only downloads the file from Microsoft.

## Security

- Not checked against NVD (unknown). MDAC 2.5 received later security fixes (for example the KB927779-type MDAC updates listed by
  MDGx, whose URLs now return 404).

## Install behaviour

- Installer type: IExpress wrapper around Microsoft's dasetup.exe. IExpress resources (7-Zip, not run): RUNPROGRAM=`"dasetup.exe"`,
  USRQCMD/ADMQCMD=<None>, REBOOT=0. dasetup.ini lists MSVCRT, OLEAUT, MTXFILES, MDACONE, MDACTWO (INF-based installs).
- Silent: `mdac_typ.exe /q:a /c:"dasetup.exe /q"`. The IExpress switches are standard; dasetup.exe contains " /Q" and the log strings
  "Running in Silent Mode. Suppressing UI". A switch to suppress the restart was NOT identified (dasetup contains " /R",
  "Suppress Reboot: %d" and "Calling Win32 API ExitWindowsEx(EWX_REBOOT, 0)"): in silent mode it may restart Windows by itself.
  Must be tested before publishing.
- Restart: likely (dasetup has reboot logic); not verified.
- Detection: HKLM\SOFTWARE\Microsoft\DataAccess, value FullInstallVer (named in dasetup.ini as ProductVersionKey/Value); expected
  2.53.6200.x (exact value not verified). Beacon has no registry or version check that fits; a `file` check on an MDAC DLL would not tell 2.5 SP3 from earlier versions.
- Uninstall: no uninstaller found in the package or dasetup.ini. `Uninstall: none`.
