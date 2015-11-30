#if !defined(AFX_COURSEINFODLG_H__1F497E2D_7A14_4024_A6FD_3BCB9AEB84FD__INCLUDED_)
#define AFX_COURSEINFODLG_H__1F497E2D_7A14_4024_A6FD_3BCB9AEB84FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CourseInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCourseInfoDlg dialog

class CCourseInfoDlg : public CDialog
{
// Construction
public:
	CCourseInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCourseInfoDlg)
	enum { IDD = IDD_COURSE };
	CString	m_length;
	CString	m_width;
	CString	m_compete;
	CString	m_judge;
	CString	m_location;
	CString	m_grid_spacing;
	COleDateTime	m_date_compete;
	CString	m_judge_inst;
	int		m_class;
	int		m_sub_class;
	int		m_type_course;
	BOOL	m_show_class;
	BOOL	m_show_comp;
	BOOL	m_show_date;
	BOOL	m_show_judge;
	BOOL	m_show_location;
	BOOL	m_show_subclass;
	CString	m_organization;
	BOOL	m_show_organization;
	//}}AFX_DATA
	BOOL set_defaults;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCourseInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCourseInfoDlg)
	virtual void OnOK();
	afx_msg void OnDefault();
	afx_msg void OnNovice();
	afx_msg void OnAdvanced();
	afx_msg void OnExcellent();
	afx_msg void OnMaster();
	afx_msg void OnTraining();
	afx_msg void OnTypeAkc();
	afx_msg void OnTypeApdt();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COURSEINFODLG_H__1F497E2D_7A14_4024_A6FD_3BCB9AEB84FD__INCLUDED_)
