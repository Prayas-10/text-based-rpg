param(
    [Parameter(Mandatory=$true)]
    [string]$ExePath,

    [string]$PfxPath = "C:\LocalDevSigningKey.pfx",
    [string]$Password = "Developer123"
)

$ErrorActionPreference = "Stop"

if (!(Test-Path $ExePath)) {
    throw "Executable not found: $ExePath"
}

if (!(Test-Path $PfxPath)) {
    throw "Signing certificate not found: $PfxPath"
}

$signtool = Get-ChildItem `
    "$env:ProgramFiles(x86)\Windows Kits\10\bin" `
    -Filter signtool.exe `
    -Recurse `
    -ErrorAction SilentlyContinue |
    Where-Object { $_.FullName -match "\\x64\\signtool.exe$" } |
    Sort-Object FullName |
    Select-Object -Last 1

if (-not $signtool) {
    throw "signtool.exe was not found. Install the Windows 10/11 SDK."
}

Write-Host "Signing Dharmadeva's Blade" -ForegroundColor Cyan
Write-Host "Certificate: $PfxPath" -ForegroundColor Yellow

& $signtool.FullName sign `
    /fd SHA256 `
    /f $PfxPath `
    /p $Password `
    $ExePath

if ($LASTEXITCODE -ne 0) {
    throw "signtool failed with exit code $LASTEXITCODE."
}

Write-Host "Signed successfully: $ExePath" -ForegroundColor Green
