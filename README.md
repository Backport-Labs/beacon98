# Beacon 98

A package manager for Windows 95 and Windows 98, by Backport Labs.

Beacon 98 installs software that is legal to distribute: open source programs and freeware whose
license permits sharing, in the last versions that run on Windows 95 and 98. It downloads a
signed catalog and checks every file against it before installing anything.

This repository is at an early stage. It holds the catalog format, the tools that sign the
catalog, the records of the first packages, and the Windows 98 program, which downloads the
catalog, verifies it, and installs and removes packages.

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
| `system.c` | Requirements, the version of Windows, and which packages are installed |
| `net.c` | Downloading: plain HTTP through WinInet, redirects, and handing HTTPS to `tls.c` |
| `tls.c` | HTTPS with BearSSL over Windows Sockets, trusted certificate authorities, wrong clocks |
| `install.c` | Updating the catalog, installing and removing packages, shortcuts |
| `unzip.c` | Unpacking ZIP files in pieces, with CRC-32 checks and safe names |
| `task.c` | The progress window; the work runs in a second thread |
| `confirm.c` | The window that shows the license and warnings before installing |
| `test.c` | The self-test and the `/shot` and `/unzip` test modes |
| `tweetnacl.c`, `tweetnacl.h` | [TweetNaCl](https://tweetnacl.cr.yp.to/) 20140427, public domain, unchanged. Used for Ed25519. |
| `../vendor/miniz` | [miniz](https://github.com/richgel999/miniz) 3.1.2, MIT license, unchanged. Only its inflate part is compiled. |
| `../vendor/bearssl` | [BearSSL](https://bearssl.org/) 0.6, MIT license, unchanged except that its system random source is left out; Beacon supplies its own. Identical to Debian's copy of the same release. |
| `../vendor/cacert` | Mozilla's certificate authorities as published by [curl](https://curl.se/docs/caextract.html), MPL 2.0. Built into the program; a `CAROOTS.PEM` next to it replaces the list. |

```powershell
.\client\build\build.ps1 -Tcc C:\tools\tcc\tcc.exe -Iscc "C:\tools\Inno Setup 5\ISCC.exe"
```

With `-Iscc` (Inno Setup 5.4.3, the last release that builds setup programs for Windows 95 and
98), the build also writes the setup program `client\dist\B98SETUP.EXE`. Beacon can update
itself: when it installs its own catalog package, `beacon98`, it starts the new setup and
closes, and the setup waits for it to be gone, then starts it again.

The build compiles the program and runs its self-test: SHA-256 test values, 256 Ed25519 test
vectors from the reference software together with forged signatures and changed messages that
must be rejected, the signed catalog, and file hashes compared with those Windows computes. It
also unpacks test archives (one self-extracting, one with a name that points outside the target
folder, which must be refused) and compares the result with the originals, and downloads from
`get.backportlabs.com`, so it needs an internet connection.

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
