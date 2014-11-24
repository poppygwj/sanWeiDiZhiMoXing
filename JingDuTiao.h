#if !defined(AFX_JINGDUTIAO_H__DF339559_A618_4D5F_B200_0D4062BAACD1__INCLUDED_)
#define AFX_JINGDUTIAO_H__DF339559_A618_4D5F_B200_0D4062BAACD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JingDuTiao.h : header file
//
#include <Resource.h>
/////////////////////////////////////////////////////////////////////////////
// CJingDuTiao dialog

class CJingDuTiao : public CDialog
{
// Construction
public:
	CJingDuTiao(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJingDuTiao)
	enum { IDD = IDD_DIALOG3 };
	CProgressCtrl	m_ctrlProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJingDuTiao)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJingDuTiao)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGDUTIAO_H__DF339559_A618_4D5F_B200_0D4062BAACD1__INCLUDED_)
