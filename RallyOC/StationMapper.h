

class StationMapper
{
public:
	StationMapper(void);
	~StationMapper(void);
	static CString AKCNumberStringFromObjectID(int objectid);
	static int BitMapFromObjectID(int objectid);
	static int GetBitMapFromAKCNumber(int akc_number);
	static CString GetAKCDescrptionFromObjectID(int objectid);
	static CString GetAKCDescrptionFromAKCNumber(int akc_number);
	static CString GetAKCDetailedDescrptionFromObjectID(int objectid);
	static CString GetAKCDetailedDescrptionFromAKCNumber(int akc_number);
	static int ObjectIDFromAKCNumber(int akc_number);
	static void GetAKCNoviceList(CStringList& Items);
	static void GetAKCAdvancedList(CStringList& Items);
	static void GetAKCExcellentList(CStringList& Items);
	static void GetStationDescriptionByAKCType(int type_class, CStringList& Items);
	static int GetComboBoxSelectionFromAKCid(int akc_number);
	static int GetAKCidFromComboBoxSelection(int choice);
};
