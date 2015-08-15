// ArrowObj.cpp: implementation of the ArrowObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "ArrowObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(ArrowObj, CObject, VERSIONABLE_SCHEMA | 2)

ArrowObj::ArrowObj()
{
	// This empty constructor should be used by serialization only
}
ArrowObj::ArrowObj(CPoint *entry_point, CPoint *exit_point, LOGPEN *default_pen, int entry_owner, int exit_owner, int arrow_type, BOOL move_with_station, BOOL create_line)
{

	this->m_arrow_pen = *default_pen;
	this->m_move_with_station = true;
	this->m_entry_point = *entry_point;
	this->m_exit_point = *exit_point;
	this->m_entry_owner = entry_owner;
	this->m_exit_owner = exit_owner;
	this->m_arrow_selected = false;
	this->m_arrow_type = arrow_type;
	this->m_draw_arrow = !create_line;
	this->m_mouse_pt = (0,0);
	this->m_handle_selected = NO_HANDLE;
	this->m_move_with_station = move_with_station;
// intilize points array
	this->IntilizeDrawPoints();

	this->SetGrabHandleRects();
}
ArrowObj::~ArrowObj()
{

}
void ArrowObj::Serialize(CArchive& ar)
{
	int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_exit_point;
		ar << m_entry_point;
		ar << m_arrow_pen.lopnColor;
		ar << m_arrow_pen.lopnStyle;
		ar << m_arrow_pen.lopnWidth;
		ar << m_exit_owner;
		ar << m_entry_owner;
		ar << m_arrow_type;
		ar << m_draw_arrow;
		ar << this->m_move_with_station;
		for (i = 0; i< 16; i++) {
			ar << m_draw_points[i];
		}
	}
	else
	{
		// TODO: add loading code here
		int version = ar.GetObjectSchema();
		switch (version) {
			case 1:
			ar >> m_exit_point;
			ar >> m_entry_point;
			ar >> m_arrow_pen.lopnColor;
			ar >> m_arrow_pen.lopnStyle;
			ar >> m_arrow_pen.lopnWidth;
			ar >> m_exit_owner;
			ar >> m_entry_owner;
			ar >> m_arrow_type;
			ar >> this->m_move_with_station;
			for (i = 0; i< 16; i++) {
				ar >> m_draw_points[i];
			}
			this->SetGrabHandleRects();
			this->m_arrow_selected = false;
			break;
		case 2:
			ar >> m_exit_point;
			ar >> m_entry_point;
			ar >> m_arrow_pen.lopnColor;
			ar >> m_arrow_pen.lopnStyle;
			ar >> m_arrow_pen.lopnWidth;
			ar >> m_exit_owner;
			ar >> m_entry_owner;
			ar >> m_arrow_type;
			ar >> m_draw_arrow;
			ar >> this->m_move_with_station;
			for (i = 0; i< 16; i++) {
				ar >> m_draw_points[i];
			}
			this->SetGrabHandleRects();
			this->m_arrow_selected = false;
			break;
		}
	}
	
}
CPoint ArrowObj::GetExitPoint()
{
	return this->m_exit_point;
}

void ArrowObj::SetExitPoint(CPoint *exit_point)
{
	CPoint off_set_pt;
	off_set_pt = *exit_point - this->m_exit_point;
	this->m_exit_point = *exit_point;
	this->IntilizeDrawPoints();
	this->m_exit_grab.SetRect(this->m_exit_point.x-4,this->m_exit_point.y-4,this->m_exit_point.x+4,this->m_exit_point.y+4);
	this->SetGrabHandleRects();
}

CPoint ArrowObj::GetEntryPoint()
{
	return this->m_entry_point;
}

void ArrowObj::SetEntryPoint(CPoint *entry_point)
{
	CPoint off_set_pt;
	off_set_pt = *entry_point - this->m_entry_point;
	this->m_entry_point = *entry_point;
	this->IntilizeDrawPoints();	
	this->m_entry_grab.SetRect(this->m_entry_point.x-4,this->m_entry_point.y-4,this->m_entry_point.x+4,this->m_entry_point.y+4);
	this->SetGrabHandleRects();	
}

void ArrowObj::SetPenForArrow(int nPenStyle, int nWidth, COLORREF crColor )
{
	this->m_arrow_pen.lopnColor = crColor;
	this->m_arrow_pen.lopnStyle = nPenStyle;
	this->m_arrow_pen.lopnWidth.x = nWidth;


}

LOGPEN  ArrowObj::GetArrowPen()
 {
 	return this->m_arrow_pen;
 }

void ArrowObj::DrawArrow(CDC *pDC, BOOL printing, BOOL dragging)
{
	CPen draw_pen;
	CPen* pOldPen;
	ARROWSTRUCT a;
	CBrush br1, *pbrOld;
	int nNumPoints, index;
	LPPOINT lpPt;
	LPBYTE  lpB;
	CPoint center_point, arrow_point;
	// setup pen 
//	if (dragging) this->m_arrow_pen.lopnStyle = PS_DASH;
//	else this->m_arrow_pen.lopnStyle = PS_SOLID;
//	draw_pen.CreatePenIndirect(&this->m_arrow_pen);
	LOGBRUSH LogBrush;
	LogBrush.lbColor = this->m_arrow_pen.lopnColor;
	LogBrush.lbStyle = BS_SOLID;
	LogBrush.lbHatch = 0;
	int variableWidth = this->m_arrow_pen.lopnWidth.x;

	draw_pen.CreatePen(PS_GEOMETRIC | this->m_arrow_pen.lopnStyle, variableWidth,&LogBrush,0,NULL);
	pOldPen = pDC->SelectObject(&draw_pen);
	CRect rect;
	pDC->GetBoundsRect(&rect, DCB_RESET);
	// setup brush
//	br1.CreateSolidBrush(RGB(0,0,0));
	br1.CreateSolidBrush(this->m_arrow_pen.lopnColor);
	pbrOld = pDC->SelectObject(&br1);

	// setup arrows
	a.nWidth = 20; // need to figure relationship between arrow width and pen width!!!
	a.fTheta = 0.9f;
	a.bFill = true;
	switch (this->m_arrow_type) {
	case LINE:
		pDC->MoveTo(this->m_exit_point);
		if (this->m_draw_arrow) {
			this->ArrowTo(pDC->m_hDC,&this->m_entry_point,&a, false);
		}
		else {
			pDC->LineTo(this->m_entry_point);
		}
		break;
	case CURVE:
		if (this->m_exit_point.x < this->m_entry_point.x) 
			center_point.x = abs(this->m_exit_point.x + ((this->m_entry_point.x - this->m_exit_point.x)/2));
		else 
			center_point.x = abs(this->m_entry_point.x + ((this->m_exit_point.x - this->m_entry_point.x)/2));
		if (this->m_exit_point.y < this->m_entry_point.y) 
			center_point.y = abs(this->m_exit_point.y + ((this->m_entry_point.y - this->m_exit_point.y)/2));
		else 
			center_point.y = abs(this->m_entry_point.y + ((this->m_exit_point.y - this->m_entry_point.y)/2));
		pDC->MoveTo(this->m_exit_point);
		pDC->AngleArc(center_point.x,center_point.y,this->m_exit_point.x,0,180);
		break;
	case POLY:
		pDC->PolyBezier(this->m_draw_points,16);

		if (pDC->BeginPath()) 	{
			pDC->PolyBezier(this->m_draw_points,16);
			if (pDC->EndPath()) {
				if (pDC->FlattenPath())
					nNumPoints = pDC->GetPath((LPPOINT)NULL, (LPBYTE)NULL, 0);
				if (nNumPoints > 0) {
					lpPt = (LPPOINT)malloc((DWORD)(sizeof(POINT) * nNumPoints));
					lpB  = (LPBYTE)malloc((DWORD)(sizeof(BYTE) * nNumPoints));
					nNumPoints = pDC->GetPath(lpPt, lpB, nNumPoints);
					index = this->FindIndexOfDrawPoints(lpPt, nNumPoints-1);
// need to draw from 1/2 of the points to draw_points[12]//
					if (this->m_draw_arrow) {
						if (index == -1) 
							this->DrawArrowPoint(pDC,&lpPt[nNumPoints-2]);
						else 
							this->DrawArrowPoint(pDC,&lpPt[index]);
					}
					arrow_point = lpPt[nNumPoints-10];
					free(lpPt);
					free(lpB);

				}
			}
		}

		if (0) {
			CString out_string;
			int line_number = 90;
			CPoint second_check_pt;
			out_string.Format("12th point x:%d y:%d",this->m_draw_points[12].x, this->m_draw_points[12].y);
			pDC->TextOut(10,10,out_string);
			out_string.Format("move to  x:%d y:%d",arrow_point.x, arrow_point.y);
			pDC->TextOut(10,30,out_string);
//			out_string.Format("exit point x:%d y:%d",this->m_exit_point.x, this->m_exit_point.y);
//			pDC->TextOut(10,50,out_string);
			out_string.Format("entry point x:%d y:%d",this->m_entry_point.x, this->m_entry_point.y);
			pDC->TextOut(10,50,out_string);
			int i;
			for (i = 0; i<16;i++) {
				
				out_string.Format("X:%d   Y:%d",this->m_draw_points[i].x, this->m_draw_points[i].y);
				pDC->TextOut(10,line_number,out_string);
//				out_string.Format("x");
//				pDC->TextOut(this->m_draw_points[i].x,this->m_draw_points[i].y,out_string);
				line_number += 20;
			}
//			free(lpPt);
//			free(lpB);

/*
			POSITION pos_to_change;
			for (pos_to_change = this->m_arrow_points.GetHeadPosition(); pos_to_change != NULL;) {
				second_check_pt = this->m_arrow_points.GetNext(pos_to_change);
				out_string.Format("X:%d   Y:%d",second_check_pt.x, second_check_pt.y);
				pDC->TextOut(10,line_number,out_string);
				line_number += 20;
			}
*/
		}
		break;
	}
	if(!printing) {
		this->DrawGrabRects(pDC);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pbrOld);
}

