// Soda Surpler
// UVa ID: 11689
// Verdict: Accepted
// Submission Date: 2018-02-27
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

    int cases, e, f, c;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> e >> f >> c;
        int total = 0;
        while (true)
        {
            if (e + f < c) break;
            int ef = (e + f);
            e = ef / c, f = ef % c;
            total += e;
        }
        cout << total << '\n';
    }

    return 0;
}
