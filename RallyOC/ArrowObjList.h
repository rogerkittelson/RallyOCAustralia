// ArrowObjList.h: interface for the ArrowObjList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARROWOBJLIST_H__CE9ED594_7F3C_454B_A6FE_C9D064C99B3F__INCLUDED_)
#define AFX_ARROWOBJLIST_H__CE9ED594_7F3C_454B_A6FE_C9D064C99B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrowObj.h"
#include "RallyObjList.h"

class ArrowObjList : public CObList  
{
public:
	void SelectAllArrows(bool include_owned_arrows);
	int HowManySelectedArrowsWithoutOwners(void);
	void AddArrowsForDeletedStationToUndoList(CRallyObject *p_deleted_station, CObList *p_undo_list, int total_number_of_stations);
	void UpdateArrowListOnRallyInsert(int rally_num_inserted,int total_num_stations);
	void CleanupArrow(RallyObjList *pRally_List);
	void ChangeArrowProperties(void);
	void ReverseSelectedArrows(void);
	void StraightenSelectedArrows(void);
	int GetTotalSelected(void);
	int HowManySelectedArrows(void);
	void UnselectAllArrows(void);
	void CopyArrowObjectData(ArrowObj *dest, ArrowObj *src);
	int AddSelectedArrowsToUndoList(CObList  *p_undo_list, int undo_action, int *how_many_items, int total_all_ready_deleted);
	void DeleteSelectedArrows(void);
	BOOL AnyArrowSelected(void);
	void DrawMovingArrows(CDC* pDC);
	void MoveSelectedArrows(CPoint *p_amt_changed);
	POSITION FindArrowPosition(int exit_owner, int entry_owner);
	POSITION RemoveArrowsForDeletedStation(CRallyObject *p_deleted_station, RallyObjList *pRally_List, int total_number_of_stations, int *p_num_deleted);
	void CurveLine(CDC *pDC, CPoint *p_mouse_pt, BOOL size_to_screen);
	void CheckForLineInRect(CRgn *rect_to_check);
	int CheckForLineHit(CPoint *mouse_point, CDC *pDC,unsigned int shift_key_pressed);
	void MoveArrowsOnStationMove(CObList *p_selectedList, RallyObjList *pRally_List, int total_number_of_stations);
	ArrowObj* FindArrow(int exit_owner, int entry_owner);
	void UpdateArrowOwnerProperties(int entry_owner, int exit_owner, int new_entry, int new_exit);
	void DrawArrows(CDC* pDC, BOOL printing, BOOL dragging);
	virtual ~ArrowObjList();
	ArrowObjList();
};

#endif // !defined(AFX_ARROWOBJLIST_H__CE9ED594_7F3C_454B_A6FE_C9D064C99B3F__INCLUDED_)
