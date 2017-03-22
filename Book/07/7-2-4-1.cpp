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

int primes[MAXN], counter = 0;

int getPhi(int m)
{
    int phi = m;
    for (int i = 0; i < counter; i++) {
        if (primes[i] > m) break;
        if (m % primes[i] == 0) phi = phi * (primes[i] - 1) / primes[i];
    }
    return phi;
}

int main(int argc, char *argv[])
{
    sieve(primes, MAXN, counter);
    
    for (int i = 1; i <= 100; i++) cout << getPhi(i) << '\n';
    
    return 0;
}
