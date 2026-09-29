# Windows 98 SE Q242975 IEEE 1394 / hot-plug update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-q242975-98se
- Version / update id: Q242975
- Verdict: **keep**
- Systems: 98. Windows 98 SE only. English.
- What it fixes: IEEE 1394 and hot-plug fixes: HOTPLUG.DLL, USER32.DLL, SYSTRAY.EXE, USER.EXE, 1394 drivers, NTMAP, IOS.VXD, DISKTSD.VXD.
- Description source: csv/MDGx title + INF
- Notes: Its 1394BUS/OHCI1394 (4.10.2224) are replaced by ms-q252958-98se (4.10.2225); the other files are not.

## Download

- URL: https://download.microsoft.com/download/win98se/Update/2944-2/W98/EN-US/242975USA8.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: 242975USA8.EXE, 597720 bytes (same size as the availability.csv row)
- SHA-256: 26d0af06768f3c7ce906946ce7a13b45cb9421f845e1cea5aa5a637fbb6ff62d
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2000-04-16, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-q242975-98se -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `242975UP.inf`; POSTRUNPROGRAM: `csetup 242975.cat`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\W98.SE\UPD242975 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: 242975UN.INF (QFE). Beacon entry: `Uninstall: none`.