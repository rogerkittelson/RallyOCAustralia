// StationPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DogRun.h"
#include "StationPropDlg.h"
#include "DogRunDoc.h"
#include "StationMapper.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StationPropDlg dialog


StationPropDlg::StationPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StationPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StationPropDlg)
	m_stat_no = _T("");
	m_stat_desc = -1;
	m_station_size = -1;
	m_actual_size = _T("");
	m_station_degrees = _T("");
	//}}AFX_DATA_INIT
}


void StationPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StationPropDlg)
	DDX_Control(pDX, IDC_CUSTOM_SIZE, m_ctl_actual_size);
	DDX_Control(pDX, IDC_A_NUMBER, m_a_number);
	DDX_Control(pDX, IDC_STAT_NAME, m_station_name);
	DDX_Text(pDX, IDC_STAT_NO, m_stat_no);
	DDX_Radio(pDX, IDC_STAT_BOTH, m_stat_desc);
	DDX_Radio(pDX, IDC_SIZE_2, m_station_size);
	DDX_Text(pDX, IDC_CUSTOM_SIZE, m_actual_size);
	DDX_Text(pDX, IDC_STATION_DEG, m_station_degrees);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StationPropDlg, CDialog)
	//{{AFX_MSG_MAP(StationPropDlg)
	ON_CBN_SELCHANGE(IDC_STAT_NAME, OnSelchangeStatName)
	ON_CBN_SELCHANGE(IDC_A_NUMBER, OnSelchangeANumber)
	ON_EN_CHANGE(IDC_STAT_NO, OnChangeStatNo)
	ON_BN_CLICKED(IDC_SIZE_2, OnSize2)
	ON_BN_CLICKED(IDC_SIZE_5, OnSize5)
	ON_BN_CLICKED(IDC_SIZE_7, OnSize7)
	ON_BN_CLICKED(IDC_SIZE_CUSTOM, OnSizeCustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StationPropDlg message handlers

int StationPropDlg::DoModal(CRallyObject *pRallyObjectInSelectList, RallyObjList *pRallyList, CScrollView *pView, 	CDocument *pDoc) 
{
	// TODO: Add your specialized code here and/or call the base class

	this->m_pRallyObject = pRallyObjectInSelectList;
	this->m_prally_list = pRallyList;
	this->m_pView = pView;
	this->m_pDoc = pDoc;
	this->m_stat_desc = this->m_pRallyObject->GetStationDescription();
	this->m_multi_stations = FALSE;
	m_degree_rotation = this->m_pRallyObject->m_rotate_degrees;
	this->m_station_degrees.Format("%f",this->m_degree_rotation);
	return CDialog::DoModal();
}

int StationPropDlg::DoModal(CObList *pRallyList, CScrollView *pView, 	CDocument *pDoc) 
{
	// TODO: Add your specialized code here and/or call the base class

	this->m_pRallyObject = NULL;
	this->m_prally_list = (RallyObjList *)pRallyList;
	this->m_pView = pView;
	this->m_pDoc = pDoc;
	this->m_multi_stations = TRUE;
	this->m_station_degrees.Format("%f",0.0);
	return CDialog::DoModal();
}
BOOL StationPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CDogRunDoc *p_dogRunDoc;
	p_dogRunDoc = (CDogRunDoc*)this->m_pDoc;	
	CourseInfo course_info;
	p_dogRunDoc->m_course_info->GetCourseInfo(&course_info);
	// TODO: Add extra initialization here
	int class_cutoff;
	
		switch (course_info.m_class) {
		case NOVICE:
			class_cutoff = 32;
			break;
		case ADVANCED:
			class_cutoff = 46;
			break;
		case EXCELLENT:
			class_cutoff = 53;
			break;
		case MASTER:
		case TRAINING:
			class_cutoff = 60;
			break;
		}

	CString str, station_number, station_name;
	int error;
	CDC *window_dc;
	CWnd *tempWnd;
	window_dc = this->m_pView->GetDC();
	int last_mode = 0;
	last_mode = SetGraphicsMode (window_dc->m_hDC, GM_ADVANCED);
	if (!last_mode) {
		tempWnd = this->GetDlgItem(IDC_STATION_DEG_ST);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_STATION_DEG);
		tempWnd->ShowWindow(SW_HIDE);
	}
	else {
		SetGraphicsMode (window_dc->m_hDC, last_mode);
	}
	if (this->m_multi_stations) {
		tempWnd = this->GetDlgItem(IDC_TX_STAT_NO);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_TX_STAT_NAME);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_TX_AKC_NO);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_STAT_NO);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_STAT_NAME);
		tempWnd->ShowWindow(SW_HIDE);
		tempWnd = this->GetDlgItem(IDC_A_NUMBER);
		tempWnd->ShowWindow(SW_HIDE);
		this->m_station_size = -1;
		this->m_stat_desc = -1;
		this->m_ctl_actual_size.ShowWindow(SW_HIDE);
		this->m_station_degrees.Empty();

	}
	else {

		if (this->m_pRallyObject->GetStationType() == AKC_COURSE) {
			CStringList Items;
			StationMapper::GetStationDescriptionByAKCType(course_info.m_class,Items);
			POSITION Position = Items.GetHeadPosition();
			
		
			while (Position){
				str = Items.GetNext(Position);
				int idx = str.Find(".");
				CString leftstr = str.Left(idx);
				int one_found = leftstr.Compare("1");
				int two_found = leftstr.Compare("2");
	//			if ((one_found != 0) && (two_found != 0) ) {
					error = this->m_a_number.AddString( leftstr );
					error = this->m_station_name.AddString( str );
//				}
			}
		}
		else {
			for (int i=1;i <= class_cutoff;i++)
			{
				str.Format(_T("%d"), i);
				error = this->m_a_number.AddString( str );
				station_name = this->m_prally_list->apdt_station_names[i];
				str.Format(_T("%d:%s"), i,station_name);
				error = this->m_station_name.AddString( str );
			}
		}
		this->m_stat_no.Format("%d",this->m_pRallyObject->GetStationNumber());
		int selection = StationMapper::GetComboBoxSelectionFromAKCid(this->m_pRallyObject->GetAKCNumber());
		this->m_a_number.SetCurSel(selection);
		this->m_station_name.SetCurSel(selection);
		if (this->m_pRallyObject->GetAKCNumber() == 1 || this->m_pRallyObject->GetAKCNumber() == 2 || this->m_pRallyObject->GetAKCNumber() == 299) {
			tempWnd = this->GetDlgItem(IDC_TX_STAT_NO);
			tempWnd->ShowWindow(SW_HIDE);
			tempWnd = this->GetDlgItem(IDC_TX_STAT_NAME);
			tempWnd->ShowWindow(SW_HIDE);
			tempWnd = this->GetDlgItem(IDC_TX_AKC_NO);
			tempWnd->ShowWindow(SW_HIDE);
			tempWnd = this->GetDlgItem(IDC_STAT_NO);
			tempWnd->ShowWindow(SW_HIDE);
			tempWnd = this->GetDlgItem(IDC_STAT_NAME);
			tempWnd->ShowWindow(SW_HIDE);
			tempWnd = this->GetDlgItem(IDC_A_NUMBER);
			tempWnd->ShowWindow(SW_HIDE);
		}
		// TODO: Add extra initialization here
		int actual_size = this->m_pRallyObject->GetRallyStationSizeInFeet(p_dogRunDoc->m_pixels_per_foot_wd);
		if (actual_size == 2) this->m_station_size = TWO_EVEN;
		else if (actual_size == 5) this->m_station_size = FIVE_EVEN;
		else if (actual_size == 7) this->m_station_size = SEVEN_EVEN;
		else this->m_station_size = CUSTOM_SIZE;
		this->m_actual_size.Format("%d",actual_size);
		
		if (this->m_station_size == TWO_EVEN) this->m_ctl_actual_size.ShowWindow(SW_HIDE);
		else if (this->m_station_size == FIVE_EVEN) this->m_ctl_actual_size.ShowWindow(SW_HIDE);
		else if (this->m_station_size == SEVEN_EVEN) 	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
		else 	this->m_ctl_actual_size.ShowWindow(SW_SHOW);
	}
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void StationPropDlg::OnSelchangeStatName() 
{
	// TODO: Add your control notification handler code here
	int choice;
	int selection = -1;
	choice = this->m_station_name.GetCurSel();
	int akc_number = StationMapper::GetAKCidFromComboBoxSelection(choice);
	CDogRunDoc *p_dogRunDoc;
	p_dogRunDoc = (CDogRunDoc*)this->m_pDoc;
	// need to make sure that we don't have Honor, Start, or Finish Station in list
	CourseInfo course_info;
	p_dogRunDoc->m_course_info->GetCourseInfo(&course_info);
	switch(akc_number) {
	case 1:
		if (p_dogRunDoc->StartStationInList()) {
			this->m_station_name.SetCurSel(this->m_pRallyObject->GetAKCNumber() - 3);
			AfxMessageBox("You can only have one START station per course.",MB_OK,ID_DRAW_START);
			return;
		}

		break;
	case 2:
		if (p_dogRunDoc->FinishStationInList()) {
			this->m_station_name.SetCurSel(this->m_pRallyObject->GetAKCNumber() - 3);
			AfxMessageBox("You can only have one FINSIH station per course.",MB_OK,ID_DRAW_START);
			return;
		}

		break;
	case 299:
			selection = StationMapper::GetComboBoxSelectionFromAKCid(this->m_pRallyObject->GetAKCNumber());
			this->m_a_number.SetCurSel(selection);
			AfxMessageBox("Changing to Call to Heel not supported at this time.",MB_OK,ID_DRAW_START);
			return;
	case 50:
		if (p_dogRunDoc->HonorStationInList(course_info.m_type_of_course)) {
			this->m_station_name.SetCurSel(this->m_pRallyObject->GetAKCNumber() - 3);
			AfxMessageBox("You can only have one HONOR station per course.",MB_OK,ID_DRAW_START);
			return;
		}
		break;
	}
	POSITION pos;
	pos = this->m_prally_list->Find(this->m_pRallyObject,NULL);
	p_dogRunDoc->AddUndoStation(this->m_pRallyObject, pos,CHANGE_STATION);
	this->m_a_number.SetCurSel(choice);
	this->m_prally_list->ChangeStationType(this->m_pRallyObject,akc_number,this->m_pRallyObject->GetStationType());
	this->m_pView->Invalidate(FALSE);
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
//	int will_need_to_fix_next_line_for_ADPT;
	pApp->m_rally_list_Dialog->SetUpRallyList(this->m_prally_list,this->m_pDoc);

}

