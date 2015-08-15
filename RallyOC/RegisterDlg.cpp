// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "RegisterDlg.h"
#include "AddressDlg.h"
#include "url.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RegisterDlg dialog


RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RegisterDlg)
	//}}AFX_DATA_INIT
}


void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RegisterDlg)
	DDX_Control(pDX, IDC_GEN_PROD_ID, m_gen_prod_id);
	DDX_Control(pDX, IDC_ACTKEY_ST, m_actkey_st);
	DDX_Control(pDX, IDC_PRODID_ST, m_prodID_st);
	DDX_Control(pDX, IDPURCHASE, m_purchase);
	DDX_Control(pDX, IDOK, m_register);
	DDX_Control(pDX, IDC_REG_USER, m_user_name);
	DDX_Control(pDX, IDC_ACT_KEY, m_act_key);
	DDX_Control(pDX, IDC_REQ_KEY, m_req_key);
	DDX_Control(pDX, IDC_DEMOMSG, m_stat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialog)
	//{{AFX_MSG_MAP(RegisterDlg)
	ON_BN_CLICKED(IDPURCHASE, OnPurchase)
	ON_BN_CLICKED(IDC_CONTACT, OnContact)
	ON_BN_CLICKED(IDC_GEN_PROD_ID, OnGenProdId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegisterDlg message handlers

BOOL RegisterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here	
	this->DaysLimit = 30;
	Version.LoadString(IDS_RALLYVER);	
	CWinApp* pApp = AfxGetApp();	
	
	int dead_flag;
	dead_flag = pApp->GetProfileInt(Version,"Dead Flag",0);	

//	long long_time;
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
	if (DaysToUse > 0 && dead_flag == DEMO_PERIOD) {
		CString Str;
		Str.Format("%d  Days left to use!\n\rTo register:\n\r1. Enter in your User Name.\n\r2. Press Generate Product ID Button\n\r3. Press Order Form to Print Out the Registration Form.\n\r4. Type Activation Key below when you have recieved it.\n\r5. Press Register Button",DaysToUse);
		m_stat.SetWindowText(Str);
	}
	else if(DaysToUse <= 0 && dead_flag != REGISTERED) {
		m_stat.SetWindowText("Sorry, trial period is finished!\n\rTo register:\n\r1. Enter in your User Name.\n\r2. Press Generate Product ID Button\n\r3. Press Order Form to Print Out the Registration Form.\n\r4. Type Activation Key below when you have recieved it.\n\r5. Press Register Button");
		int DeadFlag = TIME_EXPIRED;
		pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
		CString user_name;
		user_name = pApp->GetProfileString(Version,"User Name",0);
		user_name.TrimRight();
		if (!user_name.IsEmpty()) {
			this->m_user_name.SetWindowText(user_name);
			this->m_actkey_st.ShowWindow(SW_SHOW);
			this->m_act_key.ShowWindow(SW_SHOW);
			CString prod_id;
			prod_id = pApp->GetProfileString(Version,"Prod ID",NULL);
			this->m_req_key.SetWindowText(prod_id);
			this->m_req_key.ShowWindow(SW_SHOW);
			this->m_prodID_st.ShowWindow(SW_SHOW);
		}
	}
	else if (dead_flag == PRODID_GEN) {
		CString Str;
		Str.Format("%d  Days left to use!\n\rTo register:\n\r1. Enter in your User Name.\n\r2. Press Generate Product ID Button\n\r3. Press Order Form to Print Out the Registration Form.\n\r4. Type Activation Key below when you have recieved it.\n\r5. Press Register Button",DaysToUse);
		m_stat.SetWindowText(Str);
		CString user_name;
		user_name = pApp->GetProfileString(Version,"User Name",0);
		this->m_user_name.SetWindowText(user_name);
		

		this->m_actkey_st.ShowWindow(SW_SHOW);
		this->m_act_key.ShowWindow(SW_SHOW);
		CString prod_id;
		prod_id = pApp->GetProfileString(Version,"Prod ID",NULL);
		this->m_req_key.SetWindowText(prod_id);
		this->m_req_key.ShowWindow(SW_SHOW);
		this->m_prodID_st.ShowWindow(SW_SHOW);
	}
	else if (dead_flag == REGISTERED){
		m_stat.SetWindowText("Product is registered.");
		CString activate_key = pApp->GetProfileString(Version,"Act Key",0);
		this->m_act_key.SetWindowText(activate_key);
		this->m_act_key.ShowWindow(SW_SHOW);
		this->m_act_key.SetReadOnly(TRUE);
		this->m_actkey_st.ShowWindow(SW_SHOW);

		this->m_purchase.ShowWindow(SW_HIDE);
		this->m_register.ShowWindow(SW_HIDE);
		this->m_gen_prod_id.ShowWindow(SW_HIDE);

		CString serial_num;
		DWORD dwSerialNumber;
		dwSerialNumber = pApp->GetProfileInt(Version,"Serial",0);
		serial_num.Format("%x",dwSerialNumber);
		this->m_req_key.SetWindowText(serial_num);
		this->m_req_key.ShowWindow(SW_SHOW);
		this->m_prodID_st.ShowWindow(SW_SHOW);
		CString user_name;
		user_name = pApp->GetProfileString(Version,"User Name",0);
		this->m_user_name.SetWindowText(user_name);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int RegisterDlg::Check(void) {
	this->DaysLimit = 30;

	DWORD dwSerialNumber;
	RegisterDlg dlgReg;
//	time_t long_time;	
	CDogRunApp *pApp = (CDogRunApp*)AfxGetApp();	
	Version.LoadString(IDS_RALLYVER);	
	CString strStarted = pApp->GetProfileString(Version,"Started");
	pApp->m_view_rally_dialog= pApp->GetProfileInt(Version,"List Dialog",0);
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
		pApp->WriteProfileInt(Version,"Dead Flag",REGISTERED);
		pApp->WriteProfileInt(Version,"Size",0);
		pApp->WriteProfileInt(Version,"List Dialog",pApp->m_view_rally_dialog);		

		BOOL bSuccess = (GetVolumeInformation(_T("C:\\"), NULL, 0, &dwSerialNumber,NULL, NULL, NULL, 0) != 0);
			CString serial_num;

		pApp->WriteProfileInt(Version,"Serial",dwSerialNumber);
		return REGISTERED;
	}
	else if (!strStarted.Compare("Yes")) { // starting up version 1.1.2 for the first time
		pApp->WriteProfileString(Version,"Started","Yes, Ver 1.1.2");
		CTime theTime = CTime::GetCurrentTime();
		int Year = theTime.GetYear();
		int Month = theTime.GetMonth();
		int Day = theTime.GetDay();
		int Run = 1;
		pApp->WriteProfileInt(Version,"Run year",Year);
		pApp->WriteProfileInt(Version,"Run month",Month);
		pApp->WriteProfileInt(Version,"Run day",Day);
		pApp->WriteProfileInt(Version,"Times run",Run);	
		m_dead_flag = pApp->GetProfileInt(Version,"Dead Flag",0);
		if (m_dead_flag == TIME_EXPIRED) { // need to restart the demo 
			pApp->WriteProfileInt(Version,"Dead Flag",DEMO_PERIOD);
			m_dead_flag = DEMO_PERIOD;
		}
		return REGISTERED;
	}
	else {
		m_dead_flag = pApp->GetProfileInt(Version,"Dead Flag",0);
		CTime curTime = CTime::GetCurrentTime();
		int curYear = this->m_first_year = curTime.GetYear();
		int curMonth = this->m_first_month = curTime.GetMonth();
		int curDay = this->m_first_day= curTime.GetDay();
		int firYear =pApp->GetProfileInt(Version,"Run year",0);
		int firMonth =pApp->GetProfileInt(Version,"Run month",0);
		int firDay =pApp->GetProfileInt(Version,"Run day",0);

		int firAbs = (firYear-2000)*365+(firMonth-1)*30+(firDay);
		int curAbs = (curYear-2000)*365+(curMonth-1)*30+(curDay);
		int DaysToUse = DaysLimit-(curAbs-firAbs);
		if (DaysToUse <= 7 && DaysToUse > 0 && m_dead_flag != REGISTERED) {
			AfxMessageBox("You have less than week left your Demo Period!\n\rIf you wish to purchase the program\n\rGo to the Help Menu and select Register...\n\rFollow the instructions on the dialog.",MB_OK|MB_ICONEXCLAMATION   );
		}
		else if ((DaysToUse > 7 && m_dead_flag == DEMO_PERIOD) || m_dead_flag == REGISTERED) {
			return m_dead_flag;
		}
		else if(DaysToUse <= 0 && m_dead_flag != REGISTERED) {
			int DeadFlag = REGISTERED;
			pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
//			AfxMessageBox("Your trial period has ended!\n\rIf you wish to purchase the program\n\rGo to the Help Menu and select Register...\n\rFollow the instructions on the dialog.",MB_OK|MB_ICONEXCLAMATION   );
			return REGISTERED;

		}
		return REGISTERED;
//		return m_dead_flag;
	}		

}
CString RegisterDlg::CreateActivationKey(CString *req_code) {
	CString first_code, second_code, act_key;
	CString temp_str;
	char temp;
	int whole_string_len, first_string_len, second_string_len, i;
	int first_key, second_key, filler_num, rand_num, first_total, second_total;
	
	whole_string_len = req_code->GetLength();
	first_code = req_code->SpanExcluding("-");
	first_string_len = first_code.GetLength();
	second_string_len = whole_string_len - first_string_len - 1;
	second_code = req_code->Right(second_string_len);
	// first lets get filler number
	srand( (unsigned)time( NULL ) );	// seed random number generator
	rand_num = rand();
	filler_num = rand_num % 10;	// mod 10 should return one digit number

	first_key = first_total = 0;

	for (i=0;i<first_string_len;i++) {
//		temp_str = first_code.Mid(i,1);	
		temp = first_code.GetAt(i);
//		strcpy(&temp,temp_str);
//		first_total += atoi(temp_str);
		first_total += temp;
	}
//	first_total = first_total * 6;
//	if (first_total > 100) 
//		first_key = first_total % 100;
//	else 
//		first_key = first_total;
	if (first_total == 0) first_total = 200;
	second_key = second_total = 0;
	for (i=1;i<=second_string_len;i++) {
		temp_str = second_code.Mid(i,1);	
		second_total += atoi(temp_str);
	}
	if (second_total == 0) second_total = 11;
	first_key = first_total * second_total;
	if (first_key < 10) first_key += 10;
	second_total = second_total * 8;
	if (second_total > 100) 
		second_key = second_total % 100;
	else 
		second_key = second_total;
	if (second_key < 10) second_key += 10;

	act_key.Format("%d%d%d",first_key,filler_num,second_key);

	return act_key;
}
BOOL RegisterDlg::UseStoredKey(CString *act_key) {
// 100 unique numbers
	
	if (!act_key->Compare("kcr11011a")) return true;
/*
	if (!act_key->Compare("kcr11012a")) return true;
	if (!act_key->Compare("kcr11013a")) return true;
	if (!act_key->Compare("kcr11014a")) return true;
	if (!act_key->Compare("kcr11015a")) return true;
	if (!act_key->Compare("kcr11016a")) return true;
	if (!act_key->Compare("kcr11017a")) return true;
	if (!act_key->Compare("kcr11018a")) return true;
	if (!act_key->Compare("kcr11019a")) return true;
	if (!act_key->Compare("kcr11010b")) return true;
	if (!act_key->Compare("kcr11011b")) return true;
	if (!act_key->Compare("kcr11012b")) return true;
	if (!act_key->Compare("kcr11013b")) return true;
	if (!act_key->Compare("kcr11014b")) return true;
	if (!act_key->Compare("kcr11015b")) return true;
	if (!act_key->Compare("kcr11016b")) return true;
	if (!act_key->Compare("kcr11017b")) return true;
	if (!act_key->Compare("kcr11018b")) return true;
	if (!act_key->Compare("kcr11019b")) return true;
	if (!act_key->Compare("kcr11010c")) return true;
	if (!act_key->Compare("kcr11011c")) return true;
	if (!act_key->Compare("kcr11012c")) return true;
	if (!act_key->Compare("kcr11013c")) return true;
	if (!act_key->Compare("kcr11014c")) return true;
	if (!act_key->Compare("kcr11015c")) return true;
	if (!act_key->Compare("kcr11016c")) return true;
	if (!act_key->Compare("kcr11017c")) return true;
	if (!act_key->Compare("kcr11018c")) return true;
	if (!act_key->Compare("kcr11019c")) return true;
	if (!act_key->Compare("kcr11010d")) return true;
	if (!act_key->Compare("kcr11002a")) return true;
	if (!act_key->Compare("kcr11003a")) return true;
	if (!act_key->Compare("kcr11004a")) return true;
	if (!act_key->Compare("kcr11005a")) return true;
	if (!act_key->Compare("kcr11006a")) return true;
	if (!act_key->Compare("kcr11007a")) return true;
	if (!act_key->Compare("kcr11008a")) return true;
	if (!act_key->Compare("kcr11009a")) return true;
	if (!act_key->Compare("kcr11001b")) return true;
	if (!act_key->Compare("kcr11001b")) return true;
	if (!act_key->Compare("kcr11000b")) return true;
	if (!act_key->Compare("kcr11021a")) return true;
	if (!act_key->Compare("kcr11022a")) return true;
	if (!act_key->Compare("kcr11023a")) return true;
	if (!act_key->Compare("kcr11024a")) return true;
	if (!act_key->Compare("kcr11025a")) return true;
	if (!act_key->Compare("kcr11026a")) return true;
	if (!act_key->Compare("kcr11027a")) return true;
	if (!act_key->Compare("kcr11028a")) return true;
	if (!act_key->Compare("kcr11029a")) return true;
	if (!act_key->Compare("kcr11021b")) return true;
	if (!act_key->Compare("kcr11021c")) return true;
	if (!act_key->Compare("kcr11021d")) return true;
	if (!act_key->Compare("kcr11021e")) return true;
	if (!act_key->Compare("kcr11021f")) return true;
	if (!act_key->Compare("kcr11021g")) return true;
	if (!act_key->Compare("kcr11021h")) return true;
	if (!act_key->Compare("kcr11021i")) return true;
	if (!act_key->Compare("kcr11021j")) return true;
	if (!act_key->Compare("kcr11021k")) return true;
	if (!act_key->Compare("kcr11021l")) return true;
	if (!act_key->Compare("kcr11021m")) return true;
	if (!act_key->Compare("kcr11021n")) return true;
	if (!act_key->Compare("kcr21021a")) return true;
	if (!act_key->Compare("kcr31021a")) return true;
	if (!act_key->Compare("kcr41021a")) return true;
	if (!act_key->Compare("kcr51021a")) return true;
	if (!act_key->Compare("kcr61021a")) return true;
	if (!act_key->Compare("kcr71021a")) return true;
	if (!act_key->Compare("kcr81021a")) return true;
	if (!act_key->Compare("kcr91021a")) return true;
	if (!act_key->Compare("kcr01011a")) return true;
	if (!act_key->Compare("kcr01011b")) return true;
	if (!act_key->Compare("kcr01011c")) return true;
	if (!act_key->Compare("kcr01011c")) return true;
	if (!act_key->Compare("kcr01011e")) return true;
	if (!act_key->Compare("kcr01011f")) return true;
	if (!act_key->Compare("kcr01011g")) return true;
	if (!act_key->Compare("kcr01011h")) return true;
	if (!act_key->Compare("kcr01211i")) return true;
	if (!act_key->Compare("kcr01311i")) return true;
	if (!act_key->Compare("kcr01411i")) return true;
	if (!act_key->Compare("kcr01511i")) return true;
	if (!act_key->Compare("kcr01611i")) return true;
	if (!act_key->Compare("kcr01711i")) return true;
	if (!act_key->Compare("kcr01811i")) return true;
	if (!act_key->Compare("kcr01911i")) return true;
	if (!act_key->Compare("kcr01011x")) return true;
	if (!act_key->Compare("kcr01011y")) return true;
	if (!act_key->Compare("kcr01011z")) return true;
*/
	return false;
}
BOOL RegisterDlg::CheckActivateKey(CString *act_key) {
	int first_key, sec_key, first_key_ch, sec_key_ch;
	CString serial_num, act_key_stored, activate_key;
	CString user_name;
	CString first_three;
	BOOL stored_key = false;
	first_three = act_key->Left(3);

	this->m_user_name.GetWindowText(user_name);

	DWORD dwSerialNumber;

	CDogRunApp*  pApp = (	CDogRunApp* )AfxGetApp();	
	Version.LoadString(IDS_RALLYVER);	
	int loc = act_key->Find("-");
	activate_key = act_key->Left(loc);	
	if (first_three = "kcr") stored_key = this->UseStoredKey(&activate_key);
	
	dwSerialNumber = pApp->GetProfileInt(Version,"Serial",0);
	long second_id = this->ConvertUserNameToLongNumber(&user_name);
	
	serial_num.Format("%x-%x", dwSerialNumber,second_id);


	act_key_stored = CreateActivationKey(&serial_num);
//	act_key_stored = pApp->GetProfileString(Version,"Volume",NULL);
	
	first_key = atoi(act_key_stored.Left(2));
	sec_key = atoi(act_key_stored.Right(2));
	first_key_ch = atoi(activate_key.Left(2));
	sec_key_ch = atoi(activate_key.Right(2));

	if ((first_key == first_key_ch && sec_key == sec_key_ch) || stored_key) {
		int DeadFlag = REGISTERED;
		pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
		pApp->WriteProfileString(Version,"User Name",user_name);
		pApp->WriteProfileString(Version,"Act Key",*act_key);
		this->MessageBox("YOU HAVE REGISTERED!",NULL,MB_OK);
		pApp->m_dead_flag = REGISTERED;
		return true;
	}
	else {
		this->MessageBox("THE KEY YOU HAVE ENTERED IS INCORRECT! CHECK YOUR ENTRY OR CONTACT ALL NATURAL SOFTWARE FOR ASSISTANCE.",NULL,MB_OK);
	}
	
	return false;

}
void RegisterDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString activate_key;
	this->m_act_key.GetWindowText(activate_key);

	BOOL response = this->CheckActivateKey(&activate_key);
	if (response) CDialog::OnOK();
}

