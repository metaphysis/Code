// GCD Extreme (II)
// UVa ID: 11426
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <vector>

using namespace std;

const int MAXN = 4000001;

long long phi[MAXN] = {0}, sum[MAXN] = {0};

void preCalculate()
{
    iota(phi, phi + MAXN, 0);

    for (int i = 2; i < MAXN; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j < MAXN; j += i)
                phi[j] = phi[j] / i * (i - 1);
        }
        for (int j = i , k = 1; j < MAXN; j += i, k++)
            sum[j] += k * phi[i];
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    preCalculate();

    for (int i = 1; i < MAXN; i++)
        sum[i] += sum[i - 1] ;

    int n;
    while (cin >> n, n > 0)
        cout << sum[n] << '\n';

    return 0;
}
