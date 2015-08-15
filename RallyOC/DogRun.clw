; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRallyOCPrintDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DogRun.h"
LastPage=0

ClassCount=27
Class1=CDogRunApp
Class2=CDogRunDoc
Class3=CDogRunView
Class4=CMainFrame

ResourceCount=60
Resource1=IDR_RIGHT_TURNS_APDT
Resource2=IDR_MOVE
Resource3=IDR_HEEL
Class5=CChildFrame
Class6=CAboutDlg
Resource4=ID_POPUP_AR_MENU
Resource5=IDR_FINISH
Resource6=ID_POPUP_SCR_MENU
Class7=DocInfodlg
Resource7=IDR_NONSTATIONARY
Class8=CCourseInfoDlg
Resource8=IDD_STAT_MUL_PROP
Resource9=IDR_FINISH_X
Class9=RenumberDlg
Resource10=IDR_EXCELLENT
Resource11=IDR_ADD_APDT
Resource12=IDD_SELECT_FINISH
Resource13=IDR_ADVANCED_APDT
Resource14=IDR_PIVOT_TURNS_APDT
Resource15=IDR_STATIONARY
Resource16=IDR_LEFT_TURNS
Resource17=IDD_ABOUTBOX
Resource18=IDD_STAT_PROP
Resource19=ID_POPUP_TX_MENU
Class10=ErrorReportDlg
Resource20=IDD_STATION_LIST_PREF
Resource21=IDD_TEXT_PREF
Resource22=IDR_WEAVE_APDT
Resource23=IDR_CHANGE_PACE
Resource24=IDR_ADD_AKC
Resource25=IDR_DOGRUNTYPE
Class11=RegisterDlg
Resource26=ID_POPUP_ST_MENU
Class12=RallyListDlg
Resource27=IDD_STATION_DESC_PREF
Resource28=IDR_ADVANCED
Class13=CEditDlg
Resource29=IDD_SCORE_SHEET_PREF
Resource30=IDD_ARROW_PREF
Resource31=IDD_COURSE
Resource32=IDR_NOVICE
Resource33=IDD_RENUMBER
Resource34=IDD_DOCINFO
Class14=SelectFinishDlg
Resource35=IDD_MAIL_ADDRESS
Class15=AuthorDlg
Resource36=IDD_EDITTEXT
Resource37=PRINTDLGORD
Resource38=IDD_ERROR_REPORT
Resource39=IDR_PIVOT_TURNS
Resource40=IDR_FINISH_APDT
Resource41=IDR_EXCELLENT_APDT
Resource42=IDR_RIGHT_TURNS
Class16=StationPropDlg
Resource43=IDR_NOVICE_APDT
Class17=AuthorPref
Resource44=IDD_OBJECT_PROP
Resource45=IDR_MOVE_X
Resource46=IDR_HALT_FOR_AKC
Class18=StationPrefDlg
Resource47=IDR_LEFT_TURNS_APDT
Class19=TextPrefDlg
Resource48=IDD_REGISTER
Resource49=ID_POPUP_MENU
Resource50=IDR_MOVE_APDT
Resource51=IDD_COURSE_INFO_PREF
Resource52=IDR_RALLYO
Resource53=IDR_WEAVE
Class20=CCourseTextPrefDlg
Class21=StationListPrefdlg
Class22=StationDescDlg
Class23=ScoreSheetPrefDlg
Resource54=IDR_HALT_FOR_APDT
Resource55=IDR_PATTERN
Class24=ObjectPropDlg
Resource56=IDR_MAINFRAME
Class25=AddressDlg
Resource57=IDD_RALLY_LIST
Resource58=IDD_AUTOR_PREF
Class26=CMyPrintDialog
Class27=CRallyOCPrintDialog
Resource59=IDD_STATION_PREF
Resource60=IDD_PRINT

[CLS:CDogRunApp]
Type=0
HeaderFile=DogRun.h
ImplementationFile=DogRun.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CDogRunApp

[CLS:CDogRunDoc]
Type=0
HeaderFile=DogRunDoc.h
ImplementationFile=DogRunDoc.cpp
Filter=N
LastObject=CDogRunDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDogRunView]
Type=0
HeaderFile=DogRunView.h
ImplementationFile=DogRunView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CDogRunView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_JUMP_TOOL
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=ID_VIEW_RALLY_LIST
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=DogRun.cpp
ImplementationFile=DogRun.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308492
Control2=IDOK,button,1342373889
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342177283
Control5=IDC_REG_INFO,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_REG_DETAIL,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_CLEAR
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_REDO
Command10=ID_FILE_PRINT
Command11=ID_EDIT_TEXT
Command12=ID_ARROW_TOOL
Command13=ID_LINE_TOOL
Command14=ID_SCRIBBLE_TOOL
Command15=ID_JUMP_TOOL
Command16=ID_BR_JUMP_TOOL
Command17=ID_LEASH_TOOL
Command18=ID_GATE_TOOL
Command19=ID_TABLE_TOOL
Command20=ID_PYLONS
Command21=ID_BONE
Command22=ID_PATTERN
Command23=ID_APP_ABOUT
Command24=ID_CONTEXT_HELP
CommandCount=24

