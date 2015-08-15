// RegDialog.cpp : implementation file

///////////////////////////////////////////////////////////
//														 //
// 1. Insert CRegDialog class to project                 //
//														 //
// 2. Add to mainApp.cpp :								 //
//														 //	
//		#include "RegDialog.h"							 //
//														 //
// 3. Insert function call in mainApp.cpp				 //
//														 //
//		BOOL CMy123App::InitInstance()					 //
//		{												 //
//		      ...                                        //
//			SetRegistryKey(_T("MyCompany"));             //
//			CRegDialog RegistrationDialog;				 //
//			RegistrationDialog.Check();					 //	
//			  ...										 //
//														 //
//		...}											 //
//														 //
// 4. Set App Specific Data in RegDialog.cpp			 //
//														 //
//														 //
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////      App Specific Data !!!    ///////////////////

int DaysLimit = 30;
long KeyCode  = 12345678;
CString Version = "1.1";
//////////////////////////////////////////////////////////////////////	


CRegDialog::CRegDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDialog)
	//}}AFX_DATA_INIT
}


void CRegDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDialog)
	DDX_Control(pDX, IDC_EDIT, m_entercode);
	DDX_Control(pDX, IDC_STATIC1, m_stat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDialog, CDialog)
	//{{AFX_MSG_MAP(CRegDialog)
	ON_BN_CLICKED(IDC_ASKCODE, OnAskcode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDialog message handlers

BOOL CRegDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CWinApp* pApp = AfxGetApp();

	int Run = pApp->GetProfileInt(Version,"Times run",0);
	Run++;
	pApp->WriteProfileInt(Version,"Times run",Run);

	CTime curTime = CTime::GetCurrentTime();
	int curYear = curTime.GetYear();
	int curMonth = curTime.GetMonth();
	int curDay = curTime.GetDay();
	int firYear =pApp->GetProfileInt(Version,"Run year",0);
	int firMonth =pApp->GetProfileInt(Version,"Run month",0);
	int firDay =pApp->GetProfileInt(Version,"Run day",0);

	int firAbs = (firYear-2000)*365+(firMonth-1)*30+(firDay);
	int curAbs = (curYear-2000)*365+(curMonth-1)*30+(curDay);
	int DaysToUse = DaysLimit-(curAbs-firAbs);
	if (DaysToUse > 0)
		{
		CString Str;
		Str.Format("%d  Days left to use!\n\nTo register press Register Button and you will receive Registration Code. Type it bellow and press OK",DaysToUse);
		m_stat.SetWindowText(Str);
		}
	else
		{
		m_stat.SetWindowText("Sorry, trial period is finished!\n\nTo register press Register button and you will receive Registration Code. Type it bellow and press OK.");
		int DeadFlag = 1;
		pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
		}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegDialog::OnAskcode() 
{
	AfxMessageBox("Registration! Go to internet link, send mail or WinExec(something.exe)");	
}

void CRegDialog::OnOK() 
{
	CDialog::OnOK();

	CWinApp* pApp = AfxGetApp();	
	CString TempStr;
	m_entercode.GetWindowText(TempStr);
	long enteredCode = atol(TempStr);

	pApp->WriteProfileInt(Version,"Code",enteredCode);

	if (KeyCode == enteredCode)
		AfxMessageBox("Thank you for registering!",MB_OK);
	else
		AfxMessageBox("Registration Code incorrect!",MB_OK);

}


void CRegDialog::Check()
{

	CWinApp* pApp = AfxGetApp();
	CString strStarted = pApp->GetProfileString(Version,"Started");
	if (strStarted == "")   //First Start
	{
		pApp->WriteProfileString(Version,"Started","Yes");
		
		CTime theTime = CTime::GetCurrentTime();
		int Year = theTime.GetYear();
		int Month = theTime.GetMonth();
		int Day = theTime.GetDay();
		int Code = 0;
		int DeadFlag = 0;
		int Run = 1;
		pApp->WriteProfileInt(Version,"Run year",Year);
		pApp->WriteProfileInt(Version,"Run month",Month);
		pApp->WriteProfileInt(Version,"Run day",Day);
		pApp->WriteProfileInt(Version,"Times run",Run);
		pApp->WriteProfileInt(Version,"Code",Code);
		pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
	}
	else //Not First Start
	{
		long askCode;
		int DeadFlag;
		askCode = pApp->GetProfileInt(Version,"Code",0);
		if (KeyCode!=askCode)
			{	
				CRegDialog dlgReg;
				dlgReg.DoModal();
				askCode = pApp->GetProfileInt(Version,"Code",0);
				if (KeyCode!=askCode)
					{
						DeadFlag = pApp->GetProfileInt(Version,"Dead Flag",0);
						if (DeadFlag==1)
							exit(0);
					}
			}
		else
			{
				DeadFlag=0;
				pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
			}

	
	}

}
