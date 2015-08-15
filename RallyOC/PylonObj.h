// PylonObj.h: interface for the PylonObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PYLONOBJ_H__B5E0DBBA_4454_46A9_B3F4_E5D80676C526__INCLUDED_)
#define AFX_PYLONOBJ_H__B5E0DBBA_4454_46A9_B3F4_E5D80676C526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PylonObj : public CObject  
{
public:
	POSITION GetUndoRedoPosition(void);
	void SetUndoRedoPosition(POSITION pos_in_pylon_list);
	int GetUndoRedoAction(void);
	void SetUndoRedoAction(int undo_action);
	void SetPylonRect(void);
	void OffSetPylonRect(CPoint *point);
	int HitPointInPylonRect(POINT *loc, UINT nFlags);
	bool RallyRectInRegion(CRgn *select_rgn);
	bool GetSelectedFlag(void);
	void SetSelectedFlag(bool selected);
	int MousePointInPylonRect(POINT *p_mouse_pt);
	void DrawCones(CDC* pDC);
	void OffsetXYPos(POINT *p_offset_amt);
	CRect GetPylonRect(CRect *p_pylon_rect);
	void SetPylonRect(CRect *p_new_rect);
	POINT GetXYPosition(POINT *p_position);
	void SetXYPosition(POINT *p_new_pos);
	int GetOwner(void);
	void SetOwner(int owner_station);
	virtual void Serialize(CArchive &ar);
	PylonObj();
	DECLARE_SERIAL(PylonObj)
	PylonObj(int xPos, int yPos);
	virtual ~PylonObj();
private:
	int m_xPos;
	int m_yPos;
	int m_station_owner;
	bool m_selected;
	CRect m_pylon_rect;
	int m_width;
	int m_height;
	CString m_error_string;
	POSITION m_pos_in_pylon_list;
	int m_undo_action;
protected:

};

#endif // !defined(AFX_PYLONOBJ_H__B5E0DBBA_4454_46A9_B3F4_E5D80676C526__INCLUDED_)
