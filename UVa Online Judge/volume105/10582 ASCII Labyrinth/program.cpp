// ASCII Labyrinth
// UVa ID: 10582
// Verdict: Accepted
// Submission Date: 2017-11-16
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

string line;
int m, n, maze[70][70], used[70][70], path, cases;
// right 0, down 1, left 2, up 3
int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void dfs(int i, int j, int d)
{
    if (i == m && j == n) { path++; return; }
    
    used[i][j] = 1;
    for (int next = 0; next <= 3; next++)
    {
        if ((maze[i][j] == 1 || maze[i][j] == 3) && next > 0) continue;
        if (maze[i][j] == 2 && (next == 0 || next == 2)) continue;
        int nextd = (d + next) % 4;
        int ii = i + offset[nextd][0], jj = j + offset[nextd][1];
        if (ii >= 1 && ii <= m && jj >= 1 && jj <= n)
            if (!used[ii][jj] && maze[ii][jj])
                dfs(ii, jj, nextd);
    }
    used[i][j] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> m >> n; cin.ignore(1024, '\n');

        memset(maze, 0, sizeof(maze));
        for (int i = 1; i <= m; i++)
        {
            getline(cin, line); getline(cin, line); getline(cin, line);
            for (int j = 1, k = 0; j <= n; j++)
            {
                while (line[k] != '|') k++;
                for (k++; line[k] != '|'; k++)
                    if (line[k] == '*')
                        maze[i][j]++;
            }
            getline(cin, line);
        }
        getline(cin, line);

        path = 0, maze[1][1] = 3;
        dfs(1, 1, 0); dfs(1, 1, 1);
        
        cout << "Number of solutions: " << path << '\n';
    }

    return 0;
}
