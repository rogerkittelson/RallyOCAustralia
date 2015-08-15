// PylonObj.cpp: implementation of the PylonObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "PylonObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(PylonObj, CObject, VERSIONABLE_SCHEMA | 1)

PylonObj::PylonObj()
{
	// This empty constructor should be used by serialization only
}
PylonObj::PylonObj(int xPos, int yPos)
{
	this->m_xPos = xPos;
	this->m_yPos = yPos;
	this->m_selected = false;
	this->SetPylonRect();
}

PylonObj::~PylonObj()
{

}

void PylonObj::Serialize(CArchive &ar)
{

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_xPos;
		ar << m_yPos;
		ar << m_station_owner;

	}
	else
	{
		// TODO: add loading code here
		int version = ar.GetObjectSchema();
		switch (version) {
			case 1:
			ar >> m_xPos;
			ar >> m_yPos;
			ar >> m_station_owner;
			this->m_selected = false;
			this->SetPylonRect();
			break;
		case 2:

			break;
		}
	}
	
}

void PylonObj::SetOwner(int owner_station)
{
	this->m_station_owner = owner_station;
}

int PylonObj::GetOwner()
{
	return this->m_station_owner;
}

void PylonObj::SetXYPosition(POINT *p_new_pos)
{
	this->m_xPos = p_new_pos->x;
	this->m_yPos = p_new_pos->y;
	this->SetPylonRect();
}

POINT PylonObj::GetXYPosition(POINT *p_position)
{
	POINT position;
	position.x = this->m_xPos;
	position.y = this->m_yPos;
	*p_position = position;
	return position;
}

void PylonObj::OffsetXYPos(POINT *p_offset_amt)
{
	this->m_xPos += p_offset_amt->x;
	this->m_yPos += p_offset_amt->y;
	this->SetPylonRect();
}
void PylonObj::SetPylonRect(CRect *p_new_rect)
{
	this->m_pylon_rect = *p_new_rect;
	this->m_xPos = this->m_pylon_rect.right - (this->m_width/2);
	this->m_yPos = this->m_pylon_rect.bottom - (this->m_height/2);	
}

CRect PylonObj::GetPylonRect(CRect *p_pylon_rect)
{
	*p_pylon_rect = this->m_pylon_rect;
	return this->m_pylon_rect;
}


void PylonObj::DrawCones(CDC *pDC)
{
	BOOL draw;
	CBitmap hImage;
	CBitmap *pOldBitmap;
	CDC memDC; 
	CPen penBlack, *pOldPen;
	CPen penBlue;
	int draw_error = NO_DRAW_ERROR;
	
	if (hImage.LoadBitmap(IDB_PYLONS)) {
		BITMAP bmpInfo;

		hImage.GetBitmap(&bmpInfo);

		pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC

		RECT outline_rect = this->m_pylon_rect;

// make the outline
		InflateRect(&outline_rect,1,1);

   // create and select a black pen

		if (!pDC->IsPrinting()) {

			if(this->m_selected) {// draw a solid rect if selected
				penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			}
			else { // or a dashed if not
				penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
			}
			pOldPen = pDC->SelectObject(&penBlack);

			pDC->Rectangle(&outline_rect);
			pDC->SelectObject(pOldPen);
			DeleteObject(penBlack);

			// now rect back
			InflateRect(&outline_rect,-1,-1);

		}

		if(pDC->GetDeviceCaps(RASTERCAPS) & RC_BITBLT == 0) {
			draw_error = NO_BITBLT;
			m_error_string = "DEVICE DOES NOT SUPPORT BITBLTS";
		}
			
		memDC.CreateCompatibleDC(pDC); // dc for window 
		pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
		draw = pDC->BitBlt(outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
			&memDC, 0, 0, SRCAND);

	}
}

void PylonObj::SetPylonRect()
{
	CBitmap bmp;
	if (bmp.LoadBitmap(IDB_PYLONS)) 	{
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		this->m_pylon_rect.left = this->m_xPos - (bmpInfo.bmWidth/2);
		this->m_pylon_rect.right = this->m_xPos + (bmpInfo.bmWidth/2);
		this->m_pylon_rect.top = this->m_yPos - (bmpInfo.bmHeight/2);
		this->m_pylon_rect.bottom = this->m_yPos + (bmpInfo.bmHeight/2);
		this->m_width = this->m_pylon_rect.right - this->m_pylon_rect.left;
		this->m_height = this->m_pylon_rect.bottom - this->m_pylon_rect.top;

	}
	else {
		this->m_error_string.Format("ERROR: Where's %d?",IDB_PYLONS);
		TRACE0(this->m_error_string);
	}
}

int PylonObj::MousePointInPylonRect(POINT *p_mouse_pt)
{
	BOOL in_rect;
	in_rect = this->m_pylon_rect.PtInRect(*p_mouse_pt);
	if (in_rect) { 
		if (this->m_selected) {
			return ALL_READY_SELECTED;
		}
		else {
//			this->m_selected = true;
			return SELECTED;
		}
	}
	else {
//		this->m_selected = false;
		return NOT_SELECTED;
	}

}

void PylonObj::SetSelectedFlag(bool selected)
{
	this->m_selected = selected;
}

bool PylonObj::GetSelectedFlag()
{
	return this->m_selected;
}

bool PylonObj::RallyRectInRegion(CRgn *select_rgn)
{
	if (select_rgn->RectInRegion(&this->m_pylon_rect))
		return true;
	else 
		return false;

}

int PylonObj::HitPointInPylonRect(POINT *loc, UINT nFlags)
{
	// de-select on shift key down in rect if already selected
	if (this->m_selected && (nFlags &MK_SHIFT) && this->m_pylon_rect.PtInRect(*loc)) { 
		this->m_selected = false;
		return NOT_SELECTED;
	}
	// already selected on shift key down outside rect do nothing
	if (this->m_selected && (nFlags &MK_SHIFT) && !this->m_pylon_rect.PtInRect(*loc)) { 
		return ALL_READY_SELECTED;
	}
		
	if (this->m_pylon_rect.PtInRect(*loc)) {
		this->m_selected = true;
		return SELECTED;
	}
	else { 
		this->m_selected = false;
		return NOT_SELECTED;
	}
}

void PylonObj::OffSetPylonRect(CPoint *point)
{
	this->m_pylon_rect.OffsetRect(*point);
	this->m_xPos = this->m_pylon_rect.right - (this->m_width/2);
	this->m_yPos = this->m_pylon_rect.bottom - (this->m_height/2);	
}

void PylonObj::SetUndoRedoAction(int undo_action)
{
	this->m_undo_action = undo_action;
}

int PylonObj::GetUndoRedoAction()
{
	return this->m_undo_action;
}

void PylonObj::SetUndoRedoPosition(POSITION pos_in_pylon_list)
{
	this->m_pos_in_pylon_list = pos_in_pylon_list;
}

POSITION PylonObj::GetUndoRedoPosition()
{
	return this->m_pos_in_pylon_list;
}
