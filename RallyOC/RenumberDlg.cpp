// RenumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "RenumberDlg.h"
#include "DogRunView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RenumberDlg dialog


RenumberDlg::RenumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RenumberDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RenumberDlg)
	m_current_station = _T("");
	m_insert = 0;
	//}}AFX_DATA_INIT
}


void RenumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RenumberDlg)
	DDX_Control(pDX, IDC_STATIONLIST, m_station_list);
	DDX_Text(pDX, IDC_STATIC_CURRENT, m_current_station);
	DDX_Radio(pDX, IDC_BEFORE, m_insert);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RenumberDlg, CDialog)
	//{{AFX_MSG_MAP(RenumberDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RenumberDlg message handlers

int RenumberDlg::DoModal(CDogRunDoc *p_dogrundoc, CRallyObject *p_selectedStation) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_dog_runDoc = p_dogrundoc;
	this->m_selected_station = p_selectedStation;
	return CDialog::DoModal();
}

BOOL RenumberDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString sel_station_number, sel_station_desc;
	int sel_num_of_station;
	CString station_number, station_desc;
	CString add_string;
	int num_of_station;
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	
	sel_station_desc.LoadString( this->m_selected_station->GetStringNumber());
	sel_num_of_station = this->m_selected_station->GetStationNumber();
	sel_station_number.Format("%d",sel_num_of_station);

	this->m_current_station = "Current Selection: " + sel_station_desc + ": Station Number: " + sel_station_number;
	for( pos = this->m_dog_runDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_dog_runDoc->m_rallyList.GetNext(pos);
		num_of_station = pRallyItemInlist->GetStationNumber();
		if ((sel_num_of_station != num_of_station) && (num_of_station != 0)) {
			station_number.Format("%d",num_of_station);
			sel_station_desc.LoadString( pRallyItemInlist->GetStringNumber());
			add_string = station_number + ": " + sel_station_desc;
			this->m_station_list.AddString(add_string);
		}
	}	
	this->m_station_list.SetCurSel(0);

	
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RenumberDlg::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);

	int num_of_selection;
	int action;
	if (this->m_insert == 0) 
		action = INSERT_BEFORE;
	else 
		action = INSERT_AFTER;

	POSITION pos = this->m_dog_runDoc->GetFirstViewPosition();
	CDogRunView *pView = (CDogRunView *)this->m_dog_runDoc->GetNextView(pos);
	POSITION pos_in_rally_list =  this->m_dog_runDoc->m_rallyList.Find(this->m_selected_station,NULL);
//	pView->AddUndoStation(this->m_selected_station,pos_in_rally_list,action);

	num_of_selection = this->m_station_list.GetCurSel();
	num_of_selection++;// zero based add one

	this->m_dog_runDoc->RenumberStations(num_of_selection, action, this->m_selected_station, false);
	if (action == INSERT_BEFORE) 
		this->m_selected_station->SetStationNumber(num_of_selection);
	else 
		this->m_selected_station->SetStationNumber(++num_of_selection);
	this->m_dog_runDoc->UpdateAllViews(NULL);



	CDialog::OnOK();
}
