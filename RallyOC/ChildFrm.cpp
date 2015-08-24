// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "DogRun.h"
#include "DogRunDoc.h"
#include "ChildFrm.h"
#include "StationMapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FORWARD_HALT, OnForwardHalt)
	ON_WM_MDIACTIVATE()
	ON_COMMAND(ID_CHANGE_PACE, OnChangePace)
	ON_COMMAND(ID_RIGHT_TURNS, OnRightTurns)
	ON_COMMAND(ID_LEFT_TURNS, OnLeftTurns)
	ON_COMMAND(ID_FINISH, OnFinish)
	ON_COMMAND(ID_MOVE, OnMove)
	ON_COMMAND(ID_HEEL, OnHeel)
	ON_COMMAND(ID_WEAVE, OnWeave)
	ON_COMMAND(ID_STATIONARY, OnStationary)
	ON_COMMAND(ID_NONSTATIONARY, OnNonstationary)
	ON_COMMAND(ID_ADVANCED, OnAdvanced)
	ON_COMMAND(ID_EXCELLENT, OnExcellent)
	ON_COMMAND(ID_NOVICE, OnNovice)
	ON_COMMAND(ID_PIVOT, OnPivot)
	ON_COMMAND(ID_VIEW_RALLY_LIST, OnViewRallyList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RALLY_LIST, OnUpdateViewRallyList)
	ON_COMMAND(ID_PATTERN, OnPattern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here

}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style  = cs.style | WS_MAXIMIZE;

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
 
	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	nCmdShow = SW_SHOWMAXIMIZED;
	

	CMDIChildWnd::ActivateFrame(nCmdShow);

}

BOOL CChildFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message) {
	case WM_LBUTTONDOWN:
		this->m_point = pMsg->pt;
		break;
	}

	return CMDIChildWnd::PreTranslateMessage(pMsg);
}


void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
	if (bActivate) {
		this->UpdateInsertAfterMenu();
		this->SetUpRallyListDialog();
		this->SetUpChangeMenu();
		this->SetAddMenu();
	}
	else {
		this->ClearRallyListDialog();
	}

}
void CChildFrame::ClearRallyListDialog(void) {
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
	pApp->m_rally_list_Dialog->ClearRallyList();
}
void CChildFrame::SetUpRallyListDialog(void) {
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CObList *p_rallyList;
	p_rallyList = &pDoc->m_rallyList;;
	pApp->m_rally_list_Dialog->SetUpRallyList(p_rallyList,pDoc);

}
CMenu* CChildFrame::GetInsertAfterMenu(void) {
	CMenu *edit_menu, *insert_menu;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();

	int iPos;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
		CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_EDIT_UNDO) {
			edit_menu = pMenu;
			break;
		}
	}
	for (iPos = edit_menu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
		CMenu* pMenu = edit_menu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_ITEM1) {
			insert_menu = pMenu;
			break;
		}
	}
	ASSERT(insert_menu != NULL);
	return insert_menu;
}
void CChildFrame::UpdateInsertAfterMenu(void) {

	CMenu *insert_menu;
    insert_menu = this->GetInsertAfterMenu();
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);

	int iPos, find_slash;
	for (iPos = insert_menu->GetMenuItemCount()-1; iPos > 0; iPos--)
		insert_menu->DeleteMenu(iPos, MF_BYPOSITION);

	POSITION pos;
	CRallyObject* pRallyItemInlist;
	CString station_number, station_desc;
	CString add_string;
	int num_of_station, akc_number;
	int menu_cmd_id;
	for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);
		num_of_station = pRallyItemInlist->GetStationNumber();
		akc_number = pRallyItemInlist->GetAKCNumber();
		if (num_of_station > 0 && akc_number != 50) {
			station_number.Format("%d",num_of_station);
			station_desc.LoadString( pRallyItemInlist->GetStringNumber());
			find_slash = station_desc.Find("\n");
			station_desc = station_desc.Left(find_slash);
			add_string = station_number + ": " + station_desc;
			menu_cmd_id = num_of_station + ID_ITEM1;
			insert_menu->InsertMenu(num_of_station, MF_STRING | MF_BYPOSITION,menu_cmd_id, add_string);
		}
	}
	this->ModifyInsertAfterMenu();
}
void CChildFrame::ModifyInsertAfterMenu(void) {
	int find_slash;
	CMenu *insert_menu;
    insert_menu = this->GetInsertAfterMenu();
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);

	POSITION pos;
	CRallyObject* pRallyItemInlist;
	CString station_number, station_desc;
	CString add_string;
	int num_of_station;
	int menu_cmd_id;
	for( pos = pDoc->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)pDoc->m_rallyList.GetNext(pos);

		num_of_station = pRallyItemInlist->GetStationNumber();
		if (num_of_station > 0) {
			station_number.Format("%d",num_of_station);
			station_desc.LoadString( pRallyItemInlist->GetStringNumber());
			find_slash = station_desc.Find("\n");
			station_desc = station_desc.Left(find_slash);
			add_string = station_number + ": " + station_desc;
			menu_cmd_id = num_of_station + ID_ITEM1;
			BOOL test = insert_menu->ModifyMenu(menu_cmd_id,MF_BYCOMMAND,menu_cmd_id,add_string);
		}
	}
}
CMenu*  CChildFrame::GetChangeToMenu(void) {
	CMenu *edit_menu, *insert_menu;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	UINT editmenuid = this->FindMenuItem(pTopMenu,"&Edit");
	edit_menu =  pTopMenu->GetSubMenu(editmenuid);
	UINT undoeditid = this->FindMenuItem(edit_menu,"Change To");
	insert_menu = edit_menu->GetSubMenu(undoeditid);
	ASSERT(insert_menu != NULL);
	return insert_menu;
}
void CChildFrame::SetUpChangeMenu(void) {

	CMenu *insert_menu;
    insert_menu = this->GetChangeToMenu();
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);

	int iPos;
	for (iPos = insert_menu->GetMenuItemCount(); iPos >= 0; iPos--)
		insert_menu->DeleteMenu(iPos, MF_BYPOSITION);

	CourseInfo course_info;
	int i, menu_cmd_id;
	CString add_string;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	CStringList Items;
	StationMapper::GetStationDescriptionByAKCType(course_info.m_class,Items);
	POSITION Position = Items.GetHeadPosition();
	i=0;
	while (Position){
		add_string = Items.GetNext(Position);
		menu_cmd_id = i + ID_CH_MENU_1;
		insert_menu->InsertMenu(i, MF_STRING | MF_BYPOSITION,menu_cmd_id, add_string);
		i++;
	}
}
void CChildFrame::OnForwardHalt() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {	
		if (menu.LoadMenu(IDR_HALT_FOR_AKC)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_HALT_FOR_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}
void CChildFrame::OnChangePace() 
{
	// TODO: Add your command handler code here
	CMenu menu;

	if (menu.LoadMenu(IDR_CHANGE_PACE)) {
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
	}		
}



void CChildFrame::OnRightTurns() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {	
		if (menu.LoadMenu(IDR_RIGHT_TURNS)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_RIGHT_TURNS_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}	}
}


