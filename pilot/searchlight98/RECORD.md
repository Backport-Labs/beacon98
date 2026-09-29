# Searchlight 98

| Field | Value |
|---|---|
| Name | Searchlight 98 |
| Version | 0.3.4 |
| Publisher | Backport Labs |
| License | MIT (LICENSE.TXT in this folder) |
| Windows 9x support | Built for Windows 95 and 98. Tested on Windows 98 SE in a virtual machine (version 0.3.3; 0.3.4 changes text only). Not yet tested on Windows 95 or ME. |
| Download URL | https://github.com/Backport-Labs/searchlight98/releases/download/v0.3.4/SL98SETUP.EXE |
| File | SL98SETUP.EXE, 350,340 bytes |
| SHA-256 | e9bab1b942a736bbb962640a47a9ea9a4e7aa38a03771f6143d9230ee61bd97a |
| Published checksum | Release notes and GitHub asset digest list the same SHA-256. Match. |
| Defender | No threats found (2026-09-28) |
| Source archive | https://github.com/Backport-Labs/searchlight98/archive/refs/tags/v0.3.4.zip, SHA-256 04bebec50e8d2b8da87e6212124074608f2c71c1a62797d0cc13097331e06569 (GitHub generates this archive; its hash is not guaranteed to stay the same) |
| Security issues | None known |
| Date checked | 2026-09-28 |

## Install notes

- Installer: Inno Setup 5.4.3.
- Silent install: `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` (standard Inno Setup switches).
- Default folder: `C:\Program Files\Searchlight 98`.
- Registers an uninstaller in Add/Remove Programs.
- Stops a running copy before replacing files (`/quit`).
- The "startup" task adds a Run key entry. A silent install selects the default tasks unless `/TASKS=` is given.
