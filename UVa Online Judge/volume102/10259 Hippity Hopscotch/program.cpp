// Hippity Hopscotch
// UVa ID: 10259
// Verdict: Accepted
// Submission Date: 2018-02-14
// UVa Run Time: 0.290s
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

const int MAXV = 10010;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
};

list<edge> edges[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int n, jump, pennies[110][110], visited[MAXV], dist[MAXV];
    int offset[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> jump;

        edges[0].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> pennies[i][j];
                edges[(i - 1) * n + j].clear();
            }
        edges[0].push_back(edge(1, -pennies[1][1]));

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 0; k < 4; k++)
                    for (int x = 1; x <= jump; x++)
                    {
                        int nexti = i + offset[k][0] * x, nextj = j + offset[k][1] * x;
                        if (nexti < 1 || nexti > n || nextj < 1 || nextj > n) continue;
                        if (pennies[nexti][nextj] <= pennies[i][j]) continue;
                        edges[(i - 1) * n + j].push_back(edge((nexti - 1) * n + nextj, -pennies[nexti][nextj]));
                    }

        int maxPennies = 0;
        memset(dist, 0, sizeof(dist));
        queue<edge> q;
        q.push(edge(0, 0));
        dist[0] = 0;

        while (!q.empty())
        {
            edge e1 = q.front(); q.pop();
            for (auto e2 : edges[e1.v])
            {
                if (dist[e2.v] > dist[e1.v] + e2.w)
                {
                    dist[e2.v] = dist[e1.v] + e2.w;
                    maxPennies = min(maxPennies, dist[e2.v]);
                    q.push(edge(e2.v, dist[e2.v]));
                }
            }
        }

        if (c > 1) cout << '\n';
        cout << -maxPennies << '\n';
    }

    return 0;
}
