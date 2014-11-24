// DrawObjectDoc.cpp : implementation of the CDrawObjectDoc class
//

#include "stdafx.h"
#include "DrawObject.h"

#include "DrawObjectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectDoc

IMPLEMENT_DYNCREATE(CDrawObjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawObjectDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawObjectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectDoc construction/destruction

CDrawObjectDoc::CDrawObjectDoc()
{
	// TODO: add one-time construction code here

}

CDrawObjectDoc::~CDrawObjectDoc()
{
}

BOOL CDrawObjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawObjectDoc serialization

void CDrawObjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectDoc diagnostics

#ifdef _DEBUG
void CDrawObjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawObjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectDoc commands
