// TextObj.cpp: implementation of the TextObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "TextObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(TextObj, CObject, VERSIONABLE_SCHEMA | 1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TextObj::TextObj()
{
	// This empty constructor should be used by serialization only
}
TextObj::TextObj(CRect *p_text_rect, LOGFONT *p_logfont, COLORREF color_ref)
{
	this->m_text_rect = *p_text_rect;
	this->m_display_text.Empty();
	this->m_log_font = new MyFont(p_logfont, color_ref);
	this->m_selected = true;
	this->m_draw_box = true;
}
TextObj::~TextObj()
{
	delete this->m_log_font;
}
void TextObj::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << this->m_display_text;
		ar << this->m_text_rect;
		ar << this->m_log_font;
		ar << this->m_draw_box;

	}
	else
	{
		// TODO: add loading code here
		int version = ar.GetObjectSchema();
		switch (version) {
		case 1:
			ar >> this->m_display_text;
			ar >> this->m_text_rect;
			ar >> this->m_log_font;
			this->m_selected = false;
			ar >> this->m_draw_box;
			break;
		case 2:
			break;
		}
	}
	
}

void TextObj::DrawTextBox(CDC *pDC, BOOL is_printing)
{
	CFont *p_old_font, text_font;
	CPen* pOldPen;
	CPen penBlack, color_pen;
	CRect draw_rect;

	if (this->m_selected && !is_printing ) {
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		pOldPen = pDC->SelectObject(&penBlack);
		draw_rect = this->m_text_rect;

		draw_rect.InflateRect(5,5);
		draw_rect.top -= 1;
		draw_rect.left -= 2;
		draw_rect.bottom -= 2;
		draw_rect.right -= 2;

		pDC->MoveTo(draw_rect.TopLeft());
		pDC->LineTo(draw_rect.right, draw_rect.top);
		pDC->LineTo(draw_rect.BottomRight());
		pDC->LineTo(draw_rect.left,draw_rect.bottom);
		pDC->LineTo(draw_rect.TopLeft());		
		pDC->SelectObject(pOldPen);
		DeleteObject(penBlack);

	}

	
	if (this->m_draw_box) {
		color_pen.CreatePen(PS_SOLID, 1, this->m_color_box);
		pOldPen = pDC->SelectObject(&color_pen);
		draw_rect = this->m_text_rect;
		draw_rect.top -= 1;
		draw_rect.left -= 2;
		draw_rect.bottom -= 2;
		draw_rect.right -= 2;
		pDC->MoveTo(draw_rect.TopLeft());
		pDC->LineTo(draw_rect.right, draw_rect.top);
		pDC->LineTo(draw_rect.BottomRight());
		pDC->LineTo(draw_rect.left,draw_rect.bottom);
		pDC->LineTo(draw_rect.TopLeft());		
		pDC->SelectObject(pOldPen);
		DeleteObject(color_pen);
	}


	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       
	this->m_log_font->GetLogFont(&lf);	
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(pDC->m_hDC, LOGPIXELSY)) / 72);
	
	VERIFY(text_font.CreateFontIndirect(&lf));  // create the font

	p_old_font = pDC->SelectObject(&text_font);
	COLORREF old_color = pDC->SetTextColor(this->GetColorRef());
	draw_rect = this->m_text_rect;

	draw_rect.left += 4;
	pDC->DrawText(this->m_display_text,&draw_rect,DT_LEFT|DT_WORDBREAK|DT_END_ELLIPSIS );
	pDC->SetTextColor(old_color);
 
}

void TextObj::SetDisplayText(CString *p_display_text)
{
	this->m_display_text = *p_display_text;
}

CString TextObj::GetDisplayText()
{
	return this->m_display_text;
}

void TextObj::SetDisplayTextRect(CRect *p_text_rect)
{
	this->m_text_rect = *p_text_rect;
}

void TextObj::GetDisplayTextRect(CRect *p_text_rect)
{
	*p_text_rect = this->m_text_rect;
}
void TextObj::SetDrawBox(BOOL draw_box)
{
	this->m_draw_box = draw_box;
}

BOOL TextObj::GetDrawBox()
{
	return this->m_draw_box;
}

int TextObj::MousePtInTextRect(POINT *p_mouse_pt)
{
	BOOL in_rect;
	in_rect = this->m_text_rect.PtInRect(*p_mouse_pt);
	if (in_rect) { 
		if (this->m_selected) {
			return ALL_READY_SELECTED;
		}
		else {
			return SELECTED;
		}
	}
	else {
		return NOT_SELECTED;
	}
}

void TextObj::SetSelectedFlag(bool selected)
{
	this->m_selected = selected;
}

bool TextObj::GetSelectedFlag()
{
	return this ->m_selected;
}

bool TextObj::TextRectInRegion(CRgn *select_rgn)
{
	if (select_rgn->RectInRegion(&this->m_text_rect))
		return true;
	else 
		return false;
}

void TextObj::OffsetTextRect(CPoint *off_set)
{
	this->m_text_rect.OffsetRect(*off_set);
}


void TextObj::SetLogFont(CFont *p_text_font)
{
	this->m_log_font->SetFont(p_text_font);
}

void TextObj::SetLogFont(LOGFONT *p_log_font)
{
	this->m_log_font->SetFont(p_log_font);
}

void TextObj::GetLogFont(LOGFONT *p_log_font)
{
	this->m_log_font->GetLogFont(p_log_font);
}

void TextObj::SetTextColor(COLORREF color_ref)
{
	this->m_log_font->SetColorReference(color_ref);
}

COLORREF TextObj::GetColorRef()
{
	return this->m_log_font->GetColorReference();
}

MyFont * TextObj::GetMyFontObject()
{
	return this->m_log_font;
}

void TextObj::SetInvalRect(CRect *inval_rect)
{
	this->m_inval_rect = *inval_rect;
}

CRect TextObj::GetInvalRect()
{
	return this->m_inval_rect;
}

void TextObj::SetUndoRedoAction(int undo_action)
{
	this->m_undo_action = undo_action;
}

int TextObj::GetUndoRedoAction()
{
	return this->m_undo_action;
}

void TextObj::SetUndoRedoPosition(POSITION pos_in_text_list)
{
	this->m_pos_in_text_list = pos_in_text_list;
}


POSITION TextObj::GetUndoRedoPosition()
{
	return this->m_pos_in_text_list;
}

bool TextObj::RallyRectInRegion(CRgn *select_rgn)
{
	if (select_rgn->RectInRegion(&this->m_text_rect))
		return true;
	else 
		return false;
}

void TextObj::SetTextBoxRectColor(COLORREF outline_color)
{
	this->m_color_box = outline_color;
}

COLORREF TextObj::GetTextBoxRectColor()
{
	return this->m_color_box;
}
