                                BEACON 98
                              Version 0.6.0

         Installs free software on Windows 95, 98 and Millennium.

-----------------------------------------------------------------------------
 CONTENTS
-----------------------------------------------------------------------------
 1. What is Beacon 98?
 2. System requirements
 3. Using Beacon 98
 4. How Beacon 98 keeps downloads safe
 5. Where things are kept
 6. Troubleshooting
 7. Uninstalling
 8. License

-----------------------------------------------------------------------------
 1. WHAT IS BEACON 98?
-----------------------------------------------------------------------------
Beacon 98 is a package manager: a catalog of programs that run on Windows
95, 98 and Millennium, which it downloads and installs for you. Every
program in it is open source, or freeware whose license allows sharing,
in the last version that runs on these systems.

Beacon 98 is free and will never be sold. It is made by Backport Labs.

-----------------------------------------------------------------------------
 2. SYSTEM REQUIREMENTS
-----------------------------------------------------------------------------
 - Windows 95, 98, 98 Second Edition or Millennium Edition
 - Internet Explorer 4.0 or later (Beacon uses its internet functions)
 - An internet connection
 - 1 MB of memory for Beacon itself; each package lists what it needs

-----------------------------------------------------------------------------
 3. USING BEACON 98
-----------------------------------------------------------------------------
 Groups .................... The list on the left: all packages, installed
                             ones, updates, and one group per kind.
 Search .................... Type in the Search box. Every word must appear
                             in the name or description.
 Details ................... Select a package to see what it is, its
                             license, where it is downloaded from, what it
                             needs, and its known security problems.
 Install ................... Tick one or more packages and press Install.
                             Packages they depend on are ticked too.
                             Beacon shows each license first; nothing is
                             installed until you agree.
 Remove .................... Select an installed package and press Remove.
 Update Catalog ............ Downloads the latest catalog. Beacon does this
                             by itself the first time it starts.
 Drivers ................... "Drivers for this computer" appears when the
                             catalog has a driver for a device Windows
                             knows in this computer. A wrong display or
                             chipset driver can stop Windows from starting:
                             then start in Safe Mode (hold F8, or Ctrl on
                             98) and remove it in Device Manager.
 Sorting ................... Click a column heading to sort by it; click it
                             again to reverse the order.
 Menus ..................... File: Update Catalog, Exit.
                             Settings: Sources (see below).
                             Help: this Read Me (F1), About Beacon 98.

 CUSTOM SOURCES
 Besides the Backport Labs catalog, Beacon can read catalogs from other
 publishers, or your own, from a web address or a folder (a CD or a
 network share works too). Open Settings, Sources, press New, and enter:
   Name ............ what the source is called in Beacon
   Location ........ its web address, or its folder
   Public key ...... 64 hexadecimal digits, from its publisher; Beacon
                     only uses its catalog when it is signed with this key
   Access headers .. only for a private server that asks for them, one per
                     line (Name: value). Beacon sends them only over HTTPS
                     and only to that server.
 Then press OK and let Beacon update the catalog. The packages appear
 with the others, and in a group of their own. Add only sources you
 trust: a source decides what Beacon installs.

 Some packages need a part of Windows that Beacon 98 cannot supply, such
 as a newer Windows Installer. Their details say which one. Some need
 KernelEx, an extension to Windows 98 that Beacon can install; it asks
 first.

-----------------------------------------------------------------------------
 4. HOW BEACON 98 KEEPS DOWNLOADS SAFE
-----------------------------------------------------------------------------
 - The catalog is signed by Backport Labs. Beacon checks the signature
   with a key built into the program and refuses a catalog that does not
   match, or that is older than one it has already seen.
 - The catalog lists the size and SHA-256 checksum of every file. A
   downloaded file that does not match is deleted and never run.
 - Beacon uses HTTPS where a server offers it, with its own encryption,
   because Windows 95 and 98 cannot use what current servers require.
   Where a server offers only plain HTTP, the checksum still protects the
   file.
 - Old software has known security problems. Beacon shows them before
   installing, and asks you to confirm.

-----------------------------------------------------------------------------
 5. WHERE THINGS ARE KEPT
-----------------------------------------------------------------------------
 In the folder where Beacon 98 is installed:
   CATALOG.TXT, CATALOG.SIG   the catalog and its signature
   SOURCES.TXT                your custom sources, with their access
                              headers (keep it private if it has any)
   CAT1.TXT, CAT1.SIG, ...    the catalogs of the custom sources
   INSTALLED.TXT              the packages Beacon installed
   FILES\                     what Beacon created for each package, so
                              Remove can take it away again
   DOWNLOAD\                  files being installed; emptied afterwards
   CAROOTS.PEM                optional: your own list of certificate
                              authorities for HTTPS, instead of the
                              built-in one

-----------------------------------------------------------------------------
 6. TROUBLESHOOTING
-----------------------------------------------------------------------------
 The log says the clock of this computer is wrong.
     Beacon used the date from its own server to check certificates. You
     may want to correct the date: double-click the clock.

 A download fails.
     Beacon tries every place the catalog lists for the file. If all fail,
     check the internet connection, and try again later.

 A package does not start after installing.
     Its details may list a requirement or a note. Some programs need a
     restart of Windows first.

-----------------------------------------------------------------------------
 7. UNINSTALLING
-----------------------------------------------------------------------------
Open Control Panel, Add/Remove Programs, choose Beacon 98 and click
Add/Remove. Packages you installed with Beacon stay installed; remove them
first if you want them gone. Beacon keeps INSTALLED.TXT and the FILES
folder, so that if you install Beacon again it can still remove them.

-----------------------------------------------------------------------------
 8. LICENSE
-----------------------------------------------------------------------------
Beacon 98 is free and open source software, released under the MIT
License. See LICENSE.TXT. It includes BearSSL (MIT license), TweetNaCl
(public domain), miniz (MIT license) and Mozilla's list of certificate
authorities (Mozilla Public License 2.0). Each package in the catalog
keeps its own license, which Beacon shows before installing it.

Source code: https://github.com/Backport-Labs/beacon98

Windows is a registered trademark of Microsoft Corporation. Beacon 98 is
not affiliated with or endorsed by Microsoft.
