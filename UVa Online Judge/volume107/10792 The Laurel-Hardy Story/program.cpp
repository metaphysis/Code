// The Laurel-Hardy Story
// UVa ID: 10792
// Verdict: Accepted
// Submission Date: 2017-12-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    double r, d, h1;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> r >> d >> h1;
        
        double a1 = asin((r - h1) / r);
        double a2 = asin((r - d) / r);
        double a3 = a1 - a2;
        double AB = 2.0 * r * cos(a2);
        double h2 = h1 + AB * sin(a3);
        
        cout << "Case " << c << ": ";
        cout << fixed << setprecision(4) << h2 << '\n';
    }

    return 0;
}
