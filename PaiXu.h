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

	void swap(double x[],double y[],double z[], int low, int high );//����
	bool lt(double x[],double y[],double z[],const int low, const int high );//�Ƚϴ�С
	void bubsort(  double x[],double y[],double z[], int n );//ð������
	void quickSort(double x[],double y[],double z[], int l, int r);//��������
	bool lt(double x1,double y1,double z1,double x2,double y2,double z2 );//�Ƚ�(x1,y1,z1)��(x2,y2,z2)��С

	void Merge(double x[],double y[],double z[], int p, int q, int r);//�鲢�����еĺϲ�
	void MergeSort(double x[],double y[],double z[], int p, int r);//�鲢����

};

#endif // !defined(AFX_PAIXU_H__FB7B5161_8111_439C_88E6_C313E6316744__INCLUDED_)
