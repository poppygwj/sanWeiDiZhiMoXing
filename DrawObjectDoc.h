// DrawObjectDoc.h : interface of the CDrawObjectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLDOC_H__D8D007EA_6A74_40F5_A776_6C75DFEE163C__INCLUDED_)
#define AFX_MYSDOPENGLDOC_H__D8D007EA_6A74_40F5_A776_6C75DFEE163C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawObjectDoc : public CDocument
{
protected: // create from serialization only
	CDrawObjectDoc();
	DECLARE_DYNCREATE(CDrawObjectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawObjectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawObjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawObjectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLDOC_H__D8D007EA_6A74_40F5_A776_6C75DFEE163C__INCLUDED_)
