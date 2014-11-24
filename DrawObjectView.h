// DrawObjectView.h : interface of the CDrawObjectView class
//
/////////////////////////////////////////////////////////////////////////////
#include <GRDECL.h>
//#include <JingDuTiao.h>;
#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

DECLARE_HANDLE(HDIB);

class CDrawObjectView : public CView
{
protected: // create from serialization only
	CDrawObjectView();
	DECLARE_DYNCREATE(CDrawObjectView)

// Attributes
public:
	CDrawObjectDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawObjectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_startTo;
	float halfWidth;
	float halfHeight;
	float centerY;
	float centerX;
	float translateY;
	float translateX;
	void CalculateNormal(Point3D point1,Point3D point2,Point3D point3,GLdouble* dNormal);
	void CreateMaterial();
	GLfloat m_materialAmb[4];
	GLfloat m_materialDif[4];
	GLfloat m_materialSpe[4];
	GLfloat m_materialEmi[4];
	GLfloat m_matshininess;
	BOOL    m_bMaterial;

	void CreateLights();
	GLfloat m_lightAmb[4];
	GLfloat m_lightDif[4];
	GLfloat m_lightSpe[4];
	GLfloat m_lightPos[4];

	GLfloat m_colorRed;
	GLfloat m_colorGreen;
	GLfloat m_colorBlue;
	BOOL    m_bMaskRed;
	BOOL    m_bMaskGreen;
	BOOL    m_bMaskBlue;

	void drawLineloop();
	void drawTriangles();
	void drawPoints();
	void drawFace(int xyz,int f);
	void drawBoundaryFace(int xyz,int f);
	void drawDCFace();
	void drawZuoBiao();
	void drawString(const char* str);
	//void Ontime(CJingDuTiao* pDlg);

	int m_drawType;

	int m_trianglesNum;
	int m_pointsNum;
	
	float m_fWidth;
	float m_fHeight;
	float xRange;
	float yRange;
	float m_pointX;   
	float m_pointY; 
	
	//int f[]


	float eyeZ;

	void init();
	virtual ~CDrawObjectView();
/////////////////////////////////////////////////////////////////
//添加成员函数与成员变量
	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);
	void setNormal();

	HGLRC		m_hRC;			//OpenGL绘制描述表
	HPALETTE	m_hPalette;		//OpenGL调色板
	CDC*	    m_pDC;			//OpenGL设备描述表
/////////////////////////////////////////////////////////////////

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawObjectView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLoadObjectData();
	afx_msg void OnDrawWithPoint();
	afx_msg void OnDrawWithTriangle();
	afx_msg void OnDrawWithFill();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnColorSet();
	afx_msg void OnUpdateColorSet(CCmdUI* pCmdUI);
	afx_msg void OnSetLight();
	afx_msg void OnUpdateSetLight(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSaveToDib();
	afx_msg void OnJiaZaiJing();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawObjectView.cpp
inline CDrawObjectDoc* CDrawObjectView::GetDocument()
   { return (CDrawObjectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