void ArrowObj::ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA, BOOL just_point)
{

	POINT pFrom;
	POINT pBase;
	POINT aptPoly[3];
	float vecLine[2];
	float vecLeft[2];
	float fLength;
	float th;
	float ta;

	// get from point
	MoveToEx(hDC, 0, 0, &pFrom);

	// set to point
	aptPoly[0].x = lpTo->x;
	aptPoly[0].y = lpTo->y;

	// build the line vector
	vecLine[0] = (float) aptPoly[0].x - pFrom.x;
	vecLine[1] = (float) aptPoly[0].y - pFrom.y;

	// build the arrow base vector - normal to the line
	vecLeft[0] = -vecLine[1];
	vecLeft[1] = vecLine[0];

	// setup length parameters
	fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
	th = pA->nWidth / (2.0f * fLength);
	ta = pA->nWidth / (2.0f * (tanf(pA->fTheta) / 2.0f) * fLength);

	// find the base of the arrow
	pBase.x = (int) (aptPoly[0].x + -ta * vecLine[0]);
	pBase.y = (int) (aptPoly[0].y + -ta * vecLine[1]);

	// build the points on the sides of the arrow
	aptPoly[1].x = (int) (pBase.x + th * vecLeft[0]);
	aptPoly[1].y = (int) (pBase.y + th * vecLeft[1]);
	aptPoly[2].x = (int) (pBase.x + -th * vecLeft[0]);
	aptPoly[2].y = (int) (pBase.y + -th * vecLeft[1]);

	MoveToEx(hDC, pFrom.x, pFrom.y, NULL);

	// fill in the arrow
	if(pA->bFill) {
		if (!just_point) LineTo(hDC, aptPoly[0].x, aptPoly[0].y); // this keeps from drawing an extra line
		Polygon(hDC, aptPoly, 3);
	}


	else {
		LineTo(hDC, pBase.x, pBase.y);
		LineTo(hDC, aptPoly[1].x, aptPoly[1].y);
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		LineTo(hDC, aptPoly[2].x, aptPoly[2].y);
		LineTo(hDC, pBase.x, pBase.y);
		MoveToEx(hDC, aptPoly[0].x, aptPoly[0].y, NULL);
	}


}

void ArrowObj::SetExitOwner(int exit_owner)
{
	if (this->m_exit_owner == NO_OWNER) return;
	this->m_exit_owner = exit_owner;
}

int ArrowObj::GetExitOwner()
{
	return this->m_exit_owner;
}

void ArrowObj::SetEntryOwner(int entry_owner)
{
	if (this->m_entry_owner == NO_OWNER) return;
	this->m_entry_owner = entry_owner;
}

int ArrowObj::GetEntryOwner()
{
	return this->m_entry_owner;
}

bool ArrowObj:: HitTestLineforBezier(POINT pt0, POINT pt1, POINT ptMouse, int nWidth, HDC hdc)
{
	POINT PtM;
	VECTOR2D tt0, tt1;
	double dist;
	int nHalfWidth;

	nHalfWidth = (nWidth/2 < 1) ? 1 : nWidth/2;
	if (nHalfWidth < 2) 
		nHalfWidth = 2;
	//
	//convert the line into a vector
	//
	POINTS2VECTOR2D(pt0, pt1, tt0);
	//
	//convert the mouse points (short) into POINT (long)
	//
	MPOINT2POINT(ptMouse ,PtM);
	POINTS2VECTOR2D(pt0, PtM, tt1);
	//
	//if the mouse click is past the endpoints of 
	//a line segment return FALSE
	//
	if (pt0.x <= pt1.x) {
		if (PtM.x < pt0.x || PtM.x > pt1.x)
			return (FALSE);
	}
	else {
		if (PtM.x > pt0.x || PtM.x < pt1.x)
			return (FALSE);
	}
	//
	//currently, the only transform used is the identity
	//
	XFORM      xf;
	xf.eM11 = 1.0f;
	xf.eM12 = 0.0f;
	xf.eM21 = 0.0f;
	xf.eM22 = 1.0f;
	xf.eDx  = 0.0f;
	xf.eDy  = 0.0f;
	int last_mode = SetGraphicsMode(hdc, GM_ADVANCED);
	if (last_mode) {
		if (SetWorldTransform(hdc, &xf)) {
		//
		//this is the call to the function that does the work
		//of obtaining the distance of the point to the line
		//
			dist = vDistFromPointToLine(&pt0, &pt1, &PtM);
			SetGraphicsMode(hdc, GM_COMPATIBLE);
		}
		//
		//TRUE if the distance is within the width of the pen about the
		//line otherwise FALSE
		//
		return (dist >= -nHalfWidth && dist <= nHalfWidth);
	}
	else {
		if (this->HitTestLine(pt0, pt1,ptMouse,nWidth)) {
			this->SetSelection(true);
		}
		else {
			this->SetSelection(false);
		}

	}
	return this->m_arrow_selected;
}

