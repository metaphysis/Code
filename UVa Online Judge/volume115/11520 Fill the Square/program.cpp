// Fill the Square
// UVa ID: 11520
// Verdict: Accepted
// Submission Date: 2018-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char grid[11][11];
    int cases, n, offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];
                
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (grid[i][j] == '.')
                {
                    for (int k = 0; k < 26; k++)
                    {
                        bool equal = false;
                        for (int z = 0; z < 4; z++)
                        {
                            int nexti = i + offset[z][0], nextj = j + offset[z][1];
                            if (nexti >= 1 && nexti <= n && nextj >= 1 && nextj <= n)
                            {
                                if (grid[nexti][nextj] == (k + 'A'))
                                {
                                    equal = true;
                                    break;
                                }
                            }
                        }
                        if (!equal) 
                        {
                            grid[i][j] = 'A' + k;
                            break;
                        }
                    }
                }
                
        cout << "Case " << c << ":\n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                cout << grid[i][j];
            cout << '\n';
        }
    }

    return 0;
}
