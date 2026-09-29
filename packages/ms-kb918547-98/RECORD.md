# Windows 98 KB918547 WMF update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-kb918547-98
- Version / update id: KB918547
- Verdict: **keep**
- Systems: 98. Windows 98 and 98 SE (the csv lists this one file for both). English.
- What it fixes: Graphics Rendering Engine / Windows Metafile fix (csv/MDGx). MS06-001 says 98/98 SE/Me are not critically affected; it does not name KB918547.
- Description source: csv/MDGx title + INF
- Notes: Installs into {win}\KB918547.

## Download

- URL: http://download.windowsupdate.com/msdownload/update/v3-19990518/cabpool/Windows98-KB918547-ENU_ab29740587b8bf4cd6380a47a89e3ce.exe
- Protocol: plain HTTP only (HTTPS certificate on download.windowsupdate.com does not match: SEC_E_WRONG_PRINCIPAL)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: Windows98-KB918547-ENU_ab29740587b8bf4cd6380a47a89e3ce.exe, 148008 bytes (same size as the availability.csv row)
- SHA-256: 6e2d1b1be550a524d53ec534d02d8bcf41c386a7bccb9e274fb7fd0ec212406f
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2007-10-04, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-kb918547-98 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `KB918547.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98\UPD918547; Uninstall\918547 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Add/Remove entry "Windows 98 KB918547 Update". Beacon entry: `Uninstall: registry Windows 98 KB918547 Update`.