bool ArrowObj::HitTestLine(POINT hit_point, HDC hdc) {

	POINT PtM, pt0, pt1;
	VECTOR2D tt0, tt1;
	bool arrow_selected;
	double dist;
	int nHalfWidth, nWidth;
	nWidth = this->m_arrow_pen.lopnWidth.x * 2;
	pt0 = this->m_entry_point;
	pt1 = this->m_exit_point;
	nHalfWidth = (nWidth/2 < 1) ? 1 : nWidth/2;
	if (nHalfWidth < 5) 
		nHalfWidth = 5;
	//
	//convert the line into a vector
	//
	POINTS2VECTOR2D(pt0, pt1, tt0);
	//
	//convert the mouse points (short) into POINT (long)
	//

	PtM = hit_point;
	POINTS2VECTOR2D(pt0, PtM, tt1);
	//
	//if the mouse click is past the endpoints of 
	//a line segment return FALSE
	//
/*	if (pt0.x <= pt1.x) {
		if (PtM.x < pt0.x || PtM.x > pt1.x) {
			this->m_arrow_selected = false;
			return (this->m_arrow_selected);
		}
	}
	else {
		if (PtM.x > pt0.x || PtM.x < pt1.x) {
			this->m_arrow_selected = false;
			return (this->m_arrow_selected);
		}
	}
	*/
	//
	//currently, the only transform used is the identity
	//
	XFORM      xf;
	xf.eM11 = 1.0f;
	xf.eM12 = 0.0f;
	xf.eM21 = 0.0f;
	xf.eM22 = 1.0f;
	xf.eDx  = 0.0f;
	xf.eDy  = 0.0f;
	int last_mode = SetGraphicsMode(hdc, GM_ADVANCED);
	if (last_mode) {

		if (SetWorldTransform(hdc, &xf))
		{
		//
		//this is the call to the function that does the work
		//of obtaining the distance of the point to the line
		//
			dist = vDistFromPointToLine(&pt0, &pt1, &PtM);
			SetGraphicsMode(hdc, GM_COMPATIBLE);
		}

		//
		//TRUE if the distance is within the width of the pen about the
		//line otherwise FALSE
		//

		arrow_selected = (dist >= -nHalfWidth && dist <= nHalfWidth);
//		this->SetSelection(arrow_selected);
	}
	else {

		if (this->HitTestLine(this->m_entry_point, this->m_exit_point, hit_point, nWidth)) 
			arrow_selected = true;
//			this->SetSelection(true);
		else 
			arrow_selected = false;
//			this->SetSelection(false);
	}
	return arrow_selected;
	return (this->m_arrow_selected);

}
BOOL ArrowObj::HitTestLine(POINT pt0, POINT pt1, POINT ptMouse, int nWidth)
{
  POINT PtM;
  VECTOR2D tt0, tt1;
  double dist;
  int nHalfWidth;
  //
  //Get the half width of the line to adjust for hit testing of wide lines.
  //
  nHalfWidth = (nWidth/2 < 1) ? 1 : nWidth/2;
  	if (nHalfWidth < 2) 
		nHalfWidth = 2;
  //
  //Convert the line into a vector using the two endpoints.
  //
  POINTS2VECTOR2D(pt0, pt1, tt0);
  //
  //Convert the mouse points (short) into a POINT structure (long).
  //
//  MPOINT2POINT(ptMouse ,PtM);
  //
  //Convert the line from the left endpoint to the mouse point into a vector.
  //
	PtM = ptMouse;
  POINTS2VECTOR2D(pt0, PtM, tt1);
  //
  //Obtain the distance of the point from the line.
  //
  dist = vDistFromPointToLine(&pt0, &pt1, &PtM);
  //
  //Return TRUE if the distance of the point from the line is within the width 
  //of the line
  //
  return (dist >= -nHalfWidth && dist <= nHalfWidth);
}

int ArrowObj::HitTestCurve(POINT hit_point, HDC hdc)
{

	int nNumPoints, nPt;
	LPPOINT lpPt;
	LPBYTE  lpB;
	int hit = NO_HIT;

	if (this->PointInGrabHandle(&hit_point)) {
		hit = this->m_handle_selected;
		if (((hit == ENTRY_HANDLE || hit == EXIT_HANDLE) && this->m_arrow_type == LINE) || (this->m_arrow_type == POLY )) { 
			return hit;
		}
		else {
			this->m_handle_selected = NO_HANDLE;
			return LINE_HIT;
		}

	}
	if (!this->MousePointInGeneralRect(&hit_point)) {
		return hit;
	}
	if(this->m_arrow_type == LINE) {
		if (this->HitTestLine(hit_point,hdc)) {
			hit = LINE_HIT;
		}
	}
	else {
		if (BeginPath(hdc)) 	{
			PolyBezier(hdc,this->m_draw_points,16);
			if (EndPath(hdc)) {
				if (FlattenPath(hdc))
					nNumPoints = GetPath(hdc, (LPPOINT)NULL, (LPBYTE)NULL, 0);
				if (nNumPoints > 0) {
					lpPt = (LPPOINT)malloc((DWORD)(sizeof(POINT) * nNumPoints));
					lpB  = (LPBYTE)malloc((DWORD)(sizeof(BYTE) * nNumPoints));
					nNumPoints = GetPath(hdc, lpPt, lpB, nNumPoints);

					for (nPt = 0; nPt < nNumPoints - 1; nPt++) {
						if (HitTestLineforBezier(lpPt[nPt], lpPt[nPt + 1], hit_point, this->m_arrow_pen.lopnWidth.x + 5, hdc)) {
							this->m_hit_point = hit_point;
							hit = LINE_HIT;
						}
					}
					free(lpPt);
					free(lpB);

				}
			}
		}

	}
	return hit;

}

double ArrowObj::vDistFromPointToLine(LPPOINT pt0, LPPOINT pt1, LPPOINT ptTest)
{
  VECTOR2D ttLine, ttTest;
  PROJECTION pProjection;

  POINTS2VECTOR2D(*pt0, *pt1, ttLine);
  POINTS2VECTOR2D(*pt0, *ptTest, ttTest);

  vProjectAndResolve(&ttTest, &ttLine, &pProjection);
 
  return(pProjection.LenPerpProjection);
}

void ArrowObj::vProjectAndResolve(PVECTOR2D v0, PVECTOR2D v1, PPROJECTION ppProj)
{
  VECTOR2D ttProjection, ttOrthogonal;
  double proj1;
  //
  //obtain projection vector
  //
  //c = a * b
  //    ----- b
  //    |b|^2
  //
  proj1 = vDotProduct(v0, v1)/vDotProduct(v1, v1);
  ttProjection.x = v1->x * proj1;
  ttProjection.y = v1->y * proj1;
  //
  //obtain perpendicular projection : e = a - c
  //
  vSubtractVectors(v0, &ttProjection, &ttOrthogonal);
  //
  //fill PROJECTION structure with appropriate values
  //
  ppProj->LenProjection = vVectorMagnitude(&ttProjection);
  ppProj->LenPerpProjection = vVectorMagnitude(&ttOrthogonal);

  ppProj->ttProjection.x = ttProjection.x;
  ppProj->ttProjection.y = ttProjection.y;
  ppProj->ttPerpProjection.x = ttOrthogonal.x;
  ppProj->ttPerpProjection.y = ttOrthogonal.y;
}

double ArrowObj::vDotProduct(PVECTOR2D v0, PVECTOR2D v1)
{
  return ((v0 == NULL || v1 == NULL) ? 0.0 
                                     : (v0->x * v1->x) + (v0->y * v1->y));
}

double ArrowObj::vVectorMagnitude(PVECTOR2D v0)
{
  double dMagnitude;

  if (v0 == NULL)
    dMagnitude = 0.0;
  else
    dMagnitude = sqrt(vVectorSquared(v0));
  return (dMagnitude);
}

