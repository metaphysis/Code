// Smallest Regular Polygon 
// UVa ID: 12300
// Verdict: Accepted
// Submission Date: 2018-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int xa, ya, xb, yb, n;
    
    while (cin >> xa >> ya >> xb >> yb >> n, n > 0)
    {
        double r = 1.0;
        if (n % 2 == 1)
        {
            r /= sin((n - 1) * PI / n / 2) * sin((n - 1) * PI / n / 2);
        }
        r *= (pow(xa - xb, 2) + pow(ya - yb, 2)) / 4.0;
        r *= sin(PI / n) * cos(PI / n);
        r *= n;
        cout << fixed << setprecision(6) << r << '\n';
    }
    
    return 0;
}
