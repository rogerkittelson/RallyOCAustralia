// CRallyObject.h : interface of the CRallyObject class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
/////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Forward declaration of data structure class
//class CRallyObject;

/////////////////////////////////////////////////////////////////////////////
// class CRallyObject
//
// A CRallyObject is the contains all of the information needed for
// a stations

class CRallyTracker : public CRectTracker
{
public:
	CRallyTracker();

protected:

// Attributes
protected:

public:
void DrawTrackerRect( LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd );
public:
	BOOL m_size_to_fit;
	CDC* pDC;
	CSize m_sizeTotal;
	void ChangeDCToSizeToWindow(CDC* pDC, CWnd* pWnd);
	void FixRectInFitScreenModeLPtoDP(RECT *rect, CDC *pDC);

// Operations
public:

public:

};

