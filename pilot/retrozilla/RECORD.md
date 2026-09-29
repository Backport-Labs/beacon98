# RetroZilla 2.3 - Beacon 98 pilot record

- Date checked: 2026-09-28
- Package: RetroZilla (browser/mail/IRC suite, fork of Mozilla Gecko 1.8.1 / SeaMonkey 1.1 codebase)
- Version: 2.3 (GitHub release tag `2.3-release`, published 2025-06-11; latest release as of 2026-09-28)
- Project: https://github.com/rn10950/RetroZilla (site: https://rn10950.github.io/RetroZillaWeb/)

## Windows 9x support evidence (verified by opening)

- readme.md at tag 2.3-release (https://github.com/rn10950/RetroZilla/blob/2.3-release/readme.md):
  "RetroZilla is a fork of Gecko 1.8.1 for improved compatibility on the modern web, with Windows 95 and Windows NT 4.0 in mind."
  "### Supported Operating Systems * Windows 95 * Windows 98 * Windows Me * Windows NT 3.51 * Windows NT 4.0"
- README.txt at tag 2.3-release (https://github.com/rn10950/RetroZilla/blob/2.3-release/README.txt), System Requirements:
  "Windows 95, 98, Me, NT4, 2000 or XP / Intel Pentium class processor (233 MHz or faster recommended) / 64 MB RAM / 26 MB free hard disk space"
- Project website (https://rn10950.github.io/RetroZillaWeb/, fetched): lists Windows 95, 98, ME, NT 4.0 and NT 3.51 as officially supported; current release 2.3.
- Windows 95 separately: yes, explicitly listed (and is the stated design target).
- Only one candidate: 2.3 is the newest release and still targets 9x. Earlier releases (2.2, 2019) are also on GitHub.

## Download

- URL: https://github.com/rn10950/RetroZilla/releases/download/2.3-release/retrozilla-2.3-win32-installer.exe
- File: retrozilla-2.3-win32-installer.exe
- Size: 13,410,304 bytes
- SHA-256: 8d8644d28e607ca1552c2f726b7e18cb455152c1148f774437b37ff940b104f9
- Published checksum: the project publishes no checksum file or signature. GitHub's release-asset API reports
  digest sha256:8d8644d28e607ca1552c2f726b7e18cb455152c1148f774437b37ff940b104f9 (this digest is computed by GitHub, not signed by the author). MATCH.
- Existing copy D:\Win98SE\software\4-Internet\retrozilla-2.3-win32-installer.exe (read only, not modified):
  SHA-256 8d8644d28e607ca1552c2f726b7e18cb455152c1148f774437b37ff940b104f9, so it is IDENTICAL to the official download.
- Alternative (not downloaded): retrozilla-2.3.en-US.win32.zip, 12,677,968 bytes, GitHub digest sha256:186579ffe158d892aabe68cff8af620ffc8ff4207de37d1d2c25a5ac70121a76
  https://github.com/rn10950/RetroZilla/releases/download/2.3-release/retrozilla-2.3.en-US.win32.zip
- Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\pilot\retrozilla -DisableRemediation` on 2026-09-28
(engine 4.18.26080.4, signatures 1.459.442.0): "found no threats".

## License

- Binary license: Mozilla Public License 1.1 (with the Netscape Public License amendments appended). LICENSE.TXT in this folder is the repo's LICENSE file at tag 2.3-release
  (https://raw.githubusercontent.com/rn10950/RetroZilla/2.3-release/LICENSE); it is byte-for-byte the same text (after line-ending normalisation) as the LICENSE.TXT embedded in the installer and shown in its license dialog.
- Source files carry the Mozilla tri-license block "Version: MPL 1.1/GPL 2.0/LGPL 2.1" (verified in xpfe/bootstrap/nsAppRunner.cpp at the tag). The recipient may pick MPL 1.1.
- GitHub reports the repository license as "Other / NOASSERTION".
- Redistribution of the unmodified binary: permitted. Conditions (MPL 1.1 s.3.6 and 3.2): the executable must be accompanied by a notice that the Covered Code source is available and where; source must stay available for at least 12 months after distribution (or 6 months after a later version); the license and notices must not be removed. If distributed under GPL/LGPL instead, the matching source must be offered.
- LEGAL file (old Netscape patent notices, Wang / Intermind) is part of the tree; informational.

## Matching source

- URL: https://github.com/rn10950/RetroZilla/archive/refs/tags/2.3-release.tar.gz
- File: RetroZilla-2.3-release-source.tar.gz, 66,454,754 bytes
- SHA-256: cf3db550464353bcfb0c0e5f1f66a2487a4552828be587f220dbb9983e176130
- Tag commit: 2f274574d3c6ee8769914046920d649bbae9f81b (2025-06-11). Note: GitHub-generated archives are not guaranteed byte-stable over time; keep this copy.

## Security

- The project itself says (website, fetched): "RetroZilla is NOT a secure browser, and is provided for entertainment purposes only", based on 2007-era code with known vulnerabilities.
- Gecko 1.8.1 branch is end-of-life: Mozilla's Firefox 2.0 advisory page (https://www.mozilla.org/en-US/security/known-vulnerabilities/firefox-2.0/) states "Firefox 2.0 is unsupported"; last Firefox 2 update 2.0.0.20 (Dec 2008). SeaMonkey 1.1.x/Thunderbird 2.0.0.x on the same branch received fixes a little longer (e.g. MFSA 2009-01 fixed in SeaMonkey 1.1.15 / Thunderbird 2.0.0.21).
- Count: there is no CVE list for RetroZilla. As a rough proxy, NVD returns 463 CVEs matching cpe seamonkey:1.1.19 (the last Gecko 1.8.1 SeaMonkey), 256 of them CVSS >= 9. This over-counts (many are for code not in 1.8.1, and RetroZilla backported some fixes, NSS updated in 2.3) but shows the scale: essentially all Mozilla memory-safety fixes since 2009 are missing.
- Examples: CVE-2009-3373 (GIF parser heap overflow, CVSS 10, fixed Firefox 3.0.15 / SeaMonkey 2.0), CVE-2009-3372, CVE-2009-3376, CVE-2009-3979 (browser engine memory corruption).
- Mitigation in 2.3: updated NSS with TLS 1.3 and updated root store (release notes).

## Install behaviour

- Installer type: legacy Mozilla XPInstall setup (stub exe with embedded CONFIG.INI, SETUP.EXE and .xpi packages as PE resources; not NSIS/MSI). Inspected by reading resources, not run.
- Silent install: the embedded CONFIG.INI usage text lists `-ms` (Silent mode) and `-ma` (Auto mode), and `-dd [path]` for destination. Not tested; whether the outer stub forwards these to SETUP.EXE is unverified.
- Default folder: `[PROGRAMFILESDIR]\RetroZilla` (C:\Program Files\RetroZilla). Start menu folder "RetroZilla".
- Uninstaller: yes. Writes HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\RetroZilla (2.3)` with DisplayName and UninstallString `[SETUP PATH]\uninstall\retrozillaUninstall.exe`.
- The installer's README tells users to temporarily disable antivirus and install into a clean directory.
- The installer also registers a GRE (Gecko runtime) component (GRE-WIN32-INSTALLER.ZIP embedded).

## Verification notes

- Verified by opening: GitHub API release data and digests, readme.md/README.txt/LICENSE at tag, project website, Mozilla advisory pages, NVD API counts, installer resources.
- Not verified: actual behaviour of `-ms` through the stub; exact list of security fixes backported by RetroZilla.
