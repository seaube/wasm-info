#!/usr/bin/env pwsh

$ErrorActionPreference = 'Stop'

$BinDirectory = if ($args.Length -eq 1) {
  $args.Get(0)
} else {
	"$Home\.local\bin"
}
$WasmInfoExe = "$BinDirectory\wasm-info.exe"

if (!(Test-Path $BinDirectory)) {
  New-Item $BinDirectory -ItemType Directory | Out-Null
}

# GitHub requires TLS 1.2
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

Write-Host "Fetching lastest release..."
$Response = Invoke-WebRequest 'https://github.com/seaube/wasm-info/releases' -UseBasicParsing
if ($PSVersionTable.PSEdition -eq 'Core') {
	$WasmInfoUri = $Response.Links |
		Where-Object { $_.href -like "/seaube/wasm-info/releases/download/*/wasm-info-windows.exe" } |
		ForEach-Object { 'https://github.com' + $_.href } |
		Select-Object -First 1
} else {
	$HTMLFile = New-Object -Com HTMLFile
	if ($HTMLFile.IHTMLDocument2_write) {
		$HTMLFile.IHTMLDocument2_write($Response.Content)
	} else {
		$ResponseBytes = [Text.Encoding]::Unicode.GetBytes($Response.Content)
		$HTMLFile.write($ResponseBytes)
	}
	$WasmInfoUri = $HTMLFile.getElementsByTagName('a') |
		Where-Object { $_.href -like "about:/seaube/wasm-info/releases/download/*/wasm-info-windows.exe" } |
		ForEach-Object { $_.href -replace 'about:', 'https://github.com' } |
		Select-Object -First 1
}


Write-Host "Downloading wasm-info.exe to $WasmInfoExe..."
Invoke-WebRequest $WasmInfoUri -OutFile $WasmInfoExe -UseBasicParsing

$User = [EnvironmentVariableTarget]::User
$Path = [Environment]::GetEnvironmentVariable('Path', $User)
if (!(";$Path;".ToLower() -like "*;$BinDirectory;*".ToLower())) {
  Write-Output "Adding bin directory ($BinDirectory) to Environment path..."
  [Environment]::SetEnvironmentVariable('Path', "$Path;$BinDirectory", $User)
  $Env:Path += ";$BinDirectory"
}

Write-Host "wasm-info installed" -ForegroundColor Green
