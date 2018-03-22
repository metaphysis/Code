// Prime Frequency
// UVa ID: 10789
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[2001] = {0}, pcnt = 0;
    for (int i = 2; i * i < 2001; i++)
        if (!primes[i])
            for (int j = i * i; j < 2001; j += i)
                primes[j] = 1;
    for (int i = 2; i < 2001; i++)
        if (!primes[i])
            primes[pcnt++] = i;

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        string line;
        cin >> line;
        map<char, int> cnt;
        for (auto letter : line) cnt[letter]++;
        
        bool printed = false;
        for (auto p : cnt)
        {
            if (binary_search(primes, primes + pcnt, p.second))
            {
                printed = true;
                cout << p.first;
            }
        }
        if (!printed) cout << "empty";
        cout << '\n';
    }

    return 0;
}
