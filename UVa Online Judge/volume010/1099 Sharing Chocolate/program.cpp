// Sharing Chocolate
// UVa ID: 1099
// Verdict: Accepted
// Submission Date: 2018-10-11
// UVa Run Time: 1.130s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, x, y, A[20], sum[1 << 16] = {};
int dp[128][1 << 16];
list<int> L[10240];

void initialize()
{
    for (int i = 0; i <= (x * y); i++)
        L[i].clear();
    sum[0] = 0;
    for (int i = 1; i < (1 << n); i++)
    {
        int j = 31 - __builtin_clz(i);
        sum[i] = sum[i ^ (1 << j)] + A[j];
        L[sum[i]].push_back(i);
    }

    for (int i = 0; i <= max(x, y); i++)
        for (int j = 0; j < (1 << n); j++)
            dp[i][j] = -1;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        int top = (int)sqrt(A[i]);
        for (int j = 1; j <= top; j++)
            if (A[i] % j == 0)
                dp[j][1 << i] = 1;
    }
}

int dfs(int w, int mask)
{
    if (~dp[w][mask]) return dp[w][mask];
    if (sum[mask] % w != 0) return dp[w][mask] = 0;
    int h = sum[mask] / w;
    for (int i = 1; i <= w / 2; i++)
        for (auto j : L[i * h])
            if ((mask | j) == mask)
                if (dfs(min(i, h), j) && dfs(min(w - i, h), mask ^ j))
                    return dp[w][mask] = 1;
    for (int i = 1; i <= h / 2; i++)
        for (auto j : L[i * w])
            if ((mask | j) == mask)
                if (dfs(min(i, w), j) && dfs(min(h - i, w), mask ^ j))
                    return dp[w][mask] = 1;
    return dp[w][mask] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int cases = 0;
    while (cin >> n)
    {
        if (n == 0) break;
        cout << "Case " << ++cases << ": ";
        cin >> x >> y;
        int s = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> A[i];
            s += A[i];
        }
        if (x * y != s)
        {
            cout << "No\n";
            continue;
        }
        initialize();
        cout << (dfs(min(x, y), (1 << n) - 1) ? "Yes\n" : "No\n");
    }
    
    return 0;
}
