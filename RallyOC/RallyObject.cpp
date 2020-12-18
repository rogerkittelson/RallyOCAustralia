#include "stdafx.h"
#include "RallyObject.h"
#include "DogRun.h"
#include "EnBitmap.h"
#include "DogRunDoc.h"

IMPLEMENT_SERIAL(CRallyObject, CObject, VERSIONABLE_SCHEMA | 3)
CRallyObject::CRallyObject()
{
	// This empty constructor should be used by serialization only
}
CRallyObject::CRallyObject(int objectID, int stringID, int type_station, int akc_num, int xPos, int yPos)
{
	this->m_selected = true;
	this->m_rally_station_ID = objectID;
	this->m_rally_string_ID = stringID;
	this->m_type_station = type_station;
	this->m_midPoint.x = xPos;
	this->m_midPoint.y = yPos;
	m_M11 = m_M22 = (float)1.0;
	m_M12 = (float)-0.0; 
	m_M21 = (float)0.0;
	this->m_rotate_text = 0;
	this->m_cus_exit.x = -1;
	this->m_cus_exit.y = -1;
	this->m_cus_entrance.x = -1;
	this->m_cus_entrance.y = -1;
	this->m_do_rotate_text = false;
	this->m_stat_desc = BOTH_TEXT_PIC;

	this->SetStationDegreeRotation();

	if (objectID != 0) // if id is zero than creating an object to add clipboard and/or undo-redo lists
		this->SetStationRect();

	this->m_akc_number = akc_num;

}
void CRallyObject::DrawStringForStationScoreSheet(CDC* pDC, CPoint top_left) {
	CString string_to_draw, sec_string;
	TEXTMETRIC tm;
	int len, half_string;
	int new_width, new_right, new_bottom, new_left, new_top, new_height;
	new_left = top_left.x;
	new_top = top_left.y;
	new_width = this->m_width * 3;
	new_right = new_left + new_width;
	new_height = this->m_height * 3;
	new_bottom = new_height + new_top;
	pDC->GetTextMetrics(&tm);

	switch(this->m_rally_string_ID) {
	case ID_DRAW_START:
		break;
	case ID_DRAW_FINISH:
		break;
	case ID_DRAW_HONOR:
		string_to_draw = "HONOR";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (new_height/2) - 10,string_to_draw);
		break;
	case ID_DRAW_SITHALT:
		string_to_draw = "SIT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string,new_bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_SITHALTDOWN:
		string_to_draw = "DOWN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string + 10,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
//		string_to_draw = "DOWN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;

	case ID_DRAW_HALTWALK:
		string_to_draw = "WALK";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string + 10,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "AROUND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;

	case ID_DRAW_DOWNWALK:
		string_to_draw = "DOWN WALK";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 15,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "AROUND DOG";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;
	case ID_DRAW_SLOWFORWARDFROMSIT:
		string_to_draw = "SLOW FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 15,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "FROM SIT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;

	case ID_DRAW_STANDWALK:
		string_to_draw = "STAND WALK";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 15,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "AROUND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;

	case ID_DRAW_DOWNSIT:
		string_to_draw = "DOWN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "SIT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string + 10 ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;
	case ID_DRAW_STAND:
		string_to_draw = "Stand";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		break;

	case ID_DRAW_STANDDOWN:
		string_to_draw = "STAND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "DOWN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;
	case ID_DRAW_STANDSIT:
		string_to_draw = "STAND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string,new_bottom - (tm.tmHeight * 2)- 5,string_to_draw);
		string_to_draw = "SIT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string + 10 ,new_bottom - tm.tmHeight- 5,string_to_draw);
		break;

// CHANGE PACE
		case ID_DRAW_NORMAL:
		string_to_draw = "NORMAL";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "PACE";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_FAST:
		string_to_draw = "FAST";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "PACE";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_SLOW:
		string_to_draw = "SLOW";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "PACE";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 10,new_bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_FAST_SIT:
		string_to_draw = "FAST";
		len = string_to_draw.GetLength();
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "FROM SIT";
		len = string_to_draw.GetLength();
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;

	case ID_DRAW_RT_TURN:
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2),new_bottom - tm.tmHeight * 2,string_to_draw);
		string_to_draw = "TURN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2),new_bottom - tm.tmHeight,string_to_draw);
		break;

	case ID_DRAW_ABOUT_RT:
		string_to_draw = "ABOUT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 20,new_top,string_to_draw);
		string_to_draw = "TURN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 5,new_top + tm.tmHeight,string_to_draw);
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_top + (tm.tmHeight*2),string_to_draw);
		break;

	case ID_ABOUT_FORWARD_RT:
		string_to_draw = "ABOUT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 20,new_top,string_to_draw);
		string_to_draw = "TURN RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_top + tm.tmHeight,string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_top + (tm.tmHeight*2),string_to_draw);
		break;
	case ID_DRAW_270_RT:
		string_to_draw = "270";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 20,new_top,string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 20, new_top, len,tm.tmAveCharWidth); 
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_top + tm.tmHeight,string_to_draw);
		break;

	case ID_DRAW_360_RT:
		string_to_draw = "360";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width/2)- half_string,new_top + (new_height/2) - tm.tmHeight,string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + (new_width/2)- half_string, new_top + (new_height/2) - tm.tmHeight, len,tm.tmAveCharWidth); 
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width/2)- half_string,new_top + (new_height/2),string_to_draw);
		break;
	case ID_DRAW_90_PIVOT_RT:
		string_to_draw = "90";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 10, new_bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
		string_to_draw = "PIVOT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_180_PIVOT_RT:
		string_to_draw = "180";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight*3),string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left, new_bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
		string_to_draw = "PIVOT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_1STEP_HEEL_RT:
		string_to_draw = "TURN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  +(new_width/2),new_top,string_to_draw);
		string_to_draw = "RIGHT 1 STEP";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "CALL TO HEEL";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight),string_to_draw);
		break;

