// Banning Balconing
// UVa ID: 12808
// Verdict: Accepted
// Submission Date: 2021-12-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    double L, D, H, V, g = 9810;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        cin >> L >> D >> H >> V;
        double hd = V * sqrt(2 * H / g);
        if (hd < D - 500 || hd > (D + L + 500)) { cout << "FLOOR\n"; continue; }
        if (hd > D + 500 && hd < (D + L - 500)) { cout << "POOL\n"; continue; }
        cout << "EDGE\n";
    }

    return 0;
}
