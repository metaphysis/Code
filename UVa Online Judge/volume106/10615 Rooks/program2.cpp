// Rooks
// UVa ID: 10615
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

int n, M;
int board[MAXN][MAXN], RC[MAXN], CC[MAXN];

struct color
{
    int clrBothInRowAndCln, clrOnlyInRow, clrOnlyInCln;
};

color getAvailableColor(int r, int c)
{
    memset(RC, 0, sizeof RC);
    memset(CC, 0, sizeof CC);

    color clr = { 0, 0, 0 };

    for (int i = 0; i < n; i++)
    {
        if (board[r][i] >= 1)
            RC[board[r][i]]++;
        if (board[i][c] >= 1)
            CC[board[i][c]]++;
    }

    for (int i = 1; i <= M; i++)
    {
        if (RC[i] == 0 && CC[i] == 0)
            clr.clrBothInRowAndCln = i;
        else
        {
            if (RC[i] == 0)
                clr.clrOnlyInRow = i;
            else
            {
                if (CC[i] == 0)
                    clr.clrOnlyInCln = i;
            }
        }
    }

    return clr;
}

void render(int r, int c, int clrInRow, int clrInCln)
{
    board[r][c] = clrInRow;
    for (int i = 0; i < n; i++)
        if (i != r && board[i][c] == clrInRow)
        {
            board[i][c] = clrInCln;
            for (int j = 0; j < n; j++)
                if (j != c && board[i][j] == clrInCln)
                {
                    render(i, j, clrInRow, clrInCln);
                    break;
                }
            break;
        }
}

int main(int argc, char *argv[])
{
    int cases;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        M = 0;

        memset(RC, 0, sizeof RC);
        memset(CC, 0, sizeof CC);

        cin >> n;
        char c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                board[i][j] = 0;
                cin >> c;
                if (c == '*')
                {
                    board[i][j] = -1;
                    RC[i]++, CC[j]++;
                }
            }

        int SR = -1, SC = -1;
        for (int i = 0; i < n; i++)
        {
            if (M < RC[i])
                M = RC[i], SR = i, SC = -1;
            if (M < CC[i])
                M = CC[i], SR = -1, SC = i;
        }

        int colors = 1;
        if (SR != -1)
        {
            for (int i = 0; i < n; i++)
                if (board[SR][i] == -1)
                    board[SR][i] = colors++;
        }
        else if (SC != -1)
        {
            for (int i = 0; i < n; i++)
                if (board[i][SC] == -1)
                    board[i][SC] = colors++;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] = -1)
                {
                    color clr = getAvailableColor(i, j);
                    if (clr.clrBothInRowAndCln)
                        board[i][j] = clr.clrBothInRowAndCln;
                    else
                        render(i, j, clr.clrOnlyInRow, clr.clrOnlyInCln);

                }

        cout << M << '\n';
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j)
                    cout << ' ';
                cout << board[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
