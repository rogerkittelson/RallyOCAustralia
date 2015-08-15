#if !defined(AFX_STATIONDESCDLG_H__FC347932_6FB2_490A_9695_D5993EED126C__INCLUDED_)
#define AFX_STATIONDESCDLG_H__FC347932_6FB2_490A_9695_D5993EED126C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationDescDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StationDescDlg dialog

class StationDescDlg : public CDialog
{
// Construction
public:
	StationDescDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StationDescDlg)
	enum { IDD = IDD_STATION_DESC_PREF };
	BOOL	m_show_akc;
	BOOL	m_show_class;
	BOOL	m_show_comp_name;
	BOOL	m_show_course_info;
	BOOL	m_show_date;
	BOOL	m_show_judge_name;
	BOOL	m_show_location;
	BOOL	m_show_station_name;
	BOOL	m_show_stat_no;
	BOOL	m_show_sub_class;
	BOOL	m_show_xy_loc;
	BOOL	m_show_organization;
	//}}AFX_DATA
	BOOL m_set_default;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StationDescDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StationDescDlg)
	afx_msg void OnDefault();
	afx_msg void OnCourseInfoList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONDESCDLG_H__FC347932_6FB2_490A_9695_D5993EED126C__INCLUDED_)
