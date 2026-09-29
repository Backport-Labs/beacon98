# AutoIt v3.2.12.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: AutoIt v3 (Jonathan Bennett and the AutoIt Team)
- Version: 3.2.12.1 (June 12, 2008), the last release before 9x support was removed
- License: AutoIt v3 EULA (freeware, closed source); redistribution allowed with notices and the EULA
- Recommendation: 3.2.12.1. Systems: 95, 98, ME (and NT4, 2000, XP). On 9x, scripts must be run with the ANSI programs (AutoIt3A.exe, Aut2ExeA.exe, Au3InfoA.exe).

## Windows 9x support evidence

- https://www.autoitscript.com/autoit3/docs/history.htm (downloaded 2026-09-29):
  "3.3.0.0 (December 24, 2008) (Release) ... Removed: Windows 9x and Windows NT 4.0 Operating System support has been removed."
  The release immediately before it in the history is "3.2.12.1 (June 12, 2008) (Release)". So 3.2.12.1 is the last 9x release, as batch2.md said. (3.2.13.x betas existed between them but were betas.)
- AutoIt3.chm inside the 3.2.12.1 installer (html/introduction.htm): "Compatible with Windows 95 / 98 / ME / NT4 / 2000 / XP / 2003 / Vista".
- html/intro/unicode.htm: "From version 3.2.4.0 AutoIt is supplied with both Unicode and ANSI compiled versions. ... ANSI versions are supplied for backwards compatibility with Windows 9x systems." and "Note: the Unicode version of AutoIt (AutoIt3.exe) and scripts compiled in Unicode mode will only run on Windows NT/2000/XP/2003/Vista and later machines. To allow scripts to run on Windows 9x scripts must be compiled using the ANSI compiler (Aut2ExeA.exe)."
- Static check (extracted to a temp folder with 7-Zip, not run): AutoIt3A.exe, Au3InfoA.exe, Aut2exeA.exe are PE32 with OS/subsystem version 4.0.
- Whether the installer makes .au3 files open with AutoIt3A.exe on 9x is unknown (the NSIS script cannot be extracted). Needs a VM check. No KernelEx needed.

## Download

- Official archive: https://www.autoitscript.com/autoit3/files/archive/autoit/ (lists autoit-v3.2.12.1-setup.exe 6.8M and autoit-v3.2.12.1-sfx.exe 6.8M)
- URL: https://www.autoitscript.com/autoit3/files/archive/autoit/autoit-v3.2.12.1-setup.exe
- File: autoit-v3.2.12.1-setup.exe, 7,170,440 bytes
- SHA-256: a3efcf49b90d96b23cd30b2d4cb57cd47268fd46839e5a167b45fe0e3a153f93
- MD5: d37652c3d574f7348e7ff1b0d7764b0c
- Published checksum: none published for archive files. Authenticode: **Valid**, signed by "E=support@autoitscript.com, CN=Jonathan Bennett, C=GB" (checked with Get-AuthenticodeSignature on the host). Version resource: FileVersion 3.2.12.1, "AutoIt v3 Setup", "AutoIt Team".
- Alternative (not downloaded): autoit-v3.2.12.1-sfx.exe, a self-extracting archive without installer.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\autoit -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats" (covers the installer and src\). Note: other antivirus products often flag AutoIt itself and the bundled Exe2Aut decompiler heuristically.

## License

AutoIt EULA of this version (html/license.htm in AutoIt3.chm from the installer), redistribution clause verbatim:

> Reproduction and Distribution. You may reproduce and distribute an
> unlimited number of copies of the SOFTWARE PRODUCT either in whole or
> in part; each copy should include all copyright and trademark notices,
> and shall be accompanied by a copy of this EULA. Copies of the
> SOFTWARE PRODUCT may be distributed as a standalone product or included
> with your own product.

