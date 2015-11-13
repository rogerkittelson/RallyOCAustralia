// DogRunView.h : interface of the CDogRunView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOGRUNVIEW_H__8A8EF023_78E6_44C9_BD65_3736C8C70892__INCLUDED_)
#define AFX_DOGRUNVIEW_H__8A8EF023_78E6_44C9_BD65_3736C8C70892__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RallyObject.h"
#include "RallyTracker.h"
#include "PylonObj.h"
#include "EditDlg.h"
#include "TextObj.h"
#include "SpecialObj.h"
#include "Scribble.h"


class CDogRunView : public CScrollView
{
protected: // create from serialization only
	CDogRunView();
	DECLARE_DYNCREATE(CDogRunView)

// Attributes
public:
	CDogRunDoc* GetDocument();
	int m_SelectedShapeOnToolBar;
	int m_XPos;
	int m_YPos;

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogRunView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	void MessageBoxUndoRedoActio(int undo_redo_action);
	void CopyScribbleObjectData(Scribble *dest, Scribble *src);
	void RemoveScribbleFromSelectedList(Scribble *scribble_object);
	void AddScribbleToSelectedList(Scribble *scribble_object);
	void ResetCourseFont(CDC *dc);
	void RedoMultipleMoveOrRotate(CObject *pObjectItemInlist);
	void UndoMultipleMoveOrRotate(CObject *pObjectItemInlist);
	void RedoMultipleCut(CObject *pObjectItemInlist);
	void UndoMultipleCut(CObject *pObjectItemInlist);
	void RedoMultipleDelete(CObject *pObjectItemInlist);
	void UndoMultipleDelete(CObject *pObjectItemInlist);
	void RedoMultiplePaste(CObject *pObjectItemInlist, int redo_action);
	void UndoMultiplePaste(CObject *pObjectItemInlist);
	void CopyArrowObjectData(ArrowObj *dest, ArrowObj *src);
	void CopyTextObjectData(TextObj *dest, TextObj *src);
	void CopyPylonObjectData(PylonObj *dest, PylonObj *src);
	void SetUpCourseVariablesAndGrid(void);
	void SetSelectedTextFont(LOGFONT *p_log_font, COLORREF new_color);
	void RemoveTextFromSelectedList(TextObj *p_text_unselect);
	void AddTextToSelectedList(TextObj *p_text_selected);

