// Destroy the Moon to Save the Earth
// UVa ID: 13142
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    long long T, S, D;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> T >> S >> D;
        int tons = (int)(1.0 * abs(D) * 1000 * 1000 / T / 24 / 3600);
        if (tons == 0 || D <= 0) cout << "Add ";
        else cout << "Remove ";
        cout << tons << " tons\n";
    }
    return 0;
}
