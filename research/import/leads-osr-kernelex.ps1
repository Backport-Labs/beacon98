# leads-osr-kernelex.ps1 - import Operating System Revival "list of working Windows 98/ME KernelEx apps"
# Output: D:\Win98SE\beacon\research\leads\osr-kernelex.csv
# Cache:  import\cache\osr-kernelex.html, import\cache\osr-kernelex-extensions-plus.html
# The source blog is "All Rights Reserved": only facts are recorded (name, version, KernelEx version/mode,
# prerequisites, link). Remarks are scanned for keywords but never copied. "Not Working" section is skipped.
. (Join-Path $PSScriptRoot 'leads-common.ps1')

$src = 'osr-kernelex'
$url = 'https://retrosystemsrevival.blogspot.com/p/list-of-working-windows-98me-kernelex.html'
$tutUrl = 'https://retrosystemsrevival.blogspot.com/p/kernelex-extensions-plus.html'
$html = Get-LeadPage -Url $url -CacheName 'osr-kernelex.html'
$tut = Get-LeadPage -Url $tutUrl -CacheName 'osr-kernelex-extensions-plus.html'
$os = 'Windows 98/ME'

function Get-PostBody([string]$h) {
    $i = $h.IndexOf('post-body entry-content')
    if ($i -lt 0) { throw 'post body not found' }
    $b = $h.Substring($i)
    $e = $b.IndexOf("<div style='clear: both;'></div>")
    if ($e -gt 0) { $b = $b.Substring(0, $e) }
    return $b
}

$body = Get-PostBody $html
# Headings are the large / x-large font runs
$headings = @{}
foreach ($m in [regex]::Matches($body, '(?is)font-size:\s*(x-)?large;?"[^>]*>(.*?)</(span|b)>')) {
    $t = Get-PlainText $m.Groups[2].Value
    if ($t) { $headings[$t] = $true }
}
$body = [regex]::Replace($body, '(?is)</?b(\s[^>]*)?>', "`n")          # bold runs delimit headings
$body = [regex]::Replace($body, '(?i)<br\s*/?>|</div>|<div[^>]*>|</p>|</li>', "`n")
$body = [regex]::Replace($body, '(?i)<a [^>]*href="([^"]*)"[^>]*>', '[[$1]]')
$body = [regex]::Replace($body, '<[^>]+>', '')
$body = [Net.WebUtility]::HtmlDecode($body) -replace '\u00A0', ' '

