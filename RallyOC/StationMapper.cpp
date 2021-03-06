#include "stdafx.h"
#include "StationMapper.h"
#include "DogRun.h"
#include "DogRunDoc.h"
#include <map>

StationMapper::StationMapper(void)
{
}

StationMapper::~StationMapper(void)
{
}

int StationMapper::ObjectIDFromAKCNumber(int akc_number){
	int object_id = -1;
	 std::map <int, int> akc_objectid_map;
	akc_objectid_map[1] = ID_DRAW_START;
	akc_objectid_map[2] = ID_DRAW_FINISH;
	akc_objectid_map[3] = ID_DRAW_SITHALT;
	akc_objectid_map[4] = ID_DRAW_SITHALTDOWN;
	akc_objectid_map[5] = ID_DRAW_RT_TURN;
	akc_objectid_map[6] = ID_DRAW_LT_TURN;
	akc_objectid_map[7] = ID_DRAW_ABOUT_RT;
	akc_objectid_map[8] = ID_DRAW_ABOUT_LT;
	akc_objectid_map[9] = ID_DRAW_270_RT;
	akc_objectid_map[10] = ID_DRAW_270_LT;
	akc_objectid_map[11] = ID_DRAW_360_RT;
	akc_objectid_map[12] = ID_DRAW_360_LT;
	akc_objectid_map[13] = ID_DRAW_FINISH_RT_FORWARD;
	akc_objectid_map[14] = ID_DRAW_FINISH_LEFT_FORWARD;
	akc_objectid_map[15] = ID_DRAW_FINISH_RT_HALT;
	akc_objectid_map[16] = ID_DRAW_FINISH_LT_HALT;
	akc_objectid_map[17] = ID_DRAW_SLOW;
	akc_objectid_map[18] = ID_DRAW_FAST;
	akc_objectid_map[19] = ID_DRAW_NORMAL;
	akc_objectid_map[20] = ID_DRAW_SIDE_RT;
	akc_objectid_map[21] = ID_DRAW_SPIRAL_RIGHT;
	akc_objectid_map[22] = ID_DRAW_SPIRAL_LEFT;
	akc_objectid_map[23] = ID_DRAW_WEAVE_TWICE;
	akc_objectid_map[24] = ID_DRAW_SERP_ONCE;
	akc_objectid_map[25] = ID_DRAW_HALT_3_STEPS_FOR;
	akc_objectid_map[26] = ID_DRAW_FRONT_3_STEPS_BACK;
	akc_objectid_map[27] = ID_DRAW_MOVE_DOWN;
	akc_objectid_map[28] = ID_DRAW_FAST_SIT;
	akc_objectid_map[29] = ID_DRAW_ABOUT_TURN_LT;
	akc_objectid_map[30] = ID_DRAW_HALTWALK;
	akc_objectid_map[31] = ID_DRAW_DOWNWALK; 
	akc_objectid_map[32] = ID_DRAW_MOVINGSTAND; 
	// end of novice
	akc_objectid_map[33] = ID_DRAW_U_FORWARD_LT; //
	akc_objectid_map[34] = ID_ABOUT_FORWARD_RT;
	akc_objectid_map[35] = ID_DRAW_1STEP_HEEL_RT;
	akc_objectid_map[36] = ID_DRAW_STANDWALK;
	akc_objectid_map[37] = ID_DRAW_90_PIVOT_RT;
	akc_objectid_map[38] = ID_DRAW_90_PIVOT_LT;
	akc_objectid_map[39] = ID_DRAW_OFFSET_8;
	akc_objectid_map[40] = ID_DRAW_SIDE_RIGHT;
	akc_objectid_map[41] = ID_DRAW_HALT_FINISH_RT;
	akc_objectid_map[42] = ID_DRAW_HALT_FINISH_LT;
	akc_objectid_map[43] = ID_DRAW_180_PIVOT_RT;
	akc_objectid_map[44] = ID_DRAW_180_PIVOT_LT;
	akc_objectid_map[45] = ID_DRAW_DOWNSIT;
//46-52
	akc_objectid_map[46] = ID_HALT_LEAVE_RECALL;
	akc_objectid_map[47] = ID_DOUBLE_RIGHT_UTURN;
	akc_objectid_map[48] = ID_DOUBLE_LEFT_UTURN;
	akc_objectid_map[49] = ID_DOUBLE_LEFT_ATURN;
	akc_objectid_map[50] = ID_FRONT_REV_3_STEPS;
	akc_objectid_map[51] = ID_LEAVE_ABOUT_RET;
	akc_objectid_map[52] = ID_HALT_CIRCLE_FOR;
	akc_objectid_map[53] = ID_DRAW_JUMP;//46
// end of advanced
	akc_objectid_map[54] = ID_DRAW_STANDSIT;//47
	akc_objectid_map[55] = ID_DRAW_STANDDOWN;//48
	akc_objectid_map[56] = ID_DRAW_MOVE_STAND_WALK;//49
	akc_objectid_map[57] = ID_DRAW_SLOWFORWARDFROMSIT;//50

	//58-63
	akc_objectid_map[58] = ID_LEAVE_ABT_REC_FIN_R; // new
	akc_objectid_map[59] = ID_LEAVE_ABT_REC_FIN_L; // new
	akc_objectid_map[60] = ID_R_U_LEFT_ABOUT; // new
	akc_objectid_map[61] = ID_L_U_LEFT_ABOUT; // new
	akc_objectid_map[62] = ID_L_ABOUT_RIGHT_U; // new
	akc_objectid_map[63] = ID_L_ABOUT_LEFT_U; // new

	akc_objectid_map[64] = ID__DRAW_CALLTOHEEL;//51
	akc_objectid_map[65] = ID_WEAVES_FIGURE8;//52
// end excellent
	akc_objectid_map[66] = ID_DRAW_STAND;//54
	akc_objectid_map[67] = ID__STAND_LEAVE_DOWN;//55
	akc_objectid_map[68] = ID__DRAW_DOWNWHILEHEELING;//56
	akc_objectid_map[69] = ID__DRAW_MOVE_DOWN;//57
	akc_objectid_map[70] = ID__DRAW_SITSTAY;//58
	akc_objectid_map[71] = ID__DRAW_2_STEPS_FORWARD;//59
	akc_objectid_map[72] = ID_DRAW_BACKUP_3;//53
	akc_objectid_map[73] = ID_STAND_PIVOT_R_FOR;//NEW
	akc_objectid_map[74] = ID_STAND_PIVOT_L_FOR;//NEW
	akc_objectid_map[75] = ID_FRT_CIR_R_FIN_L;//NEW
	akc_objectid_map[76] = ID_TR_L_HEEL_R_T_R;//NEW

	std::map<int,int>::iterator it;

	it = akc_objectid_map.find(akc_number);
	object_id = it->second;

	return object_id;
}
CString StationMapper::AKCNumberStringFromObjectID(int objectid) {
	 std::map <int, CString> akc_number_map;
	akc_number_map[ID_DRAW_START] = "1";
	akc_number_map[ID_DRAW_FINISH] = "2";
	akc_number_map[ID_DRAW_SITHALT] = "3";
	akc_number_map[ID_DRAW_SITHALTDOWN] = "4";
	akc_number_map[ID_DRAW_RT_TURN] = "5";
	akc_number_map[ID_DRAW_LT_TURN] = "6";
	akc_number_map[ID_DRAW_ABOUT_RT] = "7";
	akc_number_map[ID_DRAW_ABOUT_LT] = "8";
	akc_number_map[ID_DRAW_270_RT] = "9";
	akc_number_map[ID_DRAW_270_LT] = "10";
	akc_number_map[ID_DRAW_360_RT] = "11";
	akc_number_map[ID_DRAW_360_LT] = "12";
	akc_number_map[ID_DRAW_FINISH_RT_FORWARD] = "13";
	akc_number_map[ID_DRAW_FINISH_LEFT_FORWARD] = "14";
	akc_number_map[ID_DRAW_FINISH_RT_HALT] = "15";
	akc_number_map[ID_DRAW_FINISH_LT_HALT] = "16";
	akc_number_map[ID_DRAW_SLOW] = "17";
	akc_number_map[ID_DRAW_FAST] = "18";
	akc_number_map[ID_DRAW_NORMAL] = "19";
	akc_number_map[ID_DRAW_SIDE_RT] = "20";
	akc_number_map[ID_DRAW_SPIRAL_RIGHT] = "21";
	akc_number_map[ID_DRAW_SPIRAL_LEFT] = "22";
	akc_number_map[ID_DRAW_WEAVE_TWICE] = "23";
	akc_number_map[ID_DRAW_SERP_ONCE] = "24";
	akc_number_map[ID_DRAW_HALT_3_STEPS_FOR] = "25";
	akc_number_map[ID_DRAW_FRONT_3_STEPS_BACK] = "26";
	akc_number_map[ID_DRAW_MOVE_DOWN] = "27";
	akc_number_map[ID_DRAW_FAST_SIT] = "28";
	akc_number_map[ID_DRAW_ABOUT_TURN_LT] = "29";
	akc_number_map[ID_DRAW_HALTWALK] = "30";
	akc_number_map[ID_DRAW_DOWNWALK] = "31";
	akc_number_map[ID_DRAW_MOVINGSTAND] = "32"; // Moving Stand
// end of novice

	akc_number_map[ID_DRAW_U_FORWARD_LT] = "33";
	akc_number_map[ID_ABOUT_FORWARD_RT] = "34";
	akc_number_map[ID_DRAW_1STEP_HEEL_RT] = "35";
	akc_number_map[ID_DRAW_STANDWALK] = "36";
	akc_number_map[ID_DRAW_90_PIVOT_RT] = "37";
	akc_number_map[ID_DRAW_90_PIVOT_LT] = "38";
	akc_number_map[ID_DRAW_OFFSET_8] = "39";
	akc_number_map[ID_DRAW_SIDE_RIGHT] = "40";
	akc_number_map[ID_DRAW_HALT_FINISH_RT] = "41";
	akc_number_map[ID_DRAW_HALT_FINISH_LT] = "42";
	akc_number_map[ID_DRAW_180_PIVOT_RT] = "43";
	akc_number_map[ID_DRAW_180_PIVOT_LT] = "44";
	akc_number_map[ID_DRAW_DOWNSIT] = "45";
//46 to 52
	akc_number_map[ID_HALT_LEAVE_RECALL] = "46";
	akc_number_map[ID_DOUBLE_RIGHT_UTURN] = "47";
	akc_number_map[ID_DOUBLE_LEFT_UTURN] = "48";
	akc_number_map[ID_DOUBLE_LEFT_ATURN] = "49";
	akc_number_map[ID_FRONT_REV_3_STEPS] = "50";
	akc_number_map[ID_LEAVE_ABOUT_RET] = "51";
	akc_number_map[ID_HALT_CIRCLE_FOR] = "52";
	akc_number_map[ID_DRAW_JUMP] = "53";
	akc_number_map[ID_DRAW_STANDSIT] = "54";
	akc_number_map[ID_DRAW_STANDDOWN] = "55";
	akc_number_map[ID_DRAW_MOVE_STAND_WALK] = "56";
	akc_number_map[ID_DRAW_SLOWFORWARDFROMSIT] = "57";
//58-63
	akc_number_map[ID_LEAVE_ABT_REC_FIN_R] = "58";
	akc_number_map[ID_LEAVE_ABT_REC_FIN_L] = "59";
	akc_number_map[ID_R_U_LEFT_ABOUT] = "60";
	akc_number_map[ID_L_U_LEFT_ABOUT] = "61";
	akc_number_map[ID_L_ABOUT_RIGHT_U] = "62";
	akc_number_map[ID_L_ABOUT_LEFT_U] = "63";


	akc_number_map[ID__DRAW_CALLTOHEEL] = "64";
	akc_number_map[ID_WEAVES_FIGURE8] = "65";
	akc_number_map[ID_DRAW_STAND] = "66";
	akc_number_map[ID__STAND_LEAVE_DOWN] = "67";
	akc_number_map[ID__DRAW_DOWNWHILEHEELING] = "68";
	akc_number_map[ID__DRAW_MOVE_DOWN] = "69";
	akc_number_map[ID__DRAW_SITSTAY] = "70";
	akc_number_map[ID__DRAW_2_STEPS_FORWARD] = "71";
	akc_number_map[ID_DRAW_BACKUP_3] = "72";
	akc_number_map[ID_STAND_PIVOT_R_FOR] = "73";
	akc_number_map[ID_STAND_PIVOT_L_FOR] = "74";
	akc_number_map[ID_FRT_CIR_R_FIN_L] = "75";
	akc_number_map[ID_TR_L_HEEL_R_T_R] = "76";

	std::map<int,CString>::iterator it;

	it = akc_number_map.find(objectid);
	CString akc_number = it->second;
	return akc_number;
}
int StationMapper::GetAKCidFromComboBoxSelection(int choice) {
	int akc_number = -1;
	 std::map <int, int> combo_akc_map;
	combo_akc_map[0] = 1;
	combo_akc_map[1] = 2;
	combo_akc_map[2] = 3;
	combo_akc_map[3] = 4;
	combo_akc_map[4] = 5;
	combo_akc_map[5] = 6;
	combo_akc_map[6] = 7;
	combo_akc_map[7] = 8;
	combo_akc_map[8] = 9;
	combo_akc_map[9] = 10;
	combo_akc_map[10] = 11;
	combo_akc_map[11] = 12;
	combo_akc_map[12] = 13;
	combo_akc_map[13] = 14;
	combo_akc_map[14] = 15;
	combo_akc_map[15] = 16;
	combo_akc_map[16] = 17;
	combo_akc_map[17] = 18;
	combo_akc_map[18] = 19;
	combo_akc_map[19] = 20;
	combo_akc_map[20] = 21;
	combo_akc_map[21] = 22;
	combo_akc_map[22] = 23;
	combo_akc_map[23] = 24;
	combo_akc_map[24] = 25;
	combo_akc_map[25] = 26;
	combo_akc_map[26] = 27;
	combo_akc_map[27] = 28;
	combo_akc_map[28] = 29;
	combo_akc_map[29] = 30;
	combo_akc_map[30] = 31;
	combo_akc_map[31] = 32;
// end of novice

	combo_akc_map[32] = 33;
	combo_akc_map[33] = 34;
	combo_akc_map[34] = 35;
	combo_akc_map[35] = 36;
	combo_akc_map[36] = 37;
	combo_akc_map[37] = 38;
	combo_akc_map[38] = 39;
	combo_akc_map[39] = 40;
	combo_akc_map[40] = 41;
	combo_akc_map[41] = 42;
	combo_akc_map[42] = 43;
	combo_akc_map[43] = 44;
	combo_akc_map[44] = 45;
	combo_akc_map[45] = 46;
	combo_akc_map[46] = 47;
	combo_akc_map[47] = 48;
	combo_akc_map[48] = 49;
	combo_akc_map[49] = 50;
	combo_akc_map[50] = 51;
	combo_akc_map[51] = 52;
	combo_akc_map[52] = 53;
	// end of advanced
	combo_akc_map[53] = 54;
	combo_akc_map[54] = 55;
	combo_akc_map[55] = 56;
	combo_akc_map[56] = 57;
	combo_akc_map[57] = 58;
	combo_akc_map[58] = 59;
	combo_akc_map[59] = 60;
	combo_akc_map[60] = 61;
	combo_akc_map[61] = 62;
	combo_akc_map[62] = 63;
	combo_akc_map[63] = 64;
	combo_akc_map[64] = 65;
// end excellent
	combo_akc_map[65] = 66;
	combo_akc_map[66] = 67;
	combo_akc_map[67] = 68;
	combo_akc_map[68] = 69;
	combo_akc_map[69] = 70;
	combo_akc_map[70] = 71;
	combo_akc_map[71] = 72;
	combo_akc_map[72] = 73;
	combo_akc_map[73] = 74;
	combo_akc_map[74] = 75;
	combo_akc_map[75] = 76;

	std::map<int,int>::iterator it;

	it = combo_akc_map.find(choice);
	akc_number = it->second;
	return akc_number;
}
int StationMapper::GetComboBoxSelectionFromAKCid(int akc_number) {
	int combo_selection = -1;
	 std::map <int, int> akc_comboselect_map;
	akc_comboselect_map[1] = 1;
	akc_comboselect_map[2] = 2;
	akc_comboselect_map[3] = 3;
	akc_comboselect_map[4] = 4;
	akc_comboselect_map[5] = 5;
	akc_comboselect_map[6] = 6;
	akc_comboselect_map[7] = 7;
	akc_comboselect_map[8] = 8;
	akc_comboselect_map[9] = 9;
	akc_comboselect_map[10] = 10;
	akc_comboselect_map[11] = 11;
	akc_comboselect_map[12] = 12;
	akc_comboselect_map[13] = 13;
	akc_comboselect_map[14] = 14;
	akc_comboselect_map[15] = 15;
	akc_comboselect_map[16] = 16;
	akc_comboselect_map[17] = 17;
	akc_comboselect_map[18] = 18;
	akc_comboselect_map[19] = 19;
	akc_comboselect_map[20] = 20;
	akc_comboselect_map[21] = 21;
	akc_comboselect_map[22] = 22;
	akc_comboselect_map[23] = 23;
	akc_comboselect_map[24] = 24;
	akc_comboselect_map[25] = 25;
	akc_comboselect_map[26] = 26;
	akc_comboselect_map[27] = 27;
	akc_comboselect_map[28] = 28;
	akc_comboselect_map[29] = 29;
	akc_comboselect_map[30] = 30;
	akc_comboselect_map[31] = 31;
	akc_comboselect_map[32] = 32;
// end of novice
	akc_comboselect_map[33] = 33;
	akc_comboselect_map[34] = 34;
	akc_comboselect_map[35] = 35;
	akc_comboselect_map[36] = 36;

	akc_comboselect_map[37] = 37;
	akc_comboselect_map[38] = 38;
	akc_comboselect_map[39] = 39;
	akc_comboselect_map[40] = 40;
	akc_comboselect_map[41] = 41;
	akc_comboselect_map[42] = 42;
	akc_comboselect_map[43] = 43;
	akc_comboselect_map[44] = 44;
	akc_comboselect_map[45] = 45;
	akc_comboselect_map[46] = 46;
	akc_comboselect_map[47] = 47;
	akc_comboselect_map[48] = 48;
	akc_comboselect_map[49] = 49;
	akc_comboselect_map[50] = 50;
	akc_comboselect_map[51] = 51;
	akc_comboselect_map[52] = 52;
	akc_comboselect_map[53] = 53;
	akc_comboselect_map[54] = 54;
	akc_comboselect_map[55] = 55;
	akc_comboselect_map[56] = 56;
	akc_comboselect_map[57] = 57;
	akc_comboselect_map[58] = 58;
	akc_comboselect_map[59] = 59;
	akc_comboselect_map[60] = 60;
	akc_comboselect_map[61] = 61;
	akc_comboselect_map[62] = 62;
	akc_comboselect_map[63] = 63;
	akc_comboselect_map[64] = 64;
	akc_comboselect_map[65] = 65;
	akc_comboselect_map[66] = 66;
	akc_comboselect_map[67] = 67;
	akc_comboselect_map[68] = 68;
	akc_comboselect_map[69] = 69;
	akc_comboselect_map[70] = 70;
	akc_comboselect_map[71] = 71;
	akc_comboselect_map[72] = 72;
	akc_comboselect_map[73] = 73;
	akc_comboselect_map[74] = 74;
	akc_comboselect_map[75] = 75;
	akc_comboselect_map[76] = 76;
	std::map<int,int>::iterator it;

	it = akc_comboselect_map.find(akc_number);
	combo_selection = it->second;
	combo_selection--;
	return combo_selection;
}
int StationMapper::GetBitMapFromAKCNumber(int akc_number)
{
	int object_id = StationMapper::ObjectIDFromAKCNumber(akc_number);
	return StationMapper::BitMapFromObjectID(object_id);
}
int StationMapper::BitMapFromObjectID(int objectid) {

	 std::map <int, int> akc_bitmap_map;
	akc_bitmap_map[ID_DRAW_START] = IDB_START;
	akc_bitmap_map[ID_DRAW_FINISH] = IDB_FINISH;
	akc_bitmap_map[ID_DRAW_SITHALT] = IDB_FORWARD;
	akc_bitmap_map[ID_DRAW_SITHALTDOWN] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_RT_TURN] = IDB_RIGHT_TURN;
	akc_bitmap_map[ID_DRAW_LT_TURN] = IDB_LEFT_TURN;
	akc_bitmap_map[ID_DRAW_ABOUT_RT] = IDB_ABOUT_TURN;
	akc_bitmap_map[ID_DRAW_ABOUT_LT] = IDB_U_TURN;
	akc_bitmap_map[ID_DRAW_270_RT] = IDB_270_RT;
	akc_bitmap_map[ID_DRAW_270_LT] = IDB_270_LT;
	akc_bitmap_map[ID_DRAW_360_RT] = IDB_360_RT;
	akc_bitmap_map[ID_DRAW_360_LT] = IDB_360_LT;
	akc_bitmap_map[ID_DRAW_FINISH_RT_FORWARD] = IDB_FINISH_RT_FOR;
	akc_bitmap_map[ID_DRAW_FINISH_LEFT_FORWARD] = IDB_FINISH_LT_FOR;
	akc_bitmap_map[ID_DRAW_FINISH_RT_HALT] = IDB_FINISH_RT_HALT;
	akc_bitmap_map[ID_DRAW_FINISH_LT_HALT] = IDB_FINISH_LT_HALT;
	akc_bitmap_map[ID_DRAW_SLOW] = IDB_CHANGEPACE;
	akc_bitmap_map[ID_DRAW_FAST] = IDB_CHANGEPACE;
	akc_bitmap_map[ID_DRAW_NORMAL] = IDB_CHANGEPACE;
	akc_bitmap_map[ID_DRAW_SIDE_RT] = IDB_SIDE_RT;
	akc_bitmap_map[ID_DRAW_SPIRAL_RIGHT] = IDB_SPIRAL_RIGHT;
	akc_bitmap_map[ID_DRAW_SPIRAL_LEFT] = IDB_SPIRAL_LEFT;
	akc_bitmap_map[ID_DRAW_WEAVE_TWICE] = IDB_FIG8_TWICE;
	akc_bitmap_map[ID_DRAW_SERP_ONCE] = IDB_FIG8_ONCE;
	akc_bitmap_map[ID_DRAW_HALT_3_STEPS_FOR] = IDB_HALT_3_FOR;
	akc_bitmap_map[ID_DRAW_FRONT_3_STEPS_BACK] = IDB_FRONT_3_BACK;
	akc_bitmap_map[ID_DRAW_MOVE_DOWN] = IDB_MOVE;
	akc_bitmap_map[ID_DRAW_FAST_SIT] = IDB_FAST_SIT;
	akc_bitmap_map[ID_DRAW_ABOUT_TURN_LT] = IDB_ABOUT_TURN_LT;
	akc_bitmap_map[ID_DRAW_HALTWALK] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_DOWNWALK] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_MOVINGSTAND] = IDB_MOVE; // Moving - Stand
