param(
    [Parameter(Mandatory=$true)][string]$Repository,
    [Parameter(Mandatory=$true)][string]$Revision,
    [Parameter(Mandatory=$true)][string[]]$Paths,
    [string]$Pattern = 'rknn|RKNN|rk3568|rk3588|core_mask|sqlite|CREATE TABLE|INSERT INTO|roi|polygon|alarm|cooldown|queue|drop|ACK|outbox|TODO|stub|placeholder',
    [int]$MatchLimit = 35,
    [switch]$UseApi
)
$ErrorActionPreference = 'Stop'
$cacheDirectory = Join-Path $PSScriptRoot ('../work/completed-vision-projects/source/'+$Repository.Replace('/','__'))
[System.IO.Directory]::CreateDirectory($cacheDirectory) | Out-Null
foreach ($sourcePath in $Paths) {
    $url = 'https://raw.githubusercontent.com/'+$Repository+'/'+$Revision+'/'+$sourcePath
    try {
        $cachePath = Join-Path $cacheDirectory ($sourcePath.Replace('/','__')+'.txt')
        if (Test-Path -LiteralPath $cachePath) {
            $content = [System.IO.File]::ReadAllText($cachePath)
        } elseif ($UseApi) {
            $apiUrl = 'https://api.github.com/repos/'+$Repository+'/contents/'+$sourcePath+'?ref='+$Revision
            $response = Invoke-RestMethod -Uri $apiUrl -Headers @{'User-Agent'='Codex-RK3568-Research'; Accept='application/vnd.github+json'} -TimeoutSec 25
            $content = [System.Text.Encoding]::UTF8.GetString([Convert]::FromBase64String($response.content))
        } else {
            $response = Invoke-WebRequest -Uri $url -TimeoutSec 25
            $content = [string]$response.Content
        }
        [System.IO.File]::WriteAllText($cachePath,$content,[System.Text.UTF8Encoding]::new($false))
        $lines = $content -split "`n"
        $matches = for ($lineIndex=0; $lineIndex -lt $lines.Count; $lineIndex++) {
            if ($lines[$lineIndex] -match $Pattern) {
                '{0}: {1}' -f ($lineIndex+1),$lines[$lineIndex]
            }
        }
        [pscustomobject]@{url=$url;path=$sourcePath;lines=$lines.Count;matches=@($matches | Select-Object -First $MatchLimit)} | ConvertTo-Json -Depth 5
    } catch {
        [pscustomobject]@{url=$url;error=$_.Exception.Message} | ConvertTo-Json
    }
}
