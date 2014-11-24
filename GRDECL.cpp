// GRDECL.cpp: implementation of the GRDECL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mrst_01.h"
#include "GRDECL.h"
#include "PaiXu.h"
#include <windows.h>
#include <iostream.h>
#include<stdio.h>
#include <string>
#include "time.h"
#include <shlwapi.h>
#include <fstream.h>
#include <JingDuTiao.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GRDECL::GRDECL()
{

}

GRDECL::~GRDECL()
{

}
void GRDECL::readJingFile(CString filename,double jing[][10],int &jingCount)
{
	FILE *fp;
	char *buf=(char *)malloc(max*sizeof(char));
	if((fp=fopen(filename,"rw+"))==NULL)
	{
		MessageBox(NULL, "该文件不存在！！！", "提示", MB_OK);
	}else
	{
		int len=0;
		memset(buf,0,strlen(buf));
		len=fread(buf,1,max,fp);
		//char aa=buf[0];
		buf[len]='*';
		char *p=buf;
		char aa;
		int i;
		CString st,spe="";
		//aa=*p++;
		//st.Format("%c",aa);
			
		for(i=0;i<11;i++)
		{
			aa=*p++;
			st.Format("%c",aa);
			while(st!="\n")
			{
				aa=*p++;
				st.Format("%c",aa);
			}
			
		}
		int t=0;
		do{
			
			for(i=0;i<10;)
			{
				spe="";
				aa=*p++;
				if(aa=='*')break;
			    st.Format("%c",aa);
				while(st!=" "&&st!="\n"&&aa!='*')
				{
					spe+=aa;
					aa=*p++;
					//if(aa=='*')break;
				    st.Format("%c",aa);
				}
				if(spe!="")
				{
					jing[t][i]=atof(spe);
					i++;
				}
				if(aa=='*')break;
			}
			t++;
		}while(aa!='*');
		jingCount=t-1;
		//for(i=0;i<t;i++)
		//{
         //   st.Format("%d",jingCount);
		    MessageBox(NULL, "加载数据成功，正在画图中……", "提示", MB_OK);
		//}
		fclose(fp);
	}
}
void GRDECL::readFile(CString filename)
{
	//CJingDuTiao dlg;
	//dlg.DoModal();
	//dlg.m_ctrlProgress.SetRange(0,100);
	//dlg.m_ctrlProgress.SetStep(10);
	//jd=10;
	FILE *fp;
	char *buf=(char *)malloc(max*sizeof(char));
	clock_t start, finish;
	//MessageBox(NULL, "aaaa", "提示", MB_OK);
	start=clock();
	if((fp=fopen(filename,"rw+"))==NULL)
	{
		MessageBox(NULL, "该文件不存在！！！", "提示", MB_OK);
	}else
	{	
		//memset(buf, 0, sizeof(buf));
		//max;
		int len=0;
		memset(buf,0,strlen(buf));
		len=fread(buf,1,max,fp);
		//char aa=buf[0];
		buf[len]='*';
        CString str;
         str.Format("%i",len);
		//MessageBox(NULL, str, "提示", MB_OK);
		//MessageBox(NULL, buf, "提示", MB_OK);
		char *p=buf;
		char aa;
		CString st,spe="";
		do{
			aa=*p++;
			st.Format("%c",aa);
			if(st=="S"||st=="C"||st=="Z"||st=="A")
			{
				spe="";
				spe+=st;
				while(st!="\n"){
					aa=*p++;
			        st.Format("%c",aa);
					spe+=st;
				}
			}
			/*if(st=="C")
				{
				spe="";
				spe+=st;
				while(st!="\n"){
					aa=*p++;
			        st.Format("%c",aa);
					spe+=st;
				}
			}*/
			if(spe=="SPECGRID\n")
			{
				spe="";
                aa=*p++;
			    st.Format("%c",aa);
				spe+=st;
				while(st!="\n")
				{
					aa=*p++;
			        st.Format("%c",aa);
					spe+=st;
				}
				setMNK(spe);

			}
			if(spe=="COORD\n")
			{
				for(int i=0;i<=n;i++)
				{
					for(int j=0;j<=m;j++)
					{
						for(int l=0;l<6;l++)
						{
							spe="";
                            aa=*p++;
			                st.Format("%c",aa);
						    //spe+=st;
						    while(st!=" "&&st!="\n")
							{
						        spe+=st;
						        aa=*p++;
			                    st.Format("%c",aa);					       	
							}
							coord[i][j][l]=atof(spe);
						}
						
					}
					p++;
				}
			}
			if(spe=="ZCORN\n")
			{
				for(int i=0;i<2*k;i++)
				{
					for(int j=0;j<2*n;j++)
					{
						for(int l=0;l<2*m;l++)
						{
							spe="";
							aa=*p++;
			                st.Format("%c",aa);
						    while(st!=" "&&st!="\n")
							{
						        spe+=st;
						        aa=*p++;
			                    st.Format("%c",aa);					       	
							}
  							zcorn[i][j][l]=atof(spe);
						}
						p++;
					}

				}
			}
			if(spe=="ACTNUM\n")
			{
				p++;
				p++;
				for(int i=0;i<k;i++)
				{
					for(int j=0;j<n;j++)
					{
						for(int l=0;l<m;l++)
						{
							spe="";
							aa=*p++;
			                st.Format("%c",aa);
						    while(st!=" "&&st!="\n")
							{
						        spe+=st;
						        aa=*p++;
			                    st.Format("%c",aa);					       	
							}
							actnum[i][j][l]=atof(spe);
						}
					}
					p++;
				}
			}
				/*for(int q=0;q<=n;q++)
					for(int w=0;w<=m;w++)
					{
						for(int e=0;e<=5;e++)
						{
                            st.Format("%i",w);
				            MessageBox(NULL, zcorn[q][w][0]+" "+st, "提示", MB_OK);
					    }
					}
					*/
			
			//MessageBox(NULL, spe, "提示", MB_OK);
		}while(aa!='*');
		finish=clock();
		double aaa=double(finish-start);
		//st.Format("%f",aaa);
		//MessageBox(NULL, st, "提示", MB_OK);
		start=clock();
//		setXYcorn();
		finish=clock();
		aaa=double(finish-start);
		//st.Format("%f",aaa);
		//MessageBox(NULL, st, "提示", MB_OK);
          /*for(int q=0;q<=n;q++)
					for(int w=0;w<=m;w++)
					{
						for(int e=0;e<=5;e++)
						{
							float ab=0.0;
							ab=atof(zcorn[q][w][0]);
                            st.Format("%f",ab);
				            MessageBox(NULL, st, "提示", MB_OK);
					    }
					}*/
					
		
		/*char a[10];
	
        fgets(a,10,fp);
		if(a[0]=='S')
		{
		  fgets(specgrid,10,fp);
		}
		setMNK(specgrid);
		CString str; 
        do{
			fgets(a,10,fp);
		    str.Format(a);
		}while(strcmp(str,"COORD\n")!=0);
		SCtring *ss;
		int ab=fread(ss,7,19,fp);
		MessageBox(NULL, ab+"", "提示", MB_OK);
		*/
		fclose(fp);
	}
	
	
}

