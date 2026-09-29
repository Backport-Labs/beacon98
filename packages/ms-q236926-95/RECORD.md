# Windows 95 Q236926 VTCP.386 update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q236926-95
- Version / update id: Q236926
- Verdict: **superseded**
- Systems: 95. Windows 95 (key W95). English.
- What it fixes: TCP/IP prematurely transmitted packets (VTCP.386).
- Description source: csv/MDGx title + INF
- Notes: Superseded by ms-dun14-95: DUN 1.4 contains the identical VTCP.386 (same SHA-256 6a53236c...c418, 60,245 bytes).

## Download

- URL: https://download.microsoft.com/download/win95/update/3111/w95/en-us/236926usa5.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 236926usa5.exe, 175264 bytes (same size as the availability.csv row)
- SHA-256: d563be04da6bf3bcbac39b24f628d9412e64c8f26b775db70c4767c03abf06e3
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q236926-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `236926UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W95\UPD236926 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 236926UN.INF (QFE); no Add/Remove entry. Beacon entry: `Uninstall: none`.