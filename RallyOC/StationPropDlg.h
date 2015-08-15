#if !defined(AFX_STATIONPROPDLG_H__13EEB6AC_FFD9_4D9B_B3A0_95143B4463C5__INCLUDED_)
#define AFX_STATIONPROPDLG_H__13EEB6AC_FFD9_4D9B_B3A0_95143B4463C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationPropDlg.h : header file
//
#include "RallyObjList.h"

/////////////////////////////////////////////////////////////////////////////
// StationPropDlg dialog

class StationPropDlg : public CDialog
{
// Construction
public:
	void RenumberStation(int new_number);
	StationPropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StationPropDlg)
	enum { IDD = IDD_STAT_PROP };
	CEdit	m_ctl_actual_size;
	CComboBox	m_a_number;
	CComboBox	m_station_name;
	CString	m_stat_no;
	int		m_stat_desc;
	int		m_station_size;
	CString	m_actual_size;
	CString	m_station_degrees;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StationPropDlg)
	public:
	virtual int DoModal(CRallyObject *pRallyObjectInSelectList, RallyObjList *pRallyList, CScrollView *pView, CDocument *pDoc);
	virtual int DoModal(CObList *pRallyList, CScrollView *pView, CDocument *pDoc);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRallyObject *m_pRallyObject;
	RallyObjList *m_prally_list;
	CScrollView *m_pView;
	CDocument *m_pDoc;
	double m_degree_rotation;
	BOOL m_multi_stations;
	// Generated message map functions
	//{{AFX_MSG(StationPropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeStatName();
	afx_msg void OnSelchangeANumber();
	afx_msg void OnChangeStatNo();
	virtual void OnOK();
	afx_msg void OnSize2();
	afx_msg void OnSize5();
	afx_msg void OnSize7();
	afx_msg void OnSizeCustom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONPROPDLG_H__13EEB6AC_FFD9_4D9B_B3A0_95143B4463C5__INCLUDED_)
