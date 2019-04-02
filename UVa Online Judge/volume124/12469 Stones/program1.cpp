// Stones
// UVa ID: 12469
// Verdict: Accepted
// Submission Date: 2019-04-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int fib[20] = {1, 2};
    for (int i = 2; i < 20; i++) fib[i] = fib[i - 1] + fib[i - 2];
    int n;
    while (cin >> n, n)
    {
        if (binary_search(fib, fib + 20, n))
            cout << "Roberto\n";
        else
            cout << "Alicia\n";
    }
    return 0;
}
