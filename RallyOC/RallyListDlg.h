#if !defined(AFX_RALLYLISTDLG_H__18F9BA0D_AE97_4B45_8493_DBEF0C0BFB68__INCLUDED_)
#define AFX_RALLYLISTDLG_H__18F9BA0D_AE97_4B45_8493_DBEF0C0BFB68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RallyListDlg.h : header file
//
#include "RallyListView.h"
/////////////////////////////////////////////////////////////////////////////
// RallyListDlg dialog

class RallyListDlg : public CDialog
{
// Construction
public:
	RallyListDlg(CWnd* pParent = NULL);   // standard constructor
	void SetUpRallyList(CObList *p_rallyList,CDocument *pDoc);
	void ClearRallyList(void);
// Dialog Data
	//{{AFX_DATA(RallyListDlg)
	enum { IDD = IDD_RALLY_LIST };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RallyListDlg)
	public:
	virtual BOOL Create(UINT nID, CWnd* pParentWnd);
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	RallyListView mList;
	BOOL Except_Only_Integers(long input);
	// Generated message map functions
	//{{AFX_MSG(RallyListDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RALLYLISTDLG_H__18F9BA0D_AE97_4B45_8493_DBEF0C0BFB68__INCLUDED_)
