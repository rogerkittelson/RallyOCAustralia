// DogRunDoc.cpp : implementation of the CDogRunDoc class
//

#include "stdafx.h"
#include "DogRun.h"

#include "DogRunDoc.h"
#include "DogRunView.h"
#include "ChildFrm.h"
#include "Verify.h"
#include "ArrowObj.h"
#include "TextObj.h"
#include "SpecialObj.h"
#include "StationMapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static TCHAR BASED_CODE szSection[] = _T("Settings");
static TCHAR BASED_CODE szDefFonts[] = _T("Fonts");
//static TCHAR BASED_CODE szCourseInfo[] = _T("CourseInfo");
//static TCHAR szFormat[] = _T("%d,%d,%d,%d,%s");

/////////////////////////////////////////////////////////////////////////////
// CDogRunDoc

IMPLEMENT_DYNCREATE(CDogRunDoc, CDocument)
//IMPLEMENT_SERIAL(CDogRunDoc, CDocument, VERSIONABLE_SCHEMA | 2  )
BEGIN_MESSAGE_MAP(CDogRunDoc, CDocument)
	//{{AFX_MSG_MAP(CDogRunDoc)
	ON_COMMAND(ID_PRINT_SCORE_SHEET, OnPrintScoreSheet)
	ON_COMMAND(ID_PRINT_STATION_LIST, OnPrintStationList)
	ON_COMMAND(ID_COPY_LIST, OnCopyList)
	ON_COMMAND(ID_COPY_STATS, OnCopyStats)
	ON_COMMAND(ID_PRINT_LIST_DESC, OnPrintListDesc)
	ON_COMMAND(ID_COPY_DESC, OnCopyDesc)
	ON_COMMAND(ID_COPY_SCORE_SHEET, OnCopyScoreSheet)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDogRunDoc construction/destruction

CDogRunDoc::CDogRunDoc()
{
	// TODO: add one-time construction code here
// document information
	this->m_doc_author = _T("");
	this->m_doc_notes = _T("");
	this->m_doc_created = COleDateTime::GetCurrentTime();
	this->m_doc_modified = COleDateTime::GetCurrentTime();
	this->m_doc_printed.SetStatus(COleDateTime::null);
// course information
	this->m_course_info = new CCourseInfo();
	this->m_station_list = new StationList();
	this->m_num_stations = 0;
// default pen for now is solid black
	m_default_pen.lopnStyle = PS_SOLID;
	m_default_pen.lopnWidth.x = 1;
	m_default_pen.lopnColor = RGB(0, 0, 0);
	this->m_course_font = NULL;
	this->m_stat_font = NULL;
	this->m_text_font = NULL;
	this->m_version_number = 4.000000;	// REMEMBER TO HARD CODE SERILIZE ON SAVING!!!!

	this->m_num_undo_actions = 0;

}

CDogRunDoc::~CDogRunDoc()
{
	CRallyObject* pRallyItemInlist;
	ArrowObj *pArrowItemInlist;
	TextObj *pTextItemInlist;
	SpecialObj *pSpecialItemInlist;
	Scribble *pScribbleItemInlist;
	CObject *objectItemInlist;
	POSITION pos, pos2;

	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		this->m_rallyList.RemoveAt(pos2);
		delete pRallyItemInlist;
	}
// clear redo and undo list
	this->ClearRedoList();

	for( pos = this->m_undo_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		objectItemInlist = this->m_undo_list.GetNext(pos);
		this->m_undo_list.RemoveAt(pos2);
		delete objectItemInlist;
	}

	int count = this->m_pylonList.GetCount();
	for( pos = this->m_pylonList.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pRallyItemInlist = (CRallyObject*)this->m_pylonList.GetNext(pos);
		this->m_pylonList.RemoveAt(pos2);
		delete pRallyItemInlist;
	}

	for( pos = this->m_arrowList.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pArrowItemInlist = (ArrowObj*)this->m_arrowList.GetNext(pos);
		this->m_arrowList.RemoveAt(pos2);
		delete pArrowItemInlist;
	}

	for( pos = this->m_text_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pTextItemInlist = (TextObj*)this->m_text_list.GetNext(pos);
		this->m_text_list.RemoveAt(pos2);
		delete pTextItemInlist;
	}
	for( pos = this->m_special_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pSpecialItemInlist = (SpecialObj*)this->m_special_list.GetNext(pos);
		this->m_special_list.RemoveAt(pos2);
		delete pSpecialItemInlist;
	}
	for( pos = this->m_scribbleList.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pScribbleItemInlist = (Scribble*)this->m_scribbleList.GetNext(pos);
		this->m_scribbleList.RemoveAt(pos2);
		delete pScribbleItemInlist;
	}

	CDogRunApp* dogRunApp;
	dogRunApp = (CDogRunApp*)AfxGetApp( ); 
// then we have items on the clipboard from this view that need to be deleted!
// NOTE:THIS MEANS YOU CANNOT CUT AND PASTE BETWEEN VIEWS IF YOU CLOSE A VIEW MUST USE COPY!!!!
	// OK now I am getting Access violations if you use copy also, why???
	if (dogRunApp->m_cutting) { 
		dogRunApp->RemoveAllObjectsFromClipboard();
	}
	else {
		dogRunApp->m_clipBoard.RemoveAll();
	}
	delete this->m_course_info;
	delete this->m_station_list;

	if (this->m_course_font != NULL) delete this->m_course_font;
	if (this->m_course_font != NULL) delete this->m_stat_font;
	if (this->m_course_font != NULL) delete this->m_text_font;
}

BOOL CDogRunDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	this->GetApplicationDefaults();
	this->GetApplicationDefaultFonts();
	return TRUE;
}
BOOL CDogRunDoc::GetApplicationDefaults(void) {
	CourseInfo course_info;
	CString grid_spacing;
//	CClientDC dc(this);
	course_info.m_class = AfxGetApp()->GetProfileInt(szSection,"Class",0);
	course_info.m_ring_lenght = AfxGetApp()->GetProfileInt(szSection,"RingLen",50);
	course_info.m_ring_width = AfxGetApp()->GetProfileInt(szSection,"RingWidth",50);
	grid_spacing = AfxGetApp()->GetProfileString(szSection, "Gridm","5");
	course_info.m_grid_spacing = atof(grid_spacing);
	course_info.m_judge = AfxGetApp()->GetProfileString(szSection, "Judge");
	course_info.m_organization = AfxGetApp()->GetProfileString(szSection, "Organize");
	course_info.m_show_path = AfxGetApp()->GetProfileInt(szSection,"Path",1);
	course_info.m_stat_num_loc = AfxGetApp()->GetProfileInt(szSection,"NumLoc",0);
	course_info.m_date_compete = COleDateTime::GetCurrentTime();
	course_info.m_size_to_fit = AfxGetApp()->GetProfileInt(szSection,"Size",0);
	course_info.m_add_normal = AfxGetApp()->GetProfileInt(szSection,"AddNorm",1);
	course_info.m_print_grid_lines = AfxGetApp()->GetProfileInt(szSection,"PrintGrid",1);
	course_info.m_where_cones = AfxGetApp()->GetProfileInt(szSection,"Cones",CONE_MIDDLE);
	course_info.m_where_list = AfxGetApp()->GetProfileInt(szSection,"StatList",LIST_CUSTOM);
	course_info.m_number_honor = AfxGetApp()->GetProfileInt(szSection,"NumHonor",1);
	course_info.m_honor_in_list = AfxGetApp()->GetProfileInt(szSection,"HonorList",BEFORE_FINISH);
	course_info.m_type_of_course = AfxGetApp()->GetProfileInt(szSection,"TypeCourse",AKC_COURSE);
	course_info.m_sub_class = AfxGetApp()->GetProfileInt(szSection,"Subclass",CLASS_A);
	course_info.m_stat_desc = AfxGetApp()->GetProfileInt(szSection,"StatDesc",BOTH_TEXT_PIC);
	course_info.m_do_rotate_text = AfxGetApp()->GetProfileInt(szSection,"DoRotate",0);
	this->m_default_pen.lopnStyle = AfxGetApp()->GetProfileInt(szSection,"LineStyle",PS_SOLID);;
	this->m_default_pen.lopnWidth.x = AfxGetApp()->GetProfileInt(szSection,"PenWidth",1);
	this->m_default_pen.lopnWidth.y = 0;
	this->m_default_pen.lopnColor = AfxGetApp()->GetProfileInt(szSection,"PenColor",0);
	this->m_default_arrow_type = AfxGetApp()->GetProfileInt(szSection,"Arrow",LINE);
	this->m_move_arrows_with_station = AfxGetApp()->GetProfileInt(szSection,"MoveArrow",1);
	this->m_default_outline_text_rect = AfxGetApp()->GetProfileInt(szSection,"TextRectOuline",1);
	this->m_default_text_rect_color = AfxGetApp()->GetProfileInt(szSection,"TextRectColor",0);


	//course map text preferences
	// course info course map
	course_info.m_cmt_class = AfxGetApp()->GetProfileInt(szSection,"CMTClass",1);
	course_info.m_cmt_comp_name = AfxGetApp()->GetProfileInt(szSection,"CMTCompName",1);
	course_info.m_cmt_date = AfxGetApp()->GetProfileInt(szSection,"CMTDate",1); 
	course_info.m_cmt_judge_name = AfxGetApp()->GetProfileInt(szSection,"CMTJudgeName",1);
	course_info.m_cmt_organization = AfxGetApp()->GetProfileInt(szSection,"CMTOrganize",1);
	course_info.m_cmt_location = AfxGetApp()->GetProfileInt(szSection,"CMTLocation",1);
	course_info.m_cmt_subclass = AfxGetApp()->GetProfileInt(szSection,"CMTSubclass",1);

	this->m_course_info->SetCourseInfo(&course_info);
	this->m_rallyList.SetTypeOfCourse(course_info.m_type_of_course);

// station list course map
	this->m_cmt_akc_number = AfxGetApp()->GetProfileInt(szSection,"CMTAKCNo",1);
	this->m_cmt_station_name = AfxGetApp()->GetProfileInt(szSection,"CMTStatName",1);
	this->m_cmt_station_number = AfxGetApp()->GetProfileInt(szSection,"CMTStatNo",1);
	this->m_cmt_xy_location = AfxGetApp()->GetProfileInt(szSection,"CMTXYLoc",1);
	this->m_station_list->SetStationListViewParameters(this->m_cmt_akc_number, this->m_cmt_station_name, this->m_cmt_station_number,this->m_cmt_xy_location); 
// station list print-out
	this->m_slpo_akc_number = AfxGetApp()->GetProfileInt(szSection,"SLPOAKCNo",1);
	this->m_slpo_station_name = AfxGetApp()->GetProfileInt(szSection,"SLPOStatName",1);
	this->m_slpo_station_number = AfxGetApp()->GetProfileInt(szSection,"SLPOStatNo",1);
	this->m_slpo_xy_location = AfxGetApp()->GetProfileInt(szSection,"SLPOXYLoc",1);

	this->m_slpo_show_course_info = AfxGetApp()->GetProfileInt(szSection,"SLPOCourseInfo",1);
	this->m_slpo_class = AfxGetApp()->GetProfileInt(szSection,"SLPOClass",1);
	this->m_slpo_comp_name = AfxGetApp()->GetProfileInt(szSection,"SLPOCompName",1);
	this->m_slpo_date = AfxGetApp()->GetProfileInt(szSection,"SLPODate",1);
	this->m_slpo_judge_name = AfxGetApp()->GetProfileInt(szSection,"SLPOJudgeName",1);
	this->m_slpo_location = AfxGetApp()->GetProfileInt(szSection,"SLPOLocation",1);
	this->m_slpo_organization = AfxGetApp()->GetProfileInt(szSection,"SLPOOrganize",1);
	this->m_slpo_subclass = AfxGetApp()->GetProfileInt(szSection,"SLPOSubclass",1);
	this->m_slpo_show_stats = AfxGetApp()->GetProfileInt(szSection,"SLPOStats",1);
// station description print-out
	this->m_sdpo_show_course_info = AfxGetApp()->GetProfileInt(szSection,"SDPOCourseInfo",1);
	this->m_sdpo_class = AfxGetApp()->GetProfileInt(szSection,"SDPOClass",1);
	this->m_sdpo_comp_name = AfxGetApp()->GetProfileInt(szSection,"SDPOCompName",1);
	this->m_sdpo_date = AfxGetApp()->GetProfileInt(szSection,"SDPODate",1);
	this->m_sdpo_judge_name = AfxGetApp()->GetProfileInt(szSection,"SDPOJudgeName",1);
	this->m_sdpo_location = AfxGetApp()->GetProfileInt(szSection,"SDPOLocation",1);
	this->m_sdpo_organization = AfxGetApp()->GetProfileInt(szSection,"SDPOOrganize",1);
	this->m_sdpo_subclass = AfxGetApp()->GetProfileInt(szSection,"SDPOSubclass",1);

	this->m_sdpo_akc_number = AfxGetApp()->GetProfileInt(szSection,"SDPOAKCNo",1);
	this->m_sdpo_station_name = AfxGetApp()->GetProfileInt(szSection,"SDPOStatName",1);
	this->m_sdpo_station_number = AfxGetApp()->GetProfileInt(szSection,"SDPOStatNo",1);
	this->m_sdpo_xy_location = AfxGetApp()->GetProfileInt(szSection,"SDPOXYLoc",1);
// score sheet
	this->m_sspo_show_course_info = AfxGetApp()->GetProfileInt(szSection,"SSPOCourseInfo",1);
	this->m_sspo_class = AfxGetApp()->GetProfileInt(szSection,"SSPOClass",1);
	this->m_sspo_comp_name = AfxGetApp()->GetProfileInt(szSection,"SSPOCompName",1);
	this->m_sspo_date = AfxGetApp()->GetProfileInt(szSection,"SSPODate",1);
	this->m_sspo_judge_name = AfxGetApp()->GetProfileInt(szSection,"SSPOJudgeName",1);
	this->m_sspo_location = AfxGetApp()->GetProfileInt(szSection,"SSPOLocation",1);
	this->m_sspo_organization = AfxGetApp()->GetProfileInt(szSection,"SSPOOrganize",1);
	this->m_sspo_subclass = AfxGetApp()->GetProfileInt(szSection,"SSPOSubclass",1);

	this->m_sspo_arm_band = AfxGetApp()->GetProfileInt(szSection,"SSPOArmBand",1);
	this->m_sspo_jump_ht = AfxGetApp()->GetProfileInt(szSection,"SSPOJumpHt",1);
	this->m_sspo_breed = AfxGetApp()->GetProfileInt(szSection,"SSPOBreed",1);
	this->m_sspo_final_score = AfxGetApp()->GetProfileInt(szSection,"SSPOFinalScore",1);
	this->m_sspo_time = AfxGetApp()->GetProfileInt(szSection,"SSPOTime",1);
	this->m_sspo_judge_sign = AfxGetApp()->GetProfileInt(szSection,"SSPOJudgeSign",1);

	this->m_sspo_akc_number = AfxGetApp()->GetProfileInt(szSection,"SSPOAKCNo",1);
	this->m_sspo_station_name = AfxGetApp()->GetProfileInt(szSection,"SSPOStatName",1);
	this->m_sspo_station_number = AfxGetApp()->GetProfileInt(szSection,"SSPOStatNo",1);
	this->m_sspo_xy_location = AfxGetApp()->GetProfileInt(szSection,"SSPOXYLoc",1);

	this->m_station_size = AfxGetApp()->GetProfileInt(szSection,"StationSize",5);

	this->m_left_margin = AfxGetApp()->GetProfileInt(szSection,"LeftMargin",0);
	return TRUE;
}

BOOL CDogRunDoc::SetApplicationDefaults(CourseInfo *course_info) {
	CString grid_spacing;
	AfxGetApp()->WriteProfileInt(szSection,"Class",course_info->m_class);
	AfxGetApp()->WriteProfileInt(szSection,"RingLen",course_info->m_ring_lenght);
	AfxGetApp()->WriteProfileInt(szSection,"RingWidth",course_info->m_ring_width);
	grid_spacing.Format("%.1f",course_info->m_grid_spacing);
	AfxGetApp()->WriteProfileString(szSection,"Gridm",grid_spacing);
//	AfxGetApp()->WriteProfileInt(szSection,"Grid",course_info->m_grid_spacing);
	AfxGetApp()->WriteProfileString(szSection, "Judge",course_info->m_judge);
	AfxGetApp()->WriteProfileString(szSection, "Organize",course_info->m_organization);
	AfxGetApp()->WriteProfileInt(szSection, "Path",course_info->m_show_path);
	AfxGetApp()->WriteProfileInt(szSection, "NumLoc",course_info->m_stat_num_loc);
	AfxGetApp()->WriteProfileInt(szSection, "Size",course_info->m_size_to_fit);
	AfxGetApp()->WriteProfileInt(szSection, "AddNorm",course_info->m_add_normal);
	AfxGetApp()->WriteProfileInt(szSection, "PrintGrid",course_info->m_print_grid_lines);
	AfxGetApp()->WriteProfileInt(szSection, "Cones",course_info->m_where_cones);
	AfxGetApp()->WriteProfileInt(szSection, "StatList",course_info->m_where_list);
	AfxGetApp()->WriteProfileInt(szSection, "NumHonor",course_info->m_number_honor);
	AfxGetApp()->WriteProfileInt(szSection, "HonorList",course_info->m_honor_in_list);
	AfxGetApp()->WriteProfileInt(szSection, "TypeCourse",course_info->m_type_of_course);
	AfxGetApp()->WriteProfileInt(szSection, "Subclass",course_info->m_sub_class);
	AfxGetApp()->WriteProfileInt(szSection, "StatDesc",course_info->m_stat_desc);
	AfxGetApp()->WriteProfileInt(szSection, "DoRotate",course_info->m_do_rotate_text);
	AfxGetApp()->WriteProfileInt(szSection, "PenWidth",this->m_default_pen.lopnWidth.x);
	AfxGetApp()->WriteProfileInt(szSection, "LineStyle",this->m_default_pen.lopnStyle);
	AfxGetApp()->WriteProfileInt(szSection, "PenColor",this->m_default_pen.lopnColor );
	AfxGetApp()->WriteProfileInt(szSection, "Arrow",this->m_default_arrow_type);		
	AfxGetApp()->WriteProfileInt(szSection, "MoveArrow",this->m_move_arrows_with_station);	
	AfxGetApp()->WriteProfileInt(szSection, "TextRectOuline",this->m_default_outline_text_rect);	
	AfxGetApp()->WriteProfileInt(szSection, "TextRectColor",this->m_default_text_rect_color);
	return false;
}

