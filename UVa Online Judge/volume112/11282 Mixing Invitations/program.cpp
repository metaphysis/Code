// Mixing Invitations
// UVa ID: 11282
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long D[24] = {1}, C[24][24] = {};
    for (int i = 2; i <= 20; i++)
        D[i] = i * D[i - 1] + ((i % 2) ? (-1) : 1);
    for (int i = 1; i <= 20; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i][j - 1] * (i - j + 1) / j;
    }

    int N, M;
    while (cin >> N >> M)
    {
        long long cnt = 0;
        for (int i = 0; i <= M; i++)
            cnt += C[N][i] * D[N - i];
        cout << cnt << '\n';
    }

    return 0;
}
