// RallyObjList.cpp: implementation of the RallyObjList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "RallyObjList.h"
#include "StationMapper.h"
#include <map>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RallyObjList::RallyObjList()
{
//	this->SetUpAKCBitmapMapper();
//	this->SetUpAKCStringMapper();
//	this->SetUpAKCDescrptionMapper();
	this->m_number_of_stations = 0;

//	this->SetUpAPDTBitmapMapper();
//	this->SetUpAPDTStationNames();
//	this->SetUpAPDTStringMapper();



}

RallyObjList::~RallyObjList()
{

}

void RallyObjList::DrawRallyObjects(CDC* pDC, int stat_num_loc, BOOL advanced_mode, int where_cones, BOOL rotating, BOOL printing)
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	int error_code = 0;
	BOOL show_error = false;
	this->SetDCtoRallyStationFont(pDC);
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->GetNext(pos);
		error_code = pRallyItemInlist->DrawSelectedStation(pDC, stat_num_loc, advanced_mode, where_cones, rotating, printing);
		if (!show_error && error_code) {
			show_error = true;
		}
	
	}
	this->ResetDCFonts(pDC);
	
}
bool RallyObjList::HaveSitStayStation()
{
	CRallyObject* pRallyItem;
	POSITION pos;
	pos = this->GetTailPosition();
	while ( pos != NULL)
	{
		pRallyItem = (CRallyObject*)this->GetPrev(pos);
		int string_num = pRallyItem->GetStringNumber();
		if (string_num == ID__DRAW_SITSTAY)
		{
			return true;
		}
	}

	return false;
}
CRallyObject * RallyObjList::FindRallyStationByStationNumber(int station_number)
{
	CRallyObject* pRallyItemInlist;
	POSITION pos;
	int error_code = 0;
	BOOL show_error = false;
	for( pos = this->GetHeadPosition(); pos != NULL; ) {
		pRallyItemInlist = (CRallyObject*)this->GetNext(pos);
		if (pRallyItemInlist->GetStationNumber() == station_number) {
			return pRallyItemInlist;
		}
			
	}
	
	return NULL;
}

void RallyObjList::CalculateEntryExitPoints(CRallyObject *first_station, CRallyObject *second_station, POINT *entry, POINT *exit)
{
	POINT first_point, second_point,first_left, second_left, first_right, second_right;
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
	else if ((second_point.y == first_point.y)  && (second_point.x == first_point.x)) {
			exit_point  = top_exit;
			entry_point = bottom_entry;
	}
	*entry = entry_point;
	*exit = exit_point;

}

int RallyObjList::BitMapFromMenuChoice(int menu_choice)
{
	return StationMapper::BitMapFromObjectID(menu_choice);

}
CString RallyObjList::GetAKCDescrption(int objectid)
{
	return StationMapper::GetAKCDescrptionFromObjectID(objectid);
}

