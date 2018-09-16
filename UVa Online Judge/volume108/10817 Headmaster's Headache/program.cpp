// Headmaster's Headache
// UVa ID: 10817
// Verdict: Accepted
// Submission Date: 2018-09-16
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int weight[10] = {0, 1, 3, 9, 27, 81, 243, 729, 2187, 6561};

inline int add(int a, int b)
{
    int c = 0, idx = 1;
    while (a || b)
    {
        int digit = a % 3 + b % 3;
        if (digit > 2) digit = 2;
        c += digit * weight[idx++];
        a /= 3, b /= 3;
    }
    return c;
}

inline bool compare(int a, int b)
{
    while (a || b)
    {
        int digit = a % 3 - b % 3;
        if (digit < 0) return false;
        a /= 3, b /= 3;
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int S, M, N, C;
    int cnt[10], cost[110], bit[110], dp[6565];
    istringstream iss;

    while (cin >> S >> M >> N)
    {
        if (S == 0) break;
        cin.ignore(256, '\n');

        memset(cnt, 0, sizeof(cnt));
        memset(bit, 0, sizeof(bit));

        int baseCost = 0, subject;
        string line;
        for (int i = 1; i <= M; i++)
        {
            getline(cin, line);
            iss.clear(); iss.str(line);
            iss >> C;
            baseCost += C;
            while (iss >> subject)
                cnt[subject]++;
        }
        for (int i = 1; i <= N; i++)
        {
            getline(cin, line);
            iss.clear(); iss.str(line);
            iss >> cost[i];
            while (iss >> subject)
                bit[i] += weight[subject];
        }

        int needed = 0;
        for (int i = S; i >= 1; i--)
            needed = needed * 3 + (cnt[i] > 2 ? 0 : 2 - cnt[i]);

        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;

        int next;
        for (int i = 1; i <= N; i++)
            for (int j = weight[S + 1] - 1; j >= 0; j--)
            {
                next = add(j, bit[i]);
                dp[next] = min(dp[next], dp[j] + cost[i]);
            }

        int minimal = 0x3f3f3f3f;
        for (int i = 0; i < weight[S + 1]; i++)
            if (compare(i, needed))
                minimal = min(minimal, dp[i]);
        cout << baseCost + minimal << '\n';
    }

    return 0;
}
