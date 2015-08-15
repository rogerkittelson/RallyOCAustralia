// AddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "AddressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddressDlg dialog


AddressDlg::AddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddressDlg)
	m_city = _T("");
	m_email_add = _T("");
	m_name = _T("");
	m_phone_no = _T("");
	m_state = _T("");
	m_street = _T("");
	m_suite_no = _T("");
	m_zip_code = _T("");
	//}}AFX_DATA_INIT
}


void AddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddressDlg)
	DDX_Text(pDX, IDC_CITY, m_city);
	DDX_Text(pDX, IDC_EMAIL_ADD, m_email_add);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PHONE_NO, m_phone_no);
	DDX_Text(pDX, IDC_STATE, m_state);
	DDX_Text(pDX, IDC_STREET, m_street);
	DDX_Text(pDX, IDC_SUITE_NO, m_suite_no);
	DDX_Text(pDX, IDC_ZIP_CODE, m_zip_code);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddressDlg, CDialog)
	//{{AFX_MSG_MAP(AddressDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddressDlg message handlers
