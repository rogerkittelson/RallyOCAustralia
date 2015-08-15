#if !defined(AFX_EDITDLG_H__EF77800B_D732_4A69_8209_63584034AED8__INCLUDED_)
#define AFX_EDITDLG_H__EF77800B_D732_4A69_8209_63584034AED8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//
#include "MyFont.h"
#include "TextObj.h"
/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	void MoveTextObjectRect(void);
	virtual BOOL Create(MyFont *p_set_font, CRect *p_dialog_rect, CString *p_display_text);
	void CalculateOffSetsForCorner(void);
	void SetIntialRect(RECT *intial_rect);
	void ChangeFont(LOGFONT *p_log_font, COLORREF new_color);
	CEditDlg(CScrollView* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDITTEXT };
	CEdit	m_ctrl_edit;
	CString	m_edit_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	public:
	virtual BOOL Create(LOGFONT *p_log_font, TextObj *p_text_obj);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CScrollView* m_pParent;
	int m_nID;
	CFont m_font;
	MyFont *m_my_font;
	CRect m_intial_rect;
	CRect m_current_rect;
    CBrush* m_pEditBkBrush;
	TextObj *mp_text_obj;

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing( UINT, LPRECT ); 
	afx_msg void OnDestroy();
	afx_msg void OnChangeEditText();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__EF77800B_D732_4A69_8209_63584034AED8__INCLUDED_)
