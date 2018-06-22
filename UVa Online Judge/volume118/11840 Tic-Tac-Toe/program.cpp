// Tic-Tac-Toe
// UVa ID: 11840
// Verdict: Accepted
// Submission Date: 2018-06-22
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int sg[10001], visited[512];

void grundy()
{
    sg[0] = 0;
    sg[1] = sg[2] = sg[3] = 1;
    for (int i = 4; i <= 10000; i++)
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

    int n;
    string board;
    while (cin >> n, n > 0)
    {
        cin >> board;

        // Check if self have a chance to win.
        int win = 0;
        for (int i = 0; i < board.length(); i++)
        {
            if (board[i] == '.' && winable(board, i))
            {
                win = 1;
                break;
            }
        }
        if (win)
        {
            cout << "S\n";
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

        int bit = 0;
        if (holes.size() == 1) bit ^= sg[holes.front()];
        else
        {
            int total = holes.size();
            for (int i = 0; i < total; i++)
            {
                if (i == 0 || i == total - 1)
                    bit ^= sg[max(0, holes[i] - 2)];
                else
                    bit ^= sg[max(0, holes[i] - 4)];
            }
        }
        cout << (bit ? 'S' : 'N') << '\n';
    }

    return 0;
}
