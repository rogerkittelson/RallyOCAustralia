// RallyListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "RallyListDlg.h"
#include "RallyObject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RallyListDlg dialog


RallyListDlg::RallyListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RallyListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RallyListDlg)
	//}}AFX_DATA_INIT
}


void RallyListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList);
	//{{AFX_DATA_MAP(RallyListDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RallyListDlg, CDialog)
	//{{AFX_MSG_MAP(RallyListDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RallyListDlg message handlers

BOOL RallyListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// populate the grid control
	int COLS = 3;

	// columns...
/*
	CString col_title;

	col_title = "No." ;
	mList.InsertColumn(0, col_title, LVCFMT_LEFT, 60, 0);
	col_title = "AKC No." ;
	mList.InsertColumn(1, col_title, LVCFMT_LEFT, 60, 1);
	col_title = "Station Description"; 
	mList.InsertColumn(2, col_title, LVCFMT_LEFT, 240, 2);
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL RallyListDlg::Create(UINT nID, CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(nID, pParentWnd);
}

BOOL RallyListDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}

void RallyListDlg::SetUpRallyList(CObList *p_rallyList, CDocument *pDoc) {
	mList.SetUpRallyList(p_rallyList, pDoc);
}
void RallyListDlg::ClearRallyList(void) {
	mList.DeleteAllItems();
	this->Invalidate();
	this->UpdateWindow();
}
void RallyListDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void RallyListDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

BOOL RallyListDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}
// Screen Input for integers only
// Returning true means take input, false means skip
BOOL RallyListDlg::Except_Only_Integers(long input) {
	BOOL rejectChar = true;

	if (input == VK_TAB)
		return false;
	if (input == VK_BACK) 
		return false;
	if (input == VK_LEFT || input == VK_RIGHT || input == VK_UP || input == VK_DOWN) 
		return false;
	if (!GetAsyncKeyState(VK_SHIFT) && (input >= '0'  && input <= '9')) 
		rejectChar = false;
	if (input >= VK_NUMPAD0 && input <= VK_NUMPAD9) 
		rejectChar = false;
	return rejectChar;
}