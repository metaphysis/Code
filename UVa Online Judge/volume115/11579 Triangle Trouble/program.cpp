// Triangle Trouble
// UVa ID: 11579
// Verdict: Accepted
// Submission Date: 2017-12-16
// UVa Run Time: 0.160s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    double sides[10010];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> sides[i];
        sort(sides, sides + n);
        
        double largest = 0.0;
        for (int i = 0; i < n - 2; i++)
        {
            double a = sides[i], b = sides[i + 1], c = sides[i + 2];
            if ((a + b <= c) || (a + c <= b) || (b + c <= a)) continue;
            double p = (a + b + c) / 2;
            double s = sqrt(p * (p - a) * (p - b) * (p - c));
            largest = max(largest, s);
        }
            
        cout << fixed << setprecision(2) << largest << '\n';
    }

    return 0;
}