// end of novice

	akc_bitmap_map[ID_DRAW_U_FORWARD_LT] = IDB_U_FORWARD_LT;
	akc_bitmap_map[ID_ABOUT_FORWARD_RT] = IDB_ABOUT_FORWARD_TURN_RT;
	akc_bitmap_map[ID_DRAW_1STEP_HEEL_RT] = IDB_1STEP_HEEL_RT;
	akc_bitmap_map[ID_DRAW_STANDWALK] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_90_PIVOT_RT] = IDB_90_PIVOT_RT;
	akc_bitmap_map[ID_DRAW_90_PIVOT_LT] = IDB_90_PIVOT_LT;
	akc_bitmap_map[ID_DRAW_OFFSET_8] = IDB_OFFSET_FIG8;
	akc_bitmap_map[ID_DRAW_SIDE_RIGHT] = IDB_SIDE_RIGHT;
	akc_bitmap_map[ID_DRAW_HALT_FINISH_RT] = IDB_FINISH_RT;
	akc_bitmap_map[ID_DRAW_HALT_FINISH_LT] = IDB_FINISH_LT;
	akc_bitmap_map[ID_DRAW_180_PIVOT_RT] = IDB_180_PIVOT_RT;
	akc_bitmap_map[ID_DRAW_180_PIVOT_LT] = IDB_180_PIVOT_LT;
	akc_bitmap_map[ID_DRAW_DOWNSIT] = IDB_HALTFORWARD;

	akc_bitmap_map[ID_HALT_LEAVE_RECALL] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DOUBLE_RIGHT_UTURN] = IDB_DOUBLE_RGT_U;
	akc_bitmap_map[ID_DOUBLE_LEFT_UTURN] = IDB_DOUBLE_LFT_U;
	akc_bitmap_map[ID_DOUBLE_LEFT_ATURN] = IDB_DOUBLE_LFT_A;
	akc_bitmap_map[ID_FRONT_REV_3_STEPS] = IDB_FRO_REV_3;
	akc_bitmap_map[ID_LEAVE_ABOUT_RET] = IDB_LEAVE_ABOUT_RET;
	akc_bitmap_map[ID_HALT_CIRCLE_FOR] = IDB_HALT_CIRCLE_FORWARD;

	akc_bitmap_map[ID_DRAW_JUMP] = IDB_JUMP;
	akc_bitmap_map[ID_DRAW_STANDSIT] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_STANDDOWN] = IDB_HALTFORWARD;
