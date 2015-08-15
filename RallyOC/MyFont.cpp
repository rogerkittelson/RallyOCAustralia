// MyFont.cpp: implementation of the MyFont class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DogRun.h"
#include "MyFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(MyFont, CObject, VERSIONABLE_SCHEMA | 1)

MyFont::MyFont()
{
	// This empty constructor should be used by serialization only
}
MyFont::MyFont(LOGFONT *p_log_font, COLORREF color_ref)
{
	this->SetFont(p_log_font);
	this->m_font_color = color_ref;
}

MyFont::~MyFont()
{

}

void MyFont::Serialize(CArchive &ar)
{

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << this->m_lfHeight;
		ar << this->m_lfWidth;
		ar << this->m_lfEscapement;
		ar << this->m_lfOrientation;
		ar << this->m_lfWeight;
		ar << this->m_lfItalic;
		ar << this->m_lfUnderline;
		ar << this->m_lfStrikeOut;
		ar << this->m_lfCharSet;
		ar << this->m_lfOutPrecision;
		ar << this->m_lfClipPrecision;
		ar << this->m_lfQuality;		
		ar << this->m_lfPitchAndFamily;
		ar << this->m_lfFaceName;
		ar << this->m_font_color;

	}
	else
	{
		// TODO: add loading code here
		int version = ar.GetObjectSchema();
		switch (version) {
			case 1:
			ar >> this->m_lfHeight;
			ar >> this->m_lfWidth;
			ar >> this->m_lfEscapement;
			ar >> this->m_lfOrientation;
			ar >> this->m_lfWeight;
			ar >> this->m_lfItalic;
			ar >> this->m_lfUnderline;
			ar >> this->m_lfStrikeOut;
			ar >> this->m_lfCharSet;
			ar >> this->m_lfOutPrecision;
			ar >> this->m_lfClipPrecision;
			ar >> this->m_lfQuality;		
			ar >> this->m_lfPitchAndFamily;
			ar >> this->m_lfFaceName;
			ar >> this->m_font_color;
				break;
		case 2:

			break;
		}
	}
}

void MyFont::SetFont(LOGFONT *p_log_font)
{

	this->m_lfHeight = p_log_font->lfHeight;
	this->m_lfWidth = p_log_font->lfWidth;
	this->m_lfOrientation = p_log_font->lfOrientation;
	this->m_lfEscapement = p_log_font->lfEscapement;
	this->m_lfWeight = p_log_font->lfWeight;
	this->m_lfItalic = p_log_font->lfItalic;
	this->m_lfUnderline = p_log_font->lfUnderline;
	this->m_lfStrikeOut = p_log_font->lfStrikeOut;
	this->m_lfCharSet = p_log_font->lfCharSet;
	this->m_lfOutPrecision = p_log_font->lfOutPrecision;
	this->m_lfClipPrecision = p_log_font->lfClipPrecision;
	this->m_lfQuality = p_log_font->lfQuality;		
	this->m_lfPitchAndFamily = p_log_font->lfPitchAndFamily;
	this->m_lfFaceName = p_log_font->lfFaceName;
}

void MyFont::GetLogFont(LOGFONT *p_log_font)
{

	p_log_font->lfHeight = this->m_lfHeight;
	p_log_font->lfWidth = this->m_lfWidth;
	p_log_font->lfEscapement= this->m_lfEscapement;
	p_log_font->lfOrientation = this->m_lfOrientation;
	p_log_font->lfWeight = this->m_lfWeight;
	p_log_font->lfItalic = this->m_lfItalic;
	p_log_font->lfUnderline = this->m_lfUnderline;
	p_log_font->lfStrikeOut = this->m_lfStrikeOut;
	p_log_font->lfCharSet = this->m_lfCharSet;
	p_log_font->lfOutPrecision = this->m_lfOutPrecision;
	p_log_font->lfClipPrecision = this->m_lfClipPrecision;
	p_log_font->lfQuality = this->m_lfQuality;
	p_log_font->lfPitchAndFamily = this->m_lfPitchAndFamily;
	strcpy(p_log_font->lfFaceName, this->m_lfFaceName);

}

void MyFont::SetFont(CFont *p_text_font)
{
	LOGFONT log_font;
	p_text_font->GetLogFont(&log_font);

	this->m_lfHeight = log_font.lfHeight;
	this->m_lfWidth = log_font.lfWidth;
	this->m_lfEscapement = log_font.lfEscapement;
	this->m_lfOrientation = log_font.lfOrientation;
	this->m_lfWeight = log_font.lfWeight;
	this->m_lfItalic = log_font.lfItalic;
	this->m_lfUnderline = log_font.lfUnderline;
	this->m_lfStrikeOut = log_font.lfStrikeOut;
	this->m_lfCharSet = log_font.lfCharSet;
	this->m_lfOutPrecision = log_font.lfOutPrecision;
	this->m_lfClipPrecision = log_font.lfClipPrecision;
	this->m_lfQuality = log_font.lfQuality;		
	this->m_lfPitchAndFamily = log_font.lfPitchAndFamily;
	this->m_lfFaceName = log_font.lfFaceName;

}


COLORREF MyFont::GetColorReference()
{
	return this->m_font_color;
}

void MyFont::SetColorReference(COLORREF color_ref)
{
	this->m_font_color = color_ref;
}
