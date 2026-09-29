# Puts the passphrase of the catalog signing key on the Clipboard, to paste into
# a password manager. It is never printed. Clear the Clipboard afterwards.
$ErrorActionPreference = 'Stop'
$pass = Join-Path $env:USERPROFILE '.backportlabs\beacon-signing-key.pass.dpapi'
$s = Get-Content $pass | ConvertTo-SecureString
[Runtime.InteropServices.Marshal]::PtrToStringAuto([Runtime.InteropServices.Marshal]::SecureStringToBSTR($s)) | Set-Clipboard
'The passphrase is on the Clipboard. Paste it into your password manager, then copy something else to replace it.'
