// Find the Winning Move
// UVa ID: 10111
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int X_MOVE = 0, O_MOVE = 1;

string bits[] = {
    "1111000000000000", "0000111100000000", "0000000011110000", "0000000000001111",
    "1000100010001000", "0100010001000100", "0010001000100010", "0001000100010001",
    "1000010000100001", "0001001001001000"
};

int status[10], mask = 0xff;
int board, empty[16], used[16], total = 0, cnt = 0;

set<int> win, lose;

bool dfs(int move)
{
    for (int i = 0; i < 10; i++)
    {
        if (status == (board >> 16))
        {
            win.insert(board);
            return true;
        }
        if (status == (board & mask))
        {
            lose.insert(board);
            return false;
        }
    }
    
    for (int i = 0; i < total; i++)
        if (!used[i])
        {
            used[i] = 1;
            if (move == X_MOVE)
                board |= (1 << (15 + empty[i]));
            else
                board |= (1 << empty[i]);
            
            if (dfs(1 - move)) return true;
            if (move == X_MOVE)
                board ^= (1 << (15 + empty[i]));
            else
                board ^= (1 << empty[i]);
            used[i] = 0;
        }
        
    lose.insert(board);
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i < 10; i++)
    {
        bitset<32> binary(bits[i]);
        status[i] = binary.to_ulong();
    }
    
    char piece;
    while (cin >> piece, piece != '$')
    {
        if (piece != '?') continue;

        win.clear(); lose.clear();
        board = cnt = total = 0;
        while (cnt < 16)
        {
            cin >> piece;
            if (piece != '.' && piece != 'x' && piece != 'o') continue;
            if (piece == '.') empty[total++] = cnt;
            else if (piece == 'x') board |= (1 << (15 + cnt));
            else board |= (1 << cnt);
            cnt++;
        }

        bool found = false;
        for (int i = 0; i < total; i++)
        {
            used[i] = 1;
            board |= (1 << (15 + empty[i]));
            if (dfs(O_MOVE))
            {
                cout << '(' << empty[i] / 4 << ',' << empty[i] % 4 << ")\n";
                found = true;
            }
            board ^= (1 << (15 + empty[i]));
            used[i] = 0;
        }
        if (!found)
            cout << "####\n";
    }

    return 0;
}
