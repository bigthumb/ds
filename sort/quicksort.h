/* -------------------------------------------------------------------------
//  File Name   :   qsort.h
//  Author      :   bigthumb
//  Create Time :   2015-4-9 16:38:23
//  Description :   优化后的快速排序算法
//
// -----------------------------------------------------------------------*/

#ifndef __QSORT_H__
#define __QSORT_H__

#include "global.h"

//-------------------------------------------------------------------------

// 优化
// 1. 头、尾、中间三者取中
// 2. 若低部或高部发生交换，则分别继续排序，否则表示已有序，停止排序
// 3. 比较低部和高部的元素个数，选择个数小的先排序，降低调用栈的深度

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
