// A Match Making Problem
// UVa ID: 12210
// Verdict: Accepted
// Submission Date: 2017-12-03
// UVa Run Time: 0.010s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int bachelors[10010], spinsters[10010];
    int b, s;
    int cases = 0;

    while (cin >> b >> s, b > 0)
    {
        cout << "Case " << ++cases << ": ";

        for (int i = 0; i < b; i++) cin >> bachelors[i];
        for (int i = 0; i < s; i++) cin >> spinsters[i];

        sort(bachelors, bachelors + b);
        if (b <= s) cout << 0 << '\n';
        else cout << (b - s) << ' ' << bachelors[0] << '\n';
    }

    return 0;
}
