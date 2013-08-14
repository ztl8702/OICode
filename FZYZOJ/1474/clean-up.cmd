@echo off
mode con cols=50 lines=20
title Clean-up Tools


:menu
cls
echo  ====================  Menu  ====================
echo   [M] Rename And Delete
echo   [1] Rename;
echo   [2] Delete *.o *.lpi *.ico *.rc *.manifest 
echo              *.compiled *.res;
echo   [3] Delete *.bak;
echo   [4] Delete *.exe;
echo   [5] Exit;
echo  ================================================
echo   Enter your command:
set /P choice=
echo %choice%
IF %choice% EQU M (goto RAD) ELSE (
IF %choice% EQU 1 (goto renaming) ELSE (
IF %choice% EQU 2 (goto deleting) ELSE (
IF %choice% EQU 3 (goto delbak) ELSE (
IF %choice% EQU 4 (goto delexe) ELSE (
IF %choice% EQU 5 (exit) ELSE (
goto menu))))))


:RAD
cls
for /f "delims=" %%b in ('dir /a-d/b *.lpr') do (
ren "%%b" "%%~nb.pas"
)
del /f /q .\*.o
del /f /q .\*.lpi
del /f /q .\*.ico
del /f /q .\*.rc
del /f /q .\*.manifest
del /f /q .\*.compiled
del /f /q .\*.res
echo Done.
pause
goto menu


:renaming
cls
for /f "delims=" %%b in ('dir /a-d/b *.lpr') do (
ren "%%b" "%%~nb.pas"
)
echo Done.
pause
goto menu


:delbak
cls
del /f /q .\*.bak
echo Done.
pause
goto menu


:delexe
cls
del /f /q .\*.exe
echo Done.
pause
goto menu


:deleting
cls
del /f /q .\*.o
del /f /q .\*.lpi
del /f /q .\*.ico
del /f /q .\*.rc
del /f /q .\*.manifest
del /f /q .\*.compiled
del /f /q .\*.res
echo Done.
pause
goto menu
