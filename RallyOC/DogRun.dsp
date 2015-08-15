# Microsoft Developer Studio Project File - Name="DogRun" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DogRun - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DogRun.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DogRun.mak" CFG="DogRun - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DogRun - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DogRun - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DogRun - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"Release/RallyOC.pch" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/RallyOC.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "DogRun - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"Debug/RallyOC.pch" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/RallyOC.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "DogRun - Win32 Release"
# Name "DogRun - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrowObj.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrowObjList.cpp
# End Source File
# Begin Source File

SOURCE=.\AuthorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AuthorPref.cpp
# End Source File
# Begin Source File

SOURCE=.\CGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CourseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CourseInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CourseTextPrefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DocInfodlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DogRun.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\DogRun.hpj

!IF  "$(CFG)" == "DogRun - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__DOGRU="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=RallyOC
InputPath=.\hlp\DogRun.hpj
InputName=DogRun

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DogRun - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__DOGRU="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=RallyOC
InputPath=.\hlp\DogRun.hpj
InputName=DogRun

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DogRun.rc
# End Source File
# Begin Source File

SOURCE=.\DogRunDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DogRunView.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EnBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorReportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageProcessors.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFont.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PylonObj.cpp
# End Source File
# Begin Source File

SOURCE=.\RallyListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RallyListView.cpp
# End Source File
# Begin Source File

SOURCE=.\RallyObject.cpp
# End Source File
# Begin Source File

SOURCE=.\RallyObjList.cpp
# End Source File
# Begin Source File

SOURCE=.\RallyOCPrintDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RallyTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RenumberDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreSheetPrefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Scribble.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectFinishDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialObj.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StationDescDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StationList.cpp
# End Source File
# Begin Source File

SOURCE=.\StationListPrefdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StationPrefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StationPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextObj.cpp
# End Source File
# Begin Source File

SOURCE=.\TextPrefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Verify.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddressDlg.h
# End Source File
# Begin Source File

SOURCE=.\ArrowObj.h
# End Source File
# Begin Source File

SOURCE=.\ArrowObjList.h
# End Source File
# Begin Source File

SOURCE=.\AuthorDlg.h
# End Source File
# Begin Source File

SOURCE=.\AuthorPref.h
# End Source File
# Begin Source File

SOURCE=.\CGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CourseInfo.h
# End Source File
# Begin Source File

SOURCE=.\CourseInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\CourseTextPrefDlg.h
# End Source File
# Begin Source File

SOURCE=.\DocInfodlg.h
# End Source File
# Begin Source File

SOURCE=.\DogRun.h
# End Source File
# Begin Source File

SOURCE=.\DogRunDoc.h
# End Source File
# Begin Source File

SOURCE=.\DogRunView.h
# End Source File
# Begin Source File

SOURCE=.\EditDlg.h
# End Source File
# Begin Source File

SOURCE=.\EnBitmap.h
# End Source File
# Begin Source File

SOURCE=.\ErrorReportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageProcessors.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\MyFont.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\PylonObj.h
# End Source File
# Begin Source File

SOURCE=.\RallyListDlg.h
# End Source File
# Begin Source File

SOURCE=.\RallyListView.h
# End Source File
# Begin Source File

SOURCE=.\RallyObject.h
# End Source File
# Begin Source File

SOURCE=.\RallyObjList.h
# End Source File
# Begin Source File

SOURCE=.\RallyOCPrintDialog.h
# End Source File
# Begin Source File

SOURCE=.\RallyTracker.h
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.h
# End Source File
# Begin Source File

SOURCE=.\RenumberDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "DogRun - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=RallyOC
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DogRun - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=RallyOC
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScoreSheetPrefDlg.h
# End Source File
# Begin Source File

SOURCE=.\Scribble.h
# End Source File
# Begin Source File

SOURCE=.\SelectFinishDlg.h
# End Source File
# Begin Source File

SOURCE=.\SpecialObj.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StationDescDlg.h
# End Source File
# Begin Source File

SOURCE=.\StationList.h
# End Source File
# Begin Source File

SOURCE=.\StationListPrefdlg.h
# End Source File
# Begin Source File

SOURCE=.\StationPrefDlg.h
# End Source File
# Begin Source File

SOURCE=.\StationPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextObj.h
# End Source File
# Begin Source File

SOURCE=.\TextPrefDlg.h
# End Source File
# Begin Source File

SOURCE=.\url.h
# End Source File
# Begin Source File

SOURCE=.\Verify.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\about_fo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\about_tu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\back1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00023.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00024.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00025.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00026.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00027.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00028.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00029.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00030.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00031.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00032.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00033.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00034.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00035.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00036.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00037.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00038.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00039.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00040.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00041.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00042.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00043.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp180_p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp270_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp360_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp90_pi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\DogRun.ico
# End Source File
# Begin Source File

SOURCE=.\res\DogRun.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DogRunDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\exit_bot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fig8_onc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\finish1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\finish_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\front_3_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\front_ri.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gate_too.bmp
# End Source File
# Begin Source File

SOURCE=.\res\H_POINT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\halt_3_f.bmp
# End Source File
# Begin Source File

SOURCE=.\res\haltforw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hnesw.cur
# End Source File
# Begin Source File

SOURCE=.\res\hnwse.cur
# End Source File
# Begin Source File

SOURCE=.\res\idb_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_lea.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_rec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_too.bmp
# End Source File
# Begin Source File

SOURCE=.\res\leave_do.bmp
# End Source File
# Begin Source File

SOURCE=.\res\move1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\offset_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pan_Grab.cur
# End Source File
# Begin Source File

SOURCE=.\res\Pan_Open.cur
# End Source File
# Begin Source File

SOURCE=.\res\pylons1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pylons_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rallyo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\retrieve.bmp
# End Source File
# Begin Source File

SOURCE=.\res\right_tu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rotate1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\select_e.cur
# End Source File
# Begin Source File

SOURCE=.\res\select_r.cur
# End Source File
# Begin Source File

SOURCE=.\res\serp_pat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\side_rt1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spiral_l.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spiral_p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spiral_r.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stophalt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\turn_fro.bmp
# End Source File
# Begin Source File

SOURCE=.\res\u_turn1.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\DogRun.cnt

!IF  "$(CFG)" == "DogRun - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\DogRun.cnt
InputName=DogRun

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "DogRun - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\DogRun.cnt
InputName=DogRun

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
