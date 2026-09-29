# Creates the Ed25519 key that signs the Beacon 98 catalog.
#
# The private key is written encrypted (AES-256) with a random passphrase. The
# passphrase is kept encrypted with Windows DPAPI, so only this Windows account
# on this computer can use it without typing it. Back up two things:
#   1. beacon-signing-key.pem (the encrypted key)  -> USB drive
#   2. the passphrase (copy-key-passphrase.ps1)    -> password manager
# Either one alone is useless to someone who finds it.
param([string]$Dir = (Join-Path $env:USERPROFILE '.backportlabs'),
      [string]$OpenSsl = 'C:\Program Files\Git\usr\bin\openssl.exe',
      [string]$PublicOut = (Join-Path $PSScriptRoot '..\keys'))
$ErrorActionPreference = 'Stop'
$key = Join-Path $Dir 'beacon-signing-key.pem'
$pass = Join-Path $Dir 'beacon-signing-key.pass.dpapi'
if ((Test-Path $key) -or (Test-Path $pass)) { throw "A signing key already exists in $Dir. Not replacing it." }
New-Item -ItemType Directory -Force $Dir | Out-Null
New-Item -ItemType Directory -Force $PublicOut | Out-Null

# Only this account may read the folder.
& icacls $Dir /inheritance:r /grant:r "$($env:USERNAME):(OI)(CI)F" | Out-Null
if ($LASTEXITCODE -ne 0) { throw 'Could not restrict access to the key folder.' }

$bytes = New-Object byte[] 32
[Security.Cryptography.RandomNumberGenerator]::Create().GetBytes($bytes)
$phrase = [Convert]::ToBase64String($bytes)
ConvertTo-SecureString $phrase -AsPlainText -Force | ConvertFrom-SecureString | Set-Content $pass -Encoding ascii

$env:BEACON_KEY_PASS = $phrase
try {
    & $OpenSsl genpkey -algorithm ed25519 -aes-256-cbc -pass env:BEACON_KEY_PASS -out $key
    if ($LASTEXITCODE -ne 0) { throw 'openssl genpkey failed.' }
    $pubPem = Join-Path $PublicOut 'beacon-signing-key.pub.pem'
    & $OpenSsl pkey -in $key -passin env:BEACON_KEY_PASS -pubout -out $pubPem
    if ($LASTEXITCODE -ne 0) { throw 'openssl pkey failed.' }
} finally {
    Remove-Item Env:\BEACON_KEY_PASS -ErrorAction SilentlyContinue
    $phrase = $null
}

# The raw public key is the last 32 bytes of the DER form.
$b64 = ((Get-Content $pubPem) | Where-Object { $_ -notmatch '^-----' }) -join ''
$der = [Convert]::FromBase64String($b64)
$raw = $der[($der.Length - 32)..($der.Length - 1)]
$hex = ($raw | ForEach-Object { $_.ToString('x2') }) -join ''
$sha = [Security.Cryptography.SHA256]::Create().ComputeHash([byte[]]$raw)
$id = (($sha[0..7]) | ForEach-Object { $_.ToString('x2') }) -join ''
$txt = Join-Path $PublicOut 'beacon-signing-key.pub.txt'
[IO.File]::WriteAllText($txt, "Key-Id: $id`r`nAlgorithm: Ed25519`r`nPublic-Key: $hex`r`nCreated: $((Get-Date).ToString('yyyy-MM-dd'))`r`n", [Text.Encoding]::ASCII)
"Private key (encrypted): $key"
"Passphrase (DPAPI):      $pass"
"Public key:              $pubPem"
Get-Content $txt
