// Tennis Rounds
// UVa ID: 12643
// Verdict: Accepted
// Submission Date: 2021-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, i, j;
    while (cin >> N >> i >> j)
    {
        if (i > j) swap(i, j);
        int rounds = 0;
        while (true)
        {
            rounds++;
            if ((i & 1) && (i + 1 == j)) break;
            if (i & 1) i++;
            if (j & 1) j++;
            i >>= 1, j >>= 1;
        }
        cout << rounds << '\n';
    }

    return 0;
}
