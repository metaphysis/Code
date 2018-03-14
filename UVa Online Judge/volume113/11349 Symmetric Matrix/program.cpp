// Symmetric Matrix
// UVa ID: 11349
// Verdict: Accepted
// Submission Date: 2018-01-09
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    long long grid[110][110];
    char N, equal;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> equal >> n;
        
        bool safe = true;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] < 0) safe = false;
            }
                
        if (safe)
        {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n - i + 1; j++)
                {
                    int row = n + 1 - i;
                    int cln = n + 1 - j;
                    if (grid[i][j] != grid[row][cln])
                    {
                        safe = false;
                        goto result;
                    }
                }
        }

        result:
        cout << "Test #" << c << ": ";
        cout << (safe ? "Symmetric." : "Non-symmetric.") << '\n';
    }

    return 0;
}