//49
	akc_bitmap_map[ID_DRAW_MOVE_STAND_WALK] = IDB_MOVE;
	akc_bitmap_map[ID_DRAW_SLOWFORWARDFROMSIT] = IDB_HALTFORWARD;

	akc_bitmap_map[ID_LEAVE_ABT_REC_FIN_R] = IDB_LEAVE_ABT_REC_FIN_R;
	akc_bitmap_map[ID_LEAVE_ABT_REC_FIN_L] = IDB_LEAVE_ABT_REC_FIN_L;
	akc_bitmap_map[ID_R_U_LEFT_ABOUT] = IDB_RIGHT_U_LEFT_ABOUT;
	akc_bitmap_map[ID_L_U_LEFT_ABOUT] = IDB_LEFT_U_LEFT_ABOUT;
	akc_bitmap_map[ID_L_ABOUT_RIGHT_U] = IDB_LEFT_ABOUT_RIGHT_U;
	akc_bitmap_map[ID_L_ABOUT_LEFT_U] = IDB_LEFT_ABOUT_LEFT_U;


	akc_bitmap_map[ID__DRAW_CALLTOHEEL] = IDB_360_CIRCLE_HEEL;
	akc_bitmap_map[ID_WEAVES_FIGURE8] = IDB_FOUR_CONE_FIG8;
	akc_bitmap_map[ID_DRAW_BACKUP_3] = IDB_BACKUP;
	akc_bitmap_map[ID_DRAW_STAND] = IDB_HALTFORWARD;
	akc_bitmap_map[ID__STAND_LEAVE_DOWN] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_DOWNWHILEHEELING] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_MOVE_DOWN] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_SITSTAY] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_2_STEPS_FORWARD] = IDB_LEAVE_DOG_2_STEPS_HEEL;

	akc_bitmap_map[ID_STAND_PIVOT_R_FOR] =IDB_RIGHT_TURN ;
	akc_bitmap_map[ID_STAND_PIVOT_L_FOR] =IDB_LEFT_TURN ;
	akc_bitmap_map[ID_FRT_CIR_R_FIN_L] = IDB_FRONT_360_R_HEEL;
	akc_bitmap_map[ID_TR_L_HEEL_R_T_R] = IDB_180_L_HEEL_R_180;


	std::map<int,int>::iterator it;

	it = akc_bitmap_map.find(objectid);
	int bit_map_id = it->second;
	return bit_map_id;
}
CString StationMapper::GetAKCDescrptionFromAKCNumber(int akc_number)
{
	int object_id = StationMapper::ObjectIDFromAKCNumber(akc_number);
	return StationMapper::GetAKCDescrptionFromObjectID(object_id);
}
CString StationMapper::GetAKCDescrptionFromObjectID(int objectid) {
	 std::map <int, CString> akc_description_map;
	akc_description_map[ID_DRAW_START] = "START";
	akc_description_map[ID_DRAW_FINISH] = "FINISH";
	akc_description_map[ID_DRAW_SITHALT] = "Halt-Sit";
	akc_description_map[ID_DRAW_SITHALTDOWN] = "HALT-Down";
	akc_description_map[ID_DRAW_RT_TURN] = "Right Turn";
	akc_description_map[ID_DRAW_LT_TURN] = "Left Turn";
	akc_description_map[ID_DRAW_ABOUT_RT] = "About Turn Right";
	akc_description_map[ID_DRAW_ABOUT_LT] = "About U Turn";
	akc_description_map[ID_DRAW_270_RT] = "270 Right Turn";
	akc_description_map[ID_DRAW_270_LT] = "270 Left Turn";
	akc_description_map[ID_DRAW_360_RT] = "360 Right Turn";
	akc_description_map[ID_DRAW_360_LT] = "360 Left Turn";
	akc_description_map[ID_DRAW_FINISH_RT_FORWARD] = "Call Front-Finish Right-Forward";
	akc_description_map[ID_DRAW_FINISH_LEFT_FORWARD] = "Call Front-Finish Left-Forward";
	akc_description_map[ID_DRAW_FINISH_RT_HALT] = "Call Front-Finish Right-HALT";
	akc_description_map[ID_DRAW_FINISH_LT_HALT] = "Call Front-Finish Left-HALT";
	akc_description_map[ID_DRAW_SLOW] = "Slow Pace";
	akc_description_map[ID_DRAW_FAST] = "Fast Pace";
	akc_description_map[ID_DRAW_NORMAL] = "Normal Pace";
	akc_description_map[ID_DRAW_SIDE_RT] = "Moving Side Step Right";
	akc_description_map[ID_DRAW_SPIRAL_RIGHT] = "Spiral Right-Dog Outside";
	akc_description_map[ID_DRAW_SPIRAL_LEFT] = "Spiral Left-Dog Inside";
	akc_description_map[ID_DRAW_WEAVE_TWICE] = "Straight Figure 8 Weave Twice";
	akc_description_map[ID_DRAW_SERP_ONCE] = "Serpentine Weave Once";
	akc_description_map[ID_DRAW_HALT_3_STEPS_FOR] = "HALT-1,2,3 Steps Forward";
	akc_description_map[ID_DRAW_FRONT_3_STEPS_BACK] = "Call Front-1,2,3 Steps Backward";
	akc_description_map[ID_DRAW_MOVE_DOWN] = "Down";
	akc_description_map[ID_DRAW_FAST_SIT] = "HALT-Fast Forward From Sit";
	akc_description_map[ID_DRAW_ABOUT_TURN_LT] = "Left About Turn";
	akc_description_map[ID_DRAW_HALTWALK] = "HALT-Walk Around Dog";
	akc_description_map[ID_DRAW_DOWNWALK] = "HALT-Down-Walk Around Dog";
	akc_description_map[ID_DRAW_MOVINGSTAND] = "Stand"; // moving Stand
// end of novice
	akc_description_map[ID_DRAW_U_FORWARD_LT] = "HALT Abut U Turn Forward";
	akc_description_map[ID_ABOUT_FORWARD_RT] = "HALT-About Turn Right-Forward";
	akc_description_map[ID_DRAW_STANDWALK] = "HALT-Stand Dog- Walk Around";
	akc_description_map[ID_DRAW_1STEP_HEEL_RT] = "HALT-Turn Right One Step-Call to Heel-HALT";
	akc_description_map[ID_DRAW_90_PIVOT_RT] = "HALT-90 Pivot Right-Halt";
	akc_description_map[ID_DRAW_90_PIVOT_LT] = "HALT-90 Pivot Left-Halt";
	akc_description_map[ID_DRAW_OFFSET_8] = "Offset Figure 8";
	akc_description_map[ID_DRAW_SIDE_RIGHT] = "HALT-Side Step Right-HALT";
	akc_description_map[ID_DRAW_HALT_FINISH_RT] = "HALT-Call Dog Front-Finish Right";
	akc_description_map[ID_DRAW_HALT_FINISH_LT] = "HALT-Call Dog Front-Finish Left";
	akc_description_map[ID_DRAW_180_PIVOT_RT] = "HALT-180 Pivot Right-HALT";
	akc_description_map[ID_DRAW_180_PIVOT_LT] = "HALT-180 Pivot Left-HALT";
	akc_description_map[ID_DRAW_DOWNSIT] = "HALT-Down-Sit";

	akc_description_map[ID_HALT_LEAVE_RECALL] = "Halt – Leave Dog - Recall";
	akc_description_map[ID_DOUBLE_RIGHT_UTURN] = "Double Right U Turn";
	akc_description_map[ID_DOUBLE_LEFT_UTURN] = "Double Left U Turn";
	akc_description_map[ID_DOUBLE_LEFT_ATURN] = "Double Left About Turn";
	akc_description_map[ID_FRONT_REV_3_STEPS] = "Call front, Handler Reverses Three Steps - Finish";
	akc_description_map[ID_LEAVE_ABOUT_RET] = "Leave Dog - About Turn – Return to Dog";
	akc_description_map[ID_HALT_CIRCLE_FOR] = "Halt – Dog circles handler – Forward";


	akc_description_map[ID_DRAW_JUMP] = "Send Over Jump-Handler Passes By";
	akc_description_map[ID_DRAW_STANDSIT] = "HALT-Stand-Sit";
	akc_description_map[ID_DRAW_STANDDOWN] = "HALT-Stand-Down";
// 49
	akc_description_map[ID_DRAW_MOVE_STAND_WALK] = "Moving Stand-Walk Around Dog";
	akc_description_map[ID_DRAW_SLOWFORWARDFROMSIT] = "HALT-Leave Dog - Recall";

	akc_description_map[ID_LEAVE_ABT_REC_FIN_R] = "Leave Dog - About Turn – Recall Dog – Finish Right";
	akc_description_map[ID_LEAVE_ABT_REC_FIN_L] = "Leave Dog - About Turn – Recall Dog – Finish Left";
	akc_description_map[ID_R_U_LEFT_ABOUT] = "Right U Turn – Left About Turn";
	akc_description_map[ID_L_U_LEFT_ABOUT] = "Left U Turn – Left About Turn";
	akc_description_map[ID_L_ABOUT_RIGHT_U] = "Left About Turn – Right U Turn";
	akc_description_map[ID_L_ABOUT_LEFT_U] = "Left About Turn – Left U Turn";

	akc_description_map[ID__DRAW_CALLTOHEEL] = "Circle Spin at Heel";
	akc_description_map[ID_WEAVES_FIGURE8] = "Four Cone Figure 8";
	akc_description_map[ID_DRAW_BACKUP_3] = "Back Up 3 Steps";
	akc_description_map[ID_DRAW_STAND] = "HALT- Leave Dog-Down-Sit-Distance-Return";
	akc_description_map[ID__STAND_LEAVE_DOWN] = "Stand-Leave Dog-Down Dog-Sit-Distance-Return";
	akc_description_map[ID__DRAW_DOWNWHILEHEELING] = "Moving Stand-Leave Dog-Distance Down";
	akc_description_map[ID__DRAW_MOVE_DOWN] = "Moving Down-Walk Around Dog";
	akc_description_map[ID__DRAW_SITSTAY] = "Moving Sit - Walk Around Dog";
	akc_description_map[ID__DRAW_2_STEPS_FORWARD] = "Halt-Leave Dog-Call to Heel";

	akc_description_map[ID_STAND_PIVOT_R_FOR] = "Stand – Pivot Right – Forward";
	akc_description_map[ID_STAND_PIVOT_L_FOR] = "Stand – Pivot Left – Forward";
	akc_description_map[ID_FRT_CIR_R_FIN_L] = "Call Front – Circle Spin Right – Finish Left";
	akc_description_map[ID_TR_L_HEEL_R_T_R] = "180 Turn Left – Heel on Right – 180 Turn Right";

	std::map<int,CString>::iterator it;
//	it = NULL;
	it = akc_description_map.find(objectid);
	CString akc_descritpion = it->second;
	return akc_descritpion;
}
CString StationMapper::GetAKCDetailedDescrptionFromAKCNumber(int akc_number)
{
	int object_id = StationMapper::ObjectIDFromAKCNumber(akc_number);
	CString noLineBreaks = StationMapper::GetAKCDetailedDescrptionFromObjectID(object_id);
	int length = CString::StringLength(noLineBreaks);
	int x = length / 120;
	int insertAt = 120;

	for (int i = 1; i <= x; i++)
	{
		
		CString isblank = noLineBreaks.GetAt(insertAt);
		if (!isblank.Compare(" "))
		{
			noLineBreaks.Insert(insertAt,"\r\n");
		}
		else 
		{
			int nextSpace = noLineBreaks.Find(" ",insertAt);
			noLineBreaks.Insert(nextSpace,"\r\n");
		}
		insertAt += 120;
	}
	return noLineBreaks;
}
CString StationMapper::GetAKCDetailedDescrptionFromObjectID(int objectid) {
	 std::map <int, CString> akc_detailed_desc_map;
	akc_detailed_desc_map[ID_DRAW_START] =  "START-Indicates the beginning of the course - timing starts. Dog does not have to be sitting at start but must be under effective control.";
	akc_detailed_desc_map[ID_DRAW_FINISH] = "FINISH-Indicates the end of the course-timing stops.";
	akc_detailed_desc_map[ID_DRAW_SITHALT] = "Halt-Sit. Whilst heeling, the handler halts and the dog comes to a sit in heel position. The team then moves forward with the dog in heel position. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_SITHALTDOWN] = "HALT-Sit-Down. Whilst heeling, the handler halts and the dog comes to a sit. The handler then commands the dog to down, followed by the command to heel forward from the down position. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_RT_TURN] =  "Right Turn. Performed as a 90º turn to the right, as in traditional obedience. ";
	akc_detailed_desc_map[ID_DRAW_LT_TURN] =  "Left Turn. Performed as a 90º turn to the left, as in traditional obedience. ";
	akc_detailed_desc_map[ID_DRAW_ABOUT_RT] = "About Turn Right. Whilst heeling, the team makes a 180º about turn to the handler's right";
	akc_detailed_desc_map[ID_DRAW_ABOUT_LT] = "About U Turn. Whilst heeling, the team makes a 180º about turn to the handler's left";
	akc_detailed_desc_map[ID_DRAW_270_RT] = "270 Right Turn Whilst heeling, the team makes a 270º turn to the handler's right. 270° turns are performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_270_LT] = "270 Left Turn. Whilst heeling, the team makes a 270º turn to the handler's left. 270º turns are performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_360_RT] = "360 Right Turn. Whilst heeling, the team makes a 360º turn to the handler's right. 360º turns are performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_360_LT] = "360 Left Turn. Whilst heeling, the team makes a 360º turn to the handler's left. 360º turns are performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_FINISH_RT_FORWARD] = "Call Front-Finish Right-Forward. Whilst heeling, the handler stops forward motion and calls the dog to the front position (dog sits in front and faces the handler). The handler may take several steps backward as the dog turns and moves to sit in the front position. The second part of the exercise directs the handler to move forward while commanding the dog to change from the front position to the handler's right, around behind the handler and to heel position, as the handler continues forward. The dog does not sit before moving forward in heel position with the handler. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FINISH_LEFT_FORWARD] = "Call Front-Finish Left-Forward. Whilst heeling, the handler stops forward motion and calls the dog to the front position (dog sits in front and faces the handler). The handler may take several steps backward as the dog turns and moves to sit in the front position. The second part of the exercise directs the handler to move forward while commanding the dog to change from the front position to the handler's left and moving to heel position, as the handler continues forward. The dog does not sit before moving forward in heel position with the handler. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FINISH_RT_HALT] = "Call Front-Finish Right-Halt. Whilst heeling, the handler stops forward motion and calls the dog to the front position (dog sits in front and faces the handler). The handler may take several steps backward as the dog turns and moves to sit in the front position. The second part is the finish to the right, where the dog must return to heel position by moving around the right side of the handler. Dog must sit in heel position before moving forward with the handler. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FINISH_LT_HALT] = "Call Front-Finish Left-Halt. Whilst heeling, the handler stops forward motion and calls the dog to the front position (dog sits in front and faces the handler). The handler may take several steps backward as the dog turns and moves to a sit in the front position. The second part is the finish to the left, where the dog must move to the handler's left and sit in heel position. Dog must sit in heel position before moving forward in heel position with the handler. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_SLOW] = "Slow Pace. Dog and handler must slow down noticeably. This must be followed by a normal pace, unless it is the last station in the class.";
	akc_detailed_desc_map[ID_DRAW_FAST] = "Fast Pace. Dog and handler must speed up noticeably. This must be followed by a normal pace, unless it is the last station in the class.";
	akc_detailed_desc_map[ID_DRAW_NORMAL] = "Normal Pace. Dog and handler must move forward, walking briskly and naturally. ";
	akc_detailed_desc_map[ID_DRAW_SIDE_RT] = "Moving Side Step Right. Whilst heeling, the handler takes one step diagonally to the right and continues moving forward along the newly established line. The dog maintains heel position. The exercise may be performed just past the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_SPIRAL_RIGHT] = "Spiral Right-Dog Outside. This exercise requires three pylons or posts placed in a straight line with spaces between them of approximately 2.0 – 2.5 metres. Spiral Right indicates the handler must turn to the right when moving around each pylon or post. This places the dog on the outside of the turns. The exercise sign is placed near or on the first pylon or post where the spiral is started.";
	akc_detailed_desc_map[ID_DRAW_SPIRAL_LEFT] = "Spiral Left-Dog Inside. This exercise requires three pylons or posts placed in a straight line with spaces between them of approximately 2.0 – 2.5 metres. Spiral Left indicates that the handler must turn to the left when moving around each pylon or post. This places the dog on the inside of the turns. The exercise sign is placed near or on the first pylon or post where the spiral is started.";
	akc_detailed_desc_map[ID_DRAW_WEAVE_TWICE] = "Straight Figure 8 Weave Twice. This exercise requires four pylons or posts placed in a straight line with spaces between them of approximately 2.0 – 2.5 metres. The exercise sign is placed near or on the first obstacle where the exercise is started. Entry into the weaving pattern is with the first obstacle at the dog/handler's left side.";
	akc_detailed_desc_map[ID_DRAW_SERP_ONCE] = "Serpentine Weave Once. This exercise requires four obstacles (pylons, posts or people) placed in a straight line with spaces between them of approximately 2.0 – 2.5 metres. The exercise sign is placed near or on the first obstacle where the exercise is started. Entry into the weaving pattern is with the first obstacle at the dog/handler's left side. The dog and Handler must complete the entire exercise by passing the last pylon or post. It should be noted that in this exercise, the team does not weave back through the obstacles as they do in the Straight Figure 8.";
	akc_detailed_desc_map[ID_DRAW_HALT_3_STEPS_FOR] = "Halt-1,2,3 Steps Forward. The team halts with the dog sitting in heel position to begin the exercise. The handler takes one step forward, with the dog maintaining heel position, and halts. The dog sits when the handler halts. This is followed by two steps forward-halt, and three steps forward-halt, with the dog heeling each time the handler moves forward, and sitting each time the handler halts. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FRONT_3_STEPS_BACK] = "Call Front-1,2,3 Steps Backward. Whilst heeling, the handler stops forward motion and calls the dog to the front position (dog sits in front and faces the handler). The handler may take several steps backward as the dog turns and moves to a sit in the front position. With the dog in the front position, the handler takes one step backward and halts. The dog moves with the handler and sits in the front position as the handler halts. This is followed by the handler taking two steps backward and a halt, and three steps backward and a halt. Each time, the dog moves with the handler to the front position and sits as the handler halts. The handler then commands the dog to resume heel position as the team moves forward toward the next station. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_MOVE_DOWN] = "Down. Whilst moving with the dog in heel position, the handler commands and/or signals the dog to  down, as the handler comes to a stop next to the dog. Once the dog is completely down, the handler moves forward commanding the dog move forward from down position. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FAST_SIT] = "Halt-Fast Forward From Sit. With the dog sitting in heel position, the handler commands the dog to heel and immediately moves forward at a fast pace. This must be followed by a normal pace, unless it is the last station in the class. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_ABOUT_TURN_LT] = "Left About Turn. Whilst moving with the dog in heel position, the handler makes an about turn to the left, while at the same time, the dog must move around the handler to the right and to heel position. The dog does not sit before moving forward in heel position with the handler.";
	akc_detailed_desc_map[ID_DRAW_HALTWALK] = "Halt-Walk Around Dog. With the dog sitting in heel position, the handler commands the dog to stay, then proceeds to walk around the dog to the left, returning to heel position. The handler must pause in heel position before moving forward to the next station. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_DOWNWALK] = "Halt-Down-Walk Around Dog. With dog sitting in heel position, the handler commands the dog to down and to stay, then proceeds to walk around the dog to the left, returning to heel position. The handler must pause in heel position before moving forward to the next station. The dog heels forward from the down position. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_MOVINGSTAND] = "Moving-Stand. Whilst moving with the dog in heel position, the Handler commands and/or signals the dog to stand as the Handler comes to a stop next to the dog. Once the dog is completely paused in a stand, the Handler moves forward, commanding the dog to move forward from stand position. (Stationary exercise) ";
