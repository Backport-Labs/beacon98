# WinSCP 4.3.9 - Beacon 98 verification record

- Date checked: 2026-09-29
- Package: WinSCP (Martin Prikryl)
- Version: 4.3.9 (hotfix release of the stable 4.3 branch, 2012-07-24)
- License: GPL-3.0-or-later; the WinSCP icon set has separate terms (see License); includes PuTTY (MIT) and OpenSSL code
- Recommendation: host **winscp439.zip** (the official portable build), not the installer. batch2.md proposed 5.0.6, but 5.0.6 is a *beta* (folder "5.0.6 beta" on SourceForge). 4.3.9 is newer (2012-07-24 vs 2012-02-29), is a stable release, and has a newer OpenSSL (1.0.1c vs 1.0.0g). 5.0.6 beta stays an alternative only if a 5.0 feature is needed.

## Windows 9x support evidence

- https://winscp.net/eng/docs/incompatible_changes (opened): "5.0.7: Dropped support for Windows 95/98/ME."
- https://winscp.net/eng/docs/history_old (downloaded), entry "5.0.7 beta 2012-05-08": "IDE upgraded to Embarcadero C++Builder XE2. Change: Dropped support for Windows 95/98/ME. Minimal supported version is Windows 2000."
- The 4.3.x branch was maintained in parallel with the 5.0 betas. history_old: "4.3.9 (hotfix) 2012-07-24 Back-propagated some improvements and fixes from 5.0.8 beta release"; "4.3.8 (hotfix) 2012-06-07 ... SSL core upgraded to OpenSSL 1.0.1c". The 4.3 branch never had the 9x drop, which was tied to the XE2 compiler move in 5.0.7. So 4.3.9 is the last stable release for 95/98/ME. This is an inference from the history, not an explicit "4.3.9 runs on 98" statement.
- Windows 95: the 5.0.7 entry names 95 together with 98/ME, and older history entries fix 95/98 problems (e.g. "Drag&drop shell extension failed to register on Windows 95/98", "Removed dependency on netapi32.dll (not present on Windows 95/98/ME)" in 4.0.5). Not tested.
- The current requirements page (https://winscp.net/eng/docs/requirements) only covers Windows 7 and later.
- KernelEx: not needed.

## Download

- SourceForge folder: https://sourceforge.net/projects/winscp/files/WinSCP/4.3.9/ (opened; the official project, linked from winscp.net)
- Hosted file: https://downloads.sourceforge.net/project/winscp/WinSCP/4.3.9/winscp439.zip
  - winscp439.zip, 2,674,150 bytes
  - SHA-256: c96174ab7375faf7fe1fe9e1a6efa64a0de43e961f635011f927c4b8a27c1c5a
  - MD5 12e68a0859a28c2e57b67432d61e1ab8, SHA-1 77c494d0778e1f4cb7c66c396b09c87710885d30
- Published checksums: the author's release notes winscp439readme.txt (downloaded from the same folder, kept here) list MD5 12e68a0859a28c2e57b67432d61e1ab8 and SHA-1 77c494d0778e1f4cb7c66c396b09c87710885d30 for the zip: both MATCH. SourceForge shows the same MD5 and SHA-1.
- Installer (downloaded for inspection only, in `not-hosted\`): winscp439setup.exe, 3,951,464 bytes, SHA-256 32492ae3c93e675e75d462b356a4cf3462646a5db8547c175541bbd33f334c01. MD5 5ba330d31beb529725452c6d9c353d00 and SHA-1 093e84777d81ac0e1f93f66b3c59086aa8cf5cb0 MATCH the release notes. Authenticode: valid, signed by "Martin Prikryl" (Prague).
- winscp439readme.txt, 1,521 bytes, SHA-256 5741dddd52d3716db921a796c0aec4c50b9c2a81982dc7cf36c38c1936ae5308 (reference only).

### Why not the installer

The release notes say: "The installer includes Google Chrome recommendation." The installer script in the source (release/winscpsetup.iss) shows that the Chrome build embeds Google's files GoogleChromeInstaller.exe, chromech.exe and gcapi_dll.dll, and a separate licence file (licence.setup-chrome). Those Google binaries are not under the GPL and nothing grants us the right to redistribute them. In silent mode the offer is skipped (`ChromeAllowed := (not WizardSilent) and ...`), but hosting the file would still mean distributing Google's installer. The installer also reports the installation to http://winscp.net/install.php. The portable zip has neither problem. The installer cannot be "external" either: both winscp.net and downloads.sourceforge.net answer plain HTTP with a redirect (301 and 302) and do not serve the file over HTTP.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\winscp -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". This covered the zip, the installer in not-hosted\ and the source.

## License

- `licence` inside winscp439.zip is the unmodified GPL version 3. resource/License.txt in the source is the same GPLv3. WinSCP's license page says "either version 3 of the License, or (at your option) any later version".
- Icon set, from https://winscp.net/eng/docs/license (opened 2026-09-29; the page was last modified 2026-01-02, so these are the current terms, not necessarily the 2012 wording): "all images distributed in or with WinSCP application are NOT published under the GPL license. It means that it is not allowed to redistribute or reuse these images or parts of them or modifications of them without WinSCP separately or in or with another software." The same page says "WinSCP installation package and WinSCP icon set have separate licenses."
- **Decision on the icons.** The restriction forbids using the images *apart from WinSCP*: on their own, or in or with another program. Redistributing the unmodified official WinSCP files, with the images inside WinSCP.exe, is redistribution *with* WinSCP, and the GPL page grants "Copy WinSCP anywhere you want in any number of copies or Provide a download link on your website". Hosting the unmodified zip is therefore allowed. Beacon must not extract, reuse or modify the icons, for example for its own catalog UI. The hosted source archive also contains the images; it is distributed with WinSCP, as the GPL requires, so that is also covered.
- **Decision on the installer.** The icon terms do not forbid it, but the Google Chrome components inside it do (see above). Do not host it.
- LICENSE.TXT here contains: a header with the icon-set terms quoted from the license page, the GPLv3 (`licence` from the zip), the PuTTY licence (resource/LicensePuTTY.txt) and the OpenSSL licence (openssl/LICENSE), both from winscp439source.zip.
- Conditions: include the license, and offer the matching source (GPLv3 s.6(d): offering it from the same place is enough).

## Matching source (hosted)

- URL: https://downloads.sourceforge.net/project/winscp/WinSCP/4.3.9/winscp439source.zip
- File: src\winscp439source.zip, 4,705,587 bytes
- SHA-256: 15be1bcd5a69f84773cdb1d47df5e8de5a808c1cc98180c3c9d0848eae3cb952
- MD5 e382cd5b151f5e81957bfb20d3186150 and SHA-1 a5cbe998f3098c759e9f5a3368d61636bc56d6f5: MATCH the release notes.
- Bundled code: the archive includes the sources of PuTTY, OpenSSL, the FileZilla FTP engine, Toolbar2000/TBX and the other packages under packages/. The build needs Borland C++Builder 6, whose runtime is proprietary but is a compiler system library. No bundled library without source was found. The Chrome and OpenCandy files are *not* in the source (the script includes them from ..\chrome and ..\opencandy), which does not matter because the zip does not contain them.

## Security

Sources: NVD API 2.0, keyword "winscp" (10 results), plus the WinSCP history.

Affect 4.3.9:
- CVE-2013-4852 (CVSS2 6.8): integer overflow in PuTTY code, "WinSCP before 5.1.6"; a malicious SSH server can crash WinSCP and possibly run code. The related PuTTY 0.62 bugs fixed together in WinSCP 5.1.6 (CVE-2013-4206, -4207, -4208; from memory, not checked against NVD) also apply.
- CVE-2014-2735 (CVSS2 5.8): FTPS certificate host name not checked, "before 5.5.3" (man in the middle).
- CVE-2018-20684 (CVSS2 6.4): SCP client accepts arbitrary files from the server, "before 5.14 beta".
- CVE-2021-3331 (CVSS3 9.8): crafted URL loads session settings and runs programs, "before 5.17.10". Exploitable only when WinSCP is registered as the sftp:// / scp:// URL handler. The portable zip does not register it, but the user can from Preferences.
- The bundled OpenSSL 1.0.1c (used for FTPS) has many known problems, including CVE-2014-0160 (Heartbleed, 1.0.1 to 1.0.1f), which a malicious FTPS server could use to read client memory. WinSCP's own fix was the OpenSSL upgrade in 5.5.3 (from memory, not verified).

Not affected: CVE-2006-3015 and CVE-2007-4909 (fixed in 4.0.4 and earlier); CVE-2024-31497 (ECDSA in PuTTY 0.68 to 0.80; 4.3.9 has no ECDSA); CVE-2023-48795 (Terrapin needs ChaCha20-Poly1305 or EtM MACs, which 4.3.9 does not have; not verified in code); CVE-2024-7421 (Devolutions product). CVE-2020-28864 is recorded for 5.17.8 only; whether 4.3.9 has the same FTP long-file-name overflow is unknown.

Summary: 4 WinSCP CVEs certainly apply (plus 3 PuTTY-core CVEs and the OpenSSL 1.0.1c problems). The worst is CVE-2021-3331 (CVSS3 9.8, needs the URL handler), then CVE-2013-4852 (malicious SSH server, possible code execution). Its SSH also lacks the modern algorithms many current servers require, so connecting to a 2026 OpenSSH server may fail unless the server allows older algorithms (not tested).

## Install behaviour

Hosted package (zip):
- winscp439.zip entries (listed with .NET ZipFile, nothing extracted to run): `licence` (35,147), `readme` (354), `WinSCP.com` (95,920), `WinSCP.exe` (6,479,984). No folders.
- Beacon: `unzip {pf}\WinSCP`, Start Menu shortcut to `{pf}\WinSCP\WinSCP.exe`, `Uninstall: files`. WinSCP stores its settings in the registry (HKCU\Software\Martin Prikryl\WinSCP 2), which Beacon's `files` removal leaves behind. `WinSCP.exe /UninstallCleanup` removes them (from the installer script; not tested).

Installer (not hosted, for reference):
- Inno Setup (release/winscpsetup.iss). The documented switches (https://winscp.net/eng/docs/installation): /SILENT, /VERYSILENT, /NORESTART and /LANG=; the Chrome offer is skipped when silent.
- Default folder `{pf}\WinSCP`; AppId "winscp3", uninstall key `...\Uninstall\winscp3_is1`. DisplayName is AppVerName = "WinSCP 4.3.9" (the script sets no UninstallDisplayName). Uninstaller unins000.exe.

## Verification notes

- Opened or downloaded: incompatible_changes, history_old, license, installation, requirements and custom_distribution pages on winscp.net; the SourceForge 4.3.9, 5.0.6 beta and WinSCP folder listings (via a fetch tool, because SourceForge's web pages answered curl with 403); the four 4.3.9 files; the zip's licence and readme; the source's licence files and installer script; NVD.
- Not verified: running on 95/98/ME (no VM interaction); CVE-2013-4206/4207/4208 and the Heartbleed fix version come from memory.