void CDogRunDoc::GetApplicationDefaultFonts()
{
	int font_height, font_style, font_color;
	LOGFONT lf;
	CString font_name;

	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfEscapement = 0;
	lf.lfWidth = 0;
	lf.lfOrientation = 0;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfPitchAndFamily = 0;
	lf.lfQuality = DEFAULT_QUALITY;//PROOF_QUALITY;	
// start course font
	font_height = AfxGetApp()->GetProfileInt(szDefFonts,"CFHeight",14);
	font_style = AfxGetApp()->GetProfileInt(szDefFonts,"CFStyle",FONT_BOLD);
	font_color = AfxGetApp()->GetProfileInt(szDefFonts,"CFColor",0);
	font_name = AfxGetApp()->GetProfileString(szDefFonts, "CFName");
	if (font_name.IsEmpty()) 
		font_name = "Arial";

	lf.lfHeight = font_height;
	strcpy_s (lf.lfFaceName, TEXT(font_name));
	lf.lfItalic = (font_style & FONT_ITALIC) != 0 ? TRUE : FALSE;
	lf.lfStrikeOut = (font_style & FONT_STRIKEOUT) != 0 ? TRUE : FALSE;
	lf.lfUnderline = (font_style & FONT_UNDERLINE) != 0 ? TRUE : FALSE;
	lf.lfWeight = (font_style & FONT_BOLD) != 0 ? FW_BOLD : FW_NORMAL;
	this->m_course_font = new MyFont(&lf, m_default_pen.lopnColor);
	this->SetDefaultCourseFont(&lf, font_color);
	this->m_station_list->SetStationListFont(this->m_course_font);
	this->m_course_info->SetCourseInfoFont(this->m_course_font);

// end course font
// start station font
	font_height = AfxGetApp()->GetProfileInt(szDefFonts,"SFHeight",14);
	font_style = AfxGetApp()->GetProfileInt(szDefFonts,"SFStyle",FONT_BOLD);
	font_color = AfxGetApp()->GetProfileInt(szDefFonts,"SFColor",0);
	font_name = AfxGetApp()->GetProfileString(szDefFonts, "SFName");
	if (font_name.IsEmpty()) 
		font_name = "Arial";

	lf.lfHeight = font_height;
	strcpy_s(lf.lfFaceName, TEXT(font_name));
	lf.lfItalic = (font_style & FONT_ITALIC) != 0 ? TRUE : FALSE;
	lf.lfStrikeOut = (font_style & FONT_STRIKEOUT) != 0 ? TRUE : FALSE;
	lf.lfUnderline = (font_style & FONT_UNDERLINE) != 0 ? TRUE : FALSE;
	lf.lfWeight = (font_style & FONT_BOLD) != 0 ? FW_BOLD : FW_NORMAL;
	this->m_stat_font = new MyFont(&lf, m_default_pen.lopnColor);
	this->SetDefaultStationFont(&lf, font_color);

// end station font
// start text font
	font_height = AfxGetApp()->GetProfileInt(szDefFonts,"TFHeight",14);
	font_style = AfxGetApp()->GetProfileInt(szDefFonts,"TFStyle",FONT_BOLD);
	font_color = AfxGetApp()->GetProfileInt(szDefFonts,"TFColor",0);
	font_name = AfxGetApp()->GetProfileString(szDefFonts, "TFName");
	if (font_name.IsEmpty()) 
		font_name = "Arial";

	lf.lfHeight = font_height;
	strcpy_s(lf.lfFaceName, TEXT(font_name));
	lf.lfItalic = (font_style & FONT_ITALIC) != 0 ? TRUE : FALSE;
	lf.lfStrikeOut = (font_style & FONT_STRIKEOUT) != 0 ? TRUE : FALSE;
	lf.lfUnderline = (font_style & FONT_UNDERLINE) != 0 ? TRUE : FALSE;
	lf.lfWeight = (font_style & FONT_BOLD) != 0 ? FW_BOLD : FW_NORMAL;
	this->m_text_font = new MyFont(&lf, m_default_pen.lopnColor);	
	this->SetDefaultTextFont(&lf, font_color);

// end text font
}
void CDogRunDoc::SetApplicationDefaultFonts()
{
	LOGFONT lf;
	int font_color;
	int style= FW_NORMAL;
// start course font
	this->m_course_font->GetLogFont(&lf);
	font_color = this->m_course_font->GetColorReference();

	if (lf.lfWeight == FW_BOLD) style = FONT_BOLD;
	if (lf.lfItalic) style = style | FONT_ITALIC;
	if (lf.lfStrikeOut) style = style | FONT_STRIKEOUT;
	if (lf.lfUnderline) style = style | FONT_UNDERLINE;
	AfxGetApp()->WriteProfileInt(szDefFonts, "CFHeight",lf.lfHeight);
	AfxGetApp()->WriteProfileInt(szDefFonts, "CFStyle",style);
	AfxGetApp()->WriteProfileString(szDefFonts, "CFName",lf.lfFaceName);
	AfxGetApp()->WriteProfileInt(szDefFonts, "CFColor",font_color);
// end course font
// start station font
	this->m_stat_font->GetLogFont(&lf);
	font_color = this->m_stat_font->GetColorReference();
	if (lf.lfWeight == FW_BOLD) style = FONT_BOLD;
	if (lf.lfItalic) style = style | FONT_ITALIC;
	if (lf.lfStrikeOut) style = style | FONT_STRIKEOUT;
	if (lf.lfUnderline) style = style | FONT_UNDERLINE;
	AfxGetApp()->WriteProfileInt(szDefFonts, "SFHeight",lf.lfHeight);
	AfxGetApp()->WriteProfileInt(szDefFonts, "SFStyle",style);
	AfxGetApp()->WriteProfileString(szDefFonts, "SFName",lf.lfFaceName);
	AfxGetApp()->WriteProfileInt(szDefFonts, "SFColor",font_color);
// end station font
// start station font
	this->m_text_font->GetLogFont(&lf);
	font_color = this->m_text_font->GetColorReference();
	if (lf.lfWeight == FW_BOLD) style = FONT_BOLD;
	if (lf.lfItalic) style = style | FONT_ITALIC;
	if (lf.lfStrikeOut) style = style | FONT_STRIKEOUT;
	if (lf.lfUnderline) style = style | FONT_UNDERLINE;
	AfxGetApp()->WriteProfileInt(szDefFonts, "TFHeight",lf.lfHeight);
	AfxGetApp()->WriteProfileInt(szDefFonts, "TFStyle",style);
	AfxGetApp()->WriteProfileString(szDefFonts, "TFName",lf.lfFaceName);
	AfxGetApp()->WriteProfileInt(szDefFonts, "TFColor",font_color);
// end station font
}
/////////////////////////////////////////////////////////////////////////////
// CDogRunDoc serialization

void CDogRunDoc::Serialize(CArchive& ar)
{
 	CFile *myFile = ar.GetFile();
	CFileStatus fileStatus;
	BOOL serilize_ar;
	
	myFile->GetStatus(fileStatus);
	int month = fileStatus.m_mtime.GetMonth();
	int year = fileStatus.m_mtime.GetYear();
	int day = fileStatus.m_mtime.GetDay();
	if (year <= 2005 && month <=3 && day < 17) {
		serilize_ar = false;
	}
	else serilize_ar = true;

	if (ar.IsStoring())
	{
		// TODO: add storing code here
// doc info
//		this->PutListTogether();
		ar << 4.000000000000000100; //this->m_version_number THIS NEEDS TO HARD CODED ELSE WILL BE OVERWRITTEN!!!
		ar << this->m_doc_author;
		ar << this->m_doc_notes;
		ar << this->m_doc_created;
		ar << this->m_doc_modified;
		ar << this->m_doc_printed;
		ar << this->m_num_stations;
		// arrow information and line information
		ar << this->m_default_arrow_type;
		ar << m_move_arrows_with_station;
		ar << this->m_default_pen.lopnColor;
		ar << this->m_default_pen.lopnStyle;
		ar << this->m_default_pen.lopnWidth;
		
		this->m_course_info->Serialize(ar,serilize_ar, false);
		this->m_station_list->Serialize(ar,serilize_ar, false);
		this->m_rallyList.Serialize(ar);
		this->m_arrowList.Serialize(ar);
		this->m_pylonList.Serialize(ar);
		this->m_text_list.Serialize(ar);
		this->m_special_list.Serialize(ar);
		this->m_scribbleList.Serialize(ar);
		ar << this->m_course_font;
		ar << this->m_stat_font;
		ar << this->m_text_font;
		ar << this->m_station_size;
// course info course map
// station list	course map
		ar <<	m_cmt_akc_number;
		ar <<	m_cmt_station_name;
		ar <<	m_cmt_station_number;
		ar <<	m_cmt_xy_location;
// station list print-out
		ar <<	m_slpo_akc_number;
		ar <<	m_slpo_station_name;
		ar <<	m_slpo_station_number;
		ar <<	m_slpo_xy_location;
// station list print-out course informatin
		ar <<	m_slpo_show_course_info;
		ar <<	m_slpo_class;
		ar <<	m_slpo_comp_name;
		ar <<	m_slpo_date;
		ar <<	m_slpo_judge_name;
		ar <<	m_slpo_location;
		ar <<	m_slpo_organization;
		ar <<	m_slpo_subclass;
		ar <<	m_slpo_show_stats;
// station description preferences
		ar <<	m_sdpo_show_course_info;
		ar <<	m_sdpo_class;
		ar <<	m_sdpo_comp_name;
		ar <<	m_sdpo_date;
		ar <<	m_sdpo_judge_name;
		ar <<	m_sdpo_location;
		ar <<	m_sdpo_organization;
		ar <<	m_sdpo_subclass;

		ar <<	m_sdpo_akc_number;
		ar <<	m_sdpo_station_name;
		ar <<	m_sdpo_station_number;
		ar <<	m_sdpo_xy_location;
// score sheet preferences
		ar <<	m_sspo_show_course_info;
		ar <<	m_sspo_class;
		ar <<	m_sspo_comp_name;
		ar <<	m_sspo_date;
		ar <<	m_sspo_judge_name;
		ar <<	m_sspo_location;
		ar <<	m_sspo_organization;
		ar <<	m_sspo_subclass;

		ar <<	m_sspo_arm_band;
		ar <<	m_sspo_jump_ht;
		ar <<	m_sspo_breed;
		ar <<	m_sspo_final_score;
		ar <<	m_sspo_time;
		ar <<	m_sspo_judge_sign;

		ar <<	m_sspo_akc_number;
		ar <<	m_sspo_station_name;
		ar <<	m_sspo_station_number;
		ar <<	m_sspo_xy_location;

//		this->PullListApart();// need to this in case we keep working!
	}
	else
	{
		// TODO: add loading code here
// doc info 
		ar >> this->m_version_number;
		old_version_close = false;
		if (this->m_version_number < 4.0) {
			MessageBox(NULL,"This RallyOC course was created with an earlier version of RallyOC!/rStation List Conversion NOT YET IMPLEMENTED!",NULL,MB_OK);
			this->GetApplicationDefaults();
			this->GetApplicationDefaultFonts();
			//			ar.Abort();
//			myFile->Close();
			old_version_close = true;
			return;
		}
		ar >> this->m_doc_author;
		ar >> this->m_doc_notes;
		ar >> this->m_doc_created;
		ar >> this->m_doc_modified;
		ar >> this->m_doc_printed;
		ar >> this->m_num_stations;
		// arrow information
		ar >> this->m_default_arrow_type;
		if (this->m_version_number > 2.2) {
			ar >> this->m_move_arrows_with_station;
			ar >> this->m_default_pen.lopnColor;
			ar >> this->m_default_pen.lopnStyle;
			ar >> this->m_default_pen.lopnWidth;
		}
		this->m_course_info->Serialize(ar,serilize_ar, false);

		this->m_station_list->Serialize(ar, serilize_ar, false);

		this->m_rallyList.Serialize(ar);
		this->m_arrowList.Serialize(ar);
		this->m_pylonList.Serialize(ar);
		this->m_text_list.Serialize(ar);
		this->m_special_list.Serialize(ar);
		if (this->m_version_number >= 2.2) {
			this->m_scribbleList.Serialize(ar);
		}
		ar >> this->m_course_font;
		if (this->m_version_number < 2.2) {
			this->m_station_list->SetStationListFont(this->m_course_font);
			this->m_course_info->SetCourseInfoFont(this->m_course_font);
		}
		ar >> this->m_stat_font;
		ar >> this->m_text_font;
		ar >> this->m_station_size;
	// course info course map

	// station list	course map
		ar >>	m_cmt_akc_number;
		ar >>	m_cmt_station_name;
		ar >>	m_cmt_station_number;
		ar >>	m_cmt_xy_location;
	// station list print-out
		ar >>	m_slpo_akc_number;
		ar >>	m_slpo_station_name;
		ar >>	m_slpo_station_number;
		ar >>	m_slpo_xy_location;
	// station list print-out course informatin
		ar >>	m_slpo_show_course_info;
		ar >>	m_slpo_class;
		ar >>	m_slpo_comp_name;
		ar >>	m_slpo_date;
		ar >>	m_slpo_judge_name;
		ar >>	m_slpo_location;
		ar >>	m_slpo_organization;
		ar >>	m_slpo_subclass;

		ar >>	m_slpo_show_stats;
	// station description preferences
		ar >>	m_sdpo_show_course_info;
		ar >>	m_sdpo_class;
		ar >>	m_sdpo_comp_name;
		ar >>	m_sdpo_date;
		ar >>	m_sdpo_judge_name;
		ar >>	m_sdpo_location;
		ar >>	m_sdpo_organization;
		ar >>	m_sdpo_subclass;

		ar >>	m_sdpo_akc_number;
		ar >>	m_sdpo_station_name;
		ar >>	m_sdpo_station_number;
		ar >>	m_sdpo_xy_location;
	// score sheet preferences
		ar >>	m_sspo_show_course_info;
		ar >>	m_sspo_class;
		ar >>	m_sspo_comp_name;
		ar >>	m_sspo_date;
		ar >>	m_sspo_judge_name;
		ar >>	m_sspo_location;
		ar >>	m_sspo_organization;
		ar >>	m_sspo_subclass;

		ar >>	m_sspo_arm_band;
		ar >>	m_sspo_jump_ht;
		ar >>	m_sspo_breed;
		ar >>	m_sspo_final_score;
		ar >>	m_sspo_time;
		ar >>	m_sspo_judge_sign;

		ar >>	m_sspo_akc_number;
		ar >>	m_sspo_station_name;
		ar >>	m_sspo_station_number;
		ar >>	m_sspo_xy_location;

		this->m_rallyList.SetTypeOfCourse(this->m_course_info->GetTypeOfCourse());
		this->m_rallyList.SetLastNumber(this->m_num_stations);
		this->SetStationType(this->m_course_info->GetTypeOfCourse());
//		this->PullListApart();
	}

}

/////////////////////////////////////////////////////////////////////////////
// CDogRunDoc diagnostics

#ifdef _DEBUG
void CDogRunDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDogRunDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDogRunDoc commands
void CDogRunDoc::RenumberStations(int station_number, int action, CRallyObject *selected_station, bool from_undo_delete) {
	int station_number_list;
	POSITION pos, insert_pos, remove_pos, first_pos;
	CRallyObject* pRallyItemInlist;
	int station_num_changing = selected_station->GetStationNumber();
	switch (action) {
	case DELETE_STATION_NUMBER:
		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			station_number_list = pRallyItemInlist->GetStationNumber();
			if (station_number_list > station_number) {
				station_number_list--;
				pRallyItemInlist->SetStationNumber(station_number_list);
			}
		}				
		break;
	case INSERT_AFTER:
		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			station_number_list = pRallyItemInlist->GetStationNumber();
			if (station_number == station_number_list) {
				insert_pos = pos;
			}
			if (station_num_changing > station_number) { 
				if (station_number_list > station_number && station_number_list < station_num_changing) {
					station_number_list++;
					pRallyItemInlist->SetStationNumber(station_number_list);
				}
			}
			else {
				if (station_number_list > station_num_changing && station_number_list <= station_number) {
					station_number_list--;
					pRallyItemInlist->SetStationNumber(station_number_list);
				}
			}
		}
		if (station_num_changing > station_number) { 
			selected_station->SetStationNumber(++station_number);
		}
		else {
			selected_station->SetStationNumber(station_number);
		}
		remove_pos = this->m_rallyList.Find(selected_station);
		this->m_rallyList.RemoveAt(remove_pos);
		this->m_rallyList.InsertBefore(insert_pos,selected_station);
		this->ModifyPopupMenu();	
		this->m_arrowList.MoveArrowsOnStationMove(&this->m_rallyList, &this->m_rallyList, this->GetNumberStations());
		break;
	case INSERT_BEFORE:
		ASSERT(TRUE);
		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			station_number_list = pRallyItemInlist->GetStationNumber();
			if (station_number_list >= station_number) {
				station_number_list++;
				pRallyItemInlist->SetStationNumber(station_number_list);
			}
		}
		this->m_arrowList.MoveArrowsOnStationMove(&this->m_rallyList, &this->m_rallyList, this->GetNumberStations());
		break;
	case INSERT_AT:
		insert_pos = NULL;
		remove_pos = this->m_rallyList.Find(selected_station);
		if (remove_pos != NULL) 
			this->m_rallyList.RemoveAt(remove_pos);

		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			station_number_list = pRallyItemInlist->GetStationNumber();
			if (station_num_changing > station_number) { 
				if (station_number_list >= station_number && station_number_list < station_num_changing) {
					station_number_list++;
					pRallyItemInlist->SetStationNumber(station_number_list);
				}
			}
			else {
				if (station_number_list > station_num_changing && station_number_list <= station_number) {
					station_number_list--;
					pRallyItemInlist->SetStationNumber(station_number_list);
				}
			}
		}
		if (station_number > START_STATION) {
			for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
				first_pos = pos;
				pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
				station_number_list = pRallyItemInlist->GetStationNumber();
				if (station_num_changing > station_number) { 
					if (station_number == (station_number_list-1)) {
						insert_pos = first_pos;
					}
				}
				else {
					if (station_number == (station_number_list+1)) {
						insert_pos = first_pos;
					}
				}
			}
			
			if (insert_pos != NULL) {
				if (station_num_changing > station_number) { 
					this->m_rallyList.InsertBefore(insert_pos,selected_station);
				}
				else {
					this->m_rallyList.InsertAfter(insert_pos,selected_station);
				}
			}
		}
		else {
			this->InsertStationIntoList(selected_station,station_number, false);
			int i;
			// now need to match postion in list with station number.
			i = START_STATION;
			for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
				first_pos = pos;
				pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
				station_number_list = pRallyItemInlist->GetStationNumber();
				if (station_number_list > START_STATION) {
					i++;
					pRallyItemInlist->SetStationNumber(i);
				}
			}
		}
		selected_station->SetStationNumber(station_number);
		this->ModifyPopupMenu();	
		if (from_undo_delete) {
			this->m_arrowList.UpdateArrowListOnRallyInsert(station_number, this->m_num_stations);			
		}
		else {
			this->m_arrowList.MoveArrowsOnStationMove(&this->m_rallyList, &this->m_rallyList, this->GetNumberStations());
		}
		break;
	default:
		break;
	}
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
	pApp->m_rally_list_Dialog->SetUpRallyList(&this->m_rallyList,this);

	this->SetModifiedFlag();
}
void CDogRunDoc::SetNumberStations(int num_stations) {
	if (num_stations < 0) return;
	this->m_num_stations = num_stations;
	this->m_rallyList.SetLastNumber(this->m_num_stations);

}
int CDogRunDoc::GetNumberStations(void) {
	return this->m_num_stations;
}
void CDogRunDoc::SetUpInsertPopupMenu(void) {
	POSITION pos = GetFirstViewPosition();
	CView* pview = GetNextView(pos);
	ASSERT(pview != NULL);

	CChildFrame* pwnd = (CChildFrame*)pview->GetParentFrame();
	ASSERT_KINDOF(CChildFrame, pwnd);
	pwnd->UpdateInsertAfterMenu();


}
void CDogRunDoc::SetUpChangeToPopupMenu(void) {
	POSITION pos = GetFirstViewPosition();
	CView* pview = GetNextView(pos);
	ASSERT(pview != NULL);

	CChildFrame* pwnd = (CChildFrame*)pview->GetParentFrame();
	ASSERT_KINDOF(CChildFrame, pwnd);
	pwnd->SetUpChangeMenu();

} 
void CDogRunDoc::InsertStationIntoPopupMenu(CRallyObject *station_to_insert) {

	CString station_number, station_desc;
	int find_slash;

	CString add_string;
	int num_of_station;
	int menu_cmd_id;
	num_of_station = station_to_insert->GetStationNumber();
	station_number.Format("%d",num_of_station);
	station_desc.LoadString( station_to_insert->GetStringNumber());
	find_slash = station_desc.Find("\n");
	station_desc = station_desc.Left(find_slash);
	
	add_string = station_number + ": " + station_desc;
	menu_cmd_id = num_of_station + ID_ITEM1;
	POSITION pos = GetFirstViewPosition();
	CView* pview = GetNextView(pos);
	ASSERT(pview != NULL);

	CChildFrame* pwnd = (CChildFrame*)pview->GetParentFrame();
	CMenu *insert_menu = pwnd->GetInsertAfterMenu();
	insert_menu->InsertMenu(num_of_station,MF_STRING,menu_cmd_id, add_string);
}
void CDogRunDoc::ModifyPopupMenu(void) {
	POSITION pos = GetFirstViewPosition();
	CView* pview = GetNextView(pos);
	ASSERT(pview != NULL);

	CChildFrame* pwnd = (CChildFrame*)pview->GetParentFrame();
	ASSERT_KINDOF(CChildFrame, pwnd);
	pwnd->ModifyInsertAfterMenu();

}
void CDogRunDoc::RemoveStationFromList(CRallyObject *p_rally_station_remove, POSITION remove_pos) {
	int which_station = p_rally_station_remove->GetStationID();

	if (which_station == IDB_PYLONS) {	
		if (remove_pos == NULL) {
			remove_pos	= this->m_pylonList.Find(p_rally_station_remove,NULL);
		}
		this->m_pylonList.RemoveAt(remove_pos);

	}
	else {
		if (remove_pos == NULL) {
			remove_pos	= this->m_rallyList.Find(p_rally_station_remove,NULL);
		}


		this->m_rallyList.RemoveAt(remove_pos);
		int station_number = p_rally_station_remove->GetStationNumber();
		int akc_number = p_rally_station_remove->GetAKCNumber();
		if (station_number > 0) {
			this->RenumberStations(station_number,DELETE_STATION_NUMBER, p_rally_station_remove, false);
			this->m_num_stations--;
			this->m_rallyList.SetLastNumber(this->m_num_stations);
		}
		else {
			this->RenumberStations(station_number,UPDATE_LIST, p_rally_station_remove, false);
		}
	}
	this->SetModifiedFlag();
}
BOOL CDogRunDoc::StartStationInList(void) {
	BOOL found = false;
	CRallyObject* pRallyItem;
	POSITION pos, head_pos;
	pos = this->m_rallyList.GetHeadPosition();
	if (pos == NULL) {
		found = false;
	}
	else {
		pRallyItem = (CRallyObject*)this->m_rallyList.GetNext(pos);
		if (pRallyItem->GetStationNumber() == START_STATION) {
			found = true;
		}
	}

	return found;
}
BOOL CDogRunDoc::FinishStationInList(void) {
	BOOL found = false;
	CRallyObject* pRallyItem;
	POSITION pos;
	pos = this->m_rallyList.GetTailPosition();
	if (pos == NULL) {
		found = false;
	}
	else {
		pRallyItem = (CRallyObject*)this->m_rallyList.GetTail();
		if (pRallyItem->GetStationNumber() == FINISH_STATION) {
			found = true;
		}
	}

	return found;
}
BOOL CDogRunDoc::HonorStationInList(int type_of_course) {
	BOOL found = false;
	CRallyObject* pRallyItem;
	POSITION pos;
	pos = this->m_rallyList.GetHeadPosition();
	if (pos == NULL) {
		found = false;
	}
	else {
		pRallyItem = (CRallyObject*)this->m_rallyList.GetHead();
		if (type_of_course == AKC_COURSE) {
			if (pRallyItem->GetAKCNumber() == 50) {
				found = true;
			}
		}
		else {
			if (pRallyItem->GetAKCNumber() == 60) {
				found = true;
			}
		}
	}
	found = false;
	return found;
}

