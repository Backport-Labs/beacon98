# Windows 95 Support Assistant help files - Beacon 98 record

- Date checked: 2026-09-29
- Package id: ms-assist-95
- Version / update id: assist
- Verdict: **not useful**
- Systems: 95. Windows 95. English.
- What it fixes: Self-help help files (ASSIST.HLP, HCL95.HLP, VBRUN300). PKZIP self-extractor, unsigned (16-bit, Authenticode not applicable).
- Description source: csv/MDGx title + archive listing
- Notes: Old 1995 help content; no update value.

## Download

- URL: https://download.microsoft.com/download/win95upg/Utility/2/W9X/EN-US/assist.exe
- Protocol: HTTPS (plain HTTP answers only with a 302 redirect to HTTPS)
- Other Microsoft location: none found (the Windows Update cabpool names contain a hash and cannot be derived; web search was not available for this pass).
- File: assist.exe, 1320501 bytes (same size as the availability.csv row)
- SHA-256: 3448d5b87849f17cb8db7116a9f414c39d4d9e38e3fb05c0c89360757ef92188
- Authenticode (Get-AuthenticodeSignature on Windows 11): not signed (Get-AuthenticodeSignature: "The form specified for the subject is not one supported or known by the specified trust provider")
- Microsoft does not publish checksums for these files.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-assist-95 -DisableRemediation` on 2026-09-29: "found no threats" (engine 1.1.26080.3; signatures 1.459.466.0; scanned twice, the second time after all files were written).

## License

Microsoft software, listed as external: Backport Labs distributes nothing, the file comes from Microsoft's server. no EULA in the package; LICENSE.TXT is a short note. The Microsoft terms still apply to the user.

## Install behaviour

- Installer type: not IExpress

- Silent switches: n/a
- Restart: n/a (not an installer). The update replaces system files that are in use; with /R:N the restart must be done by the user. Which exit code wextract returns in that case (0 or 3010) was not verified.
- Detection: n/a (QFECheck reads the Setup\Updates keys). Beacon has no registry check, so this cannot yet be expressed as a Requires line.
- Uninstall: n/a Beacon entry: `Uninstall: none`.