// ScoreSheetPrefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "ScoreSheetPrefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ScoreSheetPrefDlg dialog


ScoreSheetPrefDlg::ScoreSheetPrefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ScoreSheetPrefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScoreSheetPrefDlg)
	m_show_akc = FALSE;
	m_show_arm_band = FALSE;
	m_show_breed = FALSE;
	m_show_class = FALSE;
	m_show_comp_name = FALSE;
	m_show_course_info = FALSE;
	m_show_date = FALSE;
	m_show_judge_name = FALSE;
	m_show_jump_ht = FALSE;
	m_show_location = FALSE;
	m_show_stat_name = FALSE;
	m_show_stat_no = FALSE;
	m_show_subclass = FALSE;
	m_show_xy_loc = FALSE;
	m_final_score = FALSE;
	m_judge_sign = FALSE;
	m_time = FALSE;
	m_show_organization = FALSE;
	//}}AFX_DATA_INIT
	this->m_set_default = false;
}


void ScoreSheetPrefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScoreSheetPrefDlg)
	DDX_Check(pDX, IDC_AKC_NUMBER, m_show_akc);
	DDX_Check(pDX, IDC_ARM_BAND, m_show_arm_band);
	DDX_Check(pDX, IDC_BREED, m_show_breed);
	DDX_Check(pDX, IDC_CLASS, m_show_class);
	DDX_Check(pDX, IDC_COMP_NAME, m_show_comp_name);
	DDX_Check(pDX, IDC_COURSE_INFO_LIST, m_show_course_info);
	DDX_Check(pDX, IDC_DATE, m_show_date);
	DDX_Check(pDX, IDC_JUDGE_NAME, m_show_judge_name);
	DDX_Check(pDX, IDC_JUMP_HT, m_show_jump_ht);
	DDX_Check(pDX, IDC_LOCATION, m_show_location);
	DDX_Check(pDX, IDC_STAT_NAME, m_show_stat_name);
	DDX_Check(pDX, IDC_STAT_NUMBER, m_show_stat_no);
	DDX_Check(pDX, IDC_SUBCLASS, m_show_subclass);
	DDX_Check(pDX, IDC_XY_LOCATION, m_show_xy_loc);
	DDX_Check(pDX, IDC_FINAL_SCORE, m_final_score);
	DDX_Check(pDX, IDC_JUDGE_SIGN, m_judge_sign);
	DDX_Check(pDX, IDC_TIME, m_time);
	DDX_Check(pDX, IDC_ORGANIZE, m_show_organization);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScoreSheetPrefDlg, CDialog)
	//{{AFX_MSG_MAP(ScoreSheetPrefDlg)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_COURSE_INFO_LIST, OnCourseInfoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ScoreSheetPrefDlg message handlers

void ScoreSheetPrefDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_default = true;
	this->OnOK();
}

void ScoreSheetPrefDlg::OnCourseInfoList() 
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
