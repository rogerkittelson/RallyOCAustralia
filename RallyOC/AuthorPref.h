#if !defined(AFX_AUTHORPREF_H__EE38AD5F_CB62_48CB_B2EC_2F9AFEB137DB__INCLUDED_)
#define AFX_AUTHORPREF_H__EE38AD5F_CB62_48CB_B2EC_2F9AFEB137DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuthorPref.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AuthorPref dialog

class AuthorPref : public CDialog
{
// Construction
public:
	AuthorPref(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(AuthorPref)
	enum { IDD = IDD_ARROW_PREF };
	CButton	m_default_button;
	CStatic	m_show_color;
	int		m_line_type;
	CString	m_line_thickness;
	BOOL	m_move_arrow;
	int		m_line_style;
	//}}AFX_DATA
	BOOL m_set_default;
	LOGPEN m_log_pen;
	int m_arrow_type;
	bool m_scribble;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AuthorPref)
	public:
	virtual int DoModal(LOGPEN *default_pen, int default_arrow, bool default_case);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(AuthorPref)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSetColor();
	afx_msg void OnDefault();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHORPREF_H__EE38AD5F_CB62_48CB_B2EC_2F9AFEB137DB__INCLUDED_)
