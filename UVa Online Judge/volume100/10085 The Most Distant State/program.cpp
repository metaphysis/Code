// The Most Distant State
// UVa ID: 10085
// Verdict: Accepted
// Submission Date: 2018-12-24
// UVa Run Time: 1.670s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct state
{
    int board[3][3], moves[64], n, emptyi, emptyj;
};

int getKey(int board[3][3])
{
    int key = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            key = key * 10 + board[i][j];
    return key;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string directions = "UDLR";
    int cases, offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        state s;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                cin >> s.board[i][j];
                if (s.board[i][j] == 0)
                {
                    s.emptyi = i;
                    s.emptyj = j;
                }
            }

        s.n = 0;
        queue<state> q;
        q.push(s);
        set<int> visited;
        visited.insert(getKey(s.board));
        int bestboard[3][3], bestmoves[64], bestn = 0;
        
        while (!q.empty())
        {
            s = q.front(); q.pop();
            for (int k = 0; k < 4; k++)
            {
                int nexti = s.emptyi + offset[k][0], nextj = s.emptyj + offset[k][1];
                if (nexti < 0 || nexti >= 3 || nextj < 0 || nextj >= 3) continue;
                swap(s.board[s.emptyi][s.emptyj], s.board[nexti][nextj]);
                int key = getKey(s.board);
                if (visited.find(key) == visited.end())
                {
                    state sn;
                    memcpy(sn.board, s.board, sizeof(s.board));
                    memcpy(sn.moves, s.moves, sizeof(s.moves));
                    sn.n = s.n;
                    sn.moves[sn.n++] = k;
                    sn.emptyi = nexti, sn.emptyj = nextj;
                    q.push(sn);
                    visited.insert(key);
                    if (sn.n > bestn)
                    {
                        bestn = sn.n;
                        memcpy(bestboard, sn.board, sizeof(sn.board));
                        memcpy(bestmoves, sn.moves, sizeof(sn.moves));
                    }
                }
                swap(s.board[s.emptyi][s.emptyj], s.board[nexti][nextj]);
            }
        }
        
        cout << "Puzzle #" << cs << '\n';
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j) cout << ' ';
                cout << bestboard[i][j];
            }
            cout << '\n';
        }
        for (int i = 0; i < bestn; i++)
            cout << directions[bestmoves[i]];
        cout << "\n\n";
    }

    return 0;
}
