# Beacon 98

A package manager for Windows 95 and Windows 98, by Backport Labs.

Beacon 98 installs software that is legal to distribute: open source programs and freeware whose
license permits sharing, in the last versions that run on Windows 95 and 98. It downloads a
signed catalog and checks every file against it before installing anything.

This repository is at an early stage. It holds the catalog format, the tools that sign the
catalog, the records of the first packages, and the first version of the Windows 98 program,
which reads and verifies the catalog but does not install anything yet.

## How it works

Windows 95 and 98 cannot use the encryption that current web servers require, so Beacon
downloads over plain HTTP from `http://get.backportlabs.com/`. Security comes from a signature
instead of the connection:

1. The catalog lists every package with the size and SHA-256 of each file.
2. The catalog is signed with an Ed25519 key that is kept offline by the publisher.
3. Beacon carries the public key, verifies the catalog, and refuses any file whose size or
   SHA-256 does not match.

The full specification is in [`design/FORMAT.md`](design/FORMAT.md).

## Contents

| Path | Contents |
|---|---|
| `design/FORMAT.md` | Catalog and signature format, and what the client does |
| `catalog/CATALOG.TXT` | The catalog, draft |
| `catalog/CATALOG.SIG` | Its signature |
| `keys/` | The public signing key |
| `tools/` | Scripts that create the signing key, and check, sign and verify the catalog |
| `pilot/` | One folder per package: `RECORD.md` with the checks made, and the license text |
| `client/` | The Windows 95/98 program, `BEACON98.EXE`, in C |

## The program

`client/src` is plain C for Tiny C Compiler 0.9.27, like Searchlight 98. It uses only what
Windows 95 and 98 provide.

| File | Contents |
|---|---|
| `beacon.h` | Constants, types, and the functions each file offers to the others |
| `main.c` | Start-up and command line |
| `window.c` | The main window: groups, package list, search box, status bar |
| `details.c` | The pane that describes the selected package |
| `catalog.c` | Reading `CATALOG.TXT` |
| `sign.c` | Checking `CATALOG.SIG` with the public key built into the program |
| `sha256.c` | SHA-256, for checking downloaded files |
| `system.c` | Requirements, and which packages are installed |
| `test.c` | The self-test and the `/shot` test mode |
| `tweetnacl.c`, `tweetnacl.h` | [TweetNaCl](https://tweetnacl.cr.yp.to/) 20140427, public domain, unchanged. Used for Ed25519. |

```powershell
.\client\build\build.ps1 -Tcc C:\tools\tcc\tcc.exe
```

The build compiles the program and runs its self-test: SHA-256 test values, 256 Ed25519 test
vectors from the reference software together with forged signatures and changed messages that
must be rejected, the signed catalog, and file hashes compared with those Windows computes.

The package files themselves are not in this repository. They are published on the download
server.

## Choosing packages

A package is accepted when:

- its license, or the author's written terms, permit redistributing it;
- its last version for Windows 95 or 98 is identified from the project's own notes;
- the file matches the project's published checksum or signature, where one exists;
- Windows Defender finds nothing in it;
- its known security problems are listed, and shown to the user before installing.

Components that Beacon may not distribute, such as Microsoft updates, are listed as
requirements. Beacon checks for them and tells the user what is missing.

## Signing

```powershell
.\tools\sign-catalog.ps1      # checks CATALOG.TXT, signs it, verifies the signature
.\tools\verify-catalog.ps1    # verifies CATALOG.SIG as a client would
```

The scripts need OpenSSL 3, such as the one included with Git for Windows. The private key never
enters this repository.

## License

The tools and documents in this repository are released under the MIT License. See
[`LICENSE`](LICENSE). Each package keeps its own license, recorded in `pilot/`.

Windows is a registered trademark of Microsoft Corporation. This project is not affiliated with
or endorsed by Microsoft.
