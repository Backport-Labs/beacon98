# Windows Me Q812709 Help and Support update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q812709-me
- Version / update id: Q812709
- Verdict: **keep**
- Systems: ME. Windows Me. English.
- What it fixes: Help and Support Center flaw (HELPCTR.EXE 4.90.0.3004); security fix. Bulletin number not verified.
- Description source: csv/MDGx title + INF


## Download

- URL: http://download.windowsupdate.com/msdownload/update/v3-19990518/cabpool/812709_3FE395B778B7C8704A0DE247305222EB07ED386A.EXE
- Protocol: plain HTTP only (HTTPS certificate on download.windowsupdate.com does not match: SEC_E_WRONG_PRINCIPAL)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 812709_3FE395B778B7C8704A0DE247305222EB07ED386A.EXE, 300352 bytes (same size as the availability.csv row)
- SHA-256: 2013dcbe7b5376b801c7b8480e3edb10d4fb07f023773b619fe36a47deac1cc8
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2003-11-24, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q812709-me -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `QFEREG.INF`; POSTRUNPROGRAM: `812709UP.INF`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\WinME\UPD812709 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF. Beacon entry: `Uninstall: none`.