void StationPropDlg::OnSelchangeANumber() 
{
	// TODO: Add your control notification handler code here
	int choice;
	choice = this->m_a_number.GetCurSel();
	int selection = -1;
	int akc_number = StationMapper::GetAKCidFromComboBoxSelection(choice);
	CDogRunDoc *p_dogRunDoc;
	p_dogRunDoc = (CDogRunDoc*)this->m_pDoc;
	CourseInfo course_info;
	p_dogRunDoc->m_course_info->GetCourseInfo(&course_info);
	switch(akc_number) {
	case 1:
		if (p_dogRunDoc->StartStationInList()) {
			this->m_a_number.SetCurSel(this->m_pRallyObject->GetAKCNumber() - 3);
			AfxMessageBox("You can only have one START station per course.",MB_OK,ID_DRAW_START);
			return;
		}

		break;
	case 2:
		if (p_dogRunDoc->FinishStationInList()) {
			this->m_a_number.SetCurSel(this->m_pRallyObject->GetAKCNumber() - 3);
			AfxMessageBox("You can only have one FINSIH station per course.",MB_OK,ID_DRAW_START);
			return;
		}

		break;
	case 299:
			selection = StationMapper::GetComboBoxSelectionFromAKCid(this->m_pRallyObject->GetAKCNumber());
			this->m_a_number.SetCurSel(selection);
			AfxMessageBox("Changing to Call to Heel not supported at this time.",MB_OK,ID_DRAW_START);
			return;
	case 50:
		if (p_dogRunDoc->HonorStationInList(course_info.m_type_of_course)) {
			this->m_a_number.SetCurSel(this->m_pRallyObject->GetAKCNumber() - 3);
			AfxMessageBox("You can only have one HONOR station per course.",MB_OK,ID_DRAW_START);
			return;
		}
		break;
	}
	
	
	POSITION pos;
	pos = this->m_prally_list->Find(this->m_pRallyObject,NULL);
	p_dogRunDoc->AddUndoStation(this->m_pRallyObject, pos,CHANGE_STATION);
	this->m_prally_list->ChangeStationType(this->m_pRallyObject,akc_number,this->m_pRallyObject->GetStationType());
	this->m_station_name.SetCurSel(choice);

	this->m_pView->Invalidate(FALSE);	
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
//	int will_need_to_fix_next_line_for_ADPT;
	pApp->m_rally_list_Dialog->SetUpRallyList(this->m_prally_list,this->m_pDoc);
}


