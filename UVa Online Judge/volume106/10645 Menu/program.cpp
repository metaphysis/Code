// Menu
// UVa ID: 10645
// Verdict: Accepted
// Submission Date: 2018-10-08
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct data
{
    int bft, cst, idx, cnt;
    data (int bft = 0, int cst = 0, int idx = 0, int cnt = 0): bft(bft), cst(cst), idx(idx), cnt(cnt) {}
} dp[22][51][101];

const int INF = 0x7f7f7f7f, NONE = -1;

int K, N, M, costs[51], values[51];

data dfs(int k, int n, int m)
{
    if (k == K) return data(0, 0, 0, 0);
    if (n >= 0 && dp[k][n][m].bft != INF) return dp[k][n][m];

    data r(NONE, 0, 0, 0);
    for (int i = 0; i < N; i++)
    {
        if (i == n) continue;
        for (int j = 1; k + j <= K && m + j * costs[i] <= M; j++)
        {
            data new_r = dfs(k + j, i, m + j * costs[i]);
            if (new_r.bft == NONE) continue;
            int v = (j == 1 ? values[i] * 2 : values[i] * 3);
            if (r.bft < new_r.bft + v)
            {
                r.bft = new_r.bft + v;
                r.cst = new_r.cst + j * costs[i];
                r.idx = i;
                r.cnt = j;
            }
            else if (r.bft == new_r.bft + v)
            {
                if (r.cst > new_r.cst + j * costs[i])
                {
                    r.cst = new_r.cst + j * costs[i];
                    r.idx = i;
                    r.cnt = j;
                }
            }
        }
    }

    return n >= 0 ? dp[k][n][m] = r : r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> K >> N >> M)
    {
        if (K == 0) break;
        for (int i = 0; i < N; i++)
            cin >> costs[i] >> values[i];

        for (int i = 0; i <= K; i++)
            for (int j = 0; j <= N; j++)
                for (int k = 0; k <= M; k++)
                    dp[i][j][k].bft = INF;
        data r = dfs(0, NONE, 0);

        if (r.bft == NONE) cout << "0.0\n\n";
        else
        {
            cout << (r.bft / 2);
            if (r.bft % 2 == 0) cout << ".0\n";
            else cout << ".5\n";

            int k = r.cnt, n = r.idx, m = r.cnt * costs[r.idx];

            for (int i = 0; i < r.cnt; i++)
            {
                if (i) cout << ' ';
                cout << (r.idx + 1);
            }

            while (k < K)
            {
                r = dp[k][n][m];
                for (int i = 0; i < r.cnt; i++)
                {
                    cout << ' ' << (r.idx + 1);
                }
                k += r.cnt;
                n = r.idx;
                m += r.cnt * costs[r.idx];
            }
            cout << '\n';
        }
    }

    return 0;
}
