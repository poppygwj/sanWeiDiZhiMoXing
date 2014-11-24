// DrawObjectView.cpp : implementation of the CDrawObjectView class
//

#include <gl/glut.h>
#include "stdafx.h"
#include "DrawObject.h"
#include "DrawObjectDoc.h"
#include "DrawObjectView.h"
#include "GRDECL.h"
#include <windows.h>
#include "SetColorDlg.h"
#include "LightingDlg.h"
#include "JingDuTiao.h"
#include "Global.h"

#include "math.h"

#include "afxtempl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CArray<Point3D,Point3D> pointArray;
CArray<Triangle,Triangle> triangleArray;
#define MAX_CHAR        128


/////////////////////////////////////////////////////////////////////////////
// CDrawObjectView

IMPLEMENT_DYNCREATE(CDrawObjectView, CView)

BEGIN_MESSAGE_MAP(CDrawObjectView, CView)
	//{{AFX_MSG_MAP(CDrawObjectView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_LOAD_OBJECT_DATA, OnLoadObjectData)
	ON_COMMAND(ID_DRAW_WITH_POINT, OnDrawWithPoint)
	ON_COMMAND(ID_DRAW_WITH_TRIANGLE, OnDrawWithTriangle)
	ON_COMMAND(ID_DRAW_WITH_FILL, OnDrawWithFill)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_COLOR_SET, OnColorSet)
	ON_UPDATE_COMMAND_UI(ID_COLOR_SET, OnUpdateColorSet)
	ON_COMMAND(ID_SET_LIGHT, OnSetLight)
	ON_UPDATE_COMMAND_UI(ID_SET_LIGHT, OnUpdateSetLight)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SAVE_TO_DIB, OnSaveToDib)
	ON_COMMAND(JiaZaiJing, OnJiaZaiJing)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectView construction/destruction
GRDECL *grd=new GRDECL();
CJingDuTiao* dlg1=new CJingDuTiao();
CDrawObjectView::CDrawObjectView()
{
	// TODO: add construction code here
	m_colorRed=1.0f;
	m_colorGreen=0.0f;
	m_colorBlue=0.0f;

	m_bMaskRed=FALSE;
	m_bMaskGreen=FALSE;
	m_bMaskBlue=FALSE;
	
	m_lightAmb[0]=0.2f;		m_lightAmb[1]=0.2f;		m_lightAmb[2]=0.2f;		m_lightAmb[3]=1.0f;
	m_lightDif[0]=0.5f;		m_lightDif[1]=0.5f;		m_lightDif[2]=0.5f;		m_lightAmb[3]=0.5f;
	m_lightSpe[0]=0.0f;		m_lightSpe[1]=0.0f;		m_lightSpe[2]=0.0f;		m_lightSpe[3]=0.0f;
	m_lightPos[0]=1.0f;		m_lightPos[1]=1.0f;		m_lightPos[2]=1.0f;		m_lightPos[3]=0.0f;
	
	m_materialAmb[0]=0.2f;		m_materialAmb[1]=0.2f;		m_materialAmb[2]=0.2f;		m_materialAmb[3]=0;
	m_materialDif[0]=1.0f;		m_materialDif[1]=0.3f;		m_materialDif[2]=0.5f;		m_materialDif[3]=0;	
	m_materialSpe[0]=1.0f;		m_materialSpe[1]=1.0f;		m_materialSpe[2]=1.0f;		m_materialSpe[3]=0;
	m_materialEmi[0]=0.0f;		m_materialEmi[1]=0.0f;		m_materialEmi[2]=0.0f;		m_materialEmi[3]=0;

	m_matshininess = 100.0f;
	m_bMaterial =TRUE;

	m_drawType=LoadData;
	m_startTo=1;
	xRange=0.0;
	yRange=0.0;
	
	halfWidth=0.0;
	halfHeight=0.0;
	eyeZ=0.0;

	translateX=0.0;
	translateY=0.0;


}

CDrawObjectView::~CDrawObjectView()
{
}

BOOL CDrawObjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
////////////////////////////////////////////////////////////////
//设置窗口类型
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectView drawing
void draw()
{
	    //glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
		//glDepthFunc(GL_LEQUAL); 
		//glMatrixMode(GL_MODELVIEW);
		glFrontFace(GL_CCW);//逆时针方向为正方向
		glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);
	glBegin(GL_QUADS);
	    glColor4f(1.0f,0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);//红点
        //glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,1.0f);//绿点
        //glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(1.0f,0.0f,1.0f);//蓝点
		//lColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex3f(1.0f,0.0f,0.0f);//
	glEnd();

	glBegin(GL_QUADS);
	    glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(0.0f,1.0f,0.0f);//红点
        //glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(0.0f,1.0f,1.0f);//绿点
        //glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(0.0f,0.0f,1.0f);//蓝点
		//glColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);//
	glEnd();

	glBegin(GL_QUADS);
	    glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(1.0f,0.0f,0.0f);//红点
        //glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(1.0f,0.0f,1.0f);//绿点
        //glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(1.0f,1.0f,1.0f);//蓝点
		//glColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex3f(1.0f,1.0f,0.0f);//
	glEnd();

	glBegin(GL_QUADS);
	    glColor4f(1.0f,0.0f,1.0f,1.0f);
        glVertex3f(1.0f,1.0f,0.0f);//红点
        //glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(1.0f,1.0f,1.0f);//绿点
       // glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(0.0f,1.0f,1.0f);//蓝点
		//glColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex3f(0.0f,1.0f,0.0f);//
	glEnd();

	glBegin(GL_QUADS);
	    glColor4f(1.0f,1.0f,0.0f,1.0f);
        glVertex3f(0.0f,1.0f,0.0f);//红点
        //glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);//绿点
        //glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(1.0f,0.0f,0.0f);//蓝点
		//glColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex3f(1.0f,1.0f,0.0f);//
	glEnd();

	glBegin(GL_QUADS);
	    glColor4f(0.0f,1.0f,1.0f,1.0f);
        glVertex3f(0.0f,0.0f,1.0f);//红点
        //glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex3f(0.0f,1.0f,1.0f);//绿点
        //glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3f(1.0f,1.0f,1.0f);//蓝点
		//glColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex3f(1.0f,0.0f,1.0f);//
	glEnd();

	glFlush();
}
void CDrawObjectView::OnDraw(CDC* pDC)
{
	CDrawObjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//pDC->SetTextColor(255);
	//pDC->TextOut(20,20,"Points:");
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	//pDoc->SetDialogBkColor(RGB(0,0,255),RGB(255,0,0)); 
	//pDC->SetBkColor(RGB(0,233,220));
	
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////
	

}

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectView printing

BOOL CDrawObjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawObjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawObjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectView diagnostics

#ifdef _DEBUG
void CDrawObjectView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawObjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawObjectDoc* CDrawObjectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawObjectDoc)));
	return (CDrawObjectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawObjectView message handlers

int CDrawObjectView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//////////////////////////////////////////////////////////////////
//初始化OpenGL和设置定时器
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	
	return 0;
}

void CDrawObjectView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//删除调色板和渲染上下文、定时器
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	KillTimer(1);		
/////////////////////////////////////////////////////////////////
	
}