// LEFT TURNS
	case ID_DRAW_LT_TURN:
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight * 2,string_to_draw);
		string_to_draw = "TURN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_ABOUT_LT:
			string_to_draw = "ABOUT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 20,new_top,string_to_draw);
		string_to_draw = "'U'";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_top + tm.tmHeight,string_to_draw);
		string_to_draw = "TURN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left,new_top + (tm.tmHeight*2),string_to_draw);
		break;
	case ID_DRAW_ABOUT_TURN_LT:
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left - 10,new_bottom - tm.tmHeight * 3,string_to_draw);
		string_to_draw = "ABOUT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left-10,new_bottom - tm.tmHeight * 2,string_to_draw);
		string_to_draw = "TURN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left-10,new_bottom - tm.tmHeight,string_to_draw);
		break;	
	case ID__DRAW_HALTLEFTFORWARD:
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left - 10,new_bottom - tm.tmHeight * 3,string_to_draw);
		string_to_draw = "Turn";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left-10,new_bottom - tm.tmHeight * 2,string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left-10,new_bottom - tm.tmHeight,string_to_draw);
		break;	
	case ID__DRAW_HALTRIGHTFORWARD:
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left - 10,new_bottom - tm.tmHeight * 3,string_to_draw);
		string_to_draw = "Turn";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left-10,new_bottom - tm.tmHeight * 2,string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left-10,new_bottom - tm.tmHeight,string_to_draw);
		break;	

	case ID_DRAW_U_FORWARD_LT:

		string_to_draw = "ABOUT      'U'";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left - 5,new_bottom - tm.tmHeight * 2,string_to_draw);
		string_to_draw = "TURN FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left- 5,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_270_LT:
		string_to_draw = "270";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 20,new_top,string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 20, new_top, len,tm.tmAveCharWidth); 
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_top + tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_360_LT:
		string_to_draw = "360";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width/2)- half_string,new_top + (new_height/2) - tm.tmHeight,string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + (new_width/2)- half_string, new_top + (new_height/2) - tm.tmHeight, len,tm.tmAveCharWidth); 
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width/2)- half_string,new_top + (new_height/2),string_to_draw);
		break;
	case ID_DRAW_90_PIVOT_LT:
		string_to_draw = "90";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 10, new_bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
		string_to_draw = "PIVOT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_HALTRIGHTPIVOTFORWARD:
		string_to_draw = "PIVOT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 10, new_bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_HALTLEFTPIVOTFORWARD:
		string_to_draw = "PIVOT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 10, new_bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_180_PIVOT_LT:
		string_to_draw = "180";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		this->DrawDegreeSymbol(pDC,new_left  + 10, new_bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
		string_to_draw = "PIVOT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
		//FINSIH STATIONS
	case ID_DRAW_FINISH_RT_FORWARD:
		string_to_draw = "CALL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len - 10,new_bottom - (tm.tmHeight*5),string_to_draw);
		string_to_draw = "FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len + 10,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "FINISH";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len + 8,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight *2),string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
		pDC->TextOut(new_right- len,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_FINISH_LEFT_FORWARD:
		string_to_draw = "CALL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len - 10,new_bottom - (tm.tmHeight*5),string_to_draw);
		string_to_draw = "FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len + 10,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "FINISH";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len + 8,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight *2),string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
		pDC->TextOut(new_right- len,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_FINISH_RT_HALT:
		string_to_draw = "CALL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "FINISH";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight *2),string_to_draw);
		string_to_draw = "RIGHT HALT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
		pDC->TextOut(new_right- len,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_FINISH_LT_HALT:
		string_to_draw = "CALL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "FINISH";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight *2),string_to_draw);
		string_to_draw = "LEFT HALT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
		pDC->TextOut(new_right- len,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_HALT_FINISH_RT:
		string_to_draw = "CALL FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "FINISH RIGHT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_HALT_FINISH_LT:
		string_to_draw = "CALL FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "FINISH LEFT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_FRONTHEEL:
		string_to_draw = "CALL FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "Return to Heel";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
// MOVE STATIONS
	case ID_DRAW_SIDE_RT:
		string_to_draw = "MOVING";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "SIDE";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "STEP";
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "RIGHT";
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_MOVE_DOWN:
		string_to_draw = "DOWN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 4),string_to_draw);
		string_to_draw = "AND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "STOP";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_MOVE_STAND_WALK:
		string_to_draw = "MOVING STAND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "WALK AROUND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "DOG";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight),string_to_draw);
		break;
	case ID__DRAW_MOVE_DOWN:
		string_to_draw = "MOVING DOWN";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "WALK AROUND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "DOG";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight),string_to_draw);
		break;
	case ID__DRAW_DOWNWHILEHEELING:
		string_to_draw = "Moving Stand";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "Leave dog 3 mtrs";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "Distance Down";
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "Return Around Dog";
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID__STAND_HEEL:
		string_to_draw = "STAND";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "WHILE HEELING";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(new_left  + (new_width / 2) - half_string - 15,new_bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID__DRAW_STAND_SIT_LEAVE:
		string_to_draw = "STAND";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "LEAVE DOG";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "SIT DOG";
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "CALL FRONT-FINISH";
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID__STAND_LEAVE_DOWN:
		string_to_draw = "STAND";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "LEAVE DOG 3 mtrs";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "Distance Down - Sit";
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "Return Around Dog";
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_JUMP:
		string_to_draw = "SEND";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 15 ,new_bottom - (tm.tmHeight*5),string_to_draw);
		string_to_draw = "OVER";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "JUMP";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "HANDLER";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "PASSES BY";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID__DRAW_DOUBLE_LEFT_TURN:
		string_to_draw = "DOUBLE";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "LEFT";
		pDC->TextOut(new_left ,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "ABOUT";
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight * 2),string_to_draw);
		string_to_draw = "TURN";
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID__DRAW_SENDTOJUMP:
		string_to_draw = "SEND TO JUMP";
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID__DRAW_SITSTAY:
		string_to_draw = "Moving Sit";
		pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "Walk Around";
		pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "dog";
		pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID__DRAW_CALLTOHEEL:
		string_to_draw = "360 Left";
		pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "Circle Spin";
		pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "At Heel";
		pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;

// HEEL STATIONS
	case ID_DRAW_HALT_3_STEPS_FOR:
		string_to_draw = "1 STEP";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 20 ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "2 STEPS";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "3 STEPS";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		break;
	case ID_DRAW_FRONT_3_STEPS_BACK:
		string_to_draw = "FRONT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 35 ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "1 BACK";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "2 BACK";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "3 BACK";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_SIDE_RIGHT:
		string_to_draw = "SIDE STEP";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left,new_bottom - tm.tmHeight,string_to_draw);
		break;		
	case ID_DRAW_BACKUP_3:
		string_to_draw = "BACKUP 3";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "STEPS DOG";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "STAYS IN";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "POSITION";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID__DRAW_2_STEPS_FORWARD:
		string_to_draw = "LEAVE DOG";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_right - len - 10,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "2 STEPS";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "CALL TO HEEL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
		pDC->TextOut(new_right - len + 8,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
		pDC->TextOut(new_right - len,new_bottom - (tm.tmHeight),string_to_draw);
		break;

// WEAVE STATIONS
	case ID_DRAW_SERP_ONCE:
		string_to_draw = "SERPENTINE";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 5,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "WEAVE ONCE";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 5,new_bottom - (tm.tmHeight*2),string_to_draw);
		break;
	case ID_WEAVES_FIGURE8:
		string_to_draw = "Four Cone";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 5,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "Figure 8";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 5,new_bottom - (tm.tmHeight*2),string_to_draw);
		break;
	case ID_DRAW_WEAVE_TWICE:
		string_to_draw = "STRAIGHT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10 ,new_top + 10,string_to_draw);
		string_to_draw = "FIGURE 8";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 2,new_top + tm.tmHeight + 10,string_to_draw);
		string_to_draw = "WEAVE TWICE";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 2,new_top + (tm.tmHeight*2) + 10,string_to_draw);
		break;
	case ID_DRAW_OFFSET_8:
		string_to_draw = "OFF-SET";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 5 ,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "FIGURE 8";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_SPIRAL_RIGHT:
		string_to_draw = "SPIRAL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 45 ,new_bottom - (tm.tmHeight*5),string_to_draw);
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 50,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "DOG OUTSIDE";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 5,new_bottom - tm.tmHeight,string_to_draw);
		break;
	case ID_DRAW_SPIRAL_LEFT:
		string_to_draw = "SPIRAL";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10 ,new_bottom - (tm.tmHeight*4),string_to_draw);
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - (tm.tmHeight*3),string_to_draw);
		string_to_draw = "DOG";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - (tm.tmHeight*2),string_to_draw);
		string_to_draw = "INSIDE";
		len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
		pDC->TextOut(new_left + 10,new_bottom - tm.tmHeight,string_to_draw);
		break;
	}


}
void CRallyObject::DrawStationForScoreSheet(CDC* pDC, CPoint top_left) {
	CBitmap bmp,*pOldBmp;
	CRect temp_rect;
	BOOL flg=0;
	CPalette pal;
	LOGPALETTE *pLp;

	if(pDC==NULL)
	{
		AfxMessageBox("No DC provided.");
		return;
	}
	

	CDC memdc;
	
	memdc.CreateCompatibleDC(pDC);
	if (this->m_rally_station_ID == ID_DRAW_START || this->m_rally_station_ID == ID_DRAW_FINISH) return;

	bmp.LoadBitmap(this->m_rally_station_ID);

	pOldBmp = (CBitmap*)memdc.SelectObject(bmp);	// always select object into the window mem DC

	if(pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		int nSize;
		nSize=sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256;
		pLp=(LOGPALETTE*) new BYTE[nSize];
		pLp->palVersion=0x300;
		pLp->palNumEntries=256;
		GetSystemPaletteEntries(pDC->m_hDC,0,256,pLp->palPalEntry);
		pal.CreatePalette(pLp);
		delete [] pLp;
	}
	
	/////////////////////////***
	memdc.SelectObject(pOldBmp);
	HANDLE hDIB=DDBToDIB(bmp,BI_RGB,&pal);
	if(hDIB==NULL) return;
	BITMAPINFOHEADER    *pBMI ;
	pBMI = (BITMAPINFOHEADER*)GlobalLock(hDIB) ;
	int nColors = 0;
	if (pBMI->biBitCount <= 8) {
		nColors = (1 << pBMI->biBitCount);
	}
		::StretchDIBits(pDC->m_hDC,
							top_left.x, 
							top_left.y, 
							this->m_width * 3, 
							this->m_height * 3,
							0, 
							0, 
							this->m_width,
							this->m_height,
							(LPBYTE)pBMI + (pBMI->biSize + nColors * sizeof(RGBQUAD)),
							(BITMAPINFO*)pBMI,
							DIB_RGB_COLORS, 
							SRCAND);
    GlobalUnlock(hDIB) ;
    GlobalFree(hDIB) ;

}
int CRallyObject::DrawSelectedStation(CDC* pDC, int stat_num_loc, BOOL advanced_mode, int where_cones, BOOL rotating, BOOL printing){
	// Get the size of the bitmap
	RECT handle_rect;
	BOOL draw;
	CEnBitmap hImage;
	CBitmap rotate_image, resize_image;
	CBitmap *pOldBitmap;
	CDC memDC; 
	CPen penBlack;
	CPen penBlue;
	int draw_error = NO_DRAW_ERROR;
	BITMAP bmpInfo;

	int last_mode = 0;
	CBrush br1, *pbrOld;
	br1.CreateSolidBrush(RGB(255,255,255));
	pbrOld = pDC->SelectObject(&br1);
	this->m_where_cones = where_cones;

	CPen* pOldPen;
	error_string.Empty();

	if (hImage.LoadBitmap(this->m_rally_station_ID)) {

		hImage.GetBitmap(&bmpInfo);

		pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC

		RECT outline_rect = this->m_station_rect;

// make the outline
		InflateRect(&outline_rect,1,1);

   // create and select a black pen



		if(this->m_selected && !printing) {// draw a solid rect if selected
			penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		}
		else { // or a dashed if not
			penBlack.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		}
		pOldPen = pDC->SelectObject(&penBlack);

		pDC->Rectangle(&outline_rect);
		pDC->SelectObject(pOldPen);
		DeleteObject(penBlack);

		// now rect back
		InflateRect(&outline_rect,-1,-1);



		if(pDC->GetDeviceCaps(RASTERCAPS) & RC_STRETCHBLT == 0) {
			MessageBox(NULL,"DEVICE DOES NOT SUPPORT BITBLTS",NULL,MB_OK);
			draw_error = NO_STRECHBLT;
			error_string = "DEVICE DOES NOT SUPPORT BITBLTS";
			return draw_error;
		}
			

		memDC.CreateCompatibleDC(pDC); // dc for window 
		if (advanced_mode) last_mode = SetGraphicsMode (pDC->m_hDC, GM_ADVANCED);

		if (!last_mode && advanced_mode) {			
			draw_error += NO_GRAPHICS_MODE;
			error_string += "DEVICE DOES NOT SUPPORT ADVANCED MODE";
		}

		if (!draw_error && last_mode) {

			pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
			if (this->m_rally_station_ID == IDB_FIG8_TWICE) {
				int testing = 1;
			}
			if (this->m_stat_desc != PIC_ONLY && !this->m_do_rotate_text) {
				this->DrawStringForStation(pDC);
			}

			POINT lpPoint[3];

			XFORM  x;
			POINT pivot;

			pivot.x = m_station_rect.left + (this->m_width/2); 
			pivot.y = m_station_rect.top + (this->m_height/2); 
			
			// top left
			lpPoint[0].x = m_station_rect.left;		
			lpPoint[0].y = m_station_rect.top;		
			// top right
			lpPoint[1].x = m_station_rect.right;		
			lpPoint[1].y = m_station_rect.top;		
			// bottom left
			lpPoint[2].x = m_station_rect.left;		
			lpPoint[2].y = m_station_rect.bottom;		

			x.eM11 = (float)1.0;
			x.eM12 = (float)0.0;
			x.eM21 = (float)0.0;
			x.eM22 = (float)1.0;
			x.eDx = (float)-pivot.x;
			x.eDy = (float)-pivot.y;
			draw = ModifyWorldTransform (pDC->m_hDC, &x, MWT_RIGHTMULTIPLY);
			if (!draw) 
				draw_error += NO_WORLD_TRANS;

			/* rotate object about origin. */
			x.eM11 = m_M11;
			x.eM12 = m_M12;
			x.eM21 = m_M21;
			x.eM22 = m_M22;
			x.eDx = (float)0.0;
			x.eDy = (float)0.0;
			draw = ModifyWorldTransform (pDC->m_hDC, &x, MWT_RIGHTMULTIPLY);


			/* translate objects back to pivot point. */
			x.eM11 = (float)1.0;
			x.eM12 = (float)0.0;
			x.eM21 = (float)0.0;
			x.eM22 = (float)1.0;
			x.eDx = (float)pivot.x;
			x.eDy = (float)pivot.y;
			draw = ModifyWorldTransform (pDC->m_hDC, &x, MWT_RIGHTMULTIPLY);
			if (this->m_stat_desc != PIC_ONLY && this->m_do_rotate_text) {
				this->DrawStringForStation(pDC);
			}

			if (!rotating)
				this->DrawStationPylons(pDC, true, where_cones);

//			draw = pDC->BitBlt(outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
//				&memDC, 0, 0, SRCAND);
			if (this->m_stat_desc != TEXT_ONLY) {
				draw = pDC->StretchBlt (outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
					&memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCAND);
			}

			if (!draw) {
				// it is trying to update the window behind, not all the time? why?
//				error_string.Format("ERROR: Did not print station number %d?",this->m_station_num);
	//			TRACE0(error_string);
				DWORD error = GetLastError();
	//			MessageBox(NULL,error_string,NULL,MB_OK);
				error_string += "DID NOT BITBLT STATION";

			}
			
			ModifyWorldTransform (pDC->m_hDC, &x, MWT_IDENTITY);
	//		memDC.SelectObject(pOldBitmap);
		}
		else {
			CBitmap bmp,*pOldBmp;
			if (this->m_stat_desc != PIC_ONLY) {
				this->DrawStringForStation(pDC);
			}

			bmp.CreateCompatibleBitmap(pDC,this->m_width + 20,this->m_height+ 20);
			pOldBmp=memDC.SelectObject(&bmp);
			memDC.PatBlt(0,0, this->m_width + 20, this->m_height + 20, WHITENESS);

			hImage.RotateImage(this->m_rotate_text,FALSE);	
			pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
			if (this->m_stat_desc != TEXT_ONLY) {
				switch(this->m_rotate_text) {
				case 0:
				case 180:
					draw = pDC->StretchBlt (outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
						&memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCAND);
	//				draw = pDC->BitBlt(outline_rect.left , outline_rect.top, this->m_width, this->m_height, 
	//				&memDC, 0, 0, SRCAND);
					break;
				case 90:
				case 270:
					draw = pDC->StretchBlt (outline_rect.left+ this->m_width/8 , outline_rect.top - (this->m_height/6), this->m_height, this->m_width, 
						&memDC, 0, 0, bmpInfo.bmHeight, bmpInfo.bmWidth, SRCAND);
	//				draw = pDC->BitBlt(outline_rect.left + this->m_width/8, outline_rect.top - (this->m_height/6), this->m_height, this->m_width, 
	//				&memDC, 0, 0, SRCAND);
					break;
				}
			}
			this->DrawStationPylons(pDC, false, where_cones);


			if (!draw) {
				// it is trying to update the window behind, not all the time? why?
				error_string.Format("ERROR: Did not print station number %d?",this->m_station_num);
	//			TRACE0(error_string);
				DWORD error = GetLastError();
//				MessageBox(NULL,error_string,NULL,MB_OK);
				error_string += "DID NOT BITBLT STATION";

			}
		}
		

		if (this->m_station_num > START_STATION && stat_num_loc != NUM_HIDE) {
			this->DrawStationNumber(pDC, stat_num_loc);
		}

		if (this->m_selected && !printing && last_mode) {
			if (rotate_image.LoadBitmap(IDB_ROTATE)) {
				pOldBitmap = (CBitmap*)memDC.SelectObject(rotate_image);	// always select object into the window mem DC
				rotate_image.GetBitmap(&bmpInfo);

				this->GetHandleRect(TOP_RIGHT,&handle_rect);
				draw = pDC->BitBlt(handle_rect.left , handle_rect.top, bmpInfo.bmWidth, bmpInfo.bmHeight ,&memDC, 0, 0, SRCAND);
 
			}
			else {
				COLORREF old_background = pDC->GetBkColor();
				this->GetHandleRect(TOP_RIGHT,&handle_rect);
				pDC->FillSolidRect(&handle_rect,0);
				pDC->SetBkColor(old_background);
			}

		}
		if (this->m_selected && !printing) {
			if (resize_image.LoadBitmap(IDB_RESIZE)) {
				pOldBitmap = (CBitmap*)memDC.SelectObject(resize_image);	// always select object into the window mem DC
				resize_image.GetBitmap(&bmpInfo);

				this->GetHandleRect(BOTTOM_RIGHT,&handle_rect);
				draw = pDC->BitBlt(handle_rect.left , handle_rect.top, bmpInfo.bmWidth, bmpInfo.bmHeight ,&memDC, 0, 0, SRCAND);

			}
		}
		
		
		if (last_mode)SetGraphicsMode (pDC->m_hDC, last_mode);
	}
	else {
		error_string.Format("ERROR: Where's %d?",this->m_rally_station_ID);
		TRACE0(error_string);
	}
	pDC->SelectObject(pbrOld);

	return draw_error;
}

void CRallyObject::DrawStationStats(CDC *pDC) {
	CString stat_text;
	TEXTMETRIC tm;
	double arc_sine, arc_cosine;
	double sine_degrees, cos_degrees;
	double pi = 3.1415926535;
	stat_text.Format("x:%d  y:%d",this->m_pylon_exit.x,this->m_pylon_exit.y);
	pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom,stat_text);

	pDC->GetTextMetrics(&tm);
	stat_text.Format("Top:%d  Left:%d",this->m_station_rect.top,this->m_station_rect.left);
	pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom,stat_text);
	stat_text.Format("cosine:%f   sine:%f",this->m_M11, this->m_M12);
	pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom + tm.tmHeight ,stat_text);
	arc_cosine = acos(this->m_M11);
	arc_sine = asin(this->m_M12);
	stat_text.Format("arccos:%f   arcsine:%f",arc_cosine, arc_sine);
	pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom + tm.tmHeight * 2 ,stat_text);
	sine_degrees = (arc_sine * 180) / pi;
	cos_degrees = (arc_cosine * 180)/ pi;
	stat_text.Format("cos degrees:%f sine degees:%f calc degrees:%f",cos_degrees, sine_degrees, this->m_rotate_degrees);
	pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom + tm.tmHeight * 3,stat_text);


}