POSITION CDogRunDoc::InsertStationIntoList(CRallyObject *p_rally_station_add, int stat_desc, bool from_undo_delete) {
	CRallyObject* pRallyItem;
	CourseInfo course_info;
	this->m_course_info->GetCourseInfo(&course_info);
	int call_to_station;

	POSITION pos, head_pos, temp_pos;
	if (stat_desc == PYLONS) {
		return NULL;
	}
	bool have_sit_stay = this->m_rallyList.HaveSitStayStation();
	pos = this->m_rallyList.GetHeadPosition();
	// with the change to numbering the HONOR station need to add a check here to make sure that the list doesn't get
	// all screwed up!!!
	if (course_info.m_type_of_course == AKC_COURSE) {
		int akc_number = p_rally_station_add->GetAKCNumber();
	}
	else {
		int akc_number = p_rally_station_add->GetAKCNumber();
		if (akc_number == 60) stat_desc = HONOR_STATION; // APDT BONUS STATION
		call_to_station = 60;
	}
	switch (stat_desc) {
	case START_STATION:
		if (pos == NULL) {
			pos = this->m_rallyList.AddTail(p_rally_station_add);
		}
		else {
			pRallyItem = (CRallyObject*)this->m_rallyList.GetHead();
			if (pRallyItem->GetStationNumber() == START_STATION) {
				pos = NULL;
				AfxMessageBox("You can only have one START station per course.",MB_OK,0);
				return pos;
			}
			else {
				pos = this->m_rallyList.AddHead(p_rally_station_add);
			}
		}
		break;
	case FINISH_STATION:
		if (pos == NULL) {
			pos = this->m_rallyList.AddTail(p_rally_station_add);
		}
		else {
	
			pRallyItem = (CRallyObject*)this->m_rallyList.GetTail();
			pos = this->m_rallyList.GetTailPosition();

			if (pRallyItem->GetStationNumber() == CALL_TO_HEEL_STATION) // means I have find the last heel station
			{
				// need to find last call to heel staion
				pos = this->m_rallyList.GetTailPosition();
				while (pRallyItem->GetStationNumber() == CALL_TO_HEEL_STATION)
				{
					temp_pos = pos;
					pRallyItem = (CRallyObject*)this->m_rallyList.GetPrev(pos);
				}
				pos = temp_pos;
			}

			if (pRallyItem->GetStationNumber() == FINISH_STATION) {
				pos = NULL;
				AfxMessageBox("You can only have one FINISH station per course.",MB_OK,ID_DRAW_FINISH);
				return pos;
			}
			pos = this->m_rallyList.InsertAfter(pos, p_rally_station_add);
		}
		break;

	case CALL_TO_HEEL_STATION:
		if (pos == NULL) {
			pos = this->m_rallyList.AddTail(p_rally_station_add);
		}
		else {
			pRallyItem = (CRallyObject*)this->m_rallyList.GetTail();
			pos = this->m_rallyList.AddTail(p_rally_station_add);
		}
		break;

	default:
		if (pos == NULL) {
			pos = this->m_rallyList.AddTail(p_rally_station_add);
			p_rally_station_add->SetStationNumber(1);
		}
		else {
			pos = this->m_rallyList.GetTailPosition();
			pRallyItem = (CRallyObject*)this->m_rallyList.GetAt(pos);

			if (pRallyItem->GetStationNumber() == CALL_TO_HEEL_STATION)
			{
				while (pRallyItem->GetStationNumber() == CALL_TO_HEEL_STATION)
				{
					temp_pos = pos;
					pRallyItem = (CRallyObject*)this->m_rallyList.GetPrev(pos);
				}
				pos = temp_pos;
			}
			if (pRallyItem->GetStationNumber() == FINISH_STATION) {
				if (have_sit_stay)
				{
					pRallyItem = (CRallyObject*)this->m_rallyList.GetPrev(pos);
				}
				pos = this->m_rallyList.InsertBefore(pos,p_rally_station_add);
			}
			else {
				if (stat_desc > this->m_num_stations + 1) { // have a station number larger than what should be so stick at the tail
					stat_desc = this->m_num_stations + 1;
					p_rally_station_add->SetStationNumber(stat_desc);
				}
				pos = this->m_rallyList.InsertAfter(pos, p_rally_station_add);
			}
			if ((this->m_num_stations + 1) != stat_desc) {
				p_rally_station_add->SetStationNumber(this->m_num_stations + 1); // need to create a different number
				this->RenumberStations(stat_desc,INSERT_AT,p_rally_station_add, from_undo_delete);
			}
			else {
				p_rally_station_add->SetStationNumber(stat_desc);
			}
		}
		this->m_num_stations++;
//		if (have_sit_stay) this->SetNewSitStayNumber(this->m_num_stations + 1);
		this->m_rallyList.SetLastNumber(this->m_num_stations);
		break;
	}

	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
//	int will_need_to_fix_next_line_for_ADPT;
	pApp->m_rally_list_Dialog->SetUpRallyList(&this->m_rallyList,this);
	this->SetModifiedFlag();
	if(course_info.m_show_path) {
		this->AddArrow(p_rally_station_add, from_undo_delete);
	}
	return pos;
}

// undo and redo functions
int CDogRunDoc::GetUndoListCount(void) {
	return this->m_undo_list.GetCount();
}
int CDogRunDoc::GetRedoListCount(void) {
	return this->m_redo_list.GetCount();
}
void CDogRunDoc::ClearRedoList(void) {
	CObject* pRallyItemInlist;
	POSITION pos, pos2;

	for( pos = this->m_redo_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pRallyItemInlist = this->m_redo_list.GetNext(pos);
		this->m_redo_list.RemoveAt(pos2);
		delete pRallyItemInlist;
	}	
}

void CDogRunDoc::ClearUndoList(void) {
	CObject* pRallyItemInlist;
	POSITION pos, pos2;

	for( pos = this->m_undo_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pRallyItemInlist = this->m_undo_list.GetNext(pos);
		this->m_undo_list.RemoveAt(pos2);
		delete pRallyItemInlist;
	}	
}

int CDogRunDoc::UndoActionofObject(CObject *p_undo_object)
{
	int undo_action;
	CRallyObject *pRallyItemInlist;
	PylonObj *pPylonItemInlist;
	SpecialObj *pSpecialItemInlist;
	TextObj *pTextItemInlist;
	ArrowObj *pArrowItemInlist;
	Scribble *pScribbleItemInlist;
	
	if (p_undo_object->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
		pRallyItemInlist = (CRallyObject *)p_undo_object;
		undo_action = pRallyItemInlist->GetUndoRedoAction();
	}
	if (p_undo_object->IsKindOf(RUNTIME_CLASS( PylonObj))) {
		pPylonItemInlist = (PylonObj *)p_undo_object;
		undo_action = pPylonItemInlist->GetUndoRedoAction();
	}
	if (p_undo_object->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
		pSpecialItemInlist = (SpecialObj *)p_undo_object;
		undo_action = pSpecialItemInlist->GetUndoRedoAction();
	}
	if (p_undo_object->IsKindOf(RUNTIME_CLASS( TextObj))) {
		pTextItemInlist = (TextObj *)p_undo_object;
		undo_action = pTextItemInlist->GetUndoRedoAction();
	}
	if (p_undo_object->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
		pArrowItemInlist = (ArrowObj *)p_undo_object;
		undo_action = pArrowItemInlist->GetUndoRedoAction();

	}
	if (p_undo_object->IsKindOf(RUNTIME_CLASS( Scribble))) {
		pScribbleItemInlist = (Scribble *)p_undo_object;
		undo_action = pScribbleItemInlist->GetUndoRedoAction();
	}	
	return undo_action;
}

void CDogRunDoc::RemoveActionFromUndoList()
{

	CObject *pObjectItemInlist;
	int undo_action;
	POSITION pos;
	pos = this->m_undo_list.GetHeadPosition();
	if (pos == NULL) return;
	pObjectItemInlist = this->m_undo_list.RemoveHead();
	undo_action = this->UndoActionofObject(pObjectItemInlist);

	if (undo_action == ADD_STATION) {
		delete pObjectItemInlist;
	}
	if (undo_action == PASTE_STATION) {
		delete pObjectItemInlist;
	}
	if (undo_action == MULPASTE_START) {
			
	}
	
	if(undo_action == DELETE_STATION) {
		delete pObjectItemInlist;
	}
	if (undo_action == MULDEL_START) {
		delete pObjectItemInlist;
		pObjectItemInlist = this->m_undo_list.RemoveHead();
		undo_action = this->UndoActionofObject(pObjectItemInlist);
		while(undo_action == MULDEL || undo_action == MULDEL_END) {
			delete pObjectItemInlist;
			pObjectItemInlist = this->m_undo_list.RemoveHead();
			undo_action = this->UndoActionofObject(pObjectItemInlist);
		}
	}
	if (undo_action == CUT_ONLY) { 
		delete pObjectItemInlist;		
	}
	if (undo_action == MULCUT_START) {

	}
	if (undo_action == MULMOVE_START) {
		// need to undo to MULMOVE_START

	}
	if (undo_action == ROTATE_STATION || undo_action == MOVE_STATION) { // ROTATE_STATION, MOVE_STATION
		delete pObjectItemInlist;
	}
	if (undo_action == INSERT_AT || undo_action == INSERT_BEFORE) {
		delete pObjectItemInlist;
	}
	if (undo_action == MOVE_INFO) {
		delete pObjectItemInlist;
	}
	if (undo_action == MOVE_STATION_LIST) {
		delete pObjectItemInlist;
	}
	if (undo_action == CHANGE_STATION) {
		delete pObjectItemInlist;
	}

}


void CDogRunDoc::TrackNumberOfUndoActions(int undo_action)
{
	if (undo_action == ADD_STATION) {
		this->m_num_undo_actions++;
	}
	if (undo_action == PASTE_STATION) {
		this->m_num_undo_actions++;
	}
	if (undo_action == MULPASTE_START) {
		this->m_num_undo_actions++;
	}
	if(undo_action == DELETE_STATION) {
		this->m_num_undo_actions++;
	}
	if (undo_action == MULDEL_START) {
		this->m_num_undo_actions++;
	}
	if (undo_action == CUT_ONLY) { 
		this->m_num_undo_actions++;
	}
	if (undo_action == MULCUT_START) {
		this->m_num_undo_actions++;
	}
	if (undo_action == MULMOVE_START) {
		this->m_num_undo_actions++;
	}
	if (undo_action == ROTATE_STATION || undo_action == MOVE_STATION) { // ROTATE_STATION, MOVE_STATION
		this->m_num_undo_actions++;
	}
	if (undo_action == INSERT_AT || undo_action == INSERT_BEFORE) {
		this->m_num_undo_actions++;
	}
	if (undo_action == MOVE_INFO) {
		this->m_num_undo_actions++;
	}
	if (undo_action == MOVE_STATION_LIST) {
		this->m_num_undo_actions++;
	}
	if (undo_action == CHANGE_STATION) {
		this->m_num_undo_actions++;
	}
}
void CDogRunDoc::AddUndoStation(CObject *object_to_add, POSITION pos_in_rally_list, int undo_action) {
// undo list a complete list changes made, until you start to undo
// an undo moves the pointer from the undo list to redo list
// the next action will then be added on to the tail, with the redo
// list being removed and stations deleted
	CRallyObject *pRallyItem;
	PylonObj *pPylonObj;
	SpecialObj *pSpecialObj;
	TextObj *pTextObj;
	ArrowObj *pArrowObj;
	Scribble *pScribbleObj;
	this->TrackNumberOfUndoActions(undo_action);
	if(object_to_add->IsKindOf(RUNTIME_CLASS( CRallyObject))) {
		pRallyItem = new CRallyObject(0, 0, 0, 0, 0, 0);		
		this->CopyRallyObjectData(pRallyItem,(CRallyObject *)object_to_add);
		pRallyItem->SetUndoRedoAction(undo_action);
		pRallyItem->SetUndoRedoPosition(pos_in_rally_list);
		this->m_undo_list.AddTail(pRallyItem);
	}
	if(object_to_add->IsKindOf(RUNTIME_CLASS( PylonObj))) {
		pPylonObj = new PylonObj(0, 0);		
		this->CopyPylonObjectData(pPylonObj,(PylonObj *)object_to_add);
		pPylonObj->SetUndoRedoAction(undo_action);
		pPylonObj->SetUndoRedoPosition(pos_in_rally_list);
		this->m_undo_list.AddTail(pPylonObj);
	}
	if(object_to_add->IsKindOf(RUNTIME_CLASS( SpecialObj))) {
		pSpecialObj = new SpecialObj(0,0,-1);		
		this->CopySpecialObjectData(pSpecialObj,(SpecialObj *)object_to_add);
		pSpecialObj->SetUndoRedoAction(undo_action);
		pSpecialObj->SetUndoRedoPosition(pos_in_rally_list);
		this->m_undo_list.AddTail(pSpecialObj);
	}
	if(object_to_add->IsKindOf(RUNTIME_CLASS( TextObj))) {
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
		CRect text_rect;
		text_rect.SetRect(0,0,1,1);
		pTextObj = new TextObj(&text_rect,&lf,RGB(0,0,0));		
		this->CopyTextObjectData(pTextObj,(TextObj *)object_to_add);
		pTextObj->SetUndoRedoAction(undo_action);
		pTextObj->SetUndoRedoPosition(pos_in_rally_list);
		this->m_undo_list.AddTail(pTextObj);
	}
	if(object_to_add->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
		CPoint tempPoint(0,0);
		pArrowObj = new ArrowObj(&tempPoint,&tempPoint,this->GetDefaultPen(),NO_OWNER,NO_OWNER, this->m_default_arrow_type, this->m_move_arrows_with_station, false);		
		this->CopyArrowObjectData(pArrowObj,(ArrowObj *)object_to_add);
		pArrowObj->SetUndoRedoAction(undo_action);
		pArrowObj->SetUndoRedoPosition(pos_in_rally_list);
		this->m_undo_list.AddTail(pArrowObj);
	}
	if(object_to_add->IsKindOf(RUNTIME_CLASS( Scribble))) {
		pScribbleObj = new Scribble(this->GetDefaultPen());		
		this->CopyScribbleObjectData(pScribbleObj,(Scribble *)object_to_add);
		pScribbleObj->SetUndoRedoAction(undo_action);
		pScribbleObj->SetUndoRedoPosition(pos_in_rally_list);
		this->m_undo_list.AddTail(pScribbleObj);
	}
}

void CDogRunDoc::AddRedoStation(CObject *object_to_add) {
	// all we need to do station already created in undo
	this->m_redo_list.AddTail(object_to_add);
}

void CDogRunDoc::ClearDeletedArrowFromUndoRedoList(POSITION pos_to_delete)
{

	CObject* pItemInlist;
	POSITION pos, pos2;
	ArrowObj *pArrowObj;
	for( pos = this->m_undo_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pItemInlist = this->m_redo_list.GetNext(pos);
		if(pItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowObj = (ArrowObj *)pItemInlist;
			if (pArrowObj->GetUndoRedoPosition() == pos_to_delete) {
				this->m_undo_list.RemoveAt(pos2);
				delete pItemInlist;
			}
		}
	}	
	for( pos = this->m_redo_list.GetHeadPosition(); pos != NULL; ) {
		pos2 = pos;
		pItemInlist = this->m_redo_list.GetNext(pos);
		if(pItemInlist->IsKindOf(RUNTIME_CLASS( ArrowObj))) {
			pArrowObj = (ArrowObj *)pItemInlist;
			if (pArrowObj->GetUndoRedoPosition() == pos_to_delete) {
				this->m_redo_list.RemoveAt(pos2);
				delete pItemInlist;
			}
		}
	}	
}

void CDogRunDoc::UpdatePositionsInUndoList(POSITION old_pos, POSITION new_pos, int type_of_object) {
	POSITION posInUndoListOne, posInUndoListTwo;
	CRallyObject *pRallyObjectInUndoList;
	PylonObj *pPylonObjectInUndoList;
	SpecialObj *pSpecialObjectInUndoList;
	TextObj *pTextObjectInUndoList;
	ArrowObj *pArrowObjectInUndoList;
	Scribble *pScribbleObjectInUndoList;

	for(posInUndoListOne = this->m_undo_list.GetHeadPosition(); posInUndoListOne != NULL; ) {
		posInUndoListTwo = posInUndoListOne;
		if (type_of_object == RALLY_OBJECT) {
			pRallyObjectInUndoList = (CRallyObject*)this->m_undo_list.GetNext(posInUndoListTwo);
			if (pRallyObjectInUndoList->IsKindOf(RUNTIME_CLASS( CRallyObject)) ) {
				if (pRallyObjectInUndoList->GetUndoRedoPostion() == old_pos) {
					pRallyObjectInUndoList->SetUndoRedoPosition(new_pos);
				}
			}
		}
		if (type_of_object == PYLON_OBJECT) {
			pPylonObjectInUndoList = (PylonObj*)this->m_undo_list.GetNext(posInUndoListTwo);
			if (pPylonObjectInUndoList->IsKindOf(RUNTIME_CLASS( PylonObj)) ) {
				if (pPylonObjectInUndoList->GetUndoRedoPosition() == old_pos) {
					pPylonObjectInUndoList->SetUndoRedoPosition(new_pos);
				}
			}
		}
		if (type_of_object == SPECIAL_OBJECT) {
			pSpecialObjectInUndoList = (SpecialObj*)this->m_undo_list.GetNext(posInUndoListTwo);
			if (pSpecialObjectInUndoList->IsKindOf(RUNTIME_CLASS( SpecialObj)) ) {
				if (pSpecialObjectInUndoList->GetUndoRedoPosition() == old_pos) {
					pSpecialObjectInUndoList->SetUndoRedoPosition(new_pos);
				}
			}
		}
		if (type_of_object == TEXT_OBJECT) {
			pTextObjectInUndoList = (TextObj*)this->m_undo_list.GetNext(posInUndoListTwo);
			if (pTextObjectInUndoList->IsKindOf(RUNTIME_CLASS( TextObj)) ) {
				if (pTextObjectInUndoList->GetUndoRedoPosition() == old_pos) {
					pTextObjectInUndoList->SetUndoRedoPosition(new_pos);
				}
			}
		}
		if (type_of_object == ARROW_OBJECT) {
			pArrowObjectInUndoList = (ArrowObj*)this->m_undo_list.GetNext(posInUndoListTwo);
			if (pArrowObjectInUndoList->IsKindOf(RUNTIME_CLASS( ArrowObj)) ) {
				if (pArrowObjectInUndoList->GetUndoRedoPosition() == old_pos) {
					pArrowObjectInUndoList->SetUndoRedoPosition(new_pos);
				}
			}
		}
		if (type_of_object == SCRIBBLE_OBJECT) {
			pScribbleObjectInUndoList = (Scribble*)this->m_undo_list.GetNext(posInUndoListTwo);
			if (pScribbleObjectInUndoList->IsKindOf(RUNTIME_CLASS( Scribble)) ) {
				if (pScribbleObjectInUndoList->GetUndoRedoPosition() == old_pos) {
					pScribbleObjectInUndoList->SetUndoRedoPosition(new_pos);
				}
			}
		}
		posInUndoListOne = posInUndoListTwo;
	}
}
void CDogRunDoc::UpdatePositionsInRedoList(POSITION old_pos, POSITION new_pos, int type_of_object) {
	POSITION posInUndoListOne, posInUndoListTwo;
	CRallyObject *pRallyObjectInUndoList;
	PylonObj *pPylonObjectInUndoList;
	SpecialObj *pSpecialObjectInUndoList;
	TextObj *pTextObjectInUndoList;
	ArrowObj *pArrowObjectInUndoList;
	Scribble *pScribbleObjectInUndoList;

	for(posInUndoListOne = this->m_redo_list.GetHeadPosition(); posInUndoListOne != NULL; ) {
		posInUndoListTwo = posInUndoListOne;
		if (type_of_object == RALLY_OBJECT) {
			pRallyObjectInUndoList = (CRallyObject*)this->m_redo_list.GetNext(posInUndoListTwo);
			if (pRallyObjectInUndoList->GetUndoRedoPostion() == old_pos) {
				pRallyObjectInUndoList->SetUndoRedoPosition(new_pos);
			}
		}
		if (type_of_object == PYLON_OBJECT) {
			pPylonObjectInUndoList = (PylonObj*)this->m_redo_list.GetNext(posInUndoListTwo);
			if (pPylonObjectInUndoList->GetUndoRedoPosition() == old_pos) {
				pPylonObjectInUndoList->SetUndoRedoPosition(new_pos);
			}
		}
		if (type_of_object == SPECIAL_OBJECT) {
			pSpecialObjectInUndoList = (SpecialObj*)this->m_redo_list.GetNext(posInUndoListTwo);
			if (pSpecialObjectInUndoList->GetUndoRedoPosition() == old_pos) {
				pSpecialObjectInUndoList->SetUndoRedoPosition(new_pos);
			}
		}
		if (type_of_object == TEXT_OBJECT) {
			pTextObjectInUndoList = (TextObj*)this->m_redo_list.GetNext(posInUndoListTwo);
			if (pTextObjectInUndoList->GetUndoRedoPosition() == old_pos) {
				pTextObjectInUndoList->SetUndoRedoPosition(new_pos);
			}
		}
		if (type_of_object == ARROW_OBJECT) {
			pArrowObjectInUndoList = (ArrowObj*)this->m_redo_list.GetNext(posInUndoListTwo);
			if (pArrowObjectInUndoList->GetUndoRedoPosition() == old_pos) {
				pArrowObjectInUndoList->SetUndoRedoPosition(new_pos);
			}
		}
		if (type_of_object == SCRIBBLE_OBJECT) {
			pScribbleObjectInUndoList = (Scribble*)this->m_redo_list.GetNext(posInUndoListTwo);
			if (pScribbleObjectInUndoList->GetUndoRedoPosition() == old_pos) {
				pScribbleObjectInUndoList->SetUndoRedoPosition(new_pos);
			}
		}
		posInUndoListOne = posInUndoListTwo;
	}
}
void CDogRunDoc::CopyRallyObjectData(CRallyObject *dest, CRallyObject *src) {
	int wd, ht;
	float M11, M12, M21, M22;

	dest->SetStationDescription(src->GetStationDescription());
	dest->SetStationNumber(src->GetStationNumber());
	dest->SetStringNumber(src->GetStringNumber());
	dest->SetAKCNumber(src->GetAKCNumber());
	dest->SetStationMidPoint(&src->GetStationMidPoint());
	dest->SetStationRect(&src->GetStationRect());
	dest->SetStationID(src->GetStationID());
	src->GetStationWidthHeight(&wd,&ht);
	dest->SetStationWidthHeight(wd,ht);
	src->GetStationRotateMeasurements(&M11, &M12, &M21, &M22);
	dest->SetStationRotateMeasurements(M11, M12, M21, M22);
	dest->SetRotateText(src->GetRotateText());
	
}


