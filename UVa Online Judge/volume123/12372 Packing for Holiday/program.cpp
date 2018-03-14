// Packing for Holiday
// UVa ID: 12372
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

    int cases, L, W, H;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> L >> W >> H;
        int M = max(L, max(W, H));
        cout << "Case " << c << ": ";
        if (M > 20) cout << "bad\n";
        else cout << "good\n";
    }

    return 0;
}
