// Count DePrimes
// UVa ID: 11408
// Verdict: Accepted
// Submission Date: 2018-10-26
// UVa Run Time: 0.240s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int PRIME = 1, DE_PRIME = 2, COMPOSITE = 3, MAXN = 5000001;

int numbers[MAXN] = {}, sum[MAXN] = {};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!numbers[i])
        {
            numbers[i] = PRIME;
            for (int j = i + i; j < MAXN; j += i)
            {
                sum[j] += i;
                numbers[j] = COMPOSITE;
            }
        }
        else
        {
            if (numbers[sum[i]] == PRIME)
                numbers[i] = DE_PRIME;
            else
                numbers[i] = COMPOSITE;
        }
    }
    for (int i = 2; i < MAXN; i++)
        if (numbers[i] == PRIME || numbers[i] == DE_PRIME)
            numbers[i] = 1 + numbers[i - 1];
        else
            numbers[i] = numbers[i - 1];

    int a, b;
    while (cin >> a, a > 0)
    {
        cin >> b;
        cout << numbers[b] - numbers[a - 1] << '\n';
    }

    return 0;
}
