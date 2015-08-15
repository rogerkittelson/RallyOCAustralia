#if !defined(AFX_RALLYOCPRINTDIALOG_H__8C13C37D_924E_4358_8981_19A7B48AD322__INCLUDED_)
#define AFX_RALLYOCPRINTDIALOG_H__8C13C37D_924E_4358_8981_19A7B48AD322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RallyOCPrintDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRallyOCPrintDialog dialog

class CRallyOCPrintDialog : public CPrintDialog
{
// Construction
public:
// The arguments to the following constructor closely match
  // CPrintDialog. Note the difference in the second argument.
  CRallyOCPrintDialog(BOOL bPrintSetupOnly,
                 // TRUE for Print Setup, FALSE for Print Dialog
                   DWORD dwFlags = PD_ALLPAGES | PD_USEDEVMODECOPIES |
                                PD_HIDEPRINTTOFILE,
                 // Combination of flags. Refer to the Windows SDK
                 // documentation for PRINTDLG structure for a
                 // description of all the flags that can be used.
                    CWnd* pParentWnd = NULL);


// Dialog Data
	//{{AFX_DATA(CRallyOCPrintDialog)
	enum { IDD = PRINTDLGORD };
	BOOL	m_print_left_margin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRallyOCPrintDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRallyOCPrintDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RALLYOCPRINTDIALOG_H__8C13C37D_924E_4358_8981_19A7B48AD322__INCLUDED_)
