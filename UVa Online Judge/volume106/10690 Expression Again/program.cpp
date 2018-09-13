// Expression Again
// UVa ID: 10690
// Verdict: Accepted
// Submission Date: 2017-05-08
// UVa Run Time: 0.210s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, M, T, S[101], A;
    int number[110], sum[101][10001];

    while (cin >> N >> M)
    {
        T = N + M;
        int minNumber = 200;
        for (int i = 1; i <= T; i++)
        {
            cin >> number[i];
            minNumber = min(minNumber, number[i]);
        }

        // Adjust all numbers to make sure number[i] >= 0
        for (int i = 1; i <= T; i++)
            number[i] -= minNumber;

        sort(number + 1, number + T);

        A = 0;
        memset(S, 0, sizeof(S));
        for (int i = 1; i <= T; i++) S[i] = S[i - 1] + number[i], A += number[i];

        memset(sum, 0, sizeof(sum));
        sum[0][0] = 1;

        for (int i = 1; i <= T; i++)
            for (int j = i - 1; j >= 0; j--)
                for (int k = 0; k <= S[i - 1]; k++)
                    if (sum[j][k])
                        sum[j + 1][k + number[i]] = 1;
        
        int maximum = -100000000, minimum = 100000000;
        for (int k = 0; k <= A; k++)
            if (sum[N][k])
            {
                int r = (k + N * minNumber) * (A - k + (T - N) * minNumber);
                maximum = max(maximum, r);
                minimum = min(minimum, r);
            }
            
        cout << maximum << ' ' << minimum << '\n';
    }
    
    return 0;
}
