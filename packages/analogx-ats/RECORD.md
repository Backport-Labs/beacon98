# AnalogX Atomic TimeSync 1.04 - Beacon 98 record

- Date checked: 2026-09-29
- Package: AnalogX Atomic TimeSync (AnalogX, LLC)
- Version: 1.04 (PAD release date 2009-03-17; the file on the server is dated 2009-05-25)
- License: Freeware. The publisher does not allow offsite hosting, so the package is `external`.
- Recommendation: 1.04, the only version the publisher offers. The csv row listed 1.03 (msfn-98se); 1.04 is newer and still states Windows 95 support.

## Windows 9x support evidence

- https://www.analogx.com/contents/download/network/ats.htm (opened): "Atomic TimeSync works on all versions of Windows, from Window 95 to Windows 7 and everything inbetween (including XP, Vista, Win2k, etc)." History: "v1.04 Rebuilt and fixed Vista issues".
- PAD file https://www.analogx.com/contents/download/Network/ats/pad.xml (opened): version 1.04, OS list "Win95,Win98,WinME,WinNT 3.x,WinNT 4.x,Windows2000,WinXP,...", license "Freeware", size 354536, download URL http://www.analogx.com/files/atsi.exe.
- PE header of atsi.exe (read with 7-Zip, not run): OS version 4.0, subsystem version 4.0, x86, built with linker 8.0 (Visual Studio 2005). Subsystem 4.0 is loadable by 95/98/ME. The installed program itself is inside a proprietary compressed payload and could not be inspected.
- Not tested on Windows 95/98/ME here.

## Download

- Page: https://www.analogx.com/contents/download/network/ats.htm
- URL: https://www.analogx.com/files/atsi.exe (also http://www.analogx.com/files/atsi.exe)
- `curl.exe -sS -I -L` on both: HTTP/1.1 200, Content-Length 354536, Last-Modified Mon, 25 May 2009 23:39:49 GMT, no redirect. Plain HTTP works without HTTPS.
- File: atsi.exe, 354,536 bytes
- SHA-256: b00c4f995854b087c5197bcf53bb8f4d692129c133dba1ba1567508db5df4402
- Published checksum: none published. The PAD file size (354536) matches.
- Authenticode: signed, status Valid ("Signature verified."), signer CN="AnalogX, LLC", O="AnalogX, LLC", L=Tempe, S=AZ, C=US. Windows 98 does not check Authenticode.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\analogx-ats -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- Freeware. Download FAQ (https://www.analogx.com/contents/download/faq.htm, opened): "I am giving away all of the programs on here, for free; not shareware or grovelware".
- Redistribution: NOT allowed for us to host. Same FAQ: "I don't normally allow offsite hosting of any of the programs on my site". Linking to the file on analogx.com is explicitly welcomed ("The next option would be just to have a link to the actual file"). So Beacon lists it as `external` with analogx.com as the only location.
- No trial, no nag, no expiry (freeware). The FAQ mentions an optional "electronic registration" that is only a user count, not a payment.
- LICENSE.TXT holds these quotes. Whatever license text the installer itself shows could not be read without running it.

## Security

- NVD keyword search "AnalogX" (API 2.0, 2026-09-29): 13 CVEs, all for AnalogX SimpleServer and AnalogX Proxy (CVE-2000-0011 ... CVE-2003-0410). None for Atomic TimeSync.
- Known problems for this version: 0. Note that its built-in NTP server listens on the network when enabled.

## Install behaviour

- Installer type: AnalogX's own installer (FileDescription "AnalogX Atomic TimeSync Installer"); not NSIS, Inno, InstallShield or Wise (no signatures of those in the file). The payload is a proprietary compressed block that 7-Zip cannot open.
- Silent switch: none documented. The FAQ says "you simply need to double click on the icon, and follow the directions". Beacon runs it interactively (`Install: exe`).
- Default folder: unknown (the installer asks: strings "Installation Directory...", "Install %s into %s?").
- Uninstaller: yes. The FAQ: "All of the programs that have an installer, have a corresponding uninstaller ... Control Panel->Add/Remove Programs". The installer writes `Software\Microsoft\Windows\CurrentVersion\Uninstall\%s %s` with UninstallString; the exact display name is unknown. `Uninstall: registry AnalogX Atomic TimeSync` in ENTRY.TXT is a guess that must be checked on a test machine.
- Side effects: the FAQ says the installer temporarily installs a custom font, and "None of the programs on the site install components into other places in your system".

## Verification notes

- Verified by opening: the download page, Documentation.htm, pad.xml, faq.htm, HTTP headers over https and http, the file's PE header and signature.
- Not verified: behaviour on 95/98/ME, silent install, install folder, Add/Remove Programs name.
