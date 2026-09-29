# PHP 5.2.17 - Beacon 98 verification record

- Date checked: 2026-09-29
- Package: PHP (The PHP Group)
- Version: 5.2.17 (Windows build dated 2011-01-06, published 2011-03-22), thread-safe VC6 x86
- License: PHP License 3.01 for PHP itself. The Windows zip also bundles third-party DLLs, some of them proprietary with no redistribution terms included.
- **Result: NOT LISTABLE as things stand.** 5.2.17 is confirmed as the last PHP for 98/ME, and PHP's own license allows redistribution. But the official Windows archive (and, very probably, the MSI) contains ntwdblib.dll (Microsoft SQL Server DB-Library), fdftk.dll (Adobe FDF Toolkit) and msql.dll (Hughes Technologies mini SQL client). The archive gives no license or redistribution grant for these files, so we cannot be certain that hosting it is legal. It also cannot be `external`: windows.php.net and museum.php.net answer plain HTTP with a 301 redirect to HTTPS.
- Work stopped after the evidence, download, Defender scan, license and security steps. No source archive was downloaded.

## Windows 9x support evidence

- https://wiki.php.net/internals/windows/releasenotes (opened), "Release Notes for Windows Binaries 5.3.0-alpha": "The PHP 5.3.0 branch will only support Windows 2000, XP, Server 2003, Vista, and Server 2008. Support has been dropped for Windows 98, ME, and NT." So the 5.2 branch is the last, and 5.2.17 is its final release. The 5.2.17 build in the archive is the newest 5.2 file on https://windows.php.net/downloads/releases/archives/.
- install.txt inside php-5.2.17-Win32-VC6-x86.zip (read from the archive): "This section applies to Windows 98/Me and Windows NT/2000/XP/2003. ... Windows 95 is no longer supported as of PHP 4.3.0." It also gives 98/Me-specific steps (autoexec.bat PATH, browscap path on 9x/Me).
- My own check (import tables, read only): php5ts.dll, php.exe, php-cgi.exe and php5apache.dll (the Apache 1.3 module) are subsystem 4.0 VC6 builds. php5ts.dll imports KERNEL32 InterlockedCompareExchange and GetFileAttributesExA, which exist on 98 but not on 95 (from memory). It also imports ODBC32, OLEAUT32 and WS2_32 (Winsock 2). php-cgi.exe imports NT security functions (InitializeSid, InitializeAcl, ImpersonateNamedPipeClient); I believe these are stubs on 98, but that is not verified.
- Windows 95: not supported (install.txt). ME: supported. KernelEx: not needed. Not tested.

## Download

- Official archive: https://windows.php.net/downloads/releases/archives/
- URL: https://windows.php.net/downloads/releases/archives/php-5.2.17-Win32-VC6-x86.zip
- File: php-5.2.17-Win32-VC6-x86.zip, 10,548,629 bytes
- SHA-256: 18951f4a6282b5a34afa11e07249d336169bc06a98dba88bd5cff72109105ca0
- MD5 f4e290e3eb4ef6e6453fbe5fef03eb06, SHA-1 23e1cf2f6e1bf64585ae921462340e5748fcc939
- Published checksum: none found for the Windows archive build. The archive folder lists no hash files; php.net's release pages carry hashes for the source tarballs, which were not checked.
- Others in the same folder (not downloaded): php-5.2.17-Win32-VC6-x86.msi (20 MB; would need Windows Installer), the nts zip and msi, and php-5.2.17-src.zip.
- External test: `curl.exe -sS -I --http1.0 http://windows.php.net/downloads/releases/archives/php-5.2.17-Win32-VC6-x86.zip` gives 301 to https://..., and so does museum.php.net. So external is not possible.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\php52 -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.462.0): "found no threats".

## License

- license.txt in the zip: "The PHP License, version 3.01. Copyright (c) 1999 - 2010 The PHP Group." It is BSD-style: binary redistribution is allowed with the notice. Condition 4 says derived products may not be called "PHP" without permission. Saved as LICENSE.TXT.
- **The blocker: bundled third-party DLLs** (zip root; snapshot.txt names the extension that needs each one):

| File | Used by | Origin / license | Verdict |
|---|---|---|---|
| ntwdblib.dll | php_mssql, php_pdo_mssql | Microsoft SQL Server DB-Library client, proprietary | no redistribution grant included |
| fdftk.dll | php_fdf | Adobe FDF Toolkit, proprietary | no redistribution grant included |
| msql.dll | php_msql | Hughes Technologies mSQL client, proprietary (mSQL licence; from memory) | no redistribution grant included |
| gds32.dll | php_interbase, php_pdo_firebird | Firebird/InterBase client (IPL/IDPL, open source; from memory) | probably fine, source not with us |
| libmysql.dll | php_mysql, php_mysqli, php_pdo_mysql | MySQL client, GPL with FOSS exception (from memory) | source would be needed |
| libeay32.dll, ssleay32.dll | openssl, curl, ldap | OpenSSL 0.9.8 | fine (OpenSSL licence) |
| libpq.dll | pgsql | PostgreSQL (BSD-style) | fine |
| libmcrypt.dll, libmhash.dll, aspell-15.dll | mcrypt, mhash, pspell | LGPL | source would be needed |

  The zip includes no license texts for any of these (apart from extras/openssl/README-SSL.txt).
- Options for the catalog owner (a decision, not something I can resolve):
  1. Leave PHP out (recommended under the current rule of certain legality).
  2. Change the policy to allow a Backport Labs repack of the official zip without ntwdblib.dll, fdftk.dll and msql.dll (and their php_mssql/php_fdf/php_msql extensions). The PHP License allows redistribution with or without modification, but it would no longer be "the unmodified files", and sources for the LGPL/GPL DLLs (libmysql, libmcrypt, libmhash, aspell) would still have to be found.
  3. PHP 4.4.9 probably has the same bundle (not checked).

## Security

NVD API 2.0, cpeName php 5.2.17: 259 matches. Worst: CVE-2012-2376 (com_print_typeinfo buffer overflow on Windows, CVSS2 10.0), CVE-2011-3268 (crypt() buffer overflow, 10.0), and several 10.0 SOAP / unserialize issues (CVE-2015-4599 to -4602). The 5.2 branch has been end-of-life since January 2011. Not checked one by one.

## Install behaviour (for reference)

- The zip has no top folder. php.exe, php-cgi.exe, php5ts.dll and the SAPI modules (php5apache.dll for Apache 1.3) are at the root, with ext\ (extensions), extras\, dev\, PEAR\ (go-pear), install.txt, php.ini-dist and php.ini-recommended. 194 entries.
- The documented manual setup: unzip to C:\PHP, copy php.ini-recommended to php.ini, add C:\PHP to PATH in autoexec.bat on 98/Me, and for Apache 1.3 add `LoadModule php5_module "C:/php/php5apache.dll"`, `AddModule mod_php5.c` and `AddType application/x-httpd-php .php`.
- MSI: Windows Installer package, not inspected.

## Verification notes

- Opened or downloaded: the windows.php.net release notes wiki, the windows.php.net archives listing, the 5.2.17 zip (install.txt, snapshot.txt and license.txt read from it; four binaries extracted to a temp folder for the import check only), the HTTP test of both PHP servers, and NVD.
- Not verified: the MSI contents; the licenses of the bundled DLLs (no texts included); running on 98/ME.
