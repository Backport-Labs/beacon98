# Servant Salamander 2.0 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Servant Salamander (ALTAP, Ltd.; now Altap Salamander)
- Version: 2.0 (released 2/28/2001), English, evaluation (unregistered) build
- License: commercial shareware, 30-day evaluation. The evaluation version may be redistributed unmodified and free of charge.
- Availability: hosted (the license allows it; the publisher serves it only over FTP, which Beacon cannot use).
- Recommendation: package it next to `servant-salamander` 1.52 (freeware). 2.0 has plugins (ZIP, TAR, CAB, ARJ, ACE, RAR, picture viewer),
  but it is a trial that can no longer be registered, and 1.52 is fully free. Altap Salamander 2.54's self-extractor has
  PE subsystem 5.0, so it does not start on 9x (slice 6 finding, not re-checked here).

## Windows 9x support evidence

- doc\readme.txt inside salen200.exe (opened after unpacking the archive with the host's 7-Zip; nothing was run):
  "This version of Servant Salamander requires Windows 95, Windows 98, Windows ME, Windows NT 4.0, Windows 2000 or later."
  "Servant Salamander uses HTML Help, which requires Internet Explorer 4.0 to be installed on your computer."
- setup.inf: `CheckCommonControls=4.71`. Setup checks for the common controls 4.71 (shipped with IE 4.0 and Windows 98).
  On Windows 95 without IE 4 the setup is expected to refuse or warn (not tested).
- salamand.exe (file version 2.0): PE subsystem version 4.0.
- Not tested on Windows 95/98/ME (no VM interaction).

## Download

- Official location: ftp://ftp.altap.cz/pub/altap/salamand/salen200.exe. The FTP index.txt (opened) says
  "salen200.exe 1361121 02/28/2001 Servant Salamander 2.0, English". Altap's download page
  https://www.altap.cz/salamander/downloads/ (opened) links "Previous Versions" to that FTP folder.
- HTTP/HTTPS: none. http://ftp.altap.cz/pub/altap/salamand/salen200.exe redirects to http://www.altap.cz/... then
  https://www.altap.cz/... and ends in 404; https://ftp.altap.cz/... is 404 (tested with curl.exe -sS -I -L on 2026-09-29).
  So Beacon can only get it from our server.
- File: salen200.exe, 1,361,121 bytes (downloaded over FTP; size matches index.txt)
- SHA-256: 9682a428696d0bce07fb854bebac562b0522cda08b582448df30da7da76c8513
- Published checksum: none.
- Authenticode: salen200.exe and the inner salamand.exe are not signed.
- Also on the FTP folder, not downloaded: sal20upd.exe (465,434 bytes, 11/06/2002, "Servant Salamander 2.0 Plugins Update").
  It was not examined; whether it fixes the plugin CVE below is unknown.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\servant-salamander-2 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT is doc\license.txt from salen200.exe, unchanged ("ALTAP, Ltd. Electronic End User License Agreement For Servant Salamander").
- Redistribution clause, quoted:
  "The evaluation (unregistered) version of the Software, may be freely distributed, with exceptions noted below, provided
  the distribution package is not modified. You may not charge any fee for the copy or use of the evaluation Software itself,
  but you may charge a distribution fee that is reasonably related to any cost you incur distributing the evaluation Software
  (e.g. packaging). You must not represent in any way that you are selling the Software itself."
- Conditions: unmodified package (we host salen200.exe as published); no fee (Beacon is free); do not present it as sold.
  The "exceptions noted below" are the plug-in clause (plug-ins only inside Salamander) and the clause on self-extracting
  archives made with the ZIP plug-in (free only for personal non-commercial use). Neither restricts distributing the package.
- Trial terms: "You may install this Software to test and evaluate for 30 days. Following this test period of 30 days or less,
  if you wish to continue to use Software, you must register."
- Nag: strings in salamand.exe (read, not run): "Servant Salamander is running in evaluation (unregistered) mode now. You may use
  this software to test and evaluate for 30 days. Once the trial period is over, you will have to purchase a license or
  uninstall." and "This evalution mode is fully functional." It shows an "Evaluation Mode" dialog with an expiry date.
  Whether the program stops working after 30 days is unknown (not run).
- Registration: Altap's download page now offers only Altap Salamander 4.0 as freeware ("Users of older Salamander versions
  can upgrade to version 4.0 free of charge"; 4.0 "requires Windows 7 or newer"). No way to buy a 2.0 license was found.

## Security

- CVE-2007-3314: buffer overflow in the Portable Executable Viewer plugin (peviewer.spl) of Servant Salamander 2.0 and 2.5
  (per NVD, found by slice 6). peviewer.spl is in this package. Opening a crafted PE file in the viewer could run code.
- Bundled unace.dll (1998-08-29) and unrar.dll (2000-06-19): old third-party decoders. Whether CVE-2005-2856 (UNACEV2.DLL)
  or unRAR CVEs apply to these exact builds was not verified.
- Summary: 1 known CVE, plus old archive decoders of unknown status.

## Install behaviour

- Installer type: ALTAP's own installer. salen200.exe is a small Win32 stub followed by a gzip stream (offset 20480) holding
  a tar archive with setup.exe, setup.inf and the program files. Not ZIP, so Beacon's `unzip` cannot unpack it.
- Silent install: none documented. setup.exe contains only the strings `RunProgramQuiet` and `UninstallRunProgramQuiet`,
  no recognizable command-line switch. The entry runs the installer interactively.
- Default folder: `%4\Servant Salamander 2.0` (setup.inf `DefaultDirectory`; %4 is presumably Program Files).
- Shortcuts: desktop and quick-launch style links "Salamander 2.0" / "Servant Salamander 2.0", and a Start Menu folder
  "Servant Salamander 2.0" with the program and "Uninstall Servant Salamander 2.0".
- Uninstaller: yes. setup.inf writes HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\Servant Salamander 2.0`
  with DisplayName "Servant Salamander 2.0", UninstallString `<dir>\remove\remove.exe`, QuietUninstallString
  `<dir>\remove\remove.exe /q`.
- Settings: HKCU `Software\Altap\Servant Salamander 2.0`.

## Verification notes

- Opened: FTP index.txt, Altap download page, the archive listing, doc\license.txt, doc\readme.txt, setup.inf, strings of
  setup.exe, remove.exe and salamand.exe (unpacked into a temp folder with 7-Zip; nothing executed), curl tests of HTTP(S) paths.
- From slice 6 (not re-verified here): CVE-2007-3314 details, the 2.54 PE subsystem finding.
- Not verified: behaviour after 30 days, running on 95/98/ME, whether %4 is Program Files.
