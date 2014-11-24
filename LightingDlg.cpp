// LightingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawObject.h"
#include "LightingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightingDlg dialog


CLightingDlg::CLightingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLightingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightingDlg)
	m_lightAmbientB = 0.0f;
	m_lightAmbientG = 0.0f;
	m_lightAmbientR = 0.0f;
	m_lightDiffuseB = 0.0f;
	m_lightDiffuseG = 0.0f;
	m_lightDiffuseR = 0.0f;
	m_lightPositionX = 0.0f;
	m_lightPositionY = 0.0f;
	m_lightPositionZ = 0.0f;
	m_lightSpecularB = 0.0f;
	m_lightSpecularG = 0.0f;
	m_lightSpecularR = 0.0f;
	//}}AFX_DATA_INIT
}


void CLightingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightingDlg)
	DDX_Text(pDX, IDC_L_AMBIENT_B, m_lightAmbientB);
	DDV_MinMaxFloat(pDX, m_lightAmbientB, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_AMBIENT_G, m_lightAmbientG);
	DDV_MinMaxFloat(pDX, m_lightAmbientG, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_AMBIENT_R, m_lightAmbientR);
	DDV_MinMaxFloat(pDX, m_lightAmbientR, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_DIFFUSE_B, m_lightDiffuseB);
	DDV_MinMaxFloat(pDX, m_lightDiffuseB, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_DIFFUSE_G, m_lightDiffuseG);
	DDV_MinMaxFloat(pDX, m_lightDiffuseG, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_DIFFUSE_R, m_lightDiffuseR);
	DDV_MinMaxFloat(pDX, m_lightDiffuseR, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_POSITION_X, m_lightPositionX);
	DDX_Text(pDX, IDC_L_POSITION_Y, m_lightPositionY);
	DDX_Text(pDX, IDC_L_POSITION_Z, m_lightPositionZ);
	DDX_Text(pDX, IDC_L_SPECULAR_B, m_lightSpecularB);
	DDV_MinMaxFloat(pDX, m_lightSpecularB, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_SPECULAR_G, m_lightSpecularG);
	DDV_MinMaxFloat(pDX, m_lightSpecularG, 0.f, 1.f);
	DDX_Text(pDX, IDC_L_SPECULAR_R, m_lightSpecularR);
	DDV_MinMaxFloat(pDX, m_lightSpecularR, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightingDlg, CDialog)
	//{{AFX_MSG_MAP(CLightingDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightingDlg message handlers