$rows = New-Object System.Collections.Generic.List[object]
$cat = $null
$started = $false
$stop = $false
foreach ($raw in ($body -split "`n")) {
    $line = ($raw -replace '\s+', ' ').Trim()
    if (-not $line) { continue }
    if (-not $started) { if ($line -eq 'Official Microsoft Files') { $started = $true; $cat = $line }; continue }
    if ($line -match '^Not Working$') { break }
    if ($line -notmatch '^- ') {
        if ($headings.ContainsKey($line)) { $cat = $line }
        continue
    }
    $text = $line.Substring(2).Trim()
    $link = ''
    foreach ($lm in [regex]::Matches($text, '\[\[([^\]]*)\]\]')) { if (-not $link) { $link = $lm.Groups[1].Value } }
    $text = ([regex]::Replace($text, '\[\[[^\]]*\]\]', '') -replace '\s+', ' ').Trim() -replace '\s+-$', ''
    $head = $text; $remark = ''
    $d = $text.IndexOf(' - ')
    if ($d -gt 0) { $head = $text.Substring(0, $d); $remark = $text.Substring($d + 3) }
    $notes = New-Object System.Collections.Generic.List[string]
    $kx = ''
    # ", KX 4.0" form
    $cm = [regex]::Match($head, ',\s*KX\s+([\w.]+)\s*$')
    if ($cm.Success) { $kx = $cm.Groups[1].Value; $head = $head.Substring(0, $cm.Index) }
    foreach ($pm in [regex]::Matches($head, '\(([^()]*)\)')) {
        $inner = $pm.Groups[1].Value.Trim()
        if ($inner -match '(?i)KernelEx|^KX\b') {
            $kx = ($inner -replace '(?i)^(KernelEx|KX)\s*', '' -replace '\s*[;,]\s*', '; ')
        } elseif ($inner -match '(?i)^mirror$') {
        } elseif ($inner -match '\w') { $notes.Add("qualifier: $inner") }
    }
    $head = ([regex]::Replace($head, '\([^()]*\)', '') -replace '\s+', ' ').Trim()
    if ($head -match '(?i)\sPortable$') { $head = $head -replace '(?i)\s+Portable$', ''; $notes.Add('portable build') }
    $nv = Split-NameVersion $head
    if ($nv.rest -match '\w') {
        if ($nv.rest -match '(?i)^Portable$') { $notes.Add('portable build') } else { $notes.Add("qualifier: $($nv.rest)") }
    }
    $needs = New-Object System.Collections.Generic.List[string]
    if ($kx) { $needs.Add("KernelEx $kx") } else { $needs.Add('KernelEx') }
    foreach ($x in (Get-Needs $text)) { $needs.Add($x) }
    if ($remark -match "(?i)(does not|doesn't|not) (properly )?work|cannot|crash|error|buggy|glitch|sluggish|slow|bug|issue|retest|not tested|untested|TBA|instabil") { $notes.Add('source reports limitations or untested details') }
    if ($text -match '(?i)Japanese') { $notes.Add('Japanese language') }
    $h = @{ homepage = ''; download = '' }
    if ($link -match '(?i)kernelex\.sourceforge\.net/wiki') { $notes.Add("KernelEx wiki link given: $link"); $link = '' }
    elseif ($link -match '(?i)youtube\.com') { $notes.Add("instruction video link given: $link"); $link = '' }
    Set-LeadLink $h $link
    $rows.Add((New-LeadRow -source $src -name $nv.name -version $nv.version -os $os -needs ($needs -join '; ') `
        -category $cat -homepage $h.homepage -download $h.download -notes $notes))
}

# --- KernelEx itself and community KernelEx updates referenced by the page -------------------------
# The page's "Settings Used" block names these; the tutorial page it links documents a DLL pack.
$pre = (Get-PlainText (Get-PostBody $html))
if ($pre -match 'KernelEx (4\.5\.2) \+ KernelEx (\d+) Updates') {
    $kv = $Matches[1]; $un = $Matches[2]
    $rows.Add((New-LeadRow -source $src -name 'KernelEx' -version $kv -os $os -category 'KernelEx (settings used by source)' `
        -notes @('row added: named in the source settings list; no download link on page')))
    $rows.Add((New-LeadRow -source $src -name 'KernelEx Updates (community, by Jumper)' -os $os -needs "KernelEx $kv" `
        -category 'KernelEx (settings used by source)' -homepage $tutUrl -NoMemory `
        -notes @("row added: source settings list names 'KernelEx $un Updates'; app rows cite KernelEx 4.5.2019.24; version not stated as such; link is the source's tutorial page")))
}
if ($pre -match 'Kstub(\d+)') {
    $rows.Add((New-LeadRow -source $src -name "Kstub$($Matches[1])" -version '' -os $os -needs 'KernelEx' -category 'KernelEx (settings used by source)' -NoMemory `
        -notes @("row added: source settings list names 'Kstub$($Matches[1])' (KernelEx stub pack); name as stated; whether 822 is a version is not verified; no link on page")))
}
$tb = Get-PostBody $tut
$tlinks = @([regex]::Matches($tb, '(?i)<a [^>]*href="([^"]*)"[^>]*>') | ForEach-Object { $_.Groups[1].Value } | Where-Object { $_ -notmatch 'blogger\.googleusercontent|retrosystemsrevival' })
$broken = (Get-PlainText $tb) -match '(?i)links are currently broken'
$tn = @('row added from linked tutorial page', 'pack mixes Windows 2000/XP and ReactOS DLLs plus a third-party kernel32 per source: not redistributable as-is')
if ($broken) { $tn += 'source states its links are currently broken' }
if ($tlinks.Count -gt 1) { $tn += ('mirror: ' + $tlinks[1]) }
$rows.Add((New-LeadRow -source $src -name 'KernelEx DLLs pack (OSR KernelEx Extensions Plus)' -os $os -needs 'KernelEx; KernelEx Updates' `
    -category 'KernelEx (settings used by source)' -license_class 'unknown' -homepage $tutUrl -download ($tlinks | Select-Object -First 1) -notes $tn))

Write-LeadsCsv $rows (Join-Path $script:LeadsDir 'osr-kernelex.csv')
