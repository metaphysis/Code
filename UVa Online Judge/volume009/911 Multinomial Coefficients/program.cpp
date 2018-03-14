// Multinomial Coefficients
// UVa ID: 911
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
    while (a != b) if (a > b) a -= b; else b -= a;
    return a;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, k, z;
    
    while (cin >> n)
    {
        vector<int> upper;
        for (int i = 2; i <= n; i++) upper.push_back(i);
            
        cin >> k;
        for (int i = 1; i <= k; i++)
        {
            cin >> z;
            if (z >= 2)
            {
                for (int j = 2; j <= z; j++)
                {
                    int remainder = j;
                    
                    while (remainder > 1)
                    {
                        for (int l = upper.size() - 1; l >= 0; l--)
                        {
                            int quotient = gcd(upper[l], remainder);
                            if (quotient > 1)
                            {
                                upper[l] /= quotient;
                                remainder /= quotient;
                            }
                            if (upper[l] == 1)
                            {
                                upper.erase(upper.begin() + l);
                                break;
                            }
                        }
                    }
                }
            }
        }
        
        int r = 1;
        for (int i = 0; i < upper.size(); i++)
            r *= upper[i];
        cout << r << '\n';
    }
    
    return 0;
}
