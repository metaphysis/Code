// A Dinner with Schwarzenegger
// UVa ID: 10217
// Verdict: Accepted
// Submission Date: 2019-03-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        double r = (-1.0 + sqrt(1.0 + 4.0 * n)) / 2.0;
        cout << fixed << setprecision(2) << r << ' ' << int(r) + 1 << '\n';
    }

    return 0;
}
