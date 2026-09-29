# xCHM (Win32 build) - Beacon 98 record: NOT PACKAGED (no obtainable download)

- Date checked: 2026-09-29
- Package: xCHM, CHM viewer based on wxWidgets and chmlib (Razvan Cojocaru), GNU GPL v2
- Wanted: the Win32 build that was reported working with KernelEx
- Result: **stopped.** No official copy of any xCHM Win32 build can be downloaded any more, not even from the Internet Archive. There are no files in this folder and no ENTRY.TXT.

## KernelEx evidence (the version is not stated)

- MSFN "KernelEx Apps Compatibility List (New)" (downloaded and read 2026-09-29), https://msfn.org/board/topic/152471-kernelex-apps-compatibility-list-new/ :
  "xCHM, an excellent viewer for chm files", listed under "What is working with KernelEx", linked to
  http://sourceforge.net/project/showfiles.php?group_id=87007&package_id=171760 (the SourceForge "xCHM for Win32" package). **No version, no KernelEx version, no mode.**
- Operating System Revival KernelEx list (downloaded and read 2026-09-29), https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html :
  "xCHM (2013 or earlier build tested) - An excellent viewer for chm files." No version, no mode.

## Which Win32 builds existed

From Wayback captures of the SourceForge folder "xCHM for Win32" (opened 2026-09-29):
- 2013-03-28 capture: xchm-1.19 (2011-04-25), xchm-1.18 (2010-12-09), xchm-1.16 (2009-05-16)
- 2015-10-02 capture: xchm-1.23 (2014-05-06), xchm-1.19 (2011-04-25)
- xchm-1.19 folder (2017-08-30 capture): README (177 bytes, 2011-04-25) and xchm-1.19win32.zip (906.5 kB, 2011-04-25)
- Older builds are referenced as well: xchm-1.13.zip, xchm-1.9-win32.zip, xchm-1.2-win32.zip, xchm-0.9.8-win32.zip, xchm-0.9.4-win32.zip.

The latest Win32 build from "2013 or earlier" is **1.19 (2011-04-25)**. The next one, 1.23, is from May 2014. Neither list names the version, so 1.19 is the most likely candidate but not a confirmed match; 1.16 and 1.18 are also possible.

## Why nothing could be downloaded

- The SourceForge project is gone: https://sourceforge.net/projects/xchm/ and its RSS return 301 to https://sourceforge.net/directory/graphics/graphics/viewers/. Direct file URLs (https://downloads.sourceforge.net/project/xchm/xCHM%20for%20Win32/xchm-1.19/xchm-1.19win32.zip, likewise 1.18 and 1.23, and the source xchm-1.19.tar.gz) return 404.
- The project continues at https://github.com/rzvncj/xCHM (opened): "UNIX CHM viewer". Tags 1.31 to 1.40 are shown. It has no Windows builds.
- Internet Archive: the SF "/download" pages for 1.16, 1.18, 1.19 and 1.23 are archived only as 302 redirects to downloads.sourceforge.net mirror URLs (voxel, superb-sea2, superb-dca2, deac-riga, hivelocity). None of those targets was archived (Wayback returns 404). The CDX of the mirror hosts I tried has no Win32 zip either.
- I found no other official mirror. (The web search budget for this session was used up, so third-party mirrors were not searched. They would not count as official anyway.)

## What would be needed

- An official copy of xchm-1.19win32.zip (or 1.16/1.18), plus the matching source xchm-1.19.tar.gz and the chmlib and wxWidgets sources the build used. A copy made before the SF project was removed would be acceptable if its origin can be shown. The GPL allows redistribution, so the Internet Archive rule would be satisfied if a copy turned up there.
- Whether 9x needs KernelEx at all depends on whether the build used an ANSI or a Unicode wxWidgets. That is unknown without the binary.

## Not done

- Download, hashes, Defender scan, LICENSE.TXT, source, security review and install behaviour: not possible without the file.
- Security: there is no binary to assess. NVD keyword "chmlib" (the library xCHM uses) gives 3 results. CVE-2005-2930 and CVE-2007-0619 are fixed in chmlib 0.36/0.39. CVE-2025-48172 (_chm_decompress_block integer overflow, "CHMLib through 2bef8d0", CVSS 5.6) would affect any xCHM build of that era.
