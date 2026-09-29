# AviUtl 0.99c - Beacon 98 record

- Date checked: 2026-09-29
- Package: AviUtl (by KEN-kun), Japanese freeware video filter/encoding tool
- Version: 0.99c (2008-02-17)
- License: Freeware ("このプログラムはフリーソフトウェアです"); no redistribution terms
- Recommendation: 0.99c, external. It is the last version whose readme names Windows 98.

## Windows 9x support evidence

The "Notes" section of aviutl.txt in each version on the author's past-versions page (all downloaded from the author's server and read):
- 0.98d, 0.99, 0.99a, 0.99b, 0.99c: "○Win98,Win2000以外のOSでは正常に動作しないかもしれません。" ("It may not work correctly on operating systems other than Win98 and Win2000.")
- 0.99d to 0.99l, 0.99m: "WinXP,Vista以外のOSでは..." (XP and Vista).
- 1.00: "WinXP,Win7以外". 1.10: "Win10以外", and "SSE2に対応したCPUが必要です" (needs SSE2).
- 0.99c needs MMX: "MMX専用なのでMMXが使えないCPUでは動作させないで下さい。"
- Static imports of aviutl.exe 0.99c: kernel32, user32, gdi32, advapi32, avifil32, msvfw32, msacm32, ddraw, shell32, winmm, comdlg32; no NT-only functions. ME is not named by the author (Systems lists 98 and 2000); 95 not named.
- The availability.csv row points to an old GeoCities page (fredledingo/aviutl.htm, an English-translation site), which is gone. The author's own site is http://spring-fragrance.mints.ne.jp/aviutl/.

## Download

- http://spring-fragrance.mints.ne.jp/aviutl/aviutl99c.zip (and https): 200, 288,663 bytes. Listed on http://spring-fragrance.mints.ne.jp/aviutl/oldver2.php.
- Contents: aviutl.exe (421,888), aviutl.vfp (389,120), aviutl.txt (43,772), no folders.
- SHA-256: 169cc00ca4c68ed7915168afcac44b9af87860bb5980d661ca8dca38543f7772
- MD5: acd8eee011d1bfb9bacf8f8481a95230
- Published checksum: none. Authenticode: not signed (zip).

## Windows Defender

2026-09-29, engine 1.1.26080.3, signatures 1.459.466.0: "found no threats".

## License

- aviutl.txt, "－ 使用上の注意 －": "このプログラムはフリーソフトウェアです。このプログラムの使用によって何らかの障害が発生した場合でも、作者は一切の責任を負わないものとします。" (This program is free software; the author accepts no responsibility for any problem caused by using it.)
- No statement about redistribution, so Backport Labs should not host it. External.
- LICENSE.TXT (English, with my translation marked as such) and LICENSE-JA.TXT (original lines, Shift-JIS) are in this folder.

## Security

- NVD keyword search "aviutl" (2026-09-29): 0 results. It parses AVI files through Video for Windows codecs, so opening untrusted video files carries the usual risks of the installed codecs.

## Install behaviour

- Plain zip, no installer, no folders: `unzip {pf}\AviUtl`, shortcut to aviutl.exe, uninstall by removing the files. AviUtl writes its settings (aviutl.ini) next to aviutl.exe; Beacon's `files` uninstall will not remove files AviUtl created itself.
- aviutl.vfp is a VFAPI plugin (optional; registration not needed for normal use).

## Verification notes

- Opened: author's main page and past-versions page, the aviutl.txt readmes of 0.98d, 0.99 to 0.99m, 1.00 and 1.10. Not verified: running on 98/ME.
