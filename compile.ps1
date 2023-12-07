$file = "Day6/main.cpp";
$optimization;
if($args[0] -eq "-o"){$optimization = "-O3";}
else{$optimization = "-O0";}

g++.exe -static-libstdc++ $optimization $file `
    -o main.exe;
if(!$LASTEXITCODE){
    if($args[1] -eq "-m"){ Measure-Command{./main.exe;} }
    else{ ./main.exe; }
    Remove-Item main.exe;
    Write-Host -NoNewLine 'FINSIHED RUNNING...';
    $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
    Clear-Host;
}