void GRDECL::getPointCloud(CArray<Point3D,Point3D> *pointArray)
{
	Point3D point;
	for(int i=0;i<=k;i++)
	{
		for(int j=0;j<=n;j++)
		{
			for(int l=0;l<m;l++)
			{
				point.x = xcorn[i][j][l];
				point.y = ycorn[i][j][l];
				point.z = zcorn[i][j][l];
				pointArray->Add(point);
				
			}
			
		}
	}
	
}
double zra;
void GRDECL::normalize4display(CArray<Point3D,Point3D> *pointArray)//标准化
{
	Point3D point;
	//calculate range
	zmax=zcorn1[0][0][0],zmin=zcorn1[0][0][0];
	xmax=xcorn1[0][0][0],xmin=xcorn1[0][0][0];
	ymax=ycorn1[0][0][0],ymin=ycorn1[0][0][0];
	for(int i1=0;i1<2*k+4;i1++)
		for(int j1=0;j1<2*n;j1++)
			for(int l1=0;l1<2*m;l1++)
			{
				if(zmax<zcorn1[i1][j1][l1])zmax=zcorn1[i1][j1][l1];
				if(zmin>zcorn1[i1][j1][l1])zmin=zcorn1[i1][j1][l1];
				if(xmax<xcorn1[i1][j1][l1])xmax=xcorn1[i1][j1][l1];
				if(xmin>xcorn1[i1][j1][l1])xmin=xcorn1[i1][j1][l1];
				if(ymax<ycorn1[i1][j1][l1])ymax=ycorn1[i1][j1][l1];
				if(ymin>ycorn1[i1][j1][l1])ymin=ycorn1[i1][j1][l1];
			}
	centerY=(ymax+ymin)/2;
	centerX=(xmax+xmin)/2;
	centerZ=(zmax+zmin)/2;
	//normalize
	double xratio = 200/(xmax-xmin);  
	double yratio = 200/(ymax-ymin);
	double zratio = 100/(zmax-zmin);
    zra=zmax-zmin+1;
/*	double ratio;
	if ((xratio>=yratio)&&(zratio>=yratio)) 
		ratio = yratio;

	if ((yratio>=xratio)&&(zratio>=xratio)) 
		ratio = xratio;

	if ((xratio>=zratio)&&(yratio>=zratio)) 
		ratio = zratio;*/

	for(int i=0;i<k*2+4;i++)
	{
		//if(i!=2&&i!=1&&i!=0&&i!=k*2+2&&i!=k*2+1)i++;
		for(int j=0;j<2*n;j++)
		{
			for(int l=0;l<2*m;l++)
			{
				
				xcornDisplay[i][j][l] = (xcorn1[i][j][l] - centerX) *xratio;//ratio;
				ycornDisplay[i][j][l] = (ycorn1[i][j][l] - centerY) *yratio;//ratio;
				zcornDisplay[i][j][l] = (zcorn1[i][j][l] - centerZ) *zratio;//ratio;	
				point.x = xcornDisplay[i][j][l];
				point.y = ycornDisplay[i][j][l];
				point.z = zcornDisplay[i][j][l];

				if(eyeZ<fabs(point.z))
					eyeZ=fabs(point.z);

				pointArray->Add(point);
				//if(l==0)l--;
			}
			//if(j==0)j--;
		}
	}

	xminDisplay = (xmin - centerX) *xratio;//ratio;
	xmaxDisplay = (xmax - centerX) *xratio;//ratio;
	yminDisplay = (ymin - centerY) *yratio;//ratio;
	ymaxDisplay = (ymax - centerY) *yratio;//ratio; 
	zminDisplay = (zmin - centerZ) *zratio;//ratio;
	zmaxDisplay = (zmax - centerZ) *zratio;//ratio;
	
}
void GRDECL::setZuoBiao()
{
	double xratio = 200/(xmax-xmin);  
	double yratio = 200/(ymax-ymin);
	double zratio = 100/(zmax-zmin);
	int i;
	xn=(xmax-xmin)/200+2;
	yn=(ymax-ymin)/100+2;
	zn=(zmax-zmin)/5+2;
	//double X[100],Y[100],Z[100];
	for(i=0;i<xn;i++)
	{
		X[i]=(xmin-centerX+(i-1)*200)*xratio;
		sjX[i]=xmin+(i-1)*200;
	}
	for(i=0;i<yn;i++)
	{
		Y[i]=(ymin-centerY+(i-1)*100)*yratio;
		sjY[i]=ymin+(i-1)*100;
	}
	for(i=0;i<zn;i++)
	{
		Z[i]=(zmin-centerZ+(i-1)*5)*zratio;
		sjZ[i]=zmin+(i-1)*5;
	}
}

void GRDECL::setMNK(CString str)
{
	
	int temp[]={0,0,0},j=-1;
	boolean f=true;
	//CString str;
	//str.Format(a);
	//MessageBox(NULL, str, "提示", MB_OK);
	for(int i=0;i<str.GetLength()&&j<3;i++)
	{
		if(str.GetAt(i)>='0'&&str.GetAt(i)<='9')
		{
			//char c[]={'1','2'};
			//MessageBox(NULL, i+"", "提示", MB_OK);
			temp[j]=temp[j]*10+(int)str.GetAt(i)-48;
		//	MessageBox(NULL, temp[j]+"", "提示", MB_OK);
			f=true;
		}else
		{
			if(f){
				f=false;
			    j++;
			}
		}
	}
	m=temp[0];n=temp[1];k=temp[2];
}
void GRDECL::setXYcorn()
{
	double tk=0.0;
	for(int i=0;i<2*k;i++)
	{
		for(int j=0;j<2*n;j++)
		{
			for(int l=0;l<2*m;l++)
			{
				tk=(coord[(j+1)/2][(l+1)/2][2]-zcorn[i][j][l])/(coord[(j+1)/2][(l+1)/2][2]-coord[(j+1)/2][(l+1)/2][5]);
				xcorn[i][j][l]=coord[(j+1)/2][(l+1)/2][0]-(tk*(coord[(j+1)/2][(l+1)/2][0]-coord[(j+1)/2][(l+1)/2][3]));
				ycorn[i][j][l]=coord[(j+1)/2][(l+1)/2][1]-(tk*(coord[(j+1)/2][(l+1)/2][1]-coord[(j+1)/2][(l+1)/2][4]));
				/*CString str="";
				str.Format("%i",l);
				MessageBox(NULL, str, "提示", MB_OK);
				str.Format("%f",xcorn[i][j][l]);
				MessageBox(NULL, str, "提示", MB_OK);
				str.Format("%f",ycorn[i][j][l]);
				MessageBox(NULL, str, "提示", MB_OK);*/
			}
		}
	}
}

void GRDECL::addFour()//加四层
{
	//int q=0;
	zmax=zcorn[0][0][0],zmin=zcorn[0][0][0];
	xmax=xcorn[0][0][0],xmin=xcorn[0][0][0];
	ymax=ycorn[0][0][0],ymin=ycorn[0][0][0];
	for(int i1=0;i1<2*k;i1++)
		for(int j1=0;j1<2*n;j1++)
			for(int l1=0;l1<2*m;l1++)
			{
				if(zmax<zcorn[i1][j1][l1])zmax=zcorn[i1][j1][l1];
				if(zmin>zcorn[i1][j1][l1])zmin=zcorn[i1][j1][l1];
				if(xmax<xcorn[i1][j1][l1])xmax=xcorn[i1][j1][l1];
				if(xmin>xcorn[i1][j1][l1])xmin=xcorn[i1][j1][l1];
				if(ymax<ycorn[i1][j1][l1])ymax=ycorn[i1][j1][l1];
				if(ymin>ycorn[i1][j1][l1])ymin=ycorn[i1][j1][l1];
			}
			//zmax;
			//zmin;
			centerY=(ymax-ymin)/2;
			centerX=(xmax-xmin)/2;
	for(int i=0;i<2*k+4;i++)
		for(int j=0;j<2*n;j++)
			for(int l=0;l<2*m;l++)
			{
				if(i==0||i==1)
				{
					xcorn1[i][j][l]=xcorn[0][j][l];
					ycorn1[i][j][l]=ycorn[0][j][l];
					zcorn1[i][j][l]=zmin-2+i;
				}else if(i==2*k+2||i==2*k+3)
				{
					//if(i==2*k+2)q++;
					xcorn1[i][j][l]=xcorn[2*k-1][j][l];
					ycorn1[i][j][l]=ycorn[2*k-1][j][l];
					zcorn1[i][j][l]=zmax+1-(2*k+2-i);
				}else
				{
					//q++;
					xcorn1[i][j][l]=xcorn[i-2][j][l];
					ycorn1[i][j][l]=ycorn[i-2][j][l];
					zcorn1[i][j][l]=zcorn[i-2][j][l];
				}
			}
}

