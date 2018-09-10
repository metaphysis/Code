// Tight Words
// UVa ID: 10081
// Verdict: Accepted
// Submission Date: 2018-09-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int K, N;
    while (cin >> K >> N)
    {
        double cnt[101][10] = {0};
        for (int i = 0; i <= K; i++)
            cnt[1][i] = 1;
        for (int i = 2; i <= N; i++)
        {
            for (int j = 0; j <= K; j++)
                for (int k = 0; k <= K; k++)
                    if (abs(j - k) <= 1)
                        cnt[i][k] += cnt[i - 1][j];
        }
        double total = 0;
        for (int i = 0; i <= K; i++)
            total += cnt[N][i];
        cout << fixed << setprecision(5) << (total * 100.0 / pow(K + 1, N)) << '\n';
    }

    return 0;
}
