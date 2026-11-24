param(
    [Parameter(Mandatory=$true)][string[]]$Repositories,
    [int]$ReadmeLimit = 11000,
    [string]$OutputDirectory = 'work/completed-vision-projects',
    [int]$FileLimit = 80
)
$ErrorActionPreference = 'Stop'
$cacheDirectory = Join-Path (Split-Path $PSScriptRoot -Parent) $OutputDirectory
[System.IO.Directory]::CreateDirectory($cacheDirectory) | Out-Null
$requestHeaders = @{Accept='application/vnd.github+json'; 'User-Agent'='Codex-RK3568-Research'}
$utf8Encoding = [System.Text.UTF8Encoding]::new($false)
foreach ($repository in $Repositories) {
    $cacheName = $repository.Replace('/', '__')
    $record = [ordered]@{repository=$repository; fetched_at_utc=[DateTime]::UtcNow.ToString('o')}
    try {
        $metadata = Invoke-RestMethod -Uri ('https://api.github.com/repos/'+$repository) -Headers $requestHeaders -TimeoutSec 35
        $readmeResponse = Invoke-RestMethod -Uri ('https://api.github.com/repos/'+$repository+'/readme') -Headers $requestHeaders -TimeoutSec 35
        $readme = [System.Text.Encoding]::UTF8.GetString([Convert]::FromBase64String($readmeResponse.content))
        $tree = Invoke-RestMethod -Uri ('https://api.github.com/repos/'+$repository+'/git/trees/'+$metadata.default_branch+'?recursive=1') -Headers $requestHeaders -TimeoutSec 35
        $record.metadata = $metadata
        $record.readme_path = $readmeResponse.path
        $record.readme = $readme
        $record.tree = $tree
        [System.IO.File]::WriteAllText((Join-Path $cacheDirectory ($cacheName+'.json')), ($record | ConvertTo-Json -Depth 30), $utf8Encoding)
        [pscustomobject]@{
            repository=$repository
            description=$metadata.description
            branch=$metadata.default_branch
            commit=$tree.sha
            pushed_at=$metadata.pushed_at
            stars=$metadata.stargazers_count
            license=$metadata.license.spdx_id
            archived=$metadata.archived
            tree_truncated=$tree.truncated
            files= @($tree.tree | Where-Object { $_.type -eq 'blob' } | Select-Object -First $FileLimit | ForEach-Object path)
            readme=$readme.Substring(0,[Math]::Min($ReadmeLimit,$readme.Length))
        } | ConvertTo-Json -Depth 8
    } catch {
        [pscustomobject]@{repository=$repository;error=$_.Exception.Message} | ConvertTo-Json
    }
}
