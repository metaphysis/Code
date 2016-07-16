// Big Number
// UVa ID: 1185
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases, n;
    cin >> cases;
    while (cases--)
    {
        cin >> n;
        
        if (n < 50)
        {
            // normal method
            double sum = 0.0;
            for (int i = 1; i <= n; i++)
                sum += log10(i);
            cout << ((int)floor(sum) + 1) << endl;
        }
        else
        {
            // stirling's approximation
            int count = log10(2 * acos(-1.0) * n) / 2.0 + n * log10(n / exp(1)) + 1;
            cout << count << endl;
        }
    }
    
	return 0;
}
