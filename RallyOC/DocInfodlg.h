#if !defined(AFX_DOCINFODLG_H__4851160C_C51C_4D91_A5C4_617920853A73__INCLUDED_)
#define AFX_DOCINFODLG_H__4851160C_C51C_4D91_A5C4_617920853A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DocInfodlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DocInfodlg dialog

class DocInfodlg : public CDialog
{
// Construction
public:
	DocInfodlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DocInfodlg)
	enum { IDD = IDD_DOCINFO };
	CString	m_author;
	CString	m_created;
	CString	m_modified;
	CString	m_notes;
	CString	m_printed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DocInfodlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DocInfodlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCINFODLG_H__4851160C_C51C_4D91_A5C4_617920853A73__INCLUDED_)