void StationPropDlg::OnChangeStatNo() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int new_number;
	this->UpdateData(TRUE);
	new_number = atoi(this->m_stat_no);

	if (new_number <= 0 || new_number > this->m_prally_list->GetLastNumber()) {
		this->MessageBox("INVALID ENTRY","ERROR",MB_OK + MB_ICONEXCLAMATION);
		this->m_stat_no.Format("%d",this->m_pRallyObject->GetStationNumber());
	}
	else {
		int old_number = this->m_pRallyObject->GetStationNumber();
		if (old_number == new_number) return;
		this->RenumberStation(new_number);
	}
}

void StationPropDlg::RenumberStation(int new_number)
{
	CDogRunDoc *p_dogRunDoc;
	p_dogRunDoc = (CDogRunDoc*)this->m_pDoc;
	p_dogRunDoc->ClearRedoList();
	p_dogRunDoc->ClearUndoList();
	POSITION pos;
	pos = this->m_prally_list->Find(this->m_pRallyObject,NULL);
	if (this->m_prally_list->GetTypeOfCourse() == AKC_COURSE) {
		int akc_number = this->m_pRallyObject->GetAKCNumber();
		if (akc_number == 1 || akc_number == 2 || akc_number == 50) return; //START, FINISH or HONOR 
		p_dogRunDoc->AddUndoStation(this->m_pRallyObject, pos,INSERT_AT);
		p_dogRunDoc->RenumberStations(new_number, INSERT_AT, this->m_pRallyObject, false);
		this->m_pDoc->UpdateAllViews(NULL,CHANGE_STATION,NULL);
	}
	else {
	}
	

}


