# Import MDGx "Power Toys" (toy.htm) and "Software Essentials" (web.htm) into
# research\leads\mdgx-toy.csv and research\leads\mdgx-web.csv.
# Rerunnable. Usage: powershell -File import-mdgx.ps1 [-Offline]
param([switch]$Offline)
. (Join-Path $PSScriptRoot '_common.ps1')

$Pages = @(
    @{ source = 'mdgx-toy'; url = 'https://www.mdgx.com/toy.htm'; file = 'toy.htm' },
    @{ source = 'mdgx-web'; url = 'https://www.mdgx.com/web.htm'; file = 'web.htm' }
)

$OsTokens = '^(3\.1x?|9x|95[ABC]?|98|ME|NT|NT[34](\.\d+)?|NTx|2000|2K|XP|2003|Vista|2008|7|8|8\.1|10|11|2012|2016|2019|2022|2025|Server|Me)$'
$OsRegex = 'Windows\s+([\w.]+(?:\s*[/+]\s*[\w.]+|\s+(?:SP\s?\d+a?|SE(?:\(U\))?\b|OSR\s?\d(?:\.\w+)?|R2|Professional|x64|x86|Gold|Standard Edition))*)'
$TagRegex = '[\[(]([^\[\]()]*?\b(?:free|freeware|free-ware|GPL|LGPL|open source|open-source|shareware|commercial|trial|donationware|nagware|adware|public domain|gratis|retail)\b[^\[\]()]*?)[\])]'
# Obvious gaps filled from general knowledge (rows get "class from memory" in notes). Keep this short.
$MemoryClass = [ordered]@{
    '^SysInternals'   = @('commercial', 'Sysinternals Software License (Microsoft; no redistribution)', 'Microsoft Sysinternals')
    '^EditPad Lite'   = @('freeware-unclear', 'free for non-commercial use', 'Just Great Software EditPad Lite')
    '^MiTeC'          = @('freeware-unclear', 'MiTeC freeware', 'MiTeC tools are freeware; redistribution terms not checked')
}
$FileExt ='\.(exe|zip|7z|rar|msi|cab|lzh|arj|gz|bz2|xz|tgz|cmd|bat|reg|inf)$'

function Resolve-Href([string]$h) {
    $h = [System.Net.WebUtility]::HtmlDecode($h.Trim().Trim('"', "'"))
    if ($h -match '^(https?|ftp)://') { return $h }
    if ($h -match '^//') { return "https:$h" }
    if ($h -match '^(mailto|javascript):') { return '' }
    if ($h.StartsWith('/')) { return "https://www.mdgx.com$h" }
    return "https://www.mdgx.com/$h"
}

function Get-Links([string]$html) {
    $out = @()
    foreach ($m in [regex]::Matches($html, '(?is)<A\b[^>]*?\bHREF\s*=\s*("[^"]*"|''[^'']*''|[^\s>]+)[^>]*>(.*?)</A>')) {
        $out += [pscustomobject]@{ href = (Resolve-Href $m.Groups[1].Value); text = (ConvertTo-PlainText $m.Groups[2].Value); index = $m.Index }
    }
    return $out
}

function Get-Os([string]$text) {
    foreach ($m in [regex]::Matches($text, $OsRegex)) {
        $v = $m.Groups[1].Value.TrimEnd('.', ' ', '/', '+')
        $first = ($v -split '[/+ ]')[0]
        if ($first -notmatch $OsTokens) { continue }
        # cut at the first "/" or "+" segment that is not a Windows version (e.g. "+ MS-DOS", "+ Linux")
        $segs = [regex]::Split($v, '(\s*[/+]\s*)')
        $out = $segs[0]
        for ($i = 1; $i -lt $segs.Count - 1; $i += 2) {
            $seg = $segs[$i + 1]
            if ((($seg -split ' ')[0]) -notmatch $OsTokens -and $seg -notmatch '^(OSR|SP|XP|NT)') { break }
            $out += $segs[$i] + $seg
        }
        return $out.TrimEnd('.', ' ', '/', '+')
    }
    return ''
}

