# Builds catalog\CATALOG.TXT from the pilot entries already in it and the
# package drafts in packages\<id>\ENTRY.TXT, following catalog\SOURCES.CSV:
#   include  yes/no
#   host     yes: our server keeps a copy (after the SourceForge location, if any)
#            no:  Backport Labs does not distribute it (external)
#   sf       path below http://downloads.sourceforge.net/project/, tried first
#   other    another publisher address, tried first (external packages)
# Writes catalog\UPLOAD.CSV: every pool path the catalog names, with its local file.
# Run sign-catalog.ps1 afterwards to check and sign.
param([string]$Packages = 'D:\Win98SE\beacon\packages',
      [string]$Pilot = 'D:\Win98SE\beacon\pilot',
      [switch]$Serial)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$catalogPath = Join-Path $root 'catalog\CATALOG.TXT'
$ansi = [Text.Encoding]::GetEncoding(1252)

function Blocks([string[]]$lines) {
    $blocks = @(); $cur = New-Object Collections.Generic.List[string]
    foreach ($l in $lines) {
        if ($l -eq '') { if ($cur.Count) { $blocks += ,($cur.ToArray()); $cur.Clear() }; continue }
        $cur.Add($l)
    }
    if ($cur.Count) { $blocks += ,($cur.ToArray()) }
    return ,$blocks
}
function FieldOf([string[]]$block, [string]$name) {
    foreach ($l in $block) { if ($l.StartsWith("$name`: ")) { return $l.Substring($name.Length + 2) } }
    return $null
}

$decisions = @{}
foreach ($r in Import-Csv (Join-Path $root 'catalog\SOURCES.CSV')) { $decisions[$r.id] = $r }

# The existing catalog: header block and the pilot packages (comments kept).
$existing = [IO.File]::ReadAllText($catalogPath, $ansi) -replace "`r`n", "`n" -split "`n"
$old = Blocks $existing
$header = $old[0]
# Packages with a draft in packages\ are always rebuilt from it; the others (the
# pilot) are kept from the catalog as they are.
$pilotBlocks = @($old | Select-Object -Skip 1 | Where-Object { -not (Test-Path (Join-Path $Packages "$(FieldOf $_ 'Package')\ENTRY.TXT")) })
$pilotIds = @($pilotBlocks | ForEach-Object { FieldOf $_ 'Package' })

$out = New-Object Collections.Generic.List[string[]]
foreach ($b in $pilotBlocks) {
    $id = FieldOf $b 'Package'
    if ($decisions.ContainsKey($id) -and $decisions[$id].include -ne 'yes') { continue }
    $out.Add($b)
}
$newIds = @($decisions.Values | Where-Object { $_.include -eq 'yes' -and $pilotIds -notcontains $_.id } | ForEach-Object id | Sort-Object)
foreach ($id in $newIds) {
    $entry = Join-Path $Packages "$id\ENTRY.TXT"
    if (-not (Test-Path $entry)) { throw "$id has no ENTRY.TXT" }
    $lines = @([IO.File]::ReadAllText($entry, $ansi) -replace "`r`n", "`n" -split "`n" | Where-Object { -not $_.StartsWith('#') })
    $blocks = Blocks $lines
    if ($blocks.Count -ne 1) { throw "$id`: ENTRY.TXT has $($blocks.Count) blocks, expected 1" }
    $out.Add($blocks[0])
}

