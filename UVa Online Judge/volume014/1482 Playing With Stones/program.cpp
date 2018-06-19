// Playing With Stones
// UVa ID: 1482
// Verdict: Accepted
// Submission Date: 2018-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long getSG(long long x)
{
    if (x & 1) return getSG(x >> 1);
    return x >> 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        long long sg = 0, ai;
        for (int i = 0; i < n; i++)
        {
            cin >> ai;
            sg ^= getSG(ai);
        }
        if (sg == 0) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
