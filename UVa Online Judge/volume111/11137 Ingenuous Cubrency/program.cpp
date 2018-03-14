// Ingenuous Cubrency
// UVa ID: 11137
// Verdict: Accepted
// Submission Date: 2018-01-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int coins[24];
    long long ways[10010] = {0};

    for (int i = 1; i <= 21; i++) coins[i] = i * i * i;
    
    ways[0] = 1;
    for (int i = 1; i <= 21; i++)
        for (int j = coins[i]; j <= 10000; j++)
                ways[j] += ways[j - coins[i]];
        
    int n;
    while (cin >> n) cout << ways[n] << '\n';

    return 0;
}
