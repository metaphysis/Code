// Gun Fight
// UVa ID: 12159
// Verdict: Accepted
// Submission Date: 2017-10-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 310;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }
    return 0;
}

// 匈牙利算法求最大匹配数。
int hungarian()
{
    int matches = 0;
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

struct tower { int x, y, power; } towers[MAXV];

bool above(tower a, tower b, tower c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0, a, b, r;
    
    while (cin >> n, n > 0)
    {
        tx = ty = n;
        for (int i = 0; i < n; i++)
            cin >> towers[i].x >> towers[i].y >> towers[i].power;
        cin >> a >> b >> r;
        a--, b--, r *= r;
        
        vector<int> group1, group2;
        for (int i = 0; i < n; i++)
        {
            if (i == a || i == b) continue;
            if (!towers[i].power) continue;
            if (above(towers[a], towers[b], towers[i])) group1.push_back(i);
            else group2.push_back(i);
        }
        if (group1.size() > group2.size()) group1.swap(group2);

        memset(g, 0, sizeof g);
        for (auto i : group1)
            for (auto j : group2)
            {
                int x = towers[i].x - towers[j].x, y = towers[i].y - towers[j].y;
                if((x * x + y * y) <= r && towers[i].power > towers[j].power)
                    g[i][j] = 1;
            }
        cout << "Case " << ++cases << ": " << hungarian() << '\n';
    }
    
    return 0;
}
