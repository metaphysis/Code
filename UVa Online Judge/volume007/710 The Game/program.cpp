// The Game
// UVa ID: 710
// Verdict: Accepted
// Submission Date: 2018-05-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

char grid[80][80];
int W, H, mx1, my1, mx2, my2, steps, visited[80][80];
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dfs(int mr, int mc, int dir, int moves)
{
    if (moves > steps) return;
    for (int k = 0; k < 4; k++)
    {
        if ((k + 2) % 4 == dir) continue;
        int rr = mr + offset[k][0], cc = mc + offset[k][1];
        if (rr < 0 || rr > H + 1 || cc < 0 || cc > W + 1) continue;
        if (visited[rr][cc]) continue;
        if (rr == my2 && cc == mx2)
        {
            steps = min(steps, moves + (k != dir));
            continue;
        }
        if (grid[rr][cc] == 'X') continue;
        visited[rr][cc] = 1;
        dfs(rr, cc, k, moves + (k != dir));
        visited[rr][cc] = 0;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> W >> H)
    {
        if (W == 0) break;
        cout << "Board #" << ++cases << ":\n";
        memset(grid, ' ', sizeof(grid));
        cin.ignore(256, '\n');
        string line;
        for (int i = 1; i <= H; i++)
        {
            getline(cin, line);
            for (int j = 0; j < W; j++)
                grid[i][j + 1] = line[j];
        }

        int pairs = 0;
        while (cin >> mx1 >> my1 >> mx2 >> my2)
        {
            if (mx1 == 0) break;
            cout << "Pair " << ++pairs << ": ";
            memset(visited, 0, sizeof(visited));
            steps = INF;
            dfs(my1, mx1, -1, 0);
            if (steps != INF) cout << steps << " segments.\n";
            else cout << "impossible.\n";
        }
        cout << '\n';
    }

    return 0;
}
