# Windows Installer 2.0.2505.0 for Windows 9x (instmsia.exe, "xml/Beta" path) - Beacon 98 record

- Date checked: 2026-09-29
- Package: Windows Installer redistributable for 9x, ANSI build (instmsia.exe)
- Version: 2.0.2505.0 (msi.dll and msiexec.exe 2.0.2505.0, files dated 2001-06-26)
- License: Microsoft EULA. External: downloaded from Microsoft's own server.
- Recommendation: HOLD, do not publish without testing. This is the only Windows Installer 2.0 build for 9x still found on
  Microsoft's servers, but it sits under `download/xml/Beta/4.0/...` (it was shipped with the MSXML 4.0 beta), and its files are
  dated 2001-06-26, before the final Windows Installer 2.0 (the final 2.0 build number is 2.0.2600.0 from my own knowledge; not
  verified here). It is very likely a pre-release build. The final InstMsiA.exe
  (https://download.microsoft.com/download/WindowsInstaller/Install/2.0/W9XMe/EN-US/InstMsiA.exe) returns 404.
- It would satisfy Beacon's `msi 2.0` check by version number.

## Windows 9x support evidence

- URL path `W98NT42KMeXP`. instmsi.msi launch conditions allow `Version9X`; custom actions RegExtension/RegDllServer run on
  `$MsiExecFile=3 AND Version9X`. Not tested on any 9x system.

## Download

- URL: https://download.microsoft.com/download/xml/Beta/4.0/W98NT42KMeXP/EN-US/instmsia.exe
  (found in the Internet Archive's URL index for download.microsoft.com, verified live by downloading)
- HTTPS: 200 OK (Last-Modified 2018-12-05). Plain HTTP (`--http1.0`): 302 to HTTPS only.
- File: instmsia.exe, 1,702,232 bytes
- SHA-256: b37eafa02fe6f6b498485a473bf5d1bb44a945fb780b6550bb1226d84484ed30
- Authenticode: Valid, CN=Microsoft Corporation, timestamped (certificate valid to 2002-05-29).
- The Unicode/NT twin is at .../xml/Beta/4.0/W98NT42KMeXP/EN-US/instmsiw.exe (answers; not downloaded).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-instmsia-20 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- Microsoft EULA; no license text in the package (LICENSE resource <None>). LICENSE.TXT holds a short note. As a beta component
  of MSXML 4.0, its original terms may have been beta/evaluation terms; not verified.

## Security

- Not checked (unknown).

## Install behaviour

- Installer type: IExpress. Resources (7-Zip, not run): TITLE "Installation of System Software Installer SHIP",
  RUNPROGRAM=`msiinst.exe /i instmsi.msi MSIEXECREG=1 /m /qb+!`, USRQCMD and ADMQCMD=`msiinst.exe /i instmsi.msi REBOOT=REALLYSUPRESS MSIEXECREG=1 /m /q`.
  msiinst.exe also contains the strings `delayreboot` and `delayrebootq`.
- Silent: IExpress `/q` (runs the quiet command above). Not tested.
- Restart: suppressed by the quiet command; whether one is needed was not verified.
- Detection: {sys}\MSIEXEC.EXE file version 2.0.2505.0. Beacon check: `msi 2.0`.
- Uninstall: not possible (instmsi.msi ARPNOREMOVE=1). `Uninstall: none`.
