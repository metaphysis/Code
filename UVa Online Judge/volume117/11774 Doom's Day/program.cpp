// Doom's Day
// UVa ID: 11774
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        cout << "Case " << c << ": " << (n + m) / __gcd(n, m) << '\n';
    }

    return 0;
}
