// Lost in Space
// UVa ID: 736
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    char board[64][64];
    int n, offset[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    string dirs[8] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
    string line, word;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cin >> n; cin.ignore(1024, '\n');
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            for (int j = 0; j < n; j++)
                board[i][j] = line[j];
        }

        while (getline(cin, word), word.length() > 0)
        {
            bool printed = false;
            cout << '\n' << word << '\n';
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    if (board[i][j] == word.front())
                    {
                        for (int k = 0; k < 8; k++)
                        {
                            bool same = true;
                            int nexti = i, nextj = j;
                            for (int l = 1; l < word.length(); l++)
                            {
                                nexti += offset[k][0], nextj += offset[k][1];
                                while (nexti >= 0 && nexti < n && nextj >= 0 && nextj < n && board[nexti][nextj] == ' ')
                                    nexti += offset[k][0], nextj += offset[k][1];
                                if (nexti >= 0 && nexti < n && nextj >= 0 && nextj < n && board[nexti][nextj] == word[l])
                                    continue;
                                same = false;
                                break;
                            }
                            if (same)
                            {
                                cout << '(' << (i + 1) << ',' << (j + 1) << ") - ";
                                cout << dirs[k] << '\n';
                                printed = true;
                            }
                        }
                    }
                }
            if (!printed) cout << "not found\n";
        }
    }

    return 0;
}
