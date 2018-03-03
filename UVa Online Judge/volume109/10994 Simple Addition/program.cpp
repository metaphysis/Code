// Simple Addition
// UVa ID: 10994
// Verdict: Accepted
// Submission Date: 2018-03-03
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

long long getSum(int n)
{
    if (n <= 0) return 0;
    long long sum = 0, cnt = 0;
    while (n)
    {
        long long r = n % 10;
        sum += r * cnt + (1 + r) * r / 2;
        cnt = cnt * 10 + 45;
        n /= 10;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, q;
    while (cin >> p >> q, p >= 0)
        cout << getSum(q) - getSum(p - 1) << '\n';

    return 0;
}
