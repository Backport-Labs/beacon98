# Windows 98 Q311561 IO.SYS update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q311561-98
- Version / update id: Q311561
- Verdict: **keep**
- Systems: 98. Windows 98 and 98 SE. English.
- What it fixes: MS-DOS mode hard disk errors (IO.SYS).
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/Win98/Patch/22527/W98/EN-US/311561USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 311561USA8.EXE, 306792 bytes (same size as the availability.csv row)
- SHA-256: 569ecb4fe36a7c00bf7f6d353467d8f95e4708fb8809d3e456760a8ef42be6fc
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2002-05-29, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q311561-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `311561UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD311561 or \W98.SE\UPD311561 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 1998UN/2222UN.INF (QFE). Beacon entry: `Uninstall: none`.