void CDrawObjectView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////

	m_fWidth=(float)cx;
	m_fHeight=(float)cy;

	//添加窗口缩放时的图形变换函数
	glViewport(0,0,(GLsizei) cx,(GLsizei) cy);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*if(cx<=cy)
		glOrtho(-0.5,0.5,0.5*cy/cx,0.5*cy/cx,-10.0,10.0);
	else
		glOrtho(-0.5*cx/cy,0.5*cx/cy,-0.5,0.5,-10.0,10.0);*/
	//glFrustum(-0.1,0.1,-0.1,0.1,0.8,5.0);
	//gluPerspective(90.0,1.0,0.0,1000);
	gluPerspective(30.0,1.0*(GLfloat)cx/(GLfloat)cy,0.0,500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,2*eyeZ,0.0,0.0,0.0,0.0,1.0,0.0);

	//glDrawBuffer(GL_BACK);
	
	//glEnable(GL_DEPTH_TEST);
/////////////////////////////////////////////////////////////////
	
}

void CDrawObjectView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	switch(nIDEvent)  
    {  
    default:  
        break;  
    case 1:  
		Invalidate(FALSE);
        //pDlg->m_ctrlProgress.StepIt();  
        break;  
	case 2:  
		//Invalidate(FALSE);
        //pDlg->m_ctrlProgress.StepIt();  
        break; 
    } 
	
	//	
/////////////////////////////////////////////////////////////////
	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CDrawObjectView::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}


//////////////////////////////////////////////////////////
//						初始化openGL场景
//////////////////////////////////////////////////////////
BOOL CDrawObjectView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//生成绘制描述表
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//置当前绘制描述表
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
//glClear( 1.0f, 1.0f, 1.0f );
	return TRUE;
}

