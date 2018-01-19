// sqrt log sin
// UVa ID: 11703
// Verdict: Accepted
// Submission Date: 2018-01-19
// UVa Run Time: 0.080s
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

int v[1000010];

int getV(int n)
{
    if (v[n] < 0)
    {
        int x = 0;
        x += getV(floor(n - sqrt(n))) + getV(floor(log(n))) + getV(floor(n * sin(n) * sin(n)));
        v[n] = x % 1000000;
    }
    return v[n];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(v, -1, sizeof(v));
    v[0] = 1;

    int n;
    while (cin >> n, n >= 0)
    {
        cout << getV(n) << '\n';
    }

    return 0;
}
