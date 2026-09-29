# Windows 98 VTDAPI update (49.7 days) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q216641-98
- Version / update id: Q216641
- Verdict: **keep**
- Systems: 98. Windows 98 first edition (key SP1\UPD216641.98). English.
- What it fixes: Computer hangs after 49.7 days (VTDAPI.VXD 4.10.2012).
- Description source: csv/MDGx title + INF
- Notes: No license text in the package.

## Download

- URL: https://download.microsoft.com/download/win95upg/Update/8/W95/EN-US/216641up.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 216641up.exe, 135680 bytes (same size as the availability.csv row)
- SHA-256: a85c27959d0d1d0d8cf8b962d672d7267513f92e1996ea0157f9f23ab353cbb1
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q216641-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. no EULA in the package; LICENSE.TXT is a short note. The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `216641Up.inf`; POSTRUNPROGRAM: `<None>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\SP1\UPD216641.98 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 216641UN.INF (QFE); no Add/Remove entry. Beacon entry: `Uninstall: none`.