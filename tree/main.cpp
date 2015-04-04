/* -------------------------------------------------------------------------
//  File Name   :   main.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-25 21:03:19
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "bitree.h"

#include <cstdio>

//-------------------------------------------------------------------------

inline void myvisitor(BiElemType data)
{
    ::printf("%c ", data);
}

int main(int argc, const char* argv[])
{
    // 表达式 a+b*(c-d)-e/f
    // 创建 -+a##*b##-c##d##/e##f##
    // 前序 -+a*b-cd/ef
    // 中序 a+b*c-d-e/f
    // 后序 abcd-*+ef/-
    // 层次 -+/a*efb-cd
    // 叶子数 6
    // 深度 5

    BiTree tree;
    tree.create("-+a##*b##-c##d##/e##f##");

    tree.preTraverse1(myvisitor);
    ::printf("\n");
    tree.preTraverse2(myvisitor);
    ::printf("\n");

    tree.inTraverse1(myvisitor);
    ::printf("\n");
    tree.inTraverse2(myvisitor);
    ::printf("\n");

    tree.postTraverse1(myvisitor);
    ::printf("\n");
    tree.postTraverse2(myvisitor);
    ::printf("\n");

    tree.layerTraverse(myvisitor);
    ::printf("\n");

    ::printf("%d\n", tree.leefCount());
    ::printf("%d\n", tree.depth());

    return 0;
}

//--------------------------------------------------------------------------
