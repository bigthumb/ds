/* -------------------------------------------------------------------------
//  File Name   :   KMP.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-28 13:22:56
//  Description :  
//
// -----------------------------------------------------------------------*/

#include <assert.h>
#include <cstring>

//-------------------------------------------------------------------------

void initNext(const char* str, int strLen, int next[], int nextLen)
{
    assert(strLen == nextLen);

    next[0] = -1;
    int i = 0;
    int j = -1;
    while(i < strLen - 1)
    {
        if(-1 == j || str[i] == str[j])
        {
            ++i;
            ++j;
            if(str[i] != str[j])
                next[i] = j;
            else
                next[i] = next[j];
        }
        else
        {
            j = next[j];
        }
    }
}

int KMP(const char* s, int sLen, const char* p, int pLen, int pos)
{
    int* next = new int[pLen];
    initNext(p, pLen, next, pLen);

    int i = pos;
    int j = 0;
    while(i < sLen && j < pLen)
    {
        if(-1 == j || s[i] == p[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }

    if(j >= pLen)
        return (i - pLen);
    else
        return -1;
}

int main(int argc, const char* argv[])
{
    const char* s = "d2c2d23bc";
    int sLen = ::strlen(s);
    const char* p = "2d23";
    int pLen = ::strlen(p);
    int pos = KMP(s, sLen, p, pLen, 0);

    return 0;
}

//--------------------------------------------------------------------------
