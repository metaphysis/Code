// Treblecross
// UVa ID: 10561
// Verdict: Accepted
// Submission Date: 2018-06-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int sg[205], visited[256];

void grundy()
{
    sg[0] = 0;
    sg[1] = sg[2] = sg[3] = 1;
    for (int i = 4; i <= 200; i++)
    {
        memset(visited, 0, sizeof(visited));
        for (int j = 3; j <= 5; j++)
            if (j <= i)
                visited[sg[i - j]] = 1;
        for (int j = 1; j < i - 5; j++) visited[sg[j] ^ sg[i - j - 5]] = 1;
        for (int j = min(5, i); j >= 3; j--) visited[sg[i - j]] = 1;
        for (int j = 0; ; j++)
            if (!visited[j])
            {
                sg[i] = j;
                break;
            }
    }
}

int winable(string &s, int i)
{
    int r = 0;
    if (i + 2 <= s.length() - 1) r |= (s[i + 1] == 'X' && s[i + 2] == 'X');
    if (i > 0 && i < s.length() - 1) r |= (s[i - 1] == 'X' && s[i + 1] == 'X');
    if (i >= 2) r |= (s[i - 2] == 'X' && s[i - 1] == 'X');
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    grundy();

    int cases;
    string board;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> board;

        vector<int> outs;
        
        // Check if self have a chance to win.
        for (int i = 0; i < board.length(); i++)
        {
            if (board[i] == '.' && winable(board, i))
                outs.push_back(i + 1);
        }

        if (outs.size() == 0)
        {
            for (int i = 0; i < board.length(); i++)
            {
                if (board[i] == 'X') continue;
                // Check if the oppoent has a chance to win.
                board[i] = 'X';
                int stoped = 0;
                for (int j = i - 2; j <= i + 2; j++)
                {
                    if (j < 0 || j >= board.length()) continue;
                    if (board[j] == '.' && winable(board, j))
                    {
                        stoped = 1;
                        break;
                    }
                }
                if (stoped)
                {
                    board[i] = '.';
                    continue;
                }

                // Check if the state of board is N-position.
                int cnt = 0;
                vector<int> holes;
                if (board.front() == 'X') holes.push_back(0);
                for (auto c : board)
                {
                    if (c == '.') cnt++;
                    else
                    {
                        holes.push_back(cnt);
                        cnt = 0;
                    }
                }
                holes.push_back(cnt);
                if (board.back() == 'X') holes.push_back(0);
                board[i] = '.';

                int total = holes.size(), bit = 0;
                for (int i = 0; i < total; i++)
                {
                    if (i == 0 || i == total - 1)
                        bit ^= sg[max(0, holes[i] - 2)];
                    else
                        bit ^= sg[max(0, holes[i] - 4)];
                }
                if (!bit) outs.push_back(i + 1);
            }
        }

        if (outs.size() > 0)
        {
            cout << "WINNING\n";
            for (int i = 0; i < outs.size(); i++)
            {
                if (i) cout << ' ';
                cout << outs[i];
            }
            cout << '\n';
        }
        else cout << "LOSING\n\n";
    }

    return 0;
}
