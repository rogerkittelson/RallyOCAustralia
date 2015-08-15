// DogRunDoc.h : interface of the CDogRunDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOGRUNDOC_H__5CB3DD24_49E1_415F_AE13_7BA4257ABA0E__INCLUDED_)
#define AFX_DOGRUNDOC_H__5CB3DD24_49E1_415F_AE13_7BA4257ABA0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CourseInfo.h"
#include "StationList.h"
#include "RallyObjList.h"
#include "ArrowObjList.h"
#include "PylonObj.h"
#include "SpecialObj.h"
#include "TextObj.h"
#include "Scribble.h"

class CDogRunDoc : public CDocument
{
protected: // create from serialization only
	CDogRunDoc();
	DECLARE_DYNCREATE(CDogRunDoc)
//	DECLARE_SERIAL(CDogRunDoc)
// Attributes
public:
	int GetNumberStations(void);
	void RemoveStationFromList(CRallyObject *p_rally_station_remove, POSITION remove_pos);
	void SetNumberStations(int num_stations);
	void StationListFixerUpper(void);
	BOOL StartStationInList(void);
	BOOL FinishStationInList(void);
	BOOL HonorStationInList(int type_of_course);
// document information
	CString m_doc_author;
	CString m_doc_notes;
	COleDateTime m_doc_created;
	COleDateTime m_doc_modified;
	COleDateTime m_doc_printed;
	CObList  m_undo_list;
	CObList m_redo_list;
	RallyObjList m_rallyList;
	CObList m_pylonList;
	ArrowObjList m_arrowList;
	CObList m_text_list;
	CObList m_special_list;
	CObList m_scribbleList;
	double m_version_number;
	double m_pixels_per_foot_wd;
	double m_pixels_per_foot_ht;
// default fonts
	MyFont *m_text_font;
	MyFont *m_stat_font;
	MyFont *m_print_font;
	BOOL m_default_outline_text_rect;
	COLORREF m_default_text_rect_color;
// preferences for course map text

// station list	course map
	BOOL	m_cmt_akc_number;
	BOOL	m_cmt_station_name;
	BOOL	m_cmt_station_number;
	BOOL	m_cmt_xy_location;
// station list print-out
	BOOL	m_slpo_akc_number;
	BOOL	m_slpo_station_name;
	BOOL	m_slpo_station_number;
	BOOL	m_slpo_xy_location;
// station list print-out course informatin
	BOOL	m_slpo_show_course_info;
	BOOL	m_slpo_class;
	BOOL	m_slpo_comp_name;
	BOOL	m_slpo_date;
	BOOL	m_slpo_judge_name;
	BOOL	m_slpo_location;
	BOOL	m_slpo_organization;
	BOOL	m_slpo_subclass;

	BOOL	m_slpo_show_stats;
// station description preferences
	BOOL	m_sdpo_show_course_info;
	BOOL	m_sdpo_class;
	BOOL	m_sdpo_comp_name;
	BOOL	m_sdpo_date;
	BOOL	m_sdpo_judge_name;
	BOOL	m_sdpo_location;
	BOOL	m_sdpo_organization;
	BOOL	m_sdpo_subclass;
	int		m_station_size;

	BOOL	m_sdpo_akc_number;
	BOOL	m_sdpo_station_name;
	BOOL	m_sdpo_station_number;
	BOOL	m_sdpo_xy_location;
// score sheet preferences
	BOOL	m_sspo_show_course_info;
	BOOL	m_sspo_class;
	BOOL	m_sspo_comp_name;
	BOOL	m_sspo_date;
	BOOL	m_sspo_judge_name;
	BOOL	m_sspo_location;
	BOOL	m_sspo_organization;
	BOOL	m_sspo_subclass;

	BOOL	m_sspo_arm_band;
	BOOL	m_sspo_jump_ht;
	BOOL	m_sspo_breed;
	BOOL	m_sspo_final_score;
	BOOL	m_sspo_time;
	BOOL	m_sspo_judge_sign;