// end of novice
	akc_detailed_desc_map[ID_DRAW_U_FORWARD_LT] = "Halt-About U Turn-Forward. The Handler halts and dog sits. With the dog sitting in heel position, the team turns 180° to the left and immediately moves forward. (Stationary exercise)";
	akc_detailed_desc_map[ID_ABOUT_FORWARD_RT] = "Halt-About Turn Right-Forward. The Handler halts and dog sits. With the dog sitting in heel position, the team turns 180º to the right and immediately moves forward. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_1STEP_HEEL_RT] = "Halt-Turn Right One Step-Call to Heel-HALT. The Handler halts and dog sits. With the dog sitting in heel position, the handler commands the dog to wait or stay. The handler then turns to the right, while taking one step in that direction, and halts. The dog is called to sit in heel position in the new location before moving forward to the next station.(Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_STANDWALK] = "Halt-Stand-Walk Around Dog. The Handler halts and dog sits. With the dog sitting in heel position, the handler will stand the dog, command the dog to stay and walk around the dog to the left, returning to heel position. The handler must pause in heel position before moving forward to the next station. In the Advanced class, the handler may touch the dog, move forward to stand the dog, and may pose the dog as in the show ring. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_90_PIVOT_RT] = "Halt-90 Pivot Right-Halt. The Handler halts and dog sits. With the dog sitting in heel position, the team pivots 90º to the right, halts, the dog sits and then moves forward. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_90_PIVOT_LT] = "Halt-90 Pivot Left-Halt. The Handler halts and dog sits. With the dog sitting in heel position, the team pivots 90º to the left, halts, the dog sits and then moves forward. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_OFFSET_8] = "Offset Figure 8. This exercise requires two pylons, or posts placed about 2.45 – 3.00 metres apart, around which the team will perform a complete Figure 8. Two distractions will be arranged to the sides of the Figure 8 about 1.55 – 1.85 metres apart. Entry may be between the pylons, posts or people and the distraction on either side. The distractions will consist of two securely covered containers with tempting dog treats; however, dog toys may replace one or both containers, or may be placed next to the containers. Exercise sign may be placed on or near the cone where entry is made into the Offset Figure 8.";
	akc_detailed_desc_map[ID_DRAW_SIDE_RIGHT] = "Halt-Side Step Right-HALT. The Handler halts and dog sits. With the dog sitting in heel position, the team moves one step directly to the right and halts. The dog moves with the handler and sits in heel position when the handler halts. The exercise may be performed just past the exercise sign. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_HALT_FINISH_RT] = "Halt-Call Dog Front-Finish Right. The Handler halts and dog sits. With the dog sitting in heel position, the handler calls the dog to front, and the dog sits in the front position facing the handler. On command, the dog then moves from the front position around the right of the handler and sits in heel position. Handler may not step forward or backward to aid dog during exercise. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_HALT_FINISH_LT] = "Halt-Call Dog Front-Finish Left. The Handler halts and dog sits. With the dog sitting in heel position, the handler calls the dog to front, and the dog sits in the front position facing the handler. On command, the dog then moves from the front position to the handler's left and sits in heel position. Handler may not step forward or backward to aid dog during exercise. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_180_PIVOT_RT] = "Halt-180 Pivot Right-HALT. The Handler halts and dog sits. With the dog sitting in heel position, the handler pivots 180º to the right. The dog moves with the handler and sits in heel position. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_180_PIVOT_LT] = "Halt-180 Pivot Left-HALT. The Handler halts and dog sits. With the dog sitting in heel position, the handler pivots 180º to the left. The dog moves with the handler and sits in heel position. Handler then commands and/or signals the dog to heel (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_DOWNSIT] = "Halt-Down-Sit. The Handler halts and dog sits. With dog sitting in heel position, the handler commands/or signals the dog to down, then to sit. The Handler does notphysically handle the dog or move forward or backward. The forward from the sitting position. (Stationary exercise)";

	akc_detailed_desc_map[ID_HALT_LEAVE_RECALL] = "Halt – Leave Dog - Recall - The Handler commands and/or signals the dog to sit and stay, then moves forward 3 metres to the marker, performs an about turn, halts and commands and/or signals the dog to come. The dog shall sit in front of the Handler. The Handler shall return to the right side of the dog by either a step back to the side or around the dog. The Handler must become stationary in heel position before moving forward to the next station. (Stationary exercise).";
	akc_detailed_desc_map[ID_DOUBLE_RIGHT_UTURN] = "Double Right U Turn - Whilst moving forward and without pausing, the Handler and dog will complete a right U turn, heel approximately two (2) metres and then, repeat the right U turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_DOUBLE_LEFT_UTURN] = "Double Left U Turn - Whilst moving forward and without pausing, the Handler and dog perform a left U turn, heel approximately two (2) metres and then, repeat the left U turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_DOUBLE_LEFT_ATURN] = "Double Left About Turn – Whilst moving forward and without pausing, the Handler and dog will complete a left about turn, heel approximately two (2) meters and then repeat the left about turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_FRONT_REV_3_STEPS] = "Call front, Handler Reverses Three Steps - Finish The Handler calls the dog to the front, reverses three steps, with the dog moving with Handler. The dog returns to heel and continues heeling forward without stopping. The dog does not sit during this exercise. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_LEAVE_ABOUT_RET] = "Leave Dog - About Turn – Return to Dog - The Handler halts and dog sits. The Handler leaves dog and walks forward 5 meters to the marker. The Handler performs an about turn then, facing the dog and without pausing, walks back toward dog. The Handler will return around the back of the dog to heel position. The Handler must become stationary and then command/cue the dog to move forward from the sit position. The dog must not move from the sit position and must not change position. (Stationary exercise)";
	akc_detailed_desc_map[ID_HALT_CIRCLE_FOR] = "Halt – Dog circles handler – Forward - The Handler halts and, without the dog pausing or sitting, sends the dog in a circle to the right so that the dog moves around the back of the Handler and returns to the heel position. The Handler then moves forward to the next station. The dog does not pause or sit before it is sent around the Handler or when returning to the heel position.";
	akc_detailed_desc_map[ID_DRAW_JUMP] = "Send Over Jump-Handler Passes By. Whilst moving with the dog in heel position, the handler directs the dog to take the jump, as the handler passes by the jump without any pause, hesitation or stopping. When the dog has completed the jump, it is called to heel position and the team continues to the next exercise. ";
