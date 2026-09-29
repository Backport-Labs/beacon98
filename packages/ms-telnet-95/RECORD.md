# Windows 95 Telnet update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-telnet-95
- Version / update id: W95.TELNET
- Verdict: **keep**
- Systems: 95. All Windows 95 builds (single INF, no edition check seen). English.
- What it fixes: Malformed Telnet argument (TELNET.EXE 5.0.1755.2); security fix.
- Description source: csv/MDGx title + INF contents
- Notes: KB/bulletin number not found in the package; unknown.

## Download

- URL: https://download.microsoft.com/download/win95upg/Update/10/W95/EN-US/telnet95.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: telnet95.exe, 178144 bytes (same size as the availability.csv row)
- SHA-256: 505f0e58bef857d56d26169977b98fccb3a2228187ac61606377e7d1338b43d0
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-telnet-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `Telnetup.inf`; POSTRUNPROGRAM: `<None>`; REBOOT resource value 1
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W95.TELNET; {win}\TELNET.EXE file version 5.0.1755.2 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: TelnetUN.INF copied to {win}\INF\QFE; no Add/Remove entry. Beacon entry: `Uninstall: none`.