double ArrowObj::vVectorSquared(PVECTOR2D v0)
{
  double dSqLen;

  if (v0 == NULL)
    dSqLen = 0.0;
  else
    dSqLen = (double)(v0->x * v0->x) + (double)(v0->y * v0->y);
  return (dSqLen);
}

PVECTOR2D ArrowObj::vSubtractVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v)
{
  if (v0 == NULL || v1 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    v->x = v0->x - v1->x;
    v->y = v0->y - v1->y;
  }
  return(v);
}

void ArrowObj::CheckForLineInRect(CRgn *rect_to_check)
{
	CRect line_rect;
	int i;
	line_rect.SetRect(this->m_entry_point, this->m_exit_point);
	line_rect.NormalizeRect();
	if (rect_to_check->RectInRegion(&line_rect)) {
		for (i = 0;i<16;i++) {
			if (rect_to_check->PtInRegion(this->m_draw_points[i])){
				this->SetSelection(true);
				return;
			}
		}		
		
		this->SetSelection(false);
	}
	else 
		this->SetSelection(false);

}

void ArrowObj::SetGrabHandleRects()
{
	this->m_entry_grab.SetRect(this->m_entry_point.x-4,this->m_entry_point.y-4,this->m_entry_point.x+4,this->m_entry_point.y+4);
	this->m_exit_grab.SetRect(this->m_exit_point.x-4,this->m_exit_point.y-4,this->m_exit_point.x+4,this->m_exit_point.y+4);
	this->m_first_grab.SetRect(this->m_draw_points[FIRST_HANDLE].x-4,this->m_draw_points[FIRST_HANDLE].y-4,this->m_draw_points[FIRST_HANDLE].x+4,this->m_draw_points[FIRST_HANDLE].y+4);	
	this->m_second_grab.SetRect(this->m_draw_points[SECOND_HANDLE].x-4,this->m_draw_points[SECOND_HANDLE].y-4,this->m_draw_points[SECOND_HANDLE].x+4,this->m_draw_points[SECOND_HANDLE].y+4);	
	this->m_third_grab.SetRect(this->m_draw_points[THIRD_HANDLE].x-4,this->m_draw_points[THIRD_HANDLE].y-4,this->m_draw_points[THIRD_HANDLE].x+4,this->m_draw_points[THIRD_HANDLE].y+4);	
	this->m_fourth_grab.SetRect(this->m_draw_points[FOURTH_HANDLE].x-4,this->m_draw_points[FOURTH_HANDLE].y-4,this->m_draw_points[FOURTH_HANDLE].x+4,this->m_draw_points[FOURTH_HANDLE].y+4);	

}

void ArrowObj::SetSelection(bool selected)
{
	this->m_arrow_selected = selected;
}

bool ArrowObj::GetArrowSelection()
{
	return this->m_arrow_selected;
}

void ArrowObj::SetArrowType(int arrow_type)
{
	this->m_arrow_type = arrow_type;
}

int ArrowObj::GetArrowType()
{
	return this->m_arrow_type;
}

VECTOR2D ArrowObj::NearestPointOnCurve(PVECTOR2D pvTest, PVECTOR2D pvCtrlPts)
{
	PVECTOR2D w;                    //Ctl pts for 5th-degree eqn  
	double	t_candidate[W_DEGREE];	//Possible roots  
	int	n_solutions;	            //Number of roots found  
	double	t;		                //Parameter value of closest pt  
	//
	//Convert problem to 5th-degree Bezier form  
	//
	w = ConvertToBezierForm(pvTest, pvCtrlPts);
	//
	//Find all possible roots of 5th-degree equation  
	//
	n_solutions = RecursiveSubDivide(w, W_DEGREE, t_candidate, 0);
	//free((char *)w);
	free(w);
	//
	//Compare distances of pvTest to all candidates, and to t=0, and t=1  
	//
	{
		double	 dist, new_dist;
		VECTOR2D p;
		VECTOR2D v;
		int	i;
		//
	    //  Check distance to beginning of curve, where t=0  
		//
		dist = vVectorSquared(vSubtractVectors(pvTest, (PVECTOR2D)&pvCtrlPts[0], &v));
		t = 0.0;
		//
	    //Find distances for candidate points  
		//
		for (i = 0; i < n_solutions; i++) 
		{
			p = Bezier(pvCtrlPts, DEGREE, t_candidate[i], NULL, NULL);
		    new_dist = vVectorSquared(vSubtractVectors(pvTest, (PVECTOR2D)&p, &v));
			if (new_dist < dist) {
				dist = new_dist;
				t = t_candidate[i];
			}
		}
		// 
	    //Finally, look at distance to end point, where t = 1.0 
		//
	    new_dist = vVectorSquared(vSubtractVectors(pvTest, (PVECTOR2D)&pvCtrlPts[DEGREE], &v));
		if (new_dist < dist) 
		{
			dist = new_dist;
			t = 1.0;
		}
	}
	//
	//Return the point on the curve at parameter value t 
	//
	return (Bezier(pvCtrlPts, DEGREE, t, NULL, NULL));
}


/***********************************************************************

  FUNCTION   : ConvertToBezierForm

  PARAMETERS : PVECTOR2D P  -  The point to find t for 
               PVECTOR2D pvCtrlPts 	-  The control points	

  PURPOSE    : Given a point and a Bezier curve, generate a 5th-degree
               Bezier format equation whose solution finds the point on the
               curve nearest the user defined point.

  CALLS      : vSubtractVectors
			   malloc

  MESSAGES   : 

  RETURNS    : PVECTOR2D

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

PVECTOR2D ArrowObj::ConvertToBezierForm(PVECTOR2D P, PVECTOR2D pvCtrlPts)
{
	int		   i, j, k, m, n, ub, lb;
	int		   row, column;	         //Table indices	
	VECTOR2D   c[DEGREE+1];	         //pvCtrlPts(i)'s - P	
	VECTOR2D   d[DEGREE];		     //pvCtrlPts(i+1) - pvCtrlPts(i)	
	PVECTOR2D  w;			         //Ctl pts of 5th degree curve 
	double	cdTable[3][4];	         //Dot product of c, d		 
	static     double z[3][4] =      //Precomputed "z" for cubics  
	{
	{1.0, 0.6, 0.3, 0.1},
	{0.4, 0.6, 0.6, 0.4},
	{0.1, 0.3, 0.6, 1.0},
	};
	//
	//Determine the c's    these are vectors created by subtracting
	//point P from each of the control points                    
	//
	for (i = 0; i <= DEGREE; i++) 
	  vSubtractVectors((PVECTOR2D)&pvCtrlPts[i], P, (PVECTOR2D)&c[i]);
	//
	//Determine the d's -- these are vectors created by subtracting
	//each control point from the next                           
	//
	for	(i = 0; i <= DEGREE - 1; i++)
      vScaleVector(vSubtractVectors(&pvCtrlPts[i+1], &pvCtrlPts[i], &d[i]), 3.0, &d[i]);
	//
	//Create the c,d table    this is a table of dot products of the 
	//c's and d's                                    
	//
	for (row = 0; row <= DEGREE - 1; row++) 
	{
	  for (column = 0; column <= DEGREE; column++) 
	  {
	    cdTable[row][column] = vDotProduct(&d[row], &c[column]) ;
	  }
	}
	//
	//Now, apply the z's to the dot products, on the skew diagonal
	//Also, set up the x values, making these "points"            
	//
	w = (PVECTOR2D)malloc((unsigned)(W_DEGREE+1) * sizeof(VECTOR2D));
	for (i = 0; i <= W_DEGREE; i++) 
	{
	  w[i].y = 0.0;
	  w[i].x = (double)(i) / W_DEGREE;
	}
		
	n = DEGREE;
	m = DEGREE-1;

	for (k = 0; k <= n + m; k++) 
	{
	  lb = max(0, k - m);
	  ub = min(k, n);
	  for (i = lb; i <= ub; i++) 
	  {
	  	j = k - i;
		w[i+j].y += cdTable[j][i] * z[j][i];
	  }
	}

	return (w);
}
/***********************************************************************

vScaleVector 

The vScaleVector function scales the components of a vector by a user 
supplied scaling factor.

Parameters

v0	A pointer to a VECTOR2D structure containing the components of 
    the two dimensional vector to be scaled.
dScaling	The value by which to scale the components of v0
v	A pointer to a VECTOR2D structure in which the results of 
    multiplying (scaling) the components of v0 by dScaling are stored.

Return value

A pointer to a VECTOR2D structure containing the scaled vector.

HISTORY    : - created - denniscr

************************************************************************/