void GRDECL::setXYZ2()
{
	int q=0;
	for(int i=0;i<2*k+4;i++)
		for(int j=0;j<2*n;j++)
			for(int l=0;l<2*m;l++)
			{
				x2[q]=xcorn1[i][j][l];
				y2[q]=ycorn1[i][j][l];
				z2[q]=zcorn1[i][j][l];
				//tempx[q]=x2[q];
				//tempy[q]=y2[q];
				//tempz[q]=z2[q];
				q++;
			}
	unique(n3,2*m*2*n*(2*k+4),x2,y2,z2,x3,y3,z3,flag,flag2);
}
double tempx[2080000];
double tempy[2080000];
double tempz[2080000];
//int tempp[999999999];	

void GRDECL::unique(int &n3,int count,double x2[],double y2[],double z2[],double x3[],double y3[],double z3[],int flag[],int flag2[])
{
	PaiXu *px=new PaiXu();
	for(int i=0;i<count;i++)
	{
		tempx[i]=x2[i];
		tempy[i]=y2[i];
		tempz[i]=z2[i];
	}
	//quickSort(tempx,tempy,tempz,0,2*m*2*n*(2*k+4)-1);
	//px->MergeSort(tempx,tempy,tempz,0,count-1);
	px->quickSort(tempx,tempy,tempz,0,count-1);
	x3[0]=tempx[0];
	y3[0]=tempy[0];
	z3[0]=tempz[0];
	int index=0;
	for(int j=1;j<count;j++)
	{
		if(x3[index]!=tempx[j]||y3[index]!=tempy[j]||z3[index]!=tempz[j])
		{
			index++;
			x3[index]=tempx[j];
			y3[index]=tempy[j];
			z3[index]=tempz[j];
		}
	}
	//index;j;
	if(index==0)n3=0;
	else n3=index+1;
	for(int l=0;l<count;l++)
	{
		index=0;
		while(x3[index]!=x2[l]||y3[index]!=y2[l]||z3[index]!=z2[l])
		{
			index++;
		}
		flag[l]=index;
	}
	for(int l1=0;l1<n3;l1++)
	{
		index=0;
		while(x2[index]!=x3[l1]||y2[index]!=y3[l1]||z2[index]!=z3[l1])
		{
			index++;
		}
		flag2[l1]=index;
	}

/*	ofstream fout("D://qq.txt");
	for(int j1=0;j1<n3;j1++)
			{
				//if(flag[i1*4*m*n+j1*2*m+l1]<100){
		CString aa="",bb="",cc="",dd="";
		aa.Format("%f",x3[j1]);
		bb.Format("%f",y3[j1]);
		cc.Format("%f",z3[j1]);
		//dd.Format("%d",flag[i1*4*m*n+j1*2*m+l1]);
	fout<<" "<<aa<<" "<<bb<<" "<<cc<<endl; // fout用法和cout一致, 不过是写到文件里面去
				}
	*/
}
/*
交换函数
*/
/*
void GRDECL::swap(double x[],double y[],double z[], int low, int high )
{    
    double temp = x[low];
    x[low] = x[high];
    x[high] = temp;

	temp = y[low];
    y[low] = y[high];
    y[high] = temp;

	temp = z[low];
    z[low] = z[high];
    z[high] = temp;
}*/

