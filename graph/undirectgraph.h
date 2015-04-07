/* -------------------------------------------------------------------------
//  File Name   :   undirectgraph.h
//  Author      :   bigthumb
//  Create Time :   2015-3-30 15:41:11
//  Description :   邻接多重表作为存储结构
//
// -----------------------------------------------------------------------*/

#ifndef __UNDIRECTGRAPH_H__
#define __UNDIRECTGRAPH_H__

//-------------------------------------------------------------------------

class UndirectGraph
{
public:
    UndirectGraph(void);
    ~UndirectGraph(void);
public:
    typedef char VexType;

    struct EdgeBox
    {
        int ivex;
        EdgeBox* ilink;
        int jvex;
        EdgeBox* jlink;
    };

    struct VexNode
    {
        VexType data;
        EdgeBox* firstedge;
    };

    struct Edge
    {
        VexType i;
        VexType j;
    };

    void create(const VexType vexs[], int vexnum, const Edge edges[], int edgenum);

    typedef void (*visitor)(VexType data);
    void dfs(visitor v);
    void bfs(visitor v);
    int locateVex(VexType vex) const;
private:
    void _dfs(int i, bool visited[], int num, visitor v);
private:
    VexNode m_vexs[20];
    int m_vexnum;
    int m_edgenum;
};

//--------------------------------------------------------------------------
#endif /* __UNDIRECTGRAPH_H__ */
