// Gaussian Primes
// UVa ID: 960
// Verdict: Accepted
// Submission Date: 2017-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// http://mathworld.wolfram.com/GaussianPrime.html
//

#include <bits/stdc++.h>

using namespace std;

bool isPrime(int n)
{
    int high = (int)sqrt(n);
    for (int i = 2; i <= high; i++)
        if ((n % i) == 0)
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, a, b;
    
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        cin >> a >> b;
        
        if (a != 0 && b != 0)
        {
            if (isPrime(a * a + b * b)) cout << "P\n";
            else cout << "C\n";
        }
        else
        {
            int sum = abs(a) + abs(b);
            if (isPrime(sum) && (sum % 4) == 3) cout << "P\n";
            else cout << "C\n";
        }
    }
    
    return 0;
}
