// No Ball
// UVa ID: 13091
// Verdict: Accepted
// Submission Date: 2021-12-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char grid[5][5];

void judge()
{
    for (int i = 0; i < 5; i++)
    {
        int foot = -1, line = -1;
        for (int j = 0; j < 5; j++)
        {
            if (grid[i][j] == '>') foot = j;
            if (grid[i][j] == '<') foot = 10 + j;
            if (grid[i][j] == '|') line = j;
        }
        if (foot != -1)
        {
            if (foot < 10 && foot > line || foot >= 10 && line > (foot % 10)) cout << "No Ball\n";
            else cout << "Thik Ball\n";
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases; 
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                cin >> grid[i][j]; 
        judge();
    }

    return 0;
}
