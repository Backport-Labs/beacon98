# Import MSFN "Last Versions of Software for Windows 95" into research\leads\msfn-95.csv.
# Parses list lines of the form  "LAST - FREE - 7-zip 9.20 (2010-11-18) --- URL"
# from the opening post and from replies on every page of the thread (quoted text is ignored).
# Rerunnable. Usage: powershell -File import-msfn95.ps1 [-Offline]
param([switch]$Offline)
. (Join-Path $PSScriptRoot '_common.ps1')

$Source = 'msfn-95'
$TopicUrl = 'https://msfn.org/board/topic/176623-last-versions-of-software-for-windows-95/'
$MaxPages = 20

# Legend from the opening post:
#   LAST = last version to support Win95, ONGD = ongoing development, ???? = unknown
#   FREE = Freeware/Open Source, SHAR = Shareware, $$$$ = commercial, ???? = unknown
#   superscript 2 = requires Windows 95 OSR 2.x
$TagClass = @{ 'FREE' = 'freeware'; 'SHAR' = 'shareware'; '$$$$' = 'commercial'; '????' = 'unknown' }
$TagLicense = @{ 'FREE' = 'FREE (Freeware/Open Source per thread legend)'; 'SHAR' = 'SHAR (Shareware per thread legend)'; '$$$$' = '$$$$ (commercial per thread legend)'; '????' = '' }

# Knowledge used only to fill obvious gaps. Every row touched here gets "class from memory" in notes.
# FREE is ambiguous (freeware OR open source); these are well-known open-source projects.
$MemOpenSource = [ordered]@{
    '^7-zip'              = 'LGPL-2.1-or-later (with unRAR restriction)'
    '^DOSBox'             = 'GPL-2.0-or-later'
    '^FileZilla'          = 'GPL-2.0-or-later'
    '^Mozilla Firefox'    = 'MPL-1.1 OR GPL-2.0-or-later OR LGPL-2.1-or-later'
    '^SeaMonkey'          = 'MPL-1.1 OR GPL-2.0-or-later OR LGPL-2.1-or-later'
    '^GrafX2'             = 'GPL-2.0'
    '^Stella'             = 'GPL-2.0-or-later'
    '^VLC'                = 'GPL-2.0-or-later'
    '^Bochs'              = 'LGPL-2.1-or-later'
}
$MemMicrosoft = '^(Microsoft|Internet Explorer|Windows Media Player|DirectX|Visual C\+\+|Visual Basic)'
# Tagged FREE but known to have restrictive redistribution terms: keep the source class, add a caution.
$MemCaution = [ordered]@{
    '^Adobe Acrobat Reader'   = 'Adobe Reader redistribution needs a separate Adobe distribution agreement'
    '^Java Runtime'           = 'Sun Binary Code License: redistribution only under its conditions'
    '^Macromedia Flash'       = 'Flash Player redistribution needed a Macromedia/Adobe distribution license'
    '^Apple QuickTime'        = 'QuickTime redistribution needed an Apple license'
    '^RealPlayer'             = 'proprietary; redistribution not generally permitted'
    '^Opera'                  = 'proprietary freeware; redistribution terms not verified'
    '^XnView'                 = 'free for private/non-commercial use only'
    '^(InfraView|IrfanView)'  = 'IrfanView: free for non-commercial use'
    '^PhotoFiltre'            = 'PhotoFiltre 7: free for private/educational use'
    '^Process Explorer'       = 'Sysinternals tool; redistribution not permitted by its license'
    '^mIRC'                   = 'mIRC is generally shareware; the source tags this version FREE'
    '^WS_FTP LE'              = 'free for non-commercial/educational use'
    '^(AOL Instant Messenger|Yahoo! Messenger|Netscape)' = 'proprietary client; redistribution terms not verified'
}