//////////////////////////////////////////////////////////
//						设置像素格式
//////////////////////////////////////////////////////////
BOOL CDrawObjectView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//选择像素格式
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//设置像素格式
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//设置逻辑调色板
	return TRUE;
}
void RenderBone(float x0, float y0, float z0, float x1, float y1, float z1 )  
{  
    GLdouble  dir_x = x1 - x0;  
    GLdouble  dir_y = y1 - y0;  
    GLdouble  dir_z = z1 - z0;  
    GLdouble  bone_length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );  
    static GLUquadricObj *  quad_obj = NULL;  
    if ( quad_obj == NULL )  
        quad_obj = gluNewQuadric();  
    gluQuadricDrawStyle( quad_obj, GLU_FILL );  
    gluQuadricNormals( quad_obj, GLU_SMOOTH );  
    glPushMatrix();  
    // 平移到起始点  
    glTranslated( x0, y0, z0 );  
    // 计算长度  
    double  length;  
    length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );  
    if ( length < 0.0001 ) {   
        dir_x = 0.0; dir_y = 0.0; dir_z = 1.0;  length = 1.0;  
    }  
    dir_x /= length;  dir_y /= length;  dir_z /= length;  
    GLdouble  up_x, up_y, up_z;  
    up_x = 0.0;  
    up_y = 1.0;  
    up_z = 0.0;  
    double  side_x, side_y, side_z;  
    side_x = up_y * dir_z - up_z * dir_y;  
    side_y = up_z * dir_x - up_x * dir_z;  
    side_z = up_x * dir_y - up_y * dir_x;  
    length = sqrt( side_x*side_x + side_y*side_y + side_z*side_z );  
    if ( length < 0.0001 ) {  
        side_x = 1.0; side_y = 0.0; side_z = 0.0;  length = 1.0;  
    }  
    side_x /= length;  side_y /= length;  side_z /= length;  
    up_x = dir_y * side_z - dir_z * side_y;  
    up_y = dir_z * side_x - dir_x * side_z;  
    up_z = dir_x * side_y - dir_y * side_x;  
    // 计算变换矩阵  
    GLdouble  m[16] = { side_x, side_y, side_z, 0.0,  
        up_x,   up_y,   up_z,   0.0,  
        dir_x,  dir_y,  dir_z,  0.0,  
        0.0,    0.0,    0.0,    1.0 };  
    glMultMatrixd( m );  
    // 圆柱体参数  
    GLdouble radius= .2;        // 半径  
    GLdouble slices = 8.0;      //  段数  
    GLdouble stack = 3.0;       // 递归次数  
    gluCylinder( quad_obj, radius, radius, bone_length, slices, stack );   
    glPopMatrix();  
}
void CDrawObjectView::drawZuoBiao()
{
	//grd->setZuoBiao();
	int i;
	glLineWidth(1);
	for(i=0;i<grd->yn;i++)
	{
		//m_materialAmb[0]=1.0f;		m_materialAmb[1]=0.0f;		m_materialAmb[2]=0.0f;		m_materialAmb[3]=0;
        //glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
	    glBegin( GL_LINES);
	    glColor3f(1,0,0);  // x轴glVertex3f(-r, 0, 0); glVertex3f(r, 0,0);
	    //glVertex3f(0,0,0);
		//glVertex3f(1,0,0);
	    glVertex3f(grd->X[0],grd->Y[i],grd->Z[0]);  //glVertex3f(r,0,0);
	    glVertex3f(grd->X[0],grd->Y[i],grd->Z[grd->zn-1]); //glVertex3f(r,0,0);
	    glEnd();

		//GLUquadricObj *objCylinder = gluNewQuadric();
        //gluCylinder(objCylinder, .1,.1,200, 220, 50);
		//RenderBone(grd->X[0],grd->Y[i],grd->Z[0],grd->X[0],grd->Y[i],grd->Z[grd->zn-1]);

		glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos4f(grd->X[0], grd->Y[i],grd->Z[grd->zn-1],1.0f);
		CString str;
	    str.Format(_T("%d"),(int)grd->sjY[i]);
		drawString(str);
	}
	
	for(i=0;i<grd->yn;i++)
	{
	    glBegin( GL_LINES);
	    glColor3f(1,0,0);  // x轴glVertex3f(-r, 0, 0); glVertex3f(r, 0,0);
	    glVertex3f(grd->X[grd->xn-1],grd->Y[i],grd->Z[0]);  //glVertex3f(r,0,0);
	    glVertex3f(grd->X[grd->xn-1],grd->Y[i],grd->Z[grd->zn-1]); //glVertex3f(r,0,0);
	    glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos4f(grd->X[grd->xn-1],grd->Y[i],grd->Z[grd->zn-1],1.0f);
		CString str;
	    str.Format(_T("%d"),(int)grd->sjY[i]);
		drawString(str);
	}
	for(i=0;i<grd->xn;i++)
	{
	    glBegin( GL_LINES);
	    glColor3f(1,0,0);  // x轴glVertex3f(-r, 0, 0); glVertex3f(r, 0,0);
	    glVertex3f(grd->X[i],grd->Y[0],grd->Z[0]);  //glVertex3f(r,0,0);
	    glVertex3f(grd->X[i],grd->Y[0],grd->Z[grd->zn-1]); //glVertex3f(r,0,0);
	    glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos4f(grd->X[i],grd->Y[0],grd->Z[0],1.0f);
		CString str;
	    str.Format(_T("%d"),(int)grd->sjX[i]);
		drawString(str);
	}
	for(i=0;i<grd->zn;i++)
	{
	    glBegin( GL_LINES);
	    glColor3f(1,0,0);  // x轴glVertex3f(-r, 0, 0); glVertex3f(r, 0,0);
	    glVertex3f(grd->X[0],grd->Y[0],grd->Z[i]);  //glVertex3f(r,0,0);
	    glVertex3f(grd->X[0],grd->Y[grd->yn-1],grd->Z[i]); //glVertex3f(r,0,0);
	    glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos4f(grd->X[0],grd->Y[grd->yn-1],grd->Z[i],1.0f);
		CString str;
	    str.Format(_T("%d"),(int)grd->sjZ[i]);
		drawString(str);
	}
	for(i=0;i<grd->zn;i++)
	{
	    glBegin( GL_LINES);
	    glColor3f(1,0,0);  // x轴glVertex3f(-r, 0, 0); glVertex3f(r, 0,0);
	    glVertex3f(grd->X[grd->xn-1],grd->Y[0],grd->Z[i]);  //glVertex3f(r,0,0);
	    glVertex3f(grd->X[grd->xn-1],grd->Y[grd->yn-1],grd->Z[i]); //glVertex3f(r,0,0);
	    glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos4f(grd->X[grd->xn-1],grd->Y[grd->yn-1],grd->Z[i],1.0f);
		CString str;
	    str.Format(_T("%d"),(int)grd->sjZ[i]);
		drawString(str);
	}
	for(i=0;i<grd->zn;i++)
	{
	    glBegin( GL_LINES);
	    glColor3f(1,0,0);  // x轴glVertex3f(-r, 0, 0); glVertex3f(r, 0,0);
	    glVertex3f(grd->X[0],grd->Y[0],grd->Z[i]);  //glVertex3f(r,0,0);
	    glVertex3f(grd->X[grd->xn-1],grd->Y[0],grd->Z[i]); //glVertex3f(r,0,0);
	    glEnd();
	}
	/**/

}
double jing[10400][10];
int jingCount;
void drawJing(int jingCount,double jing[][10])
{
	double x,y,z;
	
	//grd->readJingFile(sFileName,jing,jingCount);
	glLineWidth(5);
	
	    /*glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0,0,0);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(50,50,0);*/
	for(int i=0;i<jingCount-1;i++)
	{
		glBegin(GL_LINES);
		x=(jing[i][1]-grd->centerX)*(200/(grd->xmax-grd->xmin));
		y=(jing[i][2]-grd->centerY)*(200/(grd->ymax-grd->ymin));
		z=(-jing[i][3]-grd->centerZ)*(100/(grd->zmax-grd->zmin));
		glColor4f(0.0f,0.0f,0.0f,1.0f);
		
		glVertex3f(x,y,z);
		x=(jing[i+1][1]-grd->centerX)*(200/(grd->xmax-grd->xmin));
		y=(jing[i+1][2]-grd->centerY)*(200/(grd->ymax-grd->ymin));
		z=(-jing[i+1][3]-grd->centerZ)*(100/(grd->zmax-grd->zmin));
		glColor4f(0.0f,0.0f,0.0f,1.0f);
		
		glVertex3f(x,y,z);
		glEnd();
	}
	
	glFlush();
}
//////////////////////////////////////////////////////////
//						场景绘制与渲染
//////////////////////////////////////////////////////////
void  RotatefFXL(int f,float R)
{
	if(R!=0)
	{
	int i;
	double tempx,tempy,tempz;
	for(i=0;i<grd->XDuanCengDianCount;i++)//计算断层法向量
	{
		
		tempx=grd->DCXNormal[i][0];
		tempy=grd->DCXNormal[i][1];
		tempy=grd->DCXNormal[i][2];
		if(f==1)
		{
		   grd->DCXNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->DCXNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->DCXNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->DCXNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}
	for(i=0;i<grd->YDuanCengDianCount;i++)
	{
		tempx=grd->DCYNormal[i][0];
		tempy=grd->DCYNormal[i][1];
		tempy=grd->DCYNormal[i][2];
		if(f==1)
		{
		   grd->DCYNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->DCYNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->DCYNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->DCYNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}

	for(i=0;i<(grd->k+2)*grd->n*(grd->m-1)*2;i++)//计算内部层的法向量
	{
		tempx=grd->YNormal[i][0];
		tempy=grd->YNormal[i][1];
		tempy=grd->YNormal[i][2];
		if(f==1)
		{
		   grd->YNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->YNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->YNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->YNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}
	for(i=0;i<2*grd->m*(grd->n-1)*(grd->k+4);i++)
	{
		tempx=grd->XNormal[i][0];
		tempy=grd->XNormal[i][1];
		tempy=grd->XNormal[i][2];
		if(f==1)
		{
		   grd->XNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->XNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->XNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->XNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}
	for(i=0;i<2*grd->m*grd->n*(grd->k-1);i++)
	{
		tempx=grd->ZNormal[i][0];
		tempy=grd->ZNormal[i][1];
		tempy=grd->ZNormal[i][2];
		if(f==1)
		{
		   grd->ZNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->ZNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->ZNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->ZNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}


	for(i=0;i<grd->n*(grd->k+2)*2;i++)//计算边界层的法向量
	{
		tempx=grd->BYNormal[i][0];
		tempy=grd->BYNormal[i][1];
		tempy=grd->BYNormal[i][2];
		if(f==1)
		{
		   grd->BYNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->BYNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->BYNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->BYNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}
	for(i=0;i<grd->m*(grd->k+2)*2;i++)
	{
		tempx=grd->BXNormal[i][0];
		tempy=grd->BXNormal[i][1];
		tempy=grd->BXNormal[i][2];
		if(f==1)
		{
		   grd->BXNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->BXNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->BXNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->BXNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}
	for(i=0;i<grd->m*grd->n*2;i++)
	{
		tempx=grd->BZNormal[i][0];
		tempy=grd->BZNormal[i][1];
		tempy=grd->BZNormal[i][2];
		if(f==1)
		{
		   grd->BZNormal[i][0]=cos(R)*(tempx)-sin(R)*(tempz);
		   grd->BZNormal[i][2]=sin(R)*(tempx)+cos(R)*(tempz);
		}else
		{
			grd->BZNormal[i][1]=cos(R)*(tempy)+sin(R)*(tempz);
			grd->BZNormal[i][2]=cos(R)*(tempz)-sin(R)*(tempy);
		}
	}
	}
}
BOOL CDrawObjectView::RenderScene() 
{	
	init();
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,2*eyeZ,0.0,0.0,0.0,0.0,1.0,0.0);//设置视点，eyeZ用来移动视点，以改变物体大小

		
	glTranslatef(translateX,translateY,0.0);//平移，利用方向键移动物体


	glRotatef(yRange,0,1,0);//绕y轴移动物体
	if(yRange!=0)
	RotatefFXL(1,yRange);
	glRotatef(xRange,1,0,0);//绕x轴移动物体
	if(xRange!=0)
	RotatefFXL(0,xRange);
	
	
	glTranslatef(-centerX,-centerY,0.0);//平移坐标轴到物体中心
    
//	glColorMask(!m_bMaskRed,!m_bMaskGreen,!m_bMaskBlue,GL_TRUE);
	glColor3f(m_colorRed,m_colorGreen,m_colorBlue);
    //draw();
	switch(m_drawType)//绘制方式
	{
	case Points:
		drawPoints();//点方式显示物体
		drawZuoBiao();
		break;

	case Lines:
		drawLineloop();//线方式显示物体
		drawZuoBiao();
		break;

	case Filling:

		if(m_bMaterial)//填充方式下，先设置光照和材质
		{
			CreateMaterial();
			CreateLights();
		}
		glEnable(GL_DEPTH_TEST);
		//glDisable(GL_DEPTH_TEST);
		//glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LEQUAL); 
		//glMatrixMode(GL_MODELVIEW);
		glFrontFace(GL_CCW);//逆时针方向为正方向
		//glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		
		

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
		//glEnable(GL_ALPHA_TEST);
		//glAlphaFunc(GL_ONE ,GL_ZERO);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_ZERO ,GL_ONE);	
        //glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LEQUAL);
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);   

		//glDisable(GL_LIGHTING);
		//glDisable(GL_LIGHT0);
		//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//正反面
		drawZuoBiao();
		drawTriangles();//填充方式显示物体
        drawJing(jingCount,jing);
		glDisable(GL_CULL_FACE);
		
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		break;
	}

	
	glFlush();
	//glutSwapBuffers();

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区


	return TRUE;
}

void CDrawObjectView::init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
CString sFileName="";
UINT function(LPVOID pParam)
{
	//dlg1->Create(IDD_DIALOG3,this);
	//dlg1->ShowWindow(SW_SHOWNORMAL);
	//dlg1->DoModal();
	for(int i = 0; i < 1000; i++){
		CGlobal::progress++;
		Sleep(50);
	}

	CGlobal::progress = -1;
	return 0;
}
UINT function1(LPVOID pParam)
{
	grd->readFile(sFileName);
	
	grd->setXYcorn();
	grd->addFour();
	grd->setXYZ2();
	grd->setFaceXYZ();
	grd->normalize4display(&pointArray);
	//eyeZ = grd->getEyeZ();
	grd->setgun();
	grd->setZuoBiao();
	return 0;
}
void CDrawObjectView::OnLoadObjectData() 
{
	// TODO: Add your command handler code here
    

	CFileDialog dlg(TRUE, "", "*.grdecl",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"SMF Files(*.grdecl)|*.grdecl|All Files(*.*)|*.*||"); 
	if ( dlg.DoModal()!=IDOK ) 
		return; 

	if (pointArray.GetSize()>0)
		pointArray.RemoveAll();

	triangleArray.RemoveAll();

	sFileName=dlg.GetPathName(); 

//	CStdioFile file; 
//	file.Open(sFileName, CFile::modeRead); 
    
	CString tempStr,lineStr; 
//	BOOL end_of_file=FALSE;
	//int blank1,blank2;
	float minX=0,maxX=0,minY=0,maxY=0;
	//Point3D point;
//	Triangle triangle;
 	eyeZ=0;
//	clock_t start, finish;
	//MessageBox(NULL, "aaaa", "提示", MB_OK);
//	start=clock();
	/**/
	//pDlg=new CJingDuTiao();
	//dlg.DoModal();
	
	//pDlg->m_ctrlProgress.SetStep(10);
	AfxBeginThread(function1,this);
    AfxBeginThread(function,this);
	dlg1->DoModal();

	/*grd->readFile(sFileName);
	grd->setXYcorn();
	grd->addFour();
	grd->setXYZ2();
	grd->setFaceXYZ();
	grd->normalize4display(&pointArray);
	
	grd->setgun();
	grd->setZuoBiao();
*/
	eyeZ = grd->getEyeZ();
	minX = grd->getXminDisplay();	maxX = grd->getXmaxDisplay();
	minY = grd->getYminDisplay();   maxY = grd->getYmaxDisplay();
	centerX=(minX + maxX)/2;
	centerY=(minY + maxY)/2;
   

	halfWidth=fabs(minX)>maxX?fabs(minX):maxX;
	halfHeight=fabs(minY)>maxY?fabs(minY):maxY;

	m_pointsNum=pointArray.GetSize();
	m_trianglesNum=triangleArray.GetSize();
	
	m_drawType=Points;
	xRange=0.0;
	yRange=0.0;
	translateX=0.0;
	translateY=0.0;
}
/*void CDrawObjectView::OnTimer(CJingDuTiao* pDlg)
{
	pDlg->m_ctrlProgress.StepIt();
}*/

void CDrawObjectView::OnDrawWithPoint() 
{
	// TODO: Add your command handler code here
	m_drawType=Points;
	Invalidate(FALSE);
}

void CDrawObjectView::OnDrawWithTriangle() 
{
	// TODO: Add your command handler code here
	m_drawType=Lines;
	Invalidate(FALSE);
}

void CDrawObjectView::drawPoints()
{
	int i;
	Point3D p;

	glPointSize(3.0);

	glBegin(GL_POINTS);
		for(i=0;i<pointArray.GetSize();i++)
		{
			p=pointArray.GetAt(i);
			glVertex3f( p.x, p.y ,p.z );
			//glFlush();
			//::SwapBuffers(m_pDC->GetSafeHdc());
		}
	glEnd();
}

void VectorOffset (Point3D p1, Point3D p2, Point3D p3)
{ 
	p3.x = p1.x - p2.x;
	p3.y = p1.y - p2.y;
	p3.z = p1.z - p2.z;
}


// Compute the cross product a X b into pOut
void VectorGetNormal (Point3D p1, Point3D p2, Point3D p3)
{
	p3.x = p1.y * p2.z - p1.z * p2.y;
	p3.y = p1.z * p2.x - p1.x * p2.z;
	p3.z = p1.x * p2.y -p1.y * p2.x;
}


// Normalize pIn vector into pOut
bool VectorNormalize (Point3D p1, Point3D p2)
{
	GLfloat len = (GLfloat)(sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z));
	if (len)
	{
		p2.x = p1.x / len;
		p2.y = p1.y / len;
		p2.z = p1.z / len;
		return true;
	}
	return false;
}


// Compute p1,p2,p3 face normal into pOut
bool ComputeFaceNormal (Point3D p1, Point3D p2, Point3D p3, Point3D pOut)
{
	// Uses p2 as a new origin for p1,p3
	Point3D a;
	VectorOffset(p3, p2, a);
	Point3D b;
	VectorOffset(p1, p2, b);
	// Compute the cross product a X b to get the face normal
	Point3D pn;
	VectorGetNormal(a, b, pn);
	// Return a normalized vector
	return VectorNormalize(pn, pOut);
}


void CDrawObjectView::drawBoundaryFace(int xyz,int f)
{
	//double dNormal[3];
	Point3D p1,p2,p3,p4;
	double zmax = grd->zmaxDisplay;
	double xmax=grd->xmaxDisplay;
	double ymax=grd->ymaxDisplay;
	//int mm=0;
	if(xyz==1)
	{
			for(int i=f+grd->n*4;i<grd->n*(grd->k+2)*2;i+=2)
			{
					if(grd->faceBoundaryY[i][0]!=-1)
			{
				p1=pointArray.GetAt(grd->flag2[grd->faceBoundaryY[i][0]]);
		        p2=pointArray.GetAt(grd->flag2[grd->faceBoundaryY[i][1]]);
		        p3=pointArray.GetAt(grd->flag2[grd->faceBoundaryY[i][2]]);
		        p4=pointArray.GetAt(grd->flag2[grd->faceBoundaryY[i][3]]);
    
				//ComputeFaceNormal(p1,p3,p2,p5);
                //if(grd->BYNormal[i][0]<-100){
				//CalculateNormal(p1,p2,p3,grd->BYNormal[i]);	
				//}
	            //glBegin(GL_POLYGON);
				glBegin(GL_QUADS);

                m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=0;
                glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
				glNormal3dv(grd->BYNormal[i]);
				//glNormal3dv(dNormal);
				//glNormal3f(p5.x, p5.y, p5.z);
	            
	            glVertex3f(p1.x,p1.y,p1.z);
	            
	            glVertex3f(p2.x,p2.y,p2.z);
	            
	            glVertex3f(p3.x,p3.y,p3.z);
	            
	            glVertex3f(p4.x,p4.y,p4.z);
	            
	            glEnd();
		        /*glBegin(GL_LINE_LOOP);
	            glColor4f(0.0f,0.0f,1.0f,0.0f);
	            //IGLObject glRectangle = this._rectangle.makeGLObject();
	            glVertex3f(p1.x,p1.y,p1.z);
		        glColor4f(0.0f,0.0f,1.0f,0.0f);
	            glVertex3f(p2.x,p2.y,p2.z);
		        glColor4f(0.0f,0.0f,1.0f,0.0f);
	            glVertex3f(p3.x,p3.y,p3.z);
		        glColor4f(0.0f,0.0f,1.0f,0.0f);
	            glVertex3f(p4.x,p4.y,p4.z);
		        //temp++;
	            glEnd();*/
					}
		    }	        
	}else if(xyz==0)
	{
		for(int i=f+grd->m*4;i<grd->m*(grd->k+2)*2;i+=2)
			{
					if(grd->faceBoundaryX[i][0]!=-1)
			{
				p1=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][0]]);
		        p2=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][1]]);
		        p3=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][2]]);
		        p4=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][3]]);

				//ComputeFaceNormal(p1,p3,p2,p5);
				//if(grd->BXNormal[i][0]<-100)
				//CalculateNormal(p1,p2,p3,grd->BXNormal[i]);			
	           
                //glBegin(GL_POLYGON);
				glBegin(GL_QUADS);
                m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=0;
                glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
				glNormal3dv(grd->BXNormal[i]);
				//glNormal3dv(dNormal);
	            //glNormal3f(p5.x, p5.y, p5.z);

	            glVertex3f(p1.x,p1.y,p1.z);
	           
	            glVertex3f(p2.x,p2.y,p2.z);
	            
	            glVertex3f(p3.x,p3.y,p3.z);
	            
	            glVertex3f(p4.x,p4.y,p4.z);
	            
	            glEnd();
				/*glBegin(GL_LINE_LOOP);
	            glColor4f(0.0f,0.0f,1.0f,0.0f);
	            //IGLObject glRectangle = this._rectangle.makeGLObject();
	            glVertex3f(p1.x,p1.y,p1.z);
		        glColor4f(0.0f,0.0f,1.0f,0.0f);
	            glVertex3f(p2.x,p2.y,p2.z);
		        glColor4f(0.0f,0.0f,1.0f,0.0f);
	            glVertex3f(p3.x,p3.y,p3.z);
		        glColor4f(0.0f,0.0f,1.0f,0.0f);
	            glVertex3f(p4.x,p4.y,p4.z);
		        //temp++;
	            glEnd();*/
					}
		}
	}
	else
	{
		for(int i=f;i<grd->m*(grd->n)*2-1;i+=2)
			{
	
				p1=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][0]]);
		        p2=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][1]]);
		        p3=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][2]]);
		        p4=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][3]]);

				//ComputeFaceNormal(p1,p3,p2,p5);
				//if(grd->BZNormal[i][0]<-100)
				//CalculateNormal(p1,p2,p3,grd->BZNormal[i]);			
	            //glBegin(GL_POLYGON);
				glBegin(GL_QUADS);

                m_materialAmb[0]=p1.x/xmax;		m_materialAmb[1]=p1.y/ymax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=0;
                glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
				glNormal3dv(grd->BZNormal[i]);
				//glNormal3dv(dNormal);
				//glNormal3f(p5.x, p5.y, p5.z);
	            
	            glVertex3f(p1.x,p1.y,p1.z);
	            
	            glVertex3f(p2.x,p2.y,p2.z);
	            
	            glVertex3f(p3.x,p3.y,p3.z);
	            
	            glVertex3f(p4.x,p4.y,p4.z);
	            
	            glEnd();
				/*glBegin(GL_LINE_LOOP);
	            glColor3f(0.0f,0.0f,1.0f);
	            //IGLObject glRectangle = this._rectangle.makeGLObject();
	            glVertex3f(p1.x,p1.y,p1.z);
		        glColor3f(0.0f,0.0f,1.0f);
	            glVertex3f(p2.x,p2.y,p2.z);
		        glColor3f(0.0f,0.0f,1.0f);
	            glVertex3f(p3.x,p3.y,p3.z);
		        glColor3f(0.0f,0.0f,1.0f);
	            glVertex3f(p4.x,p4.y,p4.z);
		        //temp++;
	            glEnd();*/
					
		}
	}
	


}
void CDrawObjectView::setNormal()
{
	Point3D p1,p2,p3,p4;
	for(int i=0;i<grd->m*(grd->n)*2-1;i++)
	{
	
		p1=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][0]]);
		p2=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][1]]);
		p3=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][2]]);
		p4=pointArray.GetAt(grd->flag2[grd->faceBoundaryZ[i][3]]);
		CalculateNormal(p1,p2,p3,grd->BZNormal[i]);
	}
	for(i=0;i<grd->m*(grd->k+2)*2;i++)
	{
		if(grd->faceBoundaryX[i][0]!=-1)
		{
			p1=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][0]]);
		    p2=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][1]]);
		    p3=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][2]]);
		    p4=pointArray.GetAt(grd->flag2[grd->faceBoundaryX[i][3]]);
			CalculateNormal(p1,p2,p3,grd->BXNormal[i]);
		}
	}
}

