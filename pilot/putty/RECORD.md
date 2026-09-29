# PuTTY 0.67 (fallback 0.65) - Beacon 98 pilot record

- Date checked: 2026-09-28
- Package: PuTTY (Simon Tatham et al.), including PuTTY, PSCP, PSFTP, Plink, Pageant and PuTTYgen
- Version: 0.67 (2016-03-05). This is the last release whose documentation says Windows 95 and later are supported.
- Fallback: 0.65 (2015-07-25), stored in `alt-0.65\`. See "Caveat" below.
- License: MIT-style (PuTTY licence)
- Current upstream release per the release pages: 0.84

## Windows 9x support evidence

- PuTTY 0.67 FAQ, question A.3.1 "What ports of PuTTY exist?" (https://the.earth.li/~sgtatham/putty/0.67/htmldoc/AppendixA.html, opened):
  "Currently, release versions of PuTTY tools only run on full Win32 systems and Unix. 'Win32' includes versions of Windows from Windows 95 onwards (as opposed to the 16-bit Windows 3.1; see question A.3.5), up to and including Windows 7".
- PuTTY 0.68 FAQ (https://the.earth.li/~sgtatham/putty/0.68/htmldoc/AppendixA.html, opened):
  "As of 0.68, the supplied PuTTY executables run on versions of Windows from XP onwards".
  So 0.67 is the last release documented to support 95/98/ME. I checked the FAQ for every version from 0.60 to 0.78: the "Windows 95 onwards" wording appears up to 0.67 and is replaced in 0.68.
- Changelog (https://www.chiark.greenend.org.uk/~sgtatham/putty/changes.html). chiark.greenend.org.uk refused connections from this host, so I read a web.archive.org copy. The 0.68 entry says "The Windows PuTTY tools now come in a 64-bit version" and "Windows's ASLR and DEP security features turned on". 0.67 adds Authenticode signing and a restrictive process ACL. 0.66 adds "better Unicode handling in Windows PuTTY keyboard messages".
- Windows 95: covered by the FAQ above. FAQ A.7.4 (0.67): "Plink on Windows 95 says it can't find WS2_32.DLL ... installed as standard on Windows 98 and above ... but early Win95 installations don't have it", so early Win95 needs the WinSock 2 update. The 0.67 installer script (windows/putty.iss) uses `MinVersion`/`OnlyBelowVersion: 4.1` to choose .chm or .hlp help, which shows 9x was still expected.

### Caveat: 0.66 and 0.67 putty.exe may not open a window on stock Win98 (my inference from the code, not tested)

- In the 0.66 and 0.67 source (windows/window.c), putty.exe registers its main window with `RegisterClassW` and creates it with `CreateWindowExW`, with no ANSI fallback. 0.65 still uses `RegisterClass`/`CreateWindowEx` (ANSI).
- The import tables agree: 0.66 and 0.67 putty.exe import USER32 CreateWindowExW, RegisterClassW, PeekMessageW, DispatchMessageW and DefWindowProcW. 0.63 to 0.65 do not.
- Windows 9x does not implement these W functions natively; they need the Microsoft Layer for Unicode (unicows). This is general platform knowledge, not a PuTTY statement.
- The console tools (pscp, psftp, plink) do not create this window, so the concern mainly affects putty.exe (and possibly the other GUI tools).
- All 0.63 to 0.67 x86 exes are linked with MSVC 7.10 and subsystem 4.0, so the Windows loader should accept them.
- Recommendation: install 0.67 in the Win98 VM first. If putty.exe fails to open a window, ship 0.65 (in alt-0.65\). 0.65 has 2 more known vulnerabilities: vuln-ech-overflow (CVE-2015-5309, terminal memory corruption) and vuln-pscp-sink-sscanf (CVE-2016-2563).

## Download (primary: 0.67)

- Release page: https://www.chiark.greenend.org.uk/~sgtatham/putty/releases/0.67.html (read via web.archive.org, since chiark was unreachable). Files come from the official mirror the.earth.li.
- URL: https://the.earth.li/~sgtatham/putty/0.67/x86/putty-0.67-installer.exe
  - File: putty-0.67-installer.exe, 1,798,184 bytes
  - SHA-256: e4468784f831d2ef713e95f1299d4f60452c4346c3f89e541be252d68d18b38d
  - MD5: 74c61337de0e37e7bc24063783ee1b25
  - The release page lists it as a "Legacy .EXE installer, created with Inno Setup" and warns: "The .exe format installer for this release was built with a version of Inno Setup that had a DLL hijacking vulnerability. If you need to run this file, copy it into an empty directory first".
- URL: https://the.earth.li/~sgtatham/putty/0.67/x86/putty.zip (alternative, no installer)
  - File: putty.zip, 1,547,346 bytes. Contains PAGEANT, PLINK, PSCP, PSFTP, PUTTY, PUTTYGEN .EXE plus PUTTY.CHM/.HLP/.CNT.
  - SHA-256: 670e8146ecc065a34442487508b5111229206a953b465fbe20a745d7971043e5
  - MD5: bf9a1aebb8601fb38a23c474d90d0f4a
- Not usable: putty-0.67-installer.msi. It needs Windows Installer, which stock 95/98 do not have.
- Published checksums: sha256sums, md5sums and their .gpg clearsigned versions, downloaded from https://the.earth.li/~sgtatham/putty/0.67/ and stored here.
  - installer SHA-256 MATCH, MD5 MATCH; putty.zip SHA-256 MATCH, MD5 MATCH.
  - GPG: both sha256sums.gpg and md5sums.gpg give "Good signature from PuTTY Releases <putty@projects.tartarus.org>", key 9DFE2648B43434E4, primary fingerprint 0054 DDAA 8ADA 15D2 768A 6DE7 9DFE 2648 B434 34E4 (RSA-2048, created 2015-08-31, expired 2018-08-30; signature made 2016-03-09). The signed text contains the same hashes for both files.
  - Key source caveat: release-2015.asc and master-2015.asc came from the web.archive.org copy of https://www.chiark.greenend.org.uk/~sgtatham/putty/keys/, because chiark was unreachable. The master key is AB585DC604676F7C (fingerprint 440D E3B5 B7A1 CA85 B3CC 1718 AB58 5DC6 0467 6F7C). The fingerprints were not cross-checked against a second independent source.
  - Authenticode on putty-0.67-installer.exe: Valid, signer "CN=Simon Tatham, O=Simon Tatham, L=Cambridge".

## Download (fallback: 0.65, in alt-0.65\)

- https://the.earth.li/~sgtatham/putty/0.65/x86/putty-0.65-installer.exe: 1,937,883 bytes, SHA-256 0f63734e0b7f64c43837c908abdf691083d8fff044d0c82953fb1a98f3e6d30a. Matches the published sha256sums.
- https://the.earth.li/~sgtatham/putty/0.65/x86/putty.zip: 1,699,231 bytes, SHA-256 83450ac9e54e0e949a8c81996a6113d1ddecf9831f07b9a4857ef05b8753dea7. Matches the published sha256sums.
- sha256sums.RSA and md5sums.RSA (old-style detached signatures) were downloaded but NOT verified, because the pre-2015 release key was not fetched.
- LICENSE.TXT in alt-0.65\ is the LICENCE file from putty-0.65.tar.gz.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\pilot\putty -DisableRemediation` and the same for `...\putty\alt-0.65` on 2026-09-28
(engine 1.1.26080.3, signatures 1.459.442.0): "found no threats" (both).

