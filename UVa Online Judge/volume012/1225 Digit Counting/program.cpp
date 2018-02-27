// Digit Counting
// UVa ID: 1225
// Verdict: Accepted
// Submission Date: 2018-02-26
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

const int MAXV = 10010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cnt[MAXV][10] = {0};
    for (int i = 1; i < MAXV; i++)
    {
        for (int j = 0; j < 10; j++)
            cnt[i][j] = cnt[i - 1][j];
        int x = i;
        while (x) cnt[i][x % 10]++, x /= 10;
    }

    int n, cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < 10; i++)
        {
            if (i) cout << ' ';
            cout << cnt[n][i];
        }
        cout << '\n';
    }

    return 0;
}
