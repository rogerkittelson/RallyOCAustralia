// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CScrollView* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_edit_text = _T("");
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	// Instantiate and initialize the background brush to white.
	m_pEditBkBrush = new CBrush(RGB(255, 255, 255));

	m_nID = CEditDlg::IDD;
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Control(pDX, IDC_EDIT_TEXT, m_ctrl_edit);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_edit_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_SIZING( )
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

BOOL CEditDlg::Create(LOGFONT *p_log_font, TextObj *p_text_obj) 
{
	// TODO: Add your specialized code here and/or call the base class

	this->m_my_font = p_text_obj->GetMyFontObject();
//	p_set_font->GetLogFont(&lf);
	m_font.CreateFontIndirect(p_log_font);
	this->mp_text_obj = p_text_obj;
	return CDialog::Create(m_nID, m_pParent);
}

BOOL CEditDlg::Create(MyFont *p_set_font, CRect *p_dialog_rect, CString *p_display_text)
{
	LOGFONT lf;
	this->m_my_font = p_set_font;
	p_set_font->GetLogFont(&lf);
	m_font.CreateFontIndirect(&lf);
	this->m_edit_text = *p_display_text;
	return CDialog::Create(m_nID, m_pParent);
}
BOOL CEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	this->m_intial_rect.SetRectEmpty();
	this->m_current_rect.SetRectEmpty();
	GetDlgItem(IDC_EDIT_TEXT)->SetFont(&m_font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	CRect window_rect, control_rect;
	CEdit* pBoxOne;
	this->GetWindowRect(&window_rect);

	pBoxOne = (CEdit*) this->GetDlgItem(IDC_EDIT_TEXT);
	if (pBoxOne != NULL) {
		pBoxOne->GetWindowRect(&control_rect);
		this->SetIntialRect(&window_rect);
		pBoxOne->MoveWindow(0,0,window_rect.right - window_rect.left,window_rect.bottom - window_rect.top,TRUE);	
//		pBoxOne->MoveWindow(0,0,cx,cy,TRUE);	
		this->CalculateOffSetsForCorner();
	}

}

void CEditDlg::ChangeFont(LOGFONT *p_log_font, COLORREF new_color)
{
	
	CEdit* pBoxOne;
	CRect inval_rect;	
	this->m_font.DeleteObject();
	m_font.CreateFontIndirect(p_log_font);
	pBoxOne = (CEdit*) this->GetDlgItem(IDC_EDIT_TEXT);
	GetDlgItem(IDC_EDIT_TEXT)->SetFont(&m_font);
	this->m_my_font->SetColorReference(new_color);
	this->m_my_font->SetFont(p_log_font);
	this->mp_text_obj->SetLogFont(p_log_font);
	this->mp_text_obj->SetTextColor(new_color);
	CPoint sp = this->m_pParent->GetScrollPosition();
	inval_rect = this->mp_text_obj->GetInvalRect();
	OffsetRect(&inval_rect,-sp.x, -sp.y);
	this->m_pParent->InvalidateRect(&inval_rect);
}

void CEditDlg::SetIntialRect(RECT *intial_rect)
{
	if (this->m_intial_rect.IsRectEmpty()) 
		this->m_intial_rect = *intial_rect;
}

void CEditDlg::MoveTextObjectRect()
{
	CRect text_rect, inval_rect, intial_rect;
	CPoint os_top_left, os_bottom_right, top_left_text, bottom_right_text;
	CPoint sp = this->m_pParent->GetScrollPosition();
	intial_rect = this->mp_text_obj->GetInvalRect();
	OffsetRect(&intial_rect,-sp.x, -sp.y);
	this->m_pParent->InvalidateRect(&intial_rect);

}

