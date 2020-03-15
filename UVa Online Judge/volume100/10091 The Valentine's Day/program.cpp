// The Valentine's Day
// UVa ID: 10091
// Verdict: Accepted
// Submission Date: 2020-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double A[26][150], B[26][150];
    int g[26][26], neighboring[26], R;
    int Y, M, D;
    char city1, city2;

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> Y >> M >> D;
        int m1 = (Y - 1) * 12 + M;
        int m2 = (Y - 1) * 12 + 2;
        int m3 = Y * 12 + 2;
        int months = (m1 <= m2 ? m2 - m1 : m3 - m1);
        if (M == 2)
        {
            if (D >= 14) months = 12;
            else months = 0;
        }
        if (Y < 470) months = (469 * 12 + 2) - ((Y - 1) * 12 + M);

        cin >> R;
        memset(g, 0, sizeof g);
        for (int r = 1; r <= R; r++)
        {
            cin >> city1 >> city2;
            g[city1 - 'A'][city2 - 'A'] = g[city2 - 'A'][city1 - 'A'] = 1;
        }
        for (int i = 0; i < 26; i++)
        {
            neighboring[i] = 0;
            for (int j = 0; j < 26; j++)
                if (i != j && g[i][j])
                    neighboring[i]++;
        }
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 150; j++)
                A[i][j] = B[i][j] = 0;
        cin >> city1 >> city2;
        A[city1 - 'A'][0] = B[city2 - 'A'][0] = 1.0;

        for (int d = 1; d <= months; d++)
            for (int i = 0; i < 26; i++)
            {
                A[i][d] += A[i][d - 1] / (neighboring[i] + 1);
                B[i][d] += B[i][d - 1] / (neighboring[i] + 1);
                for (int j = 0; j < 26; j++)
                    if (i != j && g[i][j])
                    {
                        A[i][d] += A[j][d - 1] / (neighboring[j] + 1);
                        B[i][d] += B[j][d - 1] / (neighboring[j] + 1);
                    }
            }
        double probability = 0;
        for (int i = 0; i < 26; i++) probability += A[i][months] * B[i][months];
        cout << fixed << setprecision(5) << probability << '\n';
    }

    return 0;
}
