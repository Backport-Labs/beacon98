# leads-msfn-kernelex.ps1 - import MSFN "KernelEx Apps Compatibility List (New)" (topic 152471), first post.
# Output: D:\Win98SE\beacon\research\leads\msfn-kernelex.csv   Cache: import\cache\msfn-kernelex-p1.html
# Keeps "What is working" and "Games that works" entries (status in notes: works / partial);
# "What doesn't work" entries are skipped. Forum post text: short per-entry user notes are kept in notes.
. (Join-Path $PSScriptRoot 'leads-common.ps1')

$src = 'msfn-kernelex'
$url = 'https://msfn.org/board/topic/152471-kernelex-apps-compatibility-list-new/'
$html = Get-LeadPage -Url $url -CacheName 'msfn-kernelex-p1.html'
$os = 'Windows 98SE'   # thread scope: "working apps under Win98SE+KernelEx"

$ms = [regex]::Matches($html, '<div[^>]*data-role="commentContent"[^>]*>')
if ($ms.Count -lt 1) { throw 'no posts found' }
$end = if ($ms.Count -gt 1) { $ms[1].Index } else { $html.Length }
$post = $html.Substring($ms[0].Index, $end - $ms[0].Index)
$edited = ''
$em = [regex]::Match($post, "(?s)ipsEdited.*?datetime='([^']+)'")
if ($em.Success) { $edited = $em.Groups[1].Value.Substring(0, 10) }
Write-Host "First post last edited: $edited"

