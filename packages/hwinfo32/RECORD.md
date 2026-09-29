# HWiNFO32 8.52 - Beacon 98 record

- Date checked: 2026-09-29
- Package: HWiNFO32 ("legacy" 32-bit edition of HWiNFO), Martin Malik, REALiX s.r.o., Malacky, Slovakia
- Version: 8.52 (HWiNFO32.exe file version 8.52-6060, files dated 2026-08-25). This is the current release, not an old one:
  REALiX still builds HWiNFO32 for "Windows 95 and later".
- License: HWiNFO EULA; HWiNFO32 is freeware for non-commercial and commercial use. Redistribution is not granted.
- Recommendation: list as **external** (publisher's server and its official mirror). Do not host.

## Windows 9x support evidence

- https://www.hwinfo.com/download/ (opened 2026-09-29 with a browser User-Agent): "Portable for Windows 95 and later x86, x64 or
  ARM64 platform Version 8.52 ... Portable package containing HWiNFO(R) 32, HWiNFO(R) 64 and HWiNFO(R) ARM64. ...
  HWiNFO(R) 32 (legacy) is FREEWARE."
- https://www.hwinfo.com/licenses/ (opened): the HWiNFO 32 column gives "Operating system: Windows 95 and later (32/64-bit)".
- https://www.hwinfo.com/version-history/ (opened) contains the line "Legacy HWiNFO32 available in the portable package only."
- HWiNFO32.exe is a 32-bit PE with subsystem version 4.0 (checked from the header, not run).
- ME is not named separately; "Windows 95 and later" covers it. Not tested on any 9x system (no VM interaction).

## Download

The file name contains the version (hwi_852.zip). When REALiX publishes 8.54 or later, the 8.52 link may disappear from both
servers and this entry will need a new version, size and hash. Tell the catalog maintainer.

- Publisher: https://www.hwinfo.com/files/hwi_852.zip ("Local (U.S.)" link on the download page)
  - `curl.exe -sS -I -L` with curl's default User-Agent: **403 Forbidden** (bot protection); with a browser User-Agent: 200.
    http:// redirects (301) to https. Beacon's downloader must send a browser-like User-Agent for this location, or it will fail.
- Official mirror: https://www.sac.sk/download/utildiag/hwi_852.zip ("SAC ftp (SK)" link on the hwinfo.com download page, so
  authorized by the publisher)
  - https: 200, Content-Length 20828120, with any User-Agent. http:// redirects (301) to https.
  - Downloaded from here; same size as the hwinfo.com HEAD answer. The hwinfo.com copy was not downloaded separately, so byte
    identity of both copies is assumed from equal size and name only.
- File: hwi_852.zip, 20,828,120 bytes (plain zip)
- SHA-256: 0ce80064422e128a0f4257733c41e02970b5997a04361accc1f7f2f4b059f1ed
- MD5: f139c3c2bcb232431712362b48bda3b9
- Published checksum: none on the download page.
- Contents (listed with .NET ZipFile): `HWiNFO32.exe` (3,402,728), `HWiNFO64.exe` (10,895,848), `HWiNFO_ARM64.exe` (16,020,464). No folders.
- Authenticode: all three exes Valid, signer "CN=REALiX, s.r.o., O=REALiX, s.r.o., L=Malacky, C=SK" (EV). Windows 9x does not check it.
- Other downloads: the "dAppCDN" link and the beta hwi_853_6080.zip were not examined.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\hwinfo32 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- LICENSE.TXT: transcription of the EULA at https://www.hwinfo.com/files/license.pdf (the original PDF is kept as LICENSE.PDF,
  SHA-256 cf7c40d9cb2fbf6af2bcc69622ad84c9e8e11635c07607d9baff356d68de9075). The zip has no license file.
- Type: freeware. "HWiNFO(R) 32, HWiNFO for DOS are freeware. These products are allowed to be used free in both non-commercial and
  commercial environments."
- Redistribution: the EULA grants none, and says "Embedding or bundling HWiNFO(R) in 3rd party software is allowed only with explicit
  approval of the Licensor." (Only the DOS version is called "free distributable as-is" on the download page.) So: external.
- No trial, expiry or nag for HWiNFO32. (The 12-hour shared-memory limit applies to non-Pro HWiNFO64/ARM64 only.)

## Security

NVD keyword search "HWiNFO" (2026-09-29): 2 results, CVE-2018-8060 and CVE-2018-8061, both in the "HWiNFO AMD64 Kernel driver
version 8.98 and lower" (IOCTL handling, physical memory access). They concern the 64-bit NT kernel driver, not HWiNFO32 on
Windows 9x. No known CVE for HWiNFO32 8.52.

## Install behaviour

- Plain zip, no installer. Beacon: `unzip {pf}\HWiNFO32`, shortcut to `{dir}\HWiNFO32.exe`. The 64-bit and ARM64 exes are unpacked
  too (about 26 MB unused on 9x); Beacon cannot unpack a single file.
- The program may load a driver at run time (unknown for 9x; not run). Settings: HWiNFO32.INI next to the exe (usual for the
  portable edition; not verified).
- Uninstall: `files`.

## Verification notes

- Verified by opening/downloading: download, licenses and version-history pages, license.pdf, the zip (hash, listing, PE header,
  version resource, signatures).
- Not verified: running on 95/98/ME; whether current 8.52 actually still works on 9x hardware (the publisher states it does).
