// GRDECL.h: interface for the GRDECL class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "math.h"
#include "afxtempl.h"


#if !defined(AFX_GRDECL_H__BB5E39CA_D99C_4FD0_A96E_58180B8824A9__INCLUDED_)
#define AFX_GRDECL_H__BB5E39CA_D99C_4FD0_A96E_58180B8824A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const int max=3000*1024;

enum{LoadData,	Points,	Lines,	Filling};

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Point3D;

typedef struct
{
	GLint first;
	GLint second;
	GLint third;
}Triangle;


class GRDECL  
{
public:
		char specgrid[10];//文件中的关键字对应的字符串
		double coord[50][100][6];//文件中关键字对应下的数
		double actnum[50][50][100];//文件中关键字对应下的数
		double zcorn[100][100][200];//文件中关键字对应下的数
		double xcorn[100][100][200];//计算出的x坐标
		double ycorn[100][100][200];//计算出的y坐标
		double zcornDisplay[100][100][200];//Wen
		double xcornDisplay[100][100][200];//Wen
		double ycornDisplay[100][100][200];//Wen
		double zcorn1[104][100][200];//=========
		double xcorn1[104][100][200];//增加了四层之后的x,y,z坐标。
		double ycorn1[104][100][200];//==========
		int m,n,k;//维数
		double z2[2080000];//===================
		double x2[2080000];//向量化后的x,y,z坐标
		double y2[2080000];//===================
		double z3[1040000];//===============================
		double x3[1040000];//排序，去掉重复的点后的x,y,z坐标
		double y3[1040000];//=================================
		int faceX[2080000][4];//=================================
	    int faceY[2080000][4];//面与点的对应关系
	    int faceZ[2080000][4];//=================================
		int faceBoundaryX[10000][4];//=================================
	    int faceBoundaryY[10000][4];//边界面与点的对应关系
	    int faceBoundaryZ[10000][4];//=================================
		int flag[2080000];//对应关系
		int flag2[1040000];//逆对应关系
		int uniqueFlag[1040000];
		int uniqueFlag2[1040000];
		int n3;//排序后的点的总数
		//int intersection[1040][1040];//记录有交点的棍
		int YC[1040][2];
		int XC[1040][2];
		double centerY;
	    double centerX;
		double centerZ;
		double zmax,zmaxDisplay;
		double zmin,zminDisplay;
		double xmax,xmaxDisplay;
		double xmin,xminDisplay;
		double ymax,ymaxDisplay;
		double ymin,yminDisplay;
		float eyeZ;
		int gunYA[2080000][2];//记录a棍的两个点的下标（x3的下标）
		int gunYB[2080000][2];//记录b棍的两个点的下标（x3的下标）
		double gunYAZ[2080000][2];//记录a棍两个点的Z值
		double gunYBZ[2080000][2];//记录b棍两个点的Z值
		int flagYg[2080000];//标记a,b棍不重合的下标
		int YDCcount;//不重合棍的数量
		int Yxb[104000];//第[下标]根gunA中第一个点再x2中的对应下标【gunA中第二个点以及gunB中的两个点可计算得来】---首次意义----C的值在gunAZ中对应的下标
		int YconCount;//Connections的数量
		int gunYXB[104000];//gun中点(gunA中第一个点)再x2中对应的下标【gunA中第二个点以及gunB中的两个点可计算得来】
		
