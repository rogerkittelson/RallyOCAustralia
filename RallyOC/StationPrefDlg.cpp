// StationPrefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "StationPrefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StationPrefDlg dialog


StationPrefDlg::StationPrefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StationPrefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StationPrefDlg)
	m_cone_placement = -1;
	m_number_honor = FALSE;
	m_do_rotate_text = FALSE;
	m_stat_desc = -1;
	m_loc_station_number = -1;
	m_station_size = -1;
	m_actual_size = _T("");
	//}}AFX_DATA_INIT
	this->m_set_default = false;
}


void StationPrefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StationPrefDlg)
	DDX_Control(pDX, IDC_CUSTOM_SIZE, m_ctl_actual_size);
	DDX_Control(pDX, IDC_STATION_FONT, m_text_display);
	DDX_Radio(pDX, IDC_CONE_ENTRANCE, m_cone_placement);
	DDX_Check(pDX, IDC_NUM_HONOR, m_number_honor);
	DDX_Check(pDX, IDC_ROTATE_TEXT, m_do_rotate_text);
	DDX_Radio(pDX, IDC_STAT_BOTH, m_stat_desc);
	DDX_Radio(pDX, IDC_TOP_LEFT, m_loc_station_number);
	DDX_Radio(pDX, IDC_SIZE_2, m_station_size);
	DDX_Text(pDX, IDC_CUSTOM_SIZE, m_actual_size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StationPrefDlg, CDialog)
	//{{AFX_MSG_MAP(StationPrefDlg)
	ON_BN_CLICKED(IDC_CHANGE_FONT, OnChangeFont)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_SIZE_2, OnSize2)
	ON_BN_CLICKED(IDC_SIZE_5, OnSize5)
	ON_BN_CLICKED(IDC_SIZE_7, OnSize7)
	ON_BN_CLICKED(IDC_SIZE_CUSTOM, OnSizeCustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StationPrefDlg message handlers

void StationPrefDlg::OnChangeFont() 
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

void StationPrefDlg::OnPaint() 
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

void StationPrefDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_default = true;
	this->OnOK();
}

void StationPrefDlg::OnSize2() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
}

void StationPrefDlg::OnSize5() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
}

void StationPrefDlg::OnSize7() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
}

void StationPrefDlg::OnSizeCustom() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_SHOW);
}

BOOL StationPrefDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (this->m_station_size == TWO_EVEN) this->m_ctl_actual_size.ShowWindow(SW_HIDE);
	else if (this->m_station_size == FIVE_EVEN) this->m_ctl_actual_size.ShowWindow(SW_HIDE);
	else if (this->m_station_size == SEVEN_EVEN) 	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
	else 	this->m_ctl_actual_size.ShowWindow(SW_SHOW);
	CWnd *temp_Wnd;
	temp_Wnd = this->GetDlgItem(IDC_ROTATE_TEXT);
	if (this->m_can_rotate) {
		temp_Wnd->ShowWindow(SW_SHOW);
	}
	else {
		temp_Wnd->ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
