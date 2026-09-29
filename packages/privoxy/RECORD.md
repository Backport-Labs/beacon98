# Privoxy 3.0.19 (IPv4-only build) - Beacon 98 verification record

- Date checked: 2026-09-29
- Package: Privoxy (non-caching filtering web proxy)
- Version: 3.0.19 stable, the official Windows "IPv4-only" build (privoxy-3.0.19-ipv4only.zip, 2011-12-30)
- License: GPL-2.0-or-later; includes PCRE (BSD-style old PCRE licence) and zlib (mgwz.dll)
- Recommendation: **3.0.19 ipv4only**. batch2.md guessed "3.0.x, start at 3.0.6". Every *standard* Windows build from 3.0.17 on imports `getaddrinfo`, `freeaddrinfo` and `getnameinfo` from WS2_32.DLL. Windows 98 does not have these, so those builds cannot start on 98. The Privoxy team published IPv4-only builds for exactly this problem. 3.0.19-ipv4only is the newest of them. Fallback: 3.0.16 stable (2010-02-21), the last standard build without IPv6, which comes with an NSIS installer.

## Windows 9x support evidence

- privoxy-3.0.19-ipv4Only-notes.txt, next to the zip on Privoxy's own mirror (https://www.privoxy.org/sf-download-mirror/Win32/3.0.19%20(stable)/, downloaded): "Release of Privoxy 3.0.19 built without support for IPv6. Hopefully this version will work on Win98". The notes list the two build changes: a NI_MAXSERV define in jbsockets.c and `--disable-ipv6-support` in winsetup/GNUmakefile.
- privoxy_setup_3.0.17_IPv6disabled.txt (same mirror, 3.0.17 folder, downloaded) explains why: "The procedure entry point freeaddrinfo could not be located in the dynamic link library WS2_32.dll" (reported on Windows 2000).
- FAQ inside the 3.0.19 zip (doc/faq/installation.html, read from the archive): "At present, Privoxy is known to run on Windows(95, 98, ME, 2000, XP, Vista) ...". The 3.0.18 Windows readme.txt on the mirror says the same.
- My own check (read-only PE import listing of privoxy.exe, nothing run):
  - 3.0.16 and 3.0.19-ipv4only import only WSOCK32.DLL for sockets, and only KERNEL32 functions that exist on 98 (e.g. IsDBCSLeadByteEx, GetSystemTimeAsFileTime, SetUnhandledExceptionFilter, InterlockedExchange). mgwz.dll (zlib) imports only basic KERNEL32 and msvcrt functions. Subsystem version 4.0.
  - 3.0.19 (standard), 3.0.21, 3.0.24 and 3.0.26 import WS2_32 getaddrinfo/freeaddrinfo/getnameinfo (XP and later).
  - 3.0.28 and 3.0.34 additionally import AddVectoredExceptionHandler (XP), and 3.0.34 GetTickCount64 (Vista).
  - The list of 98's exports I compared against is from memory, not from a 98 kernel32.dll (none available on this host).
- Windows 95: the FAQ names 95. privoxy.exe needs MSVCRT.DLL, which Windows 98 includes but the original Windows 95 does not (it arrives with IE 4 and many other programs; from memory), so the entry has a `Requires` line. It uses WSOCK32 (Winsock 1.1), so Winsock 2 is not needed.
- Not tested in the VM. The build is labelled "Hopefully this version will work on Win98", so it has to be tested before release.
- KernelEx: not needed. With KernelEx, newer standard builds might load, but no evidence was looked for.

## Download

- Official mirror: https://www.privoxy.org/sf-download-mirror/Win32/3.0.19%20(stable)/ (Privoxy's own copy of the SourceForge ijbswa file area)
- URL: https://www.privoxy.org/sf-download-mirror/Win32/3.0.19%20(stable)/privoxy-3.0.19-ipv4only.zip
- File: privoxy-3.0.19-ipv4only.zip, 728,027 bytes
- SHA-256: c4dfa26703b759a9d496a657f829a3cfaf493ee7099a833afed9e3bb3963609c
- Signature: privoxy-3.0.19-ipv4only.zip.asc (194 bytes, kept here). `gpg --verify`: **Good signature** from "Lee Rian", DSA key 0FAF26420C337AEE (fingerprint 0FF4 192E FEFC 31DF 5474 1F82 0FAF 2642 0C33 7AEE), made 2011-12-30. The key has since expired, which is normal for a 2011 signature. The key came from keyserver.ubuntu.com; Lee Rian is listed as a developer in the package's AUTHORS.txt. No web of trust was checked.
- No installer exists for the IPv4-only build, only this zip.
- Alternatives (not downloaded to the package): privoxy_3.0.16_setup.exe (NSIS, 482,239 bytes) and privoxy_setup_3.0.17_IPv6disabled.exe (485,730 bytes, no .asc).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\privoxy -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE.txt inside the zip is the unmodified GPL version 2. Source headers (e.g. jcc.c) say "either version 2 of the License, or (at your option) any later version".
- PCRE is built in (source in pcre/ of the tarball). Its old licence allows free redistribution and asks for a credit sentence and a reference to its FTP site in the documentation. The licence says GPL terms supersede where incompatible. The credit sentence is in LICENSE.TXT.
- mgwz.dll is zlib (zlib licence, permissive). Its source is not in the Privoxy tarball, and none is required.
- LICENSE.TXT here contains: a header with the notices above, the GPLv2 from the zip, and pcre/licence from the source tarball.
- Conditions: include the license, offer the corresponding source. The binary was built from 3.0.19 plus the two small changes described in the notes file, so the notes file is kept with the source.