	virtual ~CDogRunView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL show_error;
	BOOL m_print_left_margin;
	BOOL m_printing;
	int m_type_course;
	CObList m_stations_selected;
	CObList m_pylons_selected;
	CObList m_text_selected;
	CObList m_special_selected;
	CObList m_scribble_selected;
	CObList m_arrow_selected;
	BOOL m_rotate_station;
	BOOL m_rotating_station;
	BOOL m_rotate_special;
	BOOL m_rotating_special;
	BOOL m_resize_station;
	BOOL m_resizing_station;
	BOOL m_resize_special;
	BOOL m_resizing_special;
	BOOL m_create_arrow;
	BOOL m_creating_arrow;
	BOOL m_create_line;
	BOOL m_curving_line;
	BOOL m_dragging_line;
	BOOL m_create_scribble;
	Scribble *mp_created_scribble;
	CPoint      m_ptPrev;       // the last mouse pt in the stroke in progress
	ArrowObj *mp_created_arrow;;
	int m_inch_per_horiz;
	int m_inch_per_vert;
	CSize m_sizeTotal;
	double m_ring_width;
	double m_ring_lenght;
	double m_grid_spacing;
	BOOL m_show_path;
	int m_stat_num_loc;
	int m_where_cones;
	int m_where_list;
	CPoint m_int_drag;
	CPoint m_last_drag;
	void DrawGrid(CDC *pDC);
	POINT m_popup_point;
	POINT m_select_rect_top_left;
	POINT m_select_rect_botom_right;
	BOOL m_drag_select;
	BOOL m_size_to_fit;
	CRect m_drag_rect;
	BOOL m_do_the_drag;
	BOOL m_drag_info;
	BOOL m_drag_station_list;
	CRect m_last_drag_rect;
	RECT m_bmp_save_rect;
	BOOL m_auto_scroll;
	int m_dead_flag;
	CFont m_course_font;
	COLORREF m_course_color;
//	COLORREF m_color_text;
	BOOL m_advanced_mode;
	BOOL m_add_normal;
	BOOL m_print_grid_lines;
	CRect m_grid_rect;
	int m_change_exit_entrance;
	BOOL m_number_honor;
	int m_line_hit;
	bool m_move_line;
	bool m_text_editing;
	bool m_in_text_box;
	int m_diff_x;
	int m_diff_y;
	CEditDlg *mp_edit_dlg;
	TextObj *mp_textobj;
// Generated message map functions
protected:
	void DeSelectAllStations(bool include_arrows);
	void SetupTrackerRect(CDC *pDC, CPoint *point);
	void CopyRallyObjectData(CRallyObject *dest, CRallyObject *src);
	void AddStationToSelectedList(CRallyObject *station_selected);
	void RemoveStationFromSelectedList(CRallyObject *station_selected);
	void AddPylonToSelectedList(PylonObj *station_selected);
	void RemovePylonFromSelectedList(PylonObj *station_selected);
	void AddSpecialToSelectedList(SpecialObj *p_special_selected);
	void RemoveSpecialFromSelectedList(SpecialObj *p_special_selected);
	void ClearAllStationsFromSelectedList(bool include_arrows);
	void AddAllStationsToSelectedList(void);
	int IsRotateHandleSelected(void);
	int HitPointInAnyRallyRect (CPoint *point);
	void MoveStations(CDC *pDC, CPoint *last_point);
	void UndoMoveOrRotateAction(CObject *p_undoStation, int type_of_object);
	void RedoMoveOrRotateStation(CObject *p_redoStation, int redo_action, int type_of_object);
	void UndoDelete(CObject *p_undoStation, int undo_action, int type_of_object);
	void RedoDelete(CObject *p_redoStation, int redo_action, int type_of_object);
	void UndoPaste(CObject *p_undoStation, int type_of_object);
	void RedoPaste(CObject *p_redoStation, int redo_action, int type_of_object);
	void UndoCut(CObject *p_undoStation, int undo_action, int type_of_object);
	void RedoCut(CObject *p_redoStation, int redo_action, int type_of_object);
	void UndoMoveInfo(CRallyObject *p_undoStation);
	void RedoMoveInfo(CRallyObject *p_redoStation); 
	void UndoMoveStationList(CRallyObject *p_undoStation);
	void RedoMoveStationList(CRallyObject *p_redoStation); 
	void UndoChangeStation(CRallyObject *p_undoStation);
	void RedoChangeStation(CRallyObject *p_undoStation);
	void ChangeDCToSizeToWindow(CDC* pDC);
	void FixRectInFitScreenModeLPtoDP(RECT *rect);
	void FixRectInFitScreenModeLPtoDP(RECT *rect, CDC *pDC);
	void FixRectInFitScreenModeDPtoLP(RECT *rect, CDC *pDC);
	void SetDCFont(CDC* pDC);
	void UndoInsertAction(CRallyObject *p_undoStation);
	void RedoInsertAction(CRallyObject *p_undoStation);
	void DrawDragRectangle(CDC *pDC, CPoint *pPoint);
	void UpdateInsertAfterMenu(CMenu* insert_menu);
	void UpdateChangeToMenu(CMenu* insert_menu);
	BOOL CheckRallyRectInRallyRect(CRallyObject* pRallyItemInlist);
	void CheckRallyRectInRectAfterMoveOrPaste(void);
	void RotateStationByDegrees(int rot_degrees);
	void InflateBMPRectIfNeeded(CRect *bmp_rect);
	HANDLE WndToBmp(CDC *pDC, CString szFile,BOOL create_file);
	BOOL AutoScrollWindow(CPoint *p_point, CRect *p_win_rect);
	void CreateMyFont(CDC *dc);
	void ArrowTo(HDC hDC, int x, int y, ARROWSTRUCT *pArrow);
	void ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pArrow);
	HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal);
	//{{AFX_MSG(CDogRunView)
	afx_msg void OnDrawSithalt();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelectarrow();
	afx_msg void OnUpdateSelectarrow(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnEditClear();
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDocInfo();
	afx_msg void OnCourseInfo();
	afx_msg void OnUpdateViewCourseInfo(CCmdUI* pCmdUI);
	afx_msg void OnViewCourseInfo();
	afx_msg void OnSizeToScreen();
	afx_msg void OnUpdateSizeToScreen(CCmdUI* pCmdUI);
	afx_msg void OnDrawFinish();
	afx_msg void OnUpdateDrawFinish(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawSithalt(CCmdUI* pCmdUI);
	afx_msg void OnDrawStart();
	afx_msg void OnUpdateDrawStart(CCmdUI* pCmdUI);
	afx_msg void OnDrawSithaltdown();
	afx_msg void OnUpdateDrawSithaltdown(CCmdUI* pCmdUI);
	afx_msg void OnUpdateForwardHalt(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltwalk();
	afx_msg void OnUpdateDrawHaltwalk(CCmdUI* pCmdUI);
	afx_msg void OnDrawDownwalk();
	afx_msg void OnUpdateDrawDownwalk(CCmdUI* pCmdUI);
	afx_msg void OnDrawDownsit();
	afx_msg void OnUpdateDrawDownsit(CCmdUI* pCmdUI);
	afx_msg void OnDrawStand();
	afx_msg void OnUpdateDrawStand(CCmdUI* pCmdUI);
	afx_msg void OnDrawStanddown();
	afx_msg void OnUpdateDrawStanddown(CCmdUI* pCmdUI);
	afx_msg void OnDrawStandsit();
	afx_msg void OnUpdateDrawStandsit(CCmdUI* pCmdUI);
	afx_msg void OnDrawSitstand();
	afx_msg void OnUpdateDrawSitstand(CCmdUI* pCmdUI);
	afx_msg void OnChStationNum();
	afx_msg void OnUpdateChStationNum(CCmdUI* pCmdUI);
	afx_msg void OnZeroDegrees();
	afx_msg void OnNinetyCcw();
	afx_msg void OnUpdateNinetyCcw(CCmdUI* pCmdUI);
	afx_msg void OnNinetyCw();
	afx_msg void OnUpdateNinetyCw(CCmdUI* pCmdUI);
	afx_msg void OnOneeighty();
	afx_msg void OnUpdateOneeighty(CCmdUI* pCmdUI);
	afx_msg void OnAlignHoriz();
	afx_msg void OnUpdateAlignHoriz(CCmdUI* pCmdUI);
	afx_msg void OnAlignVert();
	afx_msg void OnUpdateAlignVert(CCmdUI* pCmdUI);
	afx_msg void OnDrawStandwalk();
	afx_msg void OnUpdateDrawStandwalk(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChangePace(CCmdUI* pCmdUI);
	afx_msg void OnDrawFast();
	afx_msg void OnUpdateDrawFast(CCmdUI* pCmdUI);
	afx_msg void OnDrawNormal();
	afx_msg void OnUpdateDrawNormal(CCmdUI* pCmdUI);
	afx_msg void OnDrawSlow();
	afx_msg void OnUpdateDrawSlow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRightTurns(CCmdUI* pCmdUI);
	afx_msg void OnDrawRtTurn();
	afx_msg void OnUpdateDrawRtTurn(CCmdUI* pCmdUI);
	afx_msg void OnDrawAboutRt();
	afx_msg void OnUpdateDrawAboutRt(CCmdUI* pCmdUI);
	afx_msg void OnDraw270Rt();
	afx_msg void OnUpdateDraw270Rt(CCmdUI* pCmdUI);
	afx_msg void OnDraw360Rt();
	afx_msg void OnUpdateDraw360Rt(CCmdUI* pCmdUI);
	afx_msg void OnDraw90PivotRt();
	afx_msg void OnUpdateDraw90PivotRt(CCmdUI* pCmdUI);
	afx_msg void OnDraw180PivotRt();
	afx_msg void OnUpdateDraw180PivotRt(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLeftTurns(CCmdUI* pCmdUI);
	afx_msg void OnDrawLtTurn();
	afx_msg void OnUpdateDrawLtTurn(CCmdUI* pCmdUI);
	afx_msg void OnDrawAboutLt();
	afx_msg void OnUpdateDrawAboutLt(CCmdUI* pCmdUI);
	afx_msg void OnDraw270Lt();
	afx_msg void OnUpdateDraw270Lt(CCmdUI* pCmdUI);
	afx_msg void OnDraw360Lt();
	afx_msg void OnUpdateDraw360Lt(CCmdUI* pCmdUI);
	afx_msg void OnDraw90PivotLt();
	afx_msg void OnUpdateDraw90PivotLt(CCmdUI* pCmdUI);
	afx_msg void OnDraw180PivotLt();
	afx_msg void OnUpdateDraw180PivotLt(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltLeftPivotForward();
	afx_msg void OnUpdateHaltLeftPivotForward(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltRightPivotForward();
	afx_msg void OnUpdateHaltRightPivotForward(CCmdUI* pCmdUI);
	afx_msg void OnDrawHonor();
	afx_msg void OnUpdateDrawHonor(CCmdUI* pCmdUI);
	afx_msg void OnAboutForwardRt();
	afx_msg void OnUpdateAboutForwardRt(CCmdUI* pCmdUI);
	afx_msg void OnDrawAboutTurnLt();
	afx_msg void OnUpdateDrawAboutTurnLt(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltLeftForward();
	afx_msg void OnUpdateHaltLeftForward(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltRightForward();
	afx_msg void OnUpdateHaltRightForward(CCmdUI* pCmdUI);
	afx_msg void OnDrawUForwardLt();
	afx_msg void OnUpdateDrawUForwardLt(CCmdUI* pCmdUI);
	afx_msg void OnDraw1stepHeelRt();
	afx_msg void OnUpdateDraw1stepHeelRt(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFinish(CCmdUI* pCmdUI);
	afx_msg void OnDrawFinishLeftForward();
	afx_msg void OnUpdateDrawFinishLeftForward(CCmdUI* pCmdUI);
	afx_msg void OnDrawFinishLtHalt();
	afx_msg void OnUpdateDrawFinishLtHalt(CCmdUI* pCmdUI);
	afx_msg void OnDrawFinishRtForward();
	afx_msg void OnUpdateDrawFinishRtForward(CCmdUI* pCmdUI);
	afx_msg void OnDrawFinishRtHalt();
	afx_msg void OnUpdateDrawFinishRtHalt(CCmdUI* pCmdUI);
	afx_msg void OnDrawSlowForwardFromSit();
	afx_msg void OnUpdateSlowForwardFromSit(CCmdUI* pCmdUI);


	afx_msg void OnDrawFrontHeel();
	afx_msg void OnUpdateFrontHeel(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltFinishLt();
	afx_msg void OnUpdateDrawHaltFinishLt(CCmdUI* pCmdUI);
	afx_msg void OnDrawHaltFinishRt();
	afx_msg void OnUpdateDrawHaltFinishRt(CCmdUI* pCmdUI);
	afx_msg void OnDrawFastSit();
	afx_msg void OnUpdateDrawFastSit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMove(CCmdUI* pCmdUI);
	afx_msg void OnDrawSideRt();
	afx_msg void OnUpdateDrawSideRt(CCmdUI* pCmdUI);
	afx_msg void OnDrawMoveDown();
	afx_msg void OnUpdateDrawMoveDown(CCmdUI* pCmdUI);
	afx_msg void OnDrawMoveStand();
	afx_msg void OnUpdateDrawMoveStand(CCmdUI* pCmdUI);
	afx_msg void OnDrawJump();
	afx_msg void OnUpdateDrawJump(CCmdUI* pCmdUI);
	afx_msg void OnDrawMoveStandWalk();
	afx_msg void OnUpdateDrawMoveStandWalk(CCmdUI* pCmdUI);
	afx_msg void OnDrawMoveDownWalk();
	afx_msg void OnUpdateDrawMoveDownWalk(CCmdUI* pCmdUI);
	afx_msg void OnDrawDownWhileHeeling();
	afx_msg void OnUpdateDrawDownWhileHeeling(CCmdUI* pCmdUI);
	afx_msg void OnDrawStandWhileHeeling();
	afx_msg void OnUpdateDrawStandWhileHeeling(CCmdUI* pCmdUI);
	afx_msg void OnDrawDoubleLeftTurn();
	afx_msg void OnUpdateDrawDoubleLeftTurn(CCmdUI* pCmdUI);
	afx_msg void OnDrawSendtoJump();
	afx_msg void OnUpdateDrawSendtoJump(CCmdUI* pCmdUI);

	afx_msg void OnDrawSitStay();
	afx_msg void OnUpdateDrawSitStay(CCmdUI* pCmdUI);
	afx_msg void OnDrawCalltoHeel();
	afx_msg void OnUpdateDrawCalltoHeel(CCmdUI* pCmdUI);


	afx_msg void OnDrawStandSitLeave();
	afx_msg void OnUpdateDrawStandSitLeave(CCmdUI* pCmdUI);
	afx_msg void OnDrawStandDownLeave();
	afx_msg void OnUpdateDrawStandDownLeave(CCmdUI* pCmdUI);



	afx_msg void OnDrawBackup3();
	afx_msg void OnUpdateDrawBackup3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeel(CCmdUI* pCmdUI);
	afx_msg void OnDrawHalt3StepsFor();
	afx_msg void OnUpdateDrawHalt3StepsFor(CCmdUI* pCmdUI);
	afx_msg void OnDrawFront3StepsBack();
	afx_msg void OnUpdateDrawFront3StepsBack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWeave(CCmdUI* pCmdUI);
	afx_msg void OnDrawWeaveTwice();
	afx_msg void OnUpdateDrawWeaveTwice(CCmdUI* pCmdUI);
	afx_msg void OnDrawSerpOnce();
	afx_msg void OnUpdateDrawSerpOnce(CCmdUI* pCmdUI);
	afx_msg void OnDrawOffset8();
	afx_msg void OnUpdateDrawOffset8(CCmdUI* pCmdUI);
	afx_msg void OnDrawFig8NoDistractions();
	afx_msg void OnUpdateFig8NoDistractions(CCmdUI* pCmdUI);
	afx_msg void OnDrawSpiralLeft();
	afx_msg void OnUpdateDrawSpiralLeft(CCmdUI* pCmdUI);
	afx_msg void OnDrawSpiralRight();
	afx_msg void OnUpdateDrawSpiralRight(CCmdUI* pCmdUI);
	afx_msg void OnDrawSideRight();
	afx_msg void OnUpdateDrawSideRight(CCmdUI* pCmdUI);
	afx_msg void OnDrawTwoStepsForward();
	afx_msg void OnUpdateDrawTwoStepsForward(CCmdUI* pCmdUI);
	afx_msg void OnCourseVerify();
	afx_msg void OnUpdateNonstationary(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStationary(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAdvanced(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExcellent(CCmdUI* pCmdUI);
	afx_msg void OnSaveBitmap();
	afx_msg void OnRegDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFilePrintBw();
	afx_msg void OnUpdateZeroDegrees(CCmdUI* pCmdUI);
	afx_msg void OnRallyList();
	afx_msg void OnUpdateRallyList(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrintScoreSheet(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePylons(CCmdUI* pCmdUI);
	afx_msg void OnPylons();
	afx_msg void OnCopyCourse();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMyFont();
	afx_msg void OnUpdateMyFont(CCmdUI* pCmdUI);
	afx_msg void OnEditText();
	afx_msg void OnUpdateEditText(CCmdUI* pCmdUI);
	afx_msg void OnTextFont();
	afx_msg void OnUpdateTextFont(CCmdUI* pCmdUI);
	afx_msg void OnMovestandleave();
	afx_msg void OnUpdateMovestandleave(CCmdUI* pCmdUI);
	afx_msg void OnMovestandleavetwo();
	afx_msg void OnUpdateMovestandleavetwo(CCmdUI* pCmdUI);
	afx_msg void OnMovestandsitfinish();
	afx_msg void OnUpdateMovestandsitfinish(CCmdUI* pCmdUI);
	afx_msg void OnMovestandsitfinishtwo();
	afx_msg void OnUpdateMovestandsitfinishtwo(CCmdUI* pCmdUI);
	afx_msg void OnFrontrun();
	afx_msg void OnUpdateFrontrun(CCmdUI* pCmdUI);
	afx_msg void OnJumprecall();
	afx_msg void OnUpdateJumprecalltwo(CCmdUI* pCmdUI);
	afx_msg void OnJumprecalltwo();
	afx_msg void OnUpdateJumprecall(CCmdUI* pCmdUI);
	afx_msg void OnJumpleave();
	afx_msg void OnUpdateJumpleave(CCmdUI* pCmdUI);
	afx_msg void OnJumpleavetwo();
	afx_msg void OnUpdateJumpleavetwo(CCmdUI* pCmdUI);
	afx_msg void OnRightdown();
	afx_msg void OnUpdateRightdown(CCmdUI* pCmdUI);
	afx_msg void OnLeftdown();
	afx_msg void OnUpdateLeftdown(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveFinish();
	afx_msg void OnUpdateRetrieveFinish(CCmdUI* pCmdUI);
	afx_msg void OnDownRecall();
	afx_msg void OnUpdateDownRecall(CCmdUI* pCmdUI);
	afx_msg void OnDownRecalltwo();
	afx_msg void OnUpdateDownRecalltwo(CCmdUI* pCmdUI);
	afx_msg void OnRecallLeave();
	afx_msg void OnUpdateRecallLeave(CCmdUI* pCmdUI);
	afx_msg void OnTurnFront();
	afx_msg void OnUpdateTurnFront(CCmdUI* pCmdUI);
	afx_msg void OnFinishRight();
	afx_msg void OnUpdateFinishRight(CCmdUI* pCmdUI);
	afx_msg void OnFinishLeft();
	afx_msg void OnUpdateFinishLeft(CCmdUI* pCmdUI);
	afx_msg void OnAutorPref();
	afx_msg void OnJumpTool();
	afx_msg void OnUpdateJumpTool(CCmdUI* pCmdUI);
	afx_msg void OnLeashTool();
	afx_msg void OnUpdateLeashTool(CCmdUI* pCmdUI);
	afx_msg void OnGateTool();
	afx_msg void OnUpdateGateTool(CCmdUI* pCmdUI);
	afx_msg void OnArrowTool();
	afx_msg void OnUpdateArrowTool(CCmdUI* pCmdUI);
	afx_msg void OnReturnStand();
	afx_msg void OnUpdateReturnStand(CCmdUI* pCmdUI);
	afx_msg void OnArrowPref();
	afx_msg void OnUpdateArrowPref(CCmdUI* pCmdUI);
	afx_msg void OnStPropDialog();
	afx_msg void OnUpdateStPropDialog(CCmdUI* pCmdUI);
	afx_msg void OnTextPropDialog();
	afx_msg void OnUpdateTextPropDialog(CCmdUI* pCmdUI);
	afx_msg void OnStraightline();
	afx_msg void OnUpdateStraightline(CCmdUI* pCmdUI);
	afx_msg void OnReversearrow();
	afx_msg void OnUpdateReversearrow(CCmdUI* pCmdUI);
	afx_msg void OnArrowproperties();
	afx_msg void OnUpdateArrowproperties(CCmdUI* pCmdUI);
	afx_msg void OnStationPref();
	afx_msg void OnUpdateStationPref(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePattern(CCmdUI* pCmdUI);
	afx_msg void OnOffset3a();
	afx_msg void OnUpdateOffset3a(CCmdUI* pCmdUI);
	afx_msg void OnOffset3b();
	afx_msg void OnUpdateOffset3b(CCmdUI* pCmdUI);
	afx_msg void OnSpirallt();
	afx_msg void OnUpdateSpirallt(CCmdUI* pCmdUI);
	afx_msg void OnSpiralrt1a();
	afx_msg void OnUpdateSpiralrt1a(CCmdUI* pCmdUI);
	afx_msg void OnSpiralrt1b();
	afx_msg void OnUpdateSpiralrt1b(CCmdUI* pCmdUI);
	afx_msg void OnStationListPr();
	afx_msg void OnStationDescPr();
	afx_msg void OnScoreSheetPr();
	afx_msg void OnTableTool();
	afx_msg void OnUpdateTableTool(CCmdUI* pCmdUI);
	afx_msg void OnSelectAllStations();
	afx_msg void OnLineTool();
	afx_msg void OnUpdateLineTool(CCmdUI* pCmdUI);
	afx_msg void OnBrJumpTool();
	afx_msg void OnUpdateBrJumpTool(CCmdUI* pCmdUI);
	afx_msg void OnScribbleTool();
	afx_msg void OnUpdateScribbleTool(CCmdUI* pCmdUI);
	afx_msg void OnBone();
	afx_msg void OnUpdateBone(CCmdUI* pCmdUI);
	afx_msg void OnSerpPattern();
	afx_msg void OnUpdateSerpPattern(CCmdUI* pCmdUI);
	afx_msg void OnFig8Pattern();
	afx_msg void OnUpdateFig8Pattern(CCmdUI* pCmdUI);
	//}}AFX_MSG
	// special message handling
	afx_msg void OnInsertAfter(UINT nID);
	afx_msg void OnUpdateInsertAfter(CCmdUI* pCmdUI);
	afx_msg void OnChangeTo(UINT nID);
	afx_msg void OnUpdateChangeTo(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

private:
	void CopySpecialObjectData(SpecialObj *dest, SpecialObj *src);
	CRect RectangleInWindow(CRect *rect_to_check, CRect *text_rect);
	void DisplayEditDialog(CPoint *top_left, CPoint *bottom_right, bool new_text);
};

#ifndef _DEBUG  // debug version in DogRunView.cpp
inline CDogRunDoc* CDogRunView::GetDocument()
   { return (CDogRunDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOGRUNVIEW_H__8A8EF023_78E6_44C9_BD65_3736C8C70892__INCLUDED_)
