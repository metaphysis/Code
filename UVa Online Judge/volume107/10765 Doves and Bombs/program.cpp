// Doves and Bombs
// UVa ID: 10765
// Verdict: Accepted
// Submission Date: 2017-10-21
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

const int MAXV = 10010;

vector<list<int>> edges(MAXV);
int dfn[MAXV], ic[MAXV], visited[MAXV], dfstime = 0;
int n, m;

int dfs(int u, int parent)
{
    int lowu = dfn[u] = ++dfstime, lowv, children = 0;
    
    for (auto v : edges[u])
    {
        if (!dfn[v])
        {
            ++children, lowu = min(lowu, lowv = dfs(v, u));
            if (lowv >= dfn[u]) ic[u] = 1;
        }
        else 
        {
            if (dfn[v] < dfn[u] && v != parent)
                lowu = min(lowu, dfn[v]);
        }
    }

    if (parent < 0 && children == 1) ic[u] = 0;

    return dfn[u] = lowu;
}

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

struct result
{
    int number, pigeon;
    
    bool operator<(const result &r) const
    {
        if (pigeon != r.pigeon) return pigeon > r.pigeon;
        else return number < r.number;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
 
    while (cin >> n >> m, n > 0)
    {
        for (int i = 0; i < n; i++) edges[i].clear();
        
        int from, to;
        while (cin >> from >> to)
        {
            if (from == -1) break;
            edges[from].push_back(to);
            edges[to].push_back(from);
        }

        dfstime = 0;
        memset(ic, 0, sizeof(ic)); memset(dfn, 0, sizeof(dfn));
        
        dfs(0, -1);
        
        vector<result> rs;
        for (int i = 0; i < n; i++)
        {
            if (ic[i])
            {
                int cc = 0;
                memset(visited, 0, sizeof visited);
                visited[i] = 1;

                for (int u = 0; u < n; u++)
                {
                    if (!visited[u])
                    {
                        cc++;
                        dfs(u);
                    }
                }
                rs.push_back(result{i, cc});
            }
            else
                rs.push_back(result{i, 1});
        }
        
        sort(rs.begin(), rs.end());
        
        for (int i = 0; i < m; i++)
            cout << rs[i].number << ' ' << rs[i].pigeon << '\n';
        cout << '\n';
    }
    
	return 0;
}