// end of advanced
	akc_detailed_desc_map[ID_DRAW_STANDSIT] = "Halt-Stand-Sit. The Handler halts and dog sits. With dog sitting in heel position, the handler will stand the dog (without physical handling or moving forward), then command and/or signal the dog to sit. The Handler then commands and/or signals the dog to heel forward from the sitting position.(Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_STANDDOWN] = "Halt-Stand-Down. The Handler halts and dog sits. With dog sitting in heel position, the handler will stand the dog (without physical handling or moving forward), then command and/or signal the dog to down. The Handler then commands and/or signals the dog to heel forward from the down position. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_MOVE_STAND_WALK] = "Moving Stand-Walk Around Dog. While heeling and with no hesitation, the handler will stand the dog, leave and walk around the dog to the left, returning to heel position. The handler must pause in heel position after returning to the dog. Dog must move forward from the standing position.";
	akc_detailed_desc_map[ID_DRAW_SLOWFORWARDFROMSIT] = "Halt-Leave Dog - Recall. The Handler commands and/or signals the dog to sit and stay, then leaves the dog approximately 5 metres, performs an about turn, halts and commands and/or signals the dog to come. The dog shall sit in front of the Handler. The Handler shall return to the right side of the dog by either a step back to the side or around the dog. Handler must pause upon returning to the dog. (Stationary exercise)";

	akc_detailed_desc_map[ID_LEAVE_ABT_REC_FIN_R] = "Leave Dog - About Turn – Recall Dog – Finish Right. The Handler halts and dog sits. Handler leaves dog and walks forward 5 meters to the marker and does an about turn to face dog. Handler recalls dog. Dog comes briskly to sit in front of handler. The dog must return to heel position by moving around the right side of the Handler. Dog must sit in heel position before moving forward with the Handler. The dog must not anticipate the recall. (Stationary exercise)";
	akc_detailed_desc_map[ID_LEAVE_ABT_REC_FIN_L] = "Leave Dog - About Turn – Recall Dog – Finish Left. The Handler halts and dog sits. Handler leaves dog and walks forward 5 meters to the marker and does an about turn to face dog. Handler recalls dog. Dog comes briskly to sit in front of handler. The dog must return to heel position by moving around the left side of the Handler. Dog must sit in heel position before moving forward with the Handler. The dog must not anticipate the recall. (Stationary exercise)";
	akc_detailed_desc_map[ID_R_U_LEFT_ABOUT] = "Right U Turn – Left About Turn. Whilst moving forward and without pausing, the Handler and dog will complete a right U turn, travel approximately two (2) meters and then complete a left about turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_L_U_LEFT_ABOUT] = "Left U Turn – Left About Turn. Whilst moving forward and without pausing, the Handler and dog will complete a left U turn, travel approximately two (2) meters and then complete a left about turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_L_ABOUT_RIGHT_U] = "Left About Turn – Right U Turn. Whilst moving forward and without pausing, the Handler and dog will complete a left about turn, travel approximately two (2) meters and then complete a right U turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";
	akc_detailed_desc_map[ID_L_ABOUT_LEFT_U] = "Left About Turn – Left U Turn. Whilst moving forward and without pausing, the Handler and dog will complete a left about turn, travel approximately two (2) meters and then complete a left U turn and continue forward. The team must maintain continuous motion throughout the turn without partially sitting or stopping.";

	akc_detailed_desc_map[ID__DRAW_CALLTOHEEL] = "Circle Spin at Heel -The dog to complete a circle spin away from the heel position and then to return to heel. The Handler does not stop moving.";
	akc_detailed_desc_map[ID_WEAVES_FIGURE8] = "Four Cone Figure 8 -This exercise requires four cones to be placed in a square, each 1.5 metres from the centre point. The team must negotiate each opposite pair of cones as a Figure 8. The exercise sign shall be placed at the cone at which the team will negotiate the first Figure 8. (May be used as a change of direction).";
