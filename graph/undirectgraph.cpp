/* -------------------------------------------------------------------------
//  File Name   :   undirectgraph.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-30 15:41:27
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "undirectgraph.h"

#include <queue>

//-------------------------------------------------------------------------

UndirectGraph::UndirectGraph(void)
    : m_vexnum(0)
    , m_edgenum(0)
{

}

UndirectGraph::~UndirectGraph(void)
{
    // 清理工作
}

void UndirectGraph::create(const VexType vexs[], int vexnum, const Edge edges[], int edgenum)
{
    //m_vexs = new VexNode[vexnum];
    m_vexnum = vexnum;
    m_edgenum = edgenum;
    for(int i = 0; i < vexnum; ++i)
    {
        m_vexs[i].data = vexs[i];
        m_vexs[i].firstedge = NULL;
    }

    for(int i = 0; i < edgenum; ++i)
    {
        int ivex = locateVex(edges[i].i);
        int jvex = locateVex(edges[i].j);

        EdgeBox* p = new EdgeBox();
        p->ivex = ivex;
        p->ilink = m_vexs[ivex].firstedge;
        p->jvex = jvex;
        p->jlink = m_vexs[jvex].firstedge;
        m_vexs[ivex].firstedge = p;
        m_vexs[jvex].firstedge = p;
    }
}

void UndirectGraph::dfs(visitor v)
{
    bool* visited = new bool[m_vexnum];
    for(int i = 0; i < m_vexnum; ++i)
    {
        visited[i] = false;
    }

    for(int i = 0; i < m_vexnum; ++i)
    {
        if(!visited[i])
            _dfs(i, visited, m_vexnum, v);
    }

    delete[] visited;
}

void UndirectGraph::bfs(visitor v)
{
    bool* visited = new bool[m_vexnum];
    for(int i = 0; i < m_vexnum; ++i)
    {
        visited[i] = false;
    }

    std::queue<int> q;
    for(int i = 0; i < m_vexnum; ++i)
    {
        if(visited[i])
            continue;

        visited[i] = true;
        v(m_vexs[i].data);
        q.push(i);
        while(!q.empty())
        {
            int t = q.front();
            q.pop();
            for(EdgeBox* p = m_vexs[t].firstedge; p; p = p->ilink)
            {
                int jvex = p->jvex;
                if(visited[jvex])
                    continue;

                visited[jvex] = true;
                v(m_vexs[jvex].data);
                q.push(jvex);
            }
        }
    }

    delete[] visited;
}

int UndirectGraph::locateVex(VexType vex) const
{
    for(int i = 0; i < m_vexnum; ++i)
    {
        if(m_vexs[i].data == vex)
            return i;
    }

    return -1;
}

void UndirectGraph::_dfs(int i, bool visited[], int num, visitor v)
{
    visited[i] = true;
    v(m_vexs[i].data);
    for(EdgeBox* p = m_vexs[i].firstedge; p; p = p->ilink)
    {
        if(!visited[p->jvex])
            _dfs(p->jvex, visited, num, v);
    }
}

//--------------------------------------------------------------------------