function Get-Posts([string]$html, [int]$page) {
    $posts = @()
    $arts = [regex]::Matches($html, '(?s)<article\b[^>]*\bid="elComment_(\d+)"([^>]*)>(.*?)</article>')
    foreach ($a in $arts) {
        $body = $a.Groups[3].Value
        $author = ([regex]::Match($body, '(?s)class="ipsUsername"[^>]*>([^<]+)<')).Groups[1].Value.Trim()
        $cm = [regex]::Match($body, '(?s)data-role="commentContent"[^>]*>(.*)$')
        $content = $cm.Groups[1].Value
        # drop quoted text from earlier posts
        $content = [regex]::Replace($content, '(?is)<blockquote\b.*?</blockquote>', ' ')
        $posts += [pscustomobject]@{ id = $a.Groups[1].Value; first = ($a.Groups[2].Value -match 'data-ips-first-post'); author = $author; page = $page; html = $content }
    }
    return $posts
}

Write-Host "== $Source"
$allPosts = @()
$lastPage = 1
for ($pg = 1; $pg -le $lastPage; $pg++) {
    $url = if ($pg -eq 1) { $TopicUrl } else { "${TopicUrl}page/$pg/" }
    $name = if ($pg -eq 1) { 'msfn95.html' } else { "msfn95_p$pg.html" }
    $path = Get-CachedPage -Url $url -Name $name -Offline:$Offline
    $html = [IO.File]::ReadAllText($path, [Text.Encoding]::UTF8)
    if ($pg -eq 1) {
        $nums = [regex]::Matches($html, [regex]::Escape($TopicUrl) + 'page/(\d+)/') | ForEach-Object { [int]$_.Groups[1].Value }
        if ($nums) { $lastPage = [Math]::Min($MaxPages, ($nums | Measure-Object -Maximum).Maximum) }
        Write-Host "  thread pages: $lastPage"
    }
    $allPosts += Get-Posts $html $pg
}
Write-Host "  posts parsed: $($allPosts.Count)"

