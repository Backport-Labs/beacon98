# Windows 98 SE UHCD update (AMD + VIA USB) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q240075-98se
- Version / update id: Q240075
- Verdict: **keep**
- Systems: 98. Windows 98 SE only. English.
- What it fixes: USB UHCD.SYS 4.10.2223 for AMD CPU + VIA USB controllers.
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/win98SE/Patch/4.10.2223/W98/EN-US/240075up.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 240075up.exe, 162304 bytes (same size as the availability.csv row)
- SHA-256: a171800cd56a2cdcc9107d4757cb367febe98daf2b1976a152824f5ab9fa84d9
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q240075-98se -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `3781up.inf`; POSTRUNPROGRAM: `CSETUP.exe 3781up.cat`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\Win98.SE\UPD3781; UHCD.SYS 4.10.0.2223 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 3781UN.INF (QFE). Beacon entry: `Uninstall: none`.