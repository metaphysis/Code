// Rock, Scissors, Paper
// UVa ID: 10443
// Verdict: Accepted
// Submission Date: 2017-12-25
// UVa Run Time: 0.280s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

inline char getResult(char c1, char c2)
{
    if (c1 == '0') return c2;
    if (c2 == '0') return c1;

    if (c1 == 'R')
    {
        if (c2 == 'R') return 'R';
        if (c2 == 'S') return 'R';
        if (c2 == 'P') return 'P';
    }
    else if (c1 == 'S')
    {
        if (c2 == 'R') return 'R';
        if (c2 == 'S') return 'S';
        if (c2 == 'P') return 'S';
    }
    else
    {
        if (c2 == 'R') return 'P';
        if (c2 == 'S') return 'S';
        if (c2 == 'P') return 'P';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    char cell1[110][110], cell2[110][110];
    int r, c, n;

    for (int cs = 1; cs <= cases; cs++)
    {
        if (cs > 1) cout << '\n';

        cin >> r >> c >> n;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                cin >> cell1[i][j];
                
        static int r1, c1;
        static char s1, s2, s3, s4;

        for (int d = 1; d <= n; d++)
        {
            for (int i = 1; i <= r; i++)
                for (int j = 1; j <= c; j++)
                {
                    r1 = i - 1, c1 = j;
                    if (r1 >= 1 && r1 <= r && c1 >= 1 && c1 <= c)
                        s1 = getResult(cell1[r1][c1], cell1[i][j]);
                    else
                        s1 = '0';
                    
                    r1 = i + 1, c1 = j;
                    if (r1 >= 1 && r1 <= r && c1 >= 1 && c1 <= c)
                        s2 = getResult(cell1[r1][c1], cell1[i][j]);
                    else
                        s2 = '0';
                    
                    r1 = i, c1 = j - 1;
                    if (r1 >= 1 && r1 <= r && c1 >= 1 && c1 <= c)
                        s3 = getResult(cell1[r1][c1], cell1[i][j]);
                    else
                        s3 = '0';
                    
                    r1 = i, c1 = j + 1;
                    if (r1 >= 1 && r1 <= r && c1 >= 1 && c1 <= c)
                        s4 = getResult(cell1[r1][c1], cell1[i][j]);
                    else
                        s4 = '0';

                    cell2[i][j] = getResult(getResult(s1, s2), getResult(s3, s4));
                    cell2[i][j] = getResult(cell2[i][j], cell1[i][j]);
                }

            for (int i = 1; i <= r; i++)
                for (int j = 1; j <= c; j++)
                    cell1[i][j] = cell2[i][j];
        }
        
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
                cout << cell1[i][j];
            cout << '\n';
        }
    }

    return 0;
}
