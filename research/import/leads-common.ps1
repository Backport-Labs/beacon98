# leads-common.ps1 - shared helpers for the osr-final / osr-kernelex / msfn-kernelex lead importers.
# Dot-source from the importer scripts. Windows PowerShell 5.1 compatible.
# Policy: pages are used as leads only. We record facts (name, version, OS, prerequisites, link)
# and never copy descriptive prose from the "All Rights Reserved" OSR blog into our files.

$ErrorActionPreference = 'Stop'
$script:UA = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0 Safari/537.36'
$script:ResearchRoot = 'D:\Win98SE\beacon\research'
$script:CacheDir = Join-Path $script:ResearchRoot 'import\cache'
$script:LeadsDir = Join-Path $script:ResearchRoot 'leads'
$script:Columns = 'source','name','version','os','needs','category','license_class','license','license_evidence','homepage','download','notes'
foreach ($d in $script:CacheDir, $script:LeadsDir) { if (-not (Test-Path $d)) { New-Item -ItemType Directory -Force $d | Out-Null } }

# Fetch a web page (HTML only) into the cache. Falls back to the cached copy if the fetch fails
# or returns a bot-challenge page. Returns the HTML text.
function Get-LeadPage {
    param([string]$Url, [string]$CacheName, [int]$MinBytes = 10000)
    $dest = Join-Path $script:CacheDir $CacheName
    $tmp = "$dest.tmp"
    & curl.exe -sL --max-time 60 -A $script:UA -o $tmp $Url
    $ok = $false
    if (Test-Path $tmp) {
        $len = (Get-Item $tmp).Length
        $head = [IO.File]::ReadAllText($tmp)
        if ($len -ge $MinBytes -and $head -notmatch '<title>Just a moment') { $ok = $true }
    }
    if ($ok) { Move-Item -Force $tmp $dest }
    else {
        if (Test-Path $tmp) { Remove-Item -Force $tmp }
        if (Test-Path $dest) { Write-Warning "Fetch failed for $Url, using cached $dest" }
        else { throw "Fetch failed for $Url and no cache at $dest" }
    }
    return [IO.File]::ReadAllText($dest, [Text.Encoding]::UTF8)
}

function Get-PlainText([string]$html) {
    $t = [regex]::Replace($html, '<[^>]+>', '')
    $t = [Net.WebUtility]::HtmlDecode($t)
    return ($t -replace '[\s\u00A0]+', ' ').Trim()
}

# Split "Name 1.2.3 qualifier" into name / version / leftover qualifier.
# A token counts as a version only if it is dotted (1.2, 0.72RC1, 1.0.2t, 1.3-20071014), svn/rev style,
# or a bare integer followed by update/build. Bare integers otherwise stay in the name (never guess).
function Split-NameVersion([string]$s) {
    $s = ($s -replace '[\s\u00A0]+', ' ').Trim()
    $tok = @($s -split ' ' | Where-Object { $_ -ne '' })
    $qual = '^(?i)(alpha|beta|rc\d*|esr|update|build|sp\d*|rev\.?|final)$'
    $vi = -1
    for ($i = 1; $i -lt $tok.Count; $i++) {
        $t = $tok[$i]
        if ($t -match '^(?i)v?\d+\.\d+[\w.\-]*' -or $t -match '^(?i)(svn-?)?r(ev)?\d{3,}$' -or $t -match '^(?i)svn-r\d+') { $vi = $i; break }
        if ($t -match '^\d+$' -and ($i + 1) -lt $tok.Count -and $tok[$i + 1] -match '^(?i)(update|build)$') { $vi = $i; break }
        if ($t -match '^(?i)build$' -and ($i + 1) -lt $tok.Count -and $tok[$i + 1] -match '^\d+(\.\d+)*') {
            $name = ($tok[0..($i - 1)] -join ' ')
            $rest = ''
            if (($i + 2) -lt $tok.Count) { $rest = ($tok[($i + 2)..($tok.Count - 1)] -join ' ') }
            return @{ name = $name; version = ('build ' + ($tok[$i + 1] -replace '[^\w.]+.*$', '')); rest = $rest }
        }
    }
    # Single token like LAVFilters-0.66.0-10
    if ($vi -lt 0 -and $tok.Count -ge 1 -and $tok[0] -match '^([A-Za-z][A-Za-z]+)-(\d+\.\d[\w.\-]*)$') {
        return @{ name = $Matches[1]; version = $Matches[2]; rest = (($tok | Select-Object -Skip 1) -join ' ') }
    }
    if ($vi -lt 0) { return @{ name = $s; version = ''; rest = '' } }
    $name = ($tok[0..($vi - 1)] -join ' ') -replace '(?i)\s+(ver\.?|version|v)$', ''
    $v = @($tok[$vi] -replace '[^\w.\-]+$', '')
    $j = $vi + 1
    while ($j -lt $tok.Count) {
        if ($tok[$j] -match $qual) {
            $v += $tok[$j]
            if (($j + 1) -lt $tok.Count -and $tok[$j + 1] -match '^\d+[\w.]*$') { $v += $tok[$j + 1]; $j++ }
            $j++
        } elseif ($tok[$j] -match '^\d+$' -and $v[-1] -match '^(?i)(update|build|rev\.?)$') { $v += $tok[$j]; $j++ }
        else { break }
    }
    $rest = ''
    if ($j -lt $tok.Count) { $rest = ($tok[$j..($tok.Count - 1)] -join ' ') }
    return @{ name = $name.Trim(' ', ',', '-'); version = ($v -join ' '); rest = $rest.Trim() }
}

