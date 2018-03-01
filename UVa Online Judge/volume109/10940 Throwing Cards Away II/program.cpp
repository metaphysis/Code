// Throwing Cards Away II
// UVa ID: 10940
// Verdict: Accepted
// Submission Date: 2018-03-01
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

    int card[500010];
    int last = 0;
    for (int i = 1; i <= 500000; i++)
    {
        last = (last + 2) % i;
        card[i] = last ? last : i;
    }
    int n;
    while (cin >> n, n) cout << card[n] << '\n';

    return 0;
}
