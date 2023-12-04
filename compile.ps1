g++.exe -static-libstdc++ Day4/main.cpp `
    -o main.exe;
if(!$LASTEXITCODE){
    ./main.exe;
    Remove-Item main.exe;
    Write-Host -NoNewLine 'FINSIHED RUNNING...';
    $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
    Clear-Host;
}