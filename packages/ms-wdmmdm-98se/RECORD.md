# WDM Modem and USB Modem Kit - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-wdmmdm-98se
- Version / update id: kit
- Verdict: **not useful**
- Systems: 98. Modem manufacturers' kit for 98/98 SE (readme). English.
- What it fixes: CCPORT.SYS, USBSER.SYS, WDMMDMLD.VXD retail+debug files and a sample INF for modem makers; not an end-user installer (WinZip self-extractor, no setup).
- Description source: package readme (opened)
- Notes: Its redistribution license only allows modem manufacturers to ship it with their hardware.

## Download

- URL: https://download.microsoft.com/download/whistler/wdmmdm/1.0/wxp/en-us/wdmmdm.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: wdmmdm.exe, 275368 bytes (same size as the availability.csv row)
- SHA-256: b899936906c644ac822d28ab0b2e842ab81ede098072ddc2cca2409ade607fc4
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-wdmmdm-98se -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. no EULA in the package; LICENSE.TXT is a short note. The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: not IExpress

- Silent switches: n/a
- Restart: n/a (not an installer). The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: n/a (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: n/a Beacon entry: `Uninstall: none`.