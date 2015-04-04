/* -------------------------------------------------------------------------
//  File Name   :   bitree.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-25 10:00:23
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "BiTree.h"

#include <stack>
#include <queue>

//-------------------------------------------------------------------------

BiTree::BiTree() : m_tree(NULL)
{

}

BiTree::~BiTree()
{
    // Ïú»Ù
}

void BiTree::create(const char* preOrder)
{
    _preOrderCreate(m_tree, preOrder);
}

int BiTree::leefCount() const
{
    return _leefCount(m_tree);
}

int BiTree::depth() const
{
    return _depth(m_tree);
}

void BiTree::preTraverse1(visitor v)
{
    _preTraverse1(m_tree, v);
}

void BiTree::inTraverse1(visitor v)
{
    _inTraverse1(m_tree, v);
}

void BiTree::postTraverse1(visitor v)
{
    _postTraverse1(m_tree, v);
}

void BiTree::preTraverse2(visitor v)
{
    std::stack<BiNode*> s;
    BiNode* p = m_tree;
    while(p || !s.empty())
    {
        if(p)
        {
            v(p->data);
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }
}

void BiTree::inTraverse2(visitor v)
{
    std::stack<BiNode*> s;
    BiNode* p = m_tree;
    while(p || !s.empty())
    {
        if(p)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            v(p->data);

            p = p->rchild;
        }
    }
}

void BiTree::postTraverse2(visitor v)
{
    struct FlagBiNode
    {
        BiNode* node;
        bool flag;

        FlagBiNode(BiNode* n) : node(n), flag(false) {}
    };

    std::stack<FlagBiNode> s;
    BiNode* p = m_tree;
    while(p || !s.empty())
    {
        if(p)
        {
            s.push(FlagBiNode(p));
            p = p->lchild;
        }
        else
        {
            FlagBiNode fp = s.top();
            s.pop();
            if(fp.flag)
                v(fp.node->data);
            else
            {
                fp.flag = true;
                s.push(fp);
                p = fp.node->rchild;
            }
        }
    }
}

void BiTree::layerTraverse(visitor v)
{
    std::queue<BiNode*> q;
    q.push(m_tree);
    while(!q.empty())
    {
        BiNode* p = q.front();
        q.pop();

        v(p->data);
        if(p->lchild)
            q.push(p->lchild);
        if(p->rchild)
            q.push(p->rchild);
    }
}

void BiTree::_preOrderCreate(BiNode*& node, const char*& data)
{
    char ch = *data++;
    if('#' == ch || '\0' == ch) 
        node = NULL;
    else
    {
        node = new BiNode();
        node->data = ch;

        _preOrderCreate(node->lchild, data);
        _preOrderCreate(node->rchild, data);
    }
}

int BiTree::_leefCount(BiNode* node) const
{
    if(!node)
        return 0;
    else if(!node->lchild && !node->rchild)
        return 1;
    else
        return _leefCount(node->lchild) + _leefCount(node->rchild);
}

int BiTree::_depth(BiNode* node) const
{
    if(!node)
        return 0;
    else
    {
        int ldepth = _depth(node->lchild);
        int rdepth = _depth(node->rchild);

        return (ldepth > rdepth ? ldepth : rdepth) + 1;
    }
}

void BiTree::_preTraverse1(BiNode* node, visitor v)
{
    if(!node)
        return;

    v(node->data);
    _preTraverse1(node->lchild, v);
    _preTraverse1(node->rchild, v);
}

void BiTree::_inTraverse1(BiNode* node, visitor v)
{
    if(!node)
        return;

    _inTraverse1(node->lchild, v);
    v(node->data);
    _inTraverse1(node->rchild, v);
}

void BiTree::_postTraverse1(BiNode* node, visitor v)
{
    if(!node)
        return;

    _postTraverse1(node->lchild, v);
    _postTraverse1(node->rchild, v);
    v(node->data);
}


//--------------------------------------------------------------------------
