# DiskInternals NTFS Reader 2.1 - Beacon 98 record

- Date checked: 2026-09-29
- Package: DiskInternals NTFS Reader (DiskInternals Research)
- Version: 2.1 (NTFSReader.exe file version 2.1.0.0, dated 2011-01-10 inside the installer)
- License: freeware EULA that allows distribution of the unmodified distributive file free of charge -> **hosted** (publisher location listed as well)

## Windows 9x support evidence

- https://www.diskinternals.com/ntfs-reader/ (downloaded and read 2026-09-29): "NTFS Reader for Windows 95, 98, Me. DiskInternals NTFS Reader is a freeware tool that provides a read access to NTFS disks from Windows 95, 98 and Me." The page also says "Product replaced by Linux Reader" and its download button points to Linux_Reader.exe (current, not a 9x program).
- The installer contains IO.VXD (a 9x driver), which fits the 9x-only design.

## Download

- The product page does not link the file any more. The file https://eu.diskinternals.com/download/NTFS_Reader.exe was found by testing the publisher's download folder with the product name (not a link I found on a page). It is DiskInternals' own server; the version info says ProductName "DiskInternals NTFS Reader", CompanyName "DiskInternals Research".
- http://eu.diskinternals.com/download/NTFS_Reader.exe answers 200 directly over plain HTTP; https://www.diskinternals.com/download/NTFS_Reader.exe and http://www... redirect (301) to the eu. host. 3,470,933 bytes.
- File: NTFS_Reader.exe, 3,470,933 bytes
- SHA-256: bdd06e58a0c6c85f2f2db14d12fbea6d353a8cd2da62dbd889192af6bbce5c1b
- MD5: 48d85ede4a1da6b44a34d97e014323ab
- Published checksum: none.
- Authenticode: installer and NTFSReader.exe not signed.
- The msfn list names version 2.0; the file served today is 2.1.

## Windows Defender

`MpCmdRun.exe -Scan -ScanType 3 -File D:\Win98SE\beacon\packages\ntfs-reader -DisableRemediation` on 2026-09-29 (engine 1.1.26080.3, signatures 1.459.466.0): "found no threats".

## License

License.txt from inside the installer (saved as LICENSE.TXT). "The SOFTWARE is FREE." Section 2:

> "2. DISTRIBUTION. This SOFTWARE may be distributed, provided that:
> - Such distribution includes only the original distributive file supplied by DiskInternals. You may not alter, delete or add any files in the distributive file or modify the SOFTWARE in any way.
> - No money is charged to the person receiving this SOFTWARE, beyond reasonable cost of packaging and other overhead."

Beacon 98 hosts the original NTFS_Reader.exe unmodified and free, so both conditions are met. No trial, no nag.

## Security

NVD keyword "DiskInternals": 0 results. Read-only access to NTFS; it installs a VxD for raw disk access.

## Install behaviour

- Installer type: NSIS 2 (7-Zip reports Type = Nsis, SubType NSIS-2, LZMA). Files: NTFSReader.exe, IO.VXD, fsm.ini, click.wav, MIG_29.dll, License.txt, Alligator.k52, Uninstall.exe; uses InstallOptions and StartMenu plugins.
- Silent switch: standard NSIS `/S`, with `/D=<folder>` last. Whether the script honours /S (e.g. license page) is not verified.
- Default folder: unknown (the NSIS script could not be extracted). Beacon passes `/D={dir}`.
- Uninstaller: Uninstall.exe in the install folder (from the listing); Add/Remove Programs name unknown. Beacon: `run "{dir}\Uninstall.exe" /S`.

## Verification notes

- Verified: product page text, file headers, installer listing and license (extracted with host 7-Zip, not run).
- Not verified: the file is not linked from any current page; silent install behaviour; the ARP name.