void CDogRunDoc::UpdateRallyList(int index, int akc_number, POSITION pos_to_change) {
	POSITION pos;
	CRallyObject* pRallyItemInlist;

	int old_akc_number, number_of_stations;
	if (pos_to_change == NULL) {
		pos = this->m_rallyList.FindIndex(index);
	}
	else {
		pos = pos_to_change;
	}
	if (pos == NULL) return;
		// first need to make sure we don't already these stations
	CourseInfo course_info;
	this->m_course_info->GetCourseInfo(&course_info);
	if (course_info.m_type_of_course == APDT_COURSE) {
		switch(akc_number) {
		case 48:
			if (this->StartStationInList()) {
				AfxMessageBox("You can only have one START station per course.",MB_OK,ID_DRAW_START);
				return;
			}

			break;
		case 50:
			if (this->FinishStationInList()) {
				AfxMessageBox("You can only have one FINISH station per course.",MB_OK,ID_DRAW_START);
				return;
			}

			break;
		case 60:
			if (this->HonorStationInList(course_info.m_type_of_course)) {
				AfxMessageBox("You can only have one BONUS station per course.",MB_OK,ID_DRAW_START);
				return;
			}
			break;
		}
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetAt(pos);
		if (index > -2) this->AddUndoStation(pRallyItemInlist, pos,CHANGE_STATION);
		old_akc_number = pRallyItemInlist->GetAKCNumber();
		this->m_rallyList.ChangeStationType(pRallyItemInlist,akc_number,course_info.m_type_of_course);

		number_of_stations = this->GetNumberStations();
		switch (akc_number){
		case 48:
			pRallyItemInlist->SetStationNumber(START_STATION);
			number_of_stations--;
			this->SetNumberStations(number_of_stations);
			if (number_of_stations != 0) this->RenumberStations(START_STATION, INSERT_AT, pRallyItemInlist,false);
			break;
		case 49:
			pRallyItemInlist->SetStationNumber(FINISH_STATION);
			number_of_stations--;
			this->SetNumberStations(number_of_stations);
			if (number_of_stations != 0)this->RenumberStations(FINISH_STATION, INSERT_AT, pRallyItemInlist,false);
			break;
		default:
			if (old_akc_number == 49 ||old_akc_number == 50) { // START, FINISH OR HONOR STATION
				number_of_stations++;
				pRallyItemInlist->SetStationNumber(number_of_stations);
				if (number_of_stations > 1)this->RenumberStations(number_of_stations, INSERT_AT, pRallyItemInlist,false);
				this->SetNumberStations(number_of_stations);
			}
		}
	}
	else {
		switch(akc_number) {
		case 1:
			if (this->StartStationInList()) {
				AfxMessageBox("You can only have one START station per course.",MB_OK,ID_DRAW_START);
				return;
			}

			break;
		case 2:
			if (this->FinishStationInList()) {
				AfxMessageBox("You can only have one FINSIH station per course.",MB_OK,ID_DRAW_START);
				return;
			}

			break;
		case 299:
			AfxMessageBox("Changing to Call to Heel not supported at this time.",MB_OK,ID_DRAW_START);
			return;
		}
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetAt(pos);
		if (index > -2) this->AddUndoStation(pRallyItemInlist, pos,CHANGE_STATION);
		old_akc_number = pRallyItemInlist->GetAKCNumber();
		this->m_rallyList.ChangeStationType(pRallyItemInlist,akc_number,course_info.m_type_of_course);
		number_of_stations = this->GetNumberStations();
		switch (akc_number){
		case 1:
			pRallyItemInlist->SetStationNumber(START_STATION);
			number_of_stations--;
			this->SetNumberStations(number_of_stations);
			if (number_of_stations != 0) this->RenumberStations(START_STATION, INSERT_AT, pRallyItemInlist,false);
			break;
		case 2:
			pRallyItemInlist->SetStationNumber(FINISH_STATION);
			number_of_stations--;
			this->SetNumberStations(number_of_stations);
			if (number_of_stations != 0)this->RenumberStations(FINISH_STATION, INSERT_AT, pRallyItemInlist,false);
			break;
		default:
			if (old_akc_number == 1 ||old_akc_number == 2) { // START, FINISH
				number_of_stations++;
				pRallyItemInlist->SetStationNumber(number_of_stations);
				if (number_of_stations > 1)this->RenumberStations(number_of_stations, INSERT_AT, pRallyItemInlist,false);
				this->SetNumberStations(number_of_stations);
			}
		}
	
	}
//	pRallyItemInlist->SetStationRect();
	
	this->UpdateAllViews(NULL,CHANGE_STATION,NULL);
	this->SetModifiedFlag(TRUE);
	CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
//	int will_need_to_fix_next_line_for_ADPT;
	pApp->m_rally_list_Dialog->SetUpRallyList(&this->m_rallyList,this);

}


void CDogRunDoc::OnPrintScoreSheet() 
{
	// TODO: Add your command handler code here

	CPrintDialog printdlg(FALSE);
	CDC dc;
	DOCINFO di;
	CString judge_name, comp_name, organization;
	CString station_number_text, akc_number_text, station_name, x_y_location;

	TEXTMETRIC tm;
	CPen penBlack;
	CPen* pOldPen;
	CRallyObject* pRallyItemInlist;
	CFont list_font;
	CFont* def_font;
	POSITION pos;
	
	CourseInfo course_info;

	CString out_string, rally_date, rally_class;
	int line_number, line_height, char_width;
	int response = printdlg.DoModal();
	if (response == IDOK) {
		HDC hdc = printdlg.GetPrinterDC();
		ASSERT(hdc);
		penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		int left_margin, top_margin, width, height;
		int text_margin;
		int top_of_text, bottom_of_text;
		width = GetDeviceCaps(hdc,PHYSICALWIDTH);
		height = GetDeviceCaps(hdc,PHYSICALHEIGHT);
		left_margin = GetDeviceCaps(hdc,PHYSICALOFFSETX);		
		top_margin = GetDeviceCaps(hdc,PHYSICALOFFSETY);
		CRect page_rect;
		page_rect.SetRect(left_margin,top_margin,width-(2*left_margin),height-(8*left_margin));
		text_margin = left_margin + 25;

		
		this->m_course_info->GetCourseInfo(&course_info);
		
		dc.Attach (printdlg.GetPrinterDC ());
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		di.lpszDocName = "Printing RallyOC Score Sheet";

		dc.StartDoc (&di);
		dc.StartPage ();
// calculate the edge for drawing lines
		VERIFY(list_font.CreateFont(
		   0,                        // nHeight
		   0,                         // nWidth
		   0,                         // nEscapement
		   0,                         // nOrientation
		   FW_NORMAL,                 // nWeight
		   FALSE,                     // bItalic
		   FALSE,                     // bUnderline
		   0,                         // cStrikeOut
		   ANSI_CHARSET,              // nCharSet
		   OUT_DEFAULT_PRECIS,        // nOutPrecision
		   CLIP_DEFAULT_PRECIS,       // nClipPrecision
		   DEFAULT_QUALITY,           // nQuality
		   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		   "Arial"));                 // lpszFacename

		def_font = dc.SelectObject(&list_font);						  	

		dc.GetTextMetrics(&tm);
		line_height = tm.tmHeight;
		char_width = tm.tmMaxCharWidth;

		
		CString tempString = "Repeat of station, Obstacle knocked over XX";
		int temp_str_len = tempString.GetLength();
		CRect temp_rect;
		temp_rect = page_rect;
		dc.DrawText(tempString, &temp_rect, DT_LEFT | DT_CALCRECT);
		int right_edge = temp_rect.right;

		line_number = top_margin;
		if (this->m_sspo_show_course_info) {
			if (this->m_sspo_date) rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
			if (this->m_sspo_judge_name) judge_name.Format("JUDGE: %s  ",course_info.m_judge);
			if (this->m_sspo_comp_name) comp_name.Format("TRIAL: %s", course_info.m_competation);
			if (this->m_sspo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);

	//		out_string.Format("JUDGE: %s  TRIAL: %s",course_info.m_judge, course_info.m_competation);
			out_string = judge_name + comp_name + organization;
			if (!out_string.IsEmpty()) {
				dc.TextOut(text_margin,line_number,out_string);
				line_number += (int)1.5 * line_height;
			}
			if (this->m_sspo_class) {
				rally_class = "RALLY CLASS: ";
				switch (course_info.m_class) {
				case NOVICE:
					rally_class += "Novice ";
					break;
				case ADVANCED:
					rally_class += "Advanced ";		
					break;
				case EXCELLENT:
					rally_class += "Excellent ";		
					break;
				case MASTER:
					rally_class = "Master";		
					break;
				case TRAINING:
					rally_class += "Training ";
				}
			}
			if (this->m_sspo_subclass) {
				switch (course_info.m_sub_class) {
				case CLASS_A:
					rally_class += " A ";
					break;
				case CLASS_B:
					rally_class += " B ";
					break;
				}
			}
			out_string = rally_class + rally_date;
//			out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);
			if (!out_string.IsEmpty()) {
				dc.TextOut(text_margin,line_number,out_string);
				line_number += (int)1.5 * line_height;
			}
			CString arm_band, breed, jump_ht;
			if (this->m_sspo_arm_band) arm_band = "ARM BAND NO.:_____________  ";
			if (this->m_sspo_breed) breed = "BREED:__________________  ";
			if (this->m_sspo_jump_ht) jump_ht = "JUMP HEIGHT:______________";
			out_string = arm_band + breed + jump_ht;
//			out_string.Format("ARM BAND NO.:_____________  BREED:__________________  JUMP HEIGHT:______________");
			if (!out_string.IsEmpty()) {
				dc.TextOut(text_margin,line_number,out_string);
			}
// end of header
		}
		pOldPen = dc.SelectObject(&penBlack);
// begin first column
		line_number += (int)2 * line_height;
		top_of_text = line_number;
		out_string.Format("DEDUCTIONS | MARKS    | PTS LOST");
		dc.TextOut(text_margin,line_number,out_string);
		dc.MoveTo(left_margin,line_number);
		dc.LineTo(right_edge,line_number);

		line_number += line_height;
		int one_third =temp_rect.Width()/3;
		int two_third = one_third * 2;

		dc.MoveTo(left_margin,line_number);
		dc.LineTo(right_edge,line_number);
		out_string.Format("1-2 POINTS");
		dc.TextOut(text_margin,line_number,out_string);
		dc.MoveTo(left_margin,line_number+line_height+5);
		dc.LineTo(right_edge,line_number+line_height+5);

		dc.MoveTo(left_margin + one_third,line_number);
		dc.LineTo(left_margin + one_third,line_number+line_height+5);
		dc.MoveTo(left_margin + two_third,line_number);
		dc.LineTo(left_margin + two_third,line_number+line_height+5);

		line_number += (int)2 * line_height;
		out_string.Format("Tight leash, Poor sits");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Slow, delay or resistance to respond");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Out of position");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Touches jump, pylon, post or person");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Dog interfeence with handler");
		dc.TextOut(text_margin,line_number,out_string);

		line_number += (int)2 * line_height;

		dc.MoveTo(left_margin,line_number-5);
		dc.LineTo(right_edge,line_number-5);		
		out_string.Format("1-10 POINTS");
		dc.TextOut(text_margin,line_number,out_string);
		dc.MoveTo(left_margin,line_number+line_height+5);
		dc.LineTo(right_edge,line_number+line_height+5);
		dc.MoveTo(left_margin + one_third,line_number);
		dc.LineTo(left_margin + one_third,line_number+line_height+5);
		dc.MoveTo(left_margin + two_third,line_number);
		dc.LineTo(left_margin + two_third,line_number+line_height+5);


		line_number += (int)2 * line_height;
		out_string.Format("Repeat of station (1 re-tries max. 3 pt)");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Pylon or Post knocked over");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Lack of control");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5* line_height;
		out_string.Format("Lack of Teamwork");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Lack of briskness");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Handler error");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Loud or intimdating command or signal");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Excessive barking");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Hitting the jump");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Patting/clapping in Excellent-per occurance");
		dc.TextOut(text_margin,line_number,out_string);
			
		line_number += (int)2 * line_height;				
		dc.MoveTo(left_margin,line_number-5);
		dc.LineTo(right_edge,line_number-5);		
		out_string.Format("6-10 POINTS");
		dc.TextOut(text_margin,line_number,out_string);
		dc.MoveTo(left_margin,line_number+line_height+5);
		dc.LineTo(right_edge,line_number+line_height+5);
		dc.MoveTo(left_margin + one_third,line_number);
		dc.LineTo(left_margin + one_third,line_number+line_height+5);
		dc.MoveTo(left_margin + two_third,line_number);
		dc.LineTo(left_margin + two_third,line_number+line_height+5);
		
		line_number += (int)2 * line_height;
		out_string.Format("Incorrectly performed station");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Failure to complete Sit Stay (0 retries 10 pts)");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Failure of dog to go over jump in proper");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("     direction (0 retries)");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Luring /pleading with the dog");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Lack of natural manner");
		dc.TextOut(text_margin,line_number,out_string);

		line_number += (int)2 * line_height;
			
		dc.MoveTo(left_margin,line_number-5);
		dc.LineTo(right_edge,line_number-5);		
		out_string.Format("NQ");
		dc.TextOut(text_margin,line_number,out_string);
		dc.MoveTo(left_margin,line_number+line_height+5);
		dc.LineTo(right_edge,line_number+line_height+5);
		dc.MoveTo(left_margin + one_third,line_number);
		dc.LineTo(left_margin + one_third,line_number+line_height+5);
		dc.MoveTo(left_margin + two_third,line_number);
		dc.LineTo(left_margin + two_third,line_number+line_height+5);

		line_number += (int)2 * line_height;
		out_string.Format("Minimum requirements not met");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Dog unmanageable or uncontrolled barking");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Station not attempted by handler");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Consistently tight lead");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Handler error");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += (int)1.5 * line_height;
		out_string.Format("Elimination in the ring during judging");
		dc.TextOut(text_margin,line_number,out_string);

		line_number += line_height +5;

		dc.MoveTo(left_margin,line_number-5);
		dc.LineTo(right_edge,line_number-5);		

		bottom_of_text = line_number;
		dc.MoveTo(left_margin,top_of_text);
		dc.LineTo(left_margin,bottom_of_text);
		dc.MoveTo(right_edge,top_of_text);
		dc.LineTo(right_edge,bottom_of_text);

// end first column
int store_right_edge = right_edge;
int store_bottom_of_text = bottom_of_text;
// begin second  column

		
		pos = this->m_rallyList.GetHeadPosition();
		if (pos != NULL) {
			CPoint top_left, bottom_right;
			int mid_text, col_right_edge;
			BOOL have_honor;
			top_left.y = top_of_text;
			top_left.x = right_edge + 50;
			bottom_right.y = top_left.y + line_height +5;
			bottom_right.x = top_left.x + 10;
			CString station_desc, station_list;
			CRect desc_rect;
			int station_number;
			desc_rect.SetRect(top_left,bottom_right);
//			station_desc = StationMapper::GetAKCDescrptionFromAKCNumber(35); //this->m_rallyList.akc_station_names[35];
			station_desc = StationMapper::GetAKCDescrptionFromObjectID(ID_DRAW_1STEP_HEEL_RT); //this->m_rallyList.akc_station_names[35];
			station_desc = station_desc +"             ";
			dc.DrawText(station_desc, &desc_rect, DT_LEFT | DT_CALCRECT);
			desc_rect.right += 5;
			line_number = top_of_text;
			have_honor = false;
			out_string = "STATION";
			dc.TextOut(desc_rect.left,line_number, out_string);
			col_right_edge = desc_rect.right;
			dc.TextOut(desc_rect.right + 5,line_number,"PTS LOST");
			top_left.x = col_right_edge;
			bottom_right.x = top_left.x + 10;
			desc_rect.SetRect(top_left,bottom_right);
			dc.DrawText("PTS LOST",&desc_rect, DT_LEFT | DT_CALCRECT);
			dc.MoveTo(right_edge,line_number);
			dc.LineTo(desc_rect.right,line_number);	

			mid_text = line_number + line_height;
			line_number += (int)2 * line_height;
			dc.MoveTo(right_edge,mid_text);
			dc.LineTo(desc_rect.right,mid_text);		
			for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
				pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
				if (pos != NULL) {
					station_number = pRallyItemInlist->GetStationNumber();
					if (this->m_sspo_station_number)station_number_text.Format("%d. ",station_number);
					int honor_station = pRallyItemInlist->GetAKCNumber();
					if (this->m_sspo_akc_number)akc_number_text.Format(" (%d)", honor_station);

					if (station_number > 0) {
						if (this->m_sspo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()); 
						station_desc = station_number_text + station_name + akc_number_text;
//						station_desc.Format("%d. %s",station_number,this->m_rallyList.akc_station_names[pRallyItemInlist->GetAKCNumber()]);
						dc.TextOut(right_edge + 4,line_number,station_desc);
						mid_text = line_number + line_height;
						line_number += (int)2 * line_height;
						dc.MoveTo(right_edge,mid_text);
						dc.LineTo(desc_rect.right,mid_text);

					}
				}
				else {
					have_honor = false;
					if (have_honor) {
						if (course_info.m_number_honor > 0) {
							if (this->m_sspo_station_number)station_number_text.Format("%d. ",this->m_num_stations + 1);
							if (this->m_sspo_akc_number)akc_number_text.Format(" (%d)", 50);
							if (this->m_sspo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(50); 
							station_desc = station_number_text + station_name + akc_number_text;
//							station_desc.Format("%d. %s",this->m_num_stations + 1, this->m_rallyList.akc_station_names[50]);
						}
						else {
							if (this->m_sspo_station_number)station_number_text.Format("%d. ",this->m_num_stations + 1);
							if (this->m_sspo_akc_number)akc_number_text.Format(" (%d)", 50);
							if (this->m_sspo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(50); ;
							station_desc = "    " + station_name + akc_number_text;
//							station_desc.Format("    %s",this->m_rallyList.akc_station_names[50]);
						}
						dc.TextOut(right_edge + 4,line_number,station_desc);
						mid_text = line_number + line_height;
						line_number += (int)2 * line_height;
						dc.MoveTo(right_edge,mid_text);
						dc.LineTo(desc_rect.right,mid_text);
					}
				}

			}
			dc.MoveTo(col_right_edge,top_of_text);
			dc.LineTo(col_right_edge,mid_text);
			dc.MoveTo(desc_rect.right,top_of_text);
			dc.LineTo(desc_rect.right,mid_text);
			
			dc.MoveTo(store_right_edge,store_bottom_of_text);
			dc.LineTo(store_right_edge,mid_text);
			top_left.x = right_edge;
		
			
			top_left.y = line_number;
			line_number += (int)1.5 * line_height;
			bottom_right.x = top_left.x + 10;
			bottom_right.y = line_number;
			desc_rect.SetRect(top_left,bottom_right);
			
			dc.DrawText(StationMapper::GetAKCDescrptionFromAKCNumber(35) ,&desc_rect, DT_LEFT | DT_CALCRECT);
			dc.DrawText("Total Points Deducted:",&desc_rect,DT_RIGHT);
			dc.TextOut(desc_rect.right,desc_rect.top,"________");

			line_number += (int)1.5 * line_height;
			if (this->m_sspo_final_score) dc.TextOut(desc_rect.left+20,line_number, "FINAL SCORE:_________");
			line_number += (int)1.5 * line_height;
			if (this->m_sspo_time) dc.TextOut(desc_rect.left+20,line_number, "TIME:_________");
			line_number += (int)1.5 * line_height;
			if (this->m_sspo_judge_sign) dc.TextOut(desc_rect.left+20,line_number, "JUDGE'S SIGNATURE:_________________________");			

		}
		pOldPen = dc.SelectObject(pOldPen);
		dc.SelectObject(def_font);
		dc.EndPage();
		dc.EndDoc();
		CDC::FromHandle(hdc)->DeleteDC();
	}
}

