// 9 Puzzle
// UVa ID: 11513
// Verdict: Accepted
// Submission Date: 2018-07-10
// UVa Run Time: 0.470s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    string board, moves;
};

int nextIdx[3][2][9] = {
    {{2, 3, 1, 4, 5, 6, 7, 8, 9}, {7, 2, 3, 1, 5, 6, 4, 8, 9}},
    {{1, 2, 3, 5, 6, 4, 7, 8, 9}, {1, 8, 3, 4, 2, 6, 7, 5, 9}},
    {{1, 2, 3, 4, 5, 6, 8, 9, 7}, {1, 2, 9, 4, 5, 3, 7, 8, 6}},
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int key;
    string next;

    package pack;
    queue<package> q;
    q.push(package{"123456789", next});
    map<int, string> visited;
    visited[123456789] = next;
    string dir = "HV";

    while (!q.empty())
    {
        pack = q.front(); q.pop();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                key = 0;
                next.clear();
                for (int k = 0; k < 9; k++)
                {
                    key = key * 10 + pack.board[nextIdx[i][j][k] - 1] - '0';
                    next += pack.board[nextIdx[i][j][k] - 1];
                }
                if (visited.count(key) == 0)
                {
                    string moves = string(1, dir[j]) + string(1, '0' + i + 1) + pack.moves;
                    visited[key] = moves;
                    q.push(package{next, moves});
                }
            }
        }
    }
    
    int n;
    while (cin >> n, n > 0)
    {
        key = n;
        for (int i = 2; i <= 9; i++)
        {
            cin >> n;
            key = key * 10 + n;
        }
        if (visited.find(key) != visited.end())
        {
            cout << (visited[key].length() / 2) << ' ' << visited[key] << '\n';
        }
        else cout << "Not solvable\n";
    }

    return 0;
}
