// Councilling
// UVa ID: 10511
// Verdict: Accepted
// Submission Date: 2017-09-25
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *link, *parent, *visited;

    bool bfs()
    {
        memset(parent, 0xff, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> q; q.push(source);
        visited[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int i = link[u]; i != -1; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0)
                {
                    q.push(arcs[i].v);
                    visited[arcs[i].v] = 1;
                    parent[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        link = new int[v], parent = new int[v], visited = new int[v];
        arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] link, parent, visited, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
                delta = min(delta, arcs[i].residual);

            netFlow += delta;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
        }

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, link[u]};
        link[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, link[v]};
        link[v] = idx++;
    }
    
    vector<arc> getArc(int u)
    {
        vector<arc> as;
        for (int i = link[u]; i != -1; i = arcs[i].next)
            if (arcs[i].residual == 0 && arcs[i].v > u)
                as.push_back(arcs[i]);
        return as;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    getline(cin, line);
    int cases = stoi(line);
    getline(cin, line);
    
    for (int c = 1; c <= cases; c++)
    {
        int arcs = 0;

        vector<vector<int>> residents;
        map<string, int> namesIdx, partysIdx, clubsIdx;
        map<int, string> names, partys, clubs;
        int idxName = 1, idxParty = 1, idxClub = 1;
        string name, party, club;
        
        while (getline(cin, line), line.length() > 0)
        {
            vector<int> resident;

            istringstream iss(line);
            iss >> name >> party;
            
            if (namesIdx.find(name) == namesIdx.end())
            {
                names[idxName] = name;
                namesIdx[name] = idxName++;
            }
            if (partysIdx.find(party) == partysIdx.end())
            {
                partys[idxParty] = party;
                partysIdx[party] = idxParty++;
            }

            resident.push_back(namesIdx[name]);
            resident.push_back(partysIdx[party]);

            while (iss >> club)
            {
                if (clubsIdx.find(club) == clubsIdx.end())
                {
                    clubs[idxClub] = club;
                    clubsIdx[club] = idxClub++;
                }
                resident.push_back(clubsIdx[club]);
                arcs++;
            }
            
            residents.push_back(resident);
        }

        idxName--, idxParty--, idxClub--;
        int vertices = idxParty + 2 * idxName + idxClub + 2;
        arcs += idxParty + 2 * idxName + idxClub;

        EdmondsKarp ek(vertices, arcs * 2, 0, vertices - 1);

        int half = (idxClub % 2 == 0) ? (idxClub / 2 - 1) : idxClub / 2;
        for (auto pi : partysIdx)
            ek.addArc(0, pi.second, half);
        for (auto r : residents)
        {
            ek.addArc(r[1], r[0] + idxParty, 1);
            ek.addArc(r[0] + idxParty, r[0] + idxParty + idxName, 1);
            for (int i = 2; i < r.size(); i++)
                ek.addArc(r[0] + idxParty + idxName, r[i] + idxParty + 2 * idxName, 1);
        }
        for (auto ci : clubsIdx)
            ek.addArc(ci.second + idxParty + 2 * idxName, vertices - 1, 1);
        
        if (c > 1) cout << '\n';
        if (ek.maxFlow() == idxClub)
        {
            for (int u = 1; u <= idxName; u++)
            {
                for (auto a : ek.getArc(u + idxParty + idxName))
                {
                    cout << names[a.u - idxParty - idxName];
                    cout << ' ' << clubs[a.v - idxParty - 2 * idxName] << '\n';
                }
            }
        }
        else cout << "Impossible.\n";
    }
    
    return 0;
}
