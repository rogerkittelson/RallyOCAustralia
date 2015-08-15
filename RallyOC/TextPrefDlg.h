#if !defined(AFX_TEXTPREFDLG_H__5FBB4EE5_038E_4534_BBB6_528DC8A3C3FC__INCLUDED_)
#define AFX_TEXTPREFDLG_H__5FBB4EE5_038E_4534_BBB6_528DC8A3C3FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextPrefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TextPrefDlg dialog

class TextPrefDlg : public CDialog
{
// Construction
public:
	TextPrefDlg(CWnd* pParent = NULL);   // standard constructor
	bool m_set_default;
	bool m_change_font;
	COLORREF m_font_color;
	LOGFONT m_default_font;
	int m_point_size;
	COLORREF m_outline_rect_color;
	bool m_default_case;
// Dialog Data
	//{{AFX_DATA(TextPrefDlg)
	enum { IDD = IDD_TEXT_PREF };
	CButton	m_default_button;
	CStatic	m_show_color;
	CStatic	m_text_display;
	BOOL	m_outline_rect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TextPrefDlg)
	public:
	virtual int DoModal(BOOL out_line_rect, LOGFONT *default_font, COLORREF default_text_color, COLORREF default_rect_color, bool default_case);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TextPrefDlg)
	afx_msg void OnPaint();
	afx_msg void OnSetColor();
	afx_msg void OnDefault();
	afx_msg void OnChangeFont();
	virtual BOOL OnInitDialog();
	afx_msg void OnOutRect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPREFDLG_H__5FBB4EE5_038E_4534_BBB6_528DC8A3C3FC__INCLUDED_)