void CRallyObject::DrawStationNumber(CDC *pDC, int stat_num_loc) {
	CString station_number;
	switch (stat_num_loc) {
	case NUM_TOP_LEFT:
		pDC->Ellipse(this->m_station_rect.left- 15, this->m_station_rect.top - 15, this->m_station_rect.left + 15, this->m_station_rect.top + 15);
		station_number.Format("%d",this->m_station_num);
		if (this->m_station_num < 10) {
			pDC->TextOut(this->m_station_rect.left- 5,this->m_station_rect.top - 8,station_number);
		}
		else {
			pDC->TextOut(this->m_station_rect.left- 8,this->m_station_rect.top - 8,station_number);
		}
	break;
	case NUM_BOTTOM_LEFT:
		pDC->Ellipse(this->m_station_rect.left- 15, this->m_station_rect.bottom + 15, this->m_station_rect.left + 15, this->m_station_rect.bottom - 15);
		station_number.Format("%d",this->m_station_num);
		if (this->m_station_num < 10) {
			pDC->TextOut(this->m_station_rect.left- 5,this->m_station_rect.bottom - 8,station_number);
		}
		else {
			pDC->TextOut(this->m_station_rect.left- 8,this->m_station_rect.bottom - 8,station_number);
		}
	break;
	case NUM_ENTER:
		pDC->Ellipse(this->m_entrance.x - 15, this->m_entrance.y - 15, this->m_entrance.x + 15, this->m_entrance.y + 15);
		station_number.Format("%d",this->m_station_num);
		if (this->m_station_num < 10) {
			pDC->TextOut(this->m_entrance.x- 5,this->m_entrance.y - 8,station_number);
		}
		else {
			pDC->TextOut(this->m_entrance.x- 8,this->m_entrance.y - 8,station_number);
		}
	break;
	case NUM_EXIT:
		pDC->Ellipse(this->m_exit.x - 15, this->m_exit.y - 15, this->m_exit.x + 15, this->m_exit.y + 15);
		station_number.Format("%d",this->m_station_num);
		if (this->m_station_num < 10) {
			pDC->TextOut(this->m_exit.x- 5,this->m_exit.y - 8,station_number);
		}
		else {
			pDC->TextOut(this->m_exit.x- 8,this->m_exit.y - 8,station_number);
		}
	break;
	case NUM_TOP_RIGHT:
		pDC->Ellipse(this->m_station_rect.right - 15, this->m_station_rect.top - 15, this->m_station_rect.right + 15, this->m_station_rect.top + 15);
		station_number.Format("%d",this->m_station_num);
		if (this->m_station_num < 10) {
			pDC->TextOut(this->m_station_rect.right- 5,this->m_station_rect.top - 8,station_number);
		}
		else {
			pDC->TextOut(this->m_station_rect.right- 8,this->m_station_rect.top - 8,station_number);
		}
	break;
	case NUM_BOTTOM_RIGHT:
		pDC->Ellipse(this->m_station_rect.right- 15, this->m_station_rect.bottom + 15, this->m_station_rect.right + 15, this->m_station_rect.bottom - 15);
		station_number.Format("%d",this->m_station_num);
		if (this->m_station_num < 10) {
			pDC->TextOut(this->m_station_rect.right- 5,this->m_station_rect.bottom - 8,station_number);
		}
		else {
			pDC->TextOut(this->m_station_rect.right- 8,this->m_station_rect.bottom - 8,station_number);
		}
	break;
	}
	
}

void CRallyObject::DrawStationPylons(CDC* pDC, BOOL with_transform, int where_cones) {
	CBitmap hImage;
	CBitmap *pOldBitmap;
	CDC memDC;
	double shift, sec_shift;
	BOOL load_bitmap;
	BOOL draw;
	CRect pylon_rect;

	BITMAP bmpInfo;

	m_has_pylons = true;
	if (with_transform) {
		switch(this->m_rally_string_ID) {
		case ID_DRAW_OFFSET_8:
		case ID_WEAVES_FIGURE8:
					/*
			if (where_cones != CONE_HIDE) {
				load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
				if (load_bitmap) {
					shift = (double)this->m_width* 1.5/2.0;

					hImage.GetBitmap(&bmpInfo);
		

					memDC.CreateCompatibleDC(pDC); // dc for window 

					pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
					switch(where_cones) {
					case CONE_ENTRANCE:
						draw = pDC->BitBlt(this->m_station_rect.right + (int)shift + bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCAND);
						draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y , bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCAND);

						pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
						pDC->LineTo(this->m_station_rect.right + (int)shift + bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y);
						pDC->LineTo(this->m_station_rect.right + (int)shift + bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
						break;
					case CONE_EXIT:
						draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCAND);
						draw = pDC->BitBlt(this->m_station_rect.left - (int)shift - bmpInfo.bmWidth, this->m_midPoint.y , bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCAND);

						pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
						pDC->LineTo(this->m_station_rect.left - (int)shift - bmpInfo.bmWidth/2 - bmpInfo.bmWidth,this->m_midPoint.y);
						pDC->LineTo(this->m_station_rect.left - (int)shift - bmpInfo.bmWidth/2 - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
						m_pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left - (int)shift - bmpInfo.bmWidth/2 - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						break;
					case CONE_MIDDLE:
						draw = pDC->BitBlt(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCAND);
						draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y , bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCAND);

						pDC->MoveTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
						m_pylon_rect.SetRect(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y,this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);

						break;
					}

					draw = pDC->BitBlt(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCAND);
					draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y , bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCAND);

					pDC->MoveTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y);

				}
			}
					*/
			break;

		case ID_DRAW_SERP_ONCE:
		case ID_DRAW_WEAVE_TWICE:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {

				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 
				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				shift = (double)this->m_width* 1.5/2.0;
				sec_shift = (double)this->m_height* 1.5;
				switch(where_cones) {
				case CONE_ENTRANCE:
					shift += bmpInfo.bmWidth;
					draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift + bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift + (int)shift + bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift + (int)shift + (int)shift + bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);

					pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.right + (int)shift + (int)shift + (int)shift + bmpInfo.bmWidth + bmpInfo.bmWidth/2,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.right + (int)shift + (int)shift + (int)shift + bmpInfo.bmWidth + bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y, this->m_station_rect.right + (int)shift + (int)shift + (int)shift + bmpInfo.bmWidth + bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				case CONE_EXIT:
					shift += bmpInfo.bmWidth;
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - (int)shift - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - (int)shift - (int)shift - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - (int)shift - (int)shift - (int)shift - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);

					pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.left  - (int)shift - (int)shift - (int)shift - bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.left  - (int)shift - (int)shift - (int)shift - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left  - (int)shift - (int)shift - (int)shift - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				case CONE_MIDDLE:
					draw = pDC->BitBlt(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);

					pDC->MoveTo(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2, this->m_midPoint.y,this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
				}
			}
			pylon_rect.NormalizeRect();
			this->CalculatePylonEntryAndExitPoints(&pylon_rect, where_cones);					

			break;
		
		case ID_DRAW_SPIRAL_RIGHT:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {

				shift = (double)this->m_width* 1.5;

				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 
				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				switch(where_cones) {
				case CONE_ENTRANCE:	
					draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);	

					pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.right + (int)shift + (int)shift  + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.right + (int)shift + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y,this->m_station_rect.right + (int)shift + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				case CONE_EXIT:
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);	

					pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left - (int)shift- (int)shift - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				case CONE_MIDDLE:
					draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);	

					pDC->MoveTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_midPoint.x - (int)shift,this->m_midPoint.y,this->m_midPoint.x + (int)shift + (2*bmpInfo.bmWidth),this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				}

			}
			pylon_rect.NormalizeRect();
			this->CalculatePylonEntryAndExitPoints(&pylon_rect, where_cones);					
			break;
		case ID_DRAW_SPIRAL_LEFT:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {

				shift = (double)this->m_width* 1.5;

				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 
				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				switch(where_cones) {
				case CONE_EXIT:	
					draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.right + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);	

					pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.right + (int)shift + (int)shift  + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.right + (int)shift + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y,this->m_station_rect.right + (int)shift + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				case CONE_ENTRANCE:
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);	

					pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left - (int)shift- (int)shift - bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				case CONE_MIDDLE:
					draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);
					draw = pDC->BitBlt(this->m_midPoint.x - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCCOPY);	

					pDC->MoveTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
					pylon_rect.SetRect(this->m_midPoint.x - (int)shift,this->m_midPoint.y,this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
				}

			}
			pylon_rect.NormalizeRect();
			this->CalculatePylonEntryAndExitPoints(&pylon_rect, where_cones);					
			break;
		default:
			m_has_pylons = false;
			return;
			break;
		}
	}
	else { // no free hand rotation

		switch(this->m_rally_string_ID) {
/*
		case ID_DRAW_OFFSET_8:
		case ID_WEAVES_FIGURE8:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {
				shift = (double)this->m_width* 1.5/2.0;
				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 

				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				// cone middle
				switch(this->m_rotate_text) {
				case 0:
				case 180:
					draw = pDC->BitBlt(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCAND);
					draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y , bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCAND);

					pDC->MoveTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y);
					pDC->LineTo(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight);
					pDC->LineTo(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
					break;
				case 90:
				case 270:
					draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y + (int)shift - bmpInfo.bmWidth/2, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCAND);
					draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y  - (int)shift - bmpInfo.bmWidth/2, bmpInfo.bmWidth, bmpInfo.bmHeight, 
						&memDC, 0, 0, SRCAND);

					pDC->MoveTo(this->m_midPoint.x,this->m_midPoint.y - (int)shift - bmpInfo.bmWidth/2);
					pDC->LineTo(this->m_midPoint.x,this->m_midPoint.y + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth);
					pDC->LineTo(this->m_midPoint.x + bmpInfo.bmHeight,this->m_midPoint.y  + (int)shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth);
					pDC->LineTo(this->m_midPoint.x  + bmpInfo.bmHeight,this->m_midPoint.y  - (int)shift - bmpInfo.bmWidth/2);
					pDC->LineTo(this->m_midPoint.x,this->m_midPoint.y - (int)shift - bmpInfo.bmWidth/2);
					break;
				}
			}
			break;
*/
		case ID_DRAW_SERP_ONCE:
		case ID_DRAW_WEAVE_TWICE:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {


				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 
				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				shift = (double)this->m_width* 1.5/2.0;
				sec_shift = (double)this->m_height* 1.5;
				// cone middle
				switch(where_cones) {
				case CONE_MIDDLE:

					switch(this->m_rotate_text) {
					case 0:
					case 180:
						draw = pDC->BitBlt(this->m_midPoint.x + (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);

						pDC->MoveTo(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y);
						break;
					case 90:
					case 270:
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y + (int)shift - bmpInfo.bmWidth/2, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y - (int)shift - bmpInfo.bmWidth/2, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);

						pDC->MoveTo(this->m_midPoint.x,this->m_midPoint.y - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2);
						pDC->LineTo(this->m_midPoint.x,this->m_midPoint.y + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth);
						pDC->LineTo(this->m_midPoint.x  + bmpInfo.bmHeight,this->m_midPoint.y + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth);
						pDC->LineTo(this->m_midPoint.x + bmpInfo.bmHeight,this->m_midPoint.y  - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2);
						pDC->LineTo(this->m_midPoint.x ,this->m_midPoint.y- (int)shift - (int)sec_shift - bmpInfo.bmWidth/2);
						break;
					} // end switch rotatetext for cone_middle
					pylon_rect.SetRect(this->m_midPoint.x - (int)shift - (int)sec_shift - bmpInfo.bmWidth/2,this->m_midPoint.y,this->m_midPoint.x + (int)shift + (int)sec_shift - bmpInfo.bmWidth/2 + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 

					break;
					case CONE_EXIT:
						switch(this->m_rotate_text) {
						case 0:
							draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (2*bmpInfo.bmWidth) - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_station_rect.left - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (4*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (4*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
							break;
						case 180:
							draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + bmpInfo.bmWidth + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
							break;
						case 90:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - bmpInfo.bmWidth, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (2*bmpInfo.bmWidth) - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top);
							break;
						case 270:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (1*bmpInfo.bmWidth) + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (3*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom);
							break;
						}// end switch rotatetext for cone_exit
						pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left - (int)shift- (int)shift - (4*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight); 
						break;
					case CONE_ENTRANCE:
						switch(this->m_rotate_text) {
						case 0:
							draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + bmpInfo.bmWidth + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
							break;
						case 180:
							draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (2*bmpInfo.bmWidth) - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_station_rect.left - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (4*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (4*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
							break;
						case 270:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - bmpInfo.bmWidth, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (2*bmpInfo.bmWidth) - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top - (4*bmpInfo.bmWidth) - (int)shift- (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top);
							break;
						case 90:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (1*bmpInfo.bmWidth) + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (3*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom);
							break;
					}// end switch rotatetext for cone_entrance
					pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y,this->m_station_rect.right + (4*bmpInfo.bmWidth) + (int)shift + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight); 
	
				} // end switch for where_cones
			}//end if load bitmap
			pylon_rect.NormalizeRect();
			this->CalculatePylonEntryAndExitPoints(&pylon_rect, where_cones);					

			break;
		
		case ID_DRAW_SPIRAL_RIGHT:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {

//				shift = (double)this->m_width* 1.5;
				shift = (double)this->m_width* 1.5/2.0;
				sec_shift = (double)this->m_height* 1.5;
		
				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 
				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				switch(where_cones) {
				case CONE_MIDDLE:

					switch(this->m_rotate_text) {
					case 0:
					case 180:
						shift = (double)this->m_width* 1.5;
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);	

						pDC->MoveTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
						pylon_rect.SetRect(this->m_midPoint.x - (int)shift,this->m_midPoint.y,this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
						break;
					case 90:
					case 270:
						shift = (double)this->m_width* 1.5;
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);	

						pDC->MoveTo(this->m_midPoint.x,this->m_midPoint.y - (int)shift);
						pDC->LineTo(this->m_midPoint.x,this->m_midPoint.y + (int)shift + bmpInfo.bmWidth);
						pDC->LineTo(this->m_midPoint.x + bmpInfo.bmHeight,this->m_midPoint.y + (int)shift + bmpInfo.bmWidth);
						pDC->LineTo(this->m_midPoint.x + bmpInfo.bmHeight ,this->m_midPoint.y - (int)shift);
						pDC->LineTo(this->m_midPoint.x ,this->m_midPoint.y - (int)shift);		
						pylon_rect.SetRect(this->m_midPoint.x - (int)shift,this->m_midPoint.y,this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
						break;
					} // end switch rotatetext for cone_middle
					break;
					case CONE_EXIT:
						switch(this->m_rotate_text) {
						case 0:
							draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (2*bmpInfo.bmWidth) - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (3*bmpInfo.bmWidth),this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (3*bmpInfo.bmWidth),this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
							break;
						case 180:
							draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + bmpInfo.bmWidth + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
							pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y,this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight); 
							break;
						case 90:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - bmpInfo.bmWidth, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (2*bmpInfo.bmWidth) - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top);
							break;
						case 270:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (1*bmpInfo.bmWidth) + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom);
							break;
						}// end switch rotatetext for cone_exit
						pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left - (int)shift- (int)shift - (3*bmpInfo.bmWidth),this->m_midPoint.y + bmpInfo.bmHeight); 

						break;
					case CONE_ENTRANCE:
						switch(this->m_rotate_text) {
						case 0:
							draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + bmpInfo.bmWidth + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
							break;
						case 180:
							draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (2*bmpInfo.bmWidth) - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift - (3*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift - (3*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
							break;
						case 270:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - bmpInfo.bmWidth, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (2*bmpInfo.bmWidth) - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top);
							break;
						case 90:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (1*bmpInfo.bmWidth) + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom + (3*bmpInfo.bmWidth) + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom);
							break;

						}// end switch rotatetext for cone_entrance
					pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y,this->m_station_rect.right + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight); 

				} // end switch for where_cones

			}// end if load_bitmap plyon
			pylon_rect.NormalizeRect();
			this->CalculatePylonEntryAndExitPoints(&pylon_rect, where_cones);					

			break;
		case ID_DRAW_SPIRAL_LEFT:
			load_bitmap = hImage.LoadBitmap(IDB_PYLONS);
			if (load_bitmap) {

//				shift = (double)this->m_width* 1.5;
				shift = (double)this->m_width* 1.5/2.0;
				sec_shift = (double)this->m_height* 1.5;

				hImage.GetBitmap(&bmpInfo);
				memDC.CreateCompatibleDC(pDC); // dc for window 
				pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
				switch(where_cones) {
				case CONE_MIDDLE:

					switch(this->m_rotate_text) {
					case 0:
					case 180:
						shift = (double)this->m_width* 1.5;
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);	

						pDC->MoveTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y);
						pDC->LineTo(this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
						pDC->LineTo(this->m_midPoint.x - (int)shift,this->m_midPoint.y);
						break;
					case 90:
					case 270:
						shift = (double)this->m_width* 1.5;
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);
						draw = pDC->BitBlt(this->m_midPoint.x, this->m_midPoint.y - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
							&memDC, 0, 0, SRCCOPY);	

						pDC->MoveTo(this->m_midPoint.x,this->m_midPoint.y - (int)shift);
						pDC->LineTo(this->m_midPoint.x,this->m_midPoint.y + (int)shift + bmpInfo.bmWidth);
						pDC->LineTo(this->m_midPoint.x + bmpInfo.bmHeight,this->m_midPoint.y + (int)shift + bmpInfo.bmWidth);
						pDC->LineTo(this->m_midPoint.x + bmpInfo.bmHeight ,this->m_midPoint.y - (int)shift);
						pDC->LineTo(this->m_midPoint.x ,this->m_midPoint.y - (int)shift);		
						break;
					} // end switch rotatetext for cone_middle
					pylon_rect.SetRect(this->m_midPoint.x - (int)shift,this->m_midPoint.y,this->m_midPoint.x + (int)shift + bmpInfo.bmWidth,this->m_midPoint.y + bmpInfo.bmHeight); 
					break;
					case CONE_EXIT:
						switch(this->m_rotate_text) {
						case 180:
							draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (2*bmpInfo.bmWidth) - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (3*bmpInfo.bmWidth),this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift- (int)shift - (3*bmpInfo.bmWidth),this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
							break;
						case 0:
							draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + bmpInfo.bmWidth + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
							break;
						case 270:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - bmpInfo.bmWidth, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (2*bmpInfo.bmWidth) - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top);
							break;
						case 90:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (1*bmpInfo.bmWidth) + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom);
							break;
						}// end switch rotatetext for cone_exit
						pylon_rect.SetRect(this->m_station_rect.right,this->m_midPoint.y,this->m_station_rect.right + (3*bmpInfo.bmWidth) + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight); 
						break;
					case CONE_ENTRANCE:
						switch(this->m_rotate_text) {
						case 180:
							draw = pDC->BitBlt(this->m_station_rect.right, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + bmpInfo.bmWidth + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.right + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.right,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.right + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.right,this->m_midPoint.y);
							break;
						case 0:
							draw = pDC->BitBlt(this->m_station_rect.left - bmpInfo.bmWidth, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (2*bmpInfo.bmWidth) - (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_station_rect.left - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, this->m_midPoint.y, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_station_rect.left,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift - (3*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y);
							pDC->LineTo(this->m_station_rect.left - (int)shift - (3*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y + bmpInfo.bmHeight);
							pDC->LineTo(this->m_station_rect.left,this->m_midPoint.y);
							break;
						case 90:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - bmpInfo.bmWidth, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (2*bmpInfo.bmWidth) - (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift- (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top - (3*bmpInfo.bmWidth) - (int)shift - (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.top);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.top);
							break;
						case 270:
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (1*bmpInfo.bmWidth) + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);
							draw = pDC->BitBlt(this->m_midPoint.x, this->m_station_rect.bottom + (2*bmpInfo.bmWidth) + (int)shift + (int)shift, bmpInfo.bmWidth, bmpInfo.bmHeight, 
								&memDC, 0, 0, SRCCOPY);	

							pDC->MoveTo(this->m_midPoint.x,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom + (3*bmpInfo.bmWidth)  + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom + (3*bmpInfo.bmWidth) + (int)shift + (int)shift);
							pDC->LineTo(this->m_midPoint.x + bmpInfo.bmWidth,this->m_station_rect.bottom);
							pDC->LineTo(this->m_midPoint.x,this->m_station_rect.bottom);
						break;
					}// end switch rotatetext for cone_entrance
					pylon_rect.SetRect(this->m_station_rect.left,this->m_midPoint.y,this->m_station_rect.left - (int)shift - (3*bmpInfo.bmWidth) - (int)shift,this->m_midPoint.y + bmpInfo.bmHeight); 

				} // 
			}
			pylon_rect.NormalizeRect();
			this->CalculatePylonEntryAndExitPoints(&pylon_rect, where_cones);					

			break;
		default:
			m_has_pylons = false;
			return;
			break;
		}	
	
	
	}


}