void StationPropDlg::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	CDogRunDoc *p_dogRunDoc;
	POSITION pos, pos_in_rally_list;
	p_dogRunDoc = (CDogRunDoc*)this->m_pDoc;	
	int station_size, num_changed, how_many_stations;
	double degree_rotation = atof(this->m_station_degrees);
	if (this->m_station_size == TWO_EVEN) 
		station_size = 2;
	else if (this->m_station_size == FIVE_EVEN) 
		station_size = 5;
	else if (this->m_station_size == SEVEN_EVEN) 
		station_size = 7;
	else 
		station_size = atoi(this->m_actual_size);
	if (this->m_multi_stations) {
		CRallyObject* pRallyItemInlist;
		how_many_stations = this->m_prally_list->GetCount();
		if (this->m_stat_desc != -1) {
			num_changed = 1;
			for( pos = this->m_prally_list->GetHeadPosition(); pos != NULL; num_changed++) {
				pRallyItemInlist = (CRallyObject*)this->m_prally_list->GetNext(pos);
				pos_in_rally_list = p_dogRunDoc->m_rallyList.Find(pRallyItemInlist);
				if (num_changed == 1) 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE_START);
				else if (num_changed > 1 && num_changed < how_many_stations) 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE);
				else 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE_END);
				pRallyItemInlist->SetStationDescription(this->m_stat_desc);
			}
		}
		if (this->m_station_size != -1) {
			num_changed = 1;
			for( pos = this->m_prally_list->GetHeadPosition(); pos != NULL; num_changed++) {
				pRallyItemInlist = (CRallyObject*)this->m_prally_list->GetNext(pos);
				pos_in_rally_list = p_dogRunDoc->m_rallyList.Find(pRallyItemInlist);
				if (num_changed == 1) 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE_START);
				else if (num_changed > 1 && num_changed < how_many_stations) 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE);
				else 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE_END);
				if (this->m_station_size == TWO_EVEN) 
					station_size = 2;
				else if (this->m_station_size == FIVE_EVEN) 
					station_size = 5;
				else if (this->m_station_size == SEVEN_EVEN) 
					station_size = 7;
				else 
					station_size = atoi(this->m_actual_size);
				pRallyItemInlist->SetStationRect(station_size,p_dogRunDoc->m_pixels_per_foot_ht, p_dogRunDoc->m_pixels_per_foot_wd);
			}
		}
		if (!this->m_station_degrees.IsEmpty() && this->m_degree_rotation != degree_rotation) {
			num_changed = 1;
			for( pos = this->m_prally_list->GetHeadPosition(); pos != NULL;num_changed++ ) {
				pRallyItemInlist = (CRallyObject*)this->m_prally_list->GetNext(pos);
				pos_in_rally_list = p_dogRunDoc->m_rallyList.Find(pRallyItemInlist);
				if (num_changed == 1) 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE_START);
				else if (num_changed > 1 && num_changed < how_many_stations) 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE);
				else 
					p_dogRunDoc->AddUndoStation(pRallyItemInlist,pos_in_rally_list,MULMOVE_END);
				this->m_degree_rotation = atof(this->m_station_degrees);
				pRallyItemInlist->CalculateRotateMeasurements(this->m_degree_rotation);
			}
		}
	}
	else {
		int station_desc = this->m_pRallyObject->GetStationDescription();
		if ((station_size != this->m_pRallyObject->GetRallyStationSizeInFeet(p_dogRunDoc->m_pixels_per_foot_wd)) || (degree_rotation != this->m_degree_rotation) || (station_desc != this->m_stat_desc)) {
			pos_in_rally_list = p_dogRunDoc->m_rallyList.Find(this->m_pRallyObject);
			p_dogRunDoc->AddUndoStation(this->m_pRallyObject,pos_in_rally_list,MOVE_STATION);
			this->m_pRallyObject->SetStationDescription(this->m_stat_desc);
			if (this->m_station_size == TWO_EVEN) 
				station_size = 2;
			else if (this->m_station_size == FIVE_EVEN) 
				station_size = 5;
			else if (this->m_station_size == SEVEN_EVEN) 
				station_size = 7;
			else 
				station_size = atoi(this->m_actual_size);
			this->m_pRallyObject->SetStationRect(station_size,p_dogRunDoc->m_pixels_per_foot_ht, p_dogRunDoc->m_pixels_per_foot_wd);
			this->m_degree_rotation = atof(this->m_station_degrees);
			this->m_pRallyObject->CalculateRotateMeasurements(this->m_degree_rotation);
		}
	}
	this->m_pView->Invalidate(FALSE);
	CDialog::OnOK();
}

void StationPropDlg::OnSize2() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
	
}

void StationPropDlg::OnSize5() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
	
}

void StationPropDlg::OnSize7() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_HIDE);
	
}

void StationPropDlg::OnSizeCustom() 
{
	// TODO: Add your control notification handler code here
	this->m_ctl_actual_size.ShowWindow(SW_SHOW);
	
}
