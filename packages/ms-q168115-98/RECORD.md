# Windows 98 Q168115 MSNP32 update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q168115-98
- Version / update id: Q168115
- Verdict: **keep**
- Systems: 98. Windows 98 first edition (key W98.SP1\UPD168115). English.
- What it fixes: Cached domain password security fix (MSNP32.DLL 4.10.2000).
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/win98/update/168115/w98/en-us/168115us8.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 168115us8.exe, 165864 bytes (same size as the availability.csv row)
- SHA-256: 0dcde9d6effcb870e32c35fa65c01a028d47513ce52f757513dfcf66343c4f17
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q168115-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `168115Up.inf`; POSTRUNPROGRAM: `CSETUP.exe 168115up.cat`; REBOOT resource value 1
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SP1\UPD168115 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 168115UN.INF (QFE); no Add/Remove entry. Beacon entry: `Uninstall: none`.