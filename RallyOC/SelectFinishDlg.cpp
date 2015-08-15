// SelectFinishDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "SelectFinishDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectFinishDlg dialog


SelectFinishDlg::SelectFinishDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelectFinishDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectFinishDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SelectFinishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectFinishDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectFinishDlg, CDialog)
	//{{AFX_MSG_MAP(SelectFinishDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectFinishDlg message handlers
