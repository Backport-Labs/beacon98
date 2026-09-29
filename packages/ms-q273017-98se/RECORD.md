# Windows 98 SE Q273017 IFSMGR update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q273017-98se
- Version / update id: Q273017
- Verdict: **keep**
- Systems: 98. Windows 98 SE only. English.
- What it fixes: ScanDisk runs after a correct shutdown; DOS device names in paths (IFSMGR.VXD 4.10.2225).
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/win98SE/Update/11956/W98/EN-US/273017USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 273017USA8.EXE, 229568 bytes (same size as the availability.csv row)
- SHA-256: 6b37203663621010cabe3b4bf69ee3b03386db1b2bfa46e0e42639779dfe0196
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q273017-98se -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `273017UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SE\UPD273017 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 273017UN.INF (QFE). Beacon entry: `Uninstall: none`.