/* -------------------------------------------------------------------------
//  File Name   :   directgraph.cpp
//  Author      :   bigthumb
//  Create Time :   2015-3-30 15:41:45
//  Description :  
//
// -----------------------------------------------------------------------*/

#include "directgraph.h"

#include <queue>
#include <stack>

//-------------------------------------------------------------------------

DirectGraph::DirectGraph()
    //: m_vexs(NULL)
    : m_vexnum(0)
    , m_arcnum(0)
{

}

DirectGraph::~DirectGraph()
{
    // «Â¿Ì
}

void DirectGraph::create(VexType vexs[], int vexnum, Arc arcs[], int arcnum)
{
    //m_vexs = new VexNode[vexnum];
    m_vexnum = vexnum;
    m_arcnum = arcnum;
    for(int i = 0; i < vexnum; ++i)
    {
        m_vexs[i].data = vexs[i];
        m_vexs[i].firstin = NULL;
        m_vexs[i].firstout = NULL;
    }

    for(int i = 0; i < arcnum; ++i)
    {
        int t = locateVex(arcs[i].tail);
        int h = locateVex(arcs[i].head);

        ArcBox* p = new ArcBox();
        p->tailvex = t;
        p->headvex = h;
        p->headlink = m_vexs[h].firstin;
        p->taillink = m_vexs[t].firstout;
        m_vexs[h].firstin = p;
        m_vexs[t].firstout = p;
        p->weight = arcs[i].weight;
    }
}

void DirectGraph::dfs(visitor v)
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

void DirectGraph::bfs(visitor v)
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
            for(ArcBox* p = m_vexs[t].firstout; p; p = p->taillink)
            {
                int h = p->headvex;
                if(visited[h])
                    continue;

                visited[h] = true;
                v(m_vexs[h].data);
                q.push(h);
            }
        }
    }

    delete[] visited;
}

int DirectGraph::locateVex(VexType vex) const
{
    for(int i = 0; i < m_vexnum; ++i)
    {
        if(m_vexs[i].data == vex)
            return i;
    }

    return -1;
}

bool DirectGraph::topologicSort(std::vector<VexType>& v)
{
    std::stack<int> s;
    int indegree[num];
    for(int i = 0; i < m_vexnum; ++i)
    {
        indegree[i] = 0;
        for(ArcBox* p = m_vexs[i].firstin; p; p = p->headlink)
        {
            ++indegree[i];
        }

        if(0 == indegree[i])
            s.push(i);
    }

    while(!s.empty())
    {
        int j = s.top();
        s.pop();
        v.push_back(m_vexs[j].data);

        for(ArcBox* p = m_vexs[j].firstout; p; p = p->taillink)
        {
            int k = p->headvex;
            if(0 == --indegree[k])
                s.push(k);
        }
    }

    return (v.size() == m_vexnum);
}

void DirectGraph::_dfs(int i, bool visited[], int num, visitor v)
{
    visited[i] = true;
    v(m_vexs[i].data);
    for(ArcBox* p = m_vexs[i].firstout; p; p = p->taillink)
    {
        if(!visited[p->headvex])
            _dfs(p->headvex, visited, num, v);
    }
}

//--------------------------------------------------------------------------
