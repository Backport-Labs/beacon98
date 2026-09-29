# Windows 98 Q323172 certificate enrollment update (MS02-048) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q323172-98
- Version / update id: Q323172
- Verdict: **keep**
- Systems: 98. Windows 98 (Microsoft lists separate 98 and 98 SE patches; this is the 98 file; INF key W98). English.
- What it fixes: MS02-048 Certificate Enrollment Control could delete certificates (XENROLL.DLL 5.131.3659.0). Microsoft: IE 5 or later needed for the new control to work.
- Description source: Microsoft bulletin MS02-048 (opened) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2002/ms02-048
- Notes: Microsoft lists a separate 98 SE download whose URL is lost from the bulletin page; whether this file also installs on 98 SE is not verified.

## Download

- URL: https://download.microsoft.com/download/WIN98/PATCH/24421/W98/EN-US/323172USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 323172USA8.EXE, 219472 bytes (same size as the availability.csv row)
- SHA-256: d65cc961a4003494270bcb628e0fc5177ef0829a52015b56d4f54bbd807b29dc
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2003-11-24, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q323172-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `323172UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD323172 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Microsoft says the patch can be uninstalled; 323172UN.INF is copied to QFE, no Add/Remove entry. Beacon entry: `Uninstall: none`.