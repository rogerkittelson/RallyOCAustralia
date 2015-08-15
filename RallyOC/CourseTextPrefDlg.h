#if !defined(AFX_COURSETEXTPREFDLG_H__9392B296_8D03_4961_8878_144169D89D41__INCLUDED_)
#define AFX_COURSETEXTPREFDLG_H__9392B296_8D03_4961_8878_144169D89D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CourseTextPrefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCourseTextPrefDlg dialog

class CCourseTextPrefDlg : public CDialog
{
// Construction
public:
	CCourseTextPrefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCourseTextPrefDlg)
	enum { IDD = IDD_COURSE_INFO_PREF };
	BOOL	m_akc_number;
	BOOL	m_class;
	BOOL	m_comp_name;
	BOOL	m_date;
	BOOL	m_judge_name;
	BOOL	m_location;
	BOOL	m_station_name;
	BOOL	m_station_number;
	BOOL	m_subclass;
	BOOL	m_xy_location;
	//}}AFX_DATA
	BOOL m_set_defaults;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCourseTextPrefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCourseTextPrefDlg)
	afx_msg void OnDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COURSETEXTPREFDLG_H__9392B296_8D03_4961_8878_144169D89D41__INCLUDED_)
