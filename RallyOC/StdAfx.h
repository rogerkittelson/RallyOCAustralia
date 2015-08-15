// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__AE14234F_47C6_43BC_B8E6_ADF3C9A4A183__INCLUDED_)
#define AFX_STDAFX_H__AE14234F_47C6_43BC_B8E6_ADF3C9A4A183__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define OEMRESOURCE
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxtempl.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "memdc.h"
#ifndef UINT8
	#define	INT8	char
	#define UINT8	unsigned char
	#define	INT16	short
	#define UINT16	unsigned short
	#define	INT32	int
	#define UINT32	unsigned int
	#define	INT64	__int64
	#define UINT64	unsigned __int64
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AE14234F_47C6_43BC_B8E6_ADF3C9A4A183__INCLUDED_)
