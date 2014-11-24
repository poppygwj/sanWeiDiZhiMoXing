// SetColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawObject.h"
#include "SetColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetColorDlg dialog


CSetColorDlg::CSetColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetColorDlg)
	m_colorRed = 0.0f;
	m_colorBlue = 0.0f;
	m_colorGreen = 0.0f;
	m_maskBlue = FALSE;
	m_maskRed = FALSE;
	m_maskGreen = FALSE;
	m_matAmbientB = 0.0f;
	m_matAmbientG = 0.0f;
	m_matAmbientR = 0.0f;
	m_matDiffuseB = 0.0f;
	m_matDiffuseG = 0.0f;
	m_matEmissionB = 0.0f;
	m_matEmissionG = 0.0f;
	m_matEmissionR = 0.0f;
	m_matShininess = 0.0f;
	m_matSpecularB = 0.0f;
	m_matSpecularG = 0.0f;
	m_matSpecularR = 0.0f;
	m_bMaterialOnOff = FALSE;
	m_matDiffuseR = 0.0f;
	//}}AFX_DATA_INIT
}


void CSetColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetColorDlg)
	DDX_Text(pDX, IDC_COLOR_RED, m_colorRed);
	DDV_MinMaxFloat(pDX, m_colorRed, 0.f, 1.f);
	DDX_Text(pDX, IDC_COLOR_BLUE, m_colorBlue);
	DDV_MinMaxFloat(pDX, m_colorBlue, 0.f, 1.f);
	DDX_Text(pDX, IDC_COLOR_GREEN, m_colorGreen);
	DDV_MinMaxFloat(pDX, m_colorGreen, 0.f, 1.f);
	DDX_Check(pDX, IDC_COLOR_MASK_B, m_maskBlue);
	DDX_Check(pDX, IDC_COLOR_MASK_R, m_maskRed);
	DDX_Check(pDX, IDC_COLOR_MASK_G, m_maskGreen);
	DDX_Text(pDX, IDC_M_AMBIENT_B, m_matAmbientB);
	DDV_MinMaxFloat(pDX, m_matAmbientB, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_AMBIENT_G, m_matAmbientG);
	DDV_MinMaxFloat(pDX, m_matAmbientG, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_AMBIENT_R, m_matAmbientR);
	DDV_MinMaxFloat(pDX, m_matAmbientR, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_DIFFUSE_B, m_matDiffuseB);
	DDV_MinMaxFloat(pDX, m_matDiffuseB, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_DIFFUSE_G, m_matDiffuseG);
	DDV_MinMaxFloat(pDX, m_matDiffuseG, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_EMISSION_B, m_matEmissionB);
	DDV_MinMaxFloat(pDX, m_matEmissionB, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_EMISSION_G, m_matEmissionG);
	DDV_MinMaxFloat(pDX, m_matEmissionG, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_EMISSION_R, m_matEmissionR);
	DDV_MinMaxFloat(pDX, m_matEmissionR, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_SHININESS, m_matShininess);
	DDX_Text(pDX, IDC_M_SPECULAR_B, m_matSpecularB);
	DDV_MinMaxFloat(pDX, m_matSpecularB, 0.f, 1.f);
	DDX_Text(pDX, IDC_M_SPECULAR_G, m_matSpecularG);
	DDX_Text(pDX, IDC_M_SPECULAR_R, m_matSpecularR);
	DDX_Check(pDX, IDC_MATERIAL_FLAG, m_bMaterialOnOff);
	DDX_Text(pDX, IDC_M_DIFFUSE_R, m_matDiffuseR);
	DDV_MinMaxFloat(pDX, m_matDiffuseR, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetColorDlg, CDialog)
	//{{AFX_MSG_MAP(CSetColorDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetColorDlg message handlers