[MNU:IDR_DOGRUNTYPE]
Type=1
Class=CDogRunView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_SAVE_BITMAP
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_PRINT_BW
Command11=ID_PRINT_STATION_LIST
Command12=ID_PRINT_SCORE_SHEET
Command13=ID_PRINT_LIST_DESC
Command14=ID_FILE_SEND_MAIL
Command15=ID_DOC_INFO
Command16=ID_FILE_MRU_FILE1
Command17=ID_APP_EXIT
Command18=ID_EDIT_UNDO
Command19=ID_EDIT_REDO
Command20=ID_EDIT_CUT
Command21=ID_EDIT_COPY
Command22=ID_EDIT_PASTE
Command23=ID_EDIT_CLEAR
Command24=ID_STRAIGHT_LINE
Command25=ID_REVERSE_ARROW
Command26=ID_SELECT_ALL_STATIONS
Command27=ID_COPY_COURSE
Command28=ID_COPY_LIST
Command29=ID_COPY_SCORE_SHEET
Command30=ID_COPY_STATS
Command31=ID_COPY_DESC
Command32=ID_ZERO_DEGREES
Command33=ID_NINETY_CW
Command34=ID_NINETY_CCW
Command35=ID_ONEEIGHTY
Command36=ID_ALIGN_HORIZ
Command37=ID_ALIGN_VERT
Command38=ID_ST_PROP_DIALOG
Command39=ID_AR_PROP_DIALOG
Command40=ID_TEXT_PROP
Command41=ID_VIEW_TOOLBAR
Command42=IDR_RALLYO
Command43=ID_VIEW_STATUS_BAR
Command44=ID_VIEW_RALLY_LIST
Command45=ID_VIEW_COURSE_INFO
Command46=ID_RALLY_LIST
Command47=ID_SIZE_TO_SCREEN
Command48=ID_DRAW_START
Command49=ID_DRAW_FINISH
Command50=ID_DRAW_HONOR
Command51=ID_DRAW_SITHALT
Command52=ID_DRAW_SITHALTDOWN
Command53=ID_DRAW_HALTWALK
Command54=ID_DRAW_DOWNWALK
Command55=ID_DRAW_STANDWALK
Command56=ID_DRAW_DOWNSIT
Command57=ID_DRAW_STANDDOWN
Command58=ID_DRAW_STANDSIT
Command59=ID_DRAW_SLOW
Command60=ID_DRAW_NORMAL
Command61=ID_DRAW_FAST
Command62=ID_DRAW_FAST_SIT
Command63=ID_DRAW_RT_TURN
Command64=ID_DRAW_ABOUT_RT
Command65=ID_DRAW_270_RT
Command66=ID_DRAW_360_RT
Command67=ID_ABOUT_FORWARD_RT
Command68=ID_DRAW_90_PIVOT_RT
Command69=ID_DRAW_180_PIVOT_RT
Command70=ID_DRAW_1STEP_HEEL_RT
Command71=ID_DRAW_LT_TURN
Command72=ID_DRAW_ABOUT_LT
Command73=ID_DRAW_270_LT
Command74=ID_DRAW_360_LT
Command75=ID_DRAW_ABOUT_TURN_LT
Command76=ID_DRAW_U_FORWARD_LT
Command77=ID_DRAW_90_PIVOT_LT
Command78=ID_DRAW_180_PIVOT_LT
Command79=ID_DRAW_90_PIVOT_RT
Command80=ID_DRAW_180_PIVOT_RT
Command81=ID_DRAW_90_PIVOT_LT
Command82=ID_DRAW_180_PIVOT_LT
Command83=ID_DRAW_FINISH_RT_FORWARD
Command84=ID_DRAW_FINISH_LEFT_FORWARD
Command85=ID_DRAW_FINISH_RT_HALT
Command86=ID_DRAW_FINISH_LT_HALT
Command87=ID_DRAW_HALT_FINISH_RT
Command88=ID_DRAW_HALT_FINISH_LT
Command89=ID_DRAW_SIDE_RT
Command90=ID_DRAW_MOVE_DOWN
Command91=ID_DRAW_JUMP
Command92=ID_DRAW_MOVE_STAND_WALK
Command93=ID_DRAW_HALT_3_STEPS_FOR
Command94=ID_DRAW_FRONT_3_STEPS_BACK
Command95=ID_DRAW_SIDE_RIGHT
Command96=ID_DRAW_BACKUP_3
Command97=ID_DRAW_SPIRAL_RIGHT
Command98=ID_DRAW_SPIRAL_LEFT
Command99=ID_DRAW_WEAVE_TWICE
Command100=ID_DRAW_SERP_ONCE
Command101=ID_DRAW_OFFSET_8
Command102=ID_EDIT_TEXT
Command103=ID_ARROW_TOOL
Command104=ID_LINE_TOOL
Command105=ID_SCRIBBLE_TOOL
Command106=ID_JUMP_TOOL
Command107=ID_BR_JUMP_TOOL
Command108=ID_LEASH_TOOL
Command109=ID_GATE_TOOL
Command110=ID_TABLE_TOOL
Command111=ID_PYLONS
Command112=ID_BONE
Command113=ID_SPIRAL_RT_1A
Command114=ID_SPIRAL_RT_1B
Command115=ID_SPIRAL_LT
Command116=ID_FIG8_PATTERN
Command117=ID_SERP_PATTERN
Command118=ID_OFFSET_3A
Command119=IDD_COURSE_INFO
Command120=IDD_COURSE_VERIFY
Command121=IDD_AUTOR_PREF
Command122=ID_STATION_PREF
Command123=ID_ARROW_PREF
Command124=ID_TEXT_FONT
Command125=ID_STATION_LIST_PR
Command126=ID_SCORE_SHEET_PR
Command127=ID_STATION_DESC_PR
Command128=ID_WINDOW_NEW
Command129=ID_WINDOW_CASCADE
Command130=ID_WINDOW_TILE_HORZ
Command131=ID_WINDOW_ARRANGE
Command132=ID_HELP_FINDER
Command133=ID_REG_DIALOG
Command134=ID_APP_ABOUT
CommandCount=134

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=IDD_COURSE_INFO
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=IDD_COURSE_VERIFY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CLEAR
Command11=ID_EDIT_CUT
Command12=ID_ONEEIGHTY
Command13=ID_HELP
Command14=ID_CONTEXT_HELP
Command15=ID_VIEW_COURSE_INFO
Command16=ID_RALLY_LIST
Command17=ID_SIZE_TO_SCREEN
Command18=ID_ALIGN_VERT
Command19=ID_ALIGN_HORIZ
Command20=ID_EDIT_COPY
Command21=ID_EDIT_PASTE
Command22=ID_NINETY_CCW
Command23=ID_NINETY_CW
Command24=ID_ZERO_DEGREES
Command25=ID_EDIT_CUT
Command26=ID_EDIT_REDO
Command27=ID_EDIT_UNDO
CommandCount=27

