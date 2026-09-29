# Verifies CATALOG.TXT against CATALOG.SIG with the public key, as a client would.
param([string]$Catalog = (Join-Path $PSScriptRoot '..\catalog\CATALOG.TXT'),
      [string]$OpenSsl = 'C:\Program Files\Git\usr\bin\openssl.exe',
      [string]$PublicKey = (Join-Path $PSScriptRoot '..\keys\beacon-signing-key.pub.pem'))
$ErrorActionPreference = 'Stop'
$sigText = Get-Content (Join-Path (Split-Path (Resolve-Path $Catalog)) 'CATALOG.SIG')
$hex = (($sigText -match '^Signature: ')[0]).Substring(11)
$bytes = New-Object byte[] ($hex.Length / 2)
for ($i = 0; $i -lt $bytes.Length; $i++) { $bytes[$i] = [Convert]::ToByte($hex.Substring($i * 2, 2), 16) }
$raw = [IO.Path]::GetTempFileName()
[IO.File]::WriteAllBytes($raw, $bytes)
& $OpenSsl pkeyutl -verify -rawin -pubin -inkey $PublicKey -in (Resolve-Path $Catalog) -sigfile $raw | Out-Null
$ok = $LASTEXITCODE -eq 0
Remove-Item $raw
if ($ok) { 'Signature valid.' } else { 'SIGNATURE INVALID.'; exit 1 }
