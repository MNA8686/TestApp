@echo off
:開発者コマンド プロンプト for VS2019 のパスを設定
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
:MSBuild.exeのパスを設定
set PATH=%PATH%;C:\Windows\Microsoft.NET\Framework\v4.0.30319\
set VCTargetsPath=C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Microsoft\VC\v160\
set DEPLOYDIR=deploy\
set time2=%time: =0%
set APP_NAME=TestApp_%date:~0,4%-%date:~5,2%-%date:~8,2%_%time2:~0,2%-%time2:~3,2%-%time2:~6,2%

echo ==============================
echo =       TestApp Release      =
echo ==============================
MSBuild.exe TestApp.sln /t:Build /p:Configuration=Release;Platform="x86"
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

rd /s /q %DEPLOYDIR%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

md %DEPLOYDIR%
md %DEPLOYDIR%%APP_NAME%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

xcopy resources\* %DEPLOYDIR%%APP_NAME% /S/E/i
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

copy test\system.eq2 %DEPLOYDIR%%APP_NAME%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

copy test\*.dll %DEPLOYDIR%%APP_NAME%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

copy doc\* %DEPLOYDIR%%APP_NAME%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

copy test\TestApp.exe %DEPLOYDIR%%APP_NAME%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

echo %date% %time% > %DEPLOYDIR%%APP_NAME%\build.log

cd %DEPLOYDIR%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

"C:\Program Files\7-Zip\7z.exe" a %APP_NAME%.zip %APP_NAME%
if not %errorlevel% == 0 (
echo errorlevel %errorlevel%
exit /b %errorlevel%
)

cd ..

exit /b
