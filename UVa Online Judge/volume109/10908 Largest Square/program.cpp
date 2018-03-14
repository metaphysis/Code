// Largest Square
// UVa ID: 10908
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int m, n, q, grid[110][110], md[110][110];
    int r, c;
    char v;

    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> m >> n >> q;
        
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> v;
                grid[i][j] = v;
            }
            
        memset(md, 0, sizeof(md));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                md[i][j] = md[i - 1][j] + md[i][j - 1] - md[i - 1][j - 1] + grid[i][j];
                
        cout << m << ' ' << n << ' ' << q << '\n';
        for (int k = 1; k <= q; k++)
        {
            cin >> r >> c;
            r++, c++;

            int w = 1;
            while (true)
            {
                if (r + w > m || r - w < 1 || c + w > n || c - w < 1) break;
                int sum1 = grid[r][c] * (2 * w + 1) * (2 * w + 1);
                int sum2 = md[r + w][c + w] - md[r - w - 1][c + w] - md[r + w][c - w - 1] + md[r - w - 1][c - w - 1];
                if (sum1 != sum2) break;
                
                bool flag = true;
                for (int i = r - w; i <= r + w; i++)
                    for (int j = c - w; j <= c + w; j++)
                        if (grid[i][j] != grid[r][c])
                        {
                            flag = false;
                            break;
                        }
                
                if (!flag) break;
                w++;
            }
            cout << (2 * (w - 1) + 1) << '\n';
        }
    }
    
    return 0;
}
