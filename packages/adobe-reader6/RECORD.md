# Adobe Reader 6.0 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Adobe Reader (Adobe Systems Incorporated)
- Version: 6.0 (English full installer, folder `6.x/6.0/enu` on Adobe's server)
- License: proprietary, free of charge (Adobe Reader EULA). Not redistributable by us: `external`.
- Recommendation: 6.0 full installer, the only 6.x installer found on Adobe's server. The csv row names 6.0.6 (msfn-98se); 6.0.x updates were not found (guessed update file names returned 404, and the server gives no directory listing). Adobe Reader 7.0 requires Windows 2000/XP (evidence below), so 6.x is the last line for 98 SE/ME.

## Windows 9x support evidence

- Adobe's Reader system requirements page, 2003 copy (http://www.adobe.com/products/acrobat/acrrsystemreqs.html, read at the Internet Archive, id_ snapshot 2003-12): "Adobe Reader 6.0.1 system requirements Windows Intel Pentium processor Microsoft Windows 98 Second Edition, Windows Millennium Edition, Windows NT 4.0 with Service Pack 6, Windows 2000 with Service Pack 2, Windows XP Professional or Home Edition, Windows XP Tablet PC Edition 32MB of RAM (64MB recommended) 60MB of available hard-disk space Internet Explorer 5.01, 5.5, 6.0, or 6.1".
- Same page, 2004 copy: "Adobe Reader 7.0 system requirements Windows ... Microsoft Windows 2000 with Service Pack 2, Windows XP Professional or Home Edition, or Windows XP Tablet PC Edition". So 7.0 dropped 98/ME.
- The requirements above are for 6.0.1; the file here is from the 6.0 folder. Its payload is dated 2003-08-01 (7-Zip listing) and Last-Modified is 2003-11-03, so it may be a re-released 6.0 build; the exact build number inside could not be read without running the installer. Windows 95 and Windows 98 first edition are not supported.
- Not tested on 98 SE/ME here.

## Download

- URL (http and https both answer 200, same Content-Length 16706160, Last-Modified Mon, 03 Nov 2003 23:09:32 GMT, via `curl.exe -sS -I -L`):
  - http://ardownload.adobe.com/pub/adobe/reader/win/6.x/6.0/enu/AdbeRdr60_enu_full.exe
  - https://ardownload.adobe.com/pub/adobe/reader/win/6.x/6.0/enu/AdbeRdr60_enu_full.exe
  - http://ardownload2.adobe.com/pub/adobe/reader/win/6.x/6.0/enu/AdbeRdr60_enu_full.exe
  - https://ardownload2.adobe.com/pub/adobe/reader/win/6.x/6.0/enu/AdbeRdr60_enu_full.exe (downloaded from here)
- Directory URLs give 403 (no listing); ftp.adobe.com redirects to download.adobe.com, which gives 403.
- File: AdbeRdr60_enu_full.exe, 16,706,160 bytes
- SHA-256: dba7eb0e39e54d427a7fdb86b84cb563e8a40f1c187179313549ca4761437db2
- Published checksum: none found.
- Authenticode: Valid. Signer CN="Adobe Systems, Incorporated", OU=Acrobat Engineering (certificate expired 2004-10-31, but the signature carries a VeriSign Time Stamping Service countersignature, so it still verifies).

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\adobe-reader6 -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- Adobe Reader EULA (proprietary, free of charge). The 6.0 EULA text is inside the installer's compressed package and could not be extracted without running it; Adobe's archive of old terms (https://www.adobe.com/legal/licenses-terms/licenses-terms-archive.html) lists Reader terms only from 2015 on. LICENSE.TXT explains this and quotes the distribution policy.
- Redistribution: not allowed for us. Adobe's "Distributing Adobe Reader" page, 2004 copy (http://www.adobe.com/products/acrobat/distribute.html via the Internet Archive): "Third-party Web sites are required to link directly to Adobe.com for the download of Adobe Reader software. Hosting the software independently is not permitted." CD/intranet distribution needed a separate Adobe Reader Distribution Agreement.
- No trial, no expiry. Free product.

## Security

- NVD API 2.0, cpeName cpe:2.3:a:adobe:acrobat_reader:6.0: 182 CVEs match (many through version ranges; not each one checked against 6.0 code). Several scored 10.0, e.g. CVE-2008-2641, CVE-2009-3954, CVE-2009-3958, CVE-2009-3959 (crafted PDF leading to code execution). ENTRY.TXT carries a Warning.

## Install behaviour

- Installer type: Netopsystems FEAD self-extractor ("Netopsystems FEAD Recomposer" 1.3.9.0) wrapping Adobe's setup. 7-Zip cannot open the payload. Adobe Reader 6 setup is Windows Installer based (not verified from this file); if so, Windows Installer must be present or be installed by the setup.
- Silent switch: not verified (no documentation reachable). Beacon runs it interactively (`Install: exe`).
- Default folder: unknown (typically under Program Files\Adobe; not verified).
- Add/Remove Programs name: unknown. `Uninstall: registry Adobe Reader 6.0` in ENTRY.TXT is a guess to check on a test machine.

## Verification notes

- Verified by opening/downloading: HTTP headers for four URLs, the file, its signature, the 7-Zip listing, archived Adobe requirement and distribution pages (Internet Archive used only as evidence, not as a download source), NVD.
- Not verified: 6.0 vs 6.0.1 build, EULA text, silent switch, install folder, ARP name, behaviour on 98 SE/ME.
