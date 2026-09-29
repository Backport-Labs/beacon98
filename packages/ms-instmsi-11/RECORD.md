# Windows Installer 1.1 for Windows 95/98 (instmsi.exe 1.11.2405.0) - Beacon 98 record

- Date checked: 2026-09-29
- Package: Windows Installer redistributable ("Installer for the Windows Installer")
- Version: 1.11.2405.0 (msi.dll and msiexec.exe 1.11.2405.0, files dated 2000-12-05)
- License: Microsoft EULA. External: downloaded from Microsoft's own server.
- Recommendation: list as `external`. It satisfies Beacon's `msi 1.1` (Apache 1.3). It does NOT satisfy `msi 2.0`.
  Windows Installer 2.0 for 9x (InstMsiA.exe, https://download.microsoft.com/download/WindowsInstaller/Install/2.0/W9XMe/EN-US/InstMsiA.exe)
  is gone from Microsoft's servers (404); see ms-instmsia-20 for the only 2.0 build still found (a pre-release under an "xml/Beta" path).

## Windows 9x support evidence

- The URL path is `win98/Patch/1.11.2405/W9X/EN-US`.
- instmsi.msi inside (read with the Windows Installer COM API): launch conditions allow `Version9X`; custom actions RegExtension and
  RegDllServer run on `Version9X`, service actions on `VersionNT`, so the package is authored for 9x and NT.
- Windows ME already contains Windows Installer 1.2; this package is for 95 and 98. Not tested on 95 or 98.

## Download

- URL: https://download.microsoft.com/download/win98/Patch/1.11.2405/W9X/EN-US/instmsi.exe
  (found in the Internet Archive's URL index for download.microsoft.com, then verified live by downloading from Microsoft)
- HTTPS: answers (Last-Modified 2018-12-05). Plain HTTP (`--http1.0`): 302 redirect to HTTPS only. No download.windowsupdate.com copy known.
- File: instmsi.exe, 1,495,256 bytes
- SHA-256: 731174afce530b09d30490e940cd0ba1e5002c2194a28b7c883d729d695eaf79
- Authenticode: Valid, OU=Microsoft Corporation, timestamped (certificate expired 2001-04-17; timestamp keeps it valid).
- Related file found (not packaged): https://download.microsoft.com/download/winme/patch/1.20.2405/w9xme/en-us/instmsi.exe
  (Windows Installer 1.20.2405.0, 1,507,032 bytes, signed Microsoft, Valid). Its path says winme/w9xme; its purpose (an update of ME's
  built-in 1.2) was not confirmed, so it is not proposed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-instmsi-11 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- Microsoft EULA. The IExpress LICENSE resource is <None> and there is no EULA text file in the package; LICENSE.TXT holds a short note.

## Security

- Not checked against NVD (unknown).

## Install behaviour

- Installer type: IExpress. Resources (read with 7-Zip, not run):
  RUNPROGRAM=`msiinst.exe /i instmsi.msi /qb+`, USRQCMD and ADMQCMD=`msiinst.exe /i instmsi.msi REBOOT=REALLYSUPRESS /q`, REBOOT=0.
- Silent: IExpress `/q` (runs the package's own quiet command above; `/q:a` runs the identical admin command). Not tested.
- Restart: the quiet command suppresses restart (REBOOT=REALLYSUPRESS, spelled so in the package). Whether a restart is then needed
  before msiexec works was not verified; Beacon should suggest restarting.
- Detection: file version of {sys}\MSIEXEC.EXE (1.11.2405.0). Beacon check satisfied: `msi 1.1`.
- Uninstall: not possible. instmsi.msi sets ARPNOREMOVE=1 and ARPNOMODIFY=1, so no Add/Remove Programs entry. `Uninstall: none`.

## Verification notes

- Verified: download, hash, signature, 7-Zip listing, IExpress resources, MSI tables.
- Not verified: install on 95/98, restart behaviour, Microsoft documentation (the original download pages are gone).
