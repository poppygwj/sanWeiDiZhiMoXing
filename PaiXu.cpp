// PaiXu.cpp: implementation of the PaiXu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawObject.h"
#include "PaiXu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PaiXu::PaiXu()
{

}

PaiXu::~PaiXu()
{

}
void PaiXu::swap(double x[],double y[],double z[], int low, int high )
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
}

/*
小于函数
*/

bool PaiXu::lt(double x[],double y[],double z[],const int low, const int high )
{
    /*if(x[low]>x[high]||y[low]>y[high]||z[low]>z[high])
	{
               return false;
			}else 
        return true;*/
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
bool PaiXu::lt(double x1,double y1,double z1,double x2,double y2,double z2 )
{
    /*if(x[low]>x[high]||y[low]>y[high]||z[low]>z[high])
	{
               return false;
			}else 
        return true;*/
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
	
}
/*
冒泡排序（稳定）
原理：第一次的内部for循环从记录数组的底部比较到顶部，比较相邻的值。
如果低序号的值比高序号的值大，则二者交换顺序
代价是n2
*/

void PaiXu::bubsort( double x[],double y[],double z[], int n )
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
void PaiXu::quickSort(double x[],double y[],double z[], int l, int r)  
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
void PaiXu::Merge(double x[],double y[],double z[], int p, int q, int r)  //归并排序
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
  
void PaiXu::MergeSort(double x[],double y[],double z[], int p, int r)  
{  
    if (p<r)  
    {  
        int q = (p+r)/2;  
        MergeSort(x,y,z, p, q);  
        MergeSort(x,y,z, q+1, r);  
        Merge(x,y,z, p, q, r);  
    }  
} 

