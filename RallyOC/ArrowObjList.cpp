// ArrowObjList.cpp: implementation of the ArrowObjList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "ArrowObjList.h"
#include "ArrowObj.h"
#include "DogRunDoc.h"
#include "AuthorPref.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 ArrowObjList::ArrowObjList()
{
 
}

ArrowObjList::~ArrowObjList()
{

}

void ArrowObjList::DrawArrows(CDC* pDC, BOOL printing, BOOL dragging)
{
	ArrowObj* pArrow;
	POSITION pos, pos_two;
	int line_number = 40;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pos_two = pos;
		pArrow = (ArrowObj*)this->GetNext(pos);
		pArrow->DrawArrow(pDC, printing, dragging);
/*
		CString out_string;
		int entry_owner, exit_owner;
		entry_owner = pArrow->GetEntryOwner();
		exit_owner = pArrow->GetExitOwner();
		if (pArrow->GetArrowSelection()) {
			out_string.Format("Selected, Exit: %d, Entry: %d  Position: %p",exit_owner, entry_owner, pos_two);
		}
		else {
			out_string.Format("Exit: %d, Entry: %d  Position: %p",exit_owner, entry_owner, pos_two);
		}
		pDC->TextOut(280,line_number,out_string);
		line_number += 20;
*/
		
	}

}

void ArrowObjList::UpdateArrowOwnerProperties(int entry_owner, int exit_owner, int new_entry, int new_exit)
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetEntryOwner() == entry_owner && pArrow->GetExitOwner() == exit_owner) {
			pArrow->SetEntryOwner(new_entry);
			pArrow->SetExitOwner(new_exit);
			return;
		}
	}
}

ArrowObj* ArrowObjList::FindArrow(int exit_owner, int entry_owner)
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		int temp_entry = pArrow->GetEntryOwner();
		int temp_exit = pArrow->GetExitOwner();
		if (pArrow->GetEntryOwner() == entry_owner && pArrow->GetExitOwner() == exit_owner) {
			return pArrow;
		}
	}
	return NULL;
}

void ArrowObjList::MoveArrowsOnStationMove(CObList *p_selectedList, RallyObjList *pRally_List, int total_number_of_stations)
{
	POSITION pos_one;
	CRallyObject *pRallyItemSelected, *pRallyItemInList;
	int station_number;
	ArrowObj* pArrow;
	int station_to_find;
	CPoint cp_entry, cp_exit;
	bool have_sit_stay = pRally_List->HaveSitStayStation();
	if (have_sit_stay)
	{
		total_number_of_stations--;
	}

	for( pos_one = p_selectedList->GetHeadPosition(); pos_one != NULL; ) {
		pRallyItemSelected = (CRallyObject*)p_selectedList->GetNext(pos_one);
		station_number = pRallyItemSelected->GetStationNumber();
		switch(station_number) {
		case FINISH_STATION:
			if (total_number_of_stations > 0) {
				pRallyItemInList = pRally_List->FindRallyStationByStationNumber(total_number_of_stations);
				station_to_find = total_number_of_stations;
		}
			else {
				pRallyItemInList = pRally_List->FindRallyStationByStationNumber(START_STATION);
				station_to_find = START_STATION;
			}
			if (pRallyItemInList != NULL) {
				pRally_List->CalculateEntryExitPoints(pRallyItemInList, pRallyItemSelected, &cp_entry, &cp_exit);
				pArrow = this->FindArrow(station_to_find, FINISH_STATION);
				if (pArrow != NULL && pArrow->GetMoveWithStation()) {
					pArrow->SetEntryPoint(&cp_entry);
					pArrow->SetExitPoint(&cp_exit);
				}
			}
			break;
		default:
			pRallyItemInList = pRally_List->FindRallyStationByStationNumber(station_number - 1);
			if (pRallyItemInList != NULL) {
				pRally_List->CalculateEntryExitPoints(pRallyItemInList, pRallyItemSelected, &cp_entry, &cp_exit);
				pArrow = this->FindArrow(station_number - 1, station_number);
				if (pArrow != NULL && pArrow->GetMoveWithStation()) {
					pArrow->SetEntryPoint(&cp_entry);
					pArrow->SetExitPoint(&cp_exit);
				}
			}
			if (station_number == total_number_of_stations) {
				pRallyItemInList = pRally_List->FindRallyStationByStationNumber(FINISH_STATION);
				if (pRallyItemInList != NULL) {
					pRally_List->CalculateEntryExitPoints(pRallyItemSelected, pRallyItemInList,  &cp_entry, &cp_exit);
					pArrow = this->FindArrow(station_number, FINISH_STATION);
					if (pArrow != NULL && pArrow->GetMoveWithStation()) {
						pArrow->SetEntryPoint(&cp_entry);
						pArrow->SetExitPoint(&cp_exit);
					}
				}
			}
			else {
				pRallyItemInList = pRally_List->FindRallyStationByStationNumber(station_number + 1);
				if (pRallyItemInList != NULL) {
					pRally_List->CalculateEntryExitPoints(pRallyItemSelected, pRallyItemInList,  &cp_entry, &cp_exit);
					pArrow = this->FindArrow(station_number, station_number + 1);
					if (pArrow != NULL && pArrow->GetMoveWithStation()) {
						pArrow->SetEntryPoint(&cp_entry);
						pArrow->SetExitPoint(&cp_exit);
					}
				}
			}			
			break;
		}
  }

	return;	
}


