// Sudoku
// UVa ID: 13115
// Verdict: Accepted
// Submission Date: 2019-04-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grid[32][32], cnt[32];
    int n, cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        bool yes = true;
        for (int i = 0; i < n; i++)
        {
            memset(cnt, 0, sizeof(cnt));
            for (int j = 0; j < n; j++)
                cnt[grid[i][j]]++;
            for (int j = 1; j <= n; j++)
                if (cnt[j] != 1)
                {
                    yes = false;
                    i = n;
                    break;
                }
        }
        if (yes)
        {
            for (int i = 0; i < n; i++)
            {
                memset(cnt, 0, sizeof(cnt));
                for (int j = 0; j < n; j++)
                    cnt[grid[j][i]]++;
                for (int j = 1; j <= n; j++)
                    if (cnt[j] != 1)
                    {
                        yes = false;
                        i = n;
                        break;
                    }
            }
        }
        if (yes)
        {
            int nn = sqrt(n);
            for (int k = 0; k < n; k++)
            {
                memset(cnt, 0, sizeof(cnt));
                int offsetx = k / nn, offsety = k % nn;
                for (int i = 0; i < nn; i++)
                    for (int j = 0; j < nn; j++)
                        cnt[grid[i + nn * offsetx][j + nn * offsety]]++;
                for (int j = 1; j <= n; j++)
                    if (cnt[j] != 1)
                    {
                        yes = false;
                        k = n;
                        break;
                    }
            }
        }
        
        cout << (yes ? "yes" : "no") << '\n';
    }

    return 0;
}
