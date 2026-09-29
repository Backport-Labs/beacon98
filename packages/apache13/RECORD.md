# Apache HTTP Server 1.3.41 - Beacon 98 verification record

- Date checked: 2026-09-29
- Package: Apache HTTP Server (Apache Software Foundation)
- Version: 1.3.41 (released 2008-01-19 as a Win32 binary)
- License: Apache License 2.0 (not Apache License 1.1 as batch2.md guessed from memory), with bundled components under their own permissive terms and expat-lite under MPL 1.1
- Recommendation: 1.3.41. It is the last 1.3 release with an official Win32 binary: https://archive.apache.org/dist/httpd/binaries/win32/ lists 1.3.35, 1.3.37, 1.3.39 and 1.3.41 MSIs and nothing later. 1.3.42 (2010-02-03, the final 1.3 release) was published as source only. Its one fix, CVE-2010-0010, affects only 64-bit systems.

## Windows 9x support evidence

- htdocs/manual/windows.html.en in apache_1.3.41.tar.gz (read from the archive), "Requirements": "Apache 1.3 is designed to run on Windows NT 4.0 and Windows 2000. ... Apache may also run on Windows 95 and 98, but these have not been tested." and "'Winsock2' is required for Apache 1.3.7 and later. If running on Windows 95, the 'Winsock2' upgrade must be installed before Apache will run."
- The same page: "You must have the Microsoft Installer version 1.10 installed on your PC before you can install the Apache runtime distributions. Windows 2000 and Windows ME are both delivered with the Microsoft Installer support, others will need to download it." Also: "The Close menu item and close (X) button also work on Windows 95/98 as of Apache version 1.3.15."
- src/CHANGES shows that 9x was actively supported in the 1.3 series. 1.3.13: "Add 'services' for Windows 95 and 98, including install/uninstall". 1.3.15: "Added Win9xConHook.dll ... The close button on Win9x now works". 1.3.18: "Apache on Win9x now ensures the service is stopped before removal."
- The 1.3.41 MSI itself handles 9x: its dialogs test `Version9X`, and it installs Win9xConHook.dll. Inspected with the Windows Installer COM API, read only.
- My own check (PE import tables of every executable in the MSI's cab, read only): subsystem 4.0 everywhere. ApacheCore.dll imports WS2_32 (WSASocketA, WSADuplicateSocketA and others by ordinal), which is Winsock 2: present on 98 and ME, an update on 95. It also imports the ADVAPI32 service functions (CreateServiceA, StartServiceCtrlDispatcherA...). As far as I know (from memory), those exist on 98 as stubs, which is why Apache's own 9x "service" code works there.
- Windows 95: needs the Winsock 2 update and Windows Installer. ME: MSI is built in, and ME is not named in the manual. The Windows Installer requirement is 1.1: summary information page count (schema) = 110.
- KernelEx: not needed. Not tested in the VM.

## Download

- Official archive: https://archive.apache.org/dist/httpd/binaries/win32/
- URL: https://archive.apache.org/dist/httpd/binaries/win32/apache_1.3.41-win32-x86-no_src.msi
- File: apache_1.3.41-win32-x86-no_src.msi, 2,160,128 bytes
- SHA-256: 5ce8f31d36e09c006f31422af6825cf6bb6e7bc9f6c03f0ce4f2a6d58cd3ba11
- Published checksum: apache_1.3.41-win32-x86-no_src.msi.md5 says `456ef3b2000a713ab0480e1b35679d2c`: MATCH.
- Signature: apache_1.3.41-win32-x86-no_src.msi.asc is made by RSA key F713A87910FDE075. The httpd KEYS file lists it as "pub 2048/10FDE075 2000/10/09 William A. Rowe, Jr. <wrowe@apache.org>". But gpg (Git for Windows' gpg 2.x) did not import that key from KEYS (probably an old PGP 2 / v3 key, which modern gpg rejects; my inference), and keyserver.ubuntu.com has no copy, so the signature was **not checked**. The .asc and .md5 are kept in the folder.
- Alternative: apache_1.3.41-win32-x86-src.msi (3.1 MB, same runtime plus the source).
- Only a Windows Installer package exists; the older InstallShield .exe builds stopped at 1.3.17.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\apache13 -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- LICENSE in apache_1.3.41.tar.gz: Apache License, Version 2.0, followed by "APACHE HTTP SERVER SUBCOMPONENTS": MD5 (RSA/UIUC/CMU/Bellcore notices), expat-lite (James Clark, "subject to the Mozilla Public License"), the Henry Spencer regex library, expat (Thai Open Source Software Center), mod_mime_magic (Cisco), and others. NOTICE lists the required attributions.
- ALv2 s.4 allows redistribution of unmodified copies if the license and the NOTICE text are included. LICENSE.TXT here contains both. The MSI also installs them.
- Source: not required by ALv2. The MPL 1.1 files (expat-lite) must stay available as source, so the tarball is hosted anyway.
- The MSI contains InstallShield helper binaries (ISSELFREG.DLL), an awk.exe used by the installer custom actions, and the Microsoft VC runtime merge module (msvcrt.dll, "Global_VC_CRT"). These are the vendor's redistributables inside the official, unmodified installer; we distribute that file as-is. None has source in the tarball (none needs one).

## Matching source (hosted)

- URL: https://archive.apache.org/dist/httpd/apache_1.3.41.tar.gz
- File: src\apache_1.3.41.tar.gz, 2,483,180 bytes
- SHA-256: 4b016d3998f822af7a1a515e9626590f5473a4dd5c3e8466f20a6a86a2a63adc
- MD5 f7f00b635243f03a787ca9f4d4c85651: MATCH with apache_1.3.41.tar.gz.md5.
- Signature apache_1.3.41.tar.gz.asc: **Good signature** from "Jim Jagielski <jim@apache.org>" (DSA key 8B3A601F08C975E5, fingerprint 8B39 757B 1D8A 994D F243 3ED5 8B3A 601F 08C9 75E5; key from the httpd KEYS file), made 2008-01-10. No web of trust.
- The archive's files are dated 2009-10-03 on archive.apache.org (re-upload), but the signature date is 2008.

## Security

Sources: https://httpd.apache.org/security/vulnerabilities_13.html (opened) and NVD.
- The ASF page: "Apache httpd 1.3 has had no new releases since 2010 and should not be used. This page only lists security issues that occurred before March 2010. Subsequent issues may have affected 1.3 but will not be investigated or listed here."
- Listed after 1.3.41: only CVE-2010-0010 (mod_proxy, 64-bit systems only), which does not apply to this 32-bit build.
- NVD (cpeName http_server 1.3.41) returns 58 matches, mostly 2.x-only or third-party modules because the CPE ranges are broad. Those that do apply to 1.3.41:
  - CVE-2011-3368 and CVE-2011-4317: mod_proxy with RewriteRule/ProxyPassMatch can be used to reach internal hosts (1.3.x through 1.3.42, never fixed in 1.3). Only matters if mod_proxy is enabled; it is off by default.
  - CVE-2007-6750: Slowloris denial of service, all 1.x.
- Unknown: whether later 2.x core bugs (e.g. CVE-2006-20001, the If: header byte write) also exist in 1.3 code. The ASF no longer investigates.
- Summary: 3 known issues apply (worst: CVE-2011-3368, CVSS2 5.0, only with mod_proxy rewrite configurations). The main risk is that 1.3 is unmaintained. It should be used only on a LAN or for local development, never exposed to the internet. The Windows 9x build also has no SSL module.

## Install behaviour

- Installer: Windows Installer package (summary: "InstallShield 11.5 - Professional Edition", schema 110 = MSI 1.1). Needs Windows Installer 1.1 or later on 95/98 (`Requires: msi 1.1`). Built into ME.
- ProductName / Add/Remove Programs name: "Apache HTTP Server 1.3.41" (Property table). ProductCode {5D29A4EF-A57F-4F47-89F8-4EB3C5302A53}, UpgradeCode {CF51C9DD-5656-45B6-A6BE-4D37F00A21F0}.
- Default folder: `[ProgramFilesFolder]Apache Group\Apache` (Directory table: INSTALLDIR = "Apache Group", APACHEDIR = "Apache").
- Silent install: standard msiexec (`/qb` or `/qn`). The RewriteConfFiles custom action writes httpd.conf from the properties SERVERDOMAIN, SERVERNAME and SERVERADMIN, which are normally set in the dialog, so they must be passed on the command line. If ALLUSERS is set, the ApacheAdmin component installs and starts the Apache "service" (SelfInstallService, SelfStartService: `Apache.exe -i -n Apache` / `-k start`). Without ALLUSERS (the default, since no ALLUSERS property is defined), the ApacheNonAdmin component is used and Apache is started by hand (Start Menu shortcut or `Apache.exe`). rewriteconf.awk (read from the cab) only replaces @@ServerRoot@@, @@Domain@@, @@ServerName@@ and @@ServerAdmin@@. The template httpd.conf has `Port 80` and no Listen/BindAddress line, so in both modes Apache listens on port 80 on **all** network interfaces. It is reachable from the LAN unless the user adds `BindAddress 127.0.0.1` to conf\httpd.conf. Existing httpd.conf/access.conf/srm.conf are not overwritten on reinstall (duplicateconf.awk).
- Suggested catalog line: `Install: msi SERVERNAME=localhost SERVERDOMAIN=localdomain SERVERADMIN=admin@localhost`. Not tested.
- Uninstall: MSI, registered under the ProductCode, shown as "Apache HTTP Server 1.3.41".

## Verification notes

- Opened or downloaded: the archive.apache.org win32 and httpd listings, the MSI with .md5 and .asc, the tarball with .md5 and .asc, the KEYS file, the 1.3 vulnerabilities page, and NVD. I read the MSI's Property, Directory, Feature, Component, CustomAction, InstallExecuteSequence and ControlEvent tables through the Windows Installer COM object (opened read-only; nothing installed). The cab was extracted to a temp folder for the import check only.
- Not verified: running on 95/98/ME; the MSI's PGP signature; the port chosen by a silent non-admin install.