int ArrowObjList::CheckForLineHit(CPoint *pmouse_point, CDC *pDC, unsigned int shift_key_pressed)
{
	ArrowObj* pArrow;
	POSITION pos;
	int hit = NO_HIT, return_hit = NO_HIT;
	int handle_selected;
	bool already_selected = false;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		already_selected = pArrow->GetArrowSelection();
		hit = pArrow->HitTestCurve(*pmouse_point, pDC->m_hDC);
		if (hit && !shift_key_pressed) {
			this->UnselectAllArrows();
			pArrow->SetSelection(true);
			return_hit = SELECTED;
		}
		else if (hit && shift_key_pressed && already_selected) {
			pArrow->SetSelection(false);
		}
		else if (hit && shift_key_pressed && !already_selected) {
			pArrow->SetSelection(true);
			return_hit = SELECTED;
		}
		else if (!hit && !shift_key_pressed && already_selected) {
//			pArrow->SetSelection(false);
			return_hit = ALL_READY_SELECTED;
		}
		else if (!hit && shift_key_pressed && already_selected) {
			pArrow->SetSelection(true);
			return_hit = ALL_READY_SELECTED;
		}
		else if (!hit && shift_key_pressed && !already_selected){
			pArrow->SetSelection(false);
		}
		if (hit && !return_hit) {
			return_hit = hit;
		}
		if (return_hit == SELECTED || ALL_READY_SELECTED) {
			handle_selected = pArrow->GetHandleSelected();
			if (handle_selected != NO_HANDLE) return_hit = handle_selected;
		}
	}
	if (!return_hit) {
		for( pos = this->GetHeadPosition(); pos != NULL; ) {
			pArrow = (ArrowObj*)this->GetNext(pos);
			pArrow->SetSelection(false);
		}
	}
	return return_hit;
}

void ArrowObjList::CheckForLineInRect(CRgn *rect_to_check)
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		pArrow->CheckForLineInRect(rect_to_check);
	}
	
}

void ArrowObjList::CurveLine(CDC *pDC, CPoint *p_mouse_pt, BOOL size_to_screen)
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		pArrow->CurveLine(pDC, p_mouse_pt, size_to_screen);
	}
}

