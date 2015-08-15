// DocInfodlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "DocInfodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DocInfodlg dialog


DocInfodlg::DocInfodlg(CWnd* pParent /*=NULL*/)
	: CDialog(DocInfodlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DocInfodlg)
	m_author = _T("");
	m_created = _T("");
	m_modified = _T("");
	m_notes = _T("");
	m_printed = _T("");
	//}}AFX_DATA_INIT
}


void DocInfodlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DocInfodlg)
	DDX_Text(pDX, IDC_AUTHOR, m_author);
	DDX_Text(pDX, IDC_CREATED, m_created);
	DDX_Text(pDX, IDC_MODIFIED, m_modified);
	DDX_Text(pDX, IDC_NOTES, m_notes);
	DDX_Text(pDX, IDC_PRINTED, m_printed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DocInfodlg, CDialog)
	//{{AFX_MSG_MAP(DocInfodlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DocInfodlg message handlers

void DocInfodlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}
