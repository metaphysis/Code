// Car Rallying
// UVa ID: 959
// Verdict: Accepted
// Submission Date: 2018-11-08
// UVa Run Time: 1.210s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int A, B, C;
int track[10010], dp[10010][25], st[40040];

void build(int p, int left, int right)
{
    if (left == right) st[p] = track[left];
    else
    {
        int middle = (left + right) >> 1;
        build((p << 1) + 1, left, middle);
        build((p + 1) << 1, middle + 1, right);
        st[p] = min(st[(p << 1) + 1], st[(p + 1) << 1]);
    }
}

int query(int p, int left, int right, int qleft, int qright)
{
    if (qleft > right || qright < left) return INF;
    if (qleft <= left && qright >= right) return st[p];
    int middle = (left + right) >> 1;
    return min(query((p << 1) + 1, left, middle, qleft, qright), query((p + 1) << 1, middle + 1, right, qleft, qright));
}

int dfs(int spot, int v)
{
    if (spot == C) return 0;
    if (~dp[spot][v]) return dp[spot][v];
    int r = INF;
    for (int a = 0; a <= A; a++)
    {
        if (v + a == 0) continue;
        int next = min(spot + v + a - 1, C - 1);
        int minv = query(0, 0, C - 1, spot, next);
        if (minv < v + a) break;
        r = min(r, 1 + dfs(next + 1, v + a));
    }
    for (int b = 0; b <= B; b++)
    {
        if (v - b <= 0) break;
        int next = min(spot + v - b - 1, C - 1);
        int minv = query(0, 0, C - 1, spot, next);
        if (minv < v - b) continue;
        r = min(r, 1 + dfs(next + 1, v - b));
    }
    return dp[spot][v] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, V;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> A >> B;
        A /= 10, B /= 10, C = 0;
        while (cin >> N >> V)
        {
            if (N == 0 && V == 0) break;
            V /= 10;
            for (int i = 0; i < N; i++)
                track[C++] = V;
        }
        track[C++] = 1000;
        build(0, 0, C - 1);
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 0) << '\n';
    }

    return 0;
}
