// PaiXu.h: interface for the PaiXu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAIXU_H__FB7B5161_8111_439C_88E6_C313E6316744__INCLUDED_)
#define AFX_PAIXU_H__FB7B5161_8111_439C_88E6_C313E6316744__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PaiXu  
{
public:
	PaiXu();
	virtual ~PaiXu();

	void swap(double x[],double y[],double z[], int low, int high );//交换
	bool lt(double x[],double y[],double z[],const int low, const int high );//比较大小
	void bubsort(  double x[],double y[],double z[], int n );//冒泡排序
	void quickSort(double x[],double y[],double z[], int l, int r);//快速排序
	bool lt(double x1,double y1,double z1,double x2,double y2,double z2 );//比较(x1,y1,z1)和(x2,y2,z2)大小

	void Merge(double x[],double y[],double z[], int p, int q, int r);//归并排序中的合并
	void MergeSort(double x[],double y[],double z[], int p, int r);//归并排序

};

#endif // !defined(AFX_PAIXU_H__FB7B5161_8111_439C_88E6_C313E6316744__INCLUDED_)
