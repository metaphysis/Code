// Goldbach's Conjecture (II)
// UVa ID: 686
// Verdict: Accepted
// Submission Date: 2016-08-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int primes[5000] = { 0 }, number[33000] = { 0 }, prime_count = 0;
    
    for (int i = 2; i < 33000; i++)
        if (number[i] == 0)
        {
            primes[prime_count++] = i;
            for (int j = 2 * i; j < 33000; j += i)
                number[j] = -1;
        }

    int n;
    while (cin >> n, n)
    {
        int count = 0;
        for (int i = 0; i < prime_count && primes[i] <= n / 2; i++)
            if (number[n - primes[i]] == 0)
                count++;
            
        cout << count << '\n';
    }
        
	return 0;
}