- Conditions: keep all copyright/trademark notices (met by hosting the unmodified signed installer) and include the EULA (LICENSE.TXT part 1; the EULA is also inside the installer's help file). No fee restriction.
- AutoIt itself is closed source; no source obligation for AutoIt.
- Third-party files in the installer:
  - **UPX 3.01** (Aut2Exe\upx.exe, version resource "3.01 (2007-07-31)"): GPL-2.0-or-later with UPX's special exception for compressed programs. Distributing upx.exe obliges us to offer its source. Hosted in src\:
    - upx-3.01-src.tar.bz2, 728,384 bytes, SHA-256 dfc05143d37277ef2c937fa7e1bbeda54bf8b54b923589716ac6338dda6f7f64, MD5 58f3c87bf7e067ece5f7c510d4423cb8. URL: https://upx.sourceforge.net/download/upx-3.01-src.tar.bz2 (the SourceForge files mirror returned 404; this is the project's own download area). No published checksum found.
    - UPX's README.SRC says the build needs UCL and the LZMA SDK 4.43, which are not in the UPX archive, so both are hosted too:
      - ucl-1.03.tar.gz, 534,881 bytes, SHA-256 b865299ffd45d73412293369c9754b07637680e5c826915f097577cd27350348, MD5 852bd691d8abc75b52053465846fba34. URL: https://www.oberhumer.com/opensource/ucl/download/ucl-1.03.tar.gz (GPL).
      - lzma443.tar.bz2, 178,493 bytes, SHA-256 ba85f63243f1f530882cadae401e6f42f624ebb07829e467ea6177e303fa64b2, MD5 c4e1b467184c7cffd4371c74df2baf0f. URL: https://downloads.sourceforge.net/project/sevenzip/LZMA%20SDK/4.43/lzma443.tar.bz2 (official 7-Zip project).
    - Whether upx.exe 3.01 was built with exactly UCL 1.03 is taken from README.SRC's example; not proven.
  - **SciTE 1.76** (lite, SciTE\SciTE.exe): Scintilla/SciTE license (permissive; requires the copyright and permission notice in supporting documentation). The installer ships no copy of it, so LICENSE.TXT part 3 adds it (current text from scintilla.org, same terms).
  - **psapi.dll** 4.00 (Microsoft, "Microsoft redistributable file" per installdir.htm; used only on NT4). Microsoft's redistribution terms were not checked; it ships inside AutoIt's own installer, which AutoIt distributes publicly.
  - **sqlite3.exe** (Extras\SQLite): SQLite is public domain.
- LICENSE.TXT: part 1 AutoIt EULA, part 2 UPX LICENSE + COPYING, part 3 SciTE license.

## Security

- NVD keyword "autoit" (2026-09-29): 2 results, neither about AutoIt itself (CVE-2017-6714 is a Cisco "AutoIT service"; CVE-2023-20212 is ClamAV's AutoIt parser). 0 known problems in AutoIt 3.2.12.1.
- The bundled upx.exe 3.01: NVD ranges of about 16 UPX CVEs include all versions before 3.96/4.0.0 (e.g. CVE-2021-43311 to -43317, heap overflows, CVSS 7.5; CVE-2019-20805). They concern unpacking crafted (mostly Linux ELF/Mach-O) files; Aut2Exe only runs UPX on the user's own compiled scripts, so the practical risk is low. Not given a Warning in the draft; the maintainer may add one.

## Install behaviour

- Installer: NSIS 2 (7-Zip reports "Type = Nsis, SubType = NSIS-2"). Silent install: standard NSIS `/S` (not documented by AutoIt for this version; with /S the NSIS defaults apply). The installer has custom pages (default action for .au3: run or edit; previous-version handling; x64 options) whose silent defaults are unknown.
- Default folder: `\Program Files\AutoIt3` (html/intro/installdir.htm: "usually located in \Program Files\AutoIt3"); registry HKLM\SOFTWARE\AutoIt v3\AutoIt InstallDir. Start Menu shortcuts. Also writes the ShellNew template ($WINDIR\ShellNew\Template.au3) and .au3 file type.
- Uninstaller: Uninstall.exe in the install folder (installdir.htm). **Add/Remove Programs display name: unknown** (the NSIS script is not recoverable with current 7-Zip; no documentation found). Must be checked in the VM before the entry's Uninstall line is final.
- Installed size: about 20.5 MB (21,024,688 bytes unpacked, including SciTE, examples, x64 files).

## Verification notes

- Opened/downloaded: archive listing, history.htm, the installer (extracted with host 7-Zip 26.03 to a temp folder: AutoIt3.chm license/intro pages, installdir.htm, version resources, PE headers), UPX 3.01 source README.SRC/LICENSE, UCL and LZMA SDK archives, scintilla.org License.txt, NVD. Nothing was installed or run.
- Unresolved: Add/Remove name; silent-install defaults of custom pages; whether .au3 is associated with AutoIt3A.exe on 9x; Microsoft terms for psapi.dll.
