// Little Masters
// UVa ID: 12704
// Verdict: Accepted
// Submission Date: 2018-04-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    double x, y, r;

    for (int c = 1; c <= cases; c++)
    {
        cin >> x >> y >> r;
        double dist1 = sqrt(x * x + y * y);
        cout << fixed << setprecision(2) << (r - dist1);
        cout << ' ';
        cout << fixed << setprecision(2) << (r + dist1);
        cout << '\n';
    }

    return 0;
}
