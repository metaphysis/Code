// Burger Time?
// UVa ID: 11661
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int L;
    while (cin >> L, L > 0)
    {
        char P1, P2;
        int most = 0x3fffffff, dist = 0;

        int B = 1;
        while (B++ <= L)
        {
            cin >> P1;
            if (P1 != '.') break;
        }
        
        if (P1 == 'Z') most = 0;

        while (B++ <= L)
        {
            cin >> P2;
            dist += 1;
            if (P2 == '.') continue;
            if (P2 == 'Z') { most = 0; continue; }
            if (P1 != P2) { most = min(most, dist); P1 = P2; }
            dist = 0;
        }
        cout << most << '\n';
    }

    return 0;
}