CString RallyObjList::AKCNumberStringFromMenuChoice(int menu_choice)
{
	return StationMapper::AKCNumberStringFromObjectID(menu_choice);
}
void RallyObjList::SetUpAPDTBitmapMapper(void) {
	this->apdt_bitmap_map[0] = 0;
	this->apdt_bitmap_map[1] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[2] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[3] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[4] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[5] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[6] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[7] = IDB_RIGHT_TURN;
	this->apdt_bitmap_map[8] = IDB_LEFT_TURN;
	this->apdt_bitmap_map[9] = IDB_ABOUT_TURN;
	this->apdt_bitmap_map[10] = IDB_U_TURN;
	this->apdt_bitmap_map[11] = IDB_270_RT;
	this->apdt_bitmap_map[12] = IDB_270_LT;
	this->apdt_bitmap_map[13] = IDB_360_RT;
	this->apdt_bitmap_map[14] = IDB_360_LT;
	this->apdt_bitmap_map[15] = IDB_FRONT_RIGHT;
	this->apdt_bitmap_map[16] = IDB_FRONT_LEFT;
	this->apdt_bitmap_map[17] = IDB_FRONT_RIGHT;
	this->apdt_bitmap_map[18] = IDB_FRONT_LEFT;
	this->apdt_bitmap_map[19] = IDB_MOVE;
	this->apdt_bitmap_map[20] = IDB_MOVE;
	this->apdt_bitmap_map[21] = IDB_MOVE;
	this->apdt_bitmap_map[22] = IDB_SIDE_RT_APDT;
	this->apdt_bitmap_map[23] = IDB_90_PIVOT_RT;
	this->apdt_bitmap_map[24] = IDB_90_PIVOT_LT;
	this->apdt_bitmap_map[25] = IDB_SPIRAL_RIGHT;
	this->apdt_bitmap_map[26] = IDB_SPIRAL_LEFT;
	this->apdt_bitmap_map[27] = IDB_HALT_3_FOR_APDT;
	this->apdt_bitmap_map[28] = IDB_1STEP_HEEL_RT;
	this->apdt_bitmap_map[29] = IDB_FIG8_TWICE;
	this->apdt_bitmap_map[30] = IDB_OFFSET_FIG8;
	this->apdt_bitmap_map[31] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[32] = IDB_RETURN;
	this->apdt_bitmap_map[33] = IDB_LEAVE_DOWN;
	this->apdt_bitmap_map[34] = IDB_TURN_FRONT; 
	this->apdt_bitmap_map[35] = IDB_FRONT_RIGHT; 
	this->apdt_bitmap_map[36] = IDB_FRONT_LEFT;
	this->apdt_bitmap_map[37] = IDB_180_PIVOT_RT;
	this->apdt_bitmap_map[38] = IDB_180_PIVOT_LT;
	this->apdt_bitmap_map[39] = IDB_ABOUT_FORWARD_TURN_RT;
	this->apdt_bitmap_map[40] = IDB_U_FORWARD_LT;
	this->apdt_bitmap_map[41] = IDB_FRONT_3_BACK_APDT;
	this->apdt_bitmap_map[42] = IDB_JUMP;
	this->apdt_bitmap_map[43] = IDB_FRONT_RUNNING;
	this->apdt_bitmap_map[44] = IDB_MOVE;
	this->apdt_bitmap_map[45] = IDB_HALTFORWARD;
	this->apdt_bitmap_map[46] = IDB_SIDE_RIGHT;
	this->apdt_bitmap_map[47] = IDB_ABOUT_TURN_LT;
	this->apdt_bitmap_map[48] = IDB_START;
	this->apdt_bitmap_map[49] = IDB_FINISH;
	this->apdt_bitmap_map[50] = IDB_MOVE;
	this->apdt_bitmap_map[51] = IDB_MOVE; // TWO SIGNS
	this->apdt_bitmap_map[52] = IDB_MOVE; // TWO SIGNS
	this->apdt_bitmap_map[53] = IDB_BACK;
	this->apdt_bitmap_map[54] = IDB_JUMP_RECALL; // TWO SIGNS
	this->apdt_bitmap_map[55] = IDB_JUMP_LEAVE; // TWO SIGNS
	this->apdt_bitmap_map[56] = IDB_RIGHT_TURN;
	this->apdt_bitmap_map[57] = IDB_LEFT_TURN;
	this->apdt_bitmap_map[58] = IDB_FIG8_ONCE;
	this->apdt_bitmap_map[59] = IDB_LEAVE_DOWN; //TWO SIGINS!
	this->apdt_bitmap_map[60] = IDB_RETRIEVE_FINISH;
	this->apdt_bitmap_map[61] = IDB_TURN_HEEL; // GOES WITH APDT #51
	this->apdt_bitmap_map[62] = IDB_TURN_DOWN_SIT; 
	this->apdt_bitmap_map[63] = 0;
	this->apdt_bitmap_map[64] = IDB_JUMP_RECALL2; // TWO SIGNS
	this->apdt_bitmap_map[65] = IDB_JUMP_LEAVE2; // TWO SIGNS
	this->apdt_bitmap_map[66] = 0;
	this->apdt_bitmap_map[67] = 0;
	this->apdt_bitmap_map[68] = 0;
	this->apdt_bitmap_map[69] = IDB_LEAVE_DOWN2; 
	this->apdt_bitmap_map[70] = 0;
}

