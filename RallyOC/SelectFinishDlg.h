#if !defined(AFX_SELECTFINISHDLG_H__EC16FDCE_7080_4791_9527_729B4C980209__INCLUDED_)
#define AFX_SELECTFINISHDLG_H__EC16FDCE_7080_4791_9527_729B4C980209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectFinishDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectFinishDlg dialog

class SelectFinishDlg : public CDialog
{
// Construction
public:
	SelectFinishDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectFinishDlg)
	enum { IDD = IDD_SELECT_FINISH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectFinishDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectFinishDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTFINISHDLG_H__EC16FDCE_7080_4791_9527_729B4C980209__INCLUDED_)