void CDrawObjectView::drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // 如果是第一次调用，执行初始化
                         // 为每一个ASCII字符产生一个显示列表
         isFirstCall = 0;

         // 申请MAX_CHAR个连续的显示列表编号
         lists = glGenLists(MAX_CHAR);

         // 把每个字符的绘制命令都装到对应的显示列表中
         wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
     }
     // 调用每个字符对应的显示列表，绘制每个字符
    for(; *str!='\0'; ++str)
         glCallList(lists + *str);
}
void CDrawObjectView::drawDCFace()
{
	double dNormal[3];
	int t=0,j=0,i=0;
	double zmax = grd->zmaxDisplay;
	for(i=0;i<grd->XDuanCengDianCount;i++)
	{
		Point3D p[8];
		int temp;
		for(j=0;j<grd->XnumNodes[i];j++)
		{
			temp=grd->XCorners[t];
			if(grd->XCorners[t]>=grd->n3)
			{
				
				p[j].x=(grd->x3[grd->XCorners[t]]-grd->centerX)*(200/(grd->xmax-grd->xmin));
				p[j].y=(grd->y3[grd->XCorners[t]]-grd->centerY)*(200/(grd->ymax-grd->ymin));
				p[j].z=(grd->z3[grd->XCorners[t]]-grd->centerZ)*(100/(grd->zmax-grd->zmin));
			}
			else{
				p[j]=pointArray.GetAt(grd->flag2[grd->XCorners[t]]);}
			t++;
		}
		if(grd->flag2[temp]>=grd->m*grd->n*8&&grd->flag2[temp]<=4*grd->n*grd->m*(grd->k*2+2)){
		//CalculateNormal(p[0],p[1],p[2],dNormal);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_POLYGON);
		//		glBegin(GL_QUADS);
        m_materialAmb[0]=p[0].z/zmax;		m_materialAmb[1]=p[10].z/zmax;		m_materialAmb[2]=p[0].z/zmax;		m_materialAmb[3]=0;
       glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
		glNormal3dv(grd->DCXNormal[i]);
	    //for(j=0;j<grd->XnumNodes[i];j++)
		//{
		//	glVertex3f(p[j].x,p[j].y,p[j].z);
		//} 
        for(j=grd->XnumNodes[i]-1;j>=0;j--)
		{
			glVertex3f(p[j].x,p[j].y,p[j].z);
		}
		glEnd();
		}
	}/**/
    t=0;
	for(i=0;i<grd->YDuanCengDianCount;i++)
	{
		Point3D p[8];
		int temp;
		for(j=0;j<grd->YnumNodes[i];j++)
		{
			temp=grd->YCorners[t];
			if(grd->YCorners[t]>=grd->n3)
			{
				p[j].x=(grd->x3[grd->YCorners[t]]-grd->centerX)*(200/(grd->xmax-grd->xmin));
				p[j].y=(grd->y3[grd->YCorners[t]]-grd->centerY)*(200/(grd->ymax-grd->ymin));
				p[j].z=(grd->z3[grd->YCorners[t]]-grd->centerZ)*(100/(grd->zmax-grd->zmin));
			}
			else
			{
				p[j]=pointArray.GetAt(grd->flag2[grd->YCorners[t]]);
			}
			t++;
		}
		if(grd->flag2[temp]>=grd->m*grd->n*8&&grd->flag2[temp]<=4*grd->n*grd->m*(grd->k*2+2)){
		//CalculateNormal(p[0],p[1],p[2],dNormal);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_POLYGON);
		//		glBegin(GL_QUADS);
        m_materialAmb[0]=p[0].z/zmax;		m_materialAmb[1]=p[10].z/zmax;		m_materialAmb[2]=p[0].z/zmax;		m_materialAmb[3]=0;
       glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
		glNormal3dv(grd->DCYNormal[i]);
	    for(j=0;j<grd->YnumNodes[i];j++)
		{
			glVertex3f(p[j].x,p[j].y,p[j].z);
		}         
	    glEnd();
		}
	}

}
void CDrawObjectView::drawFace(int xyz,int f)
{
	double dNormal[3];
	Point3D p1,p2,p3,p4;
	double zmax = grd->zmaxDisplay;
	int i;
	//int mm=0;
	if(xyz==1)
	{
		for(int i=f+grd->n*(grd->m-1)*4;i<(grd->k+2)*grd->n*(grd->m-1)*2;i+=2*(grd->m-1))
		{
		 //int mm=grd->faceY[i][0];
		 //int nn=grd->flag2[grd->faceY[i][0]];
			if(grd->faceY[i][0]!=-1)
			{
		   p1=pointArray.GetAt(grd->flag2[grd->faceY[i][0]]);
		   p2=pointArray.GetAt(grd->flag2[grd->faceY[i][1]]);
		   p3=pointArray.GetAt(grd->flag2[grd->faceY[i][2]]);
		   p4=pointArray.GetAt(grd->flag2[grd->faceY[i][3]]);
		   //CalculateNormal(p1,p2,p3,dNormal);
		   //m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=1.0f;
	       glBegin(GL_POLYGON);
           
		   m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=1.0f;
	       glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
		   glNormal3dv(grd->YNormal[i]);
		   //glNormal3dv(dNormal);
	       glColor4f(1.0f,0.0f,0.0f,0.0f);
	       glVertex3f(p1.x,p1.y,p1.z);
	       glColor4f(1.0f,0.0f,0.0f,0.0f);
	       glVertex3f(p2.x,p2.y,p2.z);
	       glColor4f(1.0f,0.0f,0.0f,0.0f);
	       glVertex3f(p3.x,p3.y,p3.z);
	       glColor4f(1.0f,0.0f,0.0f,0.0f);
	       glVertex3f(p4.x,p4.y,p4.z);
	       //temp++;
	       glEnd();
		  /*
		   glBegin(GL_LINE_LOOP);
	       glColor4f(0.0f,0.0f,1.0f,0.0f);
	       //IGLObject glRectangle = this._rectangle.makeGLObject();
	       glVertex3f(p1.x,p1.y,p1.z);
		   glColor4f(0.0f,0.0f,1.0f,0.0f);
	       glVertex3f(p2.x,p2.y,p2.z);
		   glColor4f(0.0f,0.0f,1.0f,0.0f);
	       glVertex3f(p3.x,p3.y,p3.z);
		   glColor4f(0.0f,0.0f,1.0f,0.0f);
	       glVertex3f(p4.x,p4.y,p4.z);
		   //temp++;
	       glEnd();*/
			}
		}
	}
	else if(xyz==0)
	{
		for(i=f+grd->m*(grd->n-1)*4;i<2*grd->m*(grd->n-1)*(grd->k+2);i+=2*(grd->n-1))
		{
			if(grd->faceX[i][0]!=-1)
			{
				p1=pointArray.GetAt(grd->flag2[grd->faceX[i][0]]);
		    	p2=pointArray.GetAt(grd->flag2[grd->faceX[i][1]]);
		    	p3=pointArray.GetAt(grd->flag2[grd->faceX[i][2]]);
		    	p4=pointArray.GetAt(grd->flag2[grd->faceX[i][3]]);
		    	//CalculateNormal(p1,p2,p3,dNormal);
		   //m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=1.0f;
	        	glBegin(GL_POLYGON);
                
		    	m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=1.0f;
	        	glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
				glNormal3dv(grd->XNormal[i]);
				//glNormal3dv(dNormal);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p1.x,p1.y,p1.z);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p2.x,p2.y,p2.z);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p3.x,p3.y,p3.z);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p4.x,p4.y,p4.z);
	       //temp++;
	        	glEnd();
				//mm++;
			}
		}
		//int aa=mm;
	}
	else
	{
		for(i=f;i<2*grd->m*(grd->n-1)*(grd->k-1);i+=2*(grd->k-1))
		{
				p1=pointArray.GetAt(grd->flag2[grd->faceZ[i][0]]);
		    	p2=pointArray.GetAt(grd->flag2[grd->faceZ[i][1]]);
		    	p3=pointArray.GetAt(grd->flag2[grd->faceZ[i][2]]);
		    	p4=pointArray.GetAt(grd->flag2[grd->faceZ[i][3]]);
		    //	CalculateNormal(p1,p2,p3,dNormal);
		   //m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=1.0f;
	        	glBegin(GL_POLYGON);
	
		    	m_materialAmb[0]=p1.z/zmax;		m_materialAmb[1]=p1.z/zmax;		m_materialAmb[2]=p1.z/zmax;		m_materialAmb[3]=1.0f;
	        	//glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_materialAmb);
			    glNormal3dv(grd->ZNormal[i]);
				//glNormal3dv(dNormal);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p1.x,p1.y,p1.z);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p2.x,p2.y,p2.z);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p3.x,p3.y,p3.z);
	        	glColor4f(1.0f,0.0f,0.0f,0.0f);
	        	glVertex3f(p4.x,p4.y,p4.z);
	       //temp++;
	        	glEnd();
				//mm++;
		}
	}
}

