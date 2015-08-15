// Scribble.h: interface for the Scribble class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIBBLE_H__7BD49472_DFE1_485B_8C8A_DC727E759A35__INCLUDED_)
#define AFX_SCRIBBLE_H__7BD49472_DFE1_485B_8C8A_DC727E759A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Scribble : public CObject  
{
public:
	Scribble(LOGPEN *default_pen);
	virtual ~Scribble();
protected:
	Scribble();
	DECLARE_SERIAL(Scribble)

// Attributes
protected:
	BOOL m_selected;
	POSITION m_pos_in_scribble_list;
	int m_undo_action;
	LOGPEN m_scribble_pen;
public:
	CArray<CPoint,CPoint>  m_pointArray;   // series of connected points
	CRect               m_rectBounding; // smallest rect that surrounds all
										// of the points in the stroke
										// measured in MM_LOENGLISH units
										// (0.01 inches, with Y-axis inverted)
public:
	CRect& GetBoundingRect() { return m_rectBounding; }

// Operations
public:
	BOOL DrawStroke(CDC* pDC, BOOL printing);
	void FinishStroke();

public:
	LOGPEN * GetScribblePen(LOGPEN *scribble_pen);
	void SetScribblePen(LOGPEN *scribble_pen);
	void SetSelection(BOOL selection_status);
	void OffsetScribble(CPoint *p_offset_point);
	bool ScribbleRectInRegion(CRgn *select_rgn);
	POSITION GetUndoRedoPosition(void);
	void SetUndoRedoPosition(POSITION pos_in_scribble_list);
	int GetUndoRedoAction(void);
	void SetUndoRedoAction(int undo_action);
	CRect GetScribbleRect(void);
	int HitPointInScribbleRect(POINT *hit_point);
	BOOL GetScribbleSelectedFlag(void);
	void SetSelectedFlag(BOOL selected);
	virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_SCRIBBLE_H__7BD49472_DFE1_485B_8C8A_DC727E759A35__INCLUDED_)
