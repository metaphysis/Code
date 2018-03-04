// Fantasy of a Summation
// UVa ID: 11718
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

int powMod(int n, int K, int MOD)
{
    if (K == 0) return 1;
    if (K == 1) return (n % MOD);
    int r = powMod(n, K / 2, MOD);
    if (K % 2 == 1)
        return (((r * r) % MOD) * (n % MOD)) % MOD;
    else
        return (r * r) % MOD;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, Ai[1010], n, K, MOD;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        cin >> n >> K >> MOD;
        
        int l = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> Ai[i];
            l += Ai[i] % MOD;
            l %= MOD;
        }
        
        int r = ((K % MOD) * powMod(n, K - 1, MOD)) % MOD;
        
        cout << (l * r) % MOD << '\n';
    }

    return 0;
}
