; Beacon 98 setup script.
; Build with Inno Setup 5.4.3 (the last release that supports Windows 95/98):
;   ISCC.exe client\installer\BEACON98.ISS
; or run client\build\build.ps1 with -Iscc, which compiles BEACON98.EXE first.

#define AppName    "Beacon 98"
#define AppVersion "0.6.0"

[Setup]
AppName={#AppName}
AppVersion={#AppVersion}
AppVerName={#AppName} version {#AppVersion}
AppPublisher=Backport Labs
AppPublisherURL=https://github.com/Backport-Labs/beacon98
AppCopyright=Copyright (C) 2026 Backport Labs
AppComments=Installs free software on Windows 95, 98 and Millennium
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
AllowNoIcons=yes
LicenseFile=..\..\LICENSE
OutputDir=..\dist
OutputBaseFilename=B98SETUP
UninstallDisplayName={#AppName}
Compression=lzma
SolidCompression=yes
MinVersion=4.0,4.0
PrivilegesRequired=none

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Options:"; Flags: unchecked

[Files]
Source: "..\build\out\BEACON98.EXE"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\app\README.TXT"; DestDir: "{app}"; Flags: ignoreversion isreadme
Source: "..\..\LICENSE"; DestDir: "{app}"; DestName: "LICENSE.TXT"; Flags: ignoreversion

[Icons]
Name: "{group}\{#AppName}"; Filename: "{app}\BEACON98.EXE"; Comment: "Install free software for this computer"
Name: "{group}\Read Me"; Filename: "{app}\README.TXT"
Name: "{group}\Uninstall {#AppName}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\{#AppName}"; Filename: "{app}\BEACON98.EXE"; Tasks: desktopicon

[Run]
; Also after a silent update started by Beacon itself, so Beacon comes back.
Filename: "{app}\BEACON98.EXE"; Description: "Start {#AppName} now"; Flags: postinstall nowait

[UninstallDelete]
; INSTALLED.TXT and FILES\ stay, so a reinstalled Beacon can still remove packages.
Type: files; Name: "{app}\CATALOG.TXT"
Type: files; Name: "{app}\CATALOG.SIG"
Type: files; Name: "{app}\CATALOG.NEW"
Type: files; Name: "{app}\SIGNATUR.NEW"
Type: files; Name: "{app}\CAT?.TXT"
Type: files; Name: "{app}\CAT?.SIG"
Type: files; Name: "{app}\SIGNATUR.NEW"
Type: filesandordirs; Name: "{app}\DOWNLOAD"

[Code]
// Beacon holds the mutex Beacon98Running while it runs. When Beacon updates
// itself it starts this setup and closes once the user has read its log;
// wait up to five minutes for it to be gone before replacing its files.
function InitializeSetup(): Boolean;
var
  I: Integer;
begin
  I := 0;
  while CheckForMutexes('Beacon98Running') and (I < 600) do
  begin
    Sleep(500);
    I := I + 1;
  end;
  Result := True;
  if CheckForMutexes('Beacon98Running') then
  begin
    if not WizardSilent() then
      MsgBox('Beacon 98 is running. Close it, then run this setup again.', mbInformation, MB_OK);
    Result := False;
  end;
end;
