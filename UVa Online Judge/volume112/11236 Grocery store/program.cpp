// Grocery store
// UVa ID: 11236
// Verdict: Accepted
// Submission Date: 2017-11-09
// UVa Run Time: 1.340s
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

struct product
{
    long long a, b, c, d;
    bool operator<(const product &x)
    {
        if (a != x.a) return a < x.a;
        if (b != x.b) return b < x.b;
        if (c != x.c) return c < x.c;
        return d < x.d;
    }
} solutions[1024];

int cnt = 0;

void trick()
{
    long long upa = pow(20.0, 1.0 / 4.0) * 100 + 1;
    for (long long a = 1; a <= upa; a++)
        for (long long b = a; b < (2000LL - a); b++)
            for (long long c = b; c <= (2000LL - a - b); c++)
            {
                if (a * b * c <= 1000000LL) continue;
                if (((a + b + c) * 1000000LL) % (a * b * c - 1000000L) != 0) continue;
                long long d = ((a + b + c) * 1000000LL) / (a * b * c - 1000000LL);
                if (d < c) continue;
                if (a + b + c + d > 2000LL) continue;
                solutions[cnt++] = product{a, b, c, d};
            }
        
    sort(solutions, solutions + cnt);
}

void print(long long f)
{
    cout << (f / 100) << ".";
    f %= 100;
    cout << (f / 10);
    f %= 10;
    cout << f;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    trick();

    for (int i = 0; i < cnt; i++)
    {
        print(solutions[i].a);
        cout << ' ';
        print(solutions[i].b);
        cout << ' ';
        print(solutions[i].c);
        cout << ' ';
        print(solutions[i].d);
        cout << '\n';
    }
    
    return 0;
}
