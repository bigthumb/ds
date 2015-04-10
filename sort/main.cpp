/* -------------------------------------------------------------------------
//  File Name   :   main.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-9 16:32:16
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "quicksort.h"
#include "heapsort.h"

//-------------------------------------------------------------------------

int main(int argc, const char* argv[])
{
    {
        // 快速排序
        int a[] = {10, 6, 2, 5, 3, 7, 8};
        int alen = sizeof(a) / sizeof(int);

        myqsort(a, 0, alen - 1);

        int b[] = {8, 7, 6, 5, 4, 3, 2, 1};
        int blen = sizeof(b) / sizeof(int);

        myqsort(b, 0, blen - 1);
    }

    {
        // 堆排序
        int a[] = {10, 6, 2, 5, 3, 7, 8};
        int alen = sizeof(a) / sizeof(int);

        heapSort(a, alen);

        int b[] = {8, 7, 6, 5, 4, 3, 2, 1};
        int blen = sizeof(b) / sizeof(int);

        heapSort(b, blen);


        // 利用大顶堆找出n个数中最大m个，要求m<=floor(n/2)，否则先利用小顶堆找出最小的n-m个，剩余的就是最大的
        // 利用小顶堆找出n个数中最小m个，要求m<=floor(n/2)，否则先利用大顶堆找出最大的n-m个，剩余的就是最小的
        int c[] = {6, 3, 9, 5, 2, 7, 8};
        int clen = sizeof(c) / sizeof(int);
        for(int i = clen / 2; i > 0; --i)
        {
            heapAdjust(c, i, clen);
        }

        // 同理利用大顶堆或小顶堆从10亿个数中找出1k个最小的或1k个最大的
    }

    return 0;
}

//--------------------------------------------------------------------------
