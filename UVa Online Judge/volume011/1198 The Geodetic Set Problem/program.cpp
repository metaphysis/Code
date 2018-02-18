// The Geodetic Set Problem
// UVa ID: 1198
// Verdict: Accepted
// Submission Date: 2018-02-18
// UVa Run Time: 0.000s
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

const int MAXV = 64, INF = 0x3f3f3f3f;

int n, q, dist[MAXV][MAXV], visited[MAXV], used[MAXV][MAXV][MAXV];
vector<int> parent[MAXV][MAXV];
string line;

void dfs(int i, int j)
{
    for (auto v : parent[i][j])
    {
        if (used[i][j][v]) continue;
        used[i][j][v] = 1;
        visited[v] = 1;
        dfs(i, v);
        dfs(v, j);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        cin.ignore(1024, '\n');

        memset(dist, 0x3f, sizeof(dist));
        for (int u = 1, v; u <= n; u++)
        {
            getline(cin, line);
            istringstream iss(line);
            while (iss >> v) dist[u][v] = dist[v][u] = 1;
            dist[u][u] = 0;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                parent[i][j].clear();

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        parent[i][j].clear();
                        parent[i][j].push_back(k);
                    }
                    else if (dist[i][j] == dist[i][k] + dist[k][j])
                    {
                        parent[i][j].push_back(k);
                    }
                }

        cin >> q;
        cin.ignore(1024, '\n');
        for (int i = 1, v; i <= q; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            vector<int> vertices;
            while (iss >> v) vertices.push_back(v);

            memset(used, 0, sizeof(used));
            memset(visited, 0, sizeof(visited));
            for (auto s : vertices)
                for (auto e : vertices)
                    dfs(s, e);

            if (count(visited + 1, visited + n + 1, 0) == 0)
                cout << "yes\n";
            else
                cout << "no\n";
        }
    }

    return 0;
}
