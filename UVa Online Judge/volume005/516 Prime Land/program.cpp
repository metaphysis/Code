// Prime Land
// UVa ID: 516
// Verdict: Accepted
// Submission Date: 2016-08-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const int MAX_N = 33000;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int primes[MAX_N + 1] = { 0 }, prime_count = 0, factors[16][2], factor_count;
    
    primes[prime_count++] = 2;
    for (int i = 3; i <= MAX_N; i += 2)
        if (primes[i] == 0)
        {
            for (int j = 2 * i; j <= MAX_N; j += i)
                primes[j] = -1;
            primes[prime_count++] = i;
        }

    string line;
    while (getline(cin, line), line != "0")
    {
        int n = 1, p, e;
        
        istringstream iss(line);
        while (iss >> p >> e)
            n *= pow(p, e);

        n--;
        factor_count = 0;
        memset(factors, 0, sizeof(factors));

        for (int i = 0; i < prime_count && n > 1; i++)
        {
            if (n % primes[i] == 0)
            {
                factors[factor_count][0] = primes[i];
                factors[factor_count][1] = 1;
                n /= primes[i];
                
                while (n > 1 && n % primes[i] == 0)
                {
                    factors[factor_count][1]++;
                    n /= primes[i];
                }
                
                factor_count++;
            }
        }
        
        cout << factors[factor_count - 1][0] << ' ' << factors[factor_count - 1][1];
        for (int i = factor_count - 2; i >= 0; i--)
            cout << ' ' << factors[i][0] << ' ' << factors[i][1];
        cout << '\n';
    }
    
	return 0;
}
