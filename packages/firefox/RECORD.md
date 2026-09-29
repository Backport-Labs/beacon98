# Mozilla Firefox 2.0.0.20 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: firefox (Mozilla Firefox, Mozilla Corporation)
- Version: 2.0.0.20 (2008-12-18), the last Firefox 2 release
- License: binary under the Mozilla Firefox EULA 2.0; code under MPL 1.1 / GPL 2.0+ / LGPL 2.1+ (tri-license); Firefox name and logos are Mozilla trademarks and not licensed
- Recommendation: list as `Availability: external`, downloaded from Mozilla's own archive over plain HTTP. Do NOT host it. Mozilla's current Unaltered Software Distribution Policy only lets third parties distribute the most recent Firefox, and the 2.0 EULA grants only a right to use. See License.

## Windows 9x support evidence

- Firefox 2.0.0.20 release notes (verified by downloading;
  https://www.mozilla.org/en-US/firefox/2.0.0.20/releasenotes/ redirects to
  https://website-archive.mozilla.org/www.mozilla.org/firefox_releasenotes/en-us/firefox/2.0.0.20/releasenotes/):
  "Note: This is the last planned release of Firefox 2. All users are encouraged to upgrade to Firefox 3. Firefox 2.0.0.20 does not include Phishing Protection. Release Date: December 18, 2008".
  The same page gives the profile location for "Windows 98, ME: Windows\Application Data\Mozilla\Firefox".
- Firefox 2 system requirements. The release notes link to http://www.mozilla.org/en-US/firefox/system-requirements-v2.html, which now returns 404. Opened through the Internet Archive capture
  http://web.archive.org/web/20100513102234/http://www.mozilla.com/en-US/firefox/system-requirements-v2.html:
  "Operating Systems: Windows 98, Windows 98 SE, Windows ME, Windows NT 4.0, Windows 2000, Windows XP, Windows Server 2003, Windows Vista. Minimum Hardware: Pentium 233 MHz (Recommended: Pentium 500MHz or greater), 64 MB RAM (Recommended: 128 MB RAM or greater), 52 MB hard drive space".
- Firefox 3.0 system requirements (verified by downloading; https://www.mozilla.org/en-US/firefox/3.0/system-requirements/ redirects to firefox.com):
  "Windows Operating Systems: Windows 2000, Windows XP, Windows Server 2003, Windows Vista". So Firefox 3 dropped 98, ME and NT4, and 2.0.0.20 is the last Firefox for 98/ME.
- Windows 95: not listed in the Firefox 2 requirements, so it is not supported. It was not tested here, and I did not check whether KernelEx or other add-ons make it run.
- KernelEx: not needed on 98/ME (officially supported).
- No OS version check found in the installer script (browser/installer/windows/nsis/installer.nsi in the source).

## Download

- Release directory: https://archive.mozilla.org/pub/firefox/releases/2.0.0.20/ (same content on ftp.mozilla.org)
- URL: https://archive.mozilla.org/pub/firefox/releases/2.0.0.20/win32/en-US/Firefox%20Setup%202.0.0.20.exe
- Plain HTTP works: `curl.exe -sS -I --http1.0` on http://archive.mozilla.org/..., http://ftp.mozilla.org/..., http://download-installer.cdn.mozilla.net/... and http://releases.mozilla.org/... (same path) all return `200 OK`, Content-Length 6048152, no redirect to HTTPS.
- File: `Firefox Setup 2.0.0.20.exe`, 6,048,152 bytes (en-US, 32-bit)
- SHA-256: b7ca35bdddb8e4adf099c62013e889efd0e0b0bbac90bb18c847f7632b214960
- SHA-1: c932a5123f9a7952a7e00a72594204aa460597b2
- MD5: be504a7c00f29b5feb332a51f7d68f69
- Published checksums: the release directory's SHA1SUMS lists `c932a5123f9a7952a7e00a72594204aa460597b2  ./win32/en-US/Firefox Setup 2.0.0.20.exe` (MATCH). MD5SUMS lists `be504a7c00f29b5feb332a51f7d68f69` (MATCH).
- GPG: `Firefox Setup 2.0.0.20.exe.asc` checked with the release directory's KEY file (gpg from Git for Windows):
  "Good signature from "Mozilla Software Releases <releases@mozilla.org>" [expired]", made 2008-12-18 with DSA subkey B57B548417785FE8, primary key fingerprint 8D6F 1BA4 A340 4DDB 3F2F D080 7447 4499 8123 47DD. The key has since expired; the signature was valid when it was made.
- Other languages are in `win32/<locale>/`; only en-US was downloaded. Mozilla offered no .msi and no zip build for Windows 2.0.0.20.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\firefox -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats". Scanned folder held the installer and src\firefox-2.0.0.20-source.tar.bz2.

## License

- The installer shows `browser/EULA.rtf` as its license page (`browser/installer/windows/Makefile.in`: `cp $(topsrcdir)/browser/EULA.rtf $(CONFIG_DIR)/license.rtf`; `installer.nsi`: `!insertmacro MUI_PAGE_LICENSE license.rtf`). Its text is the same as `browser/EULA`, "MOZILLA FIREFOX END-USER SOFTWARE LICENSE AGREEMENT Version 2.0". What it says about copying:
  - "1. LICENSE GRANT. The Mozilla Corporation grants you a non-exclusive license to use the executable code version of the Product." There is no grant to copy or redistribute.
  - "3. PROPRIETARY RIGHTS. Portions of the Product are available in source code form under the terms of the Mozilla Public License and other open source licenses ... Nothing in this Agreement will be construed to limit any rights granted under the Open Source Licenses. Subject to the foregoing, Mozilla ... hereby reserves all intellectual property rights in the Product, except for the rights expressly granted in this Agreement. You may not remove or alter any trademark, logo, copyright or other proprietary notice in or on the Product. This license does not grant you any right to use the trademarks, service marks or logos of Mozilla or its licensors."
  - 9(g): "You may assign your rights under this Agreement to any party that consents to, and agrees to be bound by, its terms".
- The code inside is MPL 1.1 / GPL 2.0+ / LGPL 2.1+ (the build ships the MPL 1.1 as `LICENSE`; source files carry the tri-license block). Those licenses would let us redistribute the code, but not the Firefox branding: `other-licenses/branding/firefox/LICENSE` says "You are not granted rights or licenses to the trademarks of the Mozilla Foundation or any party, including without limitation the Firefox name or logo."
- Mozilla Trademark Guidelines (https://www.mozilla.org/en-US/foundation/trademarks/policy/, opened 2026-09-29): "Software Distribution Guidelines: Our distribution policy contains additional guidelines that apply to distribution of the Firefox Browser and other Mozilla software." Also allowed without permission: "Use Mozilla wordmarks in text to truthfully refer to and/or link to unmodified Mozilla programs, products, services and technologies."
- Distribution Policy for Mozilla Software (https://www.mozilla.org/en-US/foundation/trademarks/distribution-policy/, opened 2026-09-29):
  - "If you wish to distribute Firefox and other Mozilla software branded with our trademarks, you must comply with the relevant software licenses, the Mozilla Trademark Guidelines and either the Unaltered Software Distribution Policy or the terms of a written distribution agreement with Mozilla."
  - "Unaltered Software Distribution Policy: You may distribute unaltered copies of Mozilla Firefox and other Mozilla software from Mozilla.org without express permission from Mozilla as long as you comply with the following rules: You may not charge for the software. ... You may not collect personal information in the context of your distribution of the software. You may not add to, remove, or change any part of the software, including the Mozilla trademarks themselves. ... You may not modify the installation process of the software or use it to install any other themes, plugins, extensions, or software."
  - "We suggest that if you want to distribute Mozilla software, you do so by linking to official downloads linked from Mozilla.org to help ensure safe, reliable downloads. For example, if you wish to directly distribute copies of Firefox yourself, you must distribute the latest stable version available at www.firefox.com."
  - "When distributing you must distribute the most recent version of Firefox and other Mozilla software."
  - "Modified Versions Require Prior Written Permission ... if you make any changes to Firefox or other Mozilla software, you may not redistribute that product using any Mozilla trademark without Mozilla's prior written consent".
- Conclusion: we must not host `Firefox Setup 2.0.0.20.exe`. Leaving it unmodified is not enough, because the policy also requires the most recent version, and 2.0.0.20 is not. The EULA itself grants only use. Rebuilding from source without the branding (like "Bon Echo", the unbranded name in `browser/branding/unofficial`) would be MPL-legal, but it is a different package and would need its own verification.
- `external` fits: the file stays on Mozilla's server and Beacon only links to the official download, which is what the policy suggests. The catalog uses the name only "in text to truthfully refer to ... unmodified Mozilla programs". Whether Mozilla would accept a link to an outdated version was not asked; if we want certainty, ask trademark-permissions@mozilla.com.
- LICENSE.TXT here (39,982 bytes, SHA-256 25cdbf631321196af547a9a5e6eaa737127f790090485cfb407872faca383d2b) contains the EULA 2.0 text (browser/EULA), the MPL 1.1 as shipped in the build, and the branding notice. The GPL and LGPL texts are not in the build or the tarball root and are not included.

## Matching source (kept for reference, not to be hosted with an external package)

- URL: https://archive.mozilla.org/pub/firefox/releases/2.0.0.20/source/firefox-2.0.0.20-source.tar.bz2
- File: src\firefox-2.0.0.20-source.tar.bz2, 40,293,412 bytes, 45,395 entries
- SHA-256: cc8ac993a38d005d08a325ccaf1255648c38da2c3b7043b277909d1430424494
- SHA-1 16601fdbbb0a83b85fd053e76350f7da397f525e (SHA1SUMS: MATCH), MD5 f3718fefd01c8edc007ec0b416a8a7b8 (MD5SUMS: MATCH)
- GPG: good signature from the same Mozilla Software Releases key (expired key).
- browser/config/version.txt in the tarball says 2.0.0.20.
- Parts of the build that are not in this source archive:
  - Talkback crash reporter (optional/extensions/talkback@mozilla.org: talkback.exe, fullsoft.dll, qfaservices.dll, BrandRes.dll). It is closed-source (SupportSoft); the tarball has only its packaging scripts (talkback.jst).
  - The 7-Zip self-extractor stub `other-licenses/7zstub/firefox/7zSD.sfx` is only in binary form.
  - The NSIS plugin DLLs are only in binary form (toolkit/mozapps/installer/windows/nsis/*.dll), as is the NSIS stub of setup.exe.

## Security

Sources: Mozilla's known-vulnerabilities pages for Firefox 2.0, SeaMonkey 1.1 and Thunderbird 2.0 (https://www.mozilla.org/en-US/security/known-vulnerabilities/firefox-2.0/ etc.), the individual MFSA pages, and the NVD API 2.0.

- 2.0.0.20 itself fixed only MFSA 2008-65 (CVE-2008-5507, cross-domain data theft, Windows only).
- Mozilla made no Firefox 2 release after that, but kept fixing the same Gecko 1.8.1 engine in SeaMonkey 1.1.15 to 1.1.19 and Thunderbird 2.0.0.21 to 2.0.0.24 (2009-2010). Those fixes show which bugs Mozilla confirmed on the Firefox 2 code base. Leaving out the two that are mail-only (MFSA 2009-33, 2010-06), **18 advisories covering 31 CVEs** apply to the browser engine and are unfixed in Firefox 2.0.0.20. 12 of them are rated critical:
  - MFSA 2009-43 / CVE-2009-2404: heap overflow in NSS certificate regexp parsing (CVSS2 9.3). Can be triggered by a malicious server certificate.
  - MFSA 2009-42 / CVE-2009-2408: null-prefix certificate names let a man in the middle impersonate SSL sites (CVSS2 6.8).
  - MFSA 2009-12 / CVE-2009-1169: XSLT code execution (CVSS2 9.3).
  - MFSA 2009-29 / CVE-2009-1838 and MFSA 2009-32 / CVE-2009-1841: code execution and chrome privilege escalation via JavaScript (CVSS2 9.3).
  - MFSA 2009-07 / CVE-2009-0771 to -0774: memory corruption crashes (CVE-2009-0771 CVSS2 10.0).
  - MFSA 2009-10 / CVE-2009-0040: libpng memory safety.
  - Also critical: MFSA 2009-01, 2009-14, 2009-24, 2010-07 (memory corruption).
  - Also rated high or lower: 2009-27 (SSL tampering via proxy CONNECT), 2009-17, 2009-09, 2009-26, 2009-05, 2009-15, 2009-21.
- This is a lower bound. Every Firefox advisory after 2010 was never checked against the 1.8.1 branch. NVD's CPE match for cpe:2.3:a:mozilla:firefox:2.0.0.20 returns 2,725 CVEs, but that comes from "before version X" ranges and includes features Firefox 2 does not have (WebGL, workers and so on). Use it only as "very many".
- Encryption: the build uses NSS 3.11.9 (security/nss/lib/nss/nss.h), whose highest protocol is TLS 1.0 (sslproto.h defines SSL 2, SSL 3.0 and SSL_LIBRARY_VERSION_3_1_TLS only). Nearly all current HTTPS sites will refuse it.

## Install behaviour

- Installer type: Mozilla installer. It is a 7-Zip SFX (7zSD, app.tag: `RunProgram="setup.exe"`, title "Mozilla Firefox") that unpacks `setup.exe` (NSIS), `nonlocalized\`, `localized\` and `optional\` to a temp folder and runs setup.exe. Listed with host 7-Zip; setup.exe was unpacked the same way to see its plugins. Nothing was executed.
- Silent install: installer.nsi `.onInit` accepts `-ms` ("Support for the deprecated -ms command line argument ... SetSilent silent") and `/INI=<full path of an ini>` (keys InstallDirectoryName, InstallDirectoryPath, QuickLaunchShortcut, DesktopShortcut, StartMenuShortcuts, StartMenuDirectoryName, CloseAppNoPrompt). NSIS's own `/S` should also work if 7zSD passes it on, but that is not verified. Recommended: `Install: exe -ms` (the same switch the catalog uses for RetroZilla).
- Default folder: `$PROGRAMFILES\Mozilla Firefox` (InstallDir "$PROGRAMFILES\${BrandFullName}\", official branding.nsi: BrandFullName "Mozilla Firefox"). If the same version is already registered, it installs to that InstallLocation instead.
- Uninstaller: yes. shared.nsh SetUninstallKeys writes HKLM `Software\Microsoft\Windows\CurrentVersion\Uninstall\Mozilla Firefox (2.0.0.20)` with DisplayName "Mozilla Firefox (2.0.0.20)", DisplayVersion "2.0.0.20 (en-US)", Publisher "Mozilla", UninstallString `$INSTDIR\uninstall\helper.exe`, NoModify, NoRepair. `helper.exe /S` uninstalls silently (uninstaller.nsi). The display name comes from the source plus the official branding.nsi; it was not read from the compiled binary.
- Side effects: creates Start Menu shortcuts ("Mozilla Firefox" and "Mozilla Firefox (Safe Mode)"), desktop and Quick Launch shortcuts by default, registers under HKLM `Software\Clients\StartMenuInternet\firefox.exe` (shared.nsh SetStartMenuInternet) and `Software\Mozilla\Mozilla Firefox`. Talkback and DOM Inspector are optional components. Branding.nsi has a "Percentage of new "Standard" installs to enable talkback for", so a standard install enables Talkback only on some machines; on the others it is installed but disabled (installer.nsi writes an InstallDisabled file). What -ms does with them was not traced.

## Verification notes

- Verified by opening or downloading: the release directory listings, SHA1SUMS, MD5SUMS, KEY and .asc signatures (gpg), the 2.0.0.20 release notes, the Firefox 2 system requirements (Internet Archive capture, because Mozilla's own URL is gone), the Firefox 3.0 system requirements, the Mozilla Trademark Guidelines and Distribution Policy, Mozilla known-vulnerabilities pages and 18 MFSA pages, the NVD API, the installer contents (7-Zip listing and extraction, not executed), and the source tarball (EULA, EULA.rtf, installer NSIS scripts, branding, NSS headers).
- Not verified: running on Windows 98/ME or 95 (no VM interaction); whether `/S` passes through 7zSD; the Add/Remove name in the compiled binary; whether Talkback is installed under -ms; whether Mozilla would object to a catalog linking to an outdated build.
