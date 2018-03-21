// Playfair Cipher
// UVa ID: 11697
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[5][5];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases; cin.ignore(1024, '\n');

    for (int cs = 1; cs <= cases; cs++)
    {
        string key, text;
        getline(cin, key);
        getline(cin, text);
        
        int idx = 0;
        set<char> exist;
        for (auto letter : key)
        {
            if (isalpha(letter))
            {
                char c = toupper(letter);
                if (exist.find(c) != exist.end()) continue;
                exist.insert(c);
                board[idx / 5][idx % 5] = c;
                idx++;
            }
        }
        for (int i = 0; i < 26; i++)
        {
            char c = 'A' + i;
            if (c == 'Q') continue;
            if (exist.find(c) != exist.end()) continue;
            exist.insert(c);
            board[idx / 5][idx % 5] = c;
            idx++;
        }
        
        string next;
        for (auto letter : text)
            if (isalpha(letter))
                next += toupper(letter);

        for (int i = 0; i < next.length(); i++)
        {
            string block;
            int j = i + 1;
            if (j < next.length())
            {
                if (next[i] == next[j])
                {
                    block += next[i];
                    block += 'X';
                }
                else
                {
                    block += next[i];
                    block += next[j];
                    i++;
                }
            }
            else
            {
                block += next[i];
                block += 'X';
            }

            // Same row.
            bool encoded = false;
            for (int i = 0; i < 5; i++)
            {
                int cnt = 0, j1, j2;
                for (int j = 0; j < 5; j++)
                {
                    if (board[i][j] == block.front())
                    {
                        j1 = j;
                        cnt++;
                    }
                    if (board[i][j] == block.back())
                    {
                        j2 = j;
                        cnt++;
                    }
                }
                if (cnt == 2)
                {
                    cout << board[i][(j1 + 1) % 5] << board[i][(j2 + 1) % 5];
                    encoded = true;
                    break;
                }
            }
            
            // Same column.
            if (encoded) continue;
            for (int j = 0; j < 5; j++)
            {
                int cnt = 0, i1, i2;
                for (int i = 0; i < 5; i++)
                {
                    if (board[i][j] == block.front())
                    {
                        i1 = i;
                        cnt++;
                    }
                    if (board[i][j] == block.back())
                    {
                        i2 = i;
                        cnt++;
                    }
                }
                if (cnt == 2)
                {
                    cout << board[(i1 + 1) % 5][j] << board[(i2 + 1) % 5][j];
                    encoded = true;
                    break;
                }
            }
            
            if (encoded) continue;
            int i1, j1, i2, j2;
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                {
                    if (board[i][j] == block.front())
                        i1 = i, j1 = j;
                    if (board[i][j] == block.back())
                        i2 = i, j2 = j;
                }
            cout << board[i1][j2] << board[i2][j1];
        }
        cout << '\n';
    }

    return 0;
}
