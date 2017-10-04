// Fire! Fire!! Fire!!!
// UVa ID: 10243
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <vector>

using namespace std;

const int MAXV = 1000010;

struct edge
{
    int u, v, next;
};

int first[MAXV], nodes[MAXV], visited[MAXV], parent[MAXV], idx = 0, n;
edge edges[MAXV];

int greedy()
{
    int cvn = 0, covered[MAXV], in_mvs[MAXV];
    
    memset(covered, 0, sizeof(covered));
    memset(in_mvs, 0, sizeof(in_mvs));

    for (int i = n - 1; i >= 1; i--)
    {
        int u = nodes[i];
        if (!covered[u] && !covered[parent[u]])
        {
            in_mvs[parent[u]] = 1;
            covered[u] = covered[parent[u]] = 1;
            cvn++;
        }
    }
    
    return cvn;
}

void dfs(int u)
{
    nodes[idx++] = u;
    
    for (int k = first[u]; k != -1; k = edges[k].next)
        if (!visited[edges[k].v])
        {
            parent[edges[k].v] = u;
            visited[edges[k].v] = 1;
            dfs(edges[k].v);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    while (cin >> n, n > 0)
    {
        idx = 0;
        memset(first, -1, sizeof(first));

        int nv, v;
        for (int u = 1; u <= n; u++)
        {
            cin >> nv;
            for (int j = 1; j <= nv; j++)
            {
                cin >> v;
                edges[idx] = (edge){u, v, first[u]};
                first[u] = idx++;
                
                edges[idx] = (edge){v, u, first[v]};
                first[v] = idx++;
            }
        }

        idx = 0;
        memset(visited, 0, sizeof(visited));
        memset(parent, -1, sizeof(parent));
        
        dfs(1);
        
        if (n == 1) cout << "1\n";
        else cout << greedy() << '\n';
    }
    
	return 0;
}
