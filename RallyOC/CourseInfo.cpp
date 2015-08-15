// CourseInfo.cpp: implementation of the CCourseInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "CourseInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CCourseInfo, CObject, VERSIONABLE_SCHEMA | 3)

CCourseInfo::CCourseInfo()
{
	this->m_competation = _T("");
	this->m_class = NOVICE;
	this->m_date_compete = COleDateTime::GetCurrentTime();
	int this_year = this->m_date_compete.GetYear();
	this->m_location = _T("");
	this->m_organization = _T("");
	this->m_ring_lenght = 50;
	this->m_ring_width = 50;
	this->m_grid_spacing = 5;
	this->m_feet_or_meters = FEET;
	this->m_view_course_info = FALSE;
	this->m_course_info_rect.SetRect(10, 10, 10, 10);
	this->m_selected = false;
	this->m_show_path = true;
	this->m_stat_num_loc = 0;
	this->m_add_normal = true;
	this->m_print_grid_lines = true;
	this->m_where_cones = CONE_MIDDLE;
	this->m_where_list = LIST_CUSTOM;
	this->m_number_honor = false;
	this->m_type_of_course;
	this->m_stat_desc = BOTH_TEXT_PIC;
	this->m_do_rotate_text = FALSE;

	this->m_course_info_font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT)); 
	this->m_course_info_font = new MyFont(&lf, 0);

}

