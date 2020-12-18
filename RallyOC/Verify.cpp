// Verify.cpp: implementation of the Verify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "Verify.h"
#include "CourseInfo.h"
#include "ErrorReportDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Verify::Verify()
{
	int i;
	for (i=0;i<77;i++)this->m_num_stations[i] = -1;
}

Verify::~Verify()
{

}
void Verify::VerifyCourse(CDogRunDoc *p_doc_to_verify, BOOL show_dialog, int type_of_course) {
	CourseInfo course_info;
	CString error_report;
	ErrorReportDlg error_dlg;
	int error;
	int akc_station_list[77][2] = {	
		{0,0},
		{ID_DRAW_START,0},//1
		{ID_DRAW_FINISH,0},//2
		{ID_DRAW_SITHALT,0},//3
		{ID_DRAW_SITHALTDOWN,0},//4
		{ID_DRAW_RT_TURN,0},//5
		{ID_DRAW_LT_TURN,0},//6
		{ID_DRAW_ABOUT_RT,0},//7
		{ID_DRAW_ABOUT_LT,0},//8
		{ID_DRAW_270_RT,0},//9
		{ID_DRAW_270_LT,0},//10
		{ID_DRAW_360_RT,0},//11
		{ID_DRAW_360_LT,0},//12
		{ID_DRAW_FINISH_RT_FORWARD,0},//13
		{ID_DRAW_FINISH_LEFT_FORWARD,0},//14
		{ID_DRAW_FINISH_RT_HALT,0},//15
		{ID_DRAW_FINISH_LT_HALT,0},//16
		{ID_DRAW_SLOW,0},//17
		{ID_DRAW_FAST,0},//18
		{ID_DRAW_NORMAL,0},//19
		{ID_DRAW_SIDE_RT,0},//20
		{ID_DRAW_SPIRAL_RIGHT,0},//21
		{ID_DRAW_SPIRAL_LEFT,0},//22
		{ID_DRAW_WEAVE_TWICE,0},//23
		{ID_DRAW_SERP_ONCE,0},//24
		{ID_DRAW_HALT_3_STEPS_FOR,0},//25
		{ID_DRAW_FRONT_3_STEPS_BACK,0},//26
		{ID_DRAW_MOVE_DOWN,0},//27
		{ID_DRAW_FAST_SIT,0},//28
		{ID_DRAW_ABOUT_TURN_LT,0},//29
		{ID_DRAW_HALTWALK,0},//30
		{ID_DRAW_DOWNWALK,0},//31
		{ID_DRAW_MOVINGSTAND,0},//32
		{ID_DRAW_U_FORWARD_LT,0},//33
		{ID_ABOUT_FORWARD_RT,0},//34
		{ID_DRAW_1STEP_HEEL_RT,0},//35
		{ID_DRAW_STANDWALK,0},//36
		{ID_DRAW_90_PIVOT_RT,0},//37
		{ID_DRAW_90_PIVOT_LT,0},//38
		{ID_DRAW_OFFSET_8,0},//39
		{ID_DRAW_SIDE_RIGHT,0},//40
		{ID_DRAW_HALT_FINISH_RT,0},//41
		{ID_DRAW_HALT_FINISH_LT,0},//42
		{ID_DRAW_180_PIVOT_RT,0},//43
		{ID_DRAW_180_PIVOT_LT,0},//44
		{ID_DRAW_DOWNSIT,0},//45
		{ID_HALT_LEAVE_RECALL,0},//46
		{ID_DOUBLE_RIGHT_UTURN,0},//47
		{ID_DOUBLE_LEFT_UTURN,0},//48
		{ID_DOUBLE_LEFT_ATURN,0},//49
		{ID_FRONT_REV_3_STEPS,0},//50
		{ID_LEAVE_ABOUT_RET,0},//51
		{ID_HALT_CIRCLE_FOR,0},//52
		{ID_DRAW_JUMP,0},//53
		{ID_DRAW_STANDSIT,0},//54
		{ID_DRAW_STANDDOWN,0},//55
		{ID_DRAW_MOVE_STAND_WALK,0},//56
		{ID_DRAW_SLOWFORWARDFROMSIT,0},//57
		{ID_LEAVE_ABT_REC_FIN_R,0},//58
		{ID_LEAVE_ABT_REC_FIN_L,0},//59
		{ID_R_U_LEFT_ABOUT,0},//60
		{ID_L_U_LEFT_ABOUT,0},//61
		{ID_L_ABOUT_RIGHT_U,0},//62
		{ID_L_ABOUT_LEFT_U,0},//63
		{ID__DRAW_CALLTOHEEL,0},//64
		{ID_WEAVES_FIGURE8,0},//65
		{ID_DRAW_STAND,0},//66
		{ID__STAND_LEAVE_DOWN,0},//67
		{ID__DRAW_DOWNWHILEHEELING,0},//68
		{ID__DRAW_MOVE_DOWN,0},//69
		{ID__DRAW_SITSTAY,0},//70
		{ID__DRAW_2_STEPS_FORWARD,0},//71
		{ID_DRAW_BACKUP_3,0},//72
		{ID_STAND_PIVOT_R_FOR,0},//73
		{ID_STAND_PIVOT_L_FOR,0},//74
		{ID_FRT_CIR_R_FIN_L,0},//75
		{ID_TR_L_HEEL_R_T_R,0},//76
	};

	this->FillOutStationList(&p_doc_to_verify->m_rallyList, akc_station_list);
	error_report.Empty();
	error_dlg.m_error_report = "Congratulations! You have no errors in your course Design.";
	error = this->FindStartFinish(akc_station_list);
	if (error == NEITHER) error_report = "Missing Start and Finish Stations\r\n";
	if (error == FINISH_ONLY) error_report = "Missing Start Station\r\n";
	if (error == START_ONLY) error_report = "Missing Finish Station\r\n";

// not needed?	this->CheckForSingleStations(akc_station_list, &error_report);
	this->ChangePaceBackToNormal(&error_report);
	this->CheckConsectiveJumpStations(&error_report);
	p_doc_to_verify->m_course_info->GetCourseInfo(&course_info);
	switch (course_info.m_class) {
	case NOVICE:
		this->CheckNoviceCourse(akc_station_list, &error_report);
		break;
	case ADVANCED:
		this->CheckAdvancedCourse(akc_station_list, &error_report);
		break;
	case EXCELLENT:
		this->CheckExcellentCourse(akc_station_list, &error_report);
		break;
	case MASTER:
		this->CheckMasterCourse(akc_station_list, &error_report);
		break;
	case TRAINING:
		this->CheckExcellentCourse(akc_station_list, &error_report);//doing this to gather station stats
		error_report = "This is a training course, everything is allowed!";
		break;
	}
	if (!error_report.IsEmpty()) error_dlg.m_error_report = error_report;
	CString temp_string = this->StationStatistics(akc_station_list);
	if (!temp_string.IsEmpty()) error_dlg.m_error_report += temp_string;
	error_dlg.m_course_info = this->CreateCourseHeader(p_doc_to_verify);
	if (show_dialog) error_dlg.DoModal();



}
CString Verify::CreateCourseHeader(CDogRunDoc *p_doc_to_verify) {
	CString course_header, rally_date, rally_class;
	CourseInfo course_info;
	p_doc_to_verify->m_course_info->GetCourseInfo(&course_info);

	course_header = course_info.m_competation;

	switch(course_info.m_class) {
	case NOVICE:
		rally_class = "Novice";
		break;
	case ADVANCED:
		rally_class = "Advanced";		
		break;
	case EXCELLENT:
		rally_class = "Excellent";		
		break;
	case TRAINING:
		rally_class = "Training";
	}	
	
	
	course_header += "- " + rally_class;
	course_header.TrimRight();
	course_header +=  "; " + course_info.m_judge;
	course_header.TrimRight();

	rally_date = course_info.m_date_compete.Format(_T("%A, %B %d, %Y"));

	course_header += "; " + rally_date;
	return course_header;
}
void Verify::FillOutStationList(CObList *rallyList, int station_list[77][2]) {
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	int akc_num, string_id, station_num;
	for( pos = rallyList->GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)rallyList->GetNext(pos);
		akc_num = pRallyItemInlist->GetAKCNumber();
		station_list[akc_num][1]++;
		string_id = pRallyItemInlist->GetStringNumber();
		station_num = pRallyItemInlist->GetStationNumber();
		this->m_num_stations[station_num] = string_id;
	}
	this->m_num_advanced = this->m_num_excellent = 
		this->m_num_novice = this->m_num_stationary = this->m_num_master = 0;
	int i;
	for (i = 3; i<=32; i++) {
		this->m_num_novice += station_list[i][1];
	}
	for (i = 33; i<=53; i++) {
		this->m_num_advanced += station_list[i][1];
	}
	for (i = 54; i<=65; i++) {
		this->m_num_excellent += station_list[i][1];
	}	
	for (i = 66; i<=76; i++) {
		this->m_num_master += station_list[i][1];
	}
}
void Verify::CheckNoviceCourse(int station_list[51][2], CString *error_report) {
	int i, j, station_count, find_slash, str_len;
	CString station_num_error, station_type_error, sel_station_desc, num_stationary_error, stat_exe_loc;
	CString station_number;
	station_count = 0;
	for (i = 3; i<=32; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 10) station_num_error = "You have less than the required 10 stations!\r\n";
	if (station_count > 15) station_num_error = "You have more than 15 stations!\r\n";
	
	*error_report += station_num_error;
	for (i = 33; i<=76; i++) {
		if (station_list[i][1] > 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			station_type_error += sel_station_desc + " not allowed in this class! Station Number(s):";
			for(j=0;j<77;j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d",j);
					station_type_error  += station_number + ", ";
				}
			}
			str_len = station_type_error.GetLength();
			station_type_error = station_type_error.Left(str_len-2);
			station_type_error += "\r\n";
		}
	}

	*error_report += station_type_error;
	if (this->GetStationaryCount(station_list, &stat_exe_loc) > 5) {
		num_stationary_error = "5 Maximum Stationary exercises allowed!  ";
		num_stationary_error += stat_exe_loc;
	}
	*error_report += num_stationary_error;

	return;
}
void Verify::CheckAdvancedCourse(int station_list[51][2], CString *error_report) {
	int i, j, station_count, find_slash, str_len;
	CString station_num_error, station_type_error, sel_station_desc, jump_error, num_stationary_error;
	CString stat_exe_loc;
	CString station_number;

	station_count = 0;
	for (i = 3; i<=53; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 12) station_num_error = "You have less than the required 12 stations!\r\n";
	if (station_count > 17) station_num_error = "You have more than 17 stations!\r\n";
	*error_report += station_num_error;
	if (this->m_num_advanced < 4) station_num_error = "You must have at least 4 Advanced level Stations!\r\n"; 
	*error_report += station_num_error;
	for (i = 54; i<=76; i++) {
		if (station_list[i][1] > 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			station_type_error += sel_station_desc + " not allowed in this class! Station Number(s):";
			for(j=0;j<77;j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d",j);
					station_type_error  += station_number + ", ";
				}
			}
			str_len = station_type_error.GetLength();
			station_type_error = station_type_error.Left(str_len-2);
			station_type_error += "\r\n";
		}
	}
	
	*error_report += station_type_error;
	if (station_list[53][1] < 1) 
	{
		jump_error = "You must have one jump for this class!\r\n";
		*error_report += jump_error;
	}
	if (station_list[53][1] > 1) 
	{
		jump_error = "You are only allowed one jump for this class!\r\n";
		*error_report += jump_error;
	}

	if (this->GetStationaryCount(station_list, &stat_exe_loc) > 10) {
		num_stationary_error = "10 Maximum Stationary exercises allowed! \r\n";
		num_stationary_error += stat_exe_loc;
	}
	if (this->GetStationaryCount(station_list, &stat_exe_loc) < 3) {
		num_stationary_error = "Must have at least 3 Stationary exercises! \r\n";
		num_stationary_error += stat_exe_loc;
	}
	*error_report += num_stationary_error;

	return;
}
void Verify::CheckExcellentCourse(int station_list[51][2], CString *error_report) {
	int i, station_count, find_slash, j, str_len;
	CString station_num_error, station_type_error, sel_station_desc, jump_error, num_stationary_error;
	CString stat_exe_loc, honor_station_error;
	CString station_number;
	
	station_count = 0;
	for (i = 3; i<65; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 15) station_num_error = "You have less than the required 15 stations!\r\n";
	if (station_count > 20) station_num_error = "You have more than 20 stations!\r\n";
	*error_report += station_num_error;
	for (i = 66; i<=76; i++) {
		if (station_list[i][1] > 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			station_type_error += sel_station_desc + " not allowed in this class! Station Number(s):";
			for(j=0;j<77;j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d",j);
					station_type_error  += station_number + ", ";
				}
			}
			str_len = station_type_error.GetLength();
			station_type_error = station_type_error.Left(str_len-2);
			station_type_error += "\r\n";
		}
	}
	*error_report += station_type_error;
	
	if (this->m_num_advanced < 6) 
	{
		station_num_error = "You must have at least 6 Advanced level stations!\r\n"; 
		*error_report += station_num_error;
	}
	if (this->m_num_excellent < 4) 
	{
		station_num_error = "You must have at least 4 Excellent level stations!\r\n"; 
		*error_report += station_num_error;
	}
	if (station_list[53][1] < 2) {
		jump_error = "You must have two jumps for this class!\r\n";
		*error_report += jump_error;
	}
	if (station_list[53][1] > 2) {
		jump_error = "You are only allowed two jumps for this class!\r\n";
		*error_report += jump_error;
	}
	
	if (this->GetStationaryCount(station_list, &stat_exe_loc) > 10) {
		num_stationary_error = "10 Maximum Stationary exercises allowed!";
		num_stationary_error += stat_exe_loc;
	}
	if (this->GetStationaryCount(station_list, &stat_exe_loc) < 3) {
		num_stationary_error = "Must have at least 3 Stationary exercises!";
		num_stationary_error += stat_exe_loc;
	}
	*error_report += num_stationary_error;	

	*error_report += honor_station_error;	
	return;
}

