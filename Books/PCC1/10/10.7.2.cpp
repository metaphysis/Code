#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, INF = 0x7f7f7f7f;

int w[MAXN][MAXN], linky[MAXN], cx[MAXN], cy[MAXN], slack;
int lx[MAXN] = {0}, ly[MAXN] = {0};

bool dfs(int x)
{
    cx[x] = true;
    for (int y = 0; y < MAXN; y++) {
        if (cy[y]) continue;
        int d = lx[x] + ly[y] - w[x][y];
        if (!d) {
            cy[y] = true;
            if (!(~linky[y]) || dfs(linky[y])) {
                linky[y] = x;
                return true;
            }
        }
        else slack = min(slack, d);
    }
    return false;
}

int kuhnMunkres()
{
    memset(linky, -1, sizeof(linky));
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            lx[i] = max(lx[i], w[i][j]);
    for (int x = 0; x < MAXN; x++)
        while (true) {
            memset(cx, 0, sizeof(cx));
            memset(cy, 0, sizeof(cy));
            slack = INF;
            if (dfs(x)) break;
            for (int i = 0; i < MAXN; i++) {
                if (cx[i]) lx[i] -= slack;
                if (cy[i]) ly[i] += slack;
            }
        }
    int r = 0;
    for (int y = 0; y < n; y++)
        if (~linky[y])
            r += w[linky[y]][y];
    return r;
}

int main(int argc, char *argv[])
{
    kuhnMunkres();

    return 0;
}