CCourseInfo::~CCourseInfo()
{
	delete this->m_course_info_font;

}
void CCourseInfo::Serialize(CArchive& ar, BOOL serilize_ar, BOOL convert_old_course)
{

	if (serilize_ar) {
		CObject::Serialize(ar);
		ar.SerializeClass(GetRuntimeClass()); 
	}


	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << this->m_competation ;
		ar << this->m_class;
		ar << this->m_sub_class;
		ar << this->m_date_compete;
		ar << this->m_location;
		ar << this->m_organization;
		ar << this->m_judge;
		ar << this->m_ring_lenght;
		ar << this->m_ring_width;
		ar << this->m_grid_spacing;
		ar << this->m_feet_or_meters;
		ar << this->m_view_course_info;
		ar << this->m_course_info_rect;
		ar << this->m_stat_num_loc;
		ar << this->m_show_path;
		ar << this->m_size_to_fit;
		ar << this->m_print_grid_lines;
		ar << this->m_add_normal;
		ar << this->m_where_cones;
		ar << this->m_where_list;
		ar << this->m_number_honor;
		ar << this->m_type_of_course;
		ar << this->m_stat_desc;
		ar << this->m_do_rotate_text;
		ar <<	m_cmt_class;
		ar <<	m_cmt_comp_name;
		ar <<	m_cmt_date;
		ar <<	m_cmt_judge_name;
		ar <<	m_cmt_location;
		ar <<	m_cmt_subclass;
		ar << this->m_course_info_font;
	}
	else
	{
		// TODO: add loading code here
		unsigned int Schema;
        Schema = ar.GetObjectSchema();
        if (convert_old_course && Schema != 1) Schema = 0;
		switch (Schema)
        {
			case -1:
 				ar >> this->m_competation ;
				ar >> this->m_class;
				ar >> this->m_date_compete;
				ar >> this->m_location;
				ar >> this->m_judge;
				ar >> this->m_ring_lenght;
				ar >> this->m_ring_width;
				ar >> this->m_grid_spacing;		
				ar >> this->m_feet_or_meters;
				ar >> this->m_view_course_info;
				ar >> this->m_course_info_rect;
				ar >> this->m_stat_num_loc;
				ar >> this->m_show_path;
				ar >> this->m_size_to_fit;
              break;
			case 1:
				ar >> this->m_competation ;
				ar >> this->m_class;
				ar >> this->m_date_compete;
				ar >> this->m_location;
				ar >> this->m_judge;
				ar >> this->m_ring_lenght;
				ar >> this->m_ring_width;
				ar >> this->m_grid_spacing;		
				ar >> this->m_feet_or_meters;
				ar >> this->m_view_course_info;
				ar >> this->m_course_info_rect;
				ar >> this->m_stat_num_loc;
				ar >> this->m_show_path;
				ar >> this->m_size_to_fit;
				ar >> this->m_print_grid_lines;
				ar >> this->m_add_normal;
				ar >> this->m_where_cones;
				ar >> this->m_where_list;
				break;
 
			case 0:// converting version 1 course
				ar >> this->m_competation ;
				ar >> this->m_class;
				ar >> this->m_date_compete;
				ar >> this->m_location;
				ar >> this->m_judge;
				ar >> this->m_ring_lenght;
				ar >> this->m_ring_width;
				ar >> this->m_grid_spacing;		
				ar >> this->m_feet_or_meters;
				ar >> this->m_view_course_info;
				ar >> this->m_course_info_rect;
				ar >> this->m_stat_num_loc;
				ar >> this->m_show_path;
				ar >> this->m_size_to_fit;
				ar >> this->m_print_grid_lines;
				ar >> this->m_add_normal;
				ar >> this->m_where_cones;
				ar >> this->m_where_list;
				if (this->m_where_list > 2) this->m_where_list = LIST_CUSTOM;
				ar >> this->m_number_honor;
				break;

			case 2:
				ar >> this->m_competation ;
				ar >> this->m_class;
				ar >> this->m_sub_class;
				ar >> this->m_date_compete;
				ar >> this->m_location;
				ar >> this->m_organization;
				ar >> this->m_judge;
				ar >> this->m_ring_lenght;
				ar >> this->m_ring_width;
				ar >> this->m_grid_spacing;		
				ar >> this->m_feet_or_meters;
				ar >> this->m_view_course_info;
				ar >> this->m_course_info_rect;
				ar >> this->m_stat_num_loc;
				ar >> this->m_show_path;
				ar >> this->m_size_to_fit;
				ar >> this->m_print_grid_lines;
				ar >> this->m_add_normal;
				ar >> this->m_where_cones;
				ar >> this->m_where_list;
				ar >> this->m_number_honor;
				ar >> this->m_type_of_course;
				ar >> this->m_stat_desc;
				ar >> this->m_do_rotate_text;
				ar >>	m_cmt_class;
				ar >>	m_cmt_comp_name;
				ar >>	m_cmt_date;
				ar >>	m_cmt_judge_name;
				ar >>	m_cmt_location;
				ar >>	m_cmt_subclass;
				break;  
			case 3:
				delete this->m_course_info_font;
				ar >> this->m_competation ;
				ar >> this->m_class;
				ar >> this->m_sub_class;
				ar >> this->m_date_compete;
				ar >> this->m_location;
				ar >> this->m_organization;
				ar >> this->m_judge;
				ar >> this->m_ring_lenght;
				ar >> this->m_ring_width;
				ar >> this->m_grid_spacing;		
				ar >> this->m_feet_or_meters;
				ar >> this->m_view_course_info;
				ar >> this->m_course_info_rect;
				ar >> this->m_stat_num_loc;
				ar >> this->m_show_path;
				ar >> this->m_size_to_fit;
				ar >> this->m_print_grid_lines;
				ar >> this->m_add_normal;
				ar >> this->m_where_cones;
				ar >> this->m_where_list;
				ar >> this->m_number_honor;
				ar >> this->m_type_of_course;
				ar >> this->m_stat_desc;
				ar >> this->m_do_rotate_text;
				ar >>	m_cmt_class;
				ar >>	m_cmt_comp_name;
				ar >>	m_cmt_date;
				ar >>	m_cmt_judge_name;
				ar >>	m_cmt_location;
				ar >>	m_cmt_subclass;
				ar >> this->m_course_info_font;
				break;  
			default :
                AfxThrowArchiveException(CArchiveException::badSchema, "AppVersion");
                break;
		}

	}


}
void CCourseInfo::SetCourseInfo(CourseInfo *course_info){
	this->m_class = course_info->m_class;
	this->m_competation = course_info->m_competation;
	this->m_date_compete = course_info->m_date_compete;
	this->m_feet_or_meters = course_info->m_feet_or_meters;
	this->m_grid_spacing = course_info->m_grid_spacing;
	this->m_judge = course_info->m_judge;
	this->m_location = course_info->m_location;
	this->m_organization = course_info->m_organization;
	this->m_ring_lenght = course_info->m_ring_lenght;
	this->m_ring_width = course_info->m_ring_width;
	this->m_show_path = course_info->m_show_path;
	this->m_stat_num_loc = course_info->m_stat_num_loc;
	this->m_size_to_fit = course_info->m_size_to_fit;
	this->m_add_normal = course_info->m_add_normal;
	this->m_print_grid_lines = course_info->m_print_grid_lines;
	this->m_where_cones = course_info->m_where_cones;
	this->m_where_list = course_info->m_where_list;
	this->m_number_honor = course_info->m_number_honor;
	this->m_honor_in_list = course_info->m_honor_in_list;
	this->m_type_of_course = course_info->m_type_of_course;
	this->m_sub_class = course_info->m_sub_class;
	this->m_stat_desc = course_info->m_stat_desc;
	this->m_do_rotate_text = course_info->m_do_rotate_text;
	this->m_cmt_class = course_info->m_cmt_class;
	this->m_cmt_comp_name = course_info->m_cmt_comp_name;
	this->m_cmt_date = course_info->m_cmt_date;
	this->m_cmt_judge_name = course_info->m_cmt_judge_name;
	this->m_cmt_location = course_info->m_cmt_location;
	this->m_cmt_organization = course_info->m_cmt_organization;
	this->m_cmt_subclass = course_info->m_cmt_subclass;
}
void CCourseInfo::GetCourseInfo(CourseInfo *course_info){
	course_info->m_class = this->m_class;
	course_info->m_competation = this->m_competation;
	course_info->m_date_compete = this->m_date_compete;
	int this_year = this->m_date_compete.GetYear();
	course_info->m_feet_or_meters = this->m_feet_or_meters;
	course_info->m_grid_spacing = this->m_grid_spacing;
	course_info->m_judge = this->m_judge;
	course_info->m_location = this->m_location;
	course_info->m_organization = this->m_organization;
	course_info->m_ring_lenght = this->m_ring_lenght;
	course_info->m_ring_width = this->m_ring_width;
	course_info->m_show_path = this->m_show_path;
	course_info->m_stat_num_loc = this->m_stat_num_loc;
	course_info->m_size_to_fit = this->m_size_to_fit;
	course_info->m_add_normal = this->m_add_normal;
	course_info->m_print_grid_lines = this->m_print_grid_lines;
	course_info->m_where_cones = this->m_where_cones;
	course_info->m_where_list = this->m_where_list;
	course_info->m_number_honor = this->m_number_honor;
	course_info->m_honor_in_list = this->m_honor_in_list;
	course_info->m_type_of_course = this->m_type_of_course;
	course_info->m_sub_class = this->m_sub_class;
	course_info->m_stat_desc = this->m_stat_desc;
	course_info->m_do_rotate_text = this->m_do_rotate_text;
	course_info->m_cmt_class = this->m_cmt_class;
	course_info->m_cmt_comp_name = this->m_cmt_comp_name ;
	course_info->m_cmt_date = this->m_cmt_date;
	course_info->m_cmt_judge_name = this->m_cmt_judge_name;
	course_info->m_cmt_location = this->m_cmt_location;
	course_info->m_cmt_organization = this->m_cmt_organization;
	course_info->m_cmt_subclass= this->m_cmt_subclass;
}
void CCourseInfo::GetCourseInfoRect(CRect *course_info_rect){
	*course_info_rect= *this->m_course_info_rect;
}
void CCourseInfo::SetCourseInfoRect(CRect *new_info_rect) {
	this->m_course_info_rect = new_info_rect;	
}
void CCourseInfo::SetViewCourseInfo(BOOL view_info) {
	this->m_view_course_info = view_info;
}
BOOL CCourseInfo::ViewCourse(void) {

	return this->m_view_course_info;
}
void CCourseInfo::DrawCourseInfo(CDC *pDC, BOOL show_station_list, CRect *grid_rect, CRect *station_rect) {

	CString courseInformation, rally_class, rally_date, location, comp_name, judge_name, organization;

	CFont *p_old_font, text_font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       
	this->m_course_info_font->GetLogFont(&lf);	
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(pDC->m_hDC, LOGPIXELSY)) / 72);
	
	VERIFY(text_font.CreateFontIndirect(&lf));  // create the font

	p_old_font = pDC->SelectObject(&text_font);
	COLORREF old_color = pDC->SetTextColor(this->GetColorReference());

	
	int padding;
	TEXTMETRIC tm;
	courseInformation.Empty();
	if (this->m_cmt_class) {
		switch(this->m_class) {
		case NOVICE:
			rally_class = "Novice";
			break;
		case ADVANCED:
			rally_class = "Advanced";		
			break;
		case EXCELLENT:
			rally_class = "Excellent";		
			break;
		case TRAINING:
			rally_class = "Training";
		}
		if (this->m_cmt_subclass) {
			switch (this->m_sub_class) {
			case CLASS_A:
				rally_class += " : A";
				break;
			case CLASS_B:
				rally_class += " : B";
				break;
			}
		}
		rally_class += "\n\r";
	}
	if (!this->m_cmt_class && this->m_cmt_subclass) {
		switch (this->m_sub_class) {
		case CLASS_A:
			rally_class += "A";
			break;
		case CLASS_B:
			rally_class += "B";
			break;
		}
		rally_class += "\n\r";
	}
	if (this->m_cmt_date) {
		rally_date = this->m_date_compete.Format(_T("%A, %B %d, %Y")) + "\n\r";
	}
	
	
	if (this->m_cmt_location) location = this->m_location + "\n\r";
	if (this->m_cmt_organization) organization = this->m_organization + "\n\r";
	if (this->m_cmt_judge_name && this->m_class == TRAINING) judge_name = "Instructor: " +  this->m_judge + "\n\r";
	if (this->m_cmt_judge_name && this->m_class != TRAINING) judge_name = "Judge: " +  this->m_judge + "\n\r";
	if (this->m_cmt_comp_name) comp_name = this->m_competation + "\n\r"; 
	
	courseInformation = comp_name + rally_class + rally_date + location + organization +judge_name;


	switch (this->m_where_list) {
	case LIST_CUSTOM:
		break;
	case LIST_BOTTOM:
		pDC->GetTextMetrics(&tm);

		if (show_station_list) {
			this->m_course_info_rect.left = station_rect->right + (tm.tmAveCharWidth * 2);
			this->m_course_info_rect.top = grid_rect->bottom + tm.tmHeight + (tm.tmHeight/2);
			this->m_course_info_rect.bottom = this->m_course_info_rect.top  + 10;
			this->m_course_info_rect.right = this->m_course_info_rect.left + 10;
		
		}
		else {
			this->m_course_info_rect.left = grid_rect->left;
			this->m_course_info_rect.top = grid_rect->bottom + tm.tmHeight + (tm.tmHeight/2);
			this->m_course_info_rect.bottom = this->m_course_info_rect.top  + 10;
			this->m_course_info_rect.right = this->m_course_info_rect.left + 10;

		}
		break;
	case LIST_RIGHT:
		pDC->GetTextMetrics(&tm);
		padding = tm.tmAveCharWidth * 3;

		if (show_station_list) {
			this->m_course_info_rect.top = station_rect->bottom + (tm.tmHeight * 2);
			this->m_course_info_rect.left = grid_rect->right + padding;
			this->m_course_info_rect.bottom = this->m_course_info_rect.top + 10;
			this->m_course_info_rect.right = this->m_course_info_rect.left+ padding + 10;

		}
		else {
			this->m_course_info_rect.top = grid_rect->top;
			this->m_course_info_rect.left = grid_rect->right + padding;
			this->m_course_info_rect.bottom = this->m_course_info_rect.top + 10;
			this->m_course_info_rect.right = grid_rect->right+ padding + 10;

		}
		break;
	}

	pDC->DrawText(courseInformation,&this->m_course_info_rect, DT_CENTER | DT_CALCRECT);

	CPen penBlack;
	CPen* pOldPen;

	if(this->m_selected || pDC->IsPrinting()) {// draw a solid rect if selected
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}
	else { // or a dashed if not
		penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
	}
	pOldPen = pDC->SelectObject(&penBlack);
	this->m_course_info_rect.InflateRect(2,2, 2,2);


	pDC->Rectangle(&this->m_course_info_rect);
	pDC->SelectObject(pOldPen);
	DeleteObject(penBlack);
	this->m_course_info_rect.InflateRect(-2,-2, -2,-2);
	pDC->DrawText(courseInformation,&this->m_course_info_rect, DT_CENTER);
	p_old_font = pDC->SelectObject(p_old_font);
	DeleteObject(text_font);


}
BOOL CCourseInfo::PointInCourseInfoRect(CPoint *point) {
	if (!this->m_view_course_info || this->m_where_list != LIST_CUSTOM) return false;
	if (this->m_course_info_rect.PtInRect(*point)) {
		this->m_selected = true;
		return true;
	}
	else {
		this->m_selected = false;
		return false;
	}

}
void CCourseInfo::MoveCourseInfo(CRectTracker *drag_rect, CPoint *sp){
	drag_rect->m_rect.OffsetRect(*sp);
	this->m_course_info_rect = drag_rect->m_rect;
}
void CCourseInfo::OffSetInfoRect(CPoint *point) {
	this->m_course_info_rect.OffsetRect(*point);
}
int CCourseInfo::GetStationNumberLocation(void) {
	return this->m_stat_num_loc;
}
BOOL CCourseInfo::GetSizeToFit(void) {
	return this->m_size_to_fit;
}
void CCourseInfo::SetSizeToFit(BOOL size_to_fit) {
	this->m_size_to_fit = size_to_fit;
}
BOOL CCourseInfo::GetAutoAddNormalStation(void) {
	return this->m_add_normal;
}

