/* -------------------------------------------------------------------------
//  File Name   :   directgraph.h
//  Author      :   bigthumb
//  Create Time :   2015-3-30 15:41:43
//  Description :   十字链表作为有向图的存储结构
//
// -----------------------------------------------------------------------*/

#ifndef __DIRECTGRAPH_H__
#define __DIRECTGRAPH_H__

#include <vector>

//-------------------------------------------------------------------------

// 硬编码顶点个数，方便调试
static const int num = 50;

class DirectGraph
{
public:
    DirectGraph();
    ~DirectGraph();
public:
    typedef char VexType;
    typedef int WeightType;

    struct ArcBox
    {
        int tailvex;
        int headvex;
        ArcBox* headlink;
        ArcBox* taillink;
        WeightType weight;
    };

    struct VexNode
    {
        VexType data;
        ArcBox* firstin;
        ArcBox* firstout;
    };

    struct Arc
    {
        VexType tail;
        VexType head;
        WeightType weight;
    };

    void create(VexType vexs[], int vexnum, Arc arcs[], int arcnum);

    typedef void (*visitor)(VexType data);
    void dfs(visitor v);
    void bfs(visitor v);
    int locateVex(VexType vex) const;

    bool topologicSort(std::vector<VexType>& v);
private:
    void _dfs(int i, bool visited[], int num, visitor v);
private:
    VexNode m_vexs[num];
    int m_vexnum;
    int m_arcnum;
};

//--------------------------------------------------------------------------
#endif /* __DIRECTGRAPH_H__ */
