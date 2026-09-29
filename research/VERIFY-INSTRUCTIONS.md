# How to verify a package for the Beacon 98 catalog

Beacon 98 is a package manager for Windows 95/98/ME by Backport Labs. It hosts only software that is
certain to be legal to redistribute: open source, or freeware whose own terms allow redistribution
of the unmodified files. Host: Windows 11, Windows PowerShell 5.1 (no `&&` or `||`; to use git or gh,
first run `$env:Path = [Environment]::GetEnvironmentVariable('Path','Machine') + ';' + [Environment]::GetEnvironmentVariable('Path','User')`).
The catalog format is in D:\Win98SE\beacon\design\FORMAT.md; read it first. A finished example of a
verified package is D:\Win98SE\beacon\pilot\7-zip\RECORD.md, and the current catalog is
D:\Win98SE\beacon\catalog\CATALOG.TXT.

For EACH package you are given:

1. **Version.** Find the latest version that runs on stock Windows 98 (and say whether 95 and ME too),
   from primary evidence: the project's changelog, release notes, system requirements, or the
   author's statement. Quote it and give the URL. If the version that is wanted needs KernelEx, say
   so and give the evidence. If there are two sensible choices (stable vs beta, last without KernelEx
   vs last with it), report both and recommend one.
2. **Download.** Find the official download of that version for 32-bit Windows: the project's own
   site, its official archive or mirror (SourceForge files, GitHub releases, ftp.mozilla.org, and
   similar). The Internet Archive is acceptable only for software whose license allows sharing and
   whose own server is gone; say so. Prefer the installer a Windows 98 user would normally run; note
   alternatives. A .msi needs Windows Installer on 98; say so.
3. **Files.** Download into D:\Win98SE\beacon\packages\<package-id>\ (create it; package ids are
   lowercase letters, digits and -). Compute SHA-256. If the project publishes checksums or
   signatures, compare them and report the result. Never install or run the downloaded program.
4. **Defender.** Scan the folder:
   `& "$env:ProgramFiles\Windows Defender\MpCmdRun.exe" -Scan -ScanType 3 -File "<folder>" -DisableRemediation`.
   If anything is detected, never bypass, exclude or work around it; report it and leave it.
5. **License.** Save the license text that applies to that exact version as LICENSE.TXT in the
   folder. Name the license and confirm that it permits redistributing the unmodified files, with
   its conditions. For GPL/LGPL/MPL software we must offer the matching source: download the source
   archive of that exact version into a src\ subfolder, hash it and record its URL. If the build
   bundles other libraries whose sources are not in that archive, say which. If the license forbids
   redistribution, stop working on that package, record why, and suggest whether it could be
   "external" (downloaded from the publisher's own server over plain HTTP; test with
   `curl.exe -sS -I --http1.0 http://...`).
6. **Security.** List known security problems of that version (count, and the worst few with CVE ids)
   from the project's advisories or NVD.
7. **Installing.** Installer type (Inno Setup, NSIS, MSI, Mozilla installer, InstallShield, plain
   zip...), its documented silent switch, default folder, whether it registers an uninstaller in
   Add/Remove Programs and under which display name if you can find it (for Inno Setup and NSIS the
   installer script or the program's documentation often says; otherwise write "unknown"). For zip
   packages: the folder layout inside the archive (use .NET's ZipFile to list entries, do not extract
   executables to run them), and what Beacon must do (target folder, strip, shortcuts).
8. **Record.** Write RECORD.md in the package folder with all of the above (same sections as the
   7-Zip example), and ENTRY.TXT with a draft catalog block in the CATALOG.TXT format (Windows-1252
   characters only, CR LF line endings are applied later). Use `pool/<package-id>/<version>/<file>`
   paths, `Requires: package kernelex | <text>` when KernelEx is needed, a `Warning:` for known
   security problems, and `Availability: external` with the publisher's http:// address when we must
   not host it.

Beacon 98 and its catalog are free and will never be sold. A license condition that only forbids
charging money or distributing for profit is therefore met. Personal-use-only licenses and licenses
that forbid redistribution are not acceptable.

For packages that need KernelEx: the KernelEx package id is `kernelex`. Say which KernelEx version
and compatibility mode the evidence mentions, if any.

Rules: do not invent URLs, versions, licenses or facts; write "unknown" and say what you could not
verify. State what you verified by opening a page or file and what is only from a search snippet.
Touch nothing outside D:\Win98SE\beacon\packages\ except your own temporary files. Do not interact
with any virtual machine. No accounts, no uploads.

Final report, per package: id, version, 95/98/ME support and KernelEx need, license and whether it
can be hosted, download URL, file, size, SHA-256, published checksum match, Defender result, source
archive, number of known security problems and the worst one, installer type and silent switch,
Add/Remove Programs name, and anything unresolved.
