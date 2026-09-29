# Windows 95 OSR2 AMD-K6-2 update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-amdk6upd-95
- Version / update id: 990602N1
- Verdict: **keep**
- Systems: 95. Windows 95 OSR2, 2.1, 2.5 only (readme). NTKERN.VXD only for OSR2.1. English.
- What it fixes: AMD K6-2 350 MHz+ "Windows Protection Error" (IOS.VXD, ESDI_506.PDR, SCSIPORT.PDR) and backup-to-floppy errors (KB Q192841, Q159153, Q234259 per the package readme).
- Description source: package readme AMDK6UPD.TXT (opened)
- Notes: The readme says to restart. Readme license statement: "Any transfer of this Software ... may only be transferred if first approved by Microsoft."

## Download

- URL: https://download.microsoft.com/download/win95upg/patch/1.2/w95/en-us/amdk6upd.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: amdk6upd.exe, 290288 bytes (same size as the availability.csv row)
- SHA-256: 8b31adafdeea166ef37b8724130d7477921b3fe671fd3ac1ff0ae037a7eb0b8b
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-amdk6upd-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. no EULA in the package; LICENSE.TXT is a short note. The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `AMDK6UPD.INF`; POSTRUNPROGRAM: `<None>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\<Locale>990602N1 (Locale string from the INF, normally UPD); IOS.VXD 4.00.1113 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: Readme: right-click INF\QFE\AMDK6_UN.INF > Install, needs the Windows 95 CD. No Add/Remove entry. Beacon entry: `Uninstall: none`.