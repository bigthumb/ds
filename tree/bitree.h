/* -------------------------------------------------------------------------
//  File Name   :   bitree.h
//  Author      :   bigthumb
//  Create Time :   2015-3-25 09:28:42
//  Description :   二叉树基本知识
//
// -----------------------------------------------------------------------*/

#ifndef __BITREE_H__
#define __BITREE_H__

//-------------------------------------------------------------------------

typedef char BiElemType;

struct BiNode
{
    BiElemType data;
    BiNode* lchild;
    BiNode* rchild;
};

class BiTree
{
public:
    BiTree();
    ~BiTree();
public:
    void create(const char* preOrder);

    int leefCount() const;
    int depth() const;

    typedef void (*visitor)(BiElemType data);
    void preTraverse1(visitor v);
    void inTraverse1(visitor v);
    void postTraverse1(visitor v);

    void preTraverse2(visitor v);
    void inTraverse2(visitor v);
    void postTraverse2(visitor v);

    void layerTraverse(visitor v);
private:
    void _preOrderCreate(BiNode*& node, const char*& data);

    int _leefCount(BiNode* node) const;
    int _depth(BiNode* node) const;

    void _preTraverse1(BiNode* node, visitor v);
    void _inTraverse1(BiNode* node, visitor v);
    void _postTraverse1(BiNode* node, visitor v);
private:
    BiNode* m_tree;
};

//--------------------------------------------------------------------------
#endif /* __BITREE_H__ */
