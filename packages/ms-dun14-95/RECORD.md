# Dial-Up Networking 1.4 for Windows 95 - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-dun14-95
- Version / update id: 1.4
- Verdict: **keep**
- Systems: 95. Windows 95 all builds (OSR2 sections present). English.
- What it fixes: Dial-Up Networking 1.4 upgrade (Y2K fix, VPN, updated TCP/IP stack).
- Description source: package INF (msdun.inf) + IExpress resources
- Notes: IExpress quiet command is "dunsetup.exe /q /m" (ADMQCMD/USRQCMD), so /Q:A runs it quietly. Needs Winsock 2 first? unknown.

## Download

- URL: https://download.microsoft.com/download/win95/Update/17648/W95/EN-US/dun14-95.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: dun14-95.exe, 1890376 bytes (same size as the availability.csv row)
- SHA-256: 1f72fcfbaedd9be514b3c7851a4d0190753bace91b089d6c6ac6253b02deabd2
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2002-05-29, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-dun14-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `dunsetup.exe /m`; POSTRUNPROGRAM: `<None>`; REBOOT resource value 1
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Uninstall\MSDUN (DisplayName "Dial-up Networking 1.4 Update for Windows 95"); HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\Y2K.W95.DUN (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Registers an Add/Remove entry: UninstallString "dunsetup.exe /u". Beacon entry: `Uninstall: registry Dial-up Networking 1.4 Update for Windows 95`.