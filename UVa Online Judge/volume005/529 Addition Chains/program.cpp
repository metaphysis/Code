// Addition Chains
// UVa ID: 529
// Verdict: Accepted
// Submission Date: 2016-12-21
// UVa Run Time: 0.000s
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

int part[40] = { 1 }, bestPart[40] = {1}, maxDepth, n;

void dfs(int depth)
{
    if (depth < maxDepth)
    {
        for (int i = depth - 1; i >= 0; i--)
        {
            int next = part[depth - 1] + part[i];
            if (next <= n)
            {
                part[depth] = next;
                if (part[depth] == n && maxDepth > depth)
                {
                    memcpy(bestPart, part, sizeof(part));
                    maxDepth = depth;
                }

                for (int j = depth + 1; j <= maxDepth; j++)
                    next *= 2;

                if (next >= n)
                    dfs(depth + 1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        if (n == 1)
            maxDepth = 0;
        else
            maxDepth = 20;

        dfs(1);

        for (int i = 0; i <= maxDepth; i++)
        {
            if (i > 0)
                cout << ' ';
            cout << bestPart[i];
        }
        cout << '\n';
    }

    return 0;
}