POSITION ArrowObjList::RemoveArrowsForDeletedStation(CRallyObject *p_deleted_station, RallyObjList *pRally_List, int total_number_of_stations, int *p_num_deleted)
{

	int station_number;
	ArrowObj* pArrow;
	CPoint cp_entry, cp_exit;
	cp_entry = -1;
	int entry_owner;
	POSITION pos_to_delete = NULL;
	CRallyObject* pRallyStation;	
	station_number = p_deleted_station->GetStationNumber();
	switch(station_number) {
	case START_STATION:
		if (total_number_of_stations > 0) {
			pArrow = this->FindArrow(START_STATION, 1);
			pos_to_delete = this->FindArrowPosition(START_STATION, 1);
			if (pos_to_delete != NULL) {
				this->RemoveAt(pos_to_delete);
			}
			if (pArrow != NULL) {
				if(pArrow->GetArrowSelection()) *p_num_deleted = *p_num_deleted+ 1;
				delete pArrow;
			}
		}
		else {
			pArrow = this->FindArrow(START_STATION, FINISH_STATION);
			pos_to_delete = this->FindArrowPosition(START_STATION, FINISH_STATION);
			if (pos_to_delete != NULL) {
				this->RemoveAt(pos_to_delete);
			}
			if (pArrow != NULL) {
				if(pArrow->GetArrowSelection()) *p_num_deleted = *p_num_deleted+ 1;
				delete pArrow;
			}
		}
		break;
	case FINISH_STATION:
		if (total_number_of_stations > 0) {
			pArrow = this->FindArrow(total_number_of_stations, FINISH_STATION);
			pos_to_delete = this->FindArrowPosition(total_number_of_stations, FINISH_STATION);
			if (pos_to_delete != NULL) {
				this->RemoveAt(pos_to_delete);
			}
			if (pArrow != NULL) {
				if(pArrow->GetArrowSelection()) *p_num_deleted = *p_num_deleted+ 1;
				delete pArrow;
			}
		}
		else {
			pArrow = this->FindArrow(START_STATION, FINISH_STATION);
			pos_to_delete = this->FindArrowPosition(START_STATION, FINISH_STATION);
			if (pos_to_delete != NULL) {
				this->RemoveAt(pos_to_delete);
			}
			if (pArrow != NULL) {			
				if(pArrow->GetArrowSelection()) *p_num_deleted = *p_num_deleted+ 1;
				delete pArrow;
			}
		}
		break;
	case HONOR_STATION: // should not have any arrows to delete!
		break;
	default:
		if (total_number_of_stations== station_number) {
			pArrow = this->FindArrow(station_number, FINISH_STATION);
			pos_to_delete = this->FindArrowPosition(station_number, FINISH_STATION);

			if (pArrow == NULL) { // no finish station
				pArrow = this->FindArrow(station_number-1, station_number);
				pos_to_delete = this->FindArrowPosition(station_number-1, station_number);
			}

			if (pos_to_delete != NULL) {
				this->RemoveAt(pos_to_delete);
			}
			if (pArrow != NULL) {
				cp_entry = pArrow->GetEntryPoint();
				entry_owner = pArrow->GetEntryOwner();
				if(pArrow->GetArrowSelection()) *p_num_deleted = *p_num_deleted+ 1;
				delete pArrow;
			}
			pArrow = this->FindArrow(station_number-1, station_number); //note I might delete this above!!
			if (pArrow != NULL) {
				pArrow->SetEntryPoint(&cp_entry);
				pArrow->SetEntryOwner(entry_owner);
			}
		}
		else {
			pArrow = this->FindArrow(station_number, station_number+1);
			pos_to_delete = this->FindArrowPosition(station_number, station_number+1);
			if (pos_to_delete != NULL) {
				this->RemoveAt(pos_to_delete);
			}
			if (pArrow != NULL) {
				cp_entry = pArrow->GetEntryPoint();
				entry_owner = pArrow->GetEntryOwner();
				if(pArrow->GetArrowSelection()) *p_num_deleted = *p_num_deleted+ 1;
				delete pArrow;
			}
			// first fix the arrow that was attached to entrance
			pArrow = this->FindArrow(station_number-1, station_number);
			
			if (pArrow != NULL) {
				if (cp_entry.x == -1) {
					pRallyStation = pRally_List->FindRallyStationByStationNumber(station_number+1);
					if (pRallyStation) {
						pRallyStation->GetCustomEntrancePoint(&cp_entry);
						pArrow->SetEntryPoint(&cp_entry);
						pArrow->SetEntryOwner(station_number);
					}
				}
				else {
					pArrow->SetEntryPoint(&cp_entry);
					if (entry_owner < 0) pArrow->SetEntryOwner(entry_owner);
				}
			}
			// now need to re-assign arrows that are connected to stations above this one
			int num_stations = pRally_List->GetLastNumber();
			int i;
			for (i = station_number + 1;i <= num_stations; i++) {
				pArrow = this->FindArrow(i, i+1);
				if (pArrow) {
					pArrow->SetEntryOwner(i);
					pArrow->SetExitOwner(i-1);
				}
			}
			pArrow = this->FindArrow(num_stations, FINISH_STATION);
			if (pArrow) {
				pArrow->SetExitOwner(num_stations-1);
			}
		}
		break;
	}
	return pos_to_delete;


}

