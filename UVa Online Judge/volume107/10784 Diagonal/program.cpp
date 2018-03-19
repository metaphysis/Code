// Diagonal
// UVa ID: 10784
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Number of diagonal = (n - 3) * n / 2.

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    long long N;
    while (cin >> N, N > 0)
    {
        long long n = sqrt(2 * N);
        while (n * (n - 3) / 2 < N) n++;
        while (n * (n - 3) / 2 >= N) n--;
        cout << "Case " << ++cases << ": " << n + 1 << '\n';
    }

    return 0;
}
