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
	akc_objectid_map[32] = ID_WEAVES_FIGURE8;
	akc_objectid_map[33] = ID__DRAW_HALTLEFTFORWARD;
	akc_objectid_map[34] = ID__DRAW_HALTRIGHTFORWARD;
	akc_objectid_map[35] = ID_DRAW_FRONTHEEL;
	akc_objectid_map[36] = ID_DRAW_SLOWFORWARDFROMSIT;



	akc_objectid_map[101] = ID_ABOUT_FORWARD_RT;
	akc_objectid_map[102] = ID_DRAW_U_FORWARD_LT;
	akc_objectid_map[103] = ID_DRAW_JUMP;
	akc_objectid_map[104] = ID_DRAW_1STEP_HEEL_RT;
	akc_objectid_map[105] = ID_DRAW_STANDWALK;
	akc_objectid_map[106] = ID_DRAW_90_PIVOT_RT;
	akc_objectid_map[107] = ID_DRAW_90_PIVOT_LT;
	akc_objectid_map[108] = ID_DRAW_OFFSET_8;
	akc_objectid_map[109] = ID_DRAW_SIDE_RIGHT;
	akc_objectid_map[110] = ID_DRAW_HALT_FINISH_RT;
	akc_objectid_map[111] = ID_DRAW_HALT_FINISH_LT;
	akc_objectid_map[112] = ID_DRAW_180_PIVOT_RT;
	akc_objectid_map[113] = ID_DRAW_180_PIVOT_LT;
	akc_objectid_map[114] = ID_DRAW_DOWNSIT;
	akc_objectid_map[115] = ID_DRAW_STAND;
	akc_objectid_map[116] = ID_DRAW_HALTRIGHTPIVOTFORWARD;
	akc_objectid_map[117] = ID_DRAW_HALTLEFTPIVOTFORWARD;
	akc_objectid_map[118] = ID__DRAW_2_STEPS_FORWARD;


	akc_objectid_map[201] = ID_DRAW_STANDDOWN;
	akc_objectid_map[202] = ID_DRAW_STANDSIT;
	akc_objectid_map[203] = ID_DRAW_MOVE_STAND_WALK;
	akc_objectid_map[204] = ID__DRAW_MOVE_DOWN;
	akc_objectid_map[205] = ID_DRAW_BACKUP_3;
	akc_objectid_map[206] = ID__DRAW_DOWNWHILEHEELING;
	akc_objectid_map[207] = ID__STAND_HEEL;
	akc_objectid_map[208] = ID__DRAW_STAND_SIT_LEAVE;
	akc_objectid_map[209] = ID__STAND_LEAVE_DOWN;
	akc_objectid_map[210] = ID__DRAW_SENDTOJUMP;
	akc_objectid_map[211] = ID__DRAW_DOUBLE_LEFT_TURN;
	akc_objectid_map[298] = ID__DRAW_SITSTAY;
	akc_objectid_map[299] = ID__DRAW_CALLTOHEEL;
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
	akc_number_map[ID_WEAVES_FIGURE8] = "32";
	akc_number_map[ID__DRAW_HALTLEFTFORWARD] = "33";
	akc_number_map[ID__DRAW_HALTRIGHTFORWARD] = "34";
	akc_number_map[ID_DRAW_FRONTHEEL] = "35";
	akc_number_map[ID_DRAW_SLOWFORWARDFROMSIT] = "36";



	akc_number_map[ID_ABOUT_FORWARD_RT] = "101";
	akc_number_map[ID_DRAW_U_FORWARD_LT] = "102";
	akc_number_map[ID_DRAW_JUMP] = "103";
	akc_number_map[ID_DRAW_1STEP_HEEL_RT] = "104";
	akc_number_map[ID_DRAW_STANDWALK] = "105";
	akc_number_map[ID_DRAW_90_PIVOT_RT] = "106";
	akc_number_map[ID_DRAW_90_PIVOT_LT] = "107";
	akc_number_map[ID_DRAW_OFFSET_8] = "108";
	akc_number_map[ID_DRAW_SIDE_RIGHT] = "109";
	akc_number_map[ID_DRAW_HALT_FINISH_RT] = "110";
	akc_number_map[ID_DRAW_HALT_FINISH_LT] = "111";
	akc_number_map[ID_DRAW_180_PIVOT_RT] = "112";
	akc_number_map[ID_DRAW_180_PIVOT_LT] = "113";
	akc_number_map[ID_DRAW_DOWNSIT] = "114";
	akc_number_map[ID_DRAW_STAND] = "115";
	akc_number_map[ID_DRAW_HALTRIGHTPIVOTFORWARD] = "116";
	akc_number_map[ID_DRAW_HALTLEFTPIVOTFORWARD] = "117";
	akc_number_map[ID__DRAW_2_STEPS_FORWARD] = "118";

	akc_number_map[ID_DRAW_STANDDOWN] = "201";
	akc_number_map[ID_DRAW_STANDSIT] = "202";
	akc_number_map[ID_DRAW_MOVE_STAND_WALK] = "203";
	akc_number_map[ID__DRAW_MOVE_DOWN] = "204";
	akc_number_map[ID_DRAW_BACKUP_3] = "205";
	akc_number_map[ID__DRAW_DOWNWHILEHEELING] = "206";
	akc_number_map[ID__STAND_HEEL] = "207";
	akc_number_map[ID__DRAW_STAND_SIT_LEAVE] = "208";
	akc_number_map[ID__STAND_LEAVE_DOWN] = "209";
	akc_number_map[ID__DRAW_SENDTOJUMP] = "210";
	akc_number_map[ID__DRAW_DOUBLE_LEFT_TURN] = "211";
	akc_number_map[ID__DRAW_SITSTAY] = "298";
	akc_number_map[ID__DRAW_CALLTOHEEL] = "299";

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
	combo_akc_map[32] = 33;
	combo_akc_map[33] = 34;
	combo_akc_map[34] = 34;
	combo_akc_map[35] = 36;
	combo_akc_map[36] = 101;
	combo_akc_map[37] = 102;
	combo_akc_map[38] = 103;
	combo_akc_map[39] = 104;
	combo_akc_map[40] = 105;
	combo_akc_map[41] = 106;
	combo_akc_map[42] = 107;
	combo_akc_map[43] = 108;
	combo_akc_map[44] = 109;
	combo_akc_map[45] = 110;
	combo_akc_map[46] = 111;
	combo_akc_map[47] = 112;
	combo_akc_map[48] = 113;
	combo_akc_map[49] = 114;
	combo_akc_map[50] = 115;
	combo_akc_map[51] = 116;
	combo_akc_map[52] = 117;
	combo_akc_map[53] = 118;

	combo_akc_map[54] = 201;
	combo_akc_map[55] = 202;
	combo_akc_map[56] = 203;
	combo_akc_map[57] = 204;
	combo_akc_map[58] = 205;
	combo_akc_map[59] = 206;
	combo_akc_map[60] = 207;
	combo_akc_map[61] = 208;
	combo_akc_map[62] = 209;
	combo_akc_map[63] = 210;
	combo_akc_map[64] = 211;
	combo_akc_map[65] = 298;
	combo_akc_map[66] = 299;
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
	akc_comboselect_map[33] = 33;
	akc_comboselect_map[34] = 34;
	akc_comboselect_map[35] = 35;
	akc_comboselect_map[36] = 36;

	akc_comboselect_map[101] = 37;
	akc_comboselect_map[102] = 38;
	akc_comboselect_map[103] = 39;
	akc_comboselect_map[104] = 40;
	akc_comboselect_map[105] = 41;
	akc_comboselect_map[106] = 42;
	akc_comboselect_map[107] = 43;
	akc_comboselect_map[108] = 44;
	akc_comboselect_map[109] = 45;
	akc_comboselect_map[110] = 46;
	akc_comboselect_map[111] = 47;
	akc_comboselect_map[112] = 48;
	akc_comboselect_map[113] = 49;
	akc_comboselect_map[114] = 50;
	akc_comboselect_map[115] = 51;
	akc_comboselect_map[116] = 52;
	akc_comboselect_map[117] = 53;
	akc_comboselect_map[118] = 54;


	akc_comboselect_map[201] = 55;
	akc_comboselect_map[202] = 56;
	akc_comboselect_map[203] = 57;
	akc_comboselect_map[204] = 58;
	akc_comboselect_map[205] = 59;
	akc_comboselect_map[206] = 60;
	akc_comboselect_map[207] = 61;
	akc_comboselect_map[208] = 62;
	akc_comboselect_map[209] = 63;
	akc_comboselect_map[210] = 64;
	akc_comboselect_map[211] = 65;
	akc_comboselect_map[298] = 66;
	akc_comboselect_map[299] = 67;

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
	akc_bitmap_map[ID_DRAW_SITHALT] = IDB_HALTFORWARD;
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
	akc_bitmap_map[ID_WEAVES_FIGURE8] = IDB_FIGURE8_NODIST;
	akc_bitmap_map[ID__DRAW_HALTLEFTFORWARD] = IDB_LEFT_HALT_FORWARD;
	akc_bitmap_map[ID__DRAW_HALTRIGHTFORWARD] = IDB_RIGHT_HALT_FORWARD;
	akc_bitmap_map[ID_DRAW_FRONTHEEL] = IDB_FRONT_HEEL;
	akc_bitmap_map[ID_DRAW_SLOWFORWARDFROMSIT] = IDB_HALTFORWARD;



	akc_bitmap_map[ID_ABOUT_FORWARD_RT] = IDB_ABOUT_FORWARD_TURN_RT;
	akc_bitmap_map[ID_DRAW_U_FORWARD_LT] = IDB_U_FORWARD_LT;
	akc_bitmap_map[ID_DRAW_JUMP] = IDB_JUMP;
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
	akc_bitmap_map[ID_DRAW_STAND] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_HALTRIGHTPIVOTFORWARD] = IDB_RIGHT_HALT_FORWARD;
	akc_bitmap_map[ID_DRAW_HALTLEFTPIVOTFORWARD] = IDB_LEFT_HALT_FORWARD;
	akc_bitmap_map[ID__DRAW_2_STEPS_FORWARD] = IDB_LEAVE_DOG_2_STEPS_HEEL;



	akc_bitmap_map[ID_DRAW_STANDDOWN] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_STANDSIT] = IDB_HALTFORWARD;
	akc_bitmap_map[ID_DRAW_MOVE_STAND_WALK] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_MOVE_DOWN] = IDB_MOVE;
	akc_bitmap_map[ID_DRAW_BACKUP_3] = IDB_BACKUP;
	akc_bitmap_map[ID__DRAW_DOWNWHILEHEELING] = IDB_MOVE;
	akc_bitmap_map[ID__STAND_HEEL] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_STAND_SIT_LEAVE] = IDB_MOVE;
	akc_bitmap_map[ID__STAND_LEAVE_DOWN] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_SENDTOJUMP] = IDB_JUMP_SEND;
	akc_bitmap_map[ID__DRAW_DOUBLE_LEFT_TURN] = IDB_DOUBLE_LEFT_TURN;
	akc_bitmap_map[ID__DRAW_SITSTAY] = IDB_MOVE;
	akc_bitmap_map[ID__DRAW_CALLTOHEEL] = IDB_MOVE;

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
	akc_description_map[ID_DRAW_SITHALT] = "HALT-Sit";
	akc_description_map[ID_DRAW_SITHALTDOWN] = "HALT-Sit-Down";
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
	akc_description_map[ID_DRAW_MOVE_DOWN] = "Down and Stop";
	akc_description_map[ID_DRAW_FAST_SIT] = "HALT-Fast Forward From Sit";
	akc_description_map[ID_DRAW_ABOUT_TURN_LT] = "Left About Turn";
	akc_description_map[ID_DRAW_HALTWALK] = "HALT-Walk Around Dog";
	akc_description_map[ID_DRAW_DOWNWALK] = "HALT-Down-Walk Around Dog";
	akc_description_map[ID_WEAVES_FIGURE8] = "Figure 8 No Distractions";
	akc_description_map[ID__DRAW_HALTLEFTFORWARD] = "HALT Left Turn Forward";
	akc_description_map[ID__DRAW_HALTRIGHTFORWARD] = "HALT Right Turn Forward";
	akc_description_map[ID_DRAW_FRONTHEEL] = "Call Front-Return to Heel";
	akc_description_map[ID_DRAW_SLOWFORWARDFROMSIT] = "HALT-Slow Forward From Sit";

	akc_description_map[ID_ABOUT_FORWARD_RT] = "HALT-About Turn Right-Forward";
	akc_description_map[ID_DRAW_U_FORWARD_LT] = "HALT-About U Turn-Forward";
	akc_description_map[ID_DRAW_JUMP] = "Send Over Jump-Handler Passes By";
	akc_description_map[ID_DRAW_1STEP_HEEL_RT] = "HALT-Turn Right One Step-Call to Heel-HALT";
	akc_description_map[ID_DRAW_STANDWALK] = "HALT-Stand-Walk Around Dog";
	akc_description_map[ID_DRAW_90_PIVOT_RT] = "HALT-90 Pivot Right-Halt";
	akc_description_map[ID_DRAW_90_PIVOT_LT] = "HALT-90 Pivot Left-Halt";
	akc_description_map[ID_DRAW_OFFSET_8] = "Offset Figure 8";
	akc_description_map[ID_DRAW_SIDE_RIGHT] = "HALT-Side Step Right-HALT";
	akc_description_map[ID_DRAW_HALT_FINISH_RT] = "HALT-Call Dog Front-Finish Right";
	akc_description_map[ID_DRAW_HALT_FINISH_LT] = "HALT-Call Dog Front-Finish Left";
	akc_description_map[ID_DRAW_180_PIVOT_RT] = "HALT-180 Pivot Right-HALT";
	akc_description_map[ID_DRAW_180_PIVOT_LT] = "HALT-180 Pivot Left-HALT";
	akc_description_map[ID_DRAW_DOWNSIT] = "HALT-Down-Sit";
	akc_description_map[ID_DRAW_STAND] = "HALT-Stand";
	akc_description_map[ID_DRAW_HALTRIGHTPIVOTFORWARD] = "Halt-Pivot Right-Forward";
	akc_description_map[ID_DRAW_HALTLEFTPIVOTFORWARD] = "Halt-Pivot Left-Forward";
	akc_description_map[ID__DRAW_2_STEPS_FORWARD] = "Halt-Leave Dog-2 Steps-Call to Heel-Forward";


	akc_description_map[ID_DRAW_STANDDOWN] = "HALT-Stand-Down";
	akc_description_map[ID_DRAW_STANDSIT] = "HALT-Stand-Sit";
	akc_description_map[ID_DRAW_MOVE_STAND_WALK] = "Moving Stand-Walk Around Dog";
	akc_description_map[ID__DRAW_MOVE_DOWN] = "Moving Down-Walk Around Dog";
	akc_description_map[ID_DRAW_BACKUP_3] = "Back Up 3 Steps-Dog Stays in Position";
	akc_description_map[ID__DRAW_DOWNWHILEHEELING] = "Down While Heeling";
	akc_description_map[ID__STAND_HEEL] = "Stand While Heeling";
	akc_description_map[ID__DRAW_STAND_SIT_LEAVE] = "Stand-Leave Dog-Sit Dog-Call Front-Finish";
	akc_description_map[ID__STAND_LEAVE_DOWN] = "Stand-Leave Dog-Down Dog-Call Front-Finish";
	akc_description_map[ID__DRAW_SENDTOJUMP] = "Send to Jump";
	akc_description_map[ID__DRAW_DOUBLE_LEFT_TURN] = "Double Left About Turn";
	akc_description_map[ID__DRAW_SITSTAY] = "Sit Stay";
	akc_description_map[ID__DRAW_CALLTOHEEL] = "Call to Heel";

	std::map<int,CString>::iterator it;
	it = akc_description_map.find(objectid);
	CString akc_descritpion = it->second;
	return akc_descritpion;
}
CString StationMapper::GetAKCDetailedDescrptionFromAKCNumber(int akc_number)
{
	int object_id = StationMapper::ObjectIDFromAKCNumber(akc_number);
	return StationMapper::GetAKCDetailedDescrptionFromObjectID(object_id);
}
CString StationMapper::GetAKCDetailedDescrptionFromObjectID(int objectid) {
	 std::map <int, CString> akc_detailed_desc_map;
	akc_detailed_desc_map[ID_DRAW_START] =  "START-Indicates the beginning of the course. ";
	akc_detailed_desc_map[ID_DRAW_FINISH] = "FINISH-Indicates the end of the course-timing stops. ";
	akc_detailed_desc_map[ID_DRAW_SITHALT] = "HALT-Sit. While heeling, the handler halts and the dog comes to a sit in heel position. The team\r\n then moves forward toward the next exercise sign (station), with the dog in heel position.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_SITHALTDOWN] = "HALT-Sit-Down. While heeling, the handler halts and the dog comes to a sit. The handler then\r\n commands the dog to down, followed by the command to heel forward from the down position.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_RT_TURN] =  "Right Turn. Performed as a 90º turn to the right, as in traditional obedience. ";
	akc_detailed_desc_map[ID_DRAW_LT_TURN] =  "Left Turn. Performed as a 90º turn to the left, as in traditional obedience. ";
	akc_detailed_desc_map[ID_DRAW_ABOUT_RT] = "About Turn Right. While heeling, the team makes a 180º about turn to the handler's right";
	akc_detailed_desc_map[ID_DRAW_ABOUT_LT] = "About U Turn. While heeling, the team makes a 180º about turn to the handler's left";
	akc_detailed_desc_map[ID_DRAW_270_RT] = "270 Right Turn While heeling, the team makes a 270º turn to the handler's right. 270° turns are\r\n performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_270_LT] = "270 Left Turn. While heeling, the team makes a 270º turn to the handler's left. 270º turns are\r\n performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_360_RT] = "360 Right Turn. While heeling, the team makes a 360º turn to the handler's right. 360º turns are\r\n performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_360_LT] = "360 Left Turn. While heeling, the team makes a 360º turn to the handler's left. 360º turns are\r\n performed as a tight circle, but not around the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_FINISH_RT_FORWARD] = "Call Front-Finish Right-Forward. While heeling, the handler stops forward motion and calls the dog\r\n to the front position (dog sits in front and faces the handler). The handler may take several\r\n steps backward as the dog turns and moves to sit in the front position. The second part of\r\n the exercise directs the handler to move forward while commanding the dog to change from\r\n the front position to the handler's right, around behind the handler and to heel position,\r\n as the handler continues forward. The dog does not sit before moving forward in heel position\r\n with the handler. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FINISH_LEFT_FORWARD] = "Call Front-Finish Left-Forward. While heeling, the handler stops forward motion and calls the dog\r\n to the front position (dog sits in front and faces the handler). The handler may take several\r\n steps backward as the dog turns and moves to sit in the front position. The second part of\r\n the exercise directs the handler to move forward while commanding the dog to change from\r\n the front position to the handler's left and moving to heel position, as the handler continues\r\n forward. The dog does not sit before moving forward in heel position with the handler.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FINISH_RT_HALT] = "Call Front-Finish Right-HALT. While heeling, the handler stops forward motion and calls the dog to\r\n the front position (dog sits in front and faces the handler). The handler may take several\r\n steps backward as the dog turns and moves to sit in the front position. The second part is the\r\n finish to the right, where the dog must return to heel position by moving around the\r\n right side of the handler. Dog must sit in heel position before moving forward with the handler.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FINISH_LT_HALT] = "Call Front-Finish Left-HALT. While heeling, the handler stops forward motion and calls the dog to\r\n the front position (dog sits in front and faces the handler). The handler may take several\r\n steps backward as the dog turns and moves to a sit in the front position. The second part is the\r\n finish to the left, where the dog must move to the handler's left and sit in heel\r\n position. Dog must sit in heel position before moving forward in heel position with the handler.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_SLOW] = "Slow Pace. Dog and handler must slow down noticeably. This must be followed by a normal pace,\r\n unless it is the last station in the class.";
	akc_detailed_desc_map[ID_DRAW_FAST] = "Fast Pace. Dog and handler must speed up noticeably. This must be followed by a normal pace,\r\n unless it is the last station in the class.";
	akc_detailed_desc_map[ID_DRAW_NORMAL] = "Normal Pace. Dog and handler must move forward, walking briskly and naturally. ";
	akc_detailed_desc_map[ID_DRAW_SIDE_RT] = "Moving Side Step Right. While heeling, the handler takes one step diagonally to the right and\r\n continues moving forward along the newly established line. The dog maintains heel position.\r\n The exercise may be performed just past the exercise sign.";
	akc_detailed_desc_map[ID_DRAW_SPIRAL_RIGHT] = "Spiral Right-Dog Outside. This exercise requires three pylons or posts placed in a straight line\r\n with spaces between them of approximately 6-8 feet. Spiral Right indicates the handler must\r\n turn to the right when moving around each pylon or post. This places the dog on the outside of\r\n the turns. The exercise sign is placed near or on the first pylon or post where the spiral\r\n is started.";
	akc_detailed_desc_map[ID_DRAW_SPIRAL_LEFT] = "Spiral Left-Dog Inside. This exercise requires three pylons or posts placed in a straight line with\r\n spaces between them of approximately 6-8 feet. Spiral Left indicates that the handler must\r\n turn to the left when moving around each pylon or post. This places the dog on the inside of\r\n the turns. The exercise sign is placed near or on the first pylon or post where the spiral\r\n is started.";
	akc_detailed_desc_map[ID_DRAW_WEAVE_TWICE] = "Straight Figure 8 Weave Twice. This exercise requires four obstacles (pylons, posts or people)\r\n placed in a straight line with spaces between them of approximately 6-8 feet. The exercise sign\r\n is placed near or on the first obstacle where the exercise is started. Entry into the weaving\r\n pattern is with the first obstacle at the dog/handler's left side.";
	akc_detailed_desc_map[ID_DRAW_SERP_ONCE] = "Serpentine Weave Once. This exercise requires four obstacles (pylons, posts or people) placed in\r\n a straight line with spaces between them of approximately 6-8 feet. The exercise sign is placed\r\n near or on the first obstacle where the exercise is started. Entry into the weaving pattern\r\n is with the first obstacle at the dog/handler's left side. It should be noted that in\r\n this exercise, the team does not weave back through the obstacles as they do in the Straight\r\n Figure 8.";
	akc_detailed_desc_map[ID_DRAW_HALT_3_STEPS_FOR] = "HALT-1,2,3 Steps Forward. The team halts with the dog sitting in heel position to begin the exercise.\r\n The handler takes one step forward, with the dog maintaining heel position, and halts. The dog\r\n sits when the handler halts. This is followed by two steps forward-halt, and three steps\r\n forward-halt, with the dog heeling each time the handler moves forward, and sitting\r\n each time the handler halts. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FRONT_3_STEPS_BACK] = "Call Front-1,2,3 Steps Backward. While heeling, the handler stops forward motion and calls the dog\r\n to the front position (dog sits in front and faces the handler). The handler may take several\r\n steps backward as the dog turns and moves to a sit in the front position. With the dog in the\r\n front position, the handler takes one step backward and halts. The dog moves with the\r\n handler and sits in the front position as the handler halts. This is followed by the handler\r\n taking two steps backward and a halt, and three steps backward and a halt. Each time, the\r\n dog moves with the handler to the front position and sits as the handler halts.\r\n The handler then commands the dog to resume heel position as the team moves forward\r\n toward the next station. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_MOVE_DOWN] = "Moving Down. While moving with the dog in heel position, the handler commands the dog to drop to a\r\n down position, as the handler pauses next to the dog. Once the dog is completely in the down\r\n position, the handler moves forward commanding the dog to heel from the down position.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FAST_SIT] = "HALT-Fast Forward From Sit. With the dog sitting in heel position, the handler commands the dog to\r\n heel and immediately moves forward at a fast pace. This must be followed by a normal pace, unless\r\n it is the last station in the class. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_ABOUT_TURN_LT] = "Left About Turn. While moving with the dog in heel position, the handler makes an about turn to the\r\n left, while at the same time, the dog must move around the handler to the right and to heel\r\n position. The dog does not sit before moving forward in heel position with the handler.";
	akc_detailed_desc_map[ID_DRAW_HALTWALK] = "HALT-Walk Around Dog. With the dog sitting in heel position, the handler commands the dog to stay,\r\n then proceeds to walk around the dog to the left, returning to heel position. The handler must\r\n pause in heel position before moving forward to the next station. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_DOWNWALK] = "HALT-Down-Walk Around Dog. With dog sitting in heel position, the handler commands the dog\r\n to down and to stay, then proceeds to walk around the dog to the left, returning to heel position. The\r\n handler must pause in heel position before moving forward to the next station. The dog\r\n heels forward from the down position. (Stationary exercise)";
	akc_detailed_desc_map[ID_WEAVES_FIGURE8] = "Figure 8-No Distractions. Two pylons or posts spaced approximately 6-8 feet apart.\r\n The team enters the sequence with the posts on either left or right and will perform a complete figure 8 around\r\n the posts or pylons, crossing the center point three times.";
	akc_detailed_desc_map[ID__DRAW_HALTLEFTFORWARD] = "HALT-Left Turn-Forward. Handler halts, dog sits. With the dog sitting the handler\r\n commands and/or signals the dog to heel, as the handler turns to the left and continues to move forward\r\n in the new direction without hesitation. The dog must turn with handler as the handler turns.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_HALTRIGHTFORWARD] = "HALT-Right Turn-Forward. Handler halts, dog sits. With the dog sitting the handler\r\n commands and/or signals the dog to heel, as the handler turns to the right and continues to move forward\r\n in the new direction without hesitation. The dog must turn with handler as the handler turns.\r\n (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_FRONTHEEL] = "Call Front-Return to Heel. While heeling the handler stops forward motion and calls the dog to\r\n the front position. The handler may take several steps backward as the dog turns and moves to sit in the\r\n front position. Dog sits in front and faces the handler. The handler will then walk around\r\n behind the dog and return to the heel position and pause. Dog must remain sitting as handler\r\n walks around dog. (This is a 180º change of direction, about turn.)(Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_SLOWFORWARDFROMSIT] = "Halt-Slow Forward From Sit, The handler halts, and the dog sits in heel position.\r\n The handler then commands and/or signals the dog to heel and moves forward at a slow pace. The dog must\r\n maintain heel position as handler slowly moves forward. This must be followed by a normal pace,\r\n unless it is the last station on the course. (Stationary exercise)";


	akc_detailed_desc_map[ID_ABOUT_FORWARD_RT] = "HALT-About Turn Right-Forward. With the dog sitting in heel position, the team turns 180º to the\r\n right and immediately moves forward. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_U_FORWARD_LT] = "HALT-About U Turn-Forward. With the dog sitting in heel position, the team turns 180º to the left\r\n and immediately moves forward. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_JUMP] = "Send Over Jump-Handler Passes By. While moving with the dog in heel position, the handler directs the\r\n dog to take the jump, as the handler passes by the jump without any pause, hesitation or stopping. When the dog has\r\n completed the jump, it is called to heel position and the team continues to the next exercise. ";
	akc_detailed_desc_map[ID_DRAW_1STEP_HEEL_RT] = "HALT-Turn Right One Step-Call to Heel-HALT. With the dog sitting in heel position, the handler\r\n commands the dog to wait or stay. The handler then turns to the right, while taking one step in that\r\n direction, and halts. The dog is called to sit in heel position in the new location\r\n before moving forward to the next station.(Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_STANDWALK] = "HALT-Stand-Walk Around Dog. With the dog sitting in heel position, the handler will stand the dog,\r\n command the dog to stay and walk around the dog to the left, returning to heel position. The handler\r\n must pause in heel position before moving forward to the next station. In the\r\n Advanced class, the handler may touch the dog, move forward to stand the dog, and may pose the\r\n dog as in the show ring. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_90_PIVOT_RT] = "HALT-90 Pivot Right-Halt. With the dog sitting in heel position, the team pivots 90º to the right,\r\n halts, the dog sits and then moves forward. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_90_PIVOT_LT] = "HALT-90 Pivot Left-Halt. With the dog sitting in heel position, the team pivots 90º to the left,\r\n halts, the dog sits and then moves forward. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_OFFSET_8] = "Offset Figure 8. This exercise requires two pylons, posts or people placed about 8-10 feet apart,\r\n around which the team will perform a complete Figure 8. Two distractions will be arranged to the\r\n sides of the Figure 8 about 5-6 feet apart. Entry may be between the pylons, posts\r\n or people and the distraction on either side. The distractions will consist of two loosely\r\n covered, but secure, containers with tempting dog treats; however, dog toys may replace one\r\n or both containers, or may be placed next to the containers. Exercise sign may be placed on\r\n or near the cone where entry is made into the Offset Figure 8.";
	akc_detailed_desc_map[ID_DRAW_SIDE_RIGHT] = "HALT-Side Step Right-HALT. With the dog sitting in heel position, the team moves one step directly\r\n to the right and halts. The dog moves with the handler and sits in heel position when the handler\r\n halts. The exercise may be performed just past the exercise sign. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_HALT_FINISH_RT] = "HALT-Call Dog Front-Finish Right. With the dog sitting in heel position, the handler calls the dog\r\n to front, and the dog sits in the front position facing the handler. On command, the dog then moves\r\n from the front position around the right of the handler and sits in heel position.\r\n Handler may not step forward or backward to aid dog during exercise. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_HALT_FINISH_LT] = "HALT-Call Dog Front-Finish Left. With the dog sitting in heel position, the handler calls the dog to\r\n front, and the dog sits in the front position facing the handler. On command, the dog then moves\r\n from the front position to the handler's left and sits in heel position. Handler may\r\n not step forward or backward to aid dog during exercise. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_180_PIVOT_RT] = "HALT-180 Pivot Right-HALT. With the dog sitting in heel position, the handler pivots 180º to the\r\n right. The dog moves with the handler and sits in heel position. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_180_PIVOT_LT] = "HALT-180 Pivot Left-HALT. With the dog sitting in heel position, the handler pivots 180º to the left.\r\n The dog moves with the handler and sits in heel position. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_DOWNSIT] = "HALT-Down-Sit. With dog sitting in heel position, the handler commands the dog to down, then to sit.\r\n (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_STAND] = "HALT-Stand. Handler halts and dog sits. With the dog sitting in heel position, the handler will stand the\r\n dog. Handler may touch the dog, move forward to stand the dog and may pose the dog as in the show\r\n ring. Handler then resumes heel position while the dog stands in place. Handler pauses\r\n before moving forward. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_HALTRIGHTPIVOTFORWARD] = "Halt-Pivot Right-Forward. The handler halts and the dog sits in heel position. The handler\r\n commands and/or signals the dog to heel, then pivots to the right and dog and handler move forward\r\n. (Stationary exercise)";
	akc_detailed_desc_map[ID_DRAW_HALTLEFTPIVOTFORWARD] = "Halt-Pivot Left-Forward. The handler halts and the dog sits in heel position. The handler\r\n commands and/or signals the dog to heel, then pivots to the left and dog and handler move forward\r\n. (Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_2_STEPS_FORWARD] = "The handler halts, and the dog sits in heel position. While the dog remains sitting the handler\r\n takes two steps forward and pauses. The handler moves forward and commands the dog to resume heel\r\n position. The dog must move briskly. (Stationary exercise)";

	akc_detailed_desc_map[ID_DRAW_STANDDOWN] = "HALT-Stand-Down. With dog sitting in heel position, the handler will stand the dog (without physical\r\n handling), then commands the dog to down. The handler then commands the dog to heel forward\r\n from the down position. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_STANDSIT] = "HALT-Stand-Sit. With dog sitting in heel position, the handler will stand the dog (without physical\r\n handling), then commands the dog to sit. (Stationary exercise) ";
	akc_detailed_desc_map[ID_DRAW_MOVE_STAND_WALK] = "Moving Stand-Walk Around Dog. While heeling and with no hesitation, the handler will stand the dog,\r\n leave and walk around the dog to the left, returning to heel position. The handler must pause\r\n in heel position before moving forward to the next station. Dog must move forward fromthe standing position.";
	akc_detailed_desc_map[ID__DRAW_MOVE_DOWN] = "Moving Down-Walk Around Dog. While heeling and with no hesitation, the handler will down the dog,\r\n leave and walk around the dog to the left, returning to heel position. The handler must pause\r\n in heel position before moving forward to the next station. The dog must move forward from the down position.";


	akc_detailed_desc_map[ID_DRAW_BACKUP_3] = "Back Up 3 Steps-Dog Stays in Position. While heeling, the handler reverses direction walking\r\n backward 3 steps, without first halting, then continues heeling forward. The dog moves backward with\r\n the handler and maintains position throughout the exercise without sitting.";
	akc_detailed_desc_map[ID__DRAW_DOWNWHILEHEELING] = "Down While Heeling-While moving forward, without pause or hesitation, the handler\r\n will command and/or signal the dog to down and stay as the handler continues forward about 6 feet to\r\n the Call to Heel marker. The handler will turn and face the dog, pause and then command\r\n and/or signal the dog to heel. This is a 180º change of direction, about turn.\r\n (This sign will be followed within 6 feet by the Call to Heel marker.) Dog must return to heel position\r\n and sit, the handler must pause before moving forward. (Stationary exercise)";
	akc_detailed_desc_map[ID__STAND_HEEL] = "Stand While Heeling-While moving forward, without pause or hesitation, the handler\r\n will command and/or signal the dog to stand and stay as the handler continues forward about 6 feet to\r\n the Call to Heel marker. The handler will turn and face the dog, pause and then command\r\n and/or signal the dog to heel. This is a 180º change of direction, about turn.\r\n (This sign will be followed within 6 feet by the Call to Heel marker.) Dog must return to heel position\r\n and sit, the handler must pause before moving forward. (Stationary exercise)";
	akc_detailed_desc_map[ID__DRAW_STAND_SIT_LEAVE] = "Stand-Leave Dog-Sit Dog-Call Front-Finish-While heeling, the handler will stop\r\n and command and/or signal the dog to stand. The dog must stand and stay without sitting\r\n first. Then the handler will walk forward approximately 6 feet to the Call to Heel marker.\r\n The handler will turn to face the dog and command and/or signal the dog\r\n to sit. When the dog sits, the handler will command and/or signal the dog to front. The dog sits in the front position facing\r\n the handler. On command and/or signal, the dog will move to heel position. Dog must\r\n sit in heel position before moving forward with the handler. (Stationary Exercise) (This exercise reverses the\r\n direction of the team.)";
	akc_detailed_desc_map[ID__STAND_LEAVE_DOWN] = "Stand-Leave Dog-Down Dog-Call Front-Finish-While heeling, the handler will stop\r\n and stand the dog using a command and/or signal, then walk forward approximately 6 feet. The dog\r\n must stand and stay without sitting first. The handler will turn to face the dog and\r\n command and/or signal the dog to down. When the dog downs, the handler will\r\n command and/or signal the dog to front. The dog must sit in the front position facing the handler. On command and/or signal,\r\n the dog will move to heel position. The dog must sit in heel position before moving\r\n forward with the handler.(Stationary Exercise) (This exercise reverses the direction of the team.)";
	akc_detailed_desc_map[ID__DRAW_SENDTOJUMP] = "Send to Jump-At the sign for this station, the handler will command and/or signal the dog to leave heel position to execute the jump. The dog must leave the handler immediately and execute the jump. The handler must maintain a straight path of at least a 3 foot distance away from the jump and may not pass the jump until the dog has returned to heel position. The dog must jump the jump in the proper direction and return to heel position without pause, hesitation, or stopping. The team then continues to the next station.";
	akc_detailed_desc_map[ID__DRAW_DOUBLE_LEFT_TURN] = "Double Left About Turn- While moving with the dog in heel position, the handler makes\r\n an about turn to the left while at the same time, the dog must move around the handler to the\r\n right and into heel position. The handler must take one or two steps forward before\r\n performing the exercise a second time. The handler will end up turning 360° \r\nto the left as the dog turns 360° to the right around the handler. The dog does not sit at any time during this exercise.";
	akc_detailed_desc_map[ID__DRAW_SITSTAY] = "Sit Stay-This sign will be used as a marker for the sit stay exercise. The dog must remain\r\n in the sit position while the handler retrieves the leash and returns to heel position and the judge says “exercise finished.”";
	akc_detailed_desc_map[ID__DRAW_CALLTOHEEL] = "Call to Heel-This sign will be used as a marker for associated exercises.";



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
		case TRAINING:
			StationMapper::GetAKCNoviceList(Items);
			StationMapper::GetAKCAdvancedList(Items);
			StationMapper::GetAKCExcellentList(Items);
			break;
		}
}

