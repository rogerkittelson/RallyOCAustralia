// StationList.cpp: implementation of the StationList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "StationMapper.h"
#include "StationList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(StationList, CObject, VERSIONABLE_SCHEMA | 2)
StationList::StationList()
{
	this->m_selected = false;
	this->m_view_station_list = false;
	this->m_list_rect.SetRect(10,10,10,10);
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT)); 
	this->m_station_list_font = new MyFont(&lf, 0);
}
StationList::StationList(LOGFONT *p_logfont, COLORREF color_ref)
{
	this->m_selected = false;
	this->m_view_station_list = false;
	this->m_list_rect.SetRect(10,10,10,10);
	this->m_station_list_font->SetFont(p_logfont);
	this->m_station_list_font->SetColorReference(color_ref);
}

StationList::~StationList()
{
	delete this->m_station_list_font;
}
void StationList::Serialize(CArchive& ar, BOOL serilize_ar, BOOL convert_old)
{
	if (serilize_ar) {
		CObject::Serialize(ar);
		ar.SerializeClass(GetRuntimeClass()); 
	}

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << this->m_view_station_list;
		ar << this->m_list_rect;
		ar << this->m_cmt_akc_number;
		ar << this->m_cmt_station_name;
		ar << this->m_cmt_station_number;
		ar << this->m_cmt_xy_location;
		// new variable 2-1-06
		ar << this->m_station_list_font;
	}
	else
	{
		// TODO: add loading code here
		int nVersion = ar.GetObjectSchema();
		if (convert_old) nVersion = 0;
		switch(nVersion) {
		case 0:
			ar >> this->m_view_station_list ;
			ar >> this->m_list_rect ;
			break;
		case 1:
			ar >> this->m_view_station_list ;
			ar >> this->m_list_rect ;
			ar >> this->m_cmt_akc_number;
			ar >> this->m_cmt_station_name;
			ar >> this->m_cmt_station_number;
			ar >> this->m_cmt_xy_location;
			break;
		case 2:
			delete this->m_station_list_font;
			ar >> this->m_view_station_list ;
			ar >> this->m_list_rect ;
			ar >> this->m_cmt_akc_number;
			ar >> this->m_cmt_station_name;
			ar >> this->m_cmt_station_number;
			ar >> this->m_cmt_xy_location;
		// new variable 2-1-06
			ar >> this->m_station_list_font;
			break;
		default :
            AfxThrowArchiveException(CArchiveException::badSchema, "AppVersion");
			break;
		}


	}
}
void StationList::SetViewStationList(BOOL view_list) {
	this->m_view_station_list = view_list;

}
BOOL StationList::ViewStationList(void) {
	return this->m_view_station_list;
}
void StationList::DrawStationList(CDC *pDC, RallyObjList *p_rallyList, int where_list, CRect *grid_rect, POSITION first_non_pylon_pos) {
	CString station_desc, station_list, temp_string;
	CString station_number_text, akc_number_text, station_name, x_y_location;
	
	POSITION pos;
	CRallyObject* pRallyItemInlist;
	CPen penBlack;
	CPen* pOldPen;
	TEXTMETRIC tm;
	int remainder, i;	
	int padding = 0;
	this->m_where_list = where_list;
	int type_of_course;
	int station_number, honor_station_number, akc_number;
	int line_number, left_edge, temp_right;
	CRect temp_rect;
	BOOL have_honor;
	have_honor = false;
	type_of_course = p_rallyList->GetTypeOfCourse();
	POINT mid_point, honor_mid_point;

	CFont *p_old_font, text_font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       
	this->m_station_list_font->GetLogFont(&lf);	
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(pDC->m_hDC, LOGPIXELSY)) / 72);
	
	VERIFY(text_font.CreateFontIndirect(&lf));  // create the font

	p_old_font = pDC->SelectObject(&text_font);
	COLORREF old_color = pDC->SetTextColor(this->GetColorReference());


	switch (where_list) {
	case LIST_CUSTOM:
		for (pos = first_non_pylon_pos; pos != NULL;)
		{
			pRallyItemInlist = (CRallyObject*)p_rallyList->GetNext(pos);
			station_number = pRallyItemInlist->GetStationNumber();
			akc_number = pRallyItemInlist->GetAKCNumber();
			if (type_of_course == AKC_COURSE) {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_xy_location) {
					mid_point = pRallyItemInlist->GetStationMidPoint();
					mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
					mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);

					x_y_location.Format("X: %d, Y: %d",mid_point.x, mid_point.y);
				}

				if (station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",station_number,this->akc_station_names[pRallyItemInlist->GetAKCNumber()],pRallyItemInlist->GetAKCNumber() );
				}
				else {
					if (akc_number != 60) {
						station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//						station_desc.Format("   %s %d\n\r",this->akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
					}
				}
			}
			else {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_station_name) station_name = p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()];
				if (this->m_cmt_xy_location) {
					mid_point = pRallyItemInlist->GetStationMidPoint();
					mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
					mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);
					x_y_location.Format("X: %d, Y: %d",mid_point.x, mid_point.y);
				}

				if (akc_number == 60) {
					have_honor = true;
					honor_station_number = station_number;
					honor_mid_point = mid_point;
				}
				if (station_number > 0 && akc_number != 60) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",station_number,p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				else {
					if (akc_number != 60) {
						station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//						station_desc.Format("   %s %d\n\r",p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
					}
				}			}
			station_list += station_desc;
		}
		if (have_honor) {
			if (type_of_course == AKC_COURSE) {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", honor_station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",50);
//				if (this->m_cmt_station_name) station_name = this->akc_station_names[50];
				if (this->m_cmt_xy_location) {
					x_y_location.Format("X: %d, Y: %d",honor_mid_point.x, honor_mid_point.y);
				}

				if (honor_station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";

				}
				else {
					station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
				}
			}
			else {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", honor_station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",60);
				if (this->m_cmt_station_name) station_name = p_rallyList->apdt_station_names[60];
				if (this->m_cmt_xy_location) {
					x_y_location.Format("X: %d, Y: %d",honor_mid_point.x, honor_mid_point.y);
				}

				if (honor_station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",honor_station_number,p_rallyList->apdt_station_names[60], pRallyItemInlist->GetAKCNumber());
				}
				else {
					station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("   %s %d\n\r",p_rallyList->apdt_station_names[60], pRallyItemInlist->GetAKCNumber());
				}
			}
			station_list += station_desc;
			station_desc.Empty();
		}
		pDC->DrawText(station_list, &this->m_list_rect, DT_LEFT | DT_CALCRECT);


		if(this->m_selected || pDC->IsPrinting()) {// draw a solid rect if selected
			penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		}
		else { // or a dashed if not
			penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		}
		pOldPen = pDC->SelectObject(&penBlack);
		this->m_list_rect.InflateRect(2,2,2,2);
		pDC->Rectangle(&this->m_list_rect);
		pDC->SelectObject(pOldPen);
		DeleteObject(penBlack);
		this->m_list_rect.InflateRect(-2,-2, -2,-2);
		pDC->DrawText(station_list,&this->m_list_rect, DT_LEFT   );
		break;
	case LIST_BOTTOM:
		pDC->GetTextMetrics(&tm);
		temp_string = StationMapper::GetAKCDescrptionFromAKCNumber(35);
		temp_string += "20. ";
		pDC->DrawText(temp_string,&temp_rect,DT_LEFT | DT_CALCRECT);

		line_number = grid_rect->bottom  + tm.tmHeight + (tm.tmHeight/2);
		this->m_list_rect.left = grid_rect->left;
		left_edge = grid_rect->left + 4;
		this->m_list_rect.top = grid_rect->bottom + tm.tmHeight + (tm.tmHeight/2);
		temp_right = 0;
		temp_rect.SetRect(left_edge,this->m_list_rect.top,left_edge+5,this->m_list_rect.top + 5);
		for (i = 1,pos = first_non_pylon_pos; pos != NULL;i++)
		{
			pRallyItemInlist = (CRallyObject*)p_rallyList->GetNext(pos);
			station_number = pRallyItemInlist->GetStationNumber();
			akc_number = pRallyItemInlist->GetAKCNumber();
			if (type_of_course == AKC_COURSE) {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_xy_location) {
					mid_point = pRallyItemInlist->GetStationMidPoint();
					mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
					mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);
					x_y_location.Format("X: %d, Y: %d",mid_point.x, mid_point.y);
				}

				if (station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location ;
//					station_desc.Format("  %d. %s %d",station_number,this->akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				else if(akc_number != 60) {
					station_desc = station_name + " " + akc_number_text + x_y_location;
//					station_desc.Format("   %s %d",this->akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
			}
			else {
				if (akc_number == 60) {
					have_honor = true;
					honor_station_number = station_number;
					honor_mid_point = mid_point;
					i--;
					continue;
				}
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_station_name) station_name = p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()];
				if (this->m_cmt_xy_location) {
					mid_point = pRallyItemInlist->GetStationMidPoint();
					mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
					mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);
					x_y_location.Format("X: %d, Y: %d",mid_point.x, mid_point.y);
				}

				if (station_number > 0 && akc_number != 60) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("  %d. %s %d",station_number,p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				else if(akc_number != 60) {
					station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("   %s %d",p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
			}
			temp_string = station_desc;

					
			pDC->DrawText(temp_string,&temp_rect,DT_LEFT | DT_CALCRECT);
			if (temp_rect.right > temp_right) {
				temp_right = temp_rect.right;
			}

			pDC->TextOut(left_edge,line_number,station_desc);
			line_number += tm.tmHeight;
			remainder = i % 10;
			if (i<=10) this->m_list_rect.bottom = line_number;
			if (remainder == 0) {
				left_edge = temp_right;
				temp_rect.left = left_edge;
				temp_rect.right = temp_right + 1;
				line_number = grid_rect->bottom  + tm.tmHeight + (tm.tmHeight/2);

			}

		}
		if (have_honor) {
			if (type_of_course == AKC_COURSE) {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", honor_station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",50);
//				if (this->m_cmt_station_name) station_name = this->akc_station_names[50];
				if (this->m_cmt_xy_location) {
					x_y_location.Format("X: %d, Y: %d",honor_mid_point.x, honor_mid_point.y);
				}
				if (honor_station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location;
//					station_desc.Format("%d. %s %d",honor_station_number,this->akc_station_names[50], pRallyItemInlist->GetAKCNumber());
				}
				else {
					station_desc = station_name + " " + akc_number_text + x_y_location;
//					station_desc.Format("   %s",this->akc_station_names[50]);
				}
			}
			else {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", honor_station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",60);
				if (this->m_cmt_station_name) station_name = p_rallyList->apdt_station_names[60];
				if (this->m_cmt_xy_location) {
					x_y_location.Format("X: %d, Y: %d",honor_mid_point.x, honor_mid_point.y);
				}
				if (honor_station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location;
//					station_desc.Format("%d. %s %d",honor_station_number,p_rallyList->apdt_station_names[60], pRallyItemInlist->GetAKCNumber());
				}
				else {
					station_desc = station_name + " " + akc_number_text + x_y_location;
//					station_desc.Format("   %s %d",p_rallyList->apdt_station_names[60], pRallyItemInlist->GetAKCNumber(), pRallyItemInlist->GetAKCNumber());
				}
			}
			station_list += station_desc;
			
			pDC->TextOut(left_edge,line_number,station_desc);
			line_number += tm.tmHeight;
			remainder = (i-1) % 10;
			if (i<=10) this->m_list_rect.bottom = line_number;
			if (remainder == 0) {	// then honor station is the only station on line
				left_edge = temp_right;
				temp_rect.left = left_edge;
				temp_rect.right = temp_right + 1;
				line_number = grid_rect->bottom  + tm.tmHeight + (tm.tmHeight/2);
				pDC->DrawText(station_desc,&temp_rect,DT_LEFT | DT_CALCRECT);
				temp_right = temp_rect.right + 1;
		
			}

		}

		this->m_list_rect.right = temp_right;
