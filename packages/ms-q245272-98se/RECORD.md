# Windows 98 SE Q245272 WebTV update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q245272-98se
- Version / update id: Q245272
- Verdict: **keep**
- Systems: 98. Windows 98 SE, only with WebTV for Windows installed. English.
- What it fixes: WebTV interactive content (ENHTRIG.DLL 4.10.2224, NABTSFEC.SYS 4.10.2223).
- Description source: csv/MDGx title + INF


## Download

- URL: http://download.windowsupdate.com/msdownload/update/v3-19990518/cabpool/245272USA8_BCB9234CBD9818C3EAB1E0DEA97DC09087CDCB25.EXE
- Protocol: plain HTTP only (HTTPS certificate on download.windowsupdate.com does not match: SEC_E_WRONG_PRINCIPAL)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 245272USA8_BCB9234CBD9818C3EAB1E0DEA97DC09087CDCB25.EXE, 291520 bytes (same size as the availability.csv row)
- SHA-256: 39fd35e8715c886c24d03ae1c02888946bbc4e1df1baaa87811ecf6ff00c05a2
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q245272-98se -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `245272UP.INF`; POSTRUNPROGRAM: `csetup.exe 245272.cat`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SE\UPD245272 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF. Beacon entry: `Uninstall: none`.