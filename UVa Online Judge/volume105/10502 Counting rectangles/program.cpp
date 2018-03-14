// Counting rectangles
// UVa ID: 10502
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grid[110][110], md[110][110];
    int n, m;
    
    while (cin >> n, n > 0)
    {
        cin >> m;
        
        char v;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> v;
                grid[i][j] = v - '0';
            }

        memset(md, 0, sizeof(md));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                md[i][j] = md[i - 1][j] + md[i][j - 1] - md[i - 1][j - 1] + grid[i][j];
                
        int count = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int h = 0; h <= n - i; h++)
                    for (int w = 0; w <= m - j; w++)
                        if ((h + 1) * (w + 1) == md[i + h][j + w] - md[i - 1][j + w] - md[i + h][j - 1] + md[i - 1][j - 1])
                            count++;
            
        cout << count << '\n';
    }
    
    return 0;
}
