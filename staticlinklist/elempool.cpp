/* -------------------------------------------------------------------------
//  File Name   :   elempool.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-21 13:14:31
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "elempool.h"

#include <assert.h>

//-------------------------------------------------------------------------

ElemPool::ElemPool(int capacity)
    : m_c(capacity)
    , m_list(new Item[m_c])
{
    assert(m_c > 0);
    for(int i = 0; i < m_c - 1; ++i)
    {
        m_list[i].next = i + 1;
    }
    m_list[m_c - 1].next = 0;
}

ElemPool::~ElemPool()
{
    delete[] m_list;
}

int ElemPool::capacity() const
{
    return m_c;
}

int ElemPool::malloc()
{
    int i = m_list[0].next;
    if(m_list[0].next)
        m_list[0].next = m_list[i].next;

    return i;
}

void ElemPool::free(int i)
{
    if(i > 0 && i < m_c)
    {
        m_list[i].next = m_list[0].next;
        m_list[0].next = i;
    }
}

ElemType& ElemPool::item(int i)
{
    return m_list[i].data;
}

//--------------------------------------------------------------------------
