# QEMU 0.13.0 for Windows (Kazu / Takeda Toshiya build) - Beacon 98 record

- Date checked: 2026-09-29
- Package: QEMU PC and multi-CPU emulator, unofficial Windows build "QEMU on Windows Ver 0.13.0" (2010-10-16)
- Built by "Kazu" (QEMU on Windows, http://www.h7.dion.ne.jp/~qemu-win/) and distributed by Takeda Toshiya as "Kazu's proxy"
- License: GNU GPL v2 (QEMU as a whole), with LGPL/BSD parts. The zip also contains SDL.dll (LGPL), fmod.dll (FMOD 3.75, proprietary freeware) and libusb0.dll.
- Needs KernelEx on Windows 98 and ME (XP mode reported). Not for Windows 95.
- **Recommendation: do not publish yet.** The binary is dynamically linked to the proprietary FMOD library (see License). Whether a GPL binary may be redistributed that way is not certain, so it does not meet "certain to be legal". Everything else is ready.

## Which build, and where it comes from

- MSFN "KernelEx Apps Compatibility List (New)" (read 2026-09-29), https://msfn.org/board/topic/152471-kernelex-apps-compatibility-list-new/ :
  "QEMU PC Emulator 0.13.0, KX 4.5.1, XP mode", linked to http://homepage3.nifty.com/takeda-toshiya/qemu
- Operating System Revival KernelEx list (read 2026-09-29), https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html :
  "QEMU PC Emulator 0.13.0 (KX 4.5.1, XP mode)" (the same entry, copied from MSFN).
- KernelEx version 4.5.1, Windows XP mode. Beacon ships 4.5.2, so test it.
- Takeda's page (homepage3.nifty.com is gone; I opened the Wayback capture of 2014-10-22,
  http://web.archive.org/web/20141022042304/http://homepage3.nifty.com/takeda-toshiya/qemu/index.html):
  "QEMU on Windows ... This is the tentative page to provide QEMU windows port binaries as Kazu's proxy."
  List: "QEMU on Windows Ver 0.13.0 (10/16/2010)", 0.12.5, 0.12.2, 0.12.1, 0.11.1, 0.10.6, 0.9.1 (2/4/2008).
  "Please refer Kazu's site for more details": http://www.h7.dion.ne.jp/~qemu-win/index.html. I could not open it: the Wayback CDX returned 504.
- Official QEMU did not ship Windows binaries in 2010. Stefan Weil's builds (https://qemu.weilnetz.de/, opened) start with the 2011 and 2012 folders ("experimental QEMU for Windows"), so they do not cover 0.13. Kazu's builds, mirrored by Takeda, were the widely used Windows builds of that time, and this is the one both lists point to.

## Why KernelEx is needed; older version without KernelEx

- I read the import tables of qemu.exe with a small PE parser (nothing was executed). 0.13.0 imports `getaddrinfo`, `getnameinfo` and `freeaddrinfo` from WS2_32.DLL. Windows 98's Winsock 2 does not have these (they came with XP), so qemu.exe cannot load on stock 98. KernelEx supplies them.
- The same check on the other builds on Takeda's page (Wayback copies, downloaded to a temp folder only):
  - 0.10.6, 0.11.1 and 0.12.5 also import getaddrinfo/getnameinfo/freeaddrinfo, so they need KernelEx too.
  - **0.9.1 (2008-02-04) does not import them.** Its imports are ordinary Win32 A functions plus IPHLPAPI GetNetworkParams, WINMM, SDL.dll and fmod.dll. It is the best candidate for a build that runs WITHOUT KernelEx. Kazu's README in these packages also mentions Windows Me ("Please use Alt and Tab on WindowsMe"). There is no explicit statement that 0.9.1 runs on 98, and I did not check every kernel32 import (it uses LockFileEx and SetProcessAffinityMask, which 9x may only stub). Needs a VM test.
  - qemu-0.9.1-windows.zip: 13,150,644 bytes, SHA-256 ea311d7c05651ad6cbd54a97a75241b25b6937f2a106081ca16bdb8b68c4929a (Wayback capture 20121018124147). It has the same FMOD linkage.

## Download

- The original server is gone (homepage3.nifty.com returned 404 from 2018). I used the Internet Archive. That is acceptable only if the license allows sharing: QEMU, SDL and libusb do; FMOD's EULA allows fmod.dll to be redistributed unmodified; the GPL/FMOD combination is questionable (see License).
- URL: http://web.archive.org/web/20130507042113id_/http://homepage3.nifty.com/takeda-toshiya/qemu/qemu-0.13.0-windows.zip
- File: qemu-0.13.0-windows.zip, 20,658,855 bytes, a valid zip with 85 entries and 55,031,818 bytes unpacked
- SHA-256: 702b36ec534eb071f80eb9f588497f3d895a72066ac984ab996fad65d6340389
- MD5: 264639595a0f88531f5855e8f769cebf
- Published checksum: none (Takeda and Kazu published no hashes). Not compared.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\qemu -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- QEMU 0.13.0 LICENSE (from the source tarball): "QEMU as a whole is released under the GNU General Public License", with parts under the LGPL and BSD licenses. The zip itself carries an older Bellard LICENSE from 2005.
- Contents of the zip and their licenses:
  - qemu.exe, qemu-system-x86_64.exe, qemu-system-{arm, cris, m68k, microblaze, mips*, ppc*, sh4*, sparc*}.exe, qemu-img.exe, qemu-io.exe: GPL v2. Built from qemu-0.13.0 plus patch/qemu-0_13_0.diff (included in the zip). patch/readme.txt: "Mr.Kazu's qemu-0.9.0-patches" and "Mr.lukewarm (sava)'s cirrus bitblit fix patch".
  - SDL.dll: LGPL (License/README-SDL.txt). The exact SDL version is unknown (the DLL has no version resource).
  - **fmod.dll: FMOD 3.75, proprietary.** EULA (License/README.TXT): "The fmod.dll file may be redistributed without the authors prior permission, and must remain unmodified." "FMOD may not be used in a commercial product ... without a commercial license." Beacon is free, so the EULA's own conditions are met.
  - libusb0.dll: LibUSB-Win32 0.1.10.2 (LGPL/GPL). qemu.exe does not import it.
  - Firmware: bios.bin, vgabios.bin, vgabios-cirrus.bin, pxe-*.bin, ppc_rom.bin and optionrom/*.bin are **byte-identical** to pc-bios/ in qemu-0.13.0.tar.gz (SHA-256 compared). Their sources (roms/seabios, roms/vgabios and others) are in that tarball.
  - linux.img (10 MB): a small Linux test disk (boots to "sh-2.05b#" with nbench, per README-en.txt). It contains GPL software (Linux kernel, shell) whose source is NOT offered. Unresolved.
- **The main issue:** qemu.exe (and the other emulators) import fmod.dll directly (`_FSOUND_Init@12` and others). The binary cannot start without it. That is a GPL v2 program distributed linked to a non-free library, with no linking exception and outside the GPL "system library" exception. Upstream QEMU shipped the FMOD audio driver (audio/fmodaudio.c), but the QEMU license grants no FMOD exception. This is a real legal question, and I recommend not hosting it until it has been reviewed. "External" is not possible, because the publisher's server is gone.
- LICENSE.TXT = a summary header, then LICENSE, COPYING and COPYING.LIB from qemu-0.13.0.tar.gz, then License/LICENSE, License/README-SDL.txt and License/README.TXT (FMOD EULA) from the zip.

## Matching source (in src\)

- qemu-0.13.0.tar.gz: https://download.qemu.org/qemu-0.13.0.tar.gz, 5,184,531 bytes,
  SHA-256 1e6f5851b05cea6e377c835f4668408d4124cfb845f9948d922808743c5fd877, MD5 397a0d665da8ba9d3b9583629f3d6421.
  OpenPGP signature https://download.qemu.org/qemu-0.13.0.tar.gz.sig: **Good signature** from "Anthony Liguori <anthony@codemonkey.ws>", key 16AC FD5F BD34 880E 584E CD29 75E9 CA92 7C18 C076 (key fetched from keyserver.ubuntu.com; not otherwise certified), made 2010-10-15.
- qemu-0_13_0.diff: the build's patch, copied unchanged from patch/ in the zip. 22,224 bytes, SHA-256 3c6d79c0b25c27d168eaf2787ca99815d577c61fde5d36c0e21b8c64bf902e42. It touches block/vvfat.c, configure, hw/cirrus_vga.c, hw/cirrus_vga_rop.h, net/socket.c, osdep.c, qemu-char.c, qemu_socket.h, ui/sdl.c, ui/vnc.h and ui/x_keymap.c.
- Not included, unresolved: the source of the SDL.dll version used (unknown version); libusb-win32 0.1.10.2 source; the linux.img contents; Kazu's exact build configuration (MinGW, configure flags).

## Security

- NVD CPE match for qemu 0.13.0 (virtualMatchString cpe:2.3:a:qemu:qemu:0.13.0): **312 CVEs**. Many are for devices or features that 0.13 does not have or that are not in this build (virtio-crypto, rocker, 9pfs, AHCI...), so the real number is lower. It was not counted exactly.
- Relevant and severe for a PC emulator of this age: CVE-2015-7512 (pcnet NIC buffer overflow, CVSS 9.0), CVE-2016-3710 (VGA banked-access out-of-bounds, guest to host, 8.8), CVE-2015-3456 "VENOM" (floppy controller overflow, guest to host), CVE-2017-16845 (ps2 migration, 10.0).
- Risk: a malicious guest OS or disk image can break out into the Windows 98 host. Warn the user to run only trusted guests.

## Install behaviour

- Plain zip, no installer. Layout: files at the root (qemu.exe, qemu-system-x86_64.exe, qemu-img.exe, qemu-io.exe, SDL.dll, fmod.dll, libusb0.dll, BIOS images, linux.img, qemu-win.bat, qemu-x86_64.bat, README-en.txt/README-ja.txt, docs) plus the folders bin\ (other-CPU emulators), keymaps\, License\, optionrom\, patch\.
- README-en.txt: "Please extract ziped file. When extracted, you are ready." To uninstall: "Please delete the extracted folder."
- Beacon: `unzip {pf}\QEMU` (no strip). Shortcut to qemu-win.bat (it boots the bundled linux.img with `qemu.exe -L . -m 128 -hda linux.img ...`) with working folder {pf}\QEMU. Uninstall: files. No Add/Remove Programs entry.

## Verification notes

- Verified by opening or downloading: the MSFN and OSR lists, the Wayback CDX and a capture of Takeda's page, the zip (listing, README-en.txt, License/*, patch/*, qemu-win.bat), the import tables of qemu.exe and qemu-img.exe (0.13.0) and of qemu.exe in 0.9.1/0.10.6/0.11.1/0.12.5 (read as bytes), the firmware hash comparison, download.qemu.org with a GPG verification, qemu.weilnetz.de, and NVD.
- Not verified: Kazu's own site (Wayback unavailable); running on 98 (no VM interaction); whether 0.9.1 loads on stock 98.