$rows = New-Object System.Collections.Generic.List[object]
$section = ''
$last = $null
foreach ($pm in [regex]::Matches($post, '(?s)<p(\s[^>]*)?>(.*?)</p>')) {
    if ($pm.Groups[1].Value -match 'ipsEdited') { continue }
    $inner = $pm.Groups[2].Value
    $plain = Get-PlainText $inner
    if (-not $plain) { continue }
    if ($plain -match '^- = (.*) = -$') {
        $h = $Matches[1]
        if ($h -match "(?i)doesn't work") { $section = 'notworking' }
        elseif ($h -match '(?i)^Games') { $section = 'games' }
        else { $section = 'works' }   # header is spelled 'What is worinkg with KernelEx'
        continue
    }
    if (-not $section -or $section -eq 'notworking') { continue }
    $isItem = ($inner -match '<strong') -or ($inner.TrimStart() -match '^<a ')
    if (-not $isItem) {
        # continuation paragraph of the previous entry's notes
        if ($last) { $last.notes = ($last.notes + ' ' + $plain).Trim() }
        continue
    }
    if ($plain -match '(?i)^KX Wiki') { continue }
    $link = ''
    $lm = [regex]::Match($inner, '(?i)<a [^>]*href="([^"]*)"')
    if ($lm.Success) { $link = [Net.WebUtility]::HtmlDecode($lm.Groups[1].Value) }
    # Title = bold/link text; rest = ", KX x, mode, notes: ..."
    $tm = [regex]::Match($inner, '(?s)^(.*?(</strong>|</a>))(?!.*</strong>)')
    $title = ''; $rest = ''
    $lastStrong = $inner.LastIndexOf('</strong>')
    $cut = if ($lastStrong -ge 0) { $lastStrong + 9 } else { $inner.IndexOf('</a>') + 4 }
    $ca = $inner.IndexOf('</a>', [Math]::Max(0, $cut - 4))
    if ($ca -ge 0 -and $ca -le $cut + 2) { $cut = $ca + 4 }
    $title = Get-PlainText $inner.Substring(0, $cut)
    $rest = (Get-PlainText $inner.Substring($cut)).Trim().TrimStart(',').Trim()
    $km = [regex]::Match($title, '(?i),\s*(KX\s+[\w.]+.*)$')          # KX info inside the bold text (source markup slip)
    if ($km.Success) { $rest = ($km.Groups[1].Value + ', ' + $rest).Trim().TrimEnd(','); $title = $title.Substring(0, $km.Index) }
    $title = $title -replace '[\]/b]+$', '' -replace '/b\]$', ''
    $userNotes = ''
    $nm = [regex]::Match($rest, '(?i)\b(notes|why):\s*(.*)$')
    if ($nm.Success) { $userNotes = $nm.Groups[2].Value.Trim(); $rest = $rest.Substring(0, $nm.Index).Trim().TrimEnd(',') }
    $kx = ''; $mode = ''; $extra = @()
    foreach ($part in ($rest -split ',')) {
        $p = $part.Trim()
        if (-not $p) { continue }
        if ($p -match '(?i)^KX\s+([\w.]+)$') { $kx = $Matches[1] }
        elseif ($p -match '(?i)mode') { $mode = $p }
        else { $extra += $p }
    }
    $notes = New-Object System.Collections.Generic.List[string]
    # Parentheticals in the title -> qualifiers
    foreach ($q in [regex]::Matches($title, '\(([^()]*)\)')) { $notes.Add("qualifier: $($q.Groups[1].Value.Trim())") }
    $t2 = ([regex]::Replace($title, '\([^()]*\)', ' ') -replace '\s+', ' ').Trim()
    # "Name 1.0, a description" -> description to notes
    $ci = $t2.IndexOf(', ')
    if ($ci -gt 0) { $notes.Add("listed as: $($t2.Substring($ci + 2))"); $t2 = $t2.Substring(0, $ci) }
    $nv = Split-NameVersion $t2
    if ($nv.rest -match '\w') { $notes.Add("qualifier: $($nv.rest)") }
    foreach ($x in $extra) { $notes.Add($x) }
    $needs = New-Object System.Collections.Generic.List[string]
    $kxs = 'KernelEx'
    if ($kx) { $kxs += " $kx" }
    if ($mode) { $kxs += "; $mode" }
    $needs.Add($kxs)
    foreach ($x in (Get-Needs $userNotes)) { $needs.Add($x) }
    foreach ($dm in [regex]::Matches($userNotes, '(?i)\bmfc\d+u?\.dll')) { if (-not $needs.Contains($dm.Value)) { $needs.Add($dm.Value) } }
    $partial = ($userNotes -match "(?i)(doesn't|does not|not) work\b|crash|error|problem|cannot|can't|no movie|hang|glitch") -or ($rest -match '(?i)crash')
    $status = if ($partial) { 'partially working' } else { 'working' }
    $n2 = New-Object System.Collections.Generic.List[string]
    $n2.Add("status: $status")
    foreach ($x in $notes) { $n2.Add($x) }
    if ($userNotes) { $n2.Add("thread note: $userNotes") }
    $cat = if ($section -eq 'games') { 'Games' } else { 'Apps' }
    $h = @{ homepage = ''; download = '' }
    Set-LeadLink $h $link
    $row = New-LeadRow -source $src -name $nv.name -version $nv.version -os $os -needs ($needs -join '; ') `
        -category $cat -homepage $h.homepage -download $h.download -notes $n2
    $rows.Add($row)
    $last = $row
}

# KernelEx itself: the first post links the KernelEx wiki compatibility page.
$kw = [regex]::Match($post, '(?i)<a [^>]*href="(https?://kernelex\.sourceforge\.net/[^"]*)"')
if ($kw.Success) {
    $rows.Add((New-LeadRow -source $src -name 'KernelEx' -os 'Windows 98/ME' -category 'KernelEx' -homepage 'http://kernelex.sourceforge.net/' `
        -notes @("row added: first post links the KernelEx wiki ($($kw.Groups[1].Value)); thread entries cite KX 4.0rc2 to 4.5.2; version not stated for KernelEx itself")))
}
Write-LeadsCsv $rows (Join-Path $script:LeadsDir 'msfn-kernelex.csv')
