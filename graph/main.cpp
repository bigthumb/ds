/* -------------------------------------------------------------------------
//  File Name   :   main.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-30 16:20:25
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "directgraph.h"
#include "undirectgraph.h"

#include <cstdio>

//-------------------------------------------------------------------------

inline void myvisitor(DirectGraph::VexType data)
{
    ::printf("%c ", data);
}

int main(int argc, const char* argv[])
{
    {
        DirectGraph::VexType vexs[] = { '1', '2', '3', '4', '5', '6', '7', '8'};
        int vexnum = sizeof(vexs) / sizeof(DirectGraph::VexType);
        DirectGraph::Arc arcs[] = 
        {
            {'1', '2', 0}, {'2', '4', 0}, {'4', '8', 0}, {'2', '5', 0}, {'5', '8', 0}, 
            {'1', '3', 0}, {'3', '6', 0}, {'6', '7', 0}, {'7', '3', 0}
        };
        int arcnum = sizeof(arcs) / sizeof(DirectGraph::Arc);

        DirectGraph dg;
        dg.create(vexs, vexnum, arcs, arcnum);

        dg.dfs(myvisitor);
        ::printf("\n");

        dg.bfs(myvisitor);
        ::printf("\n");
    }

    ::printf("\n");

    {
        UndirectGraph::VexType vexs[] = { '1', '2', '3', '4', '5', '6', '7', '8'};
        int vexnum = sizeof(vexs) / sizeof(UndirectGraph::VexType);
        UndirectGraph::Edge edges[] = 
        {
            {'1', '2'}, {'1', '3'}, {'2', '4'}, {'2', '5'}, {'4', '8'}, {'5', '8'}, 
            {'3', '6'}, {'3', '7'}, {'6', '7'}
        };
        int edgenum = sizeof(edges) / sizeof(UndirectGraph::Edge);

        UndirectGraph udg;
        udg.create(vexs, vexnum, edges, edgenum);

        udg.dfs(myvisitor);
        ::printf("\n");

        udg.bfs(myvisitor);
        ::printf("\n");
    }

    return 0;
}

//--------------------------------------------------------------------------