## Matching source (hosted)

- URL: https://www.privoxy.org/sf-download-mirror/Sources/3.0.19%20(stable)/privoxy-3.0.19-stable-src.tar.gz
- File: src\privoxy-3.0.19-stable-src.tar.gz, 1,722,316 bytes
- SHA-256: 816e627b31caa3d9e71d0a8b83ac9ea7dcbeaaafef3c9a9c792696aa56255232
- Signature: src\privoxy-3.0.19-stable-src.tar.gz.asc: **Good signature** from "Fabian Keil <fk@fabiankeil.de>" (lead developer), DSA key 48C5521FBF2EA563 (fingerprint 8DA1 87F6 B624 9623 B98D 09BF 48C5 521F BF2E A563), made 2011-12-26, key since expired.
- Also in src\: privoxy-3.0.19-ipv4Only-notes.txt (779 bytes, SHA-256 e8346c58a1b5285f502c3071977026f15fab89afb0da6fed53c7fee641ded8d0), the build changes; announce.txt (24,224 bytes, SHA-256 727d252c462771eb9ec3e74ba8fa968e8b17ed9fa46d68be173eb226472bd26d), the release notes.
- Whether to host the .asc files is up to the catalog; the ENTRY lists only the tarball and the notes.

## Security

Source: NVD API 2.0, keyword "privoxy" (33 results).

Not applicable (other products or packaging): CVE-2006-3413, CVE-2007-6722, -6723, -6724 (Tor/Vidalia/TorK bundles), CVE-2019-3699 (openSUSE packaging), CVE-2021-44541 (HTTPS inspection, which 3.0.19 does not have).

Fixed after 3.0.19, so they probably apply (each "before 3.0.2x/3.0.3x" in NVD; not checked one by one against the 3.0.19 source):
- CVE-2015-1031 (CVSS2 7.5): use-after-free in list.c and other places, "unspecified impact". This is the worst.
- CVE-2013-2503: Proxy-Authenticate/Proxy-Authorization headers passed through (before 3.0.21).
- CVE-2015-1030, -1201, -1380, -1381, -1382; CVE-2016-1982, -1983: denial of service from crafted requests or responses.
- CVE-2020-35502, CVE-2021-20209, -20210, -20212, -20213, -20215, -20216, -20217, CVE-2021-20272 to -20276, CVE-2021-44540, -44542: crashes, assertion failures and memory leaks (DoS), several only through the CGI pages (http://config.privoxy.org/).
- CVE-2021-44543: XSS in the CGI error page, only when Privoxy serves the user manual itself.
- CVE-2021-20211 and -20214 concern client tags, a feature added after 3.0.19 (from memory), so probably not applicable.

Summary: about 25 known problems probably apply. All except CVE-2015-1031 (possible memory corruption) and CVE-2021-44543 (XSS) are denial of service. The default config listens on 127.0.0.1 only and disables remote toggling and action editing, which limits exposure to local browsers and the web pages they load.

## Install behaviour

- Plain zip, no installer, nothing in Add/Remove Programs, no silent switch needed.
- Layout (listed with .NET ZipFile): one top folder `privoxy-3.0.19-ipv4only/` with privoxy.exe (355,840), mgwz.dll (86,528), config.txt, *.action, *.filter, trust.txt, AUTHORS.txt, LICENSE.txt, README.txt, templates\ (37 files) and doc\ (HTML manuals). About 1,939 KB unpacked.
- config.txt: `confdir .`, `logdir .`, `logfile privoxy.log`, `listen-address 127.0.0.1:8118`, `enable-remote-toggle 0`, `enable-remote-http-toggle 0`, `enable-edit-actions 0`. Privoxy reads its files from its own folder and writes privoxy.log there, so Program Files is fine on 98.
- Beacon: `unzip {pf}\Privoxy strip 1`, a Start Menu shortcut to privoxy.exe (it starts as a tray icon), `Uninstall: files`. The user must then set the browser's HTTP proxy to 127.0.0.1 port 8118. The Windows service switches (--install) do not apply on 9x.
- Not done by Beacon: starting it with Windows. A shortcut in the Startup folder could be added later.
- Note: Privoxy only filters plain HTTP. For HTTPS it passes CONNECT through unfiltered, so it is useful with old browsers mostly on HTTP sites.

## Verification notes

- Opened or downloaded: Privoxy's mirror listings (Win32 3.0.12 to 3.0.34, Sources 3.0.19), the 3.0.19-ipv4only and 3.0.17-IPv6disabled notes, the 3.0.18 and 3.0.22 readmes, the ChangeLog (git, with the documented cookie), the user-manual installation page; the zips of 3.0.16, 3.0.19, 3.0.19-ipv4only, 3.0.21, 3.0.24, 3.0.26, 3.0.28 and 3.0.34 (to a temp folder, for the import check only); GPG signatures; NVD.
- Not verified: running on 95/98/ME; the exact list of 98 kernel32 exports (from memory); which CVEs really apply to 3.0.19 code.
