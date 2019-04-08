// Find the Winning Move
// UVa ID: 10111
// Verdict: Accepted
// Submission Date: 2018-06-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int X = 0, O = 1, X_WIN = 0, X_LOSE = 1, O_WIN = 2, O_LOSE = 3;

string bits[] = {
    "1111000000000000", "0000111100000000", "0000000011110000",
    "0000000000001111", "1000100010001000", "0100010001000100",
    "0010001000100010", "0001000100010001", "1000010000100001",
    "0001001001001000"
};

int wins[10], mask = 0xffff;
int board, empty[16], used[16] = {}, total = 0, cnt = 0;

set<int> Ps, Ns;

inline bool isWin(int key)
{
    for (int i = 0; i < 10; i++)
        if ((key & wins[i]) == wins[i])
            return true;
    return false;
}

int dfs(int player)
{
    if (player == X)
    {
        if (Ps.find(board) != Ps.end()) return X_WIN;
        if (Ns.find(board) != Ns.end()) return X_LOSE;
    }

    if (player == X && isWin(board & mask)) return X_LOSE;
    if (player == O && isWin(board >> 16)) return O_LOSE;

    for (int i = 0; i < total; i++)
        if (!used[i])
        {
            used[i] = 1;
            if (player == X) board |= (1 << (16 + empty[i]));
            else board |= (1 << empty[i]);

            int next = dfs(1 - player);

            if (player == X) board ^= (1 << (16 + empty[i]));
            else board ^= (1 << empty[i]);
            used[i] = 0;

            if (player == X && next == O_LOSE)
            {
                Ps.insert(board);
                return X_WIN;
            }
            if (player == O && next == X_LOSE)
            {
                return O_WIN;
            }
        }

    if (player == X)
    {
        Ns.insert(board);
        return X_LOSE;
    }
    else return O_LOSE;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i < 10; i++)
    {
        bitset<16> binary(bits[i]);
        wins[i] = (int)(binary.to_ulong());
    }
    
    char piece;
    while (cin >> piece, piece != '$')
    {
        if (piece != '?') continue;

        board = cnt = total = 0;
        while (cnt < 16)
        {
            cin >> piece;
            if (piece != '.' && piece != 'x' && piece != 'o') continue;
            if (piece == '.') empty[total++] = cnt;
            else if (piece == 'x') board |= (1 << (16 + cnt));
            else board |= (1 << cnt);
            cnt++;
        }

        bool flag = false;
        memset(used, 0, sizeof(used));
        for (int i = 0; i < total; i++)
        {
            used[i] = 1;
            board |= (1 << (16 + empty[i]));
            if (dfs(O) == O_LOSE)
            {
                cout << '(' << empty[i] / 4 << ',' << empty[i] % 4 << ")\n";
                flag = true;
                break;
            }
            board ^= (1 << (16 + empty[i]));
            used[i] = 0;
        }
        if (!flag) cout << "#####\n";
    }

    return 0;
}
