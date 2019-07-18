// Undraw the Trees
// UVa ID: 10562
// Verdict: Accepted
// Submission Date: 2019-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210;

int lines = 0;
char grid[MAXN][MAXN];

bool isNode(char c)
{
    return c != '|' && c != '-' && c != ' ' && c != '\n' && c != '#';
}

void dfs(int row, int cln)
{
    cout << grid[row][cln];
    cout << '(';
    if (row + 1 < lines && grid[row + 1][cln] == '|')
    {
        int c = cln;
        while (grid[row + 2][c] == '-') c--;
        for (int i = c + 1; i < MAXN && grid[row + 2][i] == '-'; i++)
            if (isNode(grid[row + 3][i]))
                dfs(row + 3, i);
    }
    cout << ')';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    cin.ignore(256, '\n');
    for (int cs = 1; cs <= cases; cs++)
    {
        memset(grid, '\n', sizeof(grid));
        string line;
        lines = 0;
        while (getline(cin, line))
        {
            if (line.front() == '#') break;
            for (int i = 0; i < line.length(); i++)
                grid[lines][i] = line[i];
            lines++;
        }
        int row = -1, cln = -1;
        for (int i = 0; i < lines; i++)
            for (int j = 0; j < MAXN; j++)
                if (isNode(grid[i][j]))
                {
                    row = i;
                    cln = j;
                    i = j = MAXN;
                }
        cout << '(';
        if (row != -1) dfs(row, cln);
        cout << ")\n";
    }

    return 0;
}
