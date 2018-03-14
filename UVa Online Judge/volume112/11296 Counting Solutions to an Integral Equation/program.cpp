// Counting Solutions to an Integral Equation
// UVa ID: 11296
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n)
    {
        long long cnt = (2 + n / 2) * (1 + n / 2) / 2;
        cout << cnt << '\n';
    }

    return 0;
}
