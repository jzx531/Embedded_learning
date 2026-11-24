param([string]$OutputDirectory = "$PSScriptRoot/repos")
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
$repos = @(
 'airockchip/rknn-toolkit2', 'airockchip/rknn_model_zoo',
 'rockchip-linux/mpp', 'airockchip/librga', 'ZLMediaKit/ZLMediaKit',
 'buildroot/buildroot', 'u-boot/u-boot', 'rockchip-linux/kernel',
 'libmodbus/libmodbus', 'eclipse-mosquitto/mosquitto', 'rauc/rauc',
 'OpenEtherCATsociety/SOEM', 'ros-navigation/navigation2',
 'openwrt/openwrt', 'RT-Thread/rt-thread', 'lvgl/lvgl',
 'home-assistant/core', 'openmediavault/openmediavault',
 'Yinyifeng18/xiaozhi-linux-rk3568', 'Qengineering/YoloV8-NPU'
)
$repos | ForEach-Object -Parallel {
 $repo = $_
 $out = $using:OutputDirectory
 $headers = @{'User-Agent'='RK3568-project-research'; 'Accept'='application/vnd.github+json'}
 $item = [ordered]@{requested_repo=$repo; fetched_at_utc=[DateTime]::UtcNow.ToString('o')}
 try {
  $meta = Invoke-RestMethod -Headers $headers -Uri "https://api.github.com/repos/$repo" -TimeoutSec 30
  $item.metadata = $meta | Select-Object full_name,html_url,description,default_branch,stargazers_count,archived,pushed_at,language,license
  $readme = Invoke-RestMethod -Headers $headers -Uri "https://api.github.com/repos/$repo/readme" -TimeoutSec 30
  $item.readme_url = $readme.html_url
  $item.readme = [Text.Encoding]::UTF8.GetString([Convert]::FromBase64String($readme.content))
 } catch { $item.error = $_.Exception.Message }
 $item | ConvertTo-Json -Depth 12 | Set-Content -Encoding utf8 -LiteralPath (Join-Path $out ($repo.Replace('/','__')+'.json'))
 [pscustomobject]@{repo=$repo; ok=($null -ne $item.readme); error=$item.error}
} -ThrottleLimit 5 | Format-Table -AutoSize
