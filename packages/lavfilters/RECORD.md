# LAV Filters 0.66 - Beacon 98 record

- Date checked: 2026-09-29
- Package: LAV Filters (Hendrik Leppkes, "Nevcairiel"), DirectShow splitter plus audio and video decoders based on FFmpeg
- Version: 0.66 (release tag "0.66", version 0.66.0, 2015-09-22), 32-bit
- License: GNU GPL v2 or later. It bundles FFmpeg (LGPL/GPL), libbluray (LGPL), dcadec (LGPL) and the Intel QuickSync decoder (BSD-3-Clause).
- Needs KernelEx on Windows 98 and ME, and a compatibility mode (XP SP3 reported). Not for Windows 95.
- Recommendation: the official 0.66 release, x86 zip. The build actually reported working is the nightly "0.66.0-10", 10 commits after the release. See below.

## Windows 9x / KernelEx evidence

- Operating System Revival, "List of Working Windows 98/ME KernelEx Applications" (downloaded and read 2026-09-29),
  https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html , Codecs:
  "LAVFilters-0.66.0-10 (KernelEx 4.5.2019.24; XP SP3 Mode)".
  - KernelEx 4.5.2019.24 is the unofficial updated KernelEx build. Beacon ships official 4.5.2, so test it.
  - Mode: Windows XP SP3.
