// Can You Solve It?
// UVa ID: 10642
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long x1, y1, x2, y2;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        cin >> x1 >> y1 >> x2 >> y2;
        long long cnt1 = (1 + x1 + y1) * (x1 + y1) / 2 + (x1 + 1);
        long long cnt2 = (1 + x2 + y2) * (x2 + y2) / 2 + (x2 + 1);
        cout << (cnt2 - cnt1) << '\n';
    }

    return 0;
}
