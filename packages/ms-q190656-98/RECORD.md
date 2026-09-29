# Windows 98 Q190656 NETDI update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q190656-98
- Version / update id: Q190656
- Verdict: **keep**
- Systems: 98. Windows 98 first edition (key W98.SP1). English.
- What it fixes: Microsoft + Novell network client NETDI.DLL 4.10.2029 fix.
- Description source: csv/MDGx title + INF


## Download

- URL: https://download.microsoft.com/download/win98/Update/Q190656/W98/EN-US/190656_98UP.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 190656_98UP.EXE, 276456 bytes (same size as the availability.csv row)
- SHA-256: f2edf4907cb9a199a7f5222b4f9b8c88c91687c8e6f1e68ae394e0dd6f85cf9f
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q190656-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `190656up.inf`; POSTRUNPROGRAM: `CSETUP.exe 190656.cat`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SP1\UPD190656 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 190656UN.INF (QFE). Beacon entry: `Uninstall: none`.