void RallyObjList::SetUpAPDTStationNames()
{
	this->apdt_station_names[0] = "";
	this->apdt_station_names[1] = "HALT-Sit";
	this->apdt_station_names[2] = "HALT-Sit-Stand";
	this->apdt_station_names[3] = "HALT-Sit-Down";
	this->apdt_station_names[4] = "HALT-Sit-Down-Sit";
	this->apdt_station_names[5] = "HALT-Sit-Walk Around";
	this->apdt_station_names[6] = "HALT-Sit-Down-Walk Around";
	this->apdt_station_names[7] = "Right Turn";
	this->apdt_station_names[8] = "Left Turn";
	this->apdt_station_names[9] = "About Turn-Right";
	this->apdt_station_names[10] = "About U Turn";
	this->apdt_station_names[11] = "270-Degree Right Turn";
	this->apdt_station_names[12] = "270-Degree Left Turn";
	this->apdt_station_names[13] = "360-Degree Right (Turn)";
	this->apdt_station_names[14] = "360-Degree Left (Turn)";
	this->apdt_station_names[15] = "Call Dog Front-Forward Right";
	this->apdt_station_names[16] = "Call Dog Front-Forward Left";
	this->apdt_station_names[17] = "Call Dog Front-Finish Right";
	this->apdt_station_names[18] = "Call Dog Front-Finish Left";
	this->apdt_station_names[19] = "Slow Pace";
	this->apdt_station_names[20] = "Fast Pace";
	this->apdt_station_names[21] = "Normal Pace";
	this->apdt_station_names[22] = "Moving Side Step Right";
	this->apdt_station_names[23] = "HALT-90 Degree Pivot Right-HALT";
	this->apdt_station_names[24] = "HALT-90 Degree Pivot Left-HALT";
	this->apdt_station_names[25] = "Spiral Right-Dog Outside";
	this->apdt_station_names[26] = "Spiral Left-Dog Inside";
	this->apdt_station_names[27] = "HALT-1, 2, 3 Steps Forward";
	this->apdt_station_names[28] = "HALT-Turn Right 1 Step-HALT";
	this->apdt_station_names[29] = "Straight Figure 8";
	this->apdt_station_names[30] = "Off-Set Figure 8";
	this->apdt_station_names[31] = "HALT-Stand-Exam-Leave";
	this->apdt_station_names[32] = "Return & Forward From Stand";
	this->apdt_station_names[33] = "HALT-Leave Dog-Recall";
	this->apdt_station_names[34] = "Turn & Call (Dog) Front";
	this->apdt_station_names[35] = "Finish Right";
	this->apdt_station_names[36] = "Finish Left";
	this->apdt_station_names[37] = "HALT-180 Degree Pivot Right-HALT";
	this->apdt_station_names[38] = "HALT-180-Degree Pivot Left-HALT";
	this->apdt_station_names[39] = "HALT-From Sit-About Turn Right & Forward";
	this->apdt_station_names[40] = "HALT-From Sit-About U Turn & Forward";
	this->apdt_station_names[41] = "Call (Dog) Front-1, 2, 3 Steps Backward";
	this->apdt_station_names[42] = "Send Over Jumps-Handler Runs By";
	this->apdt_station_names[43] = "HALT-Leave-Call (Dog) Front While Running";
	this->apdt_station_names[44] = "Moving Down & Forward";
	this->apdt_station_names[45] = "HALT-Fast Forward From Sit";
	this->apdt_station_names[46] = "HALT-Side Step Right-HALT";
	this->apdt_station_names[47] = "Left About Turn";
	this->apdt_station_names[48] = "START";
	this->apdt_station_names[49] = "FINISH";
	this->apdt_station_names[50] = "Moving Stand Walk Around";
	this->apdt_station_names[51] = "Moving Stand Leave Dog-Turn and Call to Heel";
	this->apdt_station_names[52] = "Moving Stand Leave Dog-Down, Sit, Call Front and Finish";
	this->apdt_station_names[53] = "Moving Backup";
	this->apdt_station_names[54] = "Recall over Jump";
	this->apdt_station_names[55] = "Halt, Leave Dog, Turn and Send Over Jump";
	this->apdt_station_names[56] = "Right Turn 1, 2 Steps Down, Forward";
	this->apdt_station_names[57] = "Left Turn 1, 2 Steps Down, Forward";
	this->apdt_station_names[58] = "Serpentine";
	this->apdt_station_names[59] = "Halt, Leave Dog, Down on Recall";
	this->apdt_station_names[60] = "Turn, Halt, Retrieve, Finish";
	this->apdt_station_names[61] = "Turn and Call to Heel";
	this->apdt_station_names[62] = "Turn, Down, Sit, Call Finish";
	this->apdt_station_names[63] = "";
	this->apdt_station_names[64] = "Turn Call over Jump, Finish or Forward";
	this->apdt_station_names[65] = "Turn Send over Jump, Finish or Forward";
	this->apdt_station_names[66] = "";
	this->apdt_station_names[67] = "";
	this->apdt_station_names[68] = "";
	this->apdt_station_names[69] = "Turn, Recall Down Recall, Finish or Forward";
}

