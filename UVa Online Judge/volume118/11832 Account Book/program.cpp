// Account Book
// UVa ID: 11832
// Verdict: Accepted
// Submission Date: 2018-09-13
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, F, Ti[41], cache[41][82000], offset, top;
char path[41];

int dp(int idx, int sum)
{
    if (idx == N) return sum == F;
    if (~cache[idx][sum]) return cache[idx][sum];
    cache[idx][sum] = 0;
    if (dp(idx + 1, sum + Ti[idx] + offset))
    {
        if (path[idx] == '$') path[idx] = '+';
        if (path[idx] == '-') path[idx] = '?';
        cache[idx][sum] = 1;
    }
    if (dp(idx + 1, sum - Ti[idx] + offset))
    {
        if (path[idx] == '$') path[idx] = '-';
        if (path[idx] == '+') path[idx] = '?';
        cache[idx][sum] = 1;
    }
    return cache[idx][sum];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> F)
    {
        if (N == 0) break;

        offset = 0, top = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> Ti[i];
            top += Ti[i];
            offset = max(offset, Ti[i]);
        }

        // Special case.
        if (F < -top || F > top)
        {
            cout << "*\n";
            continue;
        }
        if (F == -top)
        {
            for (int i = 1; i <= N; i++)
                cout << '-';
            cout << '\n';
            continue;
        }
        if (F == top)
        {
            for (int i = 1; i <= N; i++)
                cout << '+';
            cout << '\n';
            continue;
        }

        // DP.
        top += N * offset, F += N * offset;;
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= top; j++)
                cache[i][j] = -1;
        memset(path, '$', sizeof(path));
        if (dp(0, 0))
        {
            for (int i = 0; i < N; i++)
                cout << path[i];
            cout << '\n';
        }
        else
            cout << "*\n";
            
    }

    return 0;
}