- LAV Filters is not on the MSFN KernelEx list.
- What "0.66.0-10" is: the author's official nightly server https://files.1f0.de/lavf/nightly/0.66/ (listing opened) has "LAVFilters-0.66.0-10.exe 2015-09-28 14:07 8.9M", followed by -12, -13 ... -39. The installer script builds names as MAJOR.MINOR.REVISION-BUILD (LAVFilters.iss: `LAV_VERSION_STRING ... + "-" + str(LAV_VERSION_BUILD)`). So it is a nightly installer made 6 days after the 0.66 release, and not a release. I downloaded it to a temp folder only for its hash: 9,313,176 bytes, SHA-256 b9929f53d15bcf2ff063e566a9feaa6c905a02de1087cc6ae7f0e82acd94bbed. It is not in the package folder. The files server publishes no checksums.
- Why I chose the release: it has an exact tag, published sources for every submodule, and it differs from the tested nightly by only 10 commits over 6 days. The nightly's exact commit is not recorded on the server; `git describe` would show it, but I did not look it up. If Beacon wants the exact tested bits, it would need that commit's source for GPL compliance.
- Why KernelEx and XP mode: the installer script at tag 0.66 (https://raw.githubusercontent.com/Nevcairiel/LAVFilters/0.66/LAVFilters.iss, opened) has `MinVersion = 0,5.01SP2`. In Inno Setup, "0" for the Windows 9x version means it will not run on 95/98/ME, and the NT minimum is XP SP2. The installer is Inno Setup 5.5.6 Unicode (from the header string in the exe). The binaries are built with VC++ 2013 (README.txt: "Compiling is pretty straight forward using VC++2013"), whose runtime needs XP. That fits the reporter's use of KernelEx "XP SP3 Mode", which makes the installer and filters see XP SP3.
- Older version without KernelEx: none. I found no LAV Filters release that ever supported 9x. The project started in 2010, targeting XP and later, and VC++ 2010+ runtimes do not run on 9x. The old installers' MinVersion values were not checked one by one, so this is inference.

## Download

- Release page: https://github.com/Nevcairiel/LAVFilters/releases/tag/0.66 (opened). Assets: LAVFilters-0.66-Installer.exe, LAVFilters-0.66-x86.zip, LAVFilters-0.66-x64.zip. GitHub shows no digests for these 2015 assets.
- Recommended for Beacon: https://github.com/Nevcairiel/LAVFilters/releases/download/0.66/LAVFilters-0.66-x86.zip
  - File: LAVFilters-0.66-x86.zip, 6,801,476 bytes, SHA-256 826e63a4b11d2318adf6249e94cb97ad8237c18645787ce3c8e576fb6949f249
- Also downloaded: https://github.com/Nevcairiel/LAVFilters/releases/download/0.66/LAVFilters-0.66-Installer.exe
  - 9,197,512 bytes, SHA-256 76910ae9eee02153f63a7f4a5b2c6dec1e271303008170c29eebd9bce97920fd (contains both x86 and x64)
- Published checksums: none (GitHub assets from 2015 have no digest; the project publishes no hash files). Not compared.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\lavfilters -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- COPYING in the zip and the source is the GPL v2. Source headers: "either version 2 of the License, or (at your option) any later version".
- LICENSE.TXT = a short header, COPYING unchanged, and the Intel qsdecoder license.txt (BSD 3-clause). Its binary-redistribution condition requires reproducing that notice, and LICENSE.TXT does so.
- Redistribution of the unmodified binaries is allowed with the license and the complete corresponding source. We host the source:

## Matching source (hosted, in src\)

| File | Origin | Size | SHA-256 |
|---|---|---|---|
| LAVFilters-0.66.tar.gz | https://codeload.github.com/Nevcairiel/LAVFilters/tar.gz/refs/tags/0.66 | 1,208,829 | cc8435fd257d53a076c7863e5782c1b1aca556c991edd8320a92ef389b11cd7e |
| FFmpeg-c6229c738e2fa6de1b3aea79d2e062a882a5b4be.tar.gz | submodule `ffmpeg @ c6229c7` (2015-09-22 "Backport a few asfdec fixes"), fetched with git from https://gitea.1f0.de/LAV/FFmpeg.git (the author's server; .gitmodules says git://git.1f0.de/ffmpeg.git) and packed with `git archive` | 10,294,114 | 3e107adef38a3ee588166202f71fa84d0c1d67fdb93cd358ffedc603efc4fb13 |
| libbluray-6f37d6ad12a70f7fe90bce51dbf9393021fa6e4a.tar.gz | submodule `libbluray @ 6f37d6a`, https://gitea.1f0.de/LAV/libbluray.git, git archive | 449,639 | a51ffe4de982129a48fdcd2a0296defd2e637ef6a9fb031a30f86dd216ab30c5 |
| qsdecoder-36b2fcd80469eb7a5e958de17e3cea072ac50b86.tar.gz | submodule `qsdecoder @ 36b2fcd`, https://gitea.1f0.de/LAV/qsdecoder.git, git archive | 2,034,412 | e71175d13cf3817a3b1160c65874bf0560fc91165bea980d9a6231e3408f1053 |
| dcadec-2a9186e34ce557d3af1a20f5b558d1e6687708b9.tar.gz | submodule `thirdparty/dcadec @ 2a9186e`, https://github.com/foo86/dcadec.git, git archive | 218,186 | 766cfcad08f57f2398fd684e4a44c464e6db5507d9c9c46202b0df00b0384e92 |

- I read the submodule commits from the GitHub tree view of tag 0.66 and expanded them to full hashes with the Gitea API and git.
- The archives made with `git archive` are ours, not published files, so there are no publisher checksums. The commits are identified by their git hashes.
- Not covered: the build scripts use MSVC. The libraries linked into FFmpeg (e.g. zlib, if any) were not checked. The Intel Media SDK dispatcher used by qsdecoder may come from Intel's SDK and not be in that repository. Unverified.

## Security

- NVD keyword "LAV Filters": 0 results.
- The bundled FFmpeg is the author's fork at the 2.8 development stage (September 2015). FFmpeg has many later-fixed CVEs that affect code of that age, e.g. CVE-2016-10190 (heap overflow in libavformat/http.c, "FFmpeg before 2.8.10", CVSS 9.8) and many decoder out-of-bounds writes from 2016-2020. I did not count them precisely. Probably dozens apply.
- Summary: 0 LAV-specific CVEs; many FFmpeg CVEs. A crafted media file can compromise the player process. Give a Warning.

## Install behaviour

- Installer exe: Inno Setup 5.5.6 (Unicode). Silent switches `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART`. AppId `lavfilters`, AppName "LAV Filters", AppVerName "LAV Filters 0.66". Inno's default uninstall key is `lavfilters_is1`, DisplayName "LAV Filters 0.66" (the script sets no UninstallDisplayName). DefaultDirName `{pf}\LAV Filters`. **It refuses to run on 9x (`MinVersion = 0,5.01SP2`) unless KernelEx XP mode is set for the installer.** Beacon cannot set that, so it is not suitable as is.
- Recommended: the x86 zip (flat, no top folder): LAVSplitter.ax, LAVVideo.ax, LAVAudio.ax, avcodec-lav-56.dll, avformat-lav-56.dll, avutil-lav-54.dll, avfilter-lav-5.dll, avresample-lav-2.dll, swscale-lav-3.dll, libbluray.dll, IntelQuickSyncDecoder.dll, LAVFilters.Dependencies.manifest, install_*.bat / uninstall_*.bat (`regsvr32.exe LAVVideo.ax` etc.), README.txt, COPYING, CHANGELOG.txt. 15,555,178 bytes unpacked.
  Beacon: `unzip {pf}\LAV Filters`, then `After: run {sys}\regsvr32.exe /s "{dir}\LAVSplitter.ax"` (same for LAVAudio.ax and LAVVideo.ax). README.txt: "Unpack - Register (install_*.bat files)".
  Unresolved: (1) whether regsvr32 of these .ax files succeeds under KernelEx default mode, or whether the .ax files and the host player need XP mode set in KernelEx; (2) `Uninstall: files` does not unregister the filters (FORMAT.md has no pre-uninstall step), so the COM registrations would remain. Needs a VM test and possibly a client feature.
- Add/Remove Programs: none for the zip route.

## Verification notes

- Verified by opening or downloading: the OSR KernelEx list, the files.1f0.de nightly listing, the GitHub release page and assets, LAVFilters.iss and .gitmodules at tag 0.66, the GitHub tree (submodule hashes), the Gitea API, the zip contents (README.txt, COPYING, bat files, manifest), the source headers, the qsdecoder license.txt, NVD, and the installer header string.
- Not verified: behaviour on 98 with KernelEx 4.5.2 (no VM interaction); the exact commit of nightly 0.66.0-10.