void RallyObjList::SetUpAPDTStringMapper()
{
	this->apdt_string_map[0] = -1;
	this->apdt_string_map[1] = ID_DRAW_SITHALT;
	this->apdt_string_map[2] = ID_DRAW_SIT_STAND;
	this->apdt_string_map[3] = ID_DRAW_SITHALTDOWN;
	this->apdt_string_map[4] = ID_DRAW_DOWNSIT;
	this->apdt_string_map[5] = ID_DRAW_HALTWALK;
	this->apdt_string_map[6] = ID_DRAW_DOWNWALK;
	this->apdt_string_map[7] = ID_DRAW_RT_TURN;
	this->apdt_string_map[8] = ID_DRAW_LT_TURN;
	this->apdt_string_map[9] = ID_DRAW_ABOUT_RT;
	this->apdt_string_map[10] = ID_DRAW_ABOUT_LT;
	this->apdt_string_map[11] = ID_DRAW_270_RT;
	this->apdt_string_map[12] = ID_DRAW_270_LT;
	this->apdt_string_map[13] = ID_DRAW_360_RT;
	this->apdt_string_map[14] = ID_DRAW_360_LT;
	this->apdt_string_map[15] = ID_DRAW_FINISH_RT_FORWARD;
	this->apdt_string_map[16] = ID_DRAW_FINISH_LEFT_FORWARD;
	this->apdt_string_map[17] = ID_DRAW_HALT_FINISH_RT;
	this->apdt_string_map[18] = ID_DRAW_HALT_FINISH_LT;
	this->apdt_string_map[19] = ID_DRAW_SLOW;
	this->apdt_string_map[20] = ID_DRAW_FAST;
	this->apdt_string_map[21] = ID_DRAW_NORMAL;
	this->apdt_string_map[22] = ID_DRAW_SIDE_RT;
	this->apdt_string_map[23] = ID_DRAW_90_PIVOT_RT;
	this->apdt_string_map[24] = ID_DRAW_90_PIVOT_LT;
	this->apdt_string_map[25] = ID_DRAW_SPIRAL_RIGHT;
	this->apdt_string_map[26] = ID_DRAW_SPIRAL_LEFT;
	this->apdt_string_map[27] = ID_DRAW_HALT_3_STEPS_FOR;
	this->apdt_string_map[28] = ID_DRAW_1STEP_HEEL_RT;
	this->apdt_string_map[29] = ID_DRAW_WEAVE_TWICE;
	this->apdt_string_map[30] = ID_DRAW_OFFSET_8;
	this->apdt_string_map[31] = ID_DRAW_STANDWALK;
	this->apdt_string_map[32] = ID_RETURN_STAND;
	this->apdt_string_map[33] = ID_RECALL_LEAVE;
	this->apdt_string_map[34] = ID_TURN_FRONT;
	this->apdt_string_map[35] = ID_FINISH_RIGHT;
	this->apdt_string_map[36] = ID_FINISH_LEFT;
	this->apdt_string_map[37] = ID_DRAW_180_PIVOT_RT;
	this->apdt_string_map[38] = ID_DRAW_180_PIVOT_LT;
	this->apdt_string_map[39] = ID_ABOUT_FORWARD_RT;
	this->apdt_string_map[40] = ID_DRAW_U_FORWARD_LT;
	this->apdt_string_map[41] = ID_DRAW_FRONT_3_STEPS_BACK;
	this->apdt_string_map[42] = ID_DRAW_JUMP;
	this->apdt_string_map[43] = ID_FRONT_RUN;
	this->apdt_string_map[44] = ID_DRAW_MOVE_DOWN;
	this->apdt_string_map[45] = ID_DRAW_FAST_SIT;
	this->apdt_string_map[46] = ID_DRAW_SIDE_RIGHT;
	this->apdt_string_map[47] = ID_DRAW_ABOUT_TURN_LT;
	this->apdt_string_map[48] = ID_DRAW_START;
	this->apdt_string_map[49] = ID_DRAW_FINISH;
	this->apdt_string_map[50] = ID_DRAW_MOVE_STAND_WALK;
	this->apdt_string_map[51] = ID_MOVE_STAND_LEAVE;
	this->apdt_string_map[52] = ID_MOVE_STAND_SIT_FINISH;
	this->apdt_string_map[53] = ID_DRAW_BACKUP_3;
	this->apdt_string_map[54] = ID_JUMP_RECALL;
	this->apdt_string_map[55] = ID_JUMP_LEAVE;
	this->apdt_string_map[56] = ID_DRAW_RT_DOWN;
	this->apdt_string_map[57] = ID_DRAW_LT_DOWN;
	this->apdt_string_map[58] = ID_DRAW_SERP_ONCE;
	this->apdt_string_map[59] = ID_DOWN_RECALL;
	this->apdt_string_map[60] = ID_RETRIEVE_FINISH;
	this->apdt_string_map[61] = ID_MOVE_STAND_LEAVE_TWO;
	this->apdt_string_map[62] = ID_MOVE_STAND_SIT_FINISH_TWO;
	this->apdt_string_map[64] = ID_JUMP_RECALL_TWO;
	this->apdt_string_map[65] = ID_JUMP_LEAVE_TWO;
	this->apdt_string_map[69] = ID_DOWN_RECALL_TWO;

}
int RallyObjList::APDTNumberFromMenuChoice(int menu_choice)
{
	switch(menu_choice) {
	case ID_DRAW_SITHALT:
		return 1;
	case ID_DRAW_SIT_STAND:
		return 2;
	case ID_DRAW_SITHALTDOWN:
		return 3;
	case ID_DRAW_DOWNSIT:
		return 4;
	case ID_DRAW_HALTWALK:
		return 5;
	case ID_DRAW_DOWNWALK:
		return 6;
	case ID_DRAW_RT_TURN:
		return 7;
	case ID_DRAW_LT_TURN:
		return 8;
	case ID_DRAW_ABOUT_RT:
		return 9;
	case ID_DRAW_ABOUT_LT:
		return 10;
	case ID_DRAW_270_RT:
		return 11;
	case ID_DRAW_270_LT:
		return 12;
	case ID_DRAW_360_RT:
		return 13;
	case ID_DRAW_360_LT:
		return 14;
	case ID_DRAW_FINISH_RT_FORWARD:
		return 15;
	case ID_DRAW_FINISH_LEFT_FORWARD:
		return 16;
	case ID_DRAW_HALT_FINISH_RT: 
		return 17;
	case ID_DRAW_HALT_FINISH_LT:
		return 18;
	case ID_DRAW_SLOW:
		return 19;
	case ID_DRAW_FAST:
		return 20;
	case ID_DRAW_NORMAL:
		return 21;
	case ID_DRAW_SIDE_RT:
		return 22;
	case ID_DRAW_90_PIVOT_RT:
		return 23;
	case ID_DRAW_90_PIVOT_LT:
		return 24;
	case ID_DRAW_SPIRAL_RIGHT:
		return 25;
	case ID_DRAW_SPIRAL_LEFT:
		return 26;
	case ID_DRAW_HALT_3_STEPS_FOR:
		return 27;
	case ID_DRAW_1STEP_HEEL_RT:
		return 28;
	case ID_DRAW_WEAVE_TWICE:
		return 29;
	case ID_DRAW_OFFSET_8:
		return 30;
// note: The following two stations are linked!!!!
	case ID_DRAW_STANDWALK:
		return 31;
	case ID_RETURN_STAND: 
		return 32;
// note: The following FOUR stations are linked!!!!
	case ID_RECALL_LEAVE:
		return 33;
	case ID_TURN_FRONT:
		return 34;
// note: Now must have one of the next two!!!!
	case ID_FINISH_RIGHT:
		return 35;
	case ID_FINISH_LEFT:
		return 36;
	case ID_DRAW_180_PIVOT_RT:
		return 37;
	case ID_DRAW_180_PIVOT_LT:
		return 38;
	case ID_ABOUT_FORWARD_RT:
		return 39;
	case ID_DRAW_U_FORWARD_LT:
		return 40;
	case ID_DRAW_FRONT_3_STEPS_BACK:
		return 41;
	case ID_DRAW_JUMP:
		return 42;
	case ID_FRONT_RUN:
		return 43;
	case ID_DRAW_MOVE_DOWN:
		return 44;
	case ID_DRAW_FAST_SIT:
		return 45;
	case ID_DRAW_SIDE_RIGHT:
		return 46;		
	case ID_DRAW_ABOUT_TURN_LT:
		return 47;
	case ID_DRAW_START:
		return 48;
	case ID_DRAW_FINISH:
		return 49;
	case ID_DRAW_MOVE_STAND_WALK:
		return 50;
	case ID_MOVE_STAND_LEAVE:
		return 51; // THIS HAS TWO SIGNS!!
	case ID_MOVE_STAND_SIT_FINISH:
		return 52; // THIS HAS TWO SIGNS!!
	case ID_DRAW_BACKUP_3:
		return 53;
	case ID_JUMP_RECALL:
		return 54; // THIS HAS TWO SIGNS!!
	case ID_JUMP_LEAVE:
		return 55; // THIS HAS TWO SIGNS!!
	case ID_DRAW_RT_DOWN:
		return 56;
	case ID_DRAW_LT_DOWN:
		return 57;	
	case ID_DRAW_SERP_ONCE:
		return 58;
	case ID_DOWN_RECALL:
		return 59;	// THIS HAS TWO SIGNS!!
	case ID_RETRIEVE_FINISH:
		return 60;
	case ID_MOVE_STAND_LEAVE_TWO:
		return 61; // not a valid apdtnumber, goes with 51
	case ID_MOVE_STAND_SIT_FINISH_TWO:
		return 62; // not a valid apdtnumber- 52
	case ID_JUMP_RECALL_TWO:
		return 64; // not a valid apdtnumber - 54
	case ID_JUMP_LEAVE_TWO:
		return 65; // not a valid apdtnumber
	case ID_DOWN_RECALL_TWO:
		return 69; // not a valid apdtnumber

	}

	return 0;
}

