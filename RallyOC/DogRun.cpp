// DogRun.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DogRun.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DogRunDoc.h"
#include "DogRunView.h"
#include "Splash.h"
#include "RegisterDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
bool g_convert_course;

/////////////////////////////////////////////////////////////////////////////
// CDogRunApp

BEGIN_MESSAGE_MAP(CDogRunApp, CWinApp)
	//{{AFX_MSG_MAP(CDogRunApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_AGILITY_BAR, OnViewAgilityBar)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDogRunApp construction

CDogRunApp::CDogRunApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDogRunApp object

CDogRunApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDogRunApp initialization

BOOL CDogRunApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	AfxInitRichEdit( );
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("All Natural Software"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
// registration and demo testing	
	RegisterDlg dlgReg;
	this->m_dead_flag = dlgReg.Check();

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DOGRUNTYPE,
		RUNTIME_CLASS(CDogRunDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDogRunView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;

	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	CRect frame_rect;
	pMainFrame->GetClientRect(&frame_rect);
	g_convert_course = false; // set to false
	RallyListDlg *p_rally_list_Dialog ;
	p_rally_list_Dialog  = new RallyListDlg();
	if(p_rally_list_Dialog != NULL) {
		BOOL ret = p_rally_list_Dialog->Create(IDD_RALLY_LIST,m_pMainWnd);
		if(!ret)   //Create failed.
		AfxMessageBox("Error creating Dialog");
		CRect dialog_rect;
		p_rally_list_Dialog->GetClientRect(&dialog_rect);
		p_rally_list_Dialog->MoveWindow(frame_rect.right-80,60,dialog_rect.Width(),dialog_rect.Height(),FALSE);
		

		this->m_rally_list_Dialog = p_rally_list_Dialog;
	}
	else {
		AfxMessageBox("Error Rally List  Dialog Object");
	}

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	this->m_cutting = false;
	this->m_pcutting_view = NULL;

	// The main window has been initialized, so show and update it.
	m_nCmdShow = SW_SHOWMAXIMIZED; // I want the window to always be maximized.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();



	if (DEMO_TEST) {
		dlgReg.DoModal();
	}

	if (this->m_view_rally_dialog && this->m_dead_flag != TIME_EXPIRED) {
		p_rally_list_Dialog->ShowWindow(SW_SHOW);
	}
	else {
		p_rally_list_Dialog->ShowWindow(SW_HIDE);
	}
	return TRUE;
}

void CDogRunApp::AddObjectToClipboard(CObject* rally_to_clip) {	

	this->m_clipBoard.AddTail(rally_to_clip);

}
void CDogRunApp::RemoveAllObjectsFromClipboard(void) {
	CObject* pObjectItemInlist;
	POSITION pos, pos2;

	for( pos = this->m_clipBoard.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pObjectItemInlist = this->m_clipBoard.GetNext(pos);
		this->m_clipBoard.RemoveAt(pos2);
		delete pObjectItemInlist;
	}	

}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_reg_detail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_REG_DETAIL, m_reg_detail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDogRunApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDogRunApp message handlers


void CDogRunApp::OnViewAgilityBar() 
{
	// TODO: Add your command handler code here
	
}

BOOL CDogRunApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;
	
	return CWinApp::PreTranslateMessage(pMsg);
}

void CAboutDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	CString reg_detail, user_name, prod_id, act_key, Version;
	Version.LoadString(IDS_RALLYVER);	

	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
	if (pApp->m_dead_flag == REGISTERED) {
		user_name = pApp->GetProfileString(Version,"User Name",NULL);
		act_key = pApp->GetProfileString(Version,"Act Key",NULL);
		prod_id = pApp->GetProfileString(Version,"Prod ID",NULL);
		reg_detail.Format("User Name:%s\n\rProduct ID:%s\n\rActivation Key:%s\n\r",user_name,prod_id,act_key);
		this->m_reg_detail.SetWindowText(reg_detail);

	}
	if (pApp->m_dead_flag == PRODID_GEN) {
		user_name = pApp->GetProfileString(Version,"User Name",NULL);
		prod_id = pApp->GetProfileString(Version,"Prod ID",NULL);
		reg_detail.Format("User Name:%s\n\rProduct ID:%s\n\rActivation Key:Pending\n\r",user_name,prod_id);
		this->m_reg_detail.SetWindowText(reg_detail);

	}

	if (pApp->m_dead_flag == DEMO_PERIOD)this->m_reg_detail.SetWindowText("FULL FEATURE DEMO VERSION");
	if (pApp->m_dead_flag == TIME_EXPIRED)this->m_reg_detail.SetWindowText("READ ONLY VERSION");

}

int CDogRunApp::GetCurrentColorMode(void) {
	PRINTDLG pd;
	int current_mode = NULL;
   pd.lStructSize=(DWORD)sizeof(PRINTDLG);
   BOOL bRet=GetPrinterDeviceDefaults(&pd);
   if(bRet)
   {
      // protect memory handle with ::GlobalLock and ::GlobalUnlock
		DEVMODE FAR *pDevMode=(DEVMODE FAR *)::GlobalLock(m_hDevMode);
		// get the current mode
		current_mode = pDevMode->dmColor;
		::GlobalUnlock(m_hDevMode);
	  
   }
   return current_mode;
}
int CDogRunApp::SetCurrentColorMode(int color_mode) {
	PRINTDLG pd;
	int current_mode = NULL;
   pd.lStructSize=(DWORD)sizeof(PRINTDLG);
   BOOL bRet=GetPrinterDeviceDefaults(&pd);
   if(bRet)
   {
      // protect memory handle with ::GlobalLock and ::GlobalUnlock
		DEVMODE FAR *pDevMode=(DEVMODE FAR *)::GlobalLock(m_hDevMode);
		// set set the color mode
		pDevMode->dmColor = color_mode;
		::GlobalUnlock(m_hDevMode);
	  
   }
   return current_mode;
}

int CDogRunApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (this->m_rally_list_Dialog) {
		this->m_rally_list_Dialog->DestroyWindow();
		delete this->m_rally_list_Dialog;
	}
		
	return CWinApp::ExitInstance();
}

