# Miranda IM 0.7.19 ANSI - Beacon 98 verification record

- Date checked: 2026-09-29
- Package: Miranda IM (multi-protocol instant messenger)
- Version: 0.7.19, ANSI build (released 2009-04-17)
- License: GPL-2.0-or-later
- Recommendation: 0.7.19 ANSI from SourceForge. The miranda project's SourceForge file area has only 0.7.x (in OldFiles, up to 0.7.19) and 0.10.24 and later. No 0.8.x or 0.9.x file exists there; I checked the folder listings, the OldFiles RSS and direct download paths. 0.8.x ANSI builds were published only on miranda-im.org (the Internet Archive has the 0.8.0 to 0.8.11+ announcements). They could be fetched from the Internet Archive, which the rules allow for GPL software whose own server is gone, but I found no statement that 0.8 still runs on 98, and it was not pursued. 0.9 and later are Unicode-only (from memory).

## Windows 9x support evidence

- readme.txt in the official 0.7.19 ANSI zip and installer (read from the archive), section 5 "Compatibility issues": "Miranda IM supports all released versions of Windows from Windows 95 to Windows XP." It also says for Windows 95: "make sure that you have Winsock and DUN upgrades installed. Menu icons are not supported in Windows 95."
- Same readme, history for 0.5: "Two Miranda distributions are available since 0.5: the ANSI (for Win95/98/ME) and the Unicode one (for NT4/Win2k/XP/Win2003)".
- My own check (PE import tables of every .exe and .dll in the ANSI zip, read only, nothing run): all are subsystem 4.0. Sockets use WSOCK32 (Winsock 1.1), with no getaddrinfo and no other XP-only calls. The Unicode (W) functions imported by ICQ.dll (MessageBoxW, SendMessageW and so on) exist on 98 as exports, most of them as stubs, so the DLLs load. The ANSI build is meant to use the ANSI paths.
- Extra runtime DLLs: MSVCP60.DLL (advaimg.dll, IRC.dll), MSIMG32.DLL (avs.dll; 98 and later), SHLWAPI.DLL (chat.dll; comes with IE 4 and later), RPCRT4.DLL (msn.dll). Whether stock 98 SE includes MSVCP60.DLL is unknown; if it is missing, only the image and IRC plugins fail. On 95, MSIMG32 does not exist (from memory), so the avatar plugin would not load there.
- SSL: winssl.dll is a small OpenSSL-API shim over Windows' schannel.dll ("Microsoft Unified Security Protocol Provider"; strings read from the DLL). On 98 that means SSL 3.0/TLS 1.0 at best, so it cannot connect to current XMPP or IRC servers that require TLS 1.2. Plain IRC works in principle.
- Protocols: AIM, MSN, Yahoo and the old ICQ servers have been shut down. IRC and XMPP (Jabber) servers still exist. Gadu-Gadu is unknown. This is general knowledge, not verified today.
- KernelEx: not needed. Not tested in the VM.

## Download