POSITION ArrowObjList::FindArrowPosition(int exit_owner, int entry_owner)
{
	ArrowObj* pArrow;
	POSITION pos, pos_found;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pos_found = pos;
		pArrow = (ArrowObj*)this->GetNext(pos);
		int temp_entry = pArrow->GetEntryOwner();
		int temp_exit = pArrow->GetExitOwner();
		if (pArrow->GetEntryOwner() == entry_owner && pArrow->GetExitOwner() == exit_owner) {
			return pos_found;
		}
	}
	return NULL;
}

void ArrowObjList::MoveSelectedArrows(CPoint *p_amt_changed)
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection() && pArrow->m_handle_selected == NO_HANDLE) {
			pArrow->SetDrawPoints(p_amt_changed);
		}
	}
	
}

void ArrowObjList::DrawMovingArrows(CDC *pDC)
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection() && pArrow->m_handle_selected == NO_HANDLE) {
			pArrow->DrawArrow(pDC,false, true);
		}
	}
}


BOOL ArrowObjList::AnyArrowSelected()
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()){ // && pArrow->GetEntryOwner() == NO_OWNER) {// WHY THIS EXCEPTION?
			return true;
		}
	}
	return false;
}

void ArrowObjList::DeleteSelectedArrows()
{
	ArrowObj* pArrow;
	POSITION pos, pos_of_item;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pos_of_item = pos;
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()) {
			this->RemoveAt(pos_of_item);
			delete pArrow;
		}
	}

}

int ArrowObjList::AddSelectedArrowsToUndoList(CObList *p_undo_list, int undo_action, int *how_many_items, int total_all_ready_deleted)
{
	ArrowObj* pArrow, *pArrowObj;
	POSITION pos_one, pos_two;
	int  num_items_added = 0;
	num_items_added = total_all_ready_deleted;

	for( pos_one = this->GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;
		pArrow = (ArrowObj*)this->GetNext(pos_one);
		if (pArrow->GetArrowSelection()) { // && pArrow->m_entry_owner == NO_OWNER) {
			CPoint tempPoint(0,0);
			pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
			this->CopyArrowObjectData(pArrowObj,pArrow);
			num_items_added++;
			if (*how_many_items == 1) {
				pArrowObj->SetUndoRedoAction(undo_action);
			}
			else {
				if (undo_action == MOVE_STATION) {
					if (num_items_added == 1) pArrowObj->SetUndoRedoAction(MULMOVE_START);
					else if(num_items_added == *how_many_items) pArrowObj->SetUndoRedoAction(MULMOVE_END);
					else pArrowObj->SetUndoRedoAction(MULMOVE);
				}
				if (undo_action == DELETE_STATION) {
					if (num_items_added == 1) pArrowObj->SetUndoRedoAction(MULDEL_START);
					else if(num_items_added == *how_many_items) pArrowObj->SetUndoRedoAction(MULDEL_END);
					else pArrowObj->SetUndoRedoAction(MULDEL);
				}

			}
			pArrowObj->SetUndoRedoPosition(pos_two);
			p_undo_list->AddTail(pArrowObj);
		}

	}
	return num_items_added;
}

