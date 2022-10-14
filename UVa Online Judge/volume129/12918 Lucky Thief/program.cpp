// Lucky Thief
// UVa ID: 12918
// Verdict: Accepted
// Submission Date: 2022-10-14
// UVa Run Time: 0.020s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    int n, m;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n >> m;
        cout << 1LL * (2 * m - n - 1) * n / 2 << '\n';
    }

    return 0;
}
