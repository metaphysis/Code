// Ants
// UVa ID: 1411
// Verdict: Accepted
// Submission Date: 2019-06-27
// UVa Run Time: 0.030s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-9;
const int MAXN = 110, INF = 0x7f7f7f7f;

int n;
int linky[MAXN], cx[MAXN], cy[MAXN];
double weight[MAXN][MAXN], lx[MAXN] = {0}, ly[MAXN] = {0}, slack[MAXN];

bool dfs(int x)
{
    cx[x] = true;
    for (int y = 0; y < n; y++) {
        if (cy[y]) continue;
        double delta = lx[x] + ly[y] - weight[x][y];
        if (fabs(delta) < EPSILON) {
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
        linky[i] = -1, lx[i] = -INF, ly[i] = 0;
        for (int j = 0; j < n; j++)
            lx[i] = max(lx[i], weight[i][j]);
    }
    for (int x = 0; x < n; x++)
        while (true) {
            memset(cx, 0, sizeof(cx));
            memset(cy, 0, sizeof(cy));
            for (int i = 0; i < n; i++) slack[i] = INF;
            if (dfs(x)) break;
            double delta = INF;
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

    int cases = 0;
    int antx[MAXN], anty[MAXN], applex[MAXN], appley[MAXN];

    while (cin >> n)
    {
        for (int i = 0; i < n; i++) cin >> antx[i] >> anty[i];
        for (int i = 0; i < n; i++) cin >> applex[i] >> appley[i];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                weight[i][j] = -sqrt(pow(applex[i] - antx[j], 2) + pow(appley[i] - anty[j], 2));

        kuhnMunkres();

        if (cases++) cout << '\n';
        for (int i = 0; i < n; i++) cout << (linky[i] + 1) << '\n';
    }

    return 0;
}