void StationMapper::GetAKCNoviceList(CStringList& Items) {
	Items.AddTail("1. START");
	Items.AddTail("2. FINISH");
	Items.AddTail("3. HALT-Sit");
	Items.AddTail("4. HALT-Sit-Down");
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
	Items.AddTail("27. Moving Down");
	Items.AddTail("28. HALT-Fast Forward From Sit");
	Items.AddTail("29. Left About Turn");
	Items.AddTail("30. HALT-Walk Around Dog");
	Items.AddTail("31. HALT-Down-Walk Around Dog");
	Items.AddTail("32. Figure 8 No Distractions");
	Items.AddTail("33. HALT Left Turn Forward");
	Items.AddTail("34. HALT Right Turn Forward");
	Items.AddTail("35. Call Front Return to Heel");
	Items.AddTail("36. Halt-Slow Forward From Sit");
}
void StationMapper::GetAKCAdvancedList(CStringList& Items) {
	Items.AddTail("101. HALT-About Turn Right-Forward");
	Items.AddTail("102. HALT-About U Turn-Forward");
	Items.AddTail("103. Send Over Jump-Handler Passes By");
	Items.AddTail("104. HALT-Turn Right One Step-Call to Heel-HALT");
	Items.AddTail("105. HALT-Stand-Walk Around Dog");
	Items.AddTail("106. HALT-90 Pivot Right-Halt");
	Items.AddTail("107. HALT-90 Pivot Left-Halt");
	Items.AddTail("108. Offset Figure 8");
	Items.AddTail("109. HALT-Side Step Right-HALT");
	Items.AddTail("110. HALT-Call Dog Front-Finish Right");
	Items.AddTail("111. HALT-Call Dog Front-Finish Left");
	Items.AddTail("112. HALT-180 Pivot Right-HALT");
	Items.AddTail("113. HALT-180 Pivot Left-HALT");
	Items.AddTail("114. HALT-Down-Sit");
	Items.AddTail("115. HALT-Stand");
	Items.AddTail("116. Halt-Pivot Right-Forward");
	Items.AddTail("117. Halt-Pivot Left-Forward");
	Items.AddTail("118. Halt-Leave Dog-2 Steps-Call to Heel- Forward");
}
void StationMapper::GetAKCExcellentList(CStringList& Items) {
	Items.AddTail("201. HALT-Stand-Down");
	Items.AddTail("202. HALT-Stand-Sit");
	Items.AddTail("203. Stand-Walk Around Dog");
	Items.AddTail("204. Down-Walk Around Dog");
	Items.AddTail("205. Back Up 3 Steps-Dog Stays in Position");
	Items.AddTail("206. Down While Heeling");
	Items.AddTail("207. Stand While Heeling");
	Items.AddTail("208. Stand-Leave Dog-Sit Dog-Call Front-Finish");
	Items.AddTail("209. Stand-Leave Dog-Down Dog-Call Front-Finish");
	Items.AddTail("210. Send to Jump");
	Items.AddTail("211. Double Left About Turn");
	Items.AddTail("298. Sit Stay");
	Items.AddTail("299. Call to Heel");


}
