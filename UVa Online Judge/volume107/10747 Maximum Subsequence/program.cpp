// Maximum Subsequence
// UVa ID: 10747
// Verdict: Accepted
// Submission Date: 2021-11-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int ai[10010], bi[10010], positive[10010], negative[10010], pc, nc, zero, N, K;

void sumFirstK()
{
    cout << accumulate(bi, bi + K, 0) << '\n';
}

void sumLastK()
{
    cout << accumulate(bi + N - K, bi + N, 0) << '\n';
}

int sumAll()
{
    int sum = accumulate(positive, positive + pc, 0);
    sum += accumulate(negative, negative + nc, 0);
    return sum;
}

bool cmp(int a, int b)
{
    if (abs(a) != abs(b)) return abs(a) > abs(b);
    return a > b;
}

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> K)
    {
        if (N == 0) break;
        for (int i = 0; i < N; i++) { cin >> ai[i]; bi[i] = ai[i]; }
        sort(ai, ai + N, cmp);
        sort(bi, bi + N);
        pc = nc = zero = 0;
        for (int i = 0; i < K; i++)
        {
            if (ai[i] == 0) { zero = 1; break; }
            if (ai[i] > 0) positive[pc++] = ai[i];
            else negative[nc++] = ai[i];
        }
        if (zero || !nc) { sumLastK(); continue; }
        if (!pc)
        {
            if (K % 2 == 0) sumFirstK();
            else
            {
                if (bi[N - 1] <= 0) sumLastK();
                else
                {
                    int sum = accumulate(ai, ai + K - 1, 0) + bi[N - 1];
                    cout << sum << '\n';
                }
            }
        }
        else
        {
            if (nc % 2 == 0) cout << sumAll() << '\n';
            else
            {
                int pb, nb, pflag = 0, nflag = 0;
                for (int i = K; i < N && (!pflag || !nflag); i++)
                {
                    if (ai[i] > 0 && !pflag)
                    {
                        pflag = 1;
                        pb = ai[i];
                    }
                    if (ai[i] < 0 && !nflag)
                    {
                        nflag = 1;
                        nb = ai[i];
                    }
                }
                
                if (pflag && nflag)
                {
                    if (positive[pc - 1] * pb >= negative[nc - 1] * nb)
                    {
                        int sum = sumAll() - negative[nc - 1] + pb;
                        cout << sum << '\n';
                    }
                    else
                    {
                        int sum = sumAll() - positive[pc - 1] + nb;
                        cout << sum << '\n';
                    }
                }
                else if (pflag)
                {
                    int sum = sumAll() - negative[nc - 1] + pb;
                    cout << sum << '\n';
                }
                else if (nflag)
                {
                    int sum = sumAll() - positive[pc - 1] + nb;
                    cout << sum << '\n';
                }
                else sumLastK();
            }
        }
    }

    return 0;
}
