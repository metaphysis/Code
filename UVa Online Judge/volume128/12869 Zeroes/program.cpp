// Zeroes
// UVa ID: 12869
// Verdict: Accepted
// Submission Date: 2022-10-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long L, R;
    while (cin >> L >> R, L && R)
        cout << R / 5 - L / 5 + 1 << '\n';
    return 0;
}
