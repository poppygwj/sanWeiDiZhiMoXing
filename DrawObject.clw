; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CJingDuTiao
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DrawObject.h"
LastPage=0

ClassCount=8
Class1=CDrawObjectApp
Class2=CDrawObjectDoc
Class3=CDrawObjectView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CSetColorDlg
Resource3=IDD_DIALOG2
Class7=CLightingDlg
Resource4=IDD_DIALOG1
Class8=CJingDuTiao
Resource5=IDD_DIALOG3

[CLS:CDrawObjectApp]
Type=0
HeaderFile=DrawObject.h
ImplementationFile=DrawObject.cpp
Filter=N

[CLS:CDrawObjectDoc]
Type=0
HeaderFile=DrawObjectDoc.h
ImplementationFile=DrawObjectDoc.cpp
Filter=N

[CLS:CDrawObjectView]
Type=0
HeaderFile=DrawObjectView.h
ImplementationFile=DrawObjectView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CDrawObjectView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=JiaZaiJing
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=DrawObject.cpp
ImplementationFile=DrawObject.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_LOAD_OBJECT_DATA
Command17=ID_DRAW_WITH_POINT
Command18=ID_DRAW_WITH_TRIANGLE
Command19=ID_DRAW_WITH_FILL
Command20=ID_COLOR_SET
Command21=ID_SET_LIGHT
Command22=ID_SAVE_TO_DIB
Command23=ID_APP_ABOUT
Command24=JiaZaiJing
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_LOAD_OBJECT_DATA
Command10=ID_DRAW_WITH_POINT
Command11=ID_DRAW_WITH_TRIANGLE
Command12=ID_DRAW_WITH_FILL
Command13=ID_SAVE_TO_DIB
CommandCount=13

[DLG:IDD_DIALOG1]
Type=1
Class=CSetColorDlg
ControlCount=36
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COLOR_RED,edit,1350631552
Control7=IDC_COLOR_GREEN,edit,1350631552
Control8=IDC_COLOR_BLUE,edit,1350631552
Control9=IDC_COLOR_MASK_R,button,1342242819
Control10=IDC_COLOR_MASK_G,button,1342242819
Control11=IDC_COLOR_MASK_B,button,1342242819
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_M_AMBIENT_R,edit,1350631552
Control21=IDC_M_AMBIENT_B,edit,1350631552
Control22=IDC_M_AMBIENT_G,edit,1350631552
Control23=IDC_M_DIFFUSE_R,edit,1350631552
Control24=IDC_M_DIFFUSE_G,edit,1350631552
Control25=IDC_M_DIFFUSE_B,edit,1350631552
Control26=IDC_M_SPECULAR_R,edit,1350631552
Control27=IDC_M_SPECULAR_G,edit,1350631552
Control28=IDC_M_SPECULAR_B,edit,1350631552
Control29=IDC_M_EMISSION_R,edit,1350631552
Control30=IDC_M_EMISSION_G,edit,1350631552
Control31=IDC_M_EMISSION_B,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,static,1342308352
Control35=IDC_M_SHININESS,edit,1350631552
Control36=IDC_MATERIAL_FLAG,button,1342242819

[CLS:CSetColorDlg]
Type=0
HeaderFile=SetColorDlg.h
ImplementationFile=SetColorDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSetColorDlg

[DLG:IDD_DIALOG2]
Type=1
Class=CLightingDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_L_AMBIENT_R,edit,1350631552
Control13=IDC_L_AMBIENT_B,edit,1350631552
Control14=IDC_L_AMBIENT_G,edit,1350631552
Control15=IDC_L_DIFFUSE_R,edit,1350631552
Control16=IDC_L_DIFFUSE_G,edit,1350631552
Control17=IDC_L_DIFFUSE_B,edit,1350631552
Control18=IDC_L_SPECULAR_R,edit,1350631552
Control19=IDC_L_SPECULAR_G,edit,1350631552
Control20=IDC_L_SPECULAR_B,edit,1350631552
Control21=IDC_L_POSITION_X,edit,1350631552
Control22=IDC_L_POSITION_Y,edit,1350631552
Control23=IDC_L_POSITION_Z,edit,1350631552
Control24=IDC_STATIC,static,1342308352

[CLS:CLightingDlg]
Type=0
HeaderFile=LightingDlg.h
ImplementationFile=LightingDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLightingDlg

[DLG:IDD_DIALOG3]
Type=1
Class=CJingDuTiao
ControlCount=2
Control1=IDC_PROGRESS1,msctls_progress32,1342177281
Control2=IDC_STATIC,static,1342308352

[CLS:CJingDuTiao]
Type=0
HeaderFile=JingDuTiao.h
ImplementationFile=JingDuTiao.cpp
BaseClass=CDialog
Filter=D
LastObject=CJingDuTiao
VirtualFilter=dWC