# Prerequisites named in a line (keyword detection only; source wording is not copied).
function Get-Needs([string]$text) {
    $n = New-Object System.Collections.Generic.List[string]
    $map = [ordered]@{
        'GDIPLUS'                         = 'GDIPLUS.dll'
        'DirectX 9'                       = 'DirectX 9'
        'MSXML4'                          = 'MSXML4 SP2'
        'Internet Explorer 5\.5'          = 'Internet Explorer 5.5'
        'SSE2 CPU'                        = 'SSE2 CPU'
        '(?i)mfc80\.dll'                  = 'mfc80.dll'
        '(?i)mfc42u\.dll'                 = 'mfc42u.dll'
        '(?i)Asian language'              = 'Asian language support'
        '(?i)revolutions pack required'   = 'Revolutions Pack'
        '(?i)Requires codecs|install codecs' = 'codecs'
        '(?i)Pluggo runtime'              = 'Pluggo runtime'
    }
    foreach ($k in $map.Keys) { if ($text -match $k -and -not $n.Contains($map[$k])) { $n.Add($map[$k]) } }
    foreach ($m in [regex]::Matches($text, '(?i)d3dx9_\d+\.dll')) { if (-not $n.Contains($m.Value.ToLower())) { $n.Add($m.Value.ToLower()) } }
    return $n
}

