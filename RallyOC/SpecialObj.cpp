// SpecialObj.cpp: implementation of the SpecialObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "SpecialObj.h"
#include "EnBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(SpecialObj, CObject, VERSIONABLE_SCHEMA | 1)

SpecialObj::SpecialObj()
{
	// This empty constructor should be used by serialization only

}

SpecialObj::SpecialObj(int xPos, int yPos, int type_object)
{
	this->m_xPos = xPos;
	this->m_yPos = yPos;
	this->m_selected = false;
	this->m_type_object = type_object;
	m_M11 = m_M22 = (float)1.0;
	m_M12 = (float)-0.0; 
	m_M21 = (float)0.0;
	this->SetStationDegreeRotation();
	this->SetSpecialRect();

}
SpecialObj::~SpecialObj()
{

}
void SpecialObj::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << this->m_type_object;
		ar << this->m_object_rect;
		ar << this->m_xPos;
		ar << this->m_yPos;
		ar << this->m_M11;
		ar << this->m_M12;
		ar << this->m_M21;
		ar << this->m_M22;
		ar << this->m_height;
		ar << this->m_width;
	}
	else
	{
		// TODO: add loading code here
		ar >> this->m_type_object;
		ar >> this->m_object_rect;
		ar >> this->m_xPos;
		ar >> this->m_yPos;
		ar >> this->m_M11;
		ar >> this->m_M12;
		ar >> this->m_M21;
		ar >> this->m_M22;
		ar >> this->m_height;
		ar >> this->m_width;
		this->m_selected = false;
		this->SetStationDegreeRotation();
	}
}
void SpecialObj::DrawSpecialObjects(CDC *pDC, BOOL printing)
{
	BOOL draw;
	CEnBitmap hImage;
	CBitmap *pOldBitmap;
	CDC memDC; 

	int draw_error = NO_DRAW_ERROR;
	int last_mode = 0;
	CBitmap rotate_image, resize_image;
	RECT handle_rect;
	
	if (hImage.LoadBitmap(this->m_type_object)) {
		BITMAP bmpInfo;

		hImage.GetBitmap(&bmpInfo);

		pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC

		RECT outline_rect = this->m_object_rect;
	
// make the outline
		InflateRect(&outline_rect,1,1);

   // create and select a black pen
		CPen* pOldPen;
		CPen penBlack;

		if(this->m_selected && !printing) {// draw a solid rect if selected
			penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			pOldPen = pDC->SelectObject(&penBlack);

			pDC->MoveTo(outline_rect.left, outline_rect.top);
			pDC->LineTo(outline_rect.right, outline_rect.top);
			pDC->LineTo(outline_rect.right, outline_rect.bottom);
			pDC->LineTo(outline_rect.left, outline_rect.bottom);
			pDC->LineTo(outline_rect.left, outline_rect.top);
			pDC->SelectObject(pOldPen);
			DeleteObject(penBlack);
		}
		else if(!printing) { // or a dashed if not
			penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
			pOldPen = pDC->SelectObject(&penBlack);

			pDC->MoveTo(outline_rect.left, outline_rect.top);
			pDC->LineTo(outline_rect.right, outline_rect.top);
			pDC->LineTo(outline_rect.right, outline_rect.bottom);
			pDC->LineTo(outline_rect.left, outline_rect.bottom);
			pDC->LineTo(outline_rect.left, outline_rect.top);
			pDC->SelectObject(pOldPen);
			DeleteObject(penBlack);
		}


		// now rect back
		InflateRect(&outline_rect,-1,-1);


		if(pDC->GetDeviceCaps(RASTERCAPS) & RC_BITBLT == 0) {
			draw_error = NO_BITBLT;
			m_error_string = "DEVICE DOES NOT SUPPORT BITBLTS";
		}
		if(pDC->GetDeviceCaps(RASTERCAPS) & RC_STRETCHBLT  == 0) {
			draw_error = NO_STRECHBLT;
			m_error_string = "DEVICE DOES NOT SUPPORT STRECTCHBLT";
		}
		memDC.CreateCompatibleDC(pDC); // dc for window 
		last_mode = SetGraphicsMode (pDC->m_hDC, GM_ADVANCED);			
		if (last_mode) {
			pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC

			POINT lpPoint[3];

			XFORM  x;
			POINT pivot;

			pivot.x = this->m_object_rect.left + (this->m_width/2); 
			pivot.y = this->m_object_rect.top + (this->m_height/2); 
			
			// top left
			lpPoint[0].x = this->m_object_rect.left;		
			lpPoint[0].y = this->m_object_rect.top;		
			// top right
			lpPoint[1].x = this->m_object_rect.right;		
			lpPoint[1].y = this->m_object_rect.top;		
			// bottom left
			lpPoint[2].x = this->m_object_rect.left;		
			lpPoint[2].y = this->m_object_rect.bottom;		

			x.eM11 = (float)1.0;
			x.eM12 = (float)0.0;
			x.eM21 = (float)0.0;
			x.eM22 = (float)1.0;
			x.eDx = (float)-pivot.x;
			x.eDy = (float)-pivot.y;
			draw = ModifyWorldTransform (pDC->m_hDC, &x, MWT_RIGHTMULTIPLY);
			if (!draw) 
				draw_error += NO_WORLD_TRANS;

			/* rotate object about origin. */
			x.eM11 = m_M11;
			x.eM12 = m_M12;
			x.eM21 = m_M21;
			x.eM22 = m_M22;
			x.eDx = (float)0.0;
			x.eDy = (float)0.0;
			draw = ModifyWorldTransform (pDC->m_hDC, &x, MWT_RIGHTMULTIPLY);


			/* translate objects back to pivot point. */
			x.eM11 = (float)1.0;
			x.eM12 = (float)0.0;
			x.eM21 = (float)0.0;
			x.eM22 = (float)1.0;
			x.eDx = (float)pivot.x;
			x.eDy = (float)pivot.y;
			draw = ModifyWorldTransform (pDC->m_hDC, &x, MWT_RIGHTMULTIPLY);

			draw = pDC->StretchBlt (outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
				&memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCAND );
				
			ModifyWorldTransform (pDC->m_hDC, &x, MWT_IDENTITY);
			if (last_mode)SetGraphicsMode (pDC->m_hDC, last_mode);
		}
		else {
			CBitmap bmp,*pOldBmp;
			bmp.CreateCompatibleBitmap(pDC,this->m_width + 20,this->m_height+ 20);
			pOldBmp=memDC.SelectObject(&bmp);
			memDC.PatBlt(0,0, this->m_width + 20, this->m_height + 20, WHITENESS);
			int degrees = (int)this->m_rotate_degrees;

			hImage.RotateImage(degrees,FALSE);	
			pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
			switch(degrees) {
			case 0:
			case 180:
				draw = pDC->StretchBlt (outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
					&memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCAND);
				break;
			case 90:
			case 270:
				draw = pDC->StretchBlt (outline_rect.left + (this->m_width/2 - this->m_height/2) , outline_rect.top - (this->m_width/2 - this->m_height/2), this->m_height, this->m_width, 
					&memDC, 0, 0, bmpInfo.bmHeight, bmpInfo.bmWidth, SRCAND);
				break;
			}
		}
		if (!printing) {
				if(this->m_selected) {// draw the resize and rotate 

					if (resize_image.LoadBitmap(IDB_RESIZE)) {
						pOldBitmap = (CBitmap*)memDC.SelectObject(resize_image);	// always select object into the window mem DC
						resize_image.GetBitmap(&bmpInfo);

						this->GetHandleRect(BOTTOM_RIGHT,&handle_rect);
						draw = pDC->BitBlt(handle_rect.left , handle_rect.top, bmpInfo.bmWidth, bmpInfo.bmHeight ,&memDC, 0, 0, SRCAND);
 
					}
				}
			}
			if (this->m_selected && !printing && last_mode) {
				if (rotate_image.LoadBitmap(IDB_ROTATE)) {
					pOldBitmap = (CBitmap*)memDC.SelectObject(rotate_image);	// always select object into the window mem DC
					rotate_image.GetBitmap(&bmpInfo);

					this->GetHandleRect(TOP_RIGHT,&handle_rect);
					draw = pDC->BitBlt(handle_rect.left , handle_rect.top, bmpInfo.bmWidth, bmpInfo.bmHeight ,&memDC, 0, 0, SRCAND);
 
				}
				else {
					COLORREF old_background = pDC->GetBkColor();
					this->GetHandleRect(TOP_RIGHT,&handle_rect);
					pDC->FillSolidRect(&handle_rect,0);
					pDC->SetBkColor(old_background);
				}
			}


	}
}