function Get-Tags([string]$text) {
    $t = $text -replace 'free\(ware\)', 'free-ware'
    $tags = @()
    foreach ($m in [regex]::Matches($t, $TagRegex, 'IgnoreCase')) {
        $tag = $m.Groups[1].Value -replace 'free-ware', 'free(ware)'
        $tag = ($tag -replace '\b\d+(\.\d+)?\s?[KMG]B\b,?\s*', '').Trim(' ', ',')
        if ($tag -match '(?i)^mostly ') { continue }
        $tags += $tag
    }
    return $tags
}

function Get-Class([string]$tag) {
    $l = $tag.ToLower()
    if ($l -match 'now freeware') { return 'freeware-unclear' }
    if ($l -match 'shareware|trial|nagware') { return 'shareware' }
    if ($l -match 'commercial|retail|\$\d') { return 'commercial' }
    if ($l -match '\bl?gpl\b|open.source|\bbsd\b|\bmit\b|\bmpl\b') { return 'open-source' }
    if ($l -match 'personal use|non.?commercial|non.?profit|private use|crippled|\bnag\b|adware|spyware|registration|registered|subscription|setup only') { return 'freeware-unclear' }
    if ($l -match 'free|gratis|donationware') { return 'freeware' }
    return 'unknown'
}

function Get-Needs([string]$text) {
    $needs = @()
    $clean = $text -replace '\[[^\]]*\]', '' -replace '\s+', ' '
    foreach ($s in ($clean -split '(?<=[!.])\s+(?=[A-Z])')) {
        if ($s -match '(?i)\brequires?\b|\bneeds?\b|\bmust (?:be|have)\b.*installed|\bdepends on\b') {
            $s = $s.Trim()
            if ($s.Length -gt 260) { $s = $s.Substring(0, 257) + '...' }
            $needs += $s
        }
    }
    if ($clean -match 'KernelEx' -and -not ($needs -match 'KernelEx')) { $needs += 'KernelEx (mentioned)' }
    return ($needs | Select-Object -Unique) -join ' | '
}

function Split-NameVersion([string]$s) {
    $s = ($s -replace '\s+', ' ').Trim(' ', ':', '.', ',')
    $ver = ''
    $m = [regex]::Match($s, '^(.*?)\s+v(\d[\w.\-]*(?:\s+(?:Beta|Alpha|RC|Final|Build|Preview|Update|Release)(?:\s*\d[\w.]*(?![\w.-]))?)?)(.*)$')
    if ($m.Success) { $ver = $m.Groups[2].Value.Trim(); $s = ($m.Groups[1].Value + ' ' + $m.Groups[3].Value).Trim() }
    $s = $s -replace '\s*\+?\s*\b(16|32|64)-bit\b(\s*\+\s*(16|32|64)-bit\b)?', '' -replace '\s+', ' '
    return @($s.Trim(' ', ':', '+', ',', '/'), $ver)
}

# ---- list tree ---------------------------------------------------------------------------
function Get-LiNodes([string]$html, [int]$from, [int]$to) {
    $nodes = New-Object System.Collections.Generic.List[object]
    $stack = New-Object System.Collections.Generic.List[object]   # list frames
    $root = [pscustomobject]@{ cur = $null }
    $stack.Add($root)
    $rx = [regex]'(?i)<(/?)(UL|OL|LI)\b[^>]*>'
    $m = $rx.Match($html, $from)
    while ($m.Success -and $m.Index -lt $to) {
        $close = $m.Groups[1].Value -eq '/'
        $tag = $m.Groups[2].Value.ToUpper()
        $top = $stack[$stack.Count - 1]
        if ($tag -eq 'LI' -and -not $close) {
            if ($top.cur) { $top.cur.end = $m.Index }
            $parent = $null
            if ($stack.Count -ge 2) { $parent = $stack[$stack.Count - 2].cur }
            $n = [pscustomobject]@{ start = $m.Index + $m.Length; end = $to; parent = $parent; children = (New-Object System.Collections.Generic.List[object]); spans = (New-Object System.Collections.Generic.List[object]); id = $nodes.Count; isEntry = $false }
            if ($parent) { $parent.children.Add($n) }
            $nodes.Add($n); $top.cur = $n
        }
        elseif ($tag -eq 'LI' -and $close) {
            if ($top.cur) { $top.cur.end = $m.Index; $top.cur = $null }
        }
        elseif (-not $close) {
            $owner = $top.cur
            if ($owner) { $owner.spans.Add([pscustomobject]@{ s = $m.Index; e = $to }) }
            $stack.Add([pscustomobject]@{ cur = $null; owner = $owner })
        }
        else {
            if ($stack.Count -gt 1) {
                if ($top.cur) { $top.cur.end = $m.Index }
                if ($top.owner -and $top.owner.spans.Count -gt 0) { $top.owner.spans[$top.owner.spans.Count - 1].e = $m.Index + $m.Length }
                $stack.RemoveAt($stack.Count - 1)
            }
        }
        $m = $m.NextMatch()
    }
    return $nodes
}

