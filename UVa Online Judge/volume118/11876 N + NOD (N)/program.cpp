// N + NOD (N)
// UVa ID: 11876
// Verdict: Accepted
// Submission Date: 2017-11-30
// UVa Run Time: 0.790s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

map<int, map<int, int>> factors;
int primes[MAXN], C;
int S[70000] = {1, 2, 4, 7, 9, 12, 18}, T = 7;

void getDivisors(int n)
{
    int N = n;
    for (int i = 0; i < C && n > 1; i++)
        if (n % primes[i] == 0)
        {
            n /= primes[i];
            factors[N][primes[i]]++;
            if (n > 1 && !factors[n].size()) getDivisors(n);
            for (auto f : factors[n])
                factors[N][f.first] += f.second;
            break;
        }
}

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

    sieve(primes, MAXN, C);

    while (true)
    {
        int D = 1;
        if (!binary_search(primes, primes + C, S[T - 1]))
        {
            getDivisors(S[T - 1]);
            for (auto f : factors[S[T - 1]]) D *= (f.second + 1);
        }
        else D = 2;

        S[T] = S[T - 1] + D;
        if (S[T++] > MAXN) break;
    }
        
    int C, A, B;
    cin >> C;
    for (int c = 1; c <= C; c++)
    {
        cin >> A >> B;
        
        int i = lower_bound(S, S + T, A) - S, j = lower_bound(S, S + T, B) - S;
        if (S[j] > B) j--;
        cout << "Case " << c << ": " << (j - i + 1) << '\n';
    }
    
    return 0;
}
