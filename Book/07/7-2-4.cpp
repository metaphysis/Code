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

const int MAXN = 100000;

void sieve(int *primes, int n, int &counter)
{
    counter = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[counter++] = i;
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int main(int argc, char *argv[])
{
    int primes[MAXN], counter = 0;
    int phi[MAXN];
    
    sieve(primes, MAXN, counter);
    
    for (int i = 1; i <= 100; i++)
    {
        phi[i] = i;
        for (int j = 0; j < counter; j++)
        {
            if (primes[j] > i) break;
            if (i % primes[j] == 0)
                phi[i] = phi[i] * (primes[j] - 1) / primes[j];
        }
        
        cout << phi[i] << '\n';
    }
    
    return 0;
}
