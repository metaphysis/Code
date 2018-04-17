// Digit Generator
// UVa ID: 1583
// Verdict: Accepted
// Submission Date: 2018-04-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int smallest[100001] = {0};

    for (int i = 1; i <= 100000; i++)
    {
        int n = i, s = i;
        while (n)
        {
            s += n % 10;
            n /= 10;
        }
        if (s <= 100000 && !smallest[s])
            smallest[s] = i;
    }

    int T, N;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N;
        cout << smallest[N] << '\n';
    }

    return 0;
}
