# Windows 98 Q329048 Compressed Folders update (MS02-054) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q329048-98
- Version / update id: Q329048
- Verdict: **keep**
- Systems: 98. Windows 98 / 98 SE with Plus! 98 Compressed Folders installed. English.
- What it fixes: MS02-054 unchecked buffer and wrong target path in Compressed Folders (DUNZIP32.DLL, DZIP32.DLL 3.0.0.18, ZIPFLDR.DLL 5.0.531.0).
- Description source: Microsoft bulletin MS02-054 (opened) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2002/ms02-054


## Download

- URL: https://download.microsoft.com/download/WIN98/UPDATE/25556/W98/EN-US/329048USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 329048USA8.EXE, 273744 bytes (same size as the availability.csv row)
- SHA-256: 84fbb600e8cebff778df1f2b0b31a65e9fdef6588e6c2a0d8a1b19fdf721505b
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2003-11-24, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q329048-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `329048UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD329048 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Microsoft: cannot be uninstalled on Windows 98. Beacon entry: `Uninstall: none`.