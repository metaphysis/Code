// GCD
// UVa ID: 11417
// Verdict: Accepted
// Submission Date: 2017-03-22
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

int gcd(int a, int b)
{
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, sum[501] = {0};

    for (int i = 1; i < 501; i++)
    {
        sum[i] += sum[i - 1];
        for (int j = 1; j < i; j++)
            sum[i] += gcd(j, i);
    }

    while (cin >> n, n > 0)  cout << sum[n] << '\n';

    return 0;
}
