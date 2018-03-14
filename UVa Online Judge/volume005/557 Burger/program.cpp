// Burger
// UVa ID: 557
// Verdict: Accepted
// Submission Date: 2016-08-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    // Bernoulli trial
    double probability[50001] = { 1 };
    for (int i = 1; i <= 50000; i++)
        probability[i] = probability[i - 1] * (long double)(2 * i - 1) / (long double)(2 * i);
    
    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << fixed << setprecision(4) << (1 - probability[n / 2 - 1]) << '\n';
    }
    
	return 0;
}
