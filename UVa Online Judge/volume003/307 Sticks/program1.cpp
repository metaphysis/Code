// Sticks
// UVa ID: 307
// Verdict: Accepted
// Submission Date: 2017-01-06
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int stick[105], used[105], n, goal, total;

bool dfs(int sum, int idx, int count)
{
    if (count == total) return true;

    for (int i = idx; i < n; i++)
    {
        if (used[i] || (i && !used[i - 1] && stick[i] == stick[i - 1]))
            continue;

        if (sum + stick[i] == goal)
        {
            used[i] = 1;
            if (dfs(0, 0, count + 1)) return true;
            used[i] = 0;
            return false;
        }
        else if (sum + stick[i] < goal)
        {
            used[i] = 1;
            if (dfs(sum + stick[i], i + 1, count)) return true;
            used[i] = 0;
            if (sum == 0) return false;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    while (cin >> n, n)
    {
        int length = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> stick[i];
            length += stick[i];
        }

        sort(stick, stick + n, greater<int>());

        for (goal = stick[0]; goal <= length; goal++)
        {
            if (length % goal != 0) continue;

            total = length / goal;
            memset(used, 0, sizeof(used));

            if (dfs(0, 0, 0))
            {
                cout << goal << '\n';
                break;
            }
        }
    }
    return 0;
}
