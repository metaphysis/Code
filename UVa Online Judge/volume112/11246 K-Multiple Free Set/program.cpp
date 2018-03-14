// K-Multiple Free Set
// UVa ID: 11246
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// f(i) = (-1)^i * (n / k^i).

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k;
    cin >> cases;
    while (cases--)
    {
        cin >> n >> k;
        int total = 0, sign = 1;
        while (n)
        {
            total += sign * n;
            n /= k;
            sign *= -1;
        }
        cout << total << '\n';
    }

    return 0;
}
