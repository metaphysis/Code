// Coprimes
// UVa ID: 10637
// Verdict: Accepted
// Submission Date: 2018-07-25
// UVa Run Time: 0.890s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int S, T, selected[32], used[128], flag;

int cnt = 0;

void dfs(int mini, int t, int s)
{
    if (t == T)
    {
        if (s == S)
        {
            for (int i = 0; i < T; i++)
            {
                if (i) cout << ' ';
                cout << selected[i];
            }
            cout << '\n';
        }
        return;
    }

    for (int i = mini; i <= (S - s); i++)
    {
        if (used[i]) continue;
        flag = 1;
        for (int j = 0; j < t; j++)
            if (__gcd(i, selected[j]) > 1)
            {
                flag = 0;
                break;
            }
        if (!flag) continue;
        selected[t] = i;
        if (i > 1) for (int j = i; j <= S; j += i) used[j] = 1;
        dfs(i, t + 1, s + i);
        if (i > 1) for (int j = i; j <= S; j += i) used[j] = 0;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> S >> T;
        cout << "Case " << cs << ":\n";
        memset(used, 0, sizeof(used));
        dfs(1, 0, 0);
    }

    return 0;
}
