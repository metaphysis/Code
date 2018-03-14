// Prime Distance
// UVa ID: 10140
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 47000, MAXE = 1000010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int cnt = 0;
    long long primes[MAXN] = {0};
    
    memset(primes, 0, sizeof(primes));
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < MAXN; j += i)
                primes[j] = 1;
        }

    int visited[MAXE];
    long long L, U;

    while (cin >> L >> U)
    {
        int total = U - L + 1;
        memset(visited, 0, total * sizeof(int));
        for (int i = 0; i < cnt; i++)
        {
            long long n = max(L / primes[i] * primes[i], 2 * primes[i]);
            while (n <= U)
            {
                if (n >= L) visited[n - L] = 1;
                n += primes[i];
            }
            if (primes[i] * primes[i] > U) break;
        }
        if (L == 1) visited[0] = 1;

        long long C1 = 0, C2 = 0, D1 = 0, D2 = 0;
        int first = 0, diff = 0, diff1 = 0x3f3f3f3f, diff2 = 0;
        for (int i = 0; i < total; i++)
        {
            if (visited[i]) continue;
            if (first)
            {
                diff = L + i - first;
                if (diff < diff1) C2 = L + i, C1 = first, diff1 = diff;
                if (diff > diff2) D2 = L + i, D1 = first, diff2 = diff;
            }
            first = L + i;
        }

        if (!diff)
            cout << "There are no adjacent primes.\n";
        else
        {
            cout << C1 << ',' << C2 << " are closest, ";
            cout << D1 << ',' << D2 << " are most distant.\n";
        }
    }

    return 0;
}