void CDogRunDoc::OnCopyScoreSheet() 
{
	// TODO: Add your command handler code here
	if (1) {
		this->OnCopyHtml();
		return;
	}

	CString judge_name, comp_name, organization;
	CString station_number_text, akc_number_text, station_name, x_y_location;


	CRallyObject* pRallyItemInlist;
	POSITION pos;
	CString strResult;	
	
	CourseInfo course_info;

	CString out_string, rally_date, rally_class;
	strResult.Empty();
		
	this->m_course_info->GetCourseInfo(&course_info);
	
	if (this->m_sspo_show_course_info) {
		if (this->m_sspo_date) rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
		if (this->m_sspo_judge_name) judge_name.Format("JUDGE: %s  ",course_info.m_judge);
		if (this->m_sspo_comp_name) comp_name.Format("TRIAL: %s", course_info.m_competation);
		if (this->m_sspo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);

		out_string = judge_name + comp_name + organization + "\r\n";
		strResult += out_string + "\r\n";
		if (this->m_sspo_class) {
			rally_class = "RALLY CLASS: ";
			switch (course_info.m_class) {
			case NOVICE:
				rally_class += "Novice ";
				break;
			case ADVANCED:
				rally_class += "Advanced ";		
				break;
			case EXCELLENT:
				rally_class += "Excellent ";		
				break;
			case MASTER:
				rally_class = "Master";		
				break;
			case TRAINING:
				rally_class += "Training ";
			}
		}
		if (this->m_sspo_subclass) {
			switch (course_info.m_sub_class) {
			case CLASS_A:
				rally_class += " A ";
				break;
			case CLASS_B:
				rally_class += " B ";
				break;
			}
		}
		out_string = rally_class + rally_date;
//			out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);
		strResult += out_string + "\r\n";

		CString arm_band, breed, jump_ht;
		if (this->m_sspo_arm_band) arm_band = "ARM BAND NO.:_____________  ";
		if (this->m_sspo_breed) breed = "BREED:__________________  ";
		if (this->m_sspo_jump_ht) jump_ht = "JUMP HEIGHT:______________";
		out_string = arm_band + breed + jump_ht;
		strResult += out_string + "\r\n";

// end of header
	}

// begin first column

	out_string.Format("DEDUCTIONS | MARKS    | PTS LOST");
	strResult += out_string + "\r\n";


	out_string.Format("1-2 POINTS    |_________ |_________");
	strResult += out_string + "\r\n";
	out_string.Format("Tight leash, Poor sits");
	strResult += out_string + "\r\n";
	out_string.Format("Slow, delay or resistance to respond");
	strResult += out_string + "\r\n";
	out_string.Format("Out of position");
	strResult += out_string + "\r\n";
	out_string.Format("Touches jump, pylon, post or person");
	strResult += out_string + "\r\n";
	out_string.Format("Dog interfering with handler");
	strResult += out_string + "\r\n\r\n";

	out_string.Format("1-10 POINTS    |_________ |_________");
	strResult += out_string + "\r\n";
	out_string.Format("Repeat of station (1 re-tries max.)");
	strResult += out_string + "\r\n";
	out_string.Format("Pylon or Post knocked over");
	strResult += out_string + "\r\n";
	out_string.Format("Lack of control");
	strResult += out_string + "\r\n";
	out_string.Format("Lack of briskness");
	strResult += out_string + "\r\n";
	out_string.Format("Handler Error");
	strResult += out_string + "\r\n";
	out_string.Format("Loud command or intimidating signal");
	strResult += out_string + "\r\n";
	out_string.Format("Excessive barking");
	strResult += out_string + "\r\n\r\n";
	out_string.Format("Hiting the Jump");
	strResult += out_string + "\r\n";
	out_string.Format("Patting/clapping in Excellent");
	strResult += out_string + "\r\n";

	out_string.Format("6-10 POINTS    |_________ |_________");
	strResult += out_string + "\r\n";
	out_string.Format("Incorrectly performed station (10 pts)");
	strResult += out_string + "\r\n";
	out_string.Format("Failure to complete Sit-Stay");
	strResult += out_string + "\r\n";
	out_string.Format("Over Jump in wrong direction");
	strResult += out_string + "\r\n";
	out_string.Format("Luring/pleading with the dog");
	strResult += out_string + "\r\n";
	out_string.Format("Lack of natural manner");
	strResult += out_string + "\r\n";

	out_string.Format("NQ           |_________ |_________");
	strResult += out_string + "\r\n";
	out_string.Format("Minimum requirements not met");
	strResult += out_string + "\r\n";
	out_string.Format("Dog unmanageable or uncontrolled barking");
	strResult += out_string + "\r\n";
	out_string.Format("Station not attempted");
	strResult += out_string + "\r\n";
	out_string.Format("Consistently tight lead");
	strResult += out_string + "\r\n";
	out_string.Format("Elimination in the ring during judging");
	strResult += out_string + "\r\n";
	out_string.Format("Handler error");
	strResult += out_string + "\r\n\r\n";

// end first column

// begin second  column

	
	pos = this->m_rallyList.GetHeadPosition();
	if (pos != NULL) {
		BOOL have_honor;
		CString station_desc, station_list;
		int station_number;
		out_string = "STATION LIST                   PTS LOST";
		strResult += out_string + "\r\n";
	
		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			if (pos != NULL) {
				station_number = pRallyItemInlist->GetStationNumber();
				if (this->m_sspo_station_number)station_number_text.Format("%d. ",station_number);
				int honor_station = pRallyItemInlist->GetAKCNumber();
				if (this->m_sspo_akc_number)akc_number_text.Format(" (%d)", honor_station);
				if (honor_station == 5000) {
					have_honor = true;
				}
				if (station_number > 0) {
					if (this->m_sspo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()); 
					station_desc = station_number_text + station_name + akc_number_text;
					strResult += station_desc + "____________________\r\n";

				}
			}
			else {
				have_honor = false;
				if (have_honor) {
					if (course_info.m_number_honor > 0) {
						if (this->m_sspo_station_number)station_number_text.Format("%d. ",this->m_num_stations + 1);
						if (this->m_sspo_akc_number)akc_number_text.Format(" (%d)", 50);
						if (this->m_sspo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(50); 
						station_desc = station_number_text + station_name + akc_number_text;

					}
					else {
						if (this->m_sspo_station_number)station_number_text.Format("%d. ",this->m_num_stations + 1);
						if (this->m_sspo_akc_number)akc_number_text.Format(" (%d)", 50);
						if (this->m_sspo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(50); 
						station_desc = "    " + station_name + akc_number_text;
					}
					strResult += station_desc + "___________________\r\n";
				}
			}

		}

		strResult += "Total Points Deducted:";
		strResult +="________\r\n";
		if (this->m_sspo_final_score) strResult += "FINAL SCORE:_________\r\n";
		if (this->m_sspo_time) strResult += "TIME:_________";
		if (this->m_sspo_judge_sign) strResult += "JUDGE'S SIGNATURE:_________________________\r\n";			

	}

	
	// copy the string to the clipboard
	pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView( pos );

		
	if (!pFirstView->OpenClipboard())
	{
		AfxMessageBox("Error Opening Clipboard");
		return;
	}


	int nTextLen = (strResult.GetLength()+1)*sizeof(TCHAR);
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nTextLen);
	if (hGlobal != NULL)
	{
		LPVOID lpText = GlobalLock(hGlobal);
		memcpy(lpText, strResult, nTextLen);

		EmptyClipboard();
		GlobalUnlock(hGlobal);
	#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hGlobal);
	#else
		SetClipboardData(CF_TEXT, hGlobal);
	#endif
	}
	CloseClipboard();	
	AfxMessageBox("A copy of the score sheet is available for pasting into another application.",MB_OK);	
}
void CDogRunDoc::EzCreateFont (CDC  *hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes, CFont *hFont)
{
     FLOAT      cxDpi, cyDpi ;
     LOGFONT    lf ;
     POINT      pt ;
     TEXTMETRIC tm ;
     hdc->SaveDC();
  
  
     SetGraphicsMode (hdc->m_hDC, GM_ADVANCED) ;
     ModifyWorldTransform (hdc->m_hDC, NULL, MWT_IDENTITY) ;
     SetViewportOrgEx (hdc->m_hDC, 0, 0, NULL) ;
     SetWindowOrgEx   (hdc->m_hDC, 0, 0, NULL) ;
     
     if (fLogRes)
     {
          cxDpi = (FLOAT) hdc->GetDeviceCaps (LOGPIXELSX) ;
          cyDpi = (FLOAT) hdc->GetDeviceCaps (LOGPIXELSY) ;
     }
     else
     {
          cxDpi = (FLOAT) (25.4 * hdc->GetDeviceCaps (HORZRES) /
                                        hdc->GetDeviceCaps (HORZSIZE)) ;
          
          cyDpi = (FLOAT) (25.4 * hdc->GetDeviceCaps (VERTRES) /
                                        hdc->GetDeviceCaps (VERTSIZE)) ;
     }
     
     pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
     pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
     
     hdc->DPtoLP (&pt, 1) ;

	 double result = pt.y;
     lf.lfHeight         = - (int) (fabs (result) / 10.0 + 0.5) ;
     lf.lfWidth          = 0 ;
     lf.lfEscapement     = 0 ;
     lf.lfOrientation    = 0 ;
     lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 700 : 0 ;
     lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
     lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
     lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
     lf.lfCharSet        = DEFAULT_CHARSET ;
     lf.lfOutPrecision   = 0 ;
     lf.lfClipPrecision  = 0 ;
     lf.lfQuality        = 0 ;
     lf.lfPitchAndFamily = 0 ;
     
     lstrcpy (lf.lfFaceName, szFaceName) ;
     
     hFont->CreateFontIndirect (&lf) ;
     
     if (iDeciPtWidth != 0)
     {
          hdc->SelectObject (hFont) ;
          
          hdc->GetTextMetrics (&tm) ;
          
          DeleteObject (hdc->SelectObject (hFont)) ;
          double result_x = pt.x;
		  double result_y = pt.y;
          lf.lfWidth = (int) (tm.tmAveCharWidth *
                                        fabs (result_x) / fabs (result_y) + 0.5) ;
          
          hFont->CreateFontIndirect (&lf) ;
     }
     
     hdc->RestoreDC (-1) ;
     return;
}


POSITION CDogRunDoc::FindFirstNonPylonPosition()
{

	CRallyObject* pRallyItemInlist;
	POSITION first_non_pylon, pos;
	first_non_pylon = NULL;
	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		first_non_pylon = pos;
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		if (pRallyItemInlist->GetStationNumber() != PYLONS) return first_non_pylon;		
	}
	return first_non_pylon;
}

void CDogRunDoc::SetNewHonorStationNumber(int new_number, int type_of_course)
{

	CRallyObject* pRallyItemInlist;
	POSITION pos;

	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		if (type_of_course == AKC_COURSE) {
			if (pRallyItemInlist->GetStationID() == IDB_HONOR) {
				pRallyItemInlist->SetStationNumber(new_number);
				return;	
			}
		}
		else {
			if (pRallyItemInlist->GetStationID() == IDB_RETRIEVE_FINISH) {
				pRallyItemInlist->SetStationNumber(new_number);
				return;	
			}
		}
	}	
}
void CDogRunDoc::SetNewSitStayNumber(int new_number)
{

	CRallyObject* pRallyItemInlist;
	POSITION pos;
	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		if (pRallyItemInlist->GetStringNumber() == ID__DRAW_SITSTAY) {
			pRallyItemInlist->SetStationNumber(new_number);
			return;	
		}
	}	
}
void CDogRunDoc::PutListTogether()
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	for( pos = this->m_pylonList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_pylonList.GetNext(pos);
		this->m_rallyList.AddTail(pRallyItemInlist);
	}	
}

void CDogRunDoc::PullListApart()
{
	CRallyObject* pRallyItemInlist;
	PylonObj *pPylonObject;	
	POSITION pos;
	int station_id;
	for( pos = this->m_rallyList.GetTailPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetPrev(pos);
		station_id = pRallyItemInlist->GetStationID();
		if (station_id == IDB_PYLONS) {
			pPylonObject = new PylonObj(0, 0);		
			POINT x_y_pos;
			x_y_pos = pRallyItemInlist->GetStationMidPoint();
			pPylonObject->SetXYPosition(&x_y_pos);	
			this->m_pylonList.AddTail(pPylonObject);
		}
	}
	for( pos = this->m_rallyList.GetTailPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetPrev(pos);
		station_id = pRallyItemInlist->GetStationID();
		if (station_id == IDB_PYLONS) {
			this->m_rallyList.RemoveTail();
			delete pRallyItemInlist;
		}

	}
}

void CDogRunDoc::OnPrintStationList() 
{
	// TODO: Add your command handler code here
	CPrintDialog printdlg(FALSE);
	CDC dc;
	DOCINFO di;
	BOOL not_done = true;
	TEXTMETRIC tm;
	CPen penBlack;
	CPen* pOldPen;
	CRallyObject* pRallyItemInlist;
	CFont list_font;
	CFont* def_font;
	POSITION pos;
//	Verify verify_course;
	CPoint station_location;
	CString strResult;	
	CourseInfo course_info;
	CString out_string, rally_date, rally_class, temp_error, organization;
	CString judge_name, comp_name;
	CString station_number_text, akc_number_text, station_name, x_y_location;

	int line_number, line_height, char_width;
	int response = printdlg.DoModal();
	if (response == IDOK) {
		strResult.Empty();
		HDC hdc = printdlg.GetPrinterDC();
		ASSERT(hdc);
		penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		int left_margin, top_margin, width, height;
		int text_margin, find_return;
		int top_of_text;
		width = GetDeviceCaps(hdc,PHYSICALWIDTH);
		height = GetDeviceCaps(hdc,PHYSICALHEIGHT);
		left_margin = GetDeviceCaps(hdc,PHYSICALOFFSETX);		
		top_margin = GetDeviceCaps(hdc,PHYSICALOFFSETY);
		CRect page_rect;
		page_rect.SetRect(left_margin,top_margin,width-(2*left_margin),height-(8*left_margin));
		text_margin = left_margin + 25;
		this->m_course_info->GetCourseInfo(&course_info);
		
		dc.Attach (printdlg.GetPrinterDC ());
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		di.lpszDocName = "Printing RallyOC Station List";

		dc.StartDoc (&di);
		dc.StartPage ();
// calculate the edge for drawing lines
		VERIFY(list_font.CreateFont(
		   0,                        // nHeight
		   0,                         // nWidth
		   0,                         // nEscapement
		   0,                         // nOrientation
		   FW_NORMAL,                 // nWeight
		   FALSE,                     // bItalic
		   FALSE,                     // bUnderline
		   0,                         // cStrikeOut
		   ANSI_CHARSET,              // nCharSet
		   OUT_DEFAULT_PRECIS,        // nOutPrecision
		   CLIP_DEFAULT_PRECIS,       // nClipPrecision
		   DEFAULT_QUALITY,           // nQuality
		   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		   "Arial"));                 // lpszFacename

		def_font = dc.SelectObject(&list_font);						  	
		pOldPen = dc.SelectObject(&penBlack);
		dc.GetTextMetrics(&tm);
		line_height = tm.tmHeight;
		char_width = tm.tmMaxCharWidth;

		line_number = top_margin;
		if (this->m_slpo_show_course_info) {
			if (this->m_slpo_date) {
				rally_date = "DATE: " + course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
			}
			if (this->m_slpo_judge_name) {
				judge_name.Format("JUDGE: %s ",course_info.m_judge);
			}
			if (this->m_slpo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);
			if (this->m_slpo_comp_name) {
				comp_name.Format("TRIAL: %s",course_info.m_competation);
			}
			out_string = judge_name + comp_name + organization;
			if (!out_string.IsEmpty()) {
			//out_string.Format("JUDGE: %s  TRIAL: %s",course_info.m_judge, course_info.m_competation);
				strResult += out_string + "\r\n";
				dc.TextOut(text_margin,line_number,out_string);
				line_number += (int)1.5 * line_height;
			}
			if (this->m_slpo_class) {
				rally_class = "RALLY CLASS: ";
				switch (course_info.m_class) {
				case NOVICE:
					rally_class += "Novice ";
					break;
				case ADVANCED:
					rally_class += "Advanced ";		
					break;
				case EXCELLENT:
					rally_class += "Excellent ";		
					break;
				case MASTER:
					rally_class = "Master";		
					break;
				case TRAINING:
					rally_class += "Training ";
				}
			}
			if (this->m_slpo_subclass) {
				switch (course_info.m_sub_class) {
				case CLASS_A:
					rally_class += " A ";
					break;
				case CLASS_B:
					rally_class += " B ";
					break;
				}
			}
			out_string = rally_class + rally_date;
//			out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);
			if (!out_string.IsEmpty()) {
				dc.TextOut(text_margin,line_number,out_string);
				line_number += (int)2 * line_height;
				strResult += out_string + "\r\n";
			}
		}
		

		out_string.Format("Station List");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += line_height;
		strResult += out_string + "\r\n";
		if (this->m_slpo_station_number) out_string += "No.  ";
		if (this->m_slpo_station_name) out_string += "Station Description ";
		if (this->m_slpo_akc_number) out_string += "(AKC Number)  ";
		if (this->m_slpo_xy_location) out_string += "Grid Location (middle of station)";

//		out_string.Format("No.  Station Description (AKC Number)  X-Y Grid Location (middle of station)");
		if (!out_string.IsEmpty()) {
			dc.TextOut(text_margin,line_number,out_string);
			line_number += (int)1.5 * line_height;
			strResult += out_string + "\r\n";
		}
		top_of_text = line_number;

		
		pos = this->m_rallyList.GetHeadPosition();
		if (pos != NULL) {
			CPoint top_left, bottom_right, honor_location;
			int mid_text;
			BOOL have_honor;
			top_left.y = top_of_text;
			top_left.x = text_margin;
			bottom_right.y = top_left.y + line_height +5;
			bottom_right.x = top_left.x + 10;
			CString station_desc, station_list;
			int station_number;
			line_number = top_of_text;
			have_honor = false;

			for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
				pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
				station_number = pRallyItemInlist->GetStationNumber();
				int akc_station_number = pRallyItemInlist->GetAKCNumber();
				station_location = pRallyItemInlist->GetStationMidPoint();
				station_location.x = (long)(station_location.x/this->m_pixels_per_foot_wd);
				station_location.y = (long)(station_location.y/this->m_pixels_per_foot_ht);

				if (this->m_slpo_station_number) station_number_text.Format("%d. ",station_number);
				if (this->m_slpo_akc_number) akc_number_text.Format("(AKC # %d) ",akc_station_number);
				if (this->m_slpo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber())  + " ";
				if (this->m_slpo_xy_location) x_y_location.Format("%d-%d",station_location.x, station_location.y);

				if (akc_station_number == 5000) {
					have_honor = true;
					honor_location = station_location;

				}
				if (akc_station_number != 5000) {
					if (akc_station_number == 1 || akc_station_number == 2) {
						station_desc = "   " + station_name + akc_number_text + x_y_location;
//						station_desc.Format("   %s (AKC # %d)  %d-%d",this->m_rallyList.akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber(), station_location.x, station_location.y);
					}
					else {
						station_desc = station_number_text + station_name + akc_number_text + x_y_location;
//						station_desc.Format("%d. %s (AKC # %d)  %d-%d",station_number,this->m_rallyList.akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber(), station_location.x, station_location.y);
					}
					dc.TextOut(text_margin + 4,line_number,station_desc);
					mid_text = line_number + line_height;
					line_number += (int)1.5 * line_height;
					strResult += station_desc + "\r\n";
				}
			}
			have_honor = false;
			if (have_honor) {
				if (this->m_slpo_station_number) station_number_text.Format("%d ",this->m_num_stations + 1);
				if (this->m_slpo_akc_number) akc_number_text.Format("(AKC # %d)",50);
				if (this->m_slpo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(50) + " ";
				if (this->m_slpo_xy_location) x_y_location.Format("%d-%d",honor_location.x, honor_location.y);

				if (course_info.m_number_honor > 0) {
					station_desc = station_number_text + station_name + akc_number_text + x_y_location;
//					station_desc.Format("%d. %s (AKC # 50) %d-%d",this->m_num_stations + 1, this->m_rallyList.akc_station_names[50], honor_location.x, honor_location.y);
				}
				else {
					station_desc = "   " + station_name + akc_number_text + x_y_location;
//					station_desc.Format("    %s (AKC # 50) %d-%d", this->m_rallyList.akc_station_names[50], honor_location.x, honor_location.y);
				}
				
				dc.TextOut(text_margin + 4,line_number,station_desc);
				mid_text = line_number + line_height;
				line_number += (int)1.5 * line_height;
				strResult += station_desc + "\r\n";

			}
			if (this->m_slpo_show_stats) {
				top_left.x = text_margin;
				top_left.y = line_number;
				line_number += (int)2 * line_height;
//				verify_course.VerifyCourse(this,false, course_info.m_type_of_course);
//				temp_error = verify_course.GetStationStatistics();
				strResult += temp_error + "\r\n";

				while(not_done) {
					find_return = temp_error.Find("\r\n",0);
					if (find_return == -1) {
						out_string = temp_error;
						not_done = false;
					}
					else {
						out_string = temp_error.Left(find_return);
						temp_error.Delete(0,find_return + 2);
					}
					dc.TextOut(30,line_number,out_string);
					line_number += line_height;
					
				}
			}

		}
		pOldPen = dc.SelectObject(pOldPen);
		dc.SelectObject(def_font);
		dc.EndPage();
		dc.EndDoc();
		CDC::FromHandle(hdc)->DeleteDC();
	}

}

