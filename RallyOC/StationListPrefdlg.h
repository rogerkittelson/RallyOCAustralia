#if !defined(AFX_STATIONLISTPREFDLG_H__E431F508_4FF9_4A09_B2B6_5413855F7A57__INCLUDED_)
#define AFX_STATIONLISTPREFDLG_H__E431F508_4FF9_4A09_B2B6_5413855F7A57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationListPrefdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StationListPrefdlg dialog

class StationListPrefdlg : public CDialog
{
// Construction
public:
	StationListPrefdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StationListPrefdlg)
	enum { IDD = IDD_STATION_LIST_PREF };
	BOOL	m_show_akc;
	BOOL	m_show_class;
	BOOL	m_show_comp_name;
	BOOL	m_show_course_info;
	BOOL	m_show_date;
	BOOL	m_show_judge;
	BOOL	m_show_location;
	BOOL	m_show_statation_name;
	BOOL	m_show_station_number;
	BOOL	m_show_stats;
	BOOL	m_show_subclass;
	BOOL	m_show_xylocation;
	BOOL	m_show_ack_cm;
	BOOL	m_show_stat_name_cm;
	BOOL	m_show_stat_no_cm;
	BOOL	m_show_xy_cm;
	BOOL	m_show_organization;
	//}}AFX_DATA
	BOOL m_set_default;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StationListPrefdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(StationListPrefdlg)
	afx_msg void OnDefault();
	afx_msg void OnCourseInfoList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONLISTPREFDLG_H__E431F508_4FF9_4A09_B2B6_5413855F7A57__INCLUDED_)
