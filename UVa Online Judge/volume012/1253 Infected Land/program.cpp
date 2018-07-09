// Infected Land
// UVa ID: 1253
// Verdict: Accepted
// Submission Date: 2018-07-09
// UVa Run Time: 1.490s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    int state, vi, vj, moves;
    package(int state = 0, int vi = 0, int vj = 0, int moves = 0): state(state), vi(vi), vj(vj), moves(moves) {}
};

int n;
int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

int getNextState(int state, int vi, int vj)
{
    int nexts = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == vi && j == vj) continue;
            bool infected = state & (1 << (i * n + j));
            int adjacentInfected = 0;
            for (int k = 0; k < 8; k++)
            {
                int nexti = i + offset[k][0], nextj = j + offset[k][1];
                if (nexti < 0 || nexti >= n || nextj < 0 || nextj >= n) continue;
                if ((state & (1 << (nexti * n + nextj))) || (nexti == vi && nextj == vj))
                    adjacentInfected++;
            }
            if (infected && (adjacentInfected == 2 || adjacentInfected == 3)) nexts |= (1 << (i * n + j));
            else if (!infected && adjacentInfected == 3) nexts |= (1 << (i * n + j));
        }
    return nexts;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        package pack = package(0, 0, 0, 0);
        char c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> c;
                if (c == '@') pack.vi = i, pack.vj = j;
                if (c == '#') pack.state |= (1 << (i * n + j));
            }
        set<int> visited[n][n];
        queue<package> q;
        q.push(pack);
        visited[pack.vi][pack.vj].insert(pack.state);
        int best = -1;
        while (!q.empty())
        {
            pack = q.front(); q.pop();
            if (!pack.state)
            {
                best = pack.moves;
                break;
            }
            for (int k = 0; k < 8; k++)
            {
                int nexti = pack.vi + offset[k][0], nextj = pack.vj + offset[k][1];
                if (nexti < 0 || nexti >= n || nextj < 0 || nextj >= n) continue;
                if (pack.state & (1 << (nexti * n + nextj))) continue;
                int nexts = getNextState(pack.state, nexti, nextj);
                if (visited[nexti][nextj].find(nexts) != visited[nexti][nextj].end()) continue;
                visited[nexti][nextj].insert(nexts);
                q.push(package(nexts, nexti, nextj, pack.moves + 1));
            }
        }
        cout << best << '\n';
    }

    return 0;
}
