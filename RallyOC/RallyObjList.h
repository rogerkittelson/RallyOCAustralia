// RallyObjList.h: interface for the RallyObjList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RALLYOBJLIST_H__A3A94DC8_8C6C_42E4_99A9_A8A4BFCF98C2__INCLUDED_)
#define AFX_RALLYOBJLIST_H__A3A94DC8_8C6C_42E4_99A9_A8A4BFCF98C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RallyObject.h"
#include "MyFont.h"
#include <map>

class RallyObjList : public CObList  
{
public:
	void ResetStationFont(MyFont *p_station_font, CDC *pDC);
	void CreateStationFont(MyFont *p_station_font, CDC *pDC);
	void ResetDCFonts(CDC *pDC);
	void SetDCtoRallyStationFont(CDC* pDC);
	int GetLastNumber(void);
	void SetLastNumber(int last_number);
	int GetTypeOfCourse(void);
	void SetTypeOfCourse(int type_of_course);
	int CalculateLastNumberedStation(void);
	void SetUpAPDTStringMapper(void);
	void ChangeStationType(CRallyObject* pStation_to_change, int new_station_number, int type_of_course);
	bool HaveSitStayStation(void);
	void SetUpAPDTStationNames(void);
	CRallyObject* CreateRallyStation(int menu_choice, int station_type, int x_pos, int y_pos);
	void CalculateEntryExitPoints(CRallyObject *first_station, CRallyObject *second_station, POINT *entry, POINT *exit);
	CRallyObject * FindRallyStationByStationNumber(int station_number);
	void DrawRallyObjects(CDC* pDC, int stat_num_loc, BOOL advanced_mode, int where_cones, BOOL rotating, BOOL printing);
	CString GetAKCDescrption(int objectid);
	CString apdt_station_names[76];
	RallyObjList();
	virtual ~RallyObjList();

private:
	int AKCNumberFromMenuChoice(int menu_choice);
	CString AKCNumberStringFromMenuChoice(int menu_choice);
	int APDTNumberFromMenuChoice(int menu_choice);
//	 std::map <int, CString> akc_CString_map;
// 	 std::map <int, CString> akc_description_map;
 	int BitMapFromMenuChoice(int menu_choice);

	int apdt_bitmap_map[70];
	int apdt_string_map[70];
	int m_number_of_stations;
	int m_type_of_course;
	void SetUpAKCDescrptionMapper(void);
	void SetUpAPDTBitmapMapper(void);
	CFont m_station_font;
	CFont *mp_org_font;
	COLORREF m_station_color;
	COLORREF m_org_color;
};

#endif // !defined(AFX_RALLYOBJLIST_H__A3A94DC8_8C6C_42E4_99A9_A8A4BFCF98C2__INCLUDED_)
