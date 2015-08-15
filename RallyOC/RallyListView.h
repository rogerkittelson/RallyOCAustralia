
#pragma once

#include "CGridCtrl.h"
#include "RallyObject.h"

#define CHECK_COUNT	9

//
//	class RallyListView
//
class RallyListView: public CGridCtrl
{
public:
	RallyListView();
	void SetUpRallyList(CObList *p_rallyList, CDocument *pDoc);
protected:
	int GetNumberofNonPylonStations(void);
	int m_num_stations;
	void UpdateRallyList(int index,int akc_number);
	void OnGetComboBoxItems(IN  int Row, IN  int Col, OUT bool& HasImages, OUT CStringList& Items, OUT CArray<int, int>& Images);
	BOOL CheckRallyRectInRallyRect(CRallyObject* pRallyItemToCheck);
	bool OnGetCellColors(IN  int Row, IN  int Col, OUT COLORREF& TextColor, OUT COLORREF& BkColor, OUT UINT8& TextStyle) const;

	CellType OnGetCellType(IN int Row, IN int Col);

	void OnCheckBoxClick(IN int Row, IN int Col);

	void OnCustomCellClick(IN int Row, IN int Col);

	virtual void	PreSubclassWindow(void);
	virtual void	OnDestroy();

	void OnCellRBtnUp(IN int Row, IN int Col, IN const RECT *CellRect, IN const CPoint& Point);
	bool OnEndInPlaceEdit (IN int Row,IN int Col, IN bool Canceled, IN const TCHAR* Text, IN int Image);
	void InsertBlankRow(void);
	BOOL InsertStationIntoList(int akc_number);
	BOOL CheckForExistingStartFinishHonor(int station_type);
	BOOL RenumberStation(int index, int new_number);
	CObList *mp_rallyList;
	CDocument *pDoc;
	int m_class_type;

private:
	void AdjustBrightness(	IN OUT COLORREF& Color, IN INT16 Amount) const;

private:
	POSITION FindFirstNonPylonPosition(void);
	bool mChecks[CHECK_COUNT];
	CMenu mMenu;
};