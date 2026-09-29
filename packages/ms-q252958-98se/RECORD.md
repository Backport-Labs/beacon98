# Windows 98 SE Q252958 IEEE 1394 update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q252958-98se
- Version / update id: Q252958
- Verdict: **keep**
- Systems: 98. Windows 98 SE only. English.
- What it fixes: IEEE 1394 1394BUS.SYS / OHCI1394.SYS 4.10.2225.
- Description source: csv/MDGx title + INF
- Notes: Newer 1394BUS/OHCI1394 than ms-q242975-98se (2224); install Q242975 first.

## Download

- URL: https://download.microsoft.com/download/win98se/update/5982/w98/en-us/252958usa8.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 252958usa8.exe, 187608 bytes (same size as the availability.csv row)
- SHA-256: 285bd1754605f8daf940bc5c66bb913961309c04e98c54bc25ae76ff396b1a6e
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q252958-98se -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `252958up.inf`; POSTRUNPROGRAM: `CSETUP.exe 252958.cat`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SE\UPD252958 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 252958UN.INF (QFE). Beacon entry: `Uninstall: none`.