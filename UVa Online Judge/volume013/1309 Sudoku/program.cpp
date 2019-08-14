// Sudoku
// UVa ID: 1309
// Verdict: TLE
// Submission Date: 2019-08-14
// UVa Run Time: 3.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct DATA
{
    int row, cln, block;
    DATA (int row = 0, int cln = 0, int block = 0): row(row), cln(cln), block(block) {}
} mask[20];
char grid[20][20];
vector<DATA> dash;

int getIndex(int bit)
{
    for (int idx = 0; idx < 16; idx++)
        if (bit == (1 << idx))
            return idx;
}

bool dfs(int depth)
{
    if (depth == dash.size())
    {
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
                cout << grid[i][j];
            cout << '\n';
        }
        return true;
    }
    int i = dash[depth].row, j = dash[depth].cln, k = (i / 4) * 4 + j / 4;
    int used = mask[i].row | mask[j].cln | mask[k].block;
    int available = ((1 << 16) - 1) & (~used);
    while (available) {
        int bit = available & (~available + 1);
        if (mask[i].row & bit) continue;
        if (mask[j].cln & bit) continue;
        if (mask[k].block & bit) continue;
        available ^= bit;
        mask[i].row |= bit, mask[j].cln |= bit, mask[k].block |= bit;
        grid[i][j] = 'A' + getIndex(bit);
        if (dfs(depth + 1)) return true;
        mask[i].row ^= bit, mask[j].cln ^= bit, mask[k].block ^= bit;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char letter;
    int cases = 0;
    while (cin >> letter)
    {
        cin.putback(letter);
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                cin >> grid[i][j];
        memset(mask, 0, sizeof(mask));
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                if (grid[i][j] != '-')
                {
                    int bit = grid[i][j] - 'A';
                    mask[i].row |= (1 << bit);
                    mask[j].cln |= (1 << bit);
                    mask[(i / 4) * 4 + j / 4].block |= (1 << bit);
                }
        dash.clear();
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                if (grid[i][j] == '-')
                    dash.push_back(DATA(i, j, mask[i].row | mask[j].cln | mask[(i / 4) * 4 + j / 4].block));
        if (cases++) cout << '\n';
        dfs(0);
    }
    return 0;
}
