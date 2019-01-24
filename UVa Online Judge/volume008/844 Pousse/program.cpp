// Pousse
// UVa ID: 844
// Verdict: Accepted
// Submission Date: 2019-01-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int board[110][110];

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int N;
        cin >> N;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                board[i][j] = -1;
                
        bool xwin = false, owin = false;
        int player = 0;
        string command;
        while (cin >> command)
        {
            if (command == "QUIT") break;
            if (xwin || owin) continue;

            int n = stoi(command.substr(1));
            if (command.front() == 'L')
            {
                int empty = N;
                for (int i = 1; i <= N; i++)
                    if (board[n][i] == -1)
                    {
                        empty = i;
                        break;
                    }
                for (int i = empty; i > 1; i--)
                    board[n][i] = board[n][i - 1];
                board[n][1] = player;
            }
            else if (command.front() == 'R')
            {
                int empty = 1;
                for (int i = N; i >= 1; i--)
                    if (board[n][i] == -1)
                    {
                        empty = i;
                        break;
                    }
                for (int i = empty; i < N; i++)
                    board[n][i] = board[n][i + 1];
                board[n][N] = player;
            }
            else if (command.front() == 'T')
            {
                int empty = N;
                for (int i = 1; i <= N; i++)
                    if (board[i][n] == -1)
                    {
                        empty = i;
                        break;
                    }
                for (int i = empty; i > 1; i--)
                    board[i][n] = board[i - 1][n];
                board[1][n] = player;
            }
            else
            {
                int empty = 1;
                for (int i = N; i >= 1; i--)
                    if (board[i][n] == -1)
                    {
                        empty = i;
                        break;
                    }
                for (int i = empty; i < N; i++)
                    board[i][n] = board[i + 1][n];
                board[N][n] = player;
            }
            
            int xcnt = 0, ocnt = 0;
            for (int i = 1; i <= N; i++)
            {
                if (board[i][1] != -1)
                {
                    bool same = true;
                    for (int j = 2; j <= N; j++)
                        if (board[i][j] != board[i][1])
                        {
                            same = false;
                            break;
                        }
                    if (same)
                    {
                        if (board[i][1] == 0) xcnt++;
                        else ocnt++;
                    }
                }
                
                if (board[1][i] != -1)
                {
                    bool same = true;
                    for (int j = 2; j <= N; j++)
                        if (board[j][i] != board[1][i])
                        {
                            same = false;
                            break;
                        }
                    if (same)
                    {
                        if (board[1][i] == 0) xcnt++;
                        else ocnt++;
                    }
                }
            }

            if (xcnt > ocnt) xwin = true;
            if (xcnt < ocnt) owin = true;
            player = 1 - player;
        }

        if (cs > 1) cout << '\n';
        if (xwin) cout << "X WINS\n";
        else if (owin) cout << "O WINS\n";
        else cout << "TIE GAME\n";
    }

    return 0;
}
