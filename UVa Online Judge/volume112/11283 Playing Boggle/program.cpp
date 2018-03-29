// Playing Boggle
// UVa ID: 11283
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[4][4];
string word;
int visited[4][4];

bool dfs(int ii, int jj, int kk)
{
    if (kk == word.length()) return true;
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
        {
            int nexti = ii + x, nextj = jj + y;
            if (nexti >= 0 && nexti < 4 && nextj >= 0 && nextj < 4)
            {
                if (!visited[nexti][nextj] && board[nexti][nextj] == word[kk])
                {
                    visited[nexti][nextj] = 1;
                    if (dfs(nexti, nextj, kk + 1))
                        return true;
                    visited[nexti][nextj] = 0;
                }
            }
        }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                cin >> board[i][j];
        cin >> n;
        int scores = 0;
        for (int w = 0; w < n; w++)
        {
            cin >> word;
            memset(visited, 0, sizeof(visited));
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (board[i][j] == word.front())
                    {
                        visited[i][j] = 1;
                        if (dfs(i, j, 1))
                        {
                            if (word.length() == 3 || word.length() == 4) scores += 1;
                            else if (word.length() == 5) scores += 2;
                            else if (word.length() == 6) scores += 3;
                            else if (word.length() == 7) scores += 5;
                            else scores += 11;
                            // Count the word once!
                            goto outer;
                        }    
                        visited[i][j] = 0;
                    }
            outer:
            continue;
        }
        cout << "Score for Boggle game #" << c << ": " << scores << '\n';
    }

    return 0;
}
