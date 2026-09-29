# Windows 98 Q241134 OpenHCI update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q241134-98
- Version / update id: Q241134
- Verdict: **keep**
- Systems: 98. Windows 98 (OPENHCI.SYS 4.10.2022) and 98 SE (4.10.2225); version-check INFs pick the edition. English.
- What it fixes: USB OpenHCI controller on fast computers.
- Description source: csv/MDGx title + INF
- Notes: On 98 SE superseded by ms-q253697-98se (OPENHCI.SYS 4.10.2228); keep for 98 first edition.

## Download

- URL: https://download.microsoft.com/download/win98SE/Update/4003/W98/EN-US/241134usa8.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 241134usa8.exe, 162976 bytes (same size as the availability.csv row)
- SHA-256: 72090159b6db2327b12e436de86d9ef727b442cc236ebf4bc5d58d13708ef1c6
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q241134-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `241134UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD241134 (98) or \W98.SE\UPD241134 (SE) (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 1998UN/2222UN.INF (QFE). Beacon entry: `Uninstall: none`.