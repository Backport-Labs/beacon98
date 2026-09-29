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
if ($bad) { throw "Self-test: $bad line(s) differ." }
Write-Host "  $($expected.Count) lines and $($hashme.Count) file hashes match."
Get-Item $exe | Select-Object Name, Length
