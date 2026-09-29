# Import NirSoft PAD files (bulk pads.zip) into research\leads\nirsoft-pad.csv.
# Keeps only tools whose PAD OS field or program web page mentions Windows 95/98/ME.
# Rerunnable. Usage: powershell -File import-nirsoft.ps1 [-Offline] [-SkipPages]
#   -Offline   : use cached copies only (no network)
#   -SkipPages : do not (re)fetch the per-tool program pages; use cached ones if present
param([switch]$Offline, [switch]$SkipPages)
. (Join-Path $PSScriptRoot '_common.ps1')
Add-Type -AssemblyName System.IO.Compression.FileSystem

$Source = 'nirsoft-pad'
$LicenseText = 'NirSoft freeware (redistribution allowed, unmodified, free of charge)'
# NirSoft has no central license page (checked 2026-09-29: /license.html etc. are 404, the About page
# has no license text). Each program page carries a "License" section, so that page is the evidence.

Write-Host "== $Source"
$zipPath = Get-CachedPage -Url 'https://www.nirsoft.net/pad/pads.zip' -Name 'nirsoft_pads.zip' -Offline:$Offline
Get-CachedPage -Url 'https://www.nirsoft.net/pad/pad-links.txt' -Name 'nirsoft_pad-links.txt' -Offline:$Offline | Out-Null
Get-CachedPage -Url 'https://www.nirsoft.net/pad/' -Name 'nirsoft_pad_index.html' -Offline:$Offline | Out-Null

$padDir = Join-Path $CacheDir 'nirsoft_pads'
if (Test-Path $padDir) { Remove-Item $padDir -Recurse -Force }
[IO.Compression.ZipFile]::ExtractToDirectory($zipPath, $padDir)
$utilDir = Join-Path $CacheDir 'nirsoft_utils'
if (-not (Test-Path $utilDir)) { New-Item -ItemType Directory $utilDir | Out-Null }

function Get-Section([string]$text, [string]$heading, [int]$len = 700) {
    $m = [regex]::Match($text, "(?i)\b$heading\b\s*(.{0,$len})")
    if (-not $m.Success) { return '' }
    $s = $m.Groups[1].Value
    # stop at the next typical NirSoft section heading
    $s = ($s -split '(?i)\s(?=(Versions History|Known Problems|Start Using|Using |Command-Line Options|Translating|Disclaimer|Feedback|License|System Requirements|Download)\b)')[0]
    return $s.Trim()
}