PVECTOR2D ArrowObj::vScaleVector(PVECTOR2D v0, double dScaling, PVECTOR2D v)
{
  if (v0 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    if (dScaling != 0)
    {
      v->x = (v0->x *= dScaling);
      v->y = (v0->y *= dScaling);
	}
  }
  return(v);
}

/***********************************************************************

  FUNCTION   : RecursiveSubDivide

  PARAMETERS : PVECTOR2D w	     - The control points 
               int       degree	 - The degree of the polynomial
               double    *t		 - RETURN candidate t values
               int       depth	 - The depth of the recursion

  PURPOSE    : Given a 5th degree equation in Bernstein Bezier form, find
               all of the roots in the interval [0, 1]. 

  CALLS      : ControlPolygonFlatEnough
			   ComputeXIntercept
			   Bezier
			   RecursiveSubDivide

  MESSAGES   : none

  RETURNS    : Return the number of roots found.

  COMMENTS   : previously called FindRoots in Graphics Gems

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

int ArrowObj::RecursiveSubDivide(PVECTOR2D w, int degree, double *t, int depth)
{
	int		 i;
	VECTOR2D Left [W_DEGREE+1],      //New left and right	
			 Right[W_DEGREE+1];      //control polygons	
	int		 left_count,		     //Solution count from
			 right_count;	         //children		
	double	 left_t[W_DEGREE+1],     //Solutions from kids	
             right_t[W_DEGREE+1];

	switch (CrossingCount(w, degree))  
	{
	  case 0 :	//No solutions here	
	    return 0;
	    break;

	  case 1 : //Unique solution 
	   	//
	  	//Stop recursion when the tree is deep enough	
		//if deep enough, return 1 solution at midpoint	
		//
 		if (depth >= MAXDEPTH) 
 		{
	             t[0] = (w[0].x + w[W_DEGREE].x) / 2.0;
	             return 1;
		}
		if (ControlPolygonFlatEnough(w, degree)) 
		{
			t[0] = ComputeXIntercept(w, degree);
			return 1;
		}
		break;
    }
	//
	//Otherwise, solve recursively after 
	//subdividing control polygon        
	//
	Bezier(w, degree, 0.5, Left, Right);
	left_count  = RecursiveSubDivide(Left, degree, left_t, depth+1);
	right_count = RecursiveSubDivide(Right, degree, right_t, depth+1);
	//
	//Gather solutions together 
	//
	for (i = 0; i < left_count; i++) 
	  t[i] = left_t[i];

	for (i = 0; i < right_count; i++) 
	  t[i+left_count] = right_t[i];
	//
	//Send back total number of solutions	
	//
    return (left_count + right_count);
}

/***********************************************************************

  FUNCTION   : CrossingCount

  PARAMETERS : PVECTOR2D pvCtrlPts - Control pts of Bezier curve
               int       degree    - Degree of Bezier curve

  PURPOSE    : Count the number of times a Bezier control polygon
               crosses the 0-axis. This number is >= the number of roots.

  CALLS      : SGN macro

  MESSAGES   : none

  RETURNS    : int - number of crossings

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

int ArrowObj::CrossingCount(PVECTOR2D pvCtrlPts, int degree)
{
	int	i;
	int	n_crossings = 0; //Number of zero-crossings	
	int	sign, old_sign;  //Sign of coefficients	
										   
	sign = old_sign = SGN(pvCtrlPts[0].y);
	for 	(i = 1; i <= degree; i++) 
	{
	  sign = SGN(pvCtrlPts[i].y);
	  if (sign != old_sign) n_crossings++;
	  old_sign = sign;
	}
	return (n_crossings);
}

/***********************************************************************

  FUNCTION   : ControlPolygonFlatEnough

  PARAMETERS : PVECTOR2D pvCtrlPts - Control points
               int       degree    - Degree of polynomial

  PURPOSE    : Check if the control polygon of a Bezier curve is flat 
               enough for recursive subdivision to bottom out.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : int - 0 : not flat enough
                     1 : flat enough

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

int ArrowObj::ControlPolygonFlatEnough(PVECTOR2D pvCtrlPts, int degree)
{
	int		 i;		             //Index variable	
	double	 *distance;	         //Distances from pts to line	
	double	 max_distance_above; //maximum of these	
	double	 max_distance_below;
	double	 error;	             //Precision of root 
	double	 intercept_1,
			 intercept_2,
			 left_intercept,
			 right_intercept;
	double 	 a, b, c;	         //Coefficients of implicit	   
				                 //eqn for line from pvCtrlPts[0]-pvCtrlPts[deg] 
	//
	//Find the perpendicular distance         
	//from each interior control point to     
	//line connecting pvCtrlPts[0] and pvCtrlPts[degree]      
	//
	distance = (double *)malloc((unsigned)(degree + 1) * sizeof(double));
	{
	  double abSquared;
	  //
	  //Derive the implicit equation for line connecting first 
	  //and last control points 
	  //
	  a = pvCtrlPts[0].y - pvCtrlPts[degree].y;
	  b = pvCtrlPts[degree].x - pvCtrlPts[0].x;
	  c = pvCtrlPts[0].x * pvCtrlPts[degree].y - pvCtrlPts[degree].x * pvCtrlPts[0].y;

	  abSquared = (a * a) + (b * b);

	  for (i = 1; i < degree; i++)  
	  {
	    //
	    //Compute distance from each of the points to that line 
	    //
  	    distance[i] = a * pvCtrlPts[i].x + b * pvCtrlPts[i].y + c;
	    if (distance[i] > 0.0) 
		  distance[i] = (distance[i] * distance[i]) / abSquared;

	    if (distance[i] < 0.0) 
	      distance[i] = -((distance[i] * distance[i]) / abSquared);
	  }
	}
	//
	//Find the largest distance 
	//
	max_distance_above = 0.0;
	max_distance_below = 0.0;
	for (i = 1; i < degree; i++) 
	{
	  if (distance[i] < 0.0) 
	    max_distance_below = min(max_distance_below, distance[i]);
	  if (distance[i] > 0.0) 
	    max_distance_above = max(max_distance_above, distance[i]);
	}

	free ((char *) distance);

	{
	  double	det, dInv;
	  double	a1, b1, c1, a2, b2, c2;
	  //
	  //Implicit equation for zero line 
	  //
	  a1 = 0.0;
	  b1 = 1.0;
	  c1 = 0.0;
	  //
	  //Implicit equation for "above" line 
	  //
	  a2 = a;
	  b2 = b;
	  c2 = c + max_distance_above;

	  det = a1 * b2 - a2 * b1;
	  dInv = 1.0/det;

	  intercept_1 = (b1 * c2 - b2 * c1) * dInv;
	  //
	  //Implicit equation for "below" line 
	  //
	  a2 = a;
	  b2 = b;
	  c2 = c + max_distance_below;

	  det  = a1 * b2 - a2 * b1;
	  dInv = 1.0/det;

	  intercept_2 = (b1 * c2 - b2 * c1) * dInv;
	}
	//
	//Compute intercepts of bounding box 
	//
	left_intercept  = min(intercept_1, intercept_2);
	right_intercept = max(intercept_1, intercept_2);

	error = 0.5 * (right_intercept-left_intercept);
	if (error < EPSILON)  
	  return 1;
	else 
	  return 0;
}

/***********************************************************************

  FUNCTION   : ComputeXIntercept

  PARAMETERS : PVECTOR2D pvCtrlPts - Control points 
               int       degree	   - Degree of curve

  PURPOSE    : Compute intersection of chord from first control point to 
               last with 0-axis. 

  CALLS      : 

  MESSAGES   : none

  RETURNS    : double - X intercept

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/
double ArrowObj::ComputeXIntercept (PVECTOR2D pvCtrlPts, int degree)
{
	double XLK, YLK, XNM, YNM, XMK, YMK;
	double det, detInv;
	double S, T;
	double X, Y;

	XLK = 1.0 - 0.0;
	YLK = 0.0 - 0.0;
	XNM = pvCtrlPts[degree].x - pvCtrlPts[0].x;
	YNM = pvCtrlPts[degree].y - pvCtrlPts[0].y;
	XMK = pvCtrlPts[0].x - 0.0;
	YMK = pvCtrlPts[0].y - 0.0;

	det = XNM*YLK - YNM*XLK;
	detInv = 1.0/det;

	S = (XNM*YMK - YNM*XMK) * detInv;
	T = (XLK*YMK - YLK*XMK) * detInv;

	X = 0.0 + XLK * S;
	Y = 0.0 + YLK * S;

	return X;
}


/***********************************************************************

  FUNCTION   : Bezier

  PARAMETERS : PVECTOR2D pvCtrlPts	- Control pts
               int degree	        - Degree of bezier curve
               double t             - Parameter value
               PVECTOR2D Left       - RETURN left half ctl pts
               PVECTOR2D Right		- RETURN right half ctl pts

  PURPOSE    : Evaluate a Bezier curve at a particular parameter value
               Fill in control points for resulting sub-curves if "Left" and
               "Right" are non-null.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : 

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/
VECTOR2D ArrowObj::Bezier (PVECTOR2D pvCtrlPts, int degree, double t, 
                        PVECTOR2D Left, PVECTOR2D Right)
{
	int	      i, j;                           
	VECTOR2D  Vtemp[W_DEGREE+1][W_DEGREE+1];
	//
	//Copy control points 
	//
	for (j =0; j <= degree; j++) 
	  Vtemp[0][j] = pvCtrlPts[j];
	//
	//Triangle computation 
	//
	for (i = 1; i <= degree; i++) 
	{
	  for (j =0 ; j <= degree - i; j++) {
		Vtemp[i][j].x =
			(1.0 - t) * Vtemp[i-1][j].x + t * Vtemp[i-1][j+1].x;
		Vtemp[i][j].y =
			(1.0 - t) * Vtemp[i-1][j].y + t * Vtemp[i-1][j+1].y;
	  }
	}

	if (Left != NULL) 
	{
	  for (j = 0; j <= degree; j++) 
	    Left[j] = Vtemp[j][0];
	}

	if (Right != NULL) 
	{
	  for (j = 0; j <= degree; j++) 
 		Right[j] = Vtemp[degree-j][j];
	}

	return (Vtemp[degree][0]);
}


void ArrowObj::CurveLine(CDC *pDC, CPoint *p_mouse_pt, BOOL size_to_screen)
{


	CPoint first_check_pt, second_check_pt, first_point, second_point, pt_in_list;
	CPoint calc_ft_pt, calc_sc_pt, new_ft_pt, new_sc_pt;
	int diff_x, diff_y;
//	int i;
	this->m_mouse_pt = *p_mouse_pt;

	if (this->m_arrow_selected && (this->m_handle_selected != NO_HANDLE) &&  (this->m_hit_point != *p_mouse_pt)) {
		switch(this->m_handle_selected) {
		case ENTRY_HANDLE:
			if (this->m_arrow_type == POLY) {
				diff_x = p_mouse_pt->x - this->m_draw_points[ENTRY_HANDLE].x;
				diff_y = p_mouse_pt->y - this->m_draw_points[ENTRY_HANDLE].y;
				first_point = this->m_draw_points[ENTRY_HANDLE-1];
				first_point.Offset(diff_x,diff_y);
				second_point = this->m_draw_points[ENTRY_HANDLE+1];
				second_point.Offset(diff_x,diff_y);	
				this->m_draw_points[ENTRY_HANDLE-1] = first_point;
				this->m_draw_points[ENTRY_HANDLE] = *p_mouse_pt;
				this->m_entry_point = *p_mouse_pt;
			}
			if (this->m_arrow_type == LINE) {
				this->m_entry_point = *p_mouse_pt;
//				for (i = 0;i<16;i++) {
//					pDC->DPtoLP(&this->m_draw_points[i]);
//				}
				this->IntilizeDrawPoints();
				this->SetGrabHandleRects();
			}
			break;
		case FIRST_HANDLE:
			diff_x = p_mouse_pt->x - this->m_draw_points[FIRST_HANDLE].x;
			diff_y = p_mouse_pt->y - this->m_draw_points[FIRST_HANDLE].y;
			first_point = this->m_draw_points[FIRST_HANDLE-1];
			first_point.Offset(diff_x,diff_y);
			second_point = this->m_draw_points[FIRST_HANDLE+1];
			second_point.Offset(diff_x,diff_y);	
			this->m_draw_points[FIRST_HANDLE-1] = first_point;
			this->m_draw_points[FIRST_HANDLE] = *p_mouse_pt;
			this->m_draw_points[FIRST_HANDLE+1] = second_point;
			break;
		case SECOND_HANDLE:
			diff_x = p_mouse_pt->x - this->m_draw_points[SECOND_HANDLE].x;
			diff_y = p_mouse_pt->y - this->m_draw_points[SECOND_HANDLE].y;
			first_point = this->m_draw_points[SECOND_HANDLE-1];
			first_point.Offset(diff_x,diff_y);
			second_point = this->m_draw_points[SECOND_HANDLE+1];
			second_point.Offset(diff_x,diff_y);	
			this->m_draw_points[SECOND_HANDLE-1] = first_point;
			this->m_draw_points[SECOND_HANDLE] = *p_mouse_pt;
			this->m_draw_points[SECOND_HANDLE+1] = second_point;
			break;
		case THIRD_HANDLE:
			diff_x = p_mouse_pt->x - this->m_draw_points[THIRD_HANDLE].x;
			diff_y = p_mouse_pt->y - this->m_draw_points[THIRD_HANDLE].y;
			first_point = this->m_draw_points[THIRD_HANDLE-1];
			first_point.Offset(diff_x,diff_y);
			second_point = this->m_draw_points[THIRD_HANDLE+1];
			second_point.Offset(diff_x,diff_y);	
			this->m_draw_points[THIRD_HANDLE-1] = first_point;
			this->m_draw_points[THIRD_HANDLE] = *p_mouse_pt;
			this->m_draw_points[THIRD_HANDLE+1] = second_point;
			break;
		case FOURTH_HANDLE:
			diff_x = p_mouse_pt->x - this->m_draw_points[FOURTH_HANDLE].x;
			diff_y = p_mouse_pt->y - this->m_draw_points[FOURTH_HANDLE].y;
			first_point = this->m_draw_points[FOURTH_HANDLE-1];
			first_point.Offset(diff_x,diff_y);
			second_point = this->m_draw_points[FOURTH_HANDLE+1];
			second_point.Offset(diff_x,diff_y);	
			this->m_draw_points[FOURTH_HANDLE-1] = first_point;
			this->m_draw_points[FOURTH_HANDLE] = *p_mouse_pt;
			this->m_draw_points[FOURTH_HANDLE+1] = second_point;
			break;
		case EXIT_HANDLE:
			if (this->m_arrow_type == POLY) {
				diff_x = p_mouse_pt->x - this->m_draw_points[EXIT_HANDLE].x;
				diff_y = p_mouse_pt->y - this->m_draw_points[EXIT_HANDLE].y;
				first_point = this->m_draw_points[EXIT_HANDLE-1];
				first_point.Offset(diff_x,diff_y);
				second_point = this->m_draw_points[EXIT_HANDLE+1];
				second_point.Offset(diff_x,diff_y);	
				this->m_draw_points[EXIT_HANDLE-1] = *p_mouse_pt;
				this->m_draw_points[EXIT_HANDLE] = *p_mouse_pt;
//				this->m_draw_points[EXIT_HANDLE+1] = second_point;
				this->m_exit_point = *p_mouse_pt;
			}
			if (this->m_arrow_type == LINE) {
				this->m_exit_point = *p_mouse_pt;
				this->IntilizeDrawPoints();
				this->SetGrabHandleRects();
			}

/*
			this->m_exit_point = *p_mouse_pt;
			for (i = 0;i<16;i++) {
				pDC->DPtoLP(&this->m_draw_points[i]);
			}
			this->IntilizeDrawPoints();
			this->SetGrabHandleRects();
*/
			break;
		}
	}

	this->SetGrabHandleRects();
}
void ArrowObj::DrawArrowPoint(CDC *pDC, POINT *p_move_to)
{
	ARROWSTRUCT a;

	// setup arrows
	a.nWidth = 20; // need to figure relationship between arrow width and pen width!!!
	a.fTheta = 0.9f;
	a.bFill = true;
	int diff_x = abs(this->m_entry_point.x - p_move_to->x);
	int diff_y = abs(this->m_entry_point.y - p_move_to->y);
	if (diff_x < 25 && diff_y < 25) {
		p_move_to = &this->m_draw_points[FOURTH_HANDLE];
	}
	pDC->MoveTo(*p_move_to);
	this->ArrowTo(pDC->m_hDC,&this->m_entry_point,&a, true);

}
void ArrowObj::DrawArrowPoint(CDC *pDC)
{

	ARROWSTRUCT a;

	// setup arrows
	a.nWidth = 10; // need to figure relationship between arrow width and pen width!!!
	a.fTheta = 0.6f;
	a.bFill = true;

	

	POINT last_point;
	last_point = this->m_draw_points[15];

	double tan_of_angle, opp, adj, hyp, angle;
	
	opp = this->m_draw_points[12].y - this->m_entry_point.y;
	adj = this->m_draw_points[12].x - this->m_entry_point.x;
	tan_of_angle = opp/adj;
	angle = atan(tan_of_angle);
	hyp = 6;
	opp = hyp * sin(angle);
	adj = hyp * cos(angle);
	if (this->m_entry_point.x > this->m_exit_point.x) {
		last_point.x = this->m_entry_point.x - (long)adj;
		last_point.y = this->m_entry_point.y - (long)opp;
	} 
	else {
		last_point.x  = this->m_entry_point.x + (long)adj;
		last_point.y = this->m_entry_point.y + (long)opp;
	}	

	pDC->MoveTo(last_point);

	this->ArrowTo(pDC->m_hDC,&this->m_entry_point,&a, true);

}

