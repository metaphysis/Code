// N + NOD (N)
// UVa ID: 11876
// Verdict: Accepted
// Submission Date: 2017-11-30
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50010;

void sieve(int *primes, int n, int &C)
{
    C = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[C++] = i;
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN], C;
    int S[70000] = {1, 2, 4, 7, 9, 12, 18}, T = 7;
    
    sieve(primes, MAXN, C);

    while (true)
    {
        int D = 1, N = S[T - 1];
        if (!binary_search(primes, primes + C, N))
        {
            for (int i = 0; i < C && N > 1; i++)
            {
                if (primes[i] * primes[i] > N) break;
                if (N % primes[i] == 0)
                {
                    int c = 0;
                    while (N % primes[i] == 0)
                    {
                        N /= primes[i];
                        c++;
                    }
                    D *= (c + 1);
                }
            }
            if (N > 1) D *= 2;
        }
        else D = 2;

        S[T] = S[T - 1] + D;
        if (S[T++] > 1000000) break;
    }
        
    int cases, A, B;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> A >> B;
        
        int i = lower_bound(S, S + T, A) - S, j = lower_bound(S, S + T, B) - S;
        if (S[j] > B) j--;
        cout << "Case " << c << ": " << (j - i + 1) << '\n';
    }
    
    return 0;
}
