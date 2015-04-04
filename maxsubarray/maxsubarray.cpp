/* -------------------------------------------------------------------------
//  File Name   :   maxsubarray.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-23 10:24:21
//  Description :  
//
// -----------------------------------------------------------------------*/

#include <cstdio>

//-------------------------------------------------------------------------

struct Zone
{
    int m_value;
    int m_from;
    int m_to;
};

Zone maxSubArray(int arr[], int length)
{
    Zone curZone = {0};
    Zone maxZone = {0};
    maxZone.m_value = arr[0];
    for(int i = 0; i < length; ++i)
    {
        if(curZone.m_value >= 0)
        {
            curZone.m_value += arr[i];
            curZone.m_to = i;
        }
        else
        {
            curZone.m_value = arr[i];
            curZone.m_from = i;
            curZone.m_to = i;
        }

        if(curZone.m_value >= maxZone.m_value)
            maxZone = curZone;
    }

    return maxZone;
}

int main(int argc, const char* argv[])
{
    int arr[] = {1, -2, 3, 10, -4, 7, 2, -5};
    Zone maxZone = maxSubArray(arr, sizeof(arr) / sizeof(int));
    ::printf("%d, %d->%d\n", maxZone.m_value, maxZone.m_from, maxZone.m_to);

    return 0;
}

//--------------------------------------------------------------------------
