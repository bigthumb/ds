/* -------------------------------------------------------------------------
//  File Name   :   qsort.h
//  Author      :   bigthumb
//  Create Time :   2015-4-9 16:38:23
//  Description :   �Ż���Ŀ��������㷨
//
// -----------------------------------------------------------------------*/

#ifndef __QSORT_H__
#define __QSORT_H__

#include "global.h"

//-------------------------------------------------------------------------

// �Ż�
// 1. ͷ��β���м�����ȡ��
// 2. ���Ͳ���߲�������������ֱ�������򣬷����ʾ������ֹͣ����
// 3. �ȽϵͲ��͸߲���Ԫ�ظ�����ѡ�����С�������򣬽��͵���ջ�����

int partition(T a[], int low, int high, bool& lowSwap, bool& highSwap)
{
    int mid = (low + high) / 2;
    if(a[high] < a[mid])
        swap(a[mid], a[high]);
    if(a[high] < a[low])
        swap(a[low], a[high]);
    if(a[low] < a[mid])
        swap(a[low], a[mid]);

    int l = low;
    int h = high;
    T pivot = a[l];
    while(l < h)
    {
        for(; l < h && a[h] >= pivot; --h)
        {
            if(h < high && a[h] > a[h + 1])
            {
                swap(a[h], a[h + 1]);
                highSwap = true;
            }
        }

        a[l] = a[h];

        for(; l < h && a[l] <= pivot; ++l)
        {
            if(l > low && a[l - 1] > a[l])
            {
                swap(a[l - 1], a[l]);
                lowSwap = true;
            }
        }

        a[h] = a[l];
    }

    a[l] = pivot;

    return l;
}

void myqsort(T a[], int low, int high)
{
    if(low < high)
    {
        bool lowSwap = false;
        bool highSwap = false;
        int pivotloc = partition(a, low, high, lowSwap, highSwap);

        if(pivotloc - low <= high - pivotloc)
        {
            if(lowSwap)
                myqsort(a, low, pivotloc - 1);
            if(highSwap)
                myqsort(a, pivotloc + 1, high);
        }
        else
        {
            if(highSwap)
                myqsort(a, pivotloc + 1, high);
            if(lowSwap)
                myqsort(a, low, pivotloc - 1);
        }
    }
}

//--------------------------------------------------------------------------
#endif /* __QSORT_H__ */
