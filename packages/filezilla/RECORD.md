# FileZilla 2.2.22 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: FileZilla Client 2.x (Tim Kosse; the MFC client, before the 3.x rewrite)
- Package id: filezilla
- Version: 2.2.22 (files dated 2006-04-20)
- License: GNU GPL version 2 or later; FzSFtp.exe also under the PuTTY licence; bundles OpenSSL 0.9.8a DLLs and zlib 1.2.3
- Recommendation: 2.2.22. It is the last 2.x release that runs on Windows 98/ME. 2.2.23 through 2.2.32 (the last 2.x) are Unicode builds, and the author states in writing that they do not run on 9x/ME. No KernelEx build was tested. KernelEx could in theory run 2.2.32, which fixes more security holes, but I found no evidence that it works, so I do not recommend it.

## Windows 9x support evidence

- readme.htm of 2.2.32 (in the official FileZilla_2_2_32.zip, Internet Archive copy of http://download.filezilla-project.org/legacy/FileZilla_2_2_32.zip, opened), version history:
  "Version 2.2.23 / New features: Now using Unicode internally. As result, no longer runs on Windows 9x/ME. This should fix every charset conversion issue as long as the server supports UTF8."
  The entries for 2.2.24 to 2.2.32 do not mention bringing back 9x support. (2.2.24b only says "Fix NT4 compatibility".) The "Requirements" line in that readme still lists 95/98/ME, but it was never updated, so it is stale boilerplate.
- Trac ticket #1078 "2.2.23 won't execute after install" (https://trac.filezilla-project.org/ticket/1078; the live site returns 403 to bots, so I read the Internet Archive copy): several users report a "Microsoft Visual C++ Runtime Library / Runtime Error!" with 2.2.23 and 2.2.23a on 98SE and ME, and "Re-installing 2.2.22 solves the problem." The final comment is from Tim Kosse (author): "Windows 98 is no longer supported. Please update to Windows 2000 or newer."
- FileZilla forum sticky "Filezilla D/L links 2/3 for legacy OS" by boco (forum contributor, not the author), https://forum.filezilla-project.org/viewtopic.php?t=7089 (Internet Archive copy): "Windows 95C - last working Filezilla 2.2.18" and "Windows 98/SE/ME - last working Filezilla 2.2.22".
- readme.htm inside the 2.2.22 installer (extracted with host 7-Zip, not run): "Requirements: Windows XP, 2000, 95, 98, NT or ME ... Up-to-Date MFC and Common Controls version ... Kerberos for Windows if you want to use the GSS support."
- Import table of FileZilla.exe 2.2.22 (parsed here): it is an ANSI build. MFC is linked statically, so no MFC42.DLL is needed despite the readme text. It statically imports WS2_32.dll (Winsock 2), SHLWAPI.dll (PathStripToRootA, PathFindExtensionA, PathFindFileNameA, PathIsUNCA; these come with IE 4 or later) and COMCTL32 _TrackMouseEvent. Windows 98 and ME include all of these.
- Windows 95: the readme names it, but it needs the Winsock 2 update and the SHLWAPI.dll from IE 4 or later. A forum contributor says 2.2.18 was the last version that worked on 95C. Neither claim was verified, so the entry lists Systems 98, ME only. Adding 95 would need a test plus `Requires: winsock2` and `Requires: file {sys}\SHLWAPI.DLL`.
- KernelEx: not needed for 2.2.22.

## Download

- The official locations are gone:
  - SourceForge project "filezilla" now holds only the 3.69.3 files plus a README.md that says "FileZilla Client and Server downloads have moved for performance reasons" (https://filezilla-project.org/download.php?show_all=1, current 3.x only). The old "FileZilla Client/2.2.22" folder and its RSS return 404, so the SourceForge MD5/SHA1 from the RSS feed could not be compared.
  - FileZilla's own legacy directory http://download.filezilla-project.org/legacy/ (the link the forum sticky gives) now returns 404 over HTTP. Over HTTPS it redirects to the home page.
- Therefore I took the files from the Internet Archive copy of the author's own legacy server. That is allowed here because the license is GPL and the official server no longer has them:
  - https://web.archive.org/web/20170705id_/http://download.filezilla-project.org/legacy/FileZilla_2_2_22_setup.exe (capture 2017-07-04)
  - A second capture from 2023-12-21 (https://download.filezilla-project.org/legacy/FileZilla_2_2_22_setup.exe) is byte-identical (same SHA-256).
  - Original SourceForge-era URL (Wayback CDX, 2007): http://downloads.sourceforge.net/filezilla/FileZilla_2_2_22_setup.exe
- File: FileZilla_2_2_22_setup.exe, 3,503,265 bytes (32-bit NSIS 2.25 installer)
- SHA-256: debbded0540a69803ce6e3a99a9d9fff9996652b987d82c5bd1ae3b5bd82d6b0
- SHA-1: d0f3aeacef2eb4ae364532f16e892519d1879b28
- MD5: 7e66ac559b6041bdd291344d01d0ad80
- Published checksum: the author's FileZilla_2_2_22.md5 from the same legacy directory (Internet Archive captures 2017-07-05 and 2023-06-02, identical) lists `7e66ac559b6041bdd291344d01d0ad80 *FileZilla_2_2_22_setup.exe`: MATCH. SourceForge's RSS MD5/SHA1 were not available (folder removed).
- Authenticode: not signed.
- Alternatives (not downloaded): FileZilla_2_2_22.zip (portable zip, MD5 91d20daca2618e03a7c78de2cff57674 per the author's .md5) and FileZilla_2_2_22_dbg.zip (debug symbols). Third-party sites (FileHippo, OldVersion.com, etc.) also carry it; none were used.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\filezilla -DisableRemediation` on 2026-09-29, run once after the installer and FileZilla source were downloaded and again after all src\ files were in place (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- Source headers (e.g. source/FileZilla.cpp): "either version 2 of the License, or (at your option) any later version", so GPL-2.0-or-later. The installer shows install/license.txt (GPL v2) and ships GPL.html, legal.htm and puttylicense.html.
- FzSFtp.exe is PuTTY-based. The readme says the PuTTY licence (MIT-style) "affects the sftp stub FzSFtp.exe and all its source files".
- Redistributing the unmodified installer is allowed (GPL s.1 and s.3) if we include the license and the complete corresponding source, offered from the same place (s.3 last paragraph). We host the source:

## Matching source (hosted)

- FileZilla: https://web.archive.org/web/20170705id_/http://download.filezilla-project.org/legacy/FileZilla_2_2_22_src.zip (the installer's own "Source code" option pointed at http://filezilla.sourceforge.net/install_data/mirror.php?v=2_2_22&t=src, which no longer exists)
  - src\FileZilla_2_2_22_src.zip, 2,372,507 bytes
  - SHA-256 f76c65ec29b9ae8ba59f3b4df1ad13b0c83251be81e73e16e86a8a1049f0d0aa
  - MD5 c6b340bec1309903428d69ad192bdeb6: MATCHES the author's .md5 list.
  - It contains FileZilla, FzSFtp (PuTTY-based) with its full source, the language DLLs, the documentation and the NSIS script install/FileZilla.nsi (dated 2006-04-20, MUI_VERSION "2.2.22").
- Bundled binaries whose sources are NOT in that archive:
  - libeay32.dll / ssleay32.dll: OpenSSL 0.9.8a (file version 0.9.8a; the archive has only the headers in source/openssl/). Since the Python 2.5.4 package does the same, the source is added: https://www.openssl.org/source/old/0.9.x/openssl-0.9.8a.tar.gz, src\openssl-0.9.8a.tar.gz, 3,271,435 bytes, SHA-256 30f8f61fb1316f4fb51410c740b4879b8e26b417c8d870e486144b10b8041c73. Its MD5 1d16c727c10185e4d694f87f5e424ee1 and SHA-1 2aaba0f728179370fb3e86b43209205bc6c06a3a match openssl.org's .md5/.sha1 files. That is the same file as the one used for Python in the catalog.
  - zlib 1.2.3, linked into FileZilla.exe (strings "deflate 1.2.3 Copyright 1995-2005"; no zlib sources in the archive). Added: https://zlib.net/fossils/zlib-1.2.3.tar.gz, src\zlib-1.2.3.tar.gz, 496,597 bytes, SHA-256 1795c7d067a43174113fdf03447532f373e1c6c57c08d61d9e4e9be5e244b05e. zlib.net publishes no checksum for it, so none was compared.
  - FzGSS.dll (2004-08-29): FileZilla's Kerberos GSS helper. It loads MIT Kerberos for Windows (gssapi32.dll, krb5_32.dll) at run time, and those are not bundled. Its source is NOT in the source zip (only source/gss/*.h headers), and I could not find it. Unresolved: this is the one bundled GPL-side binary without matching source.
  - dbghelp.dll 6.3.0005.1: Microsoft redistributable, not open source and not covered by the GPL. It falls under the GPL s.3 "normally distributed with the operating system" exception only loosely. Redistribution follows Microsoft's Debugging Tools redistribution terms, which were not checked here.
  - MFC and the Visual C++ runtime are linked statically (Microsoft, system-library exception).
- License caveat: FileZilla links OpenSSL, whose license has an advertising clause that the FSF considers GPL-incompatible. The 2.2.22 sources have no explicit OpenSSL linking exception; AsyncSslSocketLayer.cpp only carries the OpenSSL acknowledgement. This is the author's own long-standing distribution (and third-party PuTTY/contributor code is MIT or contributed to him), so the practical risk is low, but it is recorded.
- LICENSE.TXT contains: a summary header, the GPL v2 (install/license.txt), the PuTTY licence (FzSFtp/LICENCE), the OpenSSL 0.9.8a LICENSE and the zlib notice from zlib 1.2.3's zlib.h.

## Security

Sources: NVD API 2.0 (cpeName cpe:2.3:a:filezilla-project:filezilla_client:2.2.22 gives 3 matches; keywordSearch "filezilla" gives 22), cpeName cpe:2.3:a:openssl:openssl:0.9.8a (93 matches), and the author's version history in the 2.2.32 readme.

Affect 2.2.22 (client):
- CVE-2006-2403: buffer overflow in FileZilla before 2.2.23, remote code execution (CVSS2 7.5). The changelog says "Fix critical buffer overflow. Remote code execution might have been possible if connecting to a malicious server." NVD lists 2.2.22 explicitly.
- CVE-2007-0315: multiple buffer overflows before 2.2.30a (registry settings storage in Options.cpp, transfer queue in QueueCtrl.cpp), CVSS2 9.3. NVD lists 2.2.22.
- CVE-2007-2318: multiple format string bugs before 2.2.32 via FTP server responses/data, remote code execution, CVSS2 9.3 (range up to 2.2.31).
- CVE-2007-0317: format string in LogMessage before 3.0.0-beta5, CVSS2 7.5 (range covers all 2.x).
- OpenSSL 0.9.8a (used for FTP over SSL/TLS): NVD returns 93 CVEs for this version. The worst include CVE-2006-3738 (SSL_get_shared_ciphers buffer overflow, CVSS2 10.0; fixed in 0.9.8d, which FileZilla adopted in 2.2.28), CVE-2009-3245 and CVE-2016-2108 (ASN.1, CVSS2 10.0), and CVE-2009-3555 (TLS renegotiation). The TLS protocol versions and ciphers are also obsolete.
- FzSFtp.exe is based on a 2005-era PuTTY ("PuTTY-FZ-Local" build) that includes sshbn.c/sshrsa.c/sshdss.c. PuTTY SSH-layer CVEs fixed in PuTTY 0.63 likely apply, e.g. CVE-2013-4206 (heap buffer underflow in modmul with a crafted DSA signature from the server, CVSS2 6.8). This was not verified CVE by CVE.

NVD matches that do not apply:
- CVE-2019-5429 (fzsftp in home directory, 3.x), CVE-2023-48795 (Terrapin; the old PuTTY code has no ChaCha20/EtM) and CVE-2024-31497 (PuTTY 0.68-0.80 P-521 ECDSA). These are CPE range matches only.
- CVE-2006-2173: FileZilla Server (CPE filezilla_server), not the client.
- CVE-2005-2898 (weak password obfuscation when "secure mode" is off; disputed): NVD lists 2.2.14b/2.2.15 only. 2.2.22 behaves the same way (the installer asks about "secure mode"; in silent mode it writes "Run in Secure Mode"=0, so passwords are stored with weak obfuscation). Treat it as applicable in practice.

Summary: 4 FileZilla CVEs apply (plus 1 disputed), and the bundled OpenSSL 0.9.8a has dozens more (93 NVD matches). The worst are CVE-2007-2318 and CVE-2007-0315 (CVSS2 9.3, code execution from a malicious FTP server) and CVE-2006-3738 in OpenSSL (CVSS2 10.0). None are fixed in any version that runs on 9x.

## Install behaviour

- Installer type: NSIS 2.25 (7-Zip reports "SubType = NSIS-2.25"). The script is install/FileZilla.nsi in the source zip (7-Zip exposes no [NSIS].nsi for this installer).
- Silent install: standard NSIS `/S` (optionally `/D=<folder>` last). FileZilla does not document it, but the script handles silent mode explicitly: `IfSilent NoSecure` (stores "Run in Secure Mode"=0) and `IfSilent usexml` (settings in FileZilla.xml, "Use Registry"=0), and it skips the download-options page. Extra documented script switches: `/secure`, `/registry`, `/forceregistry`. The two optional download sections (French documentation, source code) belong only to the "Full" install type. They fetch from filezilla.sourceforge.net, which is dead, and they are not in the Standard set, which as the first InstType should be the one selected at start (NSIS behaviour, not tested). French docs are also preselected when the installer language is French. If a download section did run, it would only fail and continue. Not verified: whether the LangDLL language dialog (MUI_LANGDLL_DISPLAY in .onInit) is suppressed by /S in this NSIS 2.25 build. It should be tested in the VM before publishing.
- Default folder: `$PROGRAMFILES\FileZilla`, stored in HKCU/HKLM `Software\FileZilla\Install_Dir`.
- Uninstaller: yes. `$INSTDIR\uninstall.exe` is registered at HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\FileZilla` with DisplayName "FileZilla (remove only)". The uninstaller removes HKCU/HKLM `Software\FileZilla` and the uninstall key. There is no documented silent uninstall switch; the NSIS standard is `uninstall.exe /S`.
- Standard install contents: FileZilla.exe, FzSFtp.exe, FzGSS.dll, dbghelp.dll, libeay32.dll, ssleay32.dll, 17 language DLLs, FileZilla.chm, FileZilla.pdb (7 MB debug symbols), readme/license files. About 12.5 MB in total, hence Installed-Size 12600. It also creates Start Menu folder "FileZilla" (FileZilla, Uninstall) and a desktop shortcut.
- Kerberos GSS login needs MIT Kerberos for Windows, which is not bundled and not required for FTP/FTPS/SFTP.

## Verification notes

- Verified by opening or downloading: SourceForge files page, RSS feeds and README.md; HEAD requests to download.filezilla-project.org/legacy; Internet Archive CDX listing of that directory; the author's FileZilla_2_2_22.md5 (two captures); the installer (hashed, listed and text files extracted with host 7-Zip 26.03, never executed); the 2.2.22 source zip (NSIS script, licenses, headers); the 2.2.32 portable zip readme (temp folder only); archived trac ticket #1078 and forum topic t=7089; NVD API records; the openssl.org .md5/.sha1 files.
- From search snippets only: nothing that the record relies on.
- Not verified: running on Windows 95/98/ME (no VM interaction); silent install behaviour of the language dialog; the source of FzGSS.dll; Microsoft's redistribution terms for dbghelp.dll 6.3.

## Hold before publishing (added 2026-09-29 by the coordinating check)

The installer ships FzGSS.dll (the Kerberos/GSS helper used by FileZilla.exe). Listing
FileZilla_2_2_22_src.zip with .NET ZipFile shows only source/AsyncGssSocketLayer.*,
source/OptionsGssPage.* and the headers source/gss/krb5.h, krb5proxy.h and win-mac.h; there is no
source for FzGSS.dll itself. Under GPL-2.0 s.3 we must offer the complete corresponding source of
what we distribute, so hosting is not certain to be legal until FzGSS.dll's source is found
(e.g. in the FileZilla 2 SVN history), or legal advice says the DLL is a separate work. The VLC
precedent (bundled libraries without sources) led to "external", but FileZilla's own server no
longer offers 2.x, so external is not possible. Do not add this entry to CATALOG.TXT until resolved.
A web search for the FzGSS source could not be made in this session (search budget used up).
