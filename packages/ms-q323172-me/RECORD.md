# Windows Me Q323172 certificate enrollment update (MS02-048) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q323172-me
- Version / update id: Q323172
- Verdict: **keep**
- Systems: ME. Windows Me. English.
- What it fixes: MS02-048 Certificate Enrollment Control (XENROLL.DLL 5.131.3659.0).
- Description source: Microsoft bulletin MS02-048 (opened; its Me URL equals this one) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2002/ms02-048


## Download

- URL: https://download.microsoft.com/download/WINME/PATCH/24421/WINME/EN-US/323172USAM.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 323172USAM.EXE, 216896 bytes (same size as the availability.csv row)
- SHA-256: 9dbd8188f643ef430ed1810d6d0bead7b8d74478044c77962e311c0c4ddf4159
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2003-11-24, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q323172-me -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `QFEREG.INF`; POSTRUNPROGRAM: `323172UP.INF`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\WinME\UPD323172 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Microsoft says it can be uninstalled, but the package has no uninstall INF; use System Restore. Beacon entry: `Uninstall: none`.