void ArrowObj::SetDrawPoints(CPoint *off_set_pt)
{
	int i;

	for (i = 0; i<16; i++) {
		this->m_draw_points[i].Offset(*off_set_pt);
	}
	this->m_exit_point = this->m_draw_points[0];
	this->m_entry_point = this->m_draw_points[15];
	this->m_mid_point.Offset(*off_set_pt);
	this->SetGrabHandleRects();
}
void ArrowObj::IntilizeDrawPoints()
{
	
	double tan_of_angle, opp, adj, hyp, angle;
	
	opp = this->m_exit_point.y - this->m_entry_point.y;
	adj = this->m_exit_point.x - this->m_entry_point.x;
	tan_of_angle = opp/adj;
	angle = atan(tan_of_angle);
	hyp = 18;
	opp = hyp * sin(angle);
	adj = hyp * cos(angle);
	
	this->m_draw_points[0]= this->m_exit_point;
	this->m_draw_points[1] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.1);

	this->m_draw_points[2] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.15);
	this->m_draw_points[3] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.2); // first handle
	this->m_draw_points[4] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.25);
	
	this->m_draw_points[5] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.35);
	this->m_draw_points[6] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.4);// second handle
	this->m_draw_points[7] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.45);
	
	this->m_draw_points[8] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.55); 
	this->m_draw_points[9] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.6);// third handle
	this->m_draw_points[10] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.66);
	
	this->m_draw_points[11] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.75);
	this->m_draw_points[12] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.8);// fourth handle
	this->m_draw_points[13] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.85);
	
	this->m_draw_points[14] = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.9);
	this->m_draw_points[15] = this->m_entry_point;
	this->m_mid_point = this->CalculatePointForArray(&this->m_exit_point,&this->m_entry_point,0.5);
}