void CDrawObjectView::drawTriangles()
{

 	/*drawFace(2,0);
	drawFace(1,3);
	//drawFace(1,5);
	drawFace(0,1);*/
	//drawFace(1,7);
	//drawFace(1,9);
	//drawFace(1,11);
	//setNormal();
	drawBoundaryFace(0,1);
	drawBoundaryFace(1,1);   
	drawBoundaryFace(0,0);
	drawBoundaryFace(1,0);
	
	drawBoundaryFace(2,0);
	drawBoundaryFace(2,1);
	drawDCFace();
	//drawJing();
}

void CDrawObjectView::OnDrawWithFill() 
{
	// TODO: Add your command handler code here
	m_drawType=Filling;
	Invalidate(FALSE);
}

void CDrawObjectView::drawLineloop()
{
	/*int i;
	Triangle t;
	Point3D p1,p2,p3;

	glLineWidth(2.0);

	for(i=0;i<triangleArray.GetSize();i++)
		{
			t=triangleArray.GetAt(i);
			p1=pointArray.GetAt(t.first-m_startTo);
			p2=pointArray.GetAt(t.second-m_startTo); 
			p3=pointArray.GetAt(t.third-m_startTo);	
		
			glBegin(GL_LINE_LOOP);
			glVertex3f(p1.x ,p1.y ,p1.z );
			glVertex3f(p2.x ,p2.y ,p2.z );
			glVertex3f(p3.x ,p3.y ,p3.z );
			glEnd();
		}*/
	Point3D p1,p2;
	for(int i=0;i<grd->m*(grd->n-1)*(2*grd->k+4);i++)
	{
		
        int t1,t2;
		//if(grd->flagXg[i]==1){
		t1=grd->flag2[grd->gunXA[i][0]];
		t2=grd->flag2[grd->gunXA[i][1]];
		p1=pointArray.GetAt(t1);
		p2=pointArray.GetAt(t2);
		glBegin(GL_LINES);
		glColor4f(1.0f,0.0f,0.0f,0.0f);
        glVertex3f(p1.x,p1.y,p1.z);
		glColor4f(1.0f,0.0f,0.0f,0.0f);
		glVertex3f(p2.x,p2.y,p2.z);
		glEnd();
		t1=grd->flag2[grd->gunXB[i][0]];
		t2=grd->flag2[grd->gunXB[i][1]];
		p1=pointArray.GetAt(t1);
		p2=pointArray.GetAt(t2);
		glBegin(GL_LINES);
		glColor4f(0.0f,1.0f,0.0f,0.0f);
        glVertex3f(p1.x,p1.y,p1.z);
		glColor4f(0.0f,1.0f,0.0f,0.0f);
		glVertex3f(p2.x,p2.y,p2.z);
		glEnd();
	//	}
	}
	

}

