// Count the factors
// UVa ID: 10699
// Verdict: Accepted
// Submission Date: 2017-09-26
// UVa Run Time: 0.030s
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

int isPrime(int a)
{
    if (a <= 1 || !(a & 1)) return 0;
    if (a == 2) return 1;

    int factor = (int)sqrt(a);
    for (int i = 3; i <= factor; i += 2)
        if ((a % i) == 0)
            return 0;

    return 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n[500000] = {0}, idx = 1;
    
    n[0] = 2;
    for (int i = 3; i <= 500000; i += 2)
        if (isPrime(i))
            n[idx++] = i;
    
    int m;
    while (cin >> m, m > 0)
    {
        cout << m << " : ";
        set<int> primes;
        for (int i = 0; i < idx; i++)
        {
            if (m == 1) break;
            while ((m % n[i]) == 0)
            {
                primes.insert(n[i]);
                m /= n[i];
            }
        }
        if (m > 1) primes.insert(m);
        cout << primes.size() << '\n';
    }
    
    return 0;
}
