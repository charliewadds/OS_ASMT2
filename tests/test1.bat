@echo off
setlocal enabledelayedexpansion

rem Get the directory of this script
set "DIR=%~dp0"

rem Call the testMain executable with the specified arguments
"%DIR%\..\cmake-build-debug\testMain.exe" "%DIR%\test_case_1.csv" "%DIR%\testOut1.csv"

endlocal