/*
void CRallyObject::DrawExitArrow(CDC* pDC) {
	CBitmap hImage;
	CBitmap bmpMask, *pOldBitmap;
	CDC memDC; 
	BOOL load_bitmap;
	
	switch(this->m_rally_string_ID) {
// top exits
	case ID_DRAW_START:
	case ID_DRAW_SITHALT:
	case ID_DRAW_SITHALTDOWN:
	case ID_DRAW_HALTWALK:
	case ID_DRAW_DOWNWALK:
	case ID_DRAW_STANDWALK:
	case ID_DRAW_DOWNSIT:
	case ID_DRAW_STANDDOWN:
	case ID_DRAW_STANDSIT:
	case ID_DRAW_NORMAL:
	case ID_DRAW_FAST:
	case ID_DRAW_SLOW:
	case ID_DRAW_FAST_SIT:
	case ID_DRAW_360_RT:
	case ID_DRAW_360_LT:
	case ID_DRAW_FINISH_RT_FORWARD:
	case ID_DRAW_FINISH_LEFT_FORWARD:
	case ID_DRAW_FINISH_RT_HALT:
	case ID_DRAW_FINISH_LT_HALT:
	case ID_DRAW_HALT_FINISH_RT:
	case ID_DRAW_HALT_FINISH_LT:
	case ID_DRAW_SIDE_RT:
	case ID_DRAW_MOVE_DOWN:
	case ID_DRAW_MOVE_STAND_WALK:
	case ID_DRAW_JUMP:
	case ID_DRAW_BACKUP_3:
	case ID_DRAW_HALT_3_STEPS_FOR:
	case ID_DRAW_FRONT_3_STEPS_BACK:
	case ID_DRAW_SIDE_RIGHT:
	case ID_DRAW_SERP_ONCE:
	case ID_DRAW_WEAVE_TWICE:
	case ID_DRAW_OFFSET_8:
	case ID_DRAW_SPIRAL_RIGHT:
	case ID_DRAW_SPIRAL_LEFT:
		load_bitmap = hImage.LoadBitmap(IDB_EXIT_TOP);
		break;
// right exits
	case ID_DRAW_RT_TURN:
	case ID_DRAW_270_LT:
	case ID_DRAW_90_PIVOT_RT:
	case ID_DRAW_1STEP_HEEL_RT:
		load_bitmap = hImage.LoadBitmap(IDB_EXIT_RIGHT);
		break;

// left exits
	case ID_DRAW_LT_TURN:
	case ID_DRAW_90_PIVOT_LT:
	case ID_DRAW_270_RT:
		load_bitmap = hImage.LoadBitmap(IDB_EXIT_LEFT);
		break;
// bottom exits
	case ID_DRAW_ABOUT_RT:
	case ID_ABOUT_FORWARD_RT:
	case ID_DRAW_180_PIVOT_RT:
	case ID_DRAW_ABOUT_LT:
	case ID_DRAW_ABOUT_TURN_LT:
	case ID_DRAW_U_FORWARD_LT:	
	case ID_DRAW_180_PIVOT_LT:
		load_bitmap = hImage.LoadBitmap(IDB_EXIT_BOTTOM);
		break;
// none
	case ID_DRAW_FINISH:
	case ID_DRAW_HONOR:
		load_bitmap = false;
		break;
	}
	if (load_bitmap) {
		BITMAP bmpInfo;
		hImage.GetBitmap(&bmpInfo);
		memDC.CreateCompatibleDC(pDC); // dc for window 
		pOldBitmap = (CBitmap*)memDC.SelectObject(hImage);	// always select object into the window mem DC
		BOOL draw = pDC->BitBlt(this->m_station_rect.left + (bmpInfo.bmWidth/2), this->m_station_rect.top - bmpInfo.bmHeight, bmpInfo.bmWidth, bmpInfo.bmHeight, 
			&memDC, 0, 0, SRCAND);
	}
}
*/
void CRallyObject::DrawStringForStation(CDC* pDC) {
	COLORREF old_text_color;
	old_text_color = pDC->SetTextColor(RGB( 0, 0, 255 ));
	CString string_to_draw, sec_string;
	TEXTMETRIC tm;
	int len, half_string;
	int temp_rotate;
	pDC->GetTextMetrics(&tm);
	if (this->m_do_rotate_text) {
		temp_rotate = this->m_rotate_text;
		this->m_rotate_text = 0;
	}

	switch(this->m_rally_string_ID) {
	case ID_DRAW_START:
		string_to_draw = "START";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (this->m_height/2) - 10,string_to_draw);
		break;
	case ID_DRAW_FINISH:
		string_to_draw = "FINISH";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top,string_to_draw);
		break;
	case ID_DRAW_HONOR:
		string_to_draw = "HONOR";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (this->m_height/2) - 10,string_to_draw);
		break;
	case ID_DRAW_SITHALT:
		string_to_draw = "SIT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		switch (this->m_rotate_text) {
		case 0:
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 90:
			pDC->TextOut(this->m_station_rect.left + half_string*2,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 180:
			pDC->TextOut(this->m_station_rect.left  + half_string*2,this->m_station_rect.bottom - (tm.tmHeight * 4),string_to_draw);
			break;
		case 270:
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			break;
		default:
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		}
		break;
	case ID_DRAW_SIT_STAND:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+10,this->m_station_rect.bottom - (tm.tmHeight * 3) - 5,string_to_draw);
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+ 8 ,this->m_station_rect.bottom - (tm.tmHeight*2) - 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2)+ 10,this->m_station_rect.bottom - (tm.tmHeight * 4) - 10,string_to_draw);
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2) ,this->m_station_rect.bottom - tm.tmHeight*3 -10,string_to_draw);
			break;
		case 270:
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)-8,string_to_draw);
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight*3-8,string_to_draw);
			break;
		default:
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
		case ID_DRAW_SITHALTDOWN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+10,this->m_station_rect.bottom - (tm.tmHeight * 3) - 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2)+ 10,this->m_station_rect.bottom - (tm.tmHeight * 4) - 10,string_to_draw);
			break;
		case 270:
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)-8,string_to_draw);
			break;
		default:
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		}
		break;
		case ID_RETURN_STAND:
			string_to_draw = "RETURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "& FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "FROM STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;
		case ID_RECALL_LEAVE:
			string_to_draw = "RECALL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;
		case ID_DOWN_RECALL:
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "ON RECALL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;
		case ID_DOWN_RECALL_TWO:
			string_to_draw = "TURN, RECALL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "DOWN-RECALL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "FINISH OR";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight - 5,string_to_draw);		
			break;
		case ID_TURN_FRONT:
			string_to_draw = "TURN &";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;
		case ID_FINISH_RIGHT:
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;
		case ID_FINISH_LEFT:
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;
		case ID_RETRIEVE_FINISH:
			string_to_draw = "TURN-HALT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "RETRIEVE";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);		
			break;

	case ID_DRAW_HALTWALK:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-WALK";
			}
			else {
				string_to_draw = "WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-WALK";
			}
			else {
				string_to_draw = "WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left +10,this->m_station_rect.bottom - (tm.tmHeight * 3) - 5,string_to_draw);
			string_to_draw = "AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2) - 5,string_to_draw);
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-WALK";
			}
			else {
				string_to_draw = "WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+ 10,this->m_station_rect.bottom - (tm.tmHeight * 4) - 10,string_to_draw);
			string_to_draw = "AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string-8) ,this->m_station_rect.bottom - tm.tmHeight*3 -10,string_to_draw);
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-WALK";
			}
			else {
				string_to_draw = "WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)-8,string_to_draw);
			string_to_draw = "AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight*3-8,string_to_draw);
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-WALK";
			}
			else {
				string_to_draw = "WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_DOWNWALK:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "WALK AROUND";
			}
			else {
				string_to_draw = "AROUND DOG";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight * 3) - 5,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "WALK AROUND";
			}
			else {
				string_to_draw = "AROUND DOG";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2) - 5,string_to_draw);
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight * 4) - 10,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "WALK AROUND";
			}
			else {
				string_to_draw = "AROUND DOG";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string-8) ,this->m_station_rect.bottom - tm.tmHeight*3 -10,string_to_draw);
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)-8,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "WALK AROUND";
			}
			else {
				string_to_draw = "AROUND DOG";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight*3-8,string_to_draw);
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "WALK AROUND";
			}
			else {
				string_to_draw = "AROUND DOG";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}	
		break;
	case ID_DRAW_SLOWFORWARDFROMSIT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Leave Dog 5 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog to Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return to Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Leave Dog 5 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog to Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return to Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Leave Dog 5 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog to Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return to Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Leave Dog 5 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog to Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return to Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Leave Dog 5 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog to Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return to Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_DRAW_STANDWALK:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "STAND-EXAM";
			}
			else {
				string_to_draw = "STAND WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "LEAVE";
			}
			else {
				string_to_draw = "AROUND";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "STAND-EXAM";
			}
			else {
				string_to_draw = "STAND WALK";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight * 3) - 5,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "LEAVE";
			}
			else {
				string_to_draw = "AROUND";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2) - 5,string_to_draw);
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "STAND-EXAM";
			}
			else {
				string_to_draw = "STAND WALK";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight * 4) - 10,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "LEAVE";
			}
			else {
				string_to_draw = "AROUND";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string-8) ,this->m_station_rect.bottom - tm.tmHeight*3 -10,string_to_draw);
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "STAND-EXAM";
			}
			else {
				string_to_draw = "STAND WALK";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)-8,string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "LEAVE";
			}
			else {
				string_to_draw = "AROUND";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight*3-8,string_to_draw);
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "STAND-EXAM";
			}
			else {
				string_to_draw = "STAND WALK";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "LEAVE";
			}
			else {
				string_to_draw = "AROUND";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}	
		break;
	case ID_DRAW_DOWNSIT:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN";
			}
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10 ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+8,this->m_station_rect.bottom - (tm.tmHeight * 2) - 5,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+ 10 ,this->m_station_rect.bottom - (tm.tmHeight) - 5,string_to_draw);
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2),this->m_station_rect.bottom - (tm.tmHeight * 4) - 5,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2) + 10 ,this->m_station_rect.bottom - tm.tmHeight*3 -5,string_to_draw);
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 3)-8,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 15 ,this->m_station_rect.bottom - tm.tmHeight*2-8,string_to_draw);
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "SIT-DOWN";
			}
			else {
				string_to_draw = "DOWN";
			}

			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_STAND:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Leave Dog 3 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Distance Down - Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return Around Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Leave Dog 3 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Distance Down - Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return Around Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Leave Dog 3 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Distance Down - Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return Around Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Leave Dog 3 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Distance Down - Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return Around Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Leave Dog 3 mtrs";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Distance Down - Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Return Around Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_STANDDOWN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string),this->m_station_rect.bottom - (tm.tmHeight * 3) - 5,string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+ 8 ,this->m_station_rect.bottom - (tm.tmHeight*2) - 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2)-8,this->m_station_rect.bottom - (tm.tmHeight * 4) - 10,string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2) ,this->m_station_rect.bottom - tm.tmHeight*3 -10,string_to_draw);
			break;
		case 270:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)-8,string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight*3-8,string_to_draw);
			break;
		default:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}		
		break;
	case ID_DRAW_STANDSIT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10 ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string),this->m_station_rect.bottom - (tm.tmHeight * 2) - 5,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string)+ 10 ,this->m_station_rect.bottom - (tm.tmHeight) - 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2)-8,this->m_station_rect.bottom - (tm.tmHeight * 4) - 5,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (half_string*2) + 10 ,this->m_station_rect.bottom - tm.tmHeight*3 -5,string_to_draw);
			break;
		case 270:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string,this->m_station_rect.bottom - (tm.tmHeight * 3)-8,string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 15 ,this->m_station_rect.bottom - tm.tmHeight*2-8,string_to_draw);
			break;
		default:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "SIT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