## License

- The PuTTY licence is MIT-style. LICENSE.TXT is the LICENCE file from the official putty-0.67.tar.gz (https://the.earth.li/~sgtatham/putty/0.67/putty-0.67.tar.gz; published SHA-256 80192458e8a46229de512afeca5c757dd8fce09606b3c992fbaeeee29b994a47; used from a temp copy, not stored here).
- Redistributing the unmodified binary is allowed ("to use, copy, modify, merge, publish, distribute, sublicense, and/or sell"). The only condition: "The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software."
- There is no source-hosting obligation. The source is available at the URL above and as putty-src.zip.

## Security

Source: the PuTTY 0.67 release page "known vulnerabilities" list (web.archive.org copy of chiark, page last modified 2026-05-22), each wishlist page (for the CVE IDs), and NVD (cpeName putty:0.67 gives 13 matches).

The PuTTY page lists 21 known vulnerabilities in 0.67:
- vuln-agent-fwd-overflow: CVE-2017-6542, agent-forwarding integer overflow, memory overwrite (fixed 0.68).
- vuln-indirect-dll-hijack: CVE-2016-6167, DLL hijacking (fixed 0.68). -2 and -3 have no CVE listed (fixed 0.69 and 0.70).
- vuln-rsa-kex-integer-overflow: CVE-2019-9894, memory overwrite before host key verification (fixed 0.71).
- vuln-fd-set-overflow: CVE-2019-9895 (Unix only).
- vuln-chm-hijack: CVE-2019-9896, malicious help file in the exe directory (fixed 0.71).
- vuln-terminal-dos-combining-chars, -double-width-gtk (GTK only), -one-column-cjk: CVE-2019-9897, terminal DoS (fixed 0.71).
- vuln-rng-reuse: CVE-2019-9898 (fixed 0.71).
- vuln-auth-prompt-spoofing: CVE-2021-36367 (fixed 0.71).
- vuln-ssh1-buffer-length-underflow and vuln-ssh1-short-rsa-keys: SSH-1 only, no CVE on the pages (fixed 0.72). NVD separately lists CVE-2019-17069 (SSH-1 disconnect use-after-free, before 0.73).
- vuln-win-pageant-client-missing-length-check: no CVE (fixed 0.72).
- vuln-win-exclusiveaddruse: CVE-2019-17067, forwarded ports can be rebound (fixed 0.73). NVD also lists CVE-2019-17068 (bracketed paste, before 0.73).
- vuln-agent-keylist-used-after-free: no CVE (fixed 0.74).
- vuln-windows-remote-title-dos: CVE-2021-33500 (fixed 0.75).
- vuln-terrapin: CVE-2023-48795 (fixed 0.80).
- ecdsa-remotely-triggerable-assertion and telnet-trust-sigil (fixed 0.84). Their own wishlist pages say "present-in: 0.71" and "0.77", so the 0.67 listing may be conservative; I did not resolve this.

Worst: CVE-2019-17067 (NVD CVSS 9.8) and CVE-2019-9894 / CVE-2017-6542 (remote memory overwrite).
Not applicable: CVE-2024-31497 (P-521 nonce bias) needs ECDSA keys, which 0.67 does not support. It is not on the 0.67 list.

## Install behaviour

- Installer type: Inno Setup 5.4.2. The header "Inno Setup Setup Data (5.4.2)" is in the exe; this is the ANSI build (no "(u)" suffix). Script: windows/putty.iss in the source.
- Silent install: standard Inno switches `/SILENT` or `/VERYSILENT`, `/SUPPRESSMSGBOXES`, `/DIR="x:\path"`, `/NORESTART`. PuTTY does not document them for 0.67; untested.
- Default folder: `{pf}\PuTTY`; Start Menu group "PuTTY".
- Uninstaller: yes, the standard Inno uninstaller (unins000.exe), registered in Add/Remove Programs. On uninstall it runs `putty.exe -cleanup-during-uninstall` to optionally remove saved sessions and the random seed. `ChangesAssociations=yes` (.ppk association with PuTTYgen/Pageant).
- Zip alternative: unpack putty.zip into a folder and create a Start Menu shortcut to PUTTY.EXE. It writes no registry entries until first use (sessions go to HKCU\Software\SimonTatham).
- Inno Setup 9x compatibility of 5.4.2 ANSI is from general knowledge; not verified here.

## Verification notes

- Verified by opening: FAQs 0.60-0.78 on the.earth.li, the changelog and release pages (archive.org copies), sha256sums/md5sums with GPG verification, source files window.c and putty.iss for 0.65/0.66/0.67, PE import tables, the Authenticode signature, and NVD.
- Not verified: actual behaviour on Win95/98 (no VM interaction), the 0.65 RSA signatures, key fingerprints against a second source, and Inno Setup 5.4.2 on 9x.
