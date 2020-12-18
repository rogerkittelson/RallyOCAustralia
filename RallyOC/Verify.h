// Verify.h: interface for the Verify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERIFY_H__F218B8E6_C573_433A_A55B_E3AE60D781AA__INCLUDED_)
#define AFX_VERIFY_H__F218B8E6_C573_433A_A55B_E3AE60D781AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DogRunDoc.h"

enum start_finish {
	BOTH,
	START_ONLY,
	FINISH_ONLY,
	NEITHER
};
class Verify  
{
public:
	CString APDTStationStatistics(int station_list[71][2]);
	void CheckLevelThreeCourse(int station_list[][2], CString *error_report);
	void CheckLevelTwoCourse(int station_list[71][2], CString *error_report);
	void CheckLevelOneCourse(int station_list[71][2], CString *error_report);
	CString GetStationStatistics(void);
	Verify();
	virtual ~Verify();
	void VerifyCourse(CDogRunDoc *p_doc_to_verify, BOOL show_dialog, int type_of_course);
	
protected:
	int FindAPDTStartFinish(int station_list[61][2]);
	void FillOutAPDTStationList(CObList *rallyList, int station_list[61][2]);
	CString StationStatistics(int station_list[51][2]);
	void FillOutStationList(CObList *rallyList,int station_list[51][2]);
	int FindStartFinish(int station_list[51][2]);
	BOOL FindHonorStation(int station_list[51][2]);
	void CheckNoviceCourse(int station_list[51][2], CString *error_report);
	void CheckAdvancedCourse(int station_list[51][2], CString *error_report);
	void CheckExcellentCourse(int station_list[51][2], CString *error_report);
	void CheckMasterCourse(int station_list[51][2], CString *error_report);
	void CheckForSingleStations(int station_list[51][2], CString *error_report);
	void ChangePaceBackToNormal(CString *error_report);
	void CheckConsectiveJumpStations(CString *error_report);
	int GetStationaryCount(int station_list[51][2], CString *stat_exe_loc);
	CString CreateCourseHeader(CDogRunDoc *p_doc_to_verify);
	int m_num_stations[77];
	int m_num_novice;
	int m_num_advanced;
	int m_num_excellent;
	int m_num_master;
	int m_num_stationary;
	CString m_station_stats;
private:
	void CheckForLinkedStations(CString *error_report);
};

#endif // !defined(AFX_VERIFY_H__F218B8E6_C573_433A_A55B_E3AE60D781AA__INCLUDED_)