void ArrowObj::CalculateMidPoint(POINT *p_first_point, POINT *p_second_point, POINT *p_mid_point)
{

	int diff_y, diff_x, new_diff_x, new_diff_y;
	double hyp, cos_angle, sine_angle, new_hyp;
	if (p_first_point->x == p_second_point->x) {
		p_mid_point->x = p_first_point->x;
		// calculate y mid_point
		diff_y = p_first_point->y - p_second_point->y;
		p_mid_point->y = p_second_point->y + (diff_y/2);
	}
	else if (p_first_point->y == p_second_point->y) {
		p_mid_point->y = p_first_point->y;
		// calculate x mid point
		diff_x = p_first_point->x - p_second_point->x;
		p_mid_point->x = p_second_point->x + (diff_x/2);
	}
	else {
		diff_x = abs(p_first_point->x - p_second_point->x);
		diff_y = abs(p_first_point->y - p_second_point->y);
		// rck
		double result = (diff_x*diff_x) + (diff_y*diff_y);
		hyp = sqrt(result);
		new_hyp = hyp/2;
		cos_angle = diff_x/hyp;
		sine_angle = diff_y/hyp;
		new_diff_x = (int)(cos_angle * new_hyp);
		new_diff_y = (int)(sine_angle * new_hyp);
		if (p_first_point->x > p_second_point->x) {
			p_mid_point->x = p_second_point->x + new_diff_x;
		}
		else {
			p_mid_point->x = p_first_point->x + new_diff_x;
		}
		if (p_first_point->y > p_second_point->y) {
			p_mid_point->y= p_second_point->y + new_diff_y;
		}
		else {
			p_mid_point->y = p_first_point->y + new_diff_y;
		}

	}
	return;
}

void ArrowObj::CalculatePointsToAdd(POINT *first_point, POINT *second_point, POINT *mouse_pt, POINT *new_ft_pt, POINT *new_sec_pt)
{
	int diff_x, diff_y;
	diff_x = first_point->x - this->m_hit_point.x;
	diff_y = first_point->y - this->m_hit_point.y;

	new_ft_pt->x = mouse_pt->x + diff_x;
	new_ft_pt->y = mouse_pt->y + diff_y;


	diff_x = this->m_hit_point.x - second_point->x;
	diff_y = this->m_hit_point.y - second_point->y;
	new_sec_pt->x = mouse_pt->x - diff_x;
	new_sec_pt->y = mouse_pt->y - diff_y;

}