void ArrowObjList::CopyArrowObjectData(ArrowObj *dest, ArrowObj *src)
{
	CPoint draw_points[16];
	dest->m_arrow_pen = src->m_arrow_pen;
	dest->m_arrow_type = src->m_arrow_type;
	dest->m_entry_point = src->m_entry_point;
	dest->m_exit_point = src->m_exit_point;
	dest->m_entry_owner = src->m_entry_owner;
	dest->m_exit_owner = src->m_exit_owner;
	dest->SetSelection(false);
	dest->m_arrow_type = src->m_arrow_type;
	dest->m_mouse_pt = (0,0);
	dest->m_handle_selected = NO_HANDLE;
// intilize points array
//	dest->IntilizeDrawPoints();
	src->GetDrawPointsArray(draw_points);
	dest->SetDrawPointsArray(draw_points);
	dest->m_mid_point = src->m_mid_point;
	dest->SetHideArrow(src->GetHideArrow());
	dest->SetGrabHandleRects();
}

void ArrowObjList::UnselectAllArrows()
{
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		pArrow->SetSelection(false);
		
	}

}

int ArrowObjList::HowManySelectedArrows()
{
	ArrowObj* pArrow;
	POSITION pos;
	int how_many_stations = 0;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()) //  why was i doing this???? && pArrow->m_entry_owner == NO_OWNER) 
			how_many_stations++;
	}
	return how_many_stations;
}

int ArrowObjList::HowManySelectedArrowsWithoutOwners()
{
	ArrowObj* pArrow;
	POSITION pos;
	int how_many_stations = 0;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection() && pArrow->m_entry_owner == NO_OWNER) 
			how_many_stations++;
	}
	return how_many_stations;
}

int ArrowObjList::GetTotalSelected()
{
	int total = 0;
	ArrowObj* pArrow;
	POSITION pos;

	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()) total++;
	}	
	return total;
}

void ArrowObjList::StraightenSelectedArrows()
{
	ArrowObj* pArrow;
	POSITION pos;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()) pArrow->StraightenArrow();
	}	

}

void ArrowObjList::ReverseSelectedArrows()
{
	ArrowObj* pArrow;
	POSITION pos;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()) pArrow->ReverseArrow();
	}
}

void ArrowObjList::ChangeArrowProperties()
{
	AuthorPref author_pref;
	ArrowObj* pArrow;
	POSITION pos;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (pArrow->GetArrowSelection()) pos = NULL;
	}
	author_pref.m_move_arrow = pArrow->m_move_with_station;
	int response = author_pref.DoModal(&pArrow->GetArrowPen(),pArrow->GetArrowType(), false);
	if (response == IDOK) {
		pArrow->SetArrowType(author_pref.m_line_type);
		pArrow->SetPenForArrow(PS_SOLID,atoi(author_pref.m_line_thickness), author_pref.m_log_pen.lopnColor);
		pArrow->m_move_with_station = author_pref.m_move_arrow;
	}


}

