// AuthorPref.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "AuthorPref.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AuthorPref dialog


AuthorPref::AuthorPref(CWnd* pParent /*=NULL*/)
	: CDialog(AuthorPref::IDD, pParent)
{
	//{{AFX_DATA_INIT(AuthorPref)
	m_line_type = LINE;
	m_line_thickness = _T("");
	m_move_arrow = FALSE;
	m_line_style = -1;
	//}}AFX_DATA_INIT
	this->m_set_default = false;
}


void AuthorPref::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AuthorPref)
	DDX_Control(pDX, ID_DEFAULT, m_default_button);
	DDX_Control(pDX, IDC_SHOW_COLOR, m_show_color);
	DDX_Radio(pDX, IDC_LINE_ST, m_line_type);
	DDX_Text(pDX, IDC_LINE_THICK, m_line_thickness);
	DDX_Check(pDX, IDC_MOVE_ARROWS, m_move_arrow);
	DDX_CBIndex(pDX, IDC_LINE_STYLE, m_line_style);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AuthorPref, CDialog)
	//{{AFX_MSG_MAP(AuthorPref)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SET_COLOR, OnSetColor)
	ON_BN_CLICKED(ID_DEFAULT, OnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AuthorPref message handlers

int AuthorPref::DoModal(LOGPEN *default_pen, int default_arrow, bool scribble) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_log_pen = *default_pen;
	this->m_arrow_type = default_arrow;
	this->m_scribble = scribble;
	this->m_line_style = default_pen->lopnStyle;
	return CDialog::DoModal();
}

BOOL AuthorPref::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_line_thickness.Format("%d",this->m_log_pen.lopnWidth.x);
	this->m_line_type = this->m_arrow_type;

	if (this->m_scribble) {
		CWnd *temp_Wnd;
		temp_Wnd = this->GetDlgItem(IDC_LINE_STYLE);
		temp_Wnd->ShowWindow(SW_HIDE);
		temp_Wnd = this->GetDlgItem(IDC_MOVE_ARROWS);
		temp_Wnd->ShowWindow(SW_HIDE);
		temp_Wnd = this->GetDlgItem(IDC_LINE_ST);
		temp_Wnd->ShowWindow(SW_HIDE);
		temp_Wnd = this->GetDlgItem(IDC_LINE_CURVE);
		temp_Wnd->ShowWindow(SW_HIDE);
		temp_Wnd = this->GetDlgItem(IDC_STATIC_TYPE);
		temp_Wnd->ShowWindow(SW_HIDE);
		this->m_default_button.ShowWindow(SW_HIDE);
		this->SetWindowText("Line Properties");
	}
	this->UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void AuthorPref::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

void AuthorPref::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBrush br1, *pbrOld;
	br1.CreateSolidBrush(this->m_log_pen.lopnColor);
	pbrOld = dc.SelectObject(&br1);
	CRect ctrl_rect, wind_rect, draw_rect, ctrl_client_rect, wind_client_rect;
	this->GetWindowRect(&wind_rect);
	this->GetClientRect(&wind_client_rect);
	this->m_show_color.GetWindowRect(&ctrl_rect);
	this->m_show_color.GetWindowRect(&ctrl_client_rect);
	draw_rect.top = ctrl_rect.top - wind_rect.top - (wind_rect.Height() - wind_client_rect.Height());
	draw_rect.left = ctrl_rect.left - wind_rect.left; //- (wind_rect.Width() - wind_client_rect.Width());
	draw_rect.bottom = draw_rect.top + ctrl_client_rect.Height();
	draw_rect.right = draw_rect.left + ctrl_client_rect.Width();
	dc.Rectangle(&draw_rect);
	dc.SelectObject(pbrOld);

	// Do not call CDialog::OnPaint() for painting messages
}

void AuthorPref::OnSetColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog color_dialog(this->m_log_pen.lopnColor,CC_FULLOPEN,this);
	color_dialog.DoModal();
	this->m_log_pen.lopnColor = color_dialog.GetColor();
	this->Invalidate(TRUE);
	this->BringWindowToTop();

}

void AuthorPref::OnDefault() 
{
	// TODO: Add your control notification handler code here
	this->m_set_default = true;
	this->OnOK();
}

void AuthorPref::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	CDialog::OnOK();

}
