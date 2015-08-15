#if !defined(AFX_SCORESHEETPREFDLG_H__DDDBB09E_CB40_4D5B_A866_F202DCFF3331__INCLUDED_)
#define AFX_SCORESHEETPREFDLG_H__DDDBB09E_CB40_4D5B_A866_F202DCFF3331__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreSheetPrefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ScoreSheetPrefDlg dialog

class ScoreSheetPrefDlg : public CDialog
{
// Construction
public:
	ScoreSheetPrefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ScoreSheetPrefDlg)
	enum { IDD = IDD_SCORE_SHEET_PREF };
	BOOL	m_show_akc;
	BOOL	m_show_arm_band;
	BOOL	m_show_breed;
	BOOL	m_show_class;
	BOOL	m_show_comp_name;
	BOOL	m_show_course_info;
	BOOL	m_show_date;
	BOOL	m_show_judge_name;
	BOOL	m_show_jump_ht;
	BOOL	m_show_location;
	BOOL	m_show_stat_name;
	BOOL	m_show_stat_no;
	BOOL	m_show_subclass;
	BOOL	m_show_xy_loc;
	BOOL	m_final_score;
	BOOL	m_judge_sign;
	BOOL	m_time;
	BOOL	m_show_organization;
	//}}AFX_DATA
	BOOL m_set_default;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScoreSheetPrefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ScoreSheetPrefDlg)
	afx_msg void OnDefault();
	afx_msg void OnCourseInfoList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORESHEETPREFDLG_H__DDDBB09E_CB40_4D5B_A866_F202DCFF3331__INCLUDED_)