[TB:IDR_RALLYO]
Type=1
Class=CDogRunView
Command1=ID_SELECTARROW
Command2=ID_DRAW_START
Command3=ID_DRAW_FINISH
Command4=ID_DRAW_HONOR
Command5=ID_FORWARD_HALT
Command6=ID_CHANGE_PACE
Command7=ID_RIGHT_TURNS
Command8=ID_LEFT_TURNS
Command9=ID_PIVOT
Command10=ID_FINISH
Command11=ID_MOVE
Command12=ID_HEEL
Command13=ID_WEAVE
Command14=ID_STATIONARY
Command15=ID_NONSTATIONARY
Command16=ID_NOVICE
Command17=ID_ADVANCED
Command18=ID_EXCELLENT
CommandCount=18

[DLG:IDD_DOCINFO]
Type=1
Class=DocInfodlg
ControlCount=12
Control1=IDC_AUTHOR,edit,1350631552
Control2=IDC_NOTES,edit,1350635524
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CREATED,static,1342308352
Control10=IDC_MODIFIED,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_PRINTED,static,1342308352

[CLS:DocInfodlg]
Type=0
HeaderFile=DocInfodlg.h
ImplementationFile=DocInfodlg.cpp
BaseClass=CDialog
Filter=D
LastObject=DocInfodlg
VirtualFilter=dWC

[DLG:IDD_COURSE]
Type=1
Class=CCourseInfoDlg
ControlCount=39
Control1=IDC_COMPETATION,edit,1350631552
Control2=IDC_TYPE_AKC,button,1342373897
Control3=IDC_TYPE_APDT,button,1073807369
Control4=IDC_NOVICE,button,1342308361
Control5=IDC_ADVANCED,button,1342177289
Control6=IDC_EXCELLENT,button,1342177289
Control7=IDC_TRAINING,button,1342177289
Control8=IDC_CLASS_A,button,1342373897
Control9=IDC_CLASS_B,button,1342242825
Control10=IDC_CLASS_NONE,button,1342242825
Control11=IDC_DATECOMPETE,SysDateTimePick32,1342242848
Control12=IDC_LOCATION,edit,1350631552
Control13=IDC_ORGANIZATION,edit,1350631552
Control14=IDC_JUDGE,edit,1350631552
Control15=IDC_RING_WIDTH,edit,1350639744
Control16=IDC_RING_LENGHT,edit,1350639744
Control17=IDC_GRID_SPACEING,edit,1350639744
Control18=IDC_COMP_NAME,button,1342242819
Control19=IDC_DATE,button,1342242819
Control20=IDC_CLASS,button,1342242819
Control21=IDC_SH_LOCATION,button,1342242819
Control22=IDC_SUBCLASS,button,1342242819
Control23=IDC_JUDGE_NAME,button,1342242819
Control24=ID_DEFAULT,button,1342242816
Control25=IDOK,button,1342242817
Control26=IDCANCEL,button,1342242816
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_JUDGE_INST,static,1342308354
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,button,1342177287
Control38=IDC_STATIC,static,1342308352
Control39=IDC_ORGANIZE,button,1342242819

[CLS:CCourseInfoDlg]
Type=0
HeaderFile=CourseInfoDlg.h
ImplementationFile=CourseInfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_DEFAULT
VirtualFilter=dWC

[DLG:IDD_RENUMBER]
Type=1
Class=RenumberDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_CURRENT,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BEFORE,button,1342308361
Control6=IDC_AFTER,button,1342177289
Control7=IDC_STATIONLIST,combobox,1342243074

[CLS:RenumberDlg]
Type=0
HeaderFile=RenumberDlg.h
ImplementationFile=RenumberDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_FORWARD_RT
VirtualFilter=dWC

[MNU:IDR_CHANGE_PACE]
Type=1
Class=?
CommandCount=0

[MNU:IDR_RIGHT_TURNS]
Type=1
Class=?
CommandCount=0

[MNU:IDR_LEFT_TURNS]
Type=1
Class=?
CommandCount=0

[MNU:IDR_FINISH]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MOVE]
Type=1
Class=?
CommandCount=0