void CCourseInfo::SetStationDescription(int stat_desc)
{
	this->m_stat_desc = stat_desc;
}

int CCourseInfo::GetStationDescription()
{
	return this->m_stat_desc;
}

int CCourseInfo::GetTypeOfCourse()
{
	return this->m_type_of_course;
}

void CCourseInfo::SetCourseInfoFont(MyFont *default_font)
{
//	this->m_course_info_font = default_font;
	LOGFONT lf;
	default_font->GetLogFont(&lf);
	this->m_course_info_font->SetFont(&lf);
}

BOOL CCourseInfo::GetCourseInfoSelected()
{
	return this->m_selected;
}

MyFont * CCourseInfo::GetCourseInfoFont()
{
	return this->m_course_info_font;
}

void CCourseInfo::SetTextColor(COLORREF color_ref)
{
	this->m_course_info_font->SetColorReference(color_ref);
}

void CCourseInfo::SetLogFont(LOGFONT *p_log_font)
{
	this->m_course_info_font->SetFont(p_log_font);
}

COLORREF CCourseInfo::GetColorReference()
{
	return this->m_course_info_font->GetColorReference();
}

void CCourseInfo::GetCourseInfoLogFont(LOGFONT *lf)
{
	this->m_course_info_font->GetLogFont(lf);
}

BOOL CCourseInfo::GetShowPath()
{
	return this->m_show_path;
}
