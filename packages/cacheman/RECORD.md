# Cacheman 5.50 - Beacon 98 record

- Date checked: 2026-09-29
- Package: Cacheman "Classic" (Outertech)
- Version: 5.50 (installer title "Cacheman 5.50 Installation")
- License: Freeware (publisher's statement); license text not extracted
- Recommendation: 5.50, external.

## Windows 9x support evidence

- https://www.outertech.com/en/cacheman-classic (opened): "This Cacheman edition is outdated and has been designed for Windows 95, 98 and ME. [...] For Windows 2000 and XP Sp1-2 you should download CachemanXP instead. [...] Download Cacheman 5.50 for Windows 95, 98, ME (32bit) Freeware. Available in English."

## Download

- The page links http://download.outertech.com/cacheman5.exe, which redirects (301 to https, 301, 302) to https://www.outertech.com/downloads/cachm550.exe (200, last modified 2017-01-18).
- The address in availability.csv, http://www.outertech.com/files/cachm550.exe, now redirects to the current Cacheman 10.70 (cachm1070.exe), not to 5.50. It is not used.
- Plain http only redirects to https; the file itself is served over https.
- File: cachm550.exe, 948,802 bytes
- SHA-256: 2d28137bd126c8e1fdb456dfb076e03c26fbf7239c2c86dc2679eaffc0912b09
- MD5: 5aa90fa78b7226cf484271819c980f65
- Published checksum: none. Authenticode: not signed.

ENTRY.TXT locations: https://www.outertech.com/downloads/cachm550.exe, then http://www.outertech.com/downloads/cachm550.exe (redirects to the https address).

## Windows Defender

2026-09-29, engine 1.1.26080.3, signatures 1.459.466.0: "found no threats".

## License

- Freeware per the publisher page above. The setup's own license text could not be extracted (Wise installer with compressed script; the program was not run), so whether it allows redistribution is unknown. LICENSE.TXT contains the publisher's statement and says so.
- Therefore external: downloaded from Outertech's own server.

## Security

- NVD keyword search "cacheman" (2026-09-29): 1 result, unrelated (audiobookshelf). No known CVEs.

## Install behaviour

- Installer type: Wise Installation System ("WiseMain", "Initializing Wise Installation Wizard..."). Silent switch `/s` is the generic Wise switch; not verified for this file.
- Default folder and Add/Remove name: unknown. ENTRY.TXT uses "Cacheman 5.50" from the installer title; not verified.

## Verification notes

- Opened: Outertech Cacheman Classic page, redirects, installer strings. Not verified: license text, silent install, Add/Remove name, running on 9x.