void CEditDlg::CalculateOffSetsForCorner(void)
{
	CRect text_rect, inval_rect, intial_rect, ctrl_rect;
	CPoint os_top_left, os_bottom_right, top_left_text, bottom_right_text;
	CPoint sp = this->m_pParent->GetScrollPosition();
	intial_rect = this->mp_text_obj->GetInvalRect();
	CEdit* pBoxOne;
	pBoxOne = (CEdit*) this->GetDlgItem(IDC_EDIT_TEXT);

	OffsetRect(&intial_rect,-sp.x, -sp.y);
	this->m_pParent->InvalidateRect(&intial_rect,TRUE);

	this->GetWindowRect(&this->m_current_rect);
	pBoxOne->GetWindowRect(&ctrl_rect);
	int wind_rect_w, ctrl_rect_w;
	wind_rect_w = this->m_current_rect.Width();
	ctrl_rect_w = ctrl_rect.Width();
	int wind_rect_h, ctrl_rect_h;
	wind_rect_h = this->m_current_rect.Height();
	ctrl_rect_h = ctrl_rect.Height();

	this->mp_text_obj->GetDisplayTextRect(&text_rect);
	top_left_text = text_rect.TopLeft();
//	bottom_right_text = text_rect.BottomRight();
	os_top_left.x = this->m_current_rect.left - this->m_intial_rect.left;
	os_top_left.y = this->m_current_rect.top - this->m_intial_rect.top ;
	os_bottom_right.x = this->m_current_rect.right - this->m_intial_rect.right;
	os_bottom_right.y = this->m_current_rect.bottom - this->m_intial_rect.bottom;
	
	top_left_text.Offset(os_top_left);
//	bottom_right_text.Offset(os_bottom_right);
	bottom_right_text.x = top_left_text.x + ctrl_rect_w;
	bottom_right_text.y = top_left_text.y + ctrl_rect_h;
	text_rect.SetRect(top_left_text, bottom_right_text);

	int text_rect_w, text_rect_h;
	text_rect_w = text_rect.Width();
	text_rect_h = text_rect.Height();

	
	this->mp_text_obj->SetDisplayTextRect(&text_rect);
	this->m_intial_rect = this->m_current_rect;

	inval_rect = this->mp_text_obj->GetInvalRect();
	top_left_text = inval_rect.TopLeft();
	bottom_right_text = inval_rect.BottomRight();
	top_left_text.Offset(os_top_left);
	bottom_right_text.Offset(os_bottom_right);
	inval_rect.SetRect(top_left_text, bottom_right_text);
	
	this->mp_text_obj->SetInvalRect(&inval_rect);
	inval_rect = this->mp_text_obj->GetInvalRect();
	OffsetRect(&inval_rect,-sp.x, -sp.y);
	this->m_pParent->InvalidateRect(&inval_rect);

}

void CEditDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	this->SetIntialRect(pRect);
}

HBRUSH CEditDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	switch (nCtlColor) {
	case CTLCOLOR_EDIT:
	case CTLCOLOR_MSGBOX:
	  // Set color to green on white and return the background brush.
		pDC->SetTextColor(this->m_my_font->GetColorReference());
		pDC->SetBkColor(RGB(255, 255, 255));
//		this->UpdateData(TRUE);
//		this->mp_text_obj->SetDisplayText(&this->m_edit_text);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());

	default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}


void CEditDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	// Free the space allocated for the background brush
	delete m_pEditBkBrush;
	
}


void CEditDlg::OnChangeEditText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
		CPoint sp = this->m_pParent->GetScrollPosition();
	// TODO: Add your control notification handler code here
		this->UpdateData(TRUE);
		this->mp_text_obj->SetDisplayText(&this->m_edit_text);
		CRect inval_rect;
		inval_rect = this->mp_text_obj->GetInvalRect();
		OffsetRect(&inval_rect,-sp.x, -sp.y);
		
		this->m_pParent->InvalidateRect(inval_rect,TRUE);
		
}

void CEditDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	CRect wind_rect;
	this->GetWindowRect(&wind_rect);
	// tryied to use the following to track window to text rect
	// problems were with scrolling (Fixed this) and fit-to-screen mode
//	if (!this->m_intial_rect.IsRectEmpty()) {
//		this->CalculateOffSetsForCorner();
//	}

	if (wind_rect.Width() == this->m_intial_rect.Width() && wind_rect.Height() == this->m_intial_rect.Height()) {
		this->m_intial_rect = wind_rect;
	}

}

