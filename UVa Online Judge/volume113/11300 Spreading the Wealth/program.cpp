// Spreading the Wealth
// UVa ID: 11300
// Verdict: Accepted
// Submission Date: 2019-07-21
// UVa Run Time: 0.110s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long int LLI;

const int MAXN = 1000010;

LLI C[MAXN], A[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    LLI n;
    while (cin >> n)
    {
        if (n == 0)
        {
            cout << "0\n";
            continue;
        }
        LLI S = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> C[i];
            S += C[i];
        }
        LLI M = S / n;
        A[0] = 0;
        for (int i = 1; i < n; i++)
            A[i] = A[i - 1] + M - C[i];
        sort(A, A + n);
        LLI m = (A[n / 2] + A[(n - 1) / 2]);
        LLI T = 0;
        for (int i = 0; i < n; i++)
            T += abs(m - 2 * A[i]);
        cout << T / 2 << '\n';
    }
    return 0;
}
