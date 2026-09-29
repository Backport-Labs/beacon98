# Python 2.5.4 - Beacon 98 pilot record

- Date checked: 2026-09-28
- Package: Python (CPython), Windows x86 installer
- Version: 2.5.4 (released 2008-12-23)
- Recommendation: 2.5.4. Later 2.5.5 (2010-01-31) and 2.5.6 (2011-05-26, final 2.5) are SOURCE-ONLY security releases; python.org ships no Windows binary for them. Building 2.5.6 for 9x ourselves is possible in principle (VS 2003 toolchain) but would be an unofficial build.

## Windows 9x support evidence (verified by opening)

- PEP 11 (https://peps.python.org/pep-0011/, source https://github.com/python/peps/blob/main/peps/pep-0011.rst):
  "Name: Win9x, WinME, NT4 / Unsupported in: Python 2.6 (warning in 2.5 installer) / Code removed in: Python 2.6"
- The 2.5.4 installer itself carries that warning: Tools/msi/msi.py in the 2.5.4 source shows on the exit dialog, only on 9x (condition Version9X):
  "Warning: Python 2.5.x is the last Python release for Windows 9x."
- 2.5.4 release page (https://www.python.org/download/releases/2.5.4/): "This is the last bugfix release of Python 2.5 ... no binaries or documentation updates will be provided in future releases of Python 2.5."
- 2.5.6 release page (https://www.python.org/download/releases/2.5.6/): "This is a source-only release that only includes security fixes. The last full bug-fix release of Python 2.5 was Python 2.5.4." python.org/ftp/python/2.5.5/ and /2.5.6/ contain only .tgz/.tar.bz2 (verified listing).
- Windows 95 separately: PEP 11 groups "Win9x" together; the 2.5.4 page says Windows Installer can be obtained "for Windows 95, 98 and Me". No separate Win95 test statement found. Not tested.

## Windows Installer requirement

- The 2.5.4 page states: "To use these installers, the Windows system must support Microsoft Installer 2.0 ... If your machine lacks Microsoft Installer, you'll have to download it freely from Microsoft for Windows 95, 98 and Me". msi.py confirms the database uses "the installer 2.0 database schema".
- So on Windows 95/98 (which do not ship Windows Installer 2.0 by default - general knowledge, not verified here), the user must install Windows Installer 2.0 (InstMsiA.exe) first.
- Windows Installer is a Microsoft component. No redistribution licence was verified; Beacon 98 must NOT host it. Treat it as a prerequisite the user obtains themselves.

## Download

- URL: https://www.python.org/ftp/python/2.5.4/python-2.5.4.msi
- File: python-2.5.4.msi, 11,323,392 bytes
- SHA-256: 485e325c0189ae06ea4b0675d2502f8ee82ce301bd2e5aa1b5387cd3cdf650bd
- Published checksum: release page lists MD5 b4bbaf5a24f7f0f5389706d768b4d210 (11323392 bytes). Computed MD5 b4bbaf5a24f7f0f5389706d768b4d210 - MATCH.
- GPG: python-2.5.4.msi.asc - "Good signature" from Martin v. Loewis, DSA key 6AF053F07D9DC8D2, fingerprint CBC5 4797 8A39 64D1 4B9A B36A 6AF0 53F0 7D9D C8D2, signed 2008-12-23. Key fetched from keyserver.ubuntu.com; python.org's PGP page (https://www.python.org/downloads/metadata/pgp/) lists Martin v. Loewis key id 6AF0 53F0 7D9D C8D2 for end-of-life releases (64-bit id match; full fingerprint not shown on that page).
- Authenticode: MSI signed by "Python Software Foundation" (VeriSign Class 3 Code Signing 2004 CA, cert valid 2008-05-12 to 2011-05-13); Windows reports "Signature verified".
- Alternatives (not for 9x): python-2.5.4.amd64.msi, python-2.5.4.ia64.msi; Python25.chm docs.
- Note: the new-style file table on the 2.5.4 page shows an odd MD5/size for Python-2.5.4.tgz ("47.8 MB", f58e4d4c...) that disagrees with the classic list (ad47b23778f64edadaaa8b5534986eed, 11604497 bytes). Not relevant to the files downloaded here.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\pilot\python -DisableRemediation` on 2026-09-28
(engine 4.18.26080.4, signatures 1.459.442.0): "found no threats" (includes source-deps\).

## License

- Python: PSF License Agreement for Python 2.5.4 (plus the historical BeOpen, CNRI and CWI licences). LICENSE.TXT here is LICENSE.txt extracted from the MSI's own cabinet (what the installer installs), 33,061 bytes.
- That same file also contains the terms of the bundled third-party components (verified sections "This copy of Python includes a copy of ..."):
  - bzip2 1.0.3 (BSD-style) - bz2.pyd reports "1.0.3, 15-Feb-2005"
  - Berkeley DB 4.4.20 (Sleepycat licence) - _bsddb.pyd reports "Berkeley DB 4.4.20"
  - OpenSSL 0.9.8a (OpenSSL + SSLeay dual licence; advertising clause) - _ssl.pyd reports "OpenSSL 0.9.8a 11 Oct 2005"
  - Tcl 8.4.12 and Tk 8.4.12 (BSD-style Tcl licence)
- Also bundled but NOT covered in LICENSE.txt: sqlite3.dll 3.3.4 (public domain), zlib (inside python25.dll, zlib licence), and msvcr71.dll (Microsoft Visual C++ .NET 2003 runtime, Microsoft redistributable terms; ships inside PSF's signed MSI).
- Redistribution of the unmodified MSI: permitted by PSF licence (keep copyright notice and licence). Conditions:
  - PSF/BeOpen/CNRI: retain the licence and copyright notices.
  - OpenSSL: acknowledgement notices must be retained ("This product includes software developed by the OpenSSL Project ...").
  - Sleepycat (Berkeley DB) clause 3: "Redistributions in any form must be accompanied by information on how to obtain complete source code for the DB software and any accompanying software that uses the DB software" - i.e. we must point to source for Berkeley DB and for Python. Sources downloaded below.
  - msvcr71.dll: redistributing PSF's unmodified MSI is how PSF itself distributes it; whether a third party may re-host it is an open legal question (Microsoft terms not reviewed).

## Source

- Python: https://www.python.org/ftp/python/2.5.4/Python-2.5.4.tar.bz2
  - File Python-2.5.4.tar.bz2, 9,821,313 bytes, SHA-256 bc8d896a2bfe5523ba93b8d89b71017b74e8e6cb21dc676a0ccff668c8780110
  - Published MD5 394a5f56a5ce811fb0f023197ec0833e - MATCH; .asc Good signature (same key, 2008-12-23).
- Berkeley DB (Sleepycat clause 3): https://download.oracle.com/berkeley-db/db-4.4.20.NC.tar.gz (PCbuild/readme.txt says the Python build uses db-4.4.20.NC renamed to db-4.4.20)
  - source-deps\db-4.4.20.NC.tar.gz, 7,913,912 bytes, SHA-256 2c2d873de7d471ba394d62f66d83c79688e0711b38bf07a8678e0064b79f2dbb (no published checksum found to compare)
- OpenSSL 0.9.8a (courtesy, not strictly required by its licence): https://www.openssl.org/source/old/0.9.x/openssl-0.9.8a.tar.gz
  - source-deps\openssl-0.9.8a.tar.gz, 3,271,435 bytes, SHA-256 30f8f61fb1316f4fb51410c740b4879b8e26b417c8d870e486144b10b8041c73
  - Published .md5 1d16c727c10185e4d694f87f5e424ee1 - MATCH; .sha1 2aaba0f728179370fb3e86b43209205bc6c06a3a - MATCH.
- Version sources: Tools/buildbot/external.bat in 2.5.4 (bzip2-1.0.3, db-4.4.20, openssl-0.9.8a, tcl8.4.12, tk8.4.12, sqlite-source-3.3.4 from svn.python.org/projects/external, which no longer exists) and strings in the shipped binaries.

## Security

- Fixed only in source-only 2.5.5/2.5.6 (so present in the 2.5.4 binary), from Misc/NEWS at v2.5.6:
  CVE-2009-3560 and CVE-2009-3720 (expat DoS), CVE-2010-1634 and CVE-2010-2089 (audioop), CVE-2011-1521 (urllib/urllib2 file:// redirect), SimpleHTTPServer XSS (issue 11442).
- NVD: 62 CVEs match cpe python:2.5.4; 6 with CVSS >= 9, e.g. CVE-2016-5636 (zipimport integer overflow, 10.0), CVE-2007-4559 (tarfile path traversal, 9.8), CVE-2017-1000158 (PyString_DecodeEscape overflow, 9.8), CVE-2019-9948 (urllib local_file:, 9.1). Also CVE-2014-1912 (socket.recvfrom_into buffer overflow, "Python 2.5 before 2.7.7", RCE, CVSS v2 7.5).
- Bundled OpenSSL 0.9.8a: NVD lists 89 CVEs (7 with CVSS >= 9), e.g. CVE-2006-3738 (SSL_get_shared_ciphers overflow, 10.0), CVE-2009-3245 (10.0), CVE-2009-3555 (TLS renegotiation), CVE-2014-0224 (CCS injection). Also no TLS 1.1/1.2, so _ssl is effectively useless and unsafe for modern HTTPS.
- Bundled bzip2 1.0.3: CVE-2010-0405 (BZ2_decompress integer overflow, before 1.0.6).
- Worst overall: CVE-2016-5636 (CPython zipimport, 10.0) / CVE-2006-3738 (bundled OpenSSL, 10.0).

## Install behaviour

- Installer type: Windows Installer (MSI, schema 2.0), built with Python's own msilib.
- Silent install (documented at https://www.python.org/download/releases/2.5/msi/): `msiexec /i python-2.5.4.msi /qn` (or /qb, /qb!); `TARGETDIR=C:\Python25`, `ALLUSERS=1`, `ADDLOCAL=...` for features. msi.py notes that on Windows 9x the ALLUSERS dialog is skipped (Win9x has no per-user/all-users distinction).
- Default folder: `[WindowsVolume]Python25` (C:\Python25).
- Uninstaller: yes, standard MSI registration in Add/Remove Programs ("Python 2.5.4").
- Prerequisite on 9x: Windows Installer 2.0 (not hostable, see above).
- Side effects: .py/.pyw/.pyc file associations, python25.dll placed in the system directory on Windows 9x (msi.py: sys32cond = "(Windows9x or (Privileged and ALLUSERS))"), Start menu group, optional byte-compilation of the standard library at install time.

## Verification notes

- Verified by opening: PEP 11 source, python.org 2.5.4/2.5.6 release pages, FTP listings, MSI contents (LICENSE.txt, bundled DLL versions), msi.py, NEWS, GPG and Authenticode signatures, NVD API.
- Not verified: Windows 95 operation (msvcr71.dll on Win95 in particular); whether plain Windows 98/98 SE already has any Windows Installer version; Microsoft redistribution terms for msvcr71.dll and InstMsiA.exe.
