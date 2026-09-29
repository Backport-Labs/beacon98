# NirCmd 2.87 - Beacon 98 record

- Date checked: 2026-09-29
- Package: NirCmd (Nir Sofer, NirSoft)
- Version: 2.87 (page date 23/04/2024; exe version resource 2.87)
- License: NirSoft freeware; free redistribution of the unmodified, complete package allowed
- Recommendation: host 2.87 (the only version NirSoft serves). Systems: 98, ME (the page says 9x, but see the import check below for 95).

## Windows 9x support evidence

- https://www.nirsoft.net/utils/nircmd.html (opened 2026-09-29), "System Requirements":
  "This utility can work in all versions of Windows operating system: Windows 9x/ME,
  Windows NT, Windows 2000, Windows XP, Windows Server 2003, Windows Vista, Windows Server 2008, Windows 7, Windows 8, and Windows 10."
- Some individual commands are marked on the page as XP or later (for example `speak`), so not every command works on 9x.
- Static check (not executed): nircmd.exe and nircmdc.exe are UPX-packed. A decompressed copy (UPX 5.2.1 `-d`, in a temp folder) imports only ANSI functions from KERNEL32/USER32/ADVAPI32/GDI32/SHELL32/WINMM/ole32/msvcrt; OS/subsystem version 4.0. It imports SendInput, EnumDisplayMonitors, EnumDisplayDevicesA and GetMonitorInfoA statically; these exist on 98 and later but not on Windows 95, and a missing static import stops the Windows loader from starting the program. So despite "9x" on the page, 2.87 almost certainly does not start on Windows 95 (inference from the import table, not tested). Systems in the entry is therefore 98, ME.
- Not tested in a VM.

## Download

- Page: https://www.nirsoft.net/utils/nircmd.html ("Download NirCmd")
- URL: https://www.nirsoft.net/utils/nircmd.zip (32-bit; a separate nircmd-x64.zip exists)
- The URL has no version number. NirSoft replaces the file when a new version comes out, so we must host our copy. Server Last-Modified: Tue, 23 Apr 2024 11:52:57 GMT.
- File: nircmd.zip, 124,310 bytes
- SHA-256: 122aee2fbdd0c793367b519635c45e5611688159b72f5e58a27f9256a53c9014
- MD5: 44b437bce960eb8343abb986d95ef5f5
- Published checksum: https://www.nirsoft.net/hash_check/?software=nircmd lists nircmd.zip, 124310 bytes, updated April 23 2024 11:52:57, SHA-256 122aee2fbdd0c793367b519635c45e5611688159b72f5e58a27f9256a53c9014: MATCH.
- Zip contents: nircmd.exe (46,080, FileVersion 2.87), nircmdc.exe (45,056, console version, 2.87), NirCmd.chm (46,449). No readme.txt.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\nircmd -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". Note: some other antivirus products flag NirCmd as a "hacktool"/PUA because it can change system settings silently.

## License

License section of the page (quoted verbatim):

> This utility is released as freeware.
> You are allowed to freely distribute this utility via floppy disk, CD-ROM,
> Internet, or in any other way, as long as you don't charge anything for this.
> If you distribute this utility, you must include all files in
> the distribution package, without any modification !

- LICENSE.TXT contains this License section and the Disclaimer from the page (the zip has no readme).
- Hosting is allowed. Conditions: no charge (met, Beacon is free), all files of the package, unmodified (met by hosting nircmd.zip as downloaded).
- No source code; not open source.

## Security

NVD keyword searches "nircmd" and "nirsoft" (2026-09-29): no CVE for NirCmd (the one "nirsoft" hit, CVE-2006-3785, is about Symantec pcAnywhere). 0 known problems. NirCmd is itself a powerful tool (registry writes, shutdown, process kill), which is its purpose.

## Install behaviour

- Plain zip, no folders inside; no installer, no uninstaller, nothing in Add/Remove Programs.
- NirCmd has no main window. Run without arguments, nircmd.exe offers to copy itself into the Windows folder; Beacon must not do that.
- Suggested: `Install: unzip C:\NIRCMD` and `After: path C:\NIRCMD`, as with Info-ZIP (a short 8.3 folder is safer in AUTOEXEC.BAT's PATH than `C:\Program Files\...`). A Start Menu shortcut to the help file is useful. Uninstall: files.

## Verification notes

- Opened/downloaded: nircmd.html, hash_check page, nircmd.zip; version resource read with .NET FileVersionInfo; imports read from a UPX-decompressed copy in a temp folder. Nothing was run.
- Unverified: actual run on 95/98/ME.
