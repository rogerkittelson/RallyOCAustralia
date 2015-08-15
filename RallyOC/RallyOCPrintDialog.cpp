// RallyOCPrintDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "RallyOCPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRallyOCPrintDialog dialog


CRallyOCPrintDialog::CRallyOCPrintDialog(BOOL bPrintSetupOnly,
    DWORD dwFlags /* = PD_ALLPAGES | PD_USEDEVMODECOPIES |
                  PD_HIDEPRINTTOFILE */,
    CWnd* pParentWnd /* = NULL */)
    : CPrintDialog(bPrintSetupOnly, dwFlags, pParentWnd)
{
	//{{AFX_DATA_INIT(CRallyOCPrintDialog)
	m_print_left_margin = FALSE;
	//}}AFX_DATA_INIT
}


void CRallyOCPrintDialog::DoDataExchange(CDataExchange* pDX)
{
	CPrintDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRallyOCPrintDialog)
	DDX_Check(pDX, IDC_LEFT_MARGIN, m_print_left_margin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRallyOCPrintDialog, CPrintDialog)
	//{{AFX_MSG_MAP(CRallyOCPrintDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRallyOCPrintDialog message handlers
