// Optimal Bus Route Design
// UVa ID: 1349
// Verdict: Accepted
// Submission Date: 2019-07-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, INF = 0x7f7f7f7f;

int linky[MAXN], cx[MAXN], cy[MAXN];
int weight[MAXN][MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
int n;

bool dfs(int x)
{
    cx[x] = true;
    for (int y = 0; y < n; y++) {
        if (cy[y]) continue;
        int delta = lx[x] + ly[y] - weight[x][y];
        if (delta == 0) {
            cy[y] = true;
            if (linky[y] == -1 || dfs(linky[y])) {
                linky[y] = x;
                return true;
            }
        }
        else slack[y] = min(slack[y], delta);
    }
    return false;
}

void kuhnMunkres()
{
    for (int i = 0; i < n; i++)
    {
        linky[i] = -1, lx[i] = 0, ly[i] = 0;
        for (int j = 0; j < n; j++)
            lx[i] = max(lx[i], weight[i][j]);
    }
    for (int x = 0; x < n; x++)
        while (true) {
            memset(cx, 0, sizeof(cx));
            memset(cy, 0, sizeof(cy));
            for (int i = 0; i < n; i++) slack[i] = INF;
            if (dfs(x)) break;
            int delta = INF;
            for (int i = 0; i < n; i++)
                if (!cy[i])
                    delta = min(delta, slack[i]);
            for (int i = 0; i < n; i++) {
                if (cx[i]) lx[i] -= delta;
                if (cy[i]) ly[i] += delta;
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                weight[i][j] = -INF;
        for (int u = 0, v, d; u < n; u++)
        {
            while(cin >> v, v > 0)
            {
                cin >> d;
                v--;
                weight[u][v] = max(weight[u][v], -d);
            }
        }
        kuhnMunkres();
        int r = 0;
        for (int y = 0; y < n; y++)
        {
            if (weight[linky[y]][y] != -INF)
                r -= weight[linky[y]][y];
            else
            {
                r = -1;
                break;
            }
        }
        if (r < 0) cout << "N\n";
        else cout << r << '\n';
    }

    return 0;
}