// CHANGE PACE
		case ID_DRAW_NORMAL:
		string_to_draw = "NORMAL";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "PACE";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_FAST:
		string_to_draw = "FAST";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "PACE";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_SLOW:
		string_to_draw = "SLOW";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
		string_to_draw = "PACE";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 10,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
	case ID_DRAW_FAST_SIT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "FAST";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "FROM SIT";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "FAST";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 4),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "FROM SIT";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "FAST";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight * 4)- 10,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight * 3)-10,string_to_draw);
			string_to_draw = "FROM SIT";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - tm.tmHeight * 2 - 10,string_to_draw);
			break;
		case 270:
			string_to_draw = "FAST";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight * 3)- 10,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight * 2)-10,string_to_draw);
			string_to_draw = "FROM SIT";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - tm.tmHeight - 10,string_to_draw);
			break;
		default:
			string_to_draw = "FAST";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "FROM SIT";
			len = string_to_draw.GetLength();
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		
//right turns
		break;	
	case ID_DRAW_RT_TURN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_ABOUT_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		case 90:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) + 5,this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) + 5,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) + 5,this->m_station_rect.top + (tm.tmHeight*3),string_to_draw);
			break;
		case 270:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "TURN RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 5,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		}
		break;
	case ID_ABOUT_FORWARD_RT:
		string_to_draw = "ABOUT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
		string_to_draw = "TURN RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
		string_to_draw = "FORWARD";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
		break;
	case ID_DRAW_270_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) + 10,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left + (this->m_width / 2) + 10, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.bottom - tm.tmHeight* 2,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.bottom - tm.tmHeight* 2, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		}
		
		break;
	case ID_DRAW_360_RT:
		string_to_draw = "360";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width/2)- half_string,this->m_station_rect.top + (this->m_height/2) - tm.tmHeight,string_to_draw);
		this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2)- half_string, this->m_station_rect.top + (this->m_height/2) - tm.tmHeight, len,tm.tmAveCharWidth); 
		string_to_draw = "RIGHT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width/2)- half_string,this->m_station_rect.top + (this->m_height/2),string_to_draw);
		break;
	case ID_DRAW_90_PIVOT_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + 5, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + half_string + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + half_string + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_180_PIVOT_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width/2),this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left + (this->m_width/2), this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width/2),this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width/2),this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width/2) + half_string + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left + (this->m_width/2) + half_string + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_1STEP_HEEL_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  +(this->m_width/2),this->m_station_rect.top,string_to_draw);
			string_to_draw = "RIGHT 1 STEP";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "CALL TO HEEL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 90:
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "1 STEP";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "CALL TO HEEL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
		break;
		case 180:
			string_to_draw = "TURN RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top,string_to_draw);
			string_to_draw = "1 STEP";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "CALL TO";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			string_to_draw = "HEEL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 270:
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*4) ,string_to_draw);
			string_to_draw = "1 STEP";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL TO";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "HEEL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		default:
			string_to_draw = "TURN RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "1 STEP";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL TO";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "HEEL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		}
		break;
		case ID_DRAW_RT_DOWN:
			string_to_draw = "";
			string_to_draw = "RIGHT TURN";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "1-2 STEPS";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOWN DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;