/*
小于函数
*/
/*
bool GRDECL::lt(double x[],double y[],double z[],const int low, const int high )
{
    
	if(z[low]<z[high])
	{
		return true;
	} else if(z[low]==z[high])
	{
		if(y[low]<y[high])
		{
			return true;
		}else if(y[low]==y[high])
		{
			if(x[low]<x[high])
			{
				return true;
			}else return false;
		}else return false;
    }else{return false;}
	
}
bool GRDECL::lt(double x1,double y1,double z1,double x2,double y2,double z2 )
{
    
	if(z1<z2)
	{
		return true;
	} else if(z1==z2)
	{
		if(y1<y2)
		{
			return true;
		}else if(y1==y2)
		{
			if(x1<=x2)
			{
				return true;
			}else return false;
		}else return false;
    }else{return false;}
	
}*/
/*
冒泡排序（稳定）
原理：第一次的内部for循环从记录数组的底部比较到顶部，比较相邻的值。
如果低序号的值比高序号的值大，则二者交换顺序
代价是n2
*/
/*
void GRDECL::bubsort( double x[],double y[],double z[], int n )
{
    int i,j;
    for ( i = 0; i < n-1; i++ )
    {
        for ( j = n-1; j > i; j-- )
        {    
            if( lt(x,y,z,j,j-1) )
                swap( x,y,z,j,j-1 );
        }
    }
}
void GRDECL::quickSort(double x[],double y[],double z[], int l, int r)  
{  
    if (l< r)  
    {        
        int i = l, j = r;
		double xx= x[l],yy=y[l],zz=z[l];  
        while (i < j)  
        {  
            while(i < j && lt(xx,yy,zz,x[j],y[j],z[j])) // 从右向左找第一个小于x的数  
                j--;   
            if(i < j)  
			{
                x[i] = x[j];  
				y[i] = y[j];
				z[i++] = z[j];
			}
            while(i < j && lt(x[i],y[i],z[i],xx,yy,zz)) // 从左向右找第一个大于等于x的数  
                i++;   
            if(i < j) 
			{
                x[j] = x[i];  
				y[j] = y[i];
				z[j--] = z[i];
			}
        }  
        x[i] = xx; 
		y[i] = yy;
		z[i] = zz;
		quickSort(x,y,z, l, i - 1); // 递归调用  
        quickSort(x,y,z, i + 1, r);  
    }  
} 
void GRDECL::Merge(double x[],double y[],double z[], int p, int q, int r)  //归并排序
{  
    int n1 = q-p+1;  
    int n2 = r-q;  
    double *Lx = new double[n1+1];  
    double *Rx = new double[n2+1];
	double *Ly = new double[n1+1];  
    double *Ry = new double[n2+1];
	double *Lz = new double[n1+1];  
    double *Rz = new double[n2+1];
    int i, j, k1;  
      
    for (i=0; i<n1; i++){  
        Lx[i] = x[p+i]; 
		Ly[i]=y[p+i];
		Lz[i]=z[p+i];
    }  
    for (j=0; j<n2; j++){  
        Rx[j] = x[q+j+1]; 
		Ry[j] = y[q+j+1];
		Rz[j] = z[q+j+1];
    }  
    Lx[n1] = 100000000;  
    Rx[n2] = 100000000;  
	Ly[n1] = 100000000;  
    Ry[n2] = 100000000; 
	Lz[n1] = 100000000;  
    Rz[n2] = 100000000; 
      for (i=0, j=0, k1=p; k1<=r; k1++)      
	  {  
        if (lt(Lx[i],Ly[i],Lz[i],Rx[j],Ry[j],Rz[j]))          
		{  
            x[k1] = Lx[i];
			y[k1] = Ly[i];
			z[k1] = Lz[i];
            i++;  
        }else{  
            x[k1] = Rx[j];
			y[k1] = Ry[j];
			z[k1] = Rz[j];  
            j++;  
        }  
    }  
  
    delete []Lx;  
    delete []Rx; 
	delete []Ly;  
    delete []Ry;
	delete []Lz;  
    delete []Rz;
}  
  
void GRDECL::MergeSort(double x[],double y[],double z[], int p, int r)  
{  
    if (p<r)  
    {  
        int q = (p+r)/2;  
        MergeSort(x,y,z, p, q);  
        MergeSort(x,y,z, q+1, r);  
        Merge(x,y,z, p, q, r);  
    }  
} 
*/
void GRDECL::getDianXuHao(int fangxiang,int xh,int jieGuo[][4],int fir)
{
	switch(fangxiang)
	{
	case 1:
	{
		jieGuo[xh][0]=flag[fir];
		jieGuo[xh][1]=flag[fir+2*m];
		jieGuo[xh][2]=flag[fir+2*m+m*2*n*2];
		jieGuo[xh][3]=flag[fir+4*m*n];
		break;
	}
	case 0:
		{
		jieGuo[xh][0]=flag[fir];
		jieGuo[xh][1]=flag[fir+1];
		jieGuo[xh][2]=flag[fir+1+m*2*n*2];
		jieGuo[xh][3]=flag[fir+4*m*n];
		break;
		}
	case 2:
		{
		jieGuo[xh][0]=flag[fir];
		jieGuo[xh][1]=flag[fir+1];
		jieGuo[xh][2]=flag[fir+1+m*2];
		jieGuo[xh][3]=flag[fir+2*m];
		break;
		}
	}
}
void GRDECL::getDianXuHao(int fangxiang,int xh,int jieGuoA[][2],int jieGuoB[][2],double jieGuoAZ[][2],double jieGuoBZ[][2],int fir)
{
	switch(fangxiang)
	{
	case 1:
		{
			jieGuoA[xh][0]=flag[fir];
			jieGuoAZ[xh][0]=z2[fir];
			jieGuoA[xh][1]=flag[fir+2*m];
			jieGuoAZ[xh][1]=z2[fir+2*m];
			jieGuoB[xh][0]=flag[fir+1];
			jieGuoBZ[xh][0]=z2[fir+1];
			jieGuoB[xh][1]=flag[fir+2*m+1];
			jieGuoBZ[xh][1]=z2[fir+2*m+1];
			break;
		}
	case 0:
		{
			jieGuoA[xh][0]=flag[fir];
			jieGuoAZ[xh][0]=z2[fir];
			jieGuoA[xh][1]=flag[fir+1];
			jieGuoAZ[xh][1]=z2[fir+1];
			jieGuoB[xh][0]=flag[fir+2*m];
			jieGuoBZ[xh][0]=z2[fir+2*m];
			jieGuoB[xh][1]=flag[fir+2*m+1];
			jieGuoBZ[xh][1]=z2[fir+2*m+1];
			break;
		}
	}
}
int faceYCount,faceXCount,faceZCount;
void GRDECL::setFaceXYZ()
{
	int f=0,bou=0,bb=-1,i,j,l;
	boolean b=true;
	//faceYCount=0;
	for(i=0;i<k*2+3;i++)//面向
	{
		if(i!=2&&i!=1&&i!=0&&i!=k*2+2&&i!=k*2+1)i++;
		for(j=0;j<n*2-1;j+=2)
		{
			for(l=1;l<m*2-1;l++)
			{
				getDianXuHao(1,f,faceY,i*m*2*n*2+j*m*2+l);
				setNormal(faceY,f,YNormal);
				//faceYCount++;
				if(bb==1)
				{
					if(isCoincide(faceY,f))
					{
						//f-=2;
						faceY[f][0]=-1;
						faceY[f][1]=-1;
						faceY[f][2]=-1;
						faceY[f][3]=-1;
					}
				}
				bb=-1*bb;f++;
				if(l==1)
				{
					getDianXuHao(1,bou,faceBoundaryY,i*m*2*n*2+j*m*2);
					setNormal(faceBoundaryY,bou,BYNormal);
				    bou++;
				    faceBoundaryY[bou][0]=flag[i*m*2*n*2+j*m*2+m*2-1];
				    faceBoundaryY[bou][3]=flag[i*m*2*n*2+j*m*2+m*4-1];
				    faceBoundaryY[bou][2]=flag[i*m*2*n*2+j*m*2+m*4-1+m*2*n*2];
				    faceBoundaryY[bou][1]=flag[i*m*2*n*2+j*m*2+m*2-1+m*2*n*2];
					setNormal(faceBoundaryY,bou,BYNormal);
				    /*getDianXuHao(1,bou,faceBoundaryY,i1*m*2*n*2+j1*m*2+m*2-1);*/
				    bou++;
				}
			}
		}
	}
	faceYCount=f;
	f=0;bou=0;
	for(i=0;i<k*2+3;i++)
	{
		if(i!=2&&i!=1&&i!=0&&i!=k*2+2&&i!=k*2+1)i++;
		for(j=0;j<m*2-1;j+=2)
		{
			for(l=1;l<n*2-1;l++)
			{
				
				getDianXuHao(0,f,faceX,i*m*2*n*2+l*m*2+j);
				setNormal(faceX,f,XNormal);
				//faceXCount++;
				if(bb==1)
				{
					if(isCoincide(faceX,f))
					{
						//f-=2;
						faceX[f][0]=-1;
						faceX[f][1]=-1;
						faceX[f][2]=-1;
						faceX[f][3]=-1;
					}
				}
				bb=-1*bb;
				f++;
				if(l==1)
				{
					faceBoundaryX[bou][0]=flag[i*m*2*n*2+j];
				    faceBoundaryX[bou][3]=flag[i*m*2*n*2+j+1];
				    faceBoundaryX[bou][2]=flag[i*m*2*n*2+j+4*m*n+1];
				    faceBoundaryX[bou][1]=flag[i*m*2*n*2+j+4*m*n];
					setNormal(faceBoundaryX,bou,BXNormal);
				//getDianXuHao(1,bou,faceBoundaryY,i1*m*2*n*2+j1*m*2+m*2-1);
				    bou++;
				    getDianXuHao(0,bou,faceBoundaryX,i*m*2*n*2+j+(2*n-1)*m*2);
					setNormal(faceBoundaryX,bou,BXNormal);
				    bou++;
				}
			}
		}
		
	}
	faceXCount=f;
	f=0;bou=0;
	for(l=0;l<n*2-1;l+=2)
	{
		
		for(j=0;j<m*2-1;j+=2)
		{
			for(i=3;i<k*2+1;i++)
			{
				//if(i!=2&&i!=1&&i!=0&&i!=k*2+2&&i!=k*2+1)i++;
				getDianXuHao(2,f,faceZ,i*m*2*n*2+l*m*2+j);
				setNormal(faceZ,f,BZNormal);
				f++;
				if(i==3)
				{
					getDianXuHao(2,bou,faceBoundaryZ,(i-1)*m*2*n*2+l*m*2+j);
					setNormal(faceBoundaryZ,bou,BZNormal);
				    bou++;
				    faceBoundaryZ[bou][0]=flag[(i-1)*m*2*n*2+l*m*2+j+(2*k-1)*m*2*n*2];
				    faceBoundaryZ[bou][3]=flag[(i-1)*m*2*n*2+l*m*2+j+1+(2*k-1)*m*2*n*2];
				    faceBoundaryZ[bou][2]=flag[(i-1)*m*2*n*2+l*m*2+j+2*m+1+(2*k-1)*m*2*n*2];
				    faceBoundaryZ[bou][1]=flag[(i-1)*m*2*n*2+l*m*2+j+2*m+(2*k-1)*m*2*n*2];
					setNormal(faceBoundaryZ,bou,BZNormal);
					//CalculateNormal(p1,p2,p3,BZNormal[i]);
				    bou++;
				}
			}
		}
		
	}
	faceZCount=f;

}
bool GRDECL::isCoincide(int face[][4],int f)
{
	bool b;
	if(face[f][0]==face[f-1][0])
		{
			if(face[f][1]==face[f-1][1])
			{
				if(face[f][2]==face[f-1][2])
				{
					if(face[f][3]==face[f-1][3])
					{b=false;}
					else {b=true;}
				}
				else {b=true;}
			}
			else {b=true;}
		}
		else {b=true;}
		return b;
}
void GRDECL::setgun()
{
	int t=0,i=0;
	YDCcount=0;
	for(i=0;i<2*n;i+=2)
	{
		for(int j=1;j<2*m-1;j+=2)
		{
			//int mm=(i/2*(m-1)+j/2+1);
			for(int l=0;l<2*k+4;l++)
			{

				//int mm=l*2*n*2*m+2*m*j+n*i;
				//int mn=l*2*n*2*m+2*m*j+n*i+2*m;
				//flag[mm];
				//flag[mn];
				/*gunYA[t][0]=flag[l*2*n*2*m+2*m*i+j];
				gunYAZ[t][0]=z2[l*2*n*2*m+2*m*i+j];
				gunYA[t][1]=flag[l*2*n*2*m+2*m*i+j+2*m];
				gunYAZ[t][1]=z2[l*2*n*2*m+2*m*i+j+2*m];
				gunYB[t][0]=flag[l*2*n*2*m+2*m*i+j+1];
				gunYBZ[t][0]=z2[l*2*n*2*m+2*m*i+j+1];
				gunYB[t][1]=flag[l*2*n*2*m+2*m*i+j+1+2*m];
				gunYBZ[t][1]=z2[l*2*n*2*m+2*m*i+j+1+2*m];*/
				getDianXuHao(1,t,gunYA,gunYB,gunYAZ,gunYBZ,l*2*n*2*m+2*m*i+j);
				if(gunYA[t][0]==gunYB[t][0]&&gunYA[t][1]==gunYB[t][1])
				{
					flagYg[t]=0;
				}else 
				{
					flagYg[t]=1;
					
 					gunYAZ[t][0]+=(i/2*(m-1)+j/2+1)*zra;
					gunYAZ[t][1]+=(i/2*(m-1)+j/2+1)*zra;
					gunYBZ[t][0]+=(i/2*(m-1)+j/2+1)*zra;
					gunYBZ[t][1]+=(i/2*(m-1)+j/2+1)*zra;
					gunYXB[t]=l*2*n*2*m+2*m*i+j;
					YDCcount++;
				}
				t++;
			}
		}
	}


    t=0;
	XDCcount=0;
	for(i=0;i<2*m;i+=2)
	{
		for(int j=1;j<2*n-1;j+=2)
		{
			//int mm=i/2*(n-1)+j/2+1;
			for(int l=0;l<2*k+4;l++)
			{
				//int mm=l*2*n*2*m+2*m*j+n*i;
				//int mn=l*2*n*2*m+2*m*j+n*i+2*m;
				//flag[mm];
				//flag[mn];
				/*gunXA[t][0]=flag[l*2*n*2*m+2*m*j+i];
				gunXAZ[t][0]=z2[l*2*n*2*m+2*m*j+i];
				gunXA[t][1]=flag[l*2*n*2*m+2*m*j+i+1];
				gunXAZ[t][1]=z2[l*2*n*2*m+2*m*j+i+1];
				gunXB[t][0]=flag[l*2*n*2*m+2*m*(j+1)+i];
				gunXBZ[t][0]=z2[l*2*n*2*m+2*m*(j+1)+i];
				gunXB[t][1]=flag[l*2*n*2*m+2*m*(j+1)+i+1];
				gunXBZ[t][1]=z2[l*2*n*2*m+2*m*(j+1)+i+1];*/
				getDianXuHao(0,t,gunXA,gunXB,gunXAZ,gunXBZ,l*2*n*2*m+2*m*j+i);
				if(gunXA[t][0]==gunXB[t][0]&&gunXA[t][1]==gunXB[t][1])
				{
					flagXg[t]=0;
				}else 
				{
					flagXg[t]=1;
 					gunXAZ[t][0]+=(i/2*(n-1)+j/2+1)*zra;
					gunXAZ[t][1]+=(i/2*(n-1)+j/2+1)*zra;
					gunXBZ[t][0]+=(i/2*(n-1)+j/2+1)*zra;
					gunXBZ[t][1]+=(i/2*(n-1)+j/2+1)*zra;
					gunXXB[t]=l*2*n*2*m+2*m*j+i;
					XDCcount++;
				}
				t++;
			}
		}
	}
	
//int mm=XDCcount;
    //setTempGun(YDCcount,flagYg,n*(m-1)*(2*k+4),gunYAZ,gunYBZ,Yxb);
	//setConnections(YDCcount,YC,YconCount);
	if(XDCcount!=0)
	{
	setTempGun(XDCcount,flagXg,(n-1)*m*(2*k+4),gunXAZ,gunXBZ,Xxb);
	setConnections(XDCcount,XC,XconCount);
	//int conCount,int C[][2],int xb[][2],int gunXB[][2]
	computeFaceGeometry(XDuanCengDianCount,0,XconCount,XC,Xxb,gunXXB,XCorners,XnumNodes);
	}/**/
	if(YDCcount!=0)
	{
	setTempGun(YDCcount,flagYg,(m-1)*n*(2*k+4),gunYAZ,gunYBZ,Yxb);
	setConnections(YDCcount,YC,YconCount);
	//int conCount,int C[][2],int xb[][2],int gunXB[][2]
	computeFaceGeometry(YDuanCengDianCount,1,YconCount,YC,Yxb,gunYXB,YCorners,YnumNodes);
	}
}


