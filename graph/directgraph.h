/* -------------------------------------------------------------------------
//  File Name   :   directgraph.h
//  Author      :   bigthumb
//  Create Time :   2015-3-30 15:41:43
//  Description :   十字链表作为有向图的存储结构
//
// -----------------------------------------------------------------------*/

#ifndef __DIRECTGRAPH_H__
#define __DIRECTGRAPH_H__

//-------------------------------------------------------------------------

class DirectGraph
{
public:
    DirectGraph();
    ~DirectGraph();
public:
    typedef char VexType;

    struct ArcBox
    {
        int tailvex;
        int headvex;
        ArcBox* headlink;
        ArcBox* taillink;
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
    };

    void create(VexType vexs[], int vexnum, Arc arcs[], int arcnum);

    typedef void (*visitor)(VexType data);
    void dfs(visitor v);
    void bfs(visitor v);
    int locateVex(VexType vex) const;
private:
    void _dfs(int i, bool visited[], int num, visitor v);
private:
    VexNode* m_vexs;
    int m_vexnum;
    int m_arcnum;
};

//--------------------------------------------------------------------------
#endif /* __DIRECTGRAPH_H__ */