void CDrawObjectView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pointX=(float)point.x;   
	m_pointY=(float)point.y; 
	CView::OnLButtonDown(nFlags, point);
}

void CDrawObjectView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	const   float   PI=3.14159265f;   
   //计算旋转角度（从最左边到最右边为180度，上下同理）   
	if(nFlags==MK_LBUTTON)   
	{   
		xRange+=4*PI*(point.y-m_pointY)/m_fWidth;     //m_fWinWidth为窗体宽，在OnSize消息函数里取得   
        yRange+=4*PI*(point.x-m_pointX)/m_fHeight;   //m_fWinHeigth为窗体高，在OnSize消息函数里取得     
	}  
    //draw();
	RenderScene();

	CView::OnMouseMove(nFlags, point);
}

void CDrawObjectView::OnColorSet() 
{
	// TODO: Add your command handler code here
	CSetColorDlg dlg;

	dlg.m_colorRed = m_colorRed;
	dlg.m_colorGreen = m_colorGreen;
	dlg.m_colorBlue = m_colorBlue;
	dlg.m_maskRed = m_bMaskRed;
	dlg.m_maskGreen = m_bMaskGreen;
	dlg.m_maskBlue = m_bMaskBlue;


	dlg.m_matAmbientR = m_materialAmb[0];
	dlg.m_matAmbientG = m_materialAmb[1];
	dlg.m_matAmbientB = m_materialAmb[2];

	dlg.m_matDiffuseR = m_materialDif[0];
	dlg.m_matDiffuseG = m_materialDif[1];
	dlg.m_matDiffuseB = m_materialDif[2];

	dlg.m_matSpecularR = m_materialSpe[0];
	dlg.m_matSpecularG = m_materialSpe[1];
	dlg.m_matSpecularB = m_materialSpe[2];

	dlg.m_matEmissionR = m_materialEmi[0];
	dlg.m_matEmissionG = m_materialEmi[1];
	dlg.m_matEmissionB = m_materialEmi[2]; 
	
	dlg.m_matShininess = m_matshininess;
	dlg.m_bMaterialOnOff =m_bMaterial;

	if(dlg.DoModal()==IDOK)
	{
		m_colorRed = dlg.m_colorRed;
		m_colorGreen = dlg.m_colorGreen;
		m_colorBlue = dlg.m_colorBlue;

		m_bMaskRed = dlg.m_maskRed;
		m_bMaskGreen = dlg.m_maskGreen;
		m_bMaskBlue = dlg.m_maskBlue;


		m_materialAmb[0] = dlg.m_matAmbientR;
		m_materialAmb[1] = dlg.m_matAmbientG;
		m_materialAmb[2] = dlg.m_matAmbientB;

		m_materialDif[0] = dlg.m_matDiffuseR;
		m_materialDif[1] = dlg.m_matDiffuseG;
		m_materialDif[2] = dlg.m_matDiffuseB;

		m_materialSpe[0] = dlg.m_matSpecularR;
		m_materialSpe[1] = dlg.m_matSpecularG;
		m_materialSpe[2] = dlg.m_matSpecularB;

		m_materialEmi[0] = dlg.m_matEmissionR;
		m_materialEmi[1] = dlg.m_matEmissionG;
		m_materialEmi[2] = dlg.m_matEmissionB;

		m_matshininess = dlg.m_matShininess;
		m_bMaterial = dlg.m_bMaterialOnOff;

		Invalidate(FALSE);
	}
}