$rows = New-Object System.Collections.Generic.List[object]
$skippedNt = New-Object System.Collections.Generic.List[string]
$problems = New-Object System.Collections.Generic.List[string]
$files = Get-ChildItem $padDir -Filter *.xml -Recurse | Sort-Object Name
foreach ($f in $files) {
    try { [xml]$x = [IO.File]::ReadAllText($f.FullName) }
    catch { $problems.Add("$($f.Name): XML parse error: $($_.Exception.Message)"); continue }
    $p = $x.XML_DIZ_INFO.Program_Info
    $w = $x.XML_DIZ_INFO.Web_Info
    $name = [string]$p.Program_Name
    $ver = [string]$p.Program_Version
    $os = [string]$p.Program_OS_Support
    $type = [string]$p.Program_Type
    $page = [string]$w.Application_URLs.Application_Info_URL
    $dl = [string]$w.Download_URLs.Primary_Download_URL
    $req = [string]$p.Program_System_Requirements
    $cat = [string]$p.Program_Category_Class
    if (-not $cat) { $cat = [string]$p.Program_Specific_Category }

    # program page (web page only; never the binary)
    $pageText = ''
    if ($page) {
        $local = 'nirsoft_utils\' + (($page -replace '^https?://[^/]+/', '') -replace '[\\/:*?"<>|]', '_')
        if (-not $local.EndsWith('.html')) { $local += '.html' }
        $localFull = Join-Path $CacheDir $local
        try {
            if ($Offline -or ($SkipPages -and (Test-Path $localFull))) {
                if (Test-Path $localFull) { $pageText = ConvertTo-PlainText ([IO.File]::ReadAllText($localFull)) }
                else { $problems.Add("$name : program page not cached ($page)") }
            }
            else {
                $pp = Get-CachedPage -Url $page -Name $local
                $pageText = ConvertTo-PlainText ([IO.File]::ReadAllText($pp))
                Start-Sleep -Milliseconds 250
            }
        }
        catch { $problems.Add("$name : program page fetch failed ($page): $($_.Exception.Message)") }
    }
    $sysreq = Get-Section $pageText 'System Requirements'
    $licSec = Get-Section $pageText 'License' 500

    $padMentions9x = $os -match '(?i)Win(95|98|ME)\b|Windows ?(95|98|ME)\b|Win9x'
    $neg = "(?i)not supported|cannot work|can't work|doesn't work|does not work|won't work"
    $allMentions = [regex]::Matches($pageText, '(?i)[^.]{0,120}\b(Windows\s?(95|98|ME|9x)|Win(95|98|ME|9x))\b[^.]{0,120}')
    $posMentions = @($allMentions | Where-Object { $_.Value -notmatch $neg })
    $pageMentions9x = $posMentions.Count -gt 0
    if (-not ($padMentions9x -or $pageMentions9x)) {
        if ($allMentions.Count -gt 0) { $skippedNt.Add("$name ($os) [page mentions 9x/ME only negatively]") }
        else { $skippedNt.Add("$name ($os)") }
        continue
    }

    $notes = @()
    if ($padMentions9x) { $notes += 'PAD OS field lists 9x/ME' } else { $notes += 'PAD OS field lists NT-family only; Windows 9x/ME mentioned on program page only' }
    $pm = [regex]::Matches($pageText, '(?i)[^.]{0,120}\b(Windows\s?(95|98|ME|9x)|Win(95|98|ME|9x))\b[^.]{0,120}')
    if ($pm.Count -gt 0) {
        $snip = ($pm | Select-Object -First 2 | ForEach-Object { $_.Value.Trim() }) -join ' ... '
        if ($snip.Length -gt 300) { $snip = $snip.Substring(0, 297) + '...' }
        $notes += "page says: $snip"
        if ($snip -match "(?i)\bnot\b|doesn't|does not|no longer|dropped|isn't") { $notes += 'CHECK: page mention of 9x/ME may be negative' }
    }
    elseif ($page) { $notes += 'program page does not mention 9x/ME' }
    $notes += "PAD Program_Type '$type'; class set per NirSoft license terms"
    if ($licSec) {
        $l = $licSec; if ($l.Length -gt 260) { $l = $l.Substring(0, 257) + '...' }
        $notes += "page License: $l"
        if ($licSec -match '(?i)non-commercial|personal') { $notes += 'page limits use to personal/non-commercial' }
        if ($licSec -notmatch '(?i)distribut') { $notes += 'CHECK: page License section does not mention distribution' }
    }
    elseif ($page) { $notes += 'CHECK: no License section found on program page' }

    $needs = @()
    if ($req) { $needs += $req }
    if ($p.Includes_JAVA_VM -eq 'Y') { $needs += 'Java VM (PAD)' }
    if ($p.Includes_VB_Runtime -eq 'Y') { $needs += 'VB runtime (PAD)' }
    if ($p.Includes_DirectX -eq 'Y') { $needs += 'DirectX (PAD)' }

    $class = 'freeware'; $lic = $LicenseText
    if ($type -match '(?i)shareware|trial|demo') { $class = 'shareware'; $lic = "PAD Program_Type: $type"; $notes += 'PAD says not freeware' }
    elseif ($type -match '(?i)commercial') { $class = 'commercial'; $lic = "PAD Program_Type: $type"; $notes += 'PAD says not freeware' }
    $rows.Add((New-Lead @{
        source = $Source; name = $name; version = $ver; os = $os; needs = ($needs -join '; '); category = $cat
        license_class = $class; license = $lic; license_evidence = $page
        homepage = $page; download = $dl; notes = ($notes -join '; ')
    }))
}

Write-LeadsCsv -Rows $rows -Source $Source | Out-Null
Write-Host "PAD files parsed: $($files.Count); kept: $($rows.Count); skipped as NT-family only: $($skippedNt.Count)"
$skippedNt | Set-Content (Join-Path $CacheDir 'nirsoft_skipped_nt_only.txt') -Encoding UTF8
if ($problems.Count) { Write-Host 'Problems:'; $problems | ForEach-Object { Write-Host "  $_" } }