- Official project: https://sourceforge.net/projects/miranda/ (files: /miranda-im/ and /OldFiles/). miranda-im.org was not used (the domain no longer belongs to the project).
- URL: https://downloads.sourceforge.net/project/miranda/OldFiles/miranda-im-v0.7.19-ansi.exe
- File: miranda-im-v0.7.19-ansi.exe, 1,497,672 bytes
- SHA-256: ec5f238109b357a93779f24d83ab987d3c8c6e4b797b5b6df85aad28d7b7beb4
- MD5: 0341485b164b847d810fe77077a792e7. The SourceForge OldFiles RSS lists 0341485b164b847d810fe77077a792e7 and 1,497,672 bytes: MATCH. The RSS was read with a fetch tool, because SourceForge answers curl on its web pages with 403. The project publishes no other checksums or signatures. Authenticode: none.
- Alternative (kept in `alternative\`, not in the entry): miranda-im-v0.7.19-ansi.zip, 1,573,532 bytes, SHA-256 44f766da3f15d0121463b790948b2570ea67f96edcd33f21b61738d6dc1e2cd7, MD5 9bebc0acbe79a72a461bb5d6d762ec08 (matches the RSS). It has the same program files but no license.txt. Its readme refers to "License.txt", which is missing from the zip, so the installer is the better file to host.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\miranda-im -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". The alternative zip was in the folder during the scan.

## License

- license.txt from the installer (extracted with 7-Zip; nothing executed): Richard Hughes' note that plugins dynamically linked to Miranda are not derived works, then the GNU GPL version 2 with the usual "either version 2 of the License, or (at your option) any later version" notice. The readme says: "Miranda IM is released under the terms of the GNU General Public License."
- Bundled pieces: advaimg.dll is built from FreeImage (dual GPL / FreeImage Public License; both texts in miranda/plugins/freeimage/ of the source); zlib.dll is zlib; the protocol plugins are part of the Miranda source tree. All sources are in the source archive below.
- LICENSE.TXT here contains a short Beacon header (the above) plus the unmodified license.txt.
- Conditions: include the license, offer the source. Redistribution of unmodified files is allowed.

## Matching source (hosted)

- URL: https://downloads.sourceforge.net/project/miranda/OldFiles/miranda-im-v0.7.19-src.zip
- File: src\miranda-im-v0.7.19-src.zip, 5,946,513 bytes
- SHA-256: 308e6babd4f3fb5afcb914f5759fe1c2cb411fc457774bd3eadb875bf343658d
- MD5 e1b1673cfb3c13d136279b070fa5e0b6: MATCH with the RSS.
- Contents checked: core (miranda/src), all bundled plugins (avs, chat, clist, db3x, freeimage, import, srmm, winssl, zlib), all protocols (AimOscar, Gadu-Gadu, IcqOscarJ, IRCG, JabberG, MSN, Yahoo), and miranda-tools (dbtool, the NSIS installer script, and the protocol icon DLL sources). Nothing without source was found.

## Security

Source: NVD API 2.0, keywords "miranda" and "miranda im".
- CVE-2007-5590 (before 0.7.1), CVE-2007-5396 (0.7.1), CVE-2007-5542 and -5543 (0.6.8 / 0.7.0, CVSS2 9.3): all are recorded for versions before 0.7.19. NVD does not list 0.7.19 as affected, and I did not check whether each fix is in 0.7.19.
- CVE-2005-1093: the third-party PopUp Plus plugin, which is not included.
- Known CVEs for 0.7.19: 0. But the program has not been maintained since 2009, and the protocol code parses data from remote servers and users. Later Miranda releases fixed bugs that never got CVEs, and its SSL (Windows 98 Schannel) is outdated. The entry carries a warning anyway.

## Install behaviour

- Installer: NSIS 2 (7-Zip reports "Nsis", SubType NSIS-2; the script is miranda-tools/installer/miranda.nsi in the source).
- Silent: standard NSIS `/S`, which Miranda's documentation does not mention. The script has no MessageBox or prompts in the sections. With /S all default sections are installed: core, all 7 protocols, the Import plugin, and Start Menu, Desktop and Quick Launch shortcuts.
- Default folder: `$PROGRAMFILES\Miranda IM`. The folder is also read from HKLM App Paths\miranda32.exe "Path" for upgrades.
- Add/Remove Programs: HKLM `...\Uninstall\Miranda IM`, DisplayName "Miranda IM 0.7.19", UninstallString `$INSTDIR\Uninstall.exe` (standard NSIS, `/S` works for silent uninstall).
- The profile database (*.dat) is stored in the program folder by default (mirandaboot.ini; the "store in user home" option exists only in the Unicode build). The uninstaller does not delete profiles (from the script's Uninstall section; not fully checked).
- Zip layout (alternative): files at the root (miranda32.exe, dbtool.exe, zlib.dll, winssl.dll, mirandaboot.ini, readme.txt, Plugins\, Icons\), about 3,615 KB unpacked.

## Verification notes

- Opened or downloaded: the SourceForge project file listings (miranda-im, OldFiles) and OldFiles RSS through a fetch tool; the Internet Archive capture list of miranda-im.org and the 0.8.0 announcement (curl); the three files; the readme and license from the archives; the installer script from the source; PE import tables; NVD.
- Not verified: running on 95/98/ME; MSVCP60.DLL on stock 98; 0.8.x on 98.
