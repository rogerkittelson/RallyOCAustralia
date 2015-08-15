#if !defined(AFX_RENUMBERDLG_H__CED75261_C556_45C2_B8A2_C1BE60523735__INCLUDED_)
#define AFX_RENUMBERDLG_H__CED75261_C556_45C2_B8A2_C1BE60523735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenumberDlg.h : header file
//
#include "DogRunDoc.h"
/////////////////////////////////////////////////////////////////////////////
// RenumberDlg dialog

class RenumberDlg : public CDialog
{
// Construction
public:
	RenumberDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RenumberDlg)
	enum { IDD = IDD_RENUMBER };
	CComboBox	m_station_list;
	CString	m_current_station;
	int		m_insert;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RenumberDlg)
	public:
	virtual int DoModal(CDogRunDoc *p_dogrundoc, CRallyObject *p_selectedStation);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRallyObject *m_selected_station;
	CDogRunDoc *m_dog_runDoc;
	// Generated message map functions
	//{{AFX_MSG(RenumberDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENUMBERDLG_H__CED75261_C556_45C2_B8A2_C1BE60523735__INCLUDED_)
