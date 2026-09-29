# Bochs 2.3.7 - Beacon 98 package record

- Date checked: 2026-09-29
- Package: Bochs, x86 PC emulator (The Bochs Project; copyright MandrakeSoft S.A. and contributors)
- Version: 2.3.7 (2008-06-03), Windows installer Bochs-2.3.7.exe
- License: LGPL-2.0-or-later (source headers say "version 2 of the License, or (at your option) any later version"; COPYING is the LGPL 2.1 text). Bundled ROMs: Bochs BIOS (LGPL, source in the Bochs tarball), LGPL VGABIOS 0.6b, Elpin VGA BIOS (freeware, "use/distribute with bochs"). Optional DLX Linux demo disk image (GPL software, no source offered).
- Recommendation: **2.3.7 as `external`** from SourceForge (see License for why not hosted). 2.3.7 is the last version that can load on stock Windows 98: the 2.4 and 2.4.6 executables are marked as needing Windows 2000.
- Correction to batch2.md: it says 2.5 needs KernelEx. The 2.4 binaries already need Windows 2000, so KernelEx is needed from 2.4 onwards, not only from 2.5.

## Windows 9x support evidence

There is no explicit written statement by the Bochs project about Windows 98 as a *host* for 2.3.7 or 2.4 (CHANGES and README only talk about 98 as a guest). The evidence comes from the official binaries, which I parsed on the host without running them:
- Bochs-2.3.7.exe (unpacked with host 7-Zip into a temp folder): bochs.exe, bochsdbg.exe, bximage.exe, bxcommit.exe and niclist.exe all have PE subsystem version **4.0**. bochs.exe imports ADVAPI32, COMCTL32, comdlg32, GDI32, KERNEL32, SHELL32, USER32, WINMM, WSOCK32 (no MSVCRT, so the C runtime is static). Nothing Windows 2000-only was found; the Unicode functions it imports (GetStringTypeW, LCMapStringW, CompareStringW...) are the usual static CRT imports that exist as stubs on 9x.
- Bochs-2.4.exe and Bochs-2.4.6.exe (downloaded to a temp folder only, SF MD5s 60ed0e076afc77fd9c5a6374c0edde12 and 1ec80e25ed35d946e819925a9e05470a matched): bochs.exe has PE OS/subsystem version **5.0**, which Windows 95/98/ME refuse to load ("requires a newer version of Windows"). It also imports InitializeCriticalSectionAndSpinCount and GetModuleHandleW. So 2.4.x needs KernelEx at least; whether it then works was not verified, and no KernelEx version or mode is named anywhere I found.
- docs/user/supported-platforms.html in 2.3.7: "Win32 ... You can compile with Microsoft Visual C++ 5.0 or 6.0 ... or Cygwin" (no OS list).
- Windows 95: unknown (not stated; COMCTL32 and WinSock needs not checked). ME: same as 98 by the binary evidence.
- Not verified: running on 98/ME.

## Download

