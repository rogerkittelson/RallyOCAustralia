// MyFont.h: interface for the MyFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFONT_H__5D2D1644_DC36_4A64_B603_B8F801DDD99F__INCLUDED_)
#define AFX_MYFONT_H__5D2D1644_DC36_4A64_B603_B8F801DDD99F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyFont : public CObject  
{
public:
	void SetColorReference(COLORREF color_ref);
	COLORREF GetColorReference(void);
	void SetFont(CFont *p_text_font);
	void GetLogFont(LOGFONT *p_log_font);
	virtual void Serialize(CArchive &ar);
	void SetFont(LOGFONT *p_log_font);
	MyFont(LOGFONT *p_log_font, COLORREF color_ref);
	virtual ~MyFont();
private:
	MyFont();
	DECLARE_SERIAL(MyFont)
	// logfont
	LONG m_lfHeight; 
	LONG m_lfWidth; 
	LONG m_lfEscapement; 
	LONG m_lfOrientation; 
	LONG m_lfWeight; 
	BYTE m_lfItalic; 
	BYTE m_lfUnderline; 
	BYTE m_lfStrikeOut; 
	BYTE m_lfCharSet; 
	BYTE m_lfOutPrecision; 
	BYTE m_lfClipPrecision; 
	BYTE m_lfQuality; 
	BYTE m_lfPitchAndFamily; 
	CString m_lfFaceName; 
	// color
	COLORREF m_font_color;

};

#endif // !defined(AFX_MYFONT_H__5D2D1644_DC36_4A64_B603_B8F801DDD99F__INCLUDED_)
