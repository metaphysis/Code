// Making Quadrilaterals
// UVa ID: 12256
// Verdict: Accepted
// Submission Date: 2018-04-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long length[61] = {0, 1, 1, 1};
    for (int i = 4; i <= 60; i++)
        length[i] = length[i - 1] + length[i - 2] + length[i - 3];
    int cases = 0, n;
    while (cin >> n, n > 0) cout << "Case " << ++ cases << ": " << length[n] << '\n';

    return 0;
}
