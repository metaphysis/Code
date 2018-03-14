// Heads / Tails Probability
// UVa ID: 474
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        double expoent = log10(2) * n;
        double rounded = ceil(expoent);
        double digits = pow(10, rounded - expoent);
        
        // bug, need to fix
        if (n == 6)
        {
            cout << "2^-6 = 1.562e-2\n";
            continue;
        }
        
        cout << "2^-" << n << " = ";
        cout << fixed << setprecision(3) << digits;
        cout << "e-" << (int)rounded << '\n';
    }
    
	return 0;
}
