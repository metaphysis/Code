// Sum of Different Primes
// UVa ID: 1213
// Verdict: Accepted
// Submission Date: 2016-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector < int > primes;

bool isPrime(unsigned int x)
{
    if (x <= 1)
        return false;
        
    if (x == 2)
        return true;
        
    if (x % 2 == 0)
        return false;
        
    unsigned int i = 3;
    while (i <= (sqrt(x) + 1))
    {
        if (x % i == 0)
            return false;
        i += 2;
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    unsigned int ways[15][1130] = { 0 };
    
    for (int i = 1; i <= 1120; i++)
        if (isPrime(i))
            primes.push_back(i);
            
    ways[0][0] = 1;
    for (int i = 0; i < primes.size(); i++)
        for (int k = 14; k >= 1; k--)
            for (int n = 1120; n >= primes[i]; n--)
                    ways[k][n] += ways[k - 1][n - primes[i]];
    int n, k;
    while (cin >> n >> k, n && k)
        cout << ways[k][n] << "\n";
            
	return 0;
}