CRallyObject* RallyObjList::CreateRallyStation(int menu_choice, int station_type, int x_pos, int y_pos)
{
	CRallyObject *p_rally_item;
	int akc_number /*, apdt_number*/;
	int bit_map_id;
	if (station_type == AKC_COURSE) {
		akc_number = atoi(this->AKCNumberStringFromMenuChoice(menu_choice));
		if (akc_number == 0) {
			p_rally_item = NULL;
		}
		else {
			bit_map_id = this->BitMapFromMenuChoice(menu_choice);
			p_rally_item = new CRallyObject(bit_map_id,menu_choice, station_type, akc_number, x_pos, y_pos);		
		}
	}
/*
	else {
		apdt_number = this->APDTNumberFromMenuChoice(menu_choice);
		if (apdt_number == 0) {
			p_rally_item = NULL;
		}
		else {
			p_rally_item = new CRallyObject(this->apdt_bitmap_map[apdt_number],menu_choice, station_type, apdt_number, x_pos, y_pos);		
		}			
	}
*/
	return p_rally_item;
}

void RallyObjList::ChangeStationType(CRallyObject* pStation_to_change, int new_station_number, int type_of_course)
{
	if (type_of_course == AKC_COURSE) {
		int object_id = StationMapper::ObjectIDFromAKCNumber(new_station_number);
		pStation_to_change->SetStationID(StationMapper::BitMapFromObjectID(object_id));
		pStation_to_change->SetStringNumber(object_id);
		pStation_to_change->SetAKCNumber(new_station_number);
	}
	else {
		pStation_to_change->SetStationID(this->apdt_bitmap_map[new_station_number]);
		pStation_to_change->SetStringNumber(this->apdt_string_map[new_station_number]);
		pStation_to_change->SetAKCNumber(new_station_number);
	}
}

