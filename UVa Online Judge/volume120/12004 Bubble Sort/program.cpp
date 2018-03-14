// Bubble Sort
// UVa ID: 12004
// Verdict: Accepted
// Submission Date: 2018-03-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    long long n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        cin >> n;
        n = n * (n - 1);
        if (n % 4 == 0) cout << n / 4 << '\n';
        else cout << n / 2 << "/2\n";
    }

    return 0;
}