$lineRx = '^(LAST|ONGD|\?\?\?\?)\s*-\s*(FREE|SHAR|\$\$\$\$|\?\?\?\?)\s*-\s*(.+?)\s*(?:-{3,}\s*(.*))?$'
$rows = New-Object System.Collections.Generic.List[object]
$seen = @{}
$problems = New-Object System.Collections.Generic.List[string]
foreach ($p in $allPosts) {
    $text = $p.html -replace '(?i)<br\s*/?>', "`n" -replace '(?i)</p>', "`n" -replace '(?i)</li>', "`n"
    $hrefs = [regex]::Matches($p.html, '(?i)<a\b[^>]*href="([^"]+)"[^>]*>(.*?)</a>') | ForEach-Object { [pscustomobject]@{ href = [System.Net.WebUtility]::HtmlDecode($_.Groups[1].Value); text = (ConvertTo-PlainText $_.Groups[2].Value) } }
    $plain = [System.Net.WebUtility]::HtmlDecode(($text -replace '<[^>]+>', '')) -replace [char]0xA0, ' '
    foreach ($ln in ($plain -split "`n")) {
        $ln = $ln.Trim()
        if ($ln -notmatch '^(LAST|ONGD|\?\?\?\?)\s*-\s*(FREE|SHAR|\$\$\$\$|\?\?\?\?)\s*-') { continue }   # skips the key legend lines
        $m = [regex]::Match($ln, $lineRx)
        if (-not $m.Success) { $problems.Add("could not split (post $($p.id)): $ln"); continue }
        $status = $m.Groups[1].Value; $tag = $m.Groups[2].Value; $item = $m.Groups[3].Value.Trim(); $tail = $m.Groups[4].Value.Trim()

        $osr2 = $item.Contains([string][char]0x00B2)
        $item = $item.Replace([string][char]0x00B2, '')
        $date = ''
        $dm = [regex]::Match($item, '\(([^)]*)\)\s*$')
        $extra = @()
        if ($dm.Success) {
            if ($dm.Groups[1].Value -match '^\d{4}(-\d{2}){0,2}$|^(late|early|mid)\s+\d{4}$') { $date = $dm.Groups[1].Value } else { $extra += $dm.Groups[1].Value }
            $item = $item.Substring(0, $dm.Index).Trim()
        }
        $name = $item; $ver = ''
        $vm = [regex]::Match($item, '^(.*?)\s+(\d[\w.]*(?:\s+(?:SP\d+|SR\d+|Update\s+\d+|Basic|ANSI|[a-z]))*)$')
        if ($vm.Success -and $vm.Groups[2].Value -notmatch '^(19|20)\d\d$') { $name = $vm.Groups[1].Value.Trim(); $ver = $vm.Groups[2].Value.Trim() }

        # URL: prefer the real href of the link on that line, fall back to the text
        $url = ''
        if ($tail) {
            $tu = ($tail -split '\s')[0]
            $h = $hrefs | Where-Object { $_.text -eq $tu -or $_.href -eq $tu } | Select-Object -First 1
            if ($h) { $url = $h.href } elseif ($tu -match '^(https?|ftp)://') { $url = $tu }
            elseif ($tu -match '\.\w{2,4}$') {
                $h = $hrefs | Where-Object { $_.text -eq $tu -or $_.href -like "*$tu" } | Select-Object -First 1
                if ($h) { $url = $h.href } else { $extra += "link text '$tu' (no URL found)" }
            }
            else { $extra += $tail.Trim('(', ')') }
        }

        $key = ($name + '|' + $ver).ToLower()
        if ($seen.ContainsKey($key)) { continue }

        $class = $TagClass[$tag]; $lic = $TagLicense[$tag]
        $notes = @("status $status" + $(switch ($status) { 'LAST' { ' (last version supporting Win95)' } 'ONGD' { ' (ongoing development)' } default { ' (unknown if last)' } }))
        if ($tag -ne '????') { $notes += "class from source tag '$tag'" }
        if ($date) { $notes += "release date per source: $date" }
        if ($extra) { $notes += ($extra -join '; ') }
        $postUrl = "${TopicUrl}#findComment-$($p.id)"
        if ($p.first) { $notes += 'from opening post list' } else { $notes += "from reply by $($p.author) (page $($p.page)), not in opening post list" }
        $evidence = if ($tag -ne '????') { $postUrl } else { '' }

        if ($name -match $MemMicrosoft) {
            $class = 'commercial'; $lic = 'Microsoft (proprietary)'; $evidence = ''
            $notes += 'Microsoft component; class from memory'
        }
        elseif ($tag -eq 'FREE') {
            foreach ($k in $MemOpenSource.Keys) {
                if ($name -match $k) { $class = 'open-source'; $lic = $MemOpenSource[$k]; $evidence = ''; $notes += 'open-source class and SPDX id from memory, not stated by source'; break }
            }
            foreach ($k in $MemCaution.Keys) {
                if ($name -match $k) { $notes += "caution (from memory): $($MemCaution[$k])"; break }
            }
        }

        $isFile = $url -match '\.(exe|zip|msi|7z|rar)$'
        $hp = ''
        if ($url -and -not $isFile -and $url -notmatch 'oldversion\.com|oldapps\.com|archive\.org|ozgundll|ftp\.|download\.|/releases/|/files/') { $hp = $url }

        $row = New-Lead @{
            source = $Source; name = $name; version = $ver; os = $(if ($osr2) { '95 OSR2.x' } else { '95' })
            needs = $(if ($osr2) { 'Windows 95 OSR 2.x (superscript 2 in source)' } else { '' }); category = ''
            license_class = $class; license = $lic; license_evidence = $evidence
            homepage = $hp; download = $url; notes = ($notes -join '; ')
        }
        $seen[$key] = $row
        $rows.Add($row)
    }
}
Write-LeadsCsv -Rows $rows -Source $Source | Out-Null
if ($problems.Count) { Write-Host 'Problems:'; $problems | ForEach-Object { Write-Host "  $_" } }

