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
#include <limits>

//-------------------------------------------------------------------------

DirectGraph::DirectGraph()
    //: m_vexs(NULL)
    : m_vexnum(0)
    , m_arcnum(0)
{

}

DirectGraph::~DirectGraph()
{
    // 清理
}

void DirectGraph::create(const VexType vexs[], int vexnum, const Arc arcs[], int arcnum)
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

bool DirectGraph::criticalPath(std::vector<Arc>& v)
{
    // 拓扑排序求出顶点最早开始时间ve
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

    // 全部初始化为0
    WeightType ve[num] = {0};

    std::vector<int> topoList;
    while(!s.empty())
    {
        int j = s.top();
        s.pop();
        topoList.push_back(j);

        for(ArcBox* p = m_vexs[j].firstout; p; p = p->taillink)
        {
            int k = p->headvex;
            if(0 == --indegree[k])
                s.push(k);
            
            if(ve[j] + p->weight > ve[k])
                ve[k] = ve[j] + p->weight;
        }
    }

    if(topoList.size() != m_vexnum)
        return false;

    // 全部初始化为ve[m_vexnum - 1]
    WeightType vl[num];
    for(int i = 0; i < m_vexnum; ++i)
    {
        vl[i] = ve[m_vexnum - 1];
    }

    // 逆拓扑排序求出顶点最迟开始时间vl
    for(int i = m_vexnum - 1; i >= 0; --i)
    {
        int j = topoList[i];
        for(ArcBox* p = m_vexs[j].firstout; p; p = p->taillink)
        {
            int k = p->headvex;
            if(vl[k] - p->weight < vl[j])
                vl[j] = vl[k] - p->weight;
        }
    }

    // 求出弧的最早开始时间e(i)=ve(i)，最迟开始时间l(i)=vl(j)-kut，若e(i)=l(i)，则该弧是关键弧
    for(int j = 0; j < m_vexnum; ++j)
    {
        for(ArcBox* p = m_vexs[j].firstout; p; p = p->taillink)
        {
            int k = p->headvex;
            WeightType e = ve[j];
            WeightType l = vl[k] - p->weight;
            if(e == l)
            {
                Arc arc = {m_vexs[j].data, m_vexs[k].data, p->weight};
                v.push_back(arc);
            }
        }
    }

    return true;
}

DirectGraph::WeightType DirectGraph::infinity()
{
    return std::numeric_limits<WeightType>::max();
}

void DirectGraph::dijkstra(VexType s, std::vector<ShortestPath>& D)
{
    // 全部初始化为false
    bool final[num] = {false};

    D.resize(m_vexnum);
    int v0 = locateVex(s);

    for(int i = 0; i < m_vexnum; ++i)
    {
        if(v0 == i)
        {
            D[i].weight = 0;
            D[i].sq.push_back(m_vexs[v0].data);
            D[i].sq.push_back(m_vexs[v0].data);
            final[v0] = true;
        }
        else
        {
            D[i].weight = infinity();
            D[i].sq.push_back(m_vexs[v0].data);
            D[i].sq.push_back(m_vexs[i].data);
        }
    }

    int v = -1;
    for(ArcBox* p = m_vexs[v0].firstout; p; p = p->taillink)
    {
        v = p->headvex;
        D[v].weight = p->weight;
    }

    for(int i = 1; -1 != v && i < m_vexnum; ++i)
    {
        v = -1;
        WeightType minW = infinity();
        for(int j = 0; j < m_vexnum; ++j)
        {
            if(!final[j] && D[j].weight < minW)
            {
                v = j;
                minW = D[j].weight;
            }
        }

        if(-1 == v)
            break;

        final[v] = true;
        for(ArcBox* p = m_vexs[v].firstout; p; p = p->taillink)
        {
            int w = p->headvex;
            if(!final[w] && D[v].weight + p->weight < D[w].weight)
            {
                D[w].weight = D[v].weight + p->weight;
                D[w].sq = D[v].sq;
                D[w].sq.push_back(w);
            }
        }
    }
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
