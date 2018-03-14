// Simply Emirp
// UVa ID: 10235
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1000010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXV] = {0}, cnt = 0;
    for (int i = 2; i < MAXV; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXV; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }
    
    int n;
    while (cin >> n)
    {
        cout << n;

        if (binary_search(primes, primes + cnt, n) == false)
        {
            cout << " is not prime.\n";
            continue;
        }
        
        int backup = n, nn = 0;
        while (n)
        {
            nn = nn * 10 + n % 10;
            n /= 10;
        }
        
        if (backup != nn && binary_search(primes, primes + cnt, nn))
            cout << " is emirp.\n";
        else
            cout << " is prime.\n";
    }
    
    return 0;
}