void Verify::CheckMasterCourse(int station_list[51][2], CString *error_report) {
	int i, station_count;
	CString station_num_error, station_type_error, sel_station_desc, jump_error, num_stationary_error;
	CString stat_exe_loc, honor_station_error;

	
	station_count = 0;
	for (i = 3; i<77; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 18) station_num_error = "You have less than the required 18 stations!\r\n";
	if (station_count > 24) station_num_error = "You have more than 24 stations!\r\n";

	*error_report += station_num_error;
/*
	if (this->m_num_advanced < 6) 
	{
		station_num_error = "You must have at least 6 Advanced level stations!\r\n"; 
		*error_report += station_num_error;
	}
*/
	if (this->m_num_excellent < 4) 
	{
		station_num_error = "You must have at least 4 Excellent level stations!\r\n"; 
		*error_report += station_num_error;
	}
	if (this->m_num_master  < 3) 
	{
		station_num_error = "You must have at least 3 Master level stations!\r\n"; 
		*error_report += station_num_error;
	}
	if (station_list[53][1] > 0) jump_error = "Master Class does not allow jumps!\r\n";
	*error_report += jump_error;
	
	if (this->GetStationaryCount(station_list, &stat_exe_loc) > 10) {
		num_stationary_error = "10 Maximum Stationary exercises allowed!\r\n";
		num_stationary_error += stat_exe_loc;
	}
	if (this->GetStationaryCount(station_list, &stat_exe_loc) < 3) {
		num_stationary_error = "Must have at least 3 Stationary exercises!\r\n";
		num_stationary_error += stat_exe_loc;
	}
	*error_report += num_stationary_error;	

	*error_report += honor_station_error;	
	return;
}
int Verify::FindStartFinish(int station_list[51][2]) {
	BOOL found_start, found_finish;
	found_start = found_finish = false;

	if (station_list[1][1] > 0) found_start = true;
	if (station_list[2][1] > 0) found_finish = true;
	if (found_start && found_finish) return BOTH;
	else if (found_start && !found_finish) return START_ONLY;
	else if (!found_start && found_finish) return FINISH_ONLY;
	else return NEITHER;
}
BOOL Verify::FindHonorStation(int station_list[51][2]) {
	if (station_list[50][1] > 0) return true;
	else return false;
}
void Verify::CheckForSingleStations(int station_list[77][2], CString *error_report) {
	CString single_station_error, sel_station_desc, station_number;	
	int i, j, find_slash, k;
	
	single_station_error.Empty();
	i = 1;
	while(i<77) {
		if (station_list[i][1] > 1) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			single_station_error += "Can Only Have 1 " + sel_station_desc + " Station Numbers: ";
			for (j = 0, k = 0; j < 77; j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d ",j);
					single_station_error += station_number;
					k++;
					if (k < station_list[i][1]) single_station_error += ", ";
				}
			}
		}
		if (i == 4) i = 10;
		if (i == 16) i = 19;
		if (i == 45) i = 46;
		i++;
	}
	if (!single_station_error.IsEmpty()) single_station_error += "\r\n";
	*error_report += single_station_error;

	return;
}

