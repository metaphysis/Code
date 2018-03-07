// Help is Needed for Dexter
// UVa ID: 11384
// Verdict: Accepted
// Submission Date: 2018-03-07
// UVa Run Time: 0.020s
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

int dp(long long n)
{
    if (n == 1) return 1;
    return dp(n / 2) + 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n) cout << dp(n) << '\n';

    return 0;
}
