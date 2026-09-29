# Beacon 98 catalog format

Draft 1, 2026-09-28.

Beacon 98 downloads one catalog that lists every package, checks its signature,
and installs packages from files whose size and SHA-256 the catalog gives.
Windows 95 and 98 cannot use the encryption current web servers require, so
Beacon carries its own TLS (BearSSL, with Mozilla's certificate authorities)
and uses HTTPS where a server offers it, with plain HTTP as the fallback. The
signature, not the connection, makes the catalog trustworthy; HTTPS keeps
downloads private and reaches servers that no longer speak plain HTTP.

## Files on the server

All files are served from `http://get.backportlabs.com/`. HTTPS serves the same
files for current computers.

| Path | Contents |
|---|---|
| `CATALOG.TXT` | The catalog |
| `CATALOG.SIG` | Its signature |
| `KEYS.TXT` | The public signing key, for reference. Beacon carries its own copy and never trusts this file. |
| `pool/<package>/<version>/<file>` | Package files |
| `pool/<package>/<version>/src/<file>` | Source code, where the license requires it to be offered |
| `pool/<package>/<version>/LICENSE.TXT` | The license, shown before installing |

A file in `pool/` never changes once published. A new version gets a new
folder. Caches and mirrors can therefore keep files indefinitely.

## CATALOG.TXT

Plain text in the Windows-1252 character set with Windows line endings (CR LF).
The format follows the control files of Debian's package manager: blocks of
`Field: value` lines, separated by one empty line.

- A line that starts with `#` is a comment.
- A line that starts with a space continues the field above it. A continuation
  line containing only ` .` is an empty line in the text.
- Field names are case-sensitive. A client ignores fields it does not know.
- Lines are at most 1,000 characters long.

The first block describes the catalog. Each further block is one package.

### Catalog block

| Field | Required | Meaning |
|---|---|---|
| `Format` | yes | `1`. A client refuses a catalog whose format it does not know. |
| `Catalog` | yes | `Beacon 98` |
| `Publisher` | yes | `Backport Labs` |
| `Serial` | yes | A number that grows with every published catalog, written as `YYYYMMDDNN`. A client refuses a catalog whose serial is lower than the last one it accepted. |
| `Date` | yes | Publication date, `YYYY-MM-DD` |
| `Expires` | yes | After this date the client warns that the catalog may be outdated. It does not refuse it, because many old computers have a wrong clock. |
| `Base` | yes | The address the paths in the catalog are relative to |
| `Mirrors` | no | Other base addresses holding the same `pool/`. Files from mirrors are checked in the same way. |

### Package block

| Field | Required | Meaning |
|---|---|---|
| `Package` | yes | Identifier: lowercase letters, digits and `-`, at most 32 characters. Unique in the catalog. |
| `Name` | yes | Name shown to the user |
| `Version` | yes | Version as the project writes it |
| `Section` | yes | One of `Utilities`, `Internet`, `Multimedia`, `Office`, `Development`, `Games`, `System` |
| `Summary` | yes | One line, at most 70 characters |
| `Description` | no | Several lines |
| `Homepage` | no | Project address, for information |
| `License` | yes | License name, SPDX identifier where one exists, or `Freeware` |
| `License-File` | yes | Path of the license text. The client shows it before installing. |
| `Systems` | yes | Systems it runs on, from `95`, `98`, `ME`, `NT4`, `2000`, or an edition: `95OSR2` (OSR 2 and later), `98FE` (first edition) or `98SE` (Second Edition). `98` means both editions of 98. |
| `Availability` | no | `hosted` (the default): Backport Labs distributes the files, from its own server or another. `external`: Backport Labs does not distribute them; every location is someone else's server, such as the publisher's or SourceForge. A package whose Download lines name no location on our server is treated as `external` either way. |
| `Download` | yes | One line per file: `location size sha256`, optionally followed by more locations: `location size sha256 location2 location3`. A location is a path on our server (relative to `Base`) or a full `http://` or `https://` address. The client tries the locations in order until one gives a file with this size and SHA-256. A path on our server is tried over HTTPS first and plain HTTP second. The file is saved under the last part of its first location; for an address with a query, such as `download.php?f=setup.exe`, under the value of the last parameter. Several files are installed in the order of the lines. An `external` package names no location on our server. |
| `Source` | no | One line per file: `path size sha256`. Not downloaded by the client; offered on the package's page. Not given for `external` packages, which we do not distribute. |
| `Installed-Size` | no | Disk space needed after installation, in KB |
| `Depends` | no | Packages from this catalog to install first, separated by commas |
| `Requires` | no | Conditions the client checks before installing. One per line: `check argument | text`. If one fails, the client shows the text and does not install. |
| `Install` | yes | How to install. See below. |
| `After` | no | Steps after installing, one per line. See below. |
| `Shortcut` | no | Start Menu shortcuts, one per line: `name | target | arguments` |
| `Uninstall` | yes | How to remove it. See below. |
| `Warning` | no | Shown before installing. The user must confirm it. Used for known security problems. |
| `Notice` | no | Shown after installing |
| `Detect` | no | Lines in the syntax of `Requires`; see Uninstall below |
| `Remove` | no | `run` steps before uninstalling; see Uninstall below |
| `Hardware` | no | For drivers: the devices it is for, one per line, `pci VEN_xxxx&DEV_yyyy` (hexadecimal, upper case), or a whole class of devices for a generic driver, `pci CC_cccc` or `pci CC_ccccpp` (PCI class, subclass and interface, e.g. `CC_0300` any display adapter, `CC_0C0330` any USB 3 controller). Beacon lists the package under "Drivers for this computer" when one of them is in the computer. |
| `Referer` | no | An address sent as the `Referer` header with full-address downloads of this package, for publishers whose servers refuse downloads without one. Never sent with paths on the catalog's own server. |

### Places

Paths in `Install`, `After`, `Shortcut` and `Requires` may use:

| Name | Meaning |
|---|---|
| `{pf}` | The Program Files folder |
| `{win}` | The Windows folder |
| `{sys}` | The Windows SYSTEM folder |
| `{dir}` | Where this package is installed |
| `{dir:<package>}` | Where another installed package is |
| `{temp}` | The folder with the downloaded files |
| `{file1}`, `{file2}` | Downloaded files, in the order of `Download` |

### Requires

| Check | Argument | Passes when |
|---|---|---|
| `file` | path | The file exists |
| `msi` | version | Windows Installer of this version or later is present (`msiexec.exe` file version) |
| `ie` | version | Internet Explorer of this version or later is present |
| `dx` | version | DirectX of this version or later is present (the major version, from the registry) |
| `reg` | `HKLM\...` or `HKCU\...` | That registry key exists |
| `winsock2` | | Windows Sockets 2 is present |
| `memory` | MB | The computer has at least this much memory |
| `package` | package identifier | That package of this catalog is installed |
| `pci` | `VEN_xxxx&DEV_yyyy` | Windows knows that PCI device in this computer (Windows 9x also remembers devices that were removed) |

The text after `|` says what is missing and where to get it. Beacon never
downloads anything a `Requires` line names; those are components we have no
right to distribute. The exception is `package`: the requirement is another
package of the catalog, such as KernelEx, which changes Windows itself.
Beacon does not install it without asking. When the user ticks or installs a
package that needs it, Beacon shows that package's warning and offers to
tick it too; it is then installed first.

## What the catalog contains

Only software that is certain to be legal to distribute: open source, and
freeware whose terms permit sharing. A package whose own files we should not
host, but which its publisher still offers, is listed as `external`. Software
that neither we nor its publisher distribute is not listed.

### Install

The first word is the kind of installer. The rest are arguments.

| Kind | Arguments | What the client does |
|---|---|---|
| `inno` | extra switches | Runs `{file1}` with `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART` and the extra switches |
| `nsis` | extra switches | Runs `{file1}` with `/S` and the extra switches |
| `msi` | extra properties | Runs `msiexec /i "{file1}" /qb` and the properties |
| `exe` | command line | Runs `{file1}` with exactly this command line |
| `unzip` | target, optionally `strip N` | Unpacks every downloaded file into the target, dropping the first N folder levels. Self-extracting ZIP files count as ZIP files. |
| `copy` | target | Copies the downloaded files into the target |

A setup program installs into its own default folder, so an update goes where
the previous version is. For `unzip` and `copy`, `{dir}` is the target; for
the others it is `{pf}\<Name>`. The client waits for the setup program to
finish. Exit codes 0, 1641 and 3010 mean success (the last two ask for a
restart); any other code is a failure.

The client records each installed package in `INSTALLED.TXT`, one
`package|version|folder` per line, and what it created itself (files,
folders, shortcuts, `PATH` additions) in `FILES\<package>.TXT`, which Remove
uses to take them away again.

### After

| Step | Arguments | Meaning |
|---|---|---|
| `run` | command line | Runs a program and waits for it |
| `write` | path, then text after `|` | Writes a small text file, replacing it. `\n` is a new line. |
| `path` | folder | Adds the folder to `PATH` in `AUTOEXEC.BAT`. Takes effect after a restart; the client says so. |

### Uninstall

| Kind | Argument | What the client does |
|---|---|---|
| `registry` | Add/Remove Programs name | Runs the uninstaller Windows lists under that name |
| `run` | command line | Runs this command and waits, for a setup program that registers no uninstaller, e.g. `run "{dir}\uninstall.exe" /S` |
| `files` | | Removes the files and shortcuts Beacon created, using its own record |
| `none` | | Cannot be removed, for example a Windows update. Beacon says so. |

With `registry` and `run`, Beacon also removes the shortcuts and `PATH` lines it
created itself.

A package may have `Detect` lines, in the syntax of `Requires` lines. When
it has them, Beacon counts the package as installed when any one of them is
met, whoever installed it. (A Windows update often writes a different
registry key on 98 and 98 SE, so either may prove it installed.) This is how
a Windows update or a component such as Windows Installer 2.0 is recognized.
A program that requires such a component names the package with
`Requires: package <id>`, so Beacon offers to install it.

A package may also have `Remove` lines: `run` steps carried out before
uninstalling, while the files are still there, for example
`run regsvr32 /u /s "{dir}\vsfilter.dll"` to undo a registration made by an
`After` step.

Places in the switches of `inno`, `nsis`, `msi` and `exe` are expanded too, so
`Install: nsis /D={dir}` puts an NSIS program into the package's folder.

## CATALOG.SIG

```
Key-Id: 94f2f398cdde0384
Signature: <128 hexadecimal digits>
```

The signature is Ed25519 (RFC 8032, without pre-hashing) over the exact bytes of
`CATALOG.TXT`. `Key-Id` is the first 8 bytes of the SHA-256 of the 32-byte public
key, in hexadecimal. It only selects the key; the signature does the checking.

## What the client does

1. Downloads `CATALOG.TXT` and `CATALOG.SIG`.
2. Verifies the signature with a public key built into the program. If it fails,
   it stops and keeps the previous catalog.
3. Checks `Format`, `Serial` and `Expires` as described above, then stores the catalog.
4. On install: checks `Systems` and `Requires`, shows `License-File` and any
   `Warning`, installs `Depends` first.
5. Downloads each file, checks its size, then its SHA-256. A file that does not
   match is deleted and the installation stops. For an `external` package the
   client says which server the file comes from. The checksum in the catalog
   only confirms that the file is the publisher's original; the publisher, not
   Backport Labs, distributes it.
6. Runs `Install`, then `After`, creates the shortcuts, and records what it did in
   `INSTALLED.TXT`.

## Keys

- The private key is on the publisher's computer only, encrypted, never in the
  cloud or in a repository. See `tools/new-signing-key.ps1`.
- The client carries up to two public keys, so a replacement key can be added in
  one version and the old one removed in a later version.
- Losing the private key means publishing a client with a new key. A leaked key
  lets someone publish packages that clients trust; it would be revoked the same
  way.

## Custom sources

Anyone can publish a catalog in this format, signed with their own Ed25519
key, and a user can add it to Beacon under Settings, Sources. Beacon keeps
the sources in `SOURCES.TXT`, next to the program, one per line:

```
name|location|public key in hexadecimal (64 digits)|header;;header
```

- The location is a web address (`http://` or `https://`) or a folder: a local
  folder, a CD, or a network share. Beacon reads `CATALOG.TXT` and
  `CATALOG.SIG` there, and keeps them as `CATn.TXT` and `CATn.SIG`.
- Each source's catalog must be signed with that source's key. The Backport
  Labs key is never accepted for another source, nor another source's key for
  the Backport Labs catalog. The serial number rule applies to each source.
- Paths in a source's `Download` lines are relative to its catalog's `Base`
  (web sources) or to its folder (folder sources). `tools/new-signing-key.ps1
  -Name <name>` and `tools/sign-catalog.ps1 -KeyName <name>` make and use such
  a key.
- Access headers, such as the token of a private server, are sent only over
  HTTPS and only to the source's own host: never over plain HTTP, never after
  a redirect to another host, and never with full-address locations. A
  source with access headers must have an `https://` address.
- The packages of all sources are listed together; each source also has a
  group of its own, and the details say which source a package is from.

A custom source is trusted as much as the user trusts its publisher: its
catalog decides what Beacon downloads and runs.

## What plain HTTP still exposes

The signature stops anyone from changing the catalog or the files. It does not
hide what a user downloads from someone on the same network, and it does not
stop someone from blocking downloads or serving the previous catalog. The
serial number limits the second: a client never goes back to an older catalog
than one it has seen.
