// Fourth Point
// UVa ID: 10242
// Verdict: Accepted
// Submission Date: 2017-12-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)
    {
        if (x1 == x4 && y1 == y4)
            swap(x1, x2), swap(y1, y2), swap(x3, x4), swap(y3, y4);
        if (x1 == x3 && y1 == y3)
            swap(x1, x2), swap(y1, y2);
        if (x2 == x4 && y2 == y4)
            swap(x3, x4), swap(y3, y4);

        x5 = x1 - (x2 - x4);
        y5 = y1 - (y2 - y4);

        cout << fixed << setprecision(3) << x5;
        cout << ' ';
        cout << fixed << setprecision(3) << y5;
        cout << '\n';
    }

    return 0;
}