void GRDECL::setTempGun(int DCcount,int flagg[],int max,double gunAZ[][2],double gunBZ[][2],int xb[])
{
	int t=0;
	for(int i1=0;i1<DCcount;i1++)
	{
		//t=i1;
		while(flagg[t]!=1)
		{
			
			t++;
			if(t>=max)break;
		}
		tgunAZ[i1][0]=gunAZ[t][0];
		tgunAZ[i1][1]=gunAZ[t][1];
		tgunBZ[i1][0]=gunBZ[t][0];
		tgunBZ[i1][1]=gunBZ[t][1];
		xb[i1]=t;
		//xb[i1]=gunXB[t];
		t++;
		if(t>=max)break;
	}
	//int mm=max;
	/*ofstream fout("D://tgunYZ.txt");
	for(int i2=0;i2<DCcount;i2++){
		CString aa="",bb="",cc="",dd="";
		aa.Format("%f",tgunAZ[i2][0]);
		//bb.Format("%f",z2[xb[C[i2][0]]]);
		cc.Format("%f",tgunAZ[i2][1]);
		//dd.Format(" %f",tgunAZ[C[i2][0]][0]);
	fout<<aa<<" "<<" "<<cc<<" "<<endl;
	}*/
}

void GRDECL::setConnections(int DCcount,int C[][2],int &conCount)
{
	int j1=0,j2=0,tc=0,j,t=0;
	
	for(int i=0;i<DCcount-1;i++)
	{
		//int j;
		if(j1<j2)j=j1;
		else j=j2;
		while(tgunBZ[j][0]<tgunAZ[i+1][0]||tgunBZ[j][1]<tgunAZ[i+1][1])
		{
			//if(i==174)
				//int mm=i;
			if(doIntersect(tgunAZ[i],tgunAZ[i+1],tgunBZ[j],tgunBZ[j+1]))
			{
				C[tc][0]=i;
				C[tc][1]=j;
				tc++;
			}
			if(tgunBZ[j][0]<tgunAZ[i+1][0])j1=j;
			if(tgunBZ[j][1]<tgunAZ[i+1][1])j2=j;
			j++;
		}
	}
	conCount=tc;
	/*ofstream fout("D://cc2.txt");
	for(int i2=0;i2<conCount;i2++){
		CString aa="",bb="",cc="",dd="";
		aa.Format("%d",(C[i2][0]+1));
		//bb.Format("%f",z2[xb[C[i2][0]]]);
		cc.Format("%d",(C[i2][1]+1));
		dd.Format(" %f",tgunAZ[C[i2][0]][0]);
	fout<<aa<<" "<<" "<<cc<<" "<<dd<<endl;
	}*/
}

