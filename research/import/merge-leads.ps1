# Merges research\leads\*.csv into research\candidates.csv: one row per program,
# with every source that mentions it. Rows already marked verified, rejected or
# packaged in candidates.csv keep their status and notes.
#
# Status: lead (to check), excluded (shareware, commercial), verified, rejected, packaged.
$ErrorActionPreference = 'Stop'
$r = Split-Path -Parent $PSScriptRoot
$outFile = Join-Path $r 'candidates.csv'

# How much each source's license information can be trusted (higher wins).
$trust = @{ 'nirsoft-pad' = 5; 'mdgx-toy' = 4; 'mdgx-web' = 4; 'msfn-95' = 3; 'msfn-98se' = 2; 'msfn-kernelex' = 1; 'osr-final' = 1; 'osr-kernelex' = 1 }

function Key([string]$name) {
    $k = $name.ToLowerInvariant()
    $k = $k -replace '\(.*?\)', ' '
    $k = $k -replace '\b(v|version)\s*\d.*$', ' '
    $k = $k -replace '\s\d+(\.\d+)+.*$', ' '
    $k = $k -replace '[^a-z0-9+]', ''
    return $k
}

$keep = @{}
if (Test-Path $outFile) {
    foreach ($row in Import-Csv $outFile) { if ($row.status -in 'verified', 'rejected', 'packaged') { $keep[$row.key] = $row } }
}

$groups = @{}
foreach ($f in Get-ChildItem (Join-Path $r 'leads') -Filter *.csv) {
    foreach ($row in Import-Csv $f.FullName) {
        if (-not $row.name) { continue }
        $k = Key $row.name
        if (-not $k) { continue }
        if (-not $groups.ContainsKey($k)) { $groups[$k] = New-Object Collections.Generic.List[object] }
        $groups[$k].Add($row)
    }
}

$result = foreach ($k in ($groups.Keys | Sort-Object)) {
    if ($keep.ContainsKey($k)) { $keep[$k]; continue }
    $rows = $groups[$k]
    $best = $rows | Sort-Object { - [int]$trust[$_.source] } | Select-Object -First 1
    $classes = @($rows | ForEach-Object { $_.license_class } | Where-Object { $_ -and $_ -ne 'unknown' } | Select-Object -Unique)
    $class = if ($best.license_class -and $best.license_class -ne 'unknown') { $best.license_class } elseif ($classes.Count) { $classes[0] } else { 'unknown' }
    $kernelex = [bool]($rows | Where-Object { $_.needs -match 'KernelEx' -or $_.source -match 'kernelex' })
    $versions = @($rows | ForEach-Object { if ($_.version) { "$($_.source)=$($_.version)" } })
    [pscustomobject]@{
        key = $k
        name = $best.name
        versions = $versions -join '; '
        os = (@($rows | ForEach-Object { $_.os } | Where-Object { $_ } | Select-Object -Unique) -join '; ')
        kernelex = $(if ($kernelex) { 'yes' } else { '' })
        needs = (@($rows | ForEach-Object { $_.needs } | Where-Object { $_ } | Select-Object -Unique) -join '; ')
        category = $best.category
        license_class = $class
        license_conflict = $(if ($classes.Count -gt 1) { $classes -join ' / ' } else { '' })
        license = $best.license
        license_evidence = (@($rows | ForEach-Object { $_.license_evidence } | Where-Object { $_ } | Select-Object -Unique) -join ' ')
        homepage = [string](@($rows | ForEach-Object { $_.homepage } | Where-Object { $_ }) | Select-Object -First 1)
        download = [string](@($rows | ForEach-Object { $_.download } | Where-Object { $_ }) | Select-Object -First 1)
        sources = (@($rows | ForEach-Object { $_.source } | Select-Object -Unique) -join ' ')
        status = $(if ($class -in 'shareware', 'commercial' -or ($rows | Where-Object { $_.notes -match 'Microsoft component' }) -or $best.name -match '^(Microsoft|MS) ') { 'excluded' } else { 'lead' })
        notes = (@($rows | ForEach-Object { $_.notes } | Where-Object { $_ } | Select-Object -Unique -First 3) -join ' || ')
    }
}
$result | Export-Csv $outFile -NoTypeInformation -Encoding UTF8
"{0} programs from {1} source rows" -f @($result).Count, (@($groups.Values | ForEach-Object { $_.Count }) | Measure-Object -Sum).Sum
$result | Group-Object status | ForEach-Object { "  status $($_.Name): $($_.Count)" }
$result | Where-Object status -eq 'lead' | Group-Object license_class | Sort-Object Count -Descending | ForEach-Object { "  lead $($_.Name): $($_.Count)" }
"  leads needing KernelEx: $(@($result | Where-Object { $_.status -eq 'lead' -and $_.kernelex }).Count)"
"  leads in two or more sources: $(@($result | Where-Object { $_.status -eq 'lead' -and $_.sources -match ' ' }).Count)"