void ArrowObjList::CleanupArrow(RallyObjList *pRally_List)
{

	POSITION pos_one, pos_two;
	CRallyObject *pFirstRallyItem, *pSecondRallyItem, *pFinishStation;
	ArrowObj* pArrow;
	CPoint exit_point, entry_point;
	bool have_finish = false;
	int station_number;
	int num_stations = pRally_List->GetLastNumber();
	pFinishStation = pRally_List->FindRallyStationByStationNumber(FINISH_STATION);
	if (pFinishStation) have_finish = true;
	for( pos_one = pRally_List->GetHeadPosition(); pos_one != NULL; ) {
		pFirstRallyItem = (CRallyObject*)pRally_List->GetNext(pos_one);
		station_number = pFirstRallyItem->GetStationNumber();
		if (station_number == START_STATION) {
			pArrow = this->FindArrow(START_STATION,1);
			if (pArrow) {
				pSecondRallyItem = pRally_List->FindRallyStationByStationNumber(1);
				if (pSecondRallyItem) {
					pRally_List->CalculateEntryExitPoints(pFirstRallyItem,pSecondRallyItem,&entry_point,&exit_point);
					pArrow->SetEntryPoint(&entry_point);
					pArrow->SetExitPoint(&exit_point);
				}

			}
		}
		else if (station_number == num_stations) {
			pArrow = this->FindArrow(station_number,FINISH_STATION);
			if (pArrow) {
				pSecondRallyItem = pRally_List->FindRallyStationByStationNumber(FINISH_STATION);
				if (pSecondRallyItem) {
					have_finish = true;
					pRally_List->CalculateEntryExitPoints(pFirstRallyItem,pSecondRallyItem,&entry_point,&exit_point);
					pArrow->SetEntryPoint(&entry_point);
					pArrow->SetExitPoint(&exit_point);
				}

			}
		}
		else {
			pArrow = this->FindArrow(station_number,station_number+1);
			if (pArrow) {
				pSecondRallyItem = pRally_List->FindRallyStationByStationNumber(station_number+1);
				if (pSecondRallyItem) {
					pRally_List->CalculateEntryExitPoints(pFirstRallyItem,pSecondRallyItem,&entry_point,&exit_point);
					pArrow->SetEntryPoint(&entry_point);
					pArrow->SetExitPoint(&exit_point);
				}

			}
		}
		
	}

	int how_many_stations = pRally_List->GetCount();
	for( pos_one = this->GetHeadPosition(); pos_one != NULL; ) {
		pos_two = pos_one;
		pArrow = (ArrowObj*)this->GetNext(pos_one);
		if (pArrow->m_entry_owner > num_stations) {
			this->RemoveAt(pos_two);
			if (pArrow != NULL) {
				delete pArrow;
			}
		}
		if (pArrow->m_entry_owner == FINISH_STATION && !have_finish) {
			this->RemoveAt(pos_two);
			if (pArrow != NULL) {
				delete pArrow;
			}
		}
	}
	
}

void ArrowObjList::UpdateArrowListOnRallyInsert(int station_number, int num_stations)
{
	int i;
	ArrowObj* pArrow;

	for (i = num_stations;i >= station_number; i--) {
		pArrow = this->FindArrow(i, i+1);
		if (pArrow) {
			pArrow->SetEntryOwner(i+2);
			pArrow->SetExitOwner(i+1);
		}
	}
	pArrow = this->FindArrow(num_stations, FINISH_STATION);
	if (pArrow) {
		pArrow->SetExitOwner(num_stations+1);
	}
}

