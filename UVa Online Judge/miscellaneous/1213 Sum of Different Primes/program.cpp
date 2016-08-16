// Sum of Different Primes
// UVa ID: 1213
// Verdict: Accepted
// Submission Date: 2016-08-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    unsigned int ways[15][1130] = { 0 }, primes[1120], prime_count = 0;
    
    memset(primes, 0, sizeof(primes));
    
    primes[prime_count++] = 2;
    for (int i = 3; i < 1120; i += 2)
        if (primes[i] == 0)
        {
            for (int j = 2 * i; j < 1120; j += i)
                primes[j] = 1;
            primes[prime_count++] = i;
        }
            
    ways[0][0] = 1;
    for (int i = 0; i < prime_count; i++)
        for (int k = 14; k >= 1; k--)
            for (int n = 1120; n >= primes[i]; n--)
                    ways[k][n] += ways[k - 1][n - primes[i]];
    int n, k;
    while (cin >> n >> k, n && k)
        cout << ways[k][n] << "\n";
            
	return 0;
}
