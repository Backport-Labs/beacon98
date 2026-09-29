# Checks CATALOG.TXT, writes it with Windows line endings, signs it and writes
# CATALOG.SIG next to it, then verifies the signature with the public key.
param([string]$Catalog = (Join-Path $PSScriptRoot '..\catalog\CATALOG.TXT'),
      [string]$OpenSsl = 'C:\Program Files\Git\usr\bin\openssl.exe',
      [string]$KeyDir = (Join-Path $env:USERPROFILE '.backportlabs'),
      [string]$PublicKey = (Join-Path $PSScriptRoot '..\keys\beacon-signing-key.pub.pem'))
$ErrorActionPreference = 'Stop'
$ansi = [Text.Encoding]::GetEncoding(1252)
$Catalog = (Resolve-Path $Catalog).Path

# 1. Text: Windows-1252, CR LF, no tabs or control characters, no trailing spaces.
$bytes = [IO.File]::ReadAllBytes($Catalog)
if ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF) { throw 'The catalog starts with a UTF-8 byte order mark.' }
$text = $ansi.GetString($bytes)
if ($ansi.GetString($ansi.GetBytes($text)) -ne $text) { throw 'The catalog has characters outside Windows-1252.' }
$lines = $text -replace "`r`n", "`n" -split "`n"
while ($lines.Count -gt 0 -and $lines[-1] -eq '') { $lines = $lines[0..($lines.Count - 2)] }
$errors = New-Object Collections.Generic.List[string]
for ($i = 0; $i -lt $lines.Count; $i++) {
    $l = $lines[$i]
    if ($l -match "[\x00-\x1F\x7F]") { $errors.Add("line $($i + 1): control character") }
    if ($l -match ' $') { $errors.Add("line $($i + 1): trailing space") }
    if ($l.Length -gt 1000) { $errors.Add("line $($i + 1): longer than 1000 characters") }
}

# 2. Structure: blocks of fields.
$blocks = @(); $cur = $null; $last = $null
for ($i = 0; $i -lt $lines.Count; $i++) {
    $l = $lines[$i]
    if ($l -eq '') { if ($cur) { $blocks += ,$cur; $cur = $null }; continue }
    if ($l.StartsWith('#')) { continue }
    if ($l.StartsWith(' ')) {
        if (-not $cur) { $errors.Add("line $($i + 1): continuation outside a field"); continue }
        $cur[$last] += "`n" + $l.Substring(1); continue
    }
    if ($l -notmatch '^([A-Za-z][A-Za-z0-9-]*): (.*)$') { $errors.Add("line $($i + 1): not a field"); continue }
    if (-not $cur) { $cur = [ordered]@{ _line = $i + 1 } }
    if ($cur.Contains($Matches[1])) { $errors.Add("line $($i + 1): field $($Matches[1]) repeated") }
    $last = $Matches[1]; $cur[$last] = $Matches[2]
}
if ($cur) { $blocks += ,$cur }
if ($blocks.Count -lt 1) { throw 'The catalog is empty.' }

$head = $blocks[0]
foreach ($f in 'Format', 'Catalog', 'Publisher', 'Serial', 'Date', 'Expires', 'Base') { if (-not $head.Contains($f)) { $errors.Add("catalog block: $f missing") } }
if ($head.Format -ne '1') { $errors.Add('catalog block: Format must be 1') }
if ($head.Serial -notmatch '^\d{10}$') { $errors.Add('catalog block: Serial must be YYYYMMDDNN') }
if ($head.Base -notmatch '^http://.+/$') { $errors.Add('catalog block: Base must be an http:// address ending in /') }