	BOOL	m_sspo_akc_number;
	BOOL	m_sspo_station_name;
	BOOL	m_sspo_station_number;
	BOOL	m_sspo_xy_location;
// print one inch left margin
	BOOL	m_left_margin;

//
// course information
	CCourseInfo *m_course_info;
	StationList *m_station_list;
	void RenumberStations(int station_number, int action, CRallyObject *selected_station, bool from_undo_delete);
	void SetUpInsertPopupMenu(void);
	void SetUpChangeToPopupMenu(void);
	void InsertStationIntoPopupMenu(CRallyObject *station_to_insert);
	void ModifyPopupMenu(void);
	BOOL GetApplicationDefaults(void);
	BOOL SetApplicationDefaults(CourseInfo *course_info);
	POSITION InsertStationIntoList(CRallyObject *p_rally_station_add, int stat_desc, bool from_undo_delete);
	POSITION PasteStationIntoList(CRallyObject *p_rally_station_add, int where_in_list);
	void UpdateRallyList(int index, int akc_number,POSITION pos_to_change);
// undo redo
	int GetUndoListCount(void);
	int GetRedoListCount(void);
	void ClearRedoList(void);
	void ClearUndoList(void);
	void AddUndoStation(CObject *object_to_add, POSITION pos_in_rally_list, int undo_action);
	void AddRedoStation(CObject *object_to_add);
	void UpdatePositionsInRedoList(POSITION old_pos, POSITION new_pos, int type_of_object);
	void UpdatePositionsInUndoList(POSITION old_pos, POSITION new_pos, int type_of_object);
	void CopyRallyObjectData(CRallyObject *dest, CRallyObject *src);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogRunDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString CreateStationDescription(CString station_desc, int row_number);
	void SetLeftOneInchMargin(BOOL left_margin_one_inch);
	BOOL GetPrintLeftOneInchMargin(void);
	void SetDocumentMoveArrowsWithStation(BOOL move_arrows_with_station);
	BOOL GetDocumentMoveArrowsWithStation(void);
	void TrackNumberOfUndoActions(int undo_action);
	int UndoActionofObject(CObject *p_undo_object);
	void RemoveActionFromUndoList(void);
	void SetStationType(int type_of_course);
	void SetNewStationVariables(void);
	void CopyScribbleObjectData(Scribble *dest, Scribble *src);
	void ClearDeletedArrowFromUndoRedoList(POSITION pos_to_delete);
	int GetRallyStationSize(void);
	void SetDefaultRallyStationSize(int rally_station_size);
	void SetApplicationDefaultScoreSheetPreferences(void);
	void SetApplicationDefaultStationDescriptionPreferences(void);
	void SetApplicationStationListPreferences(void);
	BOOL SetApplicationDefaultsCourseText(void);
	void SetDefaultTextFont(LOGFONT *p_log_font, int color_ref);
	int GetDefaultTextFont(LOGFONT *p_log_font);
	void SetDefaultStationFont(LOGFONT *p_log_font, int color_ref);
	int GetDefaultStationLogFont(LOGFONT *p_log_font);
	void SetApplicationDefaultFonts(void);
	void GetApplicationDefaultFonts(void);
	void SetDefaultCourseFont(LOGFONT *p_logfont, int color_ref);
	int GetDefaultCourseLogFont(LOGFONT *p_log_font);
	void SetDefaultPen(LOGPEN *default_pen);
	void SetDefaultArrowType(int default_arrow);
	int GetDefaultArrowType(void);
	void CopyArrowObjectData(ArrowObj *dest, ArrowObj *src);
	void CopyTextObjectData(TextObj *dest, TextObj *src);
	void CopySpecialObjectData(SpecialObj *dest, SpecialObj *src);
	LOGPEN * GetDefaultPen(void);
	void SetUpAddMenu(void);
	void SetStationNumberForHonor(BOOL number_station);
	void SetNewHonorStationNumber(int new_number,int type_of_course);
	POSITION FindFirstNonPylonPosition(void);
	virtual ~CDogRunDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool old_version_close;
	int m_num_stations;
	int m_num_undo_actions;
	BOOL m_move_arrows_with_station;
	CMenu m_insert_menu;
	LOGPEN m_default_pen;
	int	   m_default_arrow_type;
	// only set the stations by inserting or removing station within the document
	void EzCreateFont (CDC *hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes, CFont *hFont);
	MyFont *m_course_font;
	void OnCopyHtml(void);
	void CopyHTML(CString html);
// Generated message map functions
protected:
	void CreateArrowsOnFileConvert(void);
	void PutListTogether(void);
	void PullListApart(void);
	void SetNewSitStayNumber(int new_number);
	void AddArrow(CRallyObject* pRallyItemAdded, bool from_undo_delete);
	//{{AFX_MSG(CDogRunDoc)
	afx_msg void OnPrintScoreSheet();
	afx_msg void OnPrintStationList();
	afx_msg void OnCopyList();
	afx_msg void OnCopyStats();
	afx_msg void OnPrintListDesc();
	afx_msg void OnCopyDesc();
	afx_msg void OnCopyScoreSheet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CopyPylonObjectData(PylonObj *dest, PylonObj *src);
	void CalculateExitEntryPoints(CRallyObject *first_station, CRallyObject *second_station, POINT *entry, POINT *exit);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOGRUNDOC_H__5CB3DD24_49E1_415F_AE13_7BA4257ABA0E__INCLUDED_)
