// Checking the N-Queens Problem
// UVa ID: 932
// Verdict: Accepted
// Submission Date: 2019-01-26
// UVa Run Time: 0.030s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, rows[32], columns[32], diagonals[2];
vector<pair<int, int>> queens;

bool validate()
{
    if (queens.size() != n) return false;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (queens[i].first == queens[j].first) return false;
            if (queens[i].second == queens[j].second) return false;
            if (abs(queens[i].first - queens[j].first) == abs(queens[i].second - queens[j].second)) return false;
        }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    int board[32][32];

    while (cin >> n)
    {
        char cell;
        queens.clear();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> cell;
                if (cell == '0') board[i][j] = 0;
                else
                {
                    board[i][j] = 1;
                    queens.push_back(make_pair(i, j));
                }
            }
        
        if (cases++) cout << '\n';
        if (validate())
        {
            cout << "YES\n";
            continue;
        }

        cout << "NO\n";
        bool done = false;
        for (int i = 0; i < queens.size(); i++)
        {
            pair<int, int> backup = queens[i];
            for (int k = 0; k < 8; k++)
            {
                int x = queens[i].first, y = queens[i].second;
                while (true)
                {
                    x += offset[k][0], y += offset[k][1];
                    if (x < 0 || x >= n || y < 0 || y >= n) break;
                    if (board[x][y]) continue;
                    queens[i].first = x, queens[i].second = y;
                    if (validate())
                    {
                        done = true;
                        goto print;
                    }
                }
                queens[i] = backup;
            }
        }

        print:
        if (!done) cout << "NO\n";
        else
        {
            memset(board, 0, sizeof(board));
            for (auto q : queens) board[q.first][q.second] = 1;
            cout << "YES\n";
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    cout << (board[i][j] ? 'X' : '0');
                cout << '\n';
            }
        }
    }

    return 0;
}
