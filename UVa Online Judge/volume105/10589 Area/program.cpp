// Area
// UVa ID: 10589
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.090s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N1;
    double N2, xi, yi;
    
    while (cin >> N1 >> N2)
    {
        if (N1 == 0 && N2 == 0) break;

        if (N1 == 0)
        {
            cout << "0.00000\n";
            continue;
        }
        
        double S2 = N2 * N2;
        double in = 0;
        for (int i = 1; i <= N1; i++)
        {
            cin >> xi >> yi;
            double D1 = xi * xi + yi * yi;
            double D2 = xi * xi + (yi - N2) * (yi - N2);
            double D3 = (xi - N2) * (xi - N2) + yi * yi;
            double D4 = (xi - N2) * (xi - N2) + (yi - N2) * (yi - N2);
            if (D1 <= S2 && D2 <= S2 && D3 <= S2 && D4 <= S2) in += 1.0;
        }
        
        cout << fixed << setprecision(5) << in * (N2 * N2 / N1) << '\n';
    }

    return 0;
}