void CDogRunDoc::OnCopyList() 
{
	// TODO: Add your command handler code here
	BOOL not_done = true;
	CRallyObject* pRallyItemInlist;
	POSITION pos;
//	Verify verify_course;
	CPoint station_location, honor_location;
	CString strResult;	
	CourseInfo course_info;
	CString out_string, rally_date, rally_class, temp_error, organization;
	CString judge_name, comp_name;
	CString station_number_text, akc_number_text, station_name, x_y_location;

	strResult.Empty();
	this->m_course_info->GetCourseInfo(&course_info);
	if (this->m_slpo_show_course_info) {
	
		if (this->m_slpo_date) rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
//		out_string.Format("JUDGE: %s  TRIAL: %s",course_info.m_judge, course_info.m_competation);
		if (this->m_slpo_judge_name) {
			judge_name.Format("JUDGE: %s ",course_info.m_judge);
		}
		if (this->m_slpo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);
		if (this->m_slpo_comp_name) {
			comp_name.Format("TRIAL: %s",course_info.m_competation);
		}
		out_string = judge_name + comp_name + organization;
		strResult += out_string + "\r\n";

		if (this->m_slpo_class) {
			rally_class = "RALLY CLASS: ";
			switch (course_info.m_class) {
			case NOVICE:
				rally_class = "Novice";
				break;
			case ADVANCED:
				rally_class = "Advanced";		
				break;
			case EXCELLENT:
				rally_class = "Excellent";		
				break;
			case MASTER:
				rally_class = "Master";		
				break;
				case TRAINING:
				rally_class = "Training";
			}
		}
		if (this->m_slpo_subclass) {
			switch (course_info.m_sub_class) {
			case CLASS_A:
				rally_class += " A ";
				break;
			case CLASS_B:
				rally_class += " B ";
				break;
			}
		}
		out_string = rally_class + rally_date;
//		out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);

		strResult += out_string + "\r\n";
	}

	out_string.Format("Station List");

	strResult += out_string + "\r\n";
	if (this->m_slpo_station_number) out_string += "No.  ";
	if (this->m_slpo_station_name) out_string += "Station Description ";
	if (this->m_slpo_akc_number) out_string += "(AKC Number)  ";
	if (this->m_slpo_xy_location) out_string += "Grid Location (middle of station)";
//	out_string.Format("No.  Station Description (AKC Number)  X-Y Grid Location (middle of station)");

	strResult += out_string + "\r\n";
	
	
	pos = this->m_rallyList.GetHeadPosition();
	if (pos != NULL) {
		BOOL have_honor;
		CString station_desc, station_list;
		int station_number;
		have_honor = false;

		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			station_number = pRallyItemInlist->GetStationNumber();
			int akc_station_number = pRallyItemInlist->GetAKCNumber();
			station_location = pRallyItemInlist->GetStationMidPoint();
			station_location.x = (long)(station_location.x/this->m_pixels_per_foot_wd);
			station_location.y = (long)(station_location.y/this->m_pixels_per_foot_ht);
			if (this->m_slpo_station_number) station_number_text.Format("%d. ",station_number);
			if (this->m_slpo_akc_number) akc_number_text.Format("(AKC # %d) ",akc_station_number);
			if (this->m_slpo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()) + " ";
			if (this->m_slpo_xy_location) x_y_location.Format("%d-%d",station_location.x, station_location.y);

			if (akc_station_number == 5000) {
				have_honor = true;
				honor_location = station_location;

			}
			if (akc_station_number != 5000) {
				if (akc_station_number == 1 || akc_station_number == 2) {
					station_desc = "   " + station_name + akc_number_text + x_y_location;
//					station_desc.Format("   %s (AKC # %d)  %d-%d",this->m_rallyList.akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber(), station_location.x, station_location.y);
				}
				else {
					station_desc = station_number_text + station_name + akc_number_text + x_y_location;
//					station_desc.Format("%d. %s (AKC # %d)  %d-%d",station_number,this->m_rallyList.akc_station_names[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber(), station_location.x, station_location.y);
				}
				strResult += station_desc + "\r\n";
			}
		}
		have_honor = false;
		if (have_honor) {
			if (this->m_slpo_station_number) station_number_text.Format("%d ",this->m_num_stations + 1);
			if (this->m_slpo_akc_number) akc_number_text.Format("(AKC # %d)",50);
			if (this->m_slpo_station_name) station_name = StationMapper::GetAKCDescrptionFromAKCNumber(50) + " ";
			if (this->m_slpo_xy_location) x_y_location.Format("%d-%d",honor_location.x, honor_location.y);
			if (course_info.m_number_honor > 0) {
				station_desc = station_number_text + station_name + akc_number_text + x_y_location;
//				station_desc.Format("%d. %s (AKC # 50) %d-%d",this->m_num_stations + 1, this->m_rallyList.akc_station_names[50], honor_location.x, honor_location.y);
			}
			else {
				station_desc = "   " + station_name + akc_number_text + x_y_location;
//				station_desc.Format("    %s (AKC # 50) %d-%d",this->m_rallyList.akc_station_names[50], honor_location.x, honor_location.y);
			}			
			strResult += station_desc + "\r\n";

		}
		

	}

	
	// copy the string to the clipboard
	pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView( pos );

		
	if (!pFirstView->OpenClipboard())
	{
		AfxMessageBox("Error Opening Clipboard");
		return;
	}


	int nTextLen = (strResult.GetLength()+1)*sizeof(TCHAR);
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nTextLen);
	if (hGlobal != NULL)
	{
		LPVOID lpText = GlobalLock(hGlobal);
		memcpy(lpText, strResult, nTextLen);

		EmptyClipboard();
		GlobalUnlock(hGlobal);
	#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hGlobal);
	#else
		SetClipboardData(CF_TEXT, hGlobal);
	#endif
	}
	CloseClipboard();	
	AfxMessageBox("A copy of the station list is available for pasting into another application.",MB_OK);	
}

void CDogRunDoc::OnCopyStats() 
{
	// TODO: Add your command handler code here
	BOOL not_done = true;

	POSITION pos;
//	Verify verify_course;
	CPoint station_location, honor_location;
	CString strResult;	
	CourseInfo course_info;
	CString out_string, rally_date, rally_class, temp_error;
	int find_return;

	strResult.Empty();


	this->m_course_info->GetCourseInfo(&course_info);
	
	rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
	out_string.Format("JUDGE: %s  TRIAL: %s",course_info.m_judge, course_info.m_competation);
	strResult += out_string + "\r\n";
	switch (course_info.m_class) {
	case NOVICE:
		rally_class = "Novice";
		break;
	case ADVANCED:
		rally_class = "Advanced";		
		break;
	case EXCELLENT:
		rally_class = "Excellent";		
		break;
	case MASTER:
		rally_class = "Master";		
		break;
	case TRAINING:
		rally_class = "Training";
	}	
	out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);

	strResult += out_string + "\r\n";

	
	pos = this->m_rallyList.GetHeadPosition();
	if (pos != NULL) {

//		verify_course.VerifyCourse(this,false, course_info.m_type_of_course);
//		temp_error = verify_course.GetStationStatistics();
		strResult += temp_error + "\r\n";

		while(not_done) {
			find_return = temp_error.Find("\r\n",0);
			if (find_return == -1) {
				out_string = temp_error;
				not_done = false;
			}
			else {
				out_string = temp_error.Left(find_return);
				temp_error.Delete(0,find_return + 2);
			}
		
		}

	}

	
	// copy the string to the clipboard
	pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView( pos );

		
	if (!pFirstView->OpenClipboard())
	{
		AfxMessageBox("Error Opening Clipboard");
		return;
	}


	int nTextLen = (strResult.GetLength()+1)*sizeof(TCHAR);
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nTextLen);
	if (hGlobal != NULL)
	{
		LPVOID lpText = GlobalLock(hGlobal);
		memcpy(lpText, strResult, nTextLen);

		EmptyClipboard();
		GlobalUnlock(hGlobal);
	#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hGlobal);
	#else
		SetClipboardData(CF_TEXT, hGlobal);
	#endif
	}
	CloseClipboard();
	AfxMessageBox("A copy of the course statistics is available for pasting into another application.",MB_OK);	
}

void CDogRunDoc::OnPrintListDesc() 
{
	// TODO: Add your command handler code here
	CPrintDialog printdlg(FALSE);
	CDC dc;
	DOCINFO di;
	BOOL not_done = true;
	TEXTMETRIC tm;
	CPen penBlack;
	CPen* pOldPen;
	CRallyObject* pRallyItemInlist;
	CFont list_font;
	CFont* def_font;
	POSITION pos;
	CString judge_name, comp_name;
	CString station_number_text, akc_number_text, station_name, x_y_location, organization;
	CPoint station_location, honor_location;
	CString strResult;	
	CourseInfo course_info;
	CString out_string, rally_date, rally_class, temp_error;
	int line_number, line_height, char_width, find_return, num_lines, lines_printed;
	int response = printdlg.DoModal();
	if (response == IDOK) {
		strResult.Empty();
		HDC hdc = printdlg.GetPrinterDC();
		ASSERT(hdc);
		penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		int left_margin, top_margin, width, height;
		int text_margin;
		int top_of_text;
		width = GetDeviceCaps(hdc,PHYSICALWIDTH);
		height = GetDeviceCaps(hdc,PHYSICALHEIGHT);
		left_margin = GetDeviceCaps(hdc,PHYSICALOFFSETX);		
		top_margin = GetDeviceCaps(hdc,PHYSICALOFFSETY);
		num_lines = GetDeviceCaps(hdc,VERTRES);
		CRect page_rect, text_rect, temp_rect;
		page_rect.SetRect(left_margin,top_margin,width-(2*left_margin),height-(8*left_margin));
		temp_rect = text_rect = page_rect;
		text_margin = left_margin + 25;
		this->m_course_info->GetCourseInfo(&course_info);
		
		dc.Attach (printdlg.GetPrinterDC ());
		::ZeroMemory (&di, sizeof (DOCINFO));
		di.cbSize = sizeof (DOCINFO);
		di.lpszDocName = "Printing RallyOC Station List";

		dc.StartDoc (&di);
		dc.StartPage ();
// calculate the edge for drawing lines
		VERIFY(list_font.CreateFont(
		   0,                        // nHeight
		   0,                         // nWidth
		   0,                         // nEscapement
		   0,                         // nOrientation
		   FW_NORMAL,                 // nWeight
		   FALSE,                     // bItalic
		   FALSE,                     // bUnderline
		   0,                         // cStrikeOut
		   ANSI_CHARSET,              // nCharSet
		   OUT_DEFAULT_PRECIS,        // nOutPrecision
		   CLIP_DEFAULT_PRECIS,       // nClipPrecision
		   DEFAULT_QUALITY,           // nQuality
		   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		   "Arial"));                 // lpszFacename

		def_font = dc.SelectObject(&list_font);						  	
		pOldPen = dc.SelectObject(&penBlack);
		dc.GetTextMetrics(&tm);
		line_height = tm.tmHeight;
		char_width = tm.tmMaxCharWidth;
		num_lines = num_lines / (tm.tmHeight + tm.tmExternalLeading);
		lines_printed = 0;
		line_number = top_margin;
		if (this->m_sdpo_show_course_info) {
			if (this->m_sdpo_date) rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
			if (this->m_sdpo_judge_name) judge_name.Format("JUDGE: %s  ",course_info.m_judge);
			if (this->m_sdpo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);
			if (this->m_sdpo_comp_name) comp_name.Format("TRIAL: %s",course_info.m_competation);
			out_string = judge_name + comp_name + organization;
			
//			out_string.Format("JUDGE: %s  TRIAL: %s",course_info.m_judge, course_info.m_competation);
			if (!out_string.IsEmpty()) {
				strResult += out_string + "\r\n";
				dc.TextOut(text_margin,line_number,out_string);
				line_number += (int)1.5 * line_height;
				lines_printed = 1;
			}
			if (this->m_sdpo_class) {
				rally_class = "RALLY CLASS: ";
				switch (course_info.m_class) {
				case NOVICE:
					rally_class += "Novice";
					break;
				case ADVANCED:
					rally_class += "Advanced";		
					break;
				case EXCELLENT:
					rally_class += "Excellent";		
					break;
				case MASTER:
					rally_class = "Master";		
					break;
				case TRAINING:
					rally_class += "Training";
				}
			}
			if (this->m_sdpo_subclass) {
				switch (course_info.m_sub_class) {
				case CLASS_A:
					rally_class += " A ";
					break;
				case CLASS_B:
					rally_class += " B ";
					break;
				}
			}
			out_string = rally_class + rally_date;
//			out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);
			if (!out_string.IsEmpty()) {
				dc.TextOut(text_margin,line_number,out_string);
				line_number += (int)2 * line_height;
				strResult += out_string + "\r\n";
				lines_printed  = 2;
			}
		}
		out_string.Format("Station List with description");
		dc.TextOut(text_margin,line_number,out_string);
		line_number += line_height;
		strResult += out_string + "\r\n";
		lines_printed = 3;
		top_of_text = line_number;

		temp_rect.top = text_rect.top = top_of_text;
		pos = this->m_rallyList.GetHeadPosition();
		if (pos != NULL) {
			CPoint top_left, bottom_right;
			int mid_text;
			BOOL have_honor = false;
			top_left.y = top_of_text;
			top_left.x = text_margin;
			bottom_right.y = top_left.y + line_height +5;
			bottom_right.x = top_left.x + 10;
			CString station_desc, station_list;
			int station_number;
			line_number = top_of_text;
			have_honor = false;
			out_string.Empty();
			for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
				pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
				station_number = pRallyItemInlist->GetStationNumber();
				int akc_station_number = pRallyItemInlist->GetAKCNumber();
				station_location = pRallyItemInlist->GetStationMidPoint();
				station_location.x = (long)(station_location.x/this->m_pixels_per_foot_wd);
				station_location.y = (long)(station_location.y/this->m_pixels_per_foot_ht);

				if (this->m_sdpo_station_number) station_number_text.Format("%d. ",station_number);
				if (this->m_sdpo_akc_number) akc_number_text.Format("(AKC # %d) ",akc_station_number);
				if (this->m_sdpo_station_name) station_name = StationMapper::GetAKCDetailedDescrptionFromAKCNumber(akc_station_number) + " ";
				if (this->m_sdpo_xy_location) x_y_location.Format("%d-%d",station_location.x, station_location.y);

				if (akc_station_number != 1000) {
					if (akc_station_number == 1 || akc_station_number == 2) {
						station_desc = station_name + akc_number_text + x_y_location;
//						station_desc.Format("   %s (AKC # %d)",this->akc_station_desc[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
					}
					else {
						station_desc = station_number_text + station_name + akc_number_text + x_y_location;
//						station_desc.Format("%d. %s (AKC # %d)",station_number,this->akc_station_desc[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
					}

					temp_error = station_desc;
					while(not_done) {
						find_return = temp_error.Find("\r\n",0);
						if (find_return == -1) {
							out_string = temp_error;
							not_done = false;
						}
						else {
							out_string = temp_error.Left(find_return);
							temp_error.Delete(0,find_return + 2);
						}
						dc.TextOut(text_margin + 4,line_number,out_string);
						lines_printed++;
						line_number += line_height;
						if (lines_printed >= num_lines) {
							dc.EndPage();
							line_number = top_margin;
							lines_printed = 0;
							dc.StartPage();
						}
						
					}					
					line_number += line_height;
					lines_printed++;
					if (lines_printed >= num_lines) {
						dc.EndPage();
						line_number = top_margin;
						lines_printed = 0;
						dc.StartPage();
					}
					out_string.Empty();
					not_done = true;
//					text_rect.top = temp_rect.bottom;
				}
			}
			have_honor = false;
			if (have_honor) {
				if (this->m_sdpo_xy_location) x_y_location.Format("%d-%d",honor_location.x, honor_location.y);
				if (course_info.m_number_honor > 0) {
					station_desc.Format("%d. %s (AKC # 50) %s",this->m_num_stations + 1, StationMapper::GetAKCDetailedDescrptionFromAKCNumber(50),x_y_location);
				}
				else {
					station_desc.Format("    %s (AKC # 50) %s",StationMapper::GetAKCDetailedDescrptionFromAKCNumber(50),x_y_location);
				}
				temp_error = station_desc;
				while(not_done) {
					find_return = temp_error.Find("\r\n",0);
					if (find_return == -1) {
						out_string = temp_error;
						not_done = false;
					}
					else {
						out_string = temp_error.Left(find_return);
						temp_error.Delete(0,find_return + 2);
					}
					dc.TextOut(text_margin + 4,line_number,out_string);
					lines_printed++;
					line_number += line_height;
					if (lines_printed >= num_lines) {
						dc.EndPage();
						line_number = top_margin;
						lines_printed = 0;
						dc.StartPage();
					}
					
				}					
				line_number += line_height;

				out_string.Empty();
				not_done = true;
				mid_text = line_number + line_height;
				line_number += (int)1.5 * line_height;
				strResult += station_desc + "\r\n";

			}
			
			top_left.x = text_margin;
			top_left.y = line_number;
			line_number += (int)2 * line_height;


		}
		pOldPen = dc.SelectObject(pOldPen);
		dc.SelectObject(def_font);
		dc.EndPage();
		dc.EndDoc();
		CDC::FromHandle(hdc)->DeleteDC();
	}

	
}

