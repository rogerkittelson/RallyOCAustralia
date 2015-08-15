// StationDescDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "StationDescDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StationDescDlg dialog


StationDescDlg::StationDescDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StationDescDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StationDescDlg)
	m_show_akc = FALSE;
	m_show_class = FALSE;
	m_show_comp_name = FALSE;
	m_show_course_info = FALSE;
	m_show_date = FALSE;
	m_show_judge_name = FALSE;
	m_show_location = FALSE;
	m_show_station_name = FALSE;
	m_show_stat_no = FALSE;
	m_show_sub_class = FALSE;
	m_show_xy_loc = FALSE;
	m_show_organization = FALSE;
	//}}AFX_DATA_INIT
	this->m_set_default = false;
}


void StationDescDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StationDescDlg)
	DDX_Check(pDX, IDC_AKC_NUMBER, m_show_akc);
	DDX_Check(pDX, IDC_CLASS, m_show_class);
	DDX_Check(pDX, IDC_COMP_NAME, m_show_comp_name);
	DDX_Check(pDX, IDC_COURSE_INFO_LIST, m_show_course_info);
	DDX_Check(pDX, IDC_DATE, m_show_date);
	DDX_Check(pDX, IDC_JUDGE_NAME, m_show_judge_name);
	DDX_Check(pDX, IDC_LOCATION, m_show_location);
	DDX_Check(pDX, IDC_STAT_NAME, m_show_station_name);
	DDX_Check(pDX, IDC_STAT_NUMBER, m_show_stat_no);
	DDX_Check(pDX, IDC_SUBCLASS, m_show_sub_class);
	DDX_Check(pDX, IDC_XY_LOCATION, m_show_xy_loc);
	DDX_Check(pDX, IDC_ORGANIZE, m_show_organization);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StationDescDlg, CDialog)
	//{{AFX_MSG_MAP(StationDescDlg)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_COURSE_INFO_LIST, OnCourseInfoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StationDescDlg message handlers

void StationDescDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_default = true;
	this->OnOK();
}

void StationDescDlg::OnCourseInfoList() 
{
	// TODO: Add your control notification handler code here
	CWnd *tempWnd;
	this->UpdateData(true);
	if (this->m_show_course_info) {
		tempWnd = this->GetDlgItem(IDC_COMP_NAME);
		tempWnd->ShowWindow(SW_SHOW);
		tempWnd = this->GetDlgItem(IDC_DATE);
		tempWnd->ShowWindow(SW_SHOW);
		tempWnd = this->GetDlgItem(IDC_CLASS);
		tempWnd->ShowWindow(SW_SHOW);
		tempWnd = this->GetDlgItem(IDC_LOCATION);
		tempWnd->ShowWindow(SW_SHOW);
		tempWnd = this->GetDlgItem(IDC_SUBCLASS);
		tempWnd->ShowWindow(SW_SHOW);
		tempWnd = this->GetDlgItem(IDC_JUDGE_NAME);
		tempWnd->ShowWindow(SW_SHOW);
		tempWnd = this->GetDlgItem(IDC_ORGANIZE);
		tempWnd->ShowWindow(SW_SHOW);

	}
	else {
		tempWnd = this->GetDlgItem(IDC_COMP_NAME);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_DATE);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_CLASS);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_LOCATION);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_SUBCLASS);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_JUDGE_NAME);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_ORGANIZE);
		tempWnd->ShowWindow(SW_HIDE);
	}	
}