int RallyObjList::CalculateLastNumberedStation()
{
	int last_number = 0;
	if (this->m_type_of_course == AKC_COURSE) {

	}
	else {
	}
	return last_number;
}

void RallyObjList::SetTypeOfCourse(int type_of_course)
{
	this->m_type_of_course = type_of_course;
}

int RallyObjList::GetTypeOfCourse()
{
	return this->m_type_of_course;
}

void RallyObjList::SetLastNumber(int last_number)
{
	this->m_number_of_stations = last_number;
}

int RallyObjList::GetLastNumber()
{
	return this->m_number_of_stations;
}

void RallyObjList::SetDCtoRallyStationFont(CDC *pDC)
{
	mp_org_font = pDC->SelectObject(&this->m_station_font);
	m_org_color = pDC->SetTextColor(this->m_station_color);
}

void RallyObjList::ResetDCFonts(CDC *pDC)
{
	mp_org_font = pDC->SelectObject(mp_org_font);
	m_org_color = pDC->SetTextColor(m_org_color);
}

void RallyObjList::CreateStationFont(MyFont *p_station_font, CDC *pDC)
{
	LOGFONT lf;
	p_station_font->GetLogFont(&lf);
	this->m_station_color = p_station_font->GetColorReference();
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(pDC->m_hDC, LOGPIXELSY)) / 72);
	if (!this->m_station_font.m_hObject) {
		VERIFY(this->m_station_font.CreateFontIndirect(&lf));
	}
}

void RallyObjList::ResetStationFont(MyFont *p_station_font, CDC *pDC)
{
	LOGFONT lf;
	p_station_font->GetLogFont(&lf);
	this->m_station_color = p_station_font->GetColorReference();
	this->m_station_font.DeleteObject();
	lf.lfHeight = -((lf.lfHeight * GetDeviceCaps(pDC->m_hDC, LOGPIXELSY)) / 72);
	VERIFY(this->m_station_font.CreateFontIndirect(&lf));
}