void CChildFrame::OnPivot() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {	

		if (menu.LoadMenu(IDR_PIVOT_TURNS)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_PIVOT_TURNS_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}	}
}

void CChildFrame::OnLeftTurns() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_LEFT_TURNS)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_LEFT_TURNS_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}

void CChildFrame::OnFinish() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_FINISH_X)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_FINISH_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}

void CChildFrame::OnMove() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_MOVE_X)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_MOVE_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}	}

}

void CChildFrame::OnHeel() 
{
	// TODO: Add your command handler code here
	CMenu menu;

	if (menu.LoadMenu(IDR_HEEL)) {
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
	}			
}

void CChildFrame::OnWeave() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_WEAVE)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_WEAVE_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}

void CChildFrame::OnStationary() 
{
	// TODO: Add your command handler code here
	CMenu menu;

	if (menu.LoadMenu(IDR_STATIONARY)) {
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
	}			
}

void CChildFrame::OnNonstationary() 
{
	// TODO: Add your command handler code here
	CMenu menu;

	if (menu.LoadMenu(IDR_NONSTATIONARY)) {
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
	}			
}

void CChildFrame::OnAdvanced() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_ADVANCED)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_ADVANCED_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}

void CChildFrame::OnExcellent() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_EXCELLENT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_EXCELLENT_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}

void CChildFrame::OnNovice() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	pDoc->m_course_info->GetCourseInfo(&course_info);

	if (course_info.m_type_of_course == AKC_COURSE) {
		if (menu.LoadMenu(IDR_NOVICE)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
	else {
		if (menu.LoadMenu(IDR_NOVICE_APDT)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
		}
	}
}


void CChildFrame::OnViewRallyList() 
{
	// TODO: Add your command handler code here
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
	CString Version;
	Version.LoadString(IDS_RALLYVER);

	CObList *rallyList;
	rallyList = &pDoc->m_rallyList;
	if (!pApp->m_view_rally_dialog && pApp->m_dead_flag != TIME_EXPIRED) {
		pApp->m_rally_list_Dialog->ShowWindow(SW_SHOW);
		pApp->m_view_rally_dialog = true;

	}
	else {
		pApp->m_rally_list_Dialog->ShowWindow(SW_HIDE);
		pApp->m_view_rally_dialog = false;
	}
	pApp->WriteProfileInt(Version,"List Dialog",pApp->m_view_rally_dialog);

}

void CChildFrame::OnUpdateViewRallyList(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();


	pCmdUI->SetCheck(pApp->m_view_rally_dialog);		
}

void CChildFrame::SetAddMenu(void)
{
	CDogRunDoc* pDoc = (CDogRunDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDogRunDoc, pDoc);
	CourseInfo course_info;
	CMenu pNewMenu;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;

	pDoc->m_course_info->GetCourseInfo(&course_info);
	iPos = FindMenuItem(pTopMenu, "&Add AKC");
	if (iPos == -1)
	  return;

	if (course_info.m_type_of_course == AKC_COURSE) {
		pTopMenu->EnableMenuItem(iPos,MF_BYPOSITION   | MF_ENABLED );
// FOR NOW I don't have APDT Menu items so this is the Add menu
//		pTopMenu->EnableMenuItem(iPos +1 ,MF_BYPOSITION   | MF_GRAYED );
	
	}


//	else {
//		pTopMenu->EnableMenuItem(iPos + 1,MF_BYPOSITION   | MF_ENABLED );
//		pTopMenu->EnableMenuItem(iPos,MF_BYPOSITION   | MF_GRAYED );

//	}


	AfxGetMainWnd()->DrawMenuBar();
}

int CChildFrame::FindMenuItem(CMenu *Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
	  Menu->GetMenuString(i, str, MF_BYPOSITION);
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (strcmp(str, MenuString) == 0))
         return i;
   }

   return -1;

}

void CChildFrame::OnPattern() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	if (menu.LoadMenu(IDR_PATTERN)) {
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, this->m_point.x, this->m_point.y, AfxGetMainWnd()); // route commands through main window
	}
}
