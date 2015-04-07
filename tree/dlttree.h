/* -------------------------------------------------------------------------
//  File Name   :   dlttree.h
//  Author      :   bigthumb
//  Create Time :   2015-4-7 10:28:35
//  Description :   双链树作为键树的存储结构，兄弟结点自左向右升序
//
// -----------------------------------------------------------------------*/

#ifndef __DLTTREE_H__
#define __DLTTREE_H__

#include <vector>
#include <cstdint>
#include <cstring>

//-------------------------------------------------------------------------

// 硬编码KEY大小，方便调试
static const uint32_t keynum = 16;

typedef char ElemType;
struct KeyType
{
    ElemType key[keynum];
    uint32_t num;

    inline KeyType(const char* str)
        : num(::strlen(str))
    {
        ::strcpy(static_cast<char*>(key), str);
    }
};

static const ElemType EndSymbol = '\0';

// 简单起见，不保存key对应数据信息
struct DLTNode
{
    ElemType symbol;
    DLTNode* firstchild;
    DLTNode* nextsubling;
};

class DLTTree
{
public:
    DLTTree();
    ~DLTTree();
public:
    void add(const KeyType& kt);
    bool search(const KeyType& kt);

    typedef void (*visitor)(const ElemType key[], uint32_t num);
    bool startWith(const KeyType& kt, visitor v);
private:
    void _search(const KeyType& kt, DLTNode**& p, uint32_t& i);
    void _priorSearch(DLTNode* T, ElemType key[], uint32_t i, visitor v);
private:
    DLTNode* m_tree;
};

//--------------------------------------------------------------------------
#endif /* __DLTTREE_H__ */
