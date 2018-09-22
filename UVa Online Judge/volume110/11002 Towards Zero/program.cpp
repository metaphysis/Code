// Towards Zero
// UVa ID: 11002
// Verdict: Accepted
// Submission Date: 2018-09-22
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, matrix[64][64], dp[64][64][6100];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        if (n == 0) break;

        int offset = 0;
        for (int L = 1, i = 0; L <= n; L++, i++)
            for (int j = 0; j < L; j++)
            {
                cin >> matrix[i][j];
                offset = max(offset, abs(matrix[i][j]));
            }
        for (int L = n - 1, i = n; L >= 1; L--, i++)
            for (int j = 0; j < L; j++)
            {
                cin >> matrix[i][j];
                offset = max(offset, abs(matrix[i][j]));
            }

        int top = 2 * (2 * n - 1) * offset;
        for (int L = 1, i = 0; L <= n; L++, i++)
            for (int j = 0; j < L; j++)
                for (int k = 0; k <= top + 2 * offset; k++)
                    dp[i][j][k] = 0;
        for (int L = n - 1, i = n; L >= 1; L--, i++)
            for (int j = 0; j < L; j++)
                for (int k = 0; k <= top + 2 * offset; k++)
                    dp[i][j][k] = 0;

        dp[0][0][matrix[2 * n - 2][0] + offset] = 1;

        for (int L = 1, i = 0, idx = 2 * n - 2; L < n; L++, i++, idx--)
            for (int j = 0; j < L; j++)
                for (int k = 0; k <= top; k++)
                    if (dp[i][j][k])
                    {
                        dp[i + 1][j][k + matrix[idx - 1][j] + offset] = 1;
                        dp[i + 1][j][k - matrix[idx - 1][j] + offset] = 1;
                        dp[i + 1][j + 1][k + matrix[idx - 1][j + 1] + offset] = 1;
                        dp[i + 1][j + 1][k - matrix[idx - 1][j + 1] + offset] = 1;
                    }

        for (int L = n - 1, i = n, idx = n - 2; L >= 1; L--, i++, idx--)
            for (int j = 0; j < L; j++)
                for (int k = 0; k <= top; k++)
                {
                    dp[i][j][k + matrix[idx][j] + offset] |= (dp[i - 1][j][k] | dp[i - 1][j + 1][k]);
                    dp[i][j][k - matrix[idx][j] + offset] |= (dp[i - 1][j][k] | dp[i - 1][j + 1][k]);
                }

        int zero = (2 * n - 1) * offset;
        for (int i = zero, j = zero, k = 0; ; i++, j--, k++)
            if (dp[2 * n - 2][0][i] || dp[2 * n - 2][0][j])
            {
                cout << k << '\n';
                break;
            }
    }

    return 0;
}
