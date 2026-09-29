# Microsoft Visual C++ 2005 SP1 Redistributable (x86) 8.0.50727.6195 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Microsoft Visual C++ 2005 SP1 Redistributable Package (x86), MFC security update build
- Version: 8.0.50727.6195 (MSI ProductVersion 8.0.61001, ProductCode {710f4c1c-cc18-4c49-8cbf-51240c89a1a2})
- License: Microsoft EULA. External: downloaded from Microsoft's own server; Backport Labs distributes nothing.
- Recommendation: list as `external`. It is the newest VC++ 2005 runtime still on download.microsoft.com.
  The original VC++ 2005 (8.0.50727.42) and SP1 (8.0.50727.762) downloads were not found on Microsoft's servers
  (the SP1 URL https://download.microsoft.com/download/e/1/c/e1c773de-73ba-494a-a5ba-f24906ecf088/vcredist_x86.exe,
  quoted by MDGx, returns 404; the RTM URL I tried, .../d/3/4/d342efa6-.../vcredist_x86.exe, also 404).

## Windows 9x support evidence

- vcredist.msi inside the package (read with the Windows Installer COM API, not installed):
  - Component `nosxs.98CB24AD_...` installs msvcr80.dll (and likewise msvcp80/msvcm80/atl80) into SystemFolder with the
    condition `(VersionNT < 501) or Version9X`: the package is authored to install the DLLs into the SYSTEM folder on Windows 9x.
  - Component `ansi_atl80` (ANSI build of ATL80.dll) has condition `Version9X`: a 9x-only component.
  - Summary information PageCount = 200: needs Windows Installer 2.0 or later.
  - No LaunchCondition rows.
- msvcr80.dll 8.0.50727.6195 imports the same 160 KERNEL32 functions as build 8.0.50727.4053 (compared with a
  PE import reader); it does not import EncodePointer/DecodePointer. It imports GetLongPathNameW.
- Not verified: running on Windows 95/98/ME (no VM interaction). Whether Windows 95 can load msvcr80.dll was not checked.
- VC++ 2008: NOT for 9x. The VC++ 2008 SP1 redistributable still on Microsoft's server
  (https://download.microsoft.com/download/9/7/7/977B481A-7BA6-4E30-AC40-ED51EB2028F2/vcredist_x86.exe, 9.0.30729.4148,
  4,489,160 bytes, signed Microsoft, Valid) contains install.ini with `SupportWin9X=0` and `MinNTVersion=5.0`. So VC++ 2008
  requires Windows 2000 or later; no 2008 package.

## Download

- URL: https://download.microsoft.com/download/8/B/4/8B42259F-5D70-43F4-AC2E-4B208FD8D66A/vcredist_x86.EXE
  (found on the MDGx add.htm page, verified by downloading)
- HTTPS: 200 OK (Last-Modified 2025-03-04). Plain HTTP (`curl --http1.0 http://...`): 302 redirect to the HTTPS URL only.
  No download.windowsupdate.com copy is known.
- File: vcredist_x86.EXE, 2,710,520 bytes
- SHA-256: 8648c5fc29c44b9112fe52f9a33f80e7fc42d10f3b5b42b2121542a13e44adfd
- Authenticode: Valid, CN=Microsoft Corporation, timestamped (signing certificate valid to 2021-12-02; the file was re-signed after 2009).
- Published checksum: none published by Microsoft.
- Alternative kept for reference: alt-8.0.50727.4053\vcredist_x86.exe (ATL security update build, MSI ProductVersion 8.0.59193)
  - URL: https://download.microsoft.com/download/6/B/B/6BB661D6-A8AE-4819-B79F-236472F6070C/vcredist_x86.exe (HTTPS 200, HTTP 302 to HTTPS)
  - 2,748,432 bytes, SHA-256 885cc108368fe6e9689c5586a6c4fd7f34d263ee940f720ec86ac24e179305c2, Authenticode Valid (Microsoft Corporation)
  - Double-wrapped: outer IExpress runs VCREDI~3.EXE, which is another IExpress running `msiexec /i vcredist.msi`. Superseded by 6195.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ms-vcredist2005 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- Microsoft EULA. The package has no LICENSE resource and vcredist.msi has no UI/EULA dialog, so no EULA text is inside.
  LICENSE.TXT holds a short note. Microsoft's own server distributes the file; Beacon only downloads it from there.

## Security

- 8.0.50727.6195 is the newest 2005 SP1 runtime build found on Microsoft's server (it is newer than 4053, the ATL update).
  Known security problems of this build: not checked against NVD (unknown).

## Install behaviour

- Installer type: IExpress (Win32 Cabinet Self-Extractor 6.00.2900.2180) containing vcredist.msi and vcredis1.cab.
- IExpress resources (read with 7-Zip, not run): RUNPROGRAM=`msiexec /i vcredist.msi`, ADMQCMD/USRQCMD=<None>, REBOOT=1, SHOWWINDOW=0.
  Because there is no quiet command, `/q` alone would still show the MSI's UI. Silent: IExpress `/q:a` plus `/c:` to replace the command:
  `vcredist_x86.EXE /q:a /c:"msiexec /i vcredist.msi /qn"` (the /Q:A and /C: switches are IExpress's; the command is the package's own
  RUNPROGRAM with /qn added). Not tested.
- The wrapper imports only ANSI KERNEL32/ADVAPI32/USER32/GDI32/COMCTL32/VERSION functions (checked), so it should start on 9x; not tested.
- Restart: MSI property REBOOT=Suppress; restart normally not needed.
- Requires: Windows Installer 2.0 (PageCount 200). Beacon `Requires: msi 2.0`.
- Detection: file {sys}\MSVCR80.DLL (9x install location per the nosxs component), file version 8.0.50727.6195; and
  HKLM\Software\Microsoft\Windows\CurrentVersion\Uninstall\{710f4c1c-cc18-4c49-8cbf-51240c89a1a2}.
  Beacon check satisfied: `file {sys}\MSVCR80.DLL` (and `file {sys}\MSVCP80.DLL`).
- Uninstall: registered in Add/Remove Programs (ARPNOREMOVE not set; ARPNOMODIFY=1, ARPNOREPAIR=1) under the product name
  "Microsoft Visual C++ 2005 Redistributable". `Uninstall: registry Microsoft Visual C++ 2005 Redistributable`.

## Verification notes

- Verified by downloading/opening: both vcredist files, the MSI tables, the IExpress resources, the VC++ 2008 install.ini.
- Not verified: installation on 98/ME, behaviour on Windows 95, Microsoft system-requirements pages (Download Center pages for these
  files are gone; WebSearch was unavailable).
