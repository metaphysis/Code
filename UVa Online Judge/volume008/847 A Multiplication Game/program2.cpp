// A Multiplication Game
// UVa ID: 847
// Verdict: Accepted
// Submission Date: 2018-06-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n)
    {
        while (n > 18) n = (n + 17) / 18;
        if (n <= 9) cout << "Stan wins.\n";
        else cout << "Ollie wins.\n";
    }

    return 0;
}
