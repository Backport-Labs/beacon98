# Mega Mp3 Splitter 1.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Mega Mp3 Splitter (MegaSoft, author contact megax@libero.it)
- Version: 1.1 (06 March 2003), the only and last version
- License: Freeware (no license agreement; no redistribution grant)
- Recommendation: list as **external**, downloaded from the author's own site over plain HTTP.

## Windows 9x support evidence

- http://www.megax.it/mp3split/index.htm (opened 2026-09-29): "Current Version: 1.1 (06 March 2003) ... License: Freeware ...
  Platform: Windows 95/98/NT/2000/XP".
- The manual Mega MP3splitter.pdf (for 1.0) repeats "Platform: Windows 95/98/NT/2000/XP".
- The exe is a 32-bit Delphi program (imports kernel32, user32, gdi32, comctl32, comdlg32, winmm, ole32, oleaut32, version,
  advapi32, imm32), PE subsystem version 4.0. Not run.
- Windows ME is not named; not tested on any 9x system. Playback uses winmm, so MP3 playback inside the program probably needs an
  MP3 decoder in Windows (unknown, not verified); splitting itself does not.

## Download

- URL: http://www.megax.it/mp3split/dl/mp3split.zip (link "mp3split.zip" on the page)
  - http: 200, Content-Length 356039, Last-Modified 2005-09-17, server Microsoft-IIS/10.0.
  - https://www.megax.it/...: connection reset (no working HTTPS). Plain HTTP only.
- Also on the page: http://www.megax.it/mp3split/dl/mp3split.pdf (manual, 112,914 bytes; the same PDF is inside the zip).
- The zip's File_id.diz names an older home page, http://digilander.libero.it/mega27/megasoft.htm (not checked).
- Is megax.it the author's own site? The page carries the same contact address as the program (megax@libero.it), a donation
  request "If you find my free software helpful", and an Italian version of the page; treated as the author's site.
- File: mp3split.zip, 356,039 bytes (plain zip)
- SHA-256: e3c74c7a844f8d080bf78f35cee34b910073e12f5b480cd63b082fdf70d7a6cc
- MD5: 8ebf2896ba8f7d906ff0ddda6db4dd51
- Published checksum: none.
- Contents: `Mega MP3splitter.exe` (556,032, 2003-03-06), `Mega MP3splitter.pdf` (112,914), `File_id.diz` (1,160). No folders.
- Authenticode: not signed.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\mega-mp3-splitter -DisableRemediation` on 2026-09-29
(engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

- "Freeware" (File_id.diz, web page, manual). LICENSE.TXT quotes all three statements.
- No text allows or forbids redistribution. So: external, not hosted.
- No trial, expiry or nag.

## Security

NVD keyword search "Mega MP3 Splitter" (2026-09-29): 0 results. It parses MP3 files; a crafted file might crash it (not known,
not tested).

## Install behaviour

- Plain zip, no installer. Beacon: `unzip {pf}\Mega MP3 Splitter`, shortcut to `{dir}\Mega MP3splitter.exe`.
- Uninstall: `files`.

## Verification notes

- Verified by opening/downloading: the page, the zip and the PDF (hash, listing, File_id.diz, PE header).
- Not verified: running on 95/98/ME.