void SpecialObj::SetSpecialRect()
{
	CBitmap bmp;
	if (this->m_type_object == -1) return;
	if (bmp.LoadBitmap(this->m_type_object)) 	{
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		this->m_object_rect.left = this->m_xPos - (bmpInfo.bmWidth/2);
		this->m_object_rect.right = this->m_xPos + (bmpInfo.bmWidth/2);
		this->m_object_rect.top = this->m_yPos - (bmpInfo.bmHeight/2);
		this->m_object_rect.bottom = this->m_yPos + (bmpInfo.bmHeight/2);
		this->m_width = this->m_object_rect.right - this->m_object_rect.left;
		this->m_height = this->m_object_rect.bottom - this->m_object_rect.top;
	}
	else {
		this->m_error_string.Format("ERROR: Where's %d?",IDB_JUMP_TOOL);
		TRACE0(this->m_error_string);
	}
}

void SpecialObj::SetSpecialRect(CRect *p_rect)
{
	this->m_object_rect = *p_rect;
	this->m_width = this->m_object_rect.Width();
	this->m_height = this->m_object_rect.Height();
}
void SpecialObj::SetXPos(int x_pos)
{
	this->m_xPos = x_pos;
}

int SpecialObj::GetXPos()
{
	return this->m_xPos;
}

