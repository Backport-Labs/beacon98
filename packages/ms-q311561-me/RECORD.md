# Windows Me Q311561 IO.SYS update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q311561-me
- Version / update id: Q311561
- Verdict: **keep**
- Systems: ME. Windows Me. English.
- What it fixes: MS-DOS hard disk errors (IO.SYS, also EBD copy).
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/WinME/Patch/22527/WinME/EN-US/311561USAM.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 311561USAM.EXE, 356416 bytes (same size as the availability.csv row)
- SHA-256: 99ad200ac4abb7a70d6a050a234d96769ad2b0e95c0b6ae1129c25b261568e54
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2002-05-29, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q311561-me -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `QFEREG.INF`; POSTRUNPROGRAM: `311561UP.INF`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\WinME\UPD311561 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF. Beacon entry: `Uninstall: none`.