[MNU:IDR_FINISH_X]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MOVE_X]
Type=1
Class=?
CommandCount=0

[MNU:IDR_HEEL]
Type=1
Class=?
CommandCount=0

[DLG:IDD_ERROR_REPORT]
Type=1
Class=ErrorReportDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDPRINT,button,1342242816
Control3=IDC_ERROR_REPORT,edit,1353777284

[CLS:ErrorReportDlg]
Type=0
HeaderFile=ErrorReportDlg.h
ImplementationFile=ErrorReportDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ErrorReportDlg

[MNU:IDR_STATIONARY]
Type=1
Class=?
CommandCount=0

[MNU:IDR_NONSTATIONARY]
Type=1
Class=?
CommandCount=0

[MNU:IDR_NOVICE]
Type=1
Class=?
CommandCount=0

[MNU:IDR_ADVANCED]
Type=1
Class=?
CommandCount=0

[MNU:IDR_EXCELLENT]
Type=1
Class=?
CommandCount=0

[DLG:IDD_REGISTER]
Type=1
Class=RegisterDlg
ControlCount=12
Control1=IDC_REG_USER,edit,1350631552
Control2=IDC_ACT_KEY,edit,1082196096
Control3=IDOK,button,1342177281
Control4=IDC_DEMOMSG,static,1342308352
Control5=IDC_PRODID_ST,static,1073872896
Control6=IDC_ACTKEY_ST,static,1073872896
Control7=IDC_REQ_KEY,edit,1082198144
Control8=IDCANCEL,button,1342177281
Control9=IDPURCHASE,button,1342177281
Control10=IDC_CONTACT,button,1073741824
Control11=IDC_STATIC,static,1342308352
Control12=IDC_GEN_PROD_ID,button,1342242816

[CLS:RegisterDlg]
Type=0
HeaderFile=RegisterDlg.h
ImplementationFile=RegisterDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_REQ_KEY
VirtualFilter=dWC

[DLG:IDD_RALLY_LIST]
Type=1
Class=RallyListDlg
ControlCount=3
Control1=IDC_LIST1,SysListView32,1350631937
Control2=IDOK,button,1073741824
Control3=IDCANCEL,button,1073741824

[CLS:RallyListDlg]
Type=0
HeaderFile=RallyListDlg.h
ImplementationFile=RallyListDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=RallyListDlg
VirtualFilter=dWC

[MNU:IDR_PIVOT_TURNS]
Type=1
Class=?
CommandCount=0

[DLG:IDD_EDITTEXT]
Type=1
Class=CEditDlg
ControlCount=1
Control1=IDC_EDIT_TEXT,edit,1342246916

[CLS:CEditDlg]
Type=0
HeaderFile=EditDlg.h
ImplementationFile=EditDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEditDlg
VirtualFilter=dWC

[MNU:IDR_HALT_FOR_AKC]
Type=1
Class=CDogRunView
CommandCount=0

[MNU:IDR_HALT_FOR_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_RIGHT_TURNS_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_LEFT_TURNS_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_FINISH_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MOVE_APDT]
Type=1
Class=?
CommandCount=0

[DLG:IDD_SELECT_FINISH]
Type=1
Class=SelectFinishDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:SelectFinishDlg]
Type=0
HeaderFile=SelectFinishDlg.h
ImplementationFile=SelectFinishDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_FORWARD_RT

[DLG:IDD_AUTOR_PREF]
Type=1
Class=AuthorDlg
ControlCount=46
Control1=IDC_TYPE_AKC,button,1342373897
Control2=IDC_TYPE_APDT,button,1073807369
Control3=IDC_NOVICE,button,1342373897
Control4=IDC_ADVANCED,button,1342242825
Control5=IDC_EXCELLENT,button,1342242825
Control6=IDC_TRAINING,button,1342242825
Control7=IDC_CLASS_A,button,1342373897
Control8=IDC_CLASS_B,button,1342242825
Control9=IDC_CLASS_NONE,button,1342242825
Control10=IDC_JUDGE,edit,1350631552
Control11=IDC_ORGANIZATION,edit,1350631552
Control12=IDC_RING_WIDTH,edit,1350639744
Control13=IDC_RING_LENGHT,edit,1350639744
Control14=IDC_GRID_SPACEING,edit,1350639744
Control15=IDC_LINES_BLACK,button,1342373897
Control16=IDC_LINES_GREY,button,1342242825
Control17=IDC_LINES_NONE,button,1342242825
Control18=IDC_LIST_BOTTOM,button,1342373897
Control19=IDC_LIST_RIGHT,button,1342242825
Control20=IDC_LIST_CUSTOM,button,1342242825
Control21=IDC_COURSE_PATH,button,1342242819
Control22=IDC_AUTO_ADD,button,1342242819
Control23=IDC_SIZE_TO_SCREEN,button,1342242819
Control24=IDC_COMP_NAME,button,1342242819
Control25=IDC_DATE,button,1342242819
Control26=IDC_CLASS,button,1342242819
Control27=IDC_SH_LOCATION,button,1342242819
Control28=IDC_SUBCLASS,button,1342242819
Control29=IDC_JUDGE_NAME,button,1342242819
Control30=IDC_CHANGE_FONT,button,1342242816
Control31=ID_DEFAULT,button,1342242816
Control32=IDOK,button,1342242817
Control33=IDCANCEL,button,1342242816
Control34=IDC_STATIC,static,1342308352
Control35=IDC_JUDGE_INST,static,1342308354
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,button,1342177287
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,button,1342177287
Control43=IDC_COURSE_FONT,static,1073741824
Control44=IDC_STATIC,button,1342177287
Control45=IDC_STATIC,static,1342308352
Control46=IDC_ORGANIZE,button,1342242819

