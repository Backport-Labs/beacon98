# Windows 95 OSR2 PC Card update - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-pccardupd-95
- Version / update id: UPD980225N1
- Verdict: **keep**
- Systems: 95. Windows 95 OSR2 only (key OSR2). English.
- What it fixes: OSR2 PC Card / CardBus update: CBSS.VXD 4.00.1117, OPENHCI.SYS 4.03.1214, PCCARD.VXD 4.00.1119, PCI.VXD 4.00.1120. The csv title for this URL ("95B OSR 2.0/2.1 International Memory Leak IO.SYS Patches") does not match the file contents.
- Description source: package INF only
- Notes: KB number unknown.

## Download

- URL: https://download.microsoft.com/download/win95/Update/5503/W95/EN-US/PCCARDUPD.EXE
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: PCCARDUPD.EXE, 220328 bytes (same size as the availability.csv row)
- SHA-256: 4a4b89470d82f0910792965dff257ab2b83bcceb1b0cf72a9ecb68080c30cc04
- Authenticode (Get-AuthenticodeSignature on Windows 11): Valid, signer OU=Microsoft Corporation, signing certificate valid until 2001-04-17, countersigned (timestamped)
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-pccardupd-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. LICENSE.TXT = the license agreement the package shows before installing (IExpress LICENSE resource, copied verbatim). The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: IExpress (Microsoft self-extracting setup; resources RUNPROGRAM, POSTRUNPROGRAM, REBOOT, LICENSE read with 7-Zip, not run)
- RUNPROGRAM: `PCCARD.INF`; POSTRUNPROGRAM: `<none>`; REBOOT resource value 3
- Silent switches: /Q:A /R:N (IExpress/wextract switches: /Q:A = quiet, no prompts or license dialog; /R:N = never restart). Chosen from the package type; not executed here.
- Restart: needed. The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: HKLM\Software\Microsoft\Windows\CurrentVersion\Setup\Updates\OSR2\UPD980225N1 (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: No uninstall INF. Beacon entry: `Uninstall: none`.