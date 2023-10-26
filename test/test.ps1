$beforePath = $PWD.Path
cd $PSScriptRoot
Get-Content .\centerhor.txt | ..\tictactoe.exe
Get-Content .\centerver.txt | ..\tictactoe.exe
Get-Content .\leftdiag.txt | ..\tictactoe.exe
Get-Content .\rightdiag.txt | ..\tictactoe.exe
Get-Content .\draw.txt | ..\tictactoe.exe
cd $beforePath