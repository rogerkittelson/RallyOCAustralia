// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__234F9CC7_C6E0_43D2_87BC_F8CCF1A952D7__INCLUDED_)
#define AFX_CHILDFRM_H__234F9CC7_C6E0_43D2_87BC_F8CCF1A952D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	void UpdateInsertAfterMenu(void);
	void ModifyInsertAfterMenu(void);
	CMenu* GetInsertAfterMenu(void);
	void SetUpRallyListDialog(void);
	void ClearRallyListDialog(void);
	CMenu* GetChangeToMenu(void);
	void SetUpChangeMenu(void);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetAddMenu(void);
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnForwardHalt();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnChangePace();
	afx_msg void OnRightTurns();
	afx_msg void OnLeftTurns();
	afx_msg void OnFinish();
	afx_msg void OnMove();
	afx_msg void OnHeel();
	afx_msg void OnWeave();
	afx_msg void OnStationary();
	afx_msg void OnNonstationary();
	afx_msg void OnAdvanced();
	afx_msg void OnExcellent();
	afx_msg void OnMaster();
	afx_msg void OnNovice();
	afx_msg void OnPivot();
	afx_msg void OnViewRallyList();
	afx_msg void OnUpdateViewRallyList(CCmdUI* pCmdUI);
	afx_msg void OnPattern();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CPoint m_point;

private:
	int FindMenuItem(CMenu* Menu, LPCTSTR MenuString);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__234F9CC7_C6E0_43D2_87BC_F8CCF1A952D7__INCLUDED_)