void Verify::ChangePaceBackToNormal(CString *error_report) {
	int i, find_slash;
	CString pace_error, sel_station_desc, station_number;

	for(i=0;i<77;i++) {
		if (this->m_num_stations[i] == ID_DRAW_FAST || this->m_num_stations[i] == ID_DRAW_SLOW 
			|| this->m_num_stations[i] == ID_DRAW_FAST_SIT) {
			if (!(this->m_num_stations[i+1] == ID_DRAW_NORMAL) && !(this->m_num_stations[i+1] == -1)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				pace_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Normal Pace\r\n";
			}

		}
	}
	*error_report += pace_error;
	
	return;
}
void Verify::CheckConsectiveJumpStations(CString *error_report) {
	int i, find_slash;
	CString jump_error, sel_station_desc, station_number;

	for(i=0;i<77;i++) {
		if (this->m_num_stations[i] == ID_DRAW_JUMP) {
			if (this->m_num_stations[i+1] == ID_DRAW_JUMP) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				jump_error += sel_station_desc + " (Station Number:"+ station_number + ") Can not be followed by another Jump\r\n";
			}

		}
	}
	*error_report += jump_error;
	
	return;
}
int Verify::GetStationaryCount(int station_list[77][2], CString *stat_exe_loc) {
	int num_stationary_stations;
	int i, str_len;
	CString station_number;
	
	*stat_exe_loc = "Station Numbers: ";
	num_stationary_stations = 0;
	if (station_list[3][1] > 0) {
		num_stationary_stations += station_list[3][1];
		for(i=0;i<77;i++) {
			if (station_list[3][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #3), ";
			}
		}
	}
	if (station_list[4][1] > 0) {
		num_stationary_stations += station_list[4][1];
		for(i=0;i<77;i++) {
			if (station_list[4][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #4), ";
			}
		}
	}
	if (station_list[13][1] > 0) {
		num_stationary_stations += station_list[13][1];
		for(i=0;i<77;i++) {
			if (station_list[13][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #13), ";
			}
		}
	}	
	if (station_list[14][1] > 0) {
		num_stationary_stations += station_list[14][1];
		for(i=0;i<77;i++) {
			if (station_list[14][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #14), ";
			}
		}
	}	
	
	if (station_list[15][1] > 0) {
		num_stationary_stations += station_list[15][1];
		for(i=0;i<77;i++) {
			if (station_list[15][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #15), ";
			}
		}
	}
	if (station_list[16][1] > 0) {
		num_stationary_stations += station_list[16][1];
		for(i=0;i<77;i++) {
			if (station_list[16][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #16), ";
			}
		}
	}
	if (station_list[25][1] > 0) {
		num_stationary_stations += station_list[25][1];
		for(i=0;i<77;i++) {
			if (station_list[25][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #25), ";
			}
		}
	}
	if (station_list[26][1] > 0) {
		num_stationary_stations += station_list[26][1];
		for(i=0;i<77;i++) {
			if (station_list[26][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #26), ";
			}
		}
	}
	if (station_list[27][1] > 0) {
		num_stationary_stations += station_list[27][1];
		for(i=0;i<77;i++) {
			if (station_list[27][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #27), ";
			}
		}
	}
	if (station_list[28][1] > 0) {
		num_stationary_stations += station_list[28][1];
		for(i=0;i<77;i++) {
			if (station_list[28][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #28), ";
			}
		}
	}
	if (station_list[30][1] > 0) {
		num_stationary_stations += station_list[30][1];
		for(i=0;i<77;i++) {
			if (station_list[30][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #30), ";
			}
		}
	}
	if (station_list[31][1] > 0) {
		num_stationary_stations += station_list[31][1];
		for(i=0;i<77;i++) {
			if (station_list[31][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #31), ";
			}
		}
	}
	if (station_list[32][1] > 0) {
		num_stationary_stations += station_list[32][1];
		for(i=0;i<77;i++) {
			if (station_list[32][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #32), ";
			}
		}
	}
	if (station_list[33][1] > 0) {
		num_stationary_stations += station_list[33][1];
		for(i=0;i<77;i++) {
			if (station_list[33][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #33), ";
			}
		}
	}
	if (station_list[34][1] > 0) {
		num_stationary_stations += station_list[34][1];
		for(i=0;i<77;i++) {
			if (station_list[34][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #34), ";
			}
		}
	}
	if (station_list[35][1] > 0) {
		num_stationary_stations += station_list[35][1];
		for(i=0;i<77;i++) {
			if (station_list[35][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #35), ";
			}
		}
	}
	if (station_list[36][1] > 0) {
		num_stationary_stations += station_list[36][1];
		for(i=0;i<77;i++) {
			if (station_list[36][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #36), ";
			}
		}
	}
	if (station_list[37][1] > 0) {
		num_stationary_stations += station_list[37][1];
		for(i=0;i<77;i++) {
			if (station_list[37][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #37), ";
			}
		}
	}
	if (station_list[38][1] > 0) {
		num_stationary_stations += station_list[38][1];
		for(i=0;i<77;i++) {
			if (station_list[38][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #38), ";
			}
		}
	}
	if (station_list[40][1] > 0) {
		num_stationary_stations += station_list[40][1];
		for(i=0;i<77;i++) {
			if (station_list[40][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #40), ";
			}
		}
	}
	
	if (station_list[41][1] > 0) {
		num_stationary_stations += station_list[41][1];
		for(i=0;i<77;i++) {
			if (station_list[40][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #41), ";
			}
		}
	}
	
	if (station_list[42][1] > 0) {
		num_stationary_stations += station_list[42][1];
		for(i=0;i<77;i++) {
			if (station_list[42][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #42), ";
			}
		}
	}
	if (station_list[43][1] > 0) {
		num_stationary_stations += station_list[43][1];
		for(i=0;i<77;i++) {
			if (station_list[43][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #43), ";
			}
		}
	}
	if (station_list[44][1] > 0) {
		num_stationary_stations += station_list[44][1];
		for(i=0;i<77;i++) {
			if (station_list[44][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #44), ";
			}
		}
	}
	if (station_list[45][1] > 0) {
		num_stationary_stations += station_list[45][1];
		for(i=0;i<77;i++) {
			if (station_list[45][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #45), ";
			}
		}
	}
	if (station_list[46][1] > 0) {
		num_stationary_stations += station_list[46][1];
		for(i=0;i<77;i++) {
			if (station_list[46][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #47), ";
			}
		}
	}
	if (station_list[51][1] > 0) {
		num_stationary_stations += station_list[51][1];
		for(i=0;i<77;i++) {
			if (station_list[51][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #48), ";
			}
		}
	}
	if (station_list[54][1] > 0) {
		num_stationary_stations += station_list[54][1];
		for(i=0;i<77;i++) {
			if (station_list[54][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #49), ";
			}
		}
	}
	if (station_list[55][1] > 0) {
		num_stationary_stations += station_list[55][1];
		for(i=0;i<77;i++) {
			if (station_list[55][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #50), ";
			}
		}
	}	
	if (station_list[56][1] > 0) {
		num_stationary_stations += station_list[56][1];
		for(i=0;i<77;i++) {
			if (station_list[56][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #56), ";
			}
		}
	}	
	
	if (station_list[57][1] > 0) {
		num_stationary_stations += station_list[57][1];
		for(i=0;i<77;i++) {
			if (station_list[57][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #57), ";
			}
		}
	}	
	if (station_list[58][1] > 0) {
		num_stationary_stations += station_list[58][1];
		for(i=0;i<77;i++) {
			if (station_list[58][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #58), ";
			}
		}
	}	
	if (station_list[59][1] > 0) {
		num_stationary_stations += station_list[59][1];
		for(i=0;i<77;i++) {
			if (station_list[59][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[66][1] > 0) {
		num_stationary_stations += station_list[66][1];
		for(i=0;i<77;i++) {
			if (station_list[66][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[67][1] > 0) {
		num_stationary_stations += station_list[67][1];
		for(i=0;i<77;i++) {
			if (station_list[67][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[68][1] > 0) {
		num_stationary_stations += station_list[68][1];
		for(i=0;i<77;i++) {
			if (station_list[68][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[69][1] > 0) {
		num_stationary_stations += station_list[69][1];
		for(i=0;i<77;i++) {
			if (station_list[69][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[70][1] > 0) {
		num_stationary_stations += station_list[70][1];
		for(i=0;i<77;i++) {
			if (station_list[70][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[71][1] > 0) {
		num_stationary_stations += station_list[71][1];
		for(i=0;i<77;i++) {
			if (station_list[71][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[73][1] > 0) {
		num_stationary_stations += station_list[73][1];
		for(i=0;i<77;i++) {
			if (station_list[73][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}	
	if (station_list[74][1] > 0) {
		num_stationary_stations += station_list[74][1];
		for(i=0;i<77;i++) {
			if (station_list[74][0] == this->m_num_stations[i]) {
				station_number.Format("%d",i);
				*stat_exe_loc  += station_number + "(AKC #59), ";
			}
		}
	}		
	if (!stat_exe_loc->IsEmpty()) {
		str_len = stat_exe_loc->GetLength();
		*stat_exe_loc = stat_exe_loc->Left(str_len-2);
		*stat_exe_loc += "\r\n";
		
	}
	this->m_num_stationary = num_stationary_stations;
	return num_stationary_stations;
}

CString Verify::StationStatistics(int station_list[51][2])
{
	CString station_stats, temp_string, sel_station_desc;
	int i, find_slash;
	station_stats = "\r\nCourse Statistics.\r\n";
	temp_string.Format("%d  Total Number of Stations\r\n",this->m_num_novice +
		this->m_num_advanced + this->m_num_excellent + m_num_master);
	station_stats += temp_string;
	temp_string.Format("%d  Novice Stations\r\n",this->m_num_novice);
	station_stats += temp_string;
	temp_string.Format("%d  Advanced Stations\r\n",this->m_num_advanced);
	station_stats += temp_string;
	temp_string.Format("%d  Excellent Stations\r\n",this->m_num_excellent);
	station_stats += temp_string;
	temp_string.Format("%d  Master Stations\r\n",this->m_num_master);
	station_stats += temp_string;
	temp_string.Format("%d  Stationary Stations\r\n",this->m_num_stationary);
	station_stats += temp_string;
	for (i=1;i<77;i++) {
		if (station_list[i][1]> 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);			
			temp_string.Format("%d  %s Station(s) (AKC # %d) \r\n",station_list[i][1], sel_station_desc, i);
			station_stats += temp_string;
		}
	}
	this->m_station_stats = station_stats;
	return station_stats;
}

CString Verify::GetStationStatistics()
{
	return this->m_station_stats;
}

void Verify::FillOutAPDTStationList(CObList *rallyList, int station_list[][2])
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	int apdt_num, string_id, station_num;
	for( pos = rallyList->GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)rallyList->GetNext(pos);
		apdt_num = pRallyItemInlist->GetAKCNumber();
		station_list[apdt_num][1]++;
		string_id = pRallyItemInlist->GetStringNumber();
		station_num = pRallyItemInlist->GetStationNumber();
		this->m_num_stations[station_num] = string_id;
	}
	this->m_num_advanced = this->m_num_excellent = this->m_num_novice = this->m_num_stationary = 0;
	int i;
	for (i = 3; i<=29; i++) {
		this->m_num_novice += station_list[i][1];
	}
	for (i = 30; i<=47; i++) {
		this->m_num_advanced += station_list[i][1];
	}
	for (i = 50; i<=60; i++) {
		this->m_num_excellent += station_list[i][1];
	}	
}

int Verify::FindAPDTStartFinish(int station_list[][2])
{
	BOOL found_start, found_finish;
	found_start = found_finish = false;

	if (station_list[48][1] > 0) found_start = true;
	if (station_list[49][1] > 0) found_finish = true;
	if (found_start && found_finish) return BOTH;
	else if (found_start && !found_finish) return START_ONLY;
	else if (!found_start && found_finish) return FINISH_ONLY;
	else return NEITHER;
}

void Verify::CheckForLinkedStations(CString *error_report)
{
	int i, find_slash;
	CString link_error, sel_station_desc, station_number;
	link_error.Empty();
	for(i=0;i<61;i++) {
		if (this->m_num_stations[i] == ID_DRAW_FAST || this->m_num_stations[i] == ID_DRAW_SLOW 
			|| this->m_num_stations[i] == ID_DRAW_FAST_SIT) {
			if (!(this->m_num_stations[i+1] == ID_DRAW_NORMAL) && !(this->m_num_stations[i+1] == -1)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Normal Pace\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_DRAW_STANDWALK) {
			if (!(this->m_num_stations[i+1] == ID_RETURN_STAND)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Return and Forward From Stand\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_RECALL_LEAVE) {
			if (!(this->m_num_stations[i+1] == ID_TURN_FRONT)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Turn and Call Front\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_TURN_FRONT) {
			if (!(this->m_num_stations[i+1] == ID_FINISH_RIGHT || this->m_num_stations[i+1] == ID_FINISH_LEFT)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Finish Left or Right\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_DRAW_FRONT_3_STEPS_BACK) {
			if (!(this->m_num_stations[i+1] == ID_FINISH_RIGHT || this->m_num_stations[i+1] == ID_FINISH_LEFT)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Finish Left or Right\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_MOVE_STAND_LEAVE) {
			if (!(this->m_num_stations[i+1] == ID_MOVE_STAND_LEAVE_TWO)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Turn and Call to Heel\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_MOVE_STAND_SIT_FINISH) {
			if (!(this->m_num_stations[i+1] == ID_MOVE_STAND_SIT_FINISH_TWO)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Turn, Down, Sit and Call Finish\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_JUMP_RECALL) {
			if (!(this->m_num_stations[i+1] == ID_JUMP_RECALL_TWO)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Turn, Call Over Jump, Finish or Forward\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_JUMP_LEAVE) {
			if (!(this->m_num_stations[i+1] == ID_JUMP_LEAVE_TWO)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Turn, Send Over Jump, Finish or Forward\r\n";
			}
		}
		if (this->m_num_stations[i] == ID_DOWN_RECALL) {
			if (!(this->m_num_stations[i+1] == ID_DOWN_RECALL_TWO)) {
				sel_station_desc.LoadString(this->m_num_stations[i]);
				find_slash = sel_station_desc.Find("\n");
				sel_station_desc = sel_station_desc.Left(find_slash);
				station_number.Format("%d ",i);
				link_error += sel_station_desc + " (Station Number:"+ station_number + ") Not Followed By Turn, Recall Down Recall, Finish or Forward\r\n";
			}
		}
	}
	*error_report += link_error;
	
}

void Verify::CheckLevelOneCourse(int station_list[][2], CString *error_report)
{
	int i, j, station_count, find_slash, str_len;
	CString station_num_error, station_type_error, sel_station_desc, num_stationary_error, stat_exe_loc;
	CString station_number;
	station_count = 0;
	for (i = 1; i<=29; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 18) station_num_error = "You have less than the required 18 stations!\r\n";
	if (station_count > 20) station_num_error = "You have more than 20 stations!\r\n";
	
	*error_report += station_num_error;
	for (i = 30; i<=47; i++) {
		if (station_list[i][1] > 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			station_type_error += sel_station_desc + " not allowed in this class! Station Number(s):";
			for(j=0;j<48;j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d",j);
					station_type_error  += station_number + ", ";
				}
			}
			str_len = station_type_error.GetLength();
			station_type_error = station_type_error.Left(str_len-2);
			station_type_error += "\r\n";
		}
	}
	for (i = 50; i<=60; i++) {
		if (station_list[i][1] > 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			station_type_error += sel_station_desc + " not allowed in this class! Station Number(s):";
			for(j=0;j<61;j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d",j);
					station_type_error  += station_number + ", ";
				}
			}
			str_len = station_type_error.GetLength();
			station_type_error = station_type_error.Left(str_len-2);
			station_type_error += "\r\n";
		}
	}
	*error_report += station_type_error;

	return;
}

void Verify::CheckLevelTwoCourse(int station_list[][2], CString *error_report)
{
	int i, j, station_count, find_slash, str_len;
	CString station_num_error, station_type_error, sel_station_desc, total_error, num_stationary_error;
	CString stat_exe_loc;
	CString station_number;
	int ind_stay_total = 0, obs_total= 0, about_turn_total=0, misc_total = 0; 

	station_count = 0;
	for (i = 1; i<=47; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 20) station_num_error = "You have less than the required 20 stations!\r\n";
	if (station_count > 22) station_num_error = "You have more than 22 stations!\r\n";
	
	*error_report += station_num_error;
	for (i = 50; i<=60; i++) {
		if (station_list[i][1] > 0) {
			int string_id = station_list[i][0];
			sel_station_desc.LoadString(station_list[i][0]);
			
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);
			station_type_error += sel_station_desc + " not allowed in this class! Station Number(s):";
			for(j=0;j<61;j++) {
				if (station_list[i][0] == this->m_num_stations[j]) {
					station_number.Format("%d",j);
					station_type_error  += station_number + ", ";
				}
			}
			str_len = station_type_error.GetLength();
			station_type_error = station_type_error.Left(str_len-2);
			station_type_error += "\r\n";
		}
	}
	
	*error_report += station_type_error;
	ind_stay_total = station_list[31][1] + station_list[33][1] + station_list[43][1];
	if (ind_stay_total < 1) {
		total_error = "You must have at least one independent stay exercise!\r\n";
		*error_report += total_error;
	}
	obs_total = station_list[29][1] + station_list[30][1] + station_list[25][1] + station_list[26][1] + station_list[42][1];
	if (obs_total < 1) {
		total_error = "You must have at least one obstacle orientated exercise!\r\n";
		*error_report += total_error;
	}
	about_turn_total = station_list[39][1] + station_list[40][1];
	if (about_turn_total < 1) {
		total_error = "You must have at least one level 2 about turns!\r\n";
		*error_report += total_error;
	}
	misc_total = station_list[37][1] + station_list[38][1] + station_list[39][1] + station_list[40][1] + station_list[47][1];
	if (misc_total < 1) {
		total_error = "You must have at least one station of the exercises from #37 - #40 or #47!\r\n";
		*error_report += total_error;
	}
	if (this->m_num_advanced < 7) {
		total_error = "You have less than the required 7 Level 2 exercises!\r\n";
		*error_report += total_error;
	}
	

	return;
}

void Verify::CheckLevelThreeCourse(int station_list[][2], CString *error_report)
{
	int i, station_count;
	CString station_num_error, station_type_error, sel_station_desc, total_error, num_stationary_error;
	CString stat_exe_loc;
	CString station_number;
	int jump_total = 0, recall_total= 0, move_stand_total=0, level_two_turn_total = 0, level_three_turn_total = 0; 

	station_count = 0;
	for (i = 1; i<=47; i++) {
		station_count += station_list[i][1];
	}
	for (i = 50; i<=59; i++) {
		station_count += station_list[i][1];
	}
	if (station_count < 20) station_num_error = "You have less than the required 20 stations!\r\n";
	if (station_count > 22) station_num_error = "You have more than 22 stations!\r\n";
	
	*error_report += station_num_error;

	jump_total = station_list[42][1] + station_list[54][1] + station_list[55][1];
	if (jump_total < 1) {
		total_error = "You must have at least one level 2 or 3 jump exercise!\r\n";
		*error_report += total_error;
	}
	recall_total = station_list[54][1] + station_list[55][1] + station_list[59][1];
	if (recall_total < 1) {
		total_error = "You must have at least one level 3 recall exercise!\r\n";
		*error_report += total_error;
	}
	move_stand_total = station_list[50][1] + station_list[51][1] + station_list[52][1];
	if (move_stand_total < 1) {
		total_error = "You must have at least one moving stand exercise!\r\n";
		*error_report += total_error;
	}
	level_two_turn_total = station_list[39][1] + station_list[40][1] + station_list[47][1];
	if (level_two_turn_total < 1) {
		total_error = "You must have at least one level two turn exercise!\r\n";
		*error_report += total_error;
	}
	level_three_turn_total = station_list[56][1] + station_list[57][1];
	if (level_three_turn_total < 1) {
		total_error = "You must have at least one level three turn exercise!\r\n";
		*error_report += total_error;
	}
	if (station_list[56][1] != 1) {
		total_error = "You must have the bonus exercise!\r\n";
		*error_report += total_error;
	}


	return;
}

CString Verify::APDTStationStatistics(int station_list[][2])
{
	CString station_stats, temp_string, sel_station_desc;
	int i, find_slash;
	station_stats = "\r\nCourse Statistics.\r\n";
	temp_string.Format("%d  Level 1 Stations\r\n",this->m_num_novice);
	station_stats += temp_string;
	temp_string.Format("%d  Level 2 Stations\r\n",this->m_num_advanced);
	station_stats += temp_string;
	temp_string.Format("%d  Levle 3 Stations\r\n",this->m_num_excellent);
	station_stats += temp_string;
	for (i=1;i<=60;i++) {
		if (station_list[i] [1]> 0) {
			sel_station_desc.LoadString(station_list[i][0]);
			find_slash = sel_station_desc.Find("\n");
			sel_station_desc = sel_station_desc.Left(find_slash);			
			temp_string.Format("%d  %s Station(s) (AKC # %d) \r\n",station_list[i][1], sel_station_desc, i);
			station_stats += temp_string;
		}
	}
	this->m_station_stats = station_stats;
	return station_stats;
}
