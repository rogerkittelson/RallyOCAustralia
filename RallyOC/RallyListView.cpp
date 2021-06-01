
#include "StdAfx.h"
#include "RallyListView.h"
#include "DogRun.h"
#include "DogRunDoc.h"
#include "StationMapper.h"
//
//	RallyListView::RallyListView
//
RallyListView::RallyListView() : CGridCtrl() {
	// set all checkboxes to CHECKED
	FillMemory(mChecks, CHECK_COUNT, 1);
}


//
//	RallyListView::PreSubclassWindow
//
void RallyListView::PreSubclassWindow(void) {
	CGridCtrl::PreSubclassWindow();
/*	
	// init popup menu
	mMenu.CreatePopupMenu();
	mMenu.AppendMenu(MF_STRING, 1, TEXT("You can fill"));
	mMenu.AppendMenu(MF_STRING, 2, TEXT("this popup menu..."));
	mMenu.AppendMenu(MF_SEPARATOR);
	mMenu.AppendMenu(MF_STRING, 3, TEXT("...with whatever you like"));
	*/
}

//
//	RallyListView::OnDestroy
//
void RallyListView::OnDestroy() {
	CGridCtrl::OnDestroy();
}

//
//	RallyListView::OnGetComboBoxItems
//
void RallyListView::OnGetComboBoxItems(IN  int Row, IN  int Col, OUT bool& HasImages, OUT CStringList& Items, OUT CArray<int, int>& Images) {
	// first of all, call the parent implementation
	// NOTE: do it for all CGridCtrl virtual methods!
	CGridCtrl::OnGetComboBoxItems(Row, Col, HasImages, Items, Images);
	int i;

	CString add_string;
	// fill the combo boxs 
	if (Col == 1) {
		for (i=1;i<=50;i++) {
			add_string.Format("%d",i);
			Items.AddTail(TEXT(add_string));
		}

	}
	if (Col == 2) {
		StationMapper::GetStationDescriptionByAKCType(this->m_class_type,Items);
	}

	// I don't want combo images
	HasImages = false;
}

//
//	RallyListView::OnGetCellColors
//
bool RallyListView::OnGetCellColors(IN  int Row, IN  int Col, OUT COLORREF& TextColor, OUT COLORREF& BkColor, OUT UINT8& TextStyle) const {
	// NOTE: this routine is called VERY often by the painting routines. keep it
	//       as small/fast as possible!
	// NOTE: if you are comfortable with the default colors of the current cell,
	//       you should return FALSE, instead of returning TRUE and leaving the
	//       colors unchanged. this will increase drawing speed...

	if (mDraw.Type == CELL_SEPARATOR)
		return false;

	switch (Col)
	{
		case 0:
			TextStyle = FONT_BOLD;
			break;
		case 1:
			TextStyle = FONT_ITALIC;
			break;
		case 2:
			TextStyle = FONT_UNDERLINE;
			break;
		case 3:
			TextStyle = FONT_STRIKEOUT;
			break;
		case 4:
			TextStyle = FONT_BOLD | FONT_ITALIC;
			break;
		case 5:
			TextStyle = FONT_UNDERLINE | FONT_STRIKEOUT;
			break;
	}

	// change the background of even rows
	if (Row % 2 == 0 && !mDraw.Selected)
	{
		AdjustBrightness(BkColor, -15);
		AdjustBrightness(TextColor, 60);
		return true;
	}
	return (TextStyle != 0);
}

//
//	RallyListView::OnGetCellType
//
CellType RallyListView::OnGetCellType(IN int Row, IN int Col) {
	// NOTE: this routine is called VERY often by the painting routines. keep it
	//       as small/fast as possible!
	switch (Col)
	{
	case 0:
		return CELL_EDITBOX;
		break;

	case 1:
		return CELL_EDITBOX;
		break;

	case 2:
		return CELL_COMBOBOX;
		break;
	}
	return CELL_REGULAR;
}

//
//	RallyListView::OnCheckBoxClick
//
void RallyListView::OnCheckBoxClick(IN int Row, IN int Col) {
	// change the CHECKED state of this check box
	mChecks[Row] = !mChecks[Row];

	// supercall default implementation for repainting the cell
	CGridCtrl::OnCheckBoxClick(Row, Col);
}

