@echo off
setlocal

:: Define paths
set QT_PATH=C:\Qt\6.8.3\msvc2022_64\bin
set BUILD_DIR=c:\Users\Luke\Documents\software\Bounce\build\Desktop_Qt_6_8_3_MSVC2022_64bit-Release
set TARGET_DIR=C:\Users\Luke\Documents\software\BounceRelease

:: Create target directory if it doesn’t exist
if not exist "%TARGET_DIR%" mkdir "%TARGET_DIR%"

:: Copy the executable to the target directory
echo Copying executable...
copy "%BUILD_DIR%\Bounce.exe" "%TARGET_DIR%\Bounce.exe"

:: Deploy the application
echo Deploying application...
"%QT_PATH%\windeployqt" --release --dir "%TARGET_DIR%" "%BUILD_DIR%\Bounce.exe"

echo Deployment complete. Files are in: "%TARGET_DIR%"
pause