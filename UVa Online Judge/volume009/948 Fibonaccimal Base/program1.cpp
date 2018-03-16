// Fibonaccimal Base
// UVa ID: 948
// Verdict: Accepted
// Submission Date: 2018-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXF = 64;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long fibs[MAXF] = {1, 2}, n;
    for (int i = 2; i < MAXF; i++) fibs[i] = fibs[i - 1] + fibs[i - 2];
    
    int cases;
    cin >> cases;
    while (cases--)
    {
        cin >> n;
        cout << n << " = ";
        bitset<64> finary(0);
        while (n)
        {
            for (int i = MAXF - 1; i >= 0; i--)
                if (n >= fibs[i])
                {
                    finary.set(i);
                    n -= fibs[i];
                    break;
                }
        }
        string f = finary.to_string();
        while (f.size() && f.front() == '0') f.erase(f.begin());
        cout << f << " (fib)\n";
    }
    
    return 0;
}
