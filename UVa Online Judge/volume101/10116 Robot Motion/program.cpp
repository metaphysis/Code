// Robot Motion
// UVa ID: 10116
// Verdict: Accepted
// Submission Date: 2018-01-29
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

    int n, m, s;
    char grid[10][10];
    int visited[10][10];

    while (cin >> n >> m >> s, n > 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> grid[i][j];
                
        memset(visited, 0, sizeof(visited));
        map<int, int> steps;
        int x = 0, y = s - 1, cnt = 0, exited = 0;

        while (!visited[x][y])
        {
            visited[x][y] = 1;
            steps[x * m + y] = ++cnt;
            if (grid[x][y] == 'N') x -= 1;
            else if (grid[x][y] == 'S') x += 1;
            else if (grid[x][y] == 'W') y -= 1;
            else y += 1;
            if (x < 0 || y < 0 || x >= n || y >= m)
            {
                exited = 1;
                break;
            }
        }
        if (exited) cout << cnt << " step(s) to exit\n";
        else
        {
            cout << steps[x * m + y] - 1 << " step(s) before a loop of ";
            cout << cnt - steps[x * m + y] + 1 << " step(s)\n";
        }
    }

    return 0;
}
