// AuthorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "AuthorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AuthorDlg dialog


AuthorDlg::AuthorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AuthorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AuthorDlg)
	m_type = AKC_COURSE;
	m_class = NOVICE;
	m_sub_class =CLASS_A;
	m_judge_name = _T("");
	m_grid_color = GRID_BLACK;
	m_list_placement = LIST_CUSTOM;
	m_auto_add = FALSE;
	m_show_path = FALSE;
	m_grid_spacing = _T("5");
	m_judge_or_instruct = _T("");
	m_ring_lenght = _T("50");
	m_ring_width = _T("50");
	m_size_to_screen = FALSE;
	m_show_class = FALSE;
	m_show_comp_name = FALSE;
	m_show_date = FALSE;
	m_show_judge = FALSE;
	m_show_location = FALSE;
	m_show_subclass = FALSE;
	m_organization = _T("");
	m_show_organization = FALSE;
	//}}AFX_DATA_INIT
	this->m_set_default = this->m_change_font = false;
}


void AuthorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AuthorDlg)
	DDX_Control(pDX, IDC_COURSE_FONT, m_text_display);
	DDX_Radio(pDX, IDC_TYPE_AKC, m_type);
	DDX_Radio(pDX, IDC_NOVICE, m_class);
	DDX_Radio(pDX, IDC_CLASS_A, m_sub_class);
	DDX_Text(pDX, IDC_JUDGE, m_judge_name);
	DDX_Radio(pDX, IDC_LINES_BLACK, m_grid_color);
	DDX_Radio(pDX, IDC_LIST_BOTTOM, m_list_placement);
	DDX_Check(pDX, IDC_AUTO_ADD, m_auto_add);
	DDX_Check(pDX, IDC_COURSE_PATH, m_show_path);
	DDX_Text(pDX, IDC_GRID_SPACEING, m_grid_spacing);
	DDX_Text(pDX, IDC_JUDGE_INST, m_judge_or_instruct);
	DDX_Text(pDX, IDC_RING_LENGHT, m_ring_lenght);
	DDX_Text(pDX, IDC_RING_WIDTH, m_ring_width);
	DDX_Check(pDX, IDC_SIZE_TO_SCREEN, m_size_to_screen);
	DDX_Check(pDX, IDC_CLASS, m_show_class);
	DDX_Check(pDX, IDC_COMP_NAME, m_show_comp_name);
	DDX_Check(pDX, IDC_DATE, m_show_date);
	DDX_Check(pDX, IDC_JUDGE_NAME, m_show_judge);
	DDX_Check(pDX, IDC_SH_LOCATION, m_show_location);
	DDX_Check(pDX, IDC_SUBCLASS, m_show_subclass);
	DDX_Text(pDX, IDC_ORGANIZATION, m_organization);
	DDX_Check(pDX, IDC_ORGANIZE, m_show_organization);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AuthorDlg, CDialog)
	//{{AFX_MSG_MAP(AuthorDlg)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TYPE_AKC, OnTypeAkc)
	ON_BN_CLICKED(IDC_TYPE_APDT, OnTypeApdt)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHANGE_FONT, OnChangeFont)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AuthorDlg message handlers

void AuthorDlg::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	CDialog::OnOK();
}

void AuthorDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	this->m_set_default = true;
	CDialog::OnOK();	
}

void AuthorDlg::OnTypeAkc() 
{
	// TODO: Add your control notification handler code here
	CWnd *novice, *advanced, *excellent;
	novice = this->GetDlgItem(IDC_NOVICE);
	novice->SetWindowText("Novice:");
	advanced = this->GetDlgItem(IDC_ADVANCED);
	advanced->SetWindowText("Advanced:");
	excellent = this->GetDlgItem(IDC_EXCELLENT);
	excellent->SetWindowText("Excellent:");	
}

void AuthorDlg::OnTypeApdt() 
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

//		CDC dc;
//		dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
//		LONG yPerInch = dc.GetDeviceCaps(LOGPIXELSY);

void AuthorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (this->m_type == AKC_COURSE) {
		this->OnTypeAkc();
	} 
	else {
		this->OnTypeApdt();
	}	
}

void AuthorDlg::OnChangeFont() 
{
	// TODO: Add your control notification handler code here
	LOGFONT lf;

	CFontDialog dlg(&this->m_default_font);
	dlg.m_cf.rgbColors = this->m_font_color;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);

		CDC *hDC;
		hDC = this->GetDC();

		this->m_point_size = dlg.GetSize()/10;
		this->m_font_color = dlg.GetColor();
		this->UpdateData(FALSE);
		this->m_default_font = lf;
		this->m_change_font = true;
		this->Invalidate(TRUE);
	}
	this->BringWindowToTop();
}

void AuthorDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CFont text_font, *old_font;
	text_font.CreateFontIndirect(&this->m_default_font);
	old_font = dc.SelectObject(&text_font);
	COLORREF old_color = dc.SetTextColor(this->m_font_color);
	CRect ctrl_rect, wind_rect, draw_rect, ctrl_client_rect, wind_client_rect;
	this->GetWindowRect(&wind_rect);
	this->GetClientRect(&wind_client_rect);
	this->m_text_display.GetWindowRect(&ctrl_rect);
	this->m_text_display.GetWindowRect(&ctrl_client_rect);
	draw_rect.top = ctrl_rect.top - wind_rect.top - (wind_rect.Height() - wind_client_rect.Height());
	draw_rect.left = ctrl_rect.left - wind_rect.left; //- (wind_rect.Width() - wind_client_rect.Width());
	draw_rect.bottom = draw_rect.top + ctrl_client_rect.Height();
	draw_rect.right = draw_rect.left + ctrl_client_rect.Width();
	dc.DrawText(this->m_default_font.lfFaceName,&draw_rect,DT_LEFT);
	dc.SelectObject(old_font);
	// Do not call CDialog::OnPaint() for painting messages
}
