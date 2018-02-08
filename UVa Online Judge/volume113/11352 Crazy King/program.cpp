// Crazy King
// UVa ID: 11352
// Verdict: Accepted
// Submission Date: 2018-02-08
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

struct point
{
    int x, y, moves;
    point (int x = 0, int y = 0, int moves = 0): x(x), y(y), moves(moves) {}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char grid[110][110];
    int cases, visited[110][110];
    int M, N, r1, c1, r2, c2;
    int offset[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    int king[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> M >> N;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                cin >> grid[i][j];
                visited[i][j] = 0;
                if (grid[i][j] == 'A') r1 = i, c1 = j;
                if (grid[i][j] == 'B') r2 = i, c2 = j;
            }
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (grid[i][j] == 'Z')
                {
                    for (int k = 0; k < 8; k++)
                    {
                        int nexti = i + offset[k][0], nextj = j + offset[k][1];
                        if (nexti >= 0 && nexti < M && nextj >= 0 && nextj < N)
                            if (grid[nexti][nextj] == '.')
                                grid[nexti][nextj] = 'X';
                    }
                }

        queue<point> q;
        q.push(point(r1, c1, 0));
        visited[r1][c1] = 1;

        while (!q.empty())
        {
            point p = q.front(); q.pop();
            if (p.x == r2 && p.y == c2)
            {
                cout << "Minimal possible length of a trip is " << p.moves << '\n';
                break;
            }
            for (int k = 0; k < 8; k++)
            {
                int nextr = p.x + king[k][0], nextc = p.y + king[k][1];
                if (nextr >= 0 && nextr < M && nextc >= 0 && nextc < N)
                    if (!visited[nextr][nextc])
                    {
                        char g = grid[nextr][nextc];
                        if (g == '.' || g == 'B')
                        {
                            visited[nextr][nextc] = 1;
                            q.push(point(nextr, nextc, p.moves + 1));
                        }
                    }
            }
        }
        if (!visited[r2][c2]) cout << "King Peter, you can't go now!\n";
    }

    return 0;
}