POINT ArrowObj::CalculatePointForArray(POINT *p_first_point, POINT *p_second_point, double multiplier )
{
	POINT new_point;
	int diff_y, diff_x, new_diff_x, new_diff_y;
	double hyp, cos_angle, sine_angle, new_hyp;
	diff_x = abs(p_first_point->x - p_second_point->x);
	diff_y = abs(p_first_point->y - p_second_point->y);
	double result = (diff_x*diff_x) + (diff_y*diff_y);
	hyp = sqrt(result);
	new_hyp = hyp * multiplier;
	cos_angle = diff_x/hyp;
	sine_angle = diff_y/hyp;
	new_diff_x = (int)(cos_angle * new_hyp);
	new_diff_y = (int)(sine_angle * new_hyp);
	if (p_first_point->x > p_second_point->x) {
		new_point.x = p_first_point->x - new_diff_x;
	}
	else {
		new_point.x = p_first_point->x + new_diff_x;
	}
	if (p_first_point->y > p_second_point->y) {
		new_point.y= p_first_point->y - new_diff_y;
	}
	else {
		new_point.y = p_first_point->y + new_diff_y;
	}
	return new_point;
}

void ArrowObj::DrawGrabRects(CDC *pDC)
{
	COLORREF old_background = pDC->GetBkColor();

	if (this->m_arrow_selected) {
		pDC->FillSolidRect(&this->m_entry_grab,0);
		if (this->m_arrow_type == POLY) {
			pDC->FillSolidRect(&this->m_first_grab,0);
			pDC->FillSolidRect(&this->m_second_grab,0);
			pDC->FillSolidRect(&this->m_third_grab,0);
			pDC->FillSolidRect(&this->m_fourth_grab,0);
		}
		pDC->FillSolidRect(&this->m_exit_grab,0);

	}
	else {

		pDC->FillSolidRect(&this->m_entry_grab,RGB(0, 0, 255));
		if (this->m_arrow_type == POLY) {
			pDC->FillSolidRect(&this->m_first_grab,RGB(0, 0, 255));
			pDC->FillSolidRect(&this->m_second_grab,RGB(0, 0, 255));
			pDC->FillSolidRect(&this->m_third_grab,RGB(0, 0, 255));
			pDC->FillSolidRect(&this->m_fourth_grab,RGB(0, 0, 255));
		}
		pDC->FillSolidRect(&this->m_exit_grab,RGB(0, 0, 255));
	}
	pDC->SetBkColor(old_background);

}

bool ArrowObj::PointInGrabHandle(POINT *hit_point)
{
	if (this->m_entry_grab.PtInRect(*hit_point)) {
		this->m_handle_selected = ENTRY_HANDLE;
		return true;
	}
	if (this->m_first_grab.PtInRect(*hit_point)) {
		this->m_handle_selected = FIRST_HANDLE;
		return true;
	}
	if (this->m_second_grab.PtInRect(*hit_point))  {
		this->m_handle_selected = SECOND_HANDLE;
		return true;
	}

	if (this->m_third_grab.PtInRect(*hit_point))  {
		this->m_handle_selected = THIRD_HANDLE;
		return true;
	}

	if (this->m_fourth_grab.PtInRect(*hit_point))  {
		this->m_handle_selected = FOURTH_HANDLE;
		return true;
	}

	if (this->m_exit_grab.PtInRect(*hit_point)) {
		this->m_handle_selected = EXIT_HANDLE;
		return true;
	}
	this->m_handle_selected = NO_HANDLE;
	return false;
}



void ArrowObj::SetUndoRedoAction(int undo_action)
{
	this->m_undo_action = undo_action;
}

int ArrowObj::GetUndoRedoAction()
{
	return this->m_undo_action;
}

void ArrowObj::SetUndoRedoPosition(POSITION pos_in_arrow_list)
{
	this->m_pos_in_arrow_list = pos_in_arrow_list;
}

POSITION ArrowObj::GetUndoRedoPosition()
{
	return this->m_pos_in_arrow_list;
}

void ArrowObj::SetDrawPointsFromMidPoint(CPoint *p_mid_point)
{
	CPoint offset;
	offset.x = p_mid_point->x - this->m_mid_point.x;
	offset.y = p_mid_point->y - this->m_mid_point.y;
	this->SetDrawPoints(&offset);
}

void ArrowObj::GetDrawPointsArray(CPoint draw_points[])
{
	int i;
	for (i = 0; i< 16; i++) {
		draw_points[i] = this->m_draw_points[i];
	}
}

void ArrowObj::SetDrawPointsArray(CPoint draw_points[])
{
	int i;
	for (i = 0; i< 16; i++) {
		this->m_draw_points[i] = draw_points[i];
	}
}

BOOL ArrowObj::MousePointInGeneralRect(POINT *p_mouse_pt)
{
	int i;
	CRect large_rect;
	CPoint top_left(10000,10000);
	CPoint bottom_right(0,00);
	
	for (i = 0; i< 16; i++) {
		if (this->m_draw_points[i].x < top_left.x) top_left.x = this->m_draw_points[i].x;
		if (this->m_draw_points[i].y < top_left.y) top_left.y = this->m_draw_points[i].y;
		if (this->m_draw_points[i].x > bottom_right.x) bottom_right.x = this->m_draw_points[i].x;
		if (this->m_draw_points[i].y > bottom_right.y) bottom_right.y = this->m_draw_points[i].y;
	}
	if((bottom_right.x - top_left.x) < 20) {
		top_left.x	-= 10;
		bottom_right.x += 10;
	}
	if((bottom_right.y - top_left.y) < 20) {
		top_left.y	-= 10;
		bottom_right.y += 10;
	}
	large_rect.SetRect(top_left,bottom_right);
	return large_rect.PtInRect(*p_mouse_pt);
}

void ArrowObj::StraightenArrow()
{
	this->m_handle_selected = NO_HANDLE;
// intilize points array
	this->IntilizeDrawPoints();

	this->SetGrabHandleRects();
}

void ArrowObj::ReverseArrow()
{
	CPoint temp_point;
	temp_point = this->m_entry_point;
	this->m_entry_point = this->m_exit_point;
	this->m_exit_point = temp_point;
	this->IntilizeDrawPoints();
	this->SetGrabHandleRects();
}

int ArrowObj::FindIndexOfDrawPoints(POINT lpPt[], int num_points)
{
int index = 0, i;
	for (i = num_points; i> 0;i--) {
		if (lpPt[i].x == this->m_draw_points[FOURTH_HANDLE].x && lpPt[i].y == this->m_draw_points[FOURTH_HANDLE].y) {
			index = num_points - ((num_points - i) / 3) ;
			return index;
		}
	}

return -1;
}

void ArrowObj::SetMoveWithStation(bool move_with_station)
{
	this->m_move_with_station = move_with_station;
}

BOOL ArrowObj::GetMoveWithStation()
{
	return this->m_move_with_station;
}

void ArrowObj::GetArrowRect(CRect *arrow_rect)
{
	arrow_rect->SetRect(this->m_exit_point, this->m_entry_point);
	arrow_rect->NormalizeRect();
}

BOOL ArrowObj::GetHideArrow()
{
	return this->m_draw_arrow;
}

void ArrowObj::SetHideArrow(BOOL draw_arrow)
{
	this->m_draw_arrow = draw_arrow;
}

int ArrowObj::GetHandleSelected()
{
	return this->m_handle_selected;
}
