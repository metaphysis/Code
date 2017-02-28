// Pseudoprime numbers
// UVa ID: 11287
// Verdict: Accepted
// Submission Date: 2017-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 32000;

int primes[MAXN] = {0}, counter = 0;

void generate_primes()
{
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
        {
            primes[counter++] = i;
            for (int j = i; j < MAXN; j += i)
                primes[j] = 1;
        }
}

long long int bigmod(int a, int p, int n)
{
    if (p == 0) return 1;
    if (p == 1) return a;
    
    long long int remainder = bigmod(a, p / 2, n);
    remainder *= remainder;
    remainder %= n;

    if (p % 2 == 0)
        return remainder;
    else
        return (remainder * a) % n;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int p, a;
    
    generate_primes();
    
    while (cin >> p >> a, p)
    {
        bool is_prime = true;
        for (int i = 0; i < counter && primes[i] < p; i++)
            if (p % primes[i] == 0)
            {
                is_prime = false;
                break;
            }
            
        if (is_prime)
            cout << "no\n";
        else
        {
            long long int mod = bigmod(a, p, p) % p;
            cout << (mod == a ? "yes\n" : "no\n");
        }
    }
    
    return 0;
}