void CDogRunDoc::OnCopyDesc() 
{
	// TODO: Add your command handler code here
	BOOL not_done = true;
	CRallyObject* pRallyItemInlist;
	POSITION pos;
//	Verify verify_course;
	CString strResult;	
	CourseInfo course_info;
	CString out_string, rally_date, rally_class, temp_error;
	CString judge_name, comp_name;
	CString station_number_text, akc_number_text, station_name, x_y_location, organization;
	CPoint station_location, honor_location;

	strResult.Empty();


	this->m_course_info->GetCourseInfo(&course_info);
	if (this->m_sdpo_show_course_info) {
		if (this->m_sdpo_date) rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
		if (this->m_sdpo_judge_name) judge_name.Format("JUDGE: %s  ",course_info.m_judge);
		if (this->m_sdpo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);
		if (this->m_sdpo_comp_name) comp_name.Format("TRIAL: %s",course_info.m_competation);
		out_string = judge_name + comp_name + organization;
			
//		out_string.Format("JUDGE: %s  TRIAL: %s",course_info.m_judge, course_info.m_competation);
		strResult += out_string + "\r\n";
		if (this->m_sdpo_class) {
			switch (course_info.m_class) {
			rally_class = "RALLY CLASS: ";
			case NOVICE:
				rally_class = "Novice";
				break;
			case ADVANCED:
				rally_class = "Advanced";		
				break;
			case EXCELLENT:
				rally_class = "Excellent";		
				break;
			case MASTER:
				rally_class = "Master";		
				break;
			case TRAINING:
				rally_class = "Training";
			}
		}
		if (this->m_sdpo_subclass) {
			switch (course_info.m_sub_class) {
			case CLASS_A:
				rally_class += " A ";
				break;
			case CLASS_B:
				rally_class += " B ";
				break;
			}
		}
		out_string = rally_class + rally_date;
//		out_string.Format("RALLY CLASS: %s  DATE: %s",rally_class, rally_date);

		strResult += out_string + "\r\n";
	}

	out_string.Format("Station List with description");

	strResult += out_string + "\r\n";

	
	pos = this->m_rallyList.GetHeadPosition();
	if (pos != NULL) {
		BOOL have_honor;
		CString station_desc, station_list;
		int station_number;
		have_honor = false;

		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			station_number = pRallyItemInlist->GetStationNumber();
			int akc_station_number = pRallyItemInlist->GetAKCNumber();
			station_location = pRallyItemInlist->GetStationMidPoint();
			station_location.x = (long)(station_location.x/this->m_pixels_per_foot_wd);
			station_location.y = (long)(station_location.y/this->m_pixels_per_foot_ht);
			
			
			if (this->m_sdpo_station_number) station_number_text.Format("%d. ",station_number);
			if (this->m_sdpo_akc_number) akc_number_text.Format("(AKC # %d) ",akc_station_number);
			if (this->m_sdpo_station_name) station_name =  StationMapper::GetAKCDetailedDescrptionFromAKCNumber(akc_station_number) + " ";
			if (this->m_sdpo_xy_location) x_y_location.Format("%d-%d",station_location.x, station_location.y);
	
			if (akc_station_number == 5000) {
				have_honor = true;
				honor_location = station_location;

			}
			if (akc_station_number != 5000) {
				if (akc_station_number == 1 || akc_station_number == 2) {
					station_desc = station_name + akc_number_text + x_y_location;
//					station_desc.Format("   %s (AKC # %d)",this->akc_station_desc[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				else {
					station_desc = station_number_text + station_name + akc_number_text + x_y_location;
//					station_desc.Format("%d. %s (AKC # %d)",station_number,this->akc_station_desc[pRallyItemInlist->GetAKCNumber()], pRallyItemInlist->GetAKCNumber());
				}
				station_desc.Replace("\r\n"," ");
				strResult += station_desc + "\r\n";
			}
		}
		have_honor = false;
		if (have_honor) {
			if (this->m_sdpo_xy_location) x_y_location.Format("%d-%d",honor_location.x, honor_location.y);
			if (course_info.m_number_honor > 0) {
				station_desc.Format("%d. %s (AKC # 50) %s",this->m_num_stations + 1, StationMapper::GetAKCDetailedDescrptionFromAKCNumber(50),x_y_location);
			}
			else {
				station_desc.Format("    %s (AKC # 50) %s",StationMapper::GetAKCDetailedDescrptionFromAKCNumber(50),x_y_location);
			}
			station_desc.Replace("\r\n"," ");

			strResult += station_desc + "\r\n";

		}
		

	}

	// copy the string to the clipboard
	pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView( pos );

		
	if (!pFirstView->OpenClipboard())
	{
		AfxMessageBox("Error Opening Clipboard");
		return;
	}


	int nTextLen = (strResult.GetLength()+1)*sizeof(TCHAR);
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nTextLen);
	if (hGlobal != NULL)
	{
		LPVOID lpText = GlobalLock(hGlobal);
		memcpy(lpText, strResult, nTextLen);

		EmptyClipboard();
		GlobalUnlock(hGlobal);
	#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hGlobal);
	#else
		SetClipboardData(CF_TEXT, hGlobal);
	#endif
	}
	CloseClipboard();	
	AfxMessageBox("A copy of the station list is available for pasting into another application.",MB_OK);		
}

void CDogRunDoc::SetStationNumberForHonor(BOOL number_station)
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		int akc_station_number = pRallyItemInlist->GetAKCNumber();
		if (akc_station_number == 50) {
			if (number_station) {
				pRallyItemInlist->SetStationNumber(this->m_num_stations + 1);
			}
			else {
				pRallyItemInlist->SetStationNumber(HONOR_STATION);
			}			
			pos = NULL;
		}
	}
}

void CDogRunDoc::AddArrow(CRallyObject* pRallyItemAdded, bool from_undo_delete)
{

// create a new arrow
	ArrowObj *p_Arrow, *p_existing_arrow;
	CPoint cp_entry, cp_exit;
	BOOL found_start = false;
	CRallyObject* pRallyItemInlist;
	int bitmap_num, station_number_add;
	POSITION pos;
	int station_count = this->m_rallyList.GetCount();
	if (station_count<= 1) return; // no arrows needed 	
	int station_id = pRallyItemAdded->GetStationID();
	bool have_sit_stay = this->m_rallyList.HaveSitStayStation();
	switch(pRallyItemAdded->GetStationID()) {
	case IDB_START: // start station
		// need to find station to draw to next station in list or finish
		for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
			bitmap_num = pRallyItemInlist->GetStationID();
			int station_id = pRallyItemInlist->GetStationID();
			int station_number = pRallyItemInlist->GetStationNumber();
			int string_number = pRallyItemInlist->GetStringNumber();
			if (station_number != START_STATION) {// && station_number != CALL_TO_HEEL_STATION && string_number != ID__DRAW_SITSTAY ) {
				m_rallyList.CalculateEntryExitPoints(pRallyItemAdded, pRallyItemInlist, &cp_entry, &cp_exit);
				p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemInlist->GetStationNumber(), pRallyItemAdded->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
				if (bitmap_num == IDB_FINISH) {
					p_Arrow->SetEntryOwner(FINISH_STATION);
				}
				else {
					p_Arrow->SetEntryOwner(1);
				}
				p_Arrow->SetExitOwner(START_STATION);
				this->m_arrowList.AddHead(p_Arrow);
				pos = NULL;
			}
		}		
		break;
	case IDB_FINISH: // finish station
		// walk backwards looking for first non-finsh or honor station
		for( pos = this->m_rallyList.GetTailPosition(); pos != NULL; ) {
			pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetPrev(pos);
			bitmap_num = pRallyItemInlist->GetStationID();
			int station_number = pRallyItemInlist->GetStationNumber();
			int string_number = pRallyItemInlist->GetStringNumber();

			if (station_number != FINISH_STATION) {// && station_number != CALL_TO_HEEL_STATION && string_number != ID__DRAW_SITSTAY) {
				m_rallyList.CalculateEntryExitPoints(pRallyItemInlist, pRallyItemAdded, &cp_entry, &cp_exit);
				p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemAdded->GetStationNumber(), pRallyItemInlist->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
				p_Arrow->SetEntryOwner(FINISH_STATION);
				if (bitmap_num == IDB_START) {
					p_Arrow->SetExitOwner(pRallyItemInlist->GetStationNumber());
				}
				else if (this->m_num_stations < 1) {
					p_Arrow->SetExitOwner(START_STATION);
				}
				else {
					if (have_sit_stay)
					{
						if (this->m_num_stations == 1)
						{
							p_Arrow->SetExitOwner(START_STATION);
						}
						else
						{
							p_Arrow->SetExitOwner(this->m_num_stations-1);
						}
					}
					else 
					{
						p_Arrow->SetExitOwner(this->m_num_stations);
					}
				}
				this->m_arrowList.AddHead(p_Arrow);
				pos = NULL;
			}
		}
		break;
/*
	case ID__DRAW_CALLTOHEEL://call to heel  station
		return; // no p_Arrow to or from honor station
		break;
*/
	case IDB_RETRIEVE_FINISH: //APDT bonus station no arrows
		return;
		break;
	default:
		int station_number = pRallyItemAdded->GetStringNumber();
		station_number_add = pRallyItemAdded->GetStationNumber();
		bool have_sit_stay = this->m_rallyList.HaveSitStayStation();
		bool handle_sit_stay = false;
		if (from_undo_delete && (station_number_add != this->m_num_stations)){
			pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(station_number_add+1);
			if (pRallyItemInlist != NULL) {
				m_rallyList.CalculateEntryExitPoints(pRallyItemAdded ,pRallyItemInlist, &cp_entry, &cp_exit);
				p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemInlist->GetStationNumber(), pRallyItemAdded->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
				this->m_arrowList.AddHead(p_Arrow);
			}
		}
		else {
			if (have_sit_stay && (station_number_add == 2))
			{
				handle_sit_stay = true;
			}
			if (station_number_add == 1 || handle_sit_stay) {
				if (from_undo_delete) {
					pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(FINISH_STATION);
					if (pRallyItemInlist) {
						p_existing_arrow = this->m_arrowList.FindArrow(1, FINISH_STATION);
						if (!p_existing_arrow) {
							m_rallyList.CalculateEntryExitPoints(pRallyItemAdded, pRallyItemInlist, &cp_entry, &cp_exit);
							p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemInlist->GetStationNumber(), pRallyItemAdded->GetStationNumber(),  this->m_default_arrow_type, this->m_move_arrows_with_station, false);
							this->m_arrowList.AddHead(p_Arrow);
						}
					}
					pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(START_STATION);
					if (pRallyItemInlist){
						p_existing_arrow = this->m_arrowList.FindArrow(START_STATION, FINISH_STATION);
						if (p_existing_arrow) {
							m_rallyList.CalculateEntryExitPoints(pRallyItemInlist, pRallyItemAdded, &cp_entry, &cp_exit);
							p_existing_arrow->SetEntryPoint(&cp_entry);
							p_existing_arrow->SetEntryOwner(station_number_add);
						}
						else {
							m_rallyList.CalculateEntryExitPoints(pRallyItemInlist, pRallyItemAdded, &cp_entry, &cp_exit);
							p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemAdded->GetStationNumber(), pRallyItemInlist->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
							this->m_arrowList.AddHead(p_Arrow);
							found_start = true;
						}
					}
				}
				else {
					pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(START_STATION);
					p_existing_arrow = this->m_arrowList.FindArrow(START_STATION, 1);
					if (pRallyItemInlist != NULL && !p_existing_arrow) {
						m_rallyList.CalculateEntryExitPoints(pRallyItemInlist, pRallyItemAdded, &cp_entry, &cp_exit);
						p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemAdded->GetStationNumber(), pRallyItemInlist->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
						this->m_arrowList.AddHead(p_Arrow);
						found_start = true;
					}
					pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(FINISH_STATION);
					if (pRallyItemInlist != NULL) {
						m_rallyList.CalculateEntryExitPoints(pRallyItemAdded, pRallyItemInlist, &cp_entry, &cp_exit);
						if (found_start) {
							p_Arrow = this->m_arrowList.FindArrow(START_STATION, FINISH_STATION);
							if (p_Arrow != NULL) {
								p_Arrow->SetExitPoint(&cp_exit);
								p_Arrow->SetExitOwner(station_number_add);
							}
						}
						else {
							p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemAdded->GetStationNumber(), pRallyItemInlist->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
							this->m_arrowList.AddHead(p_Arrow);
						}
					}
				}
			}
			else if (station_number_add == this->m_num_stations) {
				pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(station_number_add-1);
				if (pRallyItemInlist != NULL) {
					m_rallyList.CalculateEntryExitPoints(pRallyItemInlist, pRallyItemAdded, &cp_entry, &cp_exit);
					p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemAdded->GetStationNumber(), pRallyItemInlist->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
					this->m_arrowList.AddHead(p_Arrow);
				}
				pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(FINISH_STATION);
				if (pRallyItemInlist != NULL) {
					m_rallyList.CalculateEntryExitPoints(pRallyItemAdded, pRallyItemInlist, &cp_entry, &cp_exit);
					p_Arrow = this->m_arrowList.FindArrow(station_number_add-1, FINISH_STATION);
					if (p_Arrow != NULL) {
						p_Arrow->SetExitPoint(&cp_exit);
						p_Arrow->SetExitOwner(station_number_add);
					}
				}
			}
			else {
				if (from_undo_delete){
					pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(station_number_add+1);
					if (pRallyItemInlist != NULL) {
						m_rallyList.CalculateEntryExitPoints(pRallyItemAdded ,pRallyItemInlist, &cp_entry, &cp_exit);
						p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemInlist->GetStationNumber(), pRallyItemAdded->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
						this->m_arrowList.AddHead(p_Arrow);
					}
				}
				else {
					pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(station_number_add-1);
					if (pRallyItemInlist != NULL) {
						m_rallyList.CalculateEntryExitPoints(pRallyItemInlist, pRallyItemAdded, &cp_entry, &cp_exit);
						p_Arrow = new ArrowObj(&cp_entry, &cp_exit, &this->m_default_pen, pRallyItemAdded->GetStationNumber(), pRallyItemInlist->GetStationNumber(), this->m_default_arrow_type, this->m_move_arrows_with_station, false);
						this->m_arrowList.AddHead(p_Arrow);
					}
				}
			}
		}
		break;
	}
	
}

void CDogRunDoc::CalculateExitEntryPoints(CRallyObject *first_station, CRallyObject *second_station, POINT *entry, POINT *exit)
{
	POINT first_point, second_point;
	POINT top_exit, left_exit, right_exit, bottom_exit, exit_point;
	POINT top_entry, left_entry, right_entry, bottom_entry, entry_point;

	first_station->GetRectEntryExits(&top_exit, &left_exit, &right_exit, &bottom_exit, false);				
	first_point = first_station->GetStationMidPoint();

	second_station->GetRectEntryExits(&top_entry, &left_entry, &right_entry, &bottom_entry, true);				
	second_point = second_station->GetStationMidPoint();

	if ((second_point.x == first_point.x) && (second_point.y > first_point.y)) {
		exit_point = bottom_exit;
		entry_point = top_entry;
	} 
	else if ((second_point.x == first_point.x) && (second_point.y < first_point.y)) {
		exit_point = top_exit;
		entry_point = bottom_entry;
	}
	else if ((second_point.y == first_point.y) && (second_point.x > first_point.x)) {
		exit_point = right_exit;
		entry_point = left_entry;
	}
	else if ((second_point.y == first_point.y) && (second_point.x < first_point.x)) {
		exit_point = left_exit;
		entry_point = right_entry;
	}

	else if ((second_point.y > first_point.y)  && (second_point.x > first_point.x)) {
		if (right_exit.x <= left_entry.x) {
			exit_point  = right_exit;
			entry_point = left_entry;
		}
		else {
			exit_point  = bottom_exit;
			entry_point = top_entry;

		}
	}
	else if ((second_point.y > first_point.y)  && (second_point.x < first_point.x)) {
		if (left_exit.x >= right_entry.x) {
			exit_point  = left_exit;
			entry_point = right_entry;
		}
		else {
			exit_point  = bottom_exit;
			entry_point = top_entry;

		}

	}
	else if ((second_point.y < first_point.y)  && (second_point.x > first_point.x)) {
		if (right_exit.x >= left_entry.x) {
			exit_point  = top_exit;
			entry_point = bottom_entry;
		}
		else {
			exit_point  = right_exit;
			entry_point = left_entry;

		}

	}
	else if ((second_point.y < first_point.y)  && (second_point.x < first_point.x)) {
		if (left_exit.x >= right_entry.x) {
			exit_point  = left_exit;
			entry_point = right_entry;
		}
		else {
			exit_point  = top_exit;
			entry_point = bottom_entry;

		}
	}		
	*entry = entry_point;
	*exit = exit_point;

}

void CDogRunDoc::SetUpAddMenu()
{
	POSITION pos = GetFirstViewPosition();
	CView* pview = GetNextView(pos);
	ASSERT(pview != NULL);

	CChildFrame* pwnd = (CChildFrame*)pview->GetParentFrame();
	ASSERT_KINDOF(CChildFrame, pwnd);
	pwnd->SetAddMenu();
	pwnd->SetUpChangeMenu();
}

LOGPEN * CDogRunDoc::GetDefaultPen()
{
	return &this->m_default_pen;
}

void CDogRunDoc::CopyPylonObjectData(PylonObj *dest, PylonObj *src)
{
	POINT x_y_pos;
	src->GetXYPosition(&x_y_pos);
	dest->SetXYPosition(&x_y_pos);	
}

void CDogRunDoc::CopySpecialObjectData(SpecialObj *dest, SpecialObj *src)
{
	CRect object_rect;
	float M11, M12, M21, M22;
	dest->SetXPos(src->GetXPos());
	dest->SetYPos(src->GetYPos());
	dest->SetTypeObject(src->GetTypeObject());
//	dest->SetSpecialRect();
	src->GetSpecialRect(&object_rect);
	dest->SetSpecialRect(&object_rect);	src->GetRotateMeasurements(&M11,&M12,&M21,&M22);
	dest->SetRotateMeasurements(M11,M12,M21,M22);
}

void CDogRunDoc::CopyTextObjectData(TextObj *dest, TextObj *src)
{

	CRect text_rect;
	LOGFONT text_font;
	dest->SetDisplayText(&src->GetDisplayText());
	src->GetDisplayTextRect(&text_rect);
	dest->SetDisplayTextRect(&text_rect);
	dest->SetTextColor(src->GetColorRef());
	src->GetLogFont(&text_font);
	dest->SetLogFont(&text_font);
	dest->SetDrawBox(src->GetDrawBox());
	dest->SetTextBoxRectColor(src->GetTextBoxRectColor());
}

void CDogRunDoc::CopyArrowObjectData(ArrowObj *dest, ArrowObj *src)
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
	dest->m_move_with_station = src->m_move_with_station;
}

int CDogRunDoc::GetDefaultArrowType()
{
	return this->m_default_arrow_type;
}

void CDogRunDoc::SetDefaultArrowType(int default_arrow)
{
	this->m_default_arrow_type = default_arrow;
}

void CDogRunDoc::SetDefaultPen(LOGPEN *default_pen)
{
	this->m_default_pen = *default_pen;
}

int CDogRunDoc::GetDefaultCourseLogFont(LOGFONT *p_log_font)
{
	this->m_course_font->GetLogFont(p_log_font);
	return this->m_course_font->GetColorReference();
}

void CDogRunDoc::SetDefaultCourseFont(LOGFONT *p_log_font, int color_ref)
{

	this->m_course_font->SetFont(p_log_font);
	this->m_course_font->SetColorReference(color_ref);

}

int CDogRunDoc::GetDefaultStationLogFont(LOGFONT *p_log_font)
{
	this->m_stat_font->GetLogFont(p_log_font);
	return this->m_stat_font->GetColorReference();
}

void CDogRunDoc::SetDefaultStationFont(LOGFONT *p_log_font, int color_ref)
{
	this->m_stat_font->SetFont(p_log_font);
	this->m_stat_font->SetColorReference(color_ref);
}

int CDogRunDoc::GetDefaultTextFont(LOGFONT *p_log_font)
{
	this->m_text_font->GetLogFont(p_log_font);
	return this->m_text_font->GetColorReference();
}

void CDogRunDoc::SetDefaultTextFont(LOGFONT *p_log_font, int color_ref)
{
	this->m_text_font->SetFont(p_log_font);
	this->m_text_font->SetColorReference(color_ref);
}

BOOL CDogRunDoc::SetApplicationDefaultsCourseText()
{
	//course map text preferences
// course info
	AfxGetApp()->WriteProfileInt(szSection, "CMTClass",this->m_course_info->m_cmt_class);
	AfxGetApp()->WriteProfileInt(szSection, "CMTCompName",this->m_course_info->m_cmt_comp_name);
	AfxGetApp()->WriteProfileInt(szSection, "CMTDate",this->m_course_info->m_cmt_date);
	AfxGetApp()->WriteProfileInt(szSection, "CMTJudgeName",this->m_course_info->m_cmt_judge_name);
	AfxGetApp()->WriteProfileInt(szSection, "CMTOrganize",this->m_course_info->m_cmt_organization);
	AfxGetApp()->WriteProfileInt(szSection, "CMTLocation",this->m_course_info->m_cmt_location);
	AfxGetApp()->WriteProfileInt(szSection, "CMTSubclass",this->m_course_info->m_cmt_subclass);

	return true;
}

