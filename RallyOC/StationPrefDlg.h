#if !defined(AFX_STATIONPREFDLG_H__83BF3E76_FC9F_4E10_BFFF_A9D804F4556D__INCLUDED_)
#define AFX_STATIONPREFDLG_H__83BF3E76_FC9F_4E10_BFFF_A9D804F4556D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationPrefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StationPrefDlg dialog

class StationPrefDlg : public CDialog
{
// Construction
public:
	StationPrefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StationPrefDlg)
	enum { IDD = IDD_STATION_PREF };
	CEdit	m_ctl_actual_size;
	CStatic	m_text_display;
	int		m_cone_placement;
	BOOL	m_number_honor;
	BOOL	m_do_rotate_text;
	int		m_stat_desc;
	int		m_loc_station_number;
	int		m_station_size;
	CString	m_actual_size;
	//}}AFX_DATA
	bool m_set_default;
	bool m_change_font;
	COLORREF m_font_color;
	LOGFONT m_default_font;
	int m_point_size;
	int m_actual_station_size;
	BOOL m_can_rotate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StationPrefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StationPrefDlg)
	afx_msg void OnChangeFont();
	afx_msg void OnPaint();
	afx_msg void OnDefault();
	afx_msg void OnSize2();
	afx_msg void OnSize5();
	afx_msg void OnSize7();
	afx_msg void OnSizeCustom();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONPREFDLG_H__83BF3E76_FC9F_4E10_BFFF_A9D804F4556D__INCLUDED_)
