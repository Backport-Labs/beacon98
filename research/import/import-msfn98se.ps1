# Turns the classified MSFN "Last Versions of Software for Windows 98SE" table
# (research\candidates.md, made from msfn-list.csv) into research\leads\msfn-98se.csv.
$ErrorActionPreference = 'Stop'
$r = Split-Path -Parent $PSScriptRoot
$links = @{}
foreach ($row in Import-Csv (Join-Path $r 'msfn-list.csv')) { if (-not $links.ContainsKey($row.name)) { $links[$row.name] = $row } }
$out = New-Object Collections.Generic.List[object]
$inTable = $false
foreach ($line in Get-Content (Join-Path $r 'candidates.md') -Encoding UTF8) {
    if ($line -like '| Category | Name |*') { $inTable = $true; continue }
    if (-not $inTable) { continue }
    if (-not $line.StartsWith('|')) { if ($out.Count) { break } else { continue } }
    if ($line -like '|---*') { continue }
    $c = @($line.Trim('|').Split('|') | ForEach-Object { $_.Trim() })
    if ($c.Count -lt 8) { continue }
    $class = $c[4]
    $cls = switch -regex ($class) {
        '^A' { 'open-source' }
        '^B' { 'freeware' }
        '^C' { 'freeware-unclear' }
        default { if ($c[3] -match 'SHAR') { 'shareware' } else { 'commercial' } }
    }
    $src = $links[$c[1]]
    $out.Add([pscustomobject]@{
        source = 'msfn-98se'; name = $c[1]; version = ($(if ($c[2] -eq 'unspecified') { '' } else { $c[2] }))
        os = '98SE'; needs = ($(if ($c[6] -eq 'n/a') { '' } else { $c[6] })); category = $c[0]
        license_class = $cls; license = $c[5]
        license_evidence = ''; homepage = ''; download = ($(if ($src) { $src.link } else { '' }))
        notes = "class $class; tags $($c[3]); $($c[7])"
    })
}
$dir = Join-Path $r 'leads'
New-Item -ItemType Directory -Force $dir | Out-Null
$out | Export-Csv (Join-Path $dir 'msfn-98se.csv') -NoTypeInformation -Encoding UTF8
"$($out.Count) rows"
$out | Group-Object license_class | Sort-Object Count -Descending | ForEach-Object { "  $($_.Name): $($_.Count)" }
