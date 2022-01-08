// Movie Collection
// UVa ID: 1513
// Verdict: Accepted
// Submission Date: 2022-01-07
// UVa Run Time: 0.070s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200010;

int n, m, f[MAXN], p[MAXN >> 1], y;

inline int lowbit(int x) { return x & (-x); }

void add(int x, int delta)
{
    for (int i = x; i <= MAXN; i += lowbit(i))
        f[i] += delta;
}

int get(int x)
{
    int s = 0;
    for (int i = x; i; i -= lowbit(i))
        s += f[i];
    return s;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n >> m;
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i++)
        {
            p[i] = n - i + 1;
            add(i, 1);
        }
        int x = n + 1;
        for (int i = 0, ai; i < m; i++)
        {
            if (i) cout << ' ';
            cin >> ai;
            int s = get(p[ai]);
            cout << n - s;
            add(p[ai], -1);
            p[ai] = x++;
            add(p[ai], 1);
        }
        cout << '\n';
    }
    return 0;
}
