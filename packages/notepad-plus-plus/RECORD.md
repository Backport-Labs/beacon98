# Notepad++ 5.9.6.2 (ANSI build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: Notepad++ (Don Ho), package id `notepad-plus-plus`
- Version: 5.9.6.2 (2011-11-13), ANSI build from the official zip package
- License: GNU GPL v2 or later (Notepad++); Scintilla license (SciLexer.dll); zlib-style TinyXML notice; bundled third-party plugins (see License)
- Recommendation: **5.9.6.2 ANSI**. Second sensible choice: **6.0 ANSI**, the version the project's SUPPORTED_SYSTEM.md names. Both are compared below.
  - 5.9.6.2 is the last release where every ANSI program file (notepad++.exe, SciLexer.dll, all plugins and the updater) is marked for subsystem 4.0 and imports only functions that Windows 98 has. In 5.9.8 and 6.0, the bundled Plugin Manager (PluginManager.dll) and its updater gpup.exe were rebuilt with Visual C++ 2008 and are marked subsystem 5.0 (Windows 2000).
  - 6.0 is the last release with an ANSI build at all. 6.1 has none. Its notepad++.exe and SciLexer.dll pass the same checks, so the editor itself should run. It adds PCRE regular expressions. Document Map is Unicode-only.
  - Neither version runs on Windows 95: all ANSI notepad++.exe builds from 5.9 to 6.0 import GetLongPathNameA, which KERNEL32 first exports in Windows 98.
  - Neither version needs KernelEx. Only the ANSI build works on stock 9x. The Unicode build, and the installer, which contains only the Unicode build, are not for 9x.
  - **Not resolved:** the Open/Save dialogs may not work on Windows 98 in any 5.8.3-6.0 ANSI build (see "Known functional problem"). This must be tested in the VM before publishing.

## Windows 9x support evidence

