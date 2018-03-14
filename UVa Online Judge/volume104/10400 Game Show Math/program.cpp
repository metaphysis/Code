// Game Show Math
// UVa ID: 10400
// Verdict: Accepted
// Submission Date: 2018-01-17
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int OFFSET = 32000, UP = 64000;

int cases, n, t, numbers[110];
int dp[110][UP + 10], track[110][UP + 10][2];
    
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> numbers[i];
        cin >> t;

        for (int i = 0; i < n; i++)
            for (int j = 0; j <= UP; j++)
                dp[i][j] = 0;

        dp[0][numbers[0] + OFFSET] = 1;
        for (int i = 1; i < n; i++)
            for (int j = 1; j < UP; j++)
            {
                int k = j - OFFSET;
                if (dp[i - 1][j])
                {
                    if (abs(k + numbers[i]) < OFFSET) 
                    {
                        dp[i][k + numbers[i] + OFFSET] = 1;
                        track[i][k + numbers[i] + OFFSET][0] = 0;
                        track[i][k + numbers[i] + OFFSET][1] = j;
                    }
                    if (abs(k - numbers[i]) < OFFSET)
                    {
                        dp[i][k - numbers[i] + OFFSET] = 1;
                        track[i][k - numbers[i] + OFFSET][0] = 1;
                        track[i][k - numbers[i] + OFFSET][1] = j;
                    }
                    if (abs(k * numbers[i]) < OFFSET)
                    {
                        dp[i][k * numbers[i] + OFFSET] = 1;
                        track[i][k * numbers[i] + OFFSET][0] = 2;
                        track[i][k * numbers[i] + OFFSET][1] = j;
                    }
                    if (k % numbers[i] == 0 && abs(k / numbers[i]) < OFFSET)
                    {
                        dp[i][k / numbers[i] + OFFSET] = 1;
                        track[i][k / numbers[i] + OFFSET][0] = 3;
                        track[i][k / numbers[i] + OFFSET][1] = j;
                    }
                }
            }

        if (dp[n - 1][t + OFFSET])
        {
            string operators = "+-*/";
            vector<char> ops;
            for (int i = n - 1, j = t + OFFSET; i >= 1; i--)
            {
                ops.insert(ops.begin(), operators[track[i][j][0]]);
                j = track[i][j][1];
            }
            for (int i = 0; i < n; i++)
            {
                cout << numbers[i];
                if (i < n - 1) cout << ops[i];
            }
            cout << '=' << t << '\n';
        }
        else cout << "NO EXPRESSION\n";
    }

    return 0;
}
