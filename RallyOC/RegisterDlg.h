#if !defined(AFX_REGISTERDLG_H__19503A15_CB92_4549_9E66_858F41456261__INCLUDED_)
#define AFX_REGISTERDLG_H__19503A15_CB92_4549_9E66_858F41456261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegisterDlg dialog

class RegisterDlg : public CDialog
{
// Construction
public:
	RegisterDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL Check(void); 
// Dialog Data
	//{{AFX_DATA(RegisterDlg)
	enum { IDD = IDD_REGISTER };
	CButton	m_gen_prod_id;
	CStatic	m_actkey_st;
	CStatic	m_prodID_st;
	CButton	m_purchase;
	CButton	m_register;
	CEdit	m_user_name;
	CEdit	m_act_key;
	CEdit	m_req_key;
	CStatic	m_stat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RegisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString CreateActivationKey(CString *req_code);
	int CheckActivateKey(CString *act_key);
	BOOL UseStoredKey(CString *act_key);
	long ConvertUserNameToLongNumber(CString *user_name);
	long CreateFirstIDFromDate(void);
	int m_dead_flag;
	CString Version;
	int DaysLimit;
	long KeyCode;
	int m_first_year;
	int m_first_month;
	int m_first_day;
	// Generated message map functions
	//{{AFX_MSG(RegisterDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPurchase();
	afx_msg void OnContact();
	afx_msg void OnGenProdId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERDLG_H__19503A15_CB92_4549_9E66_858F41456261__INCLUDED_)