//
//	RallyListView::OnCustomCellClick
//
void RallyListView::OnCustomCellClick(int Row, int Col) {
	CString sTemp;
	sTemp.Format(TEXT("Custom edit @ (%d, %d)\nYou could pop up a \"details\" dialog or something..."), Row + 1, Col + 1);
	MessageBox(sTemp, TEXT("CGridCtrl"), MB_ICONINFORMATION);
	
}

//
//	RallyListView::AdjustBrightness
//
void RallyListView::AdjustBrightness(IN OUT COLORREF& Color, IN INT16 Amount) const {
	INT32 comp = GetRValue(Color) + Amount;
	if (comp > 255) comp = 255;
	else if (comp < 0) comp = 0;
	Color = (Color & 0xffffff00) | comp;

	comp = GetGValue(Color) + Amount;
	if (comp > 255) comp = 255;
	else if (comp < 0) comp = 0;
	Color = (Color & 0xffff00ff) | (comp << 8);

	comp = GetBValue(Color) + Amount;
	if (comp > 255) comp = 255;
	else if (comp < 0) comp = 0;
	Color = (Color & 0xff00ffff) | (comp << 16);
	
}

//
//	RallyListView::OnRClick
//
void RallyListView::OnCellRBtnUp(IN int Row, IN int Col, IN const RECT *CellRect, IN const CPoint& Point) {
	POINT pt = { Point.x, Point.y };
	ClientToScreen(&pt);
	mMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	
}

