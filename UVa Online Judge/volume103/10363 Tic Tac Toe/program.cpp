// Tic Tac Toe
// UVa ID: 10363
// Verdict: Accepted
// Submission Date: 2017-12-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    char g[3][3];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int sx = 0, so = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> g[i][j];
                if (g[i][j] == 'X') sx++;
                if (g[i][j] == 'O') so++;
            }
        }

        int wx = 0, wo = 0;

        for (int i = 0; i < 3; i++)
        {
            if (g[i][0] == g[i][1] && g[i][1] == g[i][2])
            {
                if (g[i][0] == 'X') wx++;
                if (g[i][0] == 'O') wo++;
            }
            if (g[0][i] == g[1][i] && g[1][i] == g[2][i])
            {
                if (g[0][i] == 'X') wx++;
                if (g[0][i] == 'O') wo++;
            }
        }

        if (g[0][0] == g[1][1] && g[1][1] == g[2][2])
        {
            if (g[0][0] == 'X') wx++;
            if (g[0][0] == 'O') wo++;
        }
        if (g[0][2] == g[1][1] && g[1][1] == g[2][0])
        {
            if (g[0][2] == 'X') wx++;
            if (g[0][2] == 'O') wo++;
        }

        if (sx > 5 || so > 4) { cout << "no\n"; continue; }
        if (sx != so && sx != so + 1) { cout << "no\n"; continue; }
        if (wx > 0 && wo > 0) { cout << "no\n"; continue; }
        if (sx == so && wx > 0) { cout << "no\n"; continue; }
        if (sx == so + 1 && wo > 0) { cout << "no\n"; continue; }

        cout << "yes\n";
    }

    return 0;
}