function Get-OwnHtml($n, [string]$html) {
    $sb = New-Object System.Text.StringBuilder
    $p = $n.start
    foreach ($sp in $n.spans) {
        if ($sp.s -gt $p -and $sp.s -le $n.end) { [void]$sb.Append($html.Substring($p, $sp.s - $p)) }
        if ($sp.e -gt $p) { $p = [Math]::Min($sp.e, $n.end) }
    }
    if ($n.end -gt $p) { [void]$sb.Append($html.Substring($p, $n.end - $p)) }
    return $sb.ToString()
}

# ---- main --------------------------------------------------------------------------------
foreach ($pg in $Pages) {
    Write-Host "== $($pg.source): $($pg.url)"
    $path = Get-CachedPage -Url $pg.url -Name $pg.file -Offline:$Offline
    $html = [IO.File]::ReadAllText($path, [Text.Encoding]::GetEncoding(1252))
    $first = $html.IndexOf('<div ID=DV>', [StringComparison]::OrdinalIgnoreCase)
    $last = $html.LastIndexOf('<div ID=DV>', [StringComparison]::OrdinalIgnoreCase)

    # section (SIZE=4) and sub-section (DODGERBLUE SIZE=3) headers
    $heads = @()
    foreach ($m in [regex]::Matches($html, '(?is)<FONT\b[^>]*\bSIZE=4\b[^>]*>\s*<B>(.*?)</B>')) { $heads += [pscustomobject]@{ pos = $m.Index; lvl = 1; text = (ConvertTo-PlainText $m.Groups[1].Value) } }
    foreach ($m in [regex]::Matches($html, '(?is)<FONT\b[^>]*COLOR=DODGERBLUE[^>]*SIZE=3[^>]*>\s*<B>(.*?)</B>')) { $heads += [pscustomobject]@{ pos = $m.Index; lvl = 2; text = (ConvertTo-PlainText $m.Groups[1].Value) } }
    $heads = $heads | Sort-Object pos

    $nodes = Get-LiNodes $html $first $last
    foreach ($n in $nodes) {
        $own = Get-OwnHtml $n $html
        $n | Add-Member own $own
        $n | Add-Member ownText (ConvertTo-PlainText $own)
        $n | Add-Member links @(Get-Links $own)
        $n | Add-Member label ''
        $lm = [regex]::Match($own, '(?is)^\s*(?:<A NAME=[^>]*></A>)?\s*<B>\s*<FONT[^>]*CLASS=FRM[^>]*>(.*?)</FONT>\s*:?\s*</B>')
        if ($lm.Success) { $n.label = ConvertTo-PlainText $lm.Groups[1].Value }
    }

    # decide which LI items are software entries
    foreach ($n in $nodes) {
        $t = $n.ownText
        if ($n.links.Count -eq 0) { continue }
        if ($t -match '(?i)on the Internet|^See "|^Wikipedia\b|^More info|^Also here|\[mostly free|^Get (1|one|ALL)\b') { continue }
        if ($t -match '(?i)^Windows\s.*\brequire') { continue }   # prerequisite note, not a program
        $hasOs = [bool](Get-Os $t)
        $hasTag = (Get-Tags $t).Count -gt 0
        $hasFile = [bool]($t -match '(?i)Direct download|\[\s*\d+(\.\d+)?\s?[KMG]B')
        $looks = $n.label -or ($hasOs -and ($hasTag -or $hasFile -or $t.Length -gt 60)) -or ($hasTag -and $t.Length -gt 40)
        if (-not $looks) { continue }
        # nested item under an entry: separate only if it has a label, or its own OS + license tag and a different name
        $anc = $n.parent; $underEntry = $null
        while ($anc) { if ($anc.isEntry) { $underEntry = $anc; break }; $anc = $anc.parent }
        if ($underEntry) {
            $pName = ($underEntry.links[0].text -split '\s')[0]
            $cText = $n.links[0].text
            $sameFamily = $cText -match ('(?i)(^|\s)' + [regex]::Escape($pName) + '(\s|$)')
            if (-not ($n.label -or ($hasOs -and $hasTag -and -not $sameFamily))) { continue }
            if ($t -match '(?i)^(Direct download|Also here)') { continue }
        }
        $n.isEntry = $true
    }

    function Get-FullText($n) {
        $parts = @($n.ownText)
        foreach ($c in $n.children) { if (-not $c.isEntry) { $parts += (Get-FullText $c) } }
        return ($parts -join ' ')
    }
    function Get-AllLinks($n) {
        $l = @($n.links)
        foreach ($c in $n.children) { if (-not $c.isEntry) { $l += @(Get-AllLinks $c) } }
        return $l
    }

    $rows = New-Object System.Collections.Generic.List[object]
    $seen = @{}
    foreach ($n in ($nodes | Where-Object { $_.isEntry })) {
        $own = $n.own; $ownText = $n.ownText
        $full = Get-FullText $n
        $allLinks = @(Get-AllLinks $n)

        # name
        $prefixHtml = $own
        $ai = ([regex]::Match($own, '(?i)<A\s')).Index; if (-not ([regex]::Match($own, '(?i)<A\s')).Success) { $ai = -1 }
        if ($ai -ge 0) { $prefixHtml = $own.Substring(0, $ai) }
        $prefix = (ConvertTo-PlainText ($prefixHtml -replace '(?is)<B>\s*<FONT[^>]*CLASS=FRM.*?</B>', '')).Trim()
        $nameSrc = $n.links[0].text
        if ($prefix.Length -gt 3 -and $prefix -notmatch '^(Also|See|More)') {
            if ($n.label -and $prefix.Length -gt 40) { $nameSrc = $n.label }
            else { $nameSrc = ($prefix -split '\s+(?:for|tweaks|allows|creates|is|includes|installs|adds|lets|shows|displays)\s|\s[\[(]|:|\s+Windows\s+(?:\d|9x|NT|ME|XP)')[0] }
            if ($nameSrc -match '^(Microsoft|Unofficial|MS|OLD)$') { $nameSrc = ($prefix -split ':|\s\(')[0] }
        }
        elseif ($n.links[0].text -match '(?i)^(Direct download|download|here|More info)$' -and $n.label) { $nameSrc = $n.label }
        $nv = Split-NameVersion $nameSrc
        $name = $nv[0]; $ver = $nv[1]
        if (-not $name) { $name = $n.label }

        # category
        $sec = ($heads | Where-Object { $_.lvl -eq 1 -and $_.pos -lt $n.start } | Select-Object -Last 1)
        $sub = ($heads | Where-Object { $_.lvl -eq 2 -and $_.pos -lt $n.start -and (-not $sec -or $_.pos -gt $sec.pos) } | Select-Object -Last 1)
        $cat = ''
        if ($sec) { $cat = $sec.text -replace '^FREE Windows 9x/NTx\s+', '' }
        if ($sub -and $sub.text -ne $cat) { $cat = "$cat / $($sub.text)" }

        # os: prefer the name/first link, then own text, then children
        $os = Get-Os ($nameSrc + ' ' + $ownText)
        if (-not $os) { $os = Get-Os $full }

        # license
        $tags = @(Get-Tags $ownText)
        $tagWhere = 'entry text'
        if ($tags.Count -eq 0) { $tags = @(Get-Tags $full); $tagWhere = 'sub-item text' }
        $notes = @()
        if ($n.label -and $n.label -ne $name) { $notes += "label: $($n.label)" }
        $isMs = ($name -match '(?i)^Microsoft\b|^MS\b') -or ($prefix -match '(?i)^Microsoft\b') -or ($n.links[0].text -match '(?i)^Microsoft\b') -or
                ($name -match '^Windows\b' -and $name -match '(?i)\bFix(es)?\b|Update|Security')
        $msParent = $null; $anc = $n.parent
        while ($anc) { if ($anc.isEntry) { if ($anc.PSObject.Properties['isMs'] -and $anc.isMs) { $msParent = $anc }; break }; $anc = $anc.parent }
        if ($msParent) { $isMs = $true }
        $n | Add-Member -Force isMs $isMs
        $isUnofficialMsPatch = ($name -match '(?i)^Unofficial\b') -and ($name -match '(?i)\b\w+\.(DLL|VXD|SYS|EXE|PDR|CPL|INF|DRV|386|OCX|CAB|MPD)\b|Service Pack|Update|Fix')
        $class = 'unknown'; $lic = ''
        if ($tags.Count -gt 0) {
            $tag = $tags[0]
            $class = Get-Class $tag
            $lic = $tag
            if ($class -eq 'open-source') {
                if ($tag -match '(?i)\bLGPL\b') { $lic = 'LGPL (version not stated by source)' }
                elseif ($tag -match '(?i)\bGPL\b') { $lic = 'GPL (version not stated by source)' }
            }
            $notes += "class from source tag '$tag' ($tagWhere)"
            if ($tags.Count -gt 1 -and (($tags | ForEach-Object { Get-Class $_ } | Select-Object -Unique).Count -gt 1)) { $notes += "other tags: $((($tags | Select-Object -Skip 1) -join '; '))" }
        }
        if ($isMs) {
            if ($class -ne 'unknown') { $notes += "Microsoft component: source tag describes a free download, not redistribution rights" }
            $class = 'commercial'; $lic = 'Microsoft (proprietary)'
            $notes += 'Microsoft component; class from memory'
        }
        elseif ($isUnofficialMsPatch -and $class -eq 'unknown') {
            $class = 'commercial'; $lic = 'unofficial patch of Microsoft files'
            $notes += 'unofficial fix repackaging Microsoft system files; class from memory'
        }
        elseif ($isUnofficialMsPatch) {
            $notes += 'unofficial patch/pack that likely contains Microsoft files: the free tag does not settle redistribution rights'
        }
        if ($class -eq 'unknown' -and $MemoryClass) {
            foreach ($k in $MemoryClass.Keys) {
                if ($name -match $k) {
                    $class = $MemoryClass[$k][0]; $lic = $MemoryClass[$k][1]
                    $notes += "class from memory ($($MemoryClass[$k][2]))"; break
                }
            }
        }
        if ($full -match '(?i)discontinued') { $notes += 'source marks it discontinued' }
        if ($full -match '(?i)\bunsupported\b') { $notes += 'source says unsupported' }

        # links
        $hp = ''; $dl = ''
        foreach ($l in $allLinks) {
            if (-not $l.href) { continue }
            $isFile = $l.href -match $FileExt
            if (-not $dl -and ($isFile -or $l.text -match '(?i)direct download')) { $dl = $l.href }
            if (-not $hp -and -not $isFile -and $l.text -notmatch '(?i)direct download|more info') { $hp = $l.href }
        }
        if ($n.links.Count -gt 0 -and $n.links[0].href -and $n.links[0].href -notmatch $FileExt) { $hp = $n.links[0].href }

        $key = ($name + '|' + $hp + '|' + $dl).ToLower()
        if ($seen.ContainsKey($key)) {
            $prev = $seen[$key]
            if ($cat -and $prev.category -notmatch [regex]::Escape($cat)) { $prev.notes = ($prev.notes + "; also listed under: $cat").Trim('; ') }
            continue
        }
        $row = New-Lead @{
            source = $pg.source; name = $name; version = $ver; os = $os; needs = (Get-Needs $full); category = $cat
            license_class = $class; license = $lic; license_evidence = $(if ($tags.Count -gt 0 -and -not $isMs) { $pg.url } else { '' })
            homepage = $hp; download = $dl; notes = ($notes -join '; ')
        }
        $seen[$key] = $row
        $rows.Add($row)
    }
    Write-LeadsCsv -Rows $rows -Source $pg.source | Out-Null
}




