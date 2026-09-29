# WinHTTrack Website Copier 3.33 - Beacon 98 record

- Date checked: 2026-09-29
- Package: WinHTTrack Website Copier (Xavier Roche and contributors)
- Version: 3.33 (engine version id 3.33.15, from src/htsglobal.h inside the installer; file dated 05/Feb/2005 on the download page)
- License: GNU GPL version 2 or later, with an OpenSSL linking exception
- Recommendation: 3.33, the build the author offers for pre-2000 Windows.

## Windows 9x support evidence

- https://www.httrack.com/page/2/en/index.html (opened): the download table lists httrack-3.33.exe "For Windows systems older than Windows 2000" as "WinHTTrack installer (also included: command line version)", 3,755,091 bytes, 05/Feb/2005. The newer 3.49.2 and 3.50.4 builds are listed without such a note.
- https://www.httrack.com/history.txt (downloaded): no entry states when 9x was dropped. After 3.33 come 3.40 (many engine changes), 3.41 ("changed API/ABI"), and later "switched from wsock32.dll to ws2_32.dll" and "Unicode filenames handling". So "last for 98" rests on the author's download-page statement, not on a changelog line.
- 95: unknown. The Inno script allows 95 (MinVersion=4,4), but the program needs msvcr71.dll/MFC71.dll (Visual C++ .NET 2003 runtime), for which Windows 95 support was not verified. ME: covered by "older than Windows 2000"; not tested.
- No KernelEx needed.

## Download

- URL (official): https://download.httrack.com/cserv.php3?File=httrack-previous.exe (linked from the page as httrack-3.33.exe)
- File: httrack-3.33.exe, 3,755,091 bytes (size equals the one on the page)
- SHA-256: e81689ade88c8d7d85b4368092155947dbf987c5da21d7da01dbee6515c28ec5
- Published checksum: none found on httrack.com. Not compared.
- The installer title is "WinHTTrack Website Copier 3.33" (read with innoextract 1.9 --list; not run).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\winhttrack -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- license.txt inside the installer: GPL "either version 2 of the License, or any later version", plus "as a special exception, Xavier Roche gives permission to link the code of this program with the openSSL library ... and distribute linked combinations including the two".
- Bundled third-party files in the installer: libeay32.dll + ssleay32.dll (OpenSSL 0.9.6g, 9 Aug 2002; OpenSSL + SSLeay licenses, which allow binary redistribution with their notices), zlib1.dll (zlib 1.2.1, zlib license), msvcr71.dll and MFC71.dll (Microsoft VC++ .NET 2003 runtime, which Microsoft allowed developers to redistribute with their applications; HTTrack distributes them, and we pass the installer on unmodified).
- LICENSE.TXT here has four parts: license.txt and copying (GPL 2 text) from the installer, the OpenSSL 0.9.6g LICENSE (from the OpenSSL_0_9_6g tag on github.com/openssl/openssl), and the zlib 1.2.1 notice (from zlib.h at tag v1.2.1 on github.com/madler/zlib). The installer itself does not seem to carry the OpenSSL license, so adding it covers the OpenSSL advertising/notice clause.
- Redistribution of the unmodified installer is allowed. GPL s.3 source obligation: the installer itself contains the engine source (src\), the Windows GUI, library and IE-bar source (src_win\) and the Inno script, so the source accompanies the binary. We also host the upstream engine tarball below.

## Matching source (hosted)

- The exact 3.33 tarball is not on httrack.com any more: https://download.httrack.com/httrack-3.33.tar.gz returns HTTP 200 but serves httrack-3.50.4 (checked by listing it; deleted). GitHub xroche/httrack has no tags before 3.48.
- Used instead: Debian's copy of the upstream tarball for the same engine version, httrack 3.33.15 (Debian 3.33.15-1, first seen 2005-03-12).
  - URL: https://snapshot.debian.org/file/54ad5ae77adc96dc8ab8e31fa5f49303881d51ff (httrack_3.33.15.orig.tar.gz)
  - File: src/httrack_3.33.15.orig.tar.gz, 1,431,407 bytes
  - SHA-1 54ad5ae77adc96dc8ab8e31fa5f49303881d51ff: MATCH with snapshot.debian.org's file id
  - SHA-256: a2d6fdd49e5b822f13b89b3a74492bcb9c06c47d3bfd95675c9c62ca808b43fb
  - Its src/htsglobal.h has HTTRACK_VERSIONID "3.33.15", the same as the installer's.