/*		line_number += tm.tmHeight;
		remainder = i % 10;
		if (i<=10) this->m_list_rect.bottom = line_number;
		if (remainder == 0) {
			left_edge = temp_right;
			temp_rect.left = left_edge;
			temp_rect.right = temp_right + 1;
			line_number = grid_rect->bottom  + tm.tmHeight + (tm.tmHeight/2);

		}
*/
		p_old_font = pDC->SelectObject(p_old_font);
		DeleteObject(text_font);
		if(pDC->IsPrinting()) {// draw a solid rect if selected
			penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		}
		else { // or a dashed if not
			penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		}
		pOldPen = pDC->SelectObject(&penBlack);
//		this->m_list_rect.InflateRect(2,2,2,2);
//		pDC->Rectangle(&this->m_list_rect);
		pDC->MoveTo(this->m_list_rect.TopLeft());
		pDC->LineTo(this->m_list_rect.right,this->m_list_rect.top);
		pDC->LineTo(this->m_list_rect.right,this->m_list_rect.bottom);
		pDC->LineTo(this->m_list_rect.left,this->m_list_rect.bottom);
		pDC->LineTo(this->m_list_rect.TopLeft());

		pDC->SelectObject(pOldPen);
		DeleteObject(penBlack);

		break;
	case LIST_RIGHT:
		pDC->GetTextMetrics(&tm);
		padding = tm.tmAveCharWidth * 3;

		for (pos = first_non_pylon_pos; pos != NULL;)
		{
			pRallyItemInlist = (CRallyObject*)p_rallyList->GetNext(pos);
			station_number = pRallyItemInlist->GetStationNumber();
			akc_number = pRallyItemInlist->GetAKCNumber();
			mid_point = pRallyItemInlist->GetStationMidPoint();
			mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
			mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);
			if (type_of_course == AKC_COURSE) {
			}
			else {
				if (akc_number == 60) {
					have_honor = true;
					honor_station_number = station_number;
					honor_mid_point = mid_point;
				}
			}
			if (type_of_course == AKC_COURSE) {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_xy_location) {
					mid_point = pRallyItemInlist->GetStationMidPoint();
					mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
					mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);
					x_y_location.Format("X: %d, Y: %d",mid_point.x, mid_point.y);
				}
				if (station_number > 0 && akc_number != 60) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",station_number,this->akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				else {
					if (akc_number != 60) {
						station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//						station_desc.Format("   %s %d\n\r",this->akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
					}
				}
			}
			else {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",pRallyItemInlist->GetAKCNumber());
				if (this->m_cmt_station_name) station_name = p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()];
				if (this->m_cmt_xy_location) {
					mid_point = pRallyItemInlist->GetStationMidPoint();
					mid_point.x = (long)(mid_point.x/this->m_pixels_per_foot_wd);
					mid_point.y = (long)(mid_point.y/this->m_pixels_per_foot_ht);
					x_y_location.Format("X: %d, Y: %d",mid_point.x, mid_point.y);
				}
				if (station_number > 0 && akc_number != 60) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",station_number,p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				else {
					if (akc_number != 60) {
						station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//						station_desc.Format("   %s %d\n\r",p_rallyList->apdt_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
					}
				}
			}
			station_list += station_desc;
		}
		if (have_honor) {
			if (type_of_course == AKC_COURSE) {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", honor_station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",50);
//				if (this->m_cmt_station_name) station_name = this->akc_station_names[50];
				if (this->m_cmt_xy_location) {
					x_y_location.Format("X: %d, Y: %d",honor_mid_point.x, honor_mid_point.y);
				}
				if (honor_station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",honor_station_number,this->akc_station_names[50], pRallyItemInlist->GetAKCNumber());
				}
				else {
					station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("   %s %d\n\r",this->akc_station_names[50], pRallyItemInlist->GetAKCNumber());
				}
			}
			else {
				if (this->m_cmt_station_number) station_number_text.Format("%d. ", honor_station_number);
				if (this->m_cmt_akc_number) akc_number_text.Format("(%d)",60);
				if (this->m_cmt_station_name) station_name = p_rallyList->apdt_station_names[60];
				if (this->m_cmt_xy_location) {
					x_y_location.Format("X: %d, Y: %d",honor_mid_point.x, honor_mid_point.y);
				}
				if (honor_station_number > 0) {
					station_desc = station_number_text + station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("%d. %s %d\n\r",honor_station_number,p_rallyList->apdt_station_names[60], pRallyItemInlist->GetAKCNumber());
				}
				else {
					station_desc = station_name + " " + akc_number_text + x_y_location + "\n\r";
//					station_desc.Format("   %s %d\n\r",p_rallyList->apdt_station_names[60], pRallyItemInlist->GetAKCNumber());
				}
			}
			station_list += station_desc;
		}
		this->m_list_rect.top = grid_rect->top;
		this->m_list_rect.left = grid_rect->right + padding;
		this->m_list_rect.bottom = grid_rect->top + 10;
		this->m_list_rect.right = grid_rect->right+ padding + 10;

		pDC->DrawText(station_list, &this->m_list_rect, DT_LEFT    | DT_CALCRECT);


		if(this->m_selected || pDC->IsPrinting()) {// draw a solid rect if selected
			penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		}
		else { // or a dashed if not
			penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		}
		pOldPen = pDC->SelectObject(&penBlack);
		this->m_list_rect.InflateRect(2,2,2,2);
		pDC->Rectangle(&this->m_list_rect);
		pDC->SelectObject(pOldPen);
		DeleteObject(penBlack);
		this->m_list_rect.InflateRect(-2,-2, -2,-2);
		pDC->DrawText(station_list,&this->m_list_rect, DT_LEFT   );
		break;
	}
}
BOOL StationList::PointInStationListRect(CPoint *point) {
	if (!this->ViewStationList() || this->m_where_list != LIST_CUSTOM) return false;
	if (this->m_list_rect.PtInRect(*point)) {
		this->m_selected = true;
		return true;
	}
	else {
		this->m_selected = false;
		return false;
	}

}
CRect* StationList::GetStationListRect(CRect *list_rect){
	*list_rect= *this->m_list_rect;
	return list_rect;
}
void StationList::SetStationListRect(CRect *new_list_rect) {
	this->m_list_rect = new_list_rect;	
}
void StationList::MoveStationList(CRectTracker *drag_rect, CPoint *sp){
	drag_rect->m_rect.OffsetRect(*sp);
	this->m_list_rect = drag_rect->m_rect;
}
void StationList::OffSetStationListRect(CPoint *point) {
	this->m_list_rect.OffsetRect(*point);
}

void StationList::SetStationListViewParameters(BOOL akc_number, BOOL station_name, BOOL station_number, BOOL xy_location)
{
	this->m_cmt_akc_number = akc_number;
	this->m_cmt_station_name = station_name;
	this->m_cmt_station_number = station_number;
	this->m_cmt_xy_location = xy_location;
}

void StationList::SetStationListFont(MyFont *default_font)
{
	LOGFONT lf;
	default_font->GetLogFont(&lf);
	this->m_station_list_font->SetFont(&lf);
}

BOOL StationList::GetStationListSelected()
{
	return this->m_selected;
}

MyFont * StationList::GetStationListFont()
{
	return this->m_station_list_font;
}

void StationList::SetTextColor(COLORREF color_ref)
{
	this->m_station_list_font->SetColorReference(color_ref);
}

void StationList::SetLogFont(LOGFONT *p_log_font)
{
	this->m_station_list_font->SetFont(p_log_font);
}

COLORREF StationList::GetColorReference()
{
	return this->m_station_list_font->GetColorReference();
}

void StationList::GetStationListLogFont(LOGFONT *lf)
{
	this->m_station_list_font->GetLogFont(lf);
}