- Official: SourceForge project "bochs", folder bochs/2.3.7 (file list via the SourceForge RSS, opened with WebFetch)
- URL: https://downloads.sourceforge.net/project/bochs/bochs/2.3.7/Bochs-2.3.7.exe
- File: Bochs-2.3.7.exe, 3,358,844 bytes
- SHA-256: 4854dffb9de6492e98bad7d4fbfb2e302668d51df111650edc25a95d3f19173b
- MD5: 433b63126c70a059d2cfd6bd6326329d. SourceForge RSS lists 433b63126c70a059d2cfd6bd6326329d: MATCH (SourceForge-generated).
- Plain HTTP: `curl.exe -sS -I --http1.0 -L http://downloads.sourceforge.net/project/bochs/bochs/2.3.7/Bochs-2.3.7.exe` gives 302 to `http://master.dl.sourceforge.net/...`, then 200 OK, Content-Length 3358844.
- Other files in the folder: bochs-p4-2.3.7-win32.zip and bochs-p4-smp-2.3.7-win32.zip are add-on executables only (checked: COPYING.txt, README.txt, bochs-p4.exe), not standalone packages; bochs-2.3.7.win32msvc-src.zip (MSVC source variant).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\bochs -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- docs/user/license.html (2.3.7): "Bochs is copyrighted by MandrakeSoft S.A. and distributed under the GNU Lesser General Public License" with the LGPL "version 2 ... or (at your option) any later version" header. COPYING.txt in the installer is the LGPL 2.1 text. So LGPL-2.0-or-later (batch2.md's "LGPL-2.1+" is close but the headers say 2 or later).
- LICENSE.TXT here: the Bochs notice, COPYING.txt, VGABIOS-elpin-LICENSE.txt and the vgabios-0.6b COPYING (LGPL 2.1).

### ROM images and disk images in the installer (listed after unpacking with 7-Zip)

| File | What | License / status |
|---|---|---|
| BIOS-bochs-latest, BIOS-bochs-legacy | Bochs ROM BIOS | Bochs's own, LGPL; source bios/rombios.c, rombios32.c in bochs-2.3.7.tar.gz. Fine. |
| VGABIOS-lgpl-latest, -cirrus, -debug, -cirrus-debug + VGABIOS-lgpl-README.txt | Plex86/Bochs LGPL VGABIOS | LGPL. README history: "vgabios-0.6b : May 30 2008". The ROM carries `vgabios.c,v 1.67 2008/01/27` and `vbe.c,v 1.60 2008/03/02`, identical to the revisions in vgabios-0.6b.tgz. The ROM bytes differ from the prebuilt .bin in that tarball (separate build). Its source is not in the Bochs tarball, so it is kept in src\. Fine. |
| VGABIOS-elpin-2.40 + VGABIOS-elpin-LICENSE.txt | Elpin Systems VGA BIOS (proprietary) | "permanently licensed for use with bochs ... You may freely use/distribute it with bochs, as long as it is used in bochs for the intended use as a VGA BIOS." Redistribution with Bochs is allowed, but it is not open source and the grant is limited to use in Bochs. **Questionable for a hosted package**; acceptable if the installer is distributed unchanged. |
| dlxlinux\hd10meg.img (10.4 MB), bochsrc.bxrc, run.bat, readme.txt | DLX Linux demo disk | Contains Linux kernel 1.3.89 ("1.3.89 (root@merlin) #1 Mon Apr 15 ... 1996"), libc 4.7.5 and other tools by Erich and Hannes Boehm. GPL/LGPL software **with no source and no written offer** in the Bochs release. Installed only with the "Full (with DLX Linux demo)" install type, but it is inside the installer file either way. **Questionable for hosting.** |

No commercial BIOS (e.g. Award/AMI/Phoenix) and no Microsoft or other proprietary OS images are included.

### Conclusion

Hosting Bochs-2.3.7.exe would make Backport Labs the distributor of the DLX Linux image (GPL without obtainable complete source) and of the Elpin BIOS under a Bochs-only grant. Following the VLC precedent, the draft lists Bochs as `external`. If Backport Labs prefers hosting, it would need at least the Linux 1.3.89 and libc 4.7.5 sources and the other DLX tools' sources (not collected, and the DLX site is gone), which is not practical.

## Matching source (kept for reference; not offered for an external package)

- Bochs: https://downloads.sourceforge.net/project/bochs/bochs/2.3.7/bochs-2.3.7.tar.gz
  - src\bochs-2.3.7.tar.gz, 3,989,982 bytes, SHA-256 77f27fedadc6431df0a06ee226259a80443524ae9d221c97c5986e3f7927bb04
  - MD5 a2e5f922505bf16cabd36bb9d571a2c4, SF RSS: MATCH.
  - Contains the ROM BIOS source and the NSIS script (build/win32/nsis/bochs.nsi.in); the LGPL VGABIOS and Elpin ROMs only as binaries.
- LGPL VGABIOS 0.6b: https://download.savannah.gnu.org/releases/vgabios/vgabios-0.6b.tgz (served by the mirror mirror.marwan.ma)
  - src\vgabios-0.6b.tgz, 1,447,490 bytes, SHA-256 abd93867a2267975736c019716ee84d6799a9290aab6aef524784fa44942d8b6
  - Savannah publishes vgabios-0.6b.tgz.sig (DSA key D97373B5A9F51196, signed 2008-05-30). The public key could not be obtained (keyserver.ubuntu.com and the Savannah keyring download returned no key), so the signature was **not verified**.

## Security

- NVD keyword search "bochs" (API 2.0, 2026-09-29): 40 results, most unrelated (Linux kernel, QEMU's "bochs" block driver, radare2's bochs_open). Bochs itself:
  - CVE-2004-2372: HOME overflow when setuid, fixed in 2.1.1. Not affected.
  - CVE-2007-2893 (NE2000 heap overflow, guest-to-host, CVSS2 7.2) and CVE-2007-2894 (floppy controller divide-by-zero DoS): NVD lists only version 2.3. CHANGES for 2.3.5 closes "[1729822] Various security issues in io device emulation" (the 2007 report behind these CVEs), so 2.3.7 is very likely fixed (inference, not verified in code).
  - CVE-2018-25220: stack overflow in "Bochs 2.6-5" (a Debian package version) via a long input string. Not 2.3.7.
- Summary: 0 CVEs confirmed for 2.3.7; the 2007 NE2000 issue (CVE-2007-2893) is the worst historical one and is believed fixed. Guests are not isolated strongly (an emulator from 2008); do not run untrusted guest software expecting a sandbox.

## Install behaviour

- Installer: NSIS (7-Zip unpacks it as NSIS; script bochs.nsi.in in the source). Silent: `/S` (standard NSIS; `/D=` for a folder). Install types: "Normal" (first, used by a silent install, **without** DLX Linux) and "Full (with DLX Linux demo)".
- Default folder: `$PROGRAMFILES\Bochs-2.3.7`.
- Registers the .bxrc extension (HKCR "BochsConfigFile" with Configure/Edit/Debugger/Run verbs), Start Menu folder "Bochs 2.3.7", optional desktop icons.
- Add/Remove Programs: HKLM `...\CurrentVersion\Uninstall\Bochs 2.3.7`, DisplayName **"Bochs 2.3.7 (remove only)"** (from the script: `"${NAME} (remove only)"` with NAME = "Bochs ${VERSION}"). Uninstaller: `$INSTDIR\Uninstall.exe` (NSIS, `/S` for silent).
- Installed size (Normal): about 5,000 KB (all files 15,361 KB, of which DLX Linux 10,411 KB).

## Verification notes

- Verified by opening/downloading: SourceForge RSS for 2.3.7, 2.4 and 2.4.6 (WebFetch), the three installers (unpacked with host 7-Zip to temp folders, nothing run), PE headers and imports, CHANGES (GitHub bochs-emu/Bochs master), README, license.html, thirdparty.html, supported-platforms.html, the NSIS script, VGABIOS README and ROM strings, vgabios-0.6b sources, NVD.
- Not verified: running on 95/98/ME; 2.4.x under KernelEx; the vgabios signature; that CVE-2007-2893/2894 are fixed in 2.3.7.
