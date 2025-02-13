function Register-Protocol {
  [CmdletBinding()]
  param (
    # Parameter help description
    [Parameter(Mandatory)]
    [string]
    $ProtocolName,
    # Parameter help description
    [Parameter(Mandatory)]
    [string]
    $ExecutableName
  )
  
  process {
    $Private:ProtocolKey = "HKCU:\Software\Classes\$ProtocolName"
    if (-not (Test-Path -LiteralPath $ProtocolKey)) {
      New-Item -LiteralPath $ProtocolKey -Force
    }

    Set-ItemProperty -LiteralPath $ProtocolKey -Name "(Default)" -Value "URL:$ProtocolName Protocol"
    Set-ItemProperty -LiteralPath $ProtocolKey -Name "URL Protocol" -Value ""
    
    $Private:CommandKey = "$ProtocolKey\shell\open\command"
    if (-not (Test-Path -LiteralPath $CommandKey)) {
      New-Item -LiteralPath $CommandKey -Force
    }

    Set-ItemProperty -LiteralPath $CommandKey -Name "(Default)" -Value "`"$ExecutableName`" `"%1`""

    Write-Output "Registed $ProtocolName Protocol"
  }
}

$Private:PixEz = Join-Path $PSScriptRoot 'pixez.exe'

if (-not (Test-Path -LiteralPath $PixEz)) {
  throw 'cannot find PixEz.exe'
}

Register-Protocol -ProtocolName 'pixiv' -ExecutableName $PixEz
Register-Protocol -ProtocolName 'pixez' -ExecutableName $PixEz