// LEFT TURNS
	case ID_DRAW_LT_TURN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		}
		
		break;
	case ID_DRAW_ABOUT_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		case 90:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "'U' TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
		break;
		case 180:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) - 10,this->m_station_rect.top,string_to_draw);
			string_to_draw = "'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		case 270:
			string_to_draw = "ABOUT 'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		default:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		}
		break;
	case ID_DRAW_ABOUT_TURN_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left-10,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left-10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "LEFT ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top + (tm.tmHeight + 5),string_to_draw);
			break;
		case 180:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + (tm.tmHeight*3),string_to_draw);
			break;
		case 270:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) - 15,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "ABOUT TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		}		break;	
	case ID__DRAW_HALTLEFTFORWARD:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			string_to_draw = "Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left-10,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left-10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "LEFT Turn ";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top + (tm.tmHeight + 5),string_to_draw);
			break;
		case 180:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + (tm.tmHeight*3),string_to_draw);
			break;
		case 270:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) - 15,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "Turn FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		}	
		break;
	case ID__DRAW_HALTRIGHTFORWARD:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			string_to_draw = "Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left-10,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left-10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "RIGHT Turn ";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top + (tm.tmHeight + 5),string_to_draw);
			break;
		case 180:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + (tm.tmHeight*3),string_to_draw);
			break;
		case 270:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) - 15,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "Turn FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		}	
		break;	
	case ID_DRAW_U_FORWARD_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "ABOUT 'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left - 5,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "TURN FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left- 5,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "'U' TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight) - 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "ABOUT 'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "TURN FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "ABOUT 'U'";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 30,this->m_station_rect.top + 10,string_to_draw);
			string_to_draw = "TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 40,this->m_station_rect.bottom - tm.tmHeight * 2 + 10,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 40,this->m_station_rect.bottom - tm.tmHeight + 10,string_to_draw);
			break;
		default:
			string_to_draw = "ABOUT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "'U' TURN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + (tm.tmHeight*2),string_to_draw);
			break;
		}
		break;	
	case ID_DRAW_270_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + 10, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - tm.tmHeight * 2, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "270";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_360_LT:
		string_to_draw = "360";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width/2)- half_string,this->m_station_rect.top + (this->m_height/2) - tm.tmHeight,string_to_draw);
		this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2)- half_string, this->m_station_rect.top + (this->m_height/2) - tm.tmHeight, len,tm.tmAveCharWidth); 
		string_to_draw = "LEFT";
		len = string_to_draw.GetLength();
		half_string = (len * tm.tmAveCharWidth) / 2;
		pDC->TextOut(this->m_station_rect.left  + (this->m_width/2)- half_string,this->m_station_rect.top + (this->m_height/2),string_to_draw);
		break;
	case ID_DRAW_90_PIVOT_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 15, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_HALTLEFTPIVOTFORWARD:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 15, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;

	case ID_DRAW_HALTRIGHTPIVOTFORWARD:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 15, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_180_PIVOT_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2), this->m_station_rect.bottom - tm.tmHeight * 3, len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "180";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "PIVOT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
		case ID_DRAW_LT_DOWN:
			string_to_draw = "";
			string_to_draw = "LEFT TURN";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "1-2 STEPS";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOWN DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		//FINSIH STATIONS
	case ID_DRAW_FINISH_RT_FORWARD:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 8,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 8,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "FORWARD RIGHT ";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "RIGHT FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FRONT FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *1),string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			}
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 8,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 8,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "RIGHT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		}
		break;
	case ID_DRAW_FINISH_LEFT_FORWARD:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 8,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "FORWARD LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "LEFT FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left - 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *3),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			}
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "CALL";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len - 10,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "FINISH";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
				pDC->TextOut(this->m_station_rect.right - len + 8,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "LEFT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 30;
				pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		}
		break;
	case ID_DRAW_FINISH_RT_HALT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "RIGHT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "RIGHT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "RIGHT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *4),string_to_draw);
			string_to_draw = "RIGHT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			break;
		default:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "RIGHT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_FINISH_LT_HALT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "LEFT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "LEFT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "LEFT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *4),string_to_draw);
			string_to_draw = "LEFT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			break;
		default:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 20 ;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight *2),string_to_draw);
			string_to_draw = "LEFT HALT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 25;
			pDC->TextOut(this->m_station_rect.right- len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_HALT_FINISH_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FINISH RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FINISH RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FINISH RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		default:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FINISH RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_HALT_FINISH_LT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FINISH LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FINISH LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		default:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FINISH LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_FRONTHEEL:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "Return to Heel";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Return";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "to Heel";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.top,string_to_draw);
			string_to_draw = "Return to Heel";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.top,string_to_draw);
			string_to_draw = "Return";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "to Heel";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		default:
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "Return to Heel";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_FRONT_RUN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "LEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WHILE RUNNING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "LEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WHILE RUNNING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "LEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WHILE RUNNING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "LEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WHILE RUNNING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "LEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL FRONT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WHILE RUNNING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
// MOVE STATIONS
	case ID_DRAW_SIDE_RT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "MOVING";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "SIDE";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "STEP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "RIGHT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "MOVING";
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
			string_to_draw = "SIDE STEP";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "RIGHT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			break;
		case 180:
			string_to_draw = "MOVING SIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4) - 10,string_to_draw);
			string_to_draw = "STEP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right -len,this->m_station_rect.bottom - (tm.tmHeight * 3) - 10 ,string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight * 2 - 10,string_to_draw);
			break;
		case 270:
			string_to_draw = "MOVING SIDE";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "STEP RIGHT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "MOVING";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "SIDE";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "STEP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "RIGHT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_MOVE_DOWN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Down";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 90:
			string_to_draw = "Down";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 5,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 180:
			string_to_draw = "Down";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 5,this->m_station_rect.bottom - (tm.tmHeight * 3) + 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Down";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		default:
			string_to_draw = "Down";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		}
		break;
	case ID_DRAW_MOVINGSTAND:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 90:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 5,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 180:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 5,this->m_station_rect.bottom - (tm.tmHeight * 3) + 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		default:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			break;
		}
		break;
	case ID__DRAW_DOWNWHILEHEELING:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Moving Stand";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 90:
			string_to_draw = "Moving Stand";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 180:
			string_to_draw = "Moving Stand";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "Moving Stand";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		default:
			string_to_draw = "Moving Stand";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_HALT_LEAVE_RECALL:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "About Turn";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Recall Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Handler Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 90:
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "About Turn";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Recall Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Handler Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 180:
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "About Turn";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Recall Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Handler Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "About Turn";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Recall Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Handler Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		default:
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "About Turn";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Recall Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Handler Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_FRONT_REV_3_STEPS:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Call Front";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Reverse 3";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Steps Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "To Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 90:
			string_to_draw = "Call Front";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Reverse 3";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Steps Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "To Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 180:
			string_to_draw = "Call Front";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Reverse 3";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Steps Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "To Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "Call Front";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Reverse 3";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Steps Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "To Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		default:
			string_to_draw = "Call Front";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Reverse 3";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Steps Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "To Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_LEAVE_ABOUT_RET:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Leave Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "5 Mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "About      Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Turn       to Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 90:
			string_to_draw = "Leave Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "5 Mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "About      Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Turn       to Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		case 180:
			string_to_draw = "Leave Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "5 Mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "About      Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Turn       to Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "Leave Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "5 Mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "About      Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Turn       to Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
		break;
		default:
			string_to_draw = "Leave Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "5 Mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "About      Return";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Turn       to Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_HALT_CIRCLE_FOR:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Circles";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "Handler";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			string_to_draw = "Circles";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "Handler";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top,string_to_draw);
			string_to_draw = "Circles";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "Handler";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + half_string + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Circles";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "Handler";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Circles";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "Handler";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_LEAVE_ABT_REC_FIN_R:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_LEAVE_ABT_REC_FIN_L:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Leave Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Call Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_R_U_LEFT_ABOUT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_L_U_LEFT_ABOUT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_L_ABOUT_RIGHT_U:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_L_ABOUT_LEFT_U:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_STAND_PIVOT_R_FOR:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Right Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Right Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Right Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Right Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Right Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_STAND_PIVOT_L_FOR:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Stand";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "90";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Pivot";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_FRT_CIR_R_FIN_L:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Call Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "360 Circle";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Spin Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "Call Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "360 Circle";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Spin Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "Call Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "360 Circle";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Spin Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Call Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "360 Circle";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Spin Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "Call Front";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "360 Circle";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "Spin Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Finish Left Forward";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_TR_L_HEEL_R_T_R:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "180 Left Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "Heels Right Side";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "180 Right Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Returns to Heel";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 90:
			string_to_draw = "180 Left Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "Heels Right Side";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "180 Right Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Returns to Heel";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "180 Left Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "Heels Right Side";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "180 Right Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Returns to Heel";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "180 Left Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "Heels Right Side";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "180 Right Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Returns to Heel";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		default:
			string_to_draw = "180 Left Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 4)- 5,string_to_draw);
			string_to_draw = "Heels Right Side";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 3)- 5,string_to_draw);
			string_to_draw = "180 Right Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 15,this->m_station_rect.bottom - (tm.tmHeight * 2)- 5,string_to_draw);
			string_to_draw = "Returns to Heel";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string ,this->m_station_rect.bottom - tm.tmHeight- 5,string_to_draw);
			break;
		}	
		break;
	case ID_DOUBLE_RIGHT_UTURN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + 5, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + half_string + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + half_string + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Right";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DOUBLE_LEFT_UTURN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + 5, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + half_string + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + half_string + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "U Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DOUBLE_LEFT_ATURN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 20,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 20, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top,string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + 5, this->m_station_rect.top, len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + 5,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2) + half_string + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + (this->m_width/2) + half_string + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "Double";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			this->DrawDegreeSymbol(pDC,this->m_station_rect.left  + 10, this->m_station_rect.bottom - (tm.tmHeight*3), len,tm.tmAveCharWidth); 
			string_to_draw = "Left";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "About Turn";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID__STAND_HEEL:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WHILE HEELING";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
		case 90:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WHILE HEELING";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 180:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WHILE HEELING";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 270:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WHILE HEELING";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
		default:
			string_to_draw = "STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WHILE HEELING";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		}
		break;
	case ID__DRAW_STAND_SIT_LEAVE:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "STAND";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEAVE DOG";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "SIT DOG";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "CALL FRONT-FINISH";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "STAND";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEAVE DOG";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "SIT DOG";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "CALL FRONT-FINISH";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "STAND";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEAVE DOG";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "SIT DOG";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "CALL FRONT-FINISH";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "STAND";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEAVE DOG";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "SIT DOG";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "CALL FRONT-FINISH";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "STAND";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEAVE DOG";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "SIT DOG";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "CALL FRONT-FINISH";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID__STAND_LEAVE_DOWN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Stand Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down - Sit";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "Stand Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down - Sit";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "Stand Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down - Sit";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "Stand Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down - Sit";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "Stand Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Leave Dog 3 mtrs";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Distance Down - Sit";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Return Around Dog";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID__DRAW_DOUBLE_LEFT_TURN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "DOUBLE";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "ABOUT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "TURN";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "DOUBLE";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "ABOUT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "TURN";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "DOUBLE";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "ABOUT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "TURN";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "DOUBLE";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "ABOUT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "TURN";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "DOUBLE";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "ABOUT";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "TURN";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID__DRAW_SENDTOJUMP:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SEND TO JUMP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "SEND TO JUMP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "SEND TO JUMP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "SEND TO JUMP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "SEND TO JUMP";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
		case ID__DRAW_SITSTAY:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Moving Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "Walk Around";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
		break;
		case 90:
			string_to_draw = "Moving Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "Walk Around";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 180:
			string_to_draw = "Moving Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "Walk Around";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 270:
			string_to_draw = "Moving Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "Walk Around";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		default:
			string_to_draw = "Moving Sit";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "Walk Around";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "Dog";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
	break;
		}
		break;
		case ID__DRAW_CALLTOHEEL:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "360 Left";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Circle Spin";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "At Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 90:
			string_to_draw = "360 Left";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Circle Spin";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "At Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 180:
			string_to_draw = "360 Left";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Circle Spin";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "At Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 270:
			string_to_draw = "360 Left";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Circle Spin";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "At Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		default:
			string_to_draw = "360 Left";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Circle Spin";
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "At Heel";
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		}
		break;
	case ID_DRAW_MOVE_STAND_WALK:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
		break;
		case 90:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 180:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4) + 10,string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3) + 10,string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 270:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		default:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		}
		break;
	case ID__DRAW_MOVE_DOWN:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "MOVING DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
		break;
		case 90:
			string_to_draw = "MOVING DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 180:
			string_to_draw = "MOVING DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4) + 10,string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3) + 10,string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		case 270:
			string_to_draw = "MOVING DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		default:
			string_to_draw = "MOVING DOWN";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "WALK AROUND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight),string_to_draw);
			break;
		}
		break;
	case ID_MOVE_STAND_LEAVE:
	case ID_MOVE_STAND_SIT_FINISH:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
		break;
		case 90:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		case 180:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 4) + 10,string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3) + 10,string_to_draw);
			break;
		case 270:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		default:
			string_to_draw = "MOVING STAND";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
		}
		break;
		case ID_MOVE_STAND_LEAVE_TWO:
			string_to_draw = "TURN &";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 3),string_to_draw);
			string_to_draw = "CALL TO HEEL";
			len = string_to_draw.GetLength();
			half_string = (len * tm.tmAveCharWidth) / 2;
			pDC->TextOut(this->m_station_rect.left  + (this->m_width / 2) - half_string - 15,this->m_station_rect.bottom - (tm.tmHeight * 2),string_to_draw);
			break;
			break;
		case ID_MOVE_STAND_SIT_FINISH_TWO:
			string_to_draw = "TURN";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len - 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "DOWN";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - (len/2) ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "SIT, CALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FINISH";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - (len/2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case ID_JUMP_RECALL:
			string_to_draw = "";
			string_to_draw = "RECALL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = " OVER JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case ID_JUMP_RECALL_TWO:
			string_to_draw = "";
			string_to_draw = "TURN";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "CALL OVER JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH OR";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case ID_JUMP_LEAVE:
			string_to_draw = "";
			string_to_draw = "SEND OVER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2,this->m_station_rect.top,string_to_draw);
			string_to_draw = "JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left +  tm.tmAveCharWidth,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case ID_JUMP_LEAVE_TWO:
			string_to_draw = "";
			string_to_draw = "TURN AND";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "SEND OVER JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "FINISH OR";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			string_to_draw = "FORWARD";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_midPoint.x - len/2,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case ID_DRAW_JUMP:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SEND";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
			string_to_draw = "OVER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "HANDLER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "PASSES BY";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "SEND";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
			string_to_draw = "OVER JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "HANDLER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "PASSES BY";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight - 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "SEND";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*5) - 5,string_to_draw);
			string_to_draw = "OVER JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4) - 5,string_to_draw);
			string_to_draw = "HANDLER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15,this->m_station_rect.bottom - (tm.tmHeight*3) - 5,string_to_draw);
			string_to_draw = "PASSES BY";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			break;
		case 270:
			string_to_draw = "SEND";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) ,this->m_station_rect.top,string_to_draw);
			string_to_draw = "OVER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.top + (tm.tmHeight),string_to_draw);
			string_to_draw = "JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.top + (tm.tmHeight * 2),string_to_draw);
			string_to_draw = "HANDLER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight) - 10,string_to_draw);
			string_to_draw = "PASSES BY";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - 10,string_to_draw);
			break;
		default:
			string_to_draw = "SEND";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "OVER JUMP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "HANDLER";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "PASSES BY";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
// HEEL STATIONS
	case ID_DRAW_HALT_3_STEPS_FOR:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			else {
				string_to_draw = "1 STEP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "2 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			else {
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) - 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) - 20,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) - 20,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			else {
				string_to_draw = "1 STEP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) - 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "2 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) - 20,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) - 20,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10 ,this->m_station_rect.bottom - (tm.tmHeight*3) -10,string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2) -10,string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*1) - 10,string_to_draw);
			}
			else {
				string_to_draw = "1 STEP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10 ,this->m_station_rect.bottom - (tm.tmHeight*3) -10,string_to_draw);
				string_to_draw = "2 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2) -10,string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*1) - 10,string_to_draw);
			}
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			else {
				string_to_draw = "1 STEP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "2 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			}
			break;
		}
		break;

	case ID_DRAW_FRONT_3_STEPS_BACK:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "BACKWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "2 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "3 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "BACKWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "2 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "3 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "BACKWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "2 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "3 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "BACKWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "2 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "3 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "CALL FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1, 2, 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "BACKWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
				}
			else {
				string_to_draw = "FRONT";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "1 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "2 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "3 BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		}
		break;
	case ID_DRAW_SIDE_RIGHT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SIDE STEP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "SIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "STEP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight * 2,string_to_draw);
			break;
		case 180:
			string_to_draw = "SIDE STEP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.bottom - tm.tmHeight * 3,string_to_draw);
			break;
		case 270:
			string_to_draw = "SIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 50,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "STEP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 50,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 50,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "SIDE STEP";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;		
	case ID_DRAW_BACKUP_3:
		switch (this->m_rotate_text) {
		case 0:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "MOVING BACKUP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "HEEL BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "THAN FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "BACKUP 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS DOG";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STAYS IN";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "POSITION";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 90:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "MOVING BACKUP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "HEEL BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "THAN FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "BACKUP 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS DOG";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STAYS IN";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "POSITION";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 180:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "MOVING BACKUP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "HEEL BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "THAN FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "BACKUP 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS DOG";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STAYS IN";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "POSITION";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		case 270:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "MOVING BACKUP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "HEEL BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "THAN FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "BACKUP 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4) - 10,string_to_draw);
				string_to_draw = "STEPS DOG";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3) - 10,string_to_draw);
				string_to_draw = "STAYS IN";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2) - 10,string_to_draw);
				string_to_draw = "POSITION";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight - 10,string_to_draw);
			}
			break;
		default:
			if (this->m_type_station == APDT_COURSE) {
				string_to_draw = "MOVING BACKUP";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "HEEL BACK";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "3 STEPS";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "THAN FORWARD";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			else {
				string_to_draw = "BACKUP 3";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
				string_to_draw = "STEPS DOG";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
				string_to_draw = "STAYS IN";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
				string_to_draw = "POSITION";
				len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
				pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			}
			break;
		}
		break;
	case ID__DRAW_2_STEPS_FORWARD:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "3 mtrs";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL DOG TO HEEL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WITHOUT STOPPING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "3 mtrs";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL DOG CALL TO HEEL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WITHOUT STOPPING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);

			break;
		case 180:
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "3 mtrs";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL DOG CALL TO HEEL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WITHOUT STOPPING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "3 mtrs";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL DOG CALL TO HEEL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WITHOUT STOPPING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "LEAVE DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len +  tm.tmAveCharWidth * 3,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "3 mtrs";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "CALL DOG CALL TO HEEL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "WITHOUT STOPPING";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.right - len,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
// WEAVE STATIONS
	case ID_DRAW_SERP_ONCE:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SERPENTINE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "WEAVE ONCE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			break;
		case 90:
			string_to_draw = "SERPENTINE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 25,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "WEAVE ONCE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 25,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			break;
		case 180:
			string_to_draw = "SERPENTINE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*4) + 5,string_to_draw);
			string_to_draw = "WEAVE ONCE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3) + 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "SERPENTINE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left - 15,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "WEAVE ONCE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left - 15,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			break;
		default:
			string_to_draw = "SERPENTINE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "WEAVE ONCE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			break;
		}
		break;
	case ID_WEAVES_FIGURE8:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "Four Cone";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "Figure 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*1),string_to_draw);
			break;
		case 90:
			string_to_draw = "Four Cone";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 25,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Figure 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 25,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			break;
		case 180:
			string_to_draw = "Four Cone";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3) + 5,string_to_draw);
			string_to_draw = "Figure 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*2) + 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "Four Cone";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left - 15,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "Figure 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left - 15,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			break;
		default:
			string_to_draw = "Four Cone";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "Figure 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			break;
		}
		break;
	case ID_DRAW_WEAVE_TWICE:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "STRAIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10 ,this->m_station_rect.top + 10,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + tm.tmHeight + 10,string_to_draw);
			string_to_draw = "WEAVE TWICE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + (tm.tmHeight*2) + 10,string_to_draw);
			break;
		case 90:
			string_to_draw = "STRAIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 35 ,this->m_station_rect.top + 5,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.top + tm.tmHeight + 5,string_to_draw);
			string_to_draw = "WEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.top + (tm.tmHeight*2) + 5,string_to_draw);
			string_to_draw = "TWICE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 35,this->m_station_rect.top + (tm.tmHeight*3) + 5,string_to_draw);
			break;
		case 180:
			string_to_draw = "STRAIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.top + tm.tmHeight+ 5,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.top + tm.tmHeight * 2 + 5,string_to_draw);
			string_to_draw = "WEAVE TWICE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + (tm.tmHeight*3) + 5,string_to_draw);
			break;
		case 270:
			string_to_draw = "STRAIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left ,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + tm.tmHeight * 2,string_to_draw);
			string_to_draw = "WEAVE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + (tm.tmHeight*3),string_to_draw);
			string_to_draw = "TWICE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + (tm.tmHeight*4),string_to_draw);
			break;
		default:
			string_to_draw = "STRAIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10 ,this->m_station_rect.top + 10,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + tm.tmHeight + 10,string_to_draw);
			string_to_draw = "WEAVE TWICE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 2,this->m_station_rect.top + (tm.tmHeight*2) + 10,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_OFFSET_8:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "OFF-SET";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5 ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "OFF-SET";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 15 ,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "OFF-SET";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 25 ,this->m_station_rect.top,string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 25,this->m_station_rect.top + tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "OFF-SET";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5 ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		default:
			string_to_draw = "OFF-SET";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5 ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "FIGURE 8";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_SPIRAL_RIGHT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 45 ,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 50,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "DOG OUTSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "SPIRAL RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "DOG OUTSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 180:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "OUTSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 20 ,this->m_station_rect.bottom - (tm.tmHeight*5),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "DOG OUTSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			break;
		default:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 45 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "RIGHT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 50,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 40,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "OUTSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 40,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	case ID_DRAW_SPIRAL_LEFT:
		switch (this->m_rotate_text) {
		case 0:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "INSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 10,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 90:
			string_to_draw = "SPIRAL LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "DOG INSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			break;
		case 180:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2) ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "INSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + (this->m_width / 2),this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		case 270:
			string_to_draw = "SPIRAL LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5 ,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "DOG INSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 5,this->m_station_rect.bottom - (tm.tmHeight*1),string_to_draw);
			break;
		default:
			string_to_draw = "SPIRAL";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 45 ,this->m_station_rect.bottom - (tm.tmHeight*4),string_to_draw);
			string_to_draw = "LEFT";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 50,this->m_station_rect.bottom - (tm.tmHeight*3),string_to_draw);
			string_to_draw = "DOG";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 40,this->m_station_rect.bottom - (tm.tmHeight*2),string_to_draw);
			string_to_draw = "INSIDE";
			len = string_to_draw.GetLength() * tm.tmAveCharWidth + 15;
			pDC->TextOut(this->m_station_rect.left + 40,this->m_station_rect.bottom - tm.tmHeight,string_to_draw);
			break;
		}
		break;
	}

	old_text_color = pDC->SetTextColor(old_text_color );
	if (this->m_do_rotate_text) 
		this->m_rotate_text = temp_rotate;

}

