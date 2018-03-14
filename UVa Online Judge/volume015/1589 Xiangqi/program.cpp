// Xiangqi
// UVa ID: 1589
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int offset[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int horse[8][2] = {{-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}};
int n, blackr, blackc, piecer, piecec;
char backup[12][12], board[12][12], piece;

bool isCheckmate()
{
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 9; j++)
        {
            if (board[i][j] == 'G')
            {
                for (int k = i - 1; k >= 1; k--)
                    if (board[k][j])
                    {
                        if (board[k][j] == 'B') return true;
                        break;
                    }
            }
            if (board[i][j] == 'R')
            {
                if (j >= 4 && j <= 6)
                {
                    for (int k = i - 1; k >= 1; k--)
                        if (board[k][j])
                        {
                            if (board[k][j] == 'B') return true;
                            break;
                        }
                    for (int k = i + 1; k <= 10; k++)
                        if (board[k][j])
                        {
                            if (board[k][j] == 'B') return true;
                            break;
                        }  
                }
                if (i >= 1 && i <= 3)
                {
                    for (int k = j - 1; k >= 1; k--)
                        if (board[i][k])
                        {
                            if (board[i][k] == 'B') return true;
                            break;
                        }
                    for (int k = j + 1; k <= 9; k++)
                        if (board[i][k])
                        {
                            if (board[i][k] == 'B') return true;
                            break;
                        }
                }
            }
            if (board[i][j] == 'H')
            {
                for (int k = 0; k < 8; k++)
                {
                    int nexti = i + horse[k][0], nextj = j + horse[k][1];
                    if (nexti >= 1 && nexti <= 10 && nextj >= 1 && nextj <= 9)
                    {
                        int hobblingi = i + offset[k / 2][0], hobblingj = j + offset[k / 2][1];
                        if (board[hobblingi][hobblingj]) continue;
                        if (board[nexti][nextj] == 'B') return true;
                    }
                }
            }
            if (board[i][j] == 'C')
            {
                if (j >= 4 && j <= 6)
                {
                    for (int k = i - 1; k >= 1; k--)
                    {
                        if (board[k][j])
                        {
                            for (int l = k - 1; l >= 1; l--)
                                if (board[l][j])
                                {
                                    if (board[l][j] == 'B') return true;
                                    break;
                                }
                            break;
                        }
                    }
                    for (int k = i + 1; k <= 10; k++)
                    {
                        if (board[k][j])
                        {
                            for (int l = k + 1; l <= 10; l++)
                            {
                                if (board[l][j])
                                {
                                    if (board[l][j] == 'B') return true;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                if (i >= 1 && i <= 3)
                {
                    for (int k = j - 1; k >= 1; k--)
                    {
                        if (board[i][k])
                        {
                            for (int l = k - 1; l >= 1; l--)
                            {
                                if (board[i][l])
                                {
                                    if (board[i][l] == 'B') return true;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    for (int k = j + 1; k <= 9; k++)
                    {
                        if (board[i][k])
                        {
                            for (int l = k + 1; l <= 9; l++)
                            {
                                if (board[i][l])
                                {
                                    if (board[i][l] == 'B') return true;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
            
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> blackr >> blackc, n > 0)
    {
        memset(backup, 0, sizeof(backup));
        for (int i = 0; i < n; i++)
        {
            cin >> piece >> piecer >> piecec;
            backup[piecer][piecec] = piece;
        }

        bool safe = false;
        for (int k = 0; k < 4; k++)
        {
            int nexti = blackr + offset[k][0], nextj = blackc + offset[k][1];
            if (nexti >= 1 && nexti <= 3 && nextj >= 4 && nextj <= 6)
            {
                memcpy(board, backup, sizeof(backup));
                board[blackr][blackc] = 0;
                board[nexti][nextj] = 'B';
                if (!isCheckmate())
                {
                    safe = true;
                    break;
                }
            }
        }

        if (safe) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
