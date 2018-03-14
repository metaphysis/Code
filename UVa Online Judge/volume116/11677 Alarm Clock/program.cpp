// Alarm Clock
// UVa ID: 11677
// Verdict: Accepted
// Submission Date: 2017-12-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int H1, M1, H2, M2;
    
    while (cin >> H1 >> M1 >> H2 >> M2)
    {
        if (H1 == 0 && M1 == 0 && H2 == 0 && M2 == 0) break;
        int T1 = H1 * 60 + M1, T2 = H2 * 60 + M2;
        if (T2 >= T1) cout << (T2 - T1) << '\n';
        else cout << (1440 - T1 + T2 ) << '\n';
    }

    return 0;
}
