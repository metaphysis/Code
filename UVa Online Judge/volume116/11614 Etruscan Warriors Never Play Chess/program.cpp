// Etruscan Warriors Never Play Chess
// UVa ID: 11614
// Verdict: Accepted
// Submission Date: 2018-02-25
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        long long x = (sqrt(8.0 * n + 1.0) - 1.0) / 2.0;
        cout << x << '\n';
    }

    return 0;
}
