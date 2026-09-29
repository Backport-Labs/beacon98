# Windows 98 Q273727 IPX NMPI update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q273727-98
- Version / update id: Q273727
- Verdict: **keep**
- Systems: 98. Windows 98 and 98 SE. English.
- What it fixes: Malformed IPX NMPI packet (NWLINK.VXD, VSERVER.VXD); security fix. Only matters with IPX/SPX installed.
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/win98/Update/11974/W98/EN-US/273727USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 273727USA8.EXE, 243360 bytes (same size as the availability.csv row)
- SHA-256: e417564904f97e8c92380e33e4b2dcd4c3df029c4ca4f39c34a0611157277e1a
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q273727-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `273727UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD273727 or \W98.SE\UPD273727; NWLINK.VXD 4.10.2226 on SE (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 1998UN/2222UN.INF (QFE). Beacon entry: `Uninstall: none`.