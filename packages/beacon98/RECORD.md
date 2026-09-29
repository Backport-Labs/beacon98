# Beacon 98

| Field | Value |
|---|---|
| Version | 0.5.0 |
| Publisher | Backport Labs |
| License | MIT (LICENSE.TXT); source at https://github.com/Backport-Labs/beacon98 |
| Systems | Windows 95, 98, ME |
| File | B98SETUP.EXE, 494,878 bytes, built by `client\build\build.ps1 -Iscc` with Inno Setup 5.4.3 |
| SHA-256 | 8cfa06811d7d82471440db1fc1271f320accd8dbd425cdbc8f2d57aae1ac3189 |
| Defender | No threats found (2026-09-29) |
| Security issues | None known |

## Install notes

- Inno Setup. Beacon treats its own package specially: it starts the setup
  program with `/SILENT /SUPPRESSMSGBOXES /NORESTART` and closes. The setup
  program waits up to five minutes for the mutex `Beacon98Running` to go,
  replaces the program, and starts it again.
- Add/Remove Programs name: "Beacon 98".
- Uninstalling keeps `INSTALLED.TXT` and `FILES\`, so a reinstalled Beacon can
  still remove packages.