# License classes from the importer author's memory (NOT from the source pages). Matched in order
# against "name version". Only entries we are confident about. class, SPDX (or '' when unsure).
$script:LicenseMemory = @(
    ,@('^KernelEx( 4\.| \(|$)', 'open-source', 'GPL-2.0-only')
    ,@('(?i)^(Unofficial )?DirectX|^DotNET|\.NET framework|^Windows Media Player|^Internet Explorer|^Microsoft |^MS Paint|^MSN |^Visual C\+\+|Visual C\+\+ 2008 Runtime|^VirtualPC|^Connectix Virtual PC|Sysinternals|^WinHlp32|^Charmap|\.(EXE|DLL)\b|^VC_R_9X|^Yahoo', 'freeware-unclear', '')
    ,@('(?i)^Windows (98SE|ME) Unofficial Service Pack', 'freeware-unclear', '')
    ,@('(?i)^(Easy )?7-?zip', 'open-source', '')
    ,@('(?i)^Audacity', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Clamwin', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Clam Sentinel', 'open-source', '')
    ,@('(?i)^ffdshow', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^DirectVobSub', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Python 2\.7', 'open-source', 'PSF-2.0')
    ,@('(?i)^SumatraPDF', 'open-source', 'GPL-3.0-only')
    ,@('(?i)^Paint\.NET 2\.', 'open-source', 'MIT')
    ,@('(?i)^PeaZip', 'open-source', 'LGPL-3.0-only')
    ,@('(?i)^TestDisk', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Qt 4\.', 'open-source', '')
    ,@('(?i)^OpenSSL 1\.', 'open-source', 'OpenSSL')
    ,@('(?i)^SQLite', 'open-source', 'blessing')
    ,@('(?i)^Mesa3D', 'open-source', 'MIT')
    ,@('(?i)^(Sherpya |Redxii )?MPlayer( WW| \(|$| svn)|^MPlayerWW|^MPlayer MPUI', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^mplayer2', 'open-source', '')
    ,@('(?i)^TCPMP', 'open-source', '')
    ,@('(?i)^VLC', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^OpenOffice(\.org)? 2\.', 'open-source', 'LGPL-2.1-only')
    ,@('(?i)^OpenOffice(\.org)? 3\.', 'open-source', 'LGPL-3.0-only')
    ,@('(?i)^AbiWord', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^(Open)?JDK 1\.6|OpenJDK', 'open-source', 'GPL-2.0-only WITH Classpath-exception-2.0')
    ,@('(?i)^CamStudio', 'open-source', '')
    ,@('(?i)^PuTTY', 'open-source', 'MIT')
    ,@('(?i)^Notepad\+\+', 'open-source', '')
    ,@('(?i)^Notepad2', 'open-source', '')
    ,@('(?i)^Retro ?Arch', 'open-source', 'GPL-3.0-or-later')
    ,@('(?i)^VisualBoyAdvance', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^ZSNES', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Retrozilla', 'open-source', '')
    ,@('(?i)^FileZilla', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^(Mozilla )?Thunderbird', 'open-source', '')
    ,@('(?i)^LAVFilters', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Infrarecorder', 'open-source', '')
    ,@('(?i)^GIMP', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^Wings ?3D', 'open-source', '')
    ,@('(?i)^Universal Extractor', 'open-source', '')
    ,@('(?i)^Media Player Classic', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^SMPlayer', 'open-source', '')
    ,@('(?i)^UMPlayer', 'open-source', '')
    ,@('(?i)^Eraser 5', 'open-source', '')
    ,@('(?i)^AviDemux', 'open-source', 'GPL-2.0-or-later')
    ,@('(?i)^BOCHS', 'open-source', 'LGPL-2.1-or-later')
    ,@('(?i)^QEMU', 'open-source', '')
    ,@('(?i)^(Mozilla )?Firefox', 'open-source', '')
    ,@('(?i)^(Mozilla )?Seamonkey', 'open-source', '')
    ,@('(?i)^(Roytam1.s )?Pale ?Moon', 'open-source', '')
    ,@('(?i)^Qupzilla', 'open-source', '')
    ,@('(?i)^bbLean', 'open-source', '')
    ,@('(?i)^Graphviz', 'open-source', '')
    ,@('(?i)^xCHM', 'open-source', '')
    ,@('(?i)^Golly', 'open-source', '')
    ,@('(?i)^DownThemAll', 'open-source', '')
    ,@('(?i)^IconsExtract|^Siteshoter', 'freeware', '')
    ,@('(?i)^TrueCrypt', 'freeware-unclear', 'TrueCrypt License')
    ,@('(?i)^(AutoIt|PhotoFiltre|Artweaver|Freebyte Zip|FastStone Image Viewer|Irfanview|IfranView|Xnview|GeoGebra|GOM Player|XMPlay|Virtual ?Clone ?Drive|Eusing Free Registry Cleaner|Java 6u7|Java Runtime Environment|Java Developer Kit|(Adobe )?Flash Player|Adobe Shockwave|Skype|CPU-Z|Revolutions Pack|Avast|SpywareBlaster|Imgburn|Roadkil|Terragen|Foxit ?Reader|Adobe (Acrobat )?Reader|Opera|uTorrent|BitTorrent|pSX|Epsxe|xplorer2|Meesoft|Kobarin|K-Lite|Haali|Haihaisoft|PDF ?X-?Change ?Viewer|STDU Viewer|Download Master|Burnaware Free|ArtWeaver|Kerkythea|Pixelformer|SophosFreeEncrytion|Google Picasa|KMPlayer|(Daum )?PotPlayer|Alshow|foobar2000|TextMaker Viewer|PC-Wizard|Super2009|H2testw|Zsoft Uninstaller|BlueCat|SyncBack|AptDiff|JNES|Ootake|SUPERAntiSpyware Free|Imagine|Kingsoft Presentation)', 'freeware-unclear', '')
    ,@('(?i)^(WinZip|WinRAR|PowerISO|MilkShape|Talisman Desktop|Goldwave|Textaloud|LeaderTask)', 'shareware', '')
    ,@('(?i)^(Driver Genius Professional|Odyssey Client|AT&T (Crystal|Paul)|Nero Burning ROM|Adobe Photoshop|Photoshop CS|Corel Paint Shop Pro|Starry Night|ZoneAlarm Pro|WordPerfect|TextMaker 2008|Winamp Pro|CyberPower Audio Editing Lab|Alcohol 120|CoreCodec CorePlayer|Adobe Acrobat Professional|Doom 3|Quake 4|Prey|Need for Speed|Race On|Zombie Shooter)', 'commercial', '')
)

function Get-LicenseMemory([string]$name, [string]$version) {
    $key = ("$name $version").Trim()
    foreach ($e in $script:LicenseMemory) { if ($key -match $e[0]) { return @{ class = $e[1]; license = $e[2] } } }
    return $null
}

function Test-MicrosoftComponent([string]$name) {
    return ($name -match '(?i)^(Unofficial )?DirectX|^DotNET|\.NET framework|^Windows Media Player|^Internet Explorer|^Microsoft |^MS Paint|^MSN |^Visual C\+\+|Visual C\+\+ 2008 Runtime|^VirtualPC|^Connectix Virtual PC|Sysinternals|^WinHlp32|^Charmap|^(MSPAINT|MSXML3|QUARTZ|NOTEPAD|VC_R_9X|WORDPAD|USBVIEW)\.|^Windows (98SE|ME) Unofficial Service Pack')
}

function New-LeadRow {
    param([string]$source, [string]$name, [string]$version = '', [string]$os = '', [string]$needs = '',
          [string]$category = '', [string]$license_class = '', [string]$license = '', [string]$license_evidence = '',
          [string]$homepage = '', [string]$download = '', [string[]]$notes = @(), [switch]$NoMemory)
    $n = New-Object System.Collections.Generic.List[string]
    foreach ($x in $notes) { if ($x) { $n.Add($x) } }
    if (-not $license_class) {
        $lm = $null
        if (-not $NoMemory) { $lm = Get-LicenseMemory $name $version }
        if ($lm) { $license_class = $lm.class; if (-not $license) { $license = $lm.license }; $n.Add('class from memory') }
        else { $license_class = 'unknown' }
    }
    if (Test-MicrosoftComponent $name) { $n.Add('Microsoft component (excluded for now)') }
    # Drop a prerequisite that is the program itself (e.g. the DirectX 9 row "needing" DirectX 9)
    $kept = @()
    foreach ($nd in ($needs -split '; ')) {
        if (-not $nd) { continue }
        if ($name.IndexOf($nd, [StringComparison]::OrdinalIgnoreCase) -ge 0) { continue }
        $kept += $nd
    }
    $needs = $kept -join '; '
    $o = [ordered]@{ source = $source; name = $name; version = $version; os = $os; needs = $needs; category = $category;
        license_class = $license_class; license = $license; license_evidence = $license_evidence;
        homepage = $homepage; download = $download; notes = ($n -join '; ') }
    return [pscustomobject]$o
}

# Classify a link given by the source: direct file -> download, page -> homepage.
function Set-LeadLink($h, [string]$url) {
    if (-not $url) { return }
    if ($url -match '(?i)\.(exe|zip|msi|7z|rar)(\?|$)' -or $url -match '(?i)/download(/|$)|post_download|mega\.nz/file|downloads$') { $h.download = $url }
    else { $h.homepage = $url }
}

function Write-LeadsCsv($rows, [string]$path) {
    $lines = $rows | Select-Object $script:Columns | ConvertTo-Csv -NoTypeInformation
    [IO.File]::WriteAllLines($path, [string[]]$lines, (New-Object System.Text.UTF8Encoding($false)))
    $cnt = $lines.Count - 1
    Write-Host "Wrote $cnt rows to $path"
    $rows | Group-Object license_class | Sort-Object Name | ForEach-Object { Write-Host ('  ' + $_.Name.PadRight(17) + ' ' + $_.Count) }
}
