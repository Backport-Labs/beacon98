# Windows 95 Q273727 IPX NMPI update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q273727-95
- Version / update id: Q273727
- Verdict: **keep**
- Systems: 95. Windows 95 retail, OSR2 and OSR2.1 (separate check INFs 95G_CHK, OSR2_CHK, OSR21CHK select the files). English.
- What it fixes: Malformed IPX NMPI packet (NWLINK.VXD, VSERVER.VXD); security fix. Only matters if the IPX/SPX protocol is installed.
- Description source: csv/MDGx title + INF contents


## Download

- URL: https://download.microsoft.com/download/win95/Update/11974/W95/EN-US/273727USA5.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 273727USA5.EXE, 243872 bytes (same size as the availability.csv row)
- SHA-256: 8b34a5b9eceffee6c3d1232e9f7ae3ffe7287c4114d58c61f1e6ed8b0abe6ec4
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q273727-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `273727UP.INF`; POSTRUNPROGRAM: `<None>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W95\UPD273727, \OSR2\UPD273727 or \OSR2.1\UPD273727; NWLINK.VXD 4.0.0.958 (95) / 4.0.0.1117 (OSR2) (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Uninstall INF 273727UN is copied to INF\QFE; no Add/Remove entry. Beacon entry: `Uninstall: none`.