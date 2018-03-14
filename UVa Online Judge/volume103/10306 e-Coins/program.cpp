// e-Coins
// UVa ID: 10306
// Verdict: Accepted
// Submission Date: 2018-01-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    const int INF = 0x3fffffff;
    int cases, m, S, minimum[310][310], normal[50], logical[50];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {   
        cin >> m >> S;
        for (int i = 0; i < m; i++)
            cin >> normal[i] >> logical[i];

        for (int i = 0; i <= S; i++)
            for (int j = 0; j <= S; j++)
                minimum[i][j] = INF;

        minimum[0][0] = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j <= S; j++)
                for (int k = 0; k <= S; k++)
                {
                    int nextn = j + normal[i], nextl = k + logical[i];
                    if (nextn > S || nextl > S) continue;
                    minimum[nextn][nextl] = min(minimum[nextn][nextl], minimum[j][k] + 1);
                }

        int smallest = INF;
        for (int i = 0; i <= S; i++)
            for (int j = 0; j <= S; j++)
                if (i * i + j * j == S * S)
                    smallest = min(smallest, minimum[i][j]);

        if (smallest < INF) cout << smallest << '\n';
        else cout << "not possible\n";
    }

    return 0;
}
