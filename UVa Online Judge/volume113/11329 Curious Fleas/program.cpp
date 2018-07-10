// Curious Fleas
// UVa ID: 11329
// Verdict: Accepted
// Submission Date: 2018-07-10
// UVa Run Time: 3.320s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    int board, die, di, dj, moves;
    package (int board = 0, int die = 0, int di = 0, int dj = 0, int moves = 0): board(board), die(die), di(di), dj(dj), moves(moves) {}
};

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int bitIdx[4][6] = {
    {1, 5, 2, 0, 4, 3},
    {2, 1, 5, 3, 0, 4},
    {3, 0, 2, 5, 4, 1},
    {4, 1, 0, 3, 5, 2}
};

inline void getNextDie(int &die, int dir)
{
    int mask = 0;
    for (int k = 0; k < 6; k++)
        mask |= (((die & (1 << bitIdx[dir][k])) ? 1 : 0) << k);
    die = mask;
}

inline void getNextState(package pack, package &next, int nexti, int nextj, int dir)
{
    getNextDie(pack.die, dir);
    next.board = pack.board, next.die = pack.die;
    next.board &= (~(1 << (nexti * 4 + nextj))), next.die &= (~1);
    if (pack.die & 1) next.board |= (1 << (nexti * 4 + nextj));
    if (pack.board & (1 << (nexti * 4 + nextj))) next.die |= 1;
    next.di = nexti, next.dj = nextj, next.moves = pack.moves + 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int board = 0, die = 0, di, dj;
        char c;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                cin >> c;
                if (c == 'X') board |= (1 << (i * 4 + j));
                if (c == 'D') di = i, dj = j;
            }

        package pack;
        set<int> visited[4][4];
        queue<package> q;
        q.push(package(board, die, di, dj, 0));
        visited[di][dj].insert((board << 6) | die);
        int best = -1;
        while (!q.empty())
        {
            pack = q.front(); q.pop();
            if (pack.board == 0)
            {
                best = pack.moves;
                break;
            }
            for (int dir = 0; dir < 4; dir++)
            {
                int nexti = pack.di + offset[dir][0], nextj = pack.dj + offset[dir][1];
                if (nexti < 0 || nexti >= 4 || nextj < 0 || nextj >= 4) continue;
                package next;
                getNextState(pack, next, nexti, nextj, dir);
                int key = (next.board << 6) | next.die;
                if (visited[nexti][nextj].count(key) == 0)
                {
                    visited[nexti][nextj].insert(key);
                    q.push(next);
                }
            }
        }
        if (best == -1) cout << "impossible\n";
        else cout << best << '\n';
    }

    return 0;
}
