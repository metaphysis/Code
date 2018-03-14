// Expression Bracketing
// UVa ID: 10312
// Verdict: Accepted
// Submission Date: 2016-09-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30;

long long int catalan[MAX_N] = {0, 1}, superCatalan[MAX_N] = {0, 1};

void getCatalan()
{
    for (int n = 2; n < MAX_N; n++)
        catalan[n] = 2 * catalan[n - 1] * (2 * n - 1) / (n + 1);
}

void getSuperCatalan()
{
    for (int n = 2; n < MAX_N; n++)
        superCatalan[n] = ((6 * n - 3) * superCatalan[n - 1] -
            (n - 2) * superCatalan[n - 2]) / (n + 1);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    getCatalan(), getSuperCatalan();
        
    int n;
    while (cin >> n) cout << superCatalan[n - 1] - catalan[n - 1] << '\n';

	return 0;
}
