// Maximum sum on a torus
// UVa ID: 10827
// Verdict: Accepted
// Submission Date: 2017-11-04
// UVa Run Time: 0.260s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3fffffff;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int matrix[80][80], md[80][80], n, cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];

        memset(md, 0, sizeof(md));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                md[i][j] = md[i][j - 1] + md[i - 1][j] - md[i - 1][j - 1] + matrix[i][j];

        int area = -INF;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int h = 0; h <= n - i; h++)
                    for (int w = 0; w <= n - j; w++)
                    {
                        int s1 = md[i + h][n] - md[i - 1][n];
                        int s2 = md[n][j + w] - md[n][j - 1];
                        int s3 = md[i + h][j + w] - md[i - 1][j + w] - md[i + h][j - 1] + md[i - 1][j - 1];

                        if (w < n - j) area = max(area, s1 - s3);
                        if (h < n - i) area = max(area, s2 - s3);

                        area = max(area, max(max(s1, s2), s3));

                        int s4 = md[n][n] - s1 - s2 + s3;
                        if (w < n - j && h < n - i) area = max(area, s4);
                    }

        cout << area << '\n';
    }

	return 0;
}