bool GRDECL::doIntersect(double za1[],double za2[],double zb1[],double zb2[])
{
	bool val;
	val=overlap(za1[0],za2[0],zb1[0],zb2[0])||overlap(za1[1],za2[1],zb1[1],zb2[1])||(za1[0]-zb1[0])*(za1[1]-zb1[1])<0||(za2[0]-zb2[0])*(za2[1]-zb2[1])<0;
	if(za1[0]-za2[0]==0&&za1[1]-za2[1]==0)val=false;
	if(zb1[0]-zb2[0]==0&&zb1[1]-zb2[1]==0)val=false;
	return val;
}

bool GRDECL::overlap(double za1,double za2,double zb1,double zb2)
{
	double max,min;
	if(za1<zb1)max=zb1;
	else max=za1;
	if(za2<zb2)min=za2;
	else min=zb2;
	if(max<min)return true;
	else return false;
}
	int pa[1040000][4];
	int pb[1040000][4];
	int pan;
	double za[1040000][4];
	double zb[1040000][4];
	int I[1040000][4];

    double jiaoDianX[1040000];
    double jiaoDianY[1040000];
    double jiaoDianZ[1040000];
    double uniqueJiaoDianX[1040000];
    double uniqueJiaoDianY[1040000];
    double uniqueJiaoDianZ[1040000];
	int uniqueCount;
	int PP[1040000][2];
	int QQ[1040000][2];
	int f[240000][4];
	int J[240000][8];

void GRDECL::computeFaceGeometry(int &n4,int fangxiang,int conCount,int C[][2],int xb[],int gunXB[],int Corners[],int numNodes[])
{

	int t=0,i=0;
	for(;i<conCount;i++)
	{
		if((C[i][0]+1)==(C[i][1]+1)&&(C[i][0]+1)%2==0)
		{}
		else
		{
			/*pa[t][0]=flag[gunXB[xb[C[i][0]]]];
			pa[t][1]=flag[gunXB[xb[C[i][0]]]+2*m];
			pa[t][2]=flag[gunXB[xb[C[i][0]]+1]];
			pa[t][3]=flag[gunXB[xb[C[i][0]]+1]+2*m];
			pb[t][0]=flag[gunXB[xb[C[i][1]]]+1];
			pb[t][1]=flag[gunXB[xb[C[i][1]]]+1+2*m];
			pb[t][2]=flag[gunXB[xb[C[i][1]]+1]+1];
			pb[t][3]=flag[gunXB[xb[C[i][1]]+1]+1+2*m];*/
			if(fangxiang==0)
			{
			pa[t][0]=flag[gunXB[xb[C[i][0]]]];
			pa[t][1]=flag[gunXB[xb[C[i][0]]]+1];
			pa[t][2]=flag[gunXB[xb[C[i][0]]+1]];
			pa[t][3]=flag[gunXB[xb[C[i][0]]+1]+1];
			pb[t][0]=flag[gunXB[xb[C[i][1]]]+2*m];
			pb[t][1]=flag[gunXB[xb[C[i][1]]]+1+2*m];
			pb[t][2]=flag[gunXB[xb[C[i][1]]+1]+2*m];
			pb[t][3]=flag[gunXB[xb[C[i][1]]+1]+1+2*m];
			}else
			{
			pa[t][0]=flag[gunXB[xb[C[i][0]]]];
			pa[t][1]=flag[gunXB[xb[C[i][0]]]+2*m];
			pa[t][2]=flag[gunXB[xb[C[i][0]]+1]];
			pa[t][3]=flag[gunXB[xb[C[i][0]]+1]+2*m];
			pb[t][0]=flag[gunXB[xb[C[i][1]]]+1];
			pb[t][1]=flag[gunXB[xb[C[i][1]]]+1+2*m];
			pb[t][2]=flag[gunXB[xb[C[i][1]]+1]+1];
			pb[t][3]=flag[gunXB[xb[C[i][1]]+1]+1+2*m];
			}
			t++;
		}
	}
	pan=t;
	for(int j=0;j<pan;j++)
	{
		za[j][0]=z3[pa[j][0]];
		za[j][1]=z3[pa[j][1]];
		za[j][2]=z3[pa[j][2]];
		za[j][3]=z3[pa[j][3]];
		zb[j][0]=z3[pb[j][0]];
		zb[j][1]=z3[pb[j][1]];
		zb[j][2]=z3[pb[j][2]];
		zb[j][3]=z3[pb[j][3]];
	}
	for(int l=0;l<pan;l++)
	{
		if(za[l][0]<zb[l][0])I[l][0]=pb[l][0];
		else I[l][0]=pa[l][0];
		if(za[l][1]<zb[l][1])I[l][1]=pb[l][1];
		else I[l][1]=pa[l][1];
		if(za[l][2]>zb[l][2])I[l][2]=pb[l][2];
		else I[l][2]=pa[l][2];
		if(za[l][3]>zb[l][3])I[l][3]=pb[l][3];
		else I[l][3]=pa[l][3];
	}
	/*ofstream fout("D://pa.txt");
	for(i=0;i<pan;i++){
		CString aa="",bb="",cc="",dd="",ee="",ff="",gg="",hh="";
		aa.Format("%d",pa[i][0]);
		bb.Format("%d",pa[i][1]);
		cc.Format("%d",pa[i][2]);
		dd.Format("%d",pa[i][3]);
		ee.Format("%d",pb[i][4]);
		ff.Format("%d",pb[i][5]);
		gg.Format("%d",pb[i][6]);
		hh.Format("%d",pb[i][7]);
	fout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<" "<<ee<<" "<<ff<<" "<<gg<<" "<<hh<<endl;
	}*/
    for(i=0;i<pan*4;i++)
	{
		if(i/pan==1||i/pan==3)
		{
		PP[i][0]=pa[i%pan][2];
		PP[i][1]=pa[i%pan][3];
		}else{
		PP[i][0]=pa[i%pan][0];
		PP[i][1]=pa[i%pan][1];
		}
		if(i/pan==0||i/pan==3)
		{
		QQ[i][0]=pb[i%pan][0];
		QQ[i][1]=pb[i%pan][1];
		}
		else
		{
		QQ[i][0]=pb[i%pan][2];
		QQ[i][1]=pb[i%pan][3];
		}
		
		
	}
	int nt=0;
	for(i=0;i<pan*4;i++)
	{
		if((z3[PP[i][0]]-z3[QQ[i][0]])*(z3[PP[i][1]]-z3[QQ[i][1]])<0)
		{
			intersection(PP[i],QQ[i],nt);
			nt++;
			//f[i%pan][i/pan]=n3+
		}
	}
 	
    unique(uniqueCount,nt,jiaoDianX,jiaoDianY,jiaoDianZ,uniqueJiaoDianX,uniqueJiaoDianY,uniqueJiaoDianZ,uniqueFlag,uniqueFlag2);
	nt=0;
	for(i=0;i<pan;i++)
	{

			f[i][0]=0;
			f[i][1]=0;
			f[i][2]=0;
			f[i][3]=0;
	}
	for(i=0;i<pan*4;i++)
	{
		if((z3[PP[i][0]]-z3[QQ[i][0]])*(z3[PP[i][1]]-z3[QQ[i][1]])<0)
		{
			//intersection(PP[i],QQ[i],nt);
			//nt++;
			f[i%pan][i/pan]=n3+uniqueFlag[nt];
			nt++;
		}else
		{
			//f[i%pan][i/pan]=-1;
		}
	}
	for(i=n3;i<n3+uniqueCount;i++)
	{
		x3[i]=uniqueJiaoDianX[i-n3];
		y3[i]=uniqueJiaoDianY[i-n3];
		z3[i]=uniqueJiaoDianZ[i-n3];
	}
	for(i=0;i<pan;i++)
	{
		J[i][0]=0;
		J[i][1]=0;
		J[i][2]=0;
		J[i][3]=0;
		J[i][4]=0;
		J[i][5]=0;
		J[i][6]=0;
		J[i][7]=0;
	}
	for(i=0;i<pan;i++)
	{
		if(pa[i][0]==I[i][2])I[i][0]=-1;
		if(pa[i][1]==I[i][4])I[i][1]=-1;
		J[i][0]=I[i][0];
		J[i][2]=I[i][1];
		J[i][4]=I[i][3];
		J[i][6]=I[i][2];
		J[i][1]=f[i][0];
		J[i][5]=f[i][1];
		if(f[i][2]!=0&&za[i][0]>zb[i][2])
		{
			J[i][0]=0;
			J[i][6]=0;
			J[i][7]=f[i][2];
		}
		if(f[i][2]!=0&&za[i][0]<=zb[i][2])
		{
			J[i][2]=0;
			J[i][4]=0;
			J[i][3]=f[i][2];
		}
		if(f[i][3]!=0&&zb[i][0]>za[i][2])
		{
			J[i][0]=0;
			J[i][6]=0;
			J[i][7]=f[i][4];
		}
		if(f[i][3]!=0&&zb[i][0]<=za[i][2])
		{
			J[i][2]=0;
			J[i][4]=0;
			J[i][3]=f[i][3];
		}
	}
    t=0;
	for(i=0;i<pan;i++)
	{
		int num=0;
		for(int j=0;j<8;j++)
		{
			if(J[i][j]!=0)
			{
				Corners[t]=J[i][j];
				t++;
				num++;
			}
		}
		numNodes[i]=num;
	}
	n4=t;
	//int mm=nt;
	/*ofstream fout("D://Corners.txt");
	for(i=0;i<t;i++){
		CString aa="",bb="",cc="",dd="",ee="",ff="",gg="",hh="";
		aa.Format("%d",Corners[i]);
		//aa.Format("%d",J[i][0]);
		//bb.Format("%d",J[i][1]);
		//cc.Format("%d",J[i][2]);
		//dd.Format("%d",J[i][3]);
		//ee.Format("%d",J[i][4]);
		//ff.Format("%d",J[i][5]);
		//gg.Format("%d",J[i][6]);
		//hh.Format("%d",J[i][7]);
	fout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<" "<<ee<<" "<<ff<<" "<<gg<<" "<<hh<<endl;
	}
	*/
}

