/* -------------------------------------------------------------------------
//  File Name   :   main.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-25 21:03:19
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "bitree.h"
#include "dlttree.h"

#include <cstdio>

//-------------------------------------------------------------------------

inline void bitvisitor(BiElemType data)
{
    ::printf("%c ", data);
}

void dltvisitor(const ElemType key[], uint32_t num)
{
    for(int i = 0; i < num; ++i)
    {
        ::printf("%c", key[i]);
    }

    ::printf("\n");
}

int main(int argc, const char* argv[])
{
    {
        // 二叉树

        // 表达式 a+b*(c-d)-e/f
        // 创建 -+a##*b##-c##d##/e##f##
        // 前序 -+a*b-cd/ef
        // 中序 a+b*c-d-e/f
        // 后序 abcd-*+ef/-
        // 层次 -+/a*efb-cd
        // 叶子数 6
        // 深度 5

        BiTree bit;
        bit.create("-+a##*b##-c##d##/e##f##");

        bit.preTraverse1(bitvisitor);
        ::printf("\n");
        bit.preTraverse2(bitvisitor);
        ::printf("\n");

        bit.inTraverse1(bitvisitor);
        ::printf("\n");
        bit.inTraverse2(bitvisitor);
        ::printf("\n");

        bit.postTraverse1(bitvisitor);
        ::printf("\n");
        bit.postTraverse2(bitvisitor);
        ::printf("\n");

        bit.layerTraverse(bitvisitor);
        ::printf("\n");

        ::printf("%d\n", bit.leefCount());
        ::printf("%d\n", bit.depth());
    }

    {
        // 键树

        KeyType kt1("CHANG");
        KeyType kt2("CAI");
        KeyType kt3("CAO");
        KeyType kt4("CHA");
        KeyType kt5("CHAO");
        KeyType kt6("CHEN");

        KeyType kt7("LAN");

        DLTTree dlt;
        dlt.add(kt1);
        dlt.add(kt2);
        dlt.add(kt3);
        dlt.add(kt4);
        dlt.add(kt5);
        dlt.add(kt6);
        dlt.add(kt7);

        bool ret = dlt.search(kt1);
        ret = dlt.search(kt2);
        ret = dlt.search(kt3);
        ret = dlt.search(kt4);
        ret = dlt.search(kt5);
        ret = dlt.search(kt6);
        ret = dlt.search(kt7);

        ret = dlt.search(KeyType("NONE"));

        dlt.startWith(KeyType("C"), dltvisitor);
        ::printf("\n");

        dlt.startWith(KeyType("CH"), dltvisitor);
        ::printf("\n");

        dlt.startWith(KeyType("CHA"), dltvisitor);
        ::printf("\n");
    }

    return 0;
}

//--------------------------------------------------------------------------