void CDogRunDoc::SetApplicationStationListPreferences()
{
// station list course map
	AfxGetApp()->WriteProfileInt(szSection, "CMTStatName",this->m_cmt_station_name);
	AfxGetApp()->WriteProfileInt(szSection, "CMTStatNo",this->m_cmt_station_number);
	AfxGetApp()->WriteProfileInt(szSection, "CMTAKCNo",this->m_cmt_akc_number);
	AfxGetApp()->WriteProfileInt(szSection, "CMTXYLoc",this->m_cmt_xy_location);

	AfxGetApp()->WriteProfileInt(szSection, "SLPOStatName",this->m_slpo_station_name);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOStatNo",this->m_slpo_station_number);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOAKCNo",this->m_slpo_akc_number);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOXYLoc",this->m_slpo_xy_location);

	AfxGetApp()->WriteProfileInt(szSection, "SLPOCourseInfo",this->m_slpo_show_course_info);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOClass",this->m_slpo_class);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOCompName",this->m_slpo_comp_name);
	AfxGetApp()->WriteProfileInt(szSection, "SLPODate",this->m_slpo_date);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOJudgeName",this->m_slpo_judge_name);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOLocation",this->m_slpo_location);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOSubclass",this->m_slpo_subclass);
	AfxGetApp()->WriteProfileInt(szSection, "SLPOStats",this->m_slpo_show_stats);

}

void CDogRunDoc::SetApplicationDefaultStationDescriptionPreferences()
{
	AfxGetApp()->WriteProfileInt(szSection, "SDPOCourseInfo",this->m_slpo_show_course_info);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOClass",this->m_sdpo_class);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOCompName",this->m_sdpo_comp_name);
	AfxGetApp()->WriteProfileInt(szSection, "SDPODate",this->m_sdpo_date);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOJudgeName",this->m_sdpo_judge_name);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOLocation",this->m_sdpo_location);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOSubclass",this->m_sdpo_subclass);

	AfxGetApp()->WriteProfileInt(szSection, "SDPOStatName",this->m_sdpo_station_name);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOStatNo",this->m_sdpo_station_number);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOAKCNo",this->m_sdpo_akc_number);
	AfxGetApp()->WriteProfileInt(szSection, "SDPOXYLoc",this->m_sdpo_xy_location);


}

void CDogRunDoc::SetApplicationDefaultScoreSheetPreferences()
{
	AfxGetApp()->WriteProfileInt(szSection, "SSPOCourseInfo",this->m_sspo_show_course_info);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOClass",this->m_sspo_class);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOCompName",this->m_sspo_comp_name);
	AfxGetApp()->WriteProfileInt(szSection, "SSPODate",this->m_sspo_date);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOJudgeName",this->m_sspo_judge_name);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOLocation",this->m_sspo_location);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOSubclass",this->m_sspo_subclass);

	AfxGetApp()->WriteProfileInt(szSection, "SSPOArmBand",this->m_sspo_arm_band);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOJumpHt",this->m_sspo_jump_ht);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOBreed",this->m_sspo_breed);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOFinalScore",this->m_sspo_final_score);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOTime",this->m_sspo_time);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOJudgeSign",this->m_sspo_judge_sign);

	AfxGetApp()->WriteProfileInt(szSection, "SSPOStatName",this->m_sspo_station_name);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOStatNo",this->m_sspo_station_number);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOAKCNo",this->m_sspo_akc_number);
	AfxGetApp()->WriteProfileInt(szSection, "SSPOXYLoc",this->m_sspo_xy_location);

}

void CDogRunDoc::SetDefaultRallyStationSize(int rally_station_size)
{
	this->m_station_size = rally_station_size;
	AfxGetApp()->WriteProfileInt(szSection, "StationSize",this->m_station_size);

}

int CDogRunDoc::GetRallyStationSize()
{
	return this->m_station_size;
}



void CDogRunDoc::CopyScribbleObjectData(Scribble *dest, Scribble *src)
{
	dest->m_pointArray.RemoveAll();
	LOGPEN scribble_pen;
	dest->SetScribblePen(src->GetScribblePen(&scribble_pen));
	dest->m_rectBounding = src->m_rectBounding;
	for (int i=0; i < src->m_pointArray.GetSize(); i++) {
		dest->m_pointArray.Add(src->m_pointArray.GetAt(i));
	}
}

void CDogRunDoc::ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (CArchiveException::badIndex && !bSaving) {
		MessageBox(NULL,"This file is in the old format. File will be opened for editing.","File Error",MB_OK);
//		if (!this->OnOpenDocument(lpszPathName)) {
//			MessageBox(NULL,"Could Not Open File!","File Error",MB_OK);
//		}
	}


	else CDocument::ReportSaveLoadException(lpszPathName, e, bSaving, nIDPDefault);
}

BOOL CDogRunDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL file_open;
	BOOL open_document = CDocument::OnOpenDocument(lpszPathName);
	if (!open_document) {
		CFile theFile;
		file_open = theFile.Open(lpszPathName, CFile::modeRead);
		if (!file_open) {
			return FALSE;
		}
		CArchive archive(&theFile, CArchive::load);
		this->GetApplicationDefaults();
		this->GetApplicationDefaultFonts();
		archive >> this->m_doc_author;
		archive >> this->m_doc_notes;
		archive >> this->m_doc_created;
		archive >> this->m_doc_modified;
		archive >> this->m_doc_printed;
		archive >> this->m_num_stations;

		this->m_course_info->Serialize(archive,true, true);
		this->m_station_list->Serialize(archive, true, true);
		CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
		g_convert_course = true;

		this->m_rallyList.Serialize(archive);
		this->PullListApart();
		archive.Close();
		theFile.Close();
		g_convert_course = false;
		if (this->m_course_info->GetShowPath()){
			// we need to create Arrows
			this->CreateArrowsOnFileConvert();
		}
		this->SetNewStationVariables();
		this->SetStationType(this->m_course_info->GetTypeOfCourse());
		this->m_rallyList.SetLastNumber(this->m_num_stations);
	}
	else 
	{
		if (this->old_version_close)
		{
			return FALSE;
		}
		return TRUE;
	}
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

void CDogRunDoc::CreateArrowsOnFileConvert(void) {
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		if (pRallyItemInlist->GetStationNumber() != START_STATION) this->AddArrow(pRallyItemInlist,false);
	}
	
}

void CDogRunDoc::SetNewStationVariables()
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		pRallyItemInlist->SetStationDescription(BOTH_TEXT_PIC);
		pRallyItemInlist->SetRotateText(false);
		pRallyItemInlist->SetStringNumber(StationMapper::ObjectIDFromAKCNumber(pRallyItemInlist->GetAKCNumber()));
	}
}

void CDogRunDoc::SetStationType(int type_of_course)
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	for( pos = this->m_rallyList.GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->m_rallyList.GetNext(pos);
		pRallyItemInlist->SetStationType(type_of_course);
	}
}


BOOL CDogRunDoc::GetDocumentMoveArrowsWithStation()
{
	return this->m_move_arrows_with_station;
}

void CDogRunDoc::SetDocumentMoveArrowsWithStation(BOOL move_arrows_with_station)
{
	this->m_move_arrows_with_station = move_arrows_with_station;
}

BOOL CDogRunDoc::GetPrintLeftOneInchMargin()
{
	return this->m_left_margin;
}

void CDogRunDoc::SetLeftOneInchMargin(BOOL left_margin_one_inch)
{
	this->m_left_margin = left_margin_one_inch;
	AfxGetApp()->WriteProfileInt(szSection, "LeftMargin",this->m_left_margin);

}
void CDogRunDoc::CopyHTML(CString html)
{
   // Create temporary buffer for HTML header...
  //  char *buf = new char [400 + strlen(html)];

    // Get clipboard id for HTML format...
    static int cfid = 0;
    if(!cfid) cfid = RegisterClipboardFormat("HTML Format");

    // Create a template string for the HTML header...
	CString start_html = "Version:0.9\r\nStartHTML:00000000\r\nEndHTML:00000000\r\nStartFragment:00000000\r\nEndFragment:00000000\r\n<html><body>\r\n<!--StartFragment -->\r\n";
	int size = start_html.GetLength() + html.GetLength() + 400;
    char *buf = new char [size];
     if(!buf) return;	
	strcpy(buf, start_html);

    // Append the HTML...
	strcat(buf, html);
    strcat(buf, "\r\n");
    // Finish up the HTML format...
	CString end_html = "<!--EndFragment-->\r\n"
        "</body>\r\n"
        "</html>";
	strcat(buf, end_html);

    // Now go back, calculate all the lengths, and write out the
    // necessary header information. Note, wsprintf() truncates the
    // string when you overwrite it so you follow up with code to replace
    // the 0 appended at the end with a '\r'...
    char *ptr = strstr(buf, "StartHTML");
    wsprintf(ptr+10, "%08u", strstr(buf, "<html>") - buf);
    *(ptr+10+8) = '\r';

    ptr = strstr(buf, "EndHTML");
    wsprintf(ptr+8, "%08u", strlen(buf));
    *(ptr+8+8) = '\r';

    ptr = strstr(buf, "StartFragment");
    wsprintf(ptr+14, "%08u", strstr(buf, "<!--StartFrag") - buf);
    *(ptr+14+8) = '\r';

    ptr = strstr(buf, "EndFragment");
    wsprintf(ptr+12, "%08u", strstr(buf, "<!--EndFrag") - buf);
    *(ptr+12+8) = '\r';

    // Now you have everything in place ready to put on the
    // clipboard.

    // Open the clipboard...
	// copy the string to the clipboard
	POSITION pos = GetFirstViewPosition();
	pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView( pos );
    if(pFirstView->OpenClipboard()) {
        
        // Empty what's in there...
        EmptyClipboard();
        
        // Allocate global memory for transfer...
        HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE |GMEM_DDESHARE, strlen(buf)+4);
        
        // Put your string in the global memory...
        char *ptr = (char *)GlobalLock(hText);
        strcpy(ptr, buf);
        GlobalUnlock(hText);
        
        ::SetClipboardData(cfid, hText);
        
        CloseClipboard();
        // Free memory...
        GlobalFree(hText);
        
    }

    // Clean up...
    delete [] buf;

}

void CDogRunDoc::OnCopyHtml() 
{
	// TODO: Add your command handler code here
	CString judge_name, comp_name, organization;
	CString station_number_text, akc_number_text, station_name, x_y_location;
	BOOL have_honor, have_start, have_finish;

	CString strResult;	
	
	CourseInfo course_info;
	this->m_course_info->GetCourseInfo(&course_info);
	have_honor = false;
	have_start = this->StartStationInList();
	have_finish = this->FinishStationInList();
	CString out_string, rally_date, rally_class;

	CString score_sheet_header;
	if (this->m_sspo_show_course_info) {
		if (this->m_sspo_date) rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));
		if (this->m_sspo_judge_name) judge_name.Format("JUDGE: %s  ",course_info.m_judge);
		if (this->m_sspo_comp_name) comp_name.Format("TRIAL: %s", course_info.m_competation);
		if (this->m_sspo_organization) organization.Format(" ORGANIZATION: %s", course_info.m_organization);
		if (this->m_sspo_class) {
			rally_class = "RALLY CLASS: ";
			switch (course_info.m_class) {
			case NOVICE:
				rally_class += "Novice ";
				break;
			case ADVANCED:
				rally_class += "Advanced ";		
				break;
			case EXCELLENT:
				rally_class += "Excellent ";		
				break;
		case MASTER:
			rally_class = "Master";		
			break;
			case TRAINING:
				rally_class += "Training ";
			}
		}
		if (this->m_sspo_subclass) {
			switch (course_info.m_sub_class) {
			case CLASS_A:
				rally_class += " A ";
				break;
			case CLASS_B:
				rally_class += " B ";
				break;
			}
		}
		out_string = "<p>" +judge_name + comp_name + organization + "<BR>" + rally_class + "<BR>" + "Arm Band No:____________  Breed:_____________  Jump Height:_____________</p>";;
	}
	
	score_sheet_header = "<STYLE TYPE='text/css'> <!--BODY{ font-family:Arial;font-size:8pt }--> </STYLE><FONT FACE='Arial' SIZE='1'>" + out_string;

	
	CString table_header;
	table_header = "<table border=1 cellspacing=0 cellpadding=0"
" style='border-collapse:collapse;border:none;mso-border-alt:solid windowtext .5pt;"
" mso-yfti-tbllook:480;mso-padding-alt:0in 5.4pt 0in 5.4pt;mso-border-insideh:"
" .5pt solid windowtext;mso-border-insidev:.5pt solid windowtext'>"
" <tr style='mso-yfti-irow:0;mso-yfti-firstrow:yes' >"
"  <td width=151 valign=top style='width:113.4pt'>"
"  <p >Deductions<o:p></o:p></p>"
"  </td>"
"  <td width=48 valign=top style='width:.5in'>"
"  <p >Marks<o:p></o:p></p>"
"  </td>"
"  <td width=60 valign=top style='width:45.0pt'>"
"  <p >Pts Lost<o:p></o:p></p>"
"  </td>"
"  <td width=240 valign=top style='width:2.5in'>"
"  <p >Station<o:p></o:p></p>"
"  </td>"
"  <td width=91 valign=top style='width:.95in'>"
"  <p >Pts Lost<o:p></o:p></p>"
"  </td>"
" </tr>";// first row
	CString marks_cell, marks_pts_lost_cell, station_desc_cell, station_pts_lost_cell;
	marks_cell = "  <td width=48 valign=top style='width:.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	marks_pts_lost_cell = "  <td width=60 valign=top style='width:45.0pt'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";// marks points lost cell
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, 1);
	station_pts_lost_cell = "  <td width=91 valign=top style='width:.95in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	CString one_point;
	one_point = " <tr style='mso-yfti-irow:1'>"
"  <td width=151 valign=top style='width:113.4pt'>"
"  <p >1-2 Points<o:p></o:p></p>"
"  </td>";
	int row;
	CString score_sheet, station_desc_first, station_desc_last, station_desc;
	station_desc_first = " <tr style='mso-yfti-irow:";
	station_desc_last = ";height:14.0pt'>"
"  <td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	score_sheet = score_sheet_header + table_header + one_point + marks_cell + marks_pts_lost_cell + station_desc_cell + station_pts_lost_cell;
	score_sheet += " <tr style='mso-yfti-irow:2;height:14.0pt'>"
"  <td width=151 rowspan=6 valign=top style='width:113.4pt;height:14.0pt'>"
"  <p >Tight Leash; Poor Sits; Slow, delay, or resistance to respond; Out of Position;"
"  Touches jump, pylon, post, or person; Dog interfering with handler<o:p></o:p></p>"
"  </td> <td width=108 colspan=2 rowspan=6 valign=top style='width:81.0pt'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, 2);
	score_sheet += station_desc_cell + station_pts_lost_cell;
	row = 3;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);

	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += "<tr style='mso-yfti-irow:8'>"
"  <td width=151 valign=top style='width:113.4pt'>"
"  <p >3 Points<o:p></o:p></p>"
"  </td>" + marks_cell + marks_pts_lost_cell + station_desc_cell + station_pts_lost_cell;
	row ++;
	score_sheet += " <tr style='mso-yfti-irow:9;height:14.0pt'>"
"  <td width=151 rowspan=6 valign=top style='width:113.4pt'>"
"  <p >Repeat of station (2 re-tries max.); Pylon or Post knocked over; Lack of control; Loud"
"  or intimidating command or signal; Excessive barking<o:p></o:p></p>"
"  </td><td width=108 colspan=2 rowspan=6 valign=top style='width:81.0pt'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += station_desc_cell + station_pts_lost_cell;

	row++;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += station_desc_cell + station_pts_lost_cell;
	row ++;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
//	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
//	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
//	row++;
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += " <tr style='mso-yfti-irow:15'>"
"  <td width=151 valign=top style='width:113.4pt'>"
"  <p >10 Points<o:p></o:p></p>"
"  </td>"+ marks_cell + marks_pts_lost_cell + station_desc_cell + station_pts_lost_cell;
	row ++;
	score_sheet += " <tr style='mso-yfti-irow:16;height:14.0pt'>"
"  <td width=151 rowspan=3 valign=top style='width:113.4pt'>"
"  <p >Incorrectly performed station; Hitting the jump<o:p></o:p></p>"
"  </td> <td width=108 colspan=2 rowspan=3 valign=top style='width:81.0pt'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += station_desc_cell + station_pts_lost_cell;
	row ++;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += " <tr style='mso-yfti-irow:19'>"
"  <td width=151 valign=top style='width:113.4pt'>"
"  <p >1-10"
"  Points<o:p></o:p></p>"
"  </td>"+ marks_cell + marks_pts_lost_cell + station_desc_cell + station_pts_lost_cell;
	row ++;
	score_sheet += " <tr style='mso-yfti-irow:20;height:14.0pt'>"
"  <td width=151 rowspan=3 valign=top style='width:113.4pt'>"
"  <p >Lack of teamwork; Lack of briskness; Handler error<o:p></o:p></p>"
"  </td> <td width=108 colspan=2 rowspan=3 valign=top style='width:81.0pt'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += station_desc_cell + station_pts_lost_cell;
	row ++;	
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += " <tr style='mso-yfti-irow:23'>"
"  <td width=151 valign=top style='width:113.4pt'>"
"  <p >NQ<o:p></o:p></p>"
"  </td>" + marks_cell + marks_pts_lost_cell + station_desc_cell + station_pts_lost_cell;
	row ++;;
	score_sheet += " <tr style='mso-yfti-irow:24;height:14.0pt'>"
"  <td width=151 rowspan=21 valign=top style='width:113.4pt'>"
"  <p >Minimum requirements not met; Dog unmanageable or uncontrolled barking; Station not attempted;"
"  Consistently tight lead; Substantially out of position or not completing the"
"  honor exercise; Elimination in the ring during the judging; Bar knocked off"
"  the uprights; Using a jump as an aid in going over; Failure of dog to go over"
"  the jump in the proper direction; Handler error<o:p></o:p></p>"
"  </td><td width=108 colspan=2 rowspan=21 valign=top style='width:81.0pt'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>"; 
	station_desc_cell = "<td width=240 valign=top style='width:2.5in'>"
"  <p ><o:p>&nbsp;</o:p></p>"
"  </td>";
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	score_sheet += station_desc_cell + station_pts_lost_cell;
	row ++;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	station_desc_cell.Format("%s%d%s",station_desc_first,row,station_desc_last);
	station_desc_cell = this->CreateStationDescription(station_desc_cell, row);
	row++;
	score_sheet += station_desc_cell + station_pts_lost_cell;
	score_sheet += "</table> <p align = 'Right'>Total Points Deducted:________</p>";
	score_sheet += "<p align = 'right'>FINAL SCORE:________<BR>";
	score_sheet +=                           "TIME:________<BR>";
	score_sheet += "JUDGE'S SIGNATURE:_____________________<BR></p></FONT> ";

 
	CopyHTML(score_sheet);
	AfxMessageBox("A copy of the score sheet is available for pasting into another application.",MB_OK);		

 
}

CString CDogRunDoc::CreateStationDescription(CString station_desc, int row_number)
{
	CString station_desc_text;
	BOOL have_honor, have_finish, have_start;
	int station_number_look_up;
	CourseInfo course_info;
	CRallyObject* pRallyItemInlist;
	have_start = this->StartStationInList();
	have_finish = this->FinishStationInList();
	this->m_course_info->GetCourseInfo(&course_info);
	have_honor = false;
	int total_number_of_stations = this->m_rallyList.GetCount();
	station_number_look_up = row_number;
	if (row_number > total_number_of_stations) {
//		station_desc.Empty();
		return station_desc;
	}
	if (row_number == 1 && have_start) {
		pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(START_STATION);
		station_desc_text.Format("%s",StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()));
		station_desc.Replace("&nbsp;",station_desc_text);
		return station_desc;
	}
	if (have_start) {
		station_number_look_up--;
	}
	if (station_number_look_up <= this->m_num_stations) {
		pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(station_number_look_up);
		if (pRallyItemInlist != NULL) {
			station_desc_text.Format("%d. %s",station_number_look_up, StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()));
			station_desc.Replace("&nbsp;",station_desc_text);
		}
//		else {
//			station_desc.Empty();
//		}
		return station_desc;
	}
	if (have_finish && (station_number_look_up == this->m_num_stations + 1)) {
		pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(FINISH_STATION);
		station_desc_text.Format("%s",StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()));
		station_desc.Replace("&nbsp;",station_desc_text);
		return station_desc;
	}
	have_honor = false;
	if (have_honor) {
		pRallyItemInlist = this->m_rallyList.FindRallyStationByStationNumber(HONOR_STATION);
		station_desc_text.Format("%s",StationMapper::GetAKCDescrptionFromAKCNumber(pRallyItemInlist->GetAKCNumber()));
		station_desc.Replace("&nbsp;",station_desc_text);
		return station_desc;
	}
	return station_desc;
}
