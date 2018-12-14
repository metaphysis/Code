// Speedy Escape
// UVa ID: 11693
// Verdict: Accepted
// Submission Date: 2018-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const double EPSILON = 1e-10, MAX_SPEED = 1e10;

int n, m, e, b, p, dist[110][110], visited[110], out[110];
double speed[110], cap;
list<int> edges[110];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v] && speed[v] < cap)
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m >> e;
        for (int i = 1; i <= n; i++) edges[i].clear();
        memset(dist, INF, sizeof(dist));
        for (int i = 1, aa, bb, ll; i <= m; i++)
        {
            cin >> aa >> bb >> ll;
            dist[aa][bb] = dist[bb][aa] = min(dist[aa][bb], ll);
            edges[aa].push_back(bb);
            edges[bb].push_back(aa);
        }
        for (int i = 1; i <= e; i++) cin >> out[i];
        cin >> b >> p;

        for (int i = 1; i <= n; i++) dist[i][i] = 0;
        for (int k = 1; k <= n; k++)
        {
            if (k == p) continue;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }

        for (int i = 1; i <= n; i++)
        {
            speed[i] = MAX_SPEED;
            if (dist[p][i] > 0) speed[i] = 160.0 * dist[b][i] / dist[p][i];
        }
        
        cap = MAX_SPEED;
        memset(visited, 0, sizeof(visited));
        dfs(b);
        bool impossible = true;
        for (int i = 1; i <= e; i++)
            if (visited[out[i]])
            {
                impossible = false;
                break;
            }
        if (impossible)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        
        int its = 0;
        double low = 0, high = MAX_SPEED;
        while (fabs(high - low) > EPSILON && its++ < 100)
        {
            cap = (low + high) / 2;
            memset(visited, 0, sizeof(visited));
            dfs(b);
            bool impossible = true;
            for (int i = 1; i <= e; i++)
                if (visited[out[i]])
                {
                    impossible = false;
                    break;
                }
            if (impossible) low = cap;
            else high = cap;
        }
        cout << fixed << setprecision(8) << cap << '\n';
    }

    return 0;
}