Project statements (verified by opening):
- SUPPORTED_SYSTEM.md, current master (downloaded raw from https://raw.githubusercontent.com/notepad-plus-plus/notepad-plus-plus/master/SUPPORTED_SYSTEM.md):
  "| **Windows 95** | v3.9 | No |", "| **Windows 98** | v6.0 | No |", "| **Windows ME** | v6.0 | No |". The column is "last version can be run".
- Notepad++ 5.9.1 release news, 2011-06-01 (Wayback snapshot 20161207125341 of https://notepad-plus-plus.org/news/notepad-5.9.1-release-is-available.html; the live page is 404):
  "Notepad++ binary release will be, in the future versions, generated under VS2010. As a result Notepad++ future releases won't be supported under Windows 98/ME environments, since VS2010 cannot be used to target Win9X."
  This is the source of the community's "5.9.1 is the last" claim (Notepad++ Community topic 15238, PeterJones quoting it). **The binaries show that the switch to VS2010 did not happen up to 6.0.** Every notepad++.exe and SciLexer.dll from 5.9 to 6.0 that I checked has linker version 8.0 (VS2005) and OS/subsystem version 4.0. The source readmeFirst.txt of 5.9.6.2 also says "notepad++.exe: Visual Studio 2005".
- Installer script PowerEditor/installer/nppSetup.nsi at git tags v5.9.1, v5.9.2 and v6 (opened on GitHub), in `.onInit`, for 95, 98 and ME:
  "This version of Notepad++ does not support your OS.$\nPlease download zipped package of version 5.9 and use ANSI version." followed by `Abort`.
  At tag v5.9 the message is "The installer contains only Unicode version of Notepad++, which is not compatible with your Windows 98. Please use ANSI version in zipped package". **So no Installer.exe of 5.9 or later installs on 9x. The zip package's ansi\ folder is the only way.**
- Notepad++ 6 news, 2012-03-26 (Wayback of https://notepad-plus-plus.org/news/notepad-6.0-release.html):
  "Note that Notepad++ Document Map is only available in Unicode release. The source code for ANSI release is not maintained anymore, therefore ANSI binary will be removed in the future releases."
  npp.6.1.bin.zip (downloaded) has only unicode\.
- SourceForge forum thread "Use Notepad++ with Windows 98?" (https://sourceforge.net/p/notepad-plus/discussion/331754/thread/87f6d75c/, opened with WebFetch):
  Tony, 2011-09-13: "I tested the ANSI-version from version 5.9.3. It at least runs on Win98. But when I tried the open/save commands the windows to chose file in doesn't pop up". Don Ho, 2011-09-12: "ANSI version can handle UNICODE file perfectly. It just can not handle the file path containing the UNICODE character."

Binary analysis (my own; I parsed the PE headers and import tables inside the official zip files and ran nothing):

| Version | ansi\notepad++.exe | ansi\SciLexer.dll | ansi plugins + updater |
|---|---|---|---|
| 5.9, 5.9.1, 5.9.2, 5.9.3 | VS2005, subsys 4.0 | VS2005, subsys 4.0 | all subsys 4.0 |
| 5.9.4 - 5.9.6.2 | VS2005, subsys 4.0 | VS2005, subsys 4.0 | all subsys 4.0 |
| 5.9.8 | VS2005, subsys 4.0 | VS2005, subsys 4.0 | PluginManager.dll and updater\gpup.exe: VS2008, **subsys 5.0** |
| 6.0 | VS2005, subsys 4.0 | VS2005, subsys 4.0, imports InterlockedCompareExchange | same as 5.9.8 |
| 6.1 | no ANSI build | | |

- None of the ANSI exe/dll import EncodePointer, DecodePointer, FlsAlloc, HeapSetInformation or GetModuleHandleEx (the VS2010-era CRT imports that break 9x).
- GetLongPathNameA: listed on "Named Exports Added For KERNEL32 4.10", i.e. Windows 98 (Geoff Chappell, https://www.geoffchappell.com/studies/windows/win32/kernel32/history/names410.htm, opened). **So these builds do not load on Windows 95.** This matches SUPPORTED_SYSTEM.md (95: v3.9).
- InterlockedCompareExchange (6.0 SciLexer.dll, and LightExplorer.dll in all versions): the same site's 4.0 page marks it "NT-only in 4.0". The page defines that label as meaning the function was taken up for version 4.10 (Windows 98), so Windows 98 has it (opened).
- A subsystem 5.0 image does not start on Windows 9x ("The file expects a newer version of Windows"). This comes from search snippets only (legacyextender.com, MSFN). Whether Windows 98 also refuses to LoadLibrary a subsystem 5.0 **DLL** (6.0's PluginManager.dll) was not verified.
- Windows ME: SUPPORTED_SYSTEM.md lists ME the same as 98. Not otherwise checked.

### Known functional problem (unresolved)

- FileDialog.cpp (the same code at tags v5.8.7 through v6) sets `_ofn.lStructSize = sizeof(OPENFILENAME)` when the OS is older than Windows 2000. Since v5.8.3, PowerEditor/src/MISC/Common/precompiledHeaders.h has `#define _WIN32_WINNT 0x0501` (checked at tags v5.8.2: absent, v5.8.3 onwards: present; FileDialog.cpp includes that header). With _WIN32_WINNT >= 0x0500, sizeof(OPENFILENAME) is the Windows 2000 size (88 bytes), not the 76-byte size that 95/98/NT4 expect.
- This would explain Tony's report that Open/Save dialogs do not appear with 5.9.3 ANSI on Windows 98. I believe it applies equally to every build from 5.8.3 to 6.0, including both candidates. I confirmed it from the source only. I tried to confirm it from the binary with a byte-pattern search, which was inconclusive.
- Files can still be opened by drag and drop, from the command line or through "Open with" (not tested).
- If a VM test confirms the problem, 5.8.2 ANSI (the last build before the define) should be considered instead. It was downloaded to a temp folder only and not otherwise checked.

## Download

- Official page at release time: http://notepad-plus-plus.org/download/v5.9.6.2.html (Wayback 20130115203414, opened). It says "Release Date: 2011-11-13" and links http://download.tuxfamily.org/notepadplus/5.9.6.2/npp.5.9.6.2.bin.zip (and the Installer, 7z, minimalist, digest and src.7z in the same folder).
- In 2016 the official pages moved these files to notepad-plus-plus.org/repository/5.x/..., which now returns 404. The current notepad-plus-plus.org/downloads/ has no version older than 6.2.3 (checked). GitHub releases start at 6.7.9 (checked with gh API; the git tags exist without assets). SourceForge "notepad-plus" /OldFiles is empty.
- **The files are still live on the official TuxFamily host, now under /archive/** (directory listing opened):
  - URL: http://download.tuxfamily.org/notepadplus/archive/5.9.6.2/npp.5.9.6.2.bin.zip (plain HTTP works, including `curl --http1.0`: 200 OK, Last-Modified 2011-11-13)
  - File: npp.5.9.6.2.bin.zip, 8,037,190 bytes (zip with ansi\ and unicode\ folders)
  - SHA-256: ac1cb232f400ec22d56a86e67946b743fc7adb2f9756508553ca6cc634f82d58
  - SHA-1: 0f1ba98d59a33e3e8897b0a7e081eec7986ff91d
  - MD5: 4aaaae76efdb124427ad4acaebf906a0
- Published checksum: npp.5.9.6.2.digest.sha1 from the same folder (saved here) lists `0f1ba98d59a33e3e8897b0a7e081eec7986ff91d npp.5.9.6.2.bin.zip`: **MATCH**. The digest is not signed.
- Not used:
  - npp.5.9.6.2.Installer.exe (NSIS, Unicode only, aborts on 95/98/ME, see above);
  - npp.5.9.6.2.bin.7z (7z format, not supported by Beacon's unzip);
  - npp.5.9.6.2.bin.minimalist.7z (Unicode only; checked for 6.0).
- Alternative, if 6.0 is chosen: http://download.tuxfamily.org/notepadplus/archive/6.0/npp.6.0.bin.zip. File 8,148,111 bytes, SHA-256 aa9d3927299169fb8dc1d851c66ead3ef97519fb2ed6e36e3b30435430311c3f, SHA-1 77ca1f26c229a33bc83fc4a1ba64a9e9f30f6005, matching npp.6.0.digest.sha1. It was downloaded to a temp folder, not to this package folder.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\notepad-plus-plus -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- Notepad++: GPL "version 2 of the License, or (at your option) any later version" (header of PowerEditor/src/Notepad_plus.cpp and precompiledHeaders.h in the source archive). ansi\license.txt in the zip is the GPL v2 text.
- Scintilla (SciLexer.dll, Scintilla 2.27 per scintilla/version.txt): permissive license by Neil Hodgson. Its source is in the archive.
- TinyXML (compiled into notepad++.exe): zlib-style notice. Its source is in the archive (PowerEditor/src/TinyXml).
- LICENSE.TXT here holds the GPL v2 text from the zip, the Scintilla License.txt and the TinyXML notice, plus a header.
- Redistributing unmodified binaries is allowed under GPL v2 s.3, with the license text and the complete corresponding source, or a written offer of it.
- **Bundled programs whose source is NOT in npp.5.9.6.2.src.7z.** Found by listing the zip. License strings are read from the binaries and not verified further.
  - ansi\plugins\NppTextFXA.dll: TextFX 0.25 by Chris Severance, "(C) 2005-2007 GNU GPL"
  - ansi\plugins\NppExec.dll: NppExec 0.4.1. License not stated in the binary; unknown.
  - ansi\plugins\SpellChecker.dll: Spell Checker 1.3.3 by Jens Lorenz, "a free (GNU) Spell Checker interface for Aspell"
  - ansi\plugins\NppExportA.dll: NppExport 0.2.8, "a free (GNU) source code editor" (the string refers to Notepad++); plugin license unknown
  - ansi\plugins\LightExplorer.dll: Light Explorer 1.6. Its PDB path contains "GNU_General_Public_License"; license otherwise unknown
  - ansi\plugins\ComparePlugin.dll: Compare 1.5.5. License unknown.
  - ansi\plugins\PluginManager.dll and ansi\updater\gpup.exe: Plugin Manager 0.9.3.1 by Dave Brotherstone, "A free (GPL) plugin management plugin". They contain zlib/minizip.
  - The unicode\ folder has the Unicode versions of the same plugins plus NppFTP and Converter.
  - The source archive also contains prebuilt binaries (PowerEditor/bin/updater GUP.exe, libcurl.dll, gpup.exe, NppShell.dll), so "source" is not purely source.
- **Consequence:** like VLC, we cannot host this zip as-is without the matching sources of the bundled GPL plugins. I did not look for those sources. The publisher's own server still serves the file over plain HTTP, so ENTRY.TXT lists the package as `Availability: external`. If the plugin sources for these exact versions are found later, it can be hosted, with those sources added to `Source`.

## Matching source

- URL: http://download.tuxfamily.org/notepadplus/archive/5.9.6.2/npp.5.9.6.2.src.7z (linked as "source code" on the official 5.9.6.2 page)
- File: src\npp.5.9.6.2.src.7z, 3,901,782 bytes
- SHA-256: 5a6e1be7b75fab9086afab1d1ba26cc8d7236d0fda78ef32433a95ad0f751c7b
- SHA-1 1839f263d99df163ab09881b21ec9542ce766419. The digest file does not cover the source archive, so there is nothing to compare it with.
- Contents: PowerEditor (Notepad++, TinyXML), scintilla (2.27), readmeFirst.txt. No plugin sources. The git tag v5.9.6.2 in github.com/notepad-plus-plus/notepad-plus-plus is another official source.
- It is not offered in the ENTRY `Source` field, because the package is `external`. The folder copy is kept in case we decide to host.

## Security

Sources: NVD API 2.0 keywordSearch "notepad++" (40 results, fetched 2026-09-29), plus grep of the 5.9.6.2 source to see whether the named code exists. For CVEs about 2011-era code, I did not check whether the flaw itself is present.

Probably apply: the NVD range covers 5.9.6.2, or there is no range and the named code exists in 5.9.6.2.
- CVE-2023-40031 (CVSS3 7.8): heap buffer overflow in Utf8_16_Read::convert, fixed in 8.5.7. The function is present. **Worst: opening a crafted file.**
- CVE-2022-31901 (6.5): buffer overflow in Notepad_plus::addHotSpot, crash (8.4.3 and earlier). Present.
- CVE-2022-31902 (5.5): stack overflow in Finder::add (8.4.3 and earlier). Present.
- CVE-2026-86054 (7.8): stack overflow in NppParameters::writeSession (before 8.9.8). Present.
- CVE-2026-86056 (5.5): NPPM_SAVESESSION handler (before 8.9.8). Present.
- CVE-2026-54758 (7.8): expandNppEnvironmentStrs in RunDlg.cpp (before 8.9.7). Present.
- CVE-2026-48770 (5.0): malformed WM_COPYDATA from a local process (before 8.9.6.1). The handler is present.
- CVE-2026-48800 (7.8): `<UserDefinedCommands>` in shortcuts.xml (before 8.9.6.1). Present.
- CVE-2025-15556 (7.5): the WinGUp updater does not verify update integrity (before 8.8.9). The 5.9.6.2 zip has no GUP.exe; the ansi updater is Plugin Manager's gpup.exe. Probably not applicable.

Do not apply or not applicable:
- CVE-2023-40036, -40164 (uchardet), CVE-2023-40166 (detectLanguageFromTextBegining), CVE-2026-48778 (commandLineInterpreter), CVE-2026-52884/-52885/-85288/-71858 (HMAC/trusted-directory features): that code is not in 5.9.6.2.
- CVE-2019-16294: the NVD text says x64, so it does not apply.
- CVE-2014-9456 (6.6.9 only), CVE-2023-47452 (6.5 only), CVE-2017-8803 (Hex Editor plugin): the NVD CPE names other versions or components.
- Installer CVEs (CVE-2025-49144, CVE-2026-46710, -73250): we do not use the installer.
- CVE-2007-2666 and CVE-2008-3436 are fixed in 4.x.

Unknown: CVE-2023-6401 (dbghelp.exe, "up to 8.1", disputed); CVE-2026-25926 (Explorer search path, before 8.9.2); CVE-2026-57233 (WinGup ZIP path traversal); CVE-2026-85279 (PluginsManager::loadPluginFromPath, which does not exist under that name in 5.9.6.2); CVE-2026-77605 (Folder as Workspace, which is not in 5.9.x).

Summary: about 8 CVEs probably apply and 5 are unknown. The worst is CVE-2023-40031 (heap buffer overflow when opening a crafted file, CVSS3 7.8). Several 2026 CVEs (7.8) need a malicious config, session or shortcuts file, or a local process.

## Install behaviour

- Package type: plain zip (npp.5.9.6.2.bin.zip), 755 entries, 21,715,249 bytes unpacked (ansi\ 9,313,181 bytes). Listed with .NET ZipFile; nothing was extracted to run.
- Layout: two top-level folders, `ansi\` and `unicode\`, each a complete program: notepad++.exe, SciLexer.dll, *.model.xml, contextMenu.xml, shortcuts.xml, doLocalConf.xml, license.txt, readme.txt, change.log, plugins\ (DLLs, APIs\, Config\, doc\), updater\gpup.exe, localization\, themes\, user.manual\.
- doLocalConf.xml is present, so Notepad++ keeps its settings in its own folder.
- What Beacon must do: Beacon's `unzip` cannot pick one subfolder, and `strip 1` would put ansi\ and unicode\ into the same folder, where they overwrite each other. So unzip the whole archive into {dir} (no strip). The Start Menu shortcut must point to `{dir}\ansi\notepad++.exe`. The unused unicode\ folder costs about 12 MB. Uninstall is `files`.
  - A later format option such as `unzip {dir} only ansi/` would save that space.
- No registry entries, shell extension or file associations are created (zip package).
- For reference, the NSIS installer (not usable on 9x): default folder `$PROGRAMFILES\Notepad++`, Add/Remove Programs key `Software\Microsoft\Windows\CurrentVersion\Uninstall\Notepad++` with DisplayName "Notepad++" (nppSetup.nsi at tag v5.9.2/v6), standard NSIS `/S`.

## Verification notes

- Verified by opening or downloading:
  - SUPPORTED_SYSTEM.md (raw);
  - nppSetup.nsi, FileDialog.cpp, precompiledHeaders.h, notepadPlus.vcproj and change.log at the git tags;
  - Wayback copies of the 5.9.1 and 6.0 news pages and of the download pages for 5.9.2, 6.0 and 5.9.6.2 (2011-2016);
  - the TuxFamily /archive/ listings;
  - the bin.zip packages of 5.8.2, 5.8.3, 5.9, 5.9.1-5.9.8, 6.0 and 6.1 plus the digests, all PE-inspected in memory and never run;
  - the 5.9.6.2 source archive (extracted in a temp folder for grep);
  - the Geoff Chappell KERNEL32 export pages, the SourceForge forum thread, Notepad++ Community topic 15238, and NVD records.
- From search snippets only: that subsystem 5.0 executables do not start on 9x.
- Not verified:
  - running on 98 or ME (no VM interaction);
  - whether the Open/Save dialogs work;
  - whether a subsystem 5.0 DLL (6.0 Plugin Manager) loads on 98;
  - the plugin licenses and sources;
  - that tuxfamily.org/notepadplus/archive is still maintained by the Notepad++ team. It was the official download host for these versions in 2011-2013.
