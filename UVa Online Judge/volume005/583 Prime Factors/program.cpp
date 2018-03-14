// Prime Factors
// UVa ID: 583
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.330s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 70000;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int primes[MAX_N + 1] = { 0 }, prime_count = 0, factor_count;
    long long int factors[40];
    
    primes[prime_count++] = 2;
    for (int i = 3; i <= MAX_N; i += 2)
        if (primes[i] == 0)
        {
            for (int j = 2 * i; j <= MAX_N; j += i)
                primes[j] = -1;
            primes[prime_count++] = i;
        }

    long long int n, temp;
    while (cin >> n)
    {
        if (n == 0)
            break;

        temp = n;
        bool negative = false;
        if (temp < 0)
        {
            temp = abs(n);
            negative = true;
        }
        
        factor_count = 0;
        while (temp > 1)
        {
            bool divided = false;
            for (int i = 0; i < prime_count; i++)
                if (temp % primes[i] == 0)
                {
                    factors[factor_count++] = primes[i];
                    temp /= primes[i];
                    divided = true;
                    break;
                }
                
            if (!divided)
            {
                factors[factor_count++] = temp;
                break;
            }
        }
        
        cout << n << " = ";
        if (negative)
            cout << "-1 x " << factors[0];
        else
            cout << factors[0];

        for (int i = 1; i < factor_count; i++)
            cout << " x " << factors[i];
        
        cout << '\n';
    }
    
	return 0;
}
