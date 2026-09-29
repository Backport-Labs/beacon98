# Checks whether the download links of set-aside programs (shareware, commercial,
# freeware with unclear terms) still answer, and what they return. Reads only the
# answer headers; downloads nothing. Writes research\availability.csv.
param([int]$Threads = 16, [int]$TimeoutS = 25)
$ErrorActionPreference = 'Stop'
$r = Split-Path -Parent $PSScriptRoot
$rows = @(Import-Csv (Join-Path $r 'candidates.csv') | Where-Object {
    ($_.status -eq 'excluded' -or ($_.status -eq 'lead' -and $_.license_class -eq 'freeware-unclear')) -and ($_.download -or $_.homepage) })

$check = {
    param($row, $timeout)
    function Probe([string]$url, [string]$how) {
        $a = @('-sS', '-L', '--max-redirs', '8', '--max-time', "$timeout", '-A', 'Beacon98/0.5.0', '-o', 'NUL', '-D', '-',
               '-w', '##%{http_code}|%{url_effective}|%{content_type}')
        if ($how -eq 'head') { $a += '-I' } else { $a += @('-r', '0-0') }
        $out = & curl.exe @a $url 2>$null
        $tail = ($out | Where-Object { $_ -like '##*' } | Select-Object -Last 1)
        if (-not $tail) { return $null }
        $p = $tail.Substring(2).Split('|')
        $len = ''
        foreach ($l in $out) {
            if ($l -match '^[Cc]ontent-[Rr]ange: bytes \d+-\d+/(\d+)') { $len = $Matches[1] }
            elseif ($l -match '^[Cc]ontent-[Ll]ength: (\d+)' -and $how -eq 'head') { $len = $Matches[1] }
        }
        return [pscustomobject]@{ code = $p[0]; final = $p[1]; type = $p[2]; length = $len }
    }
    $url = if ($row.download) { $row.download } else { $row.homepage }
    $res = Probe $url 'head'
    if (-not $res -or $res.code -in '000', '403', '405', '400', '501') { $g = Probe $url 'get'; if ($g) { $res = $g } }
    if (-not $res) { $res = [pscustomobject]@{ code = '000'; final = ''; type = ''; length = '' } }
    $orig = ([uri]$url).Host
    $finalHost = if ($res.final) { try { ([uri]$res.final).Host } catch { '' } } else { '' }
    $finalPath = if ($res.final) { try { ([uri]$res.final).AbsolutePath } catch { '' } } else { '' }
    $isFile = $res.type -match 'octet-stream|x-msdownload|x-msdos-program|zip|x-msi|x-executable|x-dosexec|x-ms-installer' -or
              ($res.final -match '\.(exe|zip|msi)(\?|$)' -and $res.type -notmatch 'html')
    $kind = if ($res.code -eq '000') { 'dead: no answer' }
        elseif ($res.code -match '^(404|410)$') { 'dead: not found' }
        elseif ($res.code -match '^5') { 'dead: server error' }
        elseif ($res.code -notmatch '^(200|206)$') { "other: $($res.code)" }
        elseif ($isFile) { 'file' }
        elseif ($finalHost -and $finalHost -ne $orig -and $finalHost -notlike "*$($orig -replace '^www\.', '')" -and $finalPath -in '/', '') { 'moved: another site''s front page' }
        else { 'page' }
    [pscustomobject]@{
        key = $row.key; name = $row.name; license_class = $row.license_class; versions = $row.versions; os = $row.os
        url = $url; status = $res.code; kind = $kind; final_url = $res.final; content_type = $res.type; length = $res.length
        https_only = [string]($res.final -like 'https://*'); sources = $row.sources
    }
}

$pool = [runspacefactory]::CreateRunspacePool(1, $Threads)
$pool.Open()
$jobs = foreach ($row in $rows) {
    $ps = [powershell]::Create().AddScript($check).AddArgument($row).AddArgument($TimeoutS)
    $ps.RunspacePool = $pool
    [pscustomobject]@{ ps = $ps; handle = $ps.BeginInvoke() }
}
$results = foreach ($j in $jobs) { $j.ps.EndInvoke($j.handle); $j.ps.Dispose() }
$pool.Close()
$results | Sort-Object kind, name | Export-Csv (Join-Path $r 'availability.csv') -NoTypeInformation -Encoding UTF8
"$(@($results).Count) links checked"
$results | Group-Object kind | Sort-Object Count -Descending | ForEach-Object { "  {0,-36} {1}" -f $_.Name, $_.Count }
