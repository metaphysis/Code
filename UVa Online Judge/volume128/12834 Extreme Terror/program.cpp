// Extreme Terror
// UVa ID: 12834
// Verdict: Accepted
// Submission Date: 2022-01-28
// UVa Run Time: 0.020s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct data
{
    int x, y, profit;
    bool operator<(const data &d) const
    {
        return profit < d.profit;
    }
} P[1000010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, N, K;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> N >> K;
        for (int i = 0; i < N; i++) cin >> P[i].x;
        for (int i = 0; i < N; i++) cin >> P[i].y;
        for (int i = 0; i < N; i++) P[i].profit = P[i].y - P[i].x;
        sort(P, P + N);
        long long profit = 0;
        for (int i = 0, j = 0; i < N; i++)
        {
            if (P[i].profit < 0)
                if (j < K)
                {
                    j++;
                    continue;
                }
            profit += P[i].profit;
        }
        if (profit <= 0) cout << "No Profit\n";
        else cout << profit << '\n';
    }
    return 0;
}
