/*****************************************************************************
*                                                                            *
*                         CrystalCPUID 4.x.y.z                               *
*                   Copyright (C) 2002-2007 hiyohiyo                         *
*                                                                            *
*                                            mail: hiyohiyo@crystalmark.info *
*                                   web :   http://crystalmark.info/?lang=en *
*****************************************************************************/

 CrystalCPUID 4.x.y.z is a freeware and can be freely distributed.
 CrystalCPUID 3.x.y.z is a freeware and can be freely distributed.
 CrystalCPUID 2.x.y.z is distributed under The modified BSD license.

------------------------------------------------------------------------------
 Operating Environment
------------------------------------------------------------------------------
        OS : Windows Vista/2003/XP/2000/NT4/Me/98/95
       CPU : Intel 386 or later & x64
 Recommend : Internet Explorer 4.0 or later
             WMI 1.5 (Windows Management Instrumentation) [NT4/98/95]
      Font : MS UI Gothic (9pt) [Japanese Edition]
             Tahoma (9pt)
             MS Sans Serif (8pt)

WMI 1.5 for NT4/98/95 Users
http://www.microsoft.com/downloads/details.aspx?displaylang=en&FamilyID=AFE41F46-E213-4CBF-9C5B-FBF236E0E875

Windows 95 Kernel Toys Set
http://www.microsoft.com/windows95/downloads/contents/WUToys/W95KernelToy/
If you put WinTop.vxd into CrystalCPUID installed directry, 
CrystalCPUID can detect correct CPU Usage. (9x Users only)

------------------------------------------------------------------------------
 Abbreviation
------------------------------------------------------------------------------
 - QPC = QueryPerformanceCounter
 - MMT = Multimedia Timer
 - WT  = Windows Timer
 - x64 = AMD64 & EM64T(Intel 64)
 - EIST= Enhanced Intel SpeedStep Technology
 - ODCM= On Demand Clock Modulation

------------------------------------------------------------------------------
 Contents for Normal version
------------------------------------------------------------------------------
File Name             |bit| Description
----------------------+---+---------------------------------------------------
ReadMeCpuid.txt       | - | ReadMe (English)
ReadMeCpuidJ.txt      | - | ReadMe (Japanese)
CrystalCPUID.txt      | - | About CrystalCPUID.exe
HistoryCpuid.txt      | - | History of CrystalCPUID.exe (English)
HistoryCpuidJ.txt     | - | History of CrystalCPUID.exe (Japanese)
SysInfo.txt           | - | About SysInfo.dll
HisrotySysInfo.txt    | - | History of SysInfo.dll (English)
HisrotySysInfoJ.txt   | - | History of SysInfo.dll (Japanese)
CrystalCPUID.exe      | 32| Main Program (9x/NT)
SysInfo.dll           | 32| Support DLL (9x/NT)
SysInfo.sys           | 32| Device Driver (NT5.x or later)
SysInfoX64.sys        | 64| Device Driver (NT5.x or later)
SysInfo.vxd           | 32| Device Driver (9x)
SysInfoNT4.sys        | 32| Device Driver (NT4)

------------------------------------------------------------------------------
 Contents for Pure x64 Edition
------------------------------------------------------------------------------
File Name             |bit| Description
----------------------+---+---------------------------------------------------
ReadMeCpuid.txt       | - | ReadMe (English)
ReadMeCpuidJ.txt      | - | ReadMe (Japanese)
CrystalCPUID.txt      | - | About CrystalCPUIDx64.exe
HistoryCpuid.txt      | - | History of CrystalCPUIDx64.exe (English)
HistoryCpuidJ.txt     | - | History of CrystalCPUIDx64.exe (Japanese)
SysInfo.txt           | - | About SysInfoX64.dll
HisrotySysInfo.txt    | - | History of SysInfoX64.dll (English)
HisrotySysInfoJ.txt   | - | History of SysInfoX64.dll (Japanese)
CrystalCPUIDx64.exe   | 64| Main Program
SysInfoX64.dll        | 64| Support DLL
SysInfoX64.sys        | 64| Device Driver

------------------------------------------------------------------------------
 Library
