// Building Designing
// UVa ID: 11039
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.030s
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

bool cmp(const int &a, const int &b)
{
    return abs(a) < abs(b);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, floors[500010];
    cin >> cases;

    for (int p = 1; p <= cases; p++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> floors[i];

        sort(floors, floors + n, cmp);

        int cnt = 0, lastFloor = 0;
        for (int i = 0; i < n; i++)
        {
            if (i && ((floors[i] > 0 && lastFloor > 0) || (floors[i] < 0 && lastFloor < 0))) continue;
            cnt++, lastFloor = floors[i];
        }
        cout << cnt << '\n';
    }

    return 0;
}
