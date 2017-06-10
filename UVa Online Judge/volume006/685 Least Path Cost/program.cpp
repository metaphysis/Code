// Least Path Cost
// UVa ID: 685
// Verdict: Accepted
// Submission Date: 2017-06-10
// UVa Run Time: 0.000s
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

struct edge
{
    int start, end, height;
};

int M, N, D;
vector<vector<edge>> edges(410, vector<edge>());
vector<int> visited(410);
int minCost = -1;

void dfs(int i, int length, int previous, int cost)
{
    if (minCost != -1 && length >= 2 && cost > minCost)
        return;

    if (previous != -1 && length >= 2 && edges[i].size() == 1)
    {
        if (minCost == -1) minCost = cost;
        else minCost = min(minCost, cost);
    }
    else
    {
        for (auto e : edges[i])
        {
            if (visited[e.end]) continue;
            visited[i] = 1;
            if (previous == -1)
                dfs(e.end, length + 1, e.height, cost + D);
            else
                dfs(e.end, length + 1, e.height, cost + D + abs(e.height - previous));
            visited[i] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int start, end, height;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> M >> N >> D;
        for (int i = 1; i <= N; i++)
            edges[i].clear();
            
        for (int i = 1; i <= M; i++)
        {
            cin >> start >> end >> height;
            edges[start].push_back(edge{start, end, height});
            edges[end].push_back(edge{end, start, height});
        }

        minCost = -1;
        for (int i = 1; i <= N; i++)
        {
            if (edges[i].size() != 1) continue;
            fill(visited.begin(), visited.end(), 0);
            dfs(i, 0, -1, 0);
        }
        cout << minCost << '\n';
    }
    
    return 0;
}
