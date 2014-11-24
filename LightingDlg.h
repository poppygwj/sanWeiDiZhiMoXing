#if !defined(AFX_LIGHTINGDLG_H__02C0DE91_F40D_4785_BBBD_F28662E1439A__INCLUDED_)
#define AFX_LIGHTINGDLG_H__02C0DE91_F40D_4785_BBBD_F28662E1439A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightingDlg dialog

class CLightingDlg : public CDialog
{
// Construction
public:
	CLightingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightingDlg)
	enum { IDD = IDD_DIALOG2 };
	float	m_lightAmbientB;
	float	m_lightAmbientG;
	float	m_lightAmbientR;
	float	m_lightDiffuseB;
	float	m_lightDiffuseG;
	float	m_lightDiffuseR;
	float	m_lightPositionX;
	float	m_lightPositionY;
	float	m_lightPositionZ;
	float	m_lightSpecularB;
	float	m_lightSpecularG;
	float	m_lightSpecularR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightingDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTINGDLG_H__02C0DE91_F40D_4785_BBBD_F28662E1439A__INCLUDED_)