void CRallyObject::DrawDegreeSymbol(CDC *pDC, int left_of_string, int top_of_string, int len_of_string, int len_of_char) {
	CRect degree;
	degree.left = left_of_string + len_of_string * len_of_char + 5;
	degree.right = degree.left + 5;
	degree.top = top_of_string + 2;
	degree.bottom = degree.top + 5;
	pDC->Ellipse(&degree);
}

void CRallyObject::SetStationRect() {
	CBitmap bmp;
	if (bmp.LoadBitmap(this->m_rally_station_ID)) 	{
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		m_station_rect.left = this->m_midPoint.x - (bmpInfo.bmWidth/2);
		m_station_rect.right = this->m_midPoint.x + (bmpInfo.bmWidth/2);
		m_station_rect.top = this->m_midPoint.y - (bmpInfo.bmHeight/2);
		m_station_rect.bottom = this->m_midPoint.y + (bmpInfo.bmHeight/2);
		this->m_width = m_station_rect.right - m_station_rect.left;
		this->m_height = m_station_rect.bottom - m_station_rect.top;
		this->SetStationMidPointFromRect();
	}
	else {
		error_string.Format("ERROR: Where's %d?",this->m_rally_station_ID);
		TRACE0(error_string);
	}

}
void CRallyObject::SetStationRect(RECT *station_rect) {

//	if (station_rect->top < 0 || station_rect->left < 0) return;
	m_station_rect.left = station_rect->left;
	m_station_rect.right = station_rect->right;
	m_station_rect.top = station_rect->top;
	m_station_rect.bottom = station_rect->bottom;
	this->m_width = m_station_rect.right - m_station_rect.left;
	this->m_height = m_station_rect.bottom - m_station_rect.top;
	this->SetStationMidPointFromRect();
}
RECT CRallyObject::GetStationRect() {
	return this->m_station_rect;
}
void CRallyObject::GetRectEntryExits(POINT *top, POINT *left, POINT *right, POINT *bottom, BOOL entry) {

	switch (this->m_rally_string_ID) {
	case ID_DRAW_SERP_ONCE:
	case ID_DRAW_WEAVE_TWICE:
	case ID_DRAW_SPIRAL_RIGHT:
	case ID_DRAW_SPIRAL_LEFT:
		/*
		if (this->m_where_cones == CONE_HIDE) {
			top->y = this->m_midPoint.y - this->m_height/2;
			top->x = this->m_midPoint.x;

			bottom->y = this->m_midPoint.y  + this->m_height/2;
			bottom->x = this->m_midPoint.x;

			
			left->x = this->m_midPoint.x - this->m_width/2;
			left->y = this->m_midPoint.y;
			
			right->x = this->m_midPoint.x + this->m_width/2;
			right->y = this->m_midPoint.y;
		} 
		else {
			if (entry) {
				right->y = bottom->y =left->y = top->y = this->m_pylon_entrance.y;
				right->x = bottom->x = left->x = top->x = this->m_pylon_entrance.x;
			}
			else {
				right->y = bottom->y =left->y = top->y = this->m_pylon_exit.y;
				right->x = bottom->x = left->x = top->x = this->m_pylon_exit.x;
			}
		}

		break;*/
	default:
		top->y = this->m_midPoint.y - this->m_height/2;
		top->x = this->m_midPoint.x;

		bottom->y = this->m_midPoint.y  + this->m_height/2;
		bottom->x = this->m_midPoint.x;

		
		left->x = this->m_midPoint.x - this->m_width/2;
		left->y = this->m_midPoint.y;
		
		right->x = this->m_midPoint.x + this->m_width/2;
		right->y = this->m_midPoint.y;
		break;
	}
	if (entry && this->m_cus_entrance.y > 0) {
		right->y = bottom->y =left->y = top->y = this->m_cus_entrance.y;
		right->x = bottom->x = left->x = top->x = this->m_cus_entrance.x;
	}
	if (!entry && this->m_cus_exit.y > 0) {
		right->y = bottom->y =left->y = top->y = this->m_cus_exit.y;
		right->x = bottom->x = left->x = top->x = this->m_cus_exit.x;
	}

}
void CRallyObject::OffSetStationRect(CPoint *point) {

	this->m_station_rect.OffsetRect(*point);
	this->SetStationMidPointFromRect();
	CPoint reset_point(-1,-1);
	this->SetCustomEntrancePoint(&reset_point);
	this->SetCustomExitPoint(&reset_point);
	
}
void CRallyObject::OffSetMidPoint(CPoint *point) {
	MessageBox(NULL,"NOT IMPLEMENTED YET",NULL,MB_OK);;	
}
void CRallyObject::SetStationID(int station_id) {
	this->m_rally_station_ID = station_id;
}

int CRallyObject::GetStationID(void) {
	return this->m_rally_station_ID;
}
int CRallyObject::MousePointInStationRect(POINT *loc){
	if (this->m_station_rect.PtInRect(*loc)) {
		if (this->PointInHandleRect(loc)) return IN_HANDLE;
		return IN_RECT;
	}
	else {
		return OUTSIDE;
	}
}
int CRallyObject::HitPointInStationRect(POINT *loc, UINT nFlags){

	// de-select on shift key down in rect if already selected
	if (this->m_selected && (nFlags &MK_SHIFT) && this->m_station_rect.PtInRect(*loc)) { 
		this->m_selected = false;
		return NOT_SELECTED;
	}
	// already selected on shift key down outside rect do nothing
	if (this->m_selected && (nFlags &MK_SHIFT) && !this->m_station_rect.PtInRect(*loc)) { 
		return ALL_READY_SELECTED;
	}
		
	if (this->m_station_rect.PtInRect(*loc)) {
		this->m_selected = true;
		this->m_handle_selected = this->PointInHandleRect(loc);
		return SELECTED;
	}
	else { 
		 this->m_selected = false;
		return NOT_SELECTED;
	}
}
int CRallyObject::HitPointInStationRect(POINT *loc){

	// de-select on shift key down in rect if already selected
	BOOL in_rect;
	in_rect = this->m_station_rect.PtInRect(*loc);
	if (in_rect) { 
		this->m_handle_selected = this->PointInHandleRect(loc);
		if (this->m_selected) {
			return ALL_READY_SELECTED;
		}
		else {
			return SELECTED;
		}
	}
	else {
		this->m_handle_selected = NONE_SELECTED;
		return NOT_SELECTED;
	}

}
int CRallyObject::PointInHandleRect(POINT *loc) {
	CRect handle_rect;
	int which_handle = NONE_SELECTED;
//	this->GetHandleRect(TOP_LEFT,&handle_rect);
//	if (handle_rect.PtInRect(*loc)) which_handle = TOP_LEFT;
	this->GetHandleRect(TOP_RIGHT,&handle_rect);
	handle_rect.InflateRect(4,4);
	if (handle_rect.PtInRect(*loc)) which_handle = TOP_RIGHT;
//	this->GetHandleRect(BOTTOM_LEFT,&handle_rect);
//	if (handle_rect.PtInRect(*loc)) which_handle = BOTTOM_LEFT;
	this->GetHandleRect(BOTTOM_RIGHT,&handle_rect);
	handle_rect.InflateRect(4,4);
	if (handle_rect.PtInRect(*loc)) which_handle = BOTTOM_RIGHT;

	return which_handle;
}
BOOL CRallyObject::RallyRectInRegion(CRgn *select_rgn){
	if (select_rgn->RectInRegion(&this->m_station_rect))
		return true;
	else 
		return false;

}
void CRallyObject::GetHandleRect(int which_handle, RECT *handle_rect) {

	switch (which_handle) {
	case TOP_LEFT:
//		handle_rect->top = this->m_station_rect.top;
//		handle_rect->left = this->m_station_rect.left;
//		handle_rect->right= this->m_station_rect.left + 8;
//		handle_rect->bottom = this->m_station_rect.top + 8;
		break;
	case TOP_RIGHT:
		handle_rect->top = this->m_station_rect.top;
		handle_rect->right = this->m_station_rect.right;
		handle_rect->left= this->m_station_rect.right - 8;
		handle_rect->bottom = this->m_station_rect.top + 8;
		break;
	case BOTTOM_LEFT:
//		handle_rect->top = this->m_station_rect.bottom - 8;
//		handle_rect->left = this->m_station_rect.left;
//		handle_rect->right= this->m_station_rect.left + 8;
//		handle_rect->bottom = this->m_station_rect.bottom;
		break;
	case BOTTOM_RIGHT:
		handle_rect->top = this->m_station_rect.bottom - 8;
		handle_rect->left = this->m_station_rect.right - 8;
		handle_rect->right= this->m_station_rect.right;
		handle_rect->bottom = this->m_station_rect.bottom;
		break;
	}
	return;
}
void CRallyObject::RotateStation(CPoint *point) {
	switch (m_handle_selected) {
	case TOP_LEFT:

		break;
	case TOP_RIGHT:
		float hypo, opp, adj;
		opp = (float)point->y - this->m_station_rect.top;
		adj = (float)point->x - this->m_station_rect.left;
		hypo = (float)_hypot(opp,adj);
		m_M11 = m_M22 = adj/hypo;
		m_M12 = opp/hypo; 
		m_M21 = -(opp/hypo);
		break;
	case BOTTOM_LEFT:

		break;
	case BOTTOM_RIGHT:

		break;
	}
	if (this->m_M11 == 1.0 && this->m_M12 >=0.0 && this->m_M12 <= 1.0) 
		this->m_rotate_text = 0;
	if (this->m_M11 <= 0.0 && this->m_M11 >= -1.0 && this->m_M12 >0.0 && this->m_M12 <= 1.0) 
		this->m_rotate_text = 90;
	if (this->m_M11 < 0.0 && this->m_M11 >= -1.0 && this->m_M12 <=0.0 && this->m_M12 >= -1.0) 
		this->m_rotate_text = 180;
	if (this->m_M11 == 0.0 && this->m_M12 <0.0 && this->m_M12 >= -1.0) 
		this->m_rotate_text = 270;
	this->CalculateEntryAndExitPoints();
	HCURSOR hCursor;
	hCursor = AfxGetApp()->LoadCursor(IDC_SELECT_ROTATE);
	SetCursor(hCursor);
	this->SetStationDegreeRotation();
}