void GRDECL::intersection(int la[],int lb[],int nt)
{
	double za[2],zb[2],xa[2],ya[2];
	za[0]=z3[la[0]];
	za[1]=z3[la[1]];
	xa[0]=x3[la[0]];
	xa[1]=x3[la[1]];
	ya[0]=y3[la[0]];
	ya[1]=y3[la[1]];
	zb[0]=z3[lb[0]];
	zb[1]=z3[lb[1]];
	double t=(zb[0]-za[0])/((za[1]-za[0])-(zb[1]-zb[0]));
    jiaoDianX[nt]=(xa[1]-xa[0])*t+xa[0];
	jiaoDianY[nt]=(ya[1]-ya[0])*t+ya[0];
	jiaoDianZ[nt]=(za[1]-za[0])*t+za[0];
	//return temp;
}

void CalculateNormal(Point3D point1, Point3D point2, Point3D point3, GLdouble *dNormal)//计算法向量
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
void GRDECL::setNormal(int face[][4],int a,double normal[][3])
{
	Point3D p1,p2,p3;
	double xratio = 200/(xmax-xmin);  
	double yratio = 200/(ymax-ymin);
	double zratio = 100/(zmax-zmin);
	p1.x=(x2[ flag2[ face[a][0]]]-centerX)*xratio;
	p1.y=(y2[ flag2[ face[a][0]]]-centerY)*yratio;
	p1.z=(z2[ flag2[ face[a][0]]]-centerZ)*zratio;
	p2.x=(x2[ flag2[ face[a][1]]]-centerX)*xratio;
	p2.y=(y2[ flag2[ face[a][1]]]-centerY)*yratio;
	p2.z=(z2[ flag2[ face[a][1]]]-centerZ)*zratio;
	p3.x=(x2[ flag2[ face[a][2]]]-centerX)*xratio;
	p3.y=(y2[ flag2[ face[a][2]]]-centerY)*yratio;
	p3.z=(z2[ flag2[ face[a][2]]]-centerZ)*zratio;
	CalculateNormal(p1,p2,p3,normal[a]);
}	
void GRDECL::setNormal()
{
	double zmax = zmaxDisplay;
	int i,j,t=0;
	for(i=0;i<XDuanCengDianCount;i++)//计算断层法向量
	{
		Point3D p[8];
		int temp;
		for(j=0;j<XnumNodes[i];j++)
		{
			temp=XCorners[t];
			if(XCorners[t]>=n3)
			{
				
				p[j].x=(x3[XCorners[t]]-centerX)*(200/(xmax-xmin));
				p[j].y=(y3[XCorners[t]]-centerY)*(200/(ymax-ymin));
				p[j].z=(z3[XCorners[t]]-centerZ)*(100/(zmax-zmin));
			}
			else{
				p[j].x=(x2[flag2[XCorners[t]]]-centerX)*(200/(xmax-xmin));
				p[j].y=(y2[flag2[XCorners[t]]]-centerY)*(200/(ymax-ymin));
				p[j].z=(z2[flag2[XCorners[t]]]-centerZ)*(100/(zmax-zmin));
			}
				
			t++;
		}
		if(flag2[temp]>=m*n*8&&flag2[temp]<=4*n*m*(k*2+2)){
		CalculateNormal(p[0],p[1],p[2],DCXNormal[i]);
		}
	}/**/
	t=0;
	for(i=0;i<YDuanCengDianCount;i++)
	{
		Point3D p[8];
		int temp;
		for(j=0;j<YnumNodes[i];j++)
		{
			temp=YCorners[t];
			if(YCorners[t]>=n3)
			{
				p[j].x=(x3[YCorners[t]]- centerX)*(200/( xmax- xmin));
				p[j].y=( y3[ YCorners[t]]- centerY)*(200/( ymax- ymin));
				p[j].z=( z3[ YCorners[t]]- centerZ)*(100/( zmax- zmin));
			}
			else
			{
				p[j].x=(x2[flag2[YCorners[t]]]-centerX)*(200/( xmax- xmin));
				p[j].y=(y2[flag2[YCorners[t]]]-centerY)*(200/( ymax- ymin));
				p[j].z=(z2[flag2[YCorners[t]]]-centerZ)*(100/(zmax-zmin));
			}
			t++;
		}
		if(flag2[temp]>=m*n*8&&flag2[temp]<=4*n*m*(k*2+2)){
		CalculateNormal(p[0],p[1],p[2],DCYNormal[i]);
		}
	}

	Point3D p1,p2,p3;
	double xratio = 200/(xmax-xmin);  
	double yratio = 200/(ymax-ymin);
	double zratio = 100/(zmax-zmin);
    for(i=0;i<(k+2)*n*(m-1)*2;i++)//计算内部层的法向量
	{

		if(faceY[i][0]!=-1)
		{
			//(xcorn1[i][j][l] - centerX) *xratio;//ratio;
			p1.x=(x2[ flag2[ faceY[i][0]]]-centerX)*xratio;
			p1.y=(y2[ flag2[ faceY[i][0]]]-centerY)*yratio;
			p1.z=(z2[ flag2[ faceY[i][0]]]-centerZ)*zratio;
		    p2.x=(x2[ flag2[ faceY[i][1]]]-centerX)*xratio;
			p2.y=(y2[ flag2[ faceY[i][1]]]-centerY)*yratio;
			p2.z=(z2[ flag2[ faceY[i][1]]]-centerZ)*zratio;
			p3.x=(x2[ flag2[ faceY[i][2]]]-centerX)*xratio;
			p3.y=(y2[ flag2[ faceY[i][2]]]-centerY)*yratio;
			p3.z=(z2[ flag2[ faceY[i][2]]]-centerZ)*zratio;
		    CalculateNormal(p1,p2,p3,YNormal[i]);	   
		}	
	}
	/*	ofstream fout("D://Normal.txt");
	for(i=0;i<faceYCount;i++){
		CString aa="",bb="",cc="",dd="",ee="",ff="",gg="",hh="";
		aa.Format("%f",YNormal[i][0]);
		//aa.Format("%d",J[i][0]);
		bb.Format("%f",YNormal[i][1]);
		cc.Format("%f",YNormal[i][2]);
		//dd.Format("%d",J[i][3]);
		//ee.Format("%d",J[i][4]);
		//ff.Format("%d",J[i][5]);
		//gg.Format("%d",J[i][6]);
		//hh.Format("%d",J[i][7]);
	fout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<" "<<ee<<" "<<ff<<" "<<gg<<" "<<hh<<endl;
	}
	*/
	for(i=0;i<2*m*(n-1)*(k+4);i++)
	{
		if( faceX[i][0]!=-1)
		{
			p1.x=(x2[ flag2[ faceX[i][0]]]-centerX)*xratio;
			p1.y=(y2[ flag2[ faceX[i][0]]]-centerY)*yratio;
			p1.z=(z2[ flag2[ faceX[i][0]]]-centerZ)*zratio;
		    p2.x=(x2[ flag2[ faceX[i][1]]]-centerX)*xratio;
			p2.y=(y2[ flag2[ faceX[i][1]]]-centerY)*yratio;
			p2.z=(z2[ flag2[ faceX[i][1]]]-centerZ)*zratio;
			p3.x=(x2[ flag2[ faceX[i][2]]]-centerX)*xratio;
			p3.y=(y2[ flag2[ faceX[i][2]]]-centerY)*yratio;
			p3.z=(z2[ flag2[ faceX[i][2]]]-centerZ)*zratio;
		    CalculateNormal(p1,p2,p3,XNormal[i]);
		 }
	}
	for(i=0;i<2*m*n*(k-1);i++)
	{
		p1.x=(x2[ flag2[ faceZ[i][0]]]-centerX)*xratio;
		p1.y=(y2[ flag2[ faceZ[i][0]]]-centerY)*yratio;
		p1.z=(z2[ flag2[ faceZ[i][0]]]-centerZ)*zratio;
		p2.x=(x2[ flag2[ faceZ[i][1]]]-centerX)*xratio;
		p2.y=(y2[ flag2[ faceZ[i][1]]]-centerY)*yratio;
		p2.z=(z2[ flag2[ faceZ[i][1]]]-centerZ)*zratio;
		p3.x=(x2[ flag2[ faceZ[i][2]]]-centerX)*xratio;
		p3.y=(y2[ flag2[ faceZ[i][2]]]-centerY)*yratio;
		p3.z=(z2[ flag2[ faceZ[i][2]]]-centerZ)*zratio;
		CalculateNormal(p1,p2,p3,ZNormal[i]);	
	}

	for(i=0;i<n*(k+2)*2;i++)//计算边界层的法向量
	{
		if(faceBoundaryY[i][0]!=-1)
		{
			p1.x=(x2[flag2[faceBoundaryY[i][0]]]-centerX)*xratio;
			p1.y=(y2[flag2[faceBoundaryY[i][0]]]-centerY)*yratio;
			p1.z=(z2[flag2[faceBoundaryY[i][0]]]-centerZ)*zratio;
		    p2.x=(x2[flag2[faceBoundaryY[i][1]]]-centerX)*xratio;
			p2.y=(y2[flag2[faceBoundaryY[i][1]]]-centerY)*yratio;
			p2.z=(z2[flag2[faceBoundaryY[i][1]]]-centerZ)*zratio;
			p3.x=(x2[flag2[faceBoundaryY[i][2]]]-centerX)*xratio;
			p3.y=(y2[flag2[faceBoundaryY[i][2]]]-centerY)*yratio;
			p3.z=(z2[flag2[faceBoundaryY[i][2]]]-centerZ)*zratio;
			CalculateNormal(p1,p2,p3,BYNormal[i]);			
		}
	}
	for(i=0;i<m*(k+2)*2;i++)
	{
		if(faceBoundaryX[i][0]!=-1)
		{
			p1.x=(x2[flag2[faceBoundaryX[i][0]]]-centerX)*xratio;
			p1.y=(y2[flag2[faceBoundaryX[i][0]]]-centerY)*yratio;
			p1.z=(z2[flag2[faceBoundaryX[i][0]]]-centerZ)*zratio;
		    p2.x=(x2[flag2[faceBoundaryX[i][1]]]-centerX)*xratio;
			p2.y=(y2[flag2[faceBoundaryX[i][1]]]-centerY)*yratio;
			p2.z=(z2[flag2[faceBoundaryX[i][1]]]-centerZ)*zratio;
			p3.x=(x2[flag2[faceBoundaryX[i][2]]]-centerX)*xratio;
			p3.y=(y2[flag2[faceBoundaryX[i][2]]]-centerY)*yratio;
			p3.z=(z2[flag2[faceBoundaryX[i][2]]]-centerZ)*zratio;
			CalculateNormal(p1,p2,p3,BXNormal[i]);
		}
	}
	for(i=0;i<m*n*2;i++)
	{
		p1.x=(x2[flag2[faceBoundaryZ[i][0]]]-centerX)*xratio;
		p1.y=(y2[flag2[faceBoundaryZ[i][0]]]-centerY)*yratio;
		p1.z=(z2[flag2[faceBoundaryZ[i][0]]]-centerZ)*zratio;
		p2.x=(x2[flag2[faceBoundaryZ[i][1]]]-centerX)*xratio;
		p2.y=(y2[flag2[faceBoundaryZ[i][1]]]-centerY)*yratio;
		p2.z=(z2[flag2[faceBoundaryZ[i][1]]]-centerZ)*zratio;
		p3.x=(x2[flag2[faceBoundaryZ[i][2]]]-centerX)*xratio;
		p3.y=(y2[flag2[faceBoundaryZ[i][2]]]-centerY)*yratio;
		p3.z=(z2[flag2[faceBoundaryZ[i][2]]]-centerZ)*zratio;
		CalculateNormal(p1,p2,p3,BZNormal[i]);
	}
}