void CDrawObjectView::OnUpdateColorSet(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawObjectView::CreateLights()
{  
	glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
	  glLoadIdentity();
		glLightfv(GL_LIGHT0,GL_AMBIENT,m_lightAmb);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,m_lightDif);
		glLightfv(GL_LIGHT0,GL_SPECULAR,m_lightSpe);
		glLightfv(GL_LIGHT0,GL_POSITION,m_lightPos);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
  glPopMatrix();

	//glEnable(GL_DEPTH_TEST);
}

void CDrawObjectView::OnSetLight() 
{
	// TODO: Add your command handler code here
	CLightingDlg lightDlg;

	lightDlg.m_lightAmbientR = m_lightAmb[0];
	lightDlg.m_lightAmbientG = m_lightAmb[1];
	lightDlg.m_lightAmbientB = m_lightAmb[2];

	lightDlg.m_lightDiffuseR = m_lightDif[0];
	lightDlg.m_lightDiffuseG = m_lightDif[1];
	lightDlg.m_lightDiffuseB = m_lightDif[2];

	lightDlg.m_lightSpecularR = m_lightSpe[0];
	lightDlg.m_lightSpecularG = m_lightSpe[1];
	lightDlg.m_lightSpecularB = m_lightSpe[2];

	lightDlg.m_lightPositionX = m_lightPos[0];
	lightDlg.m_lightPositionY = m_lightPos[1];
	lightDlg.m_lightPositionZ = m_lightPos[2];

	if(lightDlg.DoModal()==IDOK)
	{
		m_lightAmb[0] = lightDlg.m_lightAmbientR;
		m_lightAmb[1] = lightDlg.m_lightAmbientG;
		m_lightAmb[2] = lightDlg.m_lightAmbientB;

		m_lightDif[0] = lightDlg.m_lightDiffuseR;
		m_lightDif[1] = lightDlg.m_lightDiffuseG;
		m_lightDif[2] = lightDlg.m_lightDiffuseB;

		m_lightSpe[0] = lightDlg.m_lightSpecularR;
		m_lightSpe[1] = lightDlg.m_lightSpecularG;
		m_lightSpe[2] = lightDlg.m_lightSpecularB;

		m_lightPos[0] = lightDlg.m_lightPositionX;
		m_lightPos[1] = lightDlg.m_lightPositionY;
		m_lightPos[2] = lightDlg.m_lightPositionZ;

		Invalidate(FALSE);
	}
}

