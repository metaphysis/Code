// The Great Wall Game
// UVa ID: 1045
// Verdict: Accepted
// Submission Date: 2019-06-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, INF = 0x7f7f7f7f;

int linky[MAXN], cx[MAXN], cy[MAXN];
int weight[MAXN][MAXN], lx[MAXN] = {0}, ly[MAXN] = {0}, slack;
int n;

bool dfs(int x)
{
    cx[x] = true;
    for (int y = 0; y < n; y++) {
        if (cy[y]) continue;
        int delta = lx[x] + ly[y] - weight[x][y];
        if (!delta) {
            cy[y] = true;
            if (linky[y] == -1 || dfs(linky[y])) {
                linky[y] = x;
                return true;
            }
        }
        else slack = min(slack, delta);
    }
    return false;
}

int kuhnMunkres()
{
    memset(linky, -1, sizeof(linky));
    for (int i = 0; i < n; i++) {
        lx[i] = -INF, ly[i] = 0;
        for (int j = 0; j < n; j++)
            lx[i] = max(lx[i], weight[i][j]);
    }
    for (int x = 0; x < n; x++)
        while (true) {
            memset(cx, 0, sizeof(cx));
            memset(cy, 0, sizeof(cy));
            slack = INF;
            if (dfs(x)) break;
            for (int i = 0; i < n; i++) {
                if (cx[i]) lx[i] -= slack;
                if (cy[i]) ly[i] += slack;
            }
        }
    int r = 0;
    for (int y = 0; y < n; y++)
        if (~linky[y])
            r += weight[linky[y]][y];
    return r;
}

int modifiedKuhnMunkres()
{
    int a = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a = max(a, weight[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            weight[i][j] = a - weight[i][j];
    int r = kuhnMunkres();
    return n * a - r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int sx[16], sy[16], cases = 0;

    while (cin >> n, n > 0) {
        for (int i = 0; i < n; i++) cin >> sx[i] >> sy[i];

        int r = INF;
        for (int row = 1; row <= n; row++) {
            memset(weight, 0, sizeof(weight));
            for (int cln = 1; cln <= n; cln++)
                for (int si = 0; si < n; si++)
                    weight[si][cln - 1] = abs(sx[si] - row) + abs(sy[si] - cln);
            r = min(r, modifiedKuhnMunkres());
        }

        for (int cln = 1; cln <= n; cln++) {
            memset(weight, 0, sizeof(weight));
            for (int row = 1; row <= n; row++)
                for (int si = 0; si < n; si++)
                    weight[si][row - 1] = abs(sx[si] - row) + abs(sy[si] - cln);
            r = min(r, modifiedKuhnMunkres());
        }

        memset(weight, 0, sizeof(weight));
        for (int row = 1, cln = 1; row <= n; row++, cln++)
            for (int si = 0; si < n; si++)
                weight[si][row - 1] = abs(sx[si] - row) + abs(sy[si] - cln);
        r = min(r, modifiedKuhnMunkres());

        memset(weight, 0, sizeof(weight));
        for (int row = n, cln = 1; cln <= n; row--, cln++)
            for (int si = 0; si < n; si++)
                weight[si][cln - 1] = abs(sx[si] - row) + abs(sy[si] - cln);
        r = min(r, modifiedKuhnMunkres());

        cout << "Board " << ++cases << ": " << r << " moves required.\n";
        cout << '\n';
    }

    return 0;
}
