/* -------------------------------------------------------------------------
//  File Name   :   dlttree.cpp
//  Author      :   bigthumb
//  Create Time :   2015-4-7 10:28:31
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "dlttree.h"

//-------------------------------------------------------------------------

DLTTree::DLTTree()
    : m_tree(NULL)
{

}

DLTTree::~DLTTree()
{
    // 清理
}

void DLTTree::add(const KeyType& kt)
{
    uint32_t i = 0;
    DLTNode** p = &m_tree;
    _search(kt, p, i);

    // 结点已存在
    if(*p && EndSymbol == (*p)->symbol)
        return;

    // 构造剩余key元素的结点
    for(; i < kt.num; ++i)
    {
        DLTNode* node = new DLTNode;
        node->symbol = kt.key[i];
        node->firstchild = NULL;
        node->nextsubling = *p;

        *p = node;
        p = &node->firstchild;
    }

    DLTNode* endNode = new DLTNode;
    endNode->symbol = EndSymbol;
    endNode->firstchild = NULL;
    endNode->nextsubling = *p;
    
    *p = endNode;
}

bool DLTTree::search(const KeyType& kt)
{
    uint32_t i = 0;
    DLTNode** p = &m_tree;
    _search(kt, p, i);

    return (*p && EndSymbol == (*p)->symbol);
}

bool DLTTree::startWith(const KeyType& kt, visitor v)
{
    // 找出匹配kt前继结点
    uint32_t i = 0;
    DLTNode** p = &m_tree;
    _search(kt, p, i);

    if(i == kt.num)
    {
        ElemType key[keynum];
        ::memcpy(key, kt.key, kt.num);

        _priorSearch(*p, key, i, v);

        return true;
    }
    
    return false;
}

void DLTTree::_search(const KeyType& kt, DLTNode**& p, uint32_t& i)
{
    // 找出第一个不匹配的结点前继结点，以及不匹配key的元素索引

    while(*p && i < kt.num)
    {
        ElemType k = kt.key[i];

        // 兄弟结点自左向右升序，找出<=[key]的结点
        while(*p && k > (*p)->symbol)
        {
            p = &(*p)->nextsubling;
        }

        if(*p && k == (*p)->symbol)
        {
            p = &(*p)->firstchild;
            ++i;
        }
        else
        {
            break;
        }
    }
}

void DLTTree::_priorSearch(DLTNode* T, ElemType key[], uint32_t i, visitor v)
{
    // 参照二叉树的前序遍历

    if(!T)
        return;
    else if(EndSymbol == T->symbol)
    {
        v(key, i);
        _priorSearch(T->nextsubling, key, i, v);
    }
    else
    {
        key[i] = T->symbol;
        _priorSearch(T->firstchild, key, i + 1, v);
        _priorSearch(T->nextsubling, key, i, v);
    }

}

//--------------------------------------------------------------------------
