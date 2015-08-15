// TextPrefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "TextPrefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TextPrefDlg dialog


TextPrefDlg::TextPrefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TextPrefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TextPrefDlg)
	m_outline_rect = TRUE;
	//}}AFX_DATA_INIT
}


void TextPrefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TextPrefDlg)
	DDX_Control(pDX, ID_DEFAULT, m_default_button);
	DDX_Control(pDX, IDC_SHOW_COLOR, m_show_color);
	DDX_Control(pDX, IDC_TEXT_FONT, m_text_display);
	DDX_Check(pDX, IDC_OUT_RECT, m_outline_rect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TextPrefDlg, CDialog)
	//{{AFX_MSG_MAP(TextPrefDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SET_COLOR, OnSetColor)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_CHANGE_FONT, OnChangeFont)
	ON_BN_CLICKED(IDC_OUT_RECT, OnOutRect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TextPrefDlg message handlers

int TextPrefDlg::DoModal(BOOL out_line_rect, LOGFONT *default_font, COLORREF default_text_color, COLORREF default_rect_color, bool default_case) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_change_font = false;
	this->m_default_font = *default_font;
	this->m_font_color = default_text_color;
	this->m_outline_rect_color = default_rect_color;
	this->m_outline_rect = out_line_rect;
	this->m_set_default = false; 
	this->m_default_case = default_case; // also means that you are changing station list and course information fonts	
	return CDialog::DoModal();
}

void TextPrefDlg::OnPaint() 
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

	if (this->m_default_case) {
		CBrush br1, *pbrOld;
		br1.CreateSolidBrush(this->m_outline_rect_color);
		pbrOld = dc.SelectObject(&br1);
		this->m_show_color.GetWindowRect(&ctrl_rect);
		this->m_show_color.GetWindowRect(&ctrl_client_rect);
		draw_rect.top = ctrl_rect.top - wind_rect.top - (wind_rect.Height() - wind_client_rect.Height());
		draw_rect.left = ctrl_rect.left - wind_rect.left; //- (wind_rect.Width() - wind_client_rect.Width());
		draw_rect.bottom = draw_rect.top + ctrl_client_rect.Height();
		draw_rect.right = draw_rect.left + ctrl_client_rect.Width();
		dc.Rectangle(&draw_rect);
		dc.SelectObject(pbrOld);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void TextPrefDlg::OnSetColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog color_dialog(this->m_outline_rect_color,CC_FULLOPEN,this);
	color_dialog.DoModal();
	this->m_outline_rect_color = color_dialog.GetColor();
	this->Invalidate(TRUE);	
	this->BringWindowToTop();
}

void TextPrefDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_default = true;
	this->OnOK();
}

void TextPrefDlg::OnChangeFont() 
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

BOOL TextPrefDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CWnd *temp_wnd;
	// TODO: Add extra initialization here
	if (this->m_default_case) {
		this->m_default_button.ShowWindow(SW_SHOW);
	}
	else {
		this->m_default_button.ShowWindow(SW_HIDE);
		this->SetWindowText("TEXT PROPERTIES");
		temp_wnd = this->GetDlgItem(IDC_OUT_RECT);
		temp_wnd->ShowWindow(SW_HIDE);
		temp_wnd = this->GetDlgItem(IDC_SHOW_COLOR);
		temp_wnd->ShowWindow(SW_HIDE);
		temp_wnd = this->GetDlgItem(IDC_SET_COLOR);
		temp_wnd->ShowWindow(SW_HIDE);

	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void TextPrefDlg::OnOutRect() 
{
	// TODO: Add your control notification handler code here

}
