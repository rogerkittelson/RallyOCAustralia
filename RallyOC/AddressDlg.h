#if !defined(AFX_ADDRESSDLG_H__56A06E13_AF8E_4AD6_A999_211AAB1E45A9__INCLUDED_)
#define AFX_ADDRESSDLG_H__56A06E13_AF8E_4AD6_A999_211AAB1E45A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddressDlg dialog

class AddressDlg : public CDialog
{
// Construction
public:
	AddressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddressDlg)
	enum { IDD = IDD_MAIL_ADDRESS };
	CString	m_city;
	CString	m_email_add;
	CString	m_name;
	CString	m_phone_no;
	CString	m_state;
	CString	m_street;
	CString	m_suite_no;
	CString	m_zip_code;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddressDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRESSDLG_H__56A06E13_AF8E_4AD6_A999_211AAB1E45A9__INCLUDED_)
