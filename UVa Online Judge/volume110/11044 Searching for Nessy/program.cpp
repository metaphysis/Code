// Searching for Nessy
// UVa ID: 11044
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
        n -= 2, m -= 2;
        m = m / 3 + (m % 3 > 0);
        n = n / 3 + (n % 3 > 0);
        cout << m * n << '\n';
    }

    return 0;
}
