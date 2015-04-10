/* -------------------------------------------------------------------------
//  File Name   :   global.h
//  Author      :   bigthumb
//  Create Time :   2015-4-10 10:20:12
//  Description :
//
// -----------------------------------------------------------------------*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <assert.h>

//-------------------------------------------------------------------------

typedef int T;

inline void swap(int& a, int& b)
{
    assert(&a != &b);
    a ^= b;
    b ^= a;
    a ^= b;
}

inline bool less(const T& a, const T& b)
{
    return (a < b);
}

//--------------------------------------------------------------------------
#endif /* __GLOBAL_H__ */