# Apply the source decisions: SourceForge or publisher first, our copy last or not at all.
$result = New-Object Collections.Generic.List[string[]]
foreach ($b in $out) {
    $id = FieldOf $b 'Package'
    $d = $decisions[$id]
    if (-not $d -or (-not $d.sf -and -not $d.other -and $d.host -ne 'no')) { $result.Add($b); continue }
    $first = if ($d.sf) { "http://downloads.sourceforge.net/project/$($d.sf)" } elseif ($d.other) { $d.other } else { $null }
    $lines = New-Object Collections.Generic.List[string]
    $inSource = $false; $downloadDone = $false; $hasAvail = $false
    foreach ($l in $b) {
        if ($l.StartsWith('Availability: ')) { $hasAvail = $true; if ($d.host -eq 'no') { $lines.Add('Availability: external') } else { $lines.Add($l) }; continue }
        if ($l.StartsWith('Source: ')) { $inSource = $true; if ($d.host -eq 'no') { continue } }
        elseif ($inSource -and $l.StartsWith(' ')) { if ($d.host -eq 'no') { continue } }
        else { $inSource = $false }
        if ($l.StartsWith('Download: ') -and $first -and -not $downloadDone) {
            $parts = $l.Substring(10) -split ' '
            if ($parts[0] -eq $first) { $lines.Add($l); $downloadDone = $true; continue }   # assembled before
            if ($parts.Count -ne 3) { throw "$id`: first Download line already has extra locations" }
            $loc = $parts[0]; $size = $parts[1]; $sha = $parts[2]
            if ((Split-Path $first -Leaf) -replace '%20', ' ' -ne ((Split-Path $loc -Leaf) -replace '%20', ' ')) { Write-Warning "$id`: file names differ: $first vs $loc" }
            if ($d.host -eq 'no' -or $loc.StartsWith('http://')) { $lines.Add("Download: $first $size $sha") }
            else { $lines.Add("Download: $first $size $sha $loc") }
            $downloadDone = $true
            continue
        }
        $lines.Add($l)
    }
    if ($d.host -eq 'no' -and -not $hasAvail) {
        $i = [Array]::FindIndex($lines.ToArray(), [Predicate[string]]{ param($x) $x.StartsWith('Download: ') })
        $lines.Insert($i, 'Availability: external')
    }
    $result.Add($lines.ToArray())
}

# Every pool path must have a local file to upload.
$upload = New-Object Collections.Generic.List[object]
foreach ($b in $result) {
    $id = FieldOf $b 'Package'
    $dir = if (Test-Path (Join-Path $Packages $id)) { Join-Path $Packages $id } else { $null }
    if (-not $dir) {
        $map = @{ '7zip' = '7-zip'; 'infozip' = 'info-zip' }
        $name = if ($map.ContainsKey($id)) { $map[$id] } else { $id }
        $dir = Join-Path $Pilot $name
    }
    $field = $null
    foreach ($l in $b) {
        if ($l -match '^([A-Za-z-]+): (.*)$') { $field = $Matches[1]; $value = $Matches[2] }
        elseif ($l.StartsWith(' ')) { $value = $l.Substring(1) }
        else { continue }
        if ($field -notin 'Download', 'Source', 'License-File') { continue }
        $words = @($value -split ' ')
        foreach ($w in $words) {
            if ($w -notmatch '^pool/') { continue }
            $leaf = Split-Path $w -Leaf
            $candidates = @(Get-ChildItem $dir -Recurse -File -Filter $leaf -ErrorAction SilentlyContinue)
            $file = $null
            if ($field -ne 'License-File') {
                # Download and Source lines give size and SHA-256: take the file that matches.
                $file = $candidates | Where-Object { "$($_.Length)" -eq $words[1] -and (Get-FileHash $_.FullName).Hash.ToLower() -eq $words[2] } | Select-Object -First 1
            } else {
                # A license: the copy in a folder named after the version, else the top one.
                $ver = ($w -split '/')[2]
                $file = $candidates | Where-Object { $_.DirectoryName -like "*\$ver" } | Select-Object -First 1
                if (-not $file) { $file = $candidates | Where-Object { $_.DirectoryName -eq $dir } | Select-Object -First 1 }
            }
            if (-not $file) { throw "$id`: no local file matching $w in $dir" }
            $upload.Add([pscustomobject]@{ package = $id; key = $w; file = $file.FullName })
        }
    }
}

# Header: a new serial for each assembly when -Serial is given.
if ($Serial) {
    $today = (Get-Date).ToString('yyyyMMdd')
    $oldSerial = FieldOf $header 'Serial'
    $n = if ($oldSerial.StartsWith($today)) { [int]$oldSerial.Substring(8) + 1 } else { 1 }
    $header = @($header | ForEach-Object {
        if ($_.StartsWith('Serial: ')) { "Serial: $today{0:D2}" -f $n }
        elseif ($_.StartsWith('Date: ')) { "Date: $((Get-Date).ToString('yyyy-MM-dd'))" }
        elseif ($_.StartsWith('Expires: ')) { "Expires: $((Get-Date).AddDays(90).ToString('yyyy-MM-dd'))" }
        else { $_ } })
}

$text = (@(($header -join "`r`n")) + @($result | ForEach-Object { $_ -join "`r`n" })) -join "`r`n`r`n"
[IO.File]::WriteAllText($catalogPath, $text + "`r`n", $ansi)
$upload | Sort-Object key -Unique | Export-Csv (Join-Path $root 'catalog\UPLOAD.CSV') -NoTypeInformation -Encoding UTF8
"{0} packages ({1} new), {2} files to host" -f $result.Count, $newIds.Count, @($upload | Sort-Object key -Unique).Count
