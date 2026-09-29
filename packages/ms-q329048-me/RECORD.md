# Windows Me Q329048 Compressed Folders update (MS02-054) - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q329048-me
- Version / update id: Q329048
- Verdict: **keep**
- Systems: ME. Windows Me with Compressed Folders installed. English.
- What it fixes: MS02-054 Compressed Folders (DUNZIP32/DZIP32 3.0.0.17, ZIPFLDR.DLL 5.50.4921.1000).
- Description source: Microsoft bulletin MS02-054 (opened; Me "only via Windows Update", this is the Windows Update file) - https://learn.microsoft.com/en-us/security-updates/securitybulletins/2002/ms02-054


## Download

- URL: http://download.windowsupdate.com/msdownload/update/v3-19990518/CabPool/329048_3E84647A527E386B05A78DD79AF876BFCFC147E1.EXE
- Protocol: plain HTTP only (HTTPS certificate on download.windowsupdate.com does not match: SEC_E_WRONG_PRINCIPAL)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 329048_3E84647A527E386B05A78DD79AF876BFCFC147E1.EXE, 293184 bytes (same size as the availability.csv row)
- SHA-256: f32042677925c526da8ca17f9089113aca74c231ceb8f4ad179ef8f3c7f20a61
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer CN=Microsoft Corporation, signing certificate valid until 2003-11-24, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q329048-me -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `QFEREG.INF`; POSTRUNPROGRAM: `329048UP.INF`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\WinME\UPD329048 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Microsoft: cannot be uninstalled on Me. Beacon entry: `Uninstall: none`.