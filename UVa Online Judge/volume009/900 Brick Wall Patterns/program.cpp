// Brick Wall Patterns
// UVa ID: 900
// Verdict: Accepted
// Submission Date: 2017-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long int ways[51] = {1, 2, 3};
    
    for (int i = 3; i < 50; i++) ways[i] = ways[i - 1] + ways[i - 2];
    
    int n;
    while (cin >> n, n) cout << ways[n - 1] << '\n';
    
    return 0;
}
