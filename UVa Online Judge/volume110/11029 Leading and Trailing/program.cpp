// Leading and Trailing
// UVa ID: 11029
// Verdict: Accepted
// Submission Date: 2018-03-13
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

int powMod(int n, int k)
{
    if (k == 1) return n % 1000;
    int half = powMod(n, k / 2);
    half = (half * half) % 1000;
    if (k % 2 == 1) half = (half * (n % 1000)) % 1000;
    return half;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        // LLL
        double exponent = k * log10(n);
        exponent -= (int)exponent;
        int integer = pow(10, exponent) * 100.0;
        cout << setw(3) << left << integer;
        cout << "...";
        // TTT
        cout << setw(3) << right << setfill('0') << powMod(n, k) % 1000 << '\n';
    }

    return 0;
}
