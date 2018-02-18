// The Tree Root
// UVa ID: 10459
// Verdict: Accepted
// Submission Date: 2018-02-19
// UVa Run Time: 0.060s
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

const int MAXV = 5100;

list<int> edges[MAXV];

int n, height[MAXV], visited[MAXV], parent[MAXV];

void dfs(int u, int d)
{
    height[u] = d;
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
        {
            parent[v] = u;
            dfs(v, d + 1);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int ki;
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++) edges[i].clear();
        for (int u = 1; u <= n; u++)
        {
            cin >> ki;
            for (int j = 1, v; j <= ki; j++)
            {
                cin >> v;
                edges[u].push_back(v);
                edges[v].push_back(u);
            }
        }

        set<int> worst;
        memset(visited, 0, sizeof(visited));
        dfs(1, 0);
        int maxD = *max_element(height + 1, height + n + 1);
        for (int i = 1; i <= n; i++)
            if (height[i] == maxD)
                worst.insert(i);

        memset(parent, -1, sizeof(parent));
        memset(visited, 0, sizeof(visited));
        dfs(*worst.begin(), 0);
        maxD = *max_element(height + 1, height + n + 1);
        bool even = (maxD % 2) == 0;
        int half = maxD / 2;
        int last = -1;
        for (int i = 1; i <= n; i++)
            if (height[i] == maxD)
            {
                worst.insert(i);
                last = i;
            }
        
        vector<int> path;
        while (parent[last] != -1)
        {
            path.push_back(last);
            last = parent[last];
        }
        path.push_back(last);
        
        set<int> best;
        best.insert(path[path.size() / 2]);
        if (path.size() % 2 == 0) best.insert(path[path.size() / 2 - 1]);

        cout << "Best Roots  :";
        for (auto v : best) cout << ' ' << v;
        cout << '\n';
        cout << "Worst Roots :";
        for (auto v : worst) cout << ' ' << v;
        cout << '\n';
    }

    return 0;
}
