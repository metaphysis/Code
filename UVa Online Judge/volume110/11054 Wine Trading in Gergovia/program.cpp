// Wine Trading in Gergovia
// UVa ID: 11054
// Verdict: Accepted
// Submission Date: 2017-10-15
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, wines[100010];
    
    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
            cin >> wines[i];
        long long exchanged = 0;
        int buy = 0, sell = 0;
        
        for (int i = 1; i <= n; i++)
            if (wines[i] > 0)
            {
                buy = i;
                break;
            }
        
        for (int i = 1; i <= n; i++)
            if (wines[i] < 0)
            {
                sell = i;
                break;
            }
            
        while (buy <= n && sell <= n)
        {
            if (wines[buy] + wines[sell] == 0)
            {
                exchanged += wines[buy] * abs(buy - sell);
                buy++, sell++;
                while (buy <= n && wines[buy] < 0) buy++;
                while (sell <= n && wines[sell] > 0) sell++;
            }
            else if (wines[buy] + wines[sell] > 0)
            {
                exchanged += abs(wines[sell]) * abs(buy - sell);
                wines[buy] += wines[sell];
                sell++;
                while (sell <= n && wines[sell] > 0) sell++;
            }
            else
            {
                exchanged += wines[buy] * abs(buy - sell);
                wines[sell] += wines[buy];
                buy++;
                while (buy <= n && wines[buy] < 0) buy++;
            }
        }

        cout << exchanged << '\n';
    }

    return 0;
}
