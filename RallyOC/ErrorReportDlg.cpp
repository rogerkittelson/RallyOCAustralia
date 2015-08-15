// ErrorReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "ErrorReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ErrorReportDlg dialog


ErrorReportDlg::ErrorReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ErrorReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ErrorReportDlg)
	m_error_report = _T("");
	//}}AFX_DATA_INIT
}


void ErrorReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ErrorReportDlg)
	DDX_Text(pDX, IDC_ERROR_REPORT, m_error_report);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ErrorReportDlg, CDialog)
	//{{AFX_MSG_MAP(ErrorReportDlg)
	ON_BN_CLICKED(IDPRINT, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ErrorReportDlg message handlers

void ErrorReportDlg::OnPrint() 
{
	// TODO: Add your control notification handler code here
	CPrintDialog printdlg(FALSE);
	CDC dc;
	DOCINFO di;
	BOOL not_done = true;
	TEXTMETRIC tm;
	CFont list_font;
	CFont* def_font;

	CString out_string, temp_error;
	int find_return, line_number, line_height;
	int response = printdlg.DoModal();
	if (response == IDOK) {
		temp_error = this->m_error_report;
		dc.Attach (printdlg.GetPrinterDC ());
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		di.lpszDocName = "Printing RallyOC Error Report";
		dc.GetTextMetrics(&tm);
		line_height = tm.tmHeight;
		dc.StartDoc (&di);
		dc.StartPage ();
		VERIFY(list_font.CreateFont(
		   0,                        // nHeight
		   0,                         // nWidth
		   0,                         // nEscapement
		   0,                         // nOrientation
		   FW_NORMAL,                 // nWeight
		   FALSE,                     // bItalic
		   FALSE,                     // bUnderline
		   0,                         // cStrikeOut
		   ANSI_CHARSET,              // nCharSet
		   OUT_DEFAULT_PRECIS,        // nOutPrecision
		   CLIP_DEFAULT_PRECIS,       // nClipPrecision
		   DEFAULT_QUALITY,           // nQuality
		   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		   "Arial"));    
		def_font = dc.SelectObject(&list_font);		
		
		line_number = 50;
		dc.TextOut(50,line_number,this->m_course_info);
		line_number += 2 * line_height;
		while(not_done) {
			find_return = temp_error.Find("\r\n",0);
			if (find_return == -1) {
				out_string = temp_error;
				not_done = false;
			}
			else {
				out_string = temp_error.Left(find_return);
				temp_error.Delete(0,find_return + 2);
			}
			dc.TextOut(30,line_number,out_string);
			line_number += line_height;
			
		}
		dc.SelectObject(def_font);

		dc.EndPage();
		dc.EndDoc();

	}



}