int SpecialObj::GetYPos()
{
	return this->m_yPos;
}
void SpecialObj::SetYPos(int y_pos)
{
	this->m_yPos = y_pos;
}


void SpecialObj::GetSpecialRect(CRect *p_rect)
{
	*p_rect = this->m_object_rect;
}

int SpecialObj::MousePointInSpecialRect(POINT *p_mouse_pt)
{
	BOOL in_rect;
	in_rect = this->m_object_rect.PtInRect(*p_mouse_pt);
	if (in_rect) { 
		this->m_handle_selected = this->PointInHandleRect(p_mouse_pt);
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

void SpecialObj::SetSelectedFlag(BOOL selected)
{
	this->m_selected = selected;
}

BOOL SpecialObj::GetSelectedFlag()
{
	return this->m_selected;
}

void SpecialObj::RotateJump(CPoint *point)
{
	float hypo, opp, adj;
	opp = (float)point->y - this->m_object_rect.top;
	adj = (float)point->x - this->m_object_rect.left;
	hypo = (float)_hypot(opp,adj);
	m_M11 = m_M22 = adj/hypo;
	m_M12 = opp/hypo; 
	m_M21 = -(opp/hypo);
	HCURSOR hCursor;
	hCursor = AfxGetApp()->LoadCursor(IDC_SELECT_ROTATE);
	SetCursor(hCursor);
}

BOOL SpecialObj::RallyRectInRegion(CRgn *select_rgn)
{
	if (select_rgn->RectInRegion(&this->m_object_rect))
		return true;
	else 
		return false;
}

void SpecialObj::OffsetXYPos(POINT *p_offset_amt)
{
	this->m_xPos += p_offset_amt->x;
	this->m_yPos += p_offset_amt->y;
	this->SetSpecialRect();
}

void SpecialObj::GetHandleRect(int which_handle, RECT *handle_rect)
{
	switch (which_handle) {
	case TOP_LEFT:
//		handle_rect->top = this->m_station_rect.top;
//		handle_rect->left = this->m_station_rect.left;
//		handle_rect->right= this->m_station_rect.left + 8;
//		handle_rect->bottom = this->m_station_rect.top + 8;
		break;
	case TOP_RIGHT:
		handle_rect->top = this->m_object_rect.top;
		handle_rect->right = this->m_object_rect.right;
		handle_rect->left= this->m_object_rect.right - 8;
		handle_rect->bottom = this->m_object_rect.top + 8;
		break;
	case BOTTOM_LEFT:
//		handle_rect->top = this->m_station_rect.bottom - 8;
//		handle_rect->left = this->m_station_rect.left;
//		handle_rect->right= this->m_station_rect.left + 8;
//		handle_rect->bottom = this->m_station_rect.bottom;
		break;
	case BOTTOM_RIGHT:
		handle_rect->top = this->m_object_rect.bottom - 8;
		handle_rect->left = this->m_object_rect.right - 8;
		handle_rect->right= this->m_object_rect.right;
		handle_rect->bottom = this->m_object_rect.bottom;
		break;
	}
	return;
}

void SpecialObj::SetRotateMeasurements(float M11, float M12, float M21, float M22)
{
	this->m_M11 = M11;
	this->m_M12 = M12;
	this->m_M21 = M21;
	this->m_M22 = M22;
	if (this->m_M11 == 1.0 && this->m_M12 >=0.0 && this->m_M12 <= 1.0) 
		this->m_rotate_degrees = 0;
	else if (this->m_M11 <= 0.0 && this->m_M11 >= -1.0 && this->m_M12 >0.0 && this->m_M12 <= 1.0) 
		this->m_rotate_degrees = 90;
	else if (this->m_M11 < 0.0 && this->m_M11 >= -1.0 && this->m_M12 <=0.0 && this->m_M12 >= -1.0) 
		this->m_rotate_degrees = 180;
	else if (this->m_M11 == 0.0 && this->m_M12 <0.0 && this->m_M12 >= -1.0) 
		this->m_rotate_degrees = 270;
	else this->SetStationDegreeRotation();
}

void SpecialObj::RotateSpecial(CPoint *point)
{
	float hypo, opp, adj;
	opp = (float)point->y - this->m_object_rect.top;
	adj = (float)point->x - this->m_object_rect.left;
	hypo = (float)_hypot(opp,adj);
	m_M11 = m_M22 = adj/hypo;
	m_M12 = opp/hypo; 
	m_M21 = -(opp/hypo);
	HCURSOR hCursor;
	hCursor = AfxGetApp()->LoadCursor(IDC_SELECT_ROTATE);
	SetCursor(hCursor);

}

int SpecialObj::PointInHandleRect(POINT *loc)
{
	CRect handle_rect;
	int which_handle = NONE_SELECTED;
//	this->GetHandleRect(TOP_LEFT,&handle_rect);
//	if (handle_rect.PtInRect(*loc)) which_handle = TOP_LEFT;
	this->GetHandleRect(TOP_RIGHT,&handle_rect);
	handle_rect.InflateRect(4,4);
	if (handle_rect.PtInRect(*loc)) which_handle = TOP_RIGHT;
//	this->GetHandleRect(BOTTOM_LEFT,&handle_rect);
//	if (handle_rect.PtInRect(*loc)) which_handle = BOTTOM_LEFT;
	this->GetHandleRect(BOTTOM_RIGHT,&handle_rect);
	handle_rect.InflateRect(4,4);
	if (handle_rect.PtInRect(*loc)) which_handle = BOTTOM_RIGHT;

	return which_handle;
}

void SpecialObj::ResizeSpecial(POINT *p_loc)
{
	this->m_object_rect.bottom = p_loc->y;
	this->m_object_rect.right = p_loc->x;
	this->m_width = m_object_rect.right - m_object_rect.left;
	this->m_height = m_object_rect.bottom - m_object_rect.top;
	this->m_xPos = this->m_object_rect.left + this->m_width/2;
	this->m_yPos = this->m_object_rect.top + this->m_height/2;
}

void SpecialObj::OffSetSpecialRect(CPoint *point)
{
	this->m_object_rect.OffsetRect(*point);
	this->m_xPos = this->m_object_rect.right - (this->m_width/2);
	this->m_yPos = this->m_object_rect.bottom - (this->m_height/2);
}


void SpecialObj::SetTypeObject(int type_object)
{
	this->m_type_object = type_object;
}

int SpecialObj::GetTypeObject()
{
	return this->m_type_object;
}

void SpecialObj::SetUndoRedoAction(int undo_action)
{
	this->m_undo_action = undo_action;
}

int SpecialObj::GetUndoRedoAction()
{
	return this->m_undo_action;
}

void SpecialObj::SetUndoRedoPosition(POSITION pos_in_special_list)
{
	this->m_pos_in_special_list = pos_in_special_list;
}

POSITION SpecialObj::GetUndoRedoPosition()
{
	return this->m_pos_in_special_list;
}

void SpecialObj::GetRotateMeasurements(float *p_M11, float *p_M12, float *p_M21, float *p_M22)
{
	*p_M11 = this->m_M11;
	*p_M12 = this->m_M12;
	*p_M21 = this->m_M21;
	*p_M22 = this->m_M22;

}

void SpecialObj::CalculateRotateMeasurements(double degree_rotation)
{
	double pi = 3.1415926535;

	m_M11 = m_M22 = (float)cos((degree_rotation * pi)/180);
	m_M12 = (float)sin((degree_rotation * pi)/180); 
	m_M21 = (float)-sin((degree_rotation * pi)/180);	
	this->m_rotate_degrees = degree_rotation;
}

void SpecialObj::SetStationDegreeRotation()
{
	double arc_sine, arc_cosine;
	double sine_degrees, cos_degrees;
	double pi = 3.1415926535;
	arc_cosine = acos(this->m_M11);
	arc_sine = asin(this->m_M12);
	sine_degrees = (arc_sine * 180.0) / pi;
	cos_degrees = (arc_cosine * 180.0)/ pi;
	if (sine_degrees < 0) this->m_rotate_degrees = 360.0 - cos_degrees;
	else this->m_rotate_degrees = cos_degrees;
}
