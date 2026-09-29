# Windows Shell update Q313829 (MS02-014) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q313829-9x
- Version / update id: Q313829
- Verdict: **keep**
- Systems: 95, 98. Microsoft: Windows 98 and 98 SE (Me not affected). The INF has a Windows 9x section, so it also installs on 95 with the IE4 Desktop Update (csv/MDGx); not verified by Microsoft text. English.
- What it fixes: MS02-014 unchecked buffer in the Windows Shell (SHELL32.DLL 4.72.3812.600).
- Description source: Microsoft bulletin MS02-014 (opened) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2002/ms02-014


## Download

- URL: https://download.microsoft.com/download/ie4095/actdesk/4.01_sp2/W9XNT4/EN-US/q313829.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: q313829.exe, 854096 bytes (same size as the availability.csv row)
- SHA-256: f76c332781520b19207ce97995b76924127d05bec511c92e0eac06c4ae963cc1
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2002-05-29, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q313829-9x -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. no EULA in the package; LICENSE.TXT is a short note. The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `q313829.inf`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: IE Help/About "Update Versions" lists Q313829 (Microsoft bulletin); {sys}\SHELL32.DLL file version 4.72.3812.600 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF in the package; bulletin gives no uninstall information. Beacon entry: `Uninstall: none`.