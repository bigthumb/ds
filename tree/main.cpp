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
    // ���ʽ a+b*(c-d)-e/f
    // ���� -+a##*b##-c##d##/e##f##
    // ǰ�� -+a*b-cd/ef
    // ���� a+b*c-d-e/f
    // ���� abcd-*+ef/-
    // ��� -+/a*efb-cd
    // Ҷ���� 6
    // ��� 5

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
