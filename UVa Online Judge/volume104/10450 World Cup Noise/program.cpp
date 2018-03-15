// World Cup Noise
// UVa ID: 10450
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long fibonacci[51] = {1, 2, 3};
    for (int i = 3; i <= 50; i++)
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];

    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << "Scenario #" << c << ":\n";
        cout << fibonacci[n] << '\n';
        cout << '\n';
    }

    return 0;
}
