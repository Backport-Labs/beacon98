# Windows 98 Q314941 UPnP update (MS01-059) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q314941-98
- Version / update id: Q314941
- Verdict: **keep**
- Systems: 98. Windows 98 and 98 SE, only with the Windows XP Internet Connection Sharing client installed; Microsoft: the patch refuses to install otherwise. English.
- What it fixes: MS01-059 unchecked buffer in Universal Plug and Play (SSDPAPI.DLL, UPNP.DLL, SSDPSRV.EXE 4.90.3003).
- Description source: Microsoft bulletin MS01-059 (opened) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2001/ms01-059


## Download

- URL: https://download.microsoft.com/download/win98SE/Patch/Q314941/W98/EN-US/314941USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 314941USA8.EXE, 228936 bytes (same size as the availability.csv row)
- SHA-256: 5a5097615095c015edf09057cda32f639f14371be116418f9cb16dbf4914dcbf
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2002-05-29, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q314941-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `314941UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD314941 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF. Beacon entry: `Uninstall: none`.