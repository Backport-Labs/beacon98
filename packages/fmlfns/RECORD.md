# FmLfns 1.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: FmLfns - File Manager Long File Name Support (WinCorner)
- Version: 1.1 (help file dated 2002.01.01)
- License: Shareware, 30-day evaluation, 11 US dollars / 10 Euro
- Recommendation: 1.1, external.

## Windows 9x support evidence

- README.TXT inside FMLFNS95.EXE: "FmLfns 1.1 - File Manager Long File Name Support for Win ME/98/95 [...] FmLfns requires Windows ME/98/95."
- http://www.wincorner.com/home/shareware.html and /home/fmlfns.html (opened) say the same.
- It is a 9x-only product (it patches WINFILE.EXE of Windows 95/98/ME).

## Download

- http://www.wincorner.com/files/fmlfns95.exe and https://www.wincorner.com/files/fmlfns95.exe: both 200, last modified 2009-09-30. Linked from WinCorner's own page.
- File: fmlfns95.exe, 49,416 bytes: a DOS ARJ self-extractor ("RJSX" stub) containing FMLFNS.ARJ (created 2002-01-01) with CAPTHOOK.DL_, FMLFNS.INF, FMLFN.DL_, INSTALL.EXE, FMLFNS.HLP, FMLFNS.ICO, FMLFNS.EX_, README.TXT.
- SHA-256: aa500a714002aa51a64f4c9d5b6fd6042dc3c85f39ea554b0e9578e120ed2043
- MD5: 01adf2b9e8b87bd01d9b5c6ba02c4296
- Published checksum: none. Authenticode: not applicable (DOS executable; Get-AuthenticodeSignature reports UnknownError).

## Windows Defender

2026-09-29, engine 1.1.26080.3, signatures 1.459.466.0: "found no threats".

## License

- Shareware. The terms are in FMLFNS.HLP. I decompressed its topics (LZ77) but not the phrase table, so the text is only partly readable and is not quoted verbatim. Readable parts: a 30-day trial; "Using an [unregistered copy] ... for more than 30 days is prohibited"; "Unregistered" in window captions and a reminder dialog "twice a month"; fee "10 (Euro) or 10 US$"; a passage that appears to encourage passing unregistered copies to friends, which could not be read reliably.
- WinCorner's order page still lists "FmLfns 1.1 Long File Names in FM $11 / 10 EUR" (opened; whether ordering still works was not tested).
- Redistribution: not established. External.

## Security

- NVD keyword search "fmlfns" (2026-09-29): 0 results.

## Install behaviour

- FMLFNS95.EXE unpacks the files (ARJ SFX, DOS). Its command-line switches (e.g. a target folder or "yes to all") were not verified, so ENTRY.TXT runs it as `exe` with no arguments and the Notice tells the user to run INSTALL.EXE. This needs a better Beacon recipe (for example, unpack with a known ARJ SFX switch into {temp}, then `rundll.exe setupx.dll,InstallHinfSection DefaultInstall 132 {temp}\FMLFNS.INF`). Unresolved.
- FMLFNS.INF (read): copies FmLfns.exe, FmLfn.dll, Capthook.dll to the SYSTEM folder, the INF to INF, the help to HELP; adds FmLfns.exe -l to HKLM Run; registers an uninstaller at HKLM ...\Uninstall\FmLfns with DisplayName "File Manager Long File Name Support (FmLfns)" and UninstallString `rundll.exe setupx.dll,InstallHinfSection DefaultUninstall 132 %17%\FmLfns.inf`.

## Verification notes

- Opened: WinCorner pages, SFX listing, README.TXT, FMLFNS.INF, partial help text. Not verified: SFX switches, running on 9x.
