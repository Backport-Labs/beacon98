# Windows Me Q314757 UPnP update (MS01-059) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q314757-me
- Version / update id: Q314757
- Verdict: **keep**
- Systems: ME. Windows Me (UPnP is an optional component, not installed by default). English.
- What it fixes: MS01-059 unchecked buffer in Universal Plug and Play.
- Description source: Microsoft bulletin MS01-059 (opened) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2001/ms01-059


## Download

- URL: https://download.microsoft.com/download/winme/Update/22940/WinMe/EN-US/314757USAM.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 314757USAM.EXE, 228928 bytes (same size as the availability.csv row)
- SHA-256: bfd22fe562752a63a8d069232c008995a8fd0356fae8b79f23cfc6b4320e5bbe
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2002-05-29, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q314757-me -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `QFEREG.INF`; POSTRUNPROGRAM: `314757UP.INF`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\WinME\UPD314757 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF; Windows Me hotfixes rely on System Restore. Beacon entry: `Uninstall: none`.