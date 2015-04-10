/* -------------------------------------------------------------------------
//  File Name   :   heapsort.h
//  Author      :   bigthumb
//  Create Time :   2015-4-10 10:20:17
//  Description :
//
// -----------------------------------------------------------------------*/

#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__

//-------------------------------------------------------------------------

// �Ƚ������ƹ���󶥶ѻ���С����
inline bool comp(const T& a, const T& b)
{
    // �󶥶�
    return (a < b);
    // С����
    //return (a > b);
}

// Ϊ�˴���ɶ��ԣ����������ȫ�����������ҽ�㣬����ΪԪ��������1��ʼ������������ĵ�Ԫ�أ�Ҫ�������ȼ�1
inline int R(int i) { return (i - 1); }

// ˢѡ�õ��󶥶ѻ�С����
void heapAdjust(T a[], int m, int n)
{
    T rc = a[R(m)];
    for(int j = 2 * m; j <= n; j *= 2)
    {
        if(j < n && comp(a[R(j)], a[R(j + 1)])) 
            j = j + 1;
        if(!comp(rc, a[R(j)]))
            break;

        a[R(m)] = a[R(j)];
        m = j;
    }

    a[R(m)] = rc;
}

void heapSort(T a[], int num)
{
    for(int i = num / 2; i > 0; --i)
    {
        heapAdjust(a, i, num);
    }

    for(int i = num; i > 1; --i)
    {
        swap(a[R(1)], a[R(i)]);
        heapAdjust(a, 1, i - 1);
    }
}

//--------------------------------------------------------------------------
#endif /* __HEAPSORT_H__ */
