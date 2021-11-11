// Subset Sum
// UVa ID: 12911
// Verdict: Accepted
// Submission Date: 2021-11-11
// UVa Run Time: 1.630s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, T, si[41];
map<long long, int> Ca, Cb;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> T)
    {
        for (int i = 0; i < N; i++) cin >> si[i];
        sort(si, si + N);
        int Na = N / 2;
        if (Na == 0) Na++;
        int Nb = N - Na;
        Ca.clear();
        for (int i = 1; i < (1 << Na); i++)
        {
            long long sum = 0;
            for (int j = 0; j < Na; j++)
                if (i & (1 << j))
                    sum += si[j];
            Ca[sum]++;
        }
        Cb.clear();
        for (int i = 1; i < (1 << Nb); i++)
        {
            long long sum = 0;
            for (int j = 0; j < Nb; j++)
                if (i & (1 << j))
                    sum += si[Na + j];
            Cb[sum]++;
        }
        long long cnt = 0;
        for (auto p : Ca)
            if (Cb.count(T - p.first))
                cnt += 1LL * p.second * Cb[T - p.first];
        cout << cnt + Ca[T] + Cb[T] << '\n';
    }

    return 0;
}
