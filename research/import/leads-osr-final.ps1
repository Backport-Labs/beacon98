# leads-osr-final.ps1 - import Operating System Revival "latest versions of software working on Windows 98/ME"
# Output: D:\Win98SE\beacon\research\leads\osr-final.csv   Cache: import\cache\osr-final.html
# The source blog is "All Rights Reserved": only facts are recorded (name, version, OS, prerequisites,
# the source's status flag, link). Remarks on the page are scanned for keywords but never copied.
. (Join-Path $PSScriptRoot 'leads-common.ps1')

$src = 'osr-final'
$url = 'https://retrosystemsrevival.blogspot.com/p/latest-versions-of-software-working-on_20.html'
$html = Get-LeadPage -Url $url -CacheName 'osr-final.html'

$i = $html.IndexOf('post-body entry-content')
if ($i -lt 0) { throw 'post body not found' }
$body = $html.Substring($i)
$e = $body.IndexOf("<div style='clear: both;'></div>")
if ($e -gt 0) { $body = $body.Substring(0, $e) }

# Mark category headings: <span style="font-size: large;"><b>Heading</b>
$body = [regex]::Replace($body, '(?is)<span style="font-size:\s*large;">\s*<b>(.*?)</b>', "`n@@CAT@@`$1`n")
$body = [regex]::Replace($body, '(?is)<b><span style="font-size:\s*large;">(.*?)</span></b>', "`n@@CAT@@`$1`n")
$body = [regex]::Replace($body, '(?is)<b style="font-size:\s*x-large;">(.*?)</b>', "`n@@CAT@@`$1`n")
$body = [regex]::Replace($body, '(?is)<b>(To Be Tested[^<]*)</b>', "`n@@CAT@@`$1`n")
$body = [regex]::Replace($body, '(?i)<br\s*/?>|</div>|<div[^>]*>|</p>|</li>', "`n")
$body = [regex]::Replace($body, '(?i)<a [^>]*href="([^"]*)"[^>]*>', '[[$1]]')
$body = [regex]::Replace($body, '<[^>]+>', '')
$body = [Net.WebUtility]::HtmlDecode($body) -replace '\u00A0', ' '

$flagWords = @{ 'FV' = 'final working version'; 'CS' = 'concurrent support'; 'US' = 'unofficial support' }
$rows = New-Object System.Collections.Generic.List[object]
$cat = $null
$skipCats = '^(To Be Tested)'
foreach ($raw in ($body -split "`n")) {
    $line = ($raw -replace '\s+', ' ').Trim()
    if (-not $line) { continue }
    if ($line -like '@@CAT@@*') { $c = $line.Substring(7).Trim(); if ($c) { $cat = $c }; continue }
    if (-not $cat) { continue }                       # preamble before first heading
    if ($cat -match $skipCats) { continue }           # untested section
    if ($line -match '^\*\*|^https?://|^Delete the |^\[\[[^\]]*\]\]$') { continue }   # notes / continuation lines
    $link = ''
    $lm = [regex]::Match($line, '\[\[([^\]]*)\]\]')
    if ($lm.Success) { $link = $lm.Groups[1].Value }
    $text = ([regex]::Replace($line, '\[\[[^\]]*\]\]', '')).Trim()
    if (-not $text) { continue }
    # Head (name/version/flags) vs remark after " - "
    $head = $text; $remark = ''
    $d = $text.IndexOf(' - ')
    if ($d -gt 0) { $head = $text.Substring(0, $d); $remark = $text.Substring($d + 3) }
    $notes = New-Object System.Collections.Generic.List[string]
    $cls = ''; $flags = @()
    # Status flags in parentheses anywhere on the line
    foreach ($pm in [regex]::Matches($text, '\(([^()]*)\)')) {
        $inner = $pm.Groups[1].Value
        if ($inner -match '^\s*(\$\$\$|~\$|FV\??|CS\??|US\??)(\s*,\s*(\$\$\$|~\$|FV\??|CS\??|US\??))*\s*$') {
            foreach ($f in ($inner -split ',')) { $flags += $f.Trim() }
        }
    }
    foreach ($f in $flags) {
        $b = $f.TrimEnd('?')
        if ($b -eq '$$$') { $cls = 'commercial'; $notes.Add('source marks $$$ (commercial)') }
        elseif ($b -eq '~$') { $cls = 'shareware'; $notes.Add('source marks ~$ (freemium)') }
        elseif ($flagWords.ContainsKey($b)) { $notes.Add("source flag $f ($($flagWords[$b]))") }
    }
    # Remove flag parens from head, keep other short parentheticals as qualifiers
    $head = [regex]::Replace($head, '\(\s*(\$\$\$|~\$|FV\??|CS\??|US\??)(\s*,\s*(\$\$\$|~\$|FV\??|CS\??|US\??))*\s*\)', '')
    $needsList = Get-Needs $text
    foreach ($pm in [regex]::Matches($head, '\(([^()]*)\)')) {
        $inner = $pm.Groups[1].Value.Trim()
        if ($inner -match '(?i)requires') { continue }   # captured via Get-Needs
        if ($inner -match '\w') { $notes.Add("qualifier: $inner") }
    }
    $head = ([regex]::Replace($head, '\([^()]*\)', '') -replace '\s+', ' ').Trim()
    $nv = Split-NameVersion $head
    if ($nv.rest -match '\w') { $notes.Add("qualifier: $($nv.rest)") }
    $os = 'Windows 98/ME'
    if ($text -match 'Windows 95') { $os = 'Windows 95/98/ME' }
    if ($text -match 'NT 4\.0') { $os += ', Windows NT 4.0' }
    if ($text -match '(?i)unofficial') { $notes.Add('unofficial build/backport per source') }
    if ($remark -match "(?i)(does not|doesn't|not) (properly )?work|cannot|may not|crash|error|yet to find|need to find|no longer work") { $notes.Add('source reports limitations') }
    if ($text -match '(?i)Japanese') { $notes.Add('Japanese language') }
    $h = @{ homepage = ''; download = '' }
    Set-LeadLink $h $link
    $rows.Add((New-LeadRow -source $src -name $nv.name -version $nv.version -os $os -needs ($needsList -join '; ') `
        -category $cat -license_class $cls -homepage $h.homepage -download $h.download -notes $notes))
}

Write-LeadsCsv $rows (Join-Path $script:LeadsDir 'osr-final.csv')
