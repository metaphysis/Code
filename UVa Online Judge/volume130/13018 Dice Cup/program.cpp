// Dice Cup
// UVa ID: 13018
// Verdict: Accepted
// Submission Date: 2022-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, M, C[64], cases = 0;
    while (cin >> N >> M)
    {
        if (cases++) cout << '\n';
        memset(C, 0, sizeof C);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                C[i + j]++;
        int most = *max_element(C, C + 64);
        for (int i = 1; i <= N + M; i++)
            if (C[i] == most)
                cout << i << '\n';
    }
    return 0;
}
