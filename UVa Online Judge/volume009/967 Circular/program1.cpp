// Circular
// UVa ID: 967
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int MAXN = 1000000, primes[MAXN], primeCounter = 0;

    memset(primes, 0, sizeof(primes));

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[primeCounter++] = i;
        for (int j = 0; j < primeCounter && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = -1;
            if (!(i % primes[j])) break;
        }
    }

    int circular[10000], circularCounter = 0, remainder[6] = {10, 100, 1000, 10000, 100000, 1000000};
    for (int k = 0; k < primeCounter; k++)
    {
        bool isCircular = true;
        int originalNumber = primes[k], nextNumber, idx;
        do
        {
            idx = 0;
            nextNumber = originalNumber % 10;
            
            while (originalNumber > remainder[idx])
            {
                nextNumber *= 10;
                idx++;
            }

            nextNumber += originalNumber / 10;
            originalNumber = nextNumber;

            isCircular = binary_search(primes, primes + primeCounter, nextNumber);
            if (!isCircular) break;

        } while (nextNumber != primes[k]);

        if (isCircular) circular[circularCounter++] = primes[k];
    }
    
    int range[1000000];
    for (int i = 0, j = 0; i < MAXN; i++)
    {
        range[i] = 0;
        if (i == circular[j])
        {
            range[i] = 1;
            j++;
        }
        range[i] += range[i - 1];
    }
    
    int start, end;
    while (cin >> start, start > 0)
    {
        cin >> end;
        int rangeCounter = range[end] - range[start - 1];
        if (rangeCounter == 0) cout << "No Circular Primes.\n";
        else if (rangeCounter == 1) cout << "1 Circular Prime.\n";
        else cout << rangeCounter << " Circular Primes.\n";
    }

    return 0;
}