// end of excellent
	akc_detailed_desc_map[ID_DRAW_BACKUP_3] = "Back Up 3 Steps-Dog Stays in Position. Whilst heeling,, the handler reverses direction walking backward 3 steps, without first stopping,, then continues heeling forward. The dog moves backward parallel to the handler and maintains heel position throughout the exercise without sitting or turning its body to face the Handler.";
	akc_detailed_desc_map[ID_DRAW_STAND] = "Halt – Leave Dog – Down – Sit - Distance Commands - Return – The Handler halts and the dog sits. The handler leaves the dog and walks forward at least 3 metres, performs an about turn and halts. The Handler commands and/or signals the dog to down. Once the dog is in down position, the Handler commands and/or signals the dog to sit. Once the dog is in sit position, the Handler returns around back of dog into heel position. The Handler must pause in heel position before moving forward to the next station. (Stationary Exercise).";
	akc_detailed_desc_map[ID__STAND_LEAVE_DOWN] = "Stand – Leave Dog – Down - Sit - Distance Commands – Return - Whilst moving with the dog in heel position, the Handler commands and/or signals the dog to stand as the Handler comes to a stop next to the dog. With the dog in a stand, the Handler leaves the dog and walks forward 3 metres, performs an about turn and halts. The Handler then commands and/or signals the dog to down. Once the dog is in down position, the Handler commands and/or signals the dog to sit. Once dog is in sit position, the Handler returns around the back of dog into heel position. Handler must pause in heel position before moving forward to the next station. (Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_DOWNWHILEHEELING] = "Moving Stand – Leave Dog - Distance Down – Whilst heeling and without pausing, the Handler commands and/or signals the dog to stand and leaves the dog to a distance at least 3 metres, turns, halts, commands and/or signals the dog to drop, then returns around the dog and, without pausing, continues on.(Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_MOVE_DOWN] = "Moving Down - Walk Around Dog - Whilst heeling and without pausing, the Handler will down the dog and walk around the dog to the left, returning to heel position. The Handler must pause in heel position after returning to the dog. The dog must move forward from the down position with the Handler at completion. (Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_SITSTAY] = "Moving Sit – Walk Around Dog - Whilst heeling and without pausing, the Handler will sit the dog and walk around the dog to the left, returning to heel position. The Handler must pause in heel position after returning to the dog. The dog must move forward from the sit position with the Handler at completion. (Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_2_STEPS_FORWARD] = "Halt – Leave Dog - Call To Heel – The Handler halts and the dog sits. The Handler leaves the dog and walks forward at least 3 metres and without pausing, calls the dog to heel. The dog is expected to catch up into heel position as the Handler moves forward and before the Handler reaches the next station. The dog must not anticipate the recall and must not forge significantly ahead of the Handler when coming into heel position.(Stationary exercise)";
	akc_detailed_desc_map[ID_STAND_PIVOT_R_FOR] = "Stand – Pivot Right – Forward – The Handler commands and/or signals the dog to Stand as Handler comes to a halt. With the dog standing, the Handler pivots 90º to the right and the dog moves with the Handler. The dog does not sit. The Handler must become stationary before the team heels forward. The Handler is required to pivot by turning in place. (Stationary exercise)";
	akc_detailed_desc_map[ID_STAND_PIVOT_L_FOR] = "Stand – Pivot Left – Forward – The Handler commands and/or signals the dog to Stand as Handler comes to a halt. With the dog standing, the Handler pivots 90º to the left and the dog moves with the Handler. The dog does not sit. The Handler must become stationary before the team heels forward. The Handler is required to pivot by turning in place. (Stationary exercise)";
	akc_detailed_desc_map[ID_FRT_CIR_R_FIN_L] = "Call Front – Circle Spin Right – Finish Left – The Handler calls dog to the front, the dog completes right 360 spin in front (Handler continues to move backward until dog has completed spin). Send dog to heel left.";
	akc_detailed_desc_map[ID_TR_L_HEEL_R_T_R] = "180 Turn Left – Heel on Right – 180 Turn Right - The Handler, whilst moving, signals the dog to complete a 180 degree turn to the left, at the same time turning 180 (left) toward the dog. The dog is to 'heel' on the right for a minimum of three steps. The Handler then signals the dog to turn 180 to the right, at the same time turning 180 to the right. Dog is returned to heel position.";
		std::map<int,CString>::iterator it;
	it = akc_detailed_desc_map.find(objectid);
	CString akc_detailed_desc = it->second;
	return akc_detailed_desc;
}
void StationMapper::GetStationDescriptionByAKCType(int type_class, CStringList& Items){
		switch (type_class) {
		case NOVICE:
			StationMapper::GetAKCNoviceList(Items);
			break;
		case ADVANCED:
			StationMapper::GetAKCNoviceList(Items);
			StationMapper::GetAKCAdvancedList(Items);
			break;
		case EXCELLENT:
			StationMapper::GetAKCNoviceList(Items);
			StationMapper::GetAKCAdvancedList(Items);
			StationMapper::GetAKCExcellentList(Items);
			break;
		case MASTER:
		case TRAINING:
			StationMapper::GetAKCNoviceList(Items);
			StationMapper::GetAKCAdvancedList(Items);
			StationMapper::GetAKCExcellentList(Items);
			StationMapper::GetAKCMasterList(Items);
			break;
		}
}

