# Shareware, trial and commercial software: 9x availability at the publisher

Checked 2026-09-29. Input: `availability.csv`, rows of kind "page", "other: 403", "other: 301", "other: 302", "moved: another site's front page", plus kind "file" on third-party hosts; Microsoft items excluded (SysInternals Suite too, as Microsoft owns it; DirectX and Internet Explorer rows were marked skipped for the Microsoft agent).

Rows examined: 159. Rows that qualify: 26 (WinZip appears twice). Packages written: 27.

How it was checked: the session's WebSearch budget was used up early, so every fact below comes from pages and files opened directly (curl.exe -sS -I -L over https and http, WebFetch, 7-Zip/innoextract listings of downloads; nothing was run) or is marked unknown / unverified. The Internet Archive was read only as evidence of old system requirements, never as a download source. No VM was touched and nothing was uploaded. Markers: [V] = verified by opening the page or file; [S] = from list data or not verified today; [I] = inference.

"Qualifies" means the publisher's own server (or its official mirror) still serves a version that runs on Windows 95, 98 or ME.

## Every row examined

| Name | Last 9x version (evidence) | Served by publisher (URL) | License type | Redistribution allowed | Qualifies | Reason |
|---|---|---|---|---|---|---|
| CacheMan | 5.50 - Outertech's Cacheman Classic page: "designed for Windows 95, 98 and ME ... Download Cacheman 5.50 for Windows 95, 98, ME (32bit) Freeware" | Yes: https://www.outertech.com/downloads/cachm550.exe (via http://download.outertech.com/cacheman5.exe). The CSV address /files/cachm550.exe now redirects to Cacheman 10.70 | Freeware (publisher statement) | Unknown (license inside Wise installer, not extractable) | Yes (external) | Publisher's own server, freeware |
| EditPad Lite | Unknown; the oldest version Just Great Software offers is 7.6.7 "Windows 2000/XP/Vista/7/8/8.1/10" (editpadlite.com/download.html) | No 9x version (SetupEditPadLite.exe is 8.6.1, XP+; older file names 404) | Freeware for non-commercial use (current) | n/a | No | No 9x version served |
| FmLfns TSR | 1.1 - README: "FmLfns requires Windows ME/98/95" | Yes: http://www.wincorner.com/files/fmlfns95.exe (also https) | Shareware, 30 days, $11 / 10 EUR (order page still up) | Not established (help file only partly readable) | Yes (external) | Publisher's own server, 9x-only product |
| Icon Master | 1.2d per mdgx list (unverified) | No: only mdgx.com (third-party mirror; returns 403/404 to curl). Publisher unknown | Shareware (CSV) | Unknown | No | No publisher server found; mdgx is not the publisher |
| Java 6u7 | Unknown for 9x (Oracle does not list 98/ME; not verified) | No: CSV file is a repackaged MSI on mdgx. Oracle's archive link download.oracle.com/otn/java/jdk/6u7/jre-6u7-windows-i586-p.exe redirects to an Oracle account login | Oracle BCL | n/a | No | Needs an Oracle account (not allowed); mdgx not publisher |
| NoteTab Lite (Light) | 7.2 (2014) - Fookes still serves a "Windows 95 and NT4 Compatibility Pack" for "NoteTab version 7" (notetab.com/ftp/Win95-NT4.zip); WhatsNew documents Win95/98/ME; no NT-only static imports. Not stated as a system requirement | Yes: https://www.fookes.com/ftp/free/NoteTab_Light_Setup.exe (http too) | Freeware | Yes: EULA s.6 "distribute NoteTab Light in its unmodified form via electronic means (Internet, BBS's, software distribution libraries, ...)" (then-current version only) | Yes (hostable) | Current version, license allows distribution |
| nVidia Unofficial ForceWare | 82.69 (modified third-party driver) | No: mdgx.com only | n/a (modified NVIDIA driver) | No | No | Not from the publisher; unofficial modification |
| PC Image Editor | Unknown | No: address now redirects to program4pc.net Photo-Editor_Setup.exe (57 MB, 2021, current product); no old versions found | Commercial (current) | n/a | No | No 9x version served |
| Registrar Registry Manager Lite | 4.04 per mdgx (unverified) | No: rrtri.exe / RegistrarLite.exe is the current v9 home edition; supported-OS page lists XP SP3 and later only | Freeware home edition (current) | n/a | No | No 9x version served |
| Search & Replace (InfoRapid) | 3.1f (2003; "3.1f" in SERAPID.EXE; product page "Version 3.1f"). 98/ME very likely (no NT-only imports; not stated by author) | Yes: https://inforapid.de/sr/sr.exe (CSV address http://www.inforapid.com/sr/sr.exe redirects there) | Freeware for private use; commercial use 25 EUR | Yes: "may be copied freely, provided this happens in full original size and in unchanged form" - but private-use-only, which VERIFY-INSTRUCTIONS excludes from hosting | Yes (external) | Publisher's own server |
| WinZip Standard | 10.0 (7245) - README "requires Windows 98, Windows Me, Windows 2000, or Windows XP"; 11.2 MSI LaunchCondition "NOT Version9X" | Yes: https://download.winzip.com/winzip100.exe and /ov/winzip100.exe (http too). CSV file winzip121.exe (12.1) is served but not 9x | Shareware (evaluation), Authenticode-signed by WinZip Computing | Unknown (license encrypted inside setup) | Yes (external) | Publisher's own server |
| AviUtl | 0.99c (2008-02-17) - readme "Win98,Win2000以外のOSでは正常に動作しないかもしれません"; 0.99d+ name XP/Vista | Yes: http://spring-fragrance.mints.ne.jp/aviutl/aviutl99c.zip (author's past-versions page; https too). CSV GeoCities page is gone | Freeware | Not stated | Yes (external) | Author's own server |
| Convar PC Inspector File Recovery | 4.0 per the MSFN list; publisher evidence unknown | No. http://www.pcinspector.de redirects to https://datenretter.de/ (Convar data-recovery service), which has no PC Inspector pages or downloads (V, links listed). www.convar.com has no "inspector" text (V). https://www.pcinspector.de does not connect. | Freeware (historically; not verified) | unknown | No | The publisher no longer serves it |
| Convar PC Inspector Smart Recovery | 4.50.0001 per the MSFN list; publisher evidence unknown | No, same as above (V) | Freeware (historically; not verified) | unknown | No | The publisher no longer serves it |
| SlimBrowser (FlashPeak) | 4.07.100 per the MSFN list. The publisher's changelog https://www.slimbrowser.net/en/whatisnew.htm (V) still covers the 4.0x series ("Fixed bug about file->open/save dialog not popping up under Win98") | No. flashpeak.com/sbrowser redirects to slimbrowser.net (V). The download page offers only 18.0.0.0 "Compatible with Windows 7/8/10/11"; there is no old-versions link (V) | Freeware | unknown | No | Only the current version is served |
| SpywareBlaster (BrightFort, formerly Javacool) | 4.x. IA copy of javacoolsoftware.com/spywareblaster.html from 2011 (V): "works on Windows 98, ME, NT, 2000, XP, Vista, 7", version 4.4. The 2013 copy, version 5.0: "Windows 2000, XP, Vista, 7, 8". 4.6 per osr-final | No. The current page says "Windows 2000, XP, Vista, 7, 8, 10, 11" (V). https://www.brightfort.net/downloads/spywareblastersetup46.exe (and ...44/45) redirect to http://www.javacoolsoftware.net/downloads/spywareblastersetup50.exe (V). 5.0, 5.2 and 5.5 are still served (5.0 and 5.2 downloaded to a temp folder: Inno Setup 5.4.2, validly signed by BrightFort LLC) but are 2000+ | Free for home/personal use (the site offers a paid NV/AutoUpdate edition) | No (personal use; no grant seen) | No | No 9x version is served. 5.0 and later dropped 9x |
| STDU Viewer | 1.5.647 / 1.6.171, both KernelEx-only per the MSFN/OSR lists | No. www.stdutility.com now redirects to an unrelated gambling domain (xoilaclivettbdl.tv) (V). stduviewer.ru exists (V) but I could not confirm it is the publisher; it lists "Windows 2000/XP/2003/Vista/7/10" | Freeware for non-commercial use (not verified) | unknown | No | The original domain is lost, and it is KernelEx-only anyway |
| WinPatrol 2010 (98/SE/ME) | 17.0.2010.0 per the MSFN list | No. Every winpatrol.com path redirects to https://www.itamg.com/ (403 to curl; the page has no WinPatrol text) (V) | Commercial/freemium | No | No | The domain has passed to another company |
| ieSpell | V.2.5.1 per the MSFN list | No. www.iespell.com redirects to an unrelated contractexperience.com article (V) | Freeware for personal use (historically; not verified) | unknown | No | The domain is lost |
| Neutron (Robin Keir) | 1.07, the last release (https://keir.net/neutron.html (V): "Neutron 1.07 ZIP", "Updated June 23rd 2008"). There is no written OS statement; the PE header shows subsystem 4.0 with ANSI-only KERNEL32/USER32/GDI32/WSOCK32 imports (V), and MSFN lists it for 98SE | Yes: https://keir.net/download/neutron.zip (200, 6,765 bytes). http://keir.net/download/neutron.zip gives 301 to https (V) | Freeware | Not stated. readme: "distributed as freeware" (V), with no redistribution grant | **Yes** | The author's own server serves the 9x-capable build. External |
| McAfee Free Scan | unknown (web-based ActiveX scanner) | No. home.mcafee.com/Downloads/FreeScanDownload.aspx loops through redirects (curl gave up after 50) (V) | Commercial vendor, free online tool | No | No | Discontinued, and it was an online service |
| Powercom UPSMON | 2.743 per the MSFN list | No. https://www.pcmups.com.tw/download/Download/upsmon2_743.zip returns 404 (V). The Monitoring page offers only UPSMON PRO 2.63 for "XP, Vista, 7, 8, 10, 11" (V). Also: the http:// URL redirects to https, whose certificate fails the name check | Freeware with hardware | unknown | No | No 9x version is served. This is a UPS hardware utility |
| 98Lite Professional | 4.7 per the mdgx list | Unknown. http and https litepc.com/98lite.html both return a Cloudflare challenge (403) to curl and WebFetch (V) | Commercial (paid) | No | No | The page cannot be verified; commercial software, not known to be given away |
| AutoDesk AutoCAD | 2002 per the MSFN list | No. Autodesk sells only current releases (www.autodesk.com gives 403 to curl) | Commercial | No | No | Retail commercial software, never given away |
| Citrix Presentation Server Client Package | 9.246 per msfn list [S]; not verified | No [V]: listed URL is a reseller (firstdatasystems.com) returning 403; citrix.com legacy-client page returns 404 | Commercial product's free client | Unknown | No | No publisher download found |
| EasyBCD Community Edition | None: EasyBCD runs on Windows Vista+ and only *boots* 9x [V neosmart.net/EasyBCD: "Also boot into legacy systems ... Windows 9x"] | n/a | Free "Only for personal, non-commercial use" [V] | No (personal use) | No | Not a 9x program; personal-use license |
| Find And Run Robot | 2.80.01 per msfn [S]; 9x support not verified | Unknown [V]: donationcoder.com is behind a Cloudflare JS challenge (403 to curl and WebFetch) | Freeware/donationware [S] | Unknown | No | Could not verify; a Beacon client could not pass the Cloudflare challenge either |
| Intel 21143/DC21x4/DEC DE500 driver | 5.5 per msfn [S] | No [V]: old downloadcenter URLs redirect to Intel's 404 redirector; intel.com blocks automated fetching (403); no 9x download found | Intel driver license [S] | Unknown | No | Hardware driver; no 9x download found on Intel's site |
| Intel Application Accelerator | 2.2.2 / 2.3 per msfn [S] | No [V] (same as above) | Intel license [S] | Unknown | No | Same |
| Intel CHIPS Video Driver | unknown | No [V] | Intel license [S] | Unknown | No | Same |
| Intel Chipset Software Install Utility | 6.3.0.1007 / 3.20.1008 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel i740 Video Driver | PV40_9 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel PRO Series Network Drivers | 10.1 / 10.3 per msfn [S] | No [V] (Detail_Desc URL -> corpredirect 404 redirector) | Intel license [S] | Unknown | No | Same |
| Intel PRO/Wireless 2011 LAN PC Card | 3.1.1.31 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel PRO/Wireless 2011B LAN PC Card | 3.1.1.31 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel PRO/Wireless 2011B LAN PCI Adapter | 1.0 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel PRO/Wireless 2011B LAN USB Device | 1.0 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel PRO/Wireless 5000 LAN CardBus Adapter | 1.0.1.33 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel PRO/Wireless 5000 LAN PCI Adapter | 1.0.1.33 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel Video Driver | 13.6.1 / 6.7 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| Intel Xircom CreditCard Wireless | 4.15 per msfn [S] | No [V] | Intel license [S] | Unknown | No | Same |
| McAfee VirusScan 2006 | 10.0 per msfn [S] | No (mcafee.com 403; retail product, never given away) [S] | Commercial | No | No | Commercial, not given away; also a 2006 antivirus is useless today |
| PaintRibbon | None: mdgx lists "XP/2003/Vista/2008/7" [S availability.csv] | Unknown: softpedia (download portal) 403; author site bluuur.com not checked | "Freeware for personal use" [S] | No | No | Not a 9x program; personal-use license |
| Rivatuner | RC15 per msfn ("Version 2 works") [S] | Unknown [V]: guru3d.com (the author's official distributor) is behind a Cloudflare JS challenge | Proprietary freeware [S] | Unknown | No | Could not verify; Cloudflare challenge would also block Beacon |
| SwissKnife | V3.22 per msfn [S] | Unknown [V]: compuapps.com redirects to michel-louvain.com, Cloudflare JS challenge (403) | Freeware, terms unknown [S] | Unknown | No | Could not verify; Cloudflare challenge |
| System Safety Monitor | 2.0.8.583 per msfn [S] | No [V]: syssafety.com returns 403 from Cloudflare with no content; earlier research notes "publisher gone" | Commercial/free edition [S] | Unknown | No | Publisher site gone |
| Voodoo Win9x Drivers | various (fan builds) | No: 3dfx is defunct; falconfly.de is a fan archive (Cloudflare 403) [V] | 3dfx proprietary | No | No | Not a vendor server |
| XPlite + 2000lite Professional | n/a: XPlite/2000lite remove components from Windows XP/2000, not 9x [S] (litepc.com behind Cloudflare challenge [V]) | Unknown | Commercial/shareware | No | No | Not a 9x program; site unreachable |
| 3D Color Changer 4 | 4.00.2050.0 per mdgx ("98/2000/ME/XP/2003") [S] | No [V]: jote.pai.net.pl is a parked domain (aftermarket.pl); jotenet.cjb.net redirect service gone | Shareware ("uncrippled") [S] | Unknown | No | Publisher site gone |
| Adobe Reader | 6.0.x [V]: Adobe 6.0.1 requirements "Windows 98 Second Edition, Windows Millennium Edition, NT 4.0 SP6, 2000 SP2, XP"; 7.0 requires 2000/XP (adobe.com pages 2003/2004 via Internet Archive, evidence only) | Yes [V]: http(s)://ardownload.adobe.com/pub/adobe/reader/win/6.x/6.0/enu/AdbeRdr60_enu_full.exe and ardownload2 (200, 16,706,160 bytes, http and https) | Free proprietary (EULA) | No [V]: "Hosting the software independently is not permitted" (Adobe distribution page, 2004) | Yes (external) | Packaged as adobe-reader6; 6.0 not 6.0.6 (updates not found) |
| AnalogX Atomic TimeSync | 1.04 [V]: page "works on all versions of Windows, from Window 95 to Windows 7"; PAD OS list Win95/98/ME | Yes [V]: https://www.analogx.com/files/atsi.exe and http://www.analogx.com/files/atsi.exe (200, 354,536 bytes) | Freeware [V] | No [V]: FAQ "I don't normally allow offsite hosting"; linking to the file is welcomed | Yes (external) | Packaged as analogx-ats |
| AnVir Task Manager Free | None offered [V]: anvir.com says "For Windows XP / 7 / 8 / 10 / 11"; download page has only current taskfree.exe/.zip | No | Freeware (Free) / commercial (Pro) | Unknown | No | No 9x version served |
| Artweaver | Free 0.5.x per msfn/osr (0.5.7 needs KernelEx) [S] | No [V]: artweaver.de offers Free 8.1.6 (Windows 10 64-bit) and an archive of Artweaver *Plus* 1.5-7 only (paid, license key); no 0.5.x | Free (non-commercial) / Plus commercial | Unknown | No | Old 9x Free versions not served |
| Atomic Clock Sync | 2.7.0.3 per msfn [S] | No [V]: worldtimeserver.com serves only current atomic.exe (797,472 bytes, 2016), a Windows Time Service configurator whose PE subsystem version is 5.0 (Windows 2000+); inspected in temp only, deleted | Freeware ("No cost!") [V] | Unknown | No | Current version is NT-only; 2.7 not served |
| Avast! 4 Home | 4.8.1368 per msfn list [S] | No. avast.com serves only current product [V: site redirects to current home page] | Commercial / free-for-home AV | No | No | Old 9x build not offered by Avast; AV engines/definitions for 4.x discontinued |
| AVGFree | 7.5 per msfn [S] | No. free.grisoft.com -> 403 then avg.com current download [V] | Free for home | No | No | Not offered by publisher |
| Belarc Advisor | 8.1e per msfn [S] | No old version; current download is email-gated (form sends a link) [V] | Free for personal use | No | No | No 9x version served; download needs an email address |
| BitTorrent | 6.0 (98SE), 6.4 with KernelEx per lists [S] | No; bittorrent.com offers current only [V: home page] | Freeware/ad-supported | No | No | Old versions not served by publisher |
| BlueCat VST/DirectX plugins | unknown | Current Freeware Pack only (VST/VST3/AAX, "Legacy 32-bit Win" = current build, 2024/09/09) [V] | Freeware | unknown | No | No 9x version offered; OS support for current pack not 9x |
| Broadcom NetLink 4401 drivers | 4.60 per msfn [S] | Old support URLs redirect to broadcom.com/support/download-search (JavaScript portal); no 9x driver found [V redirect; portal content not readable] | Driver (vendor) | n/a | No | Could not find any 9x driver on Broadcom's portal; unverified whether any remain |
| Broadcom NetLink 57xx drivers | 10.24d per msfn [S] | Same as above [V redirect] | Driver (vendor) | n/a | No | Same as above |
| BurnAtOnce | unknown | No: burnatonce.net is now a gambling spam site [V] | Freeware (was) | unknown | No | Domain lost; no publisher server |
| Clickster | unknown | No: remlapsoftware.com redirects to an unrelated site [V] | Commercial | No | No | Publisher site gone |
| Clipboards (Splinterware) | unknown | No: product page redirects to splinterware.com home, which lists only System Scheduler and iDailyDiary [V] | Freeware (was) | unknown | No | Product no longer offered |
| ConeXware PowerArchiver | 2007 10.20 per msfn [S] | No: download page links only current PowerArchiver, PA command line 7.00/9.00 and toolbox; guessed old names (powarc1020/powarc61/powarc2007.exe) 404 on powerarchiver.cachefly.net [V] | Shareware | No | No | Old 9x versions not served |
| cpu-z | 1.78 "WINDOWS 98 32-bit version"; Vintage 1.04 "for windows 95/98" [V cpuid.com/softwares/cpu-z.html] | Yes: https://download.cpuid.com/cpu-z/cpu-z_1.78-win98.zip and .../cpu-z_1.04-win9x.zip (also www.cpuid.com/downloads/...; http -> 301 https) [V] | Freeware | Not clearly (only CPUID Terms of Service, personal licence) | **Yes (external)** | Packaged as cpu-z and cpu-z-vintage |
| CrystalCPUID | 4.15.5 (2009-05-09), "Vista/2003/XP/2000/NT4/Me/98/95" [V product page + readme] | Yes: https://crystalmark.info/download/archive/CrystalCPUID/CrystalCPUID415.zip (http -> 301 https) [V] | Freeware | **Yes**: "CrystalCPUID 4.x.y.z is a freeware and can be freely distributed." | **Yes (hosted)** | Packaged as crystalcpuid |
| CyberLink PowerDVD | 6 per msfn [S] | No (retail product; cyberlink.com sells current only) [S] | Commercial | No | No | Commercial, never given away |
| Deepburner | unknown for 9x | Only DeepBurner Free 1.9, requirements "Windows 7 / 10 / 11" [V] | Freeware / Pro trial | unknown | No | No 9x version offered |
| DirectX | 8.0 for 95 per msfn [S] | Microsoft product; row URL is oldversion.com | Microsoft redistributable | n/a | No | Microsoft item, left to the Microsoft agent |
| DiskInternals NTFS Reader | 2.1 (installer file version 2.1.0.0; page: "NTFS Reader for Windows 95, 98, Me") [V] | Yes: https://eu.diskinternals.com/download/NTFS_Reader.exe, also http:// directly (200) and www.diskinternals.com/download/ (301) [V]; not linked from the page any more (found by name) | Freeware | **Yes**: EULA s.2 "This SOFTWARE may be distributed, provided that ... only the original distributive file ... No money is charged" | **Yes (hosted)** | Packaged as ntfs-reader |
| DivX Codec | 5.2.1 per msfn [S] | No; row URL is free-codecs.com (portal); divx.com offers current only [S] | Commercial/free codec | No | No | Not served by publisher |
| Dvd Shrink | 3.2.0.15 [V dvdshrink.org "Current stable version"] | dvdshrink.org is a third-party fan site, not the author's; download page has no direct file link [V] | Freeware | unknown | No | Not the publisher's server; also a DVD copy-protection circumvention tool (legal risk) |
| EA Sports FIFA | 2005 per msfn [S] | No | Commercial game | No | No | Commercial, never given away |
| Easy Duplicate Finder | 1.4.4 per msfn [S] | No; site offers current version only [V download page exists; no old versions] | Commercial/trial | No | No | Old version not served |
| Eset Online Scanner | unknown | No 9x (web/online scanner for current Windows) [S] | Free service | No | No | No 9x version |
| FastStone Image Viewer | 5.3 (2014-10-24): help "Windows 98SE, ME, XP ..."; 5.4 help drops 98/ME [V both zips] | Yes: https://www.faststone.org/DN/FSViewer53.zip, https://www.faststonesoft.net/DN/FSViewer53.zip, http://www.faststonesoft.net/DN/FSViewer53.zip (200); FSViewerSetup53.exe likewise [V]. Not linked from current pages | Freeware for personal/educational use | No (copies right given to user; commercial use needs licence) | **Yes (external)** | Packaged as faststone-viewer (personal-use licence: parent to confirm acceptable as external) |
| Flash Player 10 | 10.x per blog [S] | No: Adobe removed all Flash Player downloads; row URL is a third-party blog [S] | Adobe freeware (EOL) | No | No | Not served by publisher |
| Foxit PDF Reader | 2.3 build 4015 per msfn [S] | No: foxitsoftware.com redirects to foxit.com current; guessed cdn01.foxitsoftware.com paths for 2.3/3.0 return 404 [V] | Freeware (was) | No | No | Old versions not served |
| Fresh Diagnose | 8.02 per msfn [S] | No file on freshdevices.com: its page's download link goes to download3k.com (portal) [V] | Freeware | unknown | No | Publisher does not serve the file itself |
| Get Right | 6.5 (current); getright.com home page says "Windows 7, Vista, XP, 2000, NT, ME, 98 & 95" [V] | No. http://download.getright.com/getright-download.exe and /getright_setup.exe answer 403 AccessDenied (S3), https has a certificate name mismatch; the filekicker mirror is 410 Gone [V] | Shareware with trial, still sold ($19.95) [V] | Unknown (not checked; moot) | No | Publisher's download is broken |
| Haali's Media Splitter | Last build before 18/11/2007; changelog on https://haali.net/mkv/: "18/11/2007 ... Removed Win9x support" [V]. Exact version number of the last 9x build unknown | No 9x build. Only the current MatroskaSplitter.exe (2013 changes, file dated 2015) at https://haali.net/mkv/MatroskaSplitter.exe [V] | Freeware | Unknown | No | Only a post-9x build is served |
| HWiNFO32 | 8.52 (current). hwinfo.com download page: "Portable for Windows 95 and later ... HWiNFO(R) 32 (legacy) is FREEWARE"; licenses page: "Windows 95 and later" [V]; exe subsystem 4.0 [V] | Yes: https://www.hwinfo.com/files/hwi_852.zip (403 to non-browser User-Agents, 200 with a browser UA; http->https) and official mirror https://www.sac.sk/download/utildiag/hwi_852.zip (200) [V] | Freeware (commercial use allowed) | No grant; EULA: "Embedding or bundling ... allowed only with explicit approval" [V] | **Yes (external)** | Packaged as hwinfo32 |
| Internet Explorer | 5.5 SP2 / 6 SP1 (msfn row) | n/a | Microsoft | n/a | Skipped | Microsoft product; left to the agent handling Microsoft items |
| Intervideo WinDVD | 6 (msfn row) [not verified] | No. Row URL is corel.com; WinDVD is a Corel retail product; no 9x build offered (not searched in depth) [I] | Commercial | No | No | Retail product, not given away |
| JAM Software HeavyLoad | 2.3 on 98 (msfn row) [not verified] | No 9x build. https://www.jam-software.com/heavyload links only HeavyLoad-x86-Setup_XP.exe and HeavyLoad-x64-Setup_XP.exe as legacy builds [V] | Freeware | Yes for JAM freeware (see TreeSize) | No | No 9x build served |
| JAM Software TreeSize Free | 2.1 (TreeSizeFree.exe 2.1.0.82, 2007). TreeSize Free page: "Download TreeSize Free for Windows 9x / ME" [V] | Yes: https://downloads.jam-software.de/treesize_free/TreeSizeFree_9x.zip (https 200; http 301 -> https) [V] | Freeware | **Yes**: "Provided that the software is in its original state and all files are distributed, JAM Software GmbH permits copies of the software to be made and distributed as long as duplication and distribution are not for profit or fundraising purposes." [V] | **Yes (hostable)** | Packaged as treesize-free |
| JetAudio Basic | Unknown. jetaudio.com offers "Retro jetAudio 4.9.2, Dec 12, 02, Free" at https://www.jetaudio.com/download/5fc01426-741d-41b8-a120-d890330ec672/jetAudio/JetAudio492.zip (200, 9,590,440 bytes, InstallShield 6-era installer) [V], but the publisher states no OS for it; current jetAudio needs 2000/XP/Vista/7 [V]. 8.0.16 (mdgx) is not offered; 7.5.5 only via Softonic | Retro 4.9.2 yes; any documented 9x version no | Freeware | Unknown (no license text seen) | Not packaged (needs verification) | 9x support of 4.9.2 undocumented; InstallShield cabs could not be opened to check the program |
| Jetico (Personal Firewall) | 1.0.1.61 (msfn row) [not verified] | No. http://www.jetico.com/jpfirewall.htm redirects to a page "Jetico Personal Firewall is discontinued" [V] | Freeware (was) | n/a | No | Discontinued, not served |
| JNES | Unknown (pre-1.0 builds). Downloads page: "builds prior to 1.0 have been archived and are no longer available for download" [V]. 1.1.1 Jnes.exe has PE subsystem 5.1 (not loadable on 9x) [V] | No 9x build; 1.1.1/1.2/1.2.1 at https://jabosoft.com/gallery/ are XP+ [V] | Freeware ("can't be sold or distributed in any commercial channel") [V] | Non-commercial redistribution implied, not explicit | No | Served builds are not 9x |
| KeepVid | n/a | No. keepvid.com redirects to a Wondershare video converter page [V] | Commercial web service | n/a | No | Not 9x software |
| Kerio Personal Firewall | 2.1.5 (msfn row) [not verified] | No. kerio.com redirects to gfi.ai (403) [V]; product discontinued [I] | Commercial/free personal | n/a | No | Not served |
| Kobarin (KbMedia Player) | 2.63a (OSR row) [not verified] | No. The row points to the Internet Archive; the author's host hwm5.gyao.ne.jp gives no answer [V]. Current location unknown (no web search available) | Freeware | Unknown | No | Author's server gone; IA not allowed |
| LaunchKey | Unknown | No. splinterware.com now offers only System Scheduler, iDailyDiary and mobile apps; launchkey.htm redirects to the home page; guessed file names 404 [V] | Freeware | Unknown | No | No longer offered |
| Legacy Family Tree Standard Edition | 6.0 (msfn row) [not verified] | No. Download page requires "Windows 7, 8, 10, or 11" [V]; no older versions listed | Freeware (standard edition) | Unknown | No | Only Win7+ served |
| Lightning Download | Unknown | No. lightningdownload.com is now an Italian programming blog [V] | Shareware | n/a | No | Domain repurposed |
| LimeWire | 4.14 (msfn row) [not verified] | No. limewire.com is an unrelated new service; LimeWire was shut down in 2010 by court order [I] | Was freeware/Pro | n/a | No | Not served |
| MATTsoft Boot Manager | 1.19g (download page lists mbtmgr_1.19g_win95.exe, "Windows 95/NT") [V] | No. Files are only on ftp://penguin.cz/pub/users/mhi/mbtmgr/ (connect timeout); http://penguin.cz redirects to seznam.cz; the files are not on martin.hinner.info (404) [V] | Free for non-commercial use | **Yes**: "MBTMGR MAY BE FREELY DISTRIBUTED AND USED IN NON-COMMERCIAL ENVIRONMENT AS LONG AS NO FILES ARE REMOVED OR MODIFIED IN ANY WAY, AND AS LONG AS NO MONEY OR ANY OTHER COMPENSATION IS ASKED OR ACCEPTED..." (http://martin.hinner.info/mbtmgr/license.html) [V] | No | License would allow hosting, but no official copy is reachable (would need the file from somewhere else; IA not used) |
| Maxthon | 3.5.2.1000 (msfn row) [not verified] | No. https://www.maxthon.com/en/history lists only Maxthon 7.x for Windows 7/8/10+ [V] | Freeware | n/a | No | No 9x build served |
| McNeel Rhino | 3.0 (msfn row) [not verified] | No. rhino3d.com "Legacy Downloads" archives start at Rhino 5 (key required) [V] | Commercial | No | No | Not served, commercial |
| mIRC | 6.35 (17/10/2008) is the last non-Unicode release; 7.1 (30/07/2010) is "the first stable release of the new Unicode version" (https://www.mirc.com/versions.txt) [V]; that 7.x does not run on 9x is [I] | No. get.html: "If you are looking for an older version of mIRC ... we cannot recommend using any older versions"; old file names redirect to get.html; get.php always gives mirc785.exe (XP+) [V] | Shareware (30-day evaluation) | No | No | Old versions not served |
| MiTeC (Windows Registry Recovery) | None: WRR 2.2.0 "OS compatibility: Windows XP ... Windows 11" (reads 9x hives but runs on XP+) [V] | https://www.mitec.cz/Downloads/WRR.zip is XP+ only | Free for private/educational/non-commercial use [V] | Not stated | No | No 9x build; also non-commercial only |
| More Control | 1.0 (mdgx row) [not verified] | No. The lewe.com page now shows Lewe's current products (TeamCal Neo etc.); More Control is not listed [V] | Freeware | Unknown | No | Not offered |
| MP3Splitter (Mega Mp3 Splitter) | 1.1 (06 March 2003); page: "Platform: Windows 95/98/NT/2000/XP" [V] | Yes: http://www.megax.it/mp3split/dl/mp3split.zip (http 200; https connection reset) [V] | Freeware [V] | Not stated | **Yes (external)** | Packaged as mega-mp3-splitter |
| Norton AntiSpam | 2005 (msfn row) | No. symantec.com/Norton (Gen Digital) offers no 9x versions [I] | Commercial | No | No | Retail product, not given away |
| Norton AntiVirus | 2005 (msfn row) | No, same as above [I] | Commercial | No | No | Retail product, not given away |
| Norton CleanSweep | 2002 per source list; unknown from publisher | No. symantec.com now redirects to broadcom.com/products/cybersecurity (opened) | Commercial | No | No | Retail product, never given away; no 9x download on Broadcom/Symantec |
| Norton GoBack | 4.0 per source list; unknown | No (symantec.com -> Broadcom, opened) | Commercial | No | No | Retail product; not served |
| Norton Internet Security | 2005 per source list; unknown | No (as above) | Commercial (subscription) | No | No | Retail product; not served |
| Norton PartitionMagic | 8.0 per source list; unknown | No (as above) | Commercial | No | No | Retail product; discontinued; not served |
| Norton Personal Firewall | 2005 per source list; unknown | No (as above) | Commercial | No | No | Retail product; not served |
| Norton Utilities | 2002 (6.0) per source list; unknown | No (as above) | Commercial | No | No | Retail product; not served |
| Norton Web Services | unknown | No (as above) | Commercial | No | No | Online service/retail; not served |
| nVidia Official ForceWare | 81.98 (page https://www.nvidia.com/en-us/drivers/win9x-8198/ "Win 9x/ME", Readme "Windows 98 / Windows Me", opened); 71.84 is the last with TNT/TNT2/GeForce 256 (INF, opened) | Yes: https://download.nvidia.com/Windows/81.98/81.98_forceware_win9x_english.exe (200; http 301->https); also 77.72, 71.84, 66.94, 56.64, 53.04, 45.23 files (200); 44.03 file 404 | Proprietary driver EULA (freeware download) | No ("may not otherwise copy the SOFTWARE") | Yes (external) | Packaged: nvidia-forceware (81.98) and nvidia-forceware-tnt (71.84) |
| nVidia Official RIVA 128 driver | 3.37 for Win 9x AGP/PCI (listed on https://www.nvidia.com/en-us/drivers/riva-drivers/, opened) | No: both detail pages (object/LO_20010606_3499.html, _3508.html) redirect to page-not-found; no file URL found | Proprietary driver | unknown (assume no) | No | Listed but no longer downloadable from nvidia.com |
| Ootake | Readme of 2.40 (opened, https://www.ouma.jp/file/Ootake240.zip): "It doesn't operate in Windows 98/Me"; 0.54 readme: "Windows98/Me might work. but untested." msfn lists 2.40 with KernelEx (not verified) | Old versions still served at https://www.ouma.jp/file/ (0.50 to 3.06) | Freeware (source included) | Not stated; homepage: "Please do not link directly for the file" | No | No confirmed 9x version; author asks not to link files directly, so an external entry would go against his wish |
| PC Wizard | 2008.1.81 per source list; unknown | No: cpuid.com/pcwizard.php and /softwares/pc-wizard.html redirect to softwares.html, which no longer lists PC Wizard (opened) | Freeware (commercial per list) | unknown | No | Removed from CPUID's site |
| pcAnywhere | 12.0 per source list; unknown | No (symantec.com -> Broadcom) | Commercial | No | No | Retail product; discontinued |
| Peer Monitor | 1.6.74 per source list; unknown | No: peermonitor.com and /download.aspx are a parked "/lander" page (opened) | unknown | unknown | No | Publisher site gone |
| Pixelformer | 0.9.6.3 per source list (KernelEx lists); publisher: "Windows XP, Windows Vista, Windows 7, Windows 8, Windows 10" (https://www.qualibyte.com/pixelformer/download.html, opened) | Yes, current 0.9.6.3 at https://downloads.qualibyte.com/Pixelformer.Setup.exe (not downloaded) | Freeware (not verified) | unknown | No | Publisher states XP or later; 9x only via KernelEx per community list, unverified |
| Project Dogwaffle | 1.2 free (2004 VB5 app; 9x support inferred from its VB5 runtime/installer, not stated by publisher) | Yes: https://www.thebest3d.com/dogwaffle/free/Dogwaffle_Install_1_2_free.exe (200; http 301->https); thebest2d.com mirror 403 | Freeware | Yes: "you may freely distribute it with your commercial projects, cover CDs/DVDs ... for download from your website ... 'Any reproduction in whole or in part is totally cool'" | Yes (external in draft) | Packaged: dogwaffle. Ships an LGPL 2.1 text for an unidentified component, so external until resolved |
| QuickTime Movie (QTM) Standard | unknown (row URL is Apple's ProRes decoder, not a 9x QuickTime) | No: the URL now redirects to https://support.apple.com/en-us/docs (opened) | Freeware (Apple) | No | No | Apple serves no 9x QuickTime |
| Quickview (QuickView Pro for DOS) | 2.61 (2016): "runs ... in a DOS shell under Windows 95/98/ME" (download.htm and QV.TXT, opened) | Yes: http://www.multimediaware.com/qv/qvpro261.zip (200 plain http, and https 200) | Shareware, 3-week trial, nag screens and start delay; registration still sold | Yes: "You are encouraged to share it with others ... pass along the complete unmodified archive"; "Shareware distributors may distribute this program if no files of the package are left out or modified" | Yes (external) | Packaged: quickview-pro. External because it contains LGPL FFmpeg of unnamed version |
| Race On | unknown (2009 game) | No: simbin.se is now an unrelated Swedish gaming blog (opened) | Commercial | No | No | Publisher gone; commercial game |
| RealPlayer Basic | unknown from publisher (list says 14.0) | No: https://www.real.com/realplayer offers only RealPlayer 25 (opened) | Freeware (ad-supported) | No | No | No 9x version served |
| RegCleaner | 4.3.0.780 per list; unknown | No: URL is majorgeeks.com (a download portal) and now goes to its front page; author's vtoy.fi does not resolve; macecraft.com redirects to jv16powertools.com (opened) | Freeware (per history, unverified) | unknown | No | Publisher no longer serves it; portals excluded |
| Registry Compactor | 1.1 per list; unknown | No: majorgeeks.com (portal) front page; publisher unknown | Commercial per list | unknown | No | Only on a download portal; publisher not identified |
| Servant Salamander | 1.52 (1998; CHANGES.TXT fixes for Win95, PE subsystem 4.0) and 2.0 (2001; readme "requires Windows 95, Windows 98, Windows ME, NT 4.0, 2000"); 2.54 SFX needs Windows 2000 (PE subsystem 5.0) | Yes but FTP only: ftp://ftp.altap.cz/pub/altap/salamand/salam152.zip and salen200.exe (listing and index.txt opened); http/https paths 404 | 1.52 freeware; 2.0 shareware 30-day trial (no longer sold) | 1.52 yes: "Permission to use, copy, and distribute this software ... without fee or royalty is hereby granted, provided that the full text of this license agreement appears on ALL copies"; 2.0 yes: evaluation version "may be freely distributed ... provided the distribution package is not modified. You may not charge any fee" | Yes (hosted) | Packaged: servant-salamander 1.52, hosted because the publisher serves it only over FTP. 2.0 also qualifies (hosted, trial with no way to buy), not packaged |
| SIW | unknown | unknown: gtopala.com answers 403 behind a Cloudflare JavaScript challenge (curl and WebFetch) | Commercial (freeware edition existed) | unknown | No | Could not open the publisher's site; no 9x version verified |
| Skype | 3.8 with KernelEx per list | No: skype.com redirects to teams.live.com (Microsoft; Skype retired) (opened) | Freeware, Microsoft-owned | No | No | Not served; Microsoft item |
| SmithMicro CheckIt Diagnostics | 7.1.1.5 per list; unknown | No: smithmicro.com has no such product; support.smithmicro.com did not connect (opened) | Commercial | No | No | Discontinued retail product |
| SmithMicro HotFax MessageCenter | 5.0.1 per list; unknown | No (as above) | Commercial | No | No | Discontinued retail product |
| Procomm Plus | 4.8 per list; unknown | No (symantec.com -> Broadcom) | Commercial | No | No | Retail product; discontinued |
| Sonix SN9C105 PC Camera Controller Driver | unknown | No. https://www.sonix.com.tw/sonix/product.do?p=SN9C105 returns a script-rendered page with no product or driver content [V]; Sonix is a chip vendor and no 9x driver download was found | driver (unknown) | unknown | no | Vendor page serves no 9x driver |
| Spybot Search & Destroy | 1.6.2 [S, not verified] | No. safer-networking.org offers only 2.x; FAQ names 2.4 (Vista/XP) as oldest legacy download [V]; /files/spybotsd162.exe and download.spybot.info/spybotsd162.exe give 404 [V] | freeware (1.x) | unknown | no | No 9x version on publisher's server |
| Sygate Personal Firewall | 5.6.2808 (row data) | No. Row URL is a third-party list (freeware-guide.com) that calls it "FREE for personal use ... (last freeware version)" [V]; Sygate was acquired by Symantec, product discontinued [S] | freeware for personal use | no | no | Publisher gone; only third-party copies |
| Symantec Desktop Firewall | 2.0 (row) | No. symantec.com redirects to broadcom.com/products/cybersecurity [V] | commercial | no | no | Retail product, not given away, not served |
| Symantec Ghost | 9.0 (row) | No (same redirect) [V] | commercial | no | no | Retail product, not served |
| Symantec Norton SystemWorks | 2005 8.03 (row) | No (same redirect) [V] | commercial | no | no | Retail product, not served |
| System Lock (r2 Studios) | 1.2 build 1, released 23 Sep 2001 [V]; 9x only via MSFN 98SE list (no primary statement) | Yes. https://www.r2.com.au/static/downloads/files/system-lock-v1.2b1.exe (https 200; http 301 -> https) [V] | freeware ("free to download and use") [V] | not stated | yes (weak) | Publisher serves it; packaged as system-lock, 9x evidence and uninstall name unverified |
| System Scheduler Free Version (Splinterware) | unknown | No. Current page lists Windows 7-11/Server only; download page offers only latest versions [V] | freeware (Free edition) / shareware (Pro) | unknown | no | No 9x version offered |
| TalkWorks PRO | 3.0 (row) | No (symantec.com -> broadcom.com) [V] | commercial | no | no | Retail product, not served |
| TextMaker Viewer 2010 | unknown | No. officeviewers.com redirects to softmaker.com [V]; SoftMaker "old versions" page lists only Office 2018/2021/2024 and FlexiPDF 2019/2022 [V]; guessed viewer file names on softmaker.net/down/ all 404 [V] | freeware viewer | unknown | no | Not served |
| Trend Micro Housecall | 6.5 (row) | No. Redirects to current HouseCall product page [V] | free online scanner (commercial vendor) | no | no | Web/online tool, 9x version not offered |
| UnFREEz | 2.1 (row) | No. whitsoftdev.com is a bare directory listing with an empty recursive "unfreez" folder [V] | freeware | unknown | no | Publisher site no longer serves the file |
| Unofficial Visual C++ 2008 Runtime | - | No. Row URL is a third-party blog (retrosystemsrevival.blogspot.com), not Microsoft [V: URL only] | unofficial repack of a Microsoft component | no | no | Not a publisher download; Microsoft-derived (other agent) |
| Unofficial Windows 95B/95C OSR 2.x Upgrades, Patches + Fixes List | - | No. Row URL is an Internet Archive copy of a web page (walbeehm.com) | list of links, not software | - | no | Not software; Internet Archive only |
| WinFax Basic | 10.02 (row) | No (symantec.com -> broadcom.com) [V] | commercial | no | no | Retail product, not served |
| WinFax PRO | 10.02 (row) | No (same) [V] | commercial | no | no | Retail product, not served |
| Wink | 2.0 era (changelog lists 2.0) - 9x not verified | No. Only Wink 3.0 is served (https://www.debugmode.com/download?name=winkwindows, winksetup.exe 5,729,904 bytes) [V]; its installer is NSIS-3 Unicode (needs NT) and readme says "tested in Windows 7 to Windows 10" [V] | freeware | no: "You may not re-distribute this program without contacting the author and getting his consent" [V] | no | Served version is not 9x |
| WinRAR | 3.93 is the row's value (osr-final=3.93); which 4.x is last for 9x not verified (rarnew.htm unreachable) | Yes, on 2026-09-29 early checks: https://www.rarlab.com/rar/wrar393.exe (200, 1,364,522 bytes), wrar380.exe (1,234,120), wrar371.exe, wrar400/401/411/420.exe all 200 [V]; http:// redirects to https:// [V]. Later all connections to www.rarlab.com (and www.win-rar.com) failed (TCP connect timeout / ECONNREFUSED) | shareware, 40-day trial [S] | possibly yes (the WinRAR license traditionally allows free distribution of the unmodified trial) [S, not verified: license could not be downloaded] | yes (not packaged) | Publisher serves old versions; could not download to verify 9x support, license or hash because rarlab.com became unreachable |
| WinZip | 10.0 (7245): readme "requires Windows 98, Windows Me, Windows 2000, or Windows XP" [V]; 11.2 MSI refuses 9x ("WinZip requires Windows Vista, Windows XP, or Windows 2000", condition NOT Version9X) [V]; 12.1 MSI: "It will not run under Windows 9X" [V] | Yes. http(s)://download.winzip.com/ov/winzip100.exe (200, 6,252,136 bytes) [V]. Not served: ov/winzip81.exe, winzip81sr1, winzip80, winzip70, winzip91, winzip95, winzip110, winzip111 (all 404) [V]; served but not 9x: winzip112, winzip120, winzip121, winzip145 [V] | shareware, 45-day evaluation [V] | yes, limited: evaluation copies may be distributed "exclusively by allowing downloads through the public Internet and without charge", but not "with other products of any kind", and WinZip "reserves the right to revoke any or all distribution rights" [V] | yes | Packaged by slice 1 as `winzip` (10.0); not duplicated here. No Windows 95 build (8.x) on WinZip's server |
| WISE Disk Cleaner | 2.91 (row) | No. wisecleaner.com download page offers only current WDCFree_11.3.9.859.zip etc. [V] | freeware (current) | unknown | no | Old 9x version not served |
| WISE Registry Cleaner | 2.9.5 (row) | No. Only WRCFree_11.3.3.735.zip offered [V] | freeware (current) | unknown | no | Old 9x version not served |
| Xmplayer (XMPlay) | 4.1 (current): "audio player for Windows (versions 95* to 11)", "* Windows 95/98 require an MSIMG32.DLL update" [V] | Yes. https://www.un4seen.com/files/xmplay41.zip and http://www.un4seen.com/files/xmplay41.zip (both 200) [V] | freeware for non-commercial use [V] | not stated | yes | Packaged as xmplay (external) |
| xplorer 2 lite | Lite: none for 9x. Zabkat's only 9x build is Pro 5.0.0.3 ("last version that works on windows 98") [V] | Lite for 9x: no. Current lite 6.3.0.3 is XP-11 [V]; row URL download.php?p=2 redirects to free-downloads.net [V] | lite: free for home/academic/non-profit use | no | no (see xplorer2 Pro) | Covered by the xplorer2 Pro 98 build |
| xplorer2 Lite | as above | as above | as above | no | no (see Pro) | Duplicate of the row above |
| xplorer2 Pro | 5.0.0.3 (build 5003), author: "This is the last version that works on windows 98, for museum collectors" (https://www.zabkat.com/alldown.htm) [V] | Yes, with a Referer: https://www.zabkat.com/download.php?f=5003_98.exe returns the file only when Referer is a zabkat.com page; otherwise 302 to free-downloads.net [V] | commercial, 21-day trial + 10 days with nags, then refuses to start [V] | no: licence forbids "copy or distribute" [V] | yes | Packaged as xplorer2 (external); Beacon must send a Referer header |
| ZSoft Uninstaller | 2.4.1 (MSFN 98SE list); 2.5 in OSR KernelEx list; FAQ: "reports on it working in Windows 95, Windows 98, Windows ME" [V] | Yes. https://www.zsoft.dk/downloads/ZSoft_Uninstaller_2.4.1.exe and .../ZSoft_Uninstaller_2.5.exe (http 301 -> https) [V] | freeware, non-commercial use only [V] | no | yes | Packaged as zsoft-uninstaller 2.4.1 (external) |

## Packages written

All in `D:\Win98SE\beacon\packages\<id>\` with the downloaded file, LICENSE.TXT, RECORD.md and ENTRY.TXT. Defender (MpCmdRun -Scan -ScanType 3 -DisableRemediation) found no threats in any of them.

| id | Name | Version | Systems | Availability | File | Size | SHA-256 | Authenticode |
|---|---|---|---|---|---|---|---|---|
| cacheman | Cacheman | 5.50 | 95, 98, ME | external | cachm550.exe | 948802 | 2d28137bd126c8e1fdb456dfb076e03c26fbf7239c2c86dc2679eaffc0912b09 | not signed |
| fmlfns | FmLfns | 1.1 | 95, 98, ME | external | fmlfns95.exe | 49416 | aa500a714002aa51a64f4c9d5b6fd6042dc3c85f39ea554b0e9578e120ed2043 | not signed |
| inforapid-search-replace | InfoRapid Search & Replace | 3.1f | 98, ME, NT4, 2000 | external | sr.exe | 1037513 | fecbd8b862beaabf261d8b85ac3c4daaa899a5132bce705974c789d59d498f37 | not signed |
| notetab-light | NoteTab Light | 7.2 | 95, 98, ME, NT4, 2000 | hosted | NoteTab_Light_Setup.exe | 2060990 | b0923198ffd6dca66d8cca6242ef2781e8bf2cb9b0e0439d663aa42fa2856749 | not signed |
| winzip | WinZip | 10.0 (7245) | 98, ME, 2000 | external | winzip100.exe | 6252136 | 7ecb819cff97a67b2ac3b672471972cac9b9724899d5fe2e60792f453d591122 | valid: WinZip Computing |
| aviutl | AviUtl | 0.99c | 98, 2000 | external | aviutl99c.zip | 288663 | 169cc00ca4c68ed7915168afcac44b9af87860bb5980d661ca8dca38543f7772 | n/a (zip; see RECORD.md for the exe inside) |
| neutron | Neutron | 1.07 | 95, 98, ME, NT4, 2000 | external | neutron.zip | 6765 | 9a9ae494fe176d49abf2b764c00ffaa0d9a3b4ed9b270d0f30b5d337264b46a2 | n/a (zip; see RECORD.md for the exe inside) |
| analogx-ats | AnalogX Atomic TimeSync | 1.04 | 95, 98, ME, NT4, 2000 | external | atsi.exe | 354536 | b00c4f995854b087c5197bcf53bb8f4d692129c133dba1ba1567508db5df4402 | valid: AnalogX, LLC |
| adobe-reader6 | Adobe Reader | 6.0 | 98, ME, NT4, 2000 | external | AdbeRdr60_enu_full.exe | 16706160 | dba7eb0e39e54d427a7fdb86b84cb563e8a40f1c187179313549ca4761437db2 | valid: Adobe Systems, Incorporated |
| cpu-z | CPU-Z | 1.78 | 98 | external | cpu-z_1.78-win98.zip | 1154222 | e32663cd4982f616a01acd9e57dbf365a9145adee250b0d6e0a29346fa085128 | n/a (zip; see RECORD.md for the exe inside) |
| cpu-z-vintage | CPU-Z Vintage Edition | 1.04 | 95, 98 | external | cpu-z_1.04-win9x.zip | 1446689 | 5bbd2a01cf2768248b82f93338815ee1e37445fa255d514272db7ade72bcbc78 | n/a (zip; see RECORD.md for the exe inside) |
| crystalcpuid | CrystalCPUID | 4.15.5 | 95, 98, ME, NT4, 2000 | hosted | CrystalCPUID415.zip | 639998 | 6a053caf3e7132695e6ccb3f151f5b28ba1d3929d877ee7119b106f024c23ef4 | n/a (zip; see RECORD.md for the exe inside) |
| ntfs-reader | DiskInternals NTFS Reader | 2.1 | 95, 98, ME | hosted | NTFS_Reader.exe | 3470933 | bdd06e58a0c6c85f2f2db14d12fbea6d353a8cd2da62dbd889192af6bbce5c1b | not signed |
| faststone-viewer | FastStone Image Viewer | 5.3 | 98, ME | external | FSViewer53.zip | 7204728 | a22af33858dad8f1f2ce4dd33c1fdd8995f6ef58dd4996a511f42061355e2c38 | n/a (zip; see RECORD.md for the exe inside) |
| faststone-viewer | FastStone Image Viewer | 5.3 | 98, ME | external | FSViewerSetup53.exe | 5806407 | a4df2303edcf8cda50f76452339ae8104c9197db87e55a6f720431afe68f3e3b | not signed |
| treesize-free | TreeSize Free | 2.1 | 95, 98, ME | hosted | TreeSizeFree_9x.zip | 739972 | 98c52603ebd2278aa3abea9331f84cb71b1f7d291c14810856c81ac8dbf2afdc | n/a (zip; see RECORD.md for the exe inside) |
| hwinfo32 | HWiNFO32 | 8.52 | 95, 98, ME, 2000 | external | hwi_852.zip | 20828120 | 0ce80064422e128a0f4257733c41e02970b5997a04361accc1f7f2f4b059f1ed | n/a (zip; see RECORD.md for the exe inside) |
| mega-mp3-splitter | Mega Mp3 Splitter | 1.1 | 95, 98, NT4, 2000 | external | mp3split.zip | 356039 | e3c74c7a844f8d080bf78f35cee34b910073e12f5b480cd63b082fdf70d7a6cc | n/a (zip; see RECORD.md for the exe inside) |
| nvidia-forceware | NVIDIA ForceWare display driver | 81.98 | 98, ME | external | 81.98_forceware_win9x_english.exe | 12458912 | e05b92b1322f8d01549995ddd00a9dca93d83358ee78e868acedca9dc6c7c910 | valid: NVIDIA Corporation |
| nvidia-forceware-tnt | NVIDIA ForceWare display driver (TNT and GeForce 256) | 71.84 | 98, ME | external | 71.84_win9x_english.exe | 11232793 | c0657392fdd4ee41504e35e89f926e3bf174d25662809b7353b135efce588b94 | not signed |
| dogwaffle | Project Dogwaffle | 1.2 | 95, 98, ME, NT4, 2000 | external | Dogwaffle_Install_1_2_free.exe | 4558273 | acd8618fe3600439c932803a69cfde2c4a64cdd1b5c6f3d8cafce94eb7b9442e | not signed |
| quickview-pro | QuickView Pro for DOS | 2.61 | 95, 98, ME | external | qvpro261.zip | 1223996 | e276a25bfc421e123dec29902444263cfb3deedb4bd1430424690346213bcfb5 | n/a (zip; see RECORD.md for the exe inside) |
| servant-salamander | Servant Salamander | 1.52 | 95, 98, ME, NT4, 2000 | hosted | salam152.zip | 211773 | a8cbff2e25b602e8ae06162e6b669ea5850cbcfc09550fd96e93bc88419c0949 | n/a (zip; see RECORD.md for the exe inside) |
| xplorer2 | xplorer2 Professional | 5.0.0.3 | 98 | external | 5003_98.exe | 2969032 | a378c55e744367ceb2ebadb60eb8fb4d4c79789c7ad7b75a1f3918ccf4bb758a | valid: Nikolaos Bozinis |
| xmplay | XMPlay | 4.1 | 95, 98, ME, 2000 | external | xmplay41.zip | 337689 | f364d9490d722d1ff21b9a027d803cbf4d5489422b39b782580085bbc463dd5e | n/a (zip; see RECORD.md for the exe inside) |
| zsoft-uninstaller | ZSoft Uninstaller | 2.4.1 | 95, 98, ME | external | ZSoft_Uninstaller_2.4.1.exe | 917947 | f1aba17ef54b71127e32c0ef609ad977d8ba57c57cbc871a600aca5752cc16eb | not signed |
| system-lock | System Lock | 1.2 build 1 | 98 | external | system-lock-v1.2b1.exe | 160147 | e973570a9bfd7398d92fc3b3327bca0122dfa1f0ad1b5da8e1b63d5c70cccd68 | not signed |
| servant-salamander-2 | Servant Salamander 2.0 | 2.0 | 95, 98, ME, NT4, 2000 | hosted | salen200.exe | 1361121 | 9682a428696d0bce07fb854bebac562b0522cda08b582448df30da7da76c8513 | not signed |

## Qualifying but not packaged

- WinRAR (RARLAB): rarlab.com first answered 200 for wrar371, 380, 393, 400, 401, 411 and 420, then stopped accepting connections from this host (retried 2026-09-29, still refused on ports 80 and 443). Last 9x version, license text and hashes unverified. Probably the most useful entry here; retry later.
- Leads outside the CSV: WinCorner still serves FmView 2.0 and FmExtMan 1.2 for 9x; WinZip's server also has WinZip 9.0 and WinZip Self-Extractor 3.0 (9x status not checked). jetAudio "Retro" 4.9.2 is still served by COWON, but its Windows requirements are not stated and could not be verified.

## Details and problems, by slice

### Slice 1


(SysInternals Suite was excluded from this slice as Microsoft-owned.)

#### Packages written (6, D:\Win98SE\beacon\packages\<id>\: file, LICENSE.TXT, RECORD.md, ENTRY.TXT)

| id | Version | File | Size | SHA-256 | Defender | Availability |
|---|---|---|---|---|---|---|
| cacheman | 5.50 | cachm550.exe | 948,802 | 2d28137bd126c8e1fdb456dfb076e03c26fbf7239c2c86dc2679eaffc0912b09 | no threats | external |
| fmlfns | 1.1 | fmlfns95.exe | 49,416 | aa500a714002aa51a64f4c9d5b6fd6042dc3c85f39ea554b0e9578e120ed2043 | no threats | external |
| inforapid-search-replace | 3.1f | sr.exe | 1,037,513 | fecbd8b862beaabf261d8b85ac3c4daaa899a5132bce705974c789d59d498f37 | no threats | external (hostable under II.3 if Backport Labs accepts a private-use-only license) |
| notetab-light | 7.2 | NoteTab_Light_Setup.exe | 2,060,990 | b0923198ffd6dca66d8cca6242ef2781e8bf2cb9b0e0439d663aa42fa2856749 | no threats | hosted (pool/) + Fookes fallback |
| winzip | 10.0 (7245) | winzip100.exe | 6,252,136 | 7ecb819cff97a67b2ac3b672471972cac9b9724899d5fe2e60792f453d591122 | no threats | external |
| aviutl | 0.99c | aviutl99c.zip | 288,663 | 169cc00ca4c68ed7915168afcac44b9af87860bb5980d661ca8dca38543f7772 | no threats | external |

Defender: MpCmdRun -Scan -ScanType 3 per folder, engine 1.1.26080.3, signatures 1.459.466.0. Only winzip100.exe is Authenticode-signed (Valid, WinZip Computing). No publisher checksums exist for any of them.

#### Further qualifiers not packaged / leads

- WinCorner also still serves FmView 2.0 (Explorer file viewer, "Windows XP/2000/NT4/ME/98/95", shareware $16.50) and FmExtMan 1.2 (http://www.wincorner.com/files/fmxman.exe, "requires Windows ME/98/95"). Not in the CSV.
- download.winzip.com/ov/ also serves winzip90.exe (WinZip 9.0) and wzipse30.exe (Self-Extractor 3.0); 9x status not checked.

#### Problems / unresolved

- Silent switches unverified: Cacheman and S&R (Wise, generic `/s`), WinZip (unknown, ENTRY uses interactive `exe`), FmLfns (DOS ARJ self-extractor; the user must run INSTALL.EXE afterwards - needs a better recipe).
- Add/Remove names unverified except FmLfns (from its INF: "File Manager Long File Name Support (FmLfns)").
- License texts not readable for Cacheman (Wise), WinZip (encrypted SETUP.WZ) and FmLfns (WinHelp phrase compression; partial). LICENSE.TXT files say so and quote the publisher's statements instead.
- NoteTab Light hosting depends on 7.2 staying the "then-current version" (EULA s.6) and on reading s.5 ("no bundling") as not covering a catalog download.
- InfoRapid S&R: hosting allowed by its license, but it is private-use-only freeware; decision left to Backport Labs (entry written as external).
- Nothing was run and no program was tested on 9x.

### Slice 2


Counts: 12 examined, 1 qualifies (Neutron), 1 package written.

##### Packages written

| id | version | file | size | SHA-256 | Defender | availability |
|---|---|---|---|---|---|---|
| neutron | 1.07 | neutron.zip (plain zip, Install: unzip {pf}\Neutron, Uninstall: files) | 6,765 | 9a9ae494fe176d49abf2b764c00ffaa0d9a3b4ed9b270d0f30b5d337264b46a2 | no threats (engine 1.1.26080.3, signatures 1.459.466.0) | external (https://keir.net/download/neutron.zip; http redirects to it) |

Folder: D:\Win98SE\beacon\packages\neutron\ (neutron.zip, LICENSE.TXT, RECORD.md, ENTRY.TXT). Neutron.exe is unsigned. No published checksum. NVD: 0 CVEs.

##### Further qualifiers not packaged
None.

##### Problems
- The WebSearch budget (200 per session) was exhausted, so publisher discovery used only curl and WebFetch on known domains.
- 98lite: litepc.com is behind a Cloudflare challenge, so whether an old 98lite download is still offered could not be checked.
- Neutron: the author gives no explicit 9x statement. The 9x support is inferred from the PE header and the MSFN listing. The readme dates 1.07 to "June 23rd 2007", the web page to 2008.
- SpywareBlaster: the older file names 4.4, 4.5 and 4.6 are silently redirected to 5.0 (2000+), so a catalog entry built on those URLs would install a build that does not run on 9x.
- Temporary copies in the scratchpad (sb50.exe, sb52.exe, the extracted Neutron files) were not run.

### Slice 3


#### Packages written

| id | version | file | size | SHA-256 | Signature | Defender | Availability |
|---|---|---|---|---|---|---|---|
| analogx-ats | 1.04 | atsi.exe | 354,536 | b00c4f995854b087c5197bcf53bb8f4d692129c133dba1ba1567508db5df4402 | Valid, AnalogX, LLC | no threats (engine 1.1.26080.3, sigs 1.459.466.0) | external (analogx.com https + http) |
| adobe-reader6 | 6.0 | AdbeRdr60_enu_full.exe | 16,706,160 | dba7eb0e39e54d427a7fdb86b84cb563e8a40f1c187179313549ca4761437db2 | Valid, Adobe Systems (VeriSign timestamp) | no threats | external (ardownload/ardownload2.adobe.com, http + https) |

Folders: D:\Win98SE\beacon\packages\analogx-ats\ and D:\Win98SE\beacon\packages\adobe-reader6\ (each: installer, LICENSE.TXT, RECORD.md, ENTRY.TXT).

#### Problems

- Web search was unavailable (session budget of 200 searches used up), so rows depending on search (Intel legacy downloads, Find and Run Robot, PaintRibbon author site) were checked only by direct fetches.
- Five publisher sites (donationcoder.com, guru3d.com, michel-louvain.com/compuapps.com, litepc.com, softpedia) are behind Cloudflare JS challenges; even if they serve 9x files, a Beacon 98 client could not download from them.
- Neither installer's silent switch could be verified: AnalogX uses its own installer (no documented switch), Adobe Reader 6.0 is a Netopsystems FEAD wrapper. Both ENTRY.TXT use `Install: exe` (interactive) and a guessed `Uninstall: registry` name, flagged in comments and RECORD.md.
- Adobe Reader 6.0 EULA text could not be extracted (inside the FEAD payload); LICENSE.TXT explains this and quotes Adobe's distribution policy. 6.0.x updates (6.0.1-6.0.6) were not found on Adobe's server.
- Adobe Reader 6.0: 182 NVD CPE matches, several CVSS 10.0; Warning added.

### Slice 4


#### Packages written (5)

| id | Version | File | Size | SHA-256 | Defender | Availability |
|---|---|---|---|---|---|---|
| cpu-z | 1.78 (win98 build) | cpu-z_1.78-win98.zip | 1,154,222 | e32663cd4982f616a01acd9e57dbf365a9145adee250b0d6e0a29346fa085128 | no threats | external |
| cpu-z-vintage | 1.04 | cpu-z_1.04-win9x.zip | 1,446,689 | 5bbd2a01cf2768248b82f93338815ee1e37445fa255d514272db7ade72bcbc78 | no threats | external (exe Authenticode-signed by CPUID, Valid) |
| crystalcpuid | 4.15.5 | CrystalCPUID415.zip | 639,998 | 6a053caf3e7132695e6ccb3f151f5b28ba1d3929d877ee7119b106f024c23ef4 | no threats | hosted (+ publisher URL) |
| ntfs-reader | 2.1 | NTFS_Reader.exe (NSIS) | 3,470,933 | bdd06e58a0c6c85f2f2db14d12fbea6d353a8cd2da62dbd889192af6bbce5c1b | no threats | hosted (+ publisher URLs) |
| faststone-viewer | 5.3 | FSViewer53.zip (also FSViewerSetup53.exe, 5,806,407, a4df2303edcf8cda50f76452339ae8104c9197db87e55a6f720431afe68f3e3b, kept for reference) | 7,204,728 | a22af33858dad8f1f2ce4dd33c1fdd8995f6ef58dd4996a511f42061355e2c38 | no threats | external |

Defender: MpCmdRun -ScanType 3 per folder, engine 1.1.26080.3, signatures 1.459.466.0. Folders: D:\Win98SE\beacon\packages\{cpu-z,cpu-z-vintage,crystalcpuid,ntfs-reader,faststone-viewer}\ each with the file, LICENSE.TXT, RECORD.md, ENTRY.TXT.

#### Problems

- WebSearch budget for the session was exhausted; no search-snippet evidence used. Rows marked [S] rely on the list data plus site redirects.
- NTFS_Reader.exe and FSViewer53.zip are not linked from any current page; they were found by requesting the file name in the publisher's own download folder. They are the publisher's servers, but the publisher may remove them.
- FastStone's licence is personal/educational use only. VERIFY-INSTRUCTIONS rejects such licences for hosting; listed only as external, parent should confirm.
- NTFS Reader NSIS: default folder, silent-mode behaviour and Add/Remove Programs name unknown (script not extractable); ENTRY uses `nsis /D={dir}` and `run "{dir}\Uninstall.exe" /S`.
- Broadcom's download portal is JavaScript-only; whether any 9x NetLink driver is still offered could not be determined.
- CPU-Z 1.78 win98 build: ME support not stated; Systems set to 98 only. Vintage: 95, 98.
- FastStone 5.3 has many image-parser CVEs whose NVD ranges include it (e.g. CVE-2021-26236, CVE-2022-36947); ENTRY has a Warning.

### Slice 5


#### Packages written

| id | Version | File | Size | SHA-256 | Defender | Availability |
|---|---|---|---|---|---|---|
| treesize-free | 2.1 | TreeSizeFree_9x.zip | 739,972 | 98c52603ebd2278aa3abea9331f84cb71b1f7d291c14810856c81ac8dbf2afdc | no threats | hosted (license allows non-profit redistribution), JAM URL as 2nd location |
| hwinfo32 | 8.52 | hwi_852.zip | 20,828,120 | 0ce80064422e128a0f4257733c41e02970b5997a04361accc1f7f2f4b059f1ed | no threats | external (sac.sk official mirror first, hwinfo.com second) |
| mega-mp3-splitter | 1.1 | mp3split.zip | 356,039 | e3c74c7a844f8d080bf78f35cee34b910073e12f5b480cd63b082fdf70d7a6cc | no threats | external (plain HTTP only) |

Folders: D:\Win98SE\beacon\packages\treesize-free, \hwinfo32, \mega-mp3-splitter (each: the file, LICENSE.TXT, RECORD.md, ENTRY.TXT; hwinfo32 also LICENSE.PDF). Defender engine 1.1.26080.3, signatures 1.459.466.0. All three are plain zips (`unzip`, `Uninstall: files`); none has a trial or nag.

Further qualifiers not packaged: none certain. Candidate needing verification: jetAudio 4.9.2 "Retro" (served by COWON, 9x support undocumented).

#### Problems

- WebSearch budget for the session was exhausted; all findings are from direct page fetches/curl. Some "last 9x version" values for dead or commercial products are only the msfn/mdgx figures and are marked "not verified".
- hwinfo.com returns 403 to non-browser User-Agents; Beacon must send a browser-like UA or rely on the sac.sk mirror. The HWiNFO file name carries the version, so the entry will break when 8.52 is replaced (likely within weeks).
- TreeSize Free: LICENSE.TXT is JAM's current license agreement; the 2007 build ships none, so the text in force in 2007 is unknown.
- TreeSize and HWiNFO: http:// redirects to https:// (no plain-HTTP copy). megax.it is HTTP-only.
- GetRight is still sold and claims 95/98 support, but its download server is broken (403); might be worth re-checking later.
- MATTsoft Boot Manager's license permits hosting, but no official copy is reachable.

### Slice 6


Counts: 27 rows; 4 qualify (NVIDIA ForceWare -> 2 packages, Project Dogwaffle, QuickView Pro, Servant Salamander); 5 packages written (the maximum).
Further qualifier not packaged: Servant Salamander 2.0 (ftp://ftp.altap.cz/pub/altap/salamand/salen200.exe, 1,361,121 bytes; 95/98/ME; redistributable evaluation, could be hosted; 30-day trial whose registration is no longer sold; CVE-2007-3314 in its PE viewer plugin). Other NVIDIA 9x drivers still served (77.72, 66.94, 56.64, 53.04, 45.23) are older duplicates, not packaged.

#### Packages written

| id | Version | File | Size | SHA-256 | Defender | Availability |
|---|---|---|---|---|---|---|
| nvidia-forceware | 81.98 | 81.98_forceware_win9x_english.exe | 12,458,912 | e05b92b1322f8d01549995ddd00a9dca93d83358ee78e868acedca9dc6c7c910 | no threats | external (Authenticode valid, NVIDIA 2005 cert) |
| nvidia-forceware-tnt | 71.84 | 71.84_win9x_english.exe | 11,232,793 | c0657392fdd4ee41504e35e89f926e3bf174d25662809b7353b135efce588b94 | no threats | external (not signed; no current NVIDIA page links it) |
| dogwaffle | 1.2 | Dogwaffle_Install_1_2_free.exe | 4,558,273 | acd8618fe3600439c932803a69cfde2c4a64cdd1b5c6f3d8cafce94eb7b9442e | no threats | external (hosting permitted by publisher; LGPL part unidentified) |
| quickview-pro | 2.61 | qvpro261.zip | 1,223,996 | e276a25bfc421e123dec29902444263cfb3deedb4bd1430424690346213bcfb5 | no threats | external (sharing allowed; FFmpeg LGPL source version unknown) |
| servant-salamander | 1.52 | salam152.zip | 211,773 | a8cbff2e25b602e8ae06162e6b669ea5850cbcfc09550fd96e93bc88419c0949 | no threats | hosted (publisher serves FTP only) |

Defender: engine 1.1.26080.3, signatures 1.459.466.0, 2026-09-29.

#### Problems

- WebSearch was unavailable (budget exhausted); research used direct page fetches only. SIW could not be checked (Cloudflare 403).
- NVIDIA: silent-install switches are not documented; the PackageForTheWeb/InstallShield setup has a setup.iss that reboots (BootOption=3), so entries run the installer interactively (`Install: exe` with an empty command line). 81.98's Readme lists TNT cards but its INF does not; 71.84 is linked from no NVIDIA page.
- NVIDIA EULA had to be decompressed from an InstallShield 6 cabinet with a custom deflate scan (7-Zip cannot open it).
- Dogwaffle: 9x support not stated by the publisher (inferred); LGPL component unidentified; uninstall name "project dogwaffle" is VB5-standard, not verified.
- Salamander 1.52: Windows 98/ME not named in its files (Win95/NT4 are); settings location unknown.
- `Install: exe` with no command line is used for three interactive installers; check that the client accepts an empty command line.

### Slice 7


Counts: 26 rows examined; 6 qualify under the rule "the publisher still serves a 9x version": System Lock, WinRAR, WinZip, XMPlay, xplorer2 Pro and ZSoft Uninstaller. The two xplorer2 Lite rows lead to the same Pro build and are not counted separately. Of those, 4 packaged here, WinZip packaged by slice 1, WinRAR not packaged (server unreachable).

#### Packages written (all `external`)

| id | Version | File | Size | SHA-256 | Signature | Defender |
|---|---|---|---|---|---|---|
| xplorer2 | 5.0.0.3 | 5003_98.exe | 2,969,032 | a378c55e744367ceb2ebadb60eb8fb4d4c79789c7ad7b75a1f3918ccf4bb758a | Valid, Nikolaos Bozinis (Zabkat) | no threats |
| xmplay | 4.1 | xmplay41.zip | 337,689 | f364d9490d722d1ff21b9a027d803cbf4d5489422b39b782580085bbc463dd5e | zip unsigned; xmplay.exe Valid, Un4seen Developments Ltd | no threats |
| zsoft-uninstaller | 2.4.1 | ZSoft_Uninstaller_2.4.1.exe | 917,947 | f1aba17ef54b71127e32c0ef609ad977d8ba57c57cbc871a600aca5752cc16eb | not signed | no threats |
| system-lock | 1.2 build 1 | system-lock-v1.2b1.exe | 160,147 | e973570a9bfd7398d92fc3b3327bca0122dfa1f0ad1b5da8e1b63d5c70cccd68 | not signed | no threats |

Defender: MpCmdRun -Scan -ScanType 3 -DisableRemediation per folder, engine 1.1.26080.3, signatures 1.459.466.0.
Each folder has the file, LICENSE.TXT, RECORD.md and ENTRY.TXT (ASCII only).

#### Problems

- rarlab.com (and win-rar.com) became unreachable from this host during the run (TCP connect timeouts; WebFetch ECONNREFUSED), after HEAD requests had returned 200 for wrar371/380/393/400/401/411/420.exe. WinRAR therefore is not packaged, and its last 9x version and license text are not verified. Worth retrying; it is probably the most useful qualifier in this slice.
- xplorer2: zabkat.com serves 5003_98.exe only with a zabkat.com Referer header. The catalog format has no way to express this; either the client always sends a Referer equal to the package Homepage, or this entry cannot work.
- XMPlay and ZSoft Uninstaller are "non-commercial use only" freeware. VERIFY-INSTRUCTIONS rejects personal-use-only licenses; I treated that as a hosting rule and listed them as external. The catalog owner should confirm.
- System Lock: 9x support rests only on the MSFN 98SE list and the 2001 date; license text and the Add/Remove name are unknown (ENTRY marks the uninstall name as unverified).
- Silent switches for xplorer2 and ZSoft (NSIS /S, /D=) are standard NSIS behaviour, not documented by the publishers.
- WinZip: slice 1 already wrote packages\winzip (10.0). I found the same result (10.0 is the last 9x build on WinZip's server; 12.1 and 11.2 refuse 9x). No Windows 95 WinZip (8.x) is on WinZip's server, so no winzip-95 package.
- I ran `MpCmdRun -SignatureUpdate -?` once by mistake while reading engine versions; it may have triggered a Defender signature update on the host. Nothing else outside packages\ and temp was touched.

### Extra package: Servant Salamander 2.0 (from the Servant Salamander row, packaged after the slices)

- id servant-salamander-2, version 2.0 (2001-02-28, English evaluation build). Readme in the installer: "requires Windows 95, Windows 98, Windows ME, Windows NT 4.0, Windows 2000 or later"; needs IE 4.0 (Requires: ie 4.0).
- Source: ftp://ftp.altap.cz/pub/altap/salamand/salen200.exe (Altap's own FTP; the http/https paths redirect or 404). Size matches Altap's FTP index.txt.
- Hosted: the license says "The evaluation (unregistered) version of the Software, may be freely distributed, with exceptions noted below, provided the distribution package is not modified. You may not charge any fee..."
- 30-day evaluation; a 2.0 license can no longer be bought (Altap only offers freeware 4.0, Windows 7+). Notice says so. Behaviour after 30 days unknown (not run).
- Altap's own installer, no silent switch (Install: exe, interactive). Uninstall: registry Servant Salamander 2.0 (from setup.inf).
- Warning for CVE-2007-3314 (PE viewer plugin buffer overflow). Bundled unace.dll (1998) and unrar.dll (2000) not checked against CVEs.
