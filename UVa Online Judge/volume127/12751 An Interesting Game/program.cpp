// An Interesting Game
// UVa ID: 12751
// Verdict: Accepted
// Submission Date: 2019-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int N, K, X;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> K >> X;
        cout << "Case " << cs << ": ";
        cout << ((1 + N) * N - (X + X + K - 1) * K) / 2 << '\n';
    }

    return 0;
}
