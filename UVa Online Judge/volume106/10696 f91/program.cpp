// f91
// UVa ID: 10696
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.040s
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

int f91[1000010];

int dfs(int n)
{
    if (f91[n] < 0)
    {
        if (n >= 101) f91[n] = n - 10;
        else f91[n] = dfs(dfs(n + 11));
    }
    return f91[n];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    memset(f91, -1, sizeof(f91));
    while (cin >> n, n > 0)
    {
        cout << "f91(" << n << ") = " << dfs(n) << '\n';
    }

    return 0;
}