void RallyListView::UpdateRallyList(int index, int akc_number) {

	CDogRunDoc *p_dogRunDoc;
	p_dogRunDoc = (CDogRunDoc*)this->pDoc;
	p_dogRunDoc->UpdateRallyList(index,akc_number,NULL);

}
BOOL RallyListView::RenumberStation(int index, int new_number) {
	POSITION pos;
	CRallyObject* pRallyItemInlist;
	CDogRunDoc *p_dogRunDoc;
	p_dogRunDoc = (CDogRunDoc*)this->pDoc;
	pos = this->mp_rallyList->FindIndex(index);
	if (pos == NULL) return false;
	pRallyItemInlist = (CRallyObject*)this->mp_rallyList->GetAt(pos);
	
	int old_number = pRallyItemInlist->GetStationNumber();
	if (old_number == new_number) return false;
	int akc_number = pRallyItemInlist->GetAKCNumber();

	
	if (akc_number == 1 || akc_number == 2 ) return false; //START, FINISH 
	p_dogRunDoc->AddUndoStation(pRallyItemInlist, pos,INSERT_AT);
	p_dogRunDoc->RenumberStations(new_number, INSERT_AT, pRallyItemInlist, false);
	this->pDoc->UpdateAllViews(NULL,CHANGE_STATION,NULL);
	return true;
}
bool RallyListView::OnEndInPlaceEdit(IN int Row, IN int Col, IN bool Canceled, IN const TCHAR* Text, IN int Image) {
	if (this->mComboIndex >= 0) {
		int akc_number, new_station_number;
		CString station_description, akc_No_String, old_string;

		if (Row < (this->mNumRows - 1)) {
			if (Col == 0) {
				new_station_number = atoi(Text);
				if (new_station_number <= 0 || new_station_number > this->m_num_stations){
					old_string = this->GetItemText(Row,Col);
					Text = old_string;
					Canceled = true;
				}
				else {
					if (!this->RenumberStation(Row,new_station_number)) {
						old_string = this->GetItemText(Row,Col);
						Text = old_string;
						Canceled = true;
					}
				}
			}
			if (Col ==1) {		
				akc_number = atoi(Text);
				old_string = this->GetItemText(Row,Col);
				if (!strcmp(old_string,"1") || !strcmp(old_string,"2")) {
					Text = old_string;
					Canceled = true;
				}
				else if (akc_number >= 1 && akc_number <= this->m_class_type  && !this->CheckForExistingStartFinishHonor(akc_number)) {
// TODO: need to revise this routine to use new station number!!!
					//					station_description = this->akc_station_names[akc_number];
					CGridCtrl::OnEndInPlaceEdit(Row, 2, Canceled, station_description, Image);
					this->UpdateRallyList(Row,akc_number);\
				}
				else {
					Text = old_string;
					Canceled = true;
				}
				
			}
			if (Col == 2) {
				old_string = this->GetItemText(Row,1);
				akc_number = StationMapper::GetAKCidFromComboBoxSelection(this->mComboIndex);
				if (!strcmp(old_string,"1") || !strcmp(old_string,"2") || !strcmp(old_string,"299") || (akc_number==299)) {
					Canceled = true;
				}
				else if (!this->CheckForExistingStartFinishHonor(akc_number)) {
					akc_No_String.Format("%d",akc_number);
					CGridCtrl::OnEndInPlaceEdit(Row, 1, Canceled, akc_No_String, Image);
					this->UpdateRallyList(Row,akc_number);
				}
				else {
					Canceled = true;
//					old_string = this->GetItemText(Row,Col);
//					Text = old_string;
				}

			}
		}
		if (Row == (this->mNumRows-1)) {
			// insert new station into list
			if (Col ==1) {		
				akc_number = atoi(Text);
				if (akc_number >= 1 && akc_number <= this->m_class_type) {
					if (!this->InsertStationIntoList(akc_number)) {
						Text = "";
					}
				}
				else {
					Text = "";
				}
			}
			
			if (Col == 2) {
				akc_number = this->mComboIndex + 1;
				if (!this->InsertStationIntoList(akc_number)) {
					Text = "";
				}
			}

		}
	}
	return CGridCtrl::OnEndInPlaceEdit(Row, Col, Canceled, Text, Image);

}
BOOL RallyListView::CheckForExistingStartFinishHonor(int akc_num) {
	POSITION pos;
	CRallyObject* pRallyItem;
	pos = this->mp_rallyList->GetHeadPosition();
	if (pos == NULL) return false;
	switch (akc_num) {
	case 1:
		pRallyItem = (CRallyObject*)this->mp_rallyList->GetNext(pos);
		if (pRallyItem->GetAKCNumber() == 1) return true;
		break;
	case 2:
		pRallyItem = (CRallyObject*)this->mp_rallyList->GetTail();
		if (pRallyItem->GetAKCNumber() == 2) return true;
		break;
	default:
		return false;
		break;
	}
return false;
}
BOOL RallyListView::InsertStationIntoList(int akc_number) {
	CRallyObject* pRallyItem, *pRallyNormalStation;
	CDogRunDoc *p_dogRunDoc;
	POSITION pos;
	CPoint off_set_pt (1,1);
	CPoint insert_pt (80,60);
	CPoint sp (0,0);
	int num_stations;
	p_dogRunDoc = (CDogRunDoc*)this->pDoc;
	POSITION win_pos = p_dogRunDoc->GetFirstViewPosition();
	if (win_pos != NULL) {
		CScrollView* pView = (CScrollView*)p_dogRunDoc->GetNextView(win_pos);
		sp = pView->GetScrollPosition();
	} 
	insert_pt += sp;
	
	pRallyItem = new CRallyObject(StationMapper::GetBitMapFromAKCNumber(akc_number),StationMapper::ObjectIDFromAKCNumber(akc_number), AKC_COURSE,  akc_number,insert_pt.x, insert_pt.y);		
	pRallyItem->SetSelectedFlag(FALSE);
	if (akc_number == 1) {
		pRallyItem->SetStationNumber(START_STATION);
		pos = p_dogRunDoc->InsertStationIntoList(pRallyItem, START_STATION, false);
	}
	else if (akc_number == 2) {
		pRallyItem->SetStationNumber(FINISH_STATION);
		pos = p_dogRunDoc->InsertStationIntoList(pRallyItem, FINISH_STATION, false);
	}
	else {
		num_stations = p_dogRunDoc->GetNumberStations();
		num_stations++;
		pRallyItem->SetStationNumber(num_stations);
		p_dogRunDoc->InsertStationIntoPopupMenu(pRallyItem);
		pos = p_dogRunDoc->InsertStationIntoList(pRallyItem, num_stations, false);
	}
	if (pos == NULL) {
		delete pRallyItem;
		return false;
	}
	else {
		while(this->CheckRallyRectInRallyRect(pRallyItem)) {
			pRallyItem->OffSetStationRect(&off_set_pt);
			off_set_pt.Offset(1,1);
		}		
		p_dogRunDoc->AddUndoStation(pRallyItem,pos,ADD_STATION);

// auto add normal station		
		if (akc_number == 17 || akc_number == 18 || akc_number == 28) {
			if (p_dogRunDoc->m_course_info->GetAutoAddNormalStation()) {
				pRallyNormalStation = new CRallyObject(StationMapper::GetBitMapFromAKCNumber(19),StationMapper::ObjectIDFromAKCNumber(19), AKC_COURSE,  19,insert_pt.x, insert_pt.y);		
				pRallyNormalStation->SetSelectedFlag(FALSE);
				num_stations++;
				pRallyNormalStation->SetStationNumber(num_stations);
				p_dogRunDoc->InsertStationIntoPopupMenu(pRallyNormalStation);
				pos = p_dogRunDoc->InsertStationIntoList(pRallyNormalStation, num_stations, false);
				while(this->CheckRallyRectInRallyRect(pRallyItem)) {
					pRallyNormalStation->OffSetStationRect(&off_set_pt);
					off_set_pt.Offset(1,1);
				}
				p_dogRunDoc->AddUndoStation(pRallyNormalStation,pos,ADD_STATION);
			}
		}
		
		this->pDoc->UpdateAllViews(NULL,CHANGE_STATION,NULL);
	}
	return true;
}
BOOL  RallyListView::CheckRallyRectInRallyRect(CRallyObject* pRallyItemToCheck) {
	CRgn rallyRectRgn;

	RECT selectedRect = pRallyItemToCheck->GetStationRect();
	if (!rallyRectRgn.CreateRectRgn(selectedRect.left,selectedRect.top,selectedRect.right,selectedRect.bottom)) {
		return false;
	}
	
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	
	for( pos = this->mp_rallyList->GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->mp_rallyList->GetNext(pos);
		if (pRallyItemToCheck != pRallyItemInlist && pRallyItemInlist->RallyRectInRegion(&rallyRectRgn))
			return true;
	}	
	return false;
}

