// Weird Fence
// UVa ID: 11262
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y, color;
    point (int x = 0, int y = 0, int color = 0): x(x), y(y), color(color) {}
} ps[110];

const int MAXV = 110;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

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

int getDist(point &p1, point &p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void build(int L, int P)
{
    memset(g, 0, sizeof(g));
    for (int i = 0; i < P; i++)
    {
        if (ps[i].color == 1) continue;
        for (int j = 0; j < P; j++)
        {
            if (j == i) continue;
            if (ps[i].color == ps[j].color) continue;
            if (getDist(ps[i], ps[j]) <= L * L)
                g[i][j] = 1;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string color;
    int T, P, K;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> P >> K;
        for (int i = 0; i < P; i++)
        {
            cin >> ps[i].x >> ps[i].y;
            cin >> color;
            if (color == "red") ps[i].color = 0;
            else ps[i].color = 1;
        }

        int lowL = 0, highL = 4000, L;
        tx = ty = P;
        build(highL, P);
        if (hungarian() < K)
        {
            cout << "Impossible\n";
            continue;
        }
        while (lowL <= highL)
        {
            L = (lowL + highL) >> 1;
            build(L, P);
            int M = hungarian();
            if (hungarian() >= K) highL = L - 1;
            else lowL = L + 1;
        }
        cout << lowL << '\n';
    }

    return 0;
}
