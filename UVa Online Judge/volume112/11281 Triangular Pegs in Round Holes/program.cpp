// Triangular Pegs in Round Holes
// UVa ID: 11281
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

    double rs[110], a, b, c;
    int m, n, fit[110];
    
    while (cin >> m)
    {
        for (int i = 1; i <= m; i++) cin >> rs[i];

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> a >> b >> c;
            double p = (a + b + c) / 2;
            double S = sqrt(p * (p - a) * (p - b) * (p - c));
            double D = (a * b * c) / (2 * S);
            
            int flag = 0;
            memset(fit, 0, sizeof(fit));
            for (int j = 1; j <= m; j++)
            {
                if (D <= rs[j])
                    fit[j] = 1, flag++;
                double L = max(a, max(b, c));
                if (L <= D)
                {
                    double h = sqrt(pow(rs[j] / 2, 2) - pow(L / 2, 2));
                    h = rs[j] / 2 - h;
                    double H = 2.0 * S / L;
                    if (H <= h) fit[j] = 1, flag++;
                }
            }
            
            cout << "Peg " << (char)('A' + i);
            if (flag)
            {
                cout << " will fit into hole(s):";
                for (int j = 1; j <= m; j++)
                    if (fit[j])
                        cout << ' ' << j;
                cout << '\n';
            }
            else
            {
                cout << " will not fit into any holes\n";
            }
        }
    }

    
    return 0;
}
