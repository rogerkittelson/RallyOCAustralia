// CRallyObject.h : interface of the CRallyObject class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
/////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Forward declaration of data structure class
//class CRallyObject;

/////////////////////////////////////////////////////////////////////////////
// class CRallyObject
//
// A CRallyObject is the contains all of the information needed for
// a stations

class CRallyObject : public CObject
{
public:
	virtual void Serialize(CArchive &ar);
	CRallyObject(int objectID, int stringID, int type_station, int akc_num, int xPos, int yPos);
	int HitPointInStationRect(POINT *loc, UINT nFlags);
	int HitPointInStationRect(POINT *loc);
	int MousePointInStationRect(POINT *loc);
	int DrawSelectedStation(CDC* pDC, int stat_num_loc, BOOL advanced_mode, int where_cones, BOOL rotating, BOOL printing);
	void GetHandleRect(int which_handle, RECT* handle_rect);
	int PointInHandleRect(POINT *loc);
	BOOL RallyRectInRegion(CRgn *select_rgn);
	void RotateStation(CPoint *point);
	void SetStationMidPoint(POINT *mid_point);
	POINT GetStationMidPoint(void);
	void SetStationNumber(int station_number);
	int GetStationNumber(void);	
	void SetAKCNumber(int akc_number);
	int GetAKCNumber(void);	
	void SetStringNumber(int string_number);
	int GetStringNumber(void);	
	void SetStationRect(RECT *station_rect); // used for cutting and pasting, and sizing to screen!
	void OffSetStationRect(CPoint *point);
	RECT GetStationRect(void);
	void SetStationID(int station_ID);
	int GetStationID(void);
	void SetStationWidthHeight(int wd, int ht);
	void GetStationWidthHeight(int *wd, int *ht);
	void SetStationRotateMeasurements(float M11, float M12, float M21, float M22);
	void GetStationRotateMeasurements(float *M11, float *M12, float *M21, float *M22);
	POSITION GetUndoRedoPostion(void);
	void SetUndoRedoPosition(POSITION pos_in_rally_list);
	int GetUndoRedoAction(void);
	void SetUndoRedoAction(int undo_action);
	void SetSelectedFlag(BOOL selected);
	BOOL GetSelectedFlag(void);
	void SetCustomEntrancePoint(CPoint *entrance);
	void GetCustomEntrancePoint(CPoint *entrance);
	void SetCustomExitPoint(CPoint *exit);
	void GetCustomExitPoint(CPoint *exit);
	void CalculateEntryAndExitPoints(void);
	void OffSetMidPoint(CPoint *point);
	void GetRectEntryExits(POINT *top, POINT *left, POINT *right, POINT *bottom, BOOL entry);
	void DrawStationForScoreSheet(CDC* pDC, CPoint top_left);
	void DrawStringForStationScoreSheet(CDC* pDC, CPoint top_left);
	CString error_string; 
	BOOL m_has_pylons;
protected:
	CRallyObject();
	DECLARE_SERIAL(CRallyObject)
	void DrawStringForStation(CDC* pDC);
	void DrawStationNumber(CDC *pDC,int stat_num_loc);
	void DrawDegreeSymbol(CDC *pDC, int left_of_string, int top_of_string, int len_of_string, int len_of_char);
	void DrawStationStats(CDC *pDC);
	void SetStationMidPointFromRect(void);
	void DrawStationPylons(CDC* pDC,BOOL with_transform, int where_cones);
	HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal);
	void CalculatePylonEntryAndExitPoints(CRect *pylon_rect, int where_cones);
	void SetStationRect(void);

// Attributes
protected:
	int m_rally_station_ID;
	int m_rally_string_ID;
	int m_akc_number;
	int m_type_station;
	int m_station_num;
	int m_stat_desc;
	BOOL m_do_rotate_text;
	POINT m_midPoint;
	POINT m_pylon_entrance;
	POINT m_pylon_exit;
	int m_where_cones;
	int m_width;
	int m_height;
	float m_M11, m_M12, m_M21, m_M22;
	int m_rotate_text;
	CRect m_station_rect;
// for undo/redo list
	POSITION m_pos_in_rally_list;
	int m_undo_action;
	BOOL m_selected;
	POINT m_entrance;
	POINT m_exit;
	POINT m_cus_entrance;
	POINT m_cus_exit;
public:
	int m_handle_selected;
	CRect m_pylon_rect;
	double m_rotate_degrees;
;
public:

// Operations
public:

public:
	void SetStationDegreeRotation(void);
	void CalculateRotateMeasurements(double degree_rotation);
	int GetRallyStationSizeInFeet(double pixels_per_wd);
	void SetStationRect(int feet, double pixels_per_ht, double pixels_per_wd);
	int GetStationDescription(void);
	BOOL GetRotateText(void);
	void SetRotateText(BOOL do_rotate_text);
	void SetStationDescription(int stat_desc);
	void ResizeStation(POINT *p_loc);
	int GetStationType(void);
	void SetStationType(int type_station);
//	virtual void Serialize(CArchive& ar);
};