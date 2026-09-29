# Shared helpers for the Beacon 98 lead importers. Dot-source this file.
# Windows PowerShell 5.1 compatible.

$ErrorActionPreference = 'Stop'
$script:ResearchRoot = Split-Path -Parent $PSScriptRoot
$script:CacheDir = Join-Path $PSScriptRoot 'cache'
$script:LeadsDir = Join-Path $script:ResearchRoot 'leads'
$script:UA = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0 Safari/537.36'
$script:Columns = 'source','name','version','os','needs','category','license_class','license','license_evidence','homepage','download','notes'

foreach ($d in $script:CacheDir, $script:LeadsDir) {
    if (-not (Test-Path $d)) { New-Item -ItemType Directory -Force $d | Out-Null }
}

function Get-CachedPage {
    <#
      Fetches $Url with curl.exe into cache\$Name. If a previous copy exists and the
      new one differs, the previous copy is kept as <Name>.<yyyyMMdd-HHmmss>.prev so
      reruns can be compared. With -Offline, the cached copy is used without fetching.
      Returns the local path.
    #>
    param([string]$Url, [string]$Name, [switch]$Offline)
    $path = Join-Path $script:CacheDir $Name
    if ($Offline) {
        if (-not (Test-Path $path)) { throw "Offline and no cached copy: $path" }
        return $path
    }
    $tmp = "$path.new"
    $code = & curl.exe -s -L -A $script:UA --max-time 120 -o $tmp -w '%{http_code}' $Url
    if ($code -ne '200' -or -not (Test-Path $tmp) -or (Get-Item $tmp).Length -eq 0) {
        if (Test-Path $tmp) { Remove-Item $tmp -Force }
        if (Test-Path $path) {
            Write-Warning "Fetch of $Url returned HTTP $code; using cached copy $path"
            return $path
        }
        throw "Fetch of $Url failed with HTTP $code and there is no cached copy"
    }
    if (Test-Path $path) {
        $old = (Get-FileHash $path -Algorithm SHA256).Hash
        $new = (Get-FileHash $tmp -Algorithm SHA256).Hash
        if ($old -ne $new) {
            $stamp = (Get-Item $path).LastWriteTime.ToString('yyyyMMdd-HHmmss')
            Move-Item $path "$path.$stamp.prev" -Force
            Write-Host "  changed since last run: $Name (previous kept as $Name.$stamp.prev)"
        }
        else { Remove-Item $path -Force }
    }
    Move-Item $tmp $path -Force
    return $path
}

function ConvertTo-PlainText {
    param([string]$Html)
    if ($null -eq $Html) { return '' }
    $t = $Html -replace '(?is)<script.*?</script>', ' ' -replace '(?is)<style.*?</style>', ' '
    $t = $t -replace '(?i)<br\s*/?>', ' ' -replace '<[^>]+>', ' '
    $t = [System.Net.WebUtility]::HtmlDecode($t)
    $t = $t -replace [char]0xA0, ' ' -replace '\s+', ' '
    return $t.Trim()
}

function New-Lead {
    param([hashtable]$h)
    $o = [ordered]@{}
    foreach ($c in $script:Columns) {
        $v = $h[$c]
        if ($null -eq $v) { $v = '' }
        $o[$c] = ([string]$v -replace '[\r\n]+', ' ').Trim()
    }
    return [pscustomobject]$o
}

function Write-LeadsCsv {
    param($Rows, [string]$Source)
    $out = Join-Path $script:LeadsDir "$Source.csv"
    # UTF-8 without BOM, all fields quoted, exact column order.
    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add(($script:Columns -join ','))
    foreach ($r in $Rows) {
        $vals = foreach ($c in $script:Columns) { '"' + ([string]$r.$c).Replace('"', '""') + '"' }
        $lines.Add(($vals -join ','))
    }
    [System.IO.File]::WriteAllLines($out, $lines, (New-Object System.Text.UTF8Encoding($false)))
    Write-Host "Wrote $($Rows.Count) rows to $out"
    $Rows | Group-Object license_class | Sort-Object Count -Descending |
        ForEach-Object { Write-Host ("  {0,-17} {1}" -f $_.Name, $_.Count) }
    return $out
}
