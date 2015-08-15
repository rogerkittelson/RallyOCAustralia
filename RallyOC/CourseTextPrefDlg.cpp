// CourseTextPrefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "CourseTextPrefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCourseTextPrefDlg dialog


CCourseTextPrefDlg::CCourseTextPrefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCourseTextPrefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCourseTextPrefDlg)
	m_akc_number = FALSE;
	m_class = FALSE;
	m_comp_name = FALSE;
	m_date = FALSE;
	m_judge_name = FALSE;
	m_location = FALSE;
	m_station_name = FALSE;
	m_station_number = FALSE;
	m_subclass = FALSE;
	m_xy_location = FALSE;
	//}}AFX_DATA_INIT
	this->m_set_defaults = FALSE;
}


void CCourseTextPrefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCourseTextPrefDlg)
	DDX_Check(pDX, IDC_AKC_NUMBER, m_akc_number);
	DDX_Check(pDX, IDC_CLASS, m_class);
	DDX_Check(pDX, IDC_COMP_NAME, m_comp_name);
	DDX_Check(pDX, IDC_DATE, m_date);
	DDX_Check(pDX, IDC_JUDGE_NAME, m_judge_name);
	DDX_Check(pDX, IDC_LOCATION, m_location);
	DDX_Check(pDX, IDC_STAT_NAME, m_station_name);
	DDX_Check(pDX, IDC_STAT_NUMBER, m_station_number);
	DDX_Check(pDX, IDC_SUBCLASS, m_subclass);
	DDX_Check(pDX, IDC_XY_LOCATION, m_xy_location);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCourseTextPrefDlg, CDialog)
	//{{AFX_MSG_MAP(CCourseTextPrefDlg)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCourseTextPrefDlg message handlers

void CCourseTextPrefDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_defaults = true;
	this->OnOK();
}
