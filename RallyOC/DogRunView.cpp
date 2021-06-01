// DogRunView.cpp : implementation of the CDogRunView class
//

#include "stdafx.h"
#include "DogRun.h"

#include "DogRunDoc.h"
#include "DogRunView.h"
#include "DocInfodlg.h"
#include "CourseInfoDlg.h"
#include "CourseInfo.h"
#include "RenumberDlg.h"
#include "RallyTracker.h"
#include "Verify.h"
#include "Dibapi.h"
#include  "dibutil.h"
#include "RegisterDlg.h"
#include "RallyListDlg.h"
#include "ArrowObj.h"
#include "PylonObj.h"
#include "TextObj.h"
#include "SelectFinishDlg.h"
#include "AuthorDlg.h"
#include "StationPropDlg.h"
#include "SpecialObj.h"
#include "AuthorPref.h"
#include "StationPrefDlg.h"
#include "TextPrefDlg.h"
#include "StationListPrefdlg.h"
#include "StationDescDlg.h"
#include "ScoreSheetPrefDlg.h"
#include "Scribble.h"
#include "RallyOCPrintDialog.h"
#include "StationMapper.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDogRunView

IMPLEMENT_DYNCREATE(CDogRunView, CScrollView)

BEGIN_MESSAGE_MAP(CDogRunView, CScrollView)
	//{{AFX_MSG_MAP(CDogRunView)
	ON_COMMAND(ID_DRAW_SITHALT, OnDrawSithalt)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_SELECTARROW, OnSelectarrow)
	ON_UPDATE_COMMAND_UI(ID_SELECTARROW, OnUpdateSelectarrow)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_DOC_INFO, OnDocInfo)
	ON_COMMAND(IDD_COURSE_INFO, OnCourseInfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COURSE_INFO, OnUpdateViewCourseInfo)
	ON_COMMAND(ID_VIEW_COURSE_INFO, OnViewCourseInfo)
	ON_COMMAND(ID_SIZE_TO_SCREEN, OnSizeToScreen)
	ON_UPDATE_COMMAND_UI(ID_SIZE_TO_SCREEN, OnUpdateSizeToScreen)
	ON_COMMAND(ID_DRAW_FINISH, OnDrawFinish)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FINISH, OnUpdateDrawFinish)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SITHALT, OnUpdateDrawSithalt)
	ON_COMMAND(ID_DRAW_START, OnDrawStart)
	ON_UPDATE_COMMAND_UI(ID_DRAW_START, OnUpdateDrawStart)
	ON_COMMAND(ID_DRAW_SITHALTDOWN, OnDrawSithaltdown)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SITHALTDOWN, OnUpdateDrawSithaltdown)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_HALT, OnUpdateForwardHalt)
	ON_COMMAND(ID_DRAW_HALTWALK, OnDrawHaltwalk)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HALTWALK, OnUpdateDrawHaltwalk)
	ON_COMMAND(ID_DRAW_DOWNWALK, OnDrawDownwalk)
	ON_UPDATE_COMMAND_UI(ID_DRAW_DOWNWALK, OnUpdateDrawDownwalk)
	ON_COMMAND(ID_DRAW_DOWNSIT, OnDrawDownsit)
	ON_UPDATE_COMMAND_UI(ID_DRAW_DOWNSIT, OnUpdateDrawDownsit)
	ON_COMMAND(ID_LEAVE_ABOUT_RET, OnDrawLeaveAboutReturn)
	ON_UPDATE_COMMAND_UI(ID_LEAVE_ABOUT_RET, OnUpdateLeaveAboutReturn)
	ON_COMMAND(ID_HALT_CIRCLE_FOR, OnDrawDogCircleForward)
	ON_UPDATE_COMMAND_UI(ID_HALT_CIRCLE_FOR, OnUpdateDogCircleForwar)
	ON_UPDATE_COMMAND_UI(ID_HALT_LEAVE_RECALL, OnUpdateHaltLeaveRecall)
	ON_COMMAND(ID_HALT_LEAVE_RECALL, OnDrawHaltLeaveRecall)
	ON_COMMAND(ID_DRAW_STAND, OnDrawStand)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAND, OnUpdateDrawStand)


	ON_COMMAND(ID_DRAW_STANDDOWN, OnDrawStanddown)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STANDDOWN, OnUpdateDrawStanddown)
	ON_COMMAND(ID_DRAW_STANDSIT, OnDrawStandsit)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STANDSIT, OnUpdateDrawStandsit)
	ON_COMMAND(ID_DRAW_SIT_STAND, OnDrawSitstand)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SIT_STAND, OnUpdateDrawSitstand)
	ON_COMMAND(ID_DRAW_SLOWFORWARDFROMSIT, OnDrawSlowForwardFromSit)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SLOWFORWARDFROMSIT, OnUpdateSlowForwardFromSit)
	ON_COMMAND(ID_LEAVE_ABT_REC_FIN_R, OnDrawLeaveAboutRecallFinishRight)
	ON_UPDATE_COMMAND_UI(ID_LEAVE_ABT_REC_FIN_R, OnUpdateLeaveAboutRecallFinishRight)
	ON_COMMAND(ID_LEAVE_ABT_REC_FIN_L, OnDrawLeaveAboutRecallFinishLeft)
	ON_UPDATE_COMMAND_UI(ID_LEAVE_ABT_REC_FIN_L, OnUpdateLeaveAboutRecallFinishLeft)
	ON_COMMAND(ID_CH_STATION_NUM, OnChStationNum)
	ON_UPDATE_COMMAND_UI(ID_CH_STATION_NUM, OnUpdateChStationNum)
	ON_COMMAND(ID_ZERO_DEGREES, OnZeroDegrees)
	ON_COMMAND(ID_NINETY_CCW, OnNinetyCcw)
	ON_UPDATE_COMMAND_UI(ID_NINETY_CCW, OnUpdateNinetyCcw)
	ON_COMMAND(ID_NINETY_CW, OnNinetyCw)
	ON_UPDATE_COMMAND_UI(ID_NINETY_CW, OnUpdateNinetyCw)
	ON_COMMAND(ID_ONEEIGHTY, OnOneeighty)
	ON_UPDATE_COMMAND_UI(ID_ONEEIGHTY, OnUpdateOneeighty)
	ON_COMMAND(ID_ALIGN_HORIZ, OnAlignHoriz)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_HORIZ, OnUpdateAlignHoriz)
	ON_COMMAND(ID_ALIGN_VERT, OnAlignVert)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_VERT, OnUpdateAlignVert)
	ON_COMMAND(ID_DRAW_STANDWALK, OnDrawStandwalk)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STANDWALK, OnUpdateDrawStandwalk)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_PACE, OnUpdateChangePace)
	ON_COMMAND(ID_DRAW_FAST, OnDrawFast)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FAST, OnUpdateDrawFast)
	ON_COMMAND(ID_DRAW_NORMAL, OnDrawNormal)
	ON_UPDATE_COMMAND_UI(ID_DRAW_NORMAL, OnUpdateDrawNormal)
	ON_COMMAND(ID_DRAW_SLOW, OnDrawSlow)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SLOW, OnUpdateDrawSlow)
	ON_UPDATE_COMMAND_UI(ID_RIGHT_TURNS, OnUpdateRightTurns)
	ON_COMMAND(ID_DRAW_RT_TURN, OnDrawRtTurn)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RT_TURN, OnUpdateDrawRtTurn)
	ON_COMMAND(ID__DRAW_HALTRIGHTFORWARD, OnDrawHaltRightForward)
	ON_UPDATE_COMMAND_UI(ID__DRAW_HALTRIGHTFORWARD, OnUpdateHaltRightForward)
	ON_COMMAND(ID_DRAW_ABOUT_RT, OnDrawAboutRt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ABOUT_RT, OnUpdateDrawAboutRt)
	ON_COMMAND(ID_DRAW_270_RT, OnDraw270Rt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_270_RT, OnUpdateDraw270Rt)
	ON_COMMAND(ID_DRAW_360_RT, OnDraw360Rt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_360_RT, OnUpdateDraw360Rt)
	ON_COMMAND(ID_DRAW_90_PIVOT_RT, OnDraw90PivotRt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_90_PIVOT_RT, OnUpdateDraw90PivotRt)
	ON_COMMAND(ID_DRAW_180_PIVOT_RT, OnDraw180PivotRt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_180_PIVOT_RT, OnUpdateDraw180PivotRt)
	ON_COMMAND(ID_DOUBLE_RIGHT_UTURN, OnDrawDoubleRtUTurn)
	ON_UPDATE_COMMAND_UI(ID_DOUBLE_RIGHT_UTURN, OnUpdateDrawDoubleRtUTurn)
	ON_COMMAND(ID_R_U_LEFT_ABOUT, OnDrawRtUTurnLeftAboutTurn)
	ON_UPDATE_COMMAND_UI(ID_R_U_LEFT_ABOUT, OnUpdateDrawRtUTurnLeftAboutTurn)
	ON_COMMAND(ID_STAND_PIVOT_R_FOR, OnDrawStandPivotRightForward)
	ON_UPDATE_COMMAND_UI(ID_STAND_PIVOT_R_FOR, OnUpdateDrawStandPivotRightForward)
	ON_UPDATE_COMMAND_UI(ID_LEFT_TURNS, OnUpdateLeftTurns)
	ON_COMMAND(ID_DRAW_LT_TURN, OnDrawLtTurn)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LT_TURN, OnUpdateDrawLtTurn)
	ON_COMMAND(ID_DRAW_ABOUT_LT, OnDrawAboutLt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ABOUT_LT, OnUpdateDrawAboutLt)
	ON_COMMAND(ID_DRAW_270_LT, OnDraw270Lt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_270_LT, OnUpdateDraw270Lt)
	ON_COMMAND(ID_DRAW_360_LT, OnDraw360Lt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_360_LT, OnUpdateDraw360Lt)
	ON_COMMAND(ID_DRAW_90_PIVOT_LT, OnDraw90PivotLt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_90_PIVOT_LT, OnUpdateDraw90PivotLt)
	ON_COMMAND(ID_DRAW_180_PIVOT_LT, OnDraw180PivotLt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_180_PIVOT_LT, OnUpdateDraw180PivotLt)
	ON_COMMAND(ID_DOUBLE_LEFT_UTURN, OnDrawDoubleLeftUTurn)
	ON_UPDATE_COMMAND_UI(ID_DOUBLE_LEFT_UTURN, OnUpdateDoubleLeftUTurn)
	ON_COMMAND(ID_DOUBLE_LEFT_ATURN, OnDrawDoubleLeftAboutTurn)
	ON_UPDATE_COMMAND_UI(ID_DOUBLE_LEFT_ATURN, OnUpdateDoubleLeftAboutTurn)
	ON_COMMAND(ID_L_U_LEFT_ABOUT, OnDrawLeftUTurnLeftAboutTurn)
	ON_UPDATE_COMMAND_UI(ID_L_U_LEFT_ABOUT, OnUpdateLeftUTurnLeftAboutTurn)
	ON_COMMAND(ID_L_ABOUT_RIGHT_U, OnDrawLeftUTurnRightAboutTurn)
	ON_UPDATE_COMMAND_UI(ID_L_ABOUT_RIGHT_U, OnUpdateLeftUTurnRightAboutTurn)
	ON_COMMAND(ID_L_ABOUT_LEFT_U, OnDrawLeftAboutTurnLeftUTurn)
	ON_UPDATE_COMMAND_UI(ID_L_ABOUT_LEFT_U, OnUpdateLeftAboutTurnLeftUTurn)
	ON_COMMAND(ID_STAND_PIVOT_L_FOR, OnDrawStandPivotLeftForward)
	ON_UPDATE_COMMAND_UI(ID_STAND_PIVOT_L_FOR, OnUpdateStandPivotLeftForward)
	ON_COMMAND(ID_TR_L_HEEL_R_T_R, OnDraw180LeftHeelRight180Right)
	ON_UPDATE_COMMAND_UI(ID_TR_L_HEEL_R_T_R, OnUpdate180LeftHeelRight180Right)
	ON_COMMAND(ID_DRAW_HONOR, OnDrawHonor)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HONOR, OnUpdateDrawHonor)
	ON_COMMAND(ID_ABOUT_FORWARD_RT, OnAboutForwardRt)
	ON_UPDATE_COMMAND_UI(ID_ABOUT_FORWARD_RT, OnUpdateAboutForwardRt)
	ON_COMMAND(ID_DRAW_ABOUT_TURN_LT, OnDrawAboutTurnLt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ABOUT_TURN_LT, OnUpdateDrawAboutTurnLt)
	ON_COMMAND(ID_DRAW_FRONTHEEL, OnDrawFrontHeel)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FRONTHEEL, OnUpdateFrontHeel)
	ON_COMMAND(ID__DRAW_HALTLEFTFORWARD, OnDrawHaltLeftForward)
	ON_UPDATE_COMMAND_UI(ID__DRAW_HALTLEFTFORWARD, OnUpdateHaltLeftForward)

	ON_COMMAND(ID_DRAW_HALTLEFTPIVOTFORWARD, OnDrawHaltLeftPivotForward)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HALTLEFTPIVOTFORWARD, OnUpdateHaltLeftPivotForward)
	ON_COMMAND(ID_DRAW_HALTRIGHTPIVOTFORWARD, OnDrawHaltRightPivotForward)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HALTRIGHTPIVOTFORWARD, OnUpdateHaltRightPivotForward)



	ON_COMMAND(ID_DRAW_U_FORWARD_LT, OnDrawUForwardLt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_U_FORWARD_LT, OnUpdateDrawUForwardLt)
	ON_COMMAND(ID_DRAW_1STEP_HEEL_RT, OnDraw1stepHeelRt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_1STEP_HEEL_RT, OnUpdateDraw1stepHeelRt)
	ON_UPDATE_COMMAND_UI(ID_FINISH, OnUpdateFinish)
	ON_COMMAND(ID_DRAW_FINISH_LEFT_FORWARD, OnDrawFinishLeftForward)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FINISH_LEFT_FORWARD, OnUpdateDrawFinishLeftForward)
	ON_COMMAND(ID_DRAW_FINISH_LT_HALT, OnDrawFinishLtHalt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FINISH_LT_HALT, OnUpdateDrawFinishLtHalt)
	ON_COMMAND(ID_DRAW_FINISH_RT_FORWARD, OnDrawFinishRtForward)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FINISH_RT_FORWARD, OnUpdateDrawFinishRtForward)
	ON_COMMAND(ID_DRAW_FINISH_RT_HALT, OnDrawFinishRtHalt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FINISH_RT_HALT, OnUpdateDrawFinishRtHalt)
	ON_COMMAND(ID_DRAW_HALT_FINISH_LT, OnDrawHaltFinishLt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HALT_FINISH_LT, OnUpdateDrawHaltFinishLt)
	ON_COMMAND(ID_FRONT_REV_3_STEPS, OnDrawReverseThreeSteps)
	ON_UPDATE_COMMAND_UI(ID_FRONT_REV_3_STEPS, OnUpdateDrawReverseThreeSteps)
	ON_COMMAND(ID_FRT_CIR_R_FIN_L, OnDrawFrontCircleRightFinishLeft)
	ON_UPDATE_COMMAND_UI(ID_FRT_CIR_R_FIN_L, OnUpdateDrawFrontCircleRightFinishLeft)
	ON_COMMAND(ID_DRAW_HALT_FINISH_RT, OnDrawHaltFinishRt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HALT_FINISH_RT, OnUpdateDrawHaltFinishRt)
	ON_COMMAND(ID_DRAW_FAST_SIT, OnDrawFastSit)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FAST_SIT, OnUpdateDrawFastSit)
	ON_UPDATE_COMMAND_UI(ID_MOVE, OnUpdateMove)
	ON_COMMAND(ID_DRAW_SIDE_RT, OnDrawSideRt)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SIDE_RT, OnUpdateDrawSideRt)
	ON_COMMAND(ID_DRAW_MOVE_DOWN, OnDrawMoveDown)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MOVE_DOWN, OnUpdateDrawMoveDown)
	ON_COMMAND(ID_DRAW_MOVINGSTAND, OnDrawMoveStand)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MOVINGSTAND, OnUpdateDrawMoveStand)
	ON_COMMAND(ID_DRAW_JUMP, OnDrawJump)
	ON_UPDATE_COMMAND_UI(ID_DRAW_JUMP, OnUpdateDrawJump)
	ON_COMMAND(ID__DRAW_DOWNWHILEHEELING, OnDrawDownWhileHeeling)
	ON_UPDATE_COMMAND_UI(ID__DRAW_DOWNWHILEHEELING, OnUpdateDrawDownWhileHeeling)
	ON_COMMAND(ID__STAND_HEEL, OnDrawStandWhileHeeling)
	ON_UPDATE_COMMAND_UI(ID__STAND_HEEL, OnUpdateDrawStandWhileHeeling)
	ON_COMMAND(ID__DRAW_STAND_SIT_LEAVE, OnDrawStandSitLeave)
	ON_UPDATE_COMMAND_UI(ID__DRAW_STAND_SIT_LEAVE, OnUpdateDrawStandSitLeave)
	ON_COMMAND(ID__STAND_LEAVE_DOWN, OnDrawStandDownLeave)
	ON_UPDATE_COMMAND_UI(ID__STAND_LEAVE_DOWN, OnUpdateDrawStandDownLeave)
	ON_COMMAND(ID__DRAW_DOUBLE_LEFT_TURN, OnDrawDoubleLeftTurn)
	ON_UPDATE_COMMAND_UI(ID__DRAW_DOUBLE_LEFT_TURN, OnUpdateDrawDoubleLeftTurn)
	ON_COMMAND(ID__DRAW_SENDTOJUMP, OnDrawSendtoJump)
	ON_UPDATE_COMMAND_UI(ID__DRAW_SENDTOJUMP, OnUpdateDrawSendtoJump)

	ON_COMMAND(ID__DRAW_SITSTAY, OnDrawSitStay)
	ON_UPDATE_COMMAND_UI(ID__DRAW_SITSTAY, OnUpdateDrawSitStay)
	ON_COMMAND(ID__DRAW_CALLTOHEEL, OnDrawCalltoHeel)
	ON_UPDATE_COMMAND_UI(ID__DRAW_CALLTOHEEL, OnUpdateDrawCalltoHeel)

	ON_COMMAND(ID_DRAW_MOVE_STAND_WALK, OnDrawMoveStandWalk)
	ON_UPDATE_COMMAND_UI(ID_DRAW_MOVE_STAND_WALK, OnUpdateDrawMoveStandWalk)
	ON_COMMAND(ID__DRAW_MOVE_DOWN, OnDrawMoveDownWalk)
	ON_UPDATE_COMMAND_UI(ID__DRAW_MOVE_DOWN, OnUpdateDrawMoveDownWalk)


	ON_COMMAND(ID_DRAW_BACKUP_3, OnDrawBackup3)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BACKUP_3, OnUpdateDrawBackup3)
	ON_UPDATE_COMMAND_UI(ID_HEEL, OnUpdateHeel)
	ON_COMMAND(ID_DRAW_HALT_3_STEPS_FOR, OnDrawHalt3StepsFor)
	ON_UPDATE_COMMAND_UI(ID_DRAW_HALT_3_STEPS_FOR, OnUpdateDrawHalt3StepsFor)
	ON_COMMAND(ID_DRAW_FRONT_3_STEPS_BACK, OnDrawFront3StepsBack)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FRONT_3_STEPS_BACK, OnUpdateDrawFront3StepsBack)
	ON_UPDATE_COMMAND_UI(ID_WEAVE, OnUpdateWeave)
	ON_COMMAND(ID_DRAW_WEAVE_TWICE, OnDrawWeaveTwice)
	ON_UPDATE_COMMAND_UI(ID_DRAW_WEAVE_TWICE, OnUpdateDrawWeaveTwice)
	ON_COMMAND(ID_DRAW_SERP_ONCE, OnDrawSerpOnce)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SERP_ONCE, OnUpdateDrawSerpOnce)
	ON_COMMAND(ID_DRAW_OFFSET_8, OnDrawOffset8)
	ON_UPDATE_COMMAND_UI(ID_DRAW_OFFSET_8, OnUpdateDrawOffset8)
	ON_COMMAND(ID_WEAVES_FIGURE8, OnDrawFig8NoDistractions)
	ON_UPDATE_COMMAND_UI(ID_WEAVES_FIGURE8, OnUpdateFig8NoDistractions)
	ON_COMMAND(ID_DRAW_SPIRAL_LEFT, OnDrawSpiralLeft)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SPIRAL_LEFT, OnUpdateDrawSpiralLeft)
	ON_COMMAND(ID_DRAW_SPIRAL_RIGHT, OnDrawSpiralRight)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SPIRAL_RIGHT, OnUpdateDrawSpiralRight)
	ON_COMMAND(ID_DRAW_SIDE_RIGHT, OnDrawSideRight)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SIDE_RIGHT, OnUpdateDrawSideRight)
	ON_COMMAND(ID__DRAW_2_STEPS_FORWARD, OnDrawTwoStepsForward)
	ON_UPDATE_COMMAND_UI(ID__DRAW_2_STEPS_FORWARD, OnUpdateDrawTwoStepsForward)


	ON_COMMAND(IDD_COURSE_VERIFY, OnCourseVerify)
	ON_UPDATE_COMMAND_UI(ID_NONSTATIONARY, OnUpdateNonstationary)
	ON_UPDATE_COMMAND_UI(ID_STATIONARY, OnUpdateStationary)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED, OnUpdateAdvanced)
	ON_UPDATE_COMMAND_UI(ID_EXCELLENT, OnUpdateExcellent)
	ON_UPDATE_COMMAND_UI(ID_MASTER, OnUpdateMaster)
	ON_COMMAND(ID_SAVE_BITMAP, OnSaveBitmap)
	ON_COMMAND(ID_REG_DIALOG, OnRegDialog)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_PRINT_BW, OnFilePrintBw)
	ON_UPDATE_COMMAND_UI(ID_ZERO_DEGREES, OnUpdateZeroDegrees)
	ON_COMMAND(ID_RALLY_LIST, OnRallyList)
	ON_UPDATE_COMMAND_UI(ID_RALLY_LIST, OnUpdateRallyList)
	ON_UPDATE_COMMAND_UI(ID_PRINT_SCORE_SHEET, OnUpdatePrintScoreSheet)
	ON_UPDATE_COMMAND_UI(ID_PYLONS, OnUpdatePylons)
	ON_COMMAND(ID_PYLONS, OnPylons)
	ON_COMMAND(ID_COPY_COURSE, OnCopyCourse)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_MY_FONT, OnMyFont)
	ON_UPDATE_COMMAND_UI(ID_MY_FONT, OnUpdateMyFont)
	ON_COMMAND(ID_EDIT_TEXT, OnEditText)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TEXT, OnUpdateEditText)
	ON_COMMAND(ID_TEXT_FONT, OnTextFont)
	ON_UPDATE_COMMAND_UI(ID_TEXT_FONT, OnUpdateTextFont)
	ON_COMMAND(ID_MOVE_STAND_LEAVE, OnMovestandleave)
	ON_UPDATE_COMMAND_UI(ID_MOVE_STAND_LEAVE, OnUpdateMovestandleave)
	ON_COMMAND(ID_MOVE_STAND_LEAVE_TWO, OnMovestandleavetwo)
	ON_UPDATE_COMMAND_UI(ID_MOVE_STAND_LEAVE_TWO, OnUpdateMovestandleavetwo)
	ON_COMMAND(ID_MOVE_STAND_SIT_FINISH, OnMovestandsitfinish)
	ON_UPDATE_COMMAND_UI(ID_MOVE_STAND_SIT_FINISH, OnUpdateMovestandsitfinish)
	ON_COMMAND(ID_MOVE_STAND_SIT_FINISH_TWO, OnMovestandsitfinishtwo)
	ON_UPDATE_COMMAND_UI(ID_MOVE_STAND_SIT_FINISH_TWO, OnUpdateMovestandsitfinishtwo)
	ON_COMMAND(ID_FRONT_RUN, OnFrontrun)
	ON_UPDATE_COMMAND_UI(ID_FRONT_RUN, OnUpdateFrontrun)
	ON_COMMAND(ID_JUMP_RECALL, OnJumprecall)
	ON_UPDATE_COMMAND_UI(ID_JUMP_RECALL_TWO, OnUpdateJumprecalltwo)
	ON_COMMAND(ID_JUMP_RECALL_TWO, OnJumprecalltwo)
	ON_UPDATE_COMMAND_UI(ID_JUMP_RECALL, OnUpdateJumprecall)
	ON_COMMAND(ID_JUMP_LEAVE, OnJumpleave)
	ON_UPDATE_COMMAND_UI(ID_JUMP_LEAVE, OnUpdateJumpleave)
	ON_COMMAND(ID_JUMP_LEAVE_TWO, OnJumpleavetwo)
	ON_UPDATE_COMMAND_UI(ID_JUMP_LEAVE_TWO, OnUpdateJumpleavetwo)
	ON_COMMAND(ID_DRAW_RT_DOWN, OnRightdown)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RT_DOWN, OnUpdateRightdown)
	ON_COMMAND(ID_DRAW_LT_DOWN, OnLeftdown)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LT_DOWN, OnUpdateLeftdown)
	ON_COMMAND(ID_RETRIEVE_FINISH, OnRetrieveFinish)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_FINISH, OnUpdateRetrieveFinish)
	ON_COMMAND(ID_DOWN_RECALL, OnDownRecall)
	ON_UPDATE_COMMAND_UI(ID_DOWN_RECALL, OnUpdateDownRecall)
	ON_COMMAND(ID_DOWN_RECALL_TWO, OnDownRecalltwo)
	ON_UPDATE_COMMAND_UI(ID_DOWN_RECALL_TWO, OnUpdateDownRecalltwo)
	ON_COMMAND(ID_RECALL_LEAVE, OnRecallLeave)
	ON_UPDATE_COMMAND_UI(ID_RECALL_LEAVE, OnUpdateRecallLeave)
	ON_COMMAND(ID_TURN_FRONT, OnTurnFront)
	ON_UPDATE_COMMAND_UI(ID_TURN_FRONT, OnUpdateTurnFront)
	ON_COMMAND(ID_FINISH_RIGHT, OnFinishRight)
	ON_UPDATE_COMMAND_UI(ID_FINISH_RIGHT, OnUpdateFinishRight)
	ON_COMMAND(ID_FINISH_LEFT, OnFinishLeft)
	ON_UPDATE_COMMAND_UI(ID_FINISH_LEFT, OnUpdateFinishLeft)
	ON_COMMAND(IDD_AUTOR_PREF, OnAutorPref)
	ON_COMMAND(ID_JUMP_TOOL, OnJumpTool)
	ON_UPDATE_COMMAND_UI(ID_JUMP_TOOL, OnUpdateJumpTool)
	ON_COMMAND(ID_LEASH_TOOL, OnLeashTool)
	ON_UPDATE_COMMAND_UI(ID_LEASH_TOOL, OnUpdateLeashTool)
	ON_COMMAND(ID_GATE_TOOL, OnGateTool)
	ON_UPDATE_COMMAND_UI(ID_GATE_TOOL, OnUpdateGateTool)
	ON_COMMAND(ID_ARROW_TOOL, OnArrowTool)
	ON_UPDATE_COMMAND_UI(ID_ARROW_TOOL, OnUpdateArrowTool)
	ON_COMMAND(ID_RETURN_STAND, OnReturnStand)
	ON_UPDATE_COMMAND_UI(ID_RETURN_STAND, OnUpdateReturnStand)
	ON_COMMAND(ID_ARROW_PREF, OnArrowPref)
	ON_UPDATE_COMMAND_UI(ID_ARROW_PREF, OnUpdateArrowPref)
	ON_COMMAND(ID_ST_PROP_DIALOG, OnStPropDialog)
	ON_UPDATE_COMMAND_UI(ID_ST_PROP_DIALOG, OnUpdateStPropDialog)
	ON_COMMAND(ID_TEXT_PROP, OnTextPropDialog)
	ON_UPDATE_COMMAND_UI(ID_TEXT_PROP, OnUpdateTextPropDialog)
	ON_COMMAND(ID_STRAIGHT_LINE, OnStraightline)
	ON_UPDATE_COMMAND_UI(ID_STRAIGHT_LINE, OnUpdateStraightline)
	ON_COMMAND(ID_REVERSE_ARROW, OnReversearrow)
	ON_UPDATE_COMMAND_UI(ID_REVERSE_ARROW, OnUpdateReversearrow)
	ON_COMMAND(ID_AR_PROP_DIALOG, OnArrowproperties)
	ON_UPDATE_COMMAND_UI(ID_AR_PROP_DIALOG, OnUpdateArrowproperties)
	ON_COMMAND(ID_STATION_PREF, OnStationPref)
	ON_UPDATE_COMMAND_UI(ID_STATION_PREF, OnUpdateStationPref)
	ON_UPDATE_COMMAND_UI(ID_PATTERN, OnUpdatePattern)
	ON_COMMAND(ID_OFFSET_3A, OnOffset3a)
	ON_UPDATE_COMMAND_UI(ID_OFFSET_3A, OnUpdateOffset3a)
	ON_COMMAND(ID_OFFSET_3B, OnOffset3b)
	ON_UPDATE_COMMAND_UI(ID_OFFSET_3B, OnUpdateOffset3b)
	ON_COMMAND(ID_SPIRAL_LT, OnSpirallt)
	ON_UPDATE_COMMAND_UI(ID_SPIRAL_LT, OnUpdateSpirallt)
	ON_COMMAND(ID_SPIRAL_RT_1A, OnSpiralrt1a)
	ON_UPDATE_COMMAND_UI(ID_SPIRAL_RT_1A, OnUpdateSpiralrt1a)
	ON_COMMAND(ID_SPIRAL_RT_1B, OnSpiralrt1b)
	ON_UPDATE_COMMAND_UI(ID_SPIRAL_RT_1B, OnUpdateSpiralrt1b)
	ON_COMMAND(ID_STATION_LIST_PR, OnStationListPr)
	ON_COMMAND(ID_STATION_DESC_PR, OnStationDescPr)
	ON_COMMAND(ID_SCORE_SHEET_PR, OnScoreSheetPr)
	ON_COMMAND(ID_TABLE_TOOL, OnTableTool)
	ON_UPDATE_COMMAND_UI(ID_TABLE_TOOL, OnUpdateTableTool)
	ON_COMMAND(ID_SELECT_ALL_STATIONS, OnSelectAllStations)
	ON_COMMAND(ID_LINE_TOOL, OnLineTool)
	ON_UPDATE_COMMAND_UI(ID_LINE_TOOL, OnUpdateLineTool)
	ON_COMMAND(ID_BR_JUMP_TOOL, OnBrJumpTool)
	ON_UPDATE_COMMAND_UI(ID_BR_JUMP_TOOL, OnUpdateBrJumpTool)
	ON_COMMAND(ID_SCRIBBLE_TOOL, OnScribbleTool)
	ON_UPDATE_COMMAND_UI(ID_SCRIBBLE_TOOL, OnUpdateScribbleTool)
	ON_COMMAND(ID_BONE, OnBone)
	ON_UPDATE_COMMAND_UI(ID_BONE, OnUpdateBone)
	ON_COMMAND(ID_SERP_PATTERN, OnSerpPattern)
	ON_UPDATE_COMMAND_UI(ID_SERP_PATTERN, OnUpdateSerpPattern)
	ON_COMMAND(ID_FIG8_PATTERN, OnFig8Pattern)
	ON_UPDATE_COMMAND_UI(ID_FIG8_PATTERN, OnUpdateFig8Pattern)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_ITEM1, ID_ITEM40, OnInsertAfter)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ITEM1, ID_ITEM40, OnUpdateInsertAfter)
	ON_COMMAND_RANGE(ID_CH_MENU_1, ID_CH_MENU_76, OnChangeTo)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CH_MENU_1, ID_CH_MENU_76, OnUpdateChangeTo)

	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDogRunView construction/destruction

CDogRunView::CDogRunView()
{
	// TODO: add construction code here
	this->m_rotate_station = false;
	this->m_rotating_station = false;
	this->m_rotate_special = false;
	this->m_rotating_special = false;
	this->m_resize_station = false;
	this->m_resizing_station = false;
	this->m_resizing_special = false;
	this->m_resize_special = false;
	this->m_create_arrow = false;
	this->m_creating_arrow = false;
	this->m_create_line = false;
	this->m_dragging_line = false;
	this->m_curving_line = false;
	this->m_create_scribble = false;
	this->m_SelectedShapeOnToolBar = GRABARROW;
	this->m_popup_point.x = -10;
	this->m_popup_point.y = -10;
	this->m_print_grid_lines = GRID_BLACK;
	this->m_drag_select = false;
	this->m_size_to_fit = false;
	this->m_do_the_drag = false;
	this->m_drag_info = false;
	this->m_last_drag_rect.left = NULL;
	this->m_auto_scroll = false;
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
	this->m_dead_flag = pApp->m_dead_flag;
	show_error = false;
	this->m_advanced_mode  = true;
	this->m_number_honor = false;
	this->m_line_hit = NO_HIT;
	this->m_move_line = false;
	this->m_text_editing = false;
	this->m_in_text_box = false;
	this->mp_edit_dlg = NULL;
	this->m_printing = false;
	this->m_print_left_margin = false;
	this->m_type_course = APDT_COURSE;
	this->mp_created_arrow = NULL;
	this->mp_created_scribble = NULL;
}

CDogRunView::~CDogRunView()
{
	if (this->mp_edit_dlg != NULL) {
		this->mp_edit_dlg->DestroyWindow();
		delete this->mp_edit_dlg;
	}
	this->ClearAllStationsFromSelectedList(true);
	
}

BOOL CDogRunView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDogRunView drawing

void CDogRunView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here


//	int error_code;
	if (pDC->IsPrinting()) {
		CString file_path;
		HANDLE hDib ;
		CDC *window_dc;
		window_dc = this->GetDC();
		double dest_width, dest_height;
		double ratio_value;
		int print_x, print_y;
		CSize pixels_per_page_printer;
		if (m_print_left_margin) {
			print_x = (int)(pDC->GetDeviceCaps(LOGPIXELSX));			
		}
		else {
			print_x = (int)(pDC->GetDeviceCaps(LOGPIXELSX) * 0.5);
		}
		print_y = (int)(pDC->GetDeviceCaps(LOGPIXELSY) * 0.5);

		pixels_per_page_printer.cx = pDC->GetDeviceCaps(HORZRES ) - print_x;
		pixels_per_page_printer.cy = pDC->GetDeviceCaps(VERTRES ) - print_y;

		int x_pixels = pDC->GetDeviceCaps(PHYSICALWIDTH ) - print_x;
		int y_pixels = pDC->GetDeviceCaps(PHYSICALHEIGHT ) - print_y;
		
// does this fix a printing bug where the right side is clipped????
// apparently not!
		if (x_pixels < 	pixels_per_page_printer.cx) pixels_per_page_printer.cx = x_pixels;
		if (y_pixels < 	pixels_per_page_printer.cy) pixels_per_page_printer.cy = y_pixels;
		// adding a left side margin
		int left_margin = pDC->GetDeviceCaps(PHYSICALOFFSETX);

		hDib = WndToBmp(window_dc,file_path,FALSE);
		if(hDib == NULL) return;
		BITMAPINFOHEADER    *pBMI ;
		pBMI = (BITMAPINFOHEADER*)GlobalLock(hDib) ;
		int nColors = 0;
		if (pBMI->biBitCount <= 8) {
			nColors = (1 << pBMI->biBitCount);
		}
		// print the correct image
		ratio_value = (double)pBMI->biWidth/(double)pBMI->biHeight;

		if (ratio_value == 1) {
			if (pixels_per_page_printer.cx >= pixels_per_page_printer.cy) {
				dest_height = dest_width = pixels_per_page_printer.cy;
			}
			else {
				dest_height = dest_width = pixels_per_page_printer.cx;
			}
		}
		else if (ratio_value < 1) { // width less than height
			dest_height = pixels_per_page_printer.cy;
			dest_width = dest_height * ratio_value;
			if (dest_width > pixels_per_page_printer.cx) {
				dest_width = pixels_per_page_printer.cx;
				dest_height = dest_width / ratio_value;
			}

		}
		else { // width > height 
			dest_width = pixels_per_page_printer.cx;
			dest_height = dest_width / ratio_value;
			if (dest_height > pixels_per_page_printer.cy) {
				dest_height = pixels_per_page_printer.cy;
				dest_width = dest_height / ratio_value;
			}

		}

		::StretchDIBits(pDC->m_hDC,
							print_x, 
							print_y, 
							(int)dest_width, 
							(int)dest_height,
							0, 
							0, 
							pBMI->biWidth,
							pBMI->biHeight,
							(LPBYTE)pBMI + (pBMI->biSize + nColors * sizeof(RGBQUAD)),
							(BITMAPINFO*)pBMI,
							DIB_RGB_COLORS, 
							SRCCOPY);
		// free resources
		GlobalUnlock(hDib) ;
		GlobalFree(hDib) ;
		return;

	}

	CMemDC pmemDC(pDC);

	this->SetDCFont(pmemDC);
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
 
	CString out_string;

//	CRallyObject* pRallyItemInlist;
	PylonObj* pPylonItemInlist;
	TextObj* pTextItemInlist;
	SpecialObj *pSpecialItemInlist;
	Scribble *pScribbleItemInlist;

	POSITION pos;
	for( pos = pDoc->m_special_list.GetHeadPosition(); pos != NULL; ) {
		pSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetNext(pos);
		pSpecialItemInlist->DrawSpecialObjects(pmemDC, this->m_printing);
	}
	this->DrawGrid(pmemDC);
	if (pDoc->m_station_list->ViewStationList()) {
		POSITION first_non_pylon_pos = pDoc->FindFirstNonPylonPosition();
		pDoc->m_station_list->DrawStationList(pmemDC,&pDoc->m_rallyList, this->m_where_list, &this->m_grid_rect, first_non_pylon_pos);
	}

	if (pDoc->m_course_info->ViewCourse()) {
		CRect dummy_rect;
		pDoc->m_course_info->DrawCourseInfo(pmemDC, pDoc->m_station_list->ViewStationList(), &this->m_grid_rect, pDoc->m_station_list->GetStationListRect(&dummy_rect));
	}
	pDoc->m_rallyList.DrawRallyObjects(pmemDC, this->m_stat_num_loc, this->m_advanced_mode, this->m_where_cones, this->m_rotate_station, this->m_printing);

	if (this->m_text_editing && this->mp_textobj != NULL) {
		this->mp_textobj->DrawTextBox(pmemDC,false );
	}
	for( pos = pDoc->m_text_list.GetHeadPosition(); pos != NULL; ) {
		pTextItemInlist = (TextObj*)pDoc->m_text_list.GetNext(pos);
		pTextItemInlist->DrawTextBox(pmemDC, this->m_printing);
	}


	for( pos = pDoc->m_pylonList.GetHeadPosition(); pos != NULL; ) {
		pPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetNext(pos);
		pPylonItemInlist->DrawCones(pmemDC);
	}
	for( pos = pDoc->m_scribbleList.GetHeadPosition(); pos != NULL; ) {
		pScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetNext(pos);
		pScribbleItemInlist->DrawStroke(pmemDC, this->m_printing);
	}	
	
//	if (this->m_show_path) {
		pDoc->m_arrowList.DrawArrows(pmemDC, this->m_printing, false);
//	}
	if (this->m_creating_arrow) {
		CPoint exit_point, entry_point;
		exit_point = this->mp_created_arrow->GetExitPoint();
		entry_point = this->mp_created_arrow->GetEntryPoint();
		COLORREF line_color;
		line_color = RGB(0, 0, 0);
		CPen penDash;
		penDash.CreatePen(PS_DASH   , 1, line_color);
		CPen* pOldPen = pmemDC->SelectObject(&penDash);
		pmemDC->MoveTo(exit_point);
		pmemDC->LineTo(entry_point);
		pmemDC->SelectObject(pOldPen);
	}
	if (this->m_create_scribble) {
		mp_created_scribble->DrawStroke(pmemDC, this->m_printing);
	}
	if (!(this->m_line_hit == NO_HANDLE) && this->m_do_the_drag) {
		pDoc->m_arrowList.DrawMovingArrows(pmemDC);			
	}
	
	if (0) {
		switch(this->m_line_hit) {
		case NO_HIT:
		out_string.Format("NO HIT IN ARROW %d",this->m_line_hit);
			break;
		case EXIT_HANDLE:
		out_string.Format("exit handle hit %d",this->m_line_hit);
			break;
		case FIRST_HANDLE:
		out_string.Format("first handle hit %d",this->m_line_hit);
			break;
		case SECOND_HANDLE:
		out_string.Format("second handle hit %d",this->m_line_hit);
			break;
		case THIRD_HANDLE:
		out_string.Format("third handle hit %d",this->m_line_hit);
			break;
		case FOURTH_HANDLE:
		out_string.Format("fourth handle hit %d",this->m_line_hit);
			break;
		case ENTRY_HANDLE:
		out_string.Format("entry handle hit %d",this->m_line_hit);
			break;
		case NO_HANDLE:
		out_string.Format("no handle hit/not hit? %d",this->m_line_hit);
			break;
		case LINE_HIT:
		out_string.Format("line hit %d",this->m_line_hit);
			break;
		default:
			out_string.Format("should not see this! %d",this->m_line_hit);
			break;
		}	
		pmemDC->TextOut(10,10,out_string);
	}

	if (SHOW_LIST_COUNTS) {
		int count;
//		CString out_string;
		count = pDoc->GetUndoListCount();
		out_string.Format("items in undo list %d",count);
		pmemDC->TextOut(10,10,out_string);

		count = pDoc->GetRedoListCount();
		out_string.Format("items in redo list %d",count);
		pmemDC->TextOut(10,40,out_string);

		count = this->m_stations_selected.GetCount();
		out_string.Format("items in select list %d",count);
		pmemDC->TextOut(10,70,out_string);

		count = pDoc->m_rallyList.GetCount();
		out_string.Format("items in rally list %d",count);
		pmemDC->TextOut(10,100,out_string);

		count = pDoc->m_pylonList.GetCount();
		out_string.Format("items in pylon list %d",count);
		pmemDC->TextOut(10,130,out_string);

		CDogRunApp* dogRunApp;
		dogRunApp = (CDogRunApp*)AfxGetApp( ); 

		
		count = dogRunApp->m_clipBoard.GetCount();
		out_string.Format("items on clipboard %d",count);
		pmemDC->TextOut(10,160,out_string);

		count = pDoc->m_arrowList.GetCount();
		out_string.Format("items in arrow list %d",count);
		pmemDC->TextOut(10,190,out_string);

	}	

}
/////////////////////////////////////////////////////////////////////////////
// CDogRunView printing

BOOL CDogRunView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	if (this->m_dead_flag == TIME_EXPIRED) {
		RegisterDlg dlgReg;	
		dlgReg.DoModal();
		return false;
	}
	CDogRunDoc* pDoc = GetDocument();

    // Delete the CPrintDialog object created in the CPrintInfo
     // constructor, and substitute with customized print dialog.
     delete pInfo->m_pPD;

     // Construct and substitute with customized print dialog.
	CRallyOCPrintDialog *p_temp_dialog; 
	 pInfo->m_pPD = new CRallyOCPrintDialog(false, PD_ALLPAGES  | PD_NOSELECTION  | PD_HIDEPRINTTOFILE );
	p_temp_dialog = (CRallyOCPrintDialog *)pInfo->m_pPD;
     pInfo->m_pPD->m_pd.nMinPage = 1;      // one based page numbers
	pInfo->SetMaxPage(1);
  // Change the PRINTDLG struct so that the custom print dialog will
     // be used.
     pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();
     pInfo->m_pPD->m_pd.lpPrintTemplateName =
                                          MAKEINTRESOURCE(IDD_PRINT);
	p_temp_dialog->m_print_left_margin = pDoc->GetPrintLeftOneInchMargin();
 
     // Set the Flags of the PRINTDLG structure as shown, else the
     // changes will have no effect
     pInfo->m_pPD->m_pd.Flags |= PD_ENABLEPRINTTEMPLATE;


	BOOL bRet = DoPreparePrinting (pInfo);      // default preparation
	pInfo->m_nNumPreviewPages = 1;        //Preview 1 pages at a time

	// Set this value after calling DoPreparePrinting to override
	// value read from registry
	return bRet;


}

void CDogRunView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	CRallyOCPrintDialog *p_temp_dialog;
	p_temp_dialog = (CRallyOCPrintDialog *)pInfo->m_pPD;
	this->m_print_left_margin = p_temp_dialog->m_print_left_margin;
	this->m_printing = true;
}

void CDogRunView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	this->m_printing = false;
	CDogRunDoc* pDoc = GetDocument();
	pDoc->m_doc_printed = COleDateTime::GetCurrentTime();
	pDoc->SetLeftOneInchMargin(this->m_print_left_margin);
	
}
void CDogRunView::SetDCFont(CDC* pDC) {

	CFont* def_font = pDC->SelectObject(&this->m_course_font);
	COLORREF old_color = pDC->SetTextColor(this->m_course_color);

}
void CDogRunView::CreateMyFont(CDC *dc) {

	CDogRunDoc* pDoc = GetDocument();
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	this->m_course_color = pDoc->GetDefaultCourseLogFont(&lf);
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc->m_hDC, LOGPIXELSY)) / 72);
 
	VERIFY(this->m_course_font.CreateFontIndirect(&lf));  // create the font
	pDoc->m_rallyList.CreateStationFont(pDoc->m_stat_font,dc);

}
void CDogRunView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
 	CScrollView::OnPrepareDC(pDC, pInfo);

	if (this->m_size_to_fit && !pDC->IsPrinting()) {

		CRect window_rect;
		// seting the mode to MM_ISOTROPIC keeps makes the scale x-y same
		pDC->SetMapMode(MM_ISOTROPIC);
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0, 0);
		// The window is the logical size of the image.
		CSize window_extent = pDC->SetWindowExt(m_sizeTotal.cx, m_sizeTotal.cy);

		this->GetClientRect(&window_rect);
		// The viewport is the size of the client window.

		pDC->SetViewportExt(window_rect.right - window_rect.left, window_rect.bottom - window_rect.top);
	}
	this->SetDCFont(pDC);
}
/////////////////////////////////////////////////////////////////////////////
// CDogRunView diagnostics

#ifdef _DEBUG
void CDogRunView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDogRunView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDogRunDoc* CDogRunView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDogRunDoc)));
	return (CDogRunDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDogRunView message handlers

void CDogRunView::OnDrawSithalt() 
{
	// TODO: Add your command handler code here
	
	this->m_SelectedShapeOnToolBar = ID_DRAW_SITHALT;
	this->ClearAllStationsFromSelectedList(true);

}

void CDogRunView::OnUpdateDrawSithalt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SITHALT) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);	
}
int CDogRunView::HitPointInAnyRallyRect(CPoint *point) {
	CDogRunDoc* pDoc = GetDocument();
	POSITION pos;
	int selection_status = NOT_SELECTED;
	CRallyObject  *pRallyItemInlist;
	TextObj *pTextObjectInlist;

	SpecialObj *pSpecialObjectInlist;

	pos = pDoc->m_rallyList.GetHeadPosition();
	BOOL quit_loop = false;
		// this loop finds first station in list w/hit, and marks selected list per shift key and hit status
	while(pos != NULL && !quit_loop) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
		
		selection_status = pRallyItemInlist->HitPointInStationRect(point);

		if (selection_status == SELECTED) {
			this->AddStationToSelectedList(pRallyItemInlist);
			quit_loop = true;
		}

		if (selection_status == ALL_READY_SELECTED) {
			quit_loop = true;
		}
	}
	pos = pDoc->m_text_list.GetHeadPosition();
	while(pos != NULL && !quit_loop) {
		pTextObjectInlist = (TextObj*)pDoc->m_text_list.GetNext(pos);
		
		selection_status = pTextObjectInlist->MousePtInTextRect(point);

		if (selection_status == SELECTED) {
			this->AddTextToSelectedList(pTextObjectInlist);
			quit_loop = true;
		}

		if (selection_status == ALL_READY_SELECTED) {
			quit_loop = true;
		}
	}
	pos = pDoc->m_special_list.GetHeadPosition();
	while(pos != NULL && !quit_loop) {
		pSpecialObjectInlist = (SpecialObj*)pDoc->m_special_list.GetNext(pos);
		
		selection_status = pSpecialObjectInlist->MousePointInSpecialRect(point);

		if (selection_status == SELECTED) {
			this->AddSpecialToSelectedList(pSpecialObjectInlist);
			quit_loop = true;
		}

		if (selection_status == ALL_READY_SELECTED) {
			quit_loop = true;
		}
	}
	CClientDC dc(this);
	pDoc->m_arrowList.CheckForLineHit(point, &dc, false);
	this->Invalidate(FALSE);

	return selection_status;
}
void CDogRunView::ChangeDCToSizeToWindow(CDC* pDC) {

	CRect window_rect, course_info, station_list;
	// seting the mode to MM_ISOTROPIC makes the scale x-y same

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportOrg(0, 0);
	pDC->SetWindowOrg(0, 0);
	// The window is the logical size of the course map
	CSize current_extent = pDC->GetWindowExt();
	CSize window_extent = pDC->SetWindowExt(m_sizeTotal.cx, m_sizeTotal.cy);

	this->GetClientRect(&window_rect);
	// The viewport is the size of the client window.
	pDC->SetViewportExt(window_rect.right - window_rect.left, window_rect.bottom - window_rect.top);

}

void CDogRunView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;	

	CRect inval_rect;
	if (this->m_dead_flag == TIME_EXPIRED) {
		RegisterDlg dlgReg;	
		dlgReg.DoModal();
		return;
	}

	CClientDC dc(this);	
	HCURSOR hCursor;
	CPoint sp = this->GetScrollPosition();
	CRallyObject* pRallyItem;
	PylonObj* pPylonItem;
	PylonObj *pPylonInList;
	SpecialObj *pSpecialItem, *pSpecialItemInList;
	TextObj *pTextInList;
	ASSERT_VALID(pDoc);
	CPoint old_point;
	CPoint off_set_pt(1,1);
	old_point = point;
	if (this->m_size_to_fit) {
		this->ChangeDCToSizeToWindow(&dc);
		dc.DPtoLP(&point);
	}
		
	point.y += sp.y;
	point.x += sp.x;
	
	this->m_XPos = point.x;
	this->m_YPos = point.y;

	
	POSITION pos;
	BOOL selected = false;
	// text edit mode termination
	if (this->m_text_editing && this->mp_edit_dlg != NULL) {// kill the editor
		this->mp_edit_dlg->DestroyWindow();
		delete this->mp_edit_dlg;
		this->mp_edit_dlg = NULL;
		this->Invalidate(FALSE);
		POSITION text_pos;
		text_pos = pDoc->m_text_list.Find(this->mp_textobj);
		if (text_pos != NULL && !this->m_in_text_box) {
			pDoc->AddUndoStation(this->mp_textobj,text_pos,ADD_STATION);
		}
		this->m_text_editing = this->m_in_text_box = false;
		this->mp_textobj = NULL;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();
	}

	int selection_status, pylon_selected, text_selected, special_selected;
	special_selected = text_selected = pylon_selected = selection_status = NOT_SELECTED;
	this->m_rotate_station = false;
	if (this->m_SelectedShapeOnToolBar == ID_EDIT_TEXT) {
		this->DisplayEditDialog(&point,&point, true);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
	if (this->m_SelectedShapeOnToolBar != ID_TABLE_TOOL && this->m_SelectedShapeOnToolBar != ID_GATE_TOOL && this->m_SelectedShapeOnToolBar != ID_LEASH_TOOL && 
		  this->m_SelectedShapeOnToolBar != ID_JUMP_TOOL && this->m_SelectedShapeOnToolBar != ID_BR_JUMP_TOOL && this->m_SelectedShapeOnToolBar != ID_EDIT_TEXT && 
		    this->m_SelectedShapeOnToolBar != GRABARROW && this->m_SelectedShapeOnToolBar !=  ID_PYLONS && 
		    this->m_SelectedShapeOnToolBar != ID_OFFSET_3A && this->m_SelectedShapeOnToolBar !=  ID_OFFSET_3B && 
		    this->m_SelectedShapeOnToolBar != ID_SPIRAL_LT && this->m_SelectedShapeOnToolBar != ID_SERP_PATTERN &&
			this->m_SelectedShapeOnToolBar != ID_FIG8_PATTERN &&
		    this->m_SelectedShapeOnToolBar != ID_SPIRAL_RT_1A && this->m_SelectedShapeOnToolBar !=  ID_SPIRAL_RT_1B && 
			this->m_SelectedShapeOnToolBar != ID_ARROW_TOOL && this->m_SelectedShapeOnToolBar != ID_LINE_TOOL &&
			this->m_SelectedShapeOnToolBar != ID_SCRIBBLE_TOOL && this->m_SelectedShapeOnToolBar != ID_BONE) {
		pRallyItem = pDoc->m_rallyList.CreateRallyStation(this->m_SelectedShapeOnToolBar, this->m_type_course, this->m_XPos, this->m_YPos);
		pRallyItem->SetStationRect(pDoc->m_station_size, pDoc->m_pixels_per_foot_ht, pDoc->m_pixels_per_foot_wd);
		pDoc->m_course_info->GetCourseInfo(&course_info);
		pRallyItem->SetStationDescription(course_info.m_stat_desc);
		pRallyItem->SetRotateText(course_info.m_do_rotate_text);
	}
// special objects
	if (this->m_SelectedShapeOnToolBar == ID_JUMP_TOOL) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_JUMP_TOOL);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
		this->m_SelectedShapeOnToolBar = GRABARROW;
	}
	if (this->m_SelectedShapeOnToolBar == ID_BR_JUMP_TOOL) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_BR_JUMP_TOOL);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
		this->m_SelectedShapeOnToolBar = GRABARROW;
	}
	if (this->m_SelectedShapeOnToolBar == ID_LEASH_TOOL) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_LEASH_TOOL);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_GATE_TOOL) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_GATE_TOOL);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_BONE) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_BONE);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_TABLE_TOOL) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_TABLE_TOOL);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_OFFSET_3A) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_OFFSET_3A);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_SERP_PATTERN) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_SERP_PATTERN);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_FIG8_PATTERN) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_FIG8_PATTERN);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_SPIRAL_LT) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_SPIRAL_LT);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_SPIRAL_RT_1A) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_SPIRAL_RT_1A);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	if (this->m_SelectedShapeOnToolBar == ID_SPIRAL_RT_1B) {
		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_SPIRAL_RT_1B);
		pos = pDoc->m_special_list.AddHead(pSpecialItem);
		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}


// drawn arrows
	if (this->m_SelectedShapeOnToolBar == ID_ARROW_TOOL || this->m_SelectedShapeOnToolBar == ID_LINE_TOOL) {
		this->m_create_arrow = true;
		this->m_int_drag = point;
		if (this->m_SelectedShapeOnToolBar == ID_LINE_TOOL) {
			this->m_create_line = true;
		}
//		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
// free hand line drawing 
	if (this->m_SelectedShapeOnToolBar == ID_SCRIBBLE_TOOL) {
		this->m_create_scribble = true;
		LOGPEN *default_pen;
		default_pen = pDoc->GetDefaultPen();
		this->mp_created_scribble = new Scribble(default_pen);
		mp_created_scribble->m_pointArray.Add(point);
		this->m_int_drag  = this->m_ptPrev = old_point;  
//		this->m_SelectedShapeOnToolBar = GRABARROW;
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	}
// pylons
	if (this->m_SelectedShapeOnToolBar == ID_PYLONS) {
// pylons  rotating and resizing .
//		pSpecialItem = new SpecialObj(this->m_XPos, this->m_YPos, IDB_PYLONS);
//		pos = pDoc->m_special_list.AddHead(pSpecialItem);
//		pDoc->AddUndoStation(pSpecialItem,pos,ADD_STATION);
// do not rotate pylons use the following three lines...
		pPylonItem = new PylonObj(this->m_XPos,this->m_YPos);
		pos = pDoc->m_pylonList.AddHead(pPylonItem);
		pDoc->AddUndoStation(pPylonItem,pos,ADD_STATION);
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	}
	
	if (this->m_SelectedShapeOnToolBar != GRABARROW && this->m_SelectedShapeOnToolBar != ID_PYLONS) {
		int num_stations = pDoc->GetNumberStations();

		this->Invalidate(FALSE);
		// update data in document ID__DRAW_CALLTOHEEL
		if (this->m_SelectedShapeOnToolBar == ID_DRAW_START) {
			pRallyItem->SetStationNumber(START_STATION);
			pos = pDoc->InsertStationIntoList(pRallyItem, START_STATION, false);
		}
		else if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH) {
			pRallyItem->SetStationNumber(FINISH_STATION);
			pos = pDoc->InsertStationIntoList(pRallyItem, FINISH_STATION, false);

		}

//		else if (this->m_SelectedShapeOnToolBar == ID__DRAW_CALLTOHEEL) {
//			pRallyItem->SetStationNumber(CALL_TO_HEEL_STATION);
//			pos = pDoc->InsertStationIntoList(pRallyItem, CALL_TO_HEEL_STATION, false);
//		}
		else if (this->m_SelectedShapeOnToolBar == ID_DRAW_HONOR && false){
			if (this->m_number_honor) {
				pRallyItem->SetStationNumber(num_stations + 1);
			}
			else {
				pRallyItem->SetStationNumber(HONOR_STATION);
			}

			pos = pDoc->InsertStationIntoList(pRallyItem, HONOR_STATION, false);

		}
		else {
			num_stations++;
			pos = pDoc->InsertStationIntoList(pRallyItem, num_stations, false);
		}
		if (pos == NULL) { 
			delete pRallyItem;
			CScrollView::OnLButtonDown(nFlags, point);
			return;
		}
		BOOL station_moved = false;
		this->AddStationToSelectedList(pRallyItem);
		while(this->CheckRallyRectInRallyRect(pRallyItem)) {
			station_moved = true;
			pRallyItem->OffSetStationRect(&off_set_pt);
			off_set_pt.Offset(1,1);
		}
		pDoc->ClearRedoList();

		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
		pDoc->AddUndoStation(pRallyItem,pos,ADD_STATION);
		if (station_moved) {
			pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());
		}
		selection_status = SELECTED;
	}
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FAST || this->m_SelectedShapeOnToolBar == ID_DRAW_SLOW || this->m_SelectedShapeOnToolBar == ID_DRAW_FAST_SIT) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_DRAW_NORMAL;
			this->OnLButtonDown(nFlags, old_point);
		}
	}
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_STANDWALK && this->m_type_course == APDT_COURSE) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_RETURN_STAND;
			this->OnLButtonDown(nFlags, old_point);
		}
	}
	if (this->m_SelectedShapeOnToolBar == ID_RECALL_LEAVE) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_TURN_FRONT;
			this->OnLButtonDown(nFlags, old_point);
		}
	}
	if (this->m_SelectedShapeOnToolBar == ID_TURN_FRONT || this->m_SelectedShapeOnToolBar == ID_FRONT_RUN) {
		if (this->m_add_normal) {
			SelectFinishDlg selectFinish;
			int response = selectFinish.DoModal();
			if (response == IDOK ) this->m_SelectedShapeOnToolBar = ID_FINISH_RIGHT;
			else this->m_SelectedShapeOnToolBar = ID_FINISH_LEFT;
			this->OnLButtonDown(nFlags, old_point);
		}
	}

	if (this->m_SelectedShapeOnToolBar == ID_MOVE_STAND_LEAVE) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_MOVE_STAND_LEAVE_TWO;
			this->OnLButtonDown(nFlags, old_point);
		}
	}
	if (this->m_SelectedShapeOnToolBar == ID_MOVE_STAND_SIT_FINISH) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_MOVE_STAND_SIT_FINISH_TWO;
			this->OnLButtonDown(nFlags, old_point);
		}
	}
	if (this->m_SelectedShapeOnToolBar == ID_JUMP_RECALL) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_JUMP_RECALL_TWO;
			this->OnLButtonDown(nFlags, old_point);
		}
	}
	if (this->m_SelectedShapeOnToolBar == ID_JUMP_LEAVE) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_JUMP_LEAVE_TWO;
			this->OnLButtonDown(nFlags, old_point);
		}
	}	
	if (this->m_SelectedShapeOnToolBar == ID_DOWN_RECALL) {
		if (this->m_add_normal) {
			this->m_SelectedShapeOnToolBar = ID_DOWN_RECALL_TWO;
			this->OnLButtonDown(nFlags, old_point);
		}
	}	
		
	// set back to grabber arrow
	this->OnSelectarrow();
	pDoc->SetModifiedFlag();

	if (this->m_SelectedShapeOnToolBar == GRABARROW) {
	
		CRallyObject  *pRallyItemInlist;
		pos = pDoc->m_rallyList.GetHeadPosition();

		BOOL quit_loop = false;
		// check to see if in station list
		if (pDoc->m_station_list->ViewStationList() && pDoc->m_station_list->PointInStationListRect(&point)) {			
			this->ClearAllStationsFromSelectedList(true);
			quit_loop = true;
			this->m_do_the_drag = this->m_drag_station_list =  selected = true;
			this->m_drag_info = pDoc->m_course_info->PointInCourseInfoRect(&point);
			this->SetupTrackerRect(&dc, &point);
			hCursor = AfxGetApp()->LoadCursor(IDC_HAND_GRAB);
			if (hCursor != NULL)  SetCursor(hCursor);
			return;
		}
		// check to see if in course information
		if (pDoc->m_course_info->ViewCourse() && pDoc->m_course_info->PointInCourseInfoRect(&point)) {			
			this->ClearAllStationsFromSelectedList(true);
			quit_loop = true;
			this->m_do_the_drag = this->m_drag_info =  selected = true;
			this->SetupTrackerRect(&dc, &point);
			hCursor = AfxGetApp()->LoadCursor(IDC_HAND_GRAB);
			if (hCursor != NULL)  SetCursor(hCursor);
			return;
		}


		if (!selected) {
//			this->m_line_hit = pDoc->m_arrowList.CheckForLineHit(&point, &dc, nFlags &MK_SHIFT);
			selection_status = pDoc->m_arrowList.CheckForLineHit(&point, &dc, nFlags &MK_SHIFT);
			switch (selection_status) {
			case SELECTED:
				this->m_line_hit = LINE_HIT;
				break;
			case ALL_READY_SELECTED:
				this->m_line_hit = NO_HIT;
			case NO_HIT:
				this->m_line_hit = NO_HIT;
				break;
			default:
				this->m_line_hit = selection_status;
				break;
			}
//			if (selection_status == SELECTED) 
//				this->m_line_hit = LINE_HIT;
//			if (selection_status != SELECTED || selection_status != ALL_READY_SELECTED || selection_status != NO_HIT) 
//				this->m_line_hit = selection_status;
			
		}
		if (!selected && this->m_line_hit) {
			if (this->m_line_hit == LINE_HIT) {
				this->m_move_line = true;
			}
			selected = true;
			this->m_do_the_drag = true;
			this->m_int_drag = point;
			if (!(nFlags &MK_SHIFT)) {
				this->ClearAllStationsFromSelectedList(false);
			}
	
			if (this->m_size_to_fit) {
				dc.LPtoDP(&this->m_int_drag);
			}
		}

  // this loop finds first station in list w/hit, and marks selected list per shift key and hit status
		while(pos != NULL && !quit_loop && !selected) {
			this->m_drag_info = this->m_drag_station_list = false;
			pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
			
			selection_status = pRallyItemInlist->HitPointInStationRect(&point);
			inval_rect = pRallyItemInlist->GetStationRect();
			inval_rect.InflateRect(15,15);
			this->InvalidateRect(&inval_rect,FALSE);

			if (selection_status == SELECTED && !(nFlags &MK_SHIFT)) {
				this->ClearAllStationsFromSelectedList(true);
				this->AddStationToSelectedList(pRallyItemInlist);
				quit_loop = true;
				selected = true;
			}
			if (selection_status == SELECTED && (nFlags &MK_SHIFT)) {
				this->AddStationToSelectedList(pRallyItemInlist);
				quit_loop = true;
				selected = true;

			}
			if (selection_status == ALL_READY_SELECTED && !(nFlags &MK_SHIFT)) {
				quit_loop = true;
				selected = true;
			}
			if (selection_status == ALL_READY_SELECTED && (nFlags &MK_SHIFT)) {
				this->RemoveStationFromSelectedList(pRallyItemInlist);
				quit_loop = true;
				selected = false;
			}
		}
		// see if hit in pylon list
		pos = pDoc->m_pylonList.GetHeadPosition();
		quit_loop = false;
		while(pos != NULL && !quit_loop && !selected) {
			this->m_drag_info = this->m_drag_station_list = false;
			pPylonInList = (PylonObj*)pDoc->m_pylonList.GetNext(pos);
			
			pylon_selected = pPylonInList->MousePointInPylonRect(&point);
			inval_rect = pPylonInList->GetPylonRect(&inval_rect);
			inval_rect.InflateRect(15,15);
			this->InvalidateRect(&inval_rect,FALSE);

			if (pylon_selected == SELECTED && !(nFlags &MK_SHIFT)) {
				this->ClearAllStationsFromSelectedList(true);
				this->AddPylonToSelectedList(pPylonInList);
				quit_loop = true;
				selected = true;
			}
			if (pylon_selected == SELECTED && (nFlags &MK_SHIFT)) {
				this->AddPylonToSelectedList(pPylonInList);
				quit_loop = true;
				selected = true;

			}
			if (pylon_selected == ALL_READY_SELECTED && !(nFlags &MK_SHIFT)) {
				quit_loop = true;
				selected = true;
			}
			if (pylon_selected == ALL_READY_SELECTED && (nFlags &MK_SHIFT)) {
				this->RemovePylonFromSelectedList(pPylonInList);
				quit_loop = true;
				selected = false;
			}
		}
		// see if hit in scribble list
		Scribble *pScribbleInList;
		int scribble_selected = NOT_SELECTED;
		pos = pDoc->m_scribbleList.GetHeadPosition();
		quit_loop = false;
		while(pos != NULL && !quit_loop && !selected) {
			this->m_drag_info = this->m_drag_station_list = false;
			pScribbleInList = (Scribble*)pDoc->m_scribbleList.GetNext(pos);
			
			scribble_selected = pScribbleInList->HitPointInScribbleRect(&point);
			inval_rect = pScribbleInList->GetScribbleRect();
			inval_rect.InflateRect(15,15);
			this->InvalidateRect(&inval_rect,FALSE);

			if (scribble_selected == SELECTED && !(nFlags &MK_SHIFT)) {
				this->ClearAllStationsFromSelectedList(true);
				this->AddScribbleToSelectedList(pScribbleInList);
				quit_loop = true;
				selected = true;
			}
			if (scribble_selected == SELECTED && (nFlags &MK_SHIFT)) {
				this->AddScribbleToSelectedList(pScribbleInList);
				quit_loop = true;
				selected = true;

			}
			if (scribble_selected == ALL_READY_SELECTED && !(nFlags &MK_SHIFT)) {
				quit_loop = true;
				selected = true;
			}
			if (scribble_selected == ALL_READY_SELECTED && (nFlags &MK_SHIFT)) {
				this->RemoveScribbleFromSelectedList(pScribbleInList);
				quit_loop = true;
				selected = false;
			}
		}		
		// see if hit in text list
		pos = pDoc->m_text_list.GetHeadPosition();
		quit_loop = false;
		this->m_in_text_box = false;

		while(pos != NULL && !quit_loop && !selected) {
			this->m_drag_info = this->m_drag_station_list = false;
			pTextInList = (TextObj*)pDoc->m_text_list.GetNext(pos);
			
			text_selected = pTextInList->MousePtInTextRect(&point);

			if (text_selected == SELECTED && !(nFlags &MK_SHIFT)) {
				this->ClearAllStationsFromSelectedList(true);
				this->AddTextToSelectedList(pTextInList);
				quit_loop = true;
				selected = true;
				this->m_in_text_box = true;
			}
			if (text_selected == SELECTED && (nFlags &MK_SHIFT)) {
				this->AddTextToSelectedList(pTextInList);
				quit_loop = true;
				selected = true;
				this->m_in_text_box = true;

			}
			if (text_selected == ALL_READY_SELECTED && !(nFlags &MK_SHIFT)) {
				quit_loop = true;
				selected = true;
				this->m_in_text_box = true;
			}
			if (text_selected == ALL_READY_SELECTED && (nFlags &MK_SHIFT)) {
				this->RemoveTextFromSelectedList(pTextInList);
				quit_loop = true;
				selected = false;
				this->m_in_text_box = false;
			}
		}
		// see if hit in special list
		pos = pDoc->m_special_list.GetHeadPosition();
		quit_loop = false;

		while(pos != NULL && !quit_loop && !selected) {
			this->m_drag_info = this->m_drag_station_list = false;
			pSpecialItemInList = (SpecialObj*)pDoc->m_special_list.GetNext(pos);
			
			special_selected = pSpecialItemInList->MousePointInSpecialRect(&point);

			if (special_selected == SELECTED && !(nFlags &MK_SHIFT)) {
				this->ClearAllStationsFromSelectedList(true);
				this->AddSpecialToSelectedList(pSpecialItemInList);
				quit_loop = true;
				selected = true;
			}
			if (special_selected == SELECTED && (nFlags &MK_SHIFT)) {
				this->AddSpecialToSelectedList(pSpecialItemInList);
				quit_loop = true;
				selected = true;

			}
			if (special_selected == ALL_READY_SELECTED && !(nFlags &MK_SHIFT)) {
				quit_loop = true;
				selected = true;
			}
			if (special_selected == ALL_READY_SELECTED && (nFlags &MK_SHIFT)) {
				this->RemoveSpecialFromSelectedList(pSpecialItemInList);
				quit_loop = true;
				selected = false;
			}
		}		

		int which_handle = this->IsRotateHandleSelected();
		if (selected && !which_handle) {
			this->SetupTrackerRect(&dc, &point);
			this->m_do_the_drag = true;
			hCursor = AfxGetApp()->LoadCursor(IDC_HAND_GRAB);
			if (hCursor != NULL)  SetCursor(hCursor);			
		}
		if (selected && which_handle) {
			hCursor = AfxGetApp()->LoadCursor(IDC_SELECT_ROTATE);
			if (hCursor != NULL)  SetCursor(hCursor);	
			if (which_handle == TOP_RIGHT) {
				if (special_selected) this->m_rotate_special = true;
				else this->m_rotate_station = true;
			}
			if (which_handle == BOTTOM_RIGHT) {
				if (special_selected) this->m_resize_special = true;
				else this->m_resize_station = true;
			}

			pDoc->SetModifiedFlag();
			pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
		}
		if (!selected && !(nFlags &MK_SHIFT)) {
			this->ClearAllStationsFromSelectedList(true);
		}

		if (this->m_line_hit == NO_HIT && selection_status == NOT_SELECTED && pylon_selected == NOT_SELECTED 
				&& text_selected == NOT_SELECTED && special_selected ==NOT_SELECTED && scribble_selected == NOT_SELECTED) {
			this->ClearAllStationsFromSelectedList(true);
//			selected = false;
		}

		if (!selected) {
			point.y -= sp.y;
			point.x -= sp.x;
			CRect rect(point.x, point.y, point.x, point.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);
			this->m_do_the_drag = false;
			this->m_last_drag_rect.left = NULL;
			m_select_rect_top_left = m_select_rect_botom_right = point;
			m_drag_select = true;
//		CString temp_string;
//		temp_string.Format("Select Rect top: %d, left: %d,bottom: %d right: %d",m_select_rect_top_left.y, m_select_rect_top_left.x, m_select_rect_botom_right.y, m_select_rect_botom_right.x);
//		dc.TextOut(10,40,temp_string);

//			this->ClearAllStationsFromSelectedList(true);
		}
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CDogRunView::OnSelectarrow() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = GRABARROW;	
}

void CDogRunView::OnUpdateSelectarrow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == GRABARROW) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);

}

void CDogRunView::SetupTrackerRect(CDC *pDC, CPoint *point)
{
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect course_info_rect;

	int top, left, bottom, right;
	RECT station_rect;
	CRect pylon_rect;
	CRect text_rect;
	CRect special_rect;
	CRect scribble_rect;
	POSITION pos;
	CRallyObject *pRallyObjectInSelectList;
	PylonObj *pPylonObjectInSelectList;
	TextObj* pTextObjectInSelectList;
	SpecialObj* pSpecialObjectInSelectList;
	Scribble* pScribbleObjectInSelectList;
	right = bottom = -1;
	top = left = 30000;
	if (this->m_drag_info) {
		pDoc->m_course_info->GetCourseInfoRect(&course_info_rect);
		left = course_info_rect.left;
		top = course_info_rect.top;
		bottom = course_info_rect.bottom;
		right = course_info_rect.right;	
	}
	else if(this->m_drag_station_list){
		pDoc->m_station_list->GetStationListRect(&course_info_rect);
		left = course_info_rect.left;
		top = course_info_rect.top;
		bottom = course_info_rect.bottom;
		right = course_info_rect.right;	
	}
	else {
		for( pos = this->m_stations_selected.GetHeadPosition(); pos != NULL; ) {
			pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetNext(pos);
			station_rect = pRallyObjectInSelectList->GetStationRect();
			if (station_rect.left < left) left = station_rect.left;
			if (station_rect.top < top) top = station_rect.top;
			if (station_rect.bottom > bottom) bottom = station_rect.bottom;
			if (station_rect.right > right) right = station_rect.right;
		}	
		for( pos = this->m_pylons_selected.GetHeadPosition(); pos != NULL; ) {
			pPylonObjectInSelectList = (PylonObj*)this->m_stations_selected.GetNext(pos);
			pPylonObjectInSelectList->GetPylonRect(&pylon_rect);
			if (pylon_rect.left < left) left = pylon_rect.left;
			if (pylon_rect.top < top) top = pylon_rect.top;
			if (pylon_rect.bottom > bottom) bottom = pylon_rect.bottom;
			if (pylon_rect.right > right) right = pylon_rect.right;
		}
		for( pos = this->m_text_selected.GetHeadPosition(); pos != NULL; ) {
			pTextObjectInSelectList = (TextObj*)this->m_text_selected.GetNext(pos);
			pTextObjectInSelectList->GetDisplayTextRect(&text_rect);
			if (text_rect.left < left) left = text_rect.left;
			if (text_rect.top < top) top = text_rect.top;
			if (text_rect.bottom > bottom) bottom = text_rect.bottom;
			if (text_rect.right > right) right = text_rect.right;
		}
		for( pos = this->m_special_selected.GetHeadPosition(); pos != NULL; ) {
			pSpecialObjectInSelectList = (SpecialObj*)this->m_special_selected.GetNext(pos);
			pSpecialObjectInSelectList->GetSpecialRect(&special_rect);
			if (special_rect.left < left) left = special_rect.left;
			if (special_rect.top < top) top = special_rect.top;
			if (special_rect.bottom > bottom) bottom = special_rect.bottom;
			if (special_rect.right > right) right = special_rect.right;
		}
		for( pos = this->m_scribble_selected.GetHeadPosition(); pos != NULL; ) {
			pScribbleObjectInSelectList = (Scribble*)this->m_scribble_selected.GetNext(pos);
			scribble_rect = pScribbleObjectInSelectList->m_rectBounding;
			if (scribble_rect.left < left) left = scribble_rect.left;
			if (scribble_rect.top < top) top = scribble_rect.top;
			if (scribble_rect.bottom > bottom) bottom = scribble_rect.bottom;
			if (scribble_rect.right > right) right = scribble_rect.right;
		}
	}
	m_drag_rect.top = top;
	m_drag_rect.left = left;
	m_drag_rect.right = right;
	m_drag_rect.bottom = bottom;
	if (this->m_size_to_fit) {
		this->FixRectInFitScreenModeLPtoDP(&m_drag_rect,pDC);
	}
	this->m_last_drag_rect.left = NULL;
	this->m_int_drag.x = this->m_last_drag.x = point->x;
	this->m_int_drag.y = this->m_last_drag.y = point->y;
	if (this->m_size_to_fit) {
		pDC->LPtoDP(&this->m_int_drag);
		pDC->LPtoDP(&this->m_last_drag);
	}

}

void CDogRunView::DeSelectAllStations(bool include_arrows) {
	POSITION pos;
	CRallyObject* pRallyItemInlist;
	PylonObj* pPylonItemInList;
	TextObj* pTextItemInList;
	SpecialObj* pSpecialItemInList;
	Scribble* pScribbleItemInList;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
		pRallyItemInlist->SetSelectedFlag(false);
	}
	for( pos = pDoc->m_pylonList.GetHeadPosition(); pos != NULL; ) {
		pPylonItemInList = (PylonObj*)pDoc->m_pylonList.GetNext(pos);
		pPylonItemInList->SetSelectedFlag(false);
	}
	for( pos = pDoc->m_text_list.GetHeadPosition(); pos != NULL; ) {
		pTextItemInList = (TextObj*)pDoc->m_text_list.GetNext(pos);
		pTextItemInList->SetSelectedFlag(false);
	}
	for( pos = pDoc->m_special_list.GetHeadPosition(); pos != NULL; ) {
		pSpecialItemInList = (SpecialObj*)pDoc->m_special_list.GetNext(pos);
		pSpecialItemInList->SetSelectedFlag(false);
	}
	for( pos = pDoc->m_scribbleList.GetHeadPosition(); pos != NULL; ) {
		pScribbleItemInList = (Scribble*)pDoc->m_scribbleList.GetNext(pos);
		pScribbleItemInList->SetSelectedFlag(false);
	}
	if (include_arrows) pDoc->m_arrowList.UnselectAllArrows();

}
void CDogRunView::FixRectInFitScreenModeLPtoDP(RECT *rect) {
	CClientDC dc(this);

	CPoint top_left, bottom_right;
	top_left.x = rect->left;
	top_left.y = rect->top;
	dc.LPtoDP(&top_left);
	rect->left = top_left.x;
	rect->top = top_left.y;

	bottom_right.x = rect->right;
	bottom_right.y = rect->bottom;
	dc.LPtoDP(&bottom_right);
	rect->right = bottom_right.x;
	rect->bottom = bottom_right.y;

}
void CDogRunView::FixRectInFitScreenModeLPtoDP(RECT *rect, CDC *pDC) {
	CPoint top_left, bottom_right;
	top_left.x = rect->left;
	top_left.y = rect->top;
	pDC->LPtoDP(&top_left);
	rect->left = top_left.x;
	rect->top = top_left.y;

	bottom_right.x = rect->right;
	bottom_right.y = rect->bottom;
	pDC->LPtoDP(&bottom_right);
	rect->right = bottom_right.x;
	rect->bottom = bottom_right.y;

}
void CDogRunView::FixRectInFitScreenModeDPtoLP(RECT *rect, CDC *pDC) {
	CPoint top_left, bottom_right;
	top_left.x = rect->left;
	top_left.y = rect->top;
	pDC->DPtoLP(&top_left);
	rect->left = top_left.x;
	rect->top = top_left.y;

	bottom_right.x = rect->right;
	bottom_right.y = rect->bottom;
	pDC->DPtoLP(&bottom_right);
	rect->right = bottom_right.x;
	rect->bottom = bottom_right.y;
}
// Doesn't work with a flipp need to fix!!! -rck
BOOL CDogRunView::AutoScrollWindow(CPoint *p_point, CRect *p_win_rect) {
	if (this->m_size_to_fit) return false;
	CPoint sp = this->GetScrollPosition();
	CPoint top_left, bottom_right;
	CRect invalid_rect;
    CPoint size = GetDeviceScrollPosition ();
	BOOL scroll;
	invalid_rect = this->m_drag_rect;
	invalid_rect.InflateRect(20,20);
	scroll = this->m_auto_scroll;

	if (p_point->y > p_win_rect->bottom - 5) {
		sp.y += 20;
		this->ScrollToPosition(sp);
		this->m_auto_scroll = true;

	}
	else scroll = false;
	return scroll;;
	
	
	if (p_point->x > p_win_rect->right - 20) {
		sp.x += 20;
		this->ScrollToPosition(sp);

		this->m_auto_scroll = true;
	}
	else scroll = false;
	if (p_point->x < p_win_rect->left + 20) {
		sp.x -= 20;
		this->ScrollToPosition(sp);

		this->m_auto_scroll = true;

	}
	else scroll = false;



	if (p_point->y < p_win_rect->top + 20) {
		sp.y -= 20;
		this->ScrollToPosition(sp);

		this->m_auto_scroll = true;
	}
	else scroll = false;

	
}
void CDogRunView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRallyObject* pRallyItemInlist;
	PylonObj *pPylonItemInList;
	SpecialObj *pSpecialItemInList;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClientDC dc(this);
	CRect win_rect;
	CRect invalid_rect;
	this->GetClientRect(&win_rect);
	POSITION pos;
	HCURSOR hCursor;
	int where_in_rect;
	CPoint sp = this->GetScrollPosition();
	CPoint old_point;
	bool left_button_down = nFlags &MK_LBUTTON;


	old_point = point;

	point.y += sp.y;
	point.x += sp.x;

	if (!left_button_down) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}

		if (this->m_SelectedShapeOnToolBar == ID_SELECTARROW) { // needs to be GRABARROW to work, don't like this slows down too much!
			for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
				pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
				where_in_rect = pRallyItemInlist->MousePointInStationRect(&point);	
				if (pRallyItemInlist->GetSelectedFlag()) {	
					if (where_in_rect == IN_RECT) {
						hCursor = AfxGetApp()->LoadCursor(IDC_HAND_OPEN);
					}
					if (where_in_rect == IN_HANDLE  && this->m_advanced_mode) {
						hCursor = AfxGetApp()->LoadCursor(IDC_ROTATE);
					}
					if (hCursor != NULL)  SetCursor(hCursor);
				}

			}

			for( pos = pDoc->m_pylonList.GetHeadPosition(); pos != NULL; ) {
				pPylonItemInList = (PylonObj*)pDoc->m_pylonList.GetNext(pos);
				if (pPylonItemInList->GetSelectedFlag()) {	
					if (pPylonItemInList->MousePointInPylonRect(&point)) {
						hCursor = AfxGetApp()->LoadCursor(IDC_HAND_OPEN);
					}
					if (hCursor != NULL)  SetCursor(hCursor);
				}

			}

		}
	}

		// need to add the drag stuff here	
	if (!(this->m_line_hit == NO_HIT || this->m_line_hit == LINE_HIT)) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}
		if (!this->m_curving_line) {
			this->m_curving_line = true;
			int how_many_stations = 1;
			pDoc->m_arrowList.AddSelectedArrowsToUndoList(&pDoc->m_undo_list,MOVE_STATION, &how_many_stations, 0);
		}
		pDoc->m_arrowList.CurveLine(&dc,&point, this->m_size_to_fit);					
		this->Invalidate(FALSE);
	}

	if (this->m_line_hit == LINE_HIT) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&old_point);
		}
		CPoint amt_changed;
		if (!(this->m_int_drag == point)) {
			if (!this->m_dragging_line ) {
				amt_changed.x = point.x - this->m_int_drag.x;
				amt_changed.y = point.y - this->m_int_drag.y ;
				this->m_dragging_line = true;
				int how_many_stations = 1;
				pDoc->m_arrowList.AddSelectedArrowsToUndoList(&pDoc->m_undo_list,MOVE_STATION, &how_many_stations, 0);
				this->m_int_drag = old_point;
			}
			else {
				amt_changed.x = old_point.x - this->m_int_drag.x;
				amt_changed.y = old_point.y - this->m_int_drag.y ;
				this->m_int_drag = old_point;
			}
			pDoc->m_arrowList.MoveSelectedArrows(&amt_changed);
//			this->m_int_drag = point;
			this->Invalidate(FALSE);
		}
	}
	if (left_button_down && this->m_create_scribble) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}
		this->Invalidate(FALSE);

		mp_created_scribble->m_pointArray.Add(point);

		// Draw a line from the previous detected point in the mouse
		// drag to the current point.
//		dc.MoveTo(m_ptPrev);
//		dc.LineTo(old_point);
		m_ptPrev = old_point;
	}
	if (left_button_down && this->m_create_arrow) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}
		if (!this->m_creating_arrow) {
			mp_created_arrow = new ArrowObj(&point, &point, pDoc->GetDefaultPen(), NO_OWNER, NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), this->m_create_line);
			this->m_creating_arrow = true;
		}
		else {
			this->Invalidate(FALSE);
			CPoint exit_point, entry_point;
			exit_point = this->mp_created_arrow->GetExitPoint();
			entry_point = this->mp_created_arrow->GetEntryPoint();
			this->mp_created_arrow->SetEntryPoint(&point);
		}
	}
	if (left_button_down && this->m_resize_station) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}

		if (this->m_stations_selected.GetCount() > 1 ) {
			MessageBox("YOU CAN ONLY RESIZE ONE STATION AT AT TIME!",NULL,MB_OK);
			return;
		}
		pos = this->m_stations_selected.GetHeadPosition();
		if (pos == NULL) {
			CScrollView::OnMouseMove(nFlags, point);
			return;
		}
		pRallyItemInlist = (CRallyObject*)this->m_stations_selected.GetHead();
		if (!this->m_resizing_station) { // first time here, set is resizing flag and set-up undo station
			this->m_resizing_station = true;
			pos = pDoc->m_rallyList.Find(pRallyItemInlist,NULL);
			pDoc->ClearRedoList();
			pDoc->AddUndoStation(pRallyItemInlist,pos,ROTATE_STATION);
		}
		pRallyItemInlist->ResizeStation(&point);
		invalid_rect = pRallyItemInlist->GetStationRect();
		OffsetRect(&invalid_rect,-sp.x, -sp.y);
		dc.DrawFocusRect(&invalid_rect);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&invalid_rect,&dc);
		}
	}
	if (left_button_down && this->m_resize_special) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}

		if (this->m_special_selected.GetCount() > 1 ) {
			MessageBox("YOU CAN ONLY RESIZE ONE OBJECT AT AT TIME!",NULL,MB_OK);
			return;
		}
		pos = this->m_special_selected.GetHeadPosition();
		if (pos == NULL) {
			CScrollView::OnMouseMove(nFlags, point);
//			this->MessageBox("NOTHING SELECTED!","ERROR",MB_OK);
			return;
		}
		pSpecialItemInList = (SpecialObj*)this->m_special_selected.GetHead();
		if (!this->m_resizing_special) { // first time here, set is resizing flag and set-up undo station
			this->m_resizing_special = true;
			pDoc->ClearRedoList();
			pos = pDoc->m_special_list.Find(pSpecialItemInList,NULL);
			pDoc->AddUndoStation(pSpecialItemInList,pos,ROTATE_STATION);
		}
		pSpecialItemInList->ResizeSpecial(&point);
		pSpecialItemInList->GetSpecialRect(&invalid_rect);
		OffsetRect(&invalid_rect,-sp.x, -sp.y);
		dc.DrawFocusRect(&invalid_rect);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&invalid_rect,&dc);
		}
	}
	
	if (left_button_down && (this->m_rotate_station || this->m_rotate_special)) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}

		if (this->m_rotate_station && this->m_stations_selected.GetCount() > 1 ) {
			MessageBox("YOU CAN ONLY ROTATE ONE STATION AT A TIME!",NULL,MB_OK);
			return;
		}
		if (this->m_rotate_special && this->m_special_selected.GetCount() > 1 ) {
			MessageBox("YOU CAN ONLY ROTATE ONE OBJECT AT A TIME!",NULL,MB_OK);
			return;
		}
		if (this->m_rotate_station) {
			pos = this->m_stations_selected.GetHeadPosition();
			pRallyItemInlist = (CRallyObject*)this->m_stations_selected.GetHead();
		}
		if (this->m_rotate_special) {
			pos = this->m_special_selected.GetHeadPosition();
			if (pos == NULL) {
				this->m_rotate_special = false;
				CScrollView::OnMouseMove(nFlags, point);
				return;

			}
			else {
				pSpecialItemInList = (SpecialObj*)this->m_special_selected.GetHead();
			}
		}
		if (!this->m_rotating_station && this->m_rotate_station) { // first time here, set is rotating flag and set-up undo station
			this->m_rotating_station = true;
			pos = pDoc->m_rallyList.Find(pRallyItemInlist,NULL);
			pDoc->ClearRedoList();
			pDoc->AddUndoStation(pRallyItemInlist,pos,ROTATE_STATION);
		}
		if (this->m_rotate_station) {
			pRallyItemInlist->RotateStation(&point);
			invalid_rect = pRallyItemInlist->GetStationRect();
		}
		if (!this->m_rotating_special && this->m_rotate_special) { // first time here, set is rotating flag and set-up undo station
			this->m_rotating_special = true;
			pos = pDoc->m_special_list.Find(pSpecialItemInList,NULL);
			pDoc->ClearRedoList();
			pDoc->AddUndoStation(pSpecialItemInList,pos,ROTATE_STATION);
		}
		if (this->m_rotate_special) {
			pSpecialItemInList->RotateSpecial(&point);
			pSpecialItemInList->GetSpecialRect(&invalid_rect);
			if (invalid_rect.Width() > invalid_rect.Height()) {
				int width = invalid_rect.Width();
				invalid_rect.bottom = invalid_rect.bottom + (width/2);
				invalid_rect.top = invalid_rect.top - (width/2);
			}
		}
		OffsetRect(&invalid_rect,-sp.x, -sp.y);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&invalid_rect,&dc);
		}
		if (this->m_size_to_fit) {
			InflateRect(&invalid_rect,8,13);
		}
		else {
			InflateRect(&invalid_rect,15,27);
		}

		this->InvalidateRect(&invalid_rect,false);

		return;
	}

	if (left_button_down && this->m_do_the_drag && this->m_line_hit == NO_HIT) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}
	
		if (AutoScrollWindow(&old_point, &win_rect)) {
//			Invalidate(TRUE);
			this->m_last_drag_rect.left = NULL;
		}
		else {
			this->DrawDragRectangle(&dc, &old_point);
		}

	}

	if (this->m_drag_select && this->m_line_hit == NO_HIT && !this->m_create_arrow && !this->m_create_scribble) {
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			dc.DPtoLP(&point);
		}
		point.y -= sp.y;
		point.x -= sp.x;		
		CRect rect(m_select_rect_top_left.x, m_select_rect_top_left.y, m_select_rect_botom_right.x, m_select_rect_botom_right.y);
		rect.NormalizeRect();

		dc.DrawFocusRect(rect);

		
		rect.SetRect(m_select_rect_top_left.x, m_select_rect_top_left.y, point.x, point.y);
		m_select_rect_botom_right = point;

		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
	}

	CScrollView::OnMouseMove(nFlags, point);
}
void CDogRunView::DrawDragRectangle(CDC *pDC, CPoint *pPoint) {
	int dist_x;
	int dist_y;	

	SIZE border_size;
	border_size.cx = 1;
	border_size.cy = 1;


	dist_x = pPoint->x - this->m_last_drag.x;
	dist_y = pPoint->y - this->m_last_drag.y;

	this->m_drag_rect.left = this->m_drag_rect.left + dist_x;
	this->m_drag_rect.right = this->m_drag_rect.right + dist_x;
	this->m_drag_rect.top = this->m_drag_rect.top + dist_y;
	this->m_drag_rect.bottom = this->m_drag_rect.bottom + dist_y;
	
	if (this->m_last_drag_rect.left != NULL)
		pDC->DrawDragRect(&this->m_drag_rect,border_size, &this->m_last_drag_rect,border_size, NULL, NULL);
	else 
		pDC->DrawDragRect(&this->m_drag_rect,border_size, NULL,border_size, NULL, NULL);

	this->m_last_drag_rect = this->m_drag_rect;
	this->m_last_drag.x = pPoint->x;
	this->m_last_drag.y = pPoint->y;
}
void CDogRunView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CClientDC dc(this);	
	this->CreateMyFont(&dc);
	this->SetUpCourseVariablesAndGrid();

}

void CDogRunView::DrawGrid(CDC* pDC) {

	CRect rect;
	if (this->m_rotate_station || this->m_rotate_special) return;
	COLORREF gridColor;
	if (this->m_print_grid_lines == GRID_BLACK) {
		gridColor = RGB(0, 0, 0);
	}
	else {
		gridColor = RGB(128, 128, 128);
	}
	CString spacing;
	int x, y;
	int grid_spacing = 0;
	rect.left = 10;
	rect.top = 10;
	double pixels_per_foot_wd;
	double pixels_per_grid_wd;
	double pixels_per_foot_ht;
	double pixels_per_grid_ht;

	pixels_per_foot_wd = this->m_inch_per_horiz / 1.5;	// setting for screen display is approx 1 inch = 5 ft;
	pixels_per_grid_wd = pixels_per_foot_wd * this->m_grid_spacing;
	pixels_per_foot_ht = this->m_inch_per_vert / 1.5;	// setting for screen display is 1 inch = 5 ft;
	pixels_per_grid_ht = pixels_per_foot_ht * this->m_grid_spacing;
	rect.right = (long)pixels_per_foot_wd * this->m_ring_width;
	rect.bottom = (long)pixels_per_foot_ht * this->m_ring_lenght;
	// Major unit lines

	CPen penDot;
	penDot.CreatePen(PS_DOT, 1, gridColor);
	CPen* pOldPen = pDC->SelectObject(&penDot);
//	double meter_spacing = this->m_grid_spacing * 0.3;
	for (x = rect.left ; x < rect.right; x += (int)pixels_per_grid_wd)
		{
			if (x != 0)
			{
				// vertical lines
				if (!this->m_printing) {
					pDC->MoveTo(x, rect.top);
					pDC->LineTo(x, rect.bottom);
				}

				else if (this->m_printing && m_print_grid_lines != GRID_NONE) {
					pDC->MoveTo(x, rect.top);
					pDC->LineTo(x, rect.bottom);
				}

//				spacing.Format("%.1f",grid_spacing * meter_spacing);
				spacing.Format("%.1f",grid_spacing * this->m_grid_spacing);
				pDC->TextOut(x,rect.top, spacing);
				pDC->TextOut(x,rect.bottom, spacing);
				grid_spacing++;
			}
		}
		int temp_spacing = 0;
		for (y = rect.top; y < rect.bottom; y += (int)pixels_per_grid_ht)
		{
			if (y != 0)
			{
				temp_spacing++;
			}
		}
		grid_spacing = temp_spacing;
		grid_spacing = 0;
//		for (y = rect.top; y < rect.bottom; y += (int)pixels_per_grid_ht)
		for (y = rect.bottom; y > rect.top; y -= (int)pixels_per_grid_ht)
		{
			if (y != 0)
			{
			// horiziontal lines
				if (!this->m_printing || (this->m_printing && m_print_grid_lines != GRID_NONE)) {
					pDC->MoveTo(rect.left, y);
					pDC->LineTo(rect.right, y);
				}
//				spacing.Format("%.1f",grid_spacing * meter_spacing);
				spacing.Format("%.1f",grid_spacing * this->m_grid_spacing);
				if (y != rect.bottom) pDC->TextOut(rect.right,y, spacing);
				pDC->TextOut(rect.left,y, spacing);
				grid_spacing++;
			}
		}

	// Outlines

	CPen penSolid;
	penSolid.CreatePen(PS_SOLID, 1, gridColor);
	pDC->SelectObject(&penSolid);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.left, rect.top);
//	spacing.Format("%.1f",grid_spacing * meter_spacing);
//	spacing.Format("%.1f",grid_spacing * this->m_grid_spacing);
	spacing.Format("%.1f",this->m_ring_lenght);
	pDC->TextOut(rect.right,rect.top, spacing);
	spacing.Format("%.1f",this->m_ring_width);
	pDC->TextOut(rect.right,rect.bottom, spacing);
	this->m_grid_rect = rect;
	pDC->SelectObject(pOldPen);
	DeleteObject(penSolid);
	DeleteObject(penDot);
	rect.InflateRect(50,50);
	m_bmp_save_rect = rect;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	pDoc->m_pixels_per_foot_ht = pDoc->m_station_list->m_pixels_per_foot_ht = this->m_inch_per_horiz / 5;
	pDoc->m_pixels_per_foot_wd = pDoc->m_station_list->m_pixels_per_foot_wd = this->m_inch_per_vert / 5;
	
}

BOOL  CDogRunView::CheckRallyRectInRallyRect(CRallyObject* pRallyItemToCheck) {
	CRgn rallyRectRgn;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPoint offset_point;

	CRect selectedRect = pRallyItemToCheck->GetStationRect();
	selectedRect.NormalizeRect();

//	if ((selectedRect.left < 0) || (selectedRect.top < 0)) {
//		pRallyItemToCheck->SetStationRect();
//		selectedRect = pRallyItemToCheck->GetStationRect();
//	}
	
	if (this->m_grid_rect.right < selectedRect.left) {
		offset_point = (0,0);
		offset_point.x = this->m_grid_rect.right - selectedRect.left;
		pRallyItemToCheck->OffSetStationRect(&offset_point);
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());

	}
	if (this->m_grid_rect.bottom < selectedRect.top) {
		offset_point = (0,0);
		offset_point.y = this->m_grid_rect.bottom - selectedRect.top;
		pRallyItemToCheck->OffSetStationRect(&offset_point);
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());
	}

	if (0 > selectedRect.left) {
		offset_point = (0,0);
		offset_point.x = 10 + (-selectedRect.left);
		pRallyItemToCheck->OffSetStationRect(&offset_point);
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());

	}
	if (0 > selectedRect.top) {
		offset_point = (0,0);
		offset_point.y = 10 + (-selectedRect.top);
		pRallyItemToCheck->OffSetStationRect(&offset_point);
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());
	}
	
	rallyRectRgn.CreateRectRgn(selectedRect.left,selectedRect.top,selectedRect.right,selectedRect.bottom);
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	
	for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
		if (pRallyItemToCheck != pRallyItemInlist && pRallyItemInlist->RallyRectInRegion(&rallyRectRgn)) {
			DeleteObject(rallyRectRgn);
			return true;
		}
	}
	DeleteObject(rallyRectRgn);
	return false;
}
void CDogRunView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CPoint sp = this->GetScrollPosition();
	CPoint old_point;
	old_point = point;
	point.y += sp.y;
	point.x += sp.x;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(this->m_size_to_fit) {
		this->ChangeDCToSizeToWindow(&dc);
	}
	if (this->m_resize_station || this->m_resize_special) {
		this->m_resizing_station = false;
		this->m_resize_station = false;
		this->m_resizing_special = false;
		this->m_resize_special = false;
	}
	if (this->m_rotate_station || this->m_rotate_special) { // if you were rotating now you've stopped
		this->m_rotating_station= false;
		this->m_rotate_station = false;
		this->m_rotate_special = false;
		this->m_rotating_special = false;
	}
	if (this->m_create_scribble) {
		if (this->m_int_drag == point) {
			this->m_SelectedShapeOnToolBar = GRABARROW;
			delete this->mp_created_scribble;
			this->mp_created_scribble = NULL;
			this->m_create_scribble = false;
		}
		else {
			if (this->m_size_to_fit) {
				dc.DPtoLP(&point);
			}
			this->m_create_scribble = false;
			this->m_SelectedShapeOnToolBar = GRABARROW;
			dc.MoveTo(m_ptPrev);
			dc.LineTo(old_point);
			this->mp_created_scribble->m_pointArray.Add(point);
			this->mp_created_scribble->FinishStroke();
			POSITION pos = pDoc->m_scribbleList.AddHead(this->mp_created_scribble);
			pDoc->AddUndoStation(this->mp_created_scribble,pos,ADD_STATION);
			this->AddScribbleToSelectedList(this->mp_created_scribble);
		}
	}
	if (this->m_create_arrow && this->m_creating_arrow) {
		if (this->m_size_to_fit) {
			dc.DPtoLP(&point);
		}
		this->m_creating_arrow = false;
		this->m_create_arrow = false;
		this->m_create_line = false;
		this->m_SelectedShapeOnToolBar = GRABARROW;
		CPoint exit_point = this->mp_created_arrow->GetExitPoint();
		if (exit_point == point) {
			delete this->mp_created_arrow;
			this->mp_created_arrow = NULL;
		}
		else {
			this->mp_created_arrow->SetEntryPoint(&point);
			this->mp_created_arrow->SetSelection(true);
			POSITION new_pos = pDoc->m_arrowList.AddHead(this->mp_created_arrow);
			pDoc->AddUndoStation(this->mp_created_arrow,new_pos,ADD_STATION);
		}
	}
	if (this->m_create_arrow && !this->m_creating_arrow) {
		CPoint entry_pt, exit_pt;
		if (this->m_size_to_fit) {
			dc.DPtoLP(&point);
		}
		entry_pt = point;
		exit_pt = point;
		entry_pt.x += this->m_inch_per_horiz;
		mp_created_arrow = new ArrowObj(&entry_pt, &exit_pt, pDoc->GetDefaultPen(), NO_OWNER, NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), this->m_create_line);
		this->mp_created_arrow->SetSelection(true);
		POSITION new_pos = pDoc->m_arrowList.AddHead(this->mp_created_arrow);
		pDoc->AddUndoStation(this->mp_created_arrow,new_pos,ADD_STATION);
	
		this->m_creating_arrow = false;
		this->m_create_arrow = false;
		this->m_create_line = false;
		this->m_SelectedShapeOnToolBar = GRABARROW;
		this->OnSelectarrow();	
	}
	if (this->m_drag_select) {
		this->m_drag_select = false;
		CRgn dragRgn;
		this->m_select_rect_top_left.x += sp.x;
		this->m_select_rect_botom_right.x += sp.x;
		this->m_select_rect_top_left.y += sp.y;
		this->m_select_rect_botom_right.y += sp.y;
		
		dragRgn.CreateRectRgn(this->m_select_rect_top_left.x,this->m_select_rect_top_left.y,this->m_select_rect_botom_right.x,this->m_select_rect_botom_right.y);
	
		CRallyObject* pRallyItemInlist;
		PylonObj *pPylonItemInlist;
		SpecialObj *pSpecialItemInlist;
		TextObj *pTextItemInlist;
		Scribble *pScribbleItemInlist;
		POSITION pos;
		
		for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
			if (pRallyItemInlist->RallyRectInRegion(&dragRgn)) {
				this->AddStationToSelectedList(pRallyItemInlist);
			}
		}

		for( pos = pDoc->m_pylonList.GetHeadPosition(); pos != NULL; ) {
			pPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetNext(pos);
			if (pPylonItemInlist->RallyRectInRegion(&dragRgn)) {
				this->AddPylonToSelectedList(pPylonItemInlist);
			}
		}

		for( pos = pDoc->m_special_list.GetHeadPosition(); pos != NULL; ) {
			pSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetNext(pos);
			if (pSpecialItemInlist->RallyRectInRegion(&dragRgn)) {
				this->AddSpecialToSelectedList(pSpecialItemInlist);
			}
		}
		for( pos = pDoc->m_text_list.GetHeadPosition(); pos != NULL; ) {
			pTextItemInlist = (TextObj*)pDoc->m_text_list.GetNext(pos);
			if (pTextItemInlist->RallyRectInRegion(&dragRgn)) {
				this->AddTextToSelectedList(pTextItemInlist);
			}
		}
		for( pos = pDoc->m_scribbleList.GetHeadPosition(); pos != NULL; ) {
			pScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetNext(pos);
			if (pScribbleItemInlist->ScribbleRectInRegion(&dragRgn)) {
				this->AddScribbleToSelectedList(pScribbleItemInlist);
			}
		}
		CRect rect(m_select_rect_top_left.x, m_select_rect_top_left.y, m_select_rect_botom_right.x, m_select_rect_botom_right.y);
		this->FixRectInFitScreenModeLPtoDP(&rect,&dc);
		rect.NormalizeRect();
		rect.InflateRect(5,5);

		rect.OffsetRect(-sp.x, -sp.y);
		if(this->m_select_rect_top_left.x != this->m_select_rect_botom_right.x) pDoc->m_arrowList.CheckForLineInRect(&dragRgn);
		
	}
	if (this->m_do_the_drag && !this->m_move_line && (this->m_line_hit == NO_HANDLE || this->m_line_hit == NO_HIT) ) {
		this->MoveStations(&dc, &point);
		pDoc->SetModifiedFlag();
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();
	}
	this->m_do_the_drag = this->m_drag_info = this->m_drag_station_list = false; // always on up

	if (this->m_curving_line) {
//		pDoc->m_arrowList.CurveLine(&dc,&point, this->m_size_to_fit);
		this->m_line_hit = NO_HIT;
		this->m_move_line = false;
		this->m_curving_line = false;
	}
	if (this->m_line_hit) {
		this->m_line_hit = NO_HIT;
		this->m_move_line = this->m_dragging_line = false;
	}

	this->Invalidate(FALSE);

	CScrollView::OnLButtonUp(nFlags, point);
}

void CDogRunView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ArrowObj *pArrow;
	if(dogRunApp->m_cutting) {
		dogRunApp->RemoveAllObjectsFromClipboard();
	}
	else {
		dogRunApp->m_clipBoard.RemoveAll();
	}
	dogRunApp->m_cutting = false;
	dogRunApp->m_pcutting_view = NULL;
	pDoc->ClearRedoList();
	this->m_popup_point.x = -10;
	this->m_popup_point.y = -10;
	POSITION pos;
	for( pos = this->m_stations_selected.GetHeadPosition(); pos != NULL; ) {
		dogRunApp->AddObjectToClipboard(this->m_stations_selected.GetNext(pos));
	}
	for( pos = this->m_pylons_selected.GetHeadPosition(); pos != NULL; ) {
		dogRunApp->AddObjectToClipboard(this->m_pylons_selected.GetNext(pos));
	}
	for( pos = this->m_special_selected.GetHeadPosition(); pos != NULL; ) {
		dogRunApp->AddObjectToClipboard(this->m_stations_selected.GetNext(pos));
	}	
	for( pos = this->m_text_selected.GetHeadPosition(); pos != NULL; ) {
		dogRunApp->AddObjectToClipboard(this->m_text_selected.GetNext(pos));
	}
	for( pos = this->m_scribble_selected.GetHeadPosition(); pos != NULL; ) {
		dogRunApp->AddObjectToClipboard(this->m_scribble_selected.GetNext(pos));
	}
	for( pos = pDoc->m_arrowList.GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)pDoc->m_arrowList.GetNext(pos);
		if (pArrow->GetArrowSelection() && pArrow->GetEntryOwner() == NO_OWNER) {
			dogRunApp->AddObjectToClipboard(pArrow);

		}
	}
		

}

void CDogRunView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	if (!(pDoc->m_arrowList.HowManySelectedArrowsWithoutOwners() > 0) && this->m_text_selected.IsEmpty() && 
		this->m_stations_selected.IsEmpty() && this->m_special_selected.IsEmpty() && 
		this->m_pylons_selected.IsEmpty() && this->m_scribble_selected.IsEmpty()) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}

}
void CDogRunView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	CDogRunApp* dogRunApp;
	CPoint offset_pt(50,50), top_left (10000,10000), stat_mid_point;
	POSITION pos, posInList;
	BOOL number_honor_station = true;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CObject *clipBoard;
	CRallyObject *p_station_obj;
	SpecialObj *p_special_obj;
	PylonObj *p_pylon_obj;
	TextObj *p_text_obj;
	ArrowObj *p_arrow_obj;
	Scribble *p_scribble_obj;
	CRect object_rect;
	int top,left, bottom, right;
	left = top = 10000;
	bottom = right = -100;
	this->ClearAllStationsFromSelectedList(true);
	pDoc->ClearRedoList();
	int num_pasted = 1;
	int how_many_stations, num_stations, which_station;
	how_many_stations = dogRunApp->m_clipBoard.GetCount();
	if (how_many_stations > 1 && this->m_popup_point.x > 0) { // need to find the  left-top center point
		for( pos = dogRunApp->m_clipBoard.GetHeadPosition(); pos != NULL; ) {
			clipBoard = dogRunApp->m_clipBoard.GetNext(pos);
			if(clipBoard->IsKindOf(RUNTIME_CLASS( CRallyObject))) { 
				p_station_obj = (CRallyObject *)clipBoard;
				object_rect = p_station_obj->GetStationRect();
			}
			if(clipBoard->IsKindOf(RUNTIME_CLASS( PylonObj))) { 
				p_pylon_obj = (PylonObj *)clipBoard;
				p_pylon_obj->GetPylonRect(&object_rect);
			}			
			if(clipBoard->IsKindOf(RUNTIME_CLASS( SpecialObj))) { 
				p_special_obj = (SpecialObj *)clipBoard;
				p_special_obj->GetSpecialRect(&object_rect);
			}
			if(clipBoard->IsKindOf(RUNTIME_CLASS( TextObj))) { 
				p_text_obj = (TextObj *)clipBoard;
				p_text_obj->GetDisplayTextRect(&object_rect);
			}			
			if(clipBoard->IsKindOf(RUNTIME_CLASS( ArrowObj))) { 
				p_arrow_obj = (ArrowObj *)clipBoard;
				p_arrow_obj->GetArrowRect(&object_rect);
			}			
			if(clipBoard->IsKindOf(RUNTIME_CLASS( Scribble))) { 
				p_scribble_obj = (Scribble *)clipBoard;
				object_rect = p_scribble_obj->m_rectBounding;
			}			

			if (object_rect.left < left) left = object_rect.left;
			if (object_rect.top < top) top = object_rect.top;
			if (object_rect.bottom > bottom) bottom = object_rect.bottom;
			if (object_rect.right > right) right = object_rect.right;
		}
		stat_mid_point.y = top + ((bottom - top)/2);
		stat_mid_point.x = left + ((right - left)/2);

	}
	for( pos = dogRunApp->m_clipBoard.GetHeadPosition(); pos != NULL; ) {
		clipBoard = dogRunApp->m_clipBoard.GetNext(pos);
		if(clipBoard->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);		
			p_station_obj = (CRallyObject *)clipBoard;
			this->CopyRallyObjectData(pRallyItem, p_station_obj);
			if (this->m_popup_point.x < 0) 
				if (!dogRunApp->m_cutting)
					pRallyItem->OffSetStationRect(&offset_pt);
				else 
					pRallyItem->SetStationRect(&p_station_obj->GetStationRect());
			else {			
				if (how_many_stations == 1) {
					pRallyItem->SetStationMidPoint(&this->m_popup_point);
				}
				else {
					offset_pt.x = this->m_popup_point.x - stat_mid_point.x;
					offset_pt.y = this->m_popup_point.y - stat_mid_point.y;
					pRallyItem->OffSetStationRect(&offset_pt);
				}
			}

			which_station = pRallyItem->GetStationID();
			if (which_station != IDB_START && which_station != IDB_FINISH && which_station != IDB_HONOR && which_station != IDB_PYLONS) {
				num_stations = pDoc->GetNumberStations();
				num_stations++;
				if (!dogRunApp->m_cutting || (dogRunApp->m_pcutting_view != this)) {
					pRallyItem->SetStationNumber(num_stations);
				}
				else {
				}
			}
			if (this->m_number_honor && (pRallyItem->GetAKCNumber() == 50)) {
				number_honor_station = true;
			}
			if (dogRunApp->m_cutting  && dogRunApp->m_pcutting_view == this) {
				posInList = pDoc->InsertStationIntoList(pRallyItem,pRallyItem->GetStationNumber(), true);
			}
			else {
				posInList = pDoc->InsertStationIntoList(pRallyItem,pRallyItem->GetStationNumber(), false);
			}
			if (posInList == NULL) {
				how_many_stations;
				num_pasted;
				if (how_many_stations == num_pasted + 1) { // we need to go back into undo list and make the last
				// undo MULPASTE_END
					CRallyObject *undo_station_obj;
					undo_station_obj = (CRallyObject *)pDoc->m_undo_list.GetTail();
					undo_station_obj->SetUndoRedoAction(MULPASTE_END);
				}
				delete pRallyItem;
			}
			else {
				this->AddStationToSelectedList(pRallyItem);

				if (how_many_stations == 1) 
					pDoc->AddUndoStation(pRallyItem,posInList,PASTE_STATION); 
				else if (num_pasted == 1) 
					pDoc->AddUndoStation(pRallyItem,posInList,MULPASTE_START); 
				else if (pos == NULL) 
					pDoc->AddUndoStation(pRallyItem,posInList,MULPASTE_END); 
				else 
					pDoc->AddUndoStation(pRallyItem,posInList,MULPASTE);
				num_pasted++;
			}
		}
		if (clipBoard->IsKindOf(RUNTIME_CLASS(PylonObj))) {
			PylonObj *pylon_object = new PylonObj(0,0);
			p_pylon_obj = (PylonObj*) clipBoard;
			this->CopyPylonObjectData(pylon_object,p_pylon_obj);
			if (this->m_popup_point.x < 0) 
				if (!dogRunApp->m_cutting)
					pylon_object->OffsetXYPos(&offset_pt);
				else 
					pylon_object->SetPylonRect();
			else {			
				if (how_many_stations == 1) {
					pylon_object->SetXYPosition(&this->m_popup_point);
					pylon_object->SetPylonRect();
				}
				else {
					offset_pt.x = this->m_popup_point.x - stat_mid_point.x;
					offset_pt.y = this->m_popup_point.y - stat_mid_point.y;
					pylon_object->OffSetPylonRect(&offset_pt);
				}
			}			
			posInList = pDoc->m_pylonList.AddHead(pylon_object);
			if (posInList == NULL) {
				delete pylon_object;
			}
			else {
				this->AddPylonToSelectedList(pylon_object);
				if (how_many_stations == 1) 
					pDoc->AddUndoStation(pylon_object,posInList,PASTE_STATION); 
				else if (num_pasted == 1) 
					pDoc->AddUndoStation(pylon_object,posInList,MULPASTE_START); 
				else if (pos == NULL) 
					pDoc->AddUndoStation(pylon_object,posInList,MULPASTE_END); 
				else 
					pDoc->AddUndoStation(pylon_object,posInList,MULPASTE);
				num_pasted++;
			}
		}
		if (clipBoard->IsKindOf(RUNTIME_CLASS(TextObj))){
			CRect text_rect;
			text_rect.SetRect(0, 0,100, 100); // for now default size of text rectangle.
			LOGFONT lf;
			pDoc->m_text_font->GetLogFont(&lf);
			TextObj *text_object = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
			p_text_obj = (TextObj*)clipBoard;
			this->CopyTextObjectData(text_object,p_text_obj);
			if (this->m_popup_point.x < 0) 
				if (!dogRunApp->m_cutting)
					text_object->OffsetTextRect(&offset_pt);
				else { 
					p_text_obj->GetDisplayTextRect(&text_rect);
					text_object->SetDisplayTextRect(&text_rect);
				}
			else {			
				if (how_many_stations == 1) {
					p_text_obj->GetDisplayTextRect(&text_rect);
					text_rect.SetRect(this->m_popup_point.x, this->m_popup_point.y,this->m_popup_point.x + text_rect.Width(), this->m_popup_point.y+text_rect.Height());
					text_object->SetDisplayTextRect(&text_rect);
				}
				else {
					offset_pt.x = this->m_popup_point.x - stat_mid_point.x;
					offset_pt.y = this->m_popup_point.y - stat_mid_point.y;
					text_object->OffsetTextRect(&offset_pt);
				}
			}			
			posInList = pDoc->m_text_list.AddHead(text_object);
			if (posInList == NULL) {
				delete text_object;
			}
			else {
				this->AddTextToSelectedList(text_object);
				if (how_many_stations == 1) 
					pDoc->AddUndoStation(text_object,posInList,PASTE_STATION); 
				else if (num_pasted == 1) 
					pDoc->AddUndoStation(text_object,posInList,MULPASTE_START); 
				else if (pos == NULL) 
					pDoc->AddUndoStation(text_object,posInList,MULPASTE_END); 
				else 
					pDoc->AddUndoStation(text_object,posInList,MULPASTE);
				num_pasted++;
			}

		}
		if(clipBoard->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			SpecialObj *special_object = new SpecialObj(0,0,-1);	
			CRect special_rect;
			p_special_obj = (SpecialObj*) clipBoard;
			this->CopySpecialObjectData(special_object,p_special_obj);
			if (this->m_popup_point.x < 0) 
				if (!dogRunApp->m_cutting)
					special_object->OffSetSpecialRect(&offset_pt);
				else {
					p_special_obj->GetSpecialRect(&special_rect);
					special_object->SetSpecialRect(&special_rect);
				}
			else {			
				if (how_many_stations == 1) {
					
					CPoint off_set_point;
					off_set_point.x = this->m_popup_point.x - special_object->GetXPos();
					off_set_point.y = this->m_popup_point.y - special_object->GetYPos();
					special_object->OffSetSpecialRect(&off_set_point);
				}
				else {
					offset_pt.x = this->m_popup_point.x - stat_mid_point.x;
					offset_pt.y = this->m_popup_point.y - stat_mid_point.y;
					special_object->OffSetSpecialRect(&offset_pt);
				}
			}			
			posInList = pDoc->m_special_list.AddHead(special_object);
			if (posInList == NULL) {
				delete special_object;
			}
			else {
				this->AddSpecialToSelectedList(special_object);
				if (how_many_stations == 1) 
					pDoc->AddUndoStation(special_object,posInList,PASTE_STATION); 
				else if (num_pasted == 1) 
					pDoc->AddUndoStation(special_object,posInList,MULPASTE_START); 
				else if (pos == NULL) 
					pDoc->AddUndoStation(special_object,posInList,MULPASTE_END); 
				else 
					pDoc->AddUndoStation(special_object,posInList,MULPASTE);
				num_pasted++;
			}
		}
		if(clipBoard->IsKindOf(RUNTIME_CLASS( Scribble))) {
			Scribble *scribble_object = new Scribble(pDoc->GetDefaultPen());	
			p_scribble_obj = (Scribble*) clipBoard;
			this->CopyScribbleObjectData(scribble_object,p_scribble_obj);
			if (this->m_popup_point.x < 0) 
				if (!dogRunApp->m_cutting)
					scribble_object->OffsetScribble(&offset_pt);
				else {
//					CPoint mid_point = p_scribble_obj->m_rectBounding.CenterPoint();
//					offset_pt.x = this->m_popup_point.x - mid_point.x;
//					offset_pt.y = this->m_popup_point.y - mid_point.y;
//					scribble_object->OffsetScribble(&offset_pt);
				}
			else {			
				if (how_many_stations == 1) {
					CPoint mid_point = p_scribble_obj->m_rectBounding.CenterPoint();
					offset_pt.x = this->m_popup_point.x - mid_point.x;
					offset_pt.y = this->m_popup_point.y - mid_point.y;
					scribble_object->OffsetScribble(&offset_pt);
					
//					scribble_object->SetXPos(this->m_popup_point.x);
//					scribble_object->SetYPos(this->m_popup_point.y);
//					scribble_object->SetSpecialRect();
				}
				else {
					offset_pt.x = this->m_popup_point.x - stat_mid_point.x;
					offset_pt.y = this->m_popup_point.y - stat_mid_point.y;
					scribble_object->OffsetScribble(&offset_pt);
				}
			}			
			posInList = pDoc->m_scribbleList.AddHead(scribble_object);
			if (posInList == NULL) {
				delete scribble_object;
			}
			else {
				this->AddScribbleToSelectedList(scribble_object);
				if (how_many_stations == 1) 
					pDoc->AddUndoStation(scribble_object,posInList,PASTE_STATION); 
				else if (num_pasted == 1) 
					pDoc->AddUndoStation(scribble_object,posInList,MULPASTE_START); 
				else if (pos == NULL) 
					pDoc->AddUndoStation(scribble_object,posInList,MULPASTE_END); 
				else 
					pDoc->AddUndoStation(scribble_object,posInList,MULPASTE);
				num_pasted++;
			}
		}

		if(clipBoard->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			CPoint point;
			point = this->m_popup_point;
			ArrowObj *arrow_object = new ArrowObj(&point, &point, pDoc->GetDefaultPen(), NO_OWNER, NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);	
			p_arrow_obj = (ArrowObj*) clipBoard;
			this->CopyArrowObjectData(arrow_object,p_arrow_obj);
			if (this->m_popup_point.x < 0) {
				if (!dogRunApp->m_cutting)
					arrow_object->SetDrawPoints(&offset_pt);
//				else  
//					arrow_object->SetDrawPoints(&offset_pt);
			}
			else {			
				if (how_many_stations == 1) {
					arrow_object->SetDrawPointsFromMidPoint(&point);
				}
				else {
					offset_pt.x = this->m_popup_point.x - stat_mid_point.x;
					offset_pt.y = this->m_popup_point.y - stat_mid_point.y;
					arrow_object->SetDrawPoints(&offset_pt);
				}
			}			
			posInList = pDoc->m_arrowList.AddHead(arrow_object);
			if (posInList == NULL) {
				delete arrow_object;
			}
			else {
				arrow_object->SetSelection(true);
				if (how_many_stations == 1) 
					pDoc->AddUndoStation(arrow_object,posInList,PASTE_STATION); 
				else if (num_pasted == 1) 
					pDoc->AddUndoStation(arrow_object,posInList,MULPASTE_START); 
				else if (pos == NULL) 
					pDoc->AddUndoStation(arrow_object,posInList,MULPASTE_END); 
				else 
					pDoc->AddUndoStation(arrow_object,posInList,MULPASTE);
				num_pasted++;
			}
		}

	}

	if (number_honor_station) {
		pDoc->SetStationNumberForHonor(true);	
	}
	else {
		pDoc->SetStationNumberForHonor(false);	
	}

	this->Invalidate (FALSE);
	this->OnSelectarrow();

	pDoc->SetModifiedFlag();
	pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	pDoc->SetUpInsertPopupMenu();
	this->m_popup_point.x = -10;
	this->m_popup_point.y = -10;

	this->CheckRallyRectInRectAfterMoveOrPaste();
}

void CDogRunView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 

	if (dogRunApp->m_clipBoard.IsEmpty()) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}
}

void CDogRunView::OnEditCut() 
{
	// TODO: Add your command handler code here

	CDogRunApp* dogRunApp;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRallyObject *rallyObjectInSelectList;
	PylonObj *pylonObjectInSelectList;
	SpecialObj *specialObjectInSelectList;
	TextObj *textObjectInSelectList;
	ArrowObj *arrowObjectInSelectList;
	Scribble *scribbleObjectInSelectList;

	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	this->m_popup_point.x = -10;
	this->m_popup_point.y = -10;

	if(dogRunApp->m_cutting) {
		dogRunApp->RemoveAllObjectsFromClipboard();
	}
	else {
		dogRunApp->m_clipBoard.RemoveAll();
	}

	pDoc->ClearUndoList();
	pDoc->ClearRedoList();

	POSITION posInSelect, posInRallyList, posTwo, pos_to_delete;
	int num_cut = 0, arrows_cut = 0;
	int how_many_stations = 0;
	how_many_stations = this->m_stations_selected.GetCount();
	how_many_stations += this->m_pylons_selected.GetCount();
	how_many_stations += this->m_special_selected.GetCount();
	how_many_stations += this->m_text_selected.GetCount();
	how_many_stations += this->m_scribble_selected.GetCount();
	how_many_stations += pDoc->m_arrowList.HowManySelectedArrowsWithoutOwners();
	for(posInSelect = this->m_stations_selected.GetHeadPosition(); posInSelect != NULL; ) {
		rallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetNext(posInSelect);
		dogRunApp->AddObjectToClipboard(rallyObjectInSelectList);
		posInRallyList = pDoc->m_rallyList.Find(rallyObjectInSelectList,NULL);
	// adding the cut station to our undo list
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,CUT_ONLY);
		else if (num_cut == 0)
			pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULCUT_START);
		else if (num_cut == how_many_stations-1)
			pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULCUT_END);
		else 
			pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULCUT);
		num_cut++;

		if (posInRallyList != NULL) {
			// remove from our list, will delete object during paste to clean-up memory
			pos_to_delete = pDoc->m_arrowList.RemoveArrowsForDeletedStation(rallyObjectInSelectList,&pDoc->m_rallyList,pDoc->GetNumberStations(), &arrows_cut);
			pDoc->ClearDeletedArrowFromUndoRedoList(pos_to_delete);
			pDoc->RemoveStationFromList(rallyObjectInSelectList, posInRallyList);
		}
	}
	pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
	for( posInSelect = this->m_pylons_selected.GetHeadPosition(); posInSelect != NULL; ) {
		pylonObjectInSelectList = (PylonObj*)this->m_pylons_selected.GetNext(posInSelect);
		dogRunApp->AddObjectToClipboard(pylonObjectInSelectList);
		posInRallyList = pDoc->m_pylonList.Find(pylonObjectInSelectList,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,CUT_ONLY);
		else if (num_cut == 0)
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,MULCUT_START);
		else if (num_cut == how_many_stations-1)
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,MULCUT_END);
		else 
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,MULCUT);
		num_cut++;

		if (posInRallyList != NULL) {
			// remove from our list, will delete object during paste to clean-up memory
			pDoc->m_pylonList.RemoveAt(posInRallyList);
		}
	}
	for( posInSelect = this->m_special_selected.GetHeadPosition(); posInSelect != NULL; ) {
		specialObjectInSelectList = (SpecialObj*)this->m_stations_selected.GetNext(posInSelect);
		dogRunApp->AddObjectToClipboard(specialObjectInSelectList);
		posInRallyList = pDoc->m_special_list.Find(specialObjectInSelectList,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,CUT_ONLY);
		else if (num_cut == 0)
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,MULCUT_START);
		else if (num_cut == how_many_stations-1)
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,MULCUT_END);
		else 
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,MULCUT);
		num_cut++;
		if (posInRallyList != NULL) {
			// remove from our list, will delete object during paste to clean-up memory
			pDoc->m_special_list.RemoveAt(posInRallyList);
		}
	}	
	for( posInSelect = this->m_scribble_selected.GetHeadPosition(); posInSelect != NULL; ) {
		scribbleObjectInSelectList = (Scribble*)this->m_scribble_selected.GetNext(posInSelect);
		dogRunApp->AddObjectToClipboard(scribbleObjectInSelectList);
		posInRallyList = pDoc->m_scribbleList.Find(scribbleObjectInSelectList,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,CUT_ONLY);
		else if (num_cut == 0)
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,MULCUT_START);
		else if (num_cut == how_many_stations-1)
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,MULCUT_END);
		else 
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,MULCUT);
		num_cut++;
		if (posInRallyList != NULL) {
			// remove from our list, will delete object during paste to clean-up memory
			pDoc->m_scribbleList.RemoveAt(posInRallyList);
		}
	}	
	for( posInSelect = this->m_text_selected.GetHeadPosition(); posInSelect != NULL; ) {
		textObjectInSelectList = (TextObj*)this->m_text_selected.GetNext(posInSelect);
		dogRunApp->AddObjectToClipboard(textObjectInSelectList);
		posInRallyList = pDoc->m_text_list.Find(textObjectInSelectList,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,CUT_ONLY);
		else if (num_cut == 0)
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,MULCUT_START);
		else if (num_cut == how_many_stations-1)
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,MULCUT_END);
		else 
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,MULCUT);
		num_cut++;
		if (posInRallyList != NULL) {
			// remove from our list, will delete object during paste to clean-up memory
			pDoc->m_text_list.RemoveAt(posInRallyList);
		}
	}
	for( posInSelect = pDoc->m_arrowList.GetHeadPosition(); posInSelect != NULL; ) {
		posTwo = posInSelect;
		arrowObjectInSelectList = (ArrowObj*)pDoc->m_arrowList.GetNext(posInSelect);
		if (arrowObjectInSelectList->GetArrowSelection()  && arrowObjectInSelectList->GetEntryOwner() == NO_OWNER) {
			dogRunApp->AddObjectToClipboard(arrowObjectInSelectList);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(arrowObjectInSelectList,posInRallyList,CUT_ONLY);
			else if (num_cut == 0)
				pDoc->AddUndoStation(arrowObjectInSelectList,posInRallyList,MULCUT_START);
			else if (num_cut == how_many_stations-1)
				pDoc->AddUndoStation(arrowObjectInSelectList,posInRallyList,MULCUT_END);
			else 
				pDoc->AddUndoStation(arrowObjectInSelectList,posInRallyList,MULCUT);
			num_cut++;
			if (posTwo != NULL) {
				// remove from our list, will delete object during paste to clean-up memory
				pDoc->m_arrowList.RemoveAt(posTwo);
			}
		}
	}
	dogRunApp->m_cutting = true;
	dogRunApp->m_pcutting_view = this;
	pDoc->SetUpInsertPopupMenu();
	pDoc->SetModifiedFlag();
	pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	this->ClearAllStationsFromSelectedList(true);
	this->Invalidate(FALSE);

}

void CDogRunView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	if (!(pDoc->m_arrowList.HowManySelectedArrowsWithoutOwners() > 0) && this->m_text_selected.IsEmpty() && 
		this->m_stations_selected.IsEmpty() && this->m_special_selected.IsEmpty() && 
		this->m_pylons_selected.IsEmpty() && this->m_scribble_selected.IsEmpty()) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}	
}
void CDogRunView::CopyRallyObjectData(CRallyObject *dest, CRallyObject *src) {
	int wd, ht;
	float M11, M12, M21, M22;
	dest->SetStationDescription(src->GetStationDescription());
	dest->SetStationNumber(src->GetStationNumber());
	dest->SetStringNumber(src->GetStringNumber());
	dest->SetStationType(src->GetStationType());
	dest->SetAKCNumber(src->GetAKCNumber());
	dest->SetStationMidPoint(&src->GetStationMidPoint());
	dest->SetStationRect(&src->GetStationRect());
	dest->SetStationID(src->GetStationID());
	src->GetStationWidthHeight(&wd,&ht);
	dest->SetStationWidthHeight(wd,ht);
	src->GetStationRotateMeasurements(&M11, &M12, &M21, &M22);
	dest->SetStationRotateMeasurements(M11, M12, M21, M22);
	dest->SetRotateText(src->GetRotateText());	
}

void CDogRunView::OnEditRedo() 
{
	// TODO: Add your command handler code here
	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	this->ClearAllStationsFromSelectedList(true);
	int redo_action;
	POSITION new_pos;
	CObject *pObjectItemInlist;
	
	CDogRunDoc* pDoc = GetDocument();
	if (pDoc->m_redo_list.GetCount() == 0) {
		this->MessageBox("Trying to Redo When Nothing in Redo List","Redo-Error",MB_OK);
		return;
	}
	pObjectItemInlist = pDoc->m_redo_list.RemoveTail();

	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
		pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
		redo_action = pRallyItemInlist->GetUndoRedoAction();
		this->MessageBoxUndoRedoActio(redo_action);
		if (redo_action == ADD_STATION) {
			CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);
			this->CopyRallyObjectData(pRallyItem, pRallyItemInlist);
			new_pos = pDoc->InsertStationIntoList(pRallyItem,pRallyItem->GetStationNumber(), false);
			pDoc->UpdatePositionsInRedoList(pRallyItemInlist->GetUndoRedoPostion(),new_pos, RALLY_OBJECT);
			this->AddStationToSelectedList(pRallyItem);
			pDoc->AddUndoStation(pRallyItem,new_pos,ADD_STATION);
			delete pRallyItemInlist;
			this->Invalidate(FALSE);
			return;

		}
		if (redo_action == PASTE_STATION) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoPaste(pRallyItemInlist,redo_action, RALLY_OBJECT);
			this->Invalidate(FALSE);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
			return;
		}
		if (redo_action == MULPASTE_START) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoMultiplePaste(pObjectItemInlist, redo_action);
			this->Invalidate(FALSE);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
			return;
		}
		if (redo_action == MOVE_STATION) {
			this->RedoMoveOrRotateStation(pRallyItemInlist, redo_action, RALLY_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULMOVE_START) {
			// need to redo to MULMOVE_END
			this->RedoMultipleMoveOrRotate(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == CUT_ONLY) { // just like delete
			this->RedoCut(pRallyItemInlist, redo_action, RALLY_OBJECT);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
			return;

		}
		if (redo_action == MULCUT_START) {
			RedoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
			return;
		}
		if (redo_action == DELETE_STATION) {
			this->RedoDelete(pRallyItemInlist,redo_action, RALLY_OBJECT);
			this->Invalidate(FALSE);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
			return;
		}
		if (redo_action == MULDEL_START) {
			this->RedoMultipleDelete(pObjectItemInlist);
			this->Invalidate(FALSE);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
			return;
		}
		if (redo_action == ROTATE_STATION) {
			this->RedoMoveOrRotateStation(pRallyItemInlist, redo_action, RALLY_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == INSERT_AT || redo_action == INSERT_BEFORE) {
			this->RedoInsertAction(pRallyItemInlist);
			return;
		}
		if (redo_action == MOVE_INFO) {
			this->RedoMoveInfo(pRallyItemInlist);
			return;
		}
		if (redo_action == MOVE_STATION_LIST) {
			this->RedoMoveStationList(pRallyItemInlist);
			return;
		}
		if (redo_action == CHANGE_STATION) {
			this->RedoChangeStation(pRallyItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		dogRunApp->m_rally_list_Dialog->SetUpRallyList(&pDoc->m_rallyList,pDoc);
	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
		pPylonItemInlist = (PylonObj *)pObjectItemInlist;
		redo_action = pPylonItemInlist->GetUndoRedoAction();
		this->MessageBoxUndoRedoActio(redo_action);
		if (redo_action == ADD_STATION) {
			PylonObj *pPylonItem = new PylonObj(0, 0);
			this->CopyPylonObjectData(pPylonItem, pPylonItemInlist);
			new_pos = pDoc->m_pylonList.AddTail(pPylonItem);
			pDoc->UpdatePositionsInRedoList(pPylonItemInlist->GetUndoRedoPosition(),new_pos, PYLON_OBJECT);
			this->AddPylonToSelectedList(pPylonItem);
			pDoc->AddUndoStation(pPylonItem,new_pos,ADD_STATION);
			delete pPylonItemInlist;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == PASTE_STATION) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoPaste(pPylonItemInlist,redo_action, PYLON_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULPASTE_START) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoMultiplePaste(pObjectItemInlist, redo_action);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == DELETE_STATION) {
			this->RedoDelete(pPylonItemInlist,redo_action, PYLON_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULDEL_START) {
			this->RedoMultipleDelete(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == CUT_ONLY) { // just like delete
			this->RedoCut(pPylonItemInlist, redo_action, PYLON_OBJECT);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULCUT_START) {
			RedoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MOVE_STATION) {
			this->RedoMoveOrRotateStation(pPylonItemInlist, redo_action, PYLON_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULMOVE_START) {
			// need to redo to MULMOVE_END
			this->RedoMultipleMoveOrRotate(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}

	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
		pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
		redo_action = pSpecialItemInlist->GetUndoRedoAction();
		if (redo_action == ADD_STATION) {
			SpecialObj *pSpecialItem = new SpecialObj(0, 0, -1);
			this->CopySpecialObjectData(pSpecialItem, pSpecialItemInlist);
			new_pos = pDoc->m_special_list.AddTail(pSpecialItem);
			pDoc->UpdatePositionsInRedoList(pSpecialItemInlist->GetUndoRedoPosition(),new_pos, SPECIAL_OBJECT);
			this->AddSpecialToSelectedList(pSpecialItem);
			pDoc->AddUndoStation(pSpecialItem,new_pos,ADD_STATION);
			delete pSpecialItemInlist;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == PASTE_STATION) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoPaste(pSpecialItemInlist,redo_action, SPECIAL_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULPASTE_START) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoMultiplePaste(pObjectItemInlist, redo_action);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == DELETE_STATION) {
			this->RedoDelete(pSpecialItemInlist,redo_action, SPECIAL_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULDEL_START) {
			this->RedoMultipleDelete(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == CUT_ONLY) { // just like delete
			this->RedoCut(pSpecialItemInlist, redo_action, SPECIAL_OBJECT);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULCUT_START) {
			RedoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MOVE_STATION || redo_action == ROTATE_STATION) {
			this->RedoMoveOrRotateStation(pSpecialItemInlist, redo_action, SPECIAL_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULMOVE_START) {
			// need to redo to MULMOVE_END
			this->RedoMultipleMoveOrRotate(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}

	}

	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
		pTextItemInlist = (TextObj *)pObjectItemInlist;
		redo_action = pTextItemInlist->GetUndoRedoAction();
		if (redo_action == ADD_STATION) {
			CRect text_rect;
			text_rect.SetRect(0, 0,100, 100); // for now default size of text rectangle.
			LOGFONT lf;
			pDoc->m_text_font->GetLogFont(&lf);
			TextObj *pTextItem = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
			this->CopyTextObjectData(pTextItem, pTextItemInlist);
			new_pos = pDoc->m_text_list.AddTail(pTextItem);
			pDoc->UpdatePositionsInRedoList(pTextItemInlist->GetUndoRedoPosition(),new_pos, TEXT_OBJECT);
			this->AddTextToSelectedList(pTextItem);
			pDoc->AddUndoStation(pTextItem,new_pos,ADD_STATION);
			delete pTextItemInlist;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == PASTE_STATION) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoPaste(pTextItemInlist,redo_action, TEXT_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULPASTE_START) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoMultiplePaste(pObjectItemInlist, redo_action);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == DELETE_STATION) {
			this->RedoDelete(pTextItemInlist,redo_action, TEXT_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULDEL_START) {
			this->RedoMultipleDelete(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == CUT_ONLY) { // just like delete
			this->RedoCut(pTextItemInlist, redo_action, TEXT_OBJECT);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULCUT_START) {
			RedoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MOVE_STATION || redo_action == ROTATE_STATION) {
			this->RedoMoveOrRotateStation(pTextItemInlist, redo_action, TEXT_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULMOVE_START) {
			// need to redo to MULMOVE_END
			this->RedoMultipleMoveOrRotate(pObjectItemInlist);	
			this->Invalidate(FALSE);
			return;
		}

	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
		pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
		redo_action = pArrowItemInlist->GetUndoRedoAction();
		this->MessageBoxUndoRedoActio(redo_action);
		if (redo_action == ADD_STATION) {
			CPoint tempPoint(0,0);
			ArrowObj *pArrowObj = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);		
			this->CopyArrowObjectData(pArrowObj, pArrowItemInlist);
			new_pos = pDoc->m_arrowList.AddTail(pArrowObj);
			pDoc->UpdatePositionsInRedoList(pArrowItemInlist->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
			pArrowObj->SetSelection(true);
			pDoc->AddUndoStation(pArrowObj,new_pos,ADD_STATION);
			delete pArrowItemInlist;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MOVE_STATION) {
			this->RedoMoveOrRotateStation(pArrowItemInlist, redo_action, ARROW_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULMOVE_START) {
			// need to redo to MULMOVE_END
			this->RedoMultipleMoveOrRotate(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == DELETE_STATION) {
			this->RedoDelete(pArrowItemInlist,redo_action, ARROW_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULDEL_START) {
			this->RedoMultipleDelete(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == PASTE_STATION) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoPaste(pArrowItemInlist,redo_action, ARROW_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULPASTE_START) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoMultiplePaste(pObjectItemInlist, redo_action);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == CUT_ONLY) { // just like delete
			this->RedoCut(pArrowItemInlist, redo_action, ARROW_OBJECT);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULCUT_START) {
			RedoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = true;
			dogRunApp->m_pcutting_view = this;
			this->Invalidate(FALSE);
			return;
		}

	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
		pScribbleItemInlist = (Scribble *)pObjectItemInlist;
		redo_action = pScribbleItemInlist->GetUndoRedoAction();
		this->MessageBoxUndoRedoActio(redo_action);
		if (redo_action == ADD_STATION) {
			Scribble *pScribbleItem = new Scribble(pDoc->GetDefaultPen());
			this->CopyScribbleObjectData(pScribbleItem, pScribbleItemInlist);
			new_pos = pDoc->m_scribbleList.AddTail(pScribbleItem);
			pDoc->UpdatePositionsInRedoList(pScribbleItemInlist->GetUndoRedoPosition(),new_pos, SCRIBBLE_OBJECT);
			this->AddScribbleToSelectedList(pScribbleItem);
			pDoc->AddUndoStation(pScribbleItem,new_pos,ADD_STATION);
			delete pScribbleItemInlist;
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MOVE_STATION) {
			this->RedoMoveOrRotateStation(pScribbleItemInlist, redo_action, SCRIBBLE_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULMOVE_START) {
			// need to redo to MULMOVE_END
			this->RedoMultipleMoveOrRotate(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == DELETE_STATION) {
			this->RedoDelete(pScribbleItemInlist,redo_action, SCRIBBLE_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULDEL_START) {
			this->RedoMultipleDelete(pObjectItemInlist);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == PASTE_STATION) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoPaste(pScribbleItemInlist,redo_action, SCRIBBLE_OBJECT);
			this->Invalidate(FALSE);
			return;
		}
		if (redo_action == MULPASTE_START) {
			this->ClearAllStationsFromSelectedList(true);
			this->RedoMultiplePaste(pObjectItemInlist, redo_action);
			this->Invalidate(FALSE);
			return;
		}
	}
	this->Invalidate(FALSE);
}
void CDogRunView::RedoMoveStationList(CRallyObject *p_redoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRect old_info_rect, current_info_rect;
	old_info_rect = p_redoStation->GetStationRect();
	pDoc->m_station_list->GetStationListRect(&current_info_rect);
	pDoc->m_station_list->SetStationListRect(&old_info_rect);
	p_redoStation->SetStationRect(&current_info_rect);
	pDoc->AddUndoStation(p_redoStation,NULL, MOVE_STATION_LIST);
	delete p_redoStation;
	this->Invalidate(FALSE);

}
void CDogRunView::RedoMoveInfo(CRallyObject *p_redoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRect old_info_rect, current_info_rect;
	old_info_rect = p_redoStation->GetStationRect();
	pDoc->m_course_info->GetCourseInfoRect(&current_info_rect);
	pDoc->m_course_info->SetCourseInfoRect(&old_info_rect);
	p_redoStation->SetStationRect(&current_info_rect);
	pDoc->AddUndoStation(p_redoStation,NULL, MOVE_INFO);
	delete p_redoStation;
	this->Invalidate(FALSE);

}
void CDogRunView::RedoChangeStation(CRallyObject *p_redoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pOldRallyItemInlist;
	POSITION pos;
	int  old_station_akc_num, old_station_string_num, old_station_id, old_station_num;
	pos = p_redoStation->GetUndoRedoPostion();
	pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
	pDoc->AddUndoStation(pOldRallyItemInlist,pos, CHANGE_STATION);

	int number_of_stations = pDoc->GetNumberStations();

	old_station_num = pOldRallyItemInlist->GetStationNumber();
	old_station_akc_num = p_redoStation->GetAKCNumber();
	switch (old_station_akc_num){ // need to re-order list
	case 1:
	case 2:
		pOldRallyItemInlist->SetStationNumber(number_of_stations+1);

//		if (old_station_num > START_STATION) {
//			number_of_stations--;
//			pDoc->SetNumberStations(number_of_stations);
//		}
// -2 means do not add undo station
		pDoc->UpdateRallyList(-2, p_redoStation->GetAKCNumber(), pos) ;
		break;
	default:
		break;
	}
	switch (old_station_num) {
	case START_STATION:
	case FINISH_STATION:
	case HONOR_STATION:
	case CALL_TO_HEEL_STATION:
		pOldRallyItemInlist->SetStationNumber(number_of_stations);
		break;
	}


	old_station_id = p_redoStation->GetStationID();
	pOldRallyItemInlist->SetStationID(old_station_id);
	old_station_string_num = p_redoStation->GetStringNumber();
	pOldRallyItemInlist->SetStringNumber(old_station_string_num);
	old_station_akc_num = p_redoStation->GetAKCNumber();
	pOldRallyItemInlist->SetAKCNumber(old_station_akc_num);

	switch (old_station_akc_num){
	case 1:
		pOldRallyItemInlist->SetStationNumber(START_STATION);
		break;
	case 2:
		pOldRallyItemInlist->SetStationNumber(FINISH_STATION);
		break;
	}
//	pOldRallyItemInlist->SetStationRect();
	CRect invalid_rect;
	invalid_rect = pOldRallyItemInlist->GetStationRect();
	this->InvalidateRect(&invalid_rect,FALSE);
  delete p_redoStation;

}
void CDogRunView::RedoInsertAction(CRallyObject *p_redoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pOldRallyItemInlist;
	POSITION pos;
	int current_station_num, old_station_number;
	pos = p_redoStation->GetUndoRedoPostion();
	pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
	pDoc->AddUndoStation(pOldRallyItemInlist,pos, INSERT_AT);

	current_station_num = pOldRallyItemInlist->GetStationNumber();
	old_station_number = p_redoStation->GetStationNumber();
	if (current_station_num < old_station_number) {
		pDoc->RenumberStations(old_station_number, INSERT_AT, pOldRallyItemInlist, false);
	}
	else {
		old_station_number;
		pDoc->RenumberStations(old_station_number, INSERT_AT, pOldRallyItemInlist, false);

	}
	this->Invalidate(false);
	delete p_redoStation;

}
void CDogRunView::RedoMoveOrRotateStation(CObject *p_redoStation, int redo_action, int type_of_object) {
	POSITION pos;
	CRallyObject *pOldRallyItemInlist, *p_rally_object;
	PylonObj *pOldPylonItemInlist, *p_pylon_object;
	SpecialObj *pOldSpecialItemInlist, *p_special_object;
	TextObj *pOldTextItemInlist, *p_text_object;
	ArrowObj *pOldArrowItemInlist, *p_arrow_object;
	Scribble *pOldScribbleItemInlist, *p_scribble_object;
	CDogRunDoc* pDoc = GetDocument();
	if (type_of_object == RALLY_OBJECT) {
		p_rally_object = (CRallyObject *)p_redoStation;
		pos = p_rally_object->GetUndoRedoPostion();
		pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
		pDoc->AddUndoStation(pOldRallyItemInlist,pos, redo_action);
		this->CopyRallyObjectData(pOldRallyItemInlist, p_rally_object);
		this->AddStationToSelectedList(pOldRallyItemInlist);
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected,&pDoc->m_rallyList,pDoc->GetNumberStations());
		delete p_rally_object;
	}
	if (type_of_object == PYLON_OBJECT) {
		p_pylon_object = (PylonObj *)p_redoStation;
		pos = p_pylon_object->GetUndoRedoPosition();
		pOldPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetAt(pos);
		pDoc->AddUndoStation(pOldPylonItemInlist,pos, redo_action);
		this->AddPylonToSelectedList(pOldPylonItemInlist);
		this->CopyPylonObjectData(pOldPylonItemInlist, p_pylon_object);
		delete p_pylon_object;
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_redoStation;
		pos = p_special_object->GetUndoRedoPosition();
		pOldSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetAt(pos);
		pDoc->AddUndoStation(pOldSpecialItemInlist,pos, redo_action);
		this->AddSpecialToSelectedList(pOldSpecialItemInlist);
		this->CopySpecialObjectData(pOldSpecialItemInlist, p_special_object);
		delete p_special_object;
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_redoStation;
		pos = p_text_object->GetUndoRedoPosition();
		pOldTextItemInlist = (TextObj*)pDoc->m_special_list.GetAt(pos);
		pDoc->AddUndoStation(pOldTextItemInlist,pos, redo_action);
		this->AddTextToSelectedList(pOldTextItemInlist);
		this->CopyTextObjectData(pOldTextItemInlist, p_text_object);
		delete p_text_object;
	}
	if (type_of_object == ARROW_OBJECT) {
		p_arrow_object = (ArrowObj *)p_redoStation;
		pos = p_arrow_object->GetUndoRedoPosition();
		pOldArrowItemInlist = (ArrowObj*)pDoc->m_arrowList.GetAt(pos);
		pDoc->AddUndoStation(pOldArrowItemInlist,pos, redo_action);
		this->CopyArrowObjectData(pOldArrowItemInlist, p_arrow_object);
		pOldArrowItemInlist->SetSelection(true);
		delete p_arrow_object;
	}
	if (type_of_object == SCRIBBLE_OBJECT) {
		p_scribble_object = (Scribble *)p_redoStation;
		pos = p_scribble_object->GetUndoRedoPosition();
		pOldScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetAt(pos);
		pDoc->AddUndoStation(pOldScribbleItemInlist,pos, redo_action);
		this->CopyScribbleObjectData(pOldScribbleItemInlist, p_scribble_object);
		pOldScribbleItemInlist->SetSelection(true);
		this->AddScribbleToSelectedList(pOldScribbleItemInlist);
		delete p_scribble_object;
	}
}
void CDogRunView::RedoDelete(CObject *p_redoStation, int redo_action, int type_of_object) {
	POSITION pos,  pos_to_delete;
	CRallyObject *pOldRallyItemInlist, *p_rally_object;
	PylonObj *pOldPylonItemInlist, *p_pylon_object;
	SpecialObj *pOldSpecialItemInlist, *p_special_object;
	TextObj *pOldTextItemInlist, *p_text_object;
	ArrowObj *pOldArrowItemInlist, *p_arrow_object;
	Scribble *pOldScribbleItemInlist, *p_scribble_object;
	int num_deleted = 0;
	CDogRunDoc* pDoc = GetDocument();
	int count = pDoc->m_redo_list.GetCount();
	if (type_of_object == RALLY_OBJECT) {\
		p_rally_object = (CRallyObject *)p_redoStation;
		pos = p_rally_object->GetUndoRedoPostion();
		pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
		pDoc->AddUndoStation(pOldRallyItemInlist,pos, redo_action); 
		pos_to_delete = pDoc->m_arrowList.RemoveArrowsForDeletedStation(pOldRallyItemInlist,&pDoc->m_rallyList,pDoc->GetNumberStations(), &num_deleted);
		pDoc->ClearDeletedArrowFromUndoRedoList(pos_to_delete);
		count = pDoc->m_redo_list.GetCount();
		pDoc->RemoveStationFromList(pOldRallyItemInlist, pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete pOldRallyItemInlist;
		delete p_rally_object;
	}
	if (type_of_object == PYLON_OBJECT) {\
		p_pylon_object = (PylonObj *)p_redoStation;
		pos = p_pylon_object->GetUndoRedoPosition();
		pOldPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetAt(pos);
		pDoc->AddUndoStation(pOldPylonItemInlist,pos, redo_action); 
		pDoc->m_pylonList.RemoveAt(pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete pOldPylonItemInlist;
		delete p_pylon_object;
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_redoStation;
		pos = p_special_object->GetUndoRedoPosition();
		pOldSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetAt(pos);
		pDoc->AddUndoStation(pOldSpecialItemInlist,pos, redo_action); 
		pDoc->m_special_list.RemoveAt(pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete pOldSpecialItemInlist;
		delete p_special_object;
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_redoStation;
		pos = p_text_object->GetUndoRedoPosition();
		pOldTextItemInlist = (TextObj*)pDoc->m_text_list.GetAt(pos);
		pDoc->AddUndoStation(pOldTextItemInlist,pos, redo_action); 
		pDoc->m_text_list.RemoveAt(pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete pOldTextItemInlist;
		delete p_text_object;
	}
	if (type_of_object == ARROW_OBJECT) {
		p_arrow_object = (ArrowObj *)p_redoStation;
		pos = p_arrow_object->GetUndoRedoPosition();
		pOldArrowItemInlist = (ArrowObj*)pDoc->m_arrowList.GetAt(pos);
		pDoc->AddUndoStation(pOldArrowItemInlist,pos, redo_action); 
		pDoc->m_arrowList.RemoveAt(pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete pOldArrowItemInlist;
		delete p_arrow_object;
	}
	if (type_of_object == SCRIBBLE_OBJECT) {
		p_scribble_object = (Scribble *)p_redoStation;
		pos = p_scribble_object->GetUndoRedoPosition();
		pOldScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetAt(pos);
		pDoc->AddUndoStation(pOldScribbleItemInlist,pos, redo_action); 
		pDoc->m_scribbleList.RemoveAt(pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete pOldScribbleItemInlist;
		delete p_scribble_object;
	}
	this->ClearAllStationsFromSelectedList(true);
}
void CDogRunView::RedoPaste(CObject *p_redoStation, int redo_action, int type_of_object) {
	POSITION new_pos;
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *p_rally_object;
	PylonObj *p_pylon_object;
	SpecialObj *p_special_object;
	TextObj *p_text_object;
	ArrowObj *p_arrow_object;
	Scribble *p_scribble_object;
	if (type_of_object == RALLY_OBJECT) {
		p_rally_object = (CRallyObject *)p_redoStation;
		CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);
		this->CopyRallyObjectData(pRallyItem,p_rally_object);
		new_pos = pDoc->InsertStationIntoList(pRallyItem,pRallyItem->GetStationNumber(), false);
		pDoc->UpdatePositionsInRedoList(p_rally_object->GetUndoRedoPostion(),new_pos, RALLY_OBJECT);
		pDoc->AddUndoStation(pRallyItem,new_pos,redo_action);
		this->AddStationToSelectedList(pRallyItem);
		delete p_rally_object;
	}
	if (type_of_object == PYLON_OBJECT) {
		p_pylon_object = (PylonObj *)p_redoStation;
		PylonObj *pPylonItem = new PylonObj(0, 0);
		this->CopyPylonObjectData(pPylonItem,p_pylon_object);
		new_pos = pDoc->m_pylonList.AddTail(pPylonItem);
		pDoc->UpdatePositionsInRedoList(p_pylon_object->GetUndoRedoPosition(),new_pos, PYLON_OBJECT);
		pDoc->AddUndoStation(pPylonItem,new_pos,redo_action);
		this->AddPylonToSelectedList(pPylonItem);
		delete p_pylon_object;
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_redoStation;
		SpecialObj *pSpecialItem = new SpecialObj(0, 0, -1);
		this->CopySpecialObjectData(pSpecialItem,p_special_object);
		new_pos = pDoc->m_special_list.AddTail(pSpecialItem);
		pDoc->UpdatePositionsInRedoList(p_special_object->GetUndoRedoPosition(),new_pos, SPECIAL_OBJECT);
		pDoc->AddUndoStation(pSpecialItem,new_pos,redo_action);
		this->AddSpecialToSelectedList(pSpecialItem);
		delete p_special_object;
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_redoStation;
		CRect text_rect;
		text_rect.SetRect(0,0,1,1);
		LOGFONT lf;
		pDoc->m_text_font->GetLogFont(&lf);
		TextObj *pTextItem = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
		this->CopyTextObjectData(pTextItem,p_text_object);
		new_pos = pDoc->m_text_list.AddTail(pTextItem);
		pDoc->UpdatePositionsInRedoList(p_text_object->GetUndoRedoPosition(),new_pos, TEXT_OBJECT);
		pDoc->AddUndoStation(pTextItem,new_pos,redo_action);
		this->AddTextToSelectedList(pTextItem);
		delete p_text_object;
	}
	if (type_of_object == ARROW_OBJECT) {
		p_arrow_object = (ArrowObj *)p_redoStation;
		CPoint tempPoint(0,0);
		ArrowObj *pArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);	
		this->CopyArrowObjectData(pArrowItem,p_arrow_object);
		new_pos = pDoc->m_arrowList.AddTail(pArrowItem);
		pDoc->UpdatePositionsInRedoList(p_arrow_object->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
		pDoc->AddUndoStation(pArrowItem,new_pos,redo_action);
		pArrowItem->SetSelection(true);
		delete p_arrow_object;
	}

	if (type_of_object == SCRIBBLE_OBJECT) {
		p_scribble_object = (Scribble *)p_redoStation;
		Scribble *pScribbleItem = new Scribble(pDoc->GetDefaultPen());	
		this->CopyScribbleObjectData(pScribbleItem,p_scribble_object);
		new_pos = pDoc->m_scribbleList.AddTail(pScribbleItem);
		pDoc->UpdatePositionsInRedoList(p_scribble_object->GetUndoRedoPosition(),new_pos, SCRIBBLE_OBJECT);
		pDoc->AddUndoStation(pScribbleItem,new_pos,redo_action);
		pScribbleItem->SetSelectedFlag(TRUE);
		this->AddScribbleToSelectedList(pScribbleItem);
		delete p_scribble_object;
	}
}
void CDogRunView::RedoCut(CObject *p_redoStation, int redo_action, int type_of_object){

	POSITION pos, pos_to_delete;
	CDogRunDoc* pDoc = GetDocument();
	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	CRallyObject *pOldRallyItemInlist, *p_rally_object;
	PylonObj *pOldPylonItemInlist, *p_pylon_object;
	SpecialObj *pOldSpecialItemInlist, *p_special_object;
	TextObj *pOldTextItemInlist, *p_text_object;
	ArrowObj *pOldArrowItemInlist, *p_arrow_object;
	int num_deleted = 0;
	if (type_of_object == RALLY_OBJECT) {
		p_rally_object = (CRallyObject *)p_redoStation;
		pos = p_rally_object->GetUndoRedoPostion();
		pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
		dogRunApp->AddObjectToClipboard(pOldRallyItemInlist);
		pDoc->AddUndoStation(pOldRallyItemInlist,pos,redo_action); 
		pos_to_delete = pDoc->m_arrowList.RemoveArrowsForDeletedStation(pOldRallyItemInlist,&pDoc->m_rallyList,pDoc->GetNumberStations(), &num_deleted);
		pDoc->ClearDeletedArrowFromUndoRedoList(pos_to_delete);
		pDoc->RemoveStationFromList(pOldRallyItemInlist, pos);
	// delete the object created for the undo list!!! or we get leaks!!
		delete p_rally_object;
	}
	if (type_of_object == PYLON_OBJECT) {\
		p_pylon_object = (PylonObj *)p_redoStation;
		pos = p_pylon_object->GetUndoRedoPosition();
		pOldPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetAt(pos);
		dogRunApp->AddObjectToClipboard(pOldPylonItemInlist);
		pDoc->AddUndoStation(pOldPylonItemInlist,pos, redo_action); 
		pDoc->m_pylonList.RemoveAt(pos);
	// need to get rid of our object that created for the rally list
	// and the object created for the undo list!!! or we get leaks!!
		delete p_pylon_object;
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_redoStation;
		pos = p_special_object->GetUndoRedoPosition();
		pOldSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetAt(pos);
		dogRunApp->AddObjectToClipboard(pOldSpecialItemInlist);
		pDoc->AddUndoStation(pOldSpecialItemInlist,pos, redo_action); 
		pDoc->m_special_list.RemoveAt(pos);
	// delete the object created for the undo list!!! or we get leaks!!
		delete p_special_object;
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_redoStation;
		pos = p_text_object->GetUndoRedoPosition();
		pOldTextItemInlist = (TextObj*)pDoc->m_text_list.GetAt(pos);
		dogRunApp->AddObjectToClipboard(pOldTextItemInlist);
		pDoc->AddUndoStation(pOldTextItemInlist,pos, redo_action); 
		pDoc->m_text_list.RemoveAt(pos);
	// delete the object created for the undo list!!! or we get leaks!!
		delete p_text_object;
	}
	if (type_of_object == ARROW_OBJECT) {
		p_arrow_object = (ArrowObj *)p_redoStation;
		pos = p_arrow_object->GetUndoRedoPosition();
		pOldArrowItemInlist = (ArrowObj*)pDoc->m_arrowList.GetAt(pos);
		dogRunApp->AddObjectToClipboard(pOldArrowItemInlist);
		pDoc->AddUndoStation(pOldArrowItemInlist,pos, redo_action); 
		pDoc->m_arrowList.RemoveAt(pos);
	// delete the object created for the undo list!!! or we get leaks!!
		delete p_arrow_object;
	}
}
void CDogRunView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();

	if (pDoc->m_redo_list.IsEmpty()) {
		pCmdUI->Enable(FALSE);

	}
	else {
		pCmdUI->Enable(TRUE);
	}	
}

void CDogRunView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();

	if (pDoc->m_undo_list.IsEmpty()) {
		pCmdUI->Enable(FALSE);

	}
	else {
		pCmdUI->Enable(TRUE);
	}
}

void CDogRunView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	CRallyObject *pRallyItemInlist, *pOldRallyItemInlist;
	PylonObj *pPylonItemInlist, *pOldPylonItemInlist;
	SpecialObj *pSpecialItemInlist, *pOldSpecialItemInlist;
	TextObj *pTextItemInlist, *pOldTextItemInlist;
	ArrowObj *pArrowItemInlist, *pOldArrowItemInlist;
	Scribble *pScribbleItemInlist, *pOldScribbleItemInlist;
	CObject *pObjectItemInlist;
	int undo_action;
	POSITION pos, pos_to_delete;
	int num_deleted;
	CDogRunDoc* pDoc = GetDocument();
	
	pDoc->ClearRedoList();

	if (pDoc->m_undo_list.GetCount() == 0) {
		this->MessageBox("Trying to Undo When Nothing in Undo List","Undo-Error",MB_OK);
		return;
	}
	pObjectItemInlist = pDoc->m_undo_list.RemoveTail();
	this->ClearAllStationsFromSelectedList(true);
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
		pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
		undo_action = pRallyItemInlist->GetUndoRedoAction();
		this->MessageBoxUndoRedoActio(undo_action);
		if (undo_action == ADD_STATION) {
			dogRunApp->m_clipBoard.RemoveAll();
			pos = pRallyItemInlist->GetUndoRedoPostion();
			pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
			pos_to_delete = pDoc->m_arrowList.RemoveArrowsForDeletedStation(pOldRallyItemInlist,&pDoc->m_rallyList,pDoc->GetNumberStations(), &num_deleted);
			pDoc->ClearDeletedArrowFromUndoRedoList(pos_to_delete);
			pDoc->RemoveStationFromList(pRallyItemInlist,pos);
			delete pOldRallyItemInlist;
			pDoc->AddRedoStation(pRallyItemInlist);// item as is

		}
		if (undo_action == PASTE_STATION) {
			this->UndoPaste(pRallyItemInlist, RALLY_OBJECT);
		}
		if (undo_action == MULPASTE_END) {
			this->UndoMultiplePaste(pObjectItemInlist);
		}
		
		if(undo_action == DELETE_STATION) {
			this->UndoDelete(pRallyItemInlist, DELETE_STATION, RALLY_OBJECT);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}
		if (undo_action == MULDEL_END) {
			this->UndoMultipleDelete(pObjectItemInlist);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}
		if (undo_action == CUT_ONLY) { // still have an object in memory, reference is on the clipboard!
			// cut only, object not deleted so just need to put in back in rally list
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoCut(pRallyItemInlist, undo_action, RALLY_OBJECT);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}
		if (undo_action == MULCUT_END) {
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}
		if (undo_action == MULMOVE_END) {
			// need to undo to MULMOVE_START
			this->UndoMultipleMoveOrRotate(pObjectItemInlist);
		}
		if (undo_action == ROTATE_STATION || undo_action == MOVE_STATION) { // ROTATE_STATION, MOVE_STATION
			this->UndoMoveOrRotateAction(pRallyItemInlist, RALLY_OBJECT);
		}
		if (undo_action == INSERT_AT || undo_action == INSERT_BEFORE) {
			this->UndoInsertAction(pRallyItemInlist);
		}
		if (undo_action == MOVE_INFO) {
			this->UndoMoveInfo(pRallyItemInlist);
		}
		if (undo_action == MOVE_STATION_LIST) {
			this->UndoMoveStationList(pRallyItemInlist);
		}
		if (undo_action == CHANGE_STATION) {
			this->UndoChangeStation(pRallyItemInlist);
		}
		dogRunApp->m_rally_list_Dialog->SetUpRallyList(&pDoc->m_rallyList,pDoc);
	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
		pPylonItemInlist = (PylonObj *)pObjectItemInlist;
		undo_action = pPylonItemInlist->GetUndoRedoAction();
		if (undo_action == ADD_STATION) {
			dogRunApp->m_clipBoard.RemoveAll();
			pos = pPylonItemInlist->GetUndoRedoPosition();
			pOldPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetAt(pos);
			pDoc->m_pylonList.RemoveAt(pos);
			delete pOldPylonItemInlist;
			pDoc->AddRedoStation(pPylonItemInlist);// item as is

		}
		if (undo_action == PASTE_STATION) {
			this->UndoPaste(pPylonItemInlist, PYLON_OBJECT);
		}
		if (undo_action == MULPASTE_END) {
			this->UndoMultiplePaste(pObjectItemInlist);
		}
		if(undo_action == DELETE_STATION) {
			this->UndoDelete(pPylonItemInlist, DELETE_STATION, PYLON_OBJECT);
		}
		if (undo_action == MULDEL_END) {
			this->UndoMultipleDelete(pObjectItemInlist);
		}
		if (undo_action == CUT_ONLY) { // still have an object in memory, reference is on the clipboard!
			// cut only, object not deleted so just need to put in back in rally list
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoCut(pPylonItemInlist, undo_action, PYLON_OBJECT);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULCUT_END) {
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULMOVE_END) {
			// need to undo to MULMOVE_START
			this->UndoMultipleMoveOrRotate(pObjectItemInlist);
		}
		if (undo_action == ROTATE_STATION || undo_action == MOVE_STATION) { // ROTATE_STATION, MOVE_STATION
			this->UndoMoveOrRotateAction(pPylonItemInlist, PYLON_OBJECT);
		}

	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
		pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
		undo_action = pSpecialItemInlist->GetUndoRedoAction();
		if (undo_action == ADD_STATION) {
			dogRunApp->m_clipBoard.RemoveAll();
			pos = pSpecialItemInlist->GetUndoRedoPosition();
			pOldSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetAt(pos);
			pDoc->m_special_list.RemoveAt(pos);
			delete pOldSpecialItemInlist;
			pDoc->AddRedoStation(pSpecialItemInlist);// item as is
		}
		if (undo_action == PASTE_STATION) {
			this->UndoPaste(pSpecialItemInlist, SPECIAL_OBJECT);
		}
		if (undo_action == MULPASTE_END) {
			this->UndoMultiplePaste(pObjectItemInlist);
		}
		if(undo_action == DELETE_STATION) {
			this->UndoDelete(pSpecialItemInlist, DELETE_STATION, SPECIAL_OBJECT);
		}
		if (undo_action == MULDEL_END) {
			this->UndoMultipleDelete(pObjectItemInlist);
		}
		if (undo_action == CUT_ONLY) { // still have an object in memory, reference is on the clipboard!
			// cut only, object not deleted so just need to put in back in rally list
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoCut(pSpecialItemInlist, undo_action, SPECIAL_OBJECT);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULCUT_END) {
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULMOVE_END) {
			// need to undo to MULMOVE_START
			this->UndoMultipleMoveOrRotate(pObjectItemInlist);
		}
		if (undo_action == ROTATE_STATION || undo_action == MOVE_STATION) { // ROTATE_STATION, MOVE_STATION
			this->UndoMoveOrRotateAction(pSpecialItemInlist, SPECIAL_OBJECT);
		}
	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
		pTextItemInlist = (TextObj *)pObjectItemInlist;
		undo_action = pTextItemInlist->GetUndoRedoAction();
		if (undo_action == ADD_STATION) {
			dogRunApp->m_clipBoard.RemoveAll();
			pos = pTextItemInlist->GetUndoRedoPosition();
			pOldTextItemInlist = (TextObj*)pDoc->m_text_list.GetAt(pos);
			pDoc->m_text_list.RemoveAt(pos);
			delete pOldTextItemInlist;
			pDoc->AddRedoStation(pTextItemInlist);// item as is
		}
		if (undo_action == PASTE_STATION) {
			this->UndoPaste(pTextItemInlist, TEXT_OBJECT);
		}
		if (undo_action == MULPASTE_END) {
			this->UndoMultiplePaste(pObjectItemInlist);
		}
		if(undo_action == DELETE_STATION) {
			this->UndoDelete(pTextItemInlist, DELETE_STATION, TEXT_OBJECT);
		}
		if (undo_action == MULDEL_END) {
			this->UndoMultipleDelete(pObjectItemInlist);
		}	
		if (undo_action == CUT_ONLY) { // still have an object in memory, reference is on the clipboard!
			// cut only, object not deleted so just need to put in back in rally list
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoCut(pTextItemInlist, undo_action, TEXT_OBJECT);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULCUT_END) {
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULMOVE_END) {
			// need to undo to MULMOVE_START
			this->UndoMultipleMoveOrRotate(pObjectItemInlist);
		}
		if (undo_action == ROTATE_STATION || undo_action == MOVE_STATION) { // ROTATE_STATION, MOVE_STATION
			this->UndoMoveOrRotateAction(pTextItemInlist, TEXT_OBJECT);
		}
	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
		pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
		undo_action = pArrowItemInlist->GetUndoRedoAction();
		this->MessageBoxUndoRedoActio(undo_action);
		if (undo_action == ADD_STATION) {
			dogRunApp->m_clipBoard.RemoveAll();
			pos = pArrowItemInlist->GetUndoRedoPosition();
			pOldArrowItemInlist = (ArrowObj*)pDoc->m_arrowList.GetAt(pos);
			pDoc->m_arrowList.RemoveAt(pos);
			delete pOldArrowItemInlist;
			pDoc->AddRedoStation(pArrowItemInlist);// item as is
		}
		if (undo_action == MOVE_STATION) {
			this->UndoMoveOrRotateAction(pArrowItemInlist, ARROW_OBJECT);
		}
		if (undo_action == MULMOVE_END) {
			// need to undo to MULMOVE_START
			this->UndoMultipleMoveOrRotate(pObjectItemInlist);
		}
		if(undo_action == DELETE_STATION) {
			this->UndoDelete(pArrowItemInlist, DELETE_STATION, ARROW_OBJECT);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}
		if (undo_action == MULDEL_END) {
			this->UndoMultipleDelete(pObjectItemInlist);
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}	
		if (undo_action == PASTE_STATION) {
			this->UndoPaste(pArrowItemInlist, ARROW_OBJECT);
		}
		if (undo_action == MULPASTE_END) {
			this->UndoMultiplePaste(pObjectItemInlist);
		}
		if (undo_action == CUT_ONLY) { // still have an object in memory, reference is on the clipboard!
			// cut only, object not deleted so just need to put in back in rally list
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoCut(pArrowItemInlist, undo_action, ARROW_OBJECT);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}
		if (undo_action == MULCUT_END) {
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
			pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);
		}

	}
	if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
		pScribbleItemInlist = (Scribble *)pObjectItemInlist;
		undo_action = pScribbleItemInlist->GetUndoRedoAction();
		if (undo_action == ADD_STATION) {
			dogRunApp->m_clipBoard.RemoveAll();
			pos = pScribbleItemInlist->GetUndoRedoPosition();
			pOldScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetAt(pos);
			pDoc->m_scribbleList.RemoveAt(pos);
			delete pOldScribbleItemInlist;
			pDoc->AddRedoStation(pScribbleItemInlist);// item as is

		}
		if (undo_action == MOVE_STATION) {
			this->UndoMoveOrRotateAction(pScribbleItemInlist, SCRIBBLE_OBJECT);
		}
		if (undo_action == MULMOVE_END) {
			// need to undo to MULMOVE_START
			this->UndoMultipleMoveOrRotate(pObjectItemInlist);
		}
		if(undo_action == DELETE_STATION) {
			this->UndoDelete(pScribbleItemInlist, DELETE_STATION, SCRIBBLE_OBJECT);
		}
		if (undo_action == MULDEL_END) {
			this->UndoMultipleDelete(pObjectItemInlist);
		}
		if (undo_action == PASTE_STATION) {
			this->UndoPaste(pScribbleItemInlist, SCRIBBLE_OBJECT);
		}
		if (undo_action == MULPASTE_END) {
			this->UndoMultiplePaste(pObjectItemInlist);
		}
		if (undo_action == CUT_ONLY) { // still have an object in memory, reference is on the clipboard!
			// cut only, object not deleted so just need to put in back in rally list
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoCut(pScribbleItemInlist, undo_action, SCRIBBLE_OBJECT);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}
		if (undo_action == MULCUT_END) {
			if (dogRunApp->m_cutting) dogRunApp->RemoveAllObjectsFromClipboard();
			this->UndoMultipleCut(pObjectItemInlist);
			dogRunApp->m_cutting = false;
			dogRunApp->m_pcutting_view = NULL;
		}

	}
	this->Invalidate(FALSE);	
}
void CDogRunView::UndoChangeStation(CRallyObject *p_undoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pOldRallyItemInlist;
	POSITION pos;
	int  old_station_akc_num, old_station_string_num, old_station_id, old_station_num;
	int  cur_station_akc_num, cur_station_string_num, cur_station_id, cur_station_num;

	pos = p_undoStation->GetUndoRedoPostion();
	pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);

	cur_station_id = pOldRallyItemInlist->GetStationID();
	cur_station_string_num = pOldRallyItemInlist->GetStringNumber();
	cur_station_akc_num = pOldRallyItemInlist->GetAKCNumber();
	cur_station_num = pOldRallyItemInlist->GetStationNumber();
		
	old_station_id = p_undoStation->GetStationID();
	pOldRallyItemInlist->SetStationID(old_station_id);
	old_station_string_num = p_undoStation->GetStringNumber();
	pOldRallyItemInlist->SetStringNumber(old_station_string_num);
	old_station_akc_num = p_undoStation->GetAKCNumber();
	pOldRallyItemInlist->SetAKCNumber(old_station_akc_num);

	old_station_num = p_undoStation->GetStationNumber();
	int number_of_stations = pDoc->GetNumberStations();

	switch (cur_station_akc_num){ // need to re-order list
	case 1:
	case 2:
		pOldRallyItemInlist->SetStationNumber(number_of_stations+1);

		if (old_station_num > START_STATION) {
			number_of_stations++;
			pDoc->SetNumberStations(number_of_stations);
		}
		if (number_of_stations > 1)  pDoc->RenumberStations(old_station_num, INSERT_AT, pOldRallyItemInlist,false);		
		else pOldRallyItemInlist->SetStationNumber(old_station_num);
		break;
	default:
		pOldRallyItemInlist->SetStationNumber(old_station_num);
		break;
	}

	switch (old_station_akc_num){
	case 1:
		pOldRallyItemInlist->SetStationNumber(START_STATION);
		break;
	case 2:
		pOldRallyItemInlist->SetStationNumber(FINISH_STATION);
		break;
	}
//	pOldRallyItemInlist->SetStationRect();

	p_undoStation->SetStationID(cur_station_id);
	p_undoStation->SetStringNumber(cur_station_string_num);
	p_undoStation->SetAKCNumber(cur_station_akc_num);
	p_undoStation->SetStationNumber(cur_station_num);

	
	switch (cur_station_akc_num){
	case 1:
		p_undoStation->SetStationNumber(START_STATION);
		break;
	case 2:
		p_undoStation->SetStationNumber(FINISH_STATION);
		break;
	}
//	p_undoStation->SetStationRect();
	
	pDoc->AddRedoStation(p_undoStation);


}
void CDogRunView::UndoMoveStationList(CRallyObject *p_undoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRect old_info_rect, current_info_rect;
	old_info_rect = p_undoStation->GetStationRect();
	pDoc->m_station_list->GetStationListRect(&current_info_rect);
	pDoc->m_station_list->SetStationListRect(&old_info_rect);
	p_undoStation->SetStationRect(&current_info_rect);
	pDoc->AddRedoStation(p_undoStation);
}
void CDogRunView::UndoMoveInfo(CRallyObject *p_undoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRect old_info_rect, current_info_rect;
	old_info_rect = p_undoStation->GetStationRect();
	pDoc->m_course_info->GetCourseInfoRect(&current_info_rect);
	pDoc->m_course_info->SetCourseInfoRect(&old_info_rect);
	p_undoStation->SetStationRect(&current_info_rect);
	pDoc->AddRedoStation(p_undoStation);
}

void CDogRunView::UndoInsertAction(CRallyObject *p_undoStation) {
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pOldRallyItemInlist;
	POSITION pos;
	int current_station_num, old_station_number;
	pos = p_undoStation->GetUndoRedoPostion();
	pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);

	current_station_num = pOldRallyItemInlist->GetStationNumber();
	old_station_number = p_undoStation->GetStationNumber();
	if (current_station_num < old_station_number) {
		pDoc->RenumberStations(old_station_number, INSERT_AT, pOldRallyItemInlist, false);
	}
	else {
		pDoc->RenumberStations(old_station_number, INSERT_AT, pOldRallyItemInlist, false);
	}
	p_undoStation->SetStationNumber(current_station_num);
	pDoc->AddRedoStation(p_undoStation);
}
void CDogRunView::UndoMoveOrRotateAction(CObject *p_undoStation, int type_of_object) {
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pOldRallyItemInlist, *pTempRallyItem, *p_rally_object;
	PylonObj *pOldPylonItemInlist, *pTempPylonItem, *p_pylon_object;
	SpecialObj *pOldSpecialItemInlist, *pTempSpecialItem, *p_special_object;
	TextObj *pOldTextItemInlist, *pTempTextItem, *p_text_object;
	ArrowObj *pOldArrowItemInlist, *pTempArrowItem, *p_arrow_object;
	Scribble *pOldScribbleItemInlist, *pTempScribbleItem, *p_scribble_object;
	POSITION pos;
	if (type_of_object == RALLY_OBJECT) {
		p_rally_object = (CRallyObject *)p_undoStation;
		pos = p_rally_object->GetUndoRedoPostion();
		pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
		pTempRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);	
		this->CopyRallyObjectData(pTempRallyItem, pOldRallyItemInlist);
		this->CopyRallyObjectData(pOldRallyItemInlist, p_rally_object);
		this->CopyRallyObjectData(p_rally_object, pTempRallyItem);
		delete pTempRallyItem;
		pDoc->AddRedoStation(p_rally_object);
		this->AddStationToSelectedList(pOldRallyItemInlist);
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected,&pDoc->m_rallyList,pDoc->GetNumberStations());
	}
	if (type_of_object == PYLON_OBJECT) {
		p_pylon_object = (PylonObj *)p_undoStation;
		pos = p_pylon_object->GetUndoRedoPosition();
		pOldPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetAt(pos);
		pTempPylonItem = new PylonObj(0, 0);	
		this->CopyPylonObjectData(pTempPylonItem, pOldPylonItemInlist);
		this->CopyPylonObjectData(pOldPylonItemInlist, p_pylon_object);
		this->CopyPylonObjectData(p_pylon_object, pTempPylonItem);
		delete pTempPylonItem;
		pDoc->AddRedoStation(p_pylon_object);
		this->AddPylonToSelectedList(pOldPylonItemInlist);
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_undoStation;
		pos = p_special_object->GetUndoRedoPosition();
		pOldSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetAt(pos);
		pTempSpecialItem = new SpecialObj(0, 0, -1);	
		this->CopySpecialObjectData(pTempSpecialItem, pOldSpecialItemInlist);
		this->CopySpecialObjectData(pOldSpecialItemInlist, p_special_object);
		this->CopySpecialObjectData(p_special_object, pTempSpecialItem);
		delete pTempSpecialItem;
		pDoc->AddRedoStation(p_special_object);
		this->AddSpecialToSelectedList(pOldSpecialItemInlist);
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_undoStation;
		pos = p_text_object->GetUndoRedoPosition();
		pOldTextItemInlist = (TextObj*)pDoc->m_text_list.GetAt(pos);
		CRect text_rect;
		text_rect.SetRect(0, 0,100, 100); // for now default size of text rectangle.
		LOGFONT lf;
		pDoc->m_text_font->GetLogFont(&lf);
		pTempTextItem = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
		this->CopyTextObjectData(pTempTextItem, pOldTextItemInlist);
		this->CopyTextObjectData(pOldTextItemInlist, p_text_object);
		this->CopyTextObjectData(p_text_object, pTempTextItem);
		delete pTempTextItem;
		pDoc->AddRedoStation(p_text_object);
		this->AddTextToSelectedList(pOldTextItemInlist);
	}
	if (type_of_object == ARROW_OBJECT) {
		p_arrow_object = (ArrowObj *)p_undoStation;
		pos = p_arrow_object->GetUndoRedoPosition();
		pOldArrowItemInlist = (ArrowObj*)pDoc->m_arrowList.GetAt(pos);
		CPoint tempPoint(0,0);
		pTempArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);	
		this->CopyArrowObjectData(pTempArrowItem, pOldArrowItemInlist);
		this->CopyArrowObjectData(pOldArrowItemInlist, p_arrow_object);
		this->CopyArrowObjectData(p_arrow_object, pTempArrowItem);
		delete pTempArrowItem;
		pDoc->AddRedoStation(p_arrow_object);
		pOldArrowItemInlist->SetSelection(TRUE);
	}
	if (type_of_object == SCRIBBLE_OBJECT) {
		p_scribble_object = (Scribble *)p_undoStation;
		pos = p_scribble_object->GetUndoRedoPosition();
		pOldScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetAt(pos);
		pTempScribbleItem = new Scribble(pDoc->GetDefaultPen());	
		this->CopyScribbleObjectData(pTempScribbleItem, pOldScribbleItemInlist);
		this->CopyScribbleObjectData(pOldScribbleItemInlist, p_scribble_object);
		this->CopyScribbleObjectData(p_scribble_object, pTempScribbleItem);
		delete pTempScribbleItem;
		pDoc->AddRedoStation(p_scribble_object);
		pOldScribbleItemInlist->SetSelection(TRUE);
		this->AddScribbleToSelectedList(pOldScribbleItemInlist);
	}
}

void CDogRunView::UndoDelete(CObject *p_undoStation, int undo_action, int type_of_object) {
	POSITION new_pos;
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *p_rally_object;
	PylonObj *p_pylon_object;
	SpecialObj *p_special_object;
	TextObj *p_text_object;
	ArrowObj *p_arrow_object;
	Scribble *p_scribble_object;

	if (type_of_object == RALLY_OBJECT) {
		p_rally_object = (CRallyObject *)p_undoStation;
		CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);
		this->CopyRallyObjectData(pRallyItem,p_rally_object);
		int old_station_number = pRallyItem->GetStationNumber();
		new_pos = pDoc->InsertStationIntoList(pRallyItem,old_station_number, true);
		pDoc->UpdatePositionsInUndoList(p_rally_object->GetUndoRedoPostion(),new_pos, RALLY_OBJECT);
		this->AddStationToSelectedList(pRallyItem);
		p_rally_object->SetUndoRedoPosition(new_pos);
		p_rally_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_rally_object);// item as is
	}
	if (type_of_object == PYLON_OBJECT) {
		p_pylon_object = (PylonObj *)p_undoStation;
		PylonObj *pPylonItem = new PylonObj(0, 0);
		this->CopyPylonObjectData(pPylonItem,p_pylon_object);
		new_pos = pDoc->m_pylonList.AddTail(pPylonItem);
		pDoc->UpdatePositionsInUndoList(p_pylon_object->GetUndoRedoPosition(),new_pos, PYLON_OBJECT);
		this->AddPylonToSelectedList(pPylonItem);
		p_pylon_object->SetUndoRedoPosition(new_pos);
		p_pylon_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_pylon_object);// item as is
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_undoStation;
		SpecialObj *pSpecialItem = new SpecialObj(0, 0, -1);
		this->CopySpecialObjectData(pSpecialItem,p_special_object);
		new_pos = pDoc->m_special_list.AddTail(pSpecialItem);
		pDoc->UpdatePositionsInUndoList(p_special_object->GetUndoRedoPosition(),new_pos, SPECIAL_OBJECT);
		this->AddSpecialToSelectedList(pSpecialItem);
		p_special_object->SetUndoRedoPosition(new_pos);
		p_special_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_special_object);// item as is
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_undoStation;
		CRect text_rect;
		text_rect.SetRect(0, 0,100, 100); // for now default size of text rectangle.
		LOGFONT lf;
		pDoc->m_text_font->GetLogFont(&lf);
		TextObj *pTextItem = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
		this->CopyTextObjectData(pTextItem,p_text_object);
		new_pos = pDoc->m_text_list.AddTail(pTextItem);
		pDoc->UpdatePositionsInUndoList(p_text_object->GetUndoRedoPosition(),new_pos, TEXT_OBJECT);
		this->AddTextToSelectedList(pTextItem);
		p_text_object->SetUndoRedoPosition(new_pos);
		p_text_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_text_object);// item as is
	}
	if (type_of_object == ARROW_OBJECT) {
		ArrowObj *p_temp_arrow;
		p_arrow_object = (ArrowObj *)p_undoStation;
		CPoint tempPoint(0,0);

		p_temp_arrow = pDoc->m_arrowList.FindArrow(p_arrow_object->m_exit_owner, p_arrow_object->m_entry_owner);
		if (p_temp_arrow) {
			int num_stations = pDoc->GetNumberStations();
			BOOL have_finish = pDoc->FinishStationInList();
			bool connect_to_finish = true;
			if (p_arrow_object->GetEntryOwner() + 1 <= num_stations) {
				p_temp_arrow = pDoc->m_arrowList.FindArrow(p_arrow_object->m_exit_owner+1, p_arrow_object->m_entry_owner+1);		
				connect_to_finish = false;
			}
			else if (p_arrow_object->GetEntryOwner() + 1 > num_stations && have_finish) {
				p_temp_arrow = pDoc->m_arrowList.FindArrow(p_arrow_object->m_exit_owner+1, FINISH_STATION);	
				connect_to_finish = true;
			}
			else if (p_arrow_object->GetEntryOwner() + 1 > num_stations) {
				p_temp_arrow = p_arrow_object;
			}
			if (!p_temp_arrow) {
				ArrowObj *pArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);		
				this->CopyArrowObjectData(pArrowItem,p_arrow_object);
				pArrowItem->SetExitOwner(pArrowItem->GetExitOwner() + 1);
				if (connect_to_finish) {
					pArrowItem->SetEntryOwner(FINISH_STATION);
				}
				else {
					pArrowItem->SetEntryOwner(p_arrow_object->m_exit_owner+1);
				}
				new_pos = pDoc->m_arrowList.AddTail(pArrowItem);
				pDoc->UpdatePositionsInUndoList(p_arrow_object->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
				pArrowItem->SetSelection(true);
				p_arrow_object->SetUndoRedoPosition(new_pos);
				p_arrow_object->SetUndoRedoAction(undo_action);
				pDoc->AddRedoStation(p_arrow_object);// item as is
			/*
				ArrowObj *pArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);		
				this->CopyArrowObjectData(pArrowItem,p_arrow_object);
				new_pos = pDoc->m_arrowList.AddTail(pArrowItem);
				pDoc->UpdatePositionsInUndoList(p_arrow_object->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
				pArrowItem->SetSelection(true);
				p_arrow_object->SetUndoRedoPosition(new_pos);
				p_arrow_object->SetUndoRedoAction(undo_action);
				pDoc->AddRedoStation(p_arrow_object);// item as is
				*/
			}
			else {
//				pDoc->AddRedoStation(p_arrow_object);// item as is				
/*
				POSITION pos_to_delete;
				pos_to_delete = pDoc->m_arrowList.Find(p_temp_arrow);
				pDoc->m_arrowList.RemoveAt(pos_to_delete);
				delete p_temp_arrow;
				ArrowObj *pArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);		
				this->CopyArrowObjectData(pArrowItem,p_arrow_object);
				pArrowItem->SetExitOwner(pArrowItem->GetExitOwner() + 1);
				if (connect_to_finish) {
					pArrowItem->SetEntryOwner(FINISH_STATION);
				}
				else {
					pArrowItem->SetEntryOwner(p_arrow_object->m_exit_owner+1);
				}
				new_pos = pDoc->m_arrowList.AddTail(pArrowItem);
			p_temp_arrow = (ArrowObj*)pDoc->m_arrowList.GetAt(new_pos);

				pDoc->UpdatePositionsInUndoList(p_arrow_object->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
				pArrowItem->SetSelection(true);
				p_arrow_object->SetUndoRedoPosition(new_pos);
				p_arrow_object->SetUndoRedoAction(undo_action);
				pDoc->AddRedoStation(p_arrow_object);// item as is
*/				
			}
		}
		else {
			ArrowObj *pArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);		
			this->CopyArrowObjectData(pArrowItem,p_arrow_object);
			new_pos = pDoc->m_arrowList.AddTail(pArrowItem);
			pDoc->UpdatePositionsInUndoList(p_arrow_object->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
			pArrowItem->SetSelection(true);
			p_arrow_object->SetUndoRedoPosition(new_pos);
			p_arrow_object->SetUndoRedoAction(undo_action);
			pDoc->AddRedoStation(p_arrow_object);// item as is
		}
	}
	if (type_of_object == SCRIBBLE_OBJECT) {
		p_scribble_object = (Scribble *)p_undoStation;
		Scribble *pScribbleItem = new Scribble(pDoc->GetDefaultPen());		
		this->CopyScribbleObjectData(pScribbleItem,p_scribble_object);
		new_pos = pDoc->m_scribbleList.AddTail(pScribbleItem);
		pDoc->UpdatePositionsInUndoList(p_scribble_object->GetUndoRedoPosition(),new_pos, SCRIBBLE_OBJECT);
		pScribbleItem->SetSelection(true);
		this->AddScribbleToSelectedList(pScribbleItem);
		p_scribble_object->SetUndoRedoPosition(new_pos);
		p_scribble_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_scribble_object);// item as is
	}
}

void CDogRunView::UndoPaste(CObject *p_undoStation, int type_of_object) {
	POSITION pos, pos_to_delete;
	CRallyObject *pOldRallyItemInlist, *pRallyItemInlist;	
	PylonObj *pOldPylonItemInlist, *pPylonItemInlist;	
	SpecialObj *pOldSpecialItemInlist, *pSpecialItemInlist;	
	TextObj *pOldTextItemInlist, *pTextItemInlist;	
	ArrowObj *pOldArrowItemInlist, *pArrowItemInlist;	
	Scribble *pOldScribbleItemInlist, *pScribbleItemInlist;	
	CDogRunDoc* pDoc = GetDocument();
	int num_deleted = 0;
	if (type_of_object == RALLY_OBJECT) {
		pRallyItemInlist = (CRallyObject *)p_undoStation;
		pos = pRallyItemInlist->GetUndoRedoPostion();
		pOldRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetAt(pos);
		pos_to_delete = pDoc->m_arrowList.RemoveArrowsForDeletedStation(pOldRallyItemInlist,&pDoc->m_rallyList,pDoc->GetNumberStations(), &num_deleted);
		pDoc->ClearDeletedArrowFromUndoRedoList(pos_to_delete);
		pDoc->RemoveStationFromList(pOldRallyItemInlist, pos);
		delete pOldRallyItemInlist;
		pDoc->AddRedoStation(pRallyItemInlist);// item as is
	}
	if (type_of_object == PYLON_OBJECT) {
		pPylonItemInlist = (PylonObj *)p_undoStation;
		pos = pPylonItemInlist->GetUndoRedoPosition();
		pOldPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetAt(pos);
		pDoc->m_pylonList.RemoveAt(pos);
		delete pOldPylonItemInlist;
		pDoc->AddRedoStation(pPylonItemInlist);// item as is
	}
	if (type_of_object == SPECIAL_OBJECT) {
		pSpecialItemInlist = (SpecialObj *)p_undoStation;
		pos = pSpecialItemInlist->GetUndoRedoPosition();
		pOldSpecialItemInlist = (SpecialObj*)pDoc->m_special_list.GetAt(pos);
		pDoc->m_special_list.RemoveAt(pos);
		delete pOldSpecialItemInlist;
		pDoc->AddRedoStation(pSpecialItemInlist);// item as is
	}
	if (type_of_object == TEXT_OBJECT) {
		pTextItemInlist = (TextObj *)p_undoStation;
		pos = pTextItemInlist->GetUndoRedoPosition();
		pOldTextItemInlist = (TextObj*)pDoc->m_text_list.GetAt(pos);
		pDoc->m_text_list.RemoveAt(pos);
		delete pOldTextItemInlist;
		pDoc->AddRedoStation(pTextItemInlist);// item as is
	}
	if (type_of_object == ARROW_OBJECT) {
		pArrowItemInlist = (ArrowObj *)p_undoStation;
		pos = pArrowItemInlist->GetUndoRedoPosition();
		pOldArrowItemInlist = (ArrowObj*)pDoc->m_arrowList.GetAt(pos);
		pDoc->m_arrowList.RemoveAt(pos);
		delete pOldArrowItemInlist;
		pDoc->AddRedoStation(pArrowItemInlist);// item as is
	}
	if (type_of_object == SCRIBBLE_OBJECT) {
		pScribbleItemInlist = (Scribble *)p_undoStation;
		pos = pScribbleItemInlist->GetUndoRedoPosition();
		pOldScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetAt(pos);
		pDoc->m_scribbleList.RemoveAt(pos);
		delete pOldScribbleItemInlist;
		pDoc->AddRedoStation(pScribbleItemInlist);// item as is
	}
}

void CDogRunView::UndoCut(CObject *p_undoStation, int undo_action, int type_of_object) {
	POSITION new_pos;
	CRallyObject *p_rally_object;
	CDogRunDoc* pDoc = GetDocument();
	PylonObj *p_pylon_object;
	SpecialObj *p_special_object;
	TextObj *p_text_object;
	ArrowObj *p_arrow_object;
	Scribble *p_scribble_object;

	if (type_of_object == RALLY_OBJECT) {
		p_rally_object = (CRallyObject *)p_undoStation;
		CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);
		this->CopyRallyObjectData(pRallyItem,p_rally_object);
		new_pos = pDoc->InsertStationIntoList(pRallyItem,pRallyItem->GetStationNumber(), true);
		pDoc->UpdatePositionsInUndoList(p_rally_object->GetUndoRedoPostion(),new_pos, RALLY_OBJECT);
		this->AddStationToSelectedList(pRallyItem);
		p_rally_object->SetUndoRedoPosition(new_pos);
		p_rally_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_rally_object);// item as is	
	}
	if (type_of_object == PYLON_OBJECT) {
		p_pylon_object = (PylonObj *)p_undoStation;
		PylonObj *pPylonItem = new PylonObj(0, 0);
		this->CopyPylonObjectData(pPylonItem,p_pylon_object);
		new_pos = pDoc->m_pylonList.AddTail(pPylonItem);
		pDoc->UpdatePositionsInUndoList(p_pylon_object->GetUndoRedoPosition(),new_pos, PYLON_OBJECT);
		this->AddPylonToSelectedList(pPylonItem);
		p_pylon_object->SetUndoRedoPosition(new_pos);
		p_pylon_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_pylon_object);// item as is
	}
	if (type_of_object == SPECIAL_OBJECT) {
		p_special_object = (SpecialObj *)p_undoStation;
		SpecialObj *pSpecialItem = new SpecialObj(0, 0, -1);
		this->CopySpecialObjectData(pSpecialItem,p_special_object);
		new_pos = pDoc->m_special_list.AddTail(pSpecialItem);
		pDoc->UpdatePositionsInUndoList(p_special_object->GetUndoRedoPosition(),new_pos, SPECIAL_OBJECT);
		this->AddSpecialToSelectedList(pSpecialItem);
		p_special_object->SetUndoRedoPosition(new_pos);
		p_special_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_special_object);// item as is
	}
	if (type_of_object == SCRIBBLE_OBJECT) {
		p_scribble_object = (Scribble *)p_undoStation;
		Scribble *pScribbleItem = new Scribble(pDoc->GetDefaultPen());
		this->CopyScribbleObjectData(pScribbleItem,p_scribble_object);
		new_pos = pDoc->m_scribbleList.AddTail(pScribbleItem);
		pDoc->UpdatePositionsInUndoList(p_scribble_object->GetUndoRedoPosition(),new_pos, SCRIBBLE_OBJECT);
		this->AddScribbleToSelectedList(pScribbleItem);
		p_scribble_object->SetUndoRedoPosition(new_pos);
		p_scribble_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_scribble_object);// item as is
	}
	if (type_of_object == TEXT_OBJECT) {
		p_text_object = (TextObj *)p_undoStation;
		CRect text_rect;
		text_rect.SetRect(0, 0,100, 100); // for now default size of text rectangle.
		LOGFONT lf;
		pDoc->m_text_font->GetLogFont(&lf);
		TextObj *pTextItem = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
		this->CopyTextObjectData(pTextItem,p_text_object);
		new_pos = pDoc->m_text_list.AddTail(pTextItem);
		pDoc->UpdatePositionsInUndoList(p_text_object->GetUndoRedoPosition(),new_pos, TEXT_OBJECT);
		this->AddTextToSelectedList(pTextItem);
		p_text_object->SetUndoRedoPosition(new_pos);
		p_text_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_text_object);// item as is
	}
	if (type_of_object == ARROW_OBJECT) {
		p_arrow_object = (ArrowObj *)p_undoStation;
		CPoint tempPoint(0,0);
		ArrowObj *pArrowItem = new ArrowObj(&tempPoint,&tempPoint,pDoc->GetDefaultPen(),NO_OWNER,NO_OWNER, pDoc->GetDefaultArrowType(), pDoc->GetDocumentMoveArrowsWithStation(), false);		
		this->CopyArrowObjectData(pArrowItem,p_arrow_object);
		new_pos = pDoc->m_arrowList.AddTail(pArrowItem);
		pDoc->UpdatePositionsInUndoList(p_arrow_object->GetUndoRedoPosition(),new_pos, ARROW_OBJECT);
		pArrowItem->SetSelection(true);
		p_arrow_object->SetUndoRedoPosition(new_pos);
		p_arrow_object->SetUndoRedoAction(undo_action);
		pDoc->AddRedoStation(p_arrow_object);// item as is
	}
}

void CDogRunView::OnEditClear() 
{
	// TODO: Add your command handler code here
	POSITION posInSelect, posInRallyList, pos_to_delete;//, posInUndoList;
	CDogRunDoc* pDoc = GetDocument();
	Scribble *scribbleObjectInSelectList, *pScribbleObject;
	SpecialObj *specialObjectInSelectList, *pSpecialObject;
	PylonObj *pylonObjectInSelectList, *pPylonObject;
	TextObj *textObjectInSelectList, *pTextObject;
	CRallyObject *rallyObjectInSelectList, *pRallyObject; //, *rallyObjectInUndoList;
	int num_deleted = 0, i = 0;
	bool arrow_deleted = false, deleted_started = false;
	int how_many_selected = 0, how_many_stations_selected = 0;
	pDoc->ClearRedoList();
	pDoc->ClearUndoList();
	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
	if(dogRunApp->m_cutting) {
		dogRunApp->RemoveAllObjectsFromClipboard();
	}
	else {
		dogRunApp->m_clipBoard.RemoveAll();
	}

	how_many_selected = this->m_stations_selected.GetCount();
	how_many_selected += this->m_pylons_selected.GetCount();
	how_many_selected += this->m_text_selected.GetCount();
	how_many_selected += this->m_special_selected.GetCount();
	how_many_selected += this->m_scribble_selected.GetCount();
	how_many_selected += pDoc->m_arrowList.HowManySelectedArrows();
	
	for( posInSelect = this->m_stations_selected.GetHeadPosition(); posInSelect != NULL; ) {
		rallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetNext(posInSelect);

		posInRallyList = pDoc->m_rallyList.Find(rallyObjectInSelectList,NULL);
	// adding the cut station to our undo list
		pRallyObject = (CRallyObject*)pDoc->m_rallyList.GetAt(posInRallyList);
		pos_to_delete = pDoc->m_arrowList.RemoveArrowsForDeletedStation(pRallyObject,&pDoc->m_rallyList,pDoc->GetNumberStations(), &num_deleted);
		i++;
		if (num_deleted > 0 && i == 1) 
			arrow_deleted = true;
		pDoc->ClearDeletedArrowFromUndoRedoList(pos_to_delete);
		if (posInRallyList != NULL) {
			switch (num_deleted) {
			case 0:
				if (how_many_selected == 1) {
					pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,DELETE_STATION); 
				}
				else {
					pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL_START);
					deleted_started = true;
				}
				break;
			case 1:
				if (how_many_selected == 2 && arrow_deleted && !deleted_started) {
					pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,DELETE_STATION); 
				}
				else {
					if (num_deleted == how_many_selected-1) {
						pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL_END);
					}
					else {
						if (arrow_deleted) {
							pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL_START); 
							deleted_started = true;
						} 
						else {
							pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL);
						}
					}
				}
				break;
			default:
				if (num_deleted == how_many_selected-1) 
					pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL_END);
				else 
					pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL);
				break;
			}
/*			if (how_many_selected == 1) 
				pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,DELETE_STATION); 
			else if (how_many_selected == 2 && arrow_deleted) 
				pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,DELETE_STATION); 
			else if (num_deleted == 0 || arrow_deleted) 
				pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL_START);  
			else if (num_deleted == how_many_selected-1) 
				pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL_END); 
			else 
				pDoc->AddUndoStation(rallyObjectInSelectList,posInRallyList,MULDEL);
*/
			num_deleted++;
			// remove from our list and delete the object
			pDoc->RemoveStationFromList(pRallyObject, posInRallyList );

			// on deletion we also have the the created station sitting in the undo stack
			// actually we might have a bunch of stations sitting there with the this position stored
			// so we are going to fix this on the undo

			
			delete pRallyObject;
		}
		pDoc->SetUpInsertPopupMenu();
	}
	if (pDoc->m_arrowList.AnyArrowSelected()) {
		num_deleted = pDoc->m_arrowList.AddSelectedArrowsToUndoList(&pDoc->m_undo_list,DELETE_STATION, &how_many_selected, num_deleted); 
		pDoc->m_arrowList.DeleteSelectedArrows();
	}	

	pDoc->m_arrowList.CleanupArrow(&pDoc->m_rallyList);

	for( posInSelect = this->m_pylons_selected.GetHeadPosition(); posInSelect != NULL; ) {
		pylonObjectInSelectList = (PylonObj*)this->m_pylons_selected.GetNext(posInSelect);

	// adding the cut station to our undo list
		posInRallyList = pDoc->m_pylonList.Find(pylonObjectInSelectList,NULL);

		if (how_many_selected == 1) 
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,DELETE_STATION); 
		else if (num_deleted == 0) 
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,MULDEL_START);  
		else if (num_deleted == how_many_selected-1) 
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,MULDEL_END); 
		else 
			pDoc->AddUndoStation(pylonObjectInSelectList,posInRallyList,MULDEL);
		num_deleted++;
		
		if (posInRallyList != NULL) {
			// remove from our list and delete the object
			
			pPylonObject = (PylonObj*)pDoc->m_pylonList.GetAt(posInRallyList);
			pDoc->m_pylonList.RemoveAt(posInRallyList);

			// on deletion we also have the the created station sitting in the undo stack
			// actually we might have a bunch of stations sitting there with the this position stored
			// so we are going to fix this on the undo

			
			delete pPylonObject;
		}
	}
	for( posInSelect = this->m_text_selected.GetHeadPosition(); posInSelect != NULL; ) {
		textObjectInSelectList = (TextObj*)this->m_text_selected.GetNext(posInSelect);

	// adding the cut station to our undo list
		posInRallyList = pDoc->m_text_list.Find(textObjectInSelectList,NULL);

		if (how_many_selected == 1) 
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,DELETE_STATION); 
		else if (num_deleted == 0) 
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,MULDEL_START);  
		else if (num_deleted == how_many_selected-1) 
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,MULDEL_END); 
		else 
			pDoc->AddUndoStation(textObjectInSelectList,posInRallyList,MULDEL);
		num_deleted++;
		
		if (posInRallyList != NULL) {
			// remove from our list and delete the object
			
			pTextObject = (TextObj*)pDoc->m_text_list.GetAt(posInRallyList);
			pDoc->m_text_list.RemoveAt(posInRallyList);

			// on deletion we also have the the created station sitting in the undo stack
			// actually we might have a bunch of stations sitting there with the this position stored
			// so we are going to fix this on the undo

			
			delete pTextObject;
		}

	}
	for( posInSelect = this->m_special_selected.GetHeadPosition(); posInSelect != NULL; ) {
		specialObjectInSelectList = (SpecialObj*)this->m_special_selected.GetNext(posInSelect);

	// adding the cut station to our undo list
		posInRallyList = pDoc->m_special_list.Find(specialObjectInSelectList,NULL);

		if (how_many_selected == 1) 
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,DELETE_STATION); 
		else if (num_deleted == 0) 
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,MULDEL_START);  
		else if (num_deleted == how_many_selected-1) 
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,MULDEL_END); 
		else 
			pDoc->AddUndoStation(specialObjectInSelectList,posInRallyList,MULDEL);
		num_deleted++;
		
		if (posInRallyList != NULL) {
			// remove from our list and delete the object
			
			pSpecialObject = (SpecialObj*)pDoc->m_special_list.GetAt(posInRallyList);
			pDoc->m_special_list.RemoveAt(posInRallyList);

			// on deletion we also have the the created station sitting in the undo stack
			// actually we might have a bunch of stations sitting there with the this position stored
			// so we are going to fix this on the undo

			
			delete pSpecialObject;
		}

	}
	for( posInSelect = this->m_scribble_selected.GetHeadPosition(); posInSelect != NULL; ) {
		scribbleObjectInSelectList = (Scribble*)this->m_scribble_selected.GetNext(posInSelect);

	// adding the cut station to our undo list
		posInRallyList = pDoc->m_scribbleList.Find(scribbleObjectInSelectList,NULL);

		if (how_many_selected == 1) 
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,DELETE_STATION); 
		else if (num_deleted == 0) 
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,MULDEL_START);  
		else if (num_deleted == how_many_selected-1) 
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,MULDEL_END); 
		else 
			pDoc->AddUndoStation(scribbleObjectInSelectList,posInRallyList,MULDEL);
		num_deleted++;
		
		if (posInRallyList != NULL) {
			// remove from our list and delete the object
			
			pScribbleObject = (Scribble*)pDoc->m_scribbleList.GetAt(posInRallyList);
			pDoc->m_scribbleList.RemoveAt(posInRallyList);

			// on deletion we also have the the created station sitting in the undo stack
			// actually we might have a bunch of stations sitting there with the this position stored
			// so we are going to fix this on the undo

			
			delete pScribbleObject;
		}

	}
	this->ClearAllStationsFromSelectedList(true);
	this->Invalidate(FALSE);

}

void CDogRunView::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();

	if (!pDoc->m_arrowList.AnyArrowSelected() && this->m_text_selected.IsEmpty() && 
		this->m_stations_selected.IsEmpty() && this->m_special_selected.IsEmpty() && 
		this->m_pylons_selected.IsEmpty() && this->m_scribble_selected.IsEmpty()) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}	
}
// use the following four functions to manage selection list for the view
// and set selected flag in rally object 
void CDogRunView::AddStationToSelectedList(CRallyObject *station_selected) {
	POSITION pos = this->m_stations_selected.AddTail(station_selected);
	station_selected->SetSelectedFlag(true);
}
void CDogRunView::RemoveStationFromSelectedList(CRallyObject *station_selected){
	POSITION pos;
	station_selected->SetSelectedFlag(false);
	pos = this->m_stations_selected.Find(station_selected,NULL);
	this->m_stations_selected.RemoveAt(pos);
}
void CDogRunView::AddPylonToSelectedList(PylonObj *pylon_selected) {
	POSITION pos = this->m_pylons_selected.AddTail(pylon_selected);
	pylon_selected->SetSelectedFlag(true);
}
void CDogRunView::RemovePylonFromSelectedList(PylonObj *pylon_selected){
	POSITION pos;
	pylon_selected->SetSelectedFlag(false);
	pos = this->m_pylons_selected.Find(pylon_selected,NULL);
	this->m_pylons_selected.RemoveAt(pos);
}

void CDogRunView::AddTextToSelectedList(TextObj *p_text_selected)
{
	POSITION pos = this->m_text_selected.AddTail(p_text_selected);
	p_text_selected->SetSelectedFlag(true);
}

void CDogRunView::RemoveTextFromSelectedList(TextObj *p_text_unselect)
{
	POSITION pos;
	p_text_unselect->SetSelectedFlag(false);
	pos = this->m_text_selected.Find(p_text_unselect,NULL);
	this->m_text_selected.RemoveAt(pos);
}
void CDogRunView::AddSpecialToSelectedList(SpecialObj *p_special_selected)
{
	POSITION pos = this->m_special_selected.AddTail(p_special_selected);
	p_special_selected->SetSelectedFlag(true);
}

void CDogRunView::RemoveSpecialFromSelectedList(SpecialObj *p_special_selected)
{
	POSITION pos;
	p_special_selected->SetSelectedFlag(false);
	pos = this->m_special_selected.Find(p_special_selected,NULL);
	this->m_special_selected.RemoveAt(pos);
}

void CDogRunView::ClearAllStationsFromSelectedList(bool include_arrows) {
	this->DeSelectAllStations(include_arrows);
	this->m_stations_selected.RemoveAll();
	this->m_pylons_selected.RemoveAll();
	this->m_text_selected.RemoveAll();
	this->m_special_selected.RemoveAll();
	this->m_scribble_selected.RemoveAll();
}
void CDogRunView::AddAllStationsToSelectedList(void){
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRallyObject* pRallyItemInlist;
	PylonObj* pPylonItemInlist;
	Scribble* pScribbleItemInlist;
	TextObj* pTextItemInList;
	SpecialObj *pSpecialItemInList;

	POSITION pos;
	this->ClearAllStationsFromSelectedList(true);
	for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
		pRallyItemInlist->SetSelectedFlag(true);
		this->m_stations_selected.AddTail(pRallyItemInlist);
	}
	for( pos = pDoc->m_pylonList.GetHeadPosition(); pos != NULL; ) {
		pPylonItemInlist = (PylonObj*)pDoc->m_pylonList.GetNext(pos);
		pPylonItemInlist->SetSelectedFlag(true);
		this->m_pylons_selected.AddTail(pPylonItemInlist);
	}	

	for( pos = pDoc->m_text_list.GetHeadPosition(); pos != NULL; ) {
		pTextItemInList = (TextObj*)pDoc->m_text_list.GetNext(pos);
		pTextItemInList->SetSelectedFlag(true);
		this->m_text_selected.AddTail(pTextItemInList);
	}
	for( pos = pDoc->m_special_list.GetHeadPosition(); pos != NULL; ) {
		pSpecialItemInList = (SpecialObj*)pDoc->m_special_list.GetNext(pos);
		pSpecialItemInList->SetSelectedFlag(true);
		this->m_special_selected.AddTail(pSpecialItemInList);
	}
	for( pos = pDoc->m_scribbleList.GetHeadPosition(); pos != NULL; ) {
		pScribbleItemInlist = (Scribble*)pDoc->m_scribbleList.GetNext(pos);
		pScribbleItemInlist->SetSelectedFlag(true);
		this->m_scribble_selected.AddTail(pScribbleItemInlist);
	}
	pDoc->m_arrowList.SelectAllArrows(false);
}
int CDogRunView::IsRotateHandleSelected(void) {
	int howManySelections;
	CRallyObject* pRallyItemInlist;
	SpecialObj *pSpecialItemInlist;

	howManySelections = this->m_stations_selected.GetCount();
	if (howManySelections > 1) return false;// can not rotate more than one selection at a time
	if (howManySelections == 1) {
		// only one selection so get the head
		pRallyItemInlist = (CRallyObject*)this->m_stations_selected.GetHead();
		return pRallyItemInlist->m_handle_selected ;
	}
	howManySelections = this->m_special_selected.GetCount();
	if (howManySelections > 1) return false;// can not rotate more than one selection at a time
	if (howManySelections == 1) {
		// only one selection so get the head
		pSpecialItemInlist = (SpecialObj*)this->m_special_selected.GetHead();
		return pSpecialItemInlist->m_handle_selected ;
	}
	if (howManySelections == 0) return false;// should never call this w/o at least one selection -- but just to be sure
	return false;
}
void CDogRunView::CheckRallyRectInRectAfterMoveOrPaste(void) {
	CRect station_rect;

	CPoint off_set_pt = (1,1);
	
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRallyObject *pRallyItemSelected;
	CClientDC dc(this);
	POSITION pos_one;
	for( pos_one = this->m_stations_selected.GetHeadPosition(); pos_one != NULL; ) {
		pRallyItemSelected = (CRallyObject*)this->m_stations_selected.GetNext(pos_one);
		if (pRallyItemSelected->GetStationID() != IDB_PYLONS) {
			station_rect = pRallyItemSelected->GetStationRect();
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&station_rect,&dc);
			}


			InflateRect(&station_rect, 15,27);
			while(this->CheckRallyRectInRallyRect(pRallyItemSelected)) {
				pRallyItemSelected->OffSetStationRect(&off_set_pt);
				off_set_pt.Offset(1,1);
			}

			station_rect = pRallyItemSelected->GetStationRect();
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&station_rect,&dc);
			}
			InflateRect(&station_rect, 15,27);
		}
	}
	this->Invalidate(FALSE);

}

void CDogRunView::MoveStations(CDC *pDC, CPoint *last_point) {
	CRallyObject *pRallyItemSelected;
	PylonObj *pPylonItemSelected;
	TextObj* pTextItemSelected;
	SpecialObj *pSpecialItemSelected;
	Scribble *pScribbleItemSelected;
	CRect pylon_rect;
	CRect text_rect;
	CRect scribble_rect;
	POSITION pos_one, pos_two, pos_in_rally_list;
	CPoint sp = this->GetScrollPosition();
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPoint  amt_change;
	int num_moved = 0;
	int how_many_stations = 0;
	pDoc->ClearRedoList();

	if (this->m_size_to_fit) {
		pDC->DPtoLP(last_point);
		pDC->DPtoLP(&this->m_int_drag);
		amt_change.x = last_point->x - this->m_int_drag.x;
		amt_change.y = last_point->y - this->m_int_drag.y;
	}
	else {
		amt_change.x = last_point->x - this->m_int_drag.x;
		amt_change.y = last_point->y - this->m_int_drag.y;
	}
	// keep from adding an undo station if nothing changed!
	if (amt_change.x == 0 && amt_change.y == 0) return;
	if (this->m_drag_info) {
		CRect course_info_rect, begining_rect;
		pDoc->m_course_info->GetCourseInfoRect(&begining_rect);
		CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);				
		pRallyItem->SetStationRect(&begining_rect);
		pDoc->AddUndoStation(pRallyItem,NULL,MOVE_INFO);
		delete pRallyItem;
		pDoc->m_course_info->OffSetInfoRect(&amt_change);
		pDoc->m_course_info->GetCourseInfoRect(&course_info_rect);
		InflateRect(&course_info_rect, 10, 10);
		InflateRect(&begining_rect, 10, 10);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&course_info_rect,pDC);
			this->FixRectInFitScreenModeLPtoDP(&begining_rect,pDC);
		}
		OffsetRect(&course_info_rect,-sp.x, -sp.y);
		OffsetRect(&begining_rect,-sp.x, -sp.y);

	}
	else if (this->m_drag_station_list) {
		CRect station_list_rect, begining_rect;
		pDoc->m_station_list->GetStationListRect(&begining_rect);
		CRallyObject *pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);				
		pRallyItem->SetStationRect(&begining_rect);
		pDoc->AddUndoStation(pRallyItem,NULL,MOVE_STATION_LIST);
		delete pRallyItem;
		pDoc->m_station_list->OffSetStationListRect(&amt_change);
		pDoc->m_station_list->GetStationListRect(&station_list_rect);
		InflateRect(&station_list_rect, 10, 10);
		InflateRect(&begining_rect, 10, 10);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&station_list_rect,pDC);
			this->FixRectInFitScreenModeLPtoDP(&begining_rect,pDC);
		}
		OffsetRect(&station_list_rect,-sp.x, -sp.y);
		OffsetRect(&begining_rect,-sp.x, -sp.y);

	}
	else {
		how_many_stations = this->m_stations_selected.GetCount();
		how_many_stations += this->m_pylons_selected.GetCount();
		how_many_stations += this->m_text_selected.GetCount();
		how_many_stations += this->m_special_selected.GetCount();
		how_many_stations += this->m_scribble_selected.GetCount();
		how_many_stations += pDoc->m_arrowList.HowManySelectedArrows();

		num_moved = pDoc->m_arrowList.AddSelectedArrowsToUndoList(&pDoc->m_undo_list,MOVE_STATION,&how_many_stations, 0);
		pDoc->m_arrowList.MoveSelectedArrows(&amt_change);
		for( pos_one = this->m_stations_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pRallyItemSelected = (CRallyObject*)this->m_stations_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_rallyList.Find(pRallyItemSelected,NULL);
			
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE);
			pos_one = pos_two;
			num_moved++;
			RECT station_rect;
			station_rect = pRallyItemSelected->GetStationRect();
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&station_rect,pDC);
			}
			InflateRect(&station_rect, 15,27);
			OffsetRect(&station_rect,-sp.x, -sp.y);
			pRallyItemSelected->OffSetStationRect(&amt_change);

			
			station_rect = pRallyItemSelected->GetStationRect();
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&station_rect,pDC);
			}
			InflateRect(&station_rect, 15,27);
			OffsetRect(&station_rect,-sp.x, -sp.y);
		}
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());
		for( pos_one = this->m_pylons_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pPylonItemSelected = (PylonObj*)this->m_pylons_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_pylonList.Find(pPylonItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE);
			
			pos_one = pos_two;
			num_moved++;
			pPylonItemSelected->GetPylonRect(&pylon_rect);
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&pylon_rect,pDC);
			}
			InflateRect(&pylon_rect, 15,27);
			OffsetRect(&pylon_rect,-sp.x, -sp.y);
			pPylonItemSelected->OffsetXYPos(&amt_change);

			pPylonItemSelected->GetPylonRect(&pylon_rect);
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&pylon_rect,pDC);
			}
			InflateRect(&pylon_rect, 15,27);
			OffsetRect(&pylon_rect,-sp.x, -sp.y);
		}
		for( pos_one = this->m_text_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pTextItemSelected = (TextObj*)this->m_text_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_text_list.Find(pTextItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MULMOVE);
			
			pos_one = pos_two;
			num_moved++;
			pTextItemSelected->GetDisplayTextRect(&text_rect);
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&text_rect,pDC);
			}
			InflateRect(&text_rect, 15,27);
			OffsetRect(&text_rect,-sp.x, -sp.y);
			pTextItemSelected->OffsetTextRect(&amt_change);

			pTextItemSelected->GetDisplayTextRect(&text_rect);

			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&text_rect,pDC);
			}
			InflateRect(&text_rect, 15,27);
			OffsetRect(&text_rect,-sp.x, -sp.y);
		}	
		for( pos_one = this->m_special_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pSpecialItemSelected = (SpecialObj*)this->m_special_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_special_list.Find(pSpecialItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE);
			
			pos_one = pos_two;
			num_moved++;
			CRect special_rect;
			pSpecialItemSelected->GetSpecialRect(&special_rect);
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&special_rect,pDC);
			}
			InflateRect(&special_rect, 15,27);
			OffsetRect(&special_rect,-sp.x, -sp.y);
			pSpecialItemSelected->OffSetSpecialRect(&amt_change);

			pSpecialItemSelected->GetSpecialRect(&special_rect);
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&special_rect,pDC);
			}
			InflateRect(&special_rect, 15,27);
			OffsetRect(&special_rect,-sp.x, -sp.y);
		}
		for( pos_one = this->m_scribble_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pScribbleItemSelected = (Scribble*)this->m_scribble_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_scribbleList.Find(pScribbleItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MULMOVE);
			
			pos_one = pos_two;
			num_moved++;

			scribble_rect = pScribbleItemSelected->m_rectBounding;
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&scribble_rect,pDC);
			}
			InflateRect(&scribble_rect, 15,27);
			OffsetRect(&scribble_rect,-sp.x, -sp.y);
			pScribbleItemSelected->OffsetScribble(&amt_change);

			scribble_rect = pScribbleItemSelected->m_rectBounding;
			if (this->m_size_to_fit) {
				this->FixRectInFitScreenModeLPtoDP(&scribble_rect,pDC);
			}
			InflateRect(&scribble_rect, 15,27);
			OffsetRect(&scribble_rect,-sp.x, -sp.y);
		}

	}		
	this->Invalidate(FALSE);
	this->CheckRallyRectInRectAfterMoveOrPaste();

}

void CDogRunView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here

	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	int tot_stat_selected, tot_spec_selected, tot_arrow_selected, 
		tot_pylon_selected, tot_text_selected, total_selected, tot_scribble_selected;
	tot_stat_selected = this->m_stations_selected.GetCount();
	tot_spec_selected = this->m_special_selected.GetCount();
	tot_pylon_selected = this->m_pylons_selected.GetCount();
	tot_scribble_selected = this->m_scribble_selected.GetCount();
	tot_arrow_selected = pDoc->m_arrowList.GetTotalSelected();
	
	tot_text_selected = this->m_text_selected.GetCount();
	if (pDoc->m_station_list->GetStationListSelected()) 
		tot_text_selected++;
	if (pDoc->m_course_info->GetCourseInfoSelected()) 
		tot_text_selected++;

	total_selected = tot_stat_selected + tot_spec_selected + tot_pylon_selected + tot_arrow_selected + tot_text_selected + tot_scribble_selected;
	if ((total_selected == 1 && tot_text_selected == 1)) {
		if (menu.LoadMenu(ID_POPUP_TX_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	if (total_selected == 1 && tot_arrow_selected == 1) {
		if (menu.LoadMenu(ID_POPUP_AR_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	if (total_selected == 1 && tot_scribble_selected == 1) {
		if (menu.LoadMenu(ID_POPUP_SCR_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	if (total_selected < 1) {
		if (menu.LoadMenu(ID_POPUP_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	if (total_selected > 1) {
		if (menu.LoadMenu(ID_POPUP_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			if (tot_stat_selected > 1) {
				pPopup->AppendMenu(MF_SEPARATOR);
				pPopup->AppendMenu(MF_STRING,ID_ST_PROP_DIALOG,"Station Properties...");
			}

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	if (tot_spec_selected == 1 && total_selected == 1) {
		if (menu.LoadMenu(ID_POPUP_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	if (total_selected == 1 && tot_stat_selected == 1) {
		if (menu.LoadMenu(ID_POPUP_ST_MENU)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			CMenu* pInsert, *pChangeTo;
			int iPos =pPopup->GetMenuItemCount();

			pInsert = pPopup->GetSubMenu(iPos-4);
			ASSERT(pInsert != NULL);
			this->UpdateInsertAfterMenu(pInsert);
			pChangeTo = pPopup->GetSubMenu(iPos-3);
			ASSERT(pInsert != NULL);
			this->UpdateChangeToMenu(pChangeTo);
			pDoc->m_course_info->GetCourseInfo(&course_info);
			int i;
			if (course_info.m_type_of_course == AKC_COURSE) {
				i =	pPopup->EnableMenuItem(iPos-6,MF_BYPOSITION   | MF_ENABLED );
				i = pPopup->EnableMenuItem(iPos-5 ,MF_BYPOSITION   | MF_GRAYED );
			
			}
			else {
				i = pPopup->EnableMenuItem(iPos-6,MF_BYPOSITION   | MF_ENABLED );
				i = pPopup->EnableMenuItem(iPos-5,MF_BYPOSITION   | MF_GRAYED );

			}
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); // route commands through main window
			return;
		}
	}
	
}
void CDogRunView::UpdateInsertAfterMenu(CMenu* insert_menu) {

	CDogRunDoc* pDoc = GetDocument();
	int iPos;
	for (iPos = insert_menu->GetMenuItemCount()-1; iPos > 0; iPos--)
		insert_menu->DeleteMenu(iPos, MF_BYPOSITION);

	POSITION pos;
	CRallyObject* pRallyItemInlist;
	CString station_number, station_desc;
	CString add_string;
	int num_of_station, akc_number;
	int menu_cmd_id;
	for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
		num_of_station = pRallyItemInlist->GetStationNumber();
		akc_number = pRallyItemInlist->GetAKCNumber();
		if (num_of_station > 0) {
			station_number.Format("%d",num_of_station);
			station_desc = StationMapper::GetAKCDescrptionFromAKCNumber(akc_number);
			add_string = station_number + ": " + station_desc;
			menu_cmd_id = num_of_station + ID_ITEM1;
			insert_menu->InsertMenu(num_of_station, MF_STRING | MF_BYPOSITION,menu_cmd_id, add_string);
		}
	}

}
void CDogRunView::UpdateChangeToMenu(CMenu* insert_menu) {
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);

	int iPos;
	for (iPos = insert_menu->GetMenuItemCount(); iPos >= 0; iPos--)
		insert_menu->DeleteMenu(iPos, MF_BYPOSITION);

	CourseInfo course_info;
	int class_cutoff, i, menu_cmd_id;
	CString add_string;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	if (course_info.m_type_of_course == AKC_COURSE) {

		CStringList Items;
		StationMapper::GetStationDescriptionByAKCType(course_info.m_class,Items);
		POSITION Position = Items.GetHeadPosition();
		i=0;
		while (Position){
			add_string = Items.GetNext(Position);
			menu_cmd_id = i + ID_CH_MENU_1;
			insert_menu->InsertMenu(i, MF_STRING | MF_BYPOSITION,menu_cmd_id, add_string);
			i++;
		}
	}
	else {
		switch (course_info.m_class) {
		case NOVICE:
			class_cutoff = 32;
			break;
		case ADVANCED:
			class_cutoff = 53;
			break;
		case EXCELLENT:
			class_cutoff = 65;
			break;
		case MASTER:
		case TRAINING:
			class_cutoff = 76;
			break;
		}
		for (i=0;i<class_cutoff;i++) {
			add_string = pDoc->m_rallyList.apdt_station_names[i+1];
			menu_cmd_id = i + ID_CH_MENU_1;
			insert_menu->InsertMenu(i, MF_STRING | MF_BYPOSITION,menu_cmd_id, add_string);
		}
	}


}
void CDogRunView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint sp = this->GetScrollPosition();
	point.y += sp.y;
	point.x += sp.x;
	CClientDC dc(this);
	if (this->m_size_to_fit) {
		this->ChangeDCToSizeToWindow(&dc);
		dc.DPtoLP(&point);
	}
	this->m_popup_point = point;
	this->HitPointInAnyRallyRect(&point);
	CScrollView::OnRButtonDown(nFlags, point);
}

void CDogRunView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_DOWN || nChar == VK_RIGHT || nChar == VK_LEFT || nChar == VK_UP) {
		
		CPoint  amt_change;

		if (nChar == VK_DOWN) {
 			amt_change.x = 0;
			amt_change.y = 10;
		}
		if (nChar == VK_RIGHT){
 			amt_change.x = 10;
			amt_change.y = 0;
		}
		if (nChar == VK_LEFT){
 			amt_change.x = -10;
			amt_change.y = 0;
		}
		if (nChar == VK_UP){
 			amt_change.x = 0;
			amt_change.y = -10;
		}	
		CClientDC dc(this);	

		CRallyObject *pRallyItemSelected;
		PylonObj *pPylonItemSelected;
		TextObj* pTextItemSelected;
		SpecialObj *pSpecialItemSelected;
		Scribble *pScribbleItemSelected;
		POSITION pos_one, pos_two, pos_in_rally_list;
		CPoint sp = this->GetScrollPosition();
		CDogRunDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		int num_moved = 0;
		int how_many_stations = 0;
		pDoc->ClearRedoList();
		how_many_stations = this->m_stations_selected.GetCount();
		how_many_stations += this->m_pylons_selected.GetCount();
		how_many_stations += this->m_special_selected.GetCount();
		how_many_stations += this->m_text_selected.GetCount();
		how_many_stations += this->m_scribble_selected.GetCount();
		how_many_stations += pDoc->m_arrowList.HowManySelectedArrows();
		
		num_moved = pDoc->m_arrowList.AddSelectedArrowsToUndoList(&pDoc->m_undo_list,MOVE_STATION,&how_many_stations, 0);
		pDoc->m_arrowList.MoveSelectedArrows(&amt_change);

		for( pos_one = this->m_stations_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pRallyItemSelected = (CRallyObject*)this->m_stations_selected.GetNext(pos_two);

			pos_in_rally_list = pDoc->m_rallyList.Find(pRallyItemSelected,NULL);

			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE);
			num_moved++;
			pos_one = pos_two;
			RECT station_rect;

			station_rect = pRallyItemSelected->GetStationRect();
			if (this->m_size_to_fit) {
				this->ChangeDCToSizeToWindow(&dc);
				this->FixRectInFitScreenModeLPtoDP(&station_rect,&dc);
			}		
			InflateRect(&station_rect,	50, 50);
			OffsetRect(&station_rect,-sp.x, -sp.y);
			pRallyItemSelected->OffSetStationRect(&amt_change);
			this->Invalidate(FALSE);
		}
		pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());
		for( pos_one = this->m_pylons_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pPylonItemSelected = (PylonObj*)this->m_pylons_selected.GetNext(pos_two);

			pos_in_rally_list = pDoc->m_pylonList.Find(pPylonItemSelected,NULL);

			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE);

			pos_one = pos_two;
			num_moved++;
			CRect pylon_rect;

			pPylonItemSelected->GetPylonRect(&pylon_rect);
			if (this->m_size_to_fit) {
				this->ChangeDCToSizeToWindow(&dc);
				this->FixRectInFitScreenModeLPtoDP(&pylon_rect,&dc);
			}		
			InflateRect(&pylon_rect,50, 50);
			OffsetRect(&pylon_rect,-sp.x, -sp.y);
			pPylonItemSelected->OffsetXYPos(&amt_change);
			this->Invalidate(FALSE);
		}
		for( pos_one = this->m_text_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pTextItemSelected = (TextObj*)this->m_stations_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_text_list.Find(pTextItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pTextItemSelected,pos_in_rally_list,MULMOVE);
			pos_one = pos_two;
			num_moved++;
			CRect text_rect;

			pTextItemSelected->GetDisplayTextRect(&text_rect);
			if (this->m_size_to_fit) {
				this->ChangeDCToSizeToWindow(&dc);
				this->FixRectInFitScreenModeLPtoDP(&text_rect,&dc);
			}		
			InflateRect(&text_rect,50, 50);
			OffsetRect(&text_rect,-sp.x, -sp.y);
			pTextItemSelected->OffsetTextRect(&amt_change);
			this->Invalidate(FALSE);
		}
		for( pos_one = this->m_special_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pSpecialItemSelected = (SpecialObj*)this->m_special_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_special_list.Find(pSpecialItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE);
			pos_one = pos_two;
			num_moved++;
			CRect special_rect;
			pSpecialItemSelected->GetSpecialRect(&special_rect);
			if (this->m_size_to_fit) {
				this->ChangeDCToSizeToWindow(&dc);
				this->FixRectInFitScreenModeLPtoDP(&special_rect,&dc);
			}
			InflateRect(&special_rect, 15,27);
			OffsetRect(&special_rect,-sp.x, -sp.y);
			pSpecialItemSelected->OffSetSpecialRect(&amt_change);
			this->Invalidate(FALSE);
		}
		for( pos_one = this->m_scribble_selected.GetHeadPosition(); pos_one != NULL; ) {
			pos_two = pos_one;
			pScribbleItemSelected = (Scribble*)this->m_scribble_selected.GetNext(pos_two);
			pos_in_rally_list = pDoc->m_scribbleList.Find(pScribbleItemSelected,NULL);
			if (how_many_stations == 1) 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MOVE_STATION);
			else if (num_moved == 0) 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MULMOVE_START);
			else if (num_moved == how_many_stations-1) 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MULMOVE_END);
			else 
				pDoc->AddUndoStation(pScribbleItemSelected,pos_in_rally_list,MULMOVE);
			pos_one = pos_two;
			num_moved++;
			CRect scribble_rect;
			scribble_rect = pScribbleItemSelected->GetBoundingRect();
			if (this->m_size_to_fit) {
				this->ChangeDCToSizeToWindow(&dc);
				this->FixRectInFitScreenModeLPtoDP(&scribble_rect,&dc);
			}
			InflateRect(&scribble_rect, 15,27);
			OffsetRect(&scribble_rect,-sp.x, -sp.y);
			pScribbleItemSelected->OffsetScribble(&amt_change);
			this->Invalidate(FALSE);
		}
		this->CheckRallyRectInRectAfterMoveOrPaste();
		this->Invalidate(FALSE);
	}
		
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDogRunView::OnDocInfo() 
{
	// TODO: Add your command handler code here
	DocInfodlg docInfo;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	docInfo.m_author = pDoc->m_doc_author;
	docInfo.m_notes = pDoc->m_doc_notes;
	docInfo.m_created = pDoc->m_doc_created.Format( "%A, %B %d, %Y" );
	docInfo.m_modified = pDoc->m_doc_modified.Format( "%A, %B %d, %Y" );
	docInfo.m_printed = pDoc->m_doc_printed.Format( "%A, %B %d, %Y" );
	docInfo.DoModal();
	pDoc->m_doc_author = docInfo.m_author;
	pDoc->m_doc_notes = docInfo.m_notes;
}

void CDogRunView::OnCourseInfo() 
{
	// TODO: Add your command handler code here
	CCourseInfoDlg courseInfo;

	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	courseInfo.m_compete = course_info.m_competation;
	courseInfo.m_type_course = course_info.m_type_of_course;
	courseInfo.m_sub_class = course_info.m_sub_class;
	courseInfo.m_class = course_info.m_class;
	courseInfo.m_date_compete = course_info.m_date_compete ;
	courseInfo.m_location = course_info.m_location;
	courseInfo.m_organization = course_info.m_organization;
	courseInfo.m_judge = course_info.m_judge;
	courseInfo.m_length.Format("%.1f", course_info.m_ring_lenght);
	courseInfo.m_width.Format("%.1f", course_info.m_ring_width);
	courseInfo.m_grid_spacing.Format("%.1f", course_info.m_grid_spacing);

	courseInfo.m_show_class = course_info.m_cmt_class;
	courseInfo.m_show_comp = course_info.m_cmt_comp_name;
	courseInfo.m_show_date = course_info.m_cmt_date;
	courseInfo.m_show_judge = course_info.m_cmt_judge_name;
	courseInfo.m_show_location = course_info.m_cmt_location;
	courseInfo.m_show_organization = course_info.m_cmt_organization;
	courseInfo.m_show_subclass = course_info.m_cmt_subclass;

	int this_year = course_info.m_date_compete.GetYear();
	this_year = courseInfo.m_date_compete.GetYear();
	
	if (course_info.m_class == TRAINING) {
		courseInfo.m_judge_inst = "Instructor:";
	}
	else {
		courseInfo.m_judge_inst = "Judge:";
	}
	int response = courseInfo.DoModal();
	if (response == IDCANCEL) return;
	pDoc->SetModifiedFlag();
	pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	
	course_info.m_type_of_course = courseInfo.m_type_course;
	course_info.m_sub_class = courseInfo.m_sub_class;
	course_info.m_competation = courseInfo.m_compete;
	course_info.m_class = courseInfo.m_class;
	course_info.m_date_compete = courseInfo.m_date_compete;
	course_info.m_location = courseInfo.m_location;
	course_info.m_organization= courseInfo.m_organization;
	course_info.m_judge = courseInfo.m_judge;
	course_info.m_ring_lenght = atof(courseInfo.m_length);
	course_info.m_ring_width = atof(courseInfo.m_width);
	course_info.m_grid_spacing = atof(courseInfo.m_grid_spacing);

	course_info.m_cmt_class = courseInfo.m_show_class;
	course_info.m_cmt_comp_name = courseInfo.m_show_comp;
	course_info.m_cmt_date = courseInfo.m_show_date;
	course_info.m_cmt_judge_name = courseInfo.m_show_judge;
	course_info.m_cmt_organization = courseInfo.m_show_organization;
	course_info.m_cmt_location = courseInfo.m_show_location;
	course_info.m_cmt_subclass = courseInfo.m_show_subclass;
			
	pDoc->m_course_info->SetCourseInfo(&course_info);

	pDoc->SetUpChangeToPopupMenu();
	if (courseInfo.set_defaults) {
		pDoc->SetApplicationDefaults(&course_info);
		pDoc->SetApplicationDefaultsCourseText();
	}
	
	this->SetUpCourseVariablesAndGrid();
	pDoc->SetUpAddMenu();
	this->Invalidate(FALSE);
}

void CDogRunView::OnUpdateViewCourseInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetCheck(pDoc->m_course_info->ViewCourse());
}

void CDogRunView::OnViewCourseInfo() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_course_info->ViewCourse()) {
		pDoc->m_course_info->SetViewCourseInfo(FALSE);
	}
	else {
		pDoc->m_course_info->SetViewCourseInfo(TRUE);
	}

//	Invalidate(TRUE);
	this->Invalidate(FALSE);
}


void CDogRunView::OnSizeToScreen() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (this->m_size_to_fit) {
		this->m_size_to_fit = false;
		CSize scroll_size = this->m_sizeTotal;
		scroll_size.cx += 450;
		scroll_size.cy += 450;
		this->SetScrollSizes(MM_TEXT,scroll_size);
		pDoc->m_course_info->SetSizeToFit(false);

	}
	else {
		this->m_size_to_fit = true;
		SIZE no_size;
		no_size.cx = 0;
		no_size.cy = 0;
		this->SetScrollSizes(MM_TEXT,no_size);
		pDoc->m_course_info->SetSizeToFit(true);

	}
	
	this->Invalidate(FALSE);
}

void CDogRunView::OnUpdateSizeToScreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(this->m_size_to_fit);	
}

void CDogRunView::OnDrawFinish() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FINISH;	
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawFinish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawStart() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_START;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_START) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSithaltdown() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SITHALTDOWN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawSithaltdown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SITHALTDOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnUpdateForwardHalt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SITHALTDOWN || this->m_SelectedShapeOnToolBar == ID_DRAW_SITHALT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_SIT_STAND
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_HALTWALK || this->m_SelectedShapeOnToolBar == ID_DRAW_DOWNWALK
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_DOWNSIT || this->m_SelectedShapeOnToolBar == ID_DRAW_STANDDOWN
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_STANDSIT || this->m_SelectedShapeOnToolBar == ID_DRAW_SLOWFORWARDFROMSIT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_STAND) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawHaltwalk() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HALTWALK;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawHaltwalk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALTWALK) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawDownwalk() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_DOWNWALK;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawDownwalk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_DOWNWALK) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawStand() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_STAND;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawStand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING ) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_STAND) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawDownsit() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_DOWNSIT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawDownsit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_DOWNSIT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawLeaveAboutReturn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_LEAVE_ABOUT_RET;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateLeaveAboutReturn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_LEAVE_ABOUT_RET) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawDogCircleForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_HALT_CIRCLE_FOR;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDogCircleForwar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_HALT_CIRCLE_FOR) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawHaltLeaveRecall() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_HALT_LEAVE_RECALL;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateHaltLeaveRecall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_HALT_LEAVE_RECALL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawStanddown() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_STANDDOWN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawStanddown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_STANDDOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawStandwalk() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_STANDWALK;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawStandwalk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_STANDWALK) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawSlowForwardFromSit() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SLOWFORWARDFROMSIT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateSlowForwardFromSit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE || course_info.m_class == ADVANCED) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SLOWFORWARDFROMSIT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawLeaveAboutRecallFinishRight() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_LEAVE_ABT_REC_FIN_R;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateLeaveAboutRecallFinishRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE || course_info.m_class == ADVANCED) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_LEAVE_ABT_REC_FIN_R) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawLeaveAboutRecallFinishLeft() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_LEAVE_ABT_REC_FIN_L;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateLeaveAboutRecallFinishLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE || course_info.m_class == ADVANCED) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_LEAVE_ABT_REC_FIN_L) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}



void CDogRunView::OnDrawStandsit() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_STANDSIT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawStandsit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_STANDSIT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSitstand() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SIT_STAND;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawSitstand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_STANDSIT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnChStationNum() 
{
	// TODO: Add your command handler code here
	RenumberDlg renumber;
	renumber.DoModal(GetDocument(), (CRallyObject*)this->m_stations_selected.GetHead());

}

void CDogRunView::OnUpdateChStationNum(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here	

	if (m_stations_selected.GetCount() != 1) {
		pCmdUI->Enable(FALSE);
	}
	else {
		CRallyObject *pRallyItemSelected;
		pRallyItemSelected = (CRallyObject*)this->m_stations_selected.GetHead();
		if (pRallyItemSelected->GetStationNumber() != 0)
			pCmdUI->Enable(TRUE);
		else 
			pCmdUI->Enable(FALSE);

	}
}
void CDogRunView::RotateStationByDegrees(int rot_degrees) {
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClientDC dc(this);
	POSITION pos_in_rally_list, pos_one, pos_two;
	int num_rotated = 0, how_many_stations = 0;
	CRallyObject *pRallyItemSelected;
	SpecialObj *pSpecialItemSelected;
	if (this->m_size_to_fit) {
		this->ChangeDCToSizeToWindow(&dc);
	}
	how_many_stations = this->m_stations_selected.GetCount();
	how_many_stations += this->m_special_selected.GetCount();

	for( pos_one = this->m_stations_selected.GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;

		pRallyItemSelected = (CRallyObject*)this->m_stations_selected.GetNext(pos_two);
		pos_in_rally_list = pDoc->m_rallyList.Find(pRallyItemSelected,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MOVE_STATION); // works for rotate station also
		else if (num_rotated == 0) 
			pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE_START);// works for rotate station also
		else if (num_rotated == how_many_stations-1) 
			pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE_END);// works for rotate station also
		else 
			pDoc->AddUndoStation(pRallyItemSelected,pos_in_rally_list,MULMOVE);// works for rotate station also
		num_rotated++;
		pos_one = pos_two;
		switch(rot_degrees) {
		case 0:
			pRallyItemSelected->SetStationRotateMeasurements(1.0, 0.0, 0.0, 1.0);
			break;
		case 90:
			pRallyItemSelected->SetStationRotateMeasurements(0, 1, -1, 0);
			break;
		case 180:
			pRallyItemSelected->SetStationRotateMeasurements(-1, 0.0, 0.0, -1);
			break;
		case 270:
			pRallyItemSelected->SetStationRotateMeasurements(0, -1, 1, 0);
			break;
		default:
			pRallyItemSelected->CalculateRotateMeasurements(rot_degrees);
			break;
		}
		RECT invalid_rect = pRallyItemSelected->GetStationRect();
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&invalid_rect,&dc);
		}
		CPoint sp = this->GetScrollPosition();

		OffsetRect(&invalid_rect,-sp.x, -sp.y);

		InflateRect(&invalid_rect,15,15);

	}
	for( pos_one = this->m_special_selected.GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;

		pSpecialItemSelected = (SpecialObj*)this->m_special_selected.GetNext(pos_two);
		
		pos_in_rally_list = pDoc->m_special_list.Find(pSpecialItemSelected,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MOVE_STATION); // works for rotate station also
		else if (num_rotated == 0) 
			pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE_START);// works for rotate station also
		else if (num_rotated == how_many_stations-1) 
			pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE_END);// works for rotate station also
		else 
			pDoc->AddUndoStation(pSpecialItemSelected,pos_in_rally_list,MULMOVE);// works for rotate station also

		num_rotated++;
		pos_one = pos_two;
		switch(rot_degrees) {
		case 0:
			pSpecialItemSelected->SetRotateMeasurements(1.0, 0.0, 0.0, 1.0);
			break;
		case 90:
			pSpecialItemSelected->SetRotateMeasurements(0, 1, -1, 0);
			break;
		case 180:
			pSpecialItemSelected->SetRotateMeasurements(-1, 0.0, 0.0, -1);
			break;
		case 270:
			pSpecialItemSelected->SetRotateMeasurements(0, -1, 1, 0);
			break;
		}

	}
	this->Invalidate(FALSE);
}

void CDogRunView::OnZeroDegrees() 
{
	// TODO: Add your command handler code here
	this->RotateStationByDegrees(0);

}

void CDogRunView::OnUpdateZeroDegrees(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_stations_selected.GetCount() == 0 && this->m_special_selected.GetCount() == 0) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}	
}

void CDogRunView::OnNinetyCcw() 
{
	// TODO: Add your command handler code here
	this->RotateStationByDegrees(270);
	return;
}

void CDogRunView::OnUpdateNinetyCcw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_stations_selected.GetCount() == 0 && this->m_special_selected.GetCount() == 0) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}		
}

void CDogRunView::OnNinetyCw() 
{
	// TODO: Add your command handler code here
	this->RotateStationByDegrees(90);
	return;
}

void CDogRunView::OnUpdateNinetyCw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_stations_selected.GetCount() == 0 && this->m_special_selected.GetCount() == 0) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}	
}

void CDogRunView::OnOneeighty() 
{
	// TODO: Add your command handler code here
	this->RotateStationByDegrees(180);

}

void CDogRunView::OnUpdateOneeighty(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_stations_selected.GetCount() == 0 && this->m_special_selected.GetCount() == 0) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}		
}

void CDogRunView::OnAlignHoriz() 
{
	// TODO: Add your command handler code here
	int off_set;
	RECT station_rect, invalid_rect;
	CRect pylon_rect;
	POSITION pos_one, pos_two, pos_in_rally_list, pos;
	CClientDC dc(this);
	CPoint sp = this->GetScrollPosition();
	POINT station_point, first_point;
	CRallyObject *pRallyObjectInSelectList;
	PylonObj *pPylonItemSelected, *pPylonObjectInSelectList;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->ClearRedoList();
	first_point.x = first_point.y = -1;
	int num_moved = 1;
	int how_many_stations = 0;
	how_many_stations = this->m_stations_selected.GetCount();
	pos = this->m_stations_selected.GetTailPosition();
	if (pos != NULL) {
		pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetTail();
		first_point = pRallyObjectInSelectList->GetStationMidPoint();
	}
	

	for( pos_one = this->m_stations_selected.GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;
		pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetNext(pos_two);

		pos_in_rally_list = pDoc->m_rallyList.Find(pRallyObjectInSelectList,NULL);

		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MOVE_STATION);
		else if (num_moved == 1) 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MULMOVE_START);
		else if (pos_two == NULL) 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MULMOVE_END);
		else 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MULMOVE);
		pos_one = pos_two;

		invalid_rect = station_rect = pRallyObjectInSelectList->GetStationRect();
		InflateRect(&invalid_rect, 15,15);
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			this->FixRectInFitScreenModeLPtoDP(&invalid_rect,&dc);
		}
		OffsetRect(&invalid_rect,-sp.x, -sp.y);
		station_point = pRallyObjectInSelectList->GetStationMidPoint();

		off_set = first_point.y - station_point.y;
		station_rect.top += off_set;
		station_rect.bottom += off_set;

		pRallyObjectInSelectList->SetStationRect(&station_rect);
		InflateRect(&station_rect, 15,15);
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			this->FixRectInFitScreenModeLPtoDP(&station_rect,&dc);
		}
		OffsetRect(&station_rect,-sp.x, -sp.y);
		num_moved++;
	}
	num_moved = 1;
	how_many_stations = this->m_pylons_selected.GetCount();
	if (first_point.x == -1 && first_point.y == -1) {
		pPylonObjectInSelectList = (PylonObj*)this->m_pylons_selected.GetTail();
		pPylonObjectInSelectList->GetXYPosition(&first_point);
	}
	for( pos_one = this->m_pylons_selected.GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;
		pPylonItemSelected = (PylonObj*)this->m_pylons_selected.GetNext(pos_two);
		pos_in_rally_list = pDoc->m_pylonList.Find(pPylonItemSelected,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MOVE_STATION);
		else if (num_moved == 1) 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_START);
		else if (pos_two == NULL) 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_END);
		else 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE);
		
		pos_one = pos_two;
		pPylonItemSelected->GetPylonRect(&pylon_rect);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&pylon_rect,&dc);
		}
		InflateRect(&pylon_rect, 15,27);
		OffsetRect(&pylon_rect,-sp.x, -sp.y);
		pPylonItemSelected->GetXYPosition(&station_point);
		off_set = first_point.y - station_point.y;
		pPylonItemSelected->GetPylonRect(&pylon_rect);
		pylon_rect.top += off_set;
		pylon_rect.bottom += off_set;
		pPylonItemSelected->SetPylonRect(&pylon_rect);
		InflateRect(&pylon_rect, 15,27);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&pylon_rect,&dc);
		}
		OffsetRect(&pylon_rect,-sp.x, -sp.y);
		num_moved++;

	}
	pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());

	this->Invalidate(FALSE);
}

void CDogRunView::OnUpdateAlignHoriz(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int num_items_selected;
	num_items_selected = this->m_stations_selected.GetCount() + this->m_pylons_selected.GetCount();
	if (num_items_selected > 1) {
		pCmdUI->Enable(TRUE);
	}
	else {
		pCmdUI->Enable(FALSE);
	}			
}

void CDogRunView::OnAlignVert() 
{
	// TODO: Add your command handler code here
	int off_set;
	RECT station_rect, invalid_rect;
	CRect pylon_rect;
	POSITION pos_one, pos_two, pos_in_rally_list,pos;
	CClientDC dc(this);
	POINT first_point, station_point;
	CRallyObject *pRallyObjectInSelectList;
	PylonObj *pPylonItemSelected, *pPylonObjectInSelectList;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPoint sp = this->GetScrollPosition();
	pDoc->ClearRedoList();
	first_point.x = first_point.y = -1;

	int num_moved = 1;
	int how_many_stations = 0;
	how_many_stations = this->m_stations_selected.GetCount();
	pos = this->m_stations_selected.GetTailPosition();
	if (pos != NULL) {
		pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetTail();
		first_point = pRallyObjectInSelectList->GetStationMidPoint();
	}


	for( pos_one = this->m_stations_selected.GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;
		pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetNext(pos_two);

		pos_in_rally_list = pDoc->m_rallyList.Find(pRallyObjectInSelectList,NULL);

		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MOVE_STATION);
		else if (num_moved == 1) 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MULMOVE_START);
		else if (pos_two == NULL) 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MULMOVE_END);
		else 
			pDoc->AddUndoStation(pRallyObjectInSelectList,pos_in_rally_list,MULMOVE);
		pos_one = pos_two;
		
		invalid_rect = station_rect = pRallyObjectInSelectList->GetStationRect();
		InflateRect(&invalid_rect, 15,27);
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			this->FixRectInFitScreenModeLPtoDP(&invalid_rect,&dc);
		}
		OffsetRect(&invalid_rect,-sp.x, -sp.y);
		station_point = pRallyObjectInSelectList->GetStationMidPoint();
		off_set = first_point.x - station_point.x;
		station_rect.left += off_set;
		station_rect.right += off_set;
		pRallyObjectInSelectList->SetStationRect(&station_rect);
		InflateRect(&station_rect, 15,27);
		if (this->m_size_to_fit) {
			this->ChangeDCToSizeToWindow(&dc);
			this->FixRectInFitScreenModeLPtoDP(&station_rect,&dc);
		}
		OffsetRect(&station_rect,-sp.x, -sp.y);

		num_moved++;
	}
	num_moved = 1;
	how_many_stations = this->m_pylons_selected.GetCount();
	if (first_point.x == -1 && first_point.y == -1) {
		pPylonObjectInSelectList = (PylonObj*)this->m_pylons_selected.GetTail();
		pPylonObjectInSelectList->GetXYPosition(&first_point);
	}
	for( pos_one = this->m_pylons_selected.GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;
		pPylonItemSelected = (PylonObj*)this->m_pylons_selected.GetNext(pos_two);
		pos_in_rally_list = pDoc->m_pylonList.Find(pPylonItemSelected,NULL);
		if (how_many_stations == 1) 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MOVE_STATION);
		else if (num_moved == 1) 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_START);
		else if (pos_two == NULL) 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE_END);
		else 
			pDoc->AddUndoStation(pPylonItemSelected,pos_in_rally_list,MULMOVE);
		
		pos_one = pos_two;
		pPylonItemSelected->GetPylonRect(&pylon_rect);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&pylon_rect,&dc);
		}
		InflateRect(&pylon_rect, 15,27);
		OffsetRect(&pylon_rect,-sp.x, -sp.y);
		pPylonItemSelected->GetXYPosition(&station_point);
		off_set = first_point.x - station_point.x;
		pPylonItemSelected->GetPylonRect(&pylon_rect);
		pylon_rect.left += off_set;
		pylon_rect.right += off_set;
		pPylonItemSelected->SetPylonRect(&pylon_rect);
		InflateRect(&pylon_rect, 15,27);
		if (this->m_size_to_fit) {
			this->FixRectInFitScreenModeLPtoDP(&pylon_rect,&dc);
		}
		OffsetRect(&pylon_rect,-sp.x, -sp.y);
		num_moved++;

	}
	pDoc->m_arrowList.MoveArrowsOnStationMove(&this->m_stations_selected, &pDoc->m_rallyList, pDoc->GetNumberStations());
	this->Invalidate(FALSE);
}

void CDogRunView::OnUpdateAlignVert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int num_items_selected;
	num_items_selected = this->m_stations_selected.GetCount() + this->m_pylons_selected.GetCount();
	if (num_items_selected > 1) {
		pCmdUI->Enable(TRUE);
	}
	else {
		pCmdUI->Enable(FALSE);
	}			
}
void CDogRunView::OnInsertAfter(UINT nID) 
{
	// TODO: Add your command handler code here
	int insert_after_num;

	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->ClearRedoList();
	pDoc->ClearUndoList();
	insert_after_num = nID - ID_ITEM1;
	CRallyObject *selected_station;
	selected_station = (CRallyObject *)this->m_stations_selected.GetHead();
	POSITION pos_in_rally_list =  pDoc->m_rallyList.Find(selected_station, NULL);
	pDoc->AddUndoStation(selected_station, pos_in_rally_list,INSERT_AT);
	pDoc->RenumberStations(insert_after_num, INSERT_AT, selected_station, false);

	pDoc->UpdateAllViews(NULL,CHANGE_STATION,NULL);
}

void CDogRunView::OnUpdateInsertAfter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int string_number;
	if (m_stations_selected.GetCount() == 1) {
		CRallyObject *selected_station;
		selected_station = (CRallyObject *)this->m_stations_selected.GetHead();
		string_number = selected_station->GetStringNumber();
		if (string_number == ID_DRAW_START || string_number == ID_DRAW_FINISH || string_number == ID_PYLONS) {
			pCmdUI->Enable(FALSE);
		} 
		else {
			UINT userID = selected_station->GetStationNumber() + ID_ITEM1 - 1;
			UINT sec_userID = selected_station->GetStationNumber() + ID_ITEM1;

//			if (userID == pCmdUI->m_nID || sec_userID == pCmdUI->m_nID) {
			if (sec_userID == pCmdUI->m_nID) {
				pCmdUI->Enable(FALSE);
			}
			else {
				pCmdUI->Enable(TRUE);
			}
		}
	}
	else {
		pCmdUI->Enable(FALSE);
	}			
}
void CDogRunView::OnChangeTo(UINT nID) 
{
	// TODO: Add your command handler code here
	int new_akc_num;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CRallyObject *selected_station;
	selected_station = (CRallyObject *)this->m_stations_selected.GetHead();
	POSITION pos_in_rally_list =  pDoc->m_rallyList.Find(selected_station, NULL);
	new_akc_num = StationMapper::GetAKCidFromComboBoxSelection(nID - ID_CH_MENU_1);
//	new_akc_num = nID - ID_CITEM1 + 1;
	pDoc->UpdateRallyList(-1,new_akc_num,pos_in_rally_list);

}

void CDogRunView::OnUpdateChangeTo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	unsigned int akc_number;
	if (m_stations_selected.GetCount() == 1) {
		CRallyObject *selected_station;
		selected_station = (CRallyObject *)this->m_stations_selected.GetHead();
		akc_number = selected_station->GetAKCNumber();
		int choice = StationMapper::GetComboBoxSelectionFromAKCid(akc_number);
		UINT userID = pCmdUI->m_nID - ID_CH_MENU_1;
		if (this->m_type_course == AKC_COURSE) {
			if (userID == choice || akc_number == 50/*honor station*/ || akc_number == -1 || akc_number == 1 || akc_number == 2 || akc_number == 299) {
				pCmdUI->Enable(FALSE);
			}
			else {
				pCmdUI->Enable(TRUE);
			}
		}
		else {
			if (userID == choice || akc_number == -1) {
				pCmdUI->Enable(FALSE);
			}
			else {
				pCmdUI->Enable(TRUE);
			}
		}
	}
	else {
		pCmdUI->Enable(FALSE);
	}			
}
void CDogRunView::OnUpdateChangePace(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FAST || this->m_SelectedShapeOnToolBar == ID_DRAW_NORMAL
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_SLOW || this->m_SelectedShapeOnToolBar == ID_DRAW_FAST_SIT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDrawFast() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FAST;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawFast(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FAST) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDrawNormal() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_NORMAL;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_NORMAL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDrawSlow() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SLOW;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawSlow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SLOW) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawFastSit() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FAST_SIT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawFastSit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == APDT_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FAST_SIT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnUpdateRightTurns(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_RT_TURN || this->m_SelectedShapeOnToolBar == ID_DRAW_ABOUT_RT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_270_RT || this->m_SelectedShapeOnToolBar == ID_DRAW_360_RT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_90_PIVOT_RT || this->m_SelectedShapeOnToolBar == ID_DRAW_180_PIVOT_RT
		|| this->m_SelectedShapeOnToolBar == ID_ABOUT_FORWARD_RT || this->m_SelectedShapeOnToolBar == ID_DRAW_1STEP_HEEL_RT 
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_HALTRIGHTFORWARD ) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawRtTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_RT_TURN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawRtTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_RT_TURN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawAboutRt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_ABOUT_RT;
	this->ClearAllStationsFromSelectedList(true);	
	
}

void CDogRunView::OnUpdateDrawAboutRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_ABOUT_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnAboutForwardRt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_ABOUT_FORWARD_RT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateAboutForwardRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	
	if (this->m_SelectedShapeOnToolBar == ID_ABOUT_FORWARD_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDraw270Rt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_270_RT;
	this->ClearAllStationsFromSelectedList(true);	
	
}

void CDogRunView::OnUpdateDraw270Rt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_270_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDraw360Rt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_360_RT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDraw360Rt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_360_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDraw90PivotRt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_90_PIVOT_RT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDraw90PivotRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_90_PIVOT_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDrawDoubleRtUTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DOUBLE_RIGHT_UTURN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawDoubleRtUTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DOUBLE_RIGHT_UTURN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawRtUTurnLeftAboutTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_R_U_LEFT_ABOUT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawRtUTurnLeftAboutTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_R_U_LEFT_ABOUT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawStandPivotRightForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_STAND_PIVOT_R_FOR;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawStandPivotRightForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_STAND_PIVOT_R_FOR) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDraw180PivotRt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_180_PIVOT_RT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDraw180PivotRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_180_PIVOT_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}


void CDogRunView::OnDraw1stepHeelRt() 
{
	// TODO: Add your command handler code here

	this->m_SelectedShapeOnToolBar = ID_DRAW_1STEP_HEEL_RT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDraw1stepHeelRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_1STEP_HEEL_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnUpdateLeftTurns(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_LT_TURN || this->m_SelectedShapeOnToolBar == ID_DRAW_ABOUT_LT || 
		this->m_SelectedShapeOnToolBar == ID_DRAW_ABOUT_TURN_LT || this->m_SelectedShapeOnToolBar == ID_DRAW_U_FORWARD_LT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_270_LT || this->m_SelectedShapeOnToolBar == ID_DRAW_360_LT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_90_PIVOT_LT || this->m_SelectedShapeOnToolBar == ID_DRAW_180_PIVOT_LT
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_HALTLEFTFORWARD || this->m_SelectedShapeOnToolBar == ID_DRAW_HALTRIGHTPIVOTFORWARD
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_HALTLEFTPIVOTFORWARD || this->m_SelectedShapeOnToolBar == ID_DRAW_HALTRIGHTPIVOTFORWARD
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_HALTLEFTPIVOTFORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}

void CDogRunView::OnDrawLtTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_LT_TURN;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawLtTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_LT_TURN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawAboutLt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_ABOUT_LT;
	this->ClearAllStationsFromSelectedList(true);	
}



void CDogRunView::OnUpdateDrawAboutLt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_ABOUT_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawAboutTurnLt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_ABOUT_TURN_LT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawAboutTurnLt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == APDT_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_ABOUT_TURN_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawHaltLeftForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_HALTLEFTFORWARD;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateHaltLeftForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_HALTLEFTFORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawFrontHeel() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FRONTHEEL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateFrontHeel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
		if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FRONTHEEL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawHaltRightForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_HALTRIGHTFORWARD;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateHaltRightForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_HALTRIGHTFORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawUForwardLt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_U_FORWARD_LT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawUForwardLt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_U_FORWARD_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDraw270Lt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_270_LT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDraw270Lt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_270_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDraw360Lt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_360_LT;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDraw360Lt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_360_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDraw90PivotLt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_90_PIVOT_LT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDraw90PivotLt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE  && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_90_PIVOT_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDraw180PivotLt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_180_PIVOT_LT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDraw180PivotLt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_180_PIVOT_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawDoubleLeftUTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DOUBLE_LEFT_UTURN;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDoubleLeftUTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DOUBLE_LEFT_UTURN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawDoubleLeftAboutTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DOUBLE_LEFT_ATURN;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDoubleLeftAboutTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DOUBLE_LEFT_ATURN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawLeftUTurnLeftAboutTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_L_U_LEFT_ABOUT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateLeftUTurnLeftAboutTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_L_U_LEFT_ABOUT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawLeftUTurnRightAboutTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_L_ABOUT_RIGHT_U;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateLeftUTurnRightAboutTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_L_ABOUT_RIGHT_U) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawLeftAboutTurnLeftUTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_L_ABOUT_LEFT_U;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateLeftAboutTurnLeftUTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_L_ABOUT_LEFT_U) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawStandPivotLeftForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_STAND_PIVOT_L_FOR;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateStandPivotLeftForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_STAND_PIVOT_L_FOR) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDraw180LeftHeelRight180Right() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_TR_L_HEEL_R_T_R;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdate180LeftHeelRight180Right(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER ||course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_TR_L_HEEL_R_T_R) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawHaltRightPivotForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HALTRIGHTPIVOTFORWARD;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateHaltRightPivotForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALTRIGHTPIVOTFORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawHaltLeftPivotForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HALTLEFTPIVOTFORWARD;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateHaltLeftPivotForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALTLEFTPIVOTFORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}



void CDogRunView::OnDrawHonor() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HONOR;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawHonor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	ASSERT_VALID(pDoc);
	if (this->m_type_course == AKC_COURSE && (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING)) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HONOR) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}	



void CDogRunView::OnUpdateFinish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_LEFT_FORWARD || this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_LT_HALT 
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_RT_FORWARD || this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_RT_HALT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_HALT_FINISH_LT || this->m_SelectedShapeOnToolBar == ID_DRAW_HALT_FINISH_RT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_FRONTHEEL)
		
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawFinishLeftForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FINISH_LEFT_FORWARD;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawFinishLeftForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_LEFT_FORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawFinishLtHalt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FINISH_LT_HALT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawFinishLtHalt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_LT_HALT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawFinishRtForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FINISH_RT_FORWARD;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawFinishRtForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_RT_FORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawFinishRtHalt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FINISH_RT_HALT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawFinishRtHalt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FINISH_RT_HALT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawHaltFinishLt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HALT_FINISH_LT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawHaltFinishLt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALT_FINISH_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawReverseThreeSteps() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_FRONT_REV_3_STEPS;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawReverseThreeSteps(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_FRONT_REV_3_STEPS) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawFrontCircleRightFinishLeft() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_FRT_CIR_R_FIN_L;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawFrontCircleRightFinishLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_FRT_CIR_R_FIN_L) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}



void CDogRunView::OnDrawHaltFinishRt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HALT_FINISH_RT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawHaltFinishRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALT_FINISH_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}



void CDogRunView::OnUpdateMove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SIDE_RT || this->m_SelectedShapeOnToolBar == ID_DRAW_MOVE_DOWN  || this->m_SelectedShapeOnToolBar == ID_DRAW_MOVINGSTAND 
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_MOVE_STAND_WALK || this->m_SelectedShapeOnToolBar == ID_DRAW_JUMP 
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_BACKUP_3 || this->m_SelectedShapeOnToolBar == ID__DRAW_DOWNWHILEHEELING
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_MOVE_DOWN || this->m_SelectedShapeOnToolBar == ID__STAND_HEEL
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_STAND_SIT_LEAVE || this->m_SelectedShapeOnToolBar == ID__STAND_LEAVE_DOWN
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_DOUBLE_LEFT_TURN || this->m_SelectedShapeOnToolBar == ID__DRAW_SENDTOJUMP
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_SITSTAY || this->m_SelectedShapeOnToolBar == ID__DRAW_CALLTOHEEL)
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSideRt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SIDE_RT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawSideRt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here


	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SIDE_RT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawMoveDown() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_MOVE_DOWN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawMoveDown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(TRUE);
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_MOVE_DOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawMoveStand() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_MOVINGSTAND;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawMoveStand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	pCmdUI->Enable(TRUE);
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_MOVINGSTAND) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawJump() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_JUMP;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawJump(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_JUMP) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawMoveDownWalk() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_MOVE_DOWN;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawMoveDownWalk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_MOVE_DOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawMoveStandWalk() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_MOVE_STAND_WALK;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawMoveStandWalk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_MOVE_STAND_WALK) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawDoubleLeftTurn() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_DOUBLE_LEFT_TURN;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawDoubleLeftTurn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_DOUBLE_LEFT_TURN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawSendtoJump() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_SENDTOJUMP;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawSendtoJump(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_SENDTOJUMP) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawSitStay() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_SITSTAY;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawSitStay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_SITSTAY) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawCalltoHeel() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_CALLTOHEEL;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawCalltoHeel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER|| course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_CALLTOHEEL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawDownWhileHeeling() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_DOWNWHILEHEELING;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawDownWhileHeeling(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_DOWNWHILEHEELING) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawStandWhileHeeling() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__STAND_HEEL;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawStandWhileHeeling(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__STAND_HEEL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawStandSitLeave() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_STAND_SIT_LEAVE;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawStandSitLeave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_STAND_SIT_LEAVE) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnDrawStandDownLeave() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__STAND_LEAVE_DOWN;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnUpdateDrawStandDownLeave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID__STAND_LEAVE_DOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);		
}
void CDogRunView::OnMovestandleave() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_MOVE_STAND_LEAVE;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateMovestandleave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_MOVE_STAND_LEAVE) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnMovestandleavetwo() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_MOVE_STAND_LEAVE_TWO;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateMovestandleavetwo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_MOVE_STAND_LEAVE_TWO) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnMovestandsitfinish() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_MOVE_STAND_SIT_FINISH;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateMovestandsitfinish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_MOVE_STAND_SIT_FINISH) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnMovestandsitfinishtwo() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_MOVE_STAND_SIT_FINISH_TWO;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateMovestandsitfinishtwo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_MOVE_STAND_SIT_FINISH_TWO) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnFrontrun() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_FRONT_RUN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateFrontrun(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_FRONT_RUN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnJumprecall() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_JUMP_RECALL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateJumprecall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_JUMP_RECALL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnJumprecalltwo() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_JUMP_RECALL_TWO;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateJumprecalltwo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;

	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);


	if (this->m_SelectedShapeOnToolBar == ID_JUMP_RECALL_TWO) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);

}
void CDogRunView::OnRightdown() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_RT_DOWN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateRightdown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);


	if (this->m_SelectedShapeOnToolBar == ID_DRAW_RT_DOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnTurnFront() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_TURN_FRONT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateTurnFront(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);

	if (course_info.m_class == NOVICE) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}

	if (this->m_SelectedShapeOnToolBar == ID_TURN_FRONT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnFinishRight() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_FINISH_RIGHT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateFinishRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);

	if (course_info.m_class == NOVICE) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}


	if (this->m_SelectedShapeOnToolBar == ID_FINISH_RIGHT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnFinishLeft() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_FINISH_LEFT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateFinishLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);

	if (course_info.m_class == NOVICE) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}


	if (this->m_SelectedShapeOnToolBar == ID_FINISH_LEFT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnRecallLeave() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_RECALL_LEAVE;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateRecallLeave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);

	if (course_info.m_class == NOVICE) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}

	if (this->m_SelectedShapeOnToolBar == ID_RECALL_LEAVE) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDownRecall() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DOWN_RECALL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDownRecall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DOWN_RECALL) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDownRecalltwo() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DOWN_RECALL_TWO;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDownRecalltwo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);


	if (this->m_SelectedShapeOnToolBar == ID_DOWN_RECALL_TWO) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnRetrieveFinish() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_RETRIEVE_FINISH;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateRetrieveFinish(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);


	if (this->m_SelectedShapeOnToolBar == ID_RETRIEVE_FINISH) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnLeftdown() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_LT_DOWN;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateLeftdown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_LT_DOWN) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnJumpleave() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_JUMP_LEAVE;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateJumpleave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);


	if (this->m_SelectedShapeOnToolBar == ID_JUMP_LEAVE) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnJumpleavetwo() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_JUMP_LEAVE_TWO;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateJumpleavetwo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);


	if (this->m_SelectedShapeOnToolBar == ID_JUMP_LEAVE_TWO) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawBackup3() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_BACKUP_3;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawBackup3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == MASTER || course_info.m_class == TRAINING) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_BACKUP_3) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnUpdateHeel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALT_3_STEPS_FOR || this->m_SelectedShapeOnToolBar == ID_DRAW_FRONT_3_STEPS_BACK
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_SIDE_RIGHT || this->m_SelectedShapeOnToolBar == IDB_LEAVE_DOG_2_STEPS_HEEL
		|| this->m_SelectedShapeOnToolBar == ID__DRAW_DOUBLE_LEFT_TURN)
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawHalt3StepsFor() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_HALT_3_STEPS_FOR;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawHalt3StepsFor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_HALT_3_STEPS_FOR) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawFront3StepsBack() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_FRONT_3_STEPS_BACK;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawFront3StepsBack(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE && course_info.m_type_of_course == APDT_COURSE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_FRONT_3_STEPS_BACK) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSideRight() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SIDE_RIGHT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawSideRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SIDE_RIGHT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnDrawTwoStepsForward() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID__DRAW_2_STEPS_FORWARD;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawTwoStepsForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE || course_info.m_class == ADVANCED || course_info.m_class == EXCELLENT) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID__DRAW_2_STEPS_FORWARD) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}
void CDogRunView::OnUpdateWeave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SERP_ONCE || this->m_SelectedShapeOnToolBar == ID_DRAW_WEAVE_TWICE
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_OFFSET_8 || this->m_SelectedShapeOnToolBar == ID_DRAW_SPIRAL_RIGHT
		|| this->m_SelectedShapeOnToolBar == ID_DRAW_SPIRAL_LEFT || this->m_SelectedShapeOnToolBar == ID_WEAVES_FIGURE8) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawWeaveTwice() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_WEAVE_TWICE;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawWeaveTwice(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_WEAVE_TWICE) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSerpOnce() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SERP_ONCE;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawSerpOnce(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (((course_info.m_class == EXCELLENT || course_info.m_class == TRAINING) && course_info.m_type_of_course == APDT_COURSE) || course_info.m_type_of_course == AKC_COURSE) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
	
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SERP_ONCE) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawOffset8() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_OFFSET_8;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawOffset8(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

	if (this->m_SelectedShapeOnToolBar == ID_DRAW_OFFSET_8) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawFig8NoDistractions() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_WEAVES_FIGURE8;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateFig8NoDistractions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	
	if (course_info.m_class == EXCELLENT || course_info.m_class == MASTER || course_info.m_class == TRAINING)pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
	if (this->m_SelectedShapeOnToolBar == ID_WEAVES_FIGURE8) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSpiralLeft() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SPIRAL_LEFT;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateDrawSpiralLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SPIRAL_LEFT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnDrawSpiralRight() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_DRAW_SPIRAL_RIGHT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateDrawSpiralRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_DRAW_SPIRAL_RIGHT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnCourseVerify() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox("Course Verificatin is not yet implemented in Version 3.0.0 Beta!");
	Verify verify_course;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	verify_course.VerifyCourse(pDoc, true, this->m_type_course);
}

void CDogRunView::OnUpdateNonstationary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CDogRunView::OnUpdateStationary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDogRunView::OnUpdateAdvanced(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

}

void CDogRunView::OnUpdateExcellent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_class == NOVICE || course_info.m_class == ADVANCED) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

}
void CDogRunView::OnUpdateMaster(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_class == NOVICE || course_info.m_class == ADVANCED || course_info.m_class == EXCELLENT) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);

}

void CDogRunView::OnSaveBitmap() 
{
	// TODO: Add your command handler code here

	CClientDC dc(this);
 
 	
	CFileDialog dlg( FALSE,_T("BMP"),_T("*.bmp"),
					 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
					 _T("(*.bmp)|*.bmp|"));
	dlg.DoModal();

	CString file_path;
	file_path = dlg.GetPathName();

	WndToBmp(&dc,file_path,TRUE);
	
	ReleaseDC(&dc);
}
void CDogRunView::InflateBMPRectIfNeeded(CRect *bmp_rect) {

	CRect course_info,station_list;
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	pDoc->m_course_info->GetCourseInfoRect(&course_info);
	pDoc->m_station_list->GetStationListRect(&station_list);
	if (pDoc->m_course_info->ViewCourse()) {
		if (course_info.right > bmp_rect->right) bmp_rect->right = course_info.right; 
		if (course_info.bottom > bmp_rect->bottom) bmp_rect->bottom = course_info.bottom;
	}
	if (pDoc->m_station_list->ViewStationList()) {
		if (station_list.right > bmp_rect->right) bmp_rect->right = station_list.right; 
		if (station_list.bottom > bmp_rect->bottom) bmp_rect->bottom = station_list.bottom; 
	}

}
HANDLE CDogRunView::WndToBmp(CDC *pDC, CString szFile, BOOL create_file)
{

//capture wnd and save into bmp file
	CString fname=szFile;
	CBitmap bmp,*pOldBmp;
	CRect rect;
	BOOL flg=0;
	CPalette pal;
	LOGPALETTE *pLp;

	if(pDC==NULL)
	{
		AfxMessageBox("DC Not Found");
		return FALSE;
	}
	
	rect = m_bmp_save_rect;
	this->InflateBMPRectIfNeeded(&rect);
	if(fname.IsEmpty() && create_file)
		return NULL;

	CDC memdc;
	
	memdc.CreateCompatibleDC(pDC);

	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBmp=memdc.SelectObject(&bmp);
	memdc.PatBlt(0,0, rect.Width(), rect.Height(), WHITENESS);
	this->m_printing = true;
	this->OnDraw(&memdc);
	this->m_printing = false;


	if(pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		int nSize;
		nSize=sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256;
		pLp=(LOGPALETTE*) new BYTE[nSize];
		pLp->palVersion=0x300;
		pLp->palNumEntries=256;
		GetSystemPaletteEntries(pDC->m_hDC,0,256,pLp->palPalEntry);
		pal.CreatePalette(pLp);
		delete [] pLp;
	}
	
	/////////////////////////***
	memdc.SelectObject(pOldBmp);
	HANDLE hDIB=DDBToDIB(bmp,BI_RGB,&pal);
	if(hDIB==NULL || !create_file)
		return hDIB;
//*************************************
	CFile m_file;
	if(!m_file.Open(fname,CFile::modeWrite | CFile::modeCreate,NULL))
		return NULL;
	else
		flg=1;
	BITMAPFILEHEADER hdr;
	LPBITMAPINFOHEADER lpbi;
	
	lpbi=(LPBITMAPINFOHEADER ) hDIB;
	
	int nColors= 1 << lpbi->biBitCount;
	
	hdr.bfType= ((WORD) ('M' << 8) | 'B');
	hdr.bfSize=GlobalSize(hDIB) + sizeof(hdr);
	hdr.bfReserved1=0;
	hdr.bfReserved2=0;
	hdr.bfOffBits=(DWORD) (sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));
	m_file.Write(&hdr,sizeof(hdr));
	m_file.Write(lpbi,GlobalSize(hDIB));
	m_file.Close();
//**************************************
	CFile  m_tempFile;
	BYTE dummy=0;//14
	BYTE pBuf[14];

	BOOL fres=m_tempFile.Open(fname,CFile::modeReadWrite | CFile::typeBinary);

	if(fres==0)
		return NULL;

	UINT tt=m_tempFile.Read(pBuf,14);
	pBuf[13]=dummy;//will replace from 04 to 00
	m_tempFile.SeekToBegin();
	m_tempFile.Write(pBuf,14);

	m_tempFile.Close();

	return hDIB;
//*****This Function is wriiten by Shailesh Kanzariya....***********
//it will capture wnd and save into bmp file

}
HANDLE CDogRunView::DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal)
{

	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;			//bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = ::GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE)lpbi 			// address for bitmap bits
				+ (bi.biSize + nColors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	::ReleaseDC(NULL,hDC);

	return hDIB;
}

void CDogRunView::OnRegDialog() 
{
	// TODO: Add your command handler code here
		RegisterDlg dlgReg;
		int app_status;
		app_status = dlgReg.Check();
		dlgReg.DoModal();
		if (app_status == TIME_EXPIRED) this->m_dead_flag = true;
		else this->m_dead_flag = false;
}

BOOL CDogRunView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return false;
	return CScrollView::OnEraseBkgnd(pDC);
}

// ArrowTo()
//
void CDogRunView::ArrowTo(HDC hDC, int x, int y, ARROWSTRUCT *pA) {

	POINT ptTo = {x, y};

	ArrowTo(hDC, &ptTo, pA);
}

// ArrowTo()
//
void CDogRunView::ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA) {

	POINT pFrom;
	POINT pBase;
	POINT aptPoly[3];
	float vecLine[2];
	float vecLeft[2];
	float fLength;
	float th;
	float ta;

	// get from point
	MoveToEx(hDC, 0, 0, &pFrom);

	// set to point
	aptPoly[0].x = lpTo->x;
	aptPoly[0].y = lpTo->y;

	// build the line vector
	vecLine[0] = (float) aptPoly[0].x - pFrom.x;
	vecLine[1] = (float) aptPoly[0].y - pFrom.y;

	// build the arrow base vector - normal to the line
	vecLeft[0] = -vecLine[1];
	vecLeft[1] = vecLine[0];

	// setup length parameters
	fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
	th = pA->nWidth / (2.0f * fLength);
	ta = pA->nWidth / (2.0f * (tanf(pA->fTheta) / 2.0f) * fLength);

	// find the base of the arrow
	pBase.x = (int) (aptPoly[0].x + -ta * vecLine[0]);
	pBase.y = (int) (aptPoly[0].y + -ta * vecLine[1]);

	// build the points on the sides of the arrow
	aptPoly[1].x = (int) (pBase.x + th * vecLeft[0]);
	aptPoly[1].y = (int) (pBase.y + th * vecLeft[1]);
	aptPoly[2].x = (int) (pBase.x + -th * vecLeft[0]);
	aptPoly[2].y = (int) (pBase.y + -th * vecLeft[1]);

	MoveToEx(hDC, pFrom.x, pFrom.y, NULL);

	// fill in the arrow
	if(pA->bFill) {
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		Polygon(hDC, aptPoly, 3);
	}


	else {
		LineTo(hDC, pBase.x, pBase.y);
		LineTo(hDC, aptPoly[1].x, aptPoly[1].y);
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		LineTo(hDC, aptPoly[2].x, aptPoly[2].y);
		LineTo(hDC, pBase.x, pBase.y);
		MoveToEx(hDC, aptPoly[0].x, aptPoly[0].y, NULL);
	}
}

void CDogRunView::OnFilePrintBw() 
{
	// TODO: Add your command handler code here
	if (this->m_dead_flag == TIME_EXPIRED) {
		RegisterDlg dlgReg;	
		dlgReg.DoModal();
		return;
	}
	int current_mode;
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();

   current_mode =pApp->GetCurrentColorMode();
   if(current_mode != NULL)
   {
		pApp->SetCurrentColorMode(DMCOLOR_MONOCHROME);
		this->OnFilePrint();
		pApp->SetCurrentColorMode(current_mode);
   }		
}

void CDogRunView::OnRallyList() 
{
	// TODO: Add your command handler code here

	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_station_list->ViewStationList()) {
		pDoc->m_station_list->SetViewStationList(FALSE);
	}
	else {
		pDoc->m_station_list->SetViewStationList(TRUE);
	}

	Invalidate(	FALSE);	
}

void CDogRunView::OnUpdateRallyList(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetCheck(pDoc->m_station_list->ViewStationList());
}


void CDogRunView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(lHint) {
	case CHANGE_STATION:
		this->Invalidate(false);
		break;
	}
	
}


void CDogRunView::OnUpdatePrintScoreSheet(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CDogRunView::OnUpdatePylons(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(TRUE);
	if (this->m_SelectedShapeOnToolBar == ID_PYLONS) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}

}

void CDogRunView::OnPylons() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_PYLONS;
	this->ClearAllStationsFromSelectedList(true);
}

void CDogRunView::OnCopyCourse() 
{
	// TODO: Add your command handler code here
	
    CRect       rect;
    CClientDC   dc(this);
    CDC         memDC;
    CBitmap     bitmap;
    
 //   GetClientRect(&rect); 
	rect = m_bmp_save_rect;
	this->InflateBMPRectIfNeeded(&rect);
    // Create memDC
    memDC.CreateCompatibleDC(&dc);
    bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

    // Fill in memDC
    memDC.FillSolidRect(rect, dc.GetBkColor()); 
 //   BOOL size_to_fit = this->m_size_to_fit;
//	this->m_size_to_fit = false;
//	OnPrepareDC(&memDC);
	this->m_printing = true;	
    OnDraw(&memDC);
	this->m_printing = false;

//	this->m_size_to_fit = size_to_fit;
    // Copy contents of memDC to clipboard
    OpenClipboard();
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, bitmap.GetSafeHandle());
    CloseClipboard();

    // Clean up
    memDC.SelectObject(pOldBitmap);
    bitmap.Detach();
	AfxMessageBox("A copy of the course map is available for pasting into another application.",MB_OK);		
}

void CDogRunView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDogRunDoc* pDoc = GetDocument();
	
	if (this->m_in_text_box) {
		this->DisplayEditDialog(&point, &point, false);
	}

	if (this->m_stations_selected.GetCount() == 1) {
		StationPropDlg station_dlg;
		CRallyObject *pRallyObjectInSelectList;
		pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetHead();
		station_dlg.DoModal(pRallyObjectInSelectList, &pDoc->m_rallyList, this, pDoc);
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDogRunView::DisplayEditDialog(CPoint *top_left, CPoint *bottom_right, bool new_text)
{
	CDogRunDoc* pDoc = GetDocument();
	TextObj *pTextObjInList;
	LOGFONT lf;
	CEdit* pBoxOne;
	CRect control_rect, dialog_rect, text_rect, intial_rect;
	BOOL create_dialog;
	mp_edit_dlg = new CEditDlg(this);
	CPoint sp = this->GetScrollPosition();
	CClientDC dc(this);	
	POSITION pos;
	POSITION text_pos;

	if (new_text) {
	
		text_rect.SetRect(top_left->x, top_left->y,top_left->x + 100, top_left->y+100); // for now default size of text rectangle.
		pDoc->m_text_font->GetLogFont(&lf);
		this->mp_textobj = new TextObj(&text_rect, &lf, pDoc->m_text_font->GetColorReference());
		this->mp_textobj->SetDrawBox(pDoc->m_default_outline_text_rect);
		this->mp_textobj->SetTextBoxRectColor(pDoc->m_default_text_rect_color);
		pos = pDoc->m_text_list.AddTail(this->mp_textobj);
		pDoc->m_doc_modified = COleDateTime::GetCurrentTime();
		lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);
		
		create_dialog = mp_edit_dlg->Create(&lf,this->mp_textobj);
		text_rect.SetRectEmpty();
		pBoxOne = (CEdit*) mp_edit_dlg->GetDlgItem(IDC_EDIT_TEXT);
		pBoxOne->GetWindowRect(&control_rect);

		text_rect.SetRect(top_left->x, top_left->y,top_left->x + control_rect.Width(), top_left->y+control_rect.Height()); // for now default size of text rectangle.
		
		
		intial_rect = text_rect;
		this->mp_textobj->SetDisplayTextRect(&text_rect);
		mp_edit_dlg->GetWindowRect(&dialog_rect);
		int diff_x = control_rect.left - dialog_rect.left;
		int diff_y = control_rect.top - dialog_rect.top;
		int width = text_rect.right - text_rect.left;
		text_rect.left = top_left->x + width;
		text_rect.top = top_left->y - diff_y;
		text_rect.right = text_rect.right + width;
		
		if (top_left == bottom_right) {
			sp.x = -sp.x;
			sp.y = -sp.y;
			text_rect.OffsetRect(sp);
			mp_edit_dlg->MoveWindow(this->RectangleInWindow(&text_rect,&intial_rect));
		}
		else {
			mp_edit_dlg->MoveWindow(top_left->x, top_left->y, bottom_right->x - top_left->x, bottom_right->y - top_left->y);
		}
		mp_edit_dlg->ShowWindow(SW_SHOW);
		this->m_text_editing = true;

	}
	else {
		pTextObjInList = (TextObj*)this->m_text_selected.GetHead();
		this->mp_textobj = pTextObjInList;
		CString display_text = pTextObjInList->GetDisplayText();
		CRect text_rect;
		pTextObjInList->GetDisplayTextRect(&text_rect);
		intial_rect = text_rect;
		pTextObjInList->GetLogFont(&lf);
		lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);
		create_dialog = mp_edit_dlg->Create(&lf,this->mp_textobj);
		pBoxOne = (CEdit*) mp_edit_dlg->GetDlgItem(IDC_EDIT_TEXT);
		pBoxOne->SetWindowText(display_text);
		pBoxOne->GetWindowRect(&control_rect);
		mp_edit_dlg->GetWindowRect(&dialog_rect);
		int diff_x = control_rect.left - dialog_rect.left;
		int diff_y = control_rect.top - dialog_rect.top;
		text_rect.top -= diff_y;
		text_rect.left -= diff_x;
		text_rect.left = text_rect.right;
		text_rect.right = text_rect.left + intial_rect.Width();
		sp.x = -sp.x;
		sp.y = -sp.y;
		text_rect.OffsetRect(sp);
		mp_edit_dlg->MoveWindow(this->RectangleInWindow(&text_rect,&intial_rect));
		mp_edit_dlg->ShowWindow(SW_SHOW);
		this->m_text_editing = true;
		text_pos = pDoc->m_text_list.Find(pTextObjInList);
		pDoc->AddUndoStation(pTextObjInList,text_pos,MOVE_STATION);
	}

	if (this->m_size_to_fit) {
		this->ChangeDCToSizeToWindow(&dc);
		this->FixRectInFitScreenModeLPtoDP(&intial_rect,&dc);
	}

	intial_rect.InflateRect(15,15);
	this->mp_textobj->SetInvalRect(&intial_rect);

}

void CDogRunView::OnMyFont() 
{
	// TODO: Add your command handler code here
	LOGFONT lf;
	CDogRunDoc* pDoc = GetDocument();
	this->m_course_font.GetLogFont(&lf);
	CFontDialog dlg(&lf);
	dlg.m_cf.rgbColors = this->m_course_color;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		this->m_course_font.DeleteObject();
		this->m_course_font.CreateFontIndirect(&lf);
		this->m_course_color = dlg.GetColor();
		pDoc->SetDefaultCourseFont(&lf, m_course_color);
		Invalidate(TRUE);
	}
	this->BringWindowToTop();
}

void CDogRunView::OnUpdateMyFont(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDogRunView::OnEditText() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_EDIT_TEXT;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateEditText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_EDIT_TEXT) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}
}


void CDogRunView::OnTextFont() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	TextPrefDlg text_pref_dlg;
	LOGFONT lf;
	CClientDC dc(this);
	pDoc->m_text_font->GetLogFont(&lf);
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);

	int response = text_pref_dlg.DoModal(pDoc->m_default_outline_text_rect,&lf,pDoc->m_text_font->GetColorReference(), pDoc->m_default_text_rect_color, true);
	if (response == IDOK) {
		pDoc->m_default_outline_text_rect = text_pref_dlg.m_outline_rect;
		pDoc->m_default_text_rect_color = text_pref_dlg.m_outline_rect_color;
		pDoc->m_text_font->SetColorReference(text_pref_dlg.m_font_color);
		if (text_pref_dlg.m_change_font) {
			text_pref_dlg.m_default_font.lfHeight = text_pref_dlg.m_point_size;
			pDoc->m_text_font->SetFont(&text_pref_dlg.m_default_font);
		}
		if (text_pref_dlg.m_set_default) {
			pDoc->SetApplicationDefaultFonts();
		}
	}

}

void CDogRunView::OnUpdateTextFont(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

CRect  CDogRunView::RectangleInWindow(CRect *rect_to_check, CRect *text_rect)
{
	// return a rect within the client window
	CRect wind_rect;
	CRect rect_in_window;

	rect_in_window.SetRectEmpty();
	this->GetClientRect(&wind_rect);
	this->ClientToScreen(&wind_rect);
	rect_in_window = *rect_to_check;
	this->ClientToScreen(&rect_in_window);
//	this->ClientToScreen(rect_to_check);

	
	int width, height;

/*
	if (wind_rect.right < rect_to_check->right && wind_rect.bottom < rect_to_check->bottom) { // both bottom and top are off screen move up and left
		rect_in_window.bottom = wind_rect.bottom;
		rect_in_window.top = rect_in_window.bottom - height;
		rect_in_window.right = text_rect->left;
		rect_in_window.left = text_rect->left - width;

	}
	else if (wind_rect.right >= rect_to_check->right && wind_rect.bottom < rect_to_check->bottom) { //bottom is off screen move up
		rect_in_window.bottom = wind_rect.bottom;
		rect_in_window.top = rect_in_window.bottom - height;

	}
	else if (wind_rect.right < rect_to_check->right && wind_rect.bottom >= rect_to_check->bottom) { //right is off-screen move left.
		rect_in_window.right = text_rect->left;
		rect_in_window.left = text_rect->left - width;
		rect_in_window.top = text_rect->top;
		rect_in_window.bottom = text_rect->bottom;
	}
*/
	rect_in_window.left = text_rect->left;
	rect_in_window.right = text_rect->right;
	if (this->m_size_to_fit) {
		height = rect_in_window.bottom - rect_in_window.top;
		width = rect_in_window.right - rect_in_window.left; 
		CClientDC dc(this);	
		this->ChangeDCToSizeToWindow(&dc);
		CPoint top_left, bottom_right;
		top_left = rect_in_window.TopLeft();
		dc.LPtoDP(&top_left);
		bottom_right = top_left;
		bottom_right.x += width;
		bottom_right.y += height;
		rect_in_window.SetRect(top_left,bottom_right);
//		this->FixRectInFitScreenModeLPtoDP(&rect_in_window,&dc);
	}

	return rect_in_window;
}

void CDogRunView::SetSelectedTextFont(LOGFONT *p_log_font, COLORREF new_color)
{
	POSITION pos;
	TextObj *pTextObjectInSelectList;
	for( pos = this->m_text_selected.GetHeadPosition(); pos != NULL; ) {
		pTextObjectInSelectList = (TextObj*)this->m_text_selected.GetNext(pos);
		pTextObjectInSelectList->SetLogFont(p_log_font);
		pTextObjectInSelectList->SetTextColor(new_color);
	}
	this->Invalidate(FALSE);
}

void CDogRunView::SetUpCourseVariablesAndGrid()
{
	CClientDC dc(this);	
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	this->m_type_course = course_info.m_type_of_course;
	this->m_ring_width = course_info.m_ring_width;
	this->m_ring_lenght = course_info.m_ring_lenght;
	this->m_grid_spacing = course_info.m_grid_spacing;
	this->m_show_path = course_info.m_show_path;
	this->m_size_to_fit = course_info.m_size_to_fit;
	this->m_stat_num_loc = course_info.m_stat_num_loc;
	this->m_add_normal = course_info.m_add_normal;
	this->m_where_cones = course_info.m_where_cones;
	this->m_where_list = course_info.m_where_list;
	this->m_print_grid_lines = course_info.m_print_grid_lines;
	this->m_number_honor = true; //course_info.m_number_honor;
	this->m_inch_per_horiz = dc.GetDeviceCaps(LOGPIXELSX);
	this->m_inch_per_vert = dc.GetDeviceCaps(LOGPIXELSY);
	this->m_sizeTotal.cx = this->m_ring_width * (this->m_inch_per_horiz / 1.5) + 50;
	this->m_sizeTotal.cy = this->m_ring_lenght * (this->m_inch_per_vert / 1.5)+ 50;	
	CSize scroll_size = this->m_sizeTotal;
	if (this->m_size_to_fit) {
		scroll_size.cx = 0;
		scroll_size.cy = 0;
	}
	else {
		scroll_size.cx += 450;
		scroll_size.cy += 450;
	}

	this->SetScrollSizes(MM_TEXT,scroll_size);
}

void CDogRunView::OnAutorPref() 
{
	// TODO: Add your command handler code here
	AuthorDlg author_dlg;
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	ASSERT_VALID(pDoc);
	pDoc->m_course_info->GetCourseInfo(&course_info);
	author_dlg.m_type = course_info.m_type_of_course;
	author_dlg.m_class = course_info.m_class;
	author_dlg.m_judge_name = course_info.m_judge;
	author_dlg.m_organization= course_info.m_organization;
	author_dlg.m_ring_lenght.Format("%.1f", course_info.m_ring_lenght);
	author_dlg.m_ring_width.Format("%.1f", course_info.m_ring_width);
	author_dlg.m_grid_spacing.Format("%.1f", course_info.m_grid_spacing);
	author_dlg.m_show_path = course_info.m_show_path;
	author_dlg.m_size_to_screen = course_info.m_size_to_fit;
	author_dlg.m_auto_add = course_info.m_add_normal;
	author_dlg.m_grid_color = course_info.m_print_grid_lines;
	author_dlg.m_list_placement = course_info.m_where_list;

	author_dlg.m_show_class = course_info.m_cmt_class;
	author_dlg.m_show_comp_name = course_info.m_cmt_comp_name;
	author_dlg.m_show_date = course_info.m_cmt_date;
	author_dlg.m_show_judge = course_info.m_cmt_judge_name;
	author_dlg.m_show_organization = course_info.m_cmt_organization;
	author_dlg.m_show_location = course_info.m_cmt_location;
	author_dlg.m_show_subclass = course_info.m_cmt_subclass;

	LOGFONT font_test;
	author_dlg.m_font_color = pDoc->GetDefaultCourseLogFont(&font_test);
//	pDoc->m_course_font->GetLogFont(&font_test);
	CClientDC dc(this);
	author_dlg.m_point_size =  font_test.lfHeight;
	font_test.lfHeight = -((font_test.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);
 	
	author_dlg.m_default_font = font_test;
//	author_dlg.m_font_color = pDoc->m_course_font->GetColorReference();
	if (author_dlg.m_class == TRAINING) {
		author_dlg.m_judge_or_instruct = "Instructor:";
	}
	else {
		author_dlg.m_judge_or_instruct = "Judge:";
	}
	int response = author_dlg.DoModal();
	if (response == IDCANCEL) return;
	pDoc->SetModifiedFlag();
	pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	

	this->m_type_course = course_info.m_type_of_course = author_dlg.m_type;
	course_info.m_class = author_dlg.m_class;
	course_info.m_judge = author_dlg.m_judge_name;
	course_info.m_organization= author_dlg.m_organization;
	course_info.m_ring_lenght = atoi(author_dlg.m_ring_lenght);
	course_info.m_ring_width = atoi(author_dlg.m_ring_width);
	course_info.m_grid_spacing = atof(author_dlg.m_grid_spacing);

	course_info.m_show_path = author_dlg.m_show_path;
	course_info.m_size_to_fit = author_dlg.m_size_to_screen;
	course_info.m_add_normal= author_dlg.m_auto_add;
	course_info.m_print_grid_lines = author_dlg.m_grid_color;
	course_info.m_where_list = author_dlg.m_list_placement;
	course_info.m_cmt_class = author_dlg.m_show_class;
	course_info.m_cmt_comp_name = author_dlg.m_show_comp_name;
	course_info.m_cmt_date = author_dlg.m_show_date;
	course_info.m_cmt_judge_name = author_dlg.m_show_judge;
	course_info.m_cmt_organization = author_dlg.m_show_organization;
	course_info.m_cmt_location = author_dlg.m_show_location;
	course_info.m_cmt_subclass = author_dlg.m_show_subclass;
	pDoc->m_course_info->SetCourseInfo(&course_info);
	pDoc->SetUpChangeToPopupMenu();
	if (author_dlg.m_change_font) {
		author_dlg.m_default_font.lfHeight = author_dlg.m_point_size;
		pDoc->SetDefaultCourseFont(&author_dlg.m_default_font,author_dlg.m_font_color);
		this->ResetCourseFont(&dc);

	}
	if (author_dlg.m_set_default) {
		pDoc->SetApplicationDefaults(&course_info);
		pDoc->SetApplicationDefaultsCourseText();
		pDoc->SetApplicationDefaultFonts();
	}
	
	this->SetUpCourseVariablesAndGrid();
	pDoc->SetUpAddMenu();

	this->Invalidate(FALSE);
}

void CDogRunView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_printing = false;
	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

void CDogRunView::OnJumpTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_JUMP_TOOL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateJumpTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_JUMP_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDogRunView::OnLeashTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_LEASH_TOOL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateLeashTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_LEASH_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDogRunView::OnGateTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_GATE_TOOL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateGateTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_GATE_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}		
}

void CDogRunView::OnArrowTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_ARROW_TOOL;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateArrowTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_ARROW_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}			
}

void CDogRunView::CopySpecialObjectData(SpecialObj *dest, SpecialObj *src)
{
	float M11, M12, M21, M22;
	CRect object_rect;
	dest->SetXPos(src->GetXPos());
	dest->SetYPos(src->GetYPos());
	dest->SetTypeObject(src->GetTypeObject());
//	dest->SetSpecialRect();
	src->GetSpecialRect(&object_rect);
	dest->SetSpecialRect(&object_rect);
	src->GetRotateMeasurements(&M11,&M12,&M21,&M22);
	dest->SetRotateMeasurements(M11,M12,M21,M22);
}

void CDogRunView::CopyPylonObjectData(PylonObj *dest, PylonObj *src)
{
	POINT x_y_pos;
	src->GetXYPosition(&x_y_pos);
	dest->SetXYPosition(&x_y_pos);	
}

void CDogRunView::CopyTextObjectData(TextObj *dest, TextObj *src)
{
	CRect text_rect;
	LOGFONT text_font;
	dest->SetDisplayText(&src->GetDisplayText());
	src->GetDisplayTextRect(&text_rect);
	dest->SetDisplayTextRect(&text_rect);
	dest->SetTextColor(src->GetColorRef());
	src->GetLogFont(&text_font);
	dest->SetLogFont(&text_font);
	dest->SetDrawBox(src->GetDrawBox());
	dest->SetTextBoxRectColor(src->GetTextBoxRectColor());
}

void CDogRunView::CopyArrowObjectData(ArrowObj *dest, ArrowObj *src)
{
	CPoint draw_points[16];
	dest->m_arrow_pen = src->m_arrow_pen;
	dest->m_arrow_type = src->m_arrow_type;
	dest->m_entry_point = src->m_entry_point;
	dest->m_exit_point = src->m_exit_point;
	dest->m_entry_owner = src->m_entry_owner;
	dest->m_exit_owner = src->m_exit_owner;
	dest->SetSelection(false);
	dest->m_arrow_type = src->m_arrow_type;
	dest->m_mouse_pt = (0,0);
	dest->m_handle_selected = NO_HANDLE;
// intilize points array
//	dest->IntilizeDrawPoints();
	src->GetDrawPointsArray(draw_points);
	dest->SetDrawPointsArray(draw_points);
	dest->m_mid_point = src->m_mid_point;
	dest->SetHideArrow(src->GetHideArrow());
	dest->SetGrabHandleRects();
	dest->m_move_with_station = src->m_move_with_station;
}

void CDogRunView::UndoMultiplePaste(CObject *pObjectItemInlist)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	int undo_action = -2;

	while(undo_action != MULPASTE_START) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			this->UndoPaste(pRallyItemInlist, RALLY_OBJECT);
			undo_action = pRallyItemInlist->GetUndoRedoAction();
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			this->UndoPaste(pPylonItemInlist, PYLON_OBJECT);
			undo_action = pPylonItemInlist->GetUndoRedoAction();
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			this->UndoPaste(pSpecialItemInlist, SPECIAL_OBJECT);
			undo_action = pSpecialItemInlist->GetUndoRedoAction();
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			this->UndoPaste(pTextItemInlist, TEXT_OBJECT);
			undo_action = pTextItemInlist->GetUndoRedoAction();
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			this->UndoPaste(pArrowItemInlist, ARROW_OBJECT);
			undo_action = pArrowItemInlist->GetUndoRedoAction();
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			this->UndoPaste(pScribbleItemInlist, SCRIBBLE_OBJECT);
			undo_action = pScribbleItemInlist->GetUndoRedoAction();
		}
		if (undo_action != MULPASTE_START) {
			if (pDoc->m_undo_list.GetCount() == 0) {
				this->MessageBox("Trying to Undo When Nothing in Undo List","Mutiple Paste-Error",MB_OK);
				return;
			}
			pObjectItemInlist = pDoc->m_undo_list.RemoveTail();
		}
	}		

}

void CDogRunView::RedoMultiplePaste(CObject *pObjectItemInlist, int redo_action)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;

	while(redo_action != MULPASTE_END) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			redo_action = pRallyItemInlist->GetUndoRedoAction();
			this->RedoPaste(pRallyItemInlist,redo_action, RALLY_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			redo_action = pPylonItemInlist->GetUndoRedoAction();
			this->RedoPaste(pPylonItemInlist,redo_action, PYLON_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			redo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->RedoPaste(pSpecialItemInlist,redo_action, SPECIAL_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			redo_action = pTextItemInlist->GetUndoRedoAction();
			this->RedoPaste(pTextItemInlist,redo_action, TEXT_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			redo_action = pArrowItemInlist->GetUndoRedoAction();
			this->RedoPaste(pArrowItemInlist,redo_action, ARROW_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			redo_action = pScribbleItemInlist->GetUndoRedoAction();
			this->RedoPaste(pScribbleItemInlist,redo_action, SCRIBBLE_OBJECT);
		}
		if (redo_action != MULPASTE_END) {
			if (pDoc->m_redo_list.GetCount() == 0) {
				this->MessageBox("Trying to Redo When Nothing in Redo List","REdo-Mutliple Paste Error",MB_OK);
				return;
			}	
			pObjectItemInlist = pDoc->m_redo_list.RemoveTail();
		}
	}

}

void CDogRunView::UndoMultipleDelete(CObject *pObjectItemInlist)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	int undo_action = MULDEL_END;
	while(undo_action != MULDEL_START) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			undo_action = pRallyItemInlist->GetUndoRedoAction();
			this->UndoDelete(pRallyItemInlist, undo_action, RALLY_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			undo_action = pPylonItemInlist->GetUndoRedoAction();
			this->UndoDelete(pPylonItemInlist, undo_action, PYLON_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			undo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->UndoDelete(pSpecialItemInlist, undo_action, SPECIAL_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			undo_action = pTextItemInlist->GetUndoRedoAction();
			this->UndoDelete(pTextItemInlist, undo_action, TEXT_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			undo_action = pArrowItemInlist->GetUndoRedoAction();
			this->UndoDelete(pArrowItemInlist, undo_action, ARROW_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			undo_action = pScribbleItemInlist->GetUndoRedoAction();
			this->UndoDelete(pScribbleItemInlist, undo_action, SCRIBBLE_OBJECT);
		}
		this->MessageBoxUndoRedoActio(undo_action);
		if (undo_action != MULDEL_START) {
			if (pDoc->m_undo_list.GetCount() == 0) {
				this->MessageBox("Trying to Undo When Nothing in Undo List","Muti-Delete Error",MB_OK);
				return;
			}
			pObjectItemInlist = pDoc->m_undo_list.RemoveTail();

		}
	}

}

void CDogRunView::RedoMultipleDelete(CObject *pObjectItemInlist)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	int redo_action = MULDEL_START;
	int count = pDoc->m_redo_list.GetCount();
	while(redo_action != MULDEL_END) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			redo_action = pRallyItemInlist->GetUndoRedoAction();
			this->RedoDelete(pRallyItemInlist,redo_action, RALLY_OBJECT);
			count = pDoc->m_redo_list.GetCount();
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			redo_action = pPylonItemInlist->GetUndoRedoAction();
			this->RedoDelete(pPylonItemInlist,redo_action, PYLON_OBJECT);
			count = pDoc->m_redo_list.GetCount();
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			redo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->RedoDelete(pSpecialItemInlist,redo_action, SPECIAL_OBJECT);
			count = pDoc->m_redo_list.GetCount();
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			redo_action = pTextItemInlist->GetUndoRedoAction();
			this->RedoDelete(pTextItemInlist,redo_action, TEXT_OBJECT);
			count = pDoc->m_redo_list.GetCount();
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			redo_action = pArrowItemInlist->GetUndoRedoAction();
			this->RedoDelete(pArrowItemInlist,redo_action, ARROW_OBJECT);
			count = pDoc->m_redo_list.GetCount();
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			redo_action = pScribbleItemInlist->GetUndoRedoAction();
			this->RedoDelete(pScribbleItemInlist,redo_action, SCRIBBLE_OBJECT);
			count = pDoc->m_redo_list.GetCount();
		}
		if (redo_action != MULDEL_END) {
			if (pDoc->m_redo_list.GetCount() == 0) {
				this->MessageBox("Trying to Redo When Nothing in Redo List","REdo-Mutliple Delete Error",MB_OK);
				return;
			}	
			else pObjectItemInlist = pDoc->m_redo_list.RemoveTail();
		}
	}

}

void CDogRunView::UndoMultipleCut(CObject *pObjectItemInlist)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	int undo_action = MULCUT_END;
	while(undo_action != MULCUT_START) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			undo_action = pRallyItemInlist->GetUndoRedoAction();
			this->UndoCut(pRallyItemInlist, undo_action, RALLY_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			undo_action = pPylonItemInlist->GetUndoRedoAction();
			this->UndoCut(pPylonItemInlist, undo_action, PYLON_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			undo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->UndoCut(pSpecialItemInlist, undo_action, SPECIAL_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			undo_action = pTextItemInlist->GetUndoRedoAction();
			this->UndoCut(pTextItemInlist, undo_action, TEXT_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			undo_action = pArrowItemInlist->GetUndoRedoAction();
			this->UndoCut(pArrowItemInlist, undo_action, ARROW_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			undo_action = pScribbleItemInlist->GetUndoRedoAction();
			this->UndoCut(pScribbleItemInlist, undo_action, SCRIBBLE_OBJECT);
		}
		if (undo_action != MULCUT_START) {
			if (pDoc->m_undo_list.GetCount() == 0) {
				this->MessageBox("Trying to Undo When Nothing in Undo List","Undo-Mutiple Cut Error",MB_OK);
				return;
			}			
			pObjectItemInlist = pDoc->m_undo_list.RemoveTail();
		}
	}

}

void CDogRunView::RedoMultipleCut(CObject *pObjectItemInlist)
{

	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	int redo_action = MULCUT_START;
	while(redo_action != MULCUT_END) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			redo_action = pRallyItemInlist->GetUndoRedoAction();
			this->RedoCut(pRallyItemInlist, redo_action, RALLY_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			redo_action = pPylonItemInlist->GetUndoRedoAction();
			this->RedoCut(pPylonItemInlist, redo_action, PYLON_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			redo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->RedoCut(pSpecialItemInlist, redo_action, SPECIAL_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			redo_action = pTextItemInlist->GetUndoRedoAction();
			this->RedoCut(pTextItemInlist, redo_action, TEXT_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			redo_action = pArrowItemInlist->GetUndoRedoAction();
			this->RedoCut(pArrowItemInlist, redo_action, ARROW_OBJECT);
		}

		if (redo_action != MULCUT_END) {
			if (pDoc->m_redo_list.GetCount() == 0) {
				this->MessageBox("Trying to Redo When Nothing in Redo List","REdo-Mutliple Cut Error",MB_OK);
				return;
			}	
			pObjectItemInlist = pDoc->m_redo_list.RemoveTail();
		}
	}	

}

void CDogRunView::UndoMultipleMoveOrRotate(CObject *pObjectItemInlist)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;

	int undo_action = MULMOVE_END;
	while(undo_action != MULMOVE_START) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			undo_action = pRallyItemInlist->GetUndoRedoAction();
			this->UndoMoveOrRotateAction(pRallyItemInlist, RALLY_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			undo_action = pPylonItemInlist->GetUndoRedoAction();
			this->UndoMoveOrRotateAction(pPylonItemInlist, PYLON_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			undo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->UndoMoveOrRotateAction(pSpecialItemInlist, SPECIAL_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			undo_action = pTextItemInlist->GetUndoRedoAction();
			this->UndoMoveOrRotateAction(pTextItemInlist, TEXT_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			undo_action = pArrowItemInlist->GetUndoRedoAction();
			this->UndoMoveOrRotateAction(pArrowItemInlist, ARROW_OBJECT);
		}
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			undo_action = pScribbleItemInlist->GetUndoRedoAction();
			this->UndoMoveOrRotateAction(pScribbleItemInlist, SCRIBBLE_OBJECT);
		}
		this->MessageBoxUndoRedoActio(undo_action);
		if (undo_action != MULMOVE_START) {
			if (pDoc->m_undo_list.GetCount() == 0) {
				this->MessageBox("Trying to Undo When Nothing in Undo List","Undo-Multiple Move",MB_OK);
				return;
			}	
			pObjectItemInlist = pDoc->m_undo_list.RemoveTail();
		}
	}
}

void CDogRunView::RedoMultipleMoveOrRotate(CObject *pObjectItemInlist)
{
	CDogRunDoc* pDoc = GetDocument();
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	int redo_action = MULMOVE_START;
	while(redo_action != MULMOVE_END) {
		if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
			pRallyItemInlist = (CRallyObject *)pObjectItemInlist;
			redo_action = pRallyItemInlist->GetUndoRedoAction();
			this->RedoMoveOrRotateStation(pRallyItemInlist, redo_action, RALLY_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( PylonObj))) {
			pPylonItemInlist = (PylonObj *)pObjectItemInlist;
			redo_action = pPylonItemInlist->GetUndoRedoAction();
			this->RedoMoveOrRotateStation(pPylonItemInlist, redo_action, PYLON_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
			pSpecialItemInlist = (SpecialObj *)pObjectItemInlist;
			redo_action = pSpecialItemInlist->GetUndoRedoAction();
			this->RedoMoveOrRotateStation(pSpecialItemInlist, redo_action, SPECIAL_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( TextObj))) {
			pTextItemInlist = (TextObj *)pObjectItemInlist;
			redo_action = pTextItemInlist->GetUndoRedoAction();
			this->RedoMoveOrRotateStation(pTextItemInlist, redo_action, TEXT_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowItemInlist = (ArrowObj *)pObjectItemInlist;
			redo_action = pArrowItemInlist->GetUndoRedoAction();
			this->RedoMoveOrRotateStation(pArrowItemInlist, redo_action, ARROW_OBJECT);
		}
		else if (pObjectItemInlist->IsKindOf(RUNTIME_CLASS( Scribble))) {
			pScribbleItemInlist = (Scribble *)pObjectItemInlist;
			redo_action = pScribbleItemInlist->GetUndoRedoAction();
			this->RedoMoveOrRotateStation(pScribbleItemInlist, redo_action, SCRIBBLE_OBJECT);
		}

		if (redo_action != MULMOVE_END) {
			if (pDoc->m_redo_list.GetCount() == 0) {
				this->MessageBox("Trying to Redo When Nothing in Redo List","REdo-Mutliple Move Error",MB_OK);
				return;
			}	
			pObjectItemInlist = pDoc->m_redo_list.RemoveTail();
		}
	}	

}

void CDogRunView::OnReturnStand() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_RETURN_STAND;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateReturnStand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	
	if (this->m_SelectedShapeOnToolBar == ID_RETURN_STAND) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);	
}

void CDogRunView::OnArrowPref() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	AuthorPref author_pref;
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	author_pref.m_move_arrow = pDoc->GetDocumentMoveArrowsWithStation();

	int response = author_pref.DoModal(pDoc->GetDefaultPen(),pDoc->GetDefaultArrowType(), false);
	if (response == IDOK) {

		pDoc->SetDefaultArrowType(author_pref.m_line_type);
		pDoc->SetDocumentMoveArrowsWithStation(author_pref.m_move_arrow);
		author_pref.m_log_pen.lopnWidth.x = atoi(author_pref.m_line_thickness);
		author_pref.m_log_pen.lopnStyle = author_pref.m_line_style;
		
		pDoc->SetDefaultPen(&author_pref.m_log_pen);
		if (author_pref.m_set_default) {
			pDoc->SetApplicationDefaults(&course_info);
		}
			
	}
}

void CDogRunView::OnUpdateArrowPref(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDogRunView::OnStPropDialog() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	if (this->m_stations_selected.GetCount() == 1) {
		StationPropDlg station_dlg;
		CRallyObject *pRallyObjectInSelectList;
		pRallyObjectInSelectList = (CRallyObject*)this->m_stations_selected.GetHead();
		station_dlg.DoModal(pRallyObjectInSelectList, &pDoc->m_rallyList, this, pDoc);
	}
	if (this->m_stations_selected.GetCount() > 1) {
		StationPropDlg station_dlg;
		station_dlg.DoModal(&this->m_stations_selected, this, pDoc);
	}	
}

void CDogRunView::OnUpdateStPropDialog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_stations_selected.GetCount() >= 1) {
		pCmdUI->Enable(TRUE);
	}
	else {
		pCmdUI->Enable(FALSE);
	}
}
void CDogRunView::OnTextPropDialog() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	LOGFONT lf;
	CClientDC dc(this);
	TextPrefDlg text_pref_dlg;

	if (pDoc->m_station_list->GetStationListSelected()) {
		CRect list_rect;
		pDoc->m_station_list->GetStationListLogFont(&lf);
		lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);
		int response = text_pref_dlg.DoModal(true,&lf,pDoc->m_station_list->GetColorReference(), pDoc->m_default_text_rect_color, false);
		if (response == IDOK) {
			if (text_pref_dlg.m_change_font) {
				pDoc->m_station_list->SetTextColor(text_pref_dlg.m_font_color);
				text_pref_dlg.m_default_font.lfHeight = text_pref_dlg.m_point_size;
				pDoc->m_station_list->SetLogFont(&text_pref_dlg.m_default_font);
			}
			this->Invalidate(FALSE);

		}

	}
	if (pDoc->m_course_info->GetCourseInfoSelected()) {
		CRect list_rect;
		pDoc->m_course_info->GetCourseInfoLogFont(&lf);
		lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);
		int response = text_pref_dlg.DoModal(true,&lf,pDoc->m_course_info->GetColorReference(), pDoc->m_default_text_rect_color, false);
		if (response == IDOK) {
			if (text_pref_dlg.m_change_font) {
				pDoc->m_course_info->SetTextColor(text_pref_dlg.m_font_color);
				text_pref_dlg.m_default_font.lfHeight = text_pref_dlg.m_point_size;
				pDoc->m_course_info->SetLogFont(&text_pref_dlg.m_default_font);
			}
			this->Invalidate(FALSE);
		}

	}

	if (this->m_text_selected.GetCount() == 1) {
		POSITION pos_in_list;
		TextObj *pTextObjectInSelectList;


		pTextObjectInSelectList = (TextObj *)this->m_text_selected.GetHead();
		pTextObjectInSelectList->GetLogFont(&lf);
		lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);

		int response = text_pref_dlg.DoModal(pTextObjectInSelectList->GetDrawBox(),&lf,pTextObjectInSelectList->GetColorRef(), pTextObjectInSelectList->GetTextBoxRectColor(), false);
		if (response == IDOK) {
			pos_in_list = pDoc->m_text_list.Find(pTextObjectInSelectList);
			pDoc->AddUndoStation(pTextObjectInSelectList,pos_in_list,MOVE_STATION);
			pTextObjectInSelectList->SetDrawBox(text_pref_dlg.m_outline_rect);
			pTextObjectInSelectList->SetTextBoxRectColor(text_pref_dlg.m_outline_rect_color);
			if (text_pref_dlg.m_change_font) {
				pTextObjectInSelectList->SetTextColor(text_pref_dlg.m_font_color);
				text_pref_dlg.m_default_font.lfHeight = text_pref_dlg.m_point_size;
				pTextObjectInSelectList->SetLogFont(&text_pref_dlg.m_default_font);
			}
			this->Invalidate(FALSE);
		}		
	}	
}

void CDogRunView::OnUpdateTextPropDialog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	int tot_text_selected = this->m_text_selected.GetCount();
	if (pDoc->m_station_list->GetStationListSelected()) tot_text_selected++;
	if (pDoc->m_course_info->GetCourseInfoSelected()) tot_text_selected++;
	if (tot_text_selected == 1) {
		pCmdUI->Enable(TRUE);
	}
	else {
		pCmdUI->Enable(FALSE);
	}
}
void CDogRunView::OnStraightline() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	ArrowObj* pArrow;
	POSITION pos, pos_in_list;
	int num_changed, how_many_selected;
	how_many_selected = pDoc->m_arrowList.HowManySelectedArrows();
	num_changed = 1;
	for( pos = pDoc->m_arrowList.GetHeadPosition(); pos != NULL;num_changed++ ) {
		pos_in_list = pos;
		pArrow = (ArrowObj*)pDoc->m_arrowList.GetNext(pos);
		if (pArrow->GetArrowSelection()) {
			if (how_many_selected = 1)pDoc->AddUndoStation(pArrow,pos_in_list,MOVE_STATION);
			else if(num_changed == 1) pDoc->AddUndoStation(pArrow,pos_in_list,MULMOVE_START);
			else if(num_changed > 1 && num_changed < how_many_selected) pDoc->AddUndoStation(pArrow,pos_in_list,MULMOVE);
			else if (num_changed == how_many_selected) 	pDoc->AddUndoStation(pArrow,pos_in_list,MULMOVE_END);		
			pArrow->StraightenArrow();
		}
	}
	
//	pDoc->m_arrowList.StraightenSelectedArrows();
	this->Invalidate(true);
}

void CDogRunView::OnUpdateStraightline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	if (pDoc->m_arrowList.AnyArrowSelected()) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
}
void CDogRunView::OnReversearrow() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
	ArrowObj* pArrow;
	POSITION pos, pos_in_list;
	int num_changed, how_many_selected;
	how_many_selected = pDoc->m_arrowList.HowManySelectedArrows();
	num_changed = 1;
	for( pos = pDoc->m_arrowList.GetHeadPosition(); pos != NULL;num_changed++ ) {
		pos_in_list = pos;
		pArrow = (ArrowObj*)pDoc->m_arrowList.GetNext(pos);
		if (pArrow->GetArrowSelection()) {
			if (how_many_selected == 1 && num_changed == 1)
				pDoc->AddUndoStation(pArrow,pos_in_list,MOVE_STATION);
			else if(num_changed == 1) 
				pDoc->AddUndoStation(pArrow,pos_in_list,MULMOVE_START);
			else if(num_changed > 1 && num_changed < how_many_selected) 
				pDoc->AddUndoStation(pArrow,pos_in_list,MULMOVE);
			else if (num_changed == how_many_selected) 	
				pDoc->AddUndoStation(pArrow,pos_in_list,MULMOVE_END);		
			pArrow->ReverseArrow();
		}
	}
//	pDoc->m_arrowList.ReverseSelectedArrows();
	this->Invalidate(true);
}

void CDogRunView::OnUpdateReversearrow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	if (pDoc->m_arrowList.AnyArrowSelected()) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
}
void CDogRunView::OnArrowproperties() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = GetDocument();
//	pDoc->m_arrowList.ChangeArrowProperties();
	AuthorPref author_pref;
	ArrowObj* pArrow;
	Scribble* pScribble;
	POSITION pos, posInList;
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	if (this->m_scribble_selected.GetCount() == 1) {
		pos = this->m_scribble_selected.GetHeadPosition();
		pScribble = (Scribble*)this->m_scribble_selected.GetNext(pos);
		LOGPEN scribble_pen;
		int response = author_pref.DoModal(pScribble->GetScribblePen(&scribble_pen),NULL, true);
		if (response == IDOK) {
			posInList = pDoc->m_scribbleList.Find(pScribble);
			pDoc->AddUndoStation(pScribble,posInList,MOVE_STATION); 
			scribble_pen.lopnColor = author_pref.m_log_pen.lopnColor;
			scribble_pen.lopnWidth.x = atoi(author_pref.m_line_thickness);
			scribble_pen.lopnStyle = PS_SOLID;
			pScribble->SetScribblePen(&scribble_pen);
		}		
	}
	else {
		
		for( pos = pDoc->m_arrowList.GetHeadPosition(); pos != NULL; ) {
			pArrow = (ArrowObj*)pDoc->m_arrowList.GetNext(pos);
			if (pArrow->GetArrowSelection()) pos = NULL;
		}
		author_pref.m_move_arrow = pArrow->m_move_with_station;
		int response = author_pref.DoModal(&pArrow->GetArrowPen(),pArrow->GetArrowType(), false);
		if (response == IDOK) {
			posInList = pDoc->m_arrowList.Find(pArrow);
			pDoc->AddUndoStation(pArrow,posInList,MOVE_STATION); 
			pArrow->SetArrowType(author_pref.m_line_type);
			pArrow->SetPenForArrow(author_pref.m_line_style,atoi(author_pref.m_line_thickness), author_pref.m_log_pen.lopnColor);
			pArrow->m_move_with_station = author_pref.m_move_arrow;
		}
	}
	if (author_pref.m_set_default) {
		pDoc->SetDefaultArrowType(author_pref.m_line_type);
		pDoc->SetDocumentMoveArrowsWithStation(author_pref.m_move_arrow);
		author_pref.m_log_pen.lopnWidth.x = atoi(author_pref.m_line_thickness);
		pDoc->SetDefaultPen(&author_pref.m_log_pen);
		pDoc->SetApplicationDefaults(&course_info);
	}

	this->Invalidate(FALSE);
}

void CDogRunView::OnUpdateArrowproperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	if (pDoc->m_arrowList.GetTotalSelected() == 1 || this->m_scribble_selected.GetCount() == 1) {
		pCmdUI->Enable(TRUE);
	}
	else {
		pCmdUI->Enable(FALSE);
	}
}

void CDogRunView::OnStationPref() 
{
	// TODO: Add your command handler code here
	StationPrefDlg station_pref_dlg;
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	CClientDC dc(this);
	ASSERT_VALID(pDoc);
	pDoc->m_course_info->GetCourseInfo(&course_info);

	station_pref_dlg.m_loc_station_number = course_info.m_stat_num_loc;

	station_pref_dlg.m_cone_placement = course_info.m_where_cones;

	station_pref_dlg.m_number_honor = course_info.m_number_honor;
	station_pref_dlg.m_stat_desc = course_info.m_stat_desc;
	station_pref_dlg.m_do_rotate_text = course_info.m_do_rotate_text;
	int last_mode = 0;
	last_mode = SetGraphicsMode (dc.m_hDC, GM_ADVANCED);
	
	station_pref_dlg.m_can_rotate  = last_mode;
	if (last_mode) SetGraphicsMode (dc.m_hDC, last_mode);
	LOGFONT font_test;

	pDoc->m_stat_font->GetLogFont(&font_test);
	station_pref_dlg.m_point_size =  font_test.lfHeight;

	font_test.lfHeight = -((font_test.lfHeight * GetDeviceCaps(dc.m_hDC, LOGPIXELSY)) / 72);
 	
	station_pref_dlg.m_default_font = font_test;
	station_pref_dlg.m_font_color = pDoc->m_stat_font->GetColorReference();
	if (pDoc->m_station_size == 2) station_pref_dlg.m_station_size = TWO_EVEN;
	else if (pDoc->m_station_size == 5) station_pref_dlg.m_station_size = FIVE_EVEN;
	else if (pDoc->m_station_size == 7) station_pref_dlg.m_station_size = SEVEN_EVEN;
	else station_pref_dlg.m_station_size = CUSTOM_SIZE;
	station_pref_dlg.m_actual_size.Format("%d",pDoc->m_station_size);
	
	int response = station_pref_dlg.DoModal();
	if (response == IDCANCEL) return;
	pDoc->SetModifiedFlag();
	pDoc->m_doc_modified = COleDateTime::GetCurrentTime();	

	course_info.m_stat_num_loc = station_pref_dlg.m_loc_station_number;

	course_info.m_where_cones = station_pref_dlg.m_cone_placement;

	if (station_pref_dlg.m_number_honor != course_info.m_number_honor) {
		pDoc->SetStationNumberForHonor(station_pref_dlg.m_number_honor);	
	}
	course_info.m_number_honor = station_pref_dlg.m_number_honor;
	course_info.m_stat_desc = station_pref_dlg.m_stat_desc;
	course_info.m_do_rotate_text = station_pref_dlg.m_do_rotate_text;
	pDoc->m_course_info->SetCourseInfo(&course_info);

	if (station_pref_dlg.m_station_size == TWO_EVEN) 
		pDoc->m_station_size = 2;
	else if (station_pref_dlg.m_station_size == FIVE_EVEN) 
		pDoc->m_station_size = 5;
	else if (station_pref_dlg.m_station_size == SEVEN_EVEN) 
		pDoc->m_station_size = 7;
	else 
		pDoc->m_station_size = atoi(station_pref_dlg.m_actual_size);

	pDoc->SetUpChangeToPopupMenu();
	if (station_pref_dlg.m_change_font) {
		station_pref_dlg.m_default_font.lfHeight = station_pref_dlg.m_point_size;
		pDoc->SetDefaultStationFont(&station_pref_dlg.m_default_font,station_pref_dlg.m_font_color);
		pDoc->m_rallyList.ResetStationFont(pDoc->m_stat_font,&dc);
	}
	if (station_pref_dlg.m_set_default) {
		pDoc->SetApplicationDefaults(&course_info);
		pDoc->SetApplicationDefaultFonts();
		pDoc->SetDefaultRallyStationSize(pDoc->m_station_size);
	}
	
	this->SetUpCourseVariablesAndGrid();
	pDoc->SetUpAddMenu();

	this->Invalidate(FALSE);	
}

void CDogRunView::OnUpdateStationPref(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}

void CDogRunView::ResetCourseFont(CDC *dc)
{
	CDogRunDoc* pDoc = GetDocument();
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	this->m_course_color = pDoc->GetDefaultCourseLogFont(&lf);
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(dc->m_hDC, LOGPIXELSY)) / 72);
 	this->m_course_font.DeleteObject();

	VERIFY(this->m_course_font.CreateFontIndirect(&lf));  // create the font
}

void CDogRunView::OnUpdatePattern(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (this->m_SelectedShapeOnToolBar == ID_PATTERN || this->m_SelectedShapeOnToolBar == ID_OFFSET_3A
	|| this->m_SelectedShapeOnToolBar == ID_OFFSET_3B || this->m_SelectedShapeOnToolBar == ID_SPIRAL_LT 
	|| this->m_SelectedShapeOnToolBar == ID_SPIRAL_RT_1A || this->m_SelectedShapeOnToolBar == ID_SPIRAL_RT_1B) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}			
}
void CDogRunView::OnOffset3a() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_OFFSET_3A;
}

void CDogRunView::OnUpdateOffset3a(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunDoc* pDoc = GetDocument();
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);
	ASSERT_VALID(pDoc);
	if (course_info.m_class == NOVICE) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
	if (this->m_SelectedShapeOnToolBar == ID_OFFSET_3A) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);
}
void CDogRunView::OnOffset3b() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_OFFSET_3B;
}

void CDogRunView::OnUpdateOffset3b(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_OFFSET_3B) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);
}
void CDogRunView::OnSpirallt() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_SPIRAL_LT;
}

void CDogRunView::OnUpdateSpirallt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_SPIRAL_LT) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);
}
void CDogRunView::OnSpiralrt1a() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_SPIRAL_RT_1A;
}

void CDogRunView::OnUpdateSpiralrt1a(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_SPIRAL_RT_1A) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);
}
void CDogRunView::OnSpiralrt1b() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_SPIRAL_RT_1B;
}

void CDogRunView::OnUpdateSpiralrt1b(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_SPIRAL_RT_1B) 
		pCmdUI->SetCheck(TRUE);
	else 
		pCmdUI->SetCheck(FALSE);
}

void CDogRunView::OnStationListPr() 
{
	// TODO: Add your command handler code here
	StationListPrefdlg station_list_pref_dlg;
	CDogRunDoc* pDoc = GetDocument();

// on course map
	station_list_pref_dlg.m_show_ack_cm = pDoc->m_cmt_akc_number;
	station_list_pref_dlg.m_show_stat_name_cm = pDoc->m_cmt_station_name;
	station_list_pref_dlg.m_show_stat_no_cm = pDoc->m_cmt_station_number;
	station_list_pref_dlg.m_show_xy_cm = pDoc->m_cmt_xy_location;
// on print out
	station_list_pref_dlg.m_show_akc = pDoc->m_slpo_akc_number;
	station_list_pref_dlg.m_show_statation_name = pDoc->m_slpo_station_name;
	station_list_pref_dlg.m_show_station_number = pDoc->m_slpo_station_number;
	station_list_pref_dlg.m_show_xylocation = pDoc->m_slpo_xy_location;	

	station_list_pref_dlg.m_show_course_info = pDoc->m_slpo_show_course_info;
	station_list_pref_dlg.m_show_class = pDoc->m_slpo_class;
	station_list_pref_dlg.m_show_comp_name = pDoc->m_slpo_comp_name;
	station_list_pref_dlg.m_show_date = pDoc->m_slpo_date;	
	station_list_pref_dlg.m_show_judge = pDoc->m_slpo_judge_name;
	station_list_pref_dlg.m_show_location = pDoc->m_slpo_location;
	station_list_pref_dlg.m_show_organization = pDoc->m_slpo_organization;
	station_list_pref_dlg.m_show_subclass = pDoc->m_slpo_subclass;
	station_list_pref_dlg.m_show_stats = pDoc->m_slpo_show_stats;	

	int response = station_list_pref_dlg.DoModal();
	if (response == IDOK) {
	// on course map
		pDoc->m_cmt_akc_number = station_list_pref_dlg.m_show_ack_cm;
		pDoc->m_cmt_station_name = station_list_pref_dlg.m_show_stat_name_cm;
		pDoc->m_cmt_station_number = station_list_pref_dlg.m_show_stat_no_cm;
		pDoc->m_cmt_xy_location = station_list_pref_dlg.m_show_xy_cm;
		pDoc->m_station_list->SetStationListViewParameters(pDoc->m_cmt_akc_number, pDoc->m_cmt_station_name, pDoc->m_cmt_station_number,pDoc->m_cmt_xy_location); 
	// on print out
		pDoc->m_slpo_akc_number = station_list_pref_dlg.m_show_akc;
		pDoc->m_slpo_station_name = station_list_pref_dlg.m_show_statation_name;
		pDoc->m_slpo_station_number = station_list_pref_dlg.m_show_station_number;
		pDoc->m_slpo_xy_location = station_list_pref_dlg.m_show_xylocation;	

		pDoc->m_slpo_show_course_info = station_list_pref_dlg.m_show_course_info;
		pDoc->m_slpo_class = station_list_pref_dlg.m_show_class;
		pDoc->m_slpo_comp_name = station_list_pref_dlg.m_show_comp_name;
		pDoc->m_slpo_date = station_list_pref_dlg.m_show_date;	
		pDoc->m_slpo_judge_name = station_list_pref_dlg.m_show_judge;
		pDoc->m_slpo_location = station_list_pref_dlg.m_show_location;
		pDoc->m_slpo_organization = station_list_pref_dlg.m_show_organization;
		pDoc->m_slpo_subclass = station_list_pref_dlg.m_show_subclass;
		pDoc->m_slpo_show_stats = station_list_pref_dlg.m_show_stats;	
		this->Invalidate(TRUE);
		if (station_list_pref_dlg.m_set_default) {
			pDoc->SetApplicationStationListPreferences();
		}
	}

}

void CDogRunView::OnStationDescPr() 
{
	// TODO: Add your command handler code here
	StationDescDlg station_desc_pref_dlg;
	CDogRunDoc* pDoc = GetDocument();

// on print out
	station_desc_pref_dlg.m_show_akc = pDoc->m_sdpo_akc_number;
	station_desc_pref_dlg.m_show_station_name = pDoc->m_sdpo_station_name;
	station_desc_pref_dlg.m_show_stat_no = pDoc->m_sdpo_station_number;
	station_desc_pref_dlg.m_show_xy_loc = pDoc->m_sdpo_xy_location;	

	station_desc_pref_dlg.m_show_course_info = pDoc->m_sdpo_show_course_info;
	station_desc_pref_dlg.m_show_class = pDoc->m_sdpo_class;
	station_desc_pref_dlg.m_show_comp_name = pDoc->m_sdpo_comp_name;
	station_desc_pref_dlg.m_show_date = pDoc->m_sdpo_date;	
	station_desc_pref_dlg.m_show_judge_name = pDoc->m_sdpo_judge_name;
	station_desc_pref_dlg.m_show_location = pDoc->m_sdpo_location;
	station_desc_pref_dlg.m_show_organization = pDoc->m_sdpo_organization;
	station_desc_pref_dlg.m_show_sub_class = pDoc->m_sdpo_subclass;

	int response = station_desc_pref_dlg.DoModal();
	if (response == IDOK) {

		pDoc->m_sdpo_akc_number = station_desc_pref_dlg.m_show_akc;
		pDoc->m_sdpo_station_name = station_desc_pref_dlg.m_show_station_name;
		pDoc->m_sdpo_station_number = station_desc_pref_dlg.m_show_stat_no;
		pDoc->m_sdpo_xy_location = station_desc_pref_dlg.m_show_xy_loc;	

		pDoc->m_sdpo_show_course_info = station_desc_pref_dlg.m_show_course_info;
		pDoc->m_sdpo_class = station_desc_pref_dlg.m_show_class;
		pDoc->m_sdpo_comp_name = station_desc_pref_dlg.m_show_comp_name;
		pDoc->m_sdpo_date = station_desc_pref_dlg.m_show_date;	
		pDoc->m_sdpo_judge_name = station_desc_pref_dlg.m_show_judge_name;
		pDoc->m_sdpo_location = station_desc_pref_dlg.m_show_location;
		pDoc->m_sdpo_organization = station_desc_pref_dlg.m_show_organization;
		pDoc->m_sdpo_subclass = station_desc_pref_dlg.m_show_sub_class;

		if (station_desc_pref_dlg.m_set_default) {
			pDoc->SetApplicationDefaultStationDescriptionPreferences();
		}
	}		
}

void CDogRunView::OnScoreSheetPr() 
{
	// TODO: Add your command handler code here
	ScoreSheetPrefDlg score_sheet_pref_dlg;
	CDogRunDoc* pDoc = GetDocument();

// on print out
	score_sheet_pref_dlg.m_show_akc = pDoc->m_sspo_akc_number;
	score_sheet_pref_dlg.m_show_stat_name = pDoc->m_sspo_station_name;
	score_sheet_pref_dlg.m_show_stat_no = pDoc->m_sspo_station_number;
	score_sheet_pref_dlg.m_show_xy_loc = pDoc->m_sspo_xy_location;	

	score_sheet_pref_dlg.m_show_arm_band= pDoc->m_sspo_arm_band;
	score_sheet_pref_dlg.m_show_breed = pDoc->m_sspo_breed;
	score_sheet_pref_dlg.m_show_jump_ht = pDoc->m_sspo_jump_ht;	
	score_sheet_pref_dlg.m_time= pDoc->m_sspo_time;
	score_sheet_pref_dlg.m_final_score = pDoc->m_sspo_final_score;
	score_sheet_pref_dlg.m_judge_sign = pDoc->m_sspo_judge_sign;	

	score_sheet_pref_dlg.m_show_course_info = pDoc->m_sspo_show_course_info;
	score_sheet_pref_dlg.m_show_class = pDoc->m_sspo_class;
	score_sheet_pref_dlg.m_show_comp_name = pDoc->m_sspo_comp_name;
	score_sheet_pref_dlg.m_show_date = pDoc->m_sspo_date;	
	score_sheet_pref_dlg.m_show_judge_name = pDoc->m_sspo_judge_name;
	score_sheet_pref_dlg.m_show_location = pDoc->m_sspo_location;
	score_sheet_pref_dlg.m_show_organization = pDoc->m_sspo_organization;
	score_sheet_pref_dlg.m_show_subclass = pDoc->m_sspo_subclass;

	int response = score_sheet_pref_dlg.DoModal();
	if (response == IDOK) {

		pDoc->m_sspo_arm_band = score_sheet_pref_dlg.m_show_arm_band ;
		pDoc->m_sspo_breed = score_sheet_pref_dlg.m_show_breed ;
		pDoc->m_sspo_jump_ht = score_sheet_pref_dlg.m_show_jump_ht ;	
		pDoc->m_sspo_time = score_sheet_pref_dlg.m_time ;
		pDoc->m_sspo_final_score = score_sheet_pref_dlg.m_final_score ;
		pDoc->m_sspo_judge_sign = score_sheet_pref_dlg.m_judge_sign ;	

		pDoc->m_sspo_akc_number = score_sheet_pref_dlg.m_show_akc;
		pDoc->m_sspo_station_name = score_sheet_pref_dlg.m_show_stat_name;
		pDoc->m_sspo_station_number = score_sheet_pref_dlg.m_show_stat_no;
		pDoc->m_sspo_xy_location = score_sheet_pref_dlg.m_show_xy_loc;	

		pDoc->m_sspo_show_course_info = score_sheet_pref_dlg.m_show_course_info;
		pDoc->m_sspo_class = score_sheet_pref_dlg.m_show_class;
		pDoc->m_sspo_comp_name = score_sheet_pref_dlg.m_show_comp_name;
		pDoc->m_sspo_date = score_sheet_pref_dlg.m_show_date;	
		pDoc->m_sspo_judge_name = score_sheet_pref_dlg.m_show_judge_name;
		pDoc->m_sspo_location = score_sheet_pref_dlg.m_show_location;
		pDoc->m_sspo_organization = score_sheet_pref_dlg.m_show_organization;
		pDoc->m_sspo_subclass = score_sheet_pref_dlg.m_show_subclass;

		if (score_sheet_pref_dlg.m_set_default) {
			pDoc->SetApplicationDefaultStationDescriptionPreferences();
		}
	}		
}

void CDogRunView::OnTableTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_TABLE_TOOL;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateTableTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_TABLE_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}		
}

void CDogRunView::OnSelectAllStations() 
{
	// TODO: Add your command handler code here
	this->AddAllStationsToSelectedList();
	this->Invalidate(FALSE);
}

BOOL CDogRunView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (this->m_text_editing) {
		CSize temp_size(0,0);
		this->OnLButtonDown(MK_LBUTTON,temp_size);
		this->OnLButtonUp(0,temp_size);
	}
		
	return CScrollView::OnScrollBy(sizeScroll, bDoScroll);
}

void CDogRunView::OnLineTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_LINE_TOOL;
	this->ClearAllStationsFromSelectedList(true);		
}


void CDogRunView::OnUpdateLineTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_LINE_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}		
}

void CDogRunView::OnBrJumpTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_BR_JUMP_TOOL;
	this->ClearAllStationsFromSelectedList(true);		
}	


void CDogRunView::OnUpdateBrJumpTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_BR_JUMP_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDogRunView::OnScribbleTool() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_SCRIBBLE_TOOL;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateScribbleTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_SCRIBBLE_TOOL) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}	
}

void CDogRunView::AddScribbleToSelectedList(Scribble *scribble_object)
{
	POSITION pos = this->m_scribble_selected.AddTail(scribble_object);
	scribble_object->SetSelectedFlag(true);
}

void CDogRunView::RemoveScribbleFromSelectedList(Scribble *scribble_object)
{
	POSITION pos;
	scribble_object->SetSelectedFlag(false);
	pos = this->m_scribble_selected.Find(scribble_object,NULL);
	this->m_scribble_selected.RemoveAt(pos);
}

void CDogRunView::CopyScribbleObjectData(Scribble *dest, Scribble *src)
{
	dest->m_pointArray.RemoveAll();
	LOGPEN scribble_pen;
	dest->SetScribblePen(src->GetScribblePen(&scribble_pen));
	dest->m_rectBounding = src->m_rectBounding;
	for (int i=0; i < src->m_pointArray.GetSize(); i++) {
		dest->m_pointArray.Add(src->m_pointArray.GetAt(i));
	}

}

void CDogRunView::OnBone() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_BONE;
	this->ClearAllStationsFromSelectedList(true);	
}

void CDogRunView::OnUpdateBone(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_BONE) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}	
}


void CDogRunView::MessageBoxUndoRedoActio(int undo_redo_action)
{
return;
	switch(undo_redo_action) {
		case ADD_STATION:
			MessageBox("ADD_STATION!",NULL,MB_OK);
			break;
		case PASTE_STATION:
			MessageBox("PASTE_STATION!",NULL,MB_OK);
			break;
		case MOVE_STATION:
			MessageBox("MOVE_STATION!",NULL,MB_OK);
			break;
		case ROTATE_STATION:
			MessageBox("ROTATE_STATION!",NULL,MB_OK);
			break;
		case DELETE_STATION:
			MessageBox("DELETE_STATION!",NULL,MB_OK);
			break;
		case MULMOVE_START:
			MessageBox("MULMOVE_START!",NULL,MB_OK);
			break;
		case MULMOVE:
			MessageBox("MULMOVE!",NULL,MB_OK);
			break;
		case MULMOVE_END:
			MessageBox("MULMOVE_END!",NULL,MB_OK);
			break;
		case CUT_ONLY:
			MessageBox("CUT_ONLY!",NULL,MB_OK);
			break;
		case MULCUT_START:
			MessageBox("MULCUT_START!",NULL,MB_OK);
			break;
		case MULCUT:
			MessageBox("MULCUT!",NULL,MB_OK);
			break;
		case MULCUT_END:
			MessageBox("MULCUT_END!",NULL,MB_OK);
			break;
		case MULCUTPAS_START:
			MessageBox("MULCUTPAS_START!",NULL,MB_OK);
			break;
		case MULCUTPAS:
			MessageBox("MULCUTPAS!",NULL,MB_OK);
			break;
		case MULCUTPAS_END:
			MessageBox("MULCUTPAS_END!",NULL,MB_OK);
			break;
		case MULPASTE_START:
			MessageBox("MULPASTE_START!",NULL,MB_OK);
			break;
		case MULPASTE:
			MessageBox("MULPASTE!",NULL,MB_OK);
			break;
		case MULPASTE_END:
			MessageBox("MULPASTE_END!",NULL,MB_OK);
			break;
		case MULDEL_START:
			MessageBox("MULDEL_START!",NULL,MB_OK);
			break;
		case MULDEL:
			MessageBox("MULDEL!",NULL,MB_OK);
			break;
		case MULDEL_END:
			MessageBox("MULDEL_END!",NULL,MB_OK);
			break;
		case DELETE_STATION_NUMBER:
			MessageBox("DELETE_STATION_NUMBER!",NULL,MB_OK);
			break;
		case INSERT_AFTER:
			MessageBox("INSERT_AFTER!",NULL,MB_OK);
			break;
		case INSERT_BEFORE:
			MessageBox("INSERT_BEFORE!",NULL,MB_OK);
			break;
		case INSERT_AT:
			MessageBox("INSERT_AT!",NULL,MB_OK);
			break;
		case UPDATE_LIST:
			MessageBox("UPDATE_LIST!",NULL,MB_OK);
			break;
		case MOVE_INFO:
			MessageBox("MOVE_INFO!",NULL,MB_OK);
			break;
		case MOVE_STATION_LIST:
			MessageBox("MOVE_STATION_LIST!",NULL,MB_OK);
			break;
		case CHANGE_STATION:
			MessageBox("CHANGE_STATION!",NULL,MB_OK);
			break;
	}

}

void CDogRunView::OnSerpPattern() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_SERP_PATTERN;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateSerpPattern(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	if (this->m_SelectedShapeOnToolBar == ID_SERP_PATTERN) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}		
}

void CDogRunView::OnFig8Pattern() 
{
	// TODO: Add your command handler code here
	this->m_SelectedShapeOnToolBar = ID_FIG8_PATTERN;
	this->ClearAllStationsFromSelectedList(true);		
}

void CDogRunView::OnUpdateFig8Pattern(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (this->m_SelectedShapeOnToolBar == ID_FIG8_PATTERN) {
		pCmdUI->SetCheck(TRUE);
	}
	else {
		pCmdUI->SetCheck(FALSE);
	}			
}