void CRallyObject::SetStationNumber(int station_num) {
	this->m_station_num = station_num;
}
int CRallyObject::GetStationNumber(void) {
	return this->m_station_num;
}
void CRallyObject::SetStringNumber(int string_num) {
	this->m_rally_string_ID = string_num;
}
int CRallyObject::GetStringNumber(void) {
	return this->m_rally_string_ID;
}
void CRallyObject::SetAKCNumber(int akc_num) {
this->m_akc_number = akc_num;
}
int CRallyObject::GetAKCNumber(void) {

	return this->m_akc_number;
}
void CRallyObject::SetStationMidPointFromRect(void) {
	this->m_midPoint.x = this->m_station_rect.right - (this->m_width/2);
	this->m_midPoint.y = this->m_station_rect.bottom - (this->m_height/2);
	this->CalculateEntryAndExitPoints();
}
void CRallyObject::SetStationMidPoint(POINT *mid_point) {
	CPoint offset_point;
	offset_point.x = mid_point->x - this->m_midPoint.x;
	offset_point.y = mid_point->y - this->m_midPoint.y;
	this->m_midPoint = *mid_point;
	this->CalculateEntryAndExitPoints();
	this->m_station_rect.OffsetRect(offset_point);
	this->m_station_rect.NormalizeRect();
	
}
POINT CRallyObject::GetStationMidPoint(void) {
	return this->m_midPoint;
}
void CRallyObject::SetStationWidthHeight(int wd, int ht) {
	this->m_width = wd;
	this->m_height = ht;
	this->SetStationMidPointFromRect();
}
void CRallyObject::GetStationWidthHeight(int *wd, int *ht) {
	*wd = this->m_width;
	*ht = this->m_height;
}
void CRallyObject::SetStationRotateMeasurements(float M11, float M12, float M21, float M22) {
	this->m_M11 = M11;
	this->m_M12 = M12;
	this->m_M21 = M21;
	this->m_M22 = M22;
	if (this->m_M11 == 1.0 && this->m_M12 >=0.0 && this->m_M12 <= 1.0) 
		this->m_rotate_text = 0;
	if (this->m_M11 <= 0.0 && this->m_M11 >= -1.0 && this->m_M12 >0.0 && this->m_M12 <= 1.0) 
		this->m_rotate_text = 90;
	if (this->m_M11 < 0.0 && this->m_M11 >= -1.0 && this->m_M12 <=0.0 && this->m_M12 >= -1.0) 
		this->m_rotate_text = 180;
	if (this->m_M11 == 0.0 && this->m_M12 <0.0 && this->m_M12 >= -1.0) 
		this->m_rotate_text = 270;
	this->CalculateEntryAndExitPoints();
	this->SetStationDegreeRotation();
}
void CRallyObject::GetStationRotateMeasurements(float *M11, float *M12, float *M21, float *M22) {
	*M11 = this->m_M11;
	*M12 = this->m_M12;
	*M21 = this->m_M21;
	*M22 = this->m_M22;
}
// for the undo/redo
POSITION CRallyObject::GetUndoRedoPostion(void) {
	return this->m_pos_in_rally_list;
}
void CRallyObject::SetUndoRedoPosition(POSITION pos_in_rally_list) {
	this->m_pos_in_rally_list = pos_in_rally_list;
}
int CRallyObject::GetUndoRedoAction(void) {
	return this->m_undo_action;
}
void CRallyObject::SetUndoRedoAction(int undo_action) {
	this->m_undo_action = undo_action;
}
void CRallyObject::SetSelectedFlag(BOOL selected) {
	this->m_selected = selected;
}
BOOL CRallyObject::GetSelectedFlag(void) {
	return this->m_selected;
}
void CRallyObject::SetCustomEntrancePoint(CPoint *entrance){
	this->m_cus_entrance = *entrance;
}
void CRallyObject::GetCustomEntrancePoint(CPoint *entrance) {
//	*entrance = this->m_cus_entrance;
	*entrance = this->m_entrance;
}
void CRallyObject::SetCustomExitPoint(CPoint *exit){
	this->m_cus_exit = *exit;
}
void CRallyObject::GetCustomExitPoint(CPoint *exit) {
//	*exit = this->m_cus_exit;
	*exit = this->m_exit;
}
void CRallyObject::CalculatePylonEntryAndExitPoints(CRect *pylon_rect, int where_cones) {
	float adj, opp;
	int hyp;
	if (this->m_has_pylons) {
		hyp = this->m_midPoint.x - pylon_rect->left;
		this->m_pylon_entrance.x = pylon_rect->left;
		this->m_pylon_exit.y = this->m_pylon_entrance.y = pylon_rect->top + pylon_rect->Height()/2;
		this->m_pylon_exit.x = pylon_rect->right;
		adj = hyp * this->m_M11;
		opp = hyp * this->m_M12;
		this->m_pylon_entrance.x = this->m_pylon_entrance.x + (int)(hyp - adj);
		this->m_pylon_entrance.y = (int)(this->m_pylon_entrance.y - opp);
		switch (where_cones) {
		case CONE_MIDDLE:
			hyp = pylon_rect->Width()/2;
			adj = hyp * this->m_M11;
			opp = hyp * this->m_M12;
			this->m_pylon_exit.x = this->m_midPoint.x + (int)adj;
			this->m_pylon_exit.y = (int)(this->m_midPoint.y + opp);
			break;
		case CONE_ENTRANCE:
			hyp = pylon_rect->Width() + (pylon_rect->left - this->m_midPoint.x);
			adj = hyp * this->m_M11;
			opp = hyp * this->m_M12;
			this->m_pylon_exit.x = this->m_pylon_exit.x - (int)(hyp - adj);
			this->m_pylon_exit.y = (int)(this->m_pylon_exit.y + opp);
			break;
		case CONE_EXIT:
			hyp = this->m_midPoint.x - pylon_rect->right;
			adj = hyp * this->m_M11;
			opp = hyp * this->m_M12;
			this->m_pylon_exit.x = this->m_pylon_exit.x + (int)(hyp - adj);
			this->m_pylon_exit.y = (int)(this->m_pylon_exit.y - opp);
			break;
		}
		if (this->m_rally_string_ID == ID_DRAW_SPIRAL_LEFT) {
			this->m_pylon_entrance = this->m_pylon_exit;
		}
		if (this->m_rally_string_ID == ID_DRAW_SPIRAL_RIGHT) {
			this->m_pylon_exit = this->m_pylon_entrance;
		}
		if (this->m_rally_string_ID == ID_DRAW_WEAVE_TWICE) {
			this->m_pylon_exit = this->m_pylon_entrance;
		}
	}
}
void CRallyObject::CalculateEntryAndExitPoints(void) {
	switch(this->m_rotate_text) {
	case 0:
		this->m_entrance.x = this->m_exit.x = this->m_midPoint.x;
		this->m_entrance.y = this->m_midPoint.y + (this->m_height/2);
		this->m_exit.y = this->m_midPoint.y - (this->m_height/2);
		break;
	case 90:
		this->m_entrance.y = this->m_exit.y = this->m_midPoint.y;
		this->m_entrance.x = this->m_midPoint.x - (this->m_width/2);
		this->m_exit.x = this->m_midPoint.x + (this->m_width/2);
		break;
	case 180:
		this->m_entrance.x = this->m_exit.x = this->m_midPoint.x;
		this->m_entrance.y = this->m_midPoint.y - (this->m_height/2);
		this->m_exit.y = this->m_midPoint.y + (this->m_height/2);
		break;
	case 270:
		this->m_entrance.y = this->m_exit.y = this->m_midPoint.y;
		this->m_entrance.x = this->m_midPoint.x + (this->m_width/2);
		this->m_exit.x = this->m_midPoint.x - (this->m_width/2);
		break;
		break;
	}

}
void CRallyObject::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_rally_station_ID;
		ar << m_rally_string_ID;
		ar << m_station_num;
		ar << m_akc_number;
		ar << m_midPoint;
		ar << m_width;
		ar << m_height;
		ar << m_M11;
		ar << m_M12;
		ar << m_M21;
		ar << m_M22;
		ar << m_station_rect;
		ar << this->m_rotate_text;
		ar << this->m_cus_entrance;
		ar << this->m_cus_exit;
		ar << this->m_stat_desc;
		ar << this->m_do_rotate_text;
	}
	else
	{
		// TODO: add loading code here
		int version = ar.GetObjectSchema();
		CDogRunApp* pApp = (CDogRunApp*)AfxGetApp();
		if (g_convert_course && version != 1) version = 0;
		switch (version) {
		case 0:
			ar >> m_rally_station_ID;
			ar >> m_rally_string_ID;
			ar >> m_station_num;
			ar >> m_akc_number;
			ar >> m_midPoint;
			ar >> m_width;
			ar >> m_height;
			ar >> m_M11;
			ar >> m_M12;
			ar >> m_M21;
			ar >> m_M22;
			ar >> m_station_rect;
			ar >> this->m_rotate_text;
			ar >> this->m_cus_entrance;
			ar >> this->m_cus_exit;
			break;
		case 1:
			ar >> m_rally_station_ID;
			ar >> m_rally_string_ID;
			ar >> m_station_num;
			ar >> m_akc_number;
			ar >> m_midPoint;
			ar >> m_width;
			ar >> m_height;
			ar >> m_M11;
			ar >> m_M12;
			ar >> m_M21;
			ar >> m_M22;
			ar >> m_station_rect;
			ar >> this->m_rotate_text;
			break;
		case 2:
			ar >> m_rally_station_ID;
			ar >> m_rally_string_ID;
			ar >> m_station_num;
			ar >> m_akc_number;
			ar >> m_midPoint;
			ar >> m_width;
			ar >> m_height;
			ar >> m_M11;
			ar >> m_M12;
			ar >> m_M21;
			ar >> m_M22;
			ar >> m_station_rect;
			ar >> this->m_rotate_text;
			ar >> this->m_cus_entrance;
			ar >> this->m_cus_exit;
			// will need to comment out these two lines for old file conversion!!!
			ar >> this->m_stat_desc;
			ar >> this->m_do_rotate_text;
			break;
		case 3:
			ar >> m_rally_station_ID;
			ar >> m_rally_string_ID;
			ar >> m_station_num;
			ar >> m_akc_number;
			ar >> m_midPoint;
			ar >> m_width;
			ar >> m_height;
			ar >> m_M11;
			ar >> m_M12;
			ar >> m_M21;
			ar >> m_M22;
			ar >> m_station_rect;
			ar >> this->m_rotate_text;
			ar >> this->m_cus_entrance;
			ar >> this->m_cus_exit;
			ar >> this->m_stat_desc;
			ar >> this->m_do_rotate_text;
			break;
		}

		this->m_selected = FALSE;
		this->SetStationMidPointFromRect();
		this->SetStationDegreeRotation();

	}
}
HANDLE CRallyObject::DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal)
{

	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;			//bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = ::GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE)lpbi 			// address for bitmap bits
				+ (bi.biSize + nColors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	::ReleaseDC(NULL,hDC);

	return hDIB;
}


void CRallyObject::SetStationType(int type_station)
{
	this->m_type_station = type_station;
}

int CRallyObject::GetStationType()
{
	return this->m_type_station;
}

void CRallyObject::ResizeStation(POINT *p_loc)
{
	this->m_station_rect.bottom = p_loc->y;
	this->m_station_rect.right = p_loc->x;
	this->m_width = m_station_rect.right - m_station_rect.left;
	this->m_height = m_station_rect.bottom - m_station_rect.top;
	this->SetStationMidPointFromRect();

}

void CRallyObject::SetStationDescription(int stat_desc)
{
	this->m_stat_desc = stat_desc;
}

int CRallyObject::GetStationDescription()
{
	return this->m_stat_desc;
}
void CRallyObject::SetRotateText(BOOL do_rotate_text)
{
	this->m_do_rotate_text = do_rotate_text;
}

BOOL CRallyObject::GetRotateText()
{
	return this->m_do_rotate_text;
}


void CRallyObject::SetStationRect(int feet, double pixels_per_ht, double pixels_per_wd)
{
	CBitmap bmp;

	if (bmp.LoadBitmap(this->m_rally_station_ID)) 	{
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		double ht_feet;
		double width, height;
		width = bmpInfo.bmWidth;
		height = bmpInfo.bmHeight;
		double ratio = height/width;
		ht_feet = ceil(ratio * feet);
		
		m_station_rect.left = this->m_midPoint.x - ((feet*(long)pixels_per_wd)/2);
		m_station_rect.right = this->m_midPoint.x + ((feet*(long)pixels_per_wd)/2);
		m_station_rect.top = this->m_midPoint.y - (((int)ht_feet*(long)pixels_per_ht)/2);
		m_station_rect.bottom = this->m_midPoint.y + (((int)ht_feet*(long)pixels_per_ht)/2);
		this->m_width = m_station_rect.right - m_station_rect.left;
		this->m_height = m_station_rect.bottom - m_station_rect.top;
		this->SetStationMidPointFromRect();
	}

}

int CRallyObject::GetRallyStationSizeInFeet(double pixels_per_wd)
{
	double station_width;
	int actual_width;
	station_width = ceil(this->m_width / pixels_per_wd);
	actual_width = (int)station_width;
	return actual_width;

}

void CRallyObject::CalculateRotateMeasurements(double degree_rotation)
{
	double pi = 3.1415926535;

	m_M11 = m_M22 = (float)cos((degree_rotation * pi)/180);
	m_M12 = (float)sin((degree_rotation * pi)/180); 
	m_M21 = (float)-sin((degree_rotation * pi)/180);	
	this->m_rotate_degrees = degree_rotation;
}

void CRallyObject::SetStationDegreeRotation()
{
	double arc_sine, arc_cosine;
	double sine_degrees, cos_degrees;
	double pi = 3.1415926535;
	arc_cosine = acos(this->m_M11);
	arc_sine = asin(this->m_M12);
	sine_degrees = (arc_sine * 180.0) / pi;
	cos_degrees = (arc_cosine * 180.0)/ pi;
	if (sine_degrees < 0) this->m_rotate_degrees = 360.0 - cos_degrees;
	else this->m_rotate_degrees = cos_degrees;
}
