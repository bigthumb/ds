/* -------------------------------------------------------------------------
//  File Name   :   main.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-9 16:32:16
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "qsort.h"

//-------------------------------------------------------------------------

int main(int argc, const char* argv[])
{
    {
        // ��������
        int a[] = {13, 9, 2, 12, 3, 16, 10};
        int alen = sizeof(a) / sizeof(int);

        myqsort(a, 0, alen - 1);

        int b[] = {2, 4, 5, 5, 10, 16, 20};
        int blen = sizeof(a) / sizeof(int);

        myqsort(b, 0, blen - 1);
    }

    return 0;
}

//--------------------------------------------------------------------------
