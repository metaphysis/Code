// Triple Ties: The Organizer's Nightmare
// UVa ID: 703
// Verdict: Accepted
// Submission Date: 2017-10-27
// UVa Run Time: 0.000s
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

struct group
{
    int a, b, c;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, maze[110][110];
    while (cin >> n)
    {
        memset(maze, 0, sizeof(maze));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> maze[i][j];
                
        vector<group> groups;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                {
                    if (i == j || i == k || j == k) continue;
                    if (maze[i][j] + maze[j][i] + maze[j][k] + maze[k][j] + maze[k][i] + maze[i][k] == 0)
                    {
                        if (i < j && j < k)
                            groups.push_back(group{i, j, k});
                    }
                    if (maze[i][j] + maze[j][k] + maze[k][i] == 3)
                    {
                        if ((i < j && j < k) || (i > j && j > k))
                            groups.push_back(group{i, j, k});
                    }
                }

        cout << groups.size() << '\n';
        for (auto t : groups) cout << t.a << ' ' << t.b << ' ' << t.c << '\n';     
    }
    
    return 0;
}
