// ObjectPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "ObjectPropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ObjectPropDlg dialog


ObjectPropDlg::ObjectPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ObjectPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ObjectPropDlg)
	m_custom_size = _T("");
	m_size_object = -1;
	m_rotate_degrees = _T("");
	//}}AFX_DATA_INIT
}


void ObjectPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ObjectPropDlg)
	DDX_Text(pDX, IDC_CUSTOM_SIZE, m_custom_size);
	DDX_Radio(pDX, IDC_SIZE_2, m_size_object);
	DDX_Text(pDX, IDC_STATION_DEG, m_rotate_degrees);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ObjectPropDlg, CDialog)
	//{{AFX_MSG_MAP(ObjectPropDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ObjectPropDlg message handlers

int ObjectPropDlg::DoModal(SpecialObj *p_special_object) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_degree_rotation = p_special_object->m_rotate_degrees;
	this->m_rotate_degrees.Format("%f",this->m_degree_rotation);
	return CDialog::DoModal();
}
