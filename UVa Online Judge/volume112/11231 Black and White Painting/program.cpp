// Black and White Painting
// UVa ID: 11231
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long cnt, n, m, c;
    long long row, cln;
    while (cin >> n >> m >> c, n > 0)
    {
        cnt = 0;
        if (c == 1)
        {
            row = 1 + (n - 8) / 2;
            cln = 1 + (m - 8) / 2;
            cnt += row * cln;
            row = (n - 7) / 2;
            cln = (m - 7) / 2;
            cnt += row * cln;
        }
        else
        {
            row = (n - 7) / 2;
            cln = 1 + (m - 8) / 2;
            cnt += row * cln;
            row = 1 + (n - 8) / 2;
            cln = (m - 7) / 2;
            cnt += row * cln;
        }
        cout << cnt << '\n';
    }

    return 0;
}