void ArrowObjList::AddArrowsForDeletedStationToUndoList(CRallyObject *p_deleted_station, CObList *p_undo_list, int total_number_of_stations)
{
	// DO NOT USE !!!!!!!!!
	int station_number;
	ArrowObj* pArrow, *pArrowObj;
	CPoint tempPoint(0,0);

	POSITION pos_to_insert = NULL;
	station_number = p_deleted_station->GetStationNumber();
	switch(station_number) {
	case START_STATION:
		pArrow = this->FindArrow(START_STATION, 1);
		if (pArrow != NULL) {
			pos_to_insert = this->FindArrowPosition(START_STATION, 1);
			pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
			this->CopyArrowObjectData(pArrowObj,pArrow);
			pArrowObj->SetUndoRedoPosition(pos_to_insert);
			pArrowObj->SetUndoRedoAction(MULDEL);
			p_undo_list->AddTail(pArrowObj);
		}
		else {
			pArrow = this->FindArrow(START_STATION, FINISH_STATION);
			if (pArrow != NULL) {
				pos_to_insert = this->FindArrowPosition(START_STATION, FINISH_STATION);
				pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
				this->CopyArrowObjectData(pArrowObj,pArrow);
				pArrowObj->SetUndoRedoPosition(pos_to_insert);
				pArrowObj->SetUndoRedoAction(MULDEL);
				p_undo_list->AddTail(pArrowObj);
			}
		}
		break;
	case FINISH_STATION:
		pArrow = this->FindArrow(total_number_of_stations, FINISH_STATION);
		if (pArrow != NULL) {
			pos_to_insert = this->FindArrowPosition(total_number_of_stations, FINISH_STATION);
			pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
			this->CopyArrowObjectData(pArrowObj,pArrow);
			pArrowObj->SetUndoRedoPosition(pos_to_insert);
			pArrowObj->SetUndoRedoAction(MULDEL);
			p_undo_list->AddTail(pArrowObj);
		}
		else {
			pArrow = this->FindArrow(START_STATION, FINISH_STATION);
			if (pArrow != NULL) {
				pos_to_insert = this->FindArrowPosition(START_STATION, FINISH_STATION);
				pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
				this->CopyArrowObjectData(pArrowObj,pArrow);
				pArrowObj->SetUndoRedoPosition(pos_to_insert);
				pArrowObj->SetUndoRedoAction(MULDEL);
				p_undo_list->AddTail(pArrowObj);
			}
		}
		break;
	default:
		if (total_number_of_stations == station_number) {
			pArrow = this->FindArrow(station_number, FINISH_STATION);
			if (pArrow != NULL) {
				pos_to_insert = this->FindArrowPosition(station_number, FINISH_STATION);
				pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
				this->CopyArrowObjectData(pArrowObj,pArrow);
				pArrowObj->SetUndoRedoPosition(pos_to_insert);
				pArrowObj->SetUndoRedoAction(MULDEL);
				p_undo_list->AddTail(pArrowObj);
			}
			else {
				pArrow = this->FindArrow(station_number-1, station_number); 
				if (pArrow != NULL) {
					pos_to_insert = this->FindArrowPosition(station_number-1, station_number);
					pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
					this->CopyArrowObjectData(pArrowObj,pArrow);
					pArrowObj->SetUndoRedoPosition(pos_to_insert);
					pArrowObj->SetUndoRedoAction(MULDEL);
					p_undo_list->AddTail(pArrowObj);
				}
			}
		}
		else {
			pArrow = this->FindArrow(station_number, station_number+1);
			if (pArrow != NULL) {
				pos_to_insert = this->FindArrowPosition(station_number-1, station_number);
				pArrowObj = new ArrowObj(&tempPoint,&tempPoint,&pArrow->GetArrowPen(),NO_OWNER,NO_OWNER, pArrow->GetArrowType(),pArrow->GetMoveWithStation(), pArrow->GetHideArrow());		
				this->CopyArrowObjectData(pArrowObj,pArrow);
				pArrowObj->SetUndoRedoPosition(pos_to_insert);
				pArrowObj->SetUndoRedoAction(MULDEL);
				p_undo_list->AddTail(pArrowObj);
			}
		}
		break;
	}


}


void ArrowObjList::SelectAllArrows(bool include_owned_arrows)
{
	ArrowObj* pArrow;
	POSITION pos;
	int how_many_stations = 0;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pArrow = (ArrowObj*)this->GetNext(pos);
		if (include_owned_arrows) {
			pArrow->SetSelection(true);
		}
		else if (pArrow->m_entry_owner == NO_OWNER && !include_owned_arrows) {
			pArrow->SetSelection(true);
		}
			
	}

}
