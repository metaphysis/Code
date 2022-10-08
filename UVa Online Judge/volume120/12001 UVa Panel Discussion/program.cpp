// UVa Panel Discussion
// UVa ID: 12001
// Verdict: Accepted
// Submission Date: 2022-10-08
// UVa Run Time: 0.240s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, M, P[64];
    while (cin >> N >> M, N)
    {
        memset(P, 0, sizeof P);
        for (int i = 1, c; i <= N; i++)
        {
            cin >> c;
            P[c]++;
        }

        sort(P + 1, P + M + 1);
        int start = 1;
        while (!P[start]) start++;

        long long r1 = 0;
        // all of them must be of the same country
        for (int i = start; i <= M; i++)
        {
            if (P[i] < 3) continue;
            r1 += P[i] * (P[i] - 1) * (P[i] - 2) / 6;
        }
        // from three different countries
        for (int i = start; i <= M; i++)
            for (int j = i + 1; j <= M; j++)
                for (int k = j + 1; k <= M; k++)
                    if (P[i] && P[j] && P[k])
                        r1 += P[i] * P[j] * P[k];

        long long r2 = 0;
        // at least three of them will be of the same country 
        for (int i = start; i <= M; i++)
        {
            if (P[i] < 3) continue;
            r2 += 1LL * (N - P[i]) * P[i] * (P[i] - 1) * (P[i] - 2) / 6;
            if (P[i] < 4) continue;
            r2 += 1LL * P[i] * (P[i] - 1) * (P[i] - 2) * (P[i] - 3) / 24;
        }
        // must be from at least three different countries
        for (int i = start; i <= M; i++)
            for (int j = i + 1; j <= M; j++)
                for (int k = j + 1; k <= M; k++)
                    if (P[i] && P[j] && P[k] && P[i] + P[j] + P[k] >= 4)
                    {
                        if (P[i] >= 2) r2 += 1LL * P[i] * (P[i] - 1) / 2 * P[j] * P[k];
                        if (P[j] >= 2) r2 += 1LL * P[j] * (P[j] - 1) / 2 * P[i] * P[k];
                        if (P[k] >= 2) r2 += 1LL * P[k] * (P[k] - 1) / 2 * P[i] * P[j];
                    }
        for (int i = 1; i <= M; i++)
            for (int j = i + 1; j <= M; j++)
                for (int k = j + 1; k <= M; k++)
                    for (int l = k + 1; l <= M; l++)
                        if (P[i] && P[j] && P[k] && P[l])
                            r2 += 1LL * P[i] * P[j] * P[k] * P[l];
        cout << r1 << ' ' << r2 << '\n';
    }

    return 0;
}
