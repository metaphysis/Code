// Miles 2 Km
// UVa ID: 11780
// Verdict: Accepted
// Submission Date: 2018-03-16
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int fibonacci[21] = {10, 10};
    for (int i = 2; i <= 20; i++)
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    
    int dp[20010] = {1};
    for (int i = 0; i <= 20000; i++)
        for (int j = 0; j <= 20; j++)
            if (dp[i] && i + fibonacci[j] <= 20000)
                dp[i + fibonacci[j]] = 1;
                
    int n;
    while (cin >> n, n > 0)
    {
        n *= 16;
        int best = 0;
        for (int i = 0; i <= 20000; i++)
            if (dp[i] && abs(i - n) < abs(best - n))
                best = i;
        int diff = abs(best - n);
        cout << diff / 10 << '.' << setw(2) << left << setfill('0') << (diff % 10) << '\n';
    }

    return 0;
}
