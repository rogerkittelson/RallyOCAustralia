#if !defined(AFX_ERRORREPORTDLG_H__1EDA9FAD_07FF_4A15_BA7B_D4DF2F08942E__INCLUDED_)
#define AFX_ERRORREPORTDLG_H__1EDA9FAD_07FF_4A15_BA7B_D4DF2F08942E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorReportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ErrorReportDlg dialog

class ErrorReportDlg : public CDialog
{
// Construction
public:
	ErrorReportDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_course_info;
// Dialog Data
	//{{AFX_DATA(ErrorReportDlg)
	enum { IDD = IDD_ERROR_REPORT };
	CString	m_error_report;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ErrorReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ErrorReportDlg)
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORREPORTDLG_H__1EDA9FAD_07FF_4A15_BA7B_D4DF2F08942E__INCLUDED_)
