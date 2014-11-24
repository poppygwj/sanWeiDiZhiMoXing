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
		char specgrid[10];//�ļ��еĹؼ��ֶ�Ӧ���ַ���
		double coord[50][100][6];//�ļ��йؼ��ֶ�Ӧ�µ���
		double actnum[50][50][100];//�ļ��йؼ��ֶ�Ӧ�µ���
		double zcorn[100][100][200];//�ļ��йؼ��ֶ�Ӧ�µ���
		double xcorn[100][100][200];//�������x����
		double ycorn[100][100][200];//�������y����
		double zcornDisplay[100][100][200];//Wen
		double xcornDisplay[100][100][200];//Wen
		double ycornDisplay[100][100][200];//Wen
		double zcorn1[104][100][200];//=========
		double xcorn1[104][100][200];//�������Ĳ�֮���x,y,z���ꡣ
		double ycorn1[104][100][200];//==========
		int m,n,k;//ά��
		double z2[2080000];//===================
		double x2[2080000];//���������x,y,z����
		double y2[2080000];//===================
		double z3[1040000];//===============================
		double x3[1040000];//����ȥ���ظ��ĵ���x,y,z����
		double y3[1040000];//=================================
		int faceX[2080000][4];//=================================
	    int faceY[2080000][4];//�����Ķ�Ӧ��ϵ
	    int faceZ[2080000][4];//=================================
		int faceBoundaryX[10000][4];//=================================
	    int faceBoundaryY[10000][4];//�߽������Ķ�Ӧ��ϵ
	    int faceBoundaryZ[10000][4];//=================================
		int flag[2080000];//��Ӧ��ϵ
		int flag2[1040000];//���Ӧ��ϵ
		int uniqueFlag[1040000];
		int uniqueFlag2[1040000];
		int n3;//�����ĵ������
		//int intersection[1040][1040];//��¼�н���Ĺ�
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
		int gunYA[2080000][2];//��¼a������������±꣨x3���±꣩
		int gunYB[2080000][2];//��¼b������������±꣨x3���±꣩
		double gunYAZ[2080000][2];//��¼a���������Zֵ
		double gunYBZ[2080000][2];//��¼b���������Zֵ
		int flagYg[2080000];//���a,b�����غϵ��±�
		int YDCcount;//���غϹ�������
		int Yxb[104000];//��[�±�]��gunA�е�һ������x2�еĶ�Ӧ�±꡾gunA�еڶ������Լ�gunB�е�������ɼ��������---�״�����----C��ֵ��gunAZ�ж�Ӧ���±�
		int YconCount;//Connections������
		int gunYXB[104000];//gun�е�(gunA�е�һ����)��x2�ж�Ӧ���±꡾gunA�еڶ������Լ�gunB�е�������ɼ��������
		
		int gunXA[2080000][2];//��¼a������������±꣨x3���±꣩
		int gunXB[2080000][2];//��¼b������������±꣨x3���±꣩
		double gunXAZ[2080000][2];//��¼a���������Zֵ
		double gunXBZ[2080000][2];//��¼b���������Zֵ
		int flagXg[2080000];//���a,b�����غϵ��±�
		int XDCcount;//���غϹ�������
		int Xxb[104000];//��[�±�]��gunA�е�һ������x2�еĶ�Ӧ�±꡾gunA�еڶ������Լ�gunB�е�������ɼ��������---�״�����----C��ֵ��gunAZ�ж�Ӧ���±�
		int XconCount;//Connections������
		int gunXXB[104000];//gun�е�(gunA�е�һ����)��x2�ж�Ӧ���±꡾gunA�еڶ������Լ�gunB�е�������ɼ��������
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
//	void readFile();//���ļ��������������ݷ�����Ӧ����
	void readFile(CString filename);
	void readJingFile(CString filename,double jing[][10],int &jingCount);
	void setMNK(CString str);//����ά��
	void setXYcorn();//����x,y,z����
	void addFour();//�����Ĳ�
	void swap(double x[],double y[],double z[], int low, int high );//����
//	bool lt(double x[],double y[],double z[],const int low, const int high );//�Ƚϴ�С
//	void bubsort(  double x[],double y[],double z[], int n );//ð������
	void setXYZ2();//������
	void unique(int &n3,int count,double x2[],double y2[],double z2[],double x3[],double y3[],double z3[],int flag[],int flag2[]);//���򣬲���ȥ���ظ��ĵ�
    void setFaceXYZ();
	void setgun();//���ù�
	void getPointCloud(CArray<Point3D,Point3D> *pointArray);
	void normalize4display(CArray<Point3D,Point3D> *pointArray);//���滯

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
//	void quickSort(double x[],double y[],double z[], int l, int r);//��������
//	bool lt(double x1,double y1,double z1,double x2,double y2,double z2 );//�Ƚ�(x1,y1,z1)��(x2,y2,z2)��С

//	void Merge(double x[],double y[],double z[], int p, int q, int r);//�鲢�����еĺϲ�
//	void MergeSort(double x[],double y[],double z[], int p, int r);//�鲢����

	//bool IfIntersection(double a[],double b[]);//�����������Ƿ��ཻ
	//void setJD();//��¼�ཻ�Ĺ�
	void setConnections(int DCcount,int C[][2],int &conCount);
	bool doIntersect(double za1[],double za2[],double zb1[],double zb2[]);
	bool overlap(double za1,double za2,double zb1,double zb2);

	void computeFaceGeometry(int &n4,int fangxiang,int conCount,int C[][2],int xb[],int gunXB[],int Corners[],int numNodes[]);
	void intersection(int la[],int lb[],int nt);//��������
	bool isCoincide(int face[][4],int f);
	void setTempGun(int DCcount,int flagg[],int max,double gunAZ[][2],double gunBZ[][2],int xb[]);

	void getDianXuHao(int fangxiang,int xh,int jieGuo[][4],int fir);
	void getDianXuHao(int fangxiang,int xh,int jieGuoA[][2],int jieGuoB[][2],double jieGuoAZ[][2],double jieGuoBZ[][2],int fir);
};

#endif // !defined(AFX_GRDECL_H__BB5E39CA_D99C_4FD0_A96E_58180B8824A9__INCLUDED_)
