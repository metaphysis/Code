// Bipartite Numbers
// UVa ID: 1051
// Verdict: Accepted
// Submission Date: 2018-01-18
// UVa Run Time: 0.260s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Please refer to: https://github.com/morris821028/UVa/blob/master/volume010/1051%20-%20Bipartite%20Numbers%5Bbfs2%5D.cpp

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

struct privateKey
{
    int m, n, s, t;
    privateKey (int m = 0, int n = 0, int s = 0, int t = 0): m(m), n(n), s(s), t(t) {}
    bool operator < (const privateKey &pk) const
    {
        if (m + n != pk.m + pk.n) return m + n < pk.m + pk.n;
        if (s != pk.s) return s < pk.s;
        if (m != pk.m) return s < pk.t;
        return t < pk.t;
    }
};

const int MAXL = 10000;
int modulo1[MAXL], modulo10[MAXL];

void precalculate(int n)
{
    modulo1[0] = 0;
    modulo10[0] = 1;
    for (int i = 1; i < MAXL; i++)
    {
        modulo1[i] = (modulo1[i - 1] * 10 + 1) % n;
        modulo10[i] = (modulo10[i - 1] * 10) % n;
    }
}

inline bool bigger(int d, int m, int s, int t, int number)
{
    if (d >= 6) return true;
    int r = 0;
    for (int i = 1; i <= d; i++)
        r = r * 10 + (i <= m ? s : t);
    return r > number;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int number;
    while (cin >> number, number > 0)
    {
        precalculate(number);

        privateKey pk(MAXL);
        for (int d = 2; ; d++)
        {
            // Prune, or TLE!
            for (int m = ((number % 10 || d <= 20) ? 1 : d - 20); m < d; m++)
                for (int s = 1; s <= 9; s++)
                    for (int t = 0; t <= 9; t++)
                    {
                        if (s == t) continue;
                        long long r = ((long long)modulo1[m] * modulo10[d - m] * s + modulo1[d - m] * t) % number;
                        privateKey candiate(m, d - m, s, t);
                        if(r == 0 && bigger(d, m, s, t, number) && candiate < pk)
                            pk = candiate;
                    }
            if (pk.m < MAXL) break;
        }
        cout << number << ": " << pk.m << ' ' << pk.s << ' ' << pk.n << ' ' << pk.t << '\n';
    }

    return 0;
}