- This tarball has the engine only. The WinHTTrack GUI source (src_win\) is only inside the installer. Not in either: OpenSSL 0.9.6g and zlib 1.2.1 sources (their licenses do not require offering source), and the MS runtime (proprietary, redistributable).

## Security

Sources: NVD API 2.0 (keyword "httrack"), history.txt, bundled library versions.

HTTrack itself:
- CVE-2008-3429: buffer overflow in URI processing, "HTTrack and WinHTTrack before 3.42-3", long URL, CVSS2 6.8. Applies.
- CVE-2010-5252: untrusted search path (httrack-plugin.dll) in 3.43-9. Whether 3.33 loads that plugin was not verified.

Bundled libraries (not individually counted):
- OpenSSL 0.9.6g (2002): dozens of later CVEs apply to 0.9.6 before 0.9.6m and to 0.9.6 in general, e.g. CVE-2003-0543/0544 (ASN.1 parsing, fixed in 0.9.6k), CVE-2004-0079 (null dereference in do_change_cipher_spec, fixed in 0.9.6m), CVE-2006-4339 (RSA signature forgery). Its TLS is also too old for most current HTTPS sites.
- zlib 1.2.1: CVE-2004-0797 (inflate DoS, fixed in 1.2.2), CVE-2005-2096 (inflate buffer overflow, fixed in 1.2.3, CVSS2 7.5), CVE-2018-25032 (deflate memory corruption, before 1.2.12).

Summary: 1 CVE for HTTrack itself (plus 1 possible), and many in the bundled OpenSSL 0.9.6g and zlib 1.2.1. Worst: CVE-2005-2096 (zlib heap overflow, reachable from downloaded compressed content) and CVE-2008-3429 (URL overflow, a malicious site can trigger it during a mirror).

## Install behaviour

- Installer type: Inno Setup 4.1.0 ("Inno Setup Setup Data (4.1.0)"; script src_win\InnoSetup\httrack.iss inside the installer, read after extracting only text files with innoextract).
- Silent install: `/VERYSILENT /NORESTART` are Inno 4.x switches. `/SUPPRESSMSGBOXES` may not exist in 4.1.0 (not verified; Inno ignores unknown switches, as far as known). The [Run] entries are `skipifsilent`, so nothing is launched after a silent install.
- Tasks: desktop icon (checked by default), Quick Launch icon (unchecked).
- Default folder: `{pf}\WinHTTrack`; group WinHTTrack; `AdminPrivilegesRequired=no`.
- Side effects: registers WinHTTrackIEBar.dll (`regserver`), .whtt file type, sound events under HKCU and HKU\.DEFAULT, HKLM `Software\WinHTTrack Website Copier\...\Path`.
- Uninstaller: yes. Add/Remove Programs name: `WinHTTrack Website Copier 3.33` (AppVerName; the script sets no UninstallDisplayName), key `WinHTTrack Website Copier_is1`. The script in the installer may not be exactly the one used to build it, but its AppVerName matches the setup's own title.
- Installed size: about 8.8 MB (sum of the file list, including the source folders).

## Verification notes

- Verified by opening or downloading: httrack.com download page, history.txt, the installer's file list and its license.txt, copying, warning.txt, httrack.iss, htsglobal.h, the DLL version strings (libeay32, zlib1), the Debian snapshot file info, OpenSSL/zlib license texts, NVD.
- Not verified: 95 support, running on 98/ME, a published checksum, whether /SUPPRESSMSGBOXES works in Inno 4.1.0, CVE-2010-5252 applicability.