void RegisterDlg::OnPurchase() 
{
	// TODO: Add your control notification handler code here
//	CURL url;
	// replace with my web address to purchase
//	url.Open(_T("http://www.codeprojectPURECAHCE.com/"));
	
	AddressDlg address_dlg;

	int response = address_dlg.DoModal();
	if (response == IDCANCEL) return;
	CFont list_font;
	CFont* def_font;
	CString user_name, prod_id;	
	this->m_req_key.GetWindowText(prod_id);
	this->m_user_name.GetWindowText(user_name);
	user_name.TrimRight();
	prod_id.TrimRight();
	if (user_name.IsEmpty() || prod_id.IsEmpty()) {
		this->MessageBox("You MUST enter in a User Name and Generate a Product ID to Register!","Register RallyOC",MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	CDC dc;
	DOCINFO di;
	BOOL not_done = true;
	TEXTMETRIC tm;
	CPrintDialog printdlg(FALSE);	
	CString out_string, temp_error;
	int line_number, line_height;
	response = printdlg.DoModal();
	if (response == IDOK) {

		dc.Attach (printdlg.GetPrinterDC ());
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		di.lpszDocName = "Printing RallyOC Order Form";
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
		
		line_number = 10;

		dc.TextOut(50,line_number,"RallyOC Order Form");
		line_number += line_height * 2;
		dc.TextOut(50,line_number,"You can send this order form via U.S. mail.");
		line_number += line_height * 2;	
		dc.TextOut(50,line_number,"TO:");
		line_number += line_height * 2;	
		dc.TextOut(50,line_number,"All Natural Software");
		line_number += line_height;	
		dc.TextOut(50,line_number,"11124 Kingston Pike, Box 102");
		line_number += line_height;	
		dc.TextOut(50,line_number,"Knoxville, TN 37922");
		line_number += line_height * 4;	
		dc.TextOut(50,line_number,"Include a check or money order in the amount of $65 payable to All Natural Software.");
		line_number += line_height;	
		dc.TextOut(50,line_number,"(Tennessee residents please add $6.13 for state taxes)");
		line_number += line_height * 4;	
		dc.TextOut(50,line_number,"FROM:");
		line_number += line_height * 2;
		if (address_dlg.m_name.IsEmpty()) {
			dc.TextOut(50,line_number,"Name: ______________________________________________________");
		}
		else {
			out_string = "Name: " + address_dlg.m_name;
			dc.TextOut(50,line_number,out_string);
		}
		line_number += line_height * 2;		

		if (address_dlg.m_street.IsEmpty()) {
			dc.TextOut(50,line_number,"Street: ______________________________________________________________");
		}
		else {
			out_string = "Street: " + address_dlg.m_street;
			dc.TextOut(50,line_number,out_string);
		}
		line_number += line_height * 2;	

		if (address_dlg.m_suite_no.IsEmpty()) {
			dc.TextOut(50,line_number,"Suite/Apt. #: ________________________________________________________");
		}
		else {
			out_string = "Suite/Apt. #: " + address_dlg.m_suite_no;
			dc.TextOut(50,line_number,out_string);
		}
		line_number += line_height * 2;	

		if (address_dlg.m_city.IsEmpty()) {
			dc.TextOut(50,line_number,"City: _______________________________________________________");
		}
		else {
			out_string = "City: " + address_dlg.m_city;
			dc.TextOut(50,line_number,out_string);
		}		
		line_number += line_height * 2;	

		if (address_dlg.m_state.IsEmpty() || address_dlg.m_zip_code.IsEmpty()) {
			dc.TextOut(50,line_number,"State: ___________________________  Zip/Postal Code: _________________");
		}
		else {
			out_string = "State: " + address_dlg.m_state + "  Zip/Postal Code: " + address_dlg.m_zip_code;
			dc.TextOut(50,line_number,out_string);
		}
		line_number += line_height * 2;	

		if (address_dlg.m_phone_no.IsEmpty()) {
			dc.TextOut(50,line_number,"Telephone #: _____________________ ");
		}
		else {
			out_string = "Telephone #: " + address_dlg.m_phone_no;
			dc.TextOut(50,line_number,out_string);
		}		


		line_number += line_height * 2;	
		if (address_dlg.m_email_add.IsEmpty()) {
			dc.TextOut(50,line_number,"E-Mail Address: ______________________________________________________");
		}
		else {
			out_string = "E-Mail Address: " + address_dlg.m_email_add;
			dc.TextOut(50,line_number,out_string);
		}

		line_number += line_height * 2;		
		out_string = "**User Name: " + user_name + " Product ID: " + prod_id;
		dc.TextOut(50,line_number,out_string);
		line_number += line_height * 2;	
		
		CTime curTime = CTime::GetCurrentTime();
		out_string = curTime.Format("%m/%d/%y ");
		Version.LoadString(IDS_VERSION);
		
		out_string += Version;
		dc.TextOut(50,line_number,out_string);
		line_number += line_height * 2;	



		dc.EndPage();
		dc.EndDoc();

	}	

}

void RegisterDlg::OnContact() 
{
	// TODO: Add your control notification handler code here
	CURL url;
	// replace with my web address to send message
	url.Open(_T("http://www.codeprojectCONTACT.com/"));	
}	


void RegisterDlg::OnGenProdId() 
{
	// TODO: Add your control notification handler code here
	CString user_name;
	long second_id;
	this->m_user_name.GetWindowText(user_name);
	if (user_name.GetLength() <= 0) {
		this->MessageBox("You must enter in a user name to generate a product id!","RallyOC Register",MB_OK);
		return;
	}
	CWinApp* pApp = AfxGetApp();	
	Version.LoadString(IDS_RALLYVER);	

	second_id = this->ConvertUserNameToLongNumber(&user_name);

	DWORD dwSerialNumber;
	dwSerialNumber = pApp->GetProfileInt(Version,"Serial",0);
	CString serial_num;
	serial_num.Format("%x-%x",dwSerialNumber,second_id);

	this->m_req_key.SetWindowText(serial_num);
	this->m_req_key.ShowWindow(SW_SHOW);
	this->m_prodID_st.ShowWindow(SW_SHOW);
	this->m_act_key.ShowWindow(SW_SHOW);
	this->m_actkey_st.ShowWindow(SW_SHOW);
	pApp->WriteProfileString(Version,"User Name",user_name);
	pApp->WriteProfileString(Version,"Prod ID",serial_num);
	pApp->WriteProfileInt(Version,"Dead Flag",PRODID_GEN);

//	CString act_key = this->CreateActivationKey(&serial_num);
//	this->m_act_key.SetWindowText(act_key);

}
long RegisterDlg::ConvertUserNameToLongNumber(CString *user_name) {
	int str_len, i;
	char temp;
	long user_name_value = 0;
	str_len = user_name->GetLength();
	for (i= 0; i<str_len; i++) {
		temp = user_name->GetAt(i);
		user_name_value += temp * 120;
	}

	
	return user_name_value;
}
long RegisterDlg::CreateFirstIDFromDate(void) {
	long first_id;
	COleDateTime first_use_date;
	first_use_date.SetDate(this->m_first_year, this->m_first_month, this->m_first_day);
	first_id = (long)first_use_date.m_dt;

	return first_id;
}