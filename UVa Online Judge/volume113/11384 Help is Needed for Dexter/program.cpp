// Help is Needed for Dexter
// UVa ID: 11384
// Verdict: Accepted
// Submission Date: 2018-03-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp(long long n)
{
    if (n == 1) return 1;
    return dp(n / 2) + 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n) cout << dp(n) << '\n';

    return 0;
}
