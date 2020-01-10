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

int kuhnMunkres()
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
    int r = 0;
    for (int y = 0; y < n; y++)
        if (~linky[y])
            r += weight[linky[y]][y];
    return r;
}

int main(int argc, char *argv[])
{
    
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> weight[i][j];

    cout << kuhnMunkres() << '\n';

    return 0;
}
