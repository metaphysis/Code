// Circular
// UVa ID: 967
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int MAXN = 1000000, primes[MAXN], primeCounter = 0;

    memset(primes, 0, sizeof(primes));

    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
        {
            primes[primeCounter++] = i;
            for (int j = i + i; j < MAXN; j += i) primes[j] = -1;
        }

    int circular[10000], circularCounter = 0;
    for (int k = 0; k < primeCounter; k++)
    {
        bool isCircular = true;
        int originalNumber = primes[k], nextNumber, backupNumber;
        do
        {
            backupNumber = originalNumber / 10;
            nextNumber = originalNumber % 10;
            originalNumber /= 10;

            while (originalNumber > 0)
            {
                nextNumber *= 10;
                originalNumber /= 10;
            }

            nextNumber += backupNumber;
            originalNumber = nextNumber;

            isCircular = binary_search(primes, primes + primeCounter, nextNumber);
            if (!isCircular) break;

        } while (nextNumber != primes[k]);

        if (isCircular) circular[circularCounter++] = primes[k];
    }

    int start, end;
    while (cin >> start, start > 0)
    {
        cin >> end;

        int rangeCounter = 0;
        for (int k = 0; k < circularCounter; k++)
            if (circular[k] >= start && circular[k] <= end)
                rangeCounter++;

        if (rangeCounter == 0) cout << "No Circular Primes.\n";
        else if (rangeCounter == 1) cout << "1 Circular Prime.\n";
        else cout << rangeCounter << " Circular Primes.\n";
    }

    return 0;
}
