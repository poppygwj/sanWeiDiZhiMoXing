#if !defined(AFX_SETCOLORDLG_H__318FFBB7_3DB2_4ABD_A7F5_110DEC91AA93__INCLUDED_)
#define AFX_SETCOLORDLG_H__318FFBB7_3DB2_4ABD_A7F5_110DEC91AA93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetColorDlg dialog

class CSetColorDlg : public CDialog
{
// Construction
public:
	CSetColorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetColorDlg)
	enum { IDD = IDD_DIALOG1 };
	float	m_colorRed;
	float	m_colorBlue;
	float	m_colorGreen;
	BOOL	m_maskBlue;
	BOOL	m_maskRed;
	BOOL	m_maskGreen;
	float	m_matAmbientB;
	float	m_matAmbientG;
	float	m_matAmbientR;
	float	m_matDiffuseB;
	float	m_matDiffuseG;
	float	m_matEmissionB;
	float	m_matEmissionG;
	float	m_matEmissionR;
	float	m_matShininess;
	float	m_matSpecularB;
	float	m_matSpecularG;
	float	m_matSpecularR;
	BOOL	m_bMaterialOnOff;
	float	m_matDiffuseR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetColorDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCOLORDLG_H__318FFBB7_3DB2_4ABD_A7F5_110DEC91AA93__INCLUDED_)
