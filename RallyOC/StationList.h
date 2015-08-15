// StationList.h: interface for the StationList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATIONLIST_H__384BDCB1_E6F1_4AEB_A02B_A558D035D028__INCLUDED_)
#define AFX_STATIONLIST_H__384BDCB1_E6F1_4AEB_A02B_A558D035D028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RallyObjList.h"
class StationList : public CObject  
{
public:
	void GetStationListLogFont(LOGFONT *lf);
	COLORREF GetColorReference(void);
	void SetLogFont(LOGFONT *p_log_font);
	void SetTextColor(COLORREF color_ref);
	MyFont * GetStationListFont(void);
	BOOL GetStationListSelected(void);
	void SetStationListFont(MyFont *default_font);
	void SetStationListViewParameters(BOOL akc_number, BOOL station_name, BOOL station_number, BOOL xy_location);
	StationList();
	StationList(LOGFONT *p_logfont, COLORREF color_ref);
	virtual void Serialize(CArchive& ar, BOOL serilize_ar, BOOL convert_old);
	virtual ~StationList();
	void SetViewStationList(BOOL view_list);
	BOOL ViewStationList(void);
	void DrawStationList(CDC *pDC, RallyObjList *p_rallyList, int where_list, CRect *grid_rect, POSITION first_non_pylon_pos);
	BOOL PointInStationListRect(CPoint *point);
	void MoveStationList(CRectTracker *drag_rect, CPoint *sp);
	void OffSetStationListRect(CPoint *point);
	CRect* GetStationListRect(CRect *list_rect);
	void SetStationListRect(CRect *new_list_rect);
	double m_pixels_per_foot_wd;
	double m_pixels_per_foot_ht;

protected:
	BOOL m_view_station_list;
	BOOL m_selected;
	CRect m_list_rect;
	int m_where_list;
	BOOL	m_cmt_akc_number;
	BOOL	m_cmt_station_name;
	BOOL	m_cmt_station_number;
	BOOL	m_cmt_xy_location;
	MyFont *m_station_list_font;
//	CString akc_station_names[51];
	DECLARE_SERIAL(StationList)
};

#endif // !defined(AFX_STATIONLIST_H__384BDCB1_E6F1_4AEB_A02B_A558D035D028__INCLUDED_)
