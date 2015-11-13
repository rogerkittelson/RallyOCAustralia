// CourseInfo.h: interface for the CCourseInfo class.
//
//////////////////////////////////////////////////////////////////////
#include "MyFont.h"
#if !defined(AFX_COURSEINFO_H__C81A4D8F_5906_4398_A0E1_40F7F037E300__INCLUDED_)
#define AFX_COURSEINFO_H__C81A4D8F_5906_4398_A0E1_40F7F037E300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCourseInfo : public CObject  
{
public:
	BOOL GetShowPath(void);
	void GetCourseInfoLogFont(LOGFONT *lf);
	COLORREF GetColorReference();
	void SetLogFont(LOGFONT *p_log_font);
	void SetTextColor(COLORREF color_ref);
	MyFont* GetCourseInfoFont();
	BOOL GetCourseInfoSelected();
	void SetCourseInfoFont(MyFont *default_font);
	int GetTypeOfCourse(void);
	int GetStationDescription(void);
	void SetStationDescription(int stat_desc);

	CCourseInfo();
	virtual void Serialize(CArchive& ar, BOOL serilize_ar, BOOL convert_old_course);
	virtual ~CCourseInfo();
	void SetCourseInfo(CourseInfo *course_info);
	void GetCourseInfo(CourseInfo *course_info);
	void SetViewCourseInfo(BOOL view_info);
	BOOL ViewCourse(void);
	void DrawCourseInfo(CDC *pDC, BOOL show_station_list, CRect *grid_rect, CRect *station_rect);
	BOOL PointInCourseInfoRect(CPoint *point);
	void MoveCourseInfo(CRectTracker *drag_rect, CPoint *sp);
	void GetCourseInfoRect(CRect *course_info_rect);
	void SetCourseInfoRect(CRect *new_info_rect);
	void OffSetInfoRect(CPoint *point);
	int GetStationNumberLocation(void);
	BOOL GetSizeToFit(void);
	void SetSizeToFit(BOOL size_to_fit);
	BOOL GetAutoAddNormalStation(void);
// display information
	BOOL	m_cmt_class;
	BOOL	m_cmt_comp_name;
	BOOL	m_cmt_date;
	BOOL	m_cmt_judge_name;
	BOOL	m_cmt_location;
	BOOL	m_cmt_organization;
	BOOL	m_cmt_subclass;
private:
	CString m_competation;
	int m_class;
	COleDateTime m_date_compete;
	CString m_location;
	CString m_organization;
	CString m_judge;
	int m_ring_width;
	int m_ring_lenght;
	int m_feet_or_meters;
	double m_grid_spacing;
	int m_show_path;
	int m_stat_num_loc;
	int m_stat_desc;
	BOOL m_do_rotate_text;
	BOOL m_view_course_info;
	BOOL m_size_to_fit;
	CRect m_course_info_rect;
	BOOL m_selected;
	BOOL m_add_normal;
	int m_print_grid_lines;
	int m_where_cones;
	int m_where_list;
	BOOL m_number_honor;
	int m_honor_in_list;
	int m_type_of_course;
	int m_sub_class;
	MyFont *m_course_info_font;

protected:
	DECLARE_SERIAL(CCourseInfo)


};

#endif // !defined(AFX_COURSEINFO_H__C81A4D8F_5906_4398_A0E1_40F7F037E300__INCLUDED_)
