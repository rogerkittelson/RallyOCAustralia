// DogRun.h : main header file for the DOGRUN application
//



#if !defined(AFX_DOGRUN_H__D495712D_5C81_421E_96CB_22A2A4B89FA3__INCLUDED_)
#define AFX_DOGRUN_H__D495712D_5C81_421E_96CB_22A2A4B89FA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include <math.h>
#include "resource.h"       // main symbols
#include "RallyObject.h"
#include "RallyListDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDogRunApp:
// See DogRun.cpp for the implementation of this class
//
#define FILE_CONV_TEST		1		
#define ARROW_ARRAY			1
#define DEMO_TEST			0
#define SHOW_LIST_COUNTS	0
#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8
#define NO_OWNER			-100
#define MAX_NUM_UNDO_ACTIONS    1
extern bool g_convert_course;;
enum course_type {
	AKC_COURSE,
	APDT_COURSE
};
enum station_size {
	TWO_EVEN,
	FIVE_EVEN,
	SEVEN_EVEN,
	CUSTOM_SIZE
};
enum object_type {
	RALLY_OBJECT,
	PYLON_OBJECT,
	SPECIAL_OBJECT,
	TEXT_OBJECT,
	ARROW_OBJECT,
	SCRIBBLE_OBJECT
};
enum arrow_type{
	LINE,
	POLY,
	CURVE
};
enum exit_entrance {
	NONE,
	EXIT,
	ENTRANCE
};
enum feet_meters {
	FEET,
	METERS
};
enum where_honor_list {
	BEFORE_FINISH,
	AFTER_FINISH
};
enum grid_color {
	GRID_BLACK,
	GRID_GREY,
	GRID_NONE
};
enum station_desc {
	BOTH_TEXT_PIC,
	PIC_ONLY,
	TEXT_ONLY
};
enum rally_class {
	NOVICE,
	ADVANCED,
	EXCELLENT,
	TRAINING
};
enum sub_rally_class {
	CLASS_A,
	CLASS_B,
	NO_SUB_CLASS
};
enum rally_shape {
	GRABARROW,
	START,
	FINISH,
	SITHALT
};
enum rect_handle {
	NONE_SELECTED,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};
enum mouse_in_station {
	OUTSIDE = 0,
	IN_RECT,
	IN_HANDLE
};
enum undo_actions {
	ADD_STATION,
	PASTE_STATION,
	MOVE_STATION,
	ROTATE_STATION,
	DELETE_STATION,
	MULMOVE_START,
	MULMOVE,
	MULMOVE_END,
	CUT_ONLY,
	MULCUT_START,
	MULCUT,
	MULCUT_END,
	MULCUTPAS_START,
	MULCUTPAS,
	MULCUTPAS_END,
	MULPASTE_START,
	MULPASTE,
	MULPASTE_END,
	MULDEL_START,
	MULDEL,
	MULDEL_END,
	DELETE_STATION_NUMBER,
	INSERT_AFTER,
	INSERT_BEFORE,
	INSERT_AT,
	UPDATE_LIST,
	MOVE_INFO,
	MOVE_STATION_LIST,
	CHANGE_STATION
};
enum mouse_down_select {
	NOT_SELECTED,
	SELECTED = 50,
	ALL_READY_SELECTED
};
enum program_status {
	REGISTERED,
	PRODID_GEN,
	DEMO_PERIOD,
	TIME_EXPIRED
};
enum spec_stat_numbers {
	START_STATION,
	FINISH_STATION = -1,
	HONOR_STATION = -2,
	PYLONS = -3,
	CALL_TO_HEEL_STATION = -4

};
enum stat_num_location {
	NUM_TOP_LEFT,
	NUM_EXIT,
	NUM_TOP_RIGHT,
	NUM_BOTTOM_LEFT,
	NUM_ENTER,
	NUM_BOTTOM_RIGHT,
	NUM_HIDE
};

enum draw_error_code {
	NO_DRAW_ERROR,
	NO_BITBLT,
	NO_STRECHBLT,
	NO_GRAPHICS_MODE,
	NO_WORLD_TRANS
};
enum where_cone_location {
	CONE_ENTRANCE,
	CONE_EXIT,
	CONE_MIDDLE,
	CONE_HIDE
};
enum where_list_info {
	LIST_BOTTOM,
	LIST_RIGHT,
	LIST_CUSTOM
};
// ARROWSTRUCT
//
// Defines the attributes of an arrow.
typedef struct tARROWSTRUCT {
	int nWidth;		// width (in pixels) of the full base of the arrowhead
	float fTheta;	// angle (in radians) at the arrow tip between the two
					//  sides of the arrowhead
	bool bFill;		// flag indicating whether or not the arrowhead should be
					//  filled
} ARROWSTRUCT;

typedef struct tagVECTOR2D  {
  double     x;
  double     y;
} VECTOR2D, *PVECTOR2D;

typedef struct tagPROJECTION  {
        VECTOR2D   ttProjection;
		VECTOR2D   ttPerpProjection;
        double     LenProjection;
		double     LenPerpProjection;
} PROJECTION, *PPROJECTION, FAR *LPPROJECTION; 

struct CourseInfo {
	CString m_competation;
	int m_type_of_course;
	int m_class;
	int m_sub_class;
	COleDateTime m_date_compete;
	CString m_location;
	CString m_judge;
	CString m_organization;
	int m_ring_width;
	int m_ring_lenght;
	int m_show_path;
	int m_stat_num_loc;
	int m_feet_or_meters;
	int m_grid_spacing;
	BOOL m_size_to_fit;
	BOOL m_add_normal;
	int m_print_grid_lines;
	int m_where_cones;
	int m_where_list;
	BOOL m_number_honor;
	int m_honor_in_list;
	int m_stat_desc;
	BOOL m_do_rotate_text;
	BOOL	m_cmt_class;
	BOOL	m_cmt_comp_name;
	BOOL	m_cmt_date;
	BOOL	m_cmt_judge_name;
	BOOL	m_cmt_organization;
	BOOL	m_cmt_location;
	BOOL	m_cmt_subclass;
};

class CDogRunApp : public CWinApp
{
public:
	CDogRunApp();
	CObList  m_clipBoard;
	void AddObjectToClipboard(CObject* rally_to_clip);
	void RemoveAllObjectsFromClipboard(void);
	int GetCurrentColorMode(void);
	int SetCurrentColorMode(int color_mode);
	int m_dead_flag;
	BOOL m_cutting;
	CView *m_pcutting_view;
	RallyListDlg* m_rally_list_Dialog;
	BOOL m_view_rally_dialog;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDogRunApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDogRunApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewAgilityBar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOGRUN_H__D495712D_5C81_421E_96CB_22A2A4B89FA3__INCLUDED_)