[CLS:AuthorDlg]
Type=0
HeaderFile=AuthorDlg.h
ImplementationFile=AuthorDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ORGANIZE
VirtualFilter=dWC

[MNU:IDR_PIVOT_TURNS_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_WEAVE_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_WEAVE]
Type=1
Class=?
CommandCount=0

[MNU:IDR_NOVICE_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_ADVANCED_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_EXCELLENT_APDT]
Type=1
Class=?
CommandCount=0

[MNU:IDR_ADD_AKC]
Type=1
Class=?
Command1=ID_DRAW_START
Command2=ID_DRAW_FINISH
Command3=ID_DRAW_HONOR
Command4=ID_DRAW_SITHALT
Command5=ID_DRAW_SITHALTDOWN
Command6=ID_DRAW_HALTWALK
Command7=ID_DRAW_DOWNWALK
Command8=ID_DRAW_STANDWALK
Command9=ID_DRAW_DOWNSIT
Command10=ID_DRAW_STANDDOWN
Command11=ID_DRAW_STANDSIT
Command12=ID_DRAW_SLOW
Command13=ID_DRAW_NORMAL
Command14=ID_DRAW_FAST
Command15=ID_DRAW_FAST_SIT
Command16=ID_DRAW_RT_TURN
Command17=ID_DRAW_ABOUT_RT
Command18=ID_DRAW_270_RT
Command19=ID_DRAW_360_RT
Command20=ID_ABOUT_FORWARD_RT
Command21=ID_DRAW_90_PIVOT_RT
Command22=ID_DRAW_180_PIVOT_RT
Command23=ID_DRAW_1STEP_HEEL_RT
Command24=ID_DRAW_LT_TURN
Command25=ID_DRAW_ABOUT_LT
Command26=ID_DRAW_270_LT
Command27=ID_DRAW_360_LT
Command28=ID_DRAW_ABOUT_TURN_LT
Command29=ID_DRAW_U_FORWARD_LT
Command30=ID_DRAW_90_PIVOT_LT
Command31=ID_DRAW_180_PIVOT_LT
Command32=ID_DRAW_90_PIVOT_RT
Command33=ID_DRAW_180_PIVOT_RT
Command34=ID_DRAW_90_PIVOT_LT
Command35=ID_DRAW_180_PIVOT_LT
Command36=ID_DRAW_FINISH_RT_FORWARD
Command37=ID_DRAW_FINISH_LEFT_FORWARD
Command38=ID_DRAW_FINISH_RT_HALT
Command39=ID_DRAW_FINISH_LT_HALT
Command40=ID_DRAW_HALT_FINISH_RT
Command41=ID_DRAW_HALT_FINISH_LT
Command42=ID_DRAW_SIDE_RT
Command43=ID_DRAW_MOVE_DOWN
Command44=ID_DRAW_JUMP
Command45=ID_DRAW_MOVE_STAND_WALK
Command46=ID_DRAW_HALT_3_STEPS_FOR
Command47=ID_DRAW_FRONT_3_STEPS_BACK
Command48=ID_DRAW_SIDE_RIGHT
Command49=ID_DRAW_BACKUP_3
Command50=ID_DRAW_SPIRAL_RIGHT
Command51=ID_DRAW_SPIRAL_LEFT
Command52=ID_DRAW_WEAVE_TWICE
Command53=ID_DRAW_SERP_ONCE
Command54=ID_DRAW_OFFSET_8
CommandCount=54

