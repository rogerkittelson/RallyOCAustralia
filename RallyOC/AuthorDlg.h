#if !defined(AFX_AUTHORDLG_H__1D8B8206_CBF9_4A32_8DB0_E032948EDEEF__INCLUDED_)
#define AFX_AUTHORDLG_H__1D8B8206_CBF9_4A32_8DB0_E032948EDEEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuthorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AuthorDlg dialog

class AuthorDlg : public CDialog
{
// Construction
public:
	AuthorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AuthorDlg)
	enum { IDD = IDD_AUTOR_PREF };
	CStatic	m_text_display;
	int		m_type;
	int		m_class;
	int		m_sub_class;
	CString	m_judge_name;
	int		m_grid_color;
	int		m_list_placement;
	BOOL	m_auto_add;
	BOOL	m_show_path;
	CString	m_grid_spacing;
	CString	m_judge_or_instruct;
	CString	m_ring_lenght;
	CString	m_ring_width;
	BOOL	m_size_to_screen;
	BOOL	m_show_class;
	BOOL	m_show_comp_name;
	BOOL	m_show_date;
	BOOL	m_show_judge;
	BOOL	m_show_location;
	BOOL	m_show_subclass;
	CString	m_organization;
	BOOL	m_show_organization;
	//}}AFX_DATA
	bool m_set_default;
	bool m_change_font;
	COLORREF m_font_color;
	LOGFONT m_default_font;
	int m_point_size;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AuthorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AuthorDlg)
	virtual void OnOK();
	afx_msg void OnDefault();
	afx_msg void OnTypeAkc();
	afx_msg void OnTypeApdt();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeFont();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHORDLG_H__1D8B8206_CBF9_4A32_8DB0_E032948EDEEF__INCLUDED_)