------------------------------------------------------------------------------
 Microsoft Foundation Classes C++ library (MFC)
 Copyright (C) 1992-1998 Microsoft Corporation

 PCI Debug Library for Win32
 kashiwano masahiro (http://www.otto.to/~kasiwano/)
 Customized by hiyohiyo

 libpng version 1.2.7
 Copyright (c) 1998-2004 Glenn Randers-Pehrson

 Zlib 1.2.1
 Copyright (C) 1995-2003 Jean-loup Gailly and Mark Adler

 Dib Section & libpng wrapper
 Copyright (c) 2000 Chihiro.SAKAMOTO (HyperWorks)

 MatrixStatic
 Copyright (C) 2002 by Nic Wilson  http://www.nicsoft.com.au
 Written by Nic Wilson nicw@bigpond.net.au
 All rights reserved

------------------------------------------------------------------------------
 Feature
------------------------------------------------------------------------------
 - Clock / System Clock / System Bus / Multiplier (Current & Original)
 - OverClock percentage
 - Cache information
 - Featrure Flags
 - CPUID list
 - Process rule
 - Multi Processor Support
 - Background change ( BMP, JPEG, GIF, PNG )
 - Save as Image (BMP, PNG)
 - Save as Text
 - Intel Enhanced SpeedStep Control (AT YOUR OWN RISK!!)
 - AMD K6/K7/K8 Multiplier & Volatege Change (AT YOUR OWN RISK!!)
 - VIA CyrixIII/C3 Multiplier (AT YOUR OWN RISK!!)
 - Create Shortcut of Changing Multiplier
 - Real Time Clock
 - Change Main Dialog Font
 - Support AMD64
 - Support EM64T(IA-32e)
 - Multiplier Mangement (AT YOUR OWN RISK!!)
   and so on...

------------------------------------------------------------------------------
 about Tasktray Icon
------------------------------------------------------------------------------
 - Left Click  = Show/Hide Main Dialog
 - Right Click = Popup Menu

------------------------------------------------------------------------------
 Date Format
------------------------------------------------------------------------------
 YYYY/MM/DD

------------------------------------------------------------------------------
 about measuring Clock
------------------------------------------------------------------------------
  F5 QPC + MMT (default)     =  500ms + (500ms*) Error Rate : +-0.2% @MMT
  F6 Windows Timer           = 1000ms + (500ms*) Error Rate : Large
  F7 Multimedia Timer        = 1000ms + (500ms*) Error Rate : +-0.1%
  F8 QueryPerformanceCounter =  100ms + (500ms*) Error Rate : +-0.01
  F9 QPC (No Load)           =  100ms            for SpeedStep/PowerNow!/etc.

// for F5 QPC + MMT (default)
if( ClockMMT * 0.995 < ClockQPC && ClockQPC < ClockMMT * 1.005 ){
	return ClockQPC;
}else{
	return ClockMMT;
}

------------------------------------------------------------------------------
 If you change FSB...
------------------------------------------------------------------------------
 If you change FSB, QueryPerformanceCounter don't work correctly!!
 There, you must use Multimedia Timer(F7).

------------------------------------------------------------------------------
 Real Time Clock
------------------------------------------------------------------------------
File > Customize > Real Time Clock 

- No Load ( QPC + MMT ) = default
- No Load ( MMT )       = for changing FSB.
- No Load ( QPC )       = 
- With Load ( QPC )     = for a part of Laptop/Notebook type PC.

 Only when clock cannot measure correctly, Please choose With Load ( QPC ) in 
Customize Dialog.
 Although load increases a little, clock can measure correctly.

------------------------------------------------------------------------------
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                       Multiplier Management for Power Users.
                      It does not operate in all environments.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------
 Multiplier Management use EIST / ODCM / PowerNow! / Cool'n'Quiet / LongHaul.

------------------------------------------------------------------------------
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                          Intel Enhanced SpeedStep Control
                      It does not operate in all environments.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------
 Required EIST or ODCM Support.

 Support CPU List...
 - Intel Core (Yonah)
 - Pentium M (Banias/Dothan)
 - Pentium 4 6xx (Prescott-2M)
 - Xeon (Nocona)

------------------------------------------------------------------------------
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                      AMD K6/K7/K8 Multiplier for Power Users.
                      It does not operate in all environments.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------
 Required PowerNow! or Cool'n'Quiet & BIOS & OS Support.

 - (K8 Only) When changing Multiplier, it may be made to change into 
   200MHz(default) by BIOS.
 - It may reboot depending on Power Options Properties, BIOS Setting and so on.

 Support CPU List...
 - K6 : K6-2+, K6-III+
 - K7 : Mobile Athlon XP-M, Mobile Athlon 4,
        Athlon XP (LV), Mobile Duron (Morgan)
 - K8 : Athlon 64 FX, Athlon 64, Mobile(DTR) Athlon 64, (Opteron)

 Multiplier which can be chosen...
 - K6 : 2.0x -  6.0x
 - K7 : 3.0x - 24.0x
 - K8 : 4.0x - 25.0x

 Multiplier which may be operated...
 - Athlon 64 3200+ (200x10.0) => 4.0x - 10.0x
 - Athlon 64 FX-51 (200x11.0) => 4.0x - 25.0x(!!)
 - Mobile Athlon XP-M 1500+ (133x10.0) => 3.0x - 10.0x

------------------------------------------------------------------------------
    | Current FID | Startup FID | Max FID | Currnet VID | Start VID | Max VID 
----+-------------+-------------+---------+-------------+-----------+---------
 K6 |      OK     |      NG     |    OK   |      NG     |     NG    |    NG   
 K7 |      OK     |      OK     |    OK   |      OK     |     OK    |    OK   
 K8 |      OK     |      OK     |    OK   |      OK     |     OK    |    OK   
------------------------------------------------------------------------------

for K8
 Core Voltage = Base Voltage (0.800V - 1.550V)
              + RVO1 (0.000V - 0.175V)
              + RVO2 (0.000V - 0.075V)
             => 0.800V - 1.800V

for K8 Low Voltage (*)
 Core Voltage = Base Voltage (0.700V - 1.450V)
              + RVO1 (0.000V - 0.175V)
              + RVO2 (0.000V - 0.075V)
             => 0.700V - 1.800V

 - RVO = Ramp Voltage Offset
 - RVO1/2 remains as it is.

(*) If you would like to use K8 Low Voltage Table, please set /K8LV option or
set K8LowVoltage=1 on CrystalCPUID.ini

------------------------------------------------------------------------------
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                       VIA CyrixIII/C3 Multiplier for Power Users.
                         It does not operate in all environments.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!AT YOUR OWN RISK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
------------------------------------------------------------------------------

 The changed multiplier may differ from the selected multiplier.
 If BIOS don't have multiplier change function, 

 Multiplier which can be chosen & operated...

 - Samuel / Samuel 2 Stepping 0
   3.0x - 8.0x
 - Samuel 2 Stepping 1 or later / Ezra
   3.0x - 12.0x
 - Ezra-T
   3.0x - 16.0x
 - Nehemiah
   4.0x - 16.0x

------------------------------------------------------------------------------
 Command line Option
------------------------------------------------------------------------------
for general
 /Q    = Save as PNG image. (temp.png)
 /S    = Save as Text. (temp.txt)
 /Pxx  = Select Processor (xx = 1-32)
 /R    = Launch Real Time Clock Dialog.
 /E    = Exit

 /CQ   = Enable Multiplier Management (Code Name:Crystal'n'Quiet)
 /HIDE = Hide Main Dialog
 /RESI = Residence

 /K7D  = Use K7 Desktop Voltage Table (Default = Mobile Voltage Table)
 /K8LV = Use K8 Low Voltage Table (Default = Normal Voltage Table)

 /VT310DP = for VIA VT-310DP only
            pipline length to 12!!

for EIST/K6/K7/K8/CyrixIII/C3
 /Fxx  = Change Multiplier (xx = FID, 0-15/31) 
for EIST/K7/K8
 /Vxx  = Change Voltage (xx = VID, 0-15)

example
 - K7 11.0x -> Exit (Processor#1)
   C:\CrystalCPUID.exe /F0 /P1 /E

 - K7 10.0x 1.100V -> Exit (Processor#1)
   C:\CrystalCPUID.exe /F14 V23 /P1 /E

 - K8  5.5x -> Show CrystalCPUID (Processor#1)
   C:\CrystalCPUID.exe /F3 /P1

 - Save Text/Image. -> Show CrystalCPUID (Processor#2)
   C:\CrystalCPUID.exe /S /Q /P2

Select ini file
 /INI=(FileName)
example 
 - /INI=hiyohiyo.ini
 - /INI=C:\test\hiyohiyo.ini

*default file name = CrystalCPUID.ini

------------------------------------------------------------------------------
 Detail Information of Multiplier (for K6/K7/K8)
------------------------------------------------------------------------------

 Multiplier Table for K6 (K6-2+/III+)
   4.5,  5.0,  4.0,  5.5,  2.0,  3.0,  6.0,  3.5

 Multiplier Table for K7

  11.0, 11.5, 12.0, 12.5,  5.0,  5.5,  6.0,  6.5,
   7.0,  7.5,  8.0,  8.5,  9.0,  9.5, 10.0, 10.5,
   3.0, 19.0,  4.0, 20.0, 13.0, 13.5, 14.0, 21.0,
  15.0, 22.0, 16.0, 16.5, 17.0, 18.0, 23.0, 24.0,

 example
 - FID =  0 => 11.0x
 - FID = 23 => 21.0x

 for K8

  Multiplier = FID / 2.0 + 4.0

 example
 - FID =  7 =>  7.5x (  7 / 2.0 + 4.0 )
 - FID = 20 => 14.0x ( 20 / 2.0 + 4.0 )

------------------------------------------------------------------------------
 Detail Information of Voltage (for K7/K8)
------------------------------------------------------------------------------

 K7 Mobile Voltage Table (Default)

  2.000, 1.950, 1.900, 1.850, 1.800, 1.750, 1.700, 1.650,
  1.600, 1.550, 1.500, 1.450, 1.400, 1.350, 1.300,     0,
  1.275, 1.250, 1.225, 1.200, 1.175, 1.150, 1.125, 1.100,
  1.075, 1.050, 1.025, 1.000, 0.975, 0.950, 0.925,     0,

 K7 Desktop Voltage Table

  1.850, 1.825, 1.800, 1.775, 1.750, 1.725, 1.700, 1.675,
  1.650, 1.625, 1.600, 1.575, 1.550, 1.525, 1.500, 1.475,
  1.450, 1.425, 1.400, 1.375, 1.350, 1.325, 1.300, 1.275,
  1.250, 1.225, 1.200, 1.175, 1.150, 1.125, 1.100,     0,

 for K8

  Base Voltage = 1.550 - VID * 0.025

 for K8 Low Voltage

  Base Voltage = 1.450 - VID * 0.025

------------------------------------------------------------------------------
 Version information
------------------------------------------------------------------------------
 (Major).(Minor).(Revision).(Release Number of SysInfo)
