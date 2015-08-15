// SpecialObj.h: interface for the SpecialObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECIALOBJ_H__7B96E366_06FF_4D23_A862_39D4406FCCDB__INCLUDED_)
#define AFX_SPECIALOBJ_H__7B96E366_06FF_4D23_A862_39D4406FCCDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SpecialObj : public CObject  
{
public:
	void SetStationDegreeRotation(void);
	void CalculateRotateMeasurements(double degree_rotation);
	void GetRotateMeasurements(float *p_M11, float *p_M12, float *p_M21, float *p_M22);
	POSITION GetUndoRedoPosition(void);
	void SetUndoRedoPosition(POSITION pos_in_special_list);
	int GetUndoRedoAction();
	void SetUndoRedoAction(int undo_action);
	int GetTypeObject(void);
	void SetTypeObject(int type_object);
	int GetYPos(void);
	virtual void Serialize(CArchive &ar);
	void OffSetSpecialRect(CPoint *point);
	void ResizeSpecial(POINT *p_loc);
	int PointInHandleRect(POINT *loc);
	void RotateSpecial(CPoint *point);
	void SetRotateMeasurements(float M11, float M12, float M21, float M22);
	void GetHandleRect(int which_handle, RECT *handle_rect);
	void OffsetXYPos(POINT *p_offset_amt);
	BOOL RallyRectInRegion(CRgn *select_rgn);
	void RotateJump(CPoint *point);
	BOOL GetSelectedFlag(void);
	void SetSelectedFlag(BOOL selected);
	int MousePointInSpecialRect(POINT *p_mouse_pt);
	void GetSpecialRect(CRect *p_rect);
	void SetSpecialRect(CRect *p_rect);
	void SetYPos(int y_pos);
	int GetXPos(void);
	void SetXPos(int x_pos);
	void SetSpecialRect(void);
	void DrawSpecialObjects(CDC *pDC, BOOL printing);
	int m_handle_selected;
	double m_rotate_degrees;
	DECLARE_SERIAL(SpecialObj)
	SpecialObj();
	SpecialObj(int xPos, int yPos, int type_object);
	virtual ~SpecialObj();
private:
	int m_xPos;
	int m_yPos;
	BOOL m_selected;
	CRect m_object_rect;
	int m_width;
	int m_height;
	int m_type_object;
	float m_M11, m_M12, m_M21, m_M22;
	CString m_error_string; 
	POSITION m_pos_in_special_list;
	int m_undo_action;
};

#endif // !defined(AFX_SPECIALOBJ_H__7B96E366_06FF_4D23_A862_39D4406FCCDB__INCLUDED_)
