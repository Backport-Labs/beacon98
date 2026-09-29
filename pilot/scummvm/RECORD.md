# ScummVM (Windows 95+ build)

- Date checked: 2026-09-28
- Name: ScummVM
- Version: 2026.1.0, the Windows 95+ ("win9x") build (NEWS.txt in the zip: "#### 2026.1.0 (2026-01-31)")
- Current mainline version: 2026.3.0. It has no win9x build (neither does 2026.2.0).

## License
GNU GPL version 3 or later. COPYING.txt in the zip starts with:
> GNU GENERAL PUBLIC LICENSE
> Version 3, 29 June 2007

NEWS.txt, under 2.6.0 (2022-08-01): "The project license has been upgraded to GPLv3+."
LICENSE.TXT in this folder is a verbatim copy of COPYING.txt from the zip.

The zip also ships the licences for bundled third-party code: COPYING.LGPL, BSD, MIT, Apache,
BSL, ISC, LUA, MKV, MPL, OFL, GLAD, TINYGL and CatharonLicense.txt. The package must keep all of them.

The exe is statically linked. I identified these libraries from strings in the exe; I did not
check them against the build scripts:
- SDL 1.2: inferred from the "windib" and "directx" video driver names (LGPL-2.1)
- zlib ("inflate 1.3.1")
- libpng 1.6.48
- libjpeg-turbo
- libFLAC ("reference libFLAC 1.2.1")
- libvorbis 1.3.7
- FluidSynth (LGPL)
- libmad and libmpeg2 (GPL)
- theora
- freetype
- fribidi (LGPL)

## Windows 9x evidence
- https://www.scummvm.org/downloads/ (opened 2026-09-28) lists the build in the section titled
  "Older versions (unsupported)":
  "2026.1.0 Windows 95+ zipfile (109.2 MiB .zip, last update: 2026-01-30, sha256 3385d68305cda3f8737feea08069599807847aed5af692c2aef3f260ace9a314 *scummvm-2026.1.0-win32-win9x.zip)".
  The Windows 95+ build is published officially, but the site files it under "unsupported".
- Directory listings on downloads.scummvm.org/frs/scummvm/ (opened) show these win9x builds:
  - installer: 2.1.0 (`scummvm-2.1.0-win32-win9x.exe`) and 2.2.0 (`scummvm-2.2.0-win9x-win32.exe`)
  - zip: 2.5.1, 2.6.0, 2.6.1, 2.7.0, 2.7.1, 2.8.1, 2.9.0, 2.9.1 and 2026.1.0
  - none: 2.0.0, 2.1.1, 2.1.2, 2.5.0, 2.8.0, 2026.2.0 and 2026.3.0

  **2026.1.0 is the newest release with a win9x build.**
- NEWS.txt in the zip:
  - 2.9.1: "Restored FLAC support in the Windows 9x port."
  - older entry: "Fixed detection of the Application Data path on Windows 95/98/ME."
- PE header of scummvm.exe (read, not run): i386, OS/subsystem version 4.0, GUI subsystem.
- Static imports are ADVAPI32, GDI32, KERNEL32, msvcrt.dll, OLE32, SHELL32, USER32 and WINMM.
  - msvcrt.dll ships with Windows 98. On Windows 95 it may need to be present already; not verified.
  - ddraw, dsound and dinput are not static imports. SDL loads them at runtime, so DirectX is not a
    hard load-time dependency. I infer that SDL 1.2 falls back to windib and waveOut without it;
    this is not tested.

## Download
- URL: https://downloads.scummvm.org/frs/scummvm/2026.1.0/scummvm-2026.1.0-win32-win9x.zip
- File: scummvm-2026.1.0-win32-win9x.zip
- Size: 114,460,830 bytes
- SHA-256: 3385d68305cda3f8737feea08069599807847aed5af692c2aef3f260ace9a314
- Published checksum: the same value appears in both places below, so it **MATCHES**.
  - `scummvm-2026.1.0-win32-win9x.zip.sha256` on the server
  - the downloads page
- Contents: 42 entries, one static `scummvm.exe` (196,499,982 bytes, all engines built in), docs, licences and NEWS. There are no DLLs.
- Defender: MpCmdRun -Scan -ScanType 3 on this folder found no threats. Signature version 1.459.442.0, scanned 2026-09-28.

## Source (GPL corresponding source)
- URL: https://downloads.scummvm.org/frs/scummvm/2026.1.0/scummvm-2026.1.0.tar.xz
- Size: 226,299,792 bytes
- SHA-256: e15b8650c2bd9e11b69b49eef9dea1eedccc5b1c191748b15c34167614d77b66. It **MATCHES** the published .sha256.
- Open issue: the binary statically links third-party libraries (SDL 1.2, libmad, libmpeg2, FLAC,
  vorbis, FluidSynth and others). Their source is not in this tarball. GPLv3 corresponding source
  covers them, so we must also mirror or offer those exact library sources. I could not find which
  toolchain or library versions the win9x build used.

## Security
- NVD keyword "scummvm" returns one CVE: CVE-2017-17528 (BROWSER environment variable argument
  injection, 1.9.0). It applies to the Unix/xdg path, so it is not relevant here.
- The bundled libFLAC 1.2.1 is old. NVD lists these for libFLAC <= 1.3.0:
  - CVE-2014-8962 (stack overflow)
  - CVE-2014-9028 (heap overflow)

  They can only be reached through crafted FLAC game audio. The pilot game does not use FLAC.
- The win9x build is listed as "unsupported", so do not expect security fixes. Windows 9x itself
  has no security support.

## Install notes
- No installer for 2026.1.0 win9x: it is a plain zip. The last win9x installer (.exe) was 2.2.0.
  I did not check that installer's type or silent switch.
- Package manager: unzip to a folder, e.g. C:\Program Files\ScummVM. There is no uninstaller
  registration, so Beacon must provide its own uninstall entry.
- Config file location, from source backends/platform/sdl/win32/win32.cpp (2026.1.0):
  - Portable mode: if `scummvm.ini` exists next to scummvm.exe, it is used, and icons, logs and
    saves stay in the exe folder. The Program Files exclusion applies only on Vista and later.
  - Otherwise: `<CSIDL_APPDATA>\ScummVM\scummvm.ini`. If SHGetFolderPath fails, the fallback is
    `%WINDIR%\scummvm.ini`.
  - Recommendation: have Beacon create an empty or pre-filled `scummvm.ini` beside the exe, so it
    runs portable and is easy to uninstall.
- Registering a game without the GUI (from base/commandLine.cpp):
  `scummvm.exe --add --path=C:\GAMES\BASS --game=sky`. It writes a target with `engineid` and `gameid`.
  Beacon can also write the ini section directly.