void StationMapper::GetAKCNoviceList(CStringList& Items) {
	Items.AddTail("1. START");
	Items.AddTail("2. FINISH");
	Items.AddTail("3. HALT-Sit");
	Items.AddTail("4. HALT-Down");
	Items.AddTail("5. Right Turn");
	Items.AddTail("6. Left Turn");
	Items.AddTail("7. About Turn Right");
	Items.AddTail("8. About U Turn");
	Items.AddTail("9. 270 Right Turn");
	Items.AddTail("10. 270 Left Turn");
	Items.AddTail("11. 360 Right Turn");
	Items.AddTail("12. 360 Left Turn");
	Items.AddTail("13. Call Front-Finish Right-Forward");
	Items.AddTail("14. Call Front-Finish Left-Forward");
	Items.AddTail("15. Call Front-Finish Right-HALT");
	Items.AddTail("16. Call Front-Finish Left-HALT");
	Items.AddTail("17. Slow Pace");
	Items.AddTail("18. Fast Pace");
	Items.AddTail("19. Normal Pace");
	Items.AddTail("20. Moving Side Step Right");
	Items.AddTail("21. Spiral Right-Dog Outside");
	Items.AddTail("22. Spiral Left-Dog Inside");
	Items.AddTail("23. Straight Figure 8 Weave Twice");
	Items.AddTail("24. Serpentine Weave Once");
	Items.AddTail("25. HALT-1,2,3 Steps Forward");
	Items.AddTail("26. Call Front-1,2,3 Steps Backward");
	Items.AddTail("27. Down");
	Items.AddTail("28. HALT-Fast Forward From Sit");
	Items.AddTail("29. Left About Turn");
	Items.AddTail("30. HALT-Walk Around Dog");
	Items.AddTail("31. HALT-Down-Walk Around Dog");
	Items.AddTail("32. Stand"); 

}
void StationMapper::GetAKCAdvancedList(CStringList& Items) {
	Items.AddTail("33. HALT-About U Turn-Forward");
	Items.AddTail("34. HALT-About Turn Right-Forward");
	Items.AddTail("35. HALT-Turn Right One Step-Call to Heel-HALT");
	Items.AddTail("36. HALT-Stand-Walk Around Dog");
	Items.AddTail("37. HALT-90 Pivot Right-Halt");
	Items.AddTail("38. HALT-90 Pivot Left-Halt");
	Items.AddTail("39. Offset Figure 8");
	Items.AddTail("40. HALT-Side Step Right-HALT");
	Items.AddTail("41. HALT-Call Dog Front-Finish Right");
	Items.AddTail("42. HALT-Call Dog Front-Finish Left");
	Items.AddTail("43. HALT-180 Pivot Right-HALT");
	Items.AddTail("44. HALT-180 Pivot Left-HALT");
	Items.AddTail("45. HALT-Down-Sit");
	Items.AddTail("46. Halt–Leave Dog-Recall");
	Items.AddTail("47. Double Right U Turn");
	Items.AddTail("48. Double Left U Turn");
	Items.AddTail("49. Double Left About Turn");
	Items.AddTail("50. Call front, Handler Reverses Three Steps-Finish");
	Items.AddTail("51. Leave Dog-About Turn–Return to Dog");
	Items.AddTail("52. Halt–Dog circles handler–Forward");
	Items.AddTail("53. Send Over Jump-Handler Passes By");
}
void StationMapper::GetAKCExcellentList(CStringList& Items) {
	Items.AddTail("54. HALT-Stand-Sit");
	Items.AddTail("55. HALT-Stand-Down");
	Items.AddTail("56. Moving Stand-Walk Around Dog");
	Items.AddTail("57. Halt-Leave Dog-Recall");
	Items.AddTail("58. Leave Dog-About Turn–Recall Dog–Finish Right");
	Items.AddTail("59. Leave Dog-About Turn–Recall Dog–Finish Left");
	Items.AddTail("60. Right U Turn-Left About Turn");
	Items.AddTail("61. Left U Turn–Left About Turn");
	Items.AddTail("62. Left About Turn–Right U Turn");
	Items.AddTail("63. Left About Turn–Left U Turn");
	Items.AddTail("64. Circle Spin at Heel");
	Items.AddTail("65. Four Cone Figure 8");
}
void StationMapper::GetAKCMasterList(CStringList& Items) {
	Items.AddTail("66. Halt-Leave Dog-Down Dog-Sit-Distance-Return");
	Items.AddTail("67. Stand-Leave Dog-Down Dog-Sit-Distance-Return");
	Items.AddTail("68. Moving Stand-Leave Dog-Distance Down");
	Items.AddTail("69. Moving Down-Walk Around Dog");
	Items.AddTail("70. Moving Sit-Walk Around Dog");
	Items.AddTail("71. Halt- Leave Dog-Call to Heel");
	Items.AddTail("72. Back Up 3 Steps");
	Items.AddTail("73. Stand – Pivot Right – Forward");
	Items.AddTail("74. Stand – Pivot Left – Forward");
	Items.AddTail("75. Call Front – Circle Spin Right – Finish Left");
	Items.AddTail("76. 180 Turn Left – Heel on Right – 180 Turn Right");
}
