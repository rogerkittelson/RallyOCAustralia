// CourseInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "CourseInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCourseInfoDlg dialog


CCourseInfoDlg::CCourseInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCourseInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCourseInfoDlg)
	m_length = _T("");
	m_width = _T("");
	m_compete = _T("");
	m_judge = _T("");
	m_location = _T("");
	m_grid_spacing = _T("");
	m_date_compete = COleDateTime::GetCurrentTime();
	m_judge_inst = _T("");
	m_class = -1;
	m_sub_class = -1;
	m_type_course = -1;
	m_show_class = FALSE;
	m_show_comp = FALSE;
	m_show_date = FALSE;
	m_show_judge = FALSE;
	m_show_location = FALSE;
	m_show_subclass = FALSE;
	m_organization = _T("");
	m_show_organization = FALSE;
	//}}AFX_DATA_INIT
	set_defaults = false;
}


void CCourseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	double convert;
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCourseInfoDlg)
	if (pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX, IDC_RING_LENGHT, m_length);
		DDX_Text(pDX, IDC_RING_WIDTH, m_width);
		DDX_Text(pDX, IDC_GRID_SPACEING, m_grid_spacing);
		convert = atof(m_length);
//		convert = convert / 0.3;
		m_length.Format("%.1f",convert);
		convert = atof(m_width);
//		convert = convert / 0.3;
		m_width.Format("%.1f",convert);
		convert = atof(m_grid_spacing);
//		convert = convert / 0.3;
		m_grid_spacing.Format("%.1f",convert);
}
	else 
	{
		convert = atof(m_length);
//		convert = convert * 0.3;
		m_length.Format("%.1f",convert);
		convert = atof(m_width);
//		convert = convert * 0.3;
		m_width.Format("%.1f",convert);
		convert = atof(m_grid_spacing);
//		convert = convert * 0.3;
		m_grid_spacing.Format("%.1f",convert);
		DDX_Text(pDX, IDC_RING_LENGHT, m_length);
		DDX_Text(pDX, IDC_RING_WIDTH, m_width);
		DDX_Text(pDX, IDC_GRID_SPACEING, m_grid_spacing);
	}



	DDX_Text(pDX, IDC_COMPETATION, m_compete);
	DDX_Text(pDX, IDC_JUDGE, m_judge);
	DDX_Text(pDX, IDC_LOCATION, m_location);

	DDX_DateTimeCtrl(pDX, IDC_DATECOMPETE, m_date_compete);
	DDX_Text(pDX, IDC_JUDGE_INST, m_judge_inst);
	DDX_Radio(pDX, IDC_NOVICE, m_class);
	DDX_Radio(pDX, IDC_CLASS_A, m_sub_class);
	DDX_Radio(pDX, IDC_TYPE_AKC, m_type_course);
	DDX_Check(pDX, IDC_CLASS, m_show_class);
	DDX_Check(pDX, IDC_COMP_NAME, m_show_comp);
	DDX_Check(pDX, IDC_DATE, m_show_date);
	DDX_Check(pDX, IDC_JUDGE_NAME, m_show_judge);
	DDX_Check(pDX, IDC_SH_LOCATION, m_show_location);
	DDX_Check(pDX, IDC_SUBCLASS, m_show_subclass);
	DDX_Text(pDX, IDC_ORGANIZATION, m_organization);
	DDX_Check(pDX, IDC_ORGANIZE, m_show_organization);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCourseInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CCourseInfoDlg)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_NOVICE, OnNovice)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_EXCELLENT, OnExcellent)
	ON_BN_CLICKED(IDC_TRAINING, OnTraining)
	ON_BN_CLICKED(IDC_MASTER, OnMaster)
	ON_BN_CLICKED(IDC_TYPE_AKC, OnTypeAkc)
	ON_BN_CLICKED(IDC_TYPE_APDT, OnTypeApdt)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCourseInfoDlg message handlers

void CCourseInfoDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CDialog::OnOK();
}

void CCourseInfoDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	set_defaults = true;
	UpdateData(TRUE);
	CDialog::OnOK();	
}

void CCourseInfoDlg::OnNovice() 
{
	// TODO: Add your control notification handler code here
	CWnd *judge_inst_ed;
	judge_inst_ed = this->GetDlgItem(IDC_JUDGE_INST);
	judge_inst_ed->SetWindowText("Judge:");
}

void CCourseInfoDlg::OnAdvanced() 
{
	// TODO: Add your control notification handler code here
	CWnd *judge_inst_ed;
	judge_inst_ed = this->GetDlgItem(IDC_JUDGE_INST);
	judge_inst_ed->SetWindowText("Judge:");
}	


void CCourseInfoDlg::OnExcellent() 
{
	// TODO: Add your control notification handler code here
	CWnd *judge_inst_ed;
	judge_inst_ed = this->GetDlgItem(IDC_JUDGE_INST);
	judge_inst_ed->SetWindowText("Judge:");
}	
void CCourseInfoDlg::OnMaster() 
{
	// TODO: Add your control notification handler code here
	CWnd *judge_inst_ed;
	judge_inst_ed = this->GetDlgItem(IDC_JUDGE_INST);
	judge_inst_ed->SetWindowText("Judge:");
}

void CCourseInfoDlg::OnTraining() 
{
	// TODO: Add your control notification handler code here
	CWnd *judge_inst_ed;
	judge_inst_ed = this->GetDlgItem(IDC_JUDGE_INST);
	judge_inst_ed->SetWindowText("Instructor:");
	
}

void CCourseInfoDlg::OnTypeAkc() 
{
	// TODO: Add your control notification handler code here
	CWnd *novice, *advanced, *excellent, *master;
	novice = this->GetDlgItem(IDC_NOVICE);
	novice->SetWindowText("Novice:");
	advanced = this->GetDlgItem(IDC_ADVANCED);
	advanced->SetWindowText("Advanced:");
	master = this->GetDlgItem(IDC_MASTER);
	master->SetWindowText("Master:");
	excellent = this->GetDlgItem(IDC_EXCELLENT);
	excellent->SetWindowText("Excellent:");		
}

void CCourseInfoDlg::OnTypeApdt() 
{
	// TODO: Add your control notification handler code here
	CWnd *level_one, *level_two, *level_three;
	level_one = this->GetDlgItem(IDC_NOVICE);
	level_one->SetWindowText("Level 1:");
	level_two = this->GetDlgItem(IDC_ADVANCED);
	level_two->SetWindowText("Level 2:");
	level_three = this->GetDlgItem(IDC_EXCELLENT);
	level_three->SetWindowText("Level 3:");	
}

void CCourseInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (this->m_type_course == AKC_COURSE) {
		this->OnTypeAkc();
	} 
	else {
		this->OnTypeApdt();
	}	
}
