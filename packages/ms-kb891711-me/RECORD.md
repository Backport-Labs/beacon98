# Windows Me KB891711 cursor and icon update (MS05-002) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-kb891711-me
- Version / update id: KB891711-v2
- Verdict: **keep**
- Systems: ME. Windows Me. English.
- What it fixes: MS05-002 cursor and icon handling (v2).
- Description source: Microsoft bulletin MS05-002 (opened) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2005/ms05-002


## Download

- URL: http://download.windowsupdate.com/msdownload/update/v3-19990518/cabpool/WindowsME-KB891711-v2-ENU_71c3336e6d7630cff2739a9d05d2eed.EXE
- Protocol: plain HTTP only (HTTPS certificate on download.windowsupdate.com does not match: SEC_E_WRONG_PRINCIPAL)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: WindowsME-KB891711-v2-ENU_71c3336e6d7630cff2739a9d05d2eed.EXE, 147928 bytes (same size as the availability.csv row)
- SHA-256: 97f7864d06d08c181a6d6405c599dade388555d1d853d1150d37684ed40fd33d
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2006-04-05, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-kb891711-me -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `891711UP.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\WinME\UPD891711; Uninstall\891711 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Add/Remove entry "Windows Millennium Edition KB891711 Update". Beacon entry: `Uninstall: registry Windows Millennium Edition KB891711 Update`.