$ids = @{}
$sections = 'Utilities', 'Internet', 'Multimedia', 'Office', 'Development', 'Games', 'System'
# location size sha256 [location ...]; a location is a pool path or an http:// address.
$loc = '(?:http://[A-Za-z0-9.-]+/[A-Za-z0-9._/~%+-]+|[A-Za-z0-9._/-]+)'
$fileLine = "^$loc \d+ [0-9a-f]{64}( $loc)*$"
$urlLine = '^http://[A-Za-z0-9.-]+/[A-Za-z0-9._/~%+-]+ \d+ [0-9a-f]{64}( http://[A-Za-z0-9.-]+/[A-Za-z0-9._/~%+-]+)*$'
foreach ($b in $blocks[1..($blocks.Count - 1)]) {
    $where = "package at line $($b._line)"
    foreach ($f in 'Package', 'Name', 'Version', 'Section', 'Summary', 'License', 'License-File', 'Systems', 'Download', 'Install', 'Uninstall') {
        if (-not $b.Contains($f)) { $errors.Add("${where}: $f missing") }
    }
    if ($b.Package -notmatch '^[a-z0-9-]{1,32}$') { $errors.Add("${where}: bad Package identifier") }
    elseif ($ids.ContainsKey($b.Package)) { $errors.Add("${where}: Package $($b.Package) repeated") }
    else { $ids[$b.Package] = $true }
    if ($b.Section -and $sections -notcontains $b.Section) { $errors.Add("${where}: unknown Section") }
    if ($b.Summary -and $b.Summary.Length -gt 70) { $errors.Add("${where}: Summary longer than 70 characters") }
    $external = $b.Availability -eq 'external'
    if ($b.Contains('Availability') -and @('hosted', 'external') -notcontains $b.Availability) { $errors.Add("${where}: Availability must be hosted or external") }
    if ($external -and $b.Contains('Source')) { $errors.Add("${where}: an external package has no Source") }
    foreach ($f in 'Download', 'Source') {
        if ($b.Contains($f)) {
            foreach ($x in ($b[$f] -split "`n")) {
                $pattern = if ($external) { $urlLine } else { $fileLine }
                if ($x -notmatch $pattern) { $errors.Add("${where}: bad $f line '$x'") }
            }
        }
    }
    if ($b.Install -and $b.Install -notmatch '^(inno|nsis|msi|exe|unzip|copy)( |$)') { $errors.Add("${where}: unknown Install kind") }
    if ($b.Uninstall -and $b.Uninstall -notmatch '^(registry .+|files)$') { $errors.Add("${where}: bad Uninstall") }
}
foreach ($b in $blocks[1..($blocks.Count - 1)]) {
    if ($b.Contains('Depends')) { foreach ($d in ($b.Depends -split ',\s*')) { if (-not $ids.ContainsKey($d)) { $errors.Add("package $($b.Package): depends on unknown $d") } } }
}
if ($errors.Count) { $errors | ForEach-Object { "  $_" }; throw "$($errors.Count) problem(s) in the catalog." }

# 3. Write it back with CR LF endings, exactly as it will be published.
[IO.File]::WriteAllText($Catalog, (($lines -join "`r`n") + "`r`n"), $ansi)
"Catalog checked: serial $($head.Serial), $($blocks.Count - 1) packages."

# 4. Sign and verify.
$pass = Get-Content (Join-Path $KeyDir 'beacon-signing-key.pass.dpapi') | ConvertTo-SecureString
$env:BEACON_KEY_PASS = [Runtime.InteropServices.Marshal]::PtrToStringAuto([Runtime.InteropServices.Marshal]::SecureStringToBSTR($pass))
$raw = [IO.Path]::GetTempFileName()
try {
    & $OpenSsl pkeyutl -sign -rawin -inkey (Join-Path $KeyDir 'beacon-signing-key.pem') -passin env:BEACON_KEY_PASS -in $Catalog -out $raw
    if ($LASTEXITCODE -ne 0) { throw 'Signing failed.' }
} finally { Remove-Item Env:\BEACON_KEY_PASS -ErrorAction SilentlyContinue }
$sig = [IO.File]::ReadAllBytes($raw)
if ($sig.Length -ne 64) { throw "The signature is $($sig.Length) bytes, expected 64." }
& $OpenSsl pkeyutl -verify -rawin -pubin -inkey $PublicKey -in $Catalog -sigfile $raw | Out-Null
$ok = $LASTEXITCODE -eq 0
Remove-Item $raw
if (-not $ok) { throw 'The new signature does not verify with the public key.' }

$keyId = ((Get-Content (Join-Path $PSScriptRoot '..\keys\beacon-signing-key.pub.txt')) -match '^Key-Id: ')[0].Substring(8)
$hex = ($sig | ForEach-Object { $_.ToString('x2') }) -join ''
$sigFile = Join-Path (Split-Path $Catalog) 'CATALOG.SIG'
[IO.File]::WriteAllText($sigFile, "Key-Id: $keyId`r`nSignature: $hex`r`n", [Text.Encoding]::ASCII)
"Signed and verified: $sigFile"
