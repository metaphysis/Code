// Safe Salutations
// UVa ID: 991
// Verdict: Accepted
// Submission Date: 2016-12-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20;

long long int catalan[MAX_N] = {0, 1};

void getCatalan()
{
    for (int n = 2; n < MAX_N; n++)
        catalan[n] = 2 * catalan[n - 1] * (2 * n - 1) / (n + 1);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    getCatalan();
        
    int n, cases = 0;
    while (cin >> n)
    {
        if (cases++ > 0) cout << '\n';
        cout << catalan[n] << '\n';
    }

	return 0;
}
