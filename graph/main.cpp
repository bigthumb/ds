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
        // 深度优先遍历和广度优先遍历
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
        // 拓扑排序
        // 无环
        DirectGraph::VexType vexs1[] = { '1', '2', '3', '4', '5', '6'};
        int vexnum1 = sizeof(vexs1) / sizeof(DirectGraph::VexType);
        DirectGraph::Arc arcs1[] = 
        {
            {'1', '2', 0}, {'1', '3', 0}, {'1', '4', 0}, {'4', '5', 0}, 
            {'6', '4', 0}, {'6', '5', 0}, {'3', '2', 0}, {'3', '5', 0}
        };
        int arcnum1 = sizeof(arcs1) / sizeof(DirectGraph::Arc);

        DirectGraph dg1;
        dg1.create(vexs1, vexnum1, arcs1, arcnum1);

        std::vector<DirectGraph::VexType> v1;
        bool ret1 = dg1.topologicSort(v1);


        // 有环
        DirectGraph::VexType vexs2[] = { '1', '2', '3', '4', '5', '6'};
        int vexnum2 = sizeof(vexs2) / sizeof(DirectGraph::VexType);
        DirectGraph::Arc arcs2[] = 
        {
            {'1', '2', 0}, {'1', '3', 0}, {'1', '4', 0}, {'4', '5', 0}, 
            {'6', '4', 0}, {'5', '6', 0}, {'3', '2', 0}, {'3', '5', 0}
        };
        int arcnum2 = sizeof(arcs2) / sizeof(DirectGraph::Arc);

        DirectGraph dg2;
        dg2.create(vexs2, vexnum2, arcs2, arcnum2);

        std::vector<DirectGraph::VexType> v2;
        bool ret2 = dg2.topologicSort(v2);
    }

    ::printf("\n");

    {
        // 找出关键弧，关键路径
        DirectGraph::VexType vexs[] = { '1', '2', '3', '4', '5', '6'};
        int vexnum = sizeof(vexs) / sizeof(DirectGraph::VexType);
        DirectGraph::Arc arcs[] = 
        {
            {'1', '2', 3}, {'1', '3', 2}, {'2', '5', 3}, {'2', '4', 2}, 
            {'3', '4', 4}, {'3', '6', 3}, {'5', '6', 1}, {'4', '6', 2}
        };
        int arcnum = sizeof(arcs) / sizeof(DirectGraph::Arc);

        DirectGraph dg;
        dg.create(vexs, vexnum, arcs, arcnum);

        std::vector<DirectGraph::Arc> v;
        bool ret = dg.criticalPath(v);
    }

    ::printf("\n");

    {
        // 最短路径
        DirectGraph::VexType vexs[] = { '0', '1', '2', '3', '4', '5'};
        int vexnum = sizeof(vexs) / sizeof(DirectGraph::VexType);
        DirectGraph::Arc arcs[] = 
        {
            {'0', '5', 100}, {'0', '4', 30}, {'0', '2', 10}, {'1', '2', 5}, 
            {'2', '3', 50}, {'3', '5', 10}, {'4', '5', 60}, {'4', '3', 20}
        };
        int arcnum = sizeof(arcs) / sizeof(DirectGraph::Arc);

        DirectGraph dg;
        dg.create(vexs, vexnum, arcs, arcnum);

        std::vector<DirectGraph::ShortestPath> D;
        dg.dijkstra('1', D);
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