		int gunXA[2080000][2];//记录a棍的两个点的下标（x3的下标）
		int gunXB[2080000][2];//记录b棍的两个点的下标（x3的下标）
		double gunXAZ[2080000][2];//记录a棍两个点的Z值
		double gunXBZ[2080000][2];//记录b棍两个点的Z值
		int flagXg[2080000];//标记a,b棍不重合的下标
		int XDCcount;//不重合棍的数量
		int Xxb[104000];//第[下标]根gunA中第一个点再x2中的对应下标【gunA中第二个点以及gunB中的两个点可计算得来】---首次意义----C的值在gunAZ中对应的下标
		int XconCount;//Connections的数量
		int gunXXB[104000];//gun中点(gunA中第一个点)再x2中对应的下标【gunA中第二个点以及gunB中的两个点可计算得来】
		double tgunAZ[1040000][2];
        double tgunBZ[1040000][2];
		int XDuanCengDianCount;
		int YDuanCengDianCount;
		int XnumNodes[240000];
	    int XCorners[1040000];
		int YnumNodes[240000];
	    int YCorners[1040000];
		double X[100];
		double Y[100];
		double Z[100];
		double sjX[100];
		double sjY[100];
		double sjZ[100];
		int xn,yn,zn;
		double jing[10400][10];
		int jingCount;
		double XNormal[1040000][3];
		double YNormal[1040000][3];
		double ZNormal[1040000][3];
		double BXNormal[52000][3];
		double BYNormal[52000][3];
		double BZNormal[52000][3];
		double DCXNormal[10400][3];
		double DCYNormal[10400][3];
		//int jd;


	GRDECL();
	virtual ~GRDECL();
//	void readFile();//读文件，并将所有数据放入相应变量
	void readFile(CString filename);
	void readJingFile(CString filename,double jing[][10],int &jingCount);
	void setMNK(CString str);//设置维数
	void setXYcorn();//计算x,y,z坐标
	void addFour();//增加四层
	void swap(double x[],double y[],double z[], int low, int high );//交换
//	bool lt(double x[],double y[],double z[],const int low, const int high );//比较大小
//	void bubsort(  double x[],double y[],double z[], int n );//冒泡排序
	void setXYZ2();//向量化
	void unique(int &n3,int count,double x2[],double y2[],double z2[],double x3[],double y3[],double z3[],int flag[],int flag2[]);//排序，并且去掉重复的点
    void setFaceXYZ();
	void setgun();//设置棍
	void getPointCloud(CArray<Point3D,Point3D> *pointArray);
	void normalize4display(CArray<Point3D,Point3D> *pointArray);//正规化

	double getXminDisplay(){return xminDisplay;};
	double getYminDisplay(){return yminDisplay;};
	double getZminDisplay(){return zminDisplay;};
	double getXmaxDisplay(){return xmaxDisplay;};
	double getYmaxDisplay(){return ymaxDisplay;};
	double getZmaxDisplay(){return zmaxDisplay;};

	float getEyeZ(){return eyeZ;};

	void setZuoBiao();
	void setNormal();
	void setNormal(int face[][4],int a,double normal[][3]);

	//void setFaceXYZ();
//	void quickSort(double x[],double y[],double z[], int l, int r);//快速排序
//	bool lt(double x1,double y1,double z1,double x2,double y2,double z2 );//比较(x1,y1,z1)和(x2,y2,z2)大小

//	void Merge(double x[],double y[],double z[], int p, int q, int r);//归并排序中的合并
//	void MergeSort(double x[],double y[],double z[], int p, int r);//归并排序

	//bool IfIntersection(double a[],double b[]);//计算两个棍是否相交
	//void setJD();//记录相交的棍
	void setConnections(int DCcount,int C[][2],int &conCount);
	bool doIntersect(double za1[],double za2[],double zb1[],double zb2[]);
	bool overlap(double za1,double za2,double zb1,double zb2);

	void computeFaceGeometry(int &n4,int fangxiang,int conCount,int C[][2],int xb[],int gunXB[],int Corners[],int numNodes[]);
	void intersection(int la[],int lb[],int nt);//棍棍交点
	bool isCoincide(int face[][4],int f);
	void setTempGun(int DCcount,int flagg[],int max,double gunAZ[][2],double gunBZ[][2],int xb[]);

	void getDianXuHao(int fangxiang,int xh,int jieGuo[][4],int fir);
	void getDianXuHao(int fangxiang,int xh,int jieGuoA[][2],int jieGuoB[][2],double jieGuoAZ[][2],double jieGuoBZ[][2],int fir);
};

#endif // !defined(AFX_GRDECL_H__BB5E39CA_D99C_4FD0_A96E_58180B8824A9__INCLUDED_)
