@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DOGRUN.HPJ. >"hlp\DogRun.hm"
echo. >>"hlp\DogRun.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\DogRun.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\DogRun.hm"
echo. >>"hlp\DogRun.hm"
echo // Prompts (IDP_*) >>"hlp\DogRun.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\DogRun.hm"
echo. >>"hlp\DogRun.hm"
echo // Resources (IDR_*) >>"hlp\DogRun.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\DogRun.hm"
echo. >>"hlp\DogRun.hm"
echo // Dialogs (IDD_*) >>"hlp\DogRun.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\DogRun.hm"
echo. >>"hlp\DogRun.hm"
echo // Frame Controls (IDW_*) >>"hlp\DogRun.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\DogRun.hm"
REM -- Make help for Project DOGRUN


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\DogRun.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\DogRun.hlp" goto :Error
if not exist "hlp\DogRun.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\DogRun.hlp" Debug
if exist Debug\nul copy "hlp\DogRun.cnt" Debug
if exist Release\nul copy "hlp\DogRun.hlp" Release
if exist Release\nul copy "hlp\DogRun.cnt" Release
echo.
goto :done

:Error
echo hlp\DogRun.hpj(1) : error: Problem encountered creating help file

:done
echo.
