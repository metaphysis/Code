// Tri-Isomorphism
// UVa ID: 11393
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

    int n;
    while (cin >> n, n > 0)
    {
        if (n >= 3 && (n * (n - 1) / 2) % 3 == 0) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
