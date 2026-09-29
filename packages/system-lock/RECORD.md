# System Lock 1.2 build 1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: System Lock (r2 Studios, Australia)
- Version: 1.2 build 1, "Released: 23rd Sep 2001" (publisher page). The catalog row says 1.2.1.
- License: freeware ("free to download and use"); no license text found.
- Status: weakest of the entries written in this batch; see open points.

## Windows 9x support evidence

- The publisher states no system requirements (download, FAQ, known-issues and documentation pages checked; the documentation
  page has no content).
- Indirect only: released September 2001; the MSFN Windows 98SE list (source of this row, msfn-98se=1.2.1) lists it for 98SE.
  No primary statement for 95, 98 or ME was found. Systems is set to 98 on the strength of the MSFN list only.
- Not tested (no VM use).

## Download

- Page: https://www.r2.com.au/page/products/download/system-lock/ ("System Lock is no longer under active development and has been
  Archived ... System Lock is free to download and use.") -> https://www.r2.com.au/page/products/dl/system-lock/ (meta refresh) ->
  https://www.r2.com.au/static/downloads/files/system-lock-v1.2b1.exe
- http:// gives 301 to https://, then 200 (curl -I, 2026-09-29).
- File: system-lock-v1.2b1.exe, 160,147 bytes (page says "194 KB")
- SHA-256: e973570a9bfd7398d92fc3b3327bca0122dfa1f0ad1b5da8e1b63d5c70cccd68
- Published checksum: none. Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\system-lock -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- No license text available (see LICENSE.TXT, which records the publisher's statement). Redistribution is not granted, so `external`.

## Security

- NVD keyword search (2026-09-29): nothing for r2 Studios System Lock. By design a 9x screen locker can be bypassed by a restart.

## Install behaviour

- Installer type: NSIS (the "Nullsoft"/"NSIS" strings are present), an early version whose data 7-Zip 26.03 cannot open
  ("Cannot open the file as [Nsis] archive"). Contents, default folder, uninstaller and Add/Remove name are unknown.
- Silent switch: unknown for this NSIS version, so `Install: exe` runs it interactively.
- `Uninstall: registry System Lock` is a guess and is marked as unverified in ENTRY.TXT; it must be checked before publishing.

## Verification notes

- Verified: publisher pages and download chain, file hash, signature status, Defender.
- Not verified: 9x support from a primary source, license, install/uninstall details.