[MNU:IDR_ADD_APDT]
Type=1
Class=?
Command1=ID_DRAW_START
Command2=ID_DRAW_FINISH
Command3=ID_DRAW_SITHALT
Command4=ID_DRAW_SIT_STAND
Command5=ID_DRAW_SITHALTDOWN
Command6=ID_DRAW_DOWNSIT
Command7=ID_DRAW_HALTWALK
Command8=ID_DRAW_DOWNWALK
Command9=ID_DRAW_STANDWALK
Command10=ID_RETURN_STAND
Command11=ID_RECALL_LEAVE
Command12=ID_JUMP_RECALL
Command13=ID_JUMP_LEAVE
Command14=ID_DOWN_RECALL
Command15=ID_RETRIEVE_FINISH
Command16=ID_DRAW_SLOW
Command17=ID_DRAW_NORMAL
Command18=ID_DRAW_FAST
Command19=ID_DRAW_FAST_SIT
Command20=ID_DRAW_RT_TURN
Command21=ID_DRAW_ABOUT_RT
Command22=ID_DRAW_270_RT
Command23=ID_DRAW_360_RT
Command24=ID_DRAW_90_PIVOT_RT
Command25=ID_DRAW_1STEP_HEEL_RT
Command26=ID_DRAW_180_PIVOT_RT
Command27=ID_ABOUT_FORWARD_RT
Command28=ID_DRAW_RT_DOWN
Command29=ID_DRAW_LT_TURN
Command30=ID_DRAW_ABOUT_LT
Command31=ID_DRAW_270_LT
Command32=ID_DRAW_360_LT
Command33=ID_DRAW_90_PIVOT_LT
Command34=ID_DRAW_180_PIVOT_LT
Command35=ID_DRAW_U_FORWARD_LT
Command36=ID_DRAW_ABOUT_TURN_LT
Command37=ID_DRAW_LT_DOWN
Command38=ID_DRAW_90_PIVOT_RT
Command39=ID_DRAW_90_PIVOT_LT
Command40=ID_DRAW_180_PIVOT_RT
Command41=ID_DRAW_180_PIVOT_LT
Command42=ID_DRAW_FINISH_RT_FORWARD
Command43=ID_DRAW_FINISH_LEFT_FORWARD
Command44=ID_DRAW_HALT_FINISH_RT
Command45=ID_DRAW_HALT_FINISH_LT
Command46=ID_TURN_FRONT
Command47=ID_FINISH_RIGHT
Command48=ID_FINISH_LEFT
Command49=ID_FRONT_RUN
Command50=ID_DRAW_SIDE_RT
Command51=ID_DRAW_JUMP
Command52=ID_DRAW_MOVE_DOWN
Command53=ID_DRAW_MOVE_STAND_WALK
Command54=ID_MOVE_STAND_LEAVE
Command55=ID_MOVE_STAND_SIT_FINISH
Command56=ID_JUMP_RECALL
Command57=ID_JUMP_LEAVE
Command58=ID_DRAW_HALT_3_STEPS_FOR
Command59=ID_DRAW_FRONT_3_STEPS_BACK
Command60=ID_DRAW_SIDE_RIGHT
Command61=ID_DRAW_BACKUP_3
Command62=ID_DRAW_SPIRAL_RIGHT
Command63=ID_DRAW_SPIRAL_LEFT
Command64=ID_DRAW_WEAVE_TWICE
Command65=ID_DRAW_OFFSET_8
Command66=ID_DRAW_SERP_ONCE
CommandCount=66

[DLG:IDD_STAT_PROP]
Type=1
Class=StationPropDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_TX_STAT_NO,static,1342308352
Control4=IDC_TX_STAT_NAME,static,1342308352
Control5=IDC_TX_AKC_NO,static,1342308352
Control6=IDC_STAT_NAME,combobox,1344339971
Control7=IDC_A_NUMBER,combobox,1344339971
Control8=IDC_STAT_NO,edit,1350631552
Control9=IDC_STAT_BOTH,button,1342308361
Control10=IDC_STAT_PIC,button,1342177289
Control11=IDC_STAT_TEXT,button,1342177289
Control12=IDC_STATIC,button,1342177287
Control13=IDC_SIZE_2,button,1342308361
Control14=IDC_SIZE_5,button,1342177289
Control15=IDC_SIZE_7,button,1342177289
Control16=IDC_SIZE_CUSTOM,button,1342177289
Control17=IDC_CUSTOM_SIZE,edit,1350639744
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATION_DEG_ST,static,1342308352
Control20=IDC_STATION_DEG,edit,1350639744

[CLS:StationPropDlg]
Type=0
HeaderFile=StationPropDlg.h
ImplementationFile=StationPropDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_STATION_DEG
VirtualFilter=dWC

[DLG:IDD_ARROW_PREF]
Type=1
Class=AuthorPref
ControlCount=12
Control1=IDC_LINE_THICK,edit,1350770816
Control2=IDC_LINE_ST,button,1342308361
Control3=IDC_LINE_CURVE,button,1342177289
Control4=IDC_MOVE_ARROWS,button,1342242819
Control5=IDC_SET_COLOR,button,1342373888
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=ID_DEFAULT,button,1342242816
Control9=IDC_STATIC_TYPE,button,1342177287
Control10=IDC_STATIC,static,1342177280
Control11=IDC_SHOW_COLOR,static,1073741831
Control12=IDC_LINE_STYLE,combobox,1342242819

[CLS:AuthorPref]
Type=0
HeaderFile=AuthorPref.h
ImplementationFile=AuthorPref.cpp
BaseClass=CDialog
Filter=D
LastObject=AuthorPref
VirtualFilter=dWC

[MNU:ID_POPUP_ST_MENU]
Type=1
Class=CDogRunView
CommandCount=0

[MNU:ID_POPUP_MENU]
Type=1
Class=?
CommandCount=0

[MNU:ID_POPUP_AR_MENU]
Type=1
Class=CDogRunView
CommandCount=0

[DLG:IDD_STATION_PREF]
Type=1
Class=StationPrefDlg
ControlCount=30
Control1=IDC_STAT_BOTH,button,1342308361
Control2=IDC_STAT_PIC,button,1342177289
Control3=IDC_STAT_TEXT,button,1342177289
Control4=IDC_SIZE_2,button,1342308361
Control5=IDC_SIZE_5,button,1342177289
Control6=IDC_SIZE_7,button,1342177289
Control7=IDC_SIZE_CUSTOM,button,1342177289
Control8=IDC_CUSTOM_SIZE,edit,1350639744
Control9=IDC_TOP_LEFT,button,1342373897
Control10=IDC_EXIT,button,1342242825
Control11=IDC_TOP_RIGHT,button,1342242825
Control12=IDC_BOT_LEFT,button,1342242825
Control13=IDC_ENTER,button,1342242825
Control14=IDC_BOT_RIGHT,button,1342242825
Control15=IDC_HIDE_ST_NUM,button,1342242825
Control16=IDC_CONE_ENTRANCE,button,1342373897
Control17=IDC_CONE_EXIT,button,1342242825
Control18=IDC_CONE_MIDDLE,button,1342242825
Control19=IDC_CONE_HIDE,button,1342242825
Control20=IDC_CHANGE_FONT,button,1342242816
Control21=IDOK,button,1342242817
Control22=ID_DEFAULT,button,1342242816
Control23=IDCANCEL,button,1342242816
Control24=IDC_ROTATE_TEXT,button,1342242819
Control25=IDC_NUM_HONOR,button,1342242819
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATION_FONT,static,1073741824
Control30=IDC_STATIC,button,1342177287

