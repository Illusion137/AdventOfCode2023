$file = "Day10/main.cpp";
$optimization;
if($args[0] -eq "-o"){$optimization = "-O3";}
else{$optimization = "-O0";}

g++.exe -static-libstdc++ $optimization $file `
    -o main.exe;
if(!$LASTEXITCODE){
    $completed = 0;
    try {
        $result = Measure-Command{./main.exe | Out-Default}
        Write-Host "Time Milliseconds:" $result.TotalMilliseconds -ForegroundColor Green;
        Remove-Item main.exe;
        Write-Host -NoNewLine 'FINSIHED RUNNING...' -ForegroundColor Red;
        $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
        Clear-Host;
        $completed = 1;
    }
    finally{
        if(!$completed){
            Write-Host 'FINSIHED RUNNING...' -ForegroundColor Red;
            $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
            $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
            Clear-Host;
        }
    }
}
#python test/main.py