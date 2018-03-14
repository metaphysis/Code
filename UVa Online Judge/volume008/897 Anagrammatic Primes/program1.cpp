// Anagrammatic Primes
// UVa ID: 897
// Verdict: Accepted
// Submission Date: 2016-12-06
// UVa Run Time: 0.060s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int primes[22] = {2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 199, 311, 337, 373, 733, 919, 991};
int level[7] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, upper;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < 7; i++)
            if (n < level[i])
            {
                upper = level[i];
                break;
            }
                
        int k = upper_bound(primes, primes + 22, n) - primes;
        if (k < 22 && primes[k] < upper) cout << primes[k] << '\n';
        else cout << "0\n";
    }
    
	return 0;
}
