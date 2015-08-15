#if !defined(AFX_OBJECTPROPDLG_H__54F7F54B_2F41_4870_9102_295839BD5827__INCLUDED_)
#define AFX_OBJECTPROPDLG_H__54F7F54B_2F41_4870_9102_295839BD5827__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectPropDlg.h : header file
//
#include "SpecialObj.h"
/////////////////////////////////////////////////////////////////////////////
// ObjectPropDlg dialog

class ObjectPropDlg : public CDialog
{
// Construction
public:
	ObjectPropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ObjectPropDlg)
	enum { IDD = IDD_OBJECT_PROP };
	CString	m_custom_size;
	int		m_size_object;
	CString	m_rotate_degrees;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ObjectPropDlg)
	public:
	virtual int DoModal(SpecialObj *p_special_object);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	SpecialObj *mp_special_object;
	double m_degree_rotation;
	// Generated message map functions
	//{{AFX_MSG(ObjectPropDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTPROPDLG_H__54F7F54B_2F41_4870_9102_295839BD5827__INCLUDED_)
