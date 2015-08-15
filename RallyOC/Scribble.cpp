// Scribble.cpp: implementation of the Scribble class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "Scribble.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Scribble, CObject, 1)
Scribble::Scribble()
{
	// This empty constructor should be used by serialization only
}
Scribble::~Scribble()
{

}
Scribble::Scribble(LOGPEN *default_pen)
{
	this->m_scribble_pen = *default_pen;
	m_rectBounding.SetRectEmpty();

}

void Scribble::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_rectBounding;
		ar << this->m_scribble_pen.lopnColor;
		ar << this->m_scribble_pen.lopnStyle;
		ar << this->m_scribble_pen.lopnWidth;
		m_pointArray.Serialize(ar);
	}
	else
	{
		ar >> m_rectBounding;
		ar >> this->m_scribble_pen.lopnColor;
		ar >> this->m_scribble_pen.lopnStyle;
		ar >> this->m_scribble_pen.lopnWidth;
		m_pointArray.Serialize(ar);
		this->m_selected = false;
	}
}

BOOL Scribble::DrawStroke(CDC* pDC, BOOL printing)
{
	CPen penStroke, pen_black, * pOldPen;
	if(this->m_selected && !printing) {// draw a solid rect if selected
		pen_black.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		pOldPen = pDC->SelectObject(&pen_black);
		pDC->MoveTo(this->m_rectBounding.TopLeft());
		pDC->LineTo(this->m_rectBounding.right, this->m_rectBounding.top);
		pDC->LineTo(this->m_rectBounding.BottomRight());
		pDC->LineTo(this->m_rectBounding.left,this->m_rectBounding.bottom);
		pDC->LineTo(this->m_rectBounding.TopLeft());
		pDC->SelectObject(pOldPen);
		DeleteObject(pen_black);
	}

	if (!penStroke.CreatePen(PS_SOLID, this->m_scribble_pen.lopnWidth.x, this->m_scribble_pen.lopnColor))
		return FALSE;

	pOldPen = pDC->SelectObject(&penStroke);

	pDC->MoveTo(m_pointArray[0]);
	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		pDC->LineTo(m_pointArray[i]);
	}
	
	pDC->SelectObject(pOldPen);
	return TRUE;
}
void Scribble::FinishStroke()
{
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.

	if (m_pointArray.GetSize()==0)
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = m_pointArray[0];
	m_rectBounding = CRect(pt.x, pt.y, pt.x, pt.y);

	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = m_pointArray[i];
		m_rectBounding.left     = min(m_rectBounding.left, pt.x);
		m_rectBounding.right    = max(m_rectBounding.right, pt.x);
		m_rectBounding.top      = max(m_rectBounding.top, pt.y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(this->m_scribble_pen.lopnWidth.x, -(int)this->m_scribble_pen.lopnWidth.x));
	this->m_rectBounding.NormalizeRect();
	return;
}

void Scribble::SetSelectedFlag(BOOL selected)
{
	this->m_selected = selected;
}

BOOL Scribble::GetScribbleSelectedFlag()
{
	return this->m_selected;
}

int Scribble::HitPointInScribbleRect(POINT *hit_point)
 {
 	BOOL in_rect, in_array = false;
	in_rect = this->m_rectBounding.PtInRect(*hit_point);
	if (in_rect) { 
		if (this->m_selected) return ALL_READY_SELECTED; 
		int array_size = m_pointArray.GetSize();
		for (int i=1; i < array_size; i++)
		{
			POINT x_y;
			x_y = m_pointArray[i];
			int diff_x, diff_y;
			diff_x = x_y.x - hit_point->x;
			diff_y = x_y.y - hit_point->y;

			if ((diff_x > -(this->m_scribble_pen.lopnWidth.x + 5) && diff_x < this->m_scribble_pen.lopnWidth.x + 5) && 
				(diff_y > -(this->m_scribble_pen.lopnWidth.x + 5) && diff_y < this->m_scribble_pen.lopnWidth.x + 5)) in_array = true;
			if (in_array) i = array_size + 1;
		}		
		if (in_array) {
			if (this->m_selected) {
				return ALL_READY_SELECTED;
			}
			else {
				return SELECTED;
			}
		}
		else 
			return NOT_SELECTED;
	}
	else {
		return NOT_SELECTED;
	}

 }


CRect Scribble::GetScribbleRect()
{
	return this->m_rectBounding;
}

void Scribble::SetUndoRedoAction(int undo_action)
{
	this->m_undo_action = undo_action;
}

int Scribble::GetUndoRedoAction()
{
	return this->m_undo_action;
}

void Scribble::SetUndoRedoPosition(POSITION pos_in_scribble_list)
{
	this->m_pos_in_scribble_list = pos_in_scribble_list;
}

POSITION Scribble::GetUndoRedoPosition()
{
	return this->m_pos_in_scribble_list;
}

bool Scribble::ScribbleRectInRegion(CRgn *select_rgn)
{
	if (select_rgn->RectInRegion(&this->m_rectBounding))
		return true;
	else 
		return false;

}

void Scribble::OffsetScribble(CPoint *p_offset_point)
{
	CPoint temp_point;
	int how_many = m_pointArray.GetSize();
	for (int i=0; i < m_pointArray.GetSize(); i++)
	{
		temp_point = m_pointArray[i];
		temp_point.Offset(*p_offset_point);
		m_pointArray[i] = temp_point;
	}
	this->FinishStroke();
	this->m_rectBounding.NormalizeRect();
}

void Scribble::SetSelection(BOOL selection_status)
{
	this->m_selected = selection_status;
}

void Scribble::SetScribblePen(LOGPEN *scribble_pen)
{
	this->m_scribble_pen = *scribble_pen;
}

LOGPEN * Scribble::GetScribblePen(LOGPEN *scribble_pen)
{
	*scribble_pen = this->m_scribble_pen;
	return scribble_pen;
}