[CLS:StationPrefDlg]
Type=0
HeaderFile=StationPrefDlg.h
ImplementationFile=StationPrefDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=StationPrefDlg

[DLG:IDD_TEXT_PREF]
Type=1
Class=TextPrefDlg
ControlCount=8
Control1=IDC_SET_COLOR,button,1342242816
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_SHOW_COLOR,static,1073741831
Control5=ID_DEFAULT,button,1342242816
Control6=IDC_OUT_RECT,button,1342242819
Control7=IDC_TEXT_FONT,static,1073741824
Control8=IDC_CHANGE_FONT,button,1342242816

[CLS:TextPrefDlg]
Type=0
HeaderFile=TextPrefDlg.h
ImplementationFile=TextPrefDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_FORWARD_RT
VirtualFilter=dWC

[MNU:ID_POPUP_TX_MENU]
Type=1
Class=?
CommandCount=0

[MNU:IDR_PATTERN]
Type=1
Class=?
CommandCount=0

[DLG:IDD_COURSE_INFO_PREF]
Type=1
Class=CCourseTextPrefDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_DEFAULT,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_COMP_NAME,button,1342242819
Control6=IDC_CLASS,button,1342242819
Control7=IDC_SUBCLASS,button,1342242819
Control8=IDC_DATE,button,1342242819
Control9=IDC_LOCATION,button,1342242819
Control10=IDC_JUDGE_NAME,button,1342242819
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STAT_NUMBER,button,1342242819
Control13=IDC_STAT_NAME,button,1342242819
Control14=IDC_AKC_NUMBER,button,1342242819
Control15=IDC_XY_LOCATION,button,1342242819

[DLG:IDD_STATION_LIST_PREF]
Type=1
Class=StationListPrefdlg
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_DEFAULT,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_COMP_NAME,button,1342242819
Control6=IDC_CLASS,button,1342242819
Control7=IDC_SUBCLASS,button,1342242819
Control8=IDC_DATE,button,1342242819
Control9=IDC_LOCATION,button,1342242819
Control10=IDC_JUDGE_NAME,button,1342242819
Control11=IDC_STAT_NUMBER,button,1342242819
Control12=IDC_STAT_NAME,button,1342242819
Control13=IDC_AKC_NUMBER,button,1342242819
Control14=IDC_XY_LOCATION,button,1342242819
Control15=IDC_COURSE_INFO_LIST,button,1342242819
Control16=IDC_STATS,button,1342242819
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STAT_NUMBER_CM,button,1342242819
Control19=IDC_STAT_NAME_CM,button,1342242819
Control20=IDC_AKC_NUMBER_CM,button,1342242819
Control21=IDC_XY_LOCATION_CM,button,1342242819
Control22=IDC_ORGANIZE,button,1342242819

[DLG:IDD_SCORE_SHEET_PREF]
Type=1
Class=ScoreSheetPrefDlg
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_DEFAULT,button,1342242816
Control4=65535,button,1342177287
Control5=IDC_COMP_NAME,button,1342242819
Control6=IDC_CLASS,button,1342242819
Control7=IDC_SUBCLASS,button,1342242819
Control8=IDC_DATE,button,1342242819
Control9=IDC_LOCATION,button,1342242819
Control10=IDC_JUDGE_NAME,button,1342242819
Control11=IDC_STAT_NUMBER,button,1342242819
Control12=IDC_STAT_NAME,button,1342242819
Control13=IDC_AKC_NUMBER,button,1342242819
Control14=IDC_XY_LOCATION,button,1073807363
Control15=IDC_COURSE_INFO_LIST,button,1342242819
Control16=IDC_ARM_BAND,button,1342242819
Control17=IDC_BREED,button,1342242819
Control18=IDC_JUMP_HT,button,1342242819
Control19=IDC_FINAL_SCORE,button,1342242819
Control20=IDC_TIME,button,1342242819
Control21=IDC_JUDGE_SIGN,button,1342242819
Control22=IDC_ORGANIZE,button,1342242819

[DLG:IDD_STATION_DESC_PREF]
Type=1
Class=StationDescDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_DEFAULT,button,1342242816
Control4=65535,button,1342177287
Control5=IDC_COMP_NAME,button,1342242819
Control6=IDC_CLASS,button,1342242819
Control7=IDC_SUBCLASS,button,1342242819
Control8=IDC_DATE,button,1342242819
Control9=IDC_LOCATION,button,1342242819
Control10=IDC_JUDGE_NAME,button,1342242819
Control11=IDC_STAT_NUMBER,button,1342242819
Control12=IDC_STAT_NAME,button,1342242819
Control13=IDC_AKC_NUMBER,button,1342242819
Control14=IDC_XY_LOCATION,button,1342242819
Control15=IDC_COURSE_INFO_LIST,button,1342242819
Control16=IDC_ORGANIZE,button,1342242819

