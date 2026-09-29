# Builds Beacon 98: compiles BEACON98.EXE and runs its self-test.
#
# Needs Tiny C Compiler 0.9.27, 32-bit Windows build (not included here):
#   http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win32-bin.zip
#
# Usage:
#   .\client\build\build.ps1 -Tcc C:\tools\tcc\tcc.exe
param([Parameter(Mandatory = $true)] [string] $Tcc)
$ErrorActionPreference = 'Stop'
$client = Split-Path -Parent $PSScriptRoot
$repo = Split-Path -Parent $client
$src = Join-Path $client 'src'
$out = Join-Path $client 'build\out'
New-Item -ItemType Directory -Force $out | Out-Null

Write-Host 'Compiling BEACON98.EXE...'
$exe = Join-Path $out 'BEACON98.EXE'
$sources = @(Get-ChildItem (Join-Path $src '*.c') | Sort-Object Name | ForEach-Object FullName)
$defs = @(Get-ChildItem (Join-Path $src '*.def') | Sort-Object Name | ForEach-Object FullName)
& $Tcc -mwindows -Wall -Wimplicit-function-declaration -Werror -o $exe @sources @defs -luser32 -lkernel32 -lgdi32
if ($LASTEXITCODE -ne 0) { throw 'Compiling BEACON98.EXE failed.' }

Write-Host 'Running the self-test...'
$test = Join-Path $out 'selftest'
if (Test-Path $test) { Get-ChildItem $test -File | Remove-Item -Force -Confirm:$false }
New-Item -ItemType Directory -Force $test | Out-Null
Copy-Item $exe $test -Force
Copy-Item (Join-Path $client 'tests\ED25519.TXT'), (Join-Path $client 'tests\PARSE.TXT') $test -Force
Copy-Item (Join-Path $repo 'catalog\CATALOG.TXT'), (Join-Path $repo 'catalog\CATALOG.SIG') $test -Force
# A file of random bytes, so hashing is checked across many buffer boundaries.
$random = New-Object byte[] 5000037
(New-Object Random 98).NextBytes($random)
[IO.File]::WriteAllBytes((Join-Path $test 'RANDOM.BIN'), $random)
# Archives for the unzip test: a folder with small, empty, compressible and random files.
Add-Type -AssemblyName System.IO.Compression, System.IO.Compression.FileSystem
$zipSrc = Join-Path $test 'ZIPSRC'
New-Item -ItemType Directory -Force (Join-Path $zipSrc 'top\sub') | Out-Null
[IO.File]::WriteAllText((Join-Path $zipSrc 'top\a.txt'), "Beacon 98`r`n")
[IO.File]::WriteAllBytes((Join-Path $zipSrc 'top\empty.txt'), (New-Object byte[] 0))
[IO.File]::WriteAllText((Join-Path $zipSrc 'top\sub\c.txt'), ('Windows 98 Second Edition. ' * 8000))
$bin = New-Object byte[] 300001
(New-Object Random 42).NextBytes($bin)
[IO.File]::WriteAllBytes((Join-Path $zipSrc 'top\sub\b.bin'), $bin)
[IO.Compression.ZipFile]::CreateFromDirectory($zipSrc, (Join-Path $test 'TEST.ZIP'))
$prefix = New-Object byte[] 5000
(New-Object Random 7).NextBytes($prefix)
[IO.File]::WriteAllBytes((Join-Path $test 'SFX.EXE'), $prefix + [IO.File]::ReadAllBytes((Join-Path $test 'TEST.ZIP')))
$evil = [IO.Compression.ZipFile]::Open((Join-Path $test 'EVIL.ZIP'), 'Create')
$w = New-Object IO.StreamWriter ($evil.CreateEntry('../EVIL.TXT').Open())
$w.Write('This must not be written.'); $w.Dispose(); $evil.Dispose()

$hashme = 'ED25519.TXT', 'CATALOG.TXT', 'RANDOM.BIN', 'BEACON98.EXE'
[IO.File]::WriteAllText((Join-Path $test 'HASHME.TXT'), ($hashme -join "`r`n") + "`r`n")

$p = Start-Process (Join-Path $test 'BEACON98.EXE') -ArgumentList '/selftest' -PassThru
if (-not $p.WaitForExit(120000)) { Stop-Process -Id $p.Id -Force; throw 'The self-test did not finish.' }

$expected = @(Get-Content (Join-Path $client 'tests\EXPECTED.OUT'))
$got = @(Get-Content (Join-Path $test 'SELFTEST.OUT'))
$bad = 0
for ($i = 0; $i -lt [Math]::Max($expected.Count, $got.Count); $i++) {
    if ($expected[$i] -ne $got[$i]) { $bad++; Write-Host "  expected: $($expected[$i])`n  got:      $($got[$i])" }
}
foreach ($line in @(Get-Content (Join-Path $test 'HASHES.OUT'))) {
    $name, $size, $hash = $line -split ' '
    $file = Get-Item (Join-Path $test $name)
    $want = (Get-FileHash $file.FullName -Algorithm SHA256).Hash.ToLower()
    if ($size -ne "$($file.Length)" -or $hash -ne $want) { $bad++; Write-Host "  $name`: got $size $hash, expected $($file.Length) $want" }
}
$unpacked = 0
foreach ($pair in @(@('OUT1\top', 'top'), @('OUT2', 'top'))) {
    foreach ($src in Get-ChildItem (Join-Path $zipSrc $pair[1]) -Recurse -File) {
        $rel = $src.FullName.Substring((Join-Path $zipSrc $pair[1]).Length + 1)
        $copy = Join-Path (Join-Path $test $pair[0]) $rel
        if (-not (Test-Path $copy) -or (Get-FileHash $copy).Hash -ne (Get-FileHash $src.FullName).Hash) { $bad++; Write-Host "  unzip: $($pair[0])\$rel differs or is missing" }
        else { $unpacked++ }
    }
}
if ($bad) { throw "Self-test: $bad line(s) differ." }
Write-Host "  $unpacked unpacked files match their originals."
Write-Host "  $($expected.Count) lines and $($hashme.Count) file hashes match."
Get-Item $exe | Select-Object Name, Length
