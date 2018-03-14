// Squares
// UVa ID: 11407
// Verdict: Accepted
// Submission Date: 2018-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    const int INF = 0x3fffffff;
    int cases, n, coins[110], terms[10010];

    for (int i = 1; i <= 100; i++)
        coins[i] = i * i;

    for (int i = 0; i <= 10000; i++)
        terms[i] = INF;
    terms[0] = 0;

    for (int i = 1; i <= 100; i++)
    {
        for (int j = coins[i]; j <= 10000; j++)
            terms[j] = min(terms[j], terms[j - coins[i]] + 1);
    }
        
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << terms[n] << '\n';
    }

    return 0;
}