void RallyListView::SetUpRallyList(CObList *p_rallyList, CDocument *pDoc) {

	CString row_data;
	POSITION pos;
	CRallyObject* pRallyItemInlist;
	int ROWS;
	int total_items, akc_number;
	if (!IsWindow(this->m_hWnd)) return;	
	total_items = this->DeleteAllItems();	
	this->DeleteColumn(2);
	this->DeleteColumn(1);
	this->DeleteColumn(0);
	CString col_title;
	col_title = "No." ;
	this->InsertColumn(0, col_title, LVCFMT_LEFT, 60, 0);
	col_title = "ANKC No." ;
	this->InsertColumn(1, col_title, LVCFMT_LEFT, 60, 1);
	col_title = "Station Description"; 
	this->InsertColumn(2, col_title, LVCFMT_LEFT, 240, 2);	
	
	if (p_rallyList == NULL) {
		return;
	}
	m_num_stations = 0;
	mp_rallyList = p_rallyList;
	this->pDoc = pDoc;
	// rows...
	LVITEM item;
	item.mask = LVIF_TEXT;
	ROWS = mp_rallyList->GetCount();
	this->mNumRows = ROWS;
	pos = mp_rallyList->GetHeadPosition();
	for (int i = 0; i < ROWS; i++)
	{
		pRallyItemInlist = (CRallyObject*)mp_rallyList->GetNext(pos);

		akc_number = pRallyItemInlist->GetAKCNumber();
		if( akc_number == 1 || akc_number == 2) {
			row_data.Format(TEXT(""));
		}
		else {
			row_data.Format(TEXT("%d"), pRallyItemInlist->GetStationNumber());
			this->m_num_stations++;
		}

		item.pszText = row_data.GetBuffer(0);
		item.iItem = i;
		item.iSubItem = 0;
		this->InsertItem(&item);
			
		row_data.Format(TEXT("%d"), pRallyItemInlist->GetAKCNumber());
		item.pszText = row_data.GetBuffer(0);
		item.iSubItem  = 1;
		this->SetItem(&item);

		row_data=  StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber());
		item.pszText = row_data.GetBuffer(0);
		item.iSubItem  = 2;
		this->SetItem(&item);

	}
	// always one blank row

	this->InsertBlankRow();
	// need to get the course information to set-up dropdown list
	CDogRunDoc *p_dogRunDoc;
	CourseInfo course_info;

	p_dogRunDoc = (CDogRunDoc*)this->pDoc;
	p_dogRunDoc->m_course_info->GetCourseInfo(&course_info);
	this->m_class_type = course_info.m_class;
}
void RallyListView::InsertBlankRow(void) {
	CString row_data;
	int num_items;
	LVITEM item;
	item.mask = LVIF_TEXT;
	num_items = this->GetItemCount() + 1;
	row_data.Format(TEXT(""));
	item.pszText = row_data.GetBuffer(0);
	item.iItem = num_items;
	item.iSubItem = 0;
	this->InsertItem(&item);
	item.iSubItem  = 1;
	this->SetItem(&item);
	item.iSubItem  = 2;
	this->SetItem(&item);
	this->mNumRows++;
}