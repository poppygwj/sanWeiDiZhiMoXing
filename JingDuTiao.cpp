// JingDuTiao.cpp : implementation file
//

#include "stdafx.h"
#include "DrawObject.h"
#include "JingDuTiao.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJingDuTiao dialog


CJingDuTiao::CJingDuTiao(CWnd* pParent /*=NULL*/)
	: CDialog(CJingDuTiao::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJingDuTiao)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CJingDuTiao::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJingDuTiao)
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJingDuTiao, CDialog)
	//{{AFX_MSG_MAP(CJingDuTiao)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJingDuTiao message handlers

void CJingDuTiao::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
	//CDialog::OnTimer(nIDEvent);
	m_ctrlProgress.SetPos(CGlobal::progress);
	if(CGlobal::progress == -1)
		this->EndDialog(true);
}

void CJingDuTiao::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	this->KillTimer(1);
	this->SetTimer(1,20, NULL);
	m_ctrlProgress.SetRange(1,1000);
}