[CLS:CCourseTextPrefDlg]
Type=0
HeaderFile=CourseTextPrefDlg.h
ImplementationFile=CourseTextPrefDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCourseTextPrefDlg

[CLS:StationListPrefdlg]
Type=0
HeaderFile=StationListPrefdlg.h
ImplementationFile=StationListPrefdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_FORWARD_RT
VirtualFilter=dWC

[CLS:StationDescDlg]
Type=0
HeaderFile=StationDescDlg.h
ImplementationFile=StationDescDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COURSE_INFO_LIST

[CLS:ScoreSheetPrefDlg]
Type=0
HeaderFile=ScoreSheetPrefDlg.h
ImplementationFile=ScoreSheetPrefDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[DLG:IDD_STAT_MUL_PROP]
Type=1
Class=?
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STAT_NAME,combobox,1344339971
Control7=IDC_A_NUMBER,combobox,1344339971
Control8=IDC_STAT_NO,edit,1350631552
Control9=IDC_STAT_BOTH,button,1342308361
Control10=IDC_STAT_PIC,button,1342177289
Control11=IDC_STAT_TEXT,button,1342177289
Control12=IDC_STATIC,button,1342177287
Control13=IDC_SIZE_2,button,1342308361
Control14=IDC_SIZE_5,button,1342177289
Control15=IDC_SIZE_7,button,1342177289
Control16=IDC_SIZE_CUSTOM,button,1342177289
Control17=IDC_CUSTOM_SIZE,edit,1350639744
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATION_DEG,edit,1350639744

[DLG:IDD_OBJECT_PROP]
Type=1
Class=ObjectPropDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SIZE_2,button,1342308361
Control4=IDC_SIZE_5,button,1342177289
Control5=IDC_SIZE_7,button,1342177289
Control6=IDC_SIZE_CUSTOM,button,1342177289
Control7=IDC_CUSTOM_SIZE,edit,1350639744
Control8=65535,button,1342177287
Control9=65535,static,1342308352
Control10=IDC_STATION_DEG,edit,1350639744

[CLS:ObjectPropDlg]
Type=0
HeaderFile=ObjectPropDlg.h
ImplementationFile=ObjectPropDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ObjectPropDlg

[DLG:IDD_MAIL_ADDRESS]
Type=1
Class=AddressDlg
ControlCount=18
Control1=IDC_NAME,edit,1350631552
Control2=IDC_STREET,edit,1350631552
Control3=IDC_SUITE_NO,edit,1350631552
Control4=IDC_CITY,edit,1350631552
Control5=IDC_STATE,edit,1350631552
Control6=IDC_ZIP_CODE,edit,1350631552
Control7=IDC_PHONE_NO,edit,1350631552
Control8=IDC_EMAIL_ADD,edit,1350631552
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352

[CLS:AddressDlg]
Type=0
HeaderFile=AddressDlg.h
ImplementationFile=AddressDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AddressDlg

[MNU:ID_POPUP_SCR_MENU]
Type=1
Class=?
CommandCount=0

[CLS:CMyPrintDialog]
Type=0
HeaderFile=MyPrintDialog.h
ImplementationFile=MyPrintDialog.cpp
BaseClass=CPrintDialog
Filter=D
LastObject=1024
VirtualFilter=dWC

[DLG:PRINTDLGORD]
Type=1
Class=CRallyOCPrintDialog
ControlCount=21
Control1=1093,static,1342308352
Control2=1088,static,1342308352
Control3=1072,button,1342177287
Control4=1056,button,1342373892
Control5=1057,button,1342177284
Control6=1058,button,1342177284
Control7=1089,static,1342308354
Control8=1152,edit,1350631426
Control9=1090,static,1342308354
Control10=1153,edit,1350631426
Control11=1091,static,1342308352
Control12=1136,combobox,1352859651
Control13=1092,static,1342308352
Control14=1154,edit,1350631426
Control15=1040,button,1342373891
Control16=1041,button,1342373891
Control17=IDOK,button,1342373889
Control18=IDCANCEL,button,1342373888
Control19=1024,button,1342373888
Control20=1038,button,1342373888
Control21=IDC_LEFT_MARGIN,button,1342242819

[CLS:CRallyOCPrintDialog]
Type=0
HeaderFile=RallyOCPrintDialog.h
ImplementationFile=RallyOCPrintDialog.cpp
BaseClass=CPrintDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LEFT_MARGIN

[DLG:IDD_PRINT]
Type=1
Class=?
ControlCount=28
Control1=1075,button,1342308359
Control2=1093,static,1342308352
Control3=1139,combobox,1344471299
Control4=1025,button,1342373888
Control5=1095,static,1342308480
Control6=1099,static,1342308492
Control7=1094,static,1342308480
Control8=1098,static,1342308492
Control9=1097,static,1342308480
Control10=1101,static,1342308492
Control11=1096,static,1342308480
Control12=1100,static,1342308492
Control13=1040,button,1342373891
Control14=1072,button,1342308359
Control15=1056,button,1342373897
Control16=1058,button,1342177289
Control17=1057,button,1342177289
Control18=1089,static,1342308354
Control19=1152,edit,1350770688
Control20=1090,static,1342308354
Control21=1153,edit,1350770688
Control22=1073,button,1342308359
Control23=1092,static,1342308352
Control24=1154,edit,1350770688
Control25=1041,button,1342373891
Control26=IDOK,button,1342373889
Control27=IDCANCEL,button,1342242816
Control28=IDC_LEFT_MARGIN,button,1342242819
