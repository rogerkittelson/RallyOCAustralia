// TextObj.h: interface for the TextObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTOBJ_H__1588A978_849B_400F_A253_AEC1B976FFE3__INCLUDED_)
#define AFX_TEXTOBJ_H__1588A978_849B_400F_A253_AEC1B976FFE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyFont.h"
class TextObj : public CObject  
{
public:
	COLORREF GetTextBoxRectColor(void);
	void SetTextBoxRectColor(COLORREF outline_color);
	bool RallyRectInRegion(CRgn *select_rgn);
	POSITION GetUndoRedoPosition(void);
	int GetUndoRedoAction(void);
	void SetUndoRedoPosition(POSITION pos_in_text_list);
	void SetUndoRedoAction(int undo_action);
	CRect GetInvalRect(void);
	void SetInvalRect(CRect *inval_rect);
	MyFont * GetMyFontObject(void);
	COLORREF GetColorRef(void);
	void SetTextColor(COLORREF color_ref);
	void GetLogFont(LOGFONT *p_log_font);
	void SetLogFont(LOGFONT *p_log_font);
	void SetLogFont(CFont *p_text_font);
	void GetDisplayTextRect(CRect *p_text_rect);
	void OffsetTextRect(CPoint *off_set);
	bool TextRectInRegion(CRgn *select_rgn);
	bool GetSelectedFlag(void);
	void SetSelectedFlag(bool selected);
	int MousePtInTextRect(POINT *p_mouse_pt);
	BOOL GetDrawBox(void);
	void SetDrawBox(BOOL draw_box);
	void SetDisplayTextRect(CRect *p_text_rect);
	CString GetDisplayText(void);
	void SetDisplayText(CString *p_display_text);
	void DrawTextBox(CDC *pDC, BOOL is_printing);
	TextObj(CRect *p_text_rect, LOGFONT *p_logfont, COLORREF color_ref);
	virtual ~TextObj();
	virtual void Serialize(CArchive &ar);
private:
	MyFont *m_log_font;
	CString m_display_text;
	CRect m_text_rect;
	CRect m_inval_rect;
	BOOL m_draw_box;
	COLORREF m_color_box;
	bool m_selected;
	POSITION m_pos_in_text_list;
	int m_undo_action;
	TextObj();
	DECLARE_SERIAL(TextObj)
};

#endif // !defined(AFX_TEXTOBJ_H__1588A978_849B_400F_A253_AEC1B976FFE3__INCLUDED_)
