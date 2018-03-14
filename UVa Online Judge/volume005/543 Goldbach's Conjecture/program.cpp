// Goldbach's Conjecture
// UVa ID: 543
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int primes[1000001] = { 0 };
    
    for (int i = 3; i <= 1000000; i += 2)
        if (primes[i] == 0)
            for (int j = 2 * i; j <= 1000000; j += i)
                primes[j] = -1;
    int n;
    while (cin >> n, n)
    {
        for (int i = 3; i <= 500000; i += 2)
            if (primes[i] == 0 && primes[n - i] == 0)
            {
                cout << n << " = " << i << " + " << (n - i) << '\n';
                break;
            }
    }
        
	return 0;
}
