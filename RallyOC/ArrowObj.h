// ArrowObj.h: interface for the ArrowObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARROWOBJ_H__395889BE_B81F_4A14_B698_D1B1C11F9797__INCLUDED_)
#define AFX_ARROWOBJ_H__395889BE_B81F_4A14_B698_D1B1C11F9797__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//Macro to convert mouse points (short) to points (long).
#define MPOINT2POINT(mpt, pt)   ((pt).x = (mpt).x, (pt).y = (mpt).y)

#define POINTS2VECTOR2D(pt0, pt1, vect) ((vect).x = (double)((pt1).x - (pt0).x), \
                                         (vect).y = (double)((pt1).y - (pt0).y))

#define SGN(a) (((a)<0) ? -1 : 0)

#define MAXDEPTH  64	                  //Maximum depth for recursion  
#define	EPSILON	 (ldexp(1.0,-MAXDEPTH-1)) //Flatness control value 
#define	DEGREE	 3		                  //Cubic Bezier curve  		
#define	W_DEGREE 5		                  //Degree of eqn to find roots of  

enum arrow_handles {
	NO_HIT = 0,
	EXIT_HANDLE = 1,
	FIRST_HANDLE = 3,
	SECOND_HANDLE = 6,
	THIRD_HANDLE = 9,
	FOURTH_HANDLE = 12,
	ENTRY_HANDLE = 15,
	NO_HANDLE = -1,
	LINE_HIT = 100
};
class ArrowObj : public CObject  
{
public:
	int GetHandleSelected(void);
	bool GetArrowSelection(void);
	LOGPEN GetArrowPen(void);
	bool GetArrow();
	void SetHideArrow(BOOL hide_arrow);
	BOOL GetHideArrow(void);
	void GetArrowRect(CRect *arrow_rect);
	BOOL GetMoveWithStation(void);
	void SetMoveWithStation(bool move_with_station);
	int FindIndexOfDrawPoints(POINT lpPt[], int num_points);
	void ReverseArrow(void);
	void StraightenArrow(void);
	BOOL MousePointInGeneralRect(POINT *p_mouse_pt);
	void SetDrawPointsArray(CPoint draw_points[16]);
	void GetDrawPointsArray(CPoint draw_points[16]);
	void SetDrawPointsFromMidPoint(CPoint *p_mid_point);
	POSITION GetUndoRedoPosition(void);
	void SetUndoRedoPosition(POSITION pos_in_arrow_list);
	int GetUndoRedoAction(void);
	void SetUndoRedoAction(int undo_action);
	void SetDrawPoints(CPoint *off_set_pt);
	void DrawArrowPoint(CDC *pDC, POINT *p_move_to);
	bool PointInGrabHandle(POINT *hit_point);
	void DrawGrabRects(CDC *pDC);
	void IntilizeDrawPoints(void);
	void DrawArrowPoint(CDC *pDC);
	void CurveLine(CDC *pDC, CPoint *p_mouse_pt, BOOL size_to_screen);
	int GetArrowType(void);
	void SetArrowType(int arrow_type);
	void SetSelection(bool selected);
	void CheckForLineInRect(CRgn *rect_to_check);
	PVECTOR2D vSubtractVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v);
	double vVectorSquared(PVECTOR2D v0);
	double vVectorMagnitude(PVECTOR2D v0);
	double vDotProduct(PVECTOR2D v0, PVECTOR2D v1);
	void vProjectAndResolve(PVECTOR2D v0, PVECTOR2D v1, PPROJECTION ppProj);
	double vDistFromPointToLine(LPPOINT pt0, LPPOINT pt1, LPPOINT ptTest);
	bool HitTestLineforBezier(POINT pt0, POINT pt1, POINT ptMouse, int nWidth, HDC hdc);
	BOOL ArrowObj::HitTestLine(POINT pt0, POINT pt1, POINT ptMouse, int nWidth);
	bool HitTestLine(POINT hit_point, HDC hdc);
	int HitTestCurve(POINT hit_point, HDC hdc);
	int GetEntryOwner(void);
	void SetEntryOwner(int entry_owner);
	int GetExitOwner(void);
	void SetExitOwner(int exit_owner);
	ArrowObj(CPoint *entry_point, CPoint *exit_point, LOGPEN *default_pen, int entry_owner, int exit_owner, int arrow_type, BOOL move_with_station, BOOL create_line);
	virtual void Serialize(CArchive &ar);
	void DrawArrow(CDC *pDC, BOOL printing, BOOL dragging);
	void SetPenForArrow(int nPenStyle, int nWidth, COLORREF crColor );
	void SetEntryPoint(CPoint *entry_point);
	CPoint GetEntryPoint(void);
	void SetExitPoint(CPoint *exit_point);
	CPoint GetExitPoint(void);
	void SetGrabHandleRects(void);
	virtual ~ArrowObj();
private:
	POINT CalculatePointForArray(POINT *p_first_point, POINT *p_second_point, double multiplier);
	void CalculatePointsToAdd(POINT *first_point, POINT *second_point, POINT *mouse_pt, POINT *new_ft_pt, POINT *new_sec_pt);
	void CalculateMidPoint(POINT *p_first_point, POINT *p_second_point, POINT *p_mid_point);
	VECTOR2D  NearestPointOnCurve(PVECTOR2D pvTest, PVECTOR2D pvControl);
	PVECTOR2D ConvertToBezierForm(PVECTOR2D P, PVECTOR2D V);
	int       RecursiveSubDivide(PVECTOR2D w, int degree, double *t, int depth);
	int       CrossingCount(PVECTOR2D V, int degree);
	int       ControlPolygonFlatEnough(PVECTOR2D V, int degree);
	double    ComputeXIntercept (PVECTOR2D V, int degree);
	VECTOR2D  Bezier (PVECTOR2D V, int degree, double t, PVECTOR2D Left, PVECTOR2D Right);
	PVECTOR2D vScaleVector(PVECTOR2D v0, double dScaling, PVECTOR2D v);
	void ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA, BOOL just_point);
	ArrowObj();
	DECLARE_SERIAL(ArrowObj)
// arrow charateristics
	CPoint m_exit_point;
	CPoint m_entry_point;
	CPoint m_mid_point;
	LOGPEN m_arrow_pen;
// arrow "owners", based on the station number
	int m_exit_owner;
	int m_entry_owner;
	int m_arrow_type;
	BOOL m_draw_arrow;
	BOOL m_move_with_station;
	CPoint m_draw_points[16];
	bool m_arrow_selected;
	int m_handle_selected;
	CRect m_entry_grab;
	CRect m_exit_grab;
	CRect m_first_grab;
	CRect m_second_grab;
	CRect m_third_grab;
	CRect m_fourth_grab;
	CPoint m_mouse_pt;
	CPoint m_hit_point;
	POSITION m_pos_in_arrow_list;
	int m_undo_action;
};

#endif // !defined(AFX_ARROWOBJ_H__395889BE_B81F_4A14_B698_D1B1C11F9797__INCLUDED_)
