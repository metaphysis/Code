// Not That Kind of Graph
// UVa ID: 10800
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;
    char board[128][64];
    map<char, char> graph = {{'R', '/'}, {'F', '\\'}, {'C', '_'}};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;

        int up = 60, down = 60, row = 60, cln = 2;
        memset(board, ' ', sizeof(board));
        board[row][cln] = graph[line.front()];
        for (int i = 1; i < line.length(); i++)
        {
            if (line[i - 1] == 'R' && (line[i] == 'R' || line[i] == 'C')) row -= 1;
            if (line[i - 1] == 'F' && line[i] == 'F') row += 1;
            if (line[i - 1] == 'C' && line[i] == 'F') row += 1;
            cln += 1;
            board[row][cln] = graph[line[i]];
            up = min(up, row), down = max(down, row);
        }

        for (int i = up; i <= down; i++) board[i][0] = '|';
        board[down + 1][0] = '+';
        for (int i = 1; i <= line.length() + 2; i++) board[down + 1][i] = '-';

        cout << "Case #" << c << ":\n";
        for (int i = up; i <= down + 1; i++)
        {
            for (int j = 60; j >= 0; j--)
            {
                if (board[i][j] != ' ') break;
                board[i][j] = '0';
            }
            for (int j = 0; j <= 60; j++)
            {
                if (board[i][j] == '0') break;
                cout << board[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
