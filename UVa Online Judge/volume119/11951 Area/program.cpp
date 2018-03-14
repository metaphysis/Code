// Area
// UVa ID: 11951
// Verdict: Accepted
// Submission Date: 2017-11-04
// UVa Run Time: 0.340s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x3fffffffffffffff;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long matrix[110][110], md[110][110], m, n, k, cases, area, cost;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> m >> n >> k;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];

        memset(md, 0, sizeof(md));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                md[i][j] = md[i][j - 1] + md[i - 1][j] - md[i - 1][j - 1] + matrix[i][j];

        area = 0, cost = k;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                for (int h = 0; h <= m - i; h++)
                    for (int w = 0; w <= n - j; w++)
                    {
                        if ((h + 1) * (w + 1) < area) continue;
                        int s = md[i + h][j + w] - md[i + h][j - 1] - md[i - 1][j + w] + md[i - 1][j - 1];
                        if (((h + 1) * (w + 1) > area && s <= k) || ((h + 1) * (w + 1) == area && s < cost))
                        {
                            area = (h + 1) * (w + 1);
                            cost = s;
                        }
                    }
            }

        cout << "Case #" << c << ": ";
        cout << area << ' ' << (area > 0 ? cost : 0) << '\n';
    }

	return 0;
}
