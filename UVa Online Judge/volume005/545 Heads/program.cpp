// Heads
// UVa ID: 545
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int r, n;
    cin >> r;
    for (int i = 1; i <= r; i++)
    {
        cin >> n;
        
        double expoent = log10(2) * n;
        double rounded = ceil(expoent);
        double digits = pow(10, rounded - expoent);

        cout << "2^-" << n << " = ";
        cout << fixed << setprecision(3) << digits;
        cout << "E-" << (int)rounded << '\n';
    }
    
	return 0;
}
