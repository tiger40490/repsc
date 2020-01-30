@echo off
REM copy this entire script to C:\ProgramData\Microsoft\Windows\Start 

REM we can also use cmd /c "c:\progra~1\Git\bin\bash.exe". Note bash.exe is a windowless executable.
REM In contrast, the command below launches a brand-new window created by git-bash.exe

start "title1" "c:\progra~1\Git\git-bash.exe"
