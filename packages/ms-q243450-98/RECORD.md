# Windows 98 Q243450 ESDI_506 update (disks over 32 GB) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q243450-98
- Version / update id: Q243450
- Verdict: **keep**
- Systems: 98. Windows 98 (ESDI_506.PDR 4.10.2186) and 98 SE (4.10.2225). English.
- What it fixes: ScanDisk errors with IDE hard disks larger than 32 GB.
- Description source: csv/MDGx title + INF + IExpress prompt


## Download

- URL: https://download.microsoft.com/download/win98SE/Update/5638-6151/W98/EN-US/243450USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 243450USA8.EXE, 161976 bytes (same size as the availability.csv row)
- SHA-256: 491e45764256a585b60fbff2c2daae9f7dc1952833f38a85f44f9a1b00bc7ae2
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q243450-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `243450UP.inf`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SP1\UPD243450 or \Win98.SE\UPD243450 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF. The package itself warns: "Installing this update will remove the ability to uninstall Windows." Beacon entry: `Uninstall: none`.