void CDrawObjectView::OnUpdateSetLight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawObjectView::CreateMaterial()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);//材料的环境光颜色
	glMaterialfv(GL_FRONT,GL_DIFFUSE,m_materialDif);//材料的漫反射光颜色
	glMaterialfv(GL_FRONT,GL_SPECULAR,m_materialSpe);//材料的镜面反射光颜色
	glMaterialfv(GL_FRONT,GL_EMISSION,m_materialEmi);//材料的辐射光颜色
	glMaterialf(GL_FRONT,GL_SHININESS,m_matshininess);//镜面指数
}

void CDrawObjectView::CalculateNormal(Point3D point1, Point3D point2, Point3D point3, GLdouble *dNormal)//计算法向量
{
	GLfloat dVector1[3],dVector2[3];
	dVector1[0] = point2.x - point1.x ;
	dVector1[1] = point2.y - point1.y ;
	dVector1[2] = point2.z - point1.z ;
	dVector2[0] = point3.x - point1.x ;
	dVector2[1] = point3.y - point1.y ;
	dVector2[2] = point3.z - point1.z ;

	dNormal[0] = dVector1[1]*dVector2[2] - dVector1[2]*dVector2[1];
	dNormal[1] = dVector1[2]*dVector2[0] - dVector1[0]*dVector2[2];
	dNormal[2] = dVector1[0]*dVector2[1] - dVector1[1]*dVector2[0];

	double dNormalLength = sqrt(dNormal[0]*dNormal[0] + dNormal[1]*dNormal[1] + dNormal[2]*dNormal[2]);
	if(dNormalLength != 0.0)
	{
		dNormal[0] = dNormal[0]/dNormalLength;
		dNormal[1] = dNormal[1]/dNormalLength;
		dNormal[2] = dNormal[2]/dNormalLength;
	}
	else
	{
		dNormal[0] = 0.0;
		dNormal[1] = 0.0;
		dNormal[2] = 1.0;
	}
}

void CDrawObjectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_UP:
		translateY+=halfHeight/30;
		break;
	case VK_DOWN:
        translateY-=halfHeight/30;
		break;
	case VK_LEFT:
		translateX-=halfWidth/30;
		break;
	case VK_RIGHT:
		translateX+=halfWidth/30;
		break;

    default:
        break;
    }
	//RenderScene();
	//CRect rt;
	//GetClientRect(&rt);
	//HWND hwnd = ::GetParent(m_hWnd);
	//::PostMessage(hwnd,WM_SIZE,0,0);
	//InvalidateRect(rt,TRUE);
	Invalidate(FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CDrawObjectView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0)
		eyeZ-=eyeZ/10;
	else
		eyeZ+=eyeZ/10;

	Invalidate(FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CDrawObjectView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu PopMenu;
	CMenu *pMenu;  
	CPoint pt; 
	pt = point ; 

	PopMenu.LoadMenu(IDR_MAINFRAME); //调用菜单资源 
	ClientToScreen (&pt); //客户区坐标到屏幕坐标转换 
	pMenu = PopMenu.GetSubMenu (3); //取得子菜单 

	//pMenu->EnableMenuItem(ID_LOAD_OBJECT_DATA, MF_BYCOMMAND|MF_GRAYED);
	//pMenu->ModifyMenu(ID_LOAD_OBJECT_DATA,MF_BYCOMMAND,ID_LOAD_OBJECT_DATA, "newname");

	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,  
			pt.x,pt.y,this); //使用TrackPopupMenu函数来弹出菜单

	CView::OnRButtonDown(nFlags, point);
}

void CDrawObjectView::OnSaveToDib() 
{
	// TODO: Add your command handler code here
	BeginWaitCursor();

	CRect rc;
	GetClientRect(rc);

	BITMAPFILEHEADER bmfHdr;//位图文件头
	LPBITMAPINFOHEADER lpBI;//位图信息
	DWORD dwBitsSize;//位图位数据的大小
	HDIB hDIB;//内存句柄
	LPSTR pDIBits;//位图位数据指针

	dwBitsSize=sizeof(BITMAPINFOHEADER)+rc.Width()*rc.Height()*3;
	//内存分配
	hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,dwBitsSize+32);
	if(hDIB==0)	return;
	//内存指定与指针计算
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDIB);
	if(lpBI==NULL)	return;
	
	pDIBits=(LPSTR)lpBI+sizeof(BITMAPINFOHEADER);

	//填充文件及位图信息结构
	bmfHdr.bfType=0x4d42;
	bmfHdr.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+rc.Width()*rc.Height()*3;
	bmfHdr.bfReserved1=0;
	bmfHdr.bfReserved2=0;
	bmfHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	lpBI->biSize=sizeof(BITMAPINFOHEADER);
	lpBI->biWidth=rc.Width();
	lpBI->biHeight=rc.Height();
	lpBI->biPlanes=1;
	lpBI->biBitCount=24;
	lpBI->biCompression=BI_RGB;
	lpBI->biClrImportant=0;
	lpBI->biSizeImage=rc.Width()*abs(rc.Height())*3;
	lpBI->biXPelsPerMeter=0;
	lpBI->biYPelsPerMeter=0;
	lpBI->biClrUsed=0;
	lpBI->biClrImportant=0;
	
	//读取前台缓存
	glReadBuffer(GL_FRONT);
	//获取客户区象素数据
	glReadPixels(0,0,rc.Width(),rc.Height(),GL_BGR_EXT,GL_UNSIGNED_BYTE,(GLubyte*)pDIBits);
	//CString FileName="f:\\dibtest.bmp";
	CString strFileName;
	CFileDialog dlg(FALSE, "*.bmp", strFileName.GetBuffer(0), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "位图文件(*.bmp)|*.bmp||", this);
	if(dlg.DoModal() != IDOK)
		return;
	CString strfilePath = dlg.GetPathName();
	
	CFile file(strfilePath,CFile::modeCreate|CFile::modeReadWrite|CFile::shareExclusive);

	//写入数据
	file.Write((LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER));
	file.Write((LPSTR)lpBI,dwBitsSize);
	file.Close();

	::GlobalUnlock((HGLOBAL)hDIB);
	//在此处，现在可以无效化句柄hDIB
	::GlobalFree((HGLOBAL)hDIB);

	EndWaitCursor();
}

void CDrawObjectView::OnJiaZaiJing() 
{
	// TODO: Add your command handler code here
	

	/**/CFileDialog dlg(TRUE, "", "*.dev",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"SMF Files(*.dev)|*.dev|All Files(*.*)|*.*||"); 
	if ( dlg.DoModal()!=IDOK ) 
		return;
	CString sFileName=dlg.GetPathName();
	//double jing[10400][10];
	//int jingCount;
	grd->readJingFile(sFileName,jing,jingCount);
	drawJing(jingCount,jing);
}
