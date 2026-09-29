# Tcl/Tk 8.4.20 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Tcl/Tk 8.4.20 (2013-06-01), the last 8.4 release
- License: Tcl/Tk license (BSD-style)
- Status: **NO REDISTRIBUTABLE WINDOWS BINARY FOUND.** Nothing was downloaded.

## Windows 9x support evidence

- https://wiki.tcl-lang.org/page/Windows+98 (opened): Windows 98 is "Not supported by Tcl/Tk from 8.5 onwards." So 8.4.x is the line for 98.

## Binary distributions checked

- tcl-lang.org, 8.4 page (https://www.tcl-lang.org/software/tcltk/8.4.html, opened): offers only "Tcl/Tk 8.4.20 Source Releases".
- SourceForge project tcl, /Tcl/8.4.20 (file RSS opened): only source and docs: tcl8420-src.zip (3,510,574 bytes, MD5 92155a2adc387cf1e486feff844972df), tk8420-src.zip (3,300,630, MD5 2e2b8af8fdf32240679dd1f7740862f9), the tar.gz versions, tcl8.4.20-html.tar.gz, release notes. No Windows binaries.
- tcl-lang.org binary distribution page (https://www.tcl-lang.org/software/tcltk/bindist.html, opened) lists BAWT, Magicsplat, a Codeberg build (8.6 and 9 only), LUCK, KitCreator, FreeWrap and kitgen ("currently only for Tcl 8.6"). BAWT and Magicsplat ship 8.6/9.0; IronTcl also ships 8.6 only (from memory, not reopened). None ship 8.4.
- ActiveTcl 8.4: excluded (ActiveState license does not allow redistribution).
- Equi4 Tclkit (single-file 8.4 runtimes, BSD/MIT-like license per https://www.equi4.com/tclkit/download.html, opened): the page lists Windows 8.4.17 builds at /pub/tk/8.4.17/tclkit-win32.upx.exe and tclkitsh-win32.upx.exe; both return **410 Gone**. The download matrix only lists Windows tclkits up to 8.4.15, and those links lead to empty pages. Pat Thoyts' tclkit site (patthoyts.tk) no longer resolves.
- KitCreator (kitcreator.rkeene.org) builds kits on request; that would be a new build, not an existing distribution, and was not tried.

## Conclusion

- No official or widely used Windows binary of 8.4.20 that we may host is available today. The only route is for Backport Labs to build 8.4.20 itself from tcl8420-src.zip/tk8420-src.zip (8.4's `win/makefile.vc` supports Visual C++ 6; MinGW also works), then verify on 98 and publish it clearly as our own build with the source next to it.
- Security: not assessed, since there is no binary. (NVD keyword "Tcl" returns 110 results, mostly other products.)
