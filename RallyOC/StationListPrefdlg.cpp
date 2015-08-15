// StationListPrefdlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "StationListPrefdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StationListPrefdlg dialog


StationListPrefdlg::StationListPrefdlg(CWnd* pParent /*=NULL*/)
	: CDialog(StationListPrefdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StationListPrefdlg)
	m_show_akc = FALSE;
	m_show_class = FALSE;
	m_show_comp_name = FALSE;
	m_show_course_info = FALSE;
	m_show_date = FALSE;
	m_show_judge = FALSE;
	m_show_location = FALSE;
	m_show_statation_name = FALSE;
	m_show_station_number = FALSE;
	m_show_stats = FALSE;
	m_show_subclass = FALSE;
	m_show_xylocation = FALSE;
	m_show_ack_cm = FALSE;
	m_show_stat_name_cm = FALSE;
	m_show_stat_no_cm = FALSE;
	m_show_xy_cm = FALSE;
	m_show_organization = FALSE;
	//}}AFX_DATA_INIT
	this->m_set_default = false;
}


void StationListPrefdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StationListPrefdlg)
	DDX_Check(pDX, IDC_AKC_NUMBER, m_show_akc);
	DDX_Check(pDX, IDC_CLASS, m_show_class);
	DDX_Check(pDX, IDC_COMP_NAME, m_show_comp_name);
	DDX_Check(pDX, IDC_COURSE_INFO_LIST, m_show_course_info);
	DDX_Check(pDX, IDC_DATE, m_show_date);
	DDX_Check(pDX, IDC_JUDGE_NAME, m_show_judge);
	DDX_Check(pDX, IDC_LOCATION, m_show_location);
	DDX_Check(pDX, IDC_STAT_NAME, m_show_statation_name);
	DDX_Check(pDX, IDC_STAT_NUMBER, m_show_station_number);
	DDX_Check(pDX, IDC_STATS, m_show_stats);
	DDX_Check(pDX, IDC_SUBCLASS, m_show_subclass);
	DDX_Check(pDX, IDC_XY_LOCATION, m_show_xylocation);
	DDX_Check(pDX, IDC_AKC_NUMBER_CM, m_show_ack_cm);
	DDX_Check(pDX, IDC_STAT_NAME_CM, m_show_stat_name_cm);
	DDX_Check(pDX, IDC_STAT_NUMBER_CM, m_show_stat_no_cm);
	DDX_Check(pDX, IDC_XY_LOCATION_CM, m_show_xy_cm);
	DDX_Check(pDX, IDC_ORGANIZE, m_show_organization);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StationListPrefdlg, CDialog)
	//{{AFX_MSG_MAP(StationListPrefdlg)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_COURSE_INFO_LIST, OnCourseInfoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StationListPrefdlg message handlers

void StationListPrefdlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_default = true;
	this->OnOK();
}

void StationListPrefdlg::OnCourseInfoList() 
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
