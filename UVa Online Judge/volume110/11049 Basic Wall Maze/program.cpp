// Basic Wall Maze
// UVa ID: 11049
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct state
{
    int r, c;
    string path;
};

struct forbid
{
    int r1, c1, r2, c2;
};

vector<forbid> forbids;

bool allowable(int r1, int c1, int r2, int c2)
{
    for (int i = 0; i < forbids.size(); i++)
    {
        forbid f = forbids[i];
        if (r1 == f.r1 && c1 == f.c1 && r2 == f.r2 && c2 == f.c2) return false;
        if (r1 == f.r2 && c1 == f.c2 && r2 == f.r1 && c2 == f.c1) return false;
    }
    return true;
}

void addForbid(int r1, int c1, int r2, int c2)
{
    // Horizontal
    if (r1 == r2)
    {
        for (int c = c1 + 1; c <= c2; c++)
        {
            int upr = r1, downr = r1 + 1;
            if (upr < 1 || downr > 6) continue;
            forbids.push_back(forbid{upr, c, downr, c});
        }
    }
    // Vertical
    else
    {
        for (int r = r1 + 1; r <= r2; r++)
        {
            int leftc = c1, rightc = c1 + 1;
            if (leftc < 1 || rightc > 6) continue;
            forbids.push_back(forbid{r, leftc, r, rightc});
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grid[10][10], visited[10][10];
    int startr, startc, endr, endc;
    int r1, c1, r2, c2;
    int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    string direction = "NSWE";

    while (cin >> startc >> startr)
    {
        if (startr == 0) break;
        cin >> endc >> endr;
        
        memset(visited, 0, sizeof(visited));
        forbids.clear();
        for (int i = 0; i < 3; i++)
        {
            cin >> c1 >> r1 >> c2 >> r2;
            addForbid(r1, c1, r2, c2);
        }
        
        queue<state> q;
        string empty;
        q.push(state{startr, startc, empty});
        visited[startr][startc] = 1;
        
        while (!q.empty())
        {
            state s = q.front(); q.pop();
            if (s.r == endr && s.c == endc)
            {
                cout << s.path << '\n';
                break;
            }
            for (int k = 0; k < 4; k++)
            {
                int nextr = s.r + offset[k][0];
                int nextc = s.c + offset[k][1];
                if (nextr >= 1 && nextr <= 6 && nextc >= 1 && nextc <= 6)
                {
                    if (!visited[nextr][nextc] && allowable(s.r, s.c, nextr, nextc))
                    {
                        visited[nextr][nextc] = 1;
                        q.push(state{nextr, nextc, s.path + direction[k]});
                    }
                }
            }
        }
    }

    return 0;
}
