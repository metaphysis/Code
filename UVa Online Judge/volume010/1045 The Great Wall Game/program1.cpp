// The Great Wall Game
// UVa ID: 1045
// Verdict: Accepted
// Submission Date: 2019-06-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, INF = 0x7f7f7f7f;

int w[MAXN][MAXN], linky[MAXN], cx[MAXN], cy[MAXN], slack;
int lx[MAXN] = {0}, ly[MAXN] = {0}, n;

bool dfs(int x)
{
    cx[x] = true;
    for (int y = 0; y < n; y++) {
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
    for (int i = 0; i < n; i++) {
        lx[i] = -INF;
        for (int j = 0; j < n; j++)
            lx[i] = max(lx[i], w[i][j]);
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
            r += w[linky[y]][y];
    return -r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int stonex[16], stoney[16], cases = 0;

    while (cin >> n, n > 0) {
        for (int i = 0; i < n; i++) cin >> stonex[i] >> stoney[i];

        int r = INF;
        for (int row = 1; row <= n; row++) {
            memset(w, 0, sizeof(w));
            for (int cln = 1; cln <= n; cln++)
                for (int si = 0; si < n; si++)
                    w[si][cln - 1] -= abs(stonex[si] - row) + abs(stoney[si] - cln);
            r = min(r, kuhnMunkres());
        }

        for (int cln = 1; cln <= n; cln++) {
            memset(w, 0, sizeof(w));
            for (int row = 1; row <= n; row++)
                for (int si = 0; si < n; si++)
                    w[si][row - 1] -= abs(stonex[si] - row) + abs(stoney[si] - cln);
            r = min(r, kuhnMunkres());
        }

        memset(w, 0, sizeof(w));
        for (int row = 1, cln = 1; row <= n; row++, cln++)
            for (int si = 0; si < n; si++)
                w[si][row - 1] -= abs(stonex[si] - row) + abs(stoney[si] - cln);
        r = min(r, kuhnMunkres());

        memset(w, 0, sizeof(w));
        for (int row = n, cln = 1; cln <= n; row--, cln++)
            for (int si = 0; si < n; si++)
                w[si][cln - 1] -= abs(stonex[si] - row) + abs(stoney[si] - cln);
        r = min(r, kuhnMunkres());

        cout << "Board " << ++cases << ": " << r << " moves required.\n";
        cout << '\n';
    }

    return 0;
}
