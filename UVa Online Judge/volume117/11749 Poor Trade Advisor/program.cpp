// Poor Trade Advisor
// UVa ID: 11749
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 1.300s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

struct edge
{
    int u, v, w;
    bool operator<(const edge &e) const
    {
        return w > e.w;
    }
};

int n, m, u, v, w;
int visited[510], T;
list<edge> edges[510];
vector<edge> all;

int dfs(int u, int w)
{
    visited[u] = 1;
    T++;
    for (auto e : edges[u])
        if (!visited[e.v] && e.w == w)
            dfs(e.v, w);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m, n > 0)
    {
        all.clear();
        for (int i = 1; i <= n; i++) edges[i].clear();

        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge{u, v, w});
            edges[v].push_back(edge{v, u, w});
            all.push_back(edge{u, v, w});
        }
        sort(all.begin(), all.end());

        int maxCnt = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < all.size(); i++)
            if (all[i].w == all.front().w)
            {
                T = 0;
                dfs(all[i].u, all.front().w);
                maxCnt = max(maxCnt, T);
            }
            else break;
        cout << maxCnt << '\n';
